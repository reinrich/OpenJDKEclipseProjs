#line 1 "ad_s390.hpp"
//
// Copyright (c) 2017, 2026, Oracle and/or its affiliates. All rights reserved.
// Copyright (c) 2017, 2024 SAP SE. All rights reserved.
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


#ifndef GENERATED_ADFILES_AD_HPP
#define GENERATED_ADFILES_AD_HPP

#include "memory/allocation.hpp"
#include "oops/compressedOops.hpp"
#include "code/nativeInst.hpp"
#include "opto/output.hpp"
#include "opto/machnode.hpp"
#include "opto/node.hpp"
#include "opto/regalloc.hpp"
#include "opto/subnode.hpp"
#include "opto/vectornode.hpp"

#define  DEFAULT_COST  (100)  
// value == 100 
#define  DEFAULT_COST_LOW  (80)  
// value == 80 
#define  DEFAULT_COST_HIGH  (120)  
// value == 120 
#define  HUGE_COST  (1000000)  
// value == 1000000 
#define  ALU_REG_COST  (DEFAULT_COST)  
// value == 100 
#define  ALU_MEMORY_COST  (150)  
// value == 150 
#define  MEMORY_REF_COST_HI  (2 * DEFAULT_COST+20)  
// value == 220 
#define  MEMORY_REF_COST  (2 * DEFAULT_COST)  
// value == 200 
#define  MEMORY_REF_COST_LO  (2 * DEFAULT_COST-20)  
// value == 180 
#define  BRANCH_COST  (DEFAULT_COST * 3)  
// value == 300 
#define  CALL_COST  (DEFAULT_COST * 3)  
// value == 300 

enum MachOperands {
  /*    0 */  UNIVERSE,
  /*    1 */  LABEL,
  /*    2 */  SREGI,
  /*    3 */  SREGP,
  /*    4 */  SREGF,
  /*    5 */  SREGD,
  /*    6 */  SREGL,
  /*    7 */  METHOD,
  /*    8 */  VECX,
  /*    9 */  V16TEMPREG,
  /*   10 */  V17TEMPREG,
  /*   11 */  V18TEMPREG,
  /*   12 */  V19TEMPREG,
  /*   13 */  V20TEMPREG,
  /*   14 */  V21TEMPREG,
  /*   15 */  V22TEMPREG,
  /*   16 */  V23TEMPREG,
  /*   17 */  V24TEMPREG,
  /*   18 */  V25TEMPREG,
  /*   19 */  IMMB_MINUS1,
  /*   20 */  IMMB_N0M1,
  /*   21 */  IMMS_MINUS1,
  /*   22 */  IMMS_N0M1,
  /*   23 */  IMMI,
  /*   24 */  IMMI20,
  /*   25 */  IMMI16,
  /*   26 */  IMMI8,
  /*   27 */  IMMI_0,
  /*   28 */  IMMI_MINUS1,
  /*   29 */  IMMI_N0M1,
  /*   30 */  UIMMI,
  /*   31 */  UIMMI16,
  /*   32 */  UIMMI12,
  /*   33 */  UIMMI8,
  /*   34 */  SSLENDW,
  /*   35 */  IMMI_1,
  /*   36 */  IMMI_16,
  /*   37 */  IMMI_24,
  /*   38 */  IMMI_32_63,
  /*   39 */  UIMMI_LL1,
  /*   40 */  UIMMI_LH1,
  /*   41 */  IMML,
  /*   42 */  IMML32,
  /*   43 */  IMML20,
  /*   44 */  IMML16,
  /*   45 */  IMML8,
  /*   46 */  UIMML32,
  /*   47 */  UIMML16,
  /*   48 */  UIMML12,
  /*   49 */  IMML_FFFFFFFF,
  /*   50 */  IMML_0,
  /*   51 */  UIMML_LL1,
  /*   52 */  UIMML_LH1,
  /*   53 */  UIMML_HL1,
  /*   54 */  UIMML_HH1,
  /*   55 */  IMML_32BITS,
  /*   56 */  IMMP,
  /*   57 */  IMMP16,
  /*   58 */  IMMP8,
  /*   59 */  IMMP0,
  /*   60 */  IMMN,
  /*   61 */  IMMNKLASS,
  /*   62 */  IMMN8,
  /*   63 */  IMMN0,
  /*   64 */  IMMD,
  /*   65 */  IMMDPM0,
  /*   66 */  IMMDP0,
  /*   67 */  IMMF,
  /*   68 */  IMMFPM0,
  /*   69 */  IMMFP0,
  /*   70 */  IREGI,
  /*   71 */  NOARG_IREGI,
  /*   72 */  REVENREGI,
  /*   73 */  RODDREGI,
  /*   74 */  RARG1REGI,
  /*   75 */  RARG2REGI,
  /*   76 */  RARG3REGI,
  /*   77 */  RARG4REGI,
  /*   78 */  RARG5REGI,
  /*   79 */  NOODD_IREGI,
  /*   80 */  IREGP,
  /*   81 */  THREADREGP,
  /*   82 */  R10TEMPREGP,
  /*   83 */  R11TEMPREGP,
  /*   84 */  NOARG_IREGP,
  /*   85 */  RARG1REGP,
  /*   86 */  RARG2REGP,
  /*   87 */  RARG3REGP,
  /*   88 */  RARG4REGP,
  /*   89 */  RARG5REGP,
  /*   90 */  MEMORYREGP,
  /*   91 */  REVENREGP,
  /*   92 */  RODDREGP,
  /*   93 */  IREGN,
  /*   94 */  NOARG_IREGN,
  /*   95 */  RARG1REGN,
  /*   96 */  RARG2REGN,
  /*   97 */  RARG3REGN,
  /*   98 */  RARG4REGN,
  /*   99 */  RARG5REGN,
  /*  100 */  IREGL,
  /*  101 */  REVENREGL,
  /*  102 */  RODDREGL,
  /*  103 */  ALLRODDREGL,
  /*  104 */  RARG1REGL,
  /*  105 */  RARG5REGL,
  /*  106 */  FLAGSREG,
  /*  107 */  REGD,
  /*  108 */  REGF,
  /*  109 */  INLINE_CACHE_REGP,
  /*  110 */  INDIRECT,
  /*  111 */  INDOFFSET20,
  /*  112 */  INDOFFSET20NARROW,
  /*  113 */  INDOFFSET12,
  /*  114 */  INDOFFSET12NARROW,
  /*  115 */  INDINDEX,
  /*  116 */  INDOFFSET20INDEX,
  /*  117 */  INDOFFSET20INDEXNARROW,
  /*  118 */  INDOFFSET12INDEX,
  /*  119 */  INDOFFSET12INDEXNARROW,
  /*  120 */  STACKSLOTI,
  /*  121 */  STACKSLOTP,
  /*  122 */  STACKSLOTF,
  /*  123 */  STACKSLOTD,
  /*  124 */  STACKSLOTL,
  /*  125 */  CMPOPT,
  /*  126 */  CMPOPF,
  /*  127 */  CMPOP,
  // last operand
  /*  128 */  MEMORY,
  /*  129 */  MEMORYRXY,
  /*  130 */  MEMORYRX,
  /*  131 */  MEMORYRSY,
  /*  132 */  MEMORYRS,
  /*  133 */  IREGN_P2N,
  /*  134 */  IREGP_N2P,
  // last operand class
  /*  135 */  _DECODEN_IREGN_,
  /*  136 */  _ADDP_MEMORYREGP_IREGL,
  /*  137 */  _ADDP__DECODEN_IREGN__IREGL,
  /*  138 */  _LOADB_MEMORY_,
  /*  139 */  _LOADUB_MEMORY_,
  /*  140 */  _LOADS_MEMORY_,
  /*  141 */  _LOADUS_MEMORY_,
  /*  142 */  _LOADI_MEMORY_,
  /*  143 */  _CONVI2L__LOADI_MEMORY__,
  /*  144 */  _LOADP_MEMORY_,
  /*  145 */  _LOADN_MEMORY_,
  /*  146 */  _LOADNKLASS_MEMORY_,
  /*  147 */  _BINARY_IREGL_IREGN,
  /*  148 */  _BINARY_CMPOP_FLAGSREG,
  /*  149 */  _BINARY_IREGN_IREGN_P2N,
  /*  150 */  _BINARY_IREGN_IMMN0,
  /*  151 */  _BINARY_IREGI_IREGI,
  /*  152 */  _BINARY_IREGI_IMMI16,
  /*  153 */  _BINARY_IREGP_IREGP_N2P,
  /*  154 */  _BINARY_IREGP_IMMP0,
  /*  155 */  _BINARY_CMPOPF_FLAGSREG,
  /*  156 */  _BINARY_REGF_REGF,
  /*  157 */  _BINARY_REGD_REGD,
  /*  158 */  _BINARY_IREGL_IREGL,
  /*  159 */  _BINARY_IREGL_IMML16,
  /*  160 */  _BINARY_RARG5REGI_IREGI,
  /*  161 */  _BINARY_RARG5REGL_IREGL,
  /*  162 */  _BINARY_RARG5REGP_IREGP_N2P,
  /*  163 */  _BINARY_RARG5REGN_IREGN_P2N,
  /*  164 */  _ADDI_IREGI_IREGI,
  /*  165 */  _LOADI_MEMORYRSY_,
  /*  166 */  _ADDI__LOADI_MEMORYRSY__IMMI8,
  /*  167 */  _CONVI2L_IREGI_,
  /*  168 */  _LOADL_MEMORY_,
  /*  169 */  _ADDL_IREGL_IREGL,
  /*  170 */  _LOADL_MEMORYRSY_,
  /*  171 */  _ADDL__LOADL_MEMORYRSY__IMML8,
  /*  172 */  _ADDP_IREGP_N2P_IREGL,
  /*  173 */  _LOADP_MEMORYRSY_,
  /*  174 */  _ADDP__LOADP_MEMORYRSY__IMML8,
  /*  175 */  _CASTP2X_IREGP_N2P_,
  /*  176 */  _LSHIFTI_IREGI_IMMI8,
  /*  177 */  _URSHIFTI_IREGI_IMMI8,
  /*  178 */  _LSHIFTL_IREGL_IMMI8,
  /*  179 */  _URSHIFTL_IREGL_IMMI8,
  /*  180 */  _LOADF_MEMORYRX_,
  /*  181 */  _LOADD_MEMORYRX_,
  /*  182 */  _NEGF_REGF_,
  /*  183 */  _NEGD_REGD_,
  /*  184 */  _BINARY_REGF__LOADF_MEMORYRX_,
  /*  185 */  _BINARY_REGD__LOADD_MEMORYRX_,
  /*  186 */  _BINARY__LOADF_MEMORYRX__REGF,
  /*  187 */  _BINARY__LOADD_MEMORYRX__REGD,
  /*  188 */  _ABSF_REGF_,
  /*  189 */  _ABSD_REGD_,
  /*  190 */  _LSHIFTI_IREGI_IMMI_16,
  /*  191 */  _LSHIFTI_IREGI_IMMI_24,
  /*  192 */  _RSHIFTL_IREGL_IMMI_32_63,
  /*  193 */  _CMPU_IREGI_UIMMI16,
  /*  194 */  _CMPU_IREGI_IREGI,
  /*  195 */  _CMPP_IREGP_N2P_IMMP0,
  /*  196 */  _CMPN_IREGN_P2N_IMMN0,
  /*  197 */  _ABSI_IREGI_,
  /*  198 */  _CMPI_IREGI_IREGI,
  /*  199 */  _CMPL_IREGL_IREGL,
  /*  200 */  _CMPP_IREGP_IREGP,
  /*  201 */  _CMPP__DECODEN_IREGN___DECODEN_IREGN_,
  /*  202 */  _CMPI_IREGI_IMMI8,
  /*  203 */  _CMPU_IREGI_UIMMI8,
  /*  204 */  _CMPL_IREGL_IMML8,
  /*  205 */  _CMPP_IREGP_IMMP8,
  /*  206 */  _CMPP__DECODEN_IREGN__IMMP0,
  /*  207 */  _DECODEN_IMMN8_,
  /*  208 */  _CMPP__DECODEN_IREGN___DECODEN_IMMN8_,
  /*  209 */  _BINARY_RARG1REGP_IMMP,
  /*  210 */  _BINARY_IREGP_IREGP,
  /*  211 */  _BINARY_IREGP_RARG2REGI,
  /*  212 */  _BINARY_IREGP_RARG5REGI,
  /*  213 */  _BINARY_IREGP_IREGI,
  /*  214 */  _BINARY_IMMP_IMMI_1,
  /*  215 */  _BINARY_IREGP_IMMI16,
  /*  216 */  _BINARY_IREGP_IMMI,
  /*  217 */  _ENCODEP_IREGP_,
  // last internally defined operand
  _LAST_MACH_OPER
};

enum MachOpcodes {
  /*    0 */  Universe_rule,
  /*    1 */  label_rule,
  /*    2 */  sRegI_rule,
  /*    3 */  sRegP_rule,
  /*    4 */  sRegF_rule,
  /*    5 */  sRegD_rule,
  /*    6 */  sRegL_rule,
  /*    7 */  method_rule,
  /*    8 */  vecX_rule,
  /*    9 */  v16TempReg_rule,
  /*   10 */  v17TempReg_rule,
  /*   11 */  v18TempReg_rule,
  /*   12 */  v19TempReg_rule,
  /*   13 */  v20TempReg_rule,
  /*   14 */  v21TempReg_rule,
  /*   15 */  v22TempReg_rule,
  /*   16 */  v23TempReg_rule,
  /*   17 */  v24TempReg_rule,
  /*   18 */  v25TempReg_rule,
  /*   19 */  immB_minus1_rule,
  /*   20 */  immB_n0m1_rule,
  /*   21 */  immS_minus1_rule,
  /*   22 */  immS_n0m1_rule,
  /*   23 */  immI_rule,
  /*   24 */  immI20_rule,
  /*   25 */  immI16_rule,
  /*   26 */  immI8_rule,
  /*   27 */  immI_0_rule,
  /*   28 */  immI_minus1_rule,
  /*   29 */  immI_n0m1_rule,
  /*   30 */  uimmI_rule,
  /*   31 */  uimmI16_rule,
  /*   32 */  uimmI12_rule,
  /*   33 */  uimmI8_rule,
  /*   34 */  SSlenDW_rule,
  /*   35 */  immI_1_rule,
  /*   36 */  immI_16_rule,
  /*   37 */  immI_24_rule,
  /*   38 */  immI_32_63_rule,
  /*   39 */  uimmI_LL1_rule,
  /*   40 */  uimmI_LH1_rule,
  /*   41 */  immL_rule,
  /*   42 */  immL32_rule,
  /*   43 */  immL20_rule,
  /*   44 */  immL16_rule,
  /*   45 */  immL8_rule,
  /*   46 */  uimmL32_rule,
  /*   47 */  uimmL16_rule,
  /*   48 */  uimmL12_rule,
  /*   49 */  immL_FFFFFFFF_rule,
  /*   50 */  immL_0_rule,
  /*   51 */  uimmL_LL1_rule,
  /*   52 */  uimmL_LH1_rule,
  /*   53 */  uimmL_HL1_rule,
  /*   54 */  uimmL_HH1_rule,
  /*   55 */  immL_32bits_rule,
  /*   56 */  immP_rule,
  /*   57 */  immP16_rule,
  /*   58 */  immP8_rule,
  /*   59 */  immP0_rule,
  /*   60 */  immN_rule,
  /*   61 */  immNKlass_rule,
  /*   62 */  immN8_rule,
  /*   63 */  immN0_rule,
  /*   64 */  immD_rule,
  /*   65 */  immDpm0_rule,
  /*   66 */  immDp0_rule,
  /*   67 */  immF_rule,
  /*   68 */  immFpm0_rule,
  /*   69 */  immFp0_rule,
  /*   70 */  iRegI_rule,
  /*   71 */  noArg_iRegI_rule,
  /*   72 */  revenRegI_rule,
  /*   73 */  roddRegI_rule,
  /*   74 */  rarg1RegI_rule,
  /*   75 */  rarg2RegI_rule,
  /*   76 */  rarg3RegI_rule,
  /*   77 */  rarg4RegI_rule,
  /*   78 */  rarg5RegI_rule,
  /*   79 */  noOdd_iRegI_rule,
  /*   80 */  iRegP_rule,
  /*   81 */  threadRegP_rule,
  /*   82 */  r10TempRegP_rule,
  /*   83 */  r11TempRegP_rule,
  /*   84 */  noArg_iRegP_rule,
  /*   85 */  rarg1RegP_rule,
  /*   86 */  rarg2RegP_rule,
  /*   87 */  rarg3RegP_rule,
  /*   88 */  rarg4RegP_rule,
  /*   89 */  rarg5RegP_rule,
  /*   90 */  memoryRegP_rule,
  /*   91 */  revenRegP_rule,
  /*   92 */  roddRegP_rule,
  /*   93 */  iRegN_rule,
  /*   94 */  noArg_iRegN_rule,
  /*   95 */  rarg1RegN_rule,
  /*   96 */  rarg2RegN_rule,
  /*   97 */  rarg3RegN_rule,
  /*   98 */  rarg4RegN_rule,
  /*   99 */  rarg5RegN_rule,
  /*  100 */  iRegL_rule,
  /*  101 */  revenRegL_rule,
  /*  102 */  roddRegL_rule,
  /*  103 */  allRoddRegL_rule,
  /*  104 */  rarg1RegL_rule,
  /*  105 */  rarg5RegL_rule,
  /*  106 */  flagsReg_rule,
  /*  107 */  regD_rule,
  /*  108 */  regF_rule,
  /*  109 */  inline_cache_regP_rule,
  /*  110 */  indirect_rule,
  /*  111 */  indOffset20_rule,
  /*  112 */  indOffset20Narrow_rule,
  /*  113 */  indOffset12_rule,
  /*  114 */  indOffset12Narrow_rule,
  /*  115 */  indIndex_rule,
  /*  116 */  indOffset20index_rule,
  /*  117 */  indOffset20indexNarrow_rule,
  /*  118 */  indOffset12index_rule,
  /*  119 */  indOffset12indexNarrow_rule,
  /*  120 */  stackSlotI_rule,
  /*  121 */  stackSlotP_rule,
  /*  122 */  stackSlotF_rule,
  /*  123 */  stackSlotD_rule,
  /*  124 */  stackSlotL_rule,
  /*  125 */  cmpOpT_rule,
  /*  126 */  cmpOpF_rule,
  /*  127 */  cmpOp_rule,
  // last operand
  /*  128 */  memory_rule,
  /*  129 */  memoryRXY_rule,
  /*  130 */  memoryRX_rule,
  /*  131 */  memoryRSY_rule,
  /*  132 */  memoryRS_rule,
  /*  133 */  iRegN_P2N_rule,
  /*  134 */  iRegP_N2P_rule,
  // last operand class
  /*  135 */  _DecodeN_iRegN__rule,
  /*  136 */  _AddP_memoryRegP_iRegL_rule,
  /*  137 */  _AddP__DecodeN_iRegN__iRegL_rule,
  /*  138 */  _LoadB_memory__rule,
  /*  139 */  _LoadUB_memory__rule,
  /*  140 */  _LoadS_memory__rule,
  /*  141 */  _LoadUS_memory__rule,
  /*  142 */  _LoadI_memory__rule,
  /*  143 */  _ConvI2L__LoadI_memory___rule,
  /*  144 */  _LoadP_memory__rule,
  /*  145 */  _LoadN_memory__rule,
  /*  146 */  _LoadNKlass_memory__rule,
  /*  147 */  _Binary_iRegL_iRegN_rule,
  /*  148 */  _Binary_cmpOp_flagsReg_rule,
  /*  149 */  _Binary_iRegN_iRegN_P2N_rule,
  /*  150 */  _Binary_iRegN_immN0_rule,
  /*  151 */  _Binary_iRegI_iRegI_rule,
  /*  152 */  _Binary_iRegI_immI16_rule,
  /*  153 */  _Binary_iRegP_iRegP_N2P_rule,
  /*  154 */  _Binary_iRegP_immP0_rule,
  /*  155 */  _Binary_cmpOpF_flagsReg_rule,
  /*  156 */  _Binary_regF_regF_rule,
  /*  157 */  _Binary_regD_regD_rule,
  /*  158 */  _Binary_iRegL_iRegL_rule,
  /*  159 */  _Binary_iRegL_immL16_rule,
  /*  160 */  _Binary_rarg5RegI_iRegI_rule,
  /*  161 */  _Binary_rarg5RegL_iRegL_rule,
  /*  162 */  _Binary_rarg5RegP_iRegP_N2P_rule,
  /*  163 */  _Binary_rarg5RegN_iRegN_P2N_rule,
  /*  164 */  _AddI_iRegI_iRegI_rule,
  /*  165 */  _LoadI_memoryRSY__rule,
  /*  166 */  _AddI__LoadI_memoryRSY__immI8_rule,
  /*  167 */  _ConvI2L_iRegI__rule,
  /*  168 */  _LoadL_memory__rule,
  /*  169 */  _AddL_iRegL_iRegL_rule,
  /*  170 */  _LoadL_memoryRSY__rule,
  /*  171 */  _AddL__LoadL_memoryRSY__immL8_rule,
  /*  172 */  _AddP_iRegP_N2P_iRegL_rule,
  /*  173 */  _LoadP_memoryRSY__rule,
  /*  174 */  _AddP__LoadP_memoryRSY__immL8_rule,
  /*  175 */  _CastP2X_iRegP_N2P__rule,
  /*  176 */  _LShiftI_iRegI_immI8_rule,
  /*  177 */  _URShiftI_iRegI_immI8_rule,
  /*  178 */  _LShiftL_iRegL_immI8_rule,
  /*  179 */  _URShiftL_iRegL_immI8_rule,
  /*  180 */  _LoadF_memoryRX__rule,
  /*  181 */  _LoadD_memoryRX__rule,
  /*  182 */  _NegF_regF__rule,
  /*  183 */  _NegD_regD__rule,
  /*  184 */  _Binary_regF__LoadF_memoryRX__rule,
  /*  185 */  _Binary_regD__LoadD_memoryRX__rule,
  /*  186 */  _Binary__LoadF_memoryRX__regF_rule,
  /*  187 */  _Binary__LoadD_memoryRX__regD_rule,
  /*  188 */  _AbsF_regF__rule,
  /*  189 */  _AbsD_regD__rule,
  /*  190 */  _LShiftI_iRegI_immI_16_rule,
  /*  191 */  _LShiftI_iRegI_immI_24_rule,
  /*  192 */  _RShiftL_iRegL_immI_32_63_rule,
  /*  193 */  _CmpU_iRegI_uimmI16_rule,
  /*  194 */  _CmpU_iRegI_iRegI_rule,
  /*  195 */  _CmpP_iRegP_N2P_immP0_rule,
  /*  196 */  _CmpN_iRegN_P2N_immN0_rule,
  /*  197 */  _AbsI_iRegI__rule,
  /*  198 */  _CmpI_iRegI_iRegI_rule,
  /*  199 */  _CmpL_iRegL_iRegL_rule,
  /*  200 */  _CmpP_iRegP_iRegP_rule,
  /*  201 */  _CmpP__DecodeN_iRegN___DecodeN_iRegN__rule,
  /*  202 */  _CmpI_iRegI_immI8_rule,
  /*  203 */  _CmpU_iRegI_uimmI8_rule,
  /*  204 */  _CmpL_iRegL_immL8_rule,
  /*  205 */  _CmpP_iRegP_immP8_rule,
  /*  206 */  _CmpP__DecodeN_iRegN__immP0_rule,
  /*  207 */  _DecodeN_immN8__rule,
  /*  208 */  _CmpP__DecodeN_iRegN___DecodeN_immN8__rule,
  /*  209 */  _Binary_rarg1RegP_immP_rule,
  /*  210 */  _Binary_iRegP_iRegP_rule,
  /*  211 */  _Binary_iRegP_rarg2RegI_rule,
  /*  212 */  _Binary_iRegP_rarg5RegI_rule,
  /*  213 */  _Binary_iRegP_iRegI_rule,
  /*  214 */  _Binary_immP_immI_1_rule,
  /*  215 */  _Binary_iRegP_immI16_rule,
  /*  216 */  _Binary_iRegP_immI_rule,
  /*  217 */  _EncodeP_iRegP__rule,
  // last internally defined operand
  /*  218 */  regI_to_stkI_rule,
  /*  219 */  regL_to_stkL_rule,
  /*  220 */  regP_to_stkP_rule,
  /*  221 */  regF_to_stkF_rule,
  /*  222 */  regD_to_stkD_rule,
  /*  223 */  stfSSD_rule,
  /*  224 */  stfSSF_rule,
  /*  225 */  stkI_to_regI_rule,
  /*  226 */  stkL_to_regL_rule,
  /*  227 */  stkP_to_regP_rule,
  /*  228 */  stkF_to_regF_rule,
  /*  229 */  stkD_to_regD_rule,
  /*  230 */  loadConI_rule,
  /*  231 */  loadConI16_rule,
  /*  232 */  loadConI_0_rule,
  /*  233 */  loadConUI16_rule,
  /*  234 */  loadConL_pcrelTOC_rule,
  /*  235 */  loadConL32_rule,
  /*  236 */  loadConL16_rule,
  /*  237 */  loadConL_0_rule,
  /*  238 */  loadConP_pcrelTOC_rule,
  /*  239 */  loadConP0_rule,
  /*  240 */  loadConF_dynTOC_rule,
  /*  241 */  loadConD_dynTOC_rule,
  /*  242 */  loadConF0_rule,
  /*  243 */  loadConD0_rule,
  /*  244 */  loadConN_rule,
  /*  245 */  loadConN0_rule,
  /*  246 */  loadConNKlass_rule,
  /*  247 */  castP2X_loadP_rule,
  /*  248 */  loadBase_rule,
  /*  249 */  compN_iRegN_rule,
  /*  250 */  compN_iRegN_immN_rule,
  /*  251 */  compNKlass_iRegN_immN_rule,
  /*  252 */  compN_iRegN_immN0_rule,
  /*  253 */  castX2P_rule,
  /*  254 */  castP2X_rule,
  /*  255 */  tlsLoadP_rule,
  /*  256 */  checkCastPP_rule,
  /*  257 */  castPP_rule,
  /*  258 */  castII_rule,
  /*  259 */  castLL_rule,
  /*  260 */  castFF_rule,
  /*  261 */  castDD_rule,
  /*  262 */  castVV_rule,
  /*  263 */  overflowAddI_reg_reg_rule,
  /*  264 */  overflowAddI_reg_imm_rule,
  /*  265 */  overflowAddL_reg_reg_rule,
  /*  266 */  overflowAddL_reg_imm_rule,
  /*  267 */  overflowSubI_reg_reg_rule,
  /*  268 */  overflowSubI_reg_imm_rule,
  /*  269 */  overflowSubL_reg_reg_rule,
  /*  270 */  overflowSubL_reg_imm_rule,
  /*  271 */  overflowNegI_rReg_rule,
  /*  272 */  overflowNegL_rReg_rule,
  /*  273 */  MoveF2I_stack_reg_rule,
  /*  274 */  MoveI2F_stack_reg_rule,
  /*  275 */  MoveD2L_stack_reg_rule,
  /*  276 */  MoveL2D_stack_reg_rule,
  /*  277 */  compI_reg_reg_rule,
  /*  278 */  compI_reg_imm_rule,
  /*  279 */  compI_reg_imm16_rule,
  /*  280 */  compI_reg_imm0_rule,
  /*  281 */  compI_reg_mem_rule,
  /*  282 */  compU_reg_reg_rule,
  /*  283 */  compU_reg_uimm_rule,
  /*  284 */  compU_reg_mem_rule,
  /*  285 */  compL_reg_reg_rule,
  /*  286 */  compL_reg_regI_rule,
  /*  287 */  compL_reg_imm32_rule,
  /*  288 */  compL_reg_imm16_rule,
  /*  289 */  compL_reg_imm0_rule,
  /*  290 */  compL_conv_reg_imm0_rule,
  /*  291 */  compL_reg_mem_rule,
  /*  292 */  compL_reg_memI_rule,
  /*  293 */  compUL_reg_reg_rule,
  /*  294 */  compUL_reg_imm32_rule,
  /*  295 */  compP_reg_reg_rule,
  /*  296 */  compP_reg_imm0_rule,
  /*  297 */  compP_decode_reg_imm0_rule,
  /*  298 */  compP_reg_mem_rule,
  /*  299 */  cmpF_cc_rule,
  /*  300 */  cmpD_cc_rule,
  /*  301 */  cmpF_cc_mem_rule,
  /*  302 */  cmpD_cc_mem_rule,
  /*  303 */  cmpF0_cc_rule,
  /*  304 */  cmpD0_cc_rule,
  /*  305 */  cmpFastLock_rule,
  /*  306 */  cmpFastUnlock_rule,
  /*  307 */  expand_LoadLogical_I2L_rule,
  /*  308 */  Repl8B_imm_rule,
  /*  309 */  Repl8B_imm0_rule,
  /*  310 */  Repl8B_immm1_rule,
  /*  311 */  Repl4S_imm_rule,
  /*  312 */  Repl4S_imm0_rule,
  /*  313 */  Repl4S_immm1_rule,
  /*  314 */  repl8S_reg_Ex_rule,
  /*  315 */  repl8S_immIminus1_rule,
  /*  316 */  repl8S_immI0_rule,
  /*  317 */  Repl2I_imm_rule,
  /*  318 */  Repl2I_imm0_rule,
  /*  319 */  Repl2I_immm1_rule,
  /*  320 */  repl4I_reg_Ex_rule,
  /*  321 */  repl4I_immI0_rule,
  /*  322 */  repl4I_immIminus1_rule,
  /*  323 */  Repl2F_imm_rule,
  /*  324 */  Repl2F_imm0_rule,
  /*  325 */  repl4F_reg_Ex_rule,
  /*  326 */  repl4F_immF0_rule,
  /*  327 */  repl2D_reg_Ex_rule,
  /*  328 */  repl2D_immD0_rule,
  /*  329 */  repl16B_reg_Ex_rule,
  /*  330 */  repl16B_immIminus1_rule,
  /*  331 */  repl16B_immI0_rule,
  /*  332 */  repl2L_reg_Ex_rule,
  /*  333 */  repl2L_immIminus1_rule,
  /*  334 */  repl2L_immI0_rule,
  /*  335 */  reinterpret_rule,
  /*  336 */  reinterpretX_rule,
  /*  337 */  vsqrt4F_reg_rule,
  /*  338 */  vsqrt2D_reg_rule,
  /*  339 */  vpopcnt_reg_rule,
  /*  340 */  loadB_rule,
  /*  341 */  loadB2L_rule,
  /*  342 */  loadUB_rule,
  /*  343 */  loadUB2L_rule,
  /*  344 */  loadS_rule,
  /*  345 */  loadS2L_rule,
  /*  346 */  loadUS_rule,
  /*  347 */  loadUS2L_rule,
  /*  348 */  loadI_rule,
  /*  349 */  loadI2L_rule,
  /*  350 */  loadUI2L_rule,
  /*  351 */  loadRange_rule,
  /*  352 */  loadL_rule,
  /*  353 */  loadL_unaligned_rule,
  /*  354 */  loadP_rule,
  /*  355 */  loadKlass_rule,
  /*  356 */  loadTOC_rule,
  /*  357 */  loadF_rule,
  /*  358 */  loadD_rule,
  /*  359 */  loadD_unaligned_rule,
  /*  360 */  storeB_rule,
  /*  361 */  storeC_rule,
  /*  362 */  storeI_rule,
  /*  363 */  storeL_rule,
  /*  364 */  storeP_rule,
  /*  365 */  storeF_rule,
  /*  366 */  storeD_rule,
  /*  367 */  prefetchAlloc_rule,
  /*  368 */  memInitB_rule,
  /*  369 */  memInitC_rule,
  /*  370 */  memInitI_rule,
  /*  371 */  memInitL_rule,
  /*  372 */  memInitP_rule,
  /*  373 */  negL_reg_reg_rule,
  /*  374 */  loadN_rule,
  /*  375 */  loadNKlass_rule,
  /*  376 */  loadNKlassCompactHeaders_rule,
  /*  377 */  decodeLoadN_rule,
  /*  378 */  decodeLoadNKlass_rule,
  /*  379 */  decodeLoadConNKlass_rule,
  /*  380 */  decodeN_rule,
  /*  381 */  decodeKlass_rule,
  /*  382 */  decodeN_NN_rule,
  /*  383 */  decodeN_base_rule,
  /*  384 */  decodeN_NN_base_rule,
  /*  385 */  decodeN_Ex_rule,
  /*  386 */  decodeN_NN_Ex_rule,
  /*  387 */  encodeP_rule,
  /*  388 */  encodeKlass_rule,
  /*  389 */  encodeP_NN_rule,
  /*  390 */  encodeP_base_rule,
  /*  391 */  encodeP_NN_base_rule,
  /*  392 */  encodeP_Ex_rule,
  /*  393 */  encodeP_NN_Ex_rule,
  /*  394 */  storeN_rule,
  /*  395 */  storeNKlass_rule,
  /*  396 */  membar_acquire_rule,
  /*  397 */  membar_acquire_0_rule,
  /*  398 */  membar_acquire_lock_rule,
  /*  399 */  membar_release_rule,
  /*  400 */  membar_release_0_rule,
  /*  401 */  membar_release_lock_rule,
  /*  402 */  membar_storeload_rule,
  /*  403 */  membar_volatile_rule,
  /*  404 */  unnecessary_membar_volatile_rule,
  /*  405 */  membar_full_rule,
  /*  406 */  membar_CPUOrder_rule,
  /*  407 */  membar_storestore_rule,
  /*  408 */  membar_storestore_0_rule,
  /*  409 */  cmovN_reg_rule,
  /*  410 */  cmovN_imm_rule,
  /*  411 */  cmovI_reg_rule,
  /*  412 */  cmovI_imm_rule,
  /*  413 */  cmovP_reg_rule,
  /*  414 */  cmovP_imm_rule,
  /*  415 */  cmovF_reg_rule,
  /*  416 */  cmovD_reg_rule,
  /*  417 */  cmovL_reg_rule,
  /*  418 */  cmovL_imm_rule,
  /*  419 */  compareAndSwapI_bool_rule,
  /*  420 */  compareAndSwapL_bool_rule,
  /*  421 */  compareAndSwapP_bool_rule,
  /*  422 */  compareAndSwapN_bool_rule,
  /*  423 */  addI_mem_imm8_atomic_no_res_rule,
  /*  424 */  addI_mem_imm16_atomic_rule,
  /*  425 */  addI_mem_imm32_atomic_rule,
  /*  426 */  addI_mem_reg_atomic_rule,
  /*  427 */  addL_mem_imm8_atomic_no_res_rule,
  /*  428 */  addL_mem_imm16_atomic_rule,
  /*  429 */  addL_mem_imm32_atomic_rule,
  /*  430 */  addL_mem_reg_atomic_rule,
  /*  431 */  addI_mem_reg_atomic_z196_rule,
  /*  432 */  addL_mem_reg_atomic_z196_rule,
  /*  433 */  xchgI_reg_mem_rule,
  /*  434 */  xchgL_reg_mem_rule,
  /*  435 */  xchgN_reg_mem_rule,
  /*  436 */  xchgP_reg_mem_rule,
  /*  437 */  addI_reg_reg_CISC_rule,
  /*  438 */  addI_reg_reg_RISC_rule,
  /*  439 */  addI_reg_imm16_CISC_rule,
  /*  440 */  addI_reg_imm16_RISC_rule,
  /*  441 */  addI_reg_imm32_rule,
  /*  442 */  addI_reg_imm12_rule,
  /*  443 */  addI_reg_imm20_rule,
  /*  444 */  addI_reg_reg_imm12_rule,
  /*  445 */  addI_reg_reg_imm20_rule,
  /*  446 */  addI_Reg_mem_rule,
  /*  447 */  addI_Reg_mem_0_rule,
  /*  448 */  addI_mem_imm_rule,
  /*  449 */  addL_reg_regI_rule,
  /*  450 */  addL_reg_regI_0_rule,
  /*  451 */  addL_reg_reg_CISC_rule,
  /*  452 */  addL_reg_reg_RISC_rule,
  /*  453 */  addL_reg_imm12_rule,
  /*  454 */  addL_reg_imm20_rule,
  /*  455 */  addL_reg_imm32_rule,
  /*  456 */  addL_reg_imm16_CISC_rule,
  /*  457 */  addL_reg_imm16_RISC_rule,
  /*  458 */  addL_Reg_memI_rule,
  /*  459 */  addL_Reg_memI_0_rule,
  /*  460 */  addL_Reg_mem_rule,
  /*  461 */  addL_Reg_mem_0_rule,
  /*  462 */  addL_reg_reg_imm12_rule,
  /*  463 */  addL_reg_reg_imm20_rule,
  /*  464 */  addL_mem_imm_rule,
  /*  465 */  addP_reg_reg_LA_rule,
  /*  466 */  addP_reg_reg_CISC_rule,
  /*  467 */  addP_reg_reg_RISC_rule,
  /*  468 */  addP_reg_imm12_rule,
  /*  469 */  addP_reg_imm16_CISC_rule,
  /*  470 */  addP_reg_imm16_RISC_rule,
  /*  471 */  addP_reg_imm20_rule,
  /*  472 */  addP_reg_imm32_rule,
  /*  473 */  addP_reg_reg_imm12_rule,
  /*  474 */  addP_regN_reg_imm12_rule,
  /*  475 */  addP_reg_reg_imm20_rule,
  /*  476 */  addP_regN_reg_imm20_rule,
  /*  477 */  addP_mem_imm_rule,
  /*  478 */  subI_reg_reg_CISC_rule,
  /*  479 */  subI_reg_reg_RISC_rule,
  /*  480 */  subI_Reg_mem_rule,
  /*  481 */  subI_zero_reg_rule,
  /*  482 */  subL_reg_reg_CISC_rule,
  /*  483 */  subL_reg_reg_RISC_rule,
  /*  484 */  subL_reg_regI_CISC_rule,
  /*  485 */  subL_Reg_memI_rule,
  /*  486 */  subL_Reg_mem_rule,
  /*  487 */  mulI_reg_reg_rule,
  /*  488 */  mulI_reg_imm16_rule,
  /*  489 */  mulI_reg_imm32_rule,
  /*  490 */  mulI_Reg_mem_rule,
  /*  491 */  mulI_Reg_mem_0_rule,
  /*  492 */  mulL_reg_regI_rule,
  /*  493 */  mulL_reg_regI_0_rule,
  /*  494 */  mulL_reg_reg_rule,
  /*  495 */  mulL_reg_imm16_rule,
  /*  496 */  mulL_reg_imm32_rule,
  /*  497 */  mulL_Reg_memI_rule,
  /*  498 */  mulL_Reg_memI_0_rule,
  /*  499 */  mulL_Reg_mem_rule,
  /*  500 */  mulL_Reg_mem_0_rule,
  /*  501 */  mulHiL_reg_reg_rule,
  /*  502 */  divModI_reg_divmod_rule,
  /*  503 */  divI_reg_reg_rule,
  /*  504 */  divI_reg_imm16_rule,
  /*  505 */  udivI_reg_reg_rule,
  /*  506 */  divModL_reg_divmod_rule,
  /*  507 */  divL_reg_reg_rule,
  /*  508 */  udivL_reg_reg_rule,
  /*  509 */  divL_reg_imm16_rule,
  /*  510 */  modI_reg_reg_rule,
  /*  511 */  umodI_reg_reg_rule,
  /*  512 */  modI_reg_imm16_rule,
  /*  513 */  modL_reg_reg_rule,
  /*  514 */  umodL_reg_reg_rule,
  /*  515 */  modL_reg_imm16_rule,
  /*  516 */  sllI_reg_reg_rule,
  /*  517 */  sllI_reg_imm_rule,
  /*  518 */  sllI_reg_imm_1_rule,
  /*  519 */  sllL_reg_reg_rule,
  /*  520 */  sllL_reg_imm_rule,
  /*  521 */  sllL_reg_imm_1_rule,
  /*  522 */  sraI_reg_reg_rule,
  /*  523 */  sraI_reg_imm_rule,
  /*  524 */  sraL_reg_reg_rule,
  /*  525 */  sraL_reg_imm_rule,
  /*  526 */  srlI_reg_reg_rule,
  /*  527 */  srlI_reg_imm_rule,
  /*  528 */  srlL_reg_reg_rule,
  /*  529 */  srlL_reg_imm_rule,
  /*  530 */  srlP_reg_imm_rule,
  /*  531 */  rotlI_reg_immI8_rule,
  /*  532 */  rotlI_reg_immI8_0_rule,
  /*  533 */  rotlL_reg_immI8_rule,
  /*  534 */  rotlL_reg_immI8_0_rule,
  /*  535 */  rotrI_reg_immI8_rule,
  /*  536 */  rotrI_reg_immI8_0_rule,
  /*  537 */  rotrL_reg_immI8_rule,
  /*  538 */  rotrL_reg_immI8_0_rule,
  /*  539 */  addF_reg_reg_rule,
  /*  540 */  addF_reg_mem_rule,
  /*  541 */  addF_reg_mem_0_rule,
  /*  542 */  addD_reg_reg_rule,
  /*  543 */  addD_reg_mem_rule,
  /*  544 */  addD_reg_mem_0_rule,
  /*  545 */  subF_reg_reg_rule,
  /*  546 */  subF_reg_mem_rule,
  /*  547 */  subD_reg_reg_rule,
  /*  548 */  subD_reg_mem_rule,
  /*  549 */  mulF_reg_reg_rule,
  /*  550 */  mulF_reg_mem_rule,
  /*  551 */  mulF_reg_mem_0_rule,
  /*  552 */  mulD_reg_reg_rule,
  /*  553 */  mulD_reg_mem_rule,
  /*  554 */  mulD_reg_mem_0_rule,
  /*  555 */  maddF_reg_reg_rule,
  /*  556 */  maddD_reg_reg_rule,
  /*  557 */  msubF_reg_reg_rule,
  /*  558 */  msubD_reg_reg_rule,
  /*  559 */  maddF_reg_mem_rule,
  /*  560 */  maddD_reg_mem_rule,
  /*  561 */  msubF_reg_mem_rule,
  /*  562 */  msubD_reg_mem_rule,
  /*  563 */  maddF_mem_reg_rule,
  /*  564 */  maddD_mem_reg_rule,
  /*  565 */  msubF_mem_reg_rule,
  /*  566 */  msubD_mem_reg_rule,
  /*  567 */  divF_reg_reg_rule,
  /*  568 */  divF_reg_mem_rule,
  /*  569 */  divD_reg_reg_rule,
  /*  570 */  divD_reg_mem_rule,
  /*  571 */  absF_reg_rule,
  /*  572 */  absD_reg_rule,
  /*  573 */  nabsF_reg_rule,
  /*  574 */  nabsD_reg_rule,
  /*  575 */  negF_reg_rule,
  /*  576 */  negD_reg_rule,
  /*  577 */  sqrtF_reg_rule,
  /*  578 */  sqrtD_reg_rule,
  /*  579 */  sqrtF_mem_rule,
  /*  580 */  sqrtD_mem_rule,
  /*  581 */  andI_reg_reg_rule,
  /*  582 */  andI_Reg_mem_rule,
  /*  583 */  andI_Reg_mem_0_rule,
  /*  584 */  andI_reg_uimm32_rule,
  /*  585 */  andI_reg_uimmI_LH1_rule,
  /*  586 */  andI_reg_uimmI_LL1_rule,
  /*  587 */  andL_reg_reg_rule,
  /*  588 */  andL_Reg_mem_rule,
  /*  589 */  andL_Reg_mem_0_rule,
  /*  590 */  andL_reg_uimmL_LL1_rule,
  /*  591 */  andL_reg_uimmL_LH1_rule,
  /*  592 */  andL_reg_uimmL_HL1_rule,
  /*  593 */  andL_reg_uimmL_HH1_rule,
  /*  594 */  orI_reg_reg_rule,
  /*  595 */  orI_Reg_mem_rule,
  /*  596 */  orI_Reg_mem_0_rule,
  /*  597 */  orI_reg_uimm16_rule,
  /*  598 */  orI_reg_uimm32_rule,
  /*  599 */  orL_reg_reg_rule,
  /*  600 */  orL_Reg_mem_rule,
  /*  601 */  orL_Reg_mem_0_rule,
  /*  602 */  orL_reg_uimm16_rule,
  /*  603 */  orL_reg_uimm32_rule,
  /*  604 */  xorI_reg_reg_rule,
  /*  605 */  xorI_Reg_mem_rule,
  /*  606 */  xorI_Reg_mem_0_rule,
  /*  607 */  xorI_reg_uimm32_rule,
  /*  608 */  xorL_reg_reg_rule,
  /*  609 */  xorL_Reg_mem_rule,
  /*  610 */  xorL_reg_uimm32_rule,
  /*  611 */  convI2B_rule,
  /*  612 */  convP2B_rule,
  /*  613 */  cmpLTMask_reg_reg_rule,
  /*  614 */  cmpLTMask_reg_zero_rule,
  /*  615 */  convD2F_reg_rule,
  /*  616 */  convF2I_reg_rule,
  /*  617 */  convD2I_reg_rule,
  /*  618 */  convF2L_reg_rule,
  /*  619 */  convD2L_reg_rule,
  /*  620 */  convF2D_reg_rule,
  /*  621 */  convF2D_mem_rule,
  /*  622 */  convI2D_reg_rule,
  /*  623 */  convI2F_ireg_rule,
  /*  624 */  convI2L_reg_rule,
  /*  625 */  convI2L_reg_zex_rule,
  /*  626 */  convI2L_mem_zex_rule,
  /*  627 */  zeroExtend_long_rule,
  /*  628 */  rShiftI16_lShiftI16_reg_rule,
  /*  629 */  rShiftI24_lShiftI24_reg_rule,
  /*  630 */  MoveI2F_reg_stack_rule,
  /*  631 */  MoveD2L_reg_stack_rule,
  /*  632 */  MoveL2D_reg_stack_rule,
  /*  633 */  convL2F_reg_rule,
  /*  634 */  convL2D_reg_rule,
  /*  635 */  convL2I_reg_rule,
  /*  636 */  shrL_reg_imm6_L2I_rule,
  /*  637 */  rangeCheck_iReg_uimmI16_rule,
  /*  638 */  rangeCheck_iReg_iReg_rule,
  /*  639 */  rangeCheck_uimmI16_iReg_rule,
  /*  640 */  zeroCheckP_iReg_imm0_rule,
  /*  641 */  zeroCheckN_iReg_imm0_rule,
  /*  642 */  z196_minI_reg_reg_rule,
  /*  643 */  z10_minI_reg_reg_rule,
  /*  644 */  minI_reg_reg_rule,
  /*  645 */  z196_minI_reg_imm32_rule,
  /*  646 */  minI_reg_imm32_rule,
  /*  647 */  z196_minI_reg_imm16_rule,
  /*  648 */  minI_reg_imm16_rule,
  /*  649 */  z10_minI_reg_imm8_rule,
  /*  650 */  z196_maxI_reg_reg_rule,
  /*  651 */  z10_maxI_reg_reg_rule,
  /*  652 */  maxI_reg_reg_rule,
  /*  653 */  z196_maxI_reg_imm32_rule,
  /*  654 */  maxI_reg_imm32_rule,
  /*  655 */  z196_maxI_reg_imm16_rule,
  /*  656 */  maxI_reg_imm16_rule,
  /*  657 */  z10_maxI_reg_imm8_rule,
  /*  658 */  absI_reg_rule,
  /*  659 */  absL_reg_rule,
  /*  660 */  negabsI_reg_rule,
  /*  661 */  cmpF_reg_rule,
  /*  662 */  cmpD_reg_rule,
  /*  663 */  branch_rule,
  /*  664 */  branchFar_rule,
  /*  665 */  branchCon_rule,
  /*  666 */  branchConFar_rule,
  /*  667 */  branchLoopEnd_rule,
  /*  668 */  branchLoopEndFar_rule,
  /*  669 */  testAndBranchLoopEnd_Reg_rule,
  /*  670 */  cmpb_RegI_rule,
  /*  671 */  cmpbU_RegI_rule,
  /*  672 */  cmpb_RegL_rule,
  /*  673 */  cmpb_RegPP_rule,
  /*  674 */  cmpb_RegNN_rule,
  /*  675 */  testAndBranchLoopEnd_Imm_rule,
  /*  676 */  cmpb_RegI_imm_rule,
  /*  677 */  cmpbU_RegI_imm_rule,
  /*  678 */  cmpb_RegL_imm_rule,
  /*  679 */  cmpb_RegP_immP_rule,
  /*  680 */  cmpb_RegN_immP0_rule,
  /*  681 */  cmpb_RegN_imm_rule,
  /*  682 */  testAndBranchLoopEnd_RegFar_rule,
  /*  683 */  cmpb_RegI_Far_rule,
  /*  684 */  cmpbU_RegI_Far_rule,
  /*  685 */  cmpb_RegL_Far_rule,
  /*  686 */  cmpb_RegPP_Far_rule,
  /*  687 */  cmpb_RegNN_Far_rule,
  /*  688 */  testAndBranchLoopEnd_ImmFar_rule,
  /*  689 */  cmpb_RegI_imm_Far_rule,
  /*  690 */  cmpbU_RegI_imm_Far_rule,
  /*  691 */  cmpb_RegL_imm_Far_rule,
  /*  692 */  cmpb_RegP_immP_Far_rule,
  /*  693 */  cmpb_RegN_immP0_Far_rule,
  /*  694 */  cmpb_RegN_immN_Far_rule,
  /*  695 */  cmpL3_reg_reg_rule,
  /*  696 */  safePoint_rule,
  /*  697 */  safePoint_poll_rule,
  /*  698 */  CallStaticJavaDirect_dynTOC_rule,
  /*  699 */  CallDynamicJavaDirect_dynTOC_rule,
  /*  700 */  CallRuntimeDirect_rule,
  /*  701 */  CallLeafDirect_rule,
  /*  702 */  CallLeafNoFPDirect_rule,
  /*  703 */  TailCalljmpInd_rule,
  /*  704 */  Ret_rule,
  /*  705 */  tailjmpInd_rule,
  /*  706 */  ForwardExceptionjmp_rule,
  /*  707 */  CreateException_rule,
  /*  708 */  RethrowException_rule,
  /*  709 */  ShouldNotReachHere_rule,
  /*  710 */  partialSubtypeCheck_rule,
  /*  711 */  partialSubtypeCheckVarSuper_rule,
  /*  712 */  partialSubtypeCheckConstSuper_rule,
  /*  713 */  inlineCallClearArrayConst_rule,
  /*  714 */  inlineCallClearArrayConstBig_rule,
  /*  715 */  inlineCallClearArray_rule,
  /*  716 */  string_equalsL_rule,
  /*  717 */  string_equals_imm_rule,
  /*  718 */  string_equalsC_imm_rule,
  /*  719 */  array_equalsB_rule,
  /*  720 */  array_equalsC_rule,
  /*  721 */  string_compareL_rule,
  /*  722 */  string_compareU_rule,
  /*  723 */  string_compareLU_rule,
  /*  724 */  string_compareUL_rule,
  /*  725 */  indexOfChar_U_rule,
  /*  726 */  indexOfChar_L_rule,
  /*  727 */  indexOf_imm1_U_rule,
  /*  728 */  indexOf_imm1_L_rule,
  /*  729 */  indexOf_imm1_UL_rule,
  /*  730 */  indexOf_imm_U_rule,
  /*  731 */  indexOf_imm_L_rule,
  /*  732 */  indexOf_imm_UL_rule,
  /*  733 */  indexOf_U_rule,
  /*  734 */  indexOf_L_rule,
  /*  735 */  indexOf_UL_rule,
  /*  736 */  string_compress_rule,
  /*  737 */  string_inflate_rule,
  /*  738 */  string_inflate_const_rule,
  /*  739 */  count_positives_rule,
  /*  740 */  encode_iso_array_rule,
  /*  741 */  encode_ascii_array_rule,
  /*  742 */  expand_storeF_rule,
  /*  743 */  expand_Repl2I_reg_rule,
  /*  744 */  Repl8B_reg_risbg_rule,
  /*  745 */  Repl4S_reg_risbg_rule,
  /*  746 */  Repl2I_reg_risbg_rule,
  /*  747 */  Repl2F_reg_indirect_rule,
  /*  748 */  Repl2F_reg_direct_rule,
  /*  749 */  storeA8B_rule,
  /*  750 */  storeV16_rule,
  /*  751 */  loadV8_rule,
  /*  752 */  loadV16_rule,
  /*  753 */  vadd16B_reg_rule,
  /*  754 */  vadd8S_reg_rule,
  /*  755 */  vadd4I_reg_rule,
  /*  756 */  vadd2L_reg_rule,
  /*  757 */  vmul16B_reg_rule,
  /*  758 */  vmul8S_reg_rule,
  /*  759 */  vmul4I_reg_rule,
  /*  760 */  vsub16B_reg_rule,
  /*  761 */  vsub8S_reg_rule,
  /*  762 */  vsub4I_reg_rule,
  /*  763 */  vsub2L_reg_rule,
  /*  764 */  vadd4F_reg_rule,
  /*  765 */  vadd2D_reg_rule,
  /*  766 */  vsub4F_reg_rule,
  /*  767 */  vsub2D_reg_rule,
  /*  768 */  vmul4F_reg_rule,
  /*  769 */  vmul2D_reg_rule,
  /*  770 */  vdiv4F_reg_rule,
  /*  771 */  vdiv2D_reg_rule,
  /*  772 */  vround2D_reg_rule,
  /*  773 */  bytes_reverse_short_rule,
  /*  774 */  bytes_reverse_unsigned_short_rule,
  /*  775 */  bytes_reverse_int_rule,
  /*  776 */  bytes_reverse_long_rule,
  /*  777 */  countLeadingZerosI_rule,
  /*  778 */  countLeadingZerosL_rule,
  /*  779 */  countTrailingZerosI_rule,
  /*  780 */  countTrailingZerosL_rule,
  /*  781 */  popCountI_Ext3_rule,
  /*  782 */  popCountL_Ext3_rule,
  /*  783 */  popCountI_rule,
  /*  784 */  popCountL_rule,
  /*  785 */  g1StoreP_rule,
  /*  786 */  g1StoreN_rule,
  /*  787 */  g1CompareAndSwapN_rule,
  /*  788 */  g1CompareAndSwapN_0_rule,
  /*  789 */  g1CompareAndExchangeN_rule,
  /*  790 */  g1LoadN_rule,
  /*  791 */  g1GetAndSetN_rule,
  /*  792 */  g1CompareAndSwapP_rule,
  /*  793 */  g1CompareAndSwapP_0_rule,
  /*  794 */  g1CompareAndExchangeP_rule,
  /*  795 */  g1LoadP_rule,
  /*  796 */  g1GetAndSetP_rule,
  /*  797 */  g1EncodePAndStoreN_rule,
  // last instruction
  _BEGIN_INST_CHAIN_RULE = 218,
  _END_INST_CHAIN_RULE  = 247,
  _BEGIN_REMATERIALIZE   = 225,
  _END_REMATERIALIZE    = 340,
  _last_Mach_Node  = 798 
};

// Enumerate machine registers starting after reserved regs.
// in the order of occurrence in the alloc_class(es).
enum MachRegisterEncodes {
  Z_R13_enc    =  13,
  Z_R13_H_enc  =  99,
  Z_R12_enc    =  12,
  Z_R12_H_enc  =  99,
  Z_R11_enc    =  11,
  Z_R11_H_enc  =  99,
  Z_R10_enc    =  10,
  Z_R10_H_enc  =  99,
  Z_R9_enc     =   9,
  Z_R9_H_enc   =  99,
  Z_R8_enc     =   8,
  Z_R8_H_enc   =  99,
  Z_R7_enc     =   7,
  Z_R7_H_enc   =  99,
  Z_R1_enc     =   1,
  Z_R1_H_enc   =  99,
  Z_R0_enc     =   0,
  Z_R0_H_enc   =  99,
  Z_R6_enc     =   6,
  Z_R6_H_enc   =  99,
  Z_R5_enc     =   5,
  Z_R5_H_enc   =  99,
  Z_R4_enc     =   4,
  Z_R4_H_enc   =  99,
  Z_R3_enc     =   3,
  Z_R3_H_enc   =  99,
  Z_R2_enc     =   2,
  Z_R2_H_enc   =  99,
  Z_R14_enc    =  14,
  Z_R14_H_enc  =  99,
  Z_R15_enc    =  15,
  Z_R15_H_enc  =  99,
  Z_F15_enc    =  15,
  Z_F15_H_enc  =  99,
  Z_F14_enc    =  14,
  Z_F14_H_enc  =  99,
  Z_F13_enc    =  13,
  Z_F13_H_enc  =  99,
  Z_F12_enc    =  12,
  Z_F12_H_enc  =  99,
  Z_F11_enc    =  11,
  Z_F11_H_enc  =  99,
  Z_F10_enc    =  10,
  Z_F10_H_enc  =  99,
  Z_F9_enc     =   9,
  Z_F9_H_enc   =  99,
  Z_F8_enc     =   8,
  Z_F8_H_enc   =  99,
  Z_F7_enc     =   7,
  Z_F7_H_enc   =  99,
  Z_F5_enc     =   5,
  Z_F5_H_enc   =  99,
  Z_F3_enc     =   3,
  Z_F3_H_enc   =  99,
  Z_F1_enc     =   1,
  Z_F1_H_enc   =  99,
  Z_F6_enc     =   6,
  Z_F6_H_enc   =  99,
  Z_F4_enc     =   4,
  Z_F4_H_enc   =  99,
  Z_F2_enc     =   2,
  Z_F2_H_enc   =  99,
  Z_F0_enc     =   0,
  Z_F0_H_enc   =  99,
  Z_VR0_enc    =   0,
  Z_VR0_H_enc  =   0,
  Z_VR0_J_enc  =   0,
  Z_VR0_K_enc  =   0,
  Z_VR1_enc    =   1,
  Z_VR1_H_enc  =   1,
  Z_VR1_J_enc  =   1,
  Z_VR1_K_enc  =   1,
  Z_VR2_enc    =   2,
  Z_VR2_H_enc  =   2,
  Z_VR2_J_enc  =   2,
  Z_VR2_K_enc  =   2,
  Z_VR3_enc    =   3,
  Z_VR3_H_enc  =   3,
  Z_VR3_J_enc  =   3,
  Z_VR3_K_enc  =   3,
  Z_VR4_enc    =   4,
  Z_VR4_H_enc  =   4,
  Z_VR4_J_enc  =   4,
  Z_VR4_K_enc  =   4,
  Z_VR5_enc    =   5,
  Z_VR5_H_enc  =   5,
  Z_VR5_J_enc  =   5,
  Z_VR5_K_enc  =   5,
  Z_VR6_enc    =   6,
  Z_VR6_H_enc  =   6,
  Z_VR6_J_enc  =   6,
  Z_VR6_K_enc  =   6,
  Z_VR7_enc    =   7,
  Z_VR7_H_enc  =   7,
  Z_VR7_J_enc  =   7,
  Z_VR7_K_enc  =   7,
  Z_VR8_enc    =   8,
  Z_VR8_H_enc  =   8,
  Z_VR8_J_enc  =   8,
  Z_VR8_K_enc  =   8,
  Z_VR9_enc    =   9,
  Z_VR9_H_enc  =   9,
  Z_VR9_J_enc  =   9,
  Z_VR9_K_enc  =   9,
  Z_VR10_enc   =  10,
  Z_VR10_H_enc =  10,
  Z_VR10_J_enc =  10,
  Z_VR10_K_enc =  10,
  Z_VR11_enc   =  11,
  Z_VR11_H_enc =  11,
  Z_VR11_J_enc =  11,
  Z_VR11_K_enc =  11,
  Z_VR12_enc   =  12,
  Z_VR12_H_enc =  12,
  Z_VR12_J_enc =  12,
  Z_VR12_K_enc =  12,
  Z_VR13_enc   =  13,
  Z_VR13_H_enc =  13,
  Z_VR13_J_enc =  13,
  Z_VR13_K_enc =  13,
  Z_VR14_enc   =  14,
  Z_VR14_H_enc =  14,
  Z_VR14_J_enc =  14,
  Z_VR14_K_enc =  14,
  Z_VR15_enc   =  15,
  Z_VR15_H_enc =  15,
  Z_VR15_J_enc =  15,
  Z_VR15_K_enc =  15,
  Z_VR16_enc   =  16,
  Z_VR16_H_enc =  16,
  Z_VR16_J_enc =  16,
  Z_VR16_K_enc =  16,
  Z_VR17_enc   =  17,
  Z_VR17_H_enc =  17,
  Z_VR17_J_enc =  17,
  Z_VR17_K_enc =  17,
  Z_VR18_enc   =  18,
  Z_VR18_H_enc =  18,
  Z_VR18_J_enc =  18,
  Z_VR18_K_enc =  18,
  Z_VR19_enc   =  19,
  Z_VR19_H_enc =  19,
  Z_VR19_J_enc =  19,
  Z_VR19_K_enc =  19,
  Z_VR20_enc   =  20,
  Z_VR20_H_enc =  20,
  Z_VR20_J_enc =  20,
  Z_VR20_K_enc =  20,
  Z_VR21_enc   =  21,
  Z_VR21_H_enc =  21,
  Z_VR21_J_enc =  21,
  Z_VR21_K_enc =  21,
  Z_VR22_enc   =  22,
  Z_VR22_H_enc =  22,
  Z_VR22_J_enc =  22,
  Z_VR22_K_enc =  22,
  Z_VR23_enc   =  23,
  Z_VR23_H_enc =  23,
  Z_VR23_J_enc =  23,
  Z_VR23_K_enc =  23,
  Z_VR24_enc   =  24,
  Z_VR24_H_enc =  24,
  Z_VR24_J_enc =  24,
  Z_VR24_K_enc =  24,
  Z_VR25_enc   =  25,
  Z_VR25_H_enc =  25,
  Z_VR25_J_enc =  25,
  Z_VR25_K_enc =  25,
  Z_VR26_enc   =  26,
  Z_VR26_H_enc =  26,
  Z_VR26_J_enc =  26,
  Z_VR26_K_enc =  26,
  Z_VR27_enc   =  27,
  Z_VR27_H_enc =  27,
  Z_VR27_J_enc =  27,
  Z_VR27_K_enc =  27,
  Z_VR28_enc   =  28,
  Z_VR28_H_enc =  28,
  Z_VR28_J_enc =  28,
  Z_VR28_K_enc =  28,
  Z_VR29_enc   =  29,
  Z_VR29_H_enc =  29,
  Z_VR29_J_enc =  29,
  Z_VR29_K_enc =  29,
  Z_VR30_enc   =  30,
  Z_VR30_H_enc =  30,
  Z_VR30_J_enc =  30,
  Z_VR30_K_enc =  30,
  Z_VR31_enc   =  31,
  Z_VR31_H_enc =  31,
  Z_VR31_J_enc =  31,
  Z_VR31_K_enc =  31,
  Z_CR_enc     =   0
};

// Pipeline Stages
enum machPipelineStages {
   stage_undefined = 0,
   stage_Z_IF      = 1,
   stage_Z_IC      = 2,
   stage_Z_D0      = 3,
   stage_Z_D1      = 4,
   stage_Z_D2      = 5,
   stage_Z_D3      = 6,
   stage_Z_Xfer1   = 7,
   stage_Z_GD      = 8,
   stage_Z_MP      = 9,
   stage_Z_ISS     = 10,
   stage_Z_RF      = 11,
   stage_Z_EX1     = 12,
   stage_Z_EX2     = 13,
   stage_Z_EX3     = 14,
   stage_Z_EX4     = 15,
   stage_Z_EX5     = 16,
   stage_Z_EX6     = 17,
   stage_Z_WB      = 18,
   stage_Z_Xfer2   = 19,
   stage_Z_CP      = 20,
   stage_count     = 20
};

// Pipeline Resources
enum machPipelineResources {
   resource_Z_BR    = 0,
   resource_Z_CR    = 1,
   resource_Z_FX1   = 2,
   resource_Z_FX2   = 3,
   resource_Z_LDST1 = 4,
   resource_Z_LDST2 = 5,
   resource_Z_FP1   = 6,
   resource_Z_FP2   = 7,

   res_mask_Z_BR    = 0x00000001,
   res_mask_Z_CR    = 0x00000002,
   res_mask_Z_FX1   = 0x00000004,
   res_mask_Z_FX2   = 0x00000008,
   res_mask_Z_LDST1 = 0x00000010,
   res_mask_Z_LDST2 = 0x00000020,
   res_mask_Z_FP1   = 0x00000040,
   res_mask_Z_FP2   = 0x00000080,
   res_mask_Z_LDST  = 0x00000030,
   res_mask_Z_FX    = 0x0000000c,
   res_mask_Z_FP    = 0x000000c0,

   resource_count = 8
};

// MACROS to inline and constant fold State::valid(index)...
// when given a constant 'index' in dfa_<arch>.cpp
#define STATE__NOT_YET_VALID(index)   ( (_rule[index] & 0x1) == 0 )

#define STATE__VALID_CHILD(state,index)   ( state && (state->_rule[index] & 0x1) )

//---------------------------State-------------------------------------------
// State contains an integral cost vector, indexed by machine operand opcodes,
// a rule vector consisting of machine operand/instruction opcodes, and also
// indexed by machine operand opcodes, pointers to the children in the label
// tree generated by the Label routines in ideal nodes (currently limited to
// two for convenience, but this could change).
class State : public ArenaObj {
private:
  unsigned int _cost[_LAST_MACH_OPER];  // Costs, indexed by operand opcodes
  uint16_t     _rule[_LAST_MACH_OPER];  // Rule and validity, indexed by operand opcodes
                                        // Lowest bit encodes validity
public:
  int    _id;                           // State identifier
  Node  *_leaf;                         // Ideal (non-machine-node) leaf of match tree
  State *_kids[2];                      // Children of state node in label tree

  State(void);
  DEBUG_ONLY( ~State(void); )

  // Methods created by ADLC and invoked by Reduce
  MachOper *MachOperGenerator(int opcode);
  MachNode *MachNodeGenerator(int opcode);

  // Assign a state to a node, definition of method produced by ADLC
  bool DFA( int opcode, const Node *ideal );

  bool valid(uint index) {
    return _rule[index] & 0x1;
  }
  unsigned int rule(uint index) {
    return _rule[index] >> 1;
  }
  unsigned int cost(uint index) {
    return _cost[index];
  }

#ifndef PRODUCT
  void dump();                // Debugging prints
  void dump(int depth);
#endif
  void  _sub_Op_RegN(const Node *n);
  void  _sub_Op_RegI(const Node *n);
  void  _sub_Op_RegP(const Node *n);
  void  _sub_Op_RegF(const Node *n);
  void  _sub_Op_RegD(const Node *n);
  void  _sub_Op_RegL(const Node *n);
  void  _sub_Op_VecX(const Node *n);
  void  _sub_Op_RegFlags(const Node *n);
  void  _sub_Op_AbsD(const Node *n);
  void  _sub_Op_AbsF(const Node *n);
  void  _sub_Op_AbsI(const Node *n);
  void  _sub_Op_AbsL(const Node *n);
  void  _sub_Op_AddD(const Node *n);
  void  _sub_Op_AddF(const Node *n);
  void  _sub_Op_AddI(const Node *n);
  void  _sub_Op_AddL(const Node *n);
  void  _sub_Op_AddP(const Node *n);
  void  _sub_Op_AndI(const Node *n);
  void  _sub_Op_AndL(const Node *n);
  void  _sub_Op_AryEq(const Node *n);
  void  _sub_Op_Binary(const Node *n);
  void  _sub_Op_Bool(const Node *n);
  void  _sub_Op_ReverseBytesI(const Node *n);
  void  _sub_Op_ReverseBytesL(const Node *n);
  void  _sub_Op_ReverseBytesUS(const Node *n);
  void  _sub_Op_ReverseBytesS(const Node *n);
  void  _sub_Op_CallDynamicJava(const Node *n);
  void  _sub_Op_CallLeaf(const Node *n);
  void  _sub_Op_CallLeafNoFP(const Node *n);
  void  _sub_Op_CallRuntime(const Node *n);
  void  _sub_Op_CallStaticJava(const Node *n);
  void  _sub_Op_CastDD(const Node *n);
  void  _sub_Op_CastFF(const Node *n);
  void  _sub_Op_CastII(const Node *n);
  void  _sub_Op_CastLL(const Node *n);
  void  _sub_Op_CastVV(const Node *n);
  void  _sub_Op_CastX2P(const Node *n);
  void  _sub_Op_CastP2X(const Node *n);
  void  _sub_Op_CastPP(const Node *n);
  void  _sub_Op_CheckCastPP(const Node *n);
  void  _sub_Op_ClearArray(const Node *n);
  void  _sub_Op_CMoveD(const Node *n);
  void  _sub_Op_CMoveF(const Node *n);
  void  _sub_Op_CMoveI(const Node *n);
  void  _sub_Op_CMoveL(const Node *n);
  void  _sub_Op_CMoveP(const Node *n);
  void  _sub_Op_CMoveN(const Node *n);
  void  _sub_Op_CmpN(const Node *n);
  void  _sub_Op_CmpD(const Node *n);
  void  _sub_Op_CmpD3(const Node *n);
  void  _sub_Op_CmpF(const Node *n);
  void  _sub_Op_CmpF3(const Node *n);
  void  _sub_Op_CmpI(const Node *n);
  void  _sub_Op_CmpL(const Node *n);
  void  _sub_Op_CmpL3(const Node *n);
  void  _sub_Op_CmpLTMask(const Node *n);
  void  _sub_Op_CmpP(const Node *n);
  void  _sub_Op_CmpU(const Node *n);
  void  _sub_Op_CmpUL(const Node *n);
  void  _sub_Op_CompareAndSwapI(const Node *n);
  void  _sub_Op_CompareAndSwapL(const Node *n);
  void  _sub_Op_CompareAndSwapP(const Node *n);
  void  _sub_Op_CompareAndSwapN(const Node *n);
  void  _sub_Op_WeakCompareAndSwapP(const Node *n);
  void  _sub_Op_WeakCompareAndSwapN(const Node *n);
  void  _sub_Op_CompareAndExchangeP(const Node *n);
  void  _sub_Op_CompareAndExchangeN(const Node *n);
  void  _sub_Op_GetAndAddI(const Node *n);
  void  _sub_Op_GetAndAddL(const Node *n);
  void  _sub_Op_GetAndSetI(const Node *n);
  void  _sub_Op_GetAndSetL(const Node *n);
  void  _sub_Op_GetAndSetP(const Node *n);
  void  _sub_Op_GetAndSetN(const Node *n);
  void  _sub_Op_ConN(const Node *n);
  void  _sub_Op_ConNKlass(const Node *n);
  void  _sub_Op_ConD(const Node *n);
  void  _sub_Op_ConF(const Node *n);
  void  _sub_Op_ConI(const Node *n);
  void  _sub_Op_ConL(const Node *n);
  void  _sub_Op_ConP(const Node *n);
  void  _sub_Op_Conv2B(const Node *n);
  void  _sub_Op_ConvD2F(const Node *n);
  void  _sub_Op_ConvD2I(const Node *n);
  void  _sub_Op_ConvD2L(const Node *n);
  void  _sub_Op_ConvF2D(const Node *n);
  void  _sub_Op_ConvF2I(const Node *n);
  void  _sub_Op_ConvF2L(const Node *n);
  void  _sub_Op_ConvI2D(const Node *n);
  void  _sub_Op_ConvI2F(const Node *n);
  void  _sub_Op_ConvI2L(const Node *n);
  void  _sub_Op_ConvL2D(const Node *n);
  void  _sub_Op_ConvL2F(const Node *n);
  void  _sub_Op_ConvL2I(const Node *n);
  void  _sub_Op_CountedLoopEnd(const Node *n);
  void  _sub_Op_CountLeadingZerosI(const Node *n);
  void  _sub_Op_CountLeadingZerosL(const Node *n);
  void  _sub_Op_CountTrailingZerosI(const Node *n);
  void  _sub_Op_CountTrailingZerosL(const Node *n);
  void  _sub_Op_CreateEx(const Node *n);
  void  _sub_Op_DecodeN(const Node *n);
  void  _sub_Op_DecodeNKlass(const Node *n);
  void  _sub_Op_DivD(const Node *n);
  void  _sub_Op_DivF(const Node *n);
  void  _sub_Op_DivI(const Node *n);
  void  _sub_Op_DivL(const Node *n);
  void  _sub_Op_UDivI(const Node *n);
  void  _sub_Op_UDivL(const Node *n);
  void  _sub_Op_DivModI(const Node *n);
  void  _sub_Op_DivModL(const Node *n);
  void  _sub_Op_EncodeISOArray(const Node *n);
  void  _sub_Op_EncodeP(const Node *n);
  void  _sub_Op_EncodePKlass(const Node *n);
  void  _sub_Op_FastLock(const Node *n);
  void  _sub_Op_FastUnlock(const Node *n);
  void  _sub_Op_FmaD(const Node *n);
  void  _sub_Op_FmaF(const Node *n);
  void  _sub_Op_ForwardException(const Node *n);
  void  _sub_Op_Goto(const Node *n);
  void  _sub_Op_Halt(const Node *n);
  void  _sub_Op_CountPositives(const Node *n);
  void  _sub_Op_If(const Node *n);
  void  _sub_Op_LShiftI(const Node *n);
  void  _sub_Op_LShiftL(const Node *n);
  void  _sub_Op_LoadB(const Node *n);
  void  _sub_Op_LoadUB(const Node *n);
  void  _sub_Op_LoadUS(const Node *n);
  void  _sub_Op_LoadD(const Node *n);
  void  _sub_Op_LoadD_unaligned(const Node *n);
  void  _sub_Op_LoadF(const Node *n);
  void  _sub_Op_LoadI(const Node *n);
  void  _sub_Op_LoadKlass(const Node *n);
  void  _sub_Op_LoadNKlass(const Node *n);
  void  _sub_Op_LoadL(const Node *n);
  void  _sub_Op_LoadL_unaligned(const Node *n);
  void  _sub_Op_LoadP(const Node *n);
  void  _sub_Op_LoadN(const Node *n);
  void  _sub_Op_LoadRange(const Node *n);
  void  _sub_Op_LoadS(const Node *n);
  void  _sub_Op_MaxI(const Node *n);
  void  _sub_Op_MemBarAcquire(const Node *n);
  void  _sub_Op_LoadFence(const Node *n);
  void  _sub_Op_MemBarAcquireLock(const Node *n);
  void  _sub_Op_MemBarCPUOrder(const Node *n);
  void  _sub_Op_MemBarRelease(const Node *n);
  void  _sub_Op_StoreFence(const Node *n);
  void  _sub_Op_StoreStoreFence(const Node *n);
  void  _sub_Op_MemBarReleaseLock(const Node *n);
  void  _sub_Op_MemBarStoreLoad(const Node *n);
  void  _sub_Op_MemBarVolatile(const Node *n);
  void  _sub_Op_MemBarStoreStore(const Node *n);
  void  _sub_Op_MemBarFull(const Node *n);
  void  _sub_Op_MinI(const Node *n);
  void  _sub_Op_ModI(const Node *n);
  void  _sub_Op_ModL(const Node *n);
  void  _sub_Op_UModI(const Node *n);
  void  _sub_Op_UModL(const Node *n);
  void  _sub_Op_MoveI2F(const Node *n);
  void  _sub_Op_MoveF2I(const Node *n);
  void  _sub_Op_MoveL2D(const Node *n);
  void  _sub_Op_MoveD2L(const Node *n);
  void  _sub_Op_MulD(const Node *n);
  void  _sub_Op_MulF(const Node *n);
  void  _sub_Op_MulHiL(const Node *n);
  void  _sub_Op_MulI(const Node *n);
  void  _sub_Op_MulL(const Node *n);
  void  _sub_Op_NegD(const Node *n);
  void  _sub_Op_NegF(const Node *n);
  void  _sub_Op_OrI(const Node *n);
  void  _sub_Op_OrL(const Node *n);
  void  _sub_Op_OverflowAddI(const Node *n);
  void  _sub_Op_OverflowSubI(const Node *n);
  void  _sub_Op_OverflowAddL(const Node *n);
  void  _sub_Op_OverflowSubL(const Node *n);
  void  _sub_Op_PartialSubtypeCheck(const Node *n);
  void  _sub_Op_PopCountI(const Node *n);
  void  _sub_Op_PopCountL(const Node *n);
  void  _sub_Op_PopCountVI(const Node *n);
  void  _sub_Op_PrefetchAllocation(const Node *n);
  void  _sub_Op_RShiftI(const Node *n);
  void  _sub_Op_RShiftL(const Node *n);
  void  _sub_Op_Rethrow(const Node *n);
  void  _sub_Op_Return(const Node *n);
  void  _sub_Op_RoundDoubleModeV(const Node *n);
  void  _sub_Op_SafePoint(const Node *n);
  void  _sub_Op_SqrtD(const Node *n);
  void  _sub_Op_SqrtF(const Node *n);
  void  _sub_Op_StoreB(const Node *n);
  void  _sub_Op_StoreC(const Node *n);
  void  _sub_Op_StoreD(const Node *n);
  void  _sub_Op_StoreF(const Node *n);
  void  _sub_Op_StoreI(const Node *n);
  void  _sub_Op_StoreL(const Node *n);
  void  _sub_Op_StoreP(const Node *n);
  void  _sub_Op_StoreN(const Node *n);
  void  _sub_Op_StoreNKlass(const Node *n);
  void  _sub_Op_StrComp(const Node *n);
  void  _sub_Op_StrCompressedCopy(const Node *n);
  void  _sub_Op_StrEquals(const Node *n);
  void  _sub_Op_StrIndexOf(const Node *n);
  void  _sub_Op_StrIndexOfChar(const Node *n);
  void  _sub_Op_StrInflatedCopy(const Node *n);
  void  _sub_Op_SubD(const Node *n);
  void  _sub_Op_SubF(const Node *n);
  void  _sub_Op_SubI(const Node *n);
  void  _sub_Op_SubL(const Node *n);
  void  _sub_Op_TailCall(const Node *n);
  void  _sub_Op_TailJump(const Node *n);
  void  _sub_Op_ThreadLocal(const Node *n);
  void  _sub_Op_URShiftI(const Node *n);
  void  _sub_Op_URShiftL(const Node *n);
  void  _sub_Op_XorI(const Node *n);
  void  _sub_Op_XorL(const Node *n);
  void  _sub_Op_AddVB(const Node *n);
  void  _sub_Op_AddVS(const Node *n);
  void  _sub_Op_AddVI(const Node *n);
  void  _sub_Op_AddVL(const Node *n);
  void  _sub_Op_AddVF(const Node *n);
  void  _sub_Op_AddVD(const Node *n);
  void  _sub_Op_SubVB(const Node *n);
  void  _sub_Op_SubVS(const Node *n);
  void  _sub_Op_SubVI(const Node *n);
  void  _sub_Op_SubVL(const Node *n);
  void  _sub_Op_SubVF(const Node *n);
  void  _sub_Op_SubVD(const Node *n);
  void  _sub_Op_MulVB(const Node *n);
  void  _sub_Op_MulVS(const Node *n);
  void  _sub_Op_MulVI(const Node *n);
  void  _sub_Op_MulVF(const Node *n);
  void  _sub_Op_MulVD(const Node *n);
  void  _sub_Op_DivVF(const Node *n);
  void  _sub_Op_DivVD(const Node *n);
  void  _sub_Op_SqrtVD(const Node *n);
  void  _sub_Op_SqrtVF(const Node *n);
  void  _sub_Op_LoadVector(const Node *n);
  void  _sub_Op_StoreVector(const Node *n);
  void  _sub_Op_Replicate(const Node *n);
  void  _sub_Op_VectorReinterpret(const Node *n);
};



// Total number of operands defined in architecture definition
#define FIRST_OPERAND_CLASS   128
#define NUM_OPERANDS          135

// Total number of instructions defined in architecture definition
#define NUM_INSTRUCTIONS   576

//----------------------------Declare classes derived from MachOper----------

class UniverseOper : public MachOper { 
private:
  virtual uint           num_edges() const { return 0; }
public:
  UniverseOper() {}
  virtual MachOper      *clone() const;
  virtual uint           opcode() const { return UNIVERSE; }

#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual const char    *Name() const { return "Universe";}
#endif
};

class sRegIOper : public MachOper { 
private:
  virtual const RegMask *in_RegMask(int index) const;
public:
  sRegIOper() {}
  virtual MachOper      *clone() const;
  virtual uint           opcode() const { return SREGI; }
  virtual int            reg(PhaseRegAlloc *ra_, const Node *node) const {
    return (int)OptoReg::reg2stack(ra_->get_reg_first(node));/* sReg */
  }
  virtual int            reg(PhaseRegAlloc *ra_, const Node *node, int idx) const {
    return (int)OptoReg::reg2stack(ra_->get_reg_first(node->in(idx)));/* sReg */
  }

#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual const char    *Name() const { return "sRegI";}
#endif
};

class sRegPOper : public MachOper { 
private:
  virtual const RegMask *in_RegMask(int index) const;
public:
  sRegPOper() {}
  virtual MachOper      *clone() const;
  virtual uint           opcode() const { return SREGP; }
  virtual int            reg(PhaseRegAlloc *ra_, const Node *node) const {
    return (int)OptoReg::reg2stack(ra_->get_reg_first(node));/* sReg */
  }
  virtual int            reg(PhaseRegAlloc *ra_, const Node *node, int idx) const {
    return (int)OptoReg::reg2stack(ra_->get_reg_first(node->in(idx)));/* sReg */
  }

#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual const char    *Name() const { return "sRegP";}
#endif
};

class sRegFOper : public MachOper { 
private:
  virtual const RegMask *in_RegMask(int index) const;
public:
  sRegFOper() {}
  virtual MachOper      *clone() const;
  virtual uint           opcode() const { return SREGF; }
  virtual int            reg(PhaseRegAlloc *ra_, const Node *node) const {
    return (int)OptoReg::reg2stack(ra_->get_reg_first(node));/* sReg */
  }
  virtual int            reg(PhaseRegAlloc *ra_, const Node *node, int idx) const {
    return (int)OptoReg::reg2stack(ra_->get_reg_first(node->in(idx)));/* sReg */
  }

#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual const char    *Name() const { return "sRegF";}
#endif
};

class sRegDOper : public MachOper { 
private:
  virtual const RegMask *in_RegMask(int index) const;
public:
  sRegDOper() {}
  virtual MachOper      *clone() const;
  virtual uint           opcode() const { return SREGD; }
  virtual int            reg(PhaseRegAlloc *ra_, const Node *node) const {
    return (int)OptoReg::reg2stack(ra_->get_reg_first(node));/* sReg */
  }
  virtual int            reg(PhaseRegAlloc *ra_, const Node *node, int idx) const {
    return (int)OptoReg::reg2stack(ra_->get_reg_first(node->in(idx)));/* sReg */
  }

#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual const char    *Name() const { return "sRegD";}
#endif
};

class sRegLOper : public MachOper { 
private:
  virtual const RegMask *in_RegMask(int index) const;
public:
  sRegLOper() {}
  virtual MachOper      *clone() const;
  virtual uint           opcode() const { return SREGL; }
  virtual int            reg(PhaseRegAlloc *ra_, const Node *node) const {
    return (int)OptoReg::reg2stack(ra_->get_reg_first(node));/* sReg */
  }
  virtual int            reg(PhaseRegAlloc *ra_, const Node *node, int idx) const {
    return (int)OptoReg::reg2stack(ra_->get_reg_first(node->in(idx)));/* sReg */
  }

#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual const char    *Name() const { return "sRegL";}
#endif
};

class vecXOper : public MachOper { 
private:
  virtual const RegMask *in_RegMask(int index) const;
public:
  vecXOper() {}
  virtual MachOper      *clone() const;
  virtual uint           opcode() const { return VECX; }
  virtual const Type    *type() const { return TypeVect::VECTX; }


#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual const char    *Name() const { return "vecX";}
#endif
};

class v16TempRegOper : public MachOper { 
private:
  virtual const RegMask *in_RegMask(int index) const;
public:
  v16TempRegOper() {}
  virtual MachOper      *clone() const;
  virtual uint           opcode() const { return V16TEMPREG; }
  virtual const Type    *type() const { return TypeVect::VECTX; }


#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual const char    *Name() const { return "v16TempReg";}
#endif
};

class v17TempRegOper : public MachOper { 
private:
  virtual const RegMask *in_RegMask(int index) const;
public:
  v17TempRegOper() {}
  virtual MachOper      *clone() const;
  virtual uint           opcode() const { return V17TEMPREG; }
  virtual const Type    *type() const { return TypeVect::VECTX; }


#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual const char    *Name() const { return "v17TempReg";}
#endif
};

class v18TempRegOper : public MachOper { 
private:
  virtual const RegMask *in_RegMask(int index) const;
public:
  v18TempRegOper() {}
  virtual MachOper      *clone() const;
  virtual uint           opcode() const { return V18TEMPREG; }
  virtual const Type    *type() const { return TypeVect::VECTX; }


#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual const char    *Name() const { return "v18TempReg";}
#endif
};

class v19TempRegOper : public MachOper { 
private:
  virtual const RegMask *in_RegMask(int index) const;
public:
  v19TempRegOper() {}
  virtual MachOper      *clone() const;
  virtual uint           opcode() const { return V19TEMPREG; }
  virtual const Type    *type() const { return TypeVect::VECTX; }


#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual const char    *Name() const { return "v19TempReg";}
#endif
};

class v20TempRegOper : public MachOper { 
private:
  virtual const RegMask *in_RegMask(int index) const;
public:
  v20TempRegOper() {}
  virtual MachOper      *clone() const;
  virtual uint           opcode() const { return V20TEMPREG; }
  virtual const Type    *type() const { return TypeVect::VECTX; }


#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual const char    *Name() const { return "v20TempReg";}
#endif
};

class v21TempRegOper : public MachOper { 
private:
  virtual const RegMask *in_RegMask(int index) const;
public:
  v21TempRegOper() {}
  virtual MachOper      *clone() const;
  virtual uint           opcode() const { return V21TEMPREG; }
  virtual const Type    *type() const { return TypeVect::VECTX; }


#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual const char    *Name() const { return "v21TempReg";}
#endif
};

class v22TempRegOper : public MachOper { 
private:
  virtual const RegMask *in_RegMask(int index) const;
public:
  v22TempRegOper() {}
  virtual MachOper      *clone() const;
  virtual uint           opcode() const { return V22TEMPREG; }
  virtual const Type    *type() const { return TypeVect::VECTX; }


#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual const char    *Name() const { return "v22TempReg";}
#endif
};

class v23TempRegOper : public MachOper { 
private:
  virtual const RegMask *in_RegMask(int index) const;
public:
  v23TempRegOper() {}
  virtual MachOper      *clone() const;
  virtual uint           opcode() const { return V23TEMPREG; }
  virtual const Type    *type() const { return TypeVect::VECTX; }


#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual const char    *Name() const { return "v23TempReg";}
#endif
};

class v24TempRegOper : public MachOper { 
private:
  virtual const RegMask *in_RegMask(int index) const;
public:
  v24TempRegOper() {}
  virtual MachOper      *clone() const;
  virtual uint           opcode() const { return V24TEMPREG; }
  virtual const Type    *type() const { return TypeVect::VECTX; }


#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual const char    *Name() const { return "v24TempReg";}
#endif
};

class v25TempRegOper : public MachOper { 
private:
  virtual const RegMask *in_RegMask(int index) const;
public:
  v25TempRegOper() {}
  virtual MachOper      *clone() const;
  virtual uint           opcode() const { return V25TEMPREG; }
  virtual const Type    *type() const { return TypeVect::VECTX; }


#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual const char    *Name() const { return "v25TempReg";}
#endif
};

class immB_minus1Oper : public MachOper { 
private:
  virtual uint           num_edges() const { return 0; }
  int32_t        _c0;
public:
  immB_minus1Oper(int32_t c0)  : _c0(c0) {}
  virtual MachOper      *clone() const;
  virtual void set_con( jint c0 ) { _c0 = c0; }
  virtual uint           opcode() const { return IMMB_MINUS1; }
  virtual const Type    *type() const { return TypeInt::INT; }

  virtual intptr_t       constant() const { return (intptr_t)_c0;  }

#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual void           dump_spec(outputStream *st) const {
   st->print("#%d", _c0);
   st->print("/0x%08x", _c0);
  }
  virtual const char    *Name() const { return "immB_minus1";}
#endif
};

class immB_n0m1Oper : public MachOper { 
private:
  virtual uint           num_edges() const { return 0; }
  int32_t        _c0;
public:
  immB_n0m1Oper(int32_t c0)  : _c0(c0) {}
  virtual MachOper      *clone() const;
  virtual void set_con( jint c0 ) { _c0 = c0; }
  virtual uint           opcode() const { return IMMB_N0M1; }
  virtual const Type    *type() const { return TypeInt::INT; }

  virtual intptr_t       constant() const { return (intptr_t)_c0;  }

#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual void           dump_spec(outputStream *st) const {
   st->print("#%d", _c0);
   st->print("/0x%08x", _c0);
  }
  virtual const char    *Name() const { return "immB_n0m1";}
#endif
};

class immS_minus1Oper : public MachOper { 
private:
  virtual uint           num_edges() const { return 0; }
  int32_t        _c0;
public:
  immS_minus1Oper(int32_t c0)  : _c0(c0) {}
  virtual MachOper      *clone() const;
  virtual void set_con( jint c0 ) { _c0 = c0; }
  virtual uint           opcode() const { return IMMS_MINUS1; }
  virtual const Type    *type() const { return TypeInt::INT; }

  virtual intptr_t       constant() const { return (intptr_t)_c0;  }

#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual void           dump_spec(outputStream *st) const {
   st->print("#%d", _c0);
   st->print("/0x%08x", _c0);
  }
  virtual const char    *Name() const { return "immS_minus1";}
#endif
};

class immS_n0m1Oper : public MachOper { 
private:
  virtual uint           num_edges() const { return 0; }
  int32_t        _c0;
public:
  immS_n0m1Oper(int32_t c0)  : _c0(c0) {}
  virtual MachOper      *clone() const;
  virtual void set_con( jint c0 ) { _c0 = c0; }
  virtual uint           opcode() const { return IMMS_N0M1; }
  virtual const Type    *type() const { return TypeInt::INT; }

  virtual intptr_t       constant() const { return (intptr_t)_c0;  }

#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual void           dump_spec(outputStream *st) const {
   st->print("#%d", _c0);
   st->print("/0x%08x", _c0);
  }
  virtual const char    *Name() const { return "immS_n0m1";}
#endif
};

class immIOper : public MachOper { 
private:
  virtual uint           num_edges() const { return 0; }
  int32_t        _c0;
public:
  immIOper(int32_t c0)  : _c0(c0) {}
  virtual MachOper      *clone() const;
  virtual void set_con( jint c0 ) { _c0 = c0; }
  virtual uint           opcode() const { return IMMI; }
  virtual const Type    *type() const { return TypeInt::INT; }

  virtual intptr_t       constant() const { return (intptr_t)_c0;  }

#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual void           dump_spec(outputStream *st) const {
   st->print("#%d", _c0);
   st->print("/0x%08x", _c0);
  }
  virtual const char    *Name() const { return "immI";}
#endif
};

class immI20Oper : public MachOper { 
private:
  virtual uint           num_edges() const { return 0; }
  int32_t        _c0;
public:
  immI20Oper(int32_t c0)  : _c0(c0) {}
  virtual MachOper      *clone() const;
  virtual void set_con( jint c0 ) { _c0 = c0; }
  virtual uint           opcode() const { return IMMI20; }
  virtual const Type    *type() const { return TypeInt::INT; }

  virtual intptr_t       constant() const { return (intptr_t)_c0;  }

#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual void           dump_spec(outputStream *st) const {
   st->print("#%d", _c0);
   st->print("/0x%08x", _c0);
  }
  virtual const char    *Name() const { return "immI20";}
#endif
};

class immI16Oper : public MachOper { 
private:
  virtual uint           num_edges() const { return 0; }
  int32_t        _c0;
public:
  immI16Oper(int32_t c0)  : _c0(c0) {}
  virtual MachOper      *clone() const;
  virtual void set_con( jint c0 ) { _c0 = c0; }
  virtual uint           opcode() const { return IMMI16; }
  virtual const Type    *type() const { return TypeInt::INT; }

  virtual intptr_t       constant() const { return (intptr_t)_c0;  }

#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual void           dump_spec(outputStream *st) const {
   st->print("#%d", _c0);
   st->print("/0x%08x", _c0);
  }
  virtual const char    *Name() const { return "immI16";}
#endif
};

class immI8Oper : public MachOper { 
private:
  virtual uint           num_edges() const { return 0; }
  int32_t        _c0;
public:
  immI8Oper(int32_t c0)  : _c0(c0) {}
  virtual MachOper      *clone() const;
  virtual void set_con( jint c0 ) { _c0 = c0; }
  virtual uint           opcode() const { return IMMI8; }
  virtual const Type    *type() const { return TypeInt::INT; }

  virtual intptr_t       constant() const { return (intptr_t)_c0;  }

#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual void           dump_spec(outputStream *st) const {
   st->print("#%d", _c0);
   st->print("/0x%08x", _c0);
  }
  virtual const char    *Name() const { return "immI8";}
#endif
};

class immI_0Oper : public MachOper { 
private:
  virtual uint           num_edges() const { return 0; }
  int32_t        _c0;
public:
  immI_0Oper(int32_t c0)  : _c0(c0) {}
  virtual MachOper      *clone() const;
  virtual void set_con( jint c0 ) { _c0 = c0; }
  virtual uint           opcode() const { return IMMI_0; }
  virtual const Type    *type() const { return TypeInt::INT; }

  virtual intptr_t       constant() const { return (intptr_t)_c0;  }

#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual void           dump_spec(outputStream *st) const {
   st->print("#%d", _c0);
   st->print("/0x%08x", _c0);
  }
  virtual const char    *Name() const { return "immI_0";}
#endif
};

class immI_minus1Oper : public MachOper { 
private:
  virtual uint           num_edges() const { return 0; }
  int32_t        _c0;
public:
  immI_minus1Oper(int32_t c0)  : _c0(c0) {}
  virtual MachOper      *clone() const;
  virtual void set_con( jint c0 ) { _c0 = c0; }
  virtual uint           opcode() const { return IMMI_MINUS1; }
  virtual const Type    *type() const { return TypeInt::INT; }

  virtual intptr_t       constant() const { return (intptr_t)_c0;  }

#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual void           dump_spec(outputStream *st) const {
   st->print("#%d", _c0);
   st->print("/0x%08x", _c0);
  }
  virtual const char    *Name() const { return "immI_minus1";}
#endif
};

class immI_n0m1Oper : public MachOper { 
private:
  virtual uint           num_edges() const { return 0; }
  int32_t        _c0;
public:
  immI_n0m1Oper(int32_t c0)  : _c0(c0) {}
  virtual MachOper      *clone() const;
  virtual void set_con( jint c0 ) { _c0 = c0; }
  virtual uint           opcode() const { return IMMI_N0M1; }
  virtual const Type    *type() const { return TypeInt::INT; }

  virtual intptr_t       constant() const { return (intptr_t)_c0;  }

#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual void           dump_spec(outputStream *st) const {
   st->print("#%d", _c0);
   st->print("/0x%08x", _c0);
  }
  virtual const char    *Name() const { return "immI_n0m1";}
#endif
};

class uimmIOper : public MachOper { 
private:
  virtual uint           num_edges() const { return 0; }
  int32_t        _c0;
public:
  uimmIOper(int32_t c0)  : _c0(c0) {}
  virtual MachOper      *clone() const;
  virtual void set_con( jint c0 ) { _c0 = c0; }
  virtual uint           opcode() const { return UIMMI; }
  virtual const Type    *type() const { return TypeInt::INT; }

  virtual intptr_t       constant() const { return (intptr_t)_c0;  }

#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual void           dump_spec(outputStream *st) const {
   st->print("#%d", _c0);
   st->print("/0x%08x", _c0);
  }
  virtual const char    *Name() const { return "uimmI";}
#endif
};

class uimmI16Oper : public MachOper { 
private:
  virtual uint           num_edges() const { return 0; }
  int32_t        _c0;
public:
  uimmI16Oper(int32_t c0)  : _c0(c0) {}
  virtual MachOper      *clone() const;
  virtual void set_con( jint c0 ) { _c0 = c0; }
  virtual uint           opcode() const { return UIMMI16; }
  virtual const Type    *type() const { return TypeInt::INT; }

  virtual intptr_t       constant() const { return (intptr_t)_c0;  }

#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual void           dump_spec(outputStream *st) const {
   st->print("#%d", _c0);
   st->print("/0x%08x", _c0);
  }
  virtual const char    *Name() const { return "uimmI16";}
#endif
};

class uimmI12Oper : public MachOper { 
private:
  virtual uint           num_edges() const { return 0; }
  int32_t        _c0;
public:
  uimmI12Oper(int32_t c0)  : _c0(c0) {}
  virtual MachOper      *clone() const;
  virtual void set_con( jint c0 ) { _c0 = c0; }
  virtual uint           opcode() const { return UIMMI12; }
  virtual const Type    *type() const { return TypeInt::INT; }

  virtual intptr_t       constant() const { return (intptr_t)_c0;  }

#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual void           dump_spec(outputStream *st) const {
   st->print("#%d", _c0);
   st->print("/0x%08x", _c0);
  }
  virtual const char    *Name() const { return "uimmI12";}
#endif
};

class uimmI8Oper : public MachOper { 
private:
  virtual uint           num_edges() const { return 0; }
  int32_t        _c0;
public:
  uimmI8Oper(int32_t c0)  : _c0(c0) {}
  virtual MachOper      *clone() const;
  virtual void set_con( jint c0 ) { _c0 = c0; }
  virtual uint           opcode() const { return UIMMI8; }
  virtual const Type    *type() const { return TypeInt::INT; }

  virtual intptr_t       constant() const { return (intptr_t)_c0;  }

#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual void           dump_spec(outputStream *st) const {
   st->print("#%d", _c0);
   st->print("/0x%08x", _c0);
  }
  virtual const char    *Name() const { return "uimmI8";}
#endif
};

class SSlenDWOper : public MachOper { 
private:
  virtual uint           num_edges() const { return 0; }
  jlong          _c0;
public:
  SSlenDWOper(jlong c0)  : _c0(c0) {}
  virtual MachOper      *clone() const;
  virtual void set_con( jint c0 ) { _c0 = c0; }
  virtual uint           opcode() const { return SSLENDW; }
  virtual const Type    *type() const { return TypeLong::LONG; }

  virtual intptr_t       constant() const {  return (intptr_t)_c0; }
  virtual jlong          constantL() const { return _c0; }

#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual void           dump_spec(outputStream *st) const {
    st->print("#" INT64_FORMAT, (int64_t)_c0);
    st->print("/" UINT64_FORMAT_X_0, (uint64_t)_c0);
  }
  virtual const char    *Name() const { return "SSlenDW";}
#endif
};

class immI_1Oper : public MachOper { 
private:
  virtual uint           num_edges() const { return 0; }
  int32_t        _c0;
public:
  immI_1Oper(int32_t c0)  : _c0(c0) {}
  virtual MachOper      *clone() const;
  virtual void set_con( jint c0 ) { _c0 = c0; }
  virtual uint           opcode() const { return IMMI_1; }
  virtual const Type    *type() const { return TypeInt::INT; }

  virtual intptr_t       constant() const { return (intptr_t)_c0;  }

#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual void           dump_spec(outputStream *st) const {
   st->print("#%d", _c0);
   st->print("/0x%08x", _c0);
  }
  virtual const char    *Name() const { return "immI_1";}
#endif
};

class immI_16Oper : public MachOper { 
private:
  virtual uint           num_edges() const { return 0; }
  int32_t        _c0;
public:
  immI_16Oper(int32_t c0)  : _c0(c0) {}
  virtual MachOper      *clone() const;
  virtual void set_con( jint c0 ) { _c0 = c0; }
  virtual uint           opcode() const { return IMMI_16; }
  virtual const Type    *type() const { return TypeInt::INT; }

  virtual intptr_t       constant() const { return (intptr_t)_c0;  }

#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual void           dump_spec(outputStream *st) const {
   st->print("#%d", _c0);
   st->print("/0x%08x", _c0);
  }
  virtual const char    *Name() const { return "immI_16";}
#endif
};

class immI_24Oper : public MachOper { 
private:
  virtual uint           num_edges() const { return 0; }
  int32_t        _c0;
public:
  immI_24Oper(int32_t c0)  : _c0(c0) {}
  virtual MachOper      *clone() const;
  virtual void set_con( jint c0 ) { _c0 = c0; }
  virtual uint           opcode() const { return IMMI_24; }
  virtual const Type    *type() const { return TypeInt::INT; }

  virtual intptr_t       constant() const { return (intptr_t)_c0;  }

#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual void           dump_spec(outputStream *st) const {
   st->print("#%d", _c0);
   st->print("/0x%08x", _c0);
  }
  virtual const char    *Name() const { return "immI_24";}
#endif
};

class immI_32_63Oper : public MachOper { 
private:
  virtual uint           num_edges() const { return 0; }
  int32_t        _c0;
public:
  immI_32_63Oper(int32_t c0)  : _c0(c0) {}
  virtual MachOper      *clone() const;
  virtual void set_con( jint c0 ) { _c0 = c0; }
  virtual uint           opcode() const { return IMMI_32_63; }
  virtual const Type    *type() const { return TypeInt::INT; }

  virtual intptr_t       constant() const { return (intptr_t)_c0;  }

#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual void           dump_spec(outputStream *st) const {
   st->print("#%d", _c0);
   st->print("/0x%08x", _c0);
  }
  virtual const char    *Name() const { return "immI_32_63";}
#endif
};

class uimmI_LL1Oper : public MachOper { 
private:
  virtual uint           num_edges() const { return 0; }
  int32_t        _c0;
public:
  uimmI_LL1Oper(int32_t c0)  : _c0(c0) {}
  virtual MachOper      *clone() const;
  virtual void set_con( jint c0 ) { _c0 = c0; }
  virtual uint           opcode() const { return UIMMI_LL1; }
  virtual const Type    *type() const { return TypeInt::INT; }

  virtual intptr_t       constant() const { return (intptr_t)_c0;  }

#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual void           dump_spec(outputStream *st) const {
   st->print("#%d", _c0);
   st->print("/0x%08x", _c0);
  }
  virtual const char    *Name() const { return "uimmI_LL1";}
#endif
};

class uimmI_LH1Oper : public MachOper { 
private:
  virtual uint           num_edges() const { return 0; }
  int32_t        _c0;
public:
  uimmI_LH1Oper(int32_t c0)  : _c0(c0) {}
  virtual MachOper      *clone() const;
  virtual void set_con( jint c0 ) { _c0 = c0; }
  virtual uint           opcode() const { return UIMMI_LH1; }
  virtual const Type    *type() const { return TypeInt::INT; }

  virtual intptr_t       constant() const { return (intptr_t)_c0;  }

#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual void           dump_spec(outputStream *st) const {
   st->print("#%d", _c0);
   st->print("/0x%08x", _c0);
  }
  virtual const char    *Name() const { return "uimmI_LH1";}
#endif
};

class immLOper : public MachOper { 
private:
  virtual uint           num_edges() const { return 0; }
  jlong          _c0;
public:
  immLOper(jlong c0)  : _c0(c0) {}
  virtual MachOper      *clone() const;
  virtual void set_con( jint c0 ) { _c0 = c0; }
  virtual uint           opcode() const { return IMML; }
  virtual const Type    *type() const { return TypeLong::LONG; }

  virtual intptr_t       constant() const {  return (intptr_t)_c0; }
  virtual jlong          constantL() const { return _c0; }

#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual void           dump_spec(outputStream *st) const {
    st->print("#" INT64_FORMAT, (int64_t)_c0);
    st->print("/" UINT64_FORMAT_X_0, (uint64_t)_c0);
  }
  virtual const char    *Name() const { return "immL";}
#endif
};

class immL32Oper : public MachOper { 
private:
  virtual uint           num_edges() const { return 0; }
  jlong          _c0;
public:
  immL32Oper(jlong c0)  : _c0(c0) {}
  virtual MachOper      *clone() const;
  virtual void set_con( jint c0 ) { _c0 = c0; }
  virtual uint           opcode() const { return IMML32; }
  virtual const Type    *type() const { return TypeLong::LONG; }

  virtual intptr_t       constant() const {  return (intptr_t)_c0; }
  virtual jlong          constantL() const { return _c0; }

#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual void           dump_spec(outputStream *st) const {
    st->print("#" INT64_FORMAT, (int64_t)_c0);
    st->print("/" UINT64_FORMAT_X_0, (uint64_t)_c0);
  }
  virtual const char    *Name() const { return "immL32";}
#endif
};

class immL20Oper : public MachOper { 
private:
  virtual uint           num_edges() const { return 0; }
  jlong          _c0;
public:
  immL20Oper(jlong c0)  : _c0(c0) {}
  virtual MachOper      *clone() const;
  virtual void set_con( jint c0 ) { _c0 = c0; }
  virtual uint           opcode() const { return IMML20; }
  virtual const Type    *type() const { return TypeLong::LONG; }

  virtual intptr_t       constant() const {  return (intptr_t)_c0; }
  virtual jlong          constantL() const { return _c0; }

#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual void           dump_spec(outputStream *st) const {
    st->print("#" INT64_FORMAT, (int64_t)_c0);
    st->print("/" UINT64_FORMAT_X_0, (uint64_t)_c0);
  }
  virtual const char    *Name() const { return "immL20";}
#endif
};

class immL16Oper : public MachOper { 
private:
  virtual uint           num_edges() const { return 0; }
  jlong          _c0;
public:
  immL16Oper(jlong c0)  : _c0(c0) {}
  virtual MachOper      *clone() const;
  virtual void set_con( jint c0 ) { _c0 = c0; }
  virtual uint           opcode() const { return IMML16; }
  virtual const Type    *type() const { return TypeLong::LONG; }

  virtual intptr_t       constant() const {  return (intptr_t)_c0; }
  virtual jlong          constantL() const { return _c0; }

#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual void           dump_spec(outputStream *st) const {
    st->print("#" INT64_FORMAT, (int64_t)_c0);
    st->print("/" UINT64_FORMAT_X_0, (uint64_t)_c0);
  }
  virtual const char    *Name() const { return "immL16";}
#endif
};

class immL8Oper : public MachOper { 
private:
  virtual uint           num_edges() const { return 0; }
  jlong          _c0;
public:
  immL8Oper(jlong c0)  : _c0(c0) {}
  virtual MachOper      *clone() const;
  virtual void set_con( jint c0 ) { _c0 = c0; }
  virtual uint           opcode() const { return IMML8; }
  virtual const Type    *type() const { return TypeLong::LONG; }

  virtual intptr_t       constant() const {  return (intptr_t)_c0; }
  virtual jlong          constantL() const { return _c0; }

#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual void           dump_spec(outputStream *st) const {
    st->print("#" INT64_FORMAT, (int64_t)_c0);
    st->print("/" UINT64_FORMAT_X_0, (uint64_t)_c0);
  }
  virtual const char    *Name() const { return "immL8";}
#endif
};

class uimmL32Oper : public MachOper { 
private:
  virtual uint           num_edges() const { return 0; }
  jlong          _c0;
public:
  uimmL32Oper(jlong c0)  : _c0(c0) {}
  virtual MachOper      *clone() const;
  virtual void set_con( jint c0 ) { _c0 = c0; }
  virtual uint           opcode() const { return UIMML32; }
  virtual const Type    *type() const { return TypeLong::LONG; }

  virtual intptr_t       constant() const {  return (intptr_t)_c0; }
  virtual jlong          constantL() const { return _c0; }

#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual void           dump_spec(outputStream *st) const {
    st->print("#" INT64_FORMAT, (int64_t)_c0);
    st->print("/" UINT64_FORMAT_X_0, (uint64_t)_c0);
  }
  virtual const char    *Name() const { return "uimmL32";}
#endif
};

class uimmL16Oper : public MachOper { 
private:
  virtual uint           num_edges() const { return 0; }
  jlong          _c0;
public:
  uimmL16Oper(jlong c0)  : _c0(c0) {}
  virtual MachOper      *clone() const;
  virtual void set_con( jint c0 ) { _c0 = c0; }
  virtual uint           opcode() const { return UIMML16; }
  virtual const Type    *type() const { return TypeLong::LONG; }

  virtual intptr_t       constant() const {  return (intptr_t)_c0; }
  virtual jlong          constantL() const { return _c0; }

#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual void           dump_spec(outputStream *st) const {
    st->print("#" INT64_FORMAT, (int64_t)_c0);
    st->print("/" UINT64_FORMAT_X_0, (uint64_t)_c0);
  }
  virtual const char    *Name() const { return "uimmL16";}
#endif
};

class uimmL12Oper : public MachOper { 
private:
  virtual uint           num_edges() const { return 0; }
  jlong          _c0;
public:
  uimmL12Oper(jlong c0)  : _c0(c0) {}
  virtual MachOper      *clone() const;
  virtual void set_con( jint c0 ) { _c0 = c0; }
  virtual uint           opcode() const { return UIMML12; }
  virtual const Type    *type() const { return TypeLong::LONG; }

  virtual intptr_t       constant() const {  return (intptr_t)_c0; }
  virtual jlong          constantL() const { return _c0; }

#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual void           dump_spec(outputStream *st) const {
    st->print("#" INT64_FORMAT, (int64_t)_c0);
    st->print("/" UINT64_FORMAT_X_0, (uint64_t)_c0);
  }
  virtual const char    *Name() const { return "uimmL12";}
#endif
};

class immL_FFFFFFFFOper : public MachOper { 
private:
  virtual uint           num_edges() const { return 0; }
  jlong          _c0;
public:
  immL_FFFFFFFFOper(jlong c0)  : _c0(c0) {}
  virtual MachOper      *clone() const;
  virtual void set_con( jint c0 ) { _c0 = c0; }
  virtual uint           opcode() const { return IMML_FFFFFFFF; }
  virtual const Type    *type() const { return TypeLong::LONG; }

  virtual intptr_t       constant() const {  return (intptr_t)_c0; }
  virtual jlong          constantL() const { return _c0; }

#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual void           dump_spec(outputStream *st) const {
    st->print("#" INT64_FORMAT, (int64_t)_c0);
    st->print("/" UINT64_FORMAT_X_0, (uint64_t)_c0);
  }
  virtual const char    *Name() const { return "immL_FFFFFFFF";}
#endif
};

class immL_0Oper : public MachOper { 
private:
  virtual uint           num_edges() const { return 0; }
  jlong          _c0;
public:
  immL_0Oper(jlong c0)  : _c0(c0) {}
  virtual MachOper      *clone() const;
  virtual void set_con( jint c0 ) { _c0 = c0; }
  virtual uint           opcode() const { return IMML_0; }
  virtual const Type    *type() const { return TypeLong::LONG; }

  virtual intptr_t       constant() const {  return (intptr_t)_c0; }
  virtual jlong          constantL() const { return _c0; }

#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual void           dump_spec(outputStream *st) const {
    st->print("#" INT64_FORMAT, (int64_t)_c0);
    st->print("/" UINT64_FORMAT_X_0, (uint64_t)_c0);
  }
  virtual const char    *Name() const { return "immL_0";}
#endif
};

class uimmL_LL1Oper : public MachOper { 
private:
  virtual uint           num_edges() const { return 0; }
  jlong          _c0;
public:
  uimmL_LL1Oper(jlong c0)  : _c0(c0) {}
  virtual MachOper      *clone() const;
  virtual void set_con( jint c0 ) { _c0 = c0; }
  virtual uint           opcode() const { return UIMML_LL1; }
  virtual const Type    *type() const { return TypeLong::LONG; }

  virtual intptr_t       constant() const {  return (intptr_t)_c0; }
  virtual jlong          constantL() const { return _c0; }

#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual void           dump_spec(outputStream *st) const {
    st->print("#" INT64_FORMAT, (int64_t)_c0);
    st->print("/" UINT64_FORMAT_X_0, (uint64_t)_c0);
  }
  virtual const char    *Name() const { return "uimmL_LL1";}
#endif
};

class uimmL_LH1Oper : public MachOper { 
private:
  virtual uint           num_edges() const { return 0; }
  jlong          _c0;
public:
  uimmL_LH1Oper(jlong c0)  : _c0(c0) {}
  virtual MachOper      *clone() const;
  virtual void set_con( jint c0 ) { _c0 = c0; }
  virtual uint           opcode() const { return UIMML_LH1; }
  virtual const Type    *type() const { return TypeLong::LONG; }

  virtual intptr_t       constant() const {  return (intptr_t)_c0; }
  virtual jlong          constantL() const { return _c0; }

#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual void           dump_spec(outputStream *st) const {
    st->print("#" INT64_FORMAT, (int64_t)_c0);
    st->print("/" UINT64_FORMAT_X_0, (uint64_t)_c0);
  }
  virtual const char    *Name() const { return "uimmL_LH1";}
#endif
};

class uimmL_HL1Oper : public MachOper { 
private:
  virtual uint           num_edges() const { return 0; }
  jlong          _c0;
public:
  uimmL_HL1Oper(jlong c0)  : _c0(c0) {}
  virtual MachOper      *clone() const;
  virtual void set_con( jint c0 ) { _c0 = c0; }
  virtual uint           opcode() const { return UIMML_HL1; }
  virtual const Type    *type() const { return TypeLong::LONG; }

  virtual intptr_t       constant() const {  return (intptr_t)_c0; }
  virtual jlong          constantL() const { return _c0; }

#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual void           dump_spec(outputStream *st) const {
    st->print("#" INT64_FORMAT, (int64_t)_c0);
    st->print("/" UINT64_FORMAT_X_0, (uint64_t)_c0);
  }
  virtual const char    *Name() const { return "uimmL_HL1";}
#endif
};

class uimmL_HH1Oper : public MachOper { 
private:
  virtual uint           num_edges() const { return 0; }
  jlong          _c0;
public:
  uimmL_HH1Oper(jlong c0)  : _c0(c0) {}
  virtual MachOper      *clone() const;
  virtual void set_con( jint c0 ) { _c0 = c0; }
  virtual uint           opcode() const { return UIMML_HH1; }
  virtual const Type    *type() const { return TypeLong::LONG; }

  virtual intptr_t       constant() const {  return (intptr_t)_c0; }
  virtual jlong          constantL() const { return _c0; }

#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual void           dump_spec(outputStream *st) const {
    st->print("#" INT64_FORMAT, (int64_t)_c0);
    st->print("/" UINT64_FORMAT_X_0, (uint64_t)_c0);
  }
  virtual const char    *Name() const { return "uimmL_HH1";}
#endif
};

class immL_32bitsOper : public MachOper { 
private:
  virtual uint           num_edges() const { return 0; }
  jlong          _c0;
public:
  immL_32bitsOper(jlong c0)  : _c0(c0) {}
  virtual MachOper      *clone() const;
  virtual void set_con( jint c0 ) { _c0 = c0; }
  virtual uint           opcode() const { return IMML_32BITS; }
  virtual const Type    *type() const { return TypeLong::LONG; }

  virtual intptr_t       constant() const {  return (intptr_t)_c0; }
  virtual jlong          constantL() const { return _c0; }

#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual void           dump_spec(outputStream *st) const {
    st->print("#" INT64_FORMAT, (int64_t)_c0);
    st->print("/" UINT64_FORMAT_X_0, (uint64_t)_c0);
  }
  virtual const char    *Name() const { return "immL_32bits";}
#endif
};

class immPOper : public MachOper { 
private:
  virtual uint           num_edges() const { return 0; }
  const TypePtr *_c0;
public:
  immPOper(const TypePtr *c0)  : _c0(c0) {}
  virtual MachOper      *clone() const;
  virtual uint           opcode() const { return IMMP; }
  virtual const Type    *type() const { return _c0; }

  virtual intptr_t       constant() const { return _c0->get_con(); }
  virtual relocInfo::relocType           constant_reloc() const { return _c0->reloc(); }

#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual void           dump_spec(outputStream *st) const {
    _c0->dump_on(st);
  }
  virtual const char    *Name() const { return "immP";}
#endif
};

class immP16Oper : public MachOper { 
private:
  virtual uint           num_edges() const { return 0; }
  const TypePtr *_c0;
public:
  immP16Oper(const TypePtr *c0)  : _c0(c0) {}
  virtual MachOper      *clone() const;
  virtual uint           opcode() const { return IMMP16; }
  virtual const Type    *type() const { return _c0; }

  virtual intptr_t       constant() const { return _c0->get_con(); }
  virtual relocInfo::relocType           constant_reloc() const { return _c0->reloc(); }

#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual void           dump_spec(outputStream *st) const {
    _c0->dump_on(st);
  }
  virtual const char    *Name() const { return "immP16";}
#endif
};

class immP8Oper : public MachOper { 
private:
  virtual uint           num_edges() const { return 0; }
  const TypePtr *_c0;
public:
  immP8Oper(const TypePtr *c0)  : _c0(c0) {}
  virtual MachOper      *clone() const;
  virtual uint           opcode() const { return IMMP8; }
  virtual const Type    *type() const { return _c0; }

  virtual intptr_t       constant() const { return _c0->get_con(); }
  virtual relocInfo::relocType           constant_reloc() const { return _c0->reloc(); }

#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual void           dump_spec(outputStream *st) const {
    _c0->dump_on(st);
  }
  virtual const char    *Name() const { return "immP8";}
#endif
};

class immP0Oper : public MachOper { 
private:
  virtual uint           num_edges() const { return 0; }
  const TypePtr *_c0;
public:
  immP0Oper(const TypePtr *c0)  : _c0(c0) {}
  virtual MachOper      *clone() const;
  virtual uint           opcode() const { return IMMP0; }
  virtual const Type    *type() const { return _c0; }

  virtual intptr_t       constant() const { return _c0->get_con(); }
  virtual relocInfo::relocType           constant_reloc() const { return _c0->reloc(); }

#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual void           dump_spec(outputStream *st) const {
    _c0->dump_on(st);
  }
  virtual const char    *Name() const { return "immP0";}
#endif
};

class immNOper : public MachOper { 
private:
  virtual uint           num_edges() const { return 0; }
  const TypeNarrowOop *_c0;
public:
  immNOper(const TypeNarrowOop *c0)  : _c0(c0) {}
  virtual MachOper      *clone() const;
  virtual uint           opcode() const { return IMMN; }
  virtual const Type    *type() const { return _c0; }

  virtual intptr_t       constant() const { return _c0->get_ptrtype()->get_con(); }
  virtual relocInfo::relocType           constant_reloc() const { return _c0->get_ptrtype()->reloc(); }

#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual void           dump_spec(outputStream *st) const {
    _c0->dump_on(st);
  }
  virtual const char    *Name() const { return "immN";}
#endif
};

class immNKlassOper : public MachOper { 
private:
  virtual uint           num_edges() const { return 0; }
  const TypeNarrowKlass *_c0;
public:
  immNKlassOper(const TypeNarrowKlass *c0)  : _c0(c0) {}
  virtual MachOper      *clone() const;
  virtual uint           opcode() const { return IMMNKLASS; }
  virtual const Type    *type() const { return _c0; }

  virtual intptr_t       constant() const { return _c0->get_ptrtype()->get_con(); }
  virtual relocInfo::relocType           constant_reloc() const { return _c0->get_ptrtype()->reloc(); }

#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual void           dump_spec(outputStream *st) const {
    _c0->dump_on(st);
  }
  virtual const char    *Name() const { return "immNKlass";}
#endif
};

class immN8Oper : public MachOper { 
private:
  virtual uint           num_edges() const { return 0; }
  const TypeNarrowOop *_c0;
public:
  immN8Oper(const TypeNarrowOop *c0)  : _c0(c0) {}
  virtual MachOper      *clone() const;
  virtual uint           opcode() const { return IMMN8; }
  virtual const Type    *type() const { return _c0; }

  virtual intptr_t       constant() const { return _c0->get_ptrtype()->get_con(); }
  virtual relocInfo::relocType           constant_reloc() const { return _c0->get_ptrtype()->reloc(); }

#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual void           dump_spec(outputStream *st) const {
    _c0->dump_on(st);
  }
  virtual const char    *Name() const { return "immN8";}
#endif
};

class immN0Oper : public MachOper { 
private:
  virtual uint           num_edges() const { return 0; }
  const TypeNarrowOop *_c0;
public:
  immN0Oper(const TypeNarrowOop *c0)  : _c0(c0) {}
  virtual MachOper      *clone() const;
  virtual uint           opcode() const { return IMMN0; }
  virtual const Type    *type() const { return _c0; }

  virtual intptr_t       constant() const { return _c0->get_ptrtype()->get_con(); }
  virtual relocInfo::relocType           constant_reloc() const { return _c0->get_ptrtype()->reloc(); }

#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual void           dump_spec(outputStream *st) const {
    _c0->dump_on(st);
  }
  virtual const char    *Name() const { return "immN0";}
#endif
};

class immDOper : public MachOper { 
private:
  virtual uint           num_edges() const { return 0; }
  jdouble        _c0;
public:
  immDOper(jdouble c0)  : _c0(c0) {}
  virtual MachOper      *clone() const;
  virtual uint           opcode() const { return IMMD; }
  virtual const Type    *type() const { return Type::DOUBLE; }

  virtual intptr_t       constant() const { ShouldNotReachHere(); return 0;  }
  virtual jdouble        constantD() const { return _c0; }

#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual void           dump_spec(outputStream *st) const {
    st->print("#%f", _c0);
    jlong _c0l = JavaValue(_c0).get_jlong();
    st->print("/" UINT64_FORMAT_X_0, (uint64_t)_c0l);
  }
  virtual const char    *Name() const { return "immD";}
#endif
};

class immDpm0Oper : public MachOper { 
private:
  virtual uint           num_edges() const { return 0; }
  jdouble        _c0;
public:
  immDpm0Oper(jdouble c0)  : _c0(c0) {}
  virtual MachOper      *clone() const;
  virtual uint           opcode() const { return IMMDPM0; }
  virtual const Type    *type() const { return Type::DOUBLE; }

  virtual intptr_t       constant() const { ShouldNotReachHere(); return 0;  }
  virtual jdouble        constantD() const { return _c0; }

#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual void           dump_spec(outputStream *st) const {
    st->print("#%f", _c0);
    jlong _c0l = JavaValue(_c0).get_jlong();
    st->print("/" UINT64_FORMAT_X_0, (uint64_t)_c0l);
  }
  virtual const char    *Name() const { return "immDpm0";}
#endif
};

class immDp0Oper : public MachOper { 
private:
  virtual uint           num_edges() const { return 0; }
  jdouble        _c0;
public:
  immDp0Oper(jdouble c0)  : _c0(c0) {}
  virtual MachOper      *clone() const;
  virtual uint           opcode() const { return IMMDP0; }
  virtual const Type    *type() const { return Type::DOUBLE; }

  virtual intptr_t       constant() const { ShouldNotReachHere(); return 0;  }
  virtual jdouble        constantD() const { return _c0; }

#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual void           dump_spec(outputStream *st) const {
    st->print("#%f", _c0);
    jlong _c0l = JavaValue(_c0).get_jlong();
    st->print("/" UINT64_FORMAT_X_0, (uint64_t)_c0l);
  }
  virtual const char    *Name() const { return "immDp0";}
#endif
};

class immFOper : public MachOper { 
private:
  virtual uint           num_edges() const { return 0; }
  jfloat         _c0;
public:
  immFOper(jfloat c0)  : _c0(c0) {}
  virtual MachOper      *clone() const;
  virtual uint           opcode() const { return IMMF; }
  virtual const Type    *type() const { return Type::FLOAT; }

  virtual intptr_t       constant() const { ShouldNotReachHere(); return 0;  }
  virtual jfloat         constantF() const { return (jfloat)_c0; }

#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual void           dump_spec(outputStream *st) const {
    st->print("#%f", _c0);
    jint _c0i = JavaValue(_c0).get_jint();
    st->print("/0x%x/", _c0i);
  }
  virtual const char    *Name() const { return "immF";}
#endif
};

class immFpm0Oper : public MachOper { 
private:
  virtual uint           num_edges() const { return 0; }
  jfloat         _c0;
public:
  immFpm0Oper(jfloat c0)  : _c0(c0) {}
  virtual MachOper      *clone() const;
  virtual uint           opcode() const { return IMMFPM0; }
  virtual const Type    *type() const { return Type::FLOAT; }

  virtual intptr_t       constant() const { ShouldNotReachHere(); return 0;  }
  virtual jfloat         constantF() const { return (jfloat)_c0; }

#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual void           dump_spec(outputStream *st) const {
    st->print("#%f", _c0);
    jint _c0i = JavaValue(_c0).get_jint();
    st->print("/0x%x/", _c0i);
  }
  virtual const char    *Name() const { return "immFpm0";}
#endif
};

class immFp0Oper : public MachOper { 
private:
  virtual uint           num_edges() const { return 0; }
  jfloat         _c0;
public:
  immFp0Oper(jfloat c0)  : _c0(c0) {}
  virtual MachOper      *clone() const;
  virtual uint           opcode() const { return IMMFP0; }
  virtual const Type    *type() const { return Type::FLOAT; }

  virtual intptr_t       constant() const { ShouldNotReachHere(); return 0;  }
  virtual jfloat         constantF() const { return (jfloat)_c0; }

#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual void           dump_spec(outputStream *st) const {
    st->print("#%f", _c0);
    jint _c0i = JavaValue(_c0).get_jint();
    st->print("/0x%x/", _c0i);
  }
  virtual const char    *Name() const { return "immFp0";}
#endif
};

class iRegIOper : public MachOper { 
private:
  virtual const RegMask *in_RegMask(int index) const;
public:
  iRegIOper() {}
  virtual MachOper      *clone() const;
  virtual uint           opcode() const { return IREGI; }
  virtual const Type    *type() const { return TypeInt::INT; }


#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual const char    *Name() const { return "iRegI";}
#endif
};

class noArg_iRegIOper : public MachOper { 
private:
  virtual const RegMask *in_RegMask(int index) const;
public:
  noArg_iRegIOper() {}
  virtual MachOper      *clone() const;
  virtual uint           opcode() const { return NOARG_IREGI; }
  virtual const Type    *type() const { return TypeInt::INT; }


#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual const char    *Name() const { return "noArg_iRegI";}
#endif
};

class revenRegIOper : public MachOper { 
private:
  virtual const RegMask *in_RegMask(int index) const;
public:
  revenRegIOper() {}
  virtual MachOper      *clone() const;
  virtual uint           opcode() const { return REVENREGI; }
  virtual const Type    *type() const { return TypeInt::INT; }


#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual const char    *Name() const { return "revenRegI";}
#endif
};

class roddRegIOper : public MachOper { 
private:
  virtual const RegMask *in_RegMask(int index) const;
public:
  roddRegIOper() {}
  virtual MachOper      *clone() const;
  virtual uint           opcode() const { return RODDREGI; }
  virtual const Type    *type() const { return TypeInt::INT; }


#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual const char    *Name() const { return "roddRegI";}
#endif
};

class rarg1RegIOper : public MachOper { 
private:
  virtual const RegMask *in_RegMask(int index) const;
public:
  rarg1RegIOper() {}
  virtual MachOper      *clone() const;
  virtual uint           opcode() const { return RARG1REGI; }
  virtual const Type    *type() const { return TypeInt::INT; }


#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual const char    *Name() const { return "rarg1RegI";}
#endif
};

class rarg2RegIOper : public MachOper { 
private:
  virtual const RegMask *in_RegMask(int index) const;
public:
  rarg2RegIOper() {}
  virtual MachOper      *clone() const;
  virtual uint           opcode() const { return RARG2REGI; }
  virtual const Type    *type() const { return TypeInt::INT; }


#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual const char    *Name() const { return "rarg2RegI";}
#endif
};

class rarg3RegIOper : public MachOper { 
private:
  virtual const RegMask *in_RegMask(int index) const;
public:
  rarg3RegIOper() {}
  virtual MachOper      *clone() const;
  virtual uint           opcode() const { return RARG3REGI; }
  virtual const Type    *type() const { return TypeInt::INT; }


#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual const char    *Name() const { return "rarg3RegI";}
#endif
};

class rarg4RegIOper : public MachOper { 
private:
  virtual const RegMask *in_RegMask(int index) const;
public:
  rarg4RegIOper() {}
  virtual MachOper      *clone() const;
  virtual uint           opcode() const { return RARG4REGI; }
  virtual const Type    *type() const { return TypeInt::INT; }


#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual const char    *Name() const { return "rarg4RegI";}
#endif
};

class rarg5RegIOper : public MachOper { 
private:
  virtual const RegMask *in_RegMask(int index) const;
public:
  rarg5RegIOper() {}
  virtual MachOper      *clone() const;
  virtual uint           opcode() const { return RARG5REGI; }
  virtual const Type    *type() const { return TypeInt::INT; }


#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual const char    *Name() const { return "rarg5RegI";}
#endif
};

class noOdd_iRegIOper : public MachOper { 
private:
  virtual const RegMask *in_RegMask(int index) const;
public:
  noOdd_iRegIOper() {}
  virtual MachOper      *clone() const;
  virtual uint           opcode() const { return NOODD_IREGI; }
  virtual const Type    *type() const { return TypeInt::INT; }


#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual const char    *Name() const { return "noOdd_iRegI";}
#endif
};

class iRegPOper : public MachOper { 
private:
  virtual const RegMask *in_RegMask(int index) const;
public:
  iRegPOper() {}
  virtual MachOper      *clone() const;
  virtual uint           opcode() const { return IREGP; }
  virtual const Type    *type() const { return TypePtr::BOTTOM; }


#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual const char    *Name() const { return "iRegP";}
#endif
};

class threadRegPOper : public MachOper { 
private:
  virtual const RegMask *in_RegMask(int index) const;
public:
  threadRegPOper() {}
  virtual MachOper      *clone() const;
  virtual uint           opcode() const { return THREADREGP; }
  virtual const Type    *type() const { return TypePtr::BOTTOM; }


#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual const char    *Name() const { return "threadRegP";}
#endif
};

class r10TempRegPOper : public MachOper { 
private:
  virtual const RegMask *in_RegMask(int index) const;
public:
  r10TempRegPOper() {}
  virtual MachOper      *clone() const;
  virtual uint           opcode() const { return R10TEMPREGP; }
  virtual const Type    *type() const { return TypePtr::BOTTOM; }


#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual const char    *Name() const { return "r10TempRegP";}
#endif
};

class r11TempRegPOper : public MachOper { 
private:
  virtual const RegMask *in_RegMask(int index) const;
public:
  r11TempRegPOper() {}
  virtual MachOper      *clone() const;
  virtual uint           opcode() const { return R11TEMPREGP; }
  virtual const Type    *type() const { return TypePtr::BOTTOM; }


#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual const char    *Name() const { return "r11TempRegP";}
#endif
};

class noArg_iRegPOper : public MachOper { 
private:
  virtual const RegMask *in_RegMask(int index) const;
public:
  noArg_iRegPOper() {}
  virtual MachOper      *clone() const;
  virtual uint           opcode() const { return NOARG_IREGP; }
  virtual const Type    *type() const { return TypePtr::BOTTOM; }


#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual const char    *Name() const { return "noArg_iRegP";}
#endif
};

class rarg1RegPOper : public MachOper { 
private:
  virtual const RegMask *in_RegMask(int index) const;
public:
  rarg1RegPOper() {}
  virtual MachOper      *clone() const;
  virtual uint           opcode() const { return RARG1REGP; }
  virtual const Type    *type() const { return TypePtr::BOTTOM; }


#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual const char    *Name() const { return "rarg1RegP";}
#endif
};

class rarg2RegPOper : public MachOper { 
private:
  virtual const RegMask *in_RegMask(int index) const;
public:
  rarg2RegPOper() {}
  virtual MachOper      *clone() const;
  virtual uint           opcode() const { return RARG2REGP; }
  virtual const Type    *type() const { return TypePtr::BOTTOM; }


#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual const char    *Name() const { return "rarg2RegP";}
#endif
};

class rarg3RegPOper : public MachOper { 
private:
  virtual const RegMask *in_RegMask(int index) const;
public:
  rarg3RegPOper() {}
  virtual MachOper      *clone() const;
  virtual uint           opcode() const { return RARG3REGP; }
  virtual const Type    *type() const { return TypePtr::BOTTOM; }


#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual const char    *Name() const { return "rarg3RegP";}
#endif
};

class rarg4RegPOper : public MachOper { 
private:
  virtual const RegMask *in_RegMask(int index) const;
public:
  rarg4RegPOper() {}
  virtual MachOper      *clone() const;
  virtual uint           opcode() const { return RARG4REGP; }
  virtual const Type    *type() const { return TypePtr::BOTTOM; }


#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual const char    *Name() const { return "rarg4RegP";}
#endif
};

class rarg5RegPOper : public MachOper { 
private:
  virtual const RegMask *in_RegMask(int index) const;
public:
  rarg5RegPOper() {}
  virtual MachOper      *clone() const;
  virtual uint           opcode() const { return RARG5REGP; }
  virtual const Type    *type() const { return TypePtr::BOTTOM; }


#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual const char    *Name() const { return "rarg5RegP";}
#endif
};

class memoryRegPOper : public MachOper { 
private:
  virtual const RegMask *in_RegMask(int index) const;
public:
  memoryRegPOper() {}
  virtual MachOper      *clone() const;
  virtual uint           opcode() const { return MEMORYREGP; }
  virtual const Type    *type() const { return TypePtr::BOTTOM; }


#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual const char    *Name() const { return "memoryRegP";}
#endif
};

class revenRegPOper : public MachOper { 
private:
  virtual const RegMask *in_RegMask(int index) const;
public:
  revenRegPOper() {}
  virtual MachOper      *clone() const;
  virtual uint           opcode() const { return REVENREGP; }
  virtual const Type    *type() const { return TypePtr::BOTTOM; }


#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual const char    *Name() const { return "revenRegP";}
#endif
};

class roddRegPOper : public MachOper { 
private:
  virtual const RegMask *in_RegMask(int index) const;
public:
  roddRegPOper() {}
  virtual MachOper      *clone() const;
  virtual uint           opcode() const { return RODDREGP; }
  virtual const Type    *type() const { return TypePtr::BOTTOM; }


#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual const char    *Name() const { return "roddRegP";}
#endif
};

class iRegNOper : public MachOper { 
private:
  virtual const RegMask *in_RegMask(int index) const;
public:
  iRegNOper() {}
  virtual MachOper      *clone() const;
  virtual uint           opcode() const { return IREGN; }
  virtual const Type    *type() const { return TypeNarrowOop::BOTTOM; }


#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual const char    *Name() const { return "iRegN";}
#endif
};

class noArg_iRegNOper : public MachOper { 
private:
  virtual const RegMask *in_RegMask(int index) const;
public:
  noArg_iRegNOper() {}
  virtual MachOper      *clone() const;
  virtual uint           opcode() const { return NOARG_IREGN; }
  virtual const Type    *type() const { return TypeNarrowOop::BOTTOM; }


#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual const char    *Name() const { return "noArg_iRegN";}
#endif
};

class rarg1RegNOper : public MachOper { 
private:
  virtual const RegMask *in_RegMask(int index) const;
public:
  rarg1RegNOper() {}
  virtual MachOper      *clone() const;
  virtual uint           opcode() const { return RARG1REGN; }
  virtual const Type    *type() const { return TypeNarrowOop::BOTTOM; }


#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual const char    *Name() const { return "rarg1RegN";}
#endif
};

class rarg2RegNOper : public MachOper { 
private:
  virtual const RegMask *in_RegMask(int index) const;
public:
  rarg2RegNOper() {}
  virtual MachOper      *clone() const;
  virtual uint           opcode() const { return RARG2REGN; }
  virtual const Type    *type() const { return TypeNarrowOop::BOTTOM; }


#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual const char    *Name() const { return "rarg2RegN";}
#endif
};

class rarg3RegNOper : public MachOper { 
private:
  virtual const RegMask *in_RegMask(int index) const;
public:
  rarg3RegNOper() {}
  virtual MachOper      *clone() const;
  virtual uint           opcode() const { return RARG3REGN; }
  virtual const Type    *type() const { return TypeNarrowOop::BOTTOM; }


#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual const char    *Name() const { return "rarg3RegN";}
#endif
};

class rarg4RegNOper : public MachOper { 
private:
  virtual const RegMask *in_RegMask(int index) const;
public:
  rarg4RegNOper() {}
  virtual MachOper      *clone() const;
  virtual uint           opcode() const { return RARG4REGN; }
  virtual const Type    *type() const { return TypeNarrowOop::BOTTOM; }


#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual const char    *Name() const { return "rarg4RegN";}
#endif
};

class rarg5RegNOper : public MachOper { 
private:
  virtual const RegMask *in_RegMask(int index) const;
public:
  rarg5RegNOper() {}
  virtual MachOper      *clone() const;
  virtual uint           opcode() const { return RARG5REGN; }
  virtual const Type    *type() const { return TypeNarrowOop::BOTTOM; }


#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual const char    *Name() const { return "rarg5RegN";}
#endif
};

class iRegLOper : public MachOper { 
private:
  virtual const RegMask *in_RegMask(int index) const;
public:
  iRegLOper() {}
  virtual MachOper      *clone() const;
  virtual uint           opcode() const { return IREGL; }
  virtual const Type    *type() const { return TypeLong::LONG; }


#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual const char    *Name() const { return "iRegL";}
#endif
};

class revenRegLOper : public MachOper { 
private:
  virtual const RegMask *in_RegMask(int index) const;
public:
  revenRegLOper() {}
  virtual MachOper      *clone() const;
  virtual uint           opcode() const { return REVENREGL; }
  virtual const Type    *type() const { return TypeLong::LONG; }


#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual const char    *Name() const { return "revenRegL";}
#endif
};

class roddRegLOper : public MachOper { 
private:
  virtual const RegMask *in_RegMask(int index) const;
public:
  roddRegLOper() {}
  virtual MachOper      *clone() const;
  virtual uint           opcode() const { return RODDREGL; }
  virtual const Type    *type() const { return TypeLong::LONG; }


#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual const char    *Name() const { return "roddRegL";}
#endif
};

class allRoddRegLOper : public MachOper { 
private:
  virtual const RegMask *in_RegMask(int index) const;
public:
  allRoddRegLOper() {}
  virtual MachOper      *clone() const;
  virtual uint           opcode() const { return ALLRODDREGL; }
  virtual const Type    *type() const { return TypeLong::LONG; }


#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual const char    *Name() const { return "allRoddRegL";}
#endif
};

class rarg1RegLOper : public MachOper { 
private:
  virtual const RegMask *in_RegMask(int index) const;
public:
  rarg1RegLOper() {}
  virtual MachOper      *clone() const;
  virtual uint           opcode() const { return RARG1REGL; }
  virtual const Type    *type() const { return TypeLong::LONG; }


#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual const char    *Name() const { return "rarg1RegL";}
#endif
};

class rarg5RegLOper : public MachOper { 
private:
  virtual const RegMask *in_RegMask(int index) const;
public:
  rarg5RegLOper() {}
  virtual MachOper      *clone() const;
  virtual uint           opcode() const { return RARG5REGL; }
  virtual const Type    *type() const { return TypeLong::LONG; }


#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual const char    *Name() const { return "rarg5RegL";}
#endif
};

class flagsRegOper : public MachOper { 
private:
  virtual const RegMask *in_RegMask(int index) const;
public:
  flagsRegOper() {}
  virtual MachOper      *clone() const;
  virtual uint           opcode() const { return FLAGSREG; }
  virtual const Type    *type() const { return TypeInt::CC /*flags*/; }


#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual const char    *Name() const { return "flagsReg";}
#endif
};

class regDOper : public MachOper { 
private:
  virtual const RegMask *in_RegMask(int index) const;
public:
  regDOper() {}
  virtual MachOper      *clone() const;
  virtual uint           opcode() const { return REGD; }
  virtual const Type    *type() const { return Type::DOUBLE; }


#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual const char    *Name() const { return "regD";}
#endif
};

class regFOper : public MachOper { 
private:
  virtual const RegMask *in_RegMask(int index) const;
public:
  regFOper() {}
  virtual MachOper      *clone() const;
  virtual uint           opcode() const { return REGF; }
  virtual const Type    *type() const { return Type::FLOAT; }


#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual const char    *Name() const { return "regF";}
#endif
};

class inline_cache_regPOper : public MachOper { 
private:
  virtual const RegMask *in_RegMask(int index) const;
public:
  inline_cache_regPOper() {}
  virtual MachOper      *clone() const;
  virtual uint           opcode() const { return INLINE_CACHE_REGP; }
  virtual const Type    *type() const { return TypePtr::BOTTOM; }


#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual const char    *Name() const { return "inline_cache_regP";}
#endif
};

class indirectOper : public MachOper { 
private:
  virtual const RegMask *in_RegMask(int index) const;
public:
  indirectOper() {}
  virtual MachOper      *clone() const;
  virtual uint           opcode() const { return INDIRECT; }
  virtual const Type    *type() const { return TypePtr::BOTTOM; }

  virtual int            base(PhaseRegAlloc *ra_, const Node *node, int idx) const { 
    // Replacement variable: base
    return (int)ra_->get_encode(node->in(idx));
  }
  virtual int            base_position() const { return 0; }
  virtual int            index(PhaseRegAlloc *ra_, const Node *node, int idx) const { 
    return 0xffffFFFF;
  }
  virtual int            scale() const {
    return 0x0;
  }
  virtual int            disp(PhaseRegAlloc *ra_, const Node *node, int idx) const { 
    return 0x0;
  }
  virtual int            constant_disp() const {
    return 0x0;
  }

#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual const char    *Name() const { return "indirect";}
#endif
};

class indOffset20Oper : public MachOper { 
private:
  virtual const RegMask *in_RegMask(int index) const;
  jlong            _c0;
public:
  indOffset20Oper(jlong c0)  : _c0(c0) {}
  virtual MachOper      *clone() const;
  virtual void set_con( jint c0 ) { _c0 = c0; }
  virtual uint           opcode() const { return INDOFFSET20; }

  virtual int            base(PhaseRegAlloc *ra_, const Node *node, int idx) const { 
    // Replacement variable: base
    return (int)ra_->get_encode(node->in(idx));
  }
  virtual int            base_position() const { return 0; }
  virtual int            index(PhaseRegAlloc *ra_, const Node *node, int idx) const { 
    return 0xffffFFFF;
  }
  virtual int            scale() const {
    return 0x0;
  }
  virtual int            disp(PhaseRegAlloc *ra_, const Node *node, int idx) const { 
    // Replacement variable: offset
    return (int)_c0;
  }
  virtual int            constant_disp() const {
    // Replacement variable: offset
    return (int)_c0;
  }

#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual void           dump_spec(outputStream *st) const {
    st->print("#" INT64_FORMAT, (int64_t)_c0);
    st->print("/" UINT64_FORMAT_X_0, (uint64_t)_c0);
  }
  virtual const char    *Name() const { return "indOffset20";}
#endif
};

class indOffset20NarrowOper : public MachOper { 
private:
  virtual const RegMask *in_RegMask(int index) const;
  jlong            _c0;
public:
  indOffset20NarrowOper(jlong c0)  : _c0(c0) {}
  virtual MachOper      *clone() const;
  virtual void set_con( jint c0 ) { _c0 = c0; }
  virtual uint           opcode() const { return INDOFFSET20NARROW; }

  virtual int            base(PhaseRegAlloc *ra_, const Node *node, int idx) const { 
    // Replacement variable: base
    return (int)ra_->get_encode(node->in(idx));
  }
  virtual int            base_position() const { return 0; }
  virtual int            index(PhaseRegAlloc *ra_, const Node *node, int idx) const { 
    return 0xffffFFFF;
  }
  virtual int            scale() const {
    return 0x0;
  }
  virtual int            disp(PhaseRegAlloc *ra_, const Node *node, int idx) const { 
    // Replacement variable: offset
    return (int)_c0;
  }
  virtual int            constant_disp() const {
    // Replacement variable: offset
    return (int)_c0;
  }

#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual void           dump_spec(outputStream *st) const {
    st->print("#" INT64_FORMAT, (int64_t)_c0);
    st->print("/" UINT64_FORMAT_X_0, (uint64_t)_c0);
  }
  virtual const char    *Name() const { return "indOffset20Narrow";}
#endif
};

class indOffset12Oper : public MachOper { 
private:
  virtual const RegMask *in_RegMask(int index) const;
  jlong            _c0;
public:
  indOffset12Oper(jlong c0)  : _c0(c0) {}
  virtual MachOper      *clone() const;
  virtual void set_con( jint c0 ) { _c0 = c0; }
  virtual uint           opcode() const { return INDOFFSET12; }

  virtual int            base(PhaseRegAlloc *ra_, const Node *node, int idx) const { 
    // Replacement variable: base
    return (int)ra_->get_encode(node->in(idx));
  }
  virtual int            base_position() const { return 0; }
  virtual int            index(PhaseRegAlloc *ra_, const Node *node, int idx) const { 
    return 0xffffFFFF;
  }
  virtual int            scale() const {
    return 0x0;
  }
  virtual int            disp(PhaseRegAlloc *ra_, const Node *node, int idx) const { 
    // Replacement variable: offset
    return (int)_c0;
  }
  virtual int            constant_disp() const {
    // Replacement variable: offset
    return (int)_c0;
  }

#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual void           dump_spec(outputStream *st) const {
    st->print("#" INT64_FORMAT, (int64_t)_c0);
    st->print("/" UINT64_FORMAT_X_0, (uint64_t)_c0);
  }
  virtual const char    *Name() const { return "indOffset12";}
#endif
};

class indOffset12NarrowOper : public MachOper { 
private:
  virtual const RegMask *in_RegMask(int index) const;
  jlong            _c0;
public:
  indOffset12NarrowOper(jlong c0)  : _c0(c0) {}
  virtual MachOper      *clone() const;
  virtual void set_con( jint c0 ) { _c0 = c0; }
  virtual uint           opcode() const { return INDOFFSET12NARROW; }

  virtual int            base(PhaseRegAlloc *ra_, const Node *node, int idx) const { 
    // Replacement variable: base
    return (int)ra_->get_encode(node->in(idx));
  }
  virtual int            base_position() const { return 0; }
  virtual int            index(PhaseRegAlloc *ra_, const Node *node, int idx) const { 
    return 0xffffFFFF;
  }
  virtual int            scale() const {
    return 0x0;
  }
  virtual int            disp(PhaseRegAlloc *ra_, const Node *node, int idx) const { 
    // Replacement variable: offset
    return (int)_c0;
  }
  virtual int            constant_disp() const {
    // Replacement variable: offset
    return (int)_c0;
  }

#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual void           dump_spec(outputStream *st) const {
    st->print("#" INT64_FORMAT, (int64_t)_c0);
    st->print("/" UINT64_FORMAT_X_0, (uint64_t)_c0);
  }
  virtual const char    *Name() const { return "indOffset12Narrow";}
#endif
};

class indIndexOper : public MachOper { 
private:
  virtual uint           num_edges() const { return 2; }
  virtual const RegMask *in_RegMask(int index) const;
public:
  indIndexOper() {}
  virtual MachOper      *clone() const;
  virtual uint           opcode() const { return INDINDEX; }

  virtual int            base(PhaseRegAlloc *ra_, const Node *node, int idx) const { 
    // Replacement variable: base
    return (int)ra_->get_encode(node->in(idx));
  }
  virtual int            base_position() const { return 0; }
  virtual int            index(PhaseRegAlloc *ra_, const Node *node, int idx) const { 
    // Replacement variable: index
    return (int)ra_->get_encode(node->in(idx+1));
  }
  virtual int            index_position() const { return 1; }
  virtual int            scale() const {
    return 0x0;
  }
  virtual int            disp(PhaseRegAlloc *ra_, const Node *node, int idx) const { 
    return 0x0;
  }
  virtual int            constant_disp() const {
    return 0x0;
  }

#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual const char    *Name() const { return "indIndex";}
#endif
};

class indOffset20indexOper : public MachOper { 
private:
  virtual uint           num_edges() const { return 2; }
  virtual const RegMask *in_RegMask(int index) const;
  jlong            _c0;
public:
  indOffset20indexOper(jlong c0)  : _c0(c0) {}
  virtual MachOper      *clone() const;
  virtual void set_con( jint c0 ) { _c0 = c0; }
  virtual uint           opcode() const { return INDOFFSET20INDEX; }

  virtual int            base(PhaseRegAlloc *ra_, const Node *node, int idx) const { 
    // Replacement variable: base
    return (int)ra_->get_encode(node->in(idx));
  }
  virtual int            base_position() const { return 0; }
  virtual int            index(PhaseRegAlloc *ra_, const Node *node, int idx) const { 
    // Replacement variable: index
    return (int)ra_->get_encode(node->in(idx+1));
  }
  virtual int            index_position() const { return 1; }
  virtual int            scale() const {
    return 0x0;
  }
  virtual int            disp(PhaseRegAlloc *ra_, const Node *node, int idx) const { 
    // Replacement variable: offset
    return (int)_c0;
  }
  virtual int            constant_disp() const {
    // Replacement variable: offset
    return (int)_c0;
  }

#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual void           dump_spec(outputStream *st) const {
    st->print("#" INT64_FORMAT, (int64_t)_c0);
    st->print("/" UINT64_FORMAT_X_0, (uint64_t)_c0);
  }
  virtual const char    *Name() const { return "indOffset20index";}
#endif
};

class indOffset20indexNarrowOper : public MachOper { 
private:
  virtual uint           num_edges() const { return 2; }
  virtual const RegMask *in_RegMask(int index) const;
  jlong            _c0;
public:
  indOffset20indexNarrowOper(jlong c0)  : _c0(c0) {}
  virtual MachOper      *clone() const;
  virtual void set_con( jint c0 ) { _c0 = c0; }
  virtual uint           opcode() const { return INDOFFSET20INDEXNARROW; }

  virtual int            base(PhaseRegAlloc *ra_, const Node *node, int idx) const { 
    // Replacement variable: base
    return (int)ra_->get_encode(node->in(idx));
  }
  virtual int            base_position() const { return 0; }
  virtual int            index(PhaseRegAlloc *ra_, const Node *node, int idx) const { 
    // Replacement variable: index
    return (int)ra_->get_encode(node->in(idx+1));
  }
  virtual int            index_position() const { return 1; }
  virtual int            scale() const {
    return 0x0;
  }
  virtual int            disp(PhaseRegAlloc *ra_, const Node *node, int idx) const { 
    // Replacement variable: offset
    return (int)_c0;
  }
  virtual int            constant_disp() const {
    // Replacement variable: offset
    return (int)_c0;
  }

#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual void           dump_spec(outputStream *st) const {
    st->print("#" INT64_FORMAT, (int64_t)_c0);
    st->print("/" UINT64_FORMAT_X_0, (uint64_t)_c0);
  }
  virtual const char    *Name() const { return "indOffset20indexNarrow";}
#endif
};

class indOffset12indexOper : public MachOper { 
private:
  virtual uint           num_edges() const { return 2; }
  virtual const RegMask *in_RegMask(int index) const;
  jlong            _c0;
public:
  indOffset12indexOper(jlong c0)  : _c0(c0) {}
  virtual MachOper      *clone() const;
  virtual void set_con( jint c0 ) { _c0 = c0; }
  virtual uint           opcode() const { return INDOFFSET12INDEX; }

  virtual int            base(PhaseRegAlloc *ra_, const Node *node, int idx) const { 
    // Replacement variable: base
    return (int)ra_->get_encode(node->in(idx));
  }
  virtual int            base_position() const { return 0; }
  virtual int            index(PhaseRegAlloc *ra_, const Node *node, int idx) const { 
    // Replacement variable: index
    return (int)ra_->get_encode(node->in(idx+1));
  }
  virtual int            index_position() const { return 1; }
  virtual int            scale() const {
    return 0x0;
  }
  virtual int            disp(PhaseRegAlloc *ra_, const Node *node, int idx) const { 
    // Replacement variable: offset
    return (int)_c0;
  }
  virtual int            constant_disp() const {
    // Replacement variable: offset
    return (int)_c0;
  }

#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual void           dump_spec(outputStream *st) const {
    st->print("#" INT64_FORMAT, (int64_t)_c0);
    st->print("/" UINT64_FORMAT_X_0, (uint64_t)_c0);
  }
  virtual const char    *Name() const { return "indOffset12index";}
#endif
};

class indOffset12indexNarrowOper : public MachOper { 
private:
  virtual uint           num_edges() const { return 2; }
  virtual const RegMask *in_RegMask(int index) const;
  jlong            _c0;
public:
  indOffset12indexNarrowOper(jlong c0)  : _c0(c0) {}
  virtual MachOper      *clone() const;
  virtual void set_con( jint c0 ) { _c0 = c0; }
  virtual uint           opcode() const { return INDOFFSET12INDEXNARROW; }

  virtual int            base(PhaseRegAlloc *ra_, const Node *node, int idx) const { 
    // Replacement variable: base
    return (int)ra_->get_encode(node->in(idx));
  }
  virtual int            base_position() const { return 0; }
  virtual int            index(PhaseRegAlloc *ra_, const Node *node, int idx) const { 
    // Replacement variable: index
    return (int)ra_->get_encode(node->in(idx+1));
  }
  virtual int            index_position() const { return 1; }
  virtual int            scale() const {
    return 0x0;
  }
  virtual int            disp(PhaseRegAlloc *ra_, const Node *node, int idx) const { 
    // Replacement variable: offset
    return (int)_c0;
  }
  virtual int            constant_disp() const {
    // Replacement variable: offset
    return (int)_c0;
  }

#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual void           dump_spec(outputStream *st) const {
    st->print("#" INT64_FORMAT, (int64_t)_c0);
    st->print("/" UINT64_FORMAT_X_0, (uint64_t)_c0);
  }
  virtual const char    *Name() const { return "indOffset12indexNarrow";}
#endif
};

class stackSlotIOper : public MachOper { 
private:
  virtual const RegMask *in_RegMask(int index) const;
public:
  stackSlotIOper() {}
  virtual MachOper      *clone() const;
  virtual uint           opcode() const { return STACKSLOTI; }
  virtual const Type    *type() const { return TypeInt::INT; } // stackSlotX

  virtual int            base(PhaseRegAlloc *ra_, const Node *node, int idx) const { 
    return 0xf;
  }
  virtual int            index(PhaseRegAlloc *ra_, const Node *node, int idx) const { 
    return 0xffffFFFF;
  }
  virtual int            scale() const {
    return 0x0;
  }
  virtual int            disp(PhaseRegAlloc *ra_, const Node *node, int idx) const { 
    // Replacement variable: reg
    if( idx != 0 ) {
      // Access stack offset (register number) for input operand
      return ra_->reg2offset(ra_->get_reg_first(node->in(idx)));/* sReg */
    }
    // Access stack offset (register number) from myself
    return ra_->reg2offset(ra_->get_reg_first(node));/* sReg */
  }
  virtual int       constant_disp() const { return Type::OffsetBot; }
#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual const char    *Name() const { return "stackSlotI";}
#endif
};

class stackSlotPOper : public MachOper { 
private:
  virtual const RegMask *in_RegMask(int index) const;
public:
  stackSlotPOper() {}
  virtual MachOper      *clone() const;
  virtual uint           opcode() const { return STACKSLOTP; }
  virtual const Type    *type() const { return TypePtr::BOTTOM; } // stackSlotX

  virtual int            base(PhaseRegAlloc *ra_, const Node *node, int idx) const { 
    return 0xf;
  }
  virtual int            index(PhaseRegAlloc *ra_, const Node *node, int idx) const { 
    return 0xffffFFFF;
  }
  virtual int            scale() const {
    return 0x0;
  }
  virtual int            disp(PhaseRegAlloc *ra_, const Node *node, int idx) const { 
    // Replacement variable: reg
    if( idx != 0 ) {
      // Access stack offset (register number) for input operand
      return ra_->reg2offset(ra_->get_reg_first(node->in(idx)));/* sReg */
    }
    // Access stack offset (register number) from myself
    return ra_->reg2offset(ra_->get_reg_first(node));/* sReg */
  }
  virtual int       constant_disp() const { return Type::OffsetBot; }
#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual const char    *Name() const { return "stackSlotP";}
#endif
};

class stackSlotFOper : public MachOper { 
private:
  virtual const RegMask *in_RegMask(int index) const;
public:
  stackSlotFOper() {}
  virtual MachOper      *clone() const;
  virtual uint           opcode() const { return STACKSLOTF; }
  virtual const Type    *type() const { return Type::FLOAT; } // stackSlotX

  virtual int            base(PhaseRegAlloc *ra_, const Node *node, int idx) const { 
    return 0xf;
  }
  virtual int            index(PhaseRegAlloc *ra_, const Node *node, int idx) const { 
    return 0xffffFFFF;
  }
  virtual int            scale() const {
    return 0x0;
  }
  virtual int            disp(PhaseRegAlloc *ra_, const Node *node, int idx) const { 
    // Replacement variable: reg
    if( idx != 0 ) {
      // Access stack offset (register number) for input operand
      return ra_->reg2offset(ra_->get_reg_first(node->in(idx)));/* sReg */
    }
    // Access stack offset (register number) from myself
    return ra_->reg2offset(ra_->get_reg_first(node));/* sReg */
  }
  virtual int       constant_disp() const { return Type::OffsetBot; }
#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual const char    *Name() const { return "stackSlotF";}
#endif
};

class stackSlotDOper : public MachOper { 
private:
  virtual const RegMask *in_RegMask(int index) const;
public:
  stackSlotDOper() {}
  virtual MachOper      *clone() const;
  virtual uint           opcode() const { return STACKSLOTD; }
  virtual const Type    *type() const { return Type::DOUBLE; } // stackSlotX

  virtual int            base(PhaseRegAlloc *ra_, const Node *node, int idx) const { 
    return 0xf;
  }
  virtual int            index(PhaseRegAlloc *ra_, const Node *node, int idx) const { 
    return 0xffffFFFF;
  }
  virtual int            scale() const {
    return 0x0;
  }
  virtual int            disp(PhaseRegAlloc *ra_, const Node *node, int idx) const { 
    // Replacement variable: reg
    if( idx != 0 ) {
      // Access stack offset (register number) for input operand
      return ra_->reg2offset(ra_->get_reg_first(node->in(idx)));/* sReg */
    }
    // Access stack offset (register number) from myself
    return ra_->reg2offset(ra_->get_reg_first(node));/* sReg */
  }
  virtual int       constant_disp() const { return Type::OffsetBot; }
#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual const char    *Name() const { return "stackSlotD";}
#endif
};

class stackSlotLOper : public MachOper { 
private:
  virtual const RegMask *in_RegMask(int index) const;
public:
  stackSlotLOper() {}
  virtual MachOper      *clone() const;
  virtual uint           opcode() const { return STACKSLOTL; }
  virtual const Type    *type() const { return TypeLong::LONG; } // stackSlotX

  virtual int            base(PhaseRegAlloc *ra_, const Node *node, int idx) const { 
    return 0xf;
  }
  virtual int            index(PhaseRegAlloc *ra_, const Node *node, int idx) const { 
    return 0xffffFFFF;
  }
  virtual int            scale() const {
    return 0x0;
  }
  virtual int            disp(PhaseRegAlloc *ra_, const Node *node, int idx) const { 
    // Replacement variable: reg
    if( idx != 0 ) {
      // Access stack offset (register number) for input operand
      return ra_->reg2offset(ra_->get_reg_first(node->in(idx)));/* sReg */
    }
    // Access stack offset (register number) from myself
    return ra_->reg2offset(ra_->get_reg_first(node));/* sReg */
  }
  virtual int       constant_disp() const { return Type::OffsetBot; }
#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual const char    *Name() const { return "stackSlotL";}
#endif
};

class cmpOpTOper : public MachOper { 
private:
  virtual uint           num_edges() const { return 0; }
private:
  BoolTest::mask _c0;
public:
  virtual int ccode() const { 
    switch (_c0) {
    case  BoolTest::eq : return equal();
    case  BoolTest::gt : return greater();
    case  BoolTest::lt : return less();
    case  BoolTest::ne : return not_equal();
    case  BoolTest::le : return less_equal();
    case  BoolTest::ge : return greater_equal();
    case  BoolTest::overflow : return overflow();
    case  BoolTest::no_overflow: return no_overflow();
    default : ShouldNotReachHere(); return 0;
    }
  };
  virtual void negate() { 
    _c0 = (BoolTest::mask)((int)_c0^0x4); 
  };
public:
  cmpOpTOper(BoolTest::mask c0)  : _c0(c0) {}
  virtual MachOper      *clone() const;
  virtual uint           opcode() const { return CMPOPT; }
  virtual const Type    *type() const { ShouldNotCallThis(); return Type::BOTTOM; }

  virtual int            equal() const {
    return 0x8;
  }
  virtual int            not_equal() const {
    return 0x6;
  }
  virtual int            less() const {
    return 0x4;
  }
  virtual int            greater_equal() const {
    return 0xa;
  }
  virtual int            less_equal() const {
    return 0xc;
  }
  virtual int            greater() const {
    return 0x2;
  }
  virtual int            overflow() const {
    return 0x1;
  }
  virtual int            no_overflow() const {
    return 0xe;
  }

#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual void           dump_spec(outputStream *st) const {
       if( _c0 == BoolTest::eq ) st->print_raw("eq");
  else if( _c0 == BoolTest::ne ) st->print_raw("ne");
  else if( _c0 == BoolTest::le ) st->print_raw("le");
  else if( _c0 == BoolTest::ge ) st->print_raw("ge");
  else if( _c0 == BoolTest::lt ) st->print_raw("lt");
  else if( _c0 == BoolTest::gt ) st->print_raw("gt");
  else if( _c0 == BoolTest::overflow ) st->print_raw("o");
  else if( _c0 == BoolTest::no_overflow ) st->print_raw("no");
  }
  virtual const char    *Name() const { return "cmpOpT";}
#endif
};

class cmpOpFOper : public MachOper { 
private:
  virtual uint           num_edges() const { return 0; }
private:
  BoolTest::mask _c0;
public:
  virtual int ccode() const { 
    switch (_c0) {
    case  BoolTest::eq : return equal();
    case  BoolTest::gt : return greater();
    case  BoolTest::lt : return less();
    case  BoolTest::ne : return not_equal();
    case  BoolTest::le : return less_equal();
    case  BoolTest::ge : return greater_equal();
    case  BoolTest::overflow : return overflow();
    case  BoolTest::no_overflow: return no_overflow();
    default : ShouldNotReachHere(); return 0;
    }
  };
  virtual void negate() { 
    _c0 = (BoolTest::mask)((int)_c0^0x4); 
  };
public:
  cmpOpFOper(BoolTest::mask c0)  : _c0(c0) {}
  virtual MachOper      *clone() const;
  virtual uint           opcode() const { return CMPOPF; }
  virtual const Type    *type() const { ShouldNotCallThis(); return Type::BOTTOM; }

  virtual int            equal() const {
    return 0x8;
  }
  virtual int            not_equal() const {
    return 0x7;
  }
  virtual int            less() const {
    return 0x5;
  }
  virtual int            greater_equal() const {
    return 0xa;
  }
  virtual int            less_equal() const {
    return 0xd;
  }
  virtual int            greater() const {
    return 0x2;
  }
  virtual int            overflow() const {
    return 0x0;
  }
  virtual int            no_overflow() const {
    return 0x0;
  }

#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual void           dump_spec(outputStream *st) const {
       if( _c0 == BoolTest::eq ) st->print_raw("eq");
  else if( _c0 == BoolTest::ne ) st->print_raw("ne");
  else if( _c0 == BoolTest::le ) st->print_raw("le");
  else if( _c0 == BoolTest::ge ) st->print_raw("ge");
  else if( _c0 == BoolTest::lt ) st->print_raw("lt");
  else if( _c0 == BoolTest::gt ) st->print_raw("gt");
  else if( _c0 == BoolTest::overflow ) st->print_raw("o");
  else if( _c0 == BoolTest::no_overflow ) st->print_raw("no");
  }
  virtual const char    *Name() const { return "cmpOpF";}
#endif
};

class cmpOpOper : public MachOper { 
private:
  virtual uint           num_edges() const { return 0; }
private:
  BoolTest::mask _c0;
public:
  virtual int ccode() const { 
    switch (_c0) {
    case  BoolTest::eq : return equal();
    case  BoolTest::gt : return greater();
    case  BoolTest::lt : return less();
    case  BoolTest::ne : return not_equal();
    case  BoolTest::le : return less_equal();
    case  BoolTest::ge : return greater_equal();
    case  BoolTest::overflow : return overflow();
    case  BoolTest::no_overflow: return no_overflow();
    default : ShouldNotReachHere(); return 0;
    }
  };
  virtual void negate() { 
    _c0 = (BoolTest::mask)((int)_c0^0x4); 
  };
public:
  cmpOpOper(BoolTest::mask c0)  : _c0(c0) {}
  virtual MachOper      *clone() const;
  virtual uint           opcode() const { return CMPOP; }
  virtual const Type    *type() const { ShouldNotCallThis(); return Type::BOTTOM; }

  virtual int            equal() const {
    return 0x8;
  }
  virtual int            not_equal() const {
    return 0x7;
  }
  virtual int            less() const {
    return 0x5;
  }
  virtual int            greater_equal() const {
    return 0xa;
  }
  virtual int            less_equal() const {
    return 0xd;
  }
  virtual int            greater() const {
    return 0x2;
  }
  virtual int            overflow() const {
    return 0x1;
  }
  virtual int            no_overflow() const {
    return 0xe;
  }

#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual void           dump_spec(outputStream *st) const {
       if( _c0 == BoolTest::eq ) st->print_raw("eq");
  else if( _c0 == BoolTest::ne ) st->print_raw("ne");
  else if( _c0 == BoolTest::le ) st->print_raw("le");
  else if( _c0 == BoolTest::ge ) st->print_raw("ge");
  else if( _c0 == BoolTest::lt ) st->print_raw("lt");
  else if( _c0 == BoolTest::gt ) st->print_raw("gt");
  else if( _c0 == BoolTest::overflow ) st->print_raw("o");
  else if( _c0 == BoolTest::no_overflow ) st->print_raw("no");
  }
  virtual const char    *Name() const { return "cmpOp";}
#endif
};

//----------------------------Declare classes for Pipelines-----------------

// Pipeline_Use_Cycle_Mask Class
class Pipeline_Use_Cycle_Mask {
protected:
  uint32_t _mask;

public:
  Pipeline_Use_Cycle_Mask() : _mask(0) {}

  Pipeline_Use_Cycle_Mask(uint32_t mask) : _mask(mask) {}

  bool overlaps(const Pipeline_Use_Cycle_Mask &in2) const {
    return ((_mask & in2._mask) != 0);
  }

  Pipeline_Use_Cycle_Mask& operator<<=(int n) {
    _mask <<= (n < 32) ? n : 31;
    return *this;
  }

  void Or(const Pipeline_Use_Cycle_Mask &in2) {
    _mask |= in2._mask;
  }

  friend Pipeline_Use_Cycle_Mask operator&(const Pipeline_Use_Cycle_Mask &, const Pipeline_Use_Cycle_Mask &);
  friend Pipeline_Use_Cycle_Mask operator|(const Pipeline_Use_Cycle_Mask &, const Pipeline_Use_Cycle_Mask &);

  friend class Pipeline_Use;

  friend class Pipeline_Use_Element;

};

// Pipeline_Use_Element Class
class Pipeline_Use_Element {
protected:
  // Mask of used functional units
  uint _used;

  // Lower and upper bound of functional unit number range
  uint _lb, _ub;

  // Indicates multiple functionals units available
  bool _multiple;

  // Mask of specific used cycles
  Pipeline_Use_Cycle_Mask _mask;

public:
  Pipeline_Use_Element() {}

  Pipeline_Use_Element(uint used, uint lb, uint ub, bool multiple, Pipeline_Use_Cycle_Mask mask)
  : _used(used), _lb(lb), _ub(ub), _multiple(multiple), _mask(mask) {}

  uint used() const { return _used; }

  uint lowerBound() const { return _lb; }

  uint upperBound() const { return _ub; }

  bool multiple() const { return _multiple; }

  Pipeline_Use_Cycle_Mask mask() const { return _mask; }

  bool overlaps(const Pipeline_Use_Element &in2) const {
    return ((_used & in2._used) != 0 && _mask.overlaps(in2._mask));
  }

  void step(uint cycles) {
    _used = 0;
    _mask <<= cycles;
  }

  friend class Pipeline_Use;
};

// Pipeline_Use Class
class Pipeline_Use {
protected:
  // These resources can be used
  uint _resources_used;

  // These resources are used; excludes multiple choice functional units
  uint _resources_used_exclusively;

  // Number of elements
  uint _count;

  // This is the array of Pipeline_Use_Elements
  Pipeline_Use_Element * _elements;

public:
  Pipeline_Use(uint resources_used, uint resources_used_exclusively, uint count, Pipeline_Use_Element *elements)
  : _resources_used(resources_used)
  , _resources_used_exclusively(resources_used_exclusively)
  , _count(count)
  , _elements(elements)
  {}

  uint resourcesUsed() const { return _resources_used; }

  uint resourcesUsedExclusively() const { return _resources_used_exclusively; }

  uint count() const { return _count; }

  Pipeline_Use_Element * element(uint i) const { return &_elements[i]; }

  uint full_latency(uint delay, const Pipeline_Use &pred) const;

  void add_usage(const Pipeline_Use &pred);

  void reset() {
    _resources_used = _resources_used_exclusively = 0;
  };

  void step(uint cycles) {
    reset();
    for (uint i = 0; i < 8; i++)
      (&_elements[i])->step(cycles);
  };

  static const Pipeline_Use         elaborated_use;
  static const Pipeline_Use_Element elaborated_elements[8];

  friend class Pipeline;
};

// Pipeline Class
class Pipeline {
public:
  static bool enabled() { return true; }

  enum {
    _variable_size_instructions = 1,
    _fixed_size_instructions = 0,
    _max_instrs_per_bundle = 1,
    _max_bundles_per_cycle = 1,
    _max_instrs_per_cycle = 1
  };

  static bool instr_has_unit_size() { return true; }

// Bundling is not supported

  // Size of an instruction
  static uint instr_unit_size() { return 2; };

  // Bundles do not exist - unsupported
  static uint bundle_unit_size() { assert( false, "Bundles are not supported" ); return 0; };

  static bool requires_bundling() { return false; }

private:
  Pipeline();  // Not a legal constructor

  const unsigned char                   _read_stage_count;
  const unsigned char                   _write_stage;
  const unsigned char                   _fixed_latency;
  const unsigned char                   _instruction_count;
  const bool                            _has_fixed_latency;
  const bool                            _has_multiple_bundles;
  const bool                            _force_serialization;
  const bool                            _may_have_no_code;
  const enum machPipelineStages * const _read_stages;
  const enum machPipelineStages * const _resource_stage;
  const uint                    * const _resource_cycles;
  const Pipeline_Use                    _resource_use;

public:
  Pipeline(uint                            write_stage,
           uint                            count,
           bool                            has_fixed_latency,
           uint                            fixed_latency,
           uint                            instruction_count,
           bool                            has_multiple_bundles,
           bool                            force_serialization,
           bool                            may_have_no_code,
           enum machPipelineStages * const dst,
           enum machPipelineStages * const stage,
           uint                    * const cycles,
           Pipeline_Use                    resource_use)
  : _read_stage_count(count)
  , _write_stage(write_stage)
  , _fixed_latency(fixed_latency)
  , _instruction_count(instruction_count)
  , _has_fixed_latency(has_fixed_latency)
  , _has_multiple_bundles(has_multiple_bundles)
  , _force_serialization(force_serialization)
  , _may_have_no_code(may_have_no_code)
  , _read_stages(dst)
  , _resource_stage(stage)
  , _resource_cycles(cycles)
  , _resource_use(resource_use)
  {};

  uint writeStage() const {
    return (_write_stage);
  }

  enum machPipelineStages readStage(int ndx) const {
    return (ndx < _read_stage_count ? _read_stages[ndx] : stage_undefined);  }

  uint resourcesUsed() const {
    return _resource_use.resourcesUsed();
  }

  uint resourcesUsedExclusively() const {
    return _resource_use.resourcesUsedExclusively();
  }

  bool hasFixedLatency() const {
    return (_has_fixed_latency);
  }

  uint fixedLatency() const {
    return (_fixed_latency);
  }

  uint functional_unit_latency(uint start, const Pipeline *pred) const;

  uint operand_latency(uint opnd, const Pipeline *pred) const;

  const Pipeline_Use& resourceUse() const {
    return (_resource_use); }

  const Pipeline_Use_Element * resourceUseElement(uint i) const {
    return (&_resource_use._elements[i]); }

  uint resourceUseCount() const {
    return (_resource_use._count); }

  uint instructionCount() const {
    return (_instruction_count); }

  bool hasMultipleBundles() const {
    return (_has_multiple_bundles); }

  bool forceSerialization() const {
    return (_force_serialization); }

  bool mayHaveNoCode() const {
    return (_may_have_no_code); }

//const Pipeline_Use_Cycle_Mask& resourceUseMask(int resource) const {
//  return (_resource_use_masks[resource]); }


#ifndef PRODUCT
  static const char * stageName(uint i);
#endif
};

// Bundle class
class Bundle {
protected:
  uint _starts_bundle  : 1,
       _instr_count    : 1,
       _resources_used : 8;
public:
  Bundle() : _starts_bundle(0), _instr_count(0), _resources_used(0) {}

  void set_instr_count(uint i) { _instr_count  = i; }
  void set_resources_used(uint i) { _resources_used   = i; }
  void set_starts_bundle() { _starts_bundle = true; }
  uint instr_count() const { return (_instr_count); }
  uint resources_used() const { return (_resources_used); }
  bool starts_bundle() const { return (_starts_bundle != 0); }
#ifndef PRODUCT
  void dump(outputStream *st = tty) const;
#endif
};


//----------------------------Declare classes derived from MachNode----------

class stkI_to_regINode : public MachNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return stkI_to_regI_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
public:
  stkI_to_regINode() {  _num_opnds = 2; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(stkI_to_regINode); }
  // Rematerialize stkI_to_regI
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "stkI_to_regI";}
#endif
};

class regI_to_stkINode : public MachNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return regI_to_stkI_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_RegI; }
public:
  regI_to_stkINode() {  _num_opnds = 2; _opnds = _opnd_array; init_flags(Flag_is_Copy); }
  virtual uint           size_of() const { return sizeof(regI_to_stkINode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "regI_to_stkI";}
#endif
};

class stkL_to_regLNode : public MachNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return stkL_to_regL_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
public:
  stkL_to_regLNode() {  _num_opnds = 2; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(stkL_to_regLNode); }
  // Rematerialize stkL_to_regL
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "stkL_to_regL";}
#endif
};

class regL_to_stkLNode : public MachNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return regL_to_stkL_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_RegL; }
public:
  regL_to_stkLNode() {  _num_opnds = 2; _opnds = _opnd_array; init_flags(Flag_is_Copy); }
  virtual uint           size_of() const { return sizeof(regL_to_stkLNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "regL_to_stkL";}
#endif
};

class stkP_to_regPNode : public MachNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return stkP_to_regP_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
public:
  stkP_to_regPNode() {  _num_opnds = 2; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(stkP_to_regPNode); }
  // Rematerialize stkP_to_regP
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "stkP_to_regP";}
#endif
};

class regP_to_stkPNode : public MachNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return regP_to_stkP_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_RegP; }
public:
  regP_to_stkPNode() {  _num_opnds = 2; _opnds = _opnd_array; init_flags(Flag_is_Copy); }
  virtual uint           size_of() const { return sizeof(regP_to_stkPNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  const Type            *bottom_type() const { return in(1)->bottom_type(); } // Copy?
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "regP_to_stkP";}
#endif
};

class stkF_to_regFNode : public MachNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return stkF_to_regF_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
public:
  stkF_to_regFNode() {  _num_opnds = 2; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(stkF_to_regFNode); }
  // Rematerialize stkF_to_regF
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "stkF_to_regF";}
#endif
};

class regF_to_stkFNode : public MachNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return regF_to_stkF_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_RegF; }
public:
  regF_to_stkFNode() {  _num_opnds = 2; _opnds = _opnd_array; init_flags(Flag_is_Copy); }
  virtual uint           size_of() const { return sizeof(regF_to_stkFNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "regF_to_stkF";}
#endif
};

class stkD_to_regDNode : public MachNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return stkD_to_regD_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
public:
  stkD_to_regDNode() {  _num_opnds = 2; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(stkD_to_regDNode); }
  // Rematerialize stkD_to_regD
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "stkD_to_regD";}
#endif
};

class regD_to_stkDNode : public MachNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return regD_to_stkD_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_RegD; }
public:
  regD_to_stkDNode() {  _num_opnds = 2; _opnds = _opnd_array; init_flags(Flag_is_Copy); }
  virtual uint           size_of() const { return sizeof(regD_to_stkDNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "regD_to_stkD";}
#endif
};

class loadBNode : public MachNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return loadB_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_LoadB; }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  loadBNode() {  _num_opnds = 2; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(loadBNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "loadB";}
#endif
};

class loadB2LNode : public MachNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return loadB2L_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_ConvI2L; }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  loadB2LNode() {  _num_opnds = 2; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(loadB2LNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "loadB2L";}
#endif
};

class loadUBNode : public MachNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return loadUB_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_LoadUB; }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  loadUBNode() {  _num_opnds = 2; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(loadUBNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "loadUB";}
#endif
};

class loadUB2LNode : public MachNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return loadUB2L_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_ConvI2L; }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  loadUB2LNode() {  _num_opnds = 2; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(loadUB2LNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "loadUB2L";}
#endif
};

class loadSNode : public MachNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return loadS_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_LoadS; }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  loadSNode() {  _num_opnds = 2; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(loadSNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "loadS";}
#endif
};

class loadS2LNode : public MachNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return loadS2L_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_ConvI2L; }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  loadS2LNode() {  _num_opnds = 2; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(loadS2LNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "loadS2L";}
#endif
};

class loadUSNode : public MachNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return loadUS_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_LoadUS; }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  loadUSNode() {  _num_opnds = 2; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(loadUSNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "loadUS";}
#endif
};

class loadUS2LNode : public MachNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return loadUS2L_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_ConvI2L; }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  loadUS2LNode() {  _num_opnds = 2; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(loadUS2LNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "loadUS2L";}
#endif
};

class loadINode : public MachNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return loadI_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_LoadI; }
  virtual int            peephole(Block* block, int block_index, PhaseCFG* cfg_, PhaseRegAlloc* ra_);
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  loadINode() {  _num_opnds = 2; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(loadINode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "loadI";}
#endif
};

class loadI2LNode : public MachNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return loadI2L_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_ConvI2L; }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  loadI2LNode() {  _num_opnds = 2; _opnds = _opnd_array; init_flags(Flag_is_cisc_alternate | Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(loadI2LNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "loadI2L";}
#endif
};

class loadUI2LNode : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return loadUI2L_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_AndL; }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  loadUI2LNode() {  _num_opnds = 3; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(loadUI2LNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "loadUI2L";}
#endif
};

class loadRangeNode : public MachNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return loadRange_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_LoadRange; }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  loadRangeNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(loadRangeNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "loadRange";}
#endif
};

class loadLNode : public MachNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return loadL_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_LoadL; }
  virtual int            peephole(Block* block, int block_index, PhaseCFG* cfg_, PhaseRegAlloc* ra_);
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  loadLNode() {  _num_opnds = 2; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(loadLNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "loadL";}
#endif
};

class loadL_unalignedNode : public MachNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return loadL_unaligned_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_LoadL_unaligned; }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  loadL_unalignedNode() {  _num_opnds = 2; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(loadL_unalignedNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "loadL_unaligned";}
#endif
};

class loadPNode : public MachTypeNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return loadP_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_LoadP; }
  virtual int            peephole(Block* block, int block_index, PhaseCFG* cfg_, PhaseRegAlloc* ra_);
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  loadPNode() {  _num_opnds = 2; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(loadPNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "loadP";}
#endif
};

class castP2X_loadPNode : public MachNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return castP2X_loadP_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_CastP2X; }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  castP2X_loadPNode() {  _num_opnds = 2; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(castP2X_loadPNode); }
  // Rematerialize castP2X_loadP
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "castP2X_loadP";}
#endif
};

class loadKlassNode : public MachTypeNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return loadKlass_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_LoadKlass; }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  loadKlassNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(loadKlassNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "loadKlass";}
#endif
};

class loadTOCNode : public MachNode { 
private:
  MachOper *_opnd_array[1];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return loadTOC_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual int            ins_should_rematerialize() const { return true; }
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
public:
  loadTOCNode() {  _num_opnds = 1; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(loadTOCNode); }
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "loadTOC";}
#endif
};

class loadFNode : public MachNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return loadF_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_LoadF; }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  loadFNode() {  _num_opnds = 2; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(loadFNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "loadF";}
#endif
};

class loadDNode : public MachNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return loadD_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_LoadD; }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  loadDNode() {  _num_opnds = 2; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(loadDNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "loadD";}
#endif
};

class loadD_unalignedNode : public MachNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return loadD_unaligned_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_LoadD_unaligned; }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  loadD_unalignedNode() {  _num_opnds = 2; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(loadD_unalignedNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "loadD_unaligned";}
#endif
};

class loadConINode : public MachNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return loadConI_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_ConI; }
public:
  loadConINode() {  _num_opnds = 2; _opnds = _opnd_array; init_flags(Flag_is_Con); }
  virtual uint           size_of() const { return sizeof(loadConINode); }
  friend MachNode *State::MachNodeGenerator(int opcode);
  // Rematerialize loadConI
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const class Type *bottom_type() const {
    return  TypeInt::make(opnd_array(1)->constant());
  };
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "loadConI";}
#endif
};

class loadConI16Node : public MachNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return loadConI16_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_ConI; }
public:
  loadConI16Node() {  _num_opnds = 2; _opnds = _opnd_array; init_flags(Flag_is_Con); }
  virtual uint           size_of() const { return sizeof(loadConI16Node); }
  friend MachNode *State::MachNodeGenerator(int opcode);
  // Rematerialize loadConI16
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const class Type *bottom_type() const {
    return  TypeInt::make(opnd_array(1)->constant());
  };
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "loadConI16";}
#endif
};

class loadConI_0Node : public MachNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return loadConI_0_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_ConI; }
public:
  loadConI_0Node() {  _num_opnds = 2; _opnds = _opnd_array; init_flags(Flag_is_Con); }
  virtual uint           size_of() const { return sizeof(loadConI_0Node); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  // Rematerialize loadConI_0
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const class Type *bottom_type() const {
    return  TypeInt::make(opnd_array(1)->constant());
  };
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "loadConI_0";}
#endif
};

class loadConUI16Node : public MachNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return loadConUI16_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_ConI; }
public:
  loadConUI16Node() {  _num_opnds = 2; _opnds = _opnd_array; init_flags(Flag_is_Con); }
  virtual uint           size_of() const { return sizeof(loadConUI16Node); }
  friend MachNode *State::MachNodeGenerator(int opcode);
  // Rematerialize loadConUI16
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const class Type *bottom_type() const {
    return  TypeInt::make(opnd_array(1)->constant());
  };
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "loadConUI16";}
#endif
};

class loadConL_pcrelTOCNode : public MachNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return loadConL_pcrelTOC_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_ConL; }
public:
  loadConL_pcrelTOCNode() {  _num_opnds = 2; _opnds = _opnd_array; init_flags(Flag_is_Con); }
  virtual uint           size_of() const { return sizeof(loadConL_pcrelTOCNode); }
  friend MachNode *State::MachNodeGenerator(int opcode);
  // Rematerialize loadConL_pcrelTOC
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const class Type *bottom_type() const {
    return  TypeLong::make(opnd_array(1)->constantL());
  };
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "loadConL_pcrelTOC";}
#endif
};

class loadConL32Node : public MachNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return loadConL32_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_ConL; }
public:
  loadConL32Node() {  _num_opnds = 2; _opnds = _opnd_array; init_flags(Flag_is_Con); }
  virtual uint           size_of() const { return sizeof(loadConL32Node); }
  friend MachNode *State::MachNodeGenerator(int opcode);
  // Rematerialize loadConL32
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const class Type *bottom_type() const {
    return  TypeLong::make(opnd_array(1)->constantL());
  };
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "loadConL32";}
#endif
};

class loadConL16Node : public MachNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return loadConL16_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_ConL; }
public:
  loadConL16Node() {  _num_opnds = 2; _opnds = _opnd_array; init_flags(Flag_is_Con); }
  virtual uint           size_of() const { return sizeof(loadConL16Node); }
  friend MachNode *State::MachNodeGenerator(int opcode);
  // Rematerialize loadConL16
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const class Type *bottom_type() const {
    return  TypeLong::make(opnd_array(1)->constantL());
  };
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "loadConL16";}
#endif
};

class loadConL_0Node : public MachNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return loadConL_0_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_ConL; }
public:
  loadConL_0Node() {  _num_opnds = 2; _opnds = _opnd_array; init_flags(Flag_is_Con); }
  virtual uint           size_of() const { return sizeof(loadConL_0Node); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  // Rematerialize loadConL_0
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const class Type *bottom_type() const {
    return  TypeLong::make(opnd_array(1)->constantL());
  };
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "loadConL_0";}
#endif
};

class loadConP_pcrelTOCNode : public MachNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return loadConP_pcrelTOC_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_ConP; }
  virtual int            reloc() const;
public:
  loadConP_pcrelTOCNode() {  _num_opnds = 2; _opnds = _opnd_array; init_flags(Flag_is_Con); }
  virtual uint           size_of() const { return sizeof(loadConP_pcrelTOCNode); }
  friend MachNode *State::MachNodeGenerator(int opcode);
  // Rematerialize loadConP_pcrelTOC
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const class Type *bottom_type() const {
    return  opnd_array(1)->type();
  };
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "loadConP_pcrelTOC";}
#endif
};

class loadConP0Node : public MachNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return loadConP0_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_ConP; }
  virtual int            reloc() const;
public:
  loadConP0Node() {  _num_opnds = 2; _opnds = _opnd_array; init_flags(Flag_is_Con); }
  virtual uint           size_of() const { return sizeof(loadConP0Node); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  // Rematerialize loadConP0
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const class Type *bottom_type() const {
    return  opnd_array(1)->type();
  };
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "loadConP0";}
#endif
};

class loadConF_dynTOCNode : public MachConstantNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return loadConF_dynTOC_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual int            ins_cannot_rematerialize() const { return true; }
  virtual void           eval_constant(Compile* C);
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_ConF; }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 1; }
public:
  loadConF_dynTOCNode() {  _num_opnds = 2; _opnds = _opnd_array; init_flags(Flag_is_Con); }
  virtual uint           size_of() const { return sizeof(loadConF_dynTOCNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  // Rematerialize loadConF_dynTOC
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const class Type *bottom_type() const {
    return  TypeF::make(opnd_array(1)->constantF());
  };
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "loadConF_dynTOC";}
#endif
};

class loadConD_dynTOCNode : public MachConstantNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return loadConD_dynTOC_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual int            ins_cannot_rematerialize() const { return true; }
  virtual void           eval_constant(Compile* C);
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_ConD; }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 1; }
public:
  loadConD_dynTOCNode() {  _num_opnds = 2; _opnds = _opnd_array; init_flags(Flag_is_Con); }
  virtual uint           size_of() const { return sizeof(loadConD_dynTOCNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  // Rematerialize loadConD_dynTOC
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const class Type *bottom_type() const {
    return  TypeD::make(opnd_array(1)->constantD());
  };
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "loadConD_dynTOC";}
#endif
};

class loadConF0Node : public MachNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return loadConF0_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_ConF; }
  virtual int            reloc() const;
public:
  loadConF0Node() {  _num_opnds = 2; _opnds = _opnd_array; init_flags(Flag_is_Con); }
  virtual uint           size_of() const { return sizeof(loadConF0Node); }
  friend MachNode *State::MachNodeGenerator(int opcode);
  // Rematerialize loadConF0
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const class Type *bottom_type() const {
    return  TypeF::make(opnd_array(1)->constantF());
  };
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "loadConF0";}
#endif
};

class loadConD0Node : public MachNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return loadConD0_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_ConD; }
  virtual int            reloc() const;
public:
  loadConD0Node() {  _num_opnds = 2; _opnds = _opnd_array; init_flags(Flag_is_Con); }
  virtual uint           size_of() const { return sizeof(loadConD0Node); }
  friend MachNode *State::MachNodeGenerator(int opcode);
  // Rematerialize loadConD0
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const class Type *bottom_type() const {
    return  TypeD::make(opnd_array(1)->constantD());
  };
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "loadConD0";}
#endif
};

class storeBNode : public MachTypeNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return storeB_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_StoreB; }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  storeBNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(storeBNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "storeB";}
#endif
};

class storeCNode : public MachTypeNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return storeC_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_StoreC; }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  storeCNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(storeCNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "storeC";}
#endif
};

class storeINode : public MachTypeNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return storeI_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_StoreI; }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  storeINode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(storeINode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "storeI";}
#endif
};

class storeLNode : public MachTypeNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return storeL_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_StoreL; }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  storeLNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(storeLNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "storeL";}
#endif
};

class storePNode : public MachTypeNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return storeP_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_StoreP; }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  storePNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(storePNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "storeP";}
#endif
};

class storeFNode : public MachTypeNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return storeF_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_StoreF; }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  storeFNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(storeFNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "storeF";}
#endif
};

class storeDNode : public MachTypeNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return storeD_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_StoreD; }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  storeDNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(storeDNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "storeD";}
#endif
};

class prefetchAllocNode : public MachNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return prefetchAlloc_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_PrefetchAllocation; }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  prefetchAllocNode() {  _num_opnds = 2; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(prefetchAllocNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "prefetchAlloc";}
#endif
};

class memInitBNode : public MachTypeNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return memInitB_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_StoreB; }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  memInitBNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(memInitBNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "memInitB";}
#endif
};

class memInitCNode : public MachTypeNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return memInitC_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_StoreC; }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  memInitCNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(memInitCNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "memInitC";}
#endif
};

class memInitINode : public MachTypeNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return memInitI_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_StoreI; }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  memInitINode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(memInitINode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "memInitI";}
#endif
};

class memInitLNode : public MachTypeNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return memInitL_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_StoreL; }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  memInitLNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(memInitLNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "memInitL";}
#endif
};

class memInitPNode : public MachTypeNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return memInitP_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_StoreP; }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  memInitPNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(memInitPNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "memInitP";}
#endif
};

class negL_reg_regNode : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return negL_reg_reg_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_SubL; }
public:
  negL_reg_regNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(negL_reg_regNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "negL_reg_reg";}
#endif
};

class loadNNode : public MachTypeNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return loadN_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_LoadN; }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  loadNNode() {  _num_opnds = 2; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(loadNNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "loadN";}
#endif
};

class loadNKlassNode : public MachTypeNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return loadNKlass_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_LoadNKlass; }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  loadNKlassNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(loadNKlassNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "loadNKlass";}
#endif
};

class loadNKlassCompactHeadersNode : public MachTypeNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return loadNKlassCompactHeaders_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_LoadNKlass; }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  loadNKlassCompactHeadersNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(loadNKlassCompactHeadersNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "loadNKlassCompactHeaders";}
#endif
};

class loadConNNode : public MachNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return loadConN_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_ConN; }
public:
  loadConNNode() {  _num_opnds = 2; _opnds = _opnd_array; init_flags(Flag_is_Con); }
  virtual uint           size_of() const { return sizeof(loadConNNode); }
  friend MachNode *State::MachNodeGenerator(int opcode);
  // Rematerialize loadConN
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const class Type *bottom_type() const {
    return  opnd_array(1)->type();
  };
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "loadConN";}
#endif
};

class loadConN0Node : public MachNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return loadConN0_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_ConN; }
public:
  loadConN0Node() {  _num_opnds = 2; _opnds = _opnd_array; init_flags(Flag_is_Con); }
  virtual uint           size_of() const { return sizeof(loadConN0Node); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  // Rematerialize loadConN0
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const class Type *bottom_type() const {
    return  opnd_array(1)->type();
  };
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "loadConN0";}
#endif
};

class loadConNKlassNode : public MachNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return loadConNKlass_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_ConNKlass; }
public:
  loadConNKlassNode() {  _num_opnds = 2; _opnds = _opnd_array; init_flags(Flag_is_Con); }
  virtual uint           size_of() const { return sizeof(loadConNKlassNode); }
  friend MachNode *State::MachNodeGenerator(int opcode);
  // Rematerialize loadConNKlass
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const class Type *bottom_type() const {
    return  opnd_array(1)->type();
  };
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "loadConNKlass";}
#endif
};

class decodeLoadNNode : public MachTypeNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return decodeLoadN_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_DecodeN; }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  decodeLoadNNode() {  _num_opnds = 2; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(decodeLoadNNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "decodeLoadN";}
#endif
};

class decodeLoadNKlassNode : public MachTypeNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return decodeLoadNKlass_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_DecodeNKlass; }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  decodeLoadNKlassNode() {  _num_opnds = 2; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(decodeLoadNKlassNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "decodeLoadNKlass";}
#endif
};

class decodeLoadConNKlassNode : public MachTypeNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return decodeLoadConNKlass_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_DecodeNKlass; }
  virtual uint           oper_input_base() const { return 1; }
public:
  decodeLoadConNKlassNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(decodeLoadConNKlassNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "decodeLoadConNKlass";}
#endif
};

class decodeNNode : public MachTypeNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return decodeN_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_DecodeN; }
  virtual uint           oper_input_base() const { return 1; }
public:
  decodeNNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(decodeNNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "decodeN";}
#endif
};

class decodeKlassNode : public MachTypeNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return decodeKlass_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_DecodeNKlass; }
  virtual uint           oper_input_base() const { return 1; }
public:
  decodeKlassNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(decodeKlassNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "decodeKlass";}
#endif
};

class decodeN_NNNode : public MachTypeNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return decodeN_NN_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_DecodeN; }
  virtual uint           oper_input_base() const { return 1; }
public:
  decodeN_NNNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(decodeN_NNNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "decodeN_NN";}
#endif
};

class loadBaseNode : public MachNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return loadBase_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
public:
  loadBaseNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(loadBaseNode); }
  friend MachNode *State::MachNodeGenerator(int opcode);
  // Rematerialize loadBase
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "loadBase";}
#endif
};

class decodeN_baseNode : public MachTypeNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return decodeN_base_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_DecodeN; }
  virtual uint           oper_input_base() const { return 1; }
public:
  decodeN_baseNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(decodeN_baseNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "decodeN_base";}
#endif
};

class decodeN_NN_baseNode : public MachTypeNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return decodeN_NN_base_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_DecodeN; }
  virtual uint           oper_input_base() const { return 1; }
public:
  decodeN_NN_baseNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(decodeN_NN_baseNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "decodeN_NN_base";}
#endif
};

class decodeN_ExNode : public MachTypeNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return decodeN_Ex_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual int            ideal_Opcode() const { return Op_DecodeN; }
  virtual uint           oper_input_base() const { return 1; }
public:
  decodeN_ExNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(decodeN_ExNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "decodeN_Ex";}
#endif
};

class decodeN_NN_ExNode : public MachTypeNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return decodeN_NN_Ex_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual int            ideal_Opcode() const { return Op_DecodeN; }
  virtual uint           oper_input_base() const { return 1; }
public:
  decodeN_NN_ExNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(decodeN_NN_ExNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "decodeN_NN_Ex";}
#endif
};

class encodePNode : public MachTypeNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return encodeP_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_EncodeP; }
  virtual uint           oper_input_base() const { return 1; }
public:
  encodePNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(encodePNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "encodeP";}
#endif
};

class encodeKlassNode : public MachTypeNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return encodeKlass_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_EncodePKlass; }
  virtual uint           oper_input_base() const { return 1; }
public:
  encodeKlassNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(encodeKlassNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "encodeKlass";}
#endif
};

class encodeP_NNNode : public MachTypeNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return encodeP_NN_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_EncodeP; }
  virtual uint           oper_input_base() const { return 1; }
public:
  encodeP_NNNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(encodeP_NNNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "encodeP_NN";}
#endif
};

class encodeP_baseNode : public MachTypeNode { 
private:
  MachOper *_opnd_array[5];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return encodeP_base_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_EncodeP; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges() + opnd_array(2)->num_edges(); }
  virtual uint           oper_input_base() const { return 1; }
public:
  encodeP_baseNode() {  _num_opnds = 5; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(encodeP_baseNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "encodeP_base";}
#endif
};

class encodeP_NN_baseNode : public MachTypeNode { 
private:
  MachOper *_opnd_array[4];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return encodeP_NN_base_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_EncodeP; }
  virtual uint           oper_input_base() const { return 1; }
public:
  encodeP_NN_baseNode() {  _num_opnds = 4; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(encodeP_NN_baseNode); }
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "encodeP_NN_base";}
#endif
};

class encodeP_ExNode : public MachTypeNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return encodeP_Ex_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual int            ideal_Opcode() const { return Op_EncodeP; }
  virtual uint           oper_input_base() const { return 1; }
public:
  encodeP_ExNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(encodeP_ExNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "encodeP_Ex";}
#endif
};

class encodeP_NN_ExNode : public MachTypeNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return encodeP_NN_Ex_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual int            ideal_Opcode() const { return Op_EncodeP; }
  virtual uint           oper_input_base() const { return 1; }
public:
  encodeP_NN_ExNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(encodeP_NN_ExNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "encodeP_NN_Ex";}
#endif
};

class storeNNode : public MachTypeNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return storeN_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_StoreN; }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  storeNNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(storeNNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "storeN";}
#endif
};

class storeNKlassNode : public MachTypeNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return storeNKlass_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_StoreNKlass; }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  storeNKlassNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(storeNKlassNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "storeNKlass";}
#endif
};

class compN_iRegNNode : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return compN_iRegN_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_CmpN; }
  virtual int            reloc() const;
public:
  compN_iRegNNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(compN_iRegNNode); }
  // Rematerialize compN_iRegN
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "compN_iRegN";}
#endif
};

class compN_iRegN_immNNode : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return compN_iRegN_immN_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_CmpN; }
  virtual int            reloc() const;
public:
  compN_iRegN_immNNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(compN_iRegN_immNNode); }
  // Rematerialize compN_iRegN_immN
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "compN_iRegN_immN";}
#endif
};

class compNKlass_iRegN_immNNode : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return compNKlass_iRegN_immN_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_CmpN; }
public:
  compNKlass_iRegN_immNNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(compNKlass_iRegN_immNNode); }
  // Rematerialize compNKlass_iRegN_immN
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "compNKlass_iRegN_immN";}
#endif
};

class compN_iRegN_immN0Node : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return compN_iRegN_immN0_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_CmpN; }
  virtual int            reloc() const;
public:
  compN_iRegN_immN0Node() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(compN_iRegN_immN0Node); }
  // Rematerialize compN_iRegN_immN0
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "compN_iRegN_immN0";}
#endif
};

class membar_acquireNode : public MachMemBarNode { 
private:
  MachOper *_opnd_array[1];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return membar_acquire_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_MemBarAcquire; }
  virtual uint           oper_input_base() const { return 1; }
public:
  membar_acquireNode() {  _num_opnds = 1; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(membar_acquireNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  const Type            *bottom_type() const { return TypeTuple::MEMBAR; } // matched MemBar
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "membar_acquire";}
#endif
};

class membar_acquire_0Node : public MachMemBarNode { 
private:
  MachOper *_opnd_array[1];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return membar_acquire_0_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_LoadFence; }
  virtual uint           oper_input_base() const { return 1; }
public:
  membar_acquire_0Node() {  _num_opnds = 1; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(membar_acquire_0Node); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  const Type            *bottom_type() const { return TypeTuple::MEMBAR; } // matched MemBar
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "membar_acquire_0";}
#endif
};

class membar_acquire_lockNode : public MachMemBarNode { 
private:
  MachOper *_opnd_array[1];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return membar_acquire_lock_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_MemBarAcquireLock; }
  virtual uint           oper_input_base() const { return 1; }
public:
  membar_acquire_lockNode() {  _num_opnds = 1; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(membar_acquire_lockNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  const Type            *bottom_type() const { return TypeTuple::MEMBAR; } // matched MemBar
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "membar_acquire_lock";}
#endif
};

class membar_releaseNode : public MachMemBarNode { 
private:
  MachOper *_opnd_array[1];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return membar_release_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_MemBarRelease; }
  virtual uint           oper_input_base() const { return 1; }
public:
  membar_releaseNode() {  _num_opnds = 1; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(membar_releaseNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  const Type            *bottom_type() const { return TypeTuple::MEMBAR; } // matched MemBar
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "membar_release";}
#endif
};

class membar_release_0Node : public MachMemBarNode { 
private:
  MachOper *_opnd_array[1];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return membar_release_0_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_StoreFence; }
  virtual uint           oper_input_base() const { return 1; }
public:
  membar_release_0Node() {  _num_opnds = 1; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(membar_release_0Node); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  const Type            *bottom_type() const { return TypeTuple::MEMBAR; } // matched MemBar
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "membar_release_0";}
#endif
};

class membar_release_lockNode : public MachMemBarNode { 
private:
  MachOper *_opnd_array[1];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return membar_release_lock_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_MemBarReleaseLock; }
  virtual uint           oper_input_base() const { return 1; }
public:
  membar_release_lockNode() {  _num_opnds = 1; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(membar_release_lockNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  const Type            *bottom_type() const { return TypeTuple::MEMBAR; } // matched MemBar
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "membar_release_lock";}
#endif
};

class membar_storeloadNode : public MachMemBarNode { 
private:
  MachOper *_opnd_array[1];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return membar_storeload_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_MemBarStoreLoad; }
  virtual uint           oper_input_base() const { return 1; }
public:
  membar_storeloadNode() {  _num_opnds = 1; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(membar_storeloadNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  const Type            *bottom_type() const { return TypeTuple::MEMBAR; } // matched MemBar
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "membar_storeload";}
#endif
};

class membar_volatileNode : public MachMemBarNode { 
private:
  MachOper *_opnd_array[1];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return membar_volatile_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_MemBarVolatile; }
  virtual uint           oper_input_base() const { return 1; }
public:
  membar_volatileNode() {  _num_opnds = 1; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(membar_volatileNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  const Type            *bottom_type() const { return TypeTuple::MEMBAR; } // matched MemBar
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "membar_volatile";}
#endif
};

class unnecessary_membar_volatileNode : public MachMemBarNode { 
private:
  MachOper *_opnd_array[1];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return unnecessary_membar_volatile_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_MemBarVolatile; }
  virtual uint           oper_input_base() const { return 1; }
public:
  unnecessary_membar_volatileNode() {  _num_opnds = 1; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(unnecessary_membar_volatileNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  const Type            *bottom_type() const { return TypeTuple::MEMBAR; } // matched MemBar
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "unnecessary_membar_volatile";}
#endif
};

class membar_fullNode : public MachMemBarNode { 
private:
  MachOper *_opnd_array[1];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return membar_full_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_MemBarFull; }
  virtual uint           oper_input_base() const { return 1; }
public:
  membar_fullNode() {  _num_opnds = 1; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(membar_fullNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  const Type            *bottom_type() const { return TypeTuple::MEMBAR; } // matched MemBar
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "membar_full";}
#endif
};

class membar_CPUOrderNode : public MachMemBarNode { 
private:
  MachOper *_opnd_array[1];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return membar_CPUOrder_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_MemBarCPUOrder; }
  virtual uint           oper_input_base() const { return 1; }
public:
  membar_CPUOrderNode() {  _num_opnds = 1; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(membar_CPUOrderNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  const Type            *bottom_type() const { return TypeTuple::MEMBAR; } // matched MemBar
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "membar_CPUOrder";}
#endif
};

class membar_storestoreNode : public MachMemBarNode { 
private:
  MachOper *_opnd_array[1];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return membar_storestore_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_MemBarStoreStore; }
  virtual uint           oper_input_base() const { return 1; }
public:
  membar_storestoreNode() {  _num_opnds = 1; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(membar_storestoreNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  const Type            *bottom_type() const { return TypeTuple::MEMBAR; } // matched MemBar
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "membar_storestore";}
#endif
};

class membar_storestore_0Node : public MachMemBarNode { 
private:
  MachOper *_opnd_array[1];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return membar_storestore_0_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_StoreStoreFence; }
  virtual uint           oper_input_base() const { return 1; }
public:
  membar_storestore_0Node() {  _num_opnds = 1; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(membar_storestore_0Node); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  const Type            *bottom_type() const { return TypeTuple::MEMBAR; } // matched MemBar
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "membar_storestore_0";}
#endif
};

class castX2PNode : public MachTypeNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return castX2P_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_CastX2P; }
  virtual uint           oper_input_base() const { return 1; }
public:
  castX2PNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(castX2PNode); }
  // Rematerialize castX2P
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "castX2P";}
#endif
};

class castP2XNode : public MachNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return castP2X_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_CastP2X; }
  virtual int            reloc() const;
public:
  castP2XNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(castP2XNode); }
  // Rematerialize castP2X
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "castP2X";}
#endif
};

class stfSSDNode : public MachNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return stfSSD_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_RegD; }
public:
  stfSSDNode() {  _num_opnds = 2; _opnds = _opnd_array; init_flags(Flag_is_Copy); }
  virtual uint           size_of() const { return sizeof(stfSSDNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "stfSSD";}
#endif
};

class stfSSFNode : public MachNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return stfSSF_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_RegF; }
public:
  stfSSFNode() {  _num_opnds = 2; _opnds = _opnd_array; init_flags(Flag_is_Copy); }
  virtual uint           size_of() const { return sizeof(stfSSFNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "stfSSF";}
#endif
};

class cmovN_regNode : public MachNode { 
private:
  MachOper *_opnd_array[5];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return cmovN_reg_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_CMoveN; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges() + opnd_array(2)->num_edges(); }
  virtual int            reloc() const;
public:
  cmovN_regNode() {  _num_opnds = 5; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(cmovN_regNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  const Type            *bottom_type() const { const Type *t = in(oper_input_base()+1)->bottom_type(); return (req() <= oper_input_base()+2) ? t : t->meet(in(oper_input_base()+2)->bottom_type()); } // CMoveN
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "cmovN_reg";}
#endif
};

class cmovN_immNode : public MachNode { 
private:
  MachOper *_opnd_array[5];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return cmovN_imm_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_CMoveN; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges() + opnd_array(2)->num_edges(); }
public:
  cmovN_immNode() {  _num_opnds = 5; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(cmovN_immNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  const Type            *bottom_type() const { const Type *t = in(oper_input_base()+1)->bottom_type(); return (req() <= oper_input_base()+2) ? t : t->meet(in(oper_input_base()+2)->bottom_type()); } // CMoveN
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "cmovN_imm";}
#endif
};

class cmovI_regNode : public MachNode { 
private:
  MachOper *_opnd_array[5];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return cmovI_reg_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_CMoveI; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges() + opnd_array(2)->num_edges(); }
public:
  cmovI_regNode() {  _num_opnds = 5; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(cmovI_regNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "cmovI_reg";}
#endif
};

class cmovI_immNode : public MachNode { 
private:
  MachOper *_opnd_array[5];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return cmovI_imm_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_CMoveI; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges() + opnd_array(2)->num_edges(); }
public:
  cmovI_immNode() {  _num_opnds = 5; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(cmovI_immNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "cmovI_imm";}
#endif
};

class cmovP_regNode : public MachNode { 
private:
  MachOper *_opnd_array[5];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return cmovP_reg_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_CMoveP; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges() + opnd_array(2)->num_edges(); }
  virtual int            reloc() const;
public:
  cmovP_regNode() {  _num_opnds = 5; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(cmovP_regNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  const Type            *bottom_type() const { const Type *t = in(oper_input_base()+1)->bottom_type(); return (req() <= oper_input_base()+2) ? t : t->meet(in(oper_input_base()+2)->bottom_type()); } // CMoveP
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "cmovP_reg";}
#endif
};

class cmovP_immNode : public MachNode { 
private:
  MachOper *_opnd_array[5];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return cmovP_imm_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_CMoveP; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges() + opnd_array(2)->num_edges(); }
  virtual int            reloc() const;
public:
  cmovP_immNode() {  _num_opnds = 5; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(cmovP_immNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  const Type            *bottom_type() const { const Type *t = in(oper_input_base()+1)->bottom_type(); return (req() <= oper_input_base()+2) ? t : t->meet(in(oper_input_base()+2)->bottom_type()); } // CMoveP
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "cmovP_imm";}
#endif
};

class cmovF_regNode : public MachNode { 
private:
  MachOper *_opnd_array[5];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return cmovF_reg_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_CMoveF; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges() + opnd_array(2)->num_edges(); }
public:
  cmovF_regNode() {  _num_opnds = 5; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(cmovF_regNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "cmovF_reg";}
#endif
};

class cmovD_regNode : public MachNode { 
private:
  MachOper *_opnd_array[5];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return cmovD_reg_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_CMoveD; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges() + opnd_array(2)->num_edges(); }
public:
  cmovD_regNode() {  _num_opnds = 5; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(cmovD_regNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "cmovD_reg";}
#endif
};

class cmovL_regNode : public MachNode { 
private:
  MachOper *_opnd_array[5];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return cmovL_reg_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_CMoveL; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges() + opnd_array(2)->num_edges(); }
public:
  cmovL_regNode() {  _num_opnds = 5; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(cmovL_regNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "cmovL_reg";}
#endif
};

class cmovL_immNode : public MachNode { 
private:
  MachOper *_opnd_array[5];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return cmovL_imm_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_CMoveL; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges() + opnd_array(2)->num_edges(); }
public:
  cmovL_immNode() {  _num_opnds = 5; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(cmovL_immNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "cmovL_imm";}
#endif
};

class tlsLoadPNode : public MachNode { 
private:
  MachOper *_opnd_array[1];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return tlsLoadP_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual int            ins_should_rematerialize() const { return true; }
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_ThreadLocal; }
public:
  tlsLoadPNode() {  _num_opnds = 1; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(tlsLoadPNode); }
  // Rematerialize tlsLoadP
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  const Type            *bottom_type() const { return TypeRawPtr::BOTTOM; } // tlsLoadP
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "tlsLoadP";}
#endif
};

class checkCastPPNode : public MachTypeNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return checkCastPP_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_CheckCastPP; }
  virtual uint           two_adr() const  { return oper_input_base(); }
  virtual uint           oper_input_base() const { return 1; }
public:
  checkCastPPNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(checkCastPPNode); }
  // Rematerialize checkCastPP
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "checkCastPP";}
#endif
};

class castPPNode : public MachTypeNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return castPP_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_CastPP; }
  virtual uint           two_adr() const  { return oper_input_base(); }
  virtual uint           oper_input_base() const { return 1; }
public:
  castPPNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(castPPNode); }
  // Rematerialize castPP
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "castPP";}
#endif
};

class castIINode : public MachTypeNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return castII_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_CastII; }
  virtual uint           two_adr() const  { return oper_input_base(); }
  virtual uint           oper_input_base() const { return 1; }
public:
  castIINode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(castIINode); }
  // Rematerialize castII
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "castII";}
#endif
};

class castLLNode : public MachTypeNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return castLL_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_CastLL; }
  virtual uint           two_adr() const  { return oper_input_base(); }
  virtual uint           oper_input_base() const { return 1; }
public:
  castLLNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(castLLNode); }
  // Rematerialize castLL
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "castLL";}
#endif
};

class castFFNode : public MachTypeNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return castFF_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_CastFF; }
  virtual uint           two_adr() const  { return oper_input_base(); }
  virtual uint           oper_input_base() const { return 1; }
public:
  castFFNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(castFFNode); }
  // Rematerialize castFF
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "castFF";}
#endif
};

class castDDNode : public MachTypeNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return castDD_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_CastDD; }
  virtual uint           two_adr() const  { return oper_input_base(); }
  virtual uint           oper_input_base() const { return 1; }
public:
  castDDNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(castDDNode); }
  // Rematerialize castDD
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "castDD";}
#endif
};

class castVVNode : public MachTypeNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return castVV_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_CastVV; }
  virtual uint           two_adr() const  { return oper_input_base(); }
  virtual uint           oper_input_base() const { return 1; }
public:
  castVVNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(castVVNode); }
  // Rematerialize castVV
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "castVV";}
#endif
};

class compareAndSwapI_boolNode : public MachNode { 
private:
  MachOper *_opnd_array[4];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return compareAndSwapI_bool_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_CompareAndSwapI; }
  virtual uint           oper_input_base() const { return 2; }
public:
  compareAndSwapI_boolNode() {  _num_opnds = 4; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(compareAndSwapI_boolNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "compareAndSwapI_bool";}
#endif
};

class compareAndSwapL_boolNode : public MachNode { 
private:
  MachOper *_opnd_array[4];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return compareAndSwapL_bool_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_CompareAndSwapL; }
  virtual uint           oper_input_base() const { return 2; }
public:
  compareAndSwapL_boolNode() {  _num_opnds = 4; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(compareAndSwapL_boolNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "compareAndSwapL_bool";}
#endif
};

class compareAndSwapP_boolNode : public MachNode { 
private:
  MachOper *_opnd_array[4];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return compareAndSwapP_bool_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_CompareAndSwapP; }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  compareAndSwapP_boolNode() {  _num_opnds = 4; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(compareAndSwapP_boolNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "compareAndSwapP_bool";}
#endif
};

class compareAndSwapN_boolNode : public MachNode { 
private:
  MachOper *_opnd_array[4];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return compareAndSwapN_bool_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_CompareAndSwapN; }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  compareAndSwapN_boolNode() {  _num_opnds = 4; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(compareAndSwapN_boolNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "compareAndSwapN_bool";}
#endif
};

class addI_mem_imm8_atomic_no_resNode : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return addI_mem_imm8_atomic_no_res_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_GetAndAddI; }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  addI_mem_imm8_atomic_no_resNode() {  _num_opnds = 3; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(addI_mem_imm8_atomic_no_resNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "addI_mem_imm8_atomic_no_res";}
#endif
};

class addI_mem_imm16_atomicNode : public MachNode { 
private:
  MachOper *_opnd_array[5];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return addI_mem_imm16_atomic_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_GetAndAddI; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges() + opnd_array(2)->num_edges(); }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  addI_mem_imm16_atomicNode() {  _num_opnds = 5; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(addI_mem_imm16_atomicNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "addI_mem_imm16_atomic";}
#endif
};

class addI_mem_imm32_atomicNode : public MachNode { 
private:
  MachOper *_opnd_array[5];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return addI_mem_imm32_atomic_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_GetAndAddI; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges() + opnd_array(2)->num_edges(); }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  addI_mem_imm32_atomicNode() {  _num_opnds = 5; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(addI_mem_imm32_atomicNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "addI_mem_imm32_atomic";}
#endif
};

class addI_mem_reg_atomicNode : public MachNode { 
private:
  MachOper *_opnd_array[5];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return addI_mem_reg_atomic_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_GetAndAddI; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges() + opnd_array(2)->num_edges(); }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  addI_mem_reg_atomicNode() {  _num_opnds = 5; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(addI_mem_reg_atomicNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "addI_mem_reg_atomic";}
#endif
};

class addL_mem_imm8_atomic_no_resNode : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return addL_mem_imm8_atomic_no_res_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_GetAndAddL; }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  addL_mem_imm8_atomic_no_resNode() {  _num_opnds = 3; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(addL_mem_imm8_atomic_no_resNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "addL_mem_imm8_atomic_no_res";}
#endif
};

class addL_mem_imm16_atomicNode : public MachNode { 
private:
  MachOper *_opnd_array[5];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return addL_mem_imm16_atomic_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_GetAndAddL; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges() + opnd_array(2)->num_edges(); }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  addL_mem_imm16_atomicNode() {  _num_opnds = 5; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(addL_mem_imm16_atomicNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "addL_mem_imm16_atomic";}
#endif
};

class addL_mem_imm32_atomicNode : public MachNode { 
private:
  MachOper *_opnd_array[5];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return addL_mem_imm32_atomic_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_GetAndAddL; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges() + opnd_array(2)->num_edges(); }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  addL_mem_imm32_atomicNode() {  _num_opnds = 5; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(addL_mem_imm32_atomicNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "addL_mem_imm32_atomic";}
#endif
};

class addL_mem_reg_atomicNode : public MachNode { 
private:
  MachOper *_opnd_array[5];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return addL_mem_reg_atomic_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_GetAndAddL; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges() + opnd_array(2)->num_edges(); }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  addL_mem_reg_atomicNode() {  _num_opnds = 5; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(addL_mem_reg_atomicNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "addL_mem_reg_atomic";}
#endif
};

class addI_mem_reg_atomic_z196Node : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return addI_mem_reg_atomic_z196_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_GetAndAddI; }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  addI_mem_reg_atomic_z196Node() {  _num_opnds = 3; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(addI_mem_reg_atomic_z196Node); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "addI_mem_reg_atomic_z196";}
#endif
};

class addL_mem_reg_atomic_z196Node : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return addL_mem_reg_atomic_z196_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_GetAndAddL; }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  addL_mem_reg_atomic_z196Node() {  _num_opnds = 3; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(addL_mem_reg_atomic_z196Node); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "addL_mem_reg_atomic_z196";}
#endif
};

class xchgI_reg_memNode : public MachNode { 
private:
  MachOper *_opnd_array[4];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return xchgI_reg_mem_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_GetAndSetI; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges(); }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  xchgI_reg_memNode() {  _num_opnds = 4; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(xchgI_reg_memNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "xchgI_reg_mem";}
#endif
};

class xchgL_reg_memNode : public MachNode { 
private:
  MachOper *_opnd_array[4];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return xchgL_reg_mem_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_GetAndSetL; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges(); }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  xchgL_reg_memNode() {  _num_opnds = 4; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(xchgL_reg_memNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "xchgL_reg_mem";}
#endif
};

class xchgN_reg_memNode : public MachTypeNode { 
private:
  MachOper *_opnd_array[4];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return xchgN_reg_mem_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_GetAndSetN; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges(); }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  xchgN_reg_memNode() {  _num_opnds = 4; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(xchgN_reg_memNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "xchgN_reg_mem";}
#endif
};

class xchgP_reg_memNode : public MachTypeNode { 
private:
  MachOper *_opnd_array[4];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return xchgP_reg_mem_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_GetAndSetP; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges(); }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  xchgP_reg_memNode() {  _num_opnds = 4; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(xchgP_reg_memNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "xchgP_reg_mem";}
#endif
};

class addI_reg_reg_CISCNode : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return addI_reg_reg_CISC_rule; }
private:
  const RegMask  *_cisc_RegMask;
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_AddI; }
  virtual uint           two_adr() const  { return oper_input_base(); }
  virtual int            cisc_operand() const { return 2; }
  virtual MachNode      *cisc_version(int offset);
  virtual void           use_cisc_RegMask();
  virtual const RegMask *cisc_RegMask() const { return _cisc_RegMask; }
public:
  addI_reg_reg_CISCNode() { _cisc_RegMask = nullptr;  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(addI_reg_reg_CISCNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "addI_reg_reg_CISC";}
#endif
};

class addI_reg_reg_RISCNode : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return addI_reg_reg_RISC_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_AddI; }
public:
  addI_reg_reg_RISCNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(addI_reg_reg_RISCNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "addI_reg_reg_RISC";}
#endif
};

class addI_reg_imm16_CISCNode : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return addI_reg_imm16_CISC_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_AddI; }
  virtual uint           two_adr() const  { return oper_input_base(); }
public:
  addI_reg_imm16_CISCNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(addI_reg_imm16_CISCNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "addI_reg_imm16_CISC";}
#endif
};

class addI_reg_imm16_RISCNode : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return addI_reg_imm16_RISC_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_AddI; }
public:
  addI_reg_imm16_RISCNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(addI_reg_imm16_RISCNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "addI_reg_imm16_RISC";}
#endif
};

class addI_reg_imm32Node : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return addI_reg_imm32_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_AddI; }
  virtual uint           two_adr() const  { return oper_input_base(); }
public:
  addI_reg_imm32Node() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(addI_reg_imm32Node); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "addI_reg_imm32";}
#endif
};

class addI_reg_imm12Node : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return addI_reg_imm12_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_AddI; }
public:
  addI_reg_imm12Node() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(addI_reg_imm12Node); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "addI_reg_imm12";}
#endif
};

class addI_reg_imm20Node : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return addI_reg_imm20_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_AddI; }
public:
  addI_reg_imm20Node() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(addI_reg_imm20Node); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "addI_reg_imm20";}
#endif
};

class addI_reg_reg_imm12Node : public MachNode { 
private:
  MachOper *_opnd_array[4];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return addI_reg_reg_imm12_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_AddI; }
public:
  addI_reg_reg_imm12Node() {  _num_opnds = 4; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(addI_reg_reg_imm12Node); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "addI_reg_reg_imm12";}
#endif
};

class addI_reg_reg_imm20Node : public MachNode { 
private:
  MachOper *_opnd_array[4];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return addI_reg_reg_imm20_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_AddI; }
public:
  addI_reg_reg_imm20Node() {  _num_opnds = 4; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(addI_reg_reg_imm20Node); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "addI_reg_reg_imm20";}
#endif
};

class addI_Reg_memNode : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return addI_Reg_mem_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_AddI; }
  virtual uint           two_adr() const  { return oper_input_base(); }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  addI_Reg_memNode() {  _num_opnds = 3; _opnds = _opnd_array; init_flags(Flag_is_cisc_alternate | Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(addI_Reg_memNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "addI_Reg_mem";}
#endif
};

class addI_Reg_mem_0Node : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return addI_Reg_mem_0_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_AddI; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges(); }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  addI_Reg_mem_0Node() {  _num_opnds = 3; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(addI_Reg_mem_0Node); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "addI_Reg_mem_0";}
#endif
};

class addI_mem_immNode : public MachTypeNode { 
private:
  MachOper *_opnd_array[4];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return addI_mem_imm_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_StoreI; }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  addI_mem_immNode() {  _num_opnds = 4; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(addI_mem_immNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "addI_mem_imm";}
#endif
};

class addL_reg_regINode : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return addL_reg_regI_rule; }
private:
  const RegMask  *_cisc_RegMask;
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_AddL; }
  virtual uint           two_adr() const  { return oper_input_base(); }
  virtual int            cisc_operand() const { return 2; }
  virtual MachNode      *cisc_version(int offset);
  virtual void           use_cisc_RegMask();
  virtual const RegMask *cisc_RegMask() const { return _cisc_RegMask; }
public:
  addL_reg_regINode() { _cisc_RegMask = nullptr;  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(addL_reg_regINode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "addL_reg_regI";}
#endif
};

class addL_reg_regI_0Node : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return addL_reg_regI_0_rule; }
private:
  const RegMask  *_cisc_RegMask;
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_AddL; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges(); }
  virtual int            cisc_operand() const { return 1; }
  virtual MachNode      *cisc_version(int offset);
  virtual void           use_cisc_RegMask();
  virtual const RegMask *cisc_RegMask() const { return _cisc_RegMask; }
public:
  addL_reg_regI_0Node() { _cisc_RegMask = nullptr;  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(addL_reg_regI_0Node); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "addL_reg_regI_0";}
#endif
};

class addL_reg_reg_CISCNode : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return addL_reg_reg_CISC_rule; }
private:
  const RegMask  *_cisc_RegMask;
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_AddL; }
  virtual uint           two_adr() const  { return oper_input_base(); }
  virtual int            cisc_operand() const { return 2; }
  virtual MachNode      *cisc_version(int offset);
  virtual void           use_cisc_RegMask();
  virtual const RegMask *cisc_RegMask() const { return _cisc_RegMask; }
public:
  addL_reg_reg_CISCNode() { _cisc_RegMask = nullptr;  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(addL_reg_reg_CISCNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "addL_reg_reg_CISC";}
#endif
};

class addL_reg_reg_RISCNode : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return addL_reg_reg_RISC_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_AddL; }
public:
  addL_reg_reg_RISCNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(addL_reg_reg_RISCNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "addL_reg_reg_RISC";}
#endif
};

class addL_reg_imm12Node : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return addL_reg_imm12_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_AddL; }
public:
  addL_reg_imm12Node() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(addL_reg_imm12Node); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "addL_reg_imm12";}
#endif
};

class addL_reg_imm20Node : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return addL_reg_imm20_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_AddL; }
public:
  addL_reg_imm20Node() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(addL_reg_imm20Node); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "addL_reg_imm20";}
#endif
};

class addL_reg_imm32Node : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return addL_reg_imm32_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_AddL; }
  virtual uint           two_adr() const  { return oper_input_base(); }
public:
  addL_reg_imm32Node() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(addL_reg_imm32Node); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "addL_reg_imm32";}
#endif
};

class addL_reg_imm16_CISCNode : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return addL_reg_imm16_CISC_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_AddL; }
  virtual uint           two_adr() const  { return oper_input_base(); }
public:
  addL_reg_imm16_CISCNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(addL_reg_imm16_CISCNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "addL_reg_imm16_CISC";}
#endif
};

class addL_reg_imm16_RISCNode : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return addL_reg_imm16_RISC_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_AddL; }
public:
  addL_reg_imm16_RISCNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(addL_reg_imm16_RISCNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "addL_reg_imm16_RISC";}
#endif
};

class addL_Reg_memINode : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return addL_Reg_memI_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_AddL; }
  virtual uint           two_adr() const  { return oper_input_base(); }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  addL_Reg_memINode() {  _num_opnds = 3; _opnds = _opnd_array; init_flags(Flag_is_cisc_alternate | Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(addL_Reg_memINode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "addL_Reg_memI";}
#endif
};

class addL_Reg_memI_0Node : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return addL_Reg_memI_0_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_AddL; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges(); }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  addL_Reg_memI_0Node() {  _num_opnds = 3; _opnds = _opnd_array; init_flags(Flag_is_cisc_alternate | Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(addL_Reg_memI_0Node); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "addL_Reg_memI_0";}
#endif
};

class addL_Reg_memNode : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return addL_Reg_mem_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_AddL; }
  virtual uint           two_adr() const  { return oper_input_base(); }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  addL_Reg_memNode() {  _num_opnds = 3; _opnds = _opnd_array; init_flags(Flag_is_cisc_alternate | Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(addL_Reg_memNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "addL_Reg_mem";}
#endif
};

class addL_Reg_mem_0Node : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return addL_Reg_mem_0_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_AddL; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges(); }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  addL_Reg_mem_0Node() {  _num_opnds = 3; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(addL_Reg_mem_0Node); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "addL_Reg_mem_0";}
#endif
};

class addL_reg_reg_imm12Node : public MachNode { 
private:
  MachOper *_opnd_array[4];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return addL_reg_reg_imm12_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_AddL; }
public:
  addL_reg_reg_imm12Node() {  _num_opnds = 4; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(addL_reg_reg_imm12Node); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "addL_reg_reg_imm12";}
#endif
};

class addL_reg_reg_imm20Node : public MachNode { 
private:
  MachOper *_opnd_array[4];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return addL_reg_reg_imm20_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_AddL; }
public:
  addL_reg_reg_imm20Node() {  _num_opnds = 4; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(addL_reg_reg_imm20Node); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "addL_reg_reg_imm20";}
#endif
};

class addL_mem_immNode : public MachTypeNode { 
private:
  MachOper *_opnd_array[4];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return addL_mem_imm_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_StoreL; }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  addL_mem_immNode() {  _num_opnds = 4; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(addL_mem_immNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "addL_mem_imm";}
#endif
};

class addP_reg_reg_LANode : public MachTypeNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return addP_reg_reg_LA_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_AddP; }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  addP_reg_reg_LANode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(addP_reg_reg_LANode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "addP_reg_reg_LA";}
#endif
};

class addP_reg_reg_CISCNode : public MachTypeNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return addP_reg_reg_CISC_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_AddP; }
  virtual uint           two_adr() const  { return oper_input_base(); }
  virtual uint           oper_input_base() const { return 2; }
public:
  addP_reg_reg_CISCNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(addP_reg_reg_CISCNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "addP_reg_reg_CISC";}
#endif
};

class addP_reg_reg_RISCNode : public MachTypeNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return addP_reg_reg_RISC_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_AddP; }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  addP_reg_reg_RISCNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(addP_reg_reg_RISCNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "addP_reg_reg_RISC";}
#endif
};

class addP_reg_imm12Node : public MachTypeNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return addP_reg_imm12_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_AddP; }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  addP_reg_imm12Node() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(addP_reg_imm12Node); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "addP_reg_imm12";}
#endif
};

class addP_reg_imm16_CISCNode : public MachTypeNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return addP_reg_imm16_CISC_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_AddP; }
  virtual uint           two_adr() const  { return oper_input_base(); }
  virtual uint           oper_input_base() const { return 2; }
public:
  addP_reg_imm16_CISCNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(addP_reg_imm16_CISCNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "addP_reg_imm16_CISC";}
#endif
};

class addP_reg_imm16_RISCNode : public MachTypeNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return addP_reg_imm16_RISC_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_AddP; }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  addP_reg_imm16_RISCNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(addP_reg_imm16_RISCNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "addP_reg_imm16_RISC";}
#endif
};

class addP_reg_imm20Node : public MachTypeNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return addP_reg_imm20_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_AddP; }
  virtual uint           oper_input_base() const { return 2; }
public:
  addP_reg_imm20Node() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(addP_reg_imm20Node); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "addP_reg_imm20";}
#endif
};

class addP_reg_imm32Node : public MachTypeNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return addP_reg_imm32_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_AddP; }
  virtual uint           two_adr() const  { return oper_input_base(); }
  virtual uint           oper_input_base() const { return 2; }
public:
  addP_reg_imm32Node() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(addP_reg_imm32Node); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "addP_reg_imm32";}
#endif
};

class addP_reg_reg_imm12Node : public MachTypeNode { 
private:
  MachOper *_opnd_array[4];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return addP_reg_reg_imm12_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_AddP; }
  virtual uint           oper_input_base() const { return 2; }
public:
  addP_reg_reg_imm12Node() {  _num_opnds = 4; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(addP_reg_reg_imm12Node); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "addP_reg_reg_imm12";}
#endif
};

class addP_regN_reg_imm12Node : public MachTypeNode { 
private:
  MachOper *_opnd_array[4];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return addP_regN_reg_imm12_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_AddP; }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  addP_regN_reg_imm12Node() {  _num_opnds = 4; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(addP_regN_reg_imm12Node); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "addP_regN_reg_imm12";}
#endif
};

class addP_reg_reg_imm20Node : public MachTypeNode { 
private:
  MachOper *_opnd_array[4];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return addP_reg_reg_imm20_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_AddP; }
  virtual uint           oper_input_base() const { return 2; }
public:
  addP_reg_reg_imm20Node() {  _num_opnds = 4; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(addP_reg_reg_imm20Node); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "addP_reg_reg_imm20";}
#endif
};

class addP_regN_reg_imm20Node : public MachTypeNode { 
private:
  MachOper *_opnd_array[4];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return addP_regN_reg_imm20_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_AddP; }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  addP_regN_reg_imm20Node() {  _num_opnds = 4; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(addP_regN_reg_imm20Node); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "addP_regN_reg_imm20";}
#endif
};

class addP_mem_immNode : public MachTypeNode { 
private:
  MachOper *_opnd_array[4];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return addP_mem_imm_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_StoreP; }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  addP_mem_immNode() {  _num_opnds = 4; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(addP_mem_immNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "addP_mem_imm";}
#endif
};

class subI_reg_reg_CISCNode : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return subI_reg_reg_CISC_rule; }
private:
  const RegMask  *_cisc_RegMask;
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_SubI; }
  virtual uint           two_adr() const  { return oper_input_base(); }
  virtual int            cisc_operand() const { return 2; }
  virtual MachNode      *cisc_version(int offset);
  virtual void           use_cisc_RegMask();
  virtual const RegMask *cisc_RegMask() const { return _cisc_RegMask; }
public:
  subI_reg_reg_CISCNode() { _cisc_RegMask = nullptr;  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(subI_reg_reg_CISCNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "subI_reg_reg_CISC";}
#endif
};

class subI_reg_reg_RISCNode : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return subI_reg_reg_RISC_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_SubI; }
public:
  subI_reg_reg_RISCNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(subI_reg_reg_RISCNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "subI_reg_reg_RISC";}
#endif
};

class subI_Reg_memNode : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return subI_Reg_mem_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_SubI; }
  virtual uint           two_adr() const  { return oper_input_base(); }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  subI_Reg_memNode() {  _num_opnds = 3; _opnds = _opnd_array; init_flags(Flag_is_cisc_alternate | Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(subI_Reg_memNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "subI_Reg_mem";}
#endif
};

class subI_zero_regNode : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return subI_zero_reg_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_SubI; }
public:
  subI_zero_regNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(subI_zero_regNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "subI_zero_reg";}
#endif
};

class subL_reg_reg_CISCNode : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return subL_reg_reg_CISC_rule; }
private:
  const RegMask  *_cisc_RegMask;
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_SubL; }
  virtual uint           two_adr() const  { return oper_input_base(); }
  virtual int            cisc_operand() const { return 2; }
  virtual MachNode      *cisc_version(int offset);
  virtual void           use_cisc_RegMask();
  virtual const RegMask *cisc_RegMask() const { return _cisc_RegMask; }
public:
  subL_reg_reg_CISCNode() { _cisc_RegMask = nullptr;  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(subL_reg_reg_CISCNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "subL_reg_reg_CISC";}
#endif
};

class subL_reg_reg_RISCNode : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return subL_reg_reg_RISC_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_SubL; }
public:
  subL_reg_reg_RISCNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(subL_reg_reg_RISCNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "subL_reg_reg_RISC";}
#endif
};

class subL_reg_regI_CISCNode : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return subL_reg_regI_CISC_rule; }
private:
  const RegMask  *_cisc_RegMask;
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_SubL; }
  virtual uint           two_adr() const  { return oper_input_base(); }
  virtual int            cisc_operand() const { return 2; }
  virtual MachNode      *cisc_version(int offset);
  virtual void           use_cisc_RegMask();
  virtual const RegMask *cisc_RegMask() const { return _cisc_RegMask; }
public:
  subL_reg_regI_CISCNode() { _cisc_RegMask = nullptr;  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(subL_reg_regI_CISCNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "subL_reg_regI_CISC";}
#endif
};

class subL_Reg_memINode : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return subL_Reg_memI_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_SubL; }
  virtual uint           two_adr() const  { return oper_input_base(); }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  subL_Reg_memINode() {  _num_opnds = 3; _opnds = _opnd_array; init_flags(Flag_is_cisc_alternate | Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(subL_Reg_memINode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "subL_Reg_memI";}
#endif
};

class subL_Reg_memNode : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return subL_Reg_mem_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_SubL; }
  virtual uint           two_adr() const  { return oper_input_base(); }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  subL_Reg_memNode() {  _num_opnds = 3; _opnds = _opnd_array; init_flags(Flag_is_cisc_alternate | Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(subL_Reg_memNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "subL_Reg_mem";}
#endif
};

class mulI_reg_regNode : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return mulI_reg_reg_rule; }
private:
  const RegMask  *_cisc_RegMask;
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_MulI; }
  virtual uint           two_adr() const  { return oper_input_base(); }
  virtual int            cisc_operand() const { return 2; }
  virtual MachNode      *cisc_version(int offset);
  virtual void           use_cisc_RegMask();
  virtual const RegMask *cisc_RegMask() const { return _cisc_RegMask; }
public:
  mulI_reg_regNode() { _cisc_RegMask = nullptr;  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(mulI_reg_regNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "mulI_reg_reg";}
#endif
};

class mulI_reg_imm16Node : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return mulI_reg_imm16_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_MulI; }
  virtual uint           two_adr() const  { return oper_input_base(); }
public:
  mulI_reg_imm16Node() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(mulI_reg_imm16Node); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "mulI_reg_imm16";}
#endif
};

class mulI_reg_imm32Node : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return mulI_reg_imm32_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_MulI; }
  virtual uint           two_adr() const  { return oper_input_base(); }
public:
  mulI_reg_imm32Node() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(mulI_reg_imm32Node); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "mulI_reg_imm32";}
#endif
};

class mulI_Reg_memNode : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return mulI_Reg_mem_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_MulI; }
  virtual uint           two_adr() const  { return oper_input_base(); }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  mulI_Reg_memNode() {  _num_opnds = 3; _opnds = _opnd_array; init_flags(Flag_is_cisc_alternate | Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(mulI_Reg_memNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "mulI_Reg_mem";}
#endif
};

class mulI_Reg_mem_0Node : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return mulI_Reg_mem_0_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_MulI; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges(); }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  mulI_Reg_mem_0Node() {  _num_opnds = 3; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(mulI_Reg_mem_0Node); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "mulI_Reg_mem_0";}
#endif
};

class mulL_reg_regINode : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return mulL_reg_regI_rule; }
private:
  const RegMask  *_cisc_RegMask;
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_MulL; }
  virtual uint           two_adr() const  { return oper_input_base(); }
  virtual int            cisc_operand() const { return 2; }
  virtual MachNode      *cisc_version(int offset);
  virtual void           use_cisc_RegMask();
  virtual const RegMask *cisc_RegMask() const { return _cisc_RegMask; }
public:
  mulL_reg_regINode() { _cisc_RegMask = nullptr;  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(mulL_reg_regINode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "mulL_reg_regI";}
#endif
};

class mulL_reg_regI_0Node : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return mulL_reg_regI_0_rule; }
private:
  const RegMask  *_cisc_RegMask;
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_MulL; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges(); }
  virtual int            cisc_operand() const { return 1; }
  virtual MachNode      *cisc_version(int offset);
  virtual void           use_cisc_RegMask();
  virtual const RegMask *cisc_RegMask() const { return _cisc_RegMask; }
public:
  mulL_reg_regI_0Node() { _cisc_RegMask = nullptr;  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(mulL_reg_regI_0Node); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "mulL_reg_regI_0";}
#endif
};

class mulL_reg_regNode : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return mulL_reg_reg_rule; }
private:
  const RegMask  *_cisc_RegMask;
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_MulL; }
  virtual uint           two_adr() const  { return oper_input_base(); }
  virtual int            cisc_operand() const { return 2; }
  virtual MachNode      *cisc_version(int offset);
  virtual void           use_cisc_RegMask();
  virtual const RegMask *cisc_RegMask() const { return _cisc_RegMask; }
public:
  mulL_reg_regNode() { _cisc_RegMask = nullptr;  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(mulL_reg_regNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "mulL_reg_reg";}
#endif
};

class mulL_reg_imm16Node : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return mulL_reg_imm16_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_MulL; }
  virtual uint           two_adr() const  { return oper_input_base(); }
public:
  mulL_reg_imm16Node() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(mulL_reg_imm16Node); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "mulL_reg_imm16";}
#endif
};

class mulL_reg_imm32Node : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return mulL_reg_imm32_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_MulL; }
  virtual uint           two_adr() const  { return oper_input_base(); }
public:
  mulL_reg_imm32Node() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(mulL_reg_imm32Node); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "mulL_reg_imm32";}
#endif
};

class mulL_Reg_memINode : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return mulL_Reg_memI_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_MulL; }
  virtual uint           two_adr() const  { return oper_input_base(); }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  mulL_Reg_memINode() {  _num_opnds = 3; _opnds = _opnd_array; init_flags(Flag_is_cisc_alternate | Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(mulL_Reg_memINode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "mulL_Reg_memI";}
#endif
};

class mulL_Reg_memI_0Node : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return mulL_Reg_memI_0_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_MulL; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges(); }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  mulL_Reg_memI_0Node() {  _num_opnds = 3; _opnds = _opnd_array; init_flags(Flag_is_cisc_alternate | Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(mulL_Reg_memI_0Node); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "mulL_Reg_memI_0";}
#endif
};

class mulL_Reg_memNode : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return mulL_Reg_mem_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_MulL; }
  virtual uint           two_adr() const  { return oper_input_base(); }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  mulL_Reg_memNode() {  _num_opnds = 3; _opnds = _opnd_array; init_flags(Flag_is_cisc_alternate | Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(mulL_Reg_memNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "mulL_Reg_mem";}
#endif
};

class mulL_Reg_mem_0Node : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return mulL_Reg_mem_0_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_MulL; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges(); }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  mulL_Reg_mem_0Node() {  _num_opnds = 3; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(mulL_Reg_mem_0Node); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "mulL_Reg_mem_0";}
#endif
};

class mulHiL_reg_regNode : public MachNode { 
private:
  MachOper *_opnd_array[5];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return mulHiL_reg_reg_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_MulHiL; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges() + opnd_array(2)->num_edges(); }
public:
  mulHiL_reg_regNode() {  _num_opnds = 5; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(mulHiL_reg_regNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "mulHiL_reg_reg";}
#endif
};

class divModI_reg_divmodNode : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return divModI_reg_divmod_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_DivModI; }
public:
  divModI_reg_divmodNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(divModI_reg_divmodNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "divModI_reg_divmod";}
#endif
};

class divI_reg_regNode : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return divI_reg_reg_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_DivI; }
public:
  divI_reg_regNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(divI_reg_regNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "divI_reg_reg";}
#endif
};

class divI_reg_imm16Node : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return divI_reg_imm16_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_DivI; }
public:
  divI_reg_imm16Node() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(divI_reg_imm16Node); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "divI_reg_imm16";}
#endif
};

class udivI_reg_regNode : public MachNode { 
private:
  MachOper *_opnd_array[4];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return udivI_reg_reg_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_UDivI; }
  virtual uint           two_adr() const  { return oper_input_base(); }
public:
  udivI_reg_regNode() {  _num_opnds = 4; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(udivI_reg_regNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "udivI_reg_reg";}
#endif
};

class divModL_reg_divmodNode : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return divModL_reg_divmod_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_DivModL; }
public:
  divModL_reg_divmodNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(divModL_reg_divmodNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "divModL_reg_divmod";}
#endif
};

class divL_reg_regNode : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return divL_reg_reg_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_DivL; }
  virtual uint           two_adr() const  { return oper_input_base(); }
public:
  divL_reg_regNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(divL_reg_regNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "divL_reg_reg";}
#endif
};

class udivL_reg_regNode : public MachNode { 
private:
  MachOper *_opnd_array[4];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return udivL_reg_reg_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_UDivL; }
  virtual uint           two_adr() const  { return oper_input_base(); }
public:
  udivL_reg_regNode() {  _num_opnds = 4; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(udivL_reg_regNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "udivL_reg_reg";}
#endif
};

class divL_reg_imm16Node : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return divL_reg_imm16_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_DivL; }
public:
  divL_reg_imm16Node() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(divL_reg_imm16Node); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "divL_reg_imm16";}
#endif
};

class modI_reg_regNode : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return modI_reg_reg_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_ModI; }
public:
  modI_reg_regNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(modI_reg_regNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "modI_reg_reg";}
#endif
};

class umodI_reg_regNode : public MachNode { 
private:
  MachOper *_opnd_array[4];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return umodI_reg_reg_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_UModI; }
  virtual uint           two_adr() const  { return oper_input_base(); }
public:
  umodI_reg_regNode() {  _num_opnds = 4; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(umodI_reg_regNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "umodI_reg_reg";}
#endif
};

class modI_reg_imm16Node : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return modI_reg_imm16_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_ModI; }
public:
  modI_reg_imm16Node() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(modI_reg_imm16Node); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "modI_reg_imm16";}
#endif
};

class modL_reg_regNode : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return modL_reg_reg_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_ModL; }
public:
  modL_reg_regNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(modL_reg_regNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "modL_reg_reg";}
#endif
};

class umodL_reg_regNode : public MachNode { 
private:
  MachOper *_opnd_array[4];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return umodL_reg_reg_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_UModL; }
  virtual uint           two_adr() const  { return oper_input_base(); }
public:
  umodL_reg_regNode() {  _num_opnds = 4; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(umodL_reg_regNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "umodL_reg_reg";}
#endif
};

class modL_reg_imm16Node : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return modL_reg_imm16_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_ModL; }
public:
  modL_reg_imm16Node() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(modL_reg_imm16Node); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "modL_reg_imm16";}
#endif
};

class sllI_reg_regNode : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return sllI_reg_reg_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_LShiftI; }
public:
  sllI_reg_regNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(sllI_reg_regNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "sllI_reg_reg";}
#endif
};

class sllI_reg_immNode : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return sllI_reg_imm_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_LShiftI; }
public:
  sllI_reg_immNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(sllI_reg_immNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "sllI_reg_imm";}
#endif
};

class sllI_reg_imm_1Node : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return sllI_reg_imm_1_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_LShiftI; }
public:
  sllI_reg_imm_1Node() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(sllI_reg_imm_1Node); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "sllI_reg_imm_1";}
#endif
};

class sllL_reg_regNode : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return sllL_reg_reg_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_LShiftL; }
public:
  sllL_reg_regNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(sllL_reg_regNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "sllL_reg_reg";}
#endif
};

class sllL_reg_immNode : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return sllL_reg_imm_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_LShiftL; }
public:
  sllL_reg_immNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(sllL_reg_immNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "sllL_reg_imm";}
#endif
};

class sllL_reg_imm_1Node : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return sllL_reg_imm_1_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_LShiftL; }
public:
  sllL_reg_imm_1Node() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(sllL_reg_imm_1Node); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "sllL_reg_imm_1";}
#endif
};

class sraI_reg_regNode : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return sraI_reg_reg_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_RShiftI; }
  virtual uint           two_adr() const  { return oper_input_base(); }
public:
  sraI_reg_regNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(sraI_reg_regNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "sraI_reg_reg";}
#endif
};

class sraI_reg_immNode : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return sraI_reg_imm_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_RShiftI; }
  virtual uint           two_adr() const  { return oper_input_base(); }
public:
  sraI_reg_immNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(sraI_reg_immNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "sraI_reg_imm";}
#endif
};

class sraL_reg_regNode : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return sraL_reg_reg_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_RShiftL; }
public:
  sraL_reg_regNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(sraL_reg_regNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "sraL_reg_reg";}
#endif
};

class sraL_reg_immNode : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return sraL_reg_imm_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_RShiftL; }
public:
  sraL_reg_immNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(sraL_reg_immNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "sraL_reg_imm";}
#endif
};

class srlI_reg_regNode : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return srlI_reg_reg_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_URShiftI; }
  virtual uint           two_adr() const  { return oper_input_base(); }
public:
  srlI_reg_regNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(srlI_reg_regNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "srlI_reg_reg";}
#endif
};

class srlI_reg_immNode : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return srlI_reg_imm_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_URShiftI; }
  virtual uint           two_adr() const  { return oper_input_base(); }
public:
  srlI_reg_immNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(srlI_reg_immNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "srlI_reg_imm";}
#endif
};

class srlL_reg_regNode : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return srlL_reg_reg_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_URShiftL; }
public:
  srlL_reg_regNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(srlL_reg_regNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "srlL_reg_reg";}
#endif
};

class srlL_reg_immNode : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return srlL_reg_imm_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_URShiftL; }
public:
  srlL_reg_immNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(srlL_reg_immNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "srlL_reg_imm";}
#endif
};

class srlP_reg_immNode : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return srlP_reg_imm_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_URShiftL; }
  virtual int            reloc() const;
public:
  srlP_reg_immNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(srlP_reg_immNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "srlP_reg_imm";}
#endif
};

class rotlI_reg_immI8Node : public MachNode { 
private:
  MachOper *_opnd_array[5];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return rotlI_reg_immI8_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_OrI; }
public:
  rotlI_reg_immI8Node() {  _num_opnds = 5; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(rotlI_reg_immI8Node); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "rotlI_reg_immI8";}
#endif
};

class rotlI_reg_immI8_0Node : public MachNode { 
private:
  MachOper *_opnd_array[5];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return rotlI_reg_immI8_0_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_OrI; }
public:
  rotlI_reg_immI8_0Node() {  _num_opnds = 5; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(rotlI_reg_immI8_0Node); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "rotlI_reg_immI8_0";}
#endif
};

class rotlL_reg_immI8Node : public MachNode { 
private:
  MachOper *_opnd_array[5];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return rotlL_reg_immI8_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_OrL; }
public:
  rotlL_reg_immI8Node() {  _num_opnds = 5; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(rotlL_reg_immI8Node); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "rotlL_reg_immI8";}
#endif
};

class rotlL_reg_immI8_0Node : public MachNode { 
private:
  MachOper *_opnd_array[5];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return rotlL_reg_immI8_0_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_OrL; }
public:
  rotlL_reg_immI8_0Node() {  _num_opnds = 5; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(rotlL_reg_immI8_0Node); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "rotlL_reg_immI8_0";}
#endif
};

class rotrI_reg_immI8Node : public MachNode { 
private:
  MachOper *_opnd_array[5];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return rotrI_reg_immI8_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_OrI; }
public:
  rotrI_reg_immI8Node() {  _num_opnds = 5; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(rotrI_reg_immI8Node); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "rotrI_reg_immI8";}
#endif
};

class rotrI_reg_immI8_0Node : public MachNode { 
private:
  MachOper *_opnd_array[5];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return rotrI_reg_immI8_0_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_OrI; }
public:
  rotrI_reg_immI8_0Node() {  _num_opnds = 5; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(rotrI_reg_immI8_0Node); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "rotrI_reg_immI8_0";}
#endif
};

class rotrL_reg_immI8Node : public MachNode { 
private:
  MachOper *_opnd_array[5];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return rotrL_reg_immI8_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_OrL; }
public:
  rotrL_reg_immI8Node() {  _num_opnds = 5; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(rotrL_reg_immI8Node); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "rotrL_reg_immI8";}
#endif
};

class rotrL_reg_immI8_0Node : public MachNode { 
private:
  MachOper *_opnd_array[5];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return rotrL_reg_immI8_0_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_OrL; }
public:
  rotrL_reg_immI8_0Node() {  _num_opnds = 5; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(rotrL_reg_immI8_0Node); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "rotrL_reg_immI8_0";}
#endif
};

class overflowAddI_reg_regNode : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return overflowAddI_reg_reg_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_OverflowAddI; }
public:
  overflowAddI_reg_regNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(overflowAddI_reg_regNode); }
  // Rematerialize overflowAddI_reg_reg
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "overflowAddI_reg_reg";}
#endif
};

class overflowAddI_reg_immNode : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return overflowAddI_reg_imm_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_OverflowAddI; }
public:
  overflowAddI_reg_immNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(overflowAddI_reg_immNode); }
  // Rematerialize overflowAddI_reg_imm
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "overflowAddI_reg_imm";}
#endif
};

class overflowAddL_reg_regNode : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return overflowAddL_reg_reg_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_OverflowAddL; }
public:
  overflowAddL_reg_regNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(overflowAddL_reg_regNode); }
  // Rematerialize overflowAddL_reg_reg
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "overflowAddL_reg_reg";}
#endif
};

class overflowAddL_reg_immNode : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return overflowAddL_reg_imm_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_OverflowAddL; }
public:
  overflowAddL_reg_immNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(overflowAddL_reg_immNode); }
  // Rematerialize overflowAddL_reg_imm
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "overflowAddL_reg_imm";}
#endif
};

class overflowSubI_reg_regNode : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return overflowSubI_reg_reg_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_OverflowSubI; }
public:
  overflowSubI_reg_regNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(overflowSubI_reg_regNode); }
  // Rematerialize overflowSubI_reg_reg
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "overflowSubI_reg_reg";}
#endif
};

class overflowSubI_reg_immNode : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return overflowSubI_reg_imm_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_OverflowSubI; }
public:
  overflowSubI_reg_immNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(overflowSubI_reg_immNode); }
  // Rematerialize overflowSubI_reg_imm
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "overflowSubI_reg_imm";}
#endif
};

class overflowSubL_reg_regNode : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return overflowSubL_reg_reg_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_OverflowSubL; }
public:
  overflowSubL_reg_regNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(overflowSubL_reg_regNode); }
  // Rematerialize overflowSubL_reg_reg
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "overflowSubL_reg_reg";}
#endif
};

class overflowSubL_reg_immNode : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return overflowSubL_reg_imm_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_OverflowSubL; }
public:
  overflowSubL_reg_immNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(overflowSubL_reg_immNode); }
  // Rematerialize overflowSubL_reg_imm
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "overflowSubL_reg_imm";}
#endif
};

class overflowNegI_rRegNode : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return overflowNegI_rReg_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_OverflowSubI; }
public:
  overflowNegI_rRegNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(overflowNegI_rRegNode); }
  // Rematerialize overflowNegI_rReg
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "overflowNegI_rReg";}
#endif
};

class overflowNegL_rRegNode : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return overflowNegL_rReg_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_OverflowSubL; }
public:
  overflowNegL_rRegNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(overflowNegL_rRegNode); }
  // Rematerialize overflowNegL_rReg
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "overflowNegL_rReg";}
#endif
};

class addF_reg_regNode : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return addF_reg_reg_rule; }
private:
  const RegMask  *_cisc_RegMask;
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_AddF; }
  virtual uint           two_adr() const  { return oper_input_base(); }
  virtual int            cisc_operand() const { return 2; }
  virtual MachNode      *cisc_version(int offset);
  virtual void           use_cisc_RegMask();
  virtual const RegMask *cisc_RegMask() const { return _cisc_RegMask; }
public:
  addF_reg_regNode() { _cisc_RegMask = nullptr;  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(addF_reg_regNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "addF_reg_reg";}
#endif
};

class addF_reg_memNode : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return addF_reg_mem_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_AddF; }
  virtual uint           two_adr() const  { return oper_input_base(); }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  addF_reg_memNode() {  _num_opnds = 3; _opnds = _opnd_array; init_flags(Flag_is_cisc_alternate | Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(addF_reg_memNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "addF_reg_mem";}
#endif
};

class addF_reg_mem_0Node : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return addF_reg_mem_0_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_AddF; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges(); }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  addF_reg_mem_0Node() {  _num_opnds = 3; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(addF_reg_mem_0Node); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "addF_reg_mem_0";}
#endif
};

class addD_reg_regNode : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return addD_reg_reg_rule; }
private:
  const RegMask  *_cisc_RegMask;
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_AddD; }
  virtual uint           two_adr() const  { return oper_input_base(); }
  virtual int            cisc_operand() const { return 2; }
  virtual MachNode      *cisc_version(int offset);
  virtual void           use_cisc_RegMask();
  virtual const RegMask *cisc_RegMask() const { return _cisc_RegMask; }
public:
  addD_reg_regNode() { _cisc_RegMask = nullptr;  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(addD_reg_regNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "addD_reg_reg";}
#endif
};

class addD_reg_memNode : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return addD_reg_mem_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_AddD; }
  virtual uint           two_adr() const  { return oper_input_base(); }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  addD_reg_memNode() {  _num_opnds = 3; _opnds = _opnd_array; init_flags(Flag_is_cisc_alternate | Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(addD_reg_memNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "addD_reg_mem";}
#endif
};

class addD_reg_mem_0Node : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return addD_reg_mem_0_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_AddD; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges(); }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  addD_reg_mem_0Node() {  _num_opnds = 3; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(addD_reg_mem_0Node); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "addD_reg_mem_0";}
#endif
};

class subF_reg_regNode : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return subF_reg_reg_rule; }
private:
  const RegMask  *_cisc_RegMask;
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_SubF; }
  virtual uint           two_adr() const  { return oper_input_base(); }
  virtual int            cisc_operand() const { return 2; }
  virtual MachNode      *cisc_version(int offset);
  virtual void           use_cisc_RegMask();
  virtual const RegMask *cisc_RegMask() const { return _cisc_RegMask; }
public:
  subF_reg_regNode() { _cisc_RegMask = nullptr;  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(subF_reg_regNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "subF_reg_reg";}
#endif
};

class subF_reg_memNode : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return subF_reg_mem_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_SubF; }
  virtual uint           two_adr() const  { return oper_input_base(); }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  subF_reg_memNode() {  _num_opnds = 3; _opnds = _opnd_array; init_flags(Flag_is_cisc_alternate | Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(subF_reg_memNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "subF_reg_mem";}
#endif
};

class subD_reg_regNode : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return subD_reg_reg_rule; }
private:
  const RegMask  *_cisc_RegMask;
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_SubD; }
  virtual uint           two_adr() const  { return oper_input_base(); }
  virtual int            cisc_operand() const { return 2; }
  virtual MachNode      *cisc_version(int offset);
  virtual void           use_cisc_RegMask();
  virtual const RegMask *cisc_RegMask() const { return _cisc_RegMask; }
public:
  subD_reg_regNode() { _cisc_RegMask = nullptr;  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(subD_reg_regNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "subD_reg_reg";}
#endif
};

class subD_reg_memNode : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return subD_reg_mem_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_SubD; }
  virtual uint           two_adr() const  { return oper_input_base(); }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  subD_reg_memNode() {  _num_opnds = 3; _opnds = _opnd_array; init_flags(Flag_is_cisc_alternate | Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(subD_reg_memNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "subD_reg_mem";}
#endif
};

class mulF_reg_regNode : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return mulF_reg_reg_rule; }
private:
  const RegMask  *_cisc_RegMask;
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_MulF; }
  virtual uint           two_adr() const  { return oper_input_base(); }
  virtual int            cisc_operand() const { return 2; }
  virtual MachNode      *cisc_version(int offset);
  virtual void           use_cisc_RegMask();
  virtual const RegMask *cisc_RegMask() const { return _cisc_RegMask; }
public:
  mulF_reg_regNode() { _cisc_RegMask = nullptr;  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(mulF_reg_regNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "mulF_reg_reg";}
#endif
};

class mulF_reg_memNode : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return mulF_reg_mem_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_MulF; }
  virtual uint           two_adr() const  { return oper_input_base(); }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  mulF_reg_memNode() {  _num_opnds = 3; _opnds = _opnd_array; init_flags(Flag_is_cisc_alternate | Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(mulF_reg_memNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "mulF_reg_mem";}
#endif
};

class mulF_reg_mem_0Node : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return mulF_reg_mem_0_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_MulF; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges(); }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  mulF_reg_mem_0Node() {  _num_opnds = 3; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(mulF_reg_mem_0Node); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "mulF_reg_mem_0";}
#endif
};

class mulD_reg_regNode : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return mulD_reg_reg_rule; }
private:
  const RegMask  *_cisc_RegMask;
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_MulD; }
  virtual uint           two_adr() const  { return oper_input_base(); }
  virtual int            cisc_operand() const { return 2; }
  virtual MachNode      *cisc_version(int offset);
  virtual void           use_cisc_RegMask();
  virtual const RegMask *cisc_RegMask() const { return _cisc_RegMask; }
public:
  mulD_reg_regNode() { _cisc_RegMask = nullptr;  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(mulD_reg_regNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "mulD_reg_reg";}
#endif
};

class mulD_reg_memNode : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return mulD_reg_mem_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_MulD; }
  virtual uint           two_adr() const  { return oper_input_base(); }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  mulD_reg_memNode() {  _num_opnds = 3; _opnds = _opnd_array; init_flags(Flag_is_cisc_alternate | Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(mulD_reg_memNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "mulD_reg_mem";}
#endif
};

class mulD_reg_mem_0Node : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return mulD_reg_mem_0_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_MulD; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges(); }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  mulD_reg_mem_0Node() {  _num_opnds = 3; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(mulD_reg_mem_0Node); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "mulD_reg_mem_0";}
#endif
};

class maddF_reg_regNode : public MachNode { 
private:
  MachOper *_opnd_array[4];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return maddF_reg_reg_rule; }
private:
  const RegMask  *_cisc_RegMask;
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_FmaF; }
  virtual uint           two_adr() const  { return oper_input_base(); }
  virtual int            cisc_operand() const { return 3; }
  virtual MachNode      *cisc_version(int offset);
  virtual void           use_cisc_RegMask();
  virtual const RegMask *cisc_RegMask() const { return _cisc_RegMask; }
public:
  maddF_reg_regNode() { _cisc_RegMask = nullptr;  _num_opnds = 4; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(maddF_reg_regNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "maddF_reg_reg";}
#endif
};

class maddD_reg_regNode : public MachNode { 
private:
  MachOper *_opnd_array[4];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return maddD_reg_reg_rule; }
private:
  const RegMask  *_cisc_RegMask;
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_FmaD; }
  virtual uint           two_adr() const  { return oper_input_base(); }
  virtual int            cisc_operand() const { return 3; }
  virtual MachNode      *cisc_version(int offset);
  virtual void           use_cisc_RegMask();
  virtual const RegMask *cisc_RegMask() const { return _cisc_RegMask; }
public:
  maddD_reg_regNode() { _cisc_RegMask = nullptr;  _num_opnds = 4; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(maddD_reg_regNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "maddD_reg_reg";}
#endif
};

class msubF_reg_regNode : public MachNode { 
private:
  MachOper *_opnd_array[4];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return msubF_reg_reg_rule; }
private:
  const RegMask  *_cisc_RegMask;
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_FmaF; }
  virtual uint           two_adr() const  { return oper_input_base(); }
  virtual int            cisc_operand() const { return 3; }
  virtual MachNode      *cisc_version(int offset);
  virtual void           use_cisc_RegMask();
  virtual const RegMask *cisc_RegMask() const { return _cisc_RegMask; }
public:
  msubF_reg_regNode() { _cisc_RegMask = nullptr;  _num_opnds = 4; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(msubF_reg_regNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "msubF_reg_reg";}
#endif
};

class msubD_reg_regNode : public MachNode { 
private:
  MachOper *_opnd_array[4];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return msubD_reg_reg_rule; }
private:
  const RegMask  *_cisc_RegMask;
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_FmaD; }
  virtual uint           two_adr() const  { return oper_input_base(); }
  virtual int            cisc_operand() const { return 3; }
  virtual MachNode      *cisc_version(int offset);
  virtual void           use_cisc_RegMask();
  virtual const RegMask *cisc_RegMask() const { return _cisc_RegMask; }
public:
  msubD_reg_regNode() { _cisc_RegMask = nullptr;  _num_opnds = 4; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(msubD_reg_regNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "msubD_reg_reg";}
#endif
};

class maddF_reg_memNode : public MachNode { 
private:
  MachOper *_opnd_array[4];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return maddF_reg_mem_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_FmaF; }
  virtual uint           two_adr() const  { return oper_input_base(); }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  maddF_reg_memNode() {  _num_opnds = 4; _opnds = _opnd_array; init_flags(Flag_is_cisc_alternate | Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(maddF_reg_memNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "maddF_reg_mem";}
#endif
};

class maddD_reg_memNode : public MachNode { 
private:
  MachOper *_opnd_array[4];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return maddD_reg_mem_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_FmaD; }
  virtual uint           two_adr() const  { return oper_input_base(); }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  maddD_reg_memNode() {  _num_opnds = 4; _opnds = _opnd_array; init_flags(Flag_is_cisc_alternate | Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(maddD_reg_memNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "maddD_reg_mem";}
#endif
};

class msubF_reg_memNode : public MachNode { 
private:
  MachOper *_opnd_array[4];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return msubF_reg_mem_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_FmaF; }
  virtual uint           two_adr() const  { return oper_input_base(); }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  msubF_reg_memNode() {  _num_opnds = 4; _opnds = _opnd_array; init_flags(Flag_is_cisc_alternate | Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(msubF_reg_memNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "msubF_reg_mem";}
#endif
};

class msubD_reg_memNode : public MachNode { 
private:
  MachOper *_opnd_array[4];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return msubD_reg_mem_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_FmaD; }
  virtual uint           two_adr() const  { return oper_input_base(); }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  msubD_reg_memNode() {  _num_opnds = 4; _opnds = _opnd_array; init_flags(Flag_is_cisc_alternate | Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(msubD_reg_memNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "msubD_reg_mem";}
#endif
};

class maddF_mem_regNode : public MachNode { 
private:
  MachOper *_opnd_array[4];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return maddF_mem_reg_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_FmaF; }
  virtual uint           two_adr() const  { return oper_input_base(); }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  maddF_mem_regNode() {  _num_opnds = 4; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(maddF_mem_regNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "maddF_mem_reg";}
#endif
};

class maddD_mem_regNode : public MachNode { 
private:
  MachOper *_opnd_array[4];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return maddD_mem_reg_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_FmaD; }
  virtual uint           two_adr() const  { return oper_input_base(); }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  maddD_mem_regNode() {  _num_opnds = 4; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(maddD_mem_regNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "maddD_mem_reg";}
#endif
};

class msubF_mem_regNode : public MachNode { 
private:
  MachOper *_opnd_array[4];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return msubF_mem_reg_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_FmaF; }
  virtual uint           two_adr() const  { return oper_input_base(); }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  msubF_mem_regNode() {  _num_opnds = 4; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(msubF_mem_regNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "msubF_mem_reg";}
#endif
};

class msubD_mem_regNode : public MachNode { 
private:
  MachOper *_opnd_array[4];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return msubD_mem_reg_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_FmaD; }
  virtual uint           two_adr() const  { return oper_input_base(); }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  msubD_mem_regNode() {  _num_opnds = 4; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(msubD_mem_regNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "msubD_mem_reg";}
#endif
};

class divF_reg_regNode : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return divF_reg_reg_rule; }
private:
  const RegMask  *_cisc_RegMask;
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_DivF; }
  virtual uint           two_adr() const  { return oper_input_base(); }
  virtual int            cisc_operand() const { return 2; }
  virtual MachNode      *cisc_version(int offset);
  virtual void           use_cisc_RegMask();
  virtual const RegMask *cisc_RegMask() const { return _cisc_RegMask; }
public:
  divF_reg_regNode() { _cisc_RegMask = nullptr;  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(divF_reg_regNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "divF_reg_reg";}
#endif
};

class divF_reg_memNode : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return divF_reg_mem_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_DivF; }
  virtual uint           two_adr() const  { return oper_input_base(); }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  divF_reg_memNode() {  _num_opnds = 3; _opnds = _opnd_array; init_flags(Flag_is_cisc_alternate | Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(divF_reg_memNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "divF_reg_mem";}
#endif
};

class divD_reg_regNode : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return divD_reg_reg_rule; }
private:
  const RegMask  *_cisc_RegMask;
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_DivD; }
  virtual uint           two_adr() const  { return oper_input_base(); }
  virtual int            cisc_operand() const { return 2; }
  virtual MachNode      *cisc_version(int offset);
  virtual void           use_cisc_RegMask();
  virtual const RegMask *cisc_RegMask() const { return _cisc_RegMask; }
public:
  divD_reg_regNode() { _cisc_RegMask = nullptr;  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(divD_reg_regNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "divD_reg_reg";}
#endif
};

class divD_reg_memNode : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return divD_reg_mem_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_DivD; }
  virtual uint           two_adr() const  { return oper_input_base(); }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  divD_reg_memNode() {  _num_opnds = 3; _opnds = _opnd_array; init_flags(Flag_is_cisc_alternate | Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(divD_reg_memNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "divD_reg_mem";}
#endif
};

class absF_regNode : public MachNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return absF_reg_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_AbsF; }
public:
  absF_regNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(absF_regNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "absF_reg";}
#endif
};

class absD_regNode : public MachNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return absD_reg_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_AbsD; }
public:
  absD_regNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(absD_regNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "absD_reg";}
#endif
};

class nabsF_regNode : public MachNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return nabsF_reg_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_NegF; }
public:
  nabsF_regNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(nabsF_regNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "nabsF_reg";}
#endif
};

class nabsD_regNode : public MachNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return nabsD_reg_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_NegD; }
public:
  nabsD_regNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(nabsD_regNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "nabsD_reg";}
#endif
};

class negF_regNode : public MachNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return negF_reg_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_NegF; }
public:
  negF_regNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(negF_regNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "negF_reg";}
#endif
};

class negD_regNode : public MachNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return negD_reg_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_NegD; }
public:
  negD_regNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(negD_regNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "negD_reg";}
#endif
};

class sqrtF_regNode : public MachNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return sqrtF_reg_rule; }
private:
  const RegMask  *_cisc_RegMask;
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_SqrtF; }
  virtual int            cisc_operand() const { return 1; }
  virtual MachNode      *cisc_version(int offset);
  virtual void           use_cisc_RegMask();
  virtual const RegMask *cisc_RegMask() const { return _cisc_RegMask; }
public:
  sqrtF_regNode() { _cisc_RegMask = nullptr;  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(sqrtF_regNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "sqrtF_reg";}
#endif
};

class sqrtD_regNode : public MachNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return sqrtD_reg_rule; }
private:
  const RegMask  *_cisc_RegMask;
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_SqrtD; }
  virtual int            cisc_operand() const { return 1; }
  virtual MachNode      *cisc_version(int offset);
  virtual void           use_cisc_RegMask();
  virtual const RegMask *cisc_RegMask() const { return _cisc_RegMask; }
public:
  sqrtD_regNode() { _cisc_RegMask = nullptr;  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(sqrtD_regNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "sqrtD_reg";}
#endif
};

class sqrtF_memNode : public MachNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return sqrtF_mem_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_SqrtF; }
  virtual int            reloc() const;
public:
  sqrtF_memNode() {  _num_opnds = 2; _opnds = _opnd_array; init_flags(Flag_is_cisc_alternate | Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(sqrtF_memNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "sqrtF_mem";}
#endif
};

class sqrtD_memNode : public MachNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return sqrtD_mem_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_SqrtD; }
  virtual int            reloc() const;
public:
  sqrtD_memNode() {  _num_opnds = 2; _opnds = _opnd_array; init_flags(Flag_is_cisc_alternate | Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(sqrtD_memNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "sqrtD_mem";}
#endif
};

class andI_reg_regNode : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return andI_reg_reg_rule; }
private:
  const RegMask  *_cisc_RegMask;
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_AndI; }
  virtual uint           two_adr() const  { return oper_input_base(); }
  virtual int            cisc_operand() const { return 2; }
  virtual MachNode      *cisc_version(int offset);
  virtual void           use_cisc_RegMask();
  virtual const RegMask *cisc_RegMask() const { return _cisc_RegMask; }
public:
  andI_reg_regNode() { _cisc_RegMask = nullptr;  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(andI_reg_regNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "andI_reg_reg";}
#endif
};

class andI_Reg_memNode : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return andI_Reg_mem_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_AndI; }
  virtual uint           two_adr() const  { return oper_input_base(); }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  andI_Reg_memNode() {  _num_opnds = 3; _opnds = _opnd_array; init_flags(Flag_is_cisc_alternate | Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(andI_Reg_memNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "andI_Reg_mem";}
#endif
};

class andI_Reg_mem_0Node : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return andI_Reg_mem_0_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_AndI; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges(); }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  andI_Reg_mem_0Node() {  _num_opnds = 3; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(andI_Reg_mem_0Node); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "andI_Reg_mem_0";}
#endif
};

class andI_reg_uimm32Node : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return andI_reg_uimm32_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_AndI; }
  virtual uint           two_adr() const  { return oper_input_base(); }
public:
  andI_reg_uimm32Node() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(andI_reg_uimm32Node); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "andI_reg_uimm32";}
#endif
};

class andI_reg_uimmI_LH1Node : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return andI_reg_uimmI_LH1_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_AndI; }
  virtual uint           two_adr() const  { return oper_input_base(); }
public:
  andI_reg_uimmI_LH1Node() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(andI_reg_uimmI_LH1Node); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "andI_reg_uimmI_LH1";}
#endif
};

class andI_reg_uimmI_LL1Node : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return andI_reg_uimmI_LL1_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_AndI; }
  virtual uint           two_adr() const  { return oper_input_base(); }
public:
  andI_reg_uimmI_LL1Node() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(andI_reg_uimmI_LL1Node); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "andI_reg_uimmI_LL1";}
#endif
};

class andL_reg_regNode : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return andL_reg_reg_rule; }
private:
  const RegMask  *_cisc_RegMask;
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_AndL; }
  virtual uint           two_adr() const  { return oper_input_base(); }
  virtual int            cisc_operand() const { return 2; }
  virtual MachNode      *cisc_version(int offset);
  virtual void           use_cisc_RegMask();
  virtual const RegMask *cisc_RegMask() const { return _cisc_RegMask; }
public:
  andL_reg_regNode() { _cisc_RegMask = nullptr;  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(andL_reg_regNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "andL_reg_reg";}
#endif
};

class andL_Reg_memNode : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return andL_Reg_mem_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_AndL; }
  virtual uint           two_adr() const  { return oper_input_base(); }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  andL_Reg_memNode() {  _num_opnds = 3; _opnds = _opnd_array; init_flags(Flag_is_cisc_alternate | Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(andL_Reg_memNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "andL_Reg_mem";}
#endif
};

class andL_Reg_mem_0Node : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return andL_Reg_mem_0_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_AndL; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges(); }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  andL_Reg_mem_0Node() {  _num_opnds = 3; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(andL_Reg_mem_0Node); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "andL_Reg_mem_0";}
#endif
};

class andL_reg_uimmL_LL1Node : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return andL_reg_uimmL_LL1_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_AndL; }
  virtual uint           two_adr() const  { return oper_input_base(); }
public:
  andL_reg_uimmL_LL1Node() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(andL_reg_uimmL_LL1Node); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "andL_reg_uimmL_LL1";}
#endif
};

class andL_reg_uimmL_LH1Node : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return andL_reg_uimmL_LH1_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_AndL; }
  virtual uint           two_adr() const  { return oper_input_base(); }
public:
  andL_reg_uimmL_LH1Node() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(andL_reg_uimmL_LH1Node); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "andL_reg_uimmL_LH1";}
#endif
};

class andL_reg_uimmL_HL1Node : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return andL_reg_uimmL_HL1_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_AndL; }
  virtual uint           two_adr() const  { return oper_input_base(); }
public:
  andL_reg_uimmL_HL1Node() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(andL_reg_uimmL_HL1Node); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "andL_reg_uimmL_HL1";}
#endif
};

class andL_reg_uimmL_HH1Node : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return andL_reg_uimmL_HH1_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_AndL; }
  virtual uint           two_adr() const  { return oper_input_base(); }
public:
  andL_reg_uimmL_HH1Node() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(andL_reg_uimmL_HH1Node); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "andL_reg_uimmL_HH1";}
#endif
};

class orI_reg_regNode : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return orI_reg_reg_rule; }
private:
  const RegMask  *_cisc_RegMask;
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_OrI; }
  virtual uint           two_adr() const  { return oper_input_base(); }
  virtual int            cisc_operand() const { return 2; }
  virtual MachNode      *cisc_version(int offset);
  virtual void           use_cisc_RegMask();
  virtual const RegMask *cisc_RegMask() const { return _cisc_RegMask; }
public:
  orI_reg_regNode() { _cisc_RegMask = nullptr;  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(orI_reg_regNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "orI_reg_reg";}
#endif
};

class orI_Reg_memNode : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return orI_Reg_mem_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_OrI; }
  virtual uint           two_adr() const  { return oper_input_base(); }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  orI_Reg_memNode() {  _num_opnds = 3; _opnds = _opnd_array; init_flags(Flag_is_cisc_alternate | Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(orI_Reg_memNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "orI_Reg_mem";}
#endif
};

class orI_Reg_mem_0Node : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return orI_Reg_mem_0_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_OrI; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges(); }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  orI_Reg_mem_0Node() {  _num_opnds = 3; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(orI_Reg_mem_0Node); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "orI_Reg_mem_0";}
#endif
};

class orI_reg_uimm16Node : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return orI_reg_uimm16_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_OrI; }
  virtual uint           two_adr() const  { return oper_input_base(); }
public:
  orI_reg_uimm16Node() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(orI_reg_uimm16Node); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "orI_reg_uimm16";}
#endif
};

class orI_reg_uimm32Node : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return orI_reg_uimm32_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_OrI; }
  virtual uint           two_adr() const  { return oper_input_base(); }
public:
  orI_reg_uimm32Node() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(orI_reg_uimm32Node); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "orI_reg_uimm32";}
#endif
};

class orL_reg_regNode : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return orL_reg_reg_rule; }
private:
  const RegMask  *_cisc_RegMask;
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_OrL; }
  virtual uint           two_adr() const  { return oper_input_base(); }
  virtual int            cisc_operand() const { return 2; }
  virtual MachNode      *cisc_version(int offset);
  virtual void           use_cisc_RegMask();
  virtual const RegMask *cisc_RegMask() const { return _cisc_RegMask; }
public:
  orL_reg_regNode() { _cisc_RegMask = nullptr;  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(orL_reg_regNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "orL_reg_reg";}
#endif
};

class orL_Reg_memNode : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return orL_Reg_mem_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_OrL; }
  virtual uint           two_adr() const  { return oper_input_base(); }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  orL_Reg_memNode() {  _num_opnds = 3; _opnds = _opnd_array; init_flags(Flag_is_cisc_alternate | Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(orL_Reg_memNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "orL_Reg_mem";}
#endif
};

class orL_Reg_mem_0Node : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return orL_Reg_mem_0_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_OrL; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges(); }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  orL_Reg_mem_0Node() {  _num_opnds = 3; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(orL_Reg_mem_0Node); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "orL_Reg_mem_0";}
#endif
};

class orL_reg_uimm16Node : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return orL_reg_uimm16_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_OrL; }
  virtual uint           two_adr() const  { return oper_input_base(); }
public:
  orL_reg_uimm16Node() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(orL_reg_uimm16Node); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "orL_reg_uimm16";}
#endif
};

class orL_reg_uimm32Node : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return orL_reg_uimm32_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_OrI; }
  virtual uint           two_adr() const  { return oper_input_base(); }
public:
  orL_reg_uimm32Node() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(orL_reg_uimm32Node); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "orL_reg_uimm32";}
#endif
};

class xorI_reg_regNode : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return xorI_reg_reg_rule; }
private:
  const RegMask  *_cisc_RegMask;
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_XorI; }
  virtual uint           two_adr() const  { return oper_input_base(); }
  virtual int            cisc_operand() const { return 2; }
  virtual MachNode      *cisc_version(int offset);
  virtual void           use_cisc_RegMask();
  virtual const RegMask *cisc_RegMask() const { return _cisc_RegMask; }
public:
  xorI_reg_regNode() { _cisc_RegMask = nullptr;  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(xorI_reg_regNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "xorI_reg_reg";}
#endif
};

class xorI_Reg_memNode : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return xorI_Reg_mem_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_XorI; }
  virtual uint           two_adr() const  { return oper_input_base(); }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  xorI_Reg_memNode() {  _num_opnds = 3; _opnds = _opnd_array; init_flags(Flag_is_cisc_alternate | Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(xorI_Reg_memNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "xorI_Reg_mem";}
#endif
};

class xorI_Reg_mem_0Node : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return xorI_Reg_mem_0_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_XorI; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges(); }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  xorI_Reg_mem_0Node() {  _num_opnds = 3; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(xorI_Reg_mem_0Node); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "xorI_Reg_mem_0";}
#endif
};

class xorI_reg_uimm32Node : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return xorI_reg_uimm32_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_XorI; }
  virtual uint           two_adr() const  { return oper_input_base(); }
public:
  xorI_reg_uimm32Node() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(xorI_reg_uimm32Node); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "xorI_reg_uimm32";}
#endif
};

class xorL_reg_regNode : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return xorL_reg_reg_rule; }
private:
  const RegMask  *_cisc_RegMask;
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_XorL; }
  virtual uint           two_adr() const  { return oper_input_base(); }
  virtual int            cisc_operand() const { return 2; }
  virtual MachNode      *cisc_version(int offset);
  virtual void           use_cisc_RegMask();
  virtual const RegMask *cisc_RegMask() const { return _cisc_RegMask; }
public:
  xorL_reg_regNode() { _cisc_RegMask = nullptr;  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(xorL_reg_regNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "xorL_reg_reg";}
#endif
};

class xorL_Reg_memNode : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return xorL_Reg_mem_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_XorL; }
  virtual uint           two_adr() const  { return oper_input_base(); }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  xorL_Reg_memNode() {  _num_opnds = 3; _opnds = _opnd_array; init_flags(Flag_is_cisc_alternate | Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(xorL_Reg_memNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "xorL_Reg_mem";}
#endif
};

class xorL_reg_uimm32Node : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return xorL_reg_uimm32_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_XorL; }
  virtual uint           two_adr() const  { return oper_input_base(); }
public:
  xorL_reg_uimm32Node() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(xorL_reg_uimm32Node); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "xorL_reg_uimm32";}
#endif
};

class convI2BNode : public MachNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return convI2B_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_Conv2B; }
public:
  convI2BNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(convI2BNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "convI2B";}
#endif
};

class convP2BNode : public MachNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return convP2B_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_Conv2B; }
  virtual int            reloc() const;
public:
  convP2BNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(convP2BNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "convP2B";}
#endif
};

class cmpLTMask_reg_regNode : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return cmpLTMask_reg_reg_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_CmpLTMask; }
  virtual uint           two_adr() const  { return oper_input_base(); }
public:
  cmpLTMask_reg_regNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(cmpLTMask_reg_regNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "cmpLTMask_reg_reg";}
#endif
};

class cmpLTMask_reg_zeroNode : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return cmpLTMask_reg_zero_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_CmpLTMask; }
  virtual uint           two_adr() const  { return oper_input_base(); }
public:
  cmpLTMask_reg_zeroNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(cmpLTMask_reg_zeroNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "cmpLTMask_reg_zero";}
#endif
};

class convD2F_regNode : public MachNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return convD2F_reg_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_ConvD2F; }
public:
  convD2F_regNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(convD2F_regNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "convD2F_reg";}
#endif
};

class convF2I_regNode : public MachNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return convF2I_reg_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_ConvF2I; }
public:
  convF2I_regNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(convF2I_regNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "convF2I_reg";}
#endif
};

class convD2I_regNode : public MachNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return convD2I_reg_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_ConvD2I; }
public:
  convD2I_regNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(convD2I_regNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "convD2I_reg";}
#endif
};

class convF2L_regNode : public MachNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return convF2L_reg_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_ConvF2L; }
public:
  convF2L_regNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(convF2L_regNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "convF2L_reg";}
#endif
};

class convD2L_regNode : public MachNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return convD2L_reg_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_ConvD2L; }
public:
  convD2L_regNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(convD2L_regNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "convD2L_reg";}
#endif
};

class convF2D_regNode : public MachNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return convF2D_reg_rule; }
private:
  const RegMask  *_cisc_RegMask;
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_ConvF2D; }
  virtual int            cisc_operand() const { return 1; }
  virtual MachNode      *cisc_version(int offset);
  virtual void           use_cisc_RegMask();
  virtual const RegMask *cisc_RegMask() const { return _cisc_RegMask; }
public:
  convF2D_regNode() { _cisc_RegMask = nullptr;  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(convF2D_regNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "convF2D_reg";}
#endif
};

class convF2D_memNode : public MachNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return convF2D_mem_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_ConvF2D; }
  virtual int            reloc() const;
public:
  convF2D_memNode() {  _num_opnds = 2; _opnds = _opnd_array; init_flags(Flag_is_cisc_alternate | Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(convF2D_memNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "convF2D_mem";}
#endif
};

class convI2D_regNode : public MachNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return convI2D_reg_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_ConvI2D; }
public:
  convI2D_regNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(convI2D_regNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "convI2D_reg";}
#endif
};

class convI2F_iregNode : public MachNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return convI2F_ireg_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_ConvI2F; }
public:
  convI2F_iregNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(convI2F_iregNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "convI2F_ireg";}
#endif
};

class convI2L_regNode : public MachNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return convI2L_reg_rule; }
private:
  const RegMask  *_cisc_RegMask;
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_ConvI2L; }
  virtual int            cisc_operand() const { return 1; }
  virtual MachNode      *cisc_version(int offset);
  virtual void           use_cisc_RegMask();
  virtual const RegMask *cisc_RegMask() const { return _cisc_RegMask; }
public:
  convI2L_regNode() { _cisc_RegMask = nullptr;  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(convI2L_regNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "convI2L_reg";}
#endif
};

class convI2L_reg_zexNode : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return convI2L_reg_zex_rule; }
private:
  const RegMask  *_cisc_RegMask;
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_AndL; }
  virtual int            cisc_operand() const { return 1; }
  virtual MachNode      *cisc_version(int offset);
  virtual void           use_cisc_RegMask();
  virtual const RegMask *cisc_RegMask() const { return _cisc_RegMask; }
public:
  convI2L_reg_zexNode() { _cisc_RegMask = nullptr;  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(convI2L_reg_zexNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "convI2L_reg_zex";}
#endif
};

class convI2L_mem_zexNode : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return convI2L_mem_zex_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_AndL; }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  convI2L_mem_zexNode() {  _num_opnds = 3; _opnds = _opnd_array; init_flags(Flag_is_cisc_alternate | Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(convI2L_mem_zexNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "convI2L_mem_zex";}
#endif
};

class zeroExtend_longNode : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return zeroExtend_long_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_AndL; }
public:
  zeroExtend_longNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(zeroExtend_longNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "zeroExtend_long";}
#endif
};

class rShiftI16_lShiftI16_regNode : public MachNode { 
private:
  MachOper *_opnd_array[4];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return rShiftI16_lShiftI16_reg_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_RShiftI; }
public:
  rShiftI16_lShiftI16_regNode() {  _num_opnds = 4; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(rShiftI16_lShiftI16_regNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "rShiftI16_lShiftI16_reg";}
#endif
};

class rShiftI24_lShiftI24_regNode : public MachNode { 
private:
  MachOper *_opnd_array[4];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return rShiftI24_lShiftI24_reg_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_RShiftI; }
public:
  rShiftI24_lShiftI24_regNode() {  _num_opnds = 4; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(rShiftI24_lShiftI24_regNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "rShiftI24_lShiftI24_reg";}
#endif
};

class MoveF2I_stack_regNode : public MachNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return MoveF2I_stack_reg_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_MoveF2I; }
public:
  MoveF2I_stack_regNode() {  _num_opnds = 2; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(MoveF2I_stack_regNode); }
  // Rematerialize MoveF2I_stack_reg
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "MoveF2I_stack_reg";}
#endif
};

class MoveI2F_stack_regNode : public MachNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return MoveI2F_stack_reg_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_MoveI2F; }
public:
  MoveI2F_stack_regNode() {  _num_opnds = 2; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(MoveI2F_stack_regNode); }
  // Rematerialize MoveI2F_stack_reg
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "MoveI2F_stack_reg";}
#endif
};

class MoveD2L_stack_regNode : public MachNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return MoveD2L_stack_reg_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_MoveD2L; }
public:
  MoveD2L_stack_regNode() {  _num_opnds = 2; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(MoveD2L_stack_regNode); }
  // Rematerialize MoveD2L_stack_reg
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "MoveD2L_stack_reg";}
#endif
};

class MoveL2D_stack_regNode : public MachNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return MoveL2D_stack_reg_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_MoveL2D; }
public:
  MoveL2D_stack_regNode() {  _num_opnds = 2; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(MoveL2D_stack_regNode); }
  // Rematerialize MoveL2D_stack_reg
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "MoveL2D_stack_reg";}
#endif
};

class MoveI2F_reg_stackNode : public MachNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return MoveI2F_reg_stack_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_MoveI2F; }
public:
  MoveI2F_reg_stackNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(MoveI2F_reg_stackNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "MoveI2F_reg_stack";}
#endif
};

class MoveD2L_reg_stackNode : public MachNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return MoveD2L_reg_stack_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_MoveD2L; }
public:
  MoveD2L_reg_stackNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(MoveD2L_reg_stackNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "MoveD2L_reg_stack";}
#endif
};

class MoveL2D_reg_stackNode : public MachNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return MoveL2D_reg_stack_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_MoveL2D; }
public:
  MoveL2D_reg_stackNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(MoveL2D_reg_stackNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "MoveL2D_reg_stack";}
#endif
};

class convL2F_regNode : public MachNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return convL2F_reg_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_ConvL2F; }
public:
  convL2F_regNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(convL2F_regNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "convL2F_reg";}
#endif
};

class convL2D_regNode : public MachNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return convL2D_reg_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_ConvL2D; }
public:
  convL2D_regNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(convL2D_regNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "convL2D_reg";}
#endif
};

class convL2I_regNode : public MachNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return convL2I_reg_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_ConvL2I; }
public:
  convL2I_regNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(convL2I_regNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "convL2I_reg";}
#endif
};

class shrL_reg_imm6_L2INode : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return shrL_reg_imm6_L2I_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_ConvL2I; }
public:
  shrL_reg_imm6_L2INode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(shrL_reg_imm6_L2INode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "shrL_reg_imm6_L2I";}
#endif
};

class rangeCheck_iReg_uimmI16Node : public MachIfNode { 
private:
  MachOper *_opnd_array[5];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return rangeCheck_iReg_uimmI16_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           label_set( Label* label, uint block_num );
  virtual void           save_label( Label** label, uint* block_num );
  virtual bool           is_TrapBasedCheckNode() const { return true; }
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_If; }
  virtual void           negate() { 
    opnd_array(1)->negate();
    _prob = 1.0f - _prob;
  };
  virtual uint           oper_input_base() const { return 1; }
public:
  rangeCheck_iReg_uimmI16Node() {  _num_opnds = 5; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(rangeCheck_iReg_uimmI16Node); }
  virtual bool           pinned() const { return true; }
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  const Type            *bottom_type() const { return TypeTuple::IFBOTH; } // matched IfNode
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "rangeCheck_iReg_uimmI16";}
#endif
};

class rangeCheck_iReg_iRegNode : public MachIfNode { 
private:
  MachOper *_opnd_array[5];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return rangeCheck_iReg_iReg_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           label_set( Label* label, uint block_num );
  virtual void           save_label( Label** label, uint* block_num );
  virtual bool           is_TrapBasedCheckNode() const { return true; }
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_If; }
  virtual void           negate() { 
    opnd_array(1)->negate();
    _prob = 1.0f - _prob;
  };
  virtual uint           oper_input_base() const { return 1; }
public:
  rangeCheck_iReg_iRegNode() {  _num_opnds = 5; _opnds = _opnd_array; init_flags(Flag_may_be_short_branch); }
  virtual uint           size_of() const { return sizeof(rangeCheck_iReg_iRegNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  virtual bool           pinned() const { return true; }
  friend MachNode *State::MachNodeGenerator(int opcode);
  virtual MachNode      *short_branch_version();
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  const Type            *bottom_type() const { return TypeTuple::IFBOTH; } // matched IfNode
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "rangeCheck_iReg_iReg";}
#endif
};

class rangeCheck_uimmI16_iRegNode : public MachIfNode { 
private:
  MachOper *_opnd_array[5];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return rangeCheck_uimmI16_iReg_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           label_set( Label* label, uint block_num );
  virtual void           save_label( Label** label, uint* block_num );
  virtual bool           is_TrapBasedCheckNode() const { return true; }
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_If; }
  virtual void           negate() { 
    opnd_array(1)->negate();
    _prob = 1.0f - _prob;
  };
  virtual uint           oper_input_base() const { return 1; }
public:
  rangeCheck_uimmI16_iRegNode() {  _num_opnds = 5; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(rangeCheck_uimmI16_iRegNode); }
  virtual bool           pinned() const { return true; }
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  const Type            *bottom_type() const { return TypeTuple::IFBOTH; } // matched IfNode
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "rangeCheck_uimmI16_iReg";}
#endif
};

class zeroCheckP_iReg_imm0Node : public MachIfNode { 
private:
  MachOper *_opnd_array[5];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return zeroCheckP_iReg_imm0_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           label_set( Label* label, uint block_num );
  virtual void           save_label( Label** label, uint* block_num );
  virtual bool           is_TrapBasedCheckNode() const { return true; }
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_If; }
  virtual void           negate() { 
    opnd_array(1)->negate();
    _prob = 1.0f - _prob;
  };
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 1; }
public:
  zeroCheckP_iReg_imm0Node() {  _num_opnds = 5; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(zeroCheckP_iReg_imm0Node); }
  virtual bool           pinned() const { return true; }
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  const Type            *bottom_type() const { return TypeTuple::IFBOTH; } // matched IfNode
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "zeroCheckP_iReg_imm0";}
#endif
};

class zeroCheckN_iReg_imm0Node : public MachIfNode { 
private:
  MachOper *_opnd_array[5];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return zeroCheckN_iReg_imm0_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           label_set( Label* label, uint block_num );
  virtual void           save_label( Label** label, uint* block_num );
  virtual bool           is_TrapBasedCheckNode() const { return true; }
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_If; }
  virtual void           negate() { 
    opnd_array(1)->negate();
    _prob = 1.0f - _prob;
  };
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 1; }
public:
  zeroCheckN_iReg_imm0Node() {  _num_opnds = 5; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(zeroCheckN_iReg_imm0Node); }
  virtual bool           pinned() const { return true; }
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  const Type            *bottom_type() const { return TypeTuple::IFBOTH; } // matched IfNode
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "zeroCheckN_iReg_imm0";}
#endif
};

class compI_reg_regNode : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return compI_reg_reg_rule; }
private:
  const RegMask  *_cisc_RegMask;
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_CmpI; }
  virtual int            cisc_operand() const { return 2; }
  virtual MachNode      *cisc_version(int offset);
  virtual void           use_cisc_RegMask();
  virtual const RegMask *cisc_RegMask() const { return _cisc_RegMask; }
public:
  compI_reg_regNode() { _cisc_RegMask = nullptr;  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(compI_reg_regNode); }
  // Rematerialize compI_reg_reg
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "compI_reg_reg";}
#endif
};

class compI_reg_immNode : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return compI_reg_imm_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_CmpI; }
public:
  compI_reg_immNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(compI_reg_immNode); }
  // Rematerialize compI_reg_imm
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "compI_reg_imm";}
#endif
};

class compI_reg_imm16Node : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return compI_reg_imm16_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_CmpI; }
public:
  compI_reg_imm16Node() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(compI_reg_imm16Node); }
  // Rematerialize compI_reg_imm16
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "compI_reg_imm16";}
#endif
};

class compI_reg_imm0Node : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return compI_reg_imm0_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_CmpI; }
public:
  compI_reg_imm0Node() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(compI_reg_imm0Node); }
  // Rematerialize compI_reg_imm0
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "compI_reg_imm0";}
#endif
};

class compI_reg_memNode : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return compI_reg_mem_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_CmpI; }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  compI_reg_memNode() {  _num_opnds = 3; _opnds = _opnd_array; init_flags(Flag_is_cisc_alternate | Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(compI_reg_memNode); }
  // Rematerialize compI_reg_mem
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "compI_reg_mem";}
#endif
};

class compU_reg_regNode : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return compU_reg_reg_rule; }
private:
  const RegMask  *_cisc_RegMask;
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_CmpU; }
  virtual int            cisc_operand() const { return 2; }
  virtual MachNode      *cisc_version(int offset);
  virtual void           use_cisc_RegMask();
  virtual const RegMask *cisc_RegMask() const { return _cisc_RegMask; }
public:
  compU_reg_regNode() { _cisc_RegMask = nullptr;  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(compU_reg_regNode); }
  // Rematerialize compU_reg_reg
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "compU_reg_reg";}
#endif
};

class compU_reg_uimmNode : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return compU_reg_uimm_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_CmpU; }
public:
  compU_reg_uimmNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(compU_reg_uimmNode); }
  // Rematerialize compU_reg_uimm
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "compU_reg_uimm";}
#endif
};

class compU_reg_memNode : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return compU_reg_mem_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_CmpU; }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  compU_reg_memNode() {  _num_opnds = 3; _opnds = _opnd_array; init_flags(Flag_is_cisc_alternate | Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(compU_reg_memNode); }
  // Rematerialize compU_reg_mem
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "compU_reg_mem";}
#endif
};

class compL_reg_regNode : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return compL_reg_reg_rule; }
private:
  const RegMask  *_cisc_RegMask;
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_CmpL; }
  virtual int            cisc_operand() const { return 2; }
  virtual MachNode      *cisc_version(int offset);
  virtual void           use_cisc_RegMask();
  virtual const RegMask *cisc_RegMask() const { return _cisc_RegMask; }
public:
  compL_reg_regNode() { _cisc_RegMask = nullptr;  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(compL_reg_regNode); }
  // Rematerialize compL_reg_reg
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "compL_reg_reg";}
#endif
};

class compL_reg_regINode : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return compL_reg_regI_rule; }
private:
  const RegMask  *_cisc_RegMask;
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_CmpL; }
  virtual int            cisc_operand() const { return 2; }
  virtual MachNode      *cisc_version(int offset);
  virtual void           use_cisc_RegMask();
  virtual const RegMask *cisc_RegMask() const { return _cisc_RegMask; }
public:
  compL_reg_regINode() { _cisc_RegMask = nullptr;  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(compL_reg_regINode); }
  // Rematerialize compL_reg_regI
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "compL_reg_regI";}
#endif
};

class compL_reg_imm32Node : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return compL_reg_imm32_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_CmpL; }
public:
  compL_reg_imm32Node() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(compL_reg_imm32Node); }
  // Rematerialize compL_reg_imm32
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "compL_reg_imm32";}
#endif
};

class compL_reg_imm16Node : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return compL_reg_imm16_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_CmpL; }
public:
  compL_reg_imm16Node() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(compL_reg_imm16Node); }
  // Rematerialize compL_reg_imm16
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "compL_reg_imm16";}
#endif
};

class compL_reg_imm0Node : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return compL_reg_imm0_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_CmpL; }
public:
  compL_reg_imm0Node() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(compL_reg_imm0Node); }
  // Rematerialize compL_reg_imm0
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "compL_reg_imm0";}
#endif
};

class compL_conv_reg_imm0Node : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return compL_conv_reg_imm0_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_CmpL; }
public:
  compL_conv_reg_imm0Node() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(compL_conv_reg_imm0Node); }
  // Rematerialize compL_conv_reg_imm0
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "compL_conv_reg_imm0";}
#endif
};

class compL_reg_memNode : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return compL_reg_mem_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_CmpL; }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  compL_reg_memNode() {  _num_opnds = 3; _opnds = _opnd_array; init_flags(Flag_is_cisc_alternate | Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(compL_reg_memNode); }
  // Rematerialize compL_reg_mem
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "compL_reg_mem";}
#endif
};

class compL_reg_memINode : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return compL_reg_memI_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_CmpL; }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  compL_reg_memINode() {  _num_opnds = 3; _opnds = _opnd_array; init_flags(Flag_is_cisc_alternate | Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(compL_reg_memINode); }
  // Rematerialize compL_reg_memI
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "compL_reg_memI";}
#endif
};

class compUL_reg_regNode : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return compUL_reg_reg_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_CmpUL; }
public:
  compUL_reg_regNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(compUL_reg_regNode); }
  // Rematerialize compUL_reg_reg
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "compUL_reg_reg";}
#endif
};

class compUL_reg_imm32Node : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return compUL_reg_imm32_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_CmpUL; }
public:
  compUL_reg_imm32Node() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(compUL_reg_imm32Node); }
  // Rematerialize compUL_reg_imm32
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "compUL_reg_imm32";}
#endif
};

class compP_reg_regNode : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return compP_reg_reg_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_CmpP; }
  virtual int            reloc() const;
public:
  compP_reg_regNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(compP_reg_regNode); }
  // Rematerialize compP_reg_reg
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "compP_reg_reg";}
#endif
};

class compP_reg_imm0Node : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return compP_reg_imm0_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_CmpP; }
  virtual int            reloc() const;
public:
  compP_reg_imm0Node() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(compP_reg_imm0Node); }
  // Rematerialize compP_reg_imm0
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "compP_reg_imm0";}
#endif
};

class compP_decode_reg_imm0Node : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return compP_decode_reg_imm0_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_CmpP; }
  virtual int            reloc() const;
public:
  compP_decode_reg_imm0Node() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(compP_decode_reg_imm0Node); }
  // Rematerialize compP_decode_reg_imm0
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "compP_decode_reg_imm0";}
#endif
};

class compP_reg_memNode : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return compP_reg_mem_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_CmpP; }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  compP_reg_memNode() {  _num_opnds = 3; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(compP_reg_memNode); }
  // Rematerialize compP_reg_mem
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "compP_reg_mem";}
#endif
};

class z196_minI_reg_regNode : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return z196_minI_reg_reg_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_MinI; }
public:
  z196_minI_reg_regNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(z196_minI_reg_regNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "z196_minI_reg_reg";}
#endif
};

class z10_minI_reg_regNode : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return z10_minI_reg_reg_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_MinI; }
public:
  z10_minI_reg_regNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(z10_minI_reg_regNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "z10_minI_reg_reg";}
#endif
};

class minI_reg_regNode : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return minI_reg_reg_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_MinI; }
public:
  minI_reg_regNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(minI_reg_regNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "minI_reg_reg";}
#endif
};

class z196_minI_reg_imm32Node : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return z196_minI_reg_imm32_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_MinI; }
public:
  z196_minI_reg_imm32Node() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(z196_minI_reg_imm32Node); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "z196_minI_reg_imm32";}
#endif
};

class minI_reg_imm32Node : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return minI_reg_imm32_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_MinI; }
public:
  minI_reg_imm32Node() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(minI_reg_imm32Node); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "minI_reg_imm32";}
#endif
};

class z196_minI_reg_imm16Node : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return z196_minI_reg_imm16_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_MinI; }
public:
  z196_minI_reg_imm16Node() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(z196_minI_reg_imm16Node); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "z196_minI_reg_imm16";}
#endif
};

class minI_reg_imm16Node : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return minI_reg_imm16_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_MinI; }
public:
  minI_reg_imm16Node() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(minI_reg_imm16Node); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "minI_reg_imm16";}
#endif
};

class z10_minI_reg_imm8Node : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return z10_minI_reg_imm8_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_MinI; }
public:
  z10_minI_reg_imm8Node() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(z10_minI_reg_imm8Node); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "z10_minI_reg_imm8";}
#endif
};

class z196_maxI_reg_regNode : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return z196_maxI_reg_reg_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_MaxI; }
public:
  z196_maxI_reg_regNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(z196_maxI_reg_regNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "z196_maxI_reg_reg";}
#endif
};

class z10_maxI_reg_regNode : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return z10_maxI_reg_reg_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_MaxI; }
public:
  z10_maxI_reg_regNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(z10_maxI_reg_regNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "z10_maxI_reg_reg";}
#endif
};

class maxI_reg_regNode : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return maxI_reg_reg_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_MaxI; }
public:
  maxI_reg_regNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(maxI_reg_regNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "maxI_reg_reg";}
#endif
};

class z196_maxI_reg_imm32Node : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return z196_maxI_reg_imm32_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_MaxI; }
public:
  z196_maxI_reg_imm32Node() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(z196_maxI_reg_imm32Node); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "z196_maxI_reg_imm32";}
#endif
};

class maxI_reg_imm32Node : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return maxI_reg_imm32_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_MaxI; }
public:
  maxI_reg_imm32Node() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(maxI_reg_imm32Node); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "maxI_reg_imm32";}
#endif
};

class z196_maxI_reg_imm16Node : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return z196_maxI_reg_imm16_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_MaxI; }
public:
  z196_maxI_reg_imm16Node() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(z196_maxI_reg_imm16Node); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "z196_maxI_reg_imm16";}
#endif
};

class maxI_reg_imm16Node : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return maxI_reg_imm16_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_MaxI; }
public:
  maxI_reg_imm16Node() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(maxI_reg_imm16Node); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "maxI_reg_imm16";}
#endif
};

class z10_maxI_reg_imm8Node : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return z10_maxI_reg_imm8_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_MaxI; }
public:
  z10_maxI_reg_imm8Node() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(z10_maxI_reg_imm8Node); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "z10_maxI_reg_imm8";}
#endif
};

class absI_regNode : public MachNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return absI_reg_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_AbsI; }
public:
  absI_regNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(absI_regNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "absI_reg";}
#endif
};

class absL_regNode : public MachNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return absL_reg_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_AbsL; }
public:
  absL_regNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(absL_regNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "absL_reg";}
#endif
};

class negabsI_regNode : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return negabsI_reg_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_SubI; }
public:
  negabsI_regNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(negabsI_regNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "negabsI_reg";}
#endif
};

class cmpF_ccNode : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return cmpF_cc_rule; }
private:
  const RegMask  *_cisc_RegMask;
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_CmpF; }
  virtual int            cisc_operand() const { return 2; }
  virtual MachNode      *cisc_version(int offset);
  virtual void           use_cisc_RegMask();
  virtual const RegMask *cisc_RegMask() const { return _cisc_RegMask; }
public:
  cmpF_ccNode() { _cisc_RegMask = nullptr;  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(cmpF_ccNode); }
  // Rematerialize cmpF_cc
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "cmpF_cc";}
#endif
};

class cmpD_ccNode : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return cmpD_cc_rule; }
private:
  const RegMask  *_cisc_RegMask;
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_CmpD; }
  virtual int            cisc_operand() const { return 2; }
  virtual MachNode      *cisc_version(int offset);
  virtual void           use_cisc_RegMask();
  virtual const RegMask *cisc_RegMask() const { return _cisc_RegMask; }
public:
  cmpD_ccNode() { _cisc_RegMask = nullptr;  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(cmpD_ccNode); }
  // Rematerialize cmpD_cc
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "cmpD_cc";}
#endif
};

class cmpF_cc_memNode : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return cmpF_cc_mem_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_CmpF; }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  cmpF_cc_memNode() {  _num_opnds = 3; _opnds = _opnd_array; init_flags(Flag_is_cisc_alternate | Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(cmpF_cc_memNode); }
  // Rematerialize cmpF_cc_mem
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "cmpF_cc_mem";}
#endif
};

class cmpD_cc_memNode : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return cmpD_cc_mem_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_CmpD; }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  cmpD_cc_memNode() {  _num_opnds = 3; _opnds = _opnd_array; init_flags(Flag_is_cisc_alternate | Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(cmpD_cc_memNode); }
  // Rematerialize cmpD_cc_mem
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "cmpD_cc_mem";}
#endif
};

class cmpF0_ccNode : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return cmpF0_cc_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_CmpF; }
  virtual int            reloc() const;
public:
  cmpF0_ccNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(cmpF0_ccNode); }
  // Rematerialize cmpF0_cc
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "cmpF0_cc";}
#endif
};

class cmpD0_ccNode : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return cmpD0_cc_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_CmpD; }
  virtual int            reloc() const;
public:
  cmpD0_ccNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(cmpD0_ccNode); }
  // Rematerialize cmpD0_cc
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "cmpD0_cc";}
#endif
};

class cmpF_regNode : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return cmpF_reg_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_CmpF3; }
public:
  cmpF_regNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(cmpF_regNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "cmpF_reg";}
#endif
};

class cmpD_regNode : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return cmpD_reg_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_CmpD3; }
public:
  cmpD_regNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(cmpD_regNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "cmpD_reg";}
#endif
};

class branchNode : public MachGotoNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return branch_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           label_set( Label* label, uint block_num );
  virtual void           save_label( Label** label, uint* block_num );
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_Goto; }
  virtual uint           oper_input_base() const { return 1; }
public:
  branchNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(branchNode); }
  virtual bool           pinned() const { return true; }
  virtual const Node *is_block_proj() const { return this; }
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "branch";}
#endif
};

class branchFarNode : public MachGotoNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return branchFar_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           label_set( Label* label, uint block_num );
  virtual void           save_label( Label** label, uint* block_num );
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_Goto; }
  virtual uint           oper_input_base() const { return 1; }
public:
  branchFarNode() {  _num_opnds = 2; _opnds = _opnd_array; init_flags(Flag_may_be_short_branch); }
  virtual uint           size_of() const { return sizeof(branchFarNode); }
  virtual bool           pinned() const { return true; }
  virtual const Node *is_block_proj() const { return this; }
  friend MachNode *State::MachNodeGenerator(int opcode);
  virtual MachNode      *short_branch_version();
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "branchFar";}
#endif
};

class branchConNode : public MachIfNode { 
private:
  MachOper *_opnd_array[4];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return branchCon_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           label_set( Label* label, uint block_num );
  virtual void           save_label( Label** label, uint* block_num );
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_If; }
  virtual void           negate() { 
    opnd_array(1)->negate();
    _prob = 1.0f - _prob;
  };
  virtual uint           oper_input_base() const { return 1; }
public:
  branchConNode() {  _num_opnds = 4; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(branchConNode); }
  virtual bool           pinned() const { return true; }
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  const Type            *bottom_type() const { return TypeTuple::IFBOTH; } // matched IfNode
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "branchCon";}
#endif
};

class branchConFarNode : public MachIfNode { 
private:
  MachOper *_opnd_array[4];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return branchConFar_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           label_set( Label* label, uint block_num );
  virtual void           save_label( Label** label, uint* block_num );
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_If; }
  virtual void           negate() { 
    opnd_array(1)->negate();
    _prob = 1.0f - _prob;
  };
  virtual uint           oper_input_base() const { return 1; }
public:
  branchConFarNode() {  _num_opnds = 4; _opnds = _opnd_array; init_flags(Flag_may_be_short_branch); }
  virtual uint           size_of() const { return sizeof(branchConFarNode); }
  virtual bool           pinned() const { return true; }
  friend MachNode *State::MachNodeGenerator(int opcode);
  virtual MachNode      *short_branch_version();
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  const Type            *bottom_type() const { return TypeTuple::IFBOTH; } // matched IfNode
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "branchConFar";}
#endif
};

class branchLoopEndNode : public MachIfNode { 
private:
  MachOper *_opnd_array[4];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return branchLoopEnd_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           label_set( Label* label, uint block_num );
  virtual void           save_label( Label** label, uint* block_num );
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_CountedLoopEnd; }
  virtual void           negate() { 
    opnd_array(1)->negate();
    _prob = 1.0f - _prob;
  };
  virtual uint           oper_input_base() const { return 1; }
public:
  branchLoopEndNode() {  _num_opnds = 4; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(branchLoopEndNode); }
  virtual bool           pinned() const { return true; }
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  const Type            *bottom_type() const { return TypeTuple::IFBOTH; } // matched IfNode
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "branchLoopEnd";}
#endif
};

class branchLoopEndFarNode : public MachIfNode { 
private:
  MachOper *_opnd_array[4];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return branchLoopEndFar_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           label_set( Label* label, uint block_num );
  virtual void           save_label( Label** label, uint* block_num );
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_CountedLoopEnd; }
  virtual void           negate() { 
    opnd_array(1)->negate();
    _prob = 1.0f - _prob;
  };
  virtual uint           oper_input_base() const { return 1; }
public:
  branchLoopEndFarNode() {  _num_opnds = 4; _opnds = _opnd_array; init_flags(Flag_may_be_short_branch); }
  virtual uint           size_of() const { return sizeof(branchLoopEndFarNode); }
  virtual bool           pinned() const { return true; }
  friend MachNode *State::MachNodeGenerator(int opcode);
  virtual MachNode      *short_branch_version();
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  const Type            *bottom_type() const { return TypeTuple::IFBOTH; } // matched IfNode
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "branchLoopEndFar";}
#endif
};

class testAndBranchLoopEnd_RegNode : public MachIfNode { 
private:
  MachOper *_opnd_array[5];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return testAndBranchLoopEnd_Reg_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           label_set( Label* label, uint block_num );
  virtual void           save_label( Label** label, uint* block_num );
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_CountedLoopEnd; }
  virtual void           negate() { 
    opnd_array(1)->negate();
    _prob = 1.0f - _prob;
  };
  virtual uint           oper_input_base() const { return 1; }
public:
  testAndBranchLoopEnd_RegNode() {  _num_opnds = 5; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(testAndBranchLoopEnd_RegNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  virtual bool           pinned() const { return true; }
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  const Type            *bottom_type() const { return TypeTuple::IFBOTH; } // matched IfNode
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "testAndBranchLoopEnd_Reg";}
#endif
};

class cmpb_RegINode : public MachIfNode { 
private:
  MachOper *_opnd_array[5];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return cmpb_RegI_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           label_set( Label* label, uint block_num );
  virtual void           save_label( Label** label, uint* block_num );
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_If; }
  virtual void           negate() { 
    opnd_array(1)->negate();
    _prob = 1.0f - _prob;
  };
  virtual uint           oper_input_base() const { return 1; }
public:
  cmpb_RegINode() {  _num_opnds = 5; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(cmpb_RegINode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  virtual bool           pinned() const { return true; }
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  const Type            *bottom_type() const { return TypeTuple::IFBOTH; } // matched IfNode
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "cmpb_RegI";}
#endif
};

class cmpbU_RegINode : public MachIfNode { 
private:
  MachOper *_opnd_array[5];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return cmpbU_RegI_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           label_set( Label* label, uint block_num );
  virtual void           save_label( Label** label, uint* block_num );
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_If; }
  virtual void           negate() { 
    opnd_array(1)->negate();
    _prob = 1.0f - _prob;
  };
  virtual uint           oper_input_base() const { return 1; }
public:
  cmpbU_RegINode() {  _num_opnds = 5; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(cmpbU_RegINode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  virtual bool           pinned() const { return true; }
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  const Type            *bottom_type() const { return TypeTuple::IFBOTH; } // matched IfNode
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "cmpbU_RegI";}
#endif
};

class cmpb_RegLNode : public MachIfNode { 
private:
  MachOper *_opnd_array[5];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return cmpb_RegL_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           label_set( Label* label, uint block_num );
  virtual void           save_label( Label** label, uint* block_num );
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_If; }
  virtual void           negate() { 
    opnd_array(1)->negate();
    _prob = 1.0f - _prob;
  };
  virtual uint           oper_input_base() const { return 1; }
public:
  cmpb_RegLNode() {  _num_opnds = 5; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(cmpb_RegLNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  virtual bool           pinned() const { return true; }
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  const Type            *bottom_type() const { return TypeTuple::IFBOTH; } // matched IfNode
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "cmpb_RegL";}
#endif
};

class cmpb_RegPPNode : public MachIfNode { 
private:
  MachOper *_opnd_array[5];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return cmpb_RegPP_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           label_set( Label* label, uint block_num );
  virtual void           save_label( Label** label, uint* block_num );
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_If; }
  virtual void           negate() { 
    opnd_array(1)->negate();
    _prob = 1.0f - _prob;
  };
  virtual uint           oper_input_base() const { return 1; }
public:
  cmpb_RegPPNode() {  _num_opnds = 5; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(cmpb_RegPPNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  virtual bool           pinned() const { return true; }
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  const Type            *bottom_type() const { return TypeTuple::IFBOTH; } // matched IfNode
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "cmpb_RegPP";}
#endif
};

class cmpb_RegNNNode : public MachIfNode { 
private:
  MachOper *_opnd_array[5];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return cmpb_RegNN_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           label_set( Label* label, uint block_num );
  virtual void           save_label( Label** label, uint* block_num );
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_If; }
  virtual void           negate() { 
    opnd_array(1)->negate();
    _prob = 1.0f - _prob;
  };
  virtual uint           oper_input_base() const { return 1; }
public:
  cmpb_RegNNNode() {  _num_opnds = 5; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(cmpb_RegNNNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  virtual bool           pinned() const { return true; }
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  const Type            *bottom_type() const { return TypeTuple::IFBOTH; } // matched IfNode
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "cmpb_RegNN";}
#endif
};

class testAndBranchLoopEnd_ImmNode : public MachIfNode { 
private:
  MachOper *_opnd_array[5];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return testAndBranchLoopEnd_Imm_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           label_set( Label* label, uint block_num );
  virtual void           save_label( Label** label, uint* block_num );
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_CountedLoopEnd; }
  virtual void           negate() { 
    opnd_array(1)->negate();
    _prob = 1.0f - _prob;
  };
  virtual uint           oper_input_base() const { return 1; }
public:
  testAndBranchLoopEnd_ImmNode() {  _num_opnds = 5; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(testAndBranchLoopEnd_ImmNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  virtual bool           pinned() const { return true; }
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  const Type            *bottom_type() const { return TypeTuple::IFBOTH; } // matched IfNode
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "testAndBranchLoopEnd_Imm";}
#endif
};

class cmpb_RegI_immNode : public MachIfNode { 
private:
  MachOper *_opnd_array[5];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return cmpb_RegI_imm_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           label_set( Label* label, uint block_num );
  virtual void           save_label( Label** label, uint* block_num );
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_If; }
  virtual void           negate() { 
    opnd_array(1)->negate();
    _prob = 1.0f - _prob;
  };
  virtual uint           oper_input_base() const { return 1; }
public:
  cmpb_RegI_immNode() {  _num_opnds = 5; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(cmpb_RegI_immNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  virtual bool           pinned() const { return true; }
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  const Type            *bottom_type() const { return TypeTuple::IFBOTH; } // matched IfNode
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "cmpb_RegI_imm";}
#endif
};

class cmpbU_RegI_immNode : public MachIfNode { 
private:
  MachOper *_opnd_array[5];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return cmpbU_RegI_imm_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           label_set( Label* label, uint block_num );
  virtual void           save_label( Label** label, uint* block_num );
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_If; }
  virtual void           negate() { 
    opnd_array(1)->negate();
    _prob = 1.0f - _prob;
  };
  virtual uint           oper_input_base() const { return 1; }
public:
  cmpbU_RegI_immNode() {  _num_opnds = 5; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(cmpbU_RegI_immNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  virtual bool           pinned() const { return true; }
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  const Type            *bottom_type() const { return TypeTuple::IFBOTH; } // matched IfNode
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "cmpbU_RegI_imm";}
#endif
};

class cmpb_RegL_immNode : public MachIfNode { 
private:
  MachOper *_opnd_array[5];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return cmpb_RegL_imm_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           label_set( Label* label, uint block_num );
  virtual void           save_label( Label** label, uint* block_num );
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_If; }
  virtual void           negate() { 
    opnd_array(1)->negate();
    _prob = 1.0f - _prob;
  };
  virtual uint           oper_input_base() const { return 1; }
public:
  cmpb_RegL_immNode() {  _num_opnds = 5; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(cmpb_RegL_immNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  virtual bool           pinned() const { return true; }
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  const Type            *bottom_type() const { return TypeTuple::IFBOTH; } // matched IfNode
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "cmpb_RegL_imm";}
#endif
};

class cmpb_RegP_immPNode : public MachIfNode { 
private:
  MachOper *_opnd_array[5];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return cmpb_RegP_immP_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           label_set( Label* label, uint block_num );
  virtual void           save_label( Label** label, uint* block_num );
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_If; }
  virtual void           negate() { 
    opnd_array(1)->negate();
    _prob = 1.0f - _prob;
  };
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 1; }
public:
  cmpb_RegP_immPNode() {  _num_opnds = 5; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(cmpb_RegP_immPNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  virtual bool           pinned() const { return true; }
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  const Type            *bottom_type() const { return TypeTuple::IFBOTH; } // matched IfNode
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "cmpb_RegP_immP";}
#endif
};

class cmpb_RegN_immP0Node : public MachIfNode { 
private:
  MachOper *_opnd_array[5];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return cmpb_RegN_immP0_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           label_set( Label* label, uint block_num );
  virtual void           save_label( Label** label, uint* block_num );
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_If; }
  virtual void           negate() { 
    opnd_array(1)->negate();
    _prob = 1.0f - _prob;
  };
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 1; }
public:
  cmpb_RegN_immP0Node() {  _num_opnds = 5; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(cmpb_RegN_immP0Node); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  virtual bool           pinned() const { return true; }
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  const Type            *bottom_type() const { return TypeTuple::IFBOTH; } // matched IfNode
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "cmpb_RegN_immP0";}
#endif
};

class cmpb_RegN_immNode : public MachIfNode { 
private:
  MachOper *_opnd_array[5];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return cmpb_RegN_imm_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           label_set( Label* label, uint block_num );
  virtual void           save_label( Label** label, uint* block_num );
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_If; }
  virtual void           negate() { 
    opnd_array(1)->negate();
    _prob = 1.0f - _prob;
  };
  virtual uint           oper_input_base() const { return 1; }
public:
  cmpb_RegN_immNode() {  _num_opnds = 5; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(cmpb_RegN_immNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  virtual bool           pinned() const { return true; }
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  const Type            *bottom_type() const { return TypeTuple::IFBOTH; } // matched IfNode
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "cmpb_RegN_imm";}
#endif
};

class testAndBranchLoopEnd_RegFarNode : public MachIfNode { 
private:
  MachOper *_opnd_array[5];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return testAndBranchLoopEnd_RegFar_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           label_set( Label* label, uint block_num );
  virtual void           save_label( Label** label, uint* block_num );
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_CountedLoopEnd; }
  virtual void           negate() { 
    opnd_array(1)->negate();
    _prob = 1.0f - _prob;
  };
  virtual uint           oper_input_base() const { return 1; }
public:
  testAndBranchLoopEnd_RegFarNode() {  _num_opnds = 5; _opnds = _opnd_array; init_flags(Flag_may_be_short_branch); }
  virtual uint           size_of() const { return sizeof(testAndBranchLoopEnd_RegFarNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  virtual bool           pinned() const { return true; }
  friend MachNode *State::MachNodeGenerator(int opcode);
  virtual MachNode      *short_branch_version();
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  const Type            *bottom_type() const { return TypeTuple::IFBOTH; } // matched IfNode
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "testAndBranchLoopEnd_RegFar";}
#endif
};

class cmpb_RegI_FarNode : public MachIfNode { 
private:
  MachOper *_opnd_array[5];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return cmpb_RegI_Far_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           label_set( Label* label, uint block_num );
  virtual void           save_label( Label** label, uint* block_num );
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_If; }
  virtual void           negate() { 
    opnd_array(1)->negate();
    _prob = 1.0f - _prob;
  };
  virtual uint           oper_input_base() const { return 1; }
public:
  cmpb_RegI_FarNode() {  _num_opnds = 5; _opnds = _opnd_array; init_flags(Flag_may_be_short_branch); }
  virtual uint           size_of() const { return sizeof(cmpb_RegI_FarNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  virtual bool           pinned() const { return true; }
  friend MachNode *State::MachNodeGenerator(int opcode);
  virtual MachNode      *short_branch_version();
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  const Type            *bottom_type() const { return TypeTuple::IFBOTH; } // matched IfNode
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "cmpb_RegI_Far";}
#endif
};

class cmpbU_RegI_FarNode : public MachIfNode { 
private:
  MachOper *_opnd_array[5];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return cmpbU_RegI_Far_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           label_set( Label* label, uint block_num );
  virtual void           save_label( Label** label, uint* block_num );
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_If; }
  virtual void           negate() { 
    opnd_array(1)->negate();
    _prob = 1.0f - _prob;
  };
  virtual uint           oper_input_base() const { return 1; }
public:
  cmpbU_RegI_FarNode() {  _num_opnds = 5; _opnds = _opnd_array; init_flags(Flag_may_be_short_branch); }
  virtual uint           size_of() const { return sizeof(cmpbU_RegI_FarNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  virtual bool           pinned() const { return true; }
  friend MachNode *State::MachNodeGenerator(int opcode);
  virtual MachNode      *short_branch_version();
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  const Type            *bottom_type() const { return TypeTuple::IFBOTH; } // matched IfNode
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "cmpbU_RegI_Far";}
#endif
};

class cmpb_RegL_FarNode : public MachIfNode { 
private:
  MachOper *_opnd_array[5];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return cmpb_RegL_Far_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           label_set( Label* label, uint block_num );
  virtual void           save_label( Label** label, uint* block_num );
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_If; }
  virtual void           negate() { 
    opnd_array(1)->negate();
    _prob = 1.0f - _prob;
  };
  virtual uint           oper_input_base() const { return 1; }
public:
  cmpb_RegL_FarNode() {  _num_opnds = 5; _opnds = _opnd_array; init_flags(Flag_may_be_short_branch); }
  virtual uint           size_of() const { return sizeof(cmpb_RegL_FarNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  virtual bool           pinned() const { return true; }
  friend MachNode *State::MachNodeGenerator(int opcode);
  virtual MachNode      *short_branch_version();
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  const Type            *bottom_type() const { return TypeTuple::IFBOTH; } // matched IfNode
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "cmpb_RegL_Far";}
#endif
};

class cmpb_RegPP_FarNode : public MachIfNode { 
private:
  MachOper *_opnd_array[5];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return cmpb_RegPP_Far_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           label_set( Label* label, uint block_num );
  virtual void           save_label( Label** label, uint* block_num );
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_If; }
  virtual void           negate() { 
    opnd_array(1)->negate();
    _prob = 1.0f - _prob;
  };
  virtual uint           oper_input_base() const { return 1; }
public:
  cmpb_RegPP_FarNode() {  _num_opnds = 5; _opnds = _opnd_array; init_flags(Flag_may_be_short_branch); }
  virtual uint           size_of() const { return sizeof(cmpb_RegPP_FarNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  virtual bool           pinned() const { return true; }
  friend MachNode *State::MachNodeGenerator(int opcode);
  virtual MachNode      *short_branch_version();
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  const Type            *bottom_type() const { return TypeTuple::IFBOTH; } // matched IfNode
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "cmpb_RegPP_Far";}
#endif
};

class cmpb_RegNN_FarNode : public MachIfNode { 
private:
  MachOper *_opnd_array[5];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return cmpb_RegNN_Far_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           label_set( Label* label, uint block_num );
  virtual void           save_label( Label** label, uint* block_num );
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_If; }
  virtual void           negate() { 
    opnd_array(1)->negate();
    _prob = 1.0f - _prob;
  };
  virtual uint           oper_input_base() const { return 1; }
public:
  cmpb_RegNN_FarNode() {  _num_opnds = 5; _opnds = _opnd_array; init_flags(Flag_may_be_short_branch); }
  virtual uint           size_of() const { return sizeof(cmpb_RegNN_FarNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  virtual bool           pinned() const { return true; }
  friend MachNode *State::MachNodeGenerator(int opcode);
  virtual MachNode      *short_branch_version();
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  const Type            *bottom_type() const { return TypeTuple::IFBOTH; } // matched IfNode
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "cmpb_RegNN_Far";}
#endif
};

class testAndBranchLoopEnd_ImmFarNode : public MachIfNode { 
private:
  MachOper *_opnd_array[5];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return testAndBranchLoopEnd_ImmFar_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           label_set( Label* label, uint block_num );
  virtual void           save_label( Label** label, uint* block_num );
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_CountedLoopEnd; }
  virtual void           negate() { 
    opnd_array(1)->negate();
    _prob = 1.0f - _prob;
  };
  virtual uint           oper_input_base() const { return 1; }
public:
  testAndBranchLoopEnd_ImmFarNode() {  _num_opnds = 5; _opnds = _opnd_array; init_flags(Flag_may_be_short_branch); }
  virtual uint           size_of() const { return sizeof(testAndBranchLoopEnd_ImmFarNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  virtual bool           pinned() const { return true; }
  friend MachNode *State::MachNodeGenerator(int opcode);
  virtual MachNode      *short_branch_version();
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  const Type            *bottom_type() const { return TypeTuple::IFBOTH; } // matched IfNode
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "testAndBranchLoopEnd_ImmFar";}
#endif
};

class cmpb_RegI_imm_FarNode : public MachIfNode { 
private:
  MachOper *_opnd_array[5];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return cmpb_RegI_imm_Far_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           label_set( Label* label, uint block_num );
  virtual void           save_label( Label** label, uint* block_num );
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_If; }
  virtual void           negate() { 
    opnd_array(1)->negate();
    _prob = 1.0f - _prob;
  };
  virtual uint           oper_input_base() const { return 1; }
public:
  cmpb_RegI_imm_FarNode() {  _num_opnds = 5; _opnds = _opnd_array; init_flags(Flag_may_be_short_branch); }
  virtual uint           size_of() const { return sizeof(cmpb_RegI_imm_FarNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  virtual bool           pinned() const { return true; }
  friend MachNode *State::MachNodeGenerator(int opcode);
  virtual MachNode      *short_branch_version();
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  const Type            *bottom_type() const { return TypeTuple::IFBOTH; } // matched IfNode
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "cmpb_RegI_imm_Far";}
#endif
};

class cmpbU_RegI_imm_FarNode : public MachIfNode { 
private:
  MachOper *_opnd_array[5];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return cmpbU_RegI_imm_Far_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           label_set( Label* label, uint block_num );
  virtual void           save_label( Label** label, uint* block_num );
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_If; }
  virtual void           negate() { 
    opnd_array(1)->negate();
    _prob = 1.0f - _prob;
  };
  virtual uint           oper_input_base() const { return 1; }
public:
  cmpbU_RegI_imm_FarNode() {  _num_opnds = 5; _opnds = _opnd_array; init_flags(Flag_may_be_short_branch); }
  virtual uint           size_of() const { return sizeof(cmpbU_RegI_imm_FarNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  virtual bool           pinned() const { return true; }
  friend MachNode *State::MachNodeGenerator(int opcode);
  virtual MachNode      *short_branch_version();
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  const Type            *bottom_type() const { return TypeTuple::IFBOTH; } // matched IfNode
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "cmpbU_RegI_imm_Far";}
#endif
};

class cmpb_RegL_imm_FarNode : public MachIfNode { 
private:
  MachOper *_opnd_array[5];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return cmpb_RegL_imm_Far_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           label_set( Label* label, uint block_num );
  virtual void           save_label( Label** label, uint* block_num );
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_If; }
  virtual void           negate() { 
    opnd_array(1)->negate();
    _prob = 1.0f - _prob;
  };
  virtual uint           oper_input_base() const { return 1; }
public:
  cmpb_RegL_imm_FarNode() {  _num_opnds = 5; _opnds = _opnd_array; init_flags(Flag_may_be_short_branch); }
  virtual uint           size_of() const { return sizeof(cmpb_RegL_imm_FarNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  virtual bool           pinned() const { return true; }
  friend MachNode *State::MachNodeGenerator(int opcode);
  virtual MachNode      *short_branch_version();
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  const Type            *bottom_type() const { return TypeTuple::IFBOTH; } // matched IfNode
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "cmpb_RegL_imm_Far";}
#endif
};

class cmpb_RegP_immP_FarNode : public MachIfNode { 
private:
  MachOper *_opnd_array[5];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return cmpb_RegP_immP_Far_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           label_set( Label* label, uint block_num );
  virtual void           save_label( Label** label, uint* block_num );
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_If; }
  virtual void           negate() { 
    opnd_array(1)->negate();
    _prob = 1.0f - _prob;
  };
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 1; }
public:
  cmpb_RegP_immP_FarNode() {  _num_opnds = 5; _opnds = _opnd_array; init_flags(Flag_may_be_short_branch); }
  virtual uint           size_of() const { return sizeof(cmpb_RegP_immP_FarNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  virtual bool           pinned() const { return true; }
  friend MachNode *State::MachNodeGenerator(int opcode);
  virtual MachNode      *short_branch_version();
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  const Type            *bottom_type() const { return TypeTuple::IFBOTH; } // matched IfNode
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "cmpb_RegP_immP_Far";}
#endif
};

class cmpb_RegN_immP0_FarNode : public MachIfNode { 
private:
  MachOper *_opnd_array[5];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return cmpb_RegN_immP0_Far_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           label_set( Label* label, uint block_num );
  virtual void           save_label( Label** label, uint* block_num );
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_If; }
  virtual void           negate() { 
    opnd_array(1)->negate();
    _prob = 1.0f - _prob;
  };
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 1; }
public:
  cmpb_RegN_immP0_FarNode() {  _num_opnds = 5; _opnds = _opnd_array; init_flags(Flag_may_be_short_branch); }
  virtual uint           size_of() const { return sizeof(cmpb_RegN_immP0_FarNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  virtual bool           pinned() const { return true; }
  friend MachNode *State::MachNodeGenerator(int opcode);
  virtual MachNode      *short_branch_version();
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  const Type            *bottom_type() const { return TypeTuple::IFBOTH; } // matched IfNode
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "cmpb_RegN_immP0_Far";}
#endif
};

class cmpb_RegN_immN_FarNode : public MachIfNode { 
private:
  MachOper *_opnd_array[5];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return cmpb_RegN_immN_Far_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           label_set( Label* label, uint block_num );
  virtual void           save_label( Label** label, uint* block_num );
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_If; }
  virtual void           negate() { 
    opnd_array(1)->negate();
    _prob = 1.0f - _prob;
  };
  virtual uint           oper_input_base() const { return 1; }
public:
  cmpb_RegN_immN_FarNode() {  _num_opnds = 5; _opnds = _opnd_array; init_flags(Flag_may_be_short_branch); }
  virtual uint           size_of() const { return sizeof(cmpb_RegN_immN_FarNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  virtual bool           pinned() const { return true; }
  friend MachNode *State::MachNodeGenerator(int opcode);
  virtual MachNode      *short_branch_version();
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  const Type            *bottom_type() const { return TypeTuple::IFBOTH; } // matched IfNode
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "cmpb_RegN_immN_Far";}
#endif
};

class cmpL3_reg_regNode : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return cmpL3_reg_reg_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_CmpL3; }
public:
  cmpL3_reg_regNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(cmpL3_reg_regNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "cmpL3_reg_reg";}
#endif
};

class safePointNode : public MachSafePointNode { 
private:
  MachOper *_opnd_array[1];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return safePoint_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_SafePoint; }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 5; }
public:
  safePointNode() {  _num_opnds = 1; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(safePointNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "safePoint";}
#endif
};

class safePoint_pollNode : public MachSafePointNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return safePoint_poll_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_SafePoint; }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 5; }
public:
  safePoint_pollNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(safePoint_pollNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "safePoint_poll";}
#endif
};

class CallStaticJavaDirect_dynTOCNode : public MachCallStaticJavaNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return CallStaticJavaDirect_dynTOC_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           method_set( intptr_t method );
  virtual int            ins_alignment() const { return 2; }
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_CallStaticJava; }
  virtual int            reloc() const;
  virtual int            alignment_required() const { return 2; }
  virtual int            compute_padding(int current_offset) const;
  virtual uint           oper_input_base() const { return 1; }
public:
  CallStaticJavaDirect_dynTOCNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(CallStaticJavaDirect_dynTOCNode); }
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "CallStaticJavaDirect_dynTOC";}
#endif
};

class CallDynamicJavaDirect_dynTOCNode : public MachCallDynamicJavaNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return CallDynamicJavaDirect_dynTOC_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           method_set( intptr_t method );
  virtual int            ins_alignment() const { return 2; }
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_CallDynamicJava; }
  virtual int            reloc() const;
  virtual int            alignment_required() const { return 2; }
  virtual int            compute_padding(int current_offset) const;
  virtual uint           oper_input_base() const { return 1; }
public:
  CallDynamicJavaDirect_dynTOCNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(CallDynamicJavaDirect_dynTOCNode); }
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "CallDynamicJavaDirect_dynTOC";}
#endif
};

class CallRuntimeDirectNode : public MachCallRuntimeNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return CallRuntimeDirect_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           method_set( intptr_t method );
  virtual int            ins_alignment() const { return 2; }
  virtual int            ins_num_consts() const { return 1; }
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_CallRuntime; }
  virtual int            reloc() const;
  virtual int            alignment_required() const { return 2; }
  virtual int            compute_padding(int current_offset) const;
  virtual uint           oper_input_base() const { return 1; }
public:
  CallRuntimeDirectNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(CallRuntimeDirectNode); }
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "CallRuntimeDirect";}
#endif
};

class CallLeafDirectNode : public MachCallLeafNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return CallLeafDirect_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           method_set( intptr_t method );
  virtual int            ins_alignment() const { return 2; }
  virtual int            ins_num_consts() const { return 1; }
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_CallLeaf; }
  virtual int            reloc() const;
  virtual int            alignment_required() const { return 2; }
  virtual int            compute_padding(int current_offset) const;
  virtual uint           oper_input_base() const { return 1; }
public:
  CallLeafDirectNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(CallLeafDirectNode); }
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "CallLeafDirect";}
#endif
};

class CallLeafNoFPDirectNode : public MachCallLeafNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return CallLeafNoFPDirect_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           method_set( intptr_t method );
  virtual int            ins_alignment() const { return 2; }
  virtual int            ins_num_consts() const { return 1; }
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_CallLeafNoFP; }
  virtual int            reloc() const;
  virtual int            alignment_required() const { return 2; }
  virtual int            compute_padding(int current_offset) const;
  virtual uint           oper_input_base() const { return 1; }
public:
  CallLeafNoFPDirectNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(CallLeafNoFPDirectNode); }
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "CallLeafNoFPDirect";}
#endif
};

class TailCalljmpIndNode : public MachReturnNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return TailCalljmpInd_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_TailCall; }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 5; }
public:
  TailCalljmpIndNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(TailCalljmpIndNode); }
  virtual bool           pinned() const { return true; }
  virtual const Node *is_block_proj() const { return this; }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "TailCalljmpInd";}
#endif
};

class RetNode : public MachReturnNode { 
private:
  MachOper *_opnd_array[1];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return Ret_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_Return; }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 5; }
public:
  RetNode() {  _num_opnds = 1; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(RetNode); }
  virtual bool           pinned() const { return true; }
  virtual const Node *is_block_proj() const { return this; }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "Ret";}
#endif
};

class tailjmpIndNode : public MachReturnNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return tailjmpInd_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_TailJump; }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 5; }
public:
  tailjmpIndNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(tailjmpIndNode); }
  virtual bool           pinned() const { return true; }
  virtual const Node *is_block_proj() const { return this; }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "tailjmpInd";}
#endif
};

class ForwardExceptionjmpNode : public MachReturnNode { 
private:
  MachOper *_opnd_array[1];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return ForwardExceptionjmp_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_ForwardException; }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 5; }
public:
  ForwardExceptionjmpNode() {  _num_opnds = 1; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(ForwardExceptionjmpNode); }
  virtual bool           pinned() const { return true; }
  virtual const Node *is_block_proj() const { return this; }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "ForwardExceptionjmp";}
#endif
};

class CreateExceptionNode : public MachTypeNode { 
private:
  MachOper *_opnd_array[1];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return CreateException_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_CreateEx; }
  virtual uint           oper_input_base() const { return 1; }
public:
  CreateExceptionNode() {  _num_opnds = 1; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(CreateExceptionNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "CreateException";}
#endif
};

class RethrowExceptionNode : public MachReturnNode { 
private:
  MachOper *_opnd_array[1];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return RethrowException_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_Rethrow; }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 5; }
public:
  RethrowExceptionNode() {  _num_opnds = 1; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(RethrowExceptionNode); }
  virtual bool           pinned() const { return true; }
  virtual const Node *is_block_proj() const { return this; }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "RethrowException";}
#endif
};

class ShouldNotReachHereNode : public MachHaltNode { 
private:
  MachOper *_opnd_array[1];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return ShouldNotReachHere_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_Halt; }
  virtual uint           oper_input_base() const { return 5; }
public:
  ShouldNotReachHereNode() {  _num_opnds = 1; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(ShouldNotReachHereNode); }
  virtual bool           pinned() const { return true; }
  virtual const Node *is_block_proj() const { return this; }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "ShouldNotReachHere";}
#endif
};

class partialSubtypeCheckNode : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return partialSubtypeCheck_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_PartialSubtypeCheck; }
public:
  partialSubtypeCheckNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(partialSubtypeCheckNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "partialSubtypeCheck";}
#endif
};

class partialSubtypeCheckVarSuperNode : public MachNode { 
private:
  MachOper *_opnd_array[7];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return partialSubtypeCheckVarSuper_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_PartialSubtypeCheck; }
public:
  partialSubtypeCheckVarSuperNode() {  _num_opnds = 7; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(partialSubtypeCheckVarSuperNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "partialSubtypeCheckVarSuper";}
#endif
};

class partialSubtypeCheckConstSuperNode : public MachNode { 
private:
  MachOper *_opnd_array[8];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return partialSubtypeCheckConstSuper_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_PartialSubtypeCheck; }
  virtual int            reloc() const;
public:
  partialSubtypeCheckConstSuperNode() {  _num_opnds = 8; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(partialSubtypeCheckConstSuperNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "partialSubtypeCheckConstSuper";}
#endif
};

class cmpFastLockNode : public MachFastLockNode { 
private:
  MachOper *_opnd_array[5];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return cmpFastLock_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_FastLock; }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 1; }
public:
  cmpFastLockNode() {  _num_opnds = 5; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(cmpFastLockNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  // Rematerialize cmpFastLock
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "cmpFastLock";}
#endif
};

class cmpFastUnlockNode : public MachNode { 
private:
  MachOper *_opnd_array[5];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return cmpFastUnlock_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_FastUnlock; }
  virtual int            reloc() const;
public:
  cmpFastUnlockNode() {  _num_opnds = 5; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(cmpFastUnlockNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  // Rematerialize cmpFastUnlock
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "cmpFastUnlock";}
#endif
};

class inlineCallClearArrayConstNode : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return inlineCallClearArrayConst_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_ClearArray; }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  inlineCallClearArrayConstNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(inlineCallClearArrayConstNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "inlineCallClearArrayConst";}
#endif
};

class inlineCallClearArrayConstBigNode : public MachNode { 
private:
  MachOper *_opnd_array[4];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return inlineCallClearArrayConstBig_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_ClearArray; }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  inlineCallClearArrayConstBigNode() {  _num_opnds = 4; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(inlineCallClearArrayConstBigNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "inlineCallClearArrayConstBig";}
#endif
};

class inlineCallClearArrayNode : public MachNode { 
private:
  MachOper *_opnd_array[4];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return inlineCallClearArray_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_ClearArray; }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  inlineCallClearArrayNode() {  _num_opnds = 4; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(inlineCallClearArrayNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "inlineCallClearArray";}
#endif
};

class string_equalsLNode : public MachNode { 
private:
  MachOper *_opnd_array[6];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return string_equalsL_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_StrEquals; }
  virtual uint           oper_input_base() const { return 2; }
public:
  string_equalsLNode() {  _num_opnds = 6; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(string_equalsLNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "string_equalsL";}
#endif
};

class string_equals_immNode : public MachNode { 
private:
  MachOper *_opnd_array[4];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return string_equals_imm_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_StrEquals; }
  virtual uint           oper_input_base() const { return 2; }
public:
  string_equals_immNode() {  _num_opnds = 4; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(string_equals_immNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "string_equals_imm";}
#endif
};

class string_equalsC_immNode : public MachNode { 
private:
  MachOper *_opnd_array[4];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return string_equalsC_imm_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_StrEquals; }
  virtual uint           oper_input_base() const { return 2; }
public:
  string_equalsC_immNode() {  _num_opnds = 4; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(string_equalsC_immNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "string_equalsC_imm";}
#endif
};

class array_equalsBNode : public MachNode { 
private:
  MachOper *_opnd_array[5];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return array_equalsB_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_AryEq; }
  virtual uint           oper_input_base() const { return 2; }
public:
  array_equalsBNode() {  _num_opnds = 5; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(array_equalsBNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "array_equalsB";}
#endif
};

class array_equalsCNode : public MachNode { 
private:
  MachOper *_opnd_array[5];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return array_equalsC_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_AryEq; }
  virtual uint           oper_input_base() const { return 2; }
public:
  array_equalsCNode() {  _num_opnds = 5; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(array_equalsCNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "array_equalsC";}
#endif
};

class string_compareLNode : public MachNode { 
private:
  MachOper *_opnd_array[8];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return string_compareL_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_StrComp; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges() + opnd_array(2)->num_edges() + opnd_array(3)->num_edges() + opnd_array(4)->num_edges(); }
  virtual uint           oper_input_base() const { return 2; }
public:
  string_compareLNode() {  _num_opnds = 8; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(string_compareLNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "string_compareL";}
#endif
};

class string_compareUNode : public MachNode { 
private:
  MachOper *_opnd_array[8];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return string_compareU_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_StrComp; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges() + opnd_array(2)->num_edges() + opnd_array(3)->num_edges() + opnd_array(4)->num_edges(); }
  virtual uint           oper_input_base() const { return 2; }
public:
  string_compareUNode() {  _num_opnds = 8; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(string_compareUNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "string_compareU";}
#endif
};

class string_compareLUNode : public MachNode { 
private:
  MachOper *_opnd_array[8];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return string_compareLU_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_StrComp; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges() + opnd_array(2)->num_edges() + opnd_array(3)->num_edges() + opnd_array(4)->num_edges(); }
  virtual uint           oper_input_base() const { return 2; }
public:
  string_compareLUNode() {  _num_opnds = 8; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(string_compareLUNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "string_compareLU";}
#endif
};

class string_compareULNode : public MachNode { 
private:
  MachOper *_opnd_array[8];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return string_compareUL_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_StrComp; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges() + opnd_array(2)->num_edges() + opnd_array(3)->num_edges() + opnd_array(4)->num_edges(); }
  virtual uint           oper_input_base() const { return 2; }
public:
  string_compareULNode() {  _num_opnds = 8; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(string_compareULNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "string_compareUL";}
#endif
};

class indexOfChar_UNode : public MachNode { 
private:
  MachOper *_opnd_array[7];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return indexOfChar_U_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_StrIndexOfChar; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges() + opnd_array(2)->num_edges() + opnd_array(3)->num_edges(); }
  virtual uint           oper_input_base() const { return 2; }
public:
  indexOfChar_UNode() {  _num_opnds = 7; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(indexOfChar_UNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "indexOfChar_U";}
#endif
};

class indexOfChar_LNode : public MachNode { 
private:
  MachOper *_opnd_array[7];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return indexOfChar_L_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_StrIndexOfChar; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges() + opnd_array(2)->num_edges() + opnd_array(3)->num_edges(); }
  virtual uint           oper_input_base() const { return 2; }
public:
  indexOfChar_LNode() {  _num_opnds = 7; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(indexOfChar_LNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "indexOfChar_L";}
#endif
};

class indexOf_imm1_UNode : public MachNode { 
private:
  MachOper *_opnd_array[8];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return indexOf_imm1_U_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_StrIndexOf; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges() + opnd_array(2)->num_edges() + opnd_array(3)->num_edges() + opnd_array(4)->num_edges(); }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  indexOf_imm1_UNode() {  _num_opnds = 8; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(indexOf_imm1_UNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "indexOf_imm1_U";}
#endif
};

class indexOf_imm1_LNode : public MachNode { 
private:
  MachOper *_opnd_array[8];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return indexOf_imm1_L_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_StrIndexOf; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges() + opnd_array(2)->num_edges() + opnd_array(3)->num_edges() + opnd_array(4)->num_edges(); }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  indexOf_imm1_LNode() {  _num_opnds = 8; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(indexOf_imm1_LNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "indexOf_imm1_L";}
#endif
};

class indexOf_imm1_ULNode : public MachNode { 
private:
  MachOper *_opnd_array[8];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return indexOf_imm1_UL_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_StrIndexOf; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges() + opnd_array(2)->num_edges() + opnd_array(3)->num_edges() + opnd_array(4)->num_edges(); }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  indexOf_imm1_ULNode() {  _num_opnds = 8; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(indexOf_imm1_ULNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "indexOf_imm1_UL";}
#endif
};

class indexOf_imm_UNode : public MachNode { 
private:
  MachOper *_opnd_array[8];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return indexOf_imm_U_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_StrIndexOf; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges() + opnd_array(2)->num_edges() + opnd_array(3)->num_edges() + opnd_array(4)->num_edges(); }
  virtual uint           oper_input_base() const { return 2; }
public:
  indexOf_imm_UNode() {  _num_opnds = 8; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(indexOf_imm_UNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "indexOf_imm_U";}
#endif
};

class indexOf_imm_LNode : public MachNode { 
private:
  MachOper *_opnd_array[8];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return indexOf_imm_L_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_StrIndexOf; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges() + opnd_array(2)->num_edges() + opnd_array(3)->num_edges() + opnd_array(4)->num_edges(); }
  virtual uint           oper_input_base() const { return 2; }
public:
  indexOf_imm_LNode() {  _num_opnds = 8; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(indexOf_imm_LNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "indexOf_imm_L";}
#endif
};

class indexOf_imm_ULNode : public MachNode { 
private:
  MachOper *_opnd_array[8];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return indexOf_imm_UL_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_StrIndexOf; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges() + opnd_array(2)->num_edges() + opnd_array(3)->num_edges() + opnd_array(4)->num_edges(); }
  virtual uint           oper_input_base() const { return 2; }
public:
  indexOf_imm_ULNode() {  _num_opnds = 8; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(indexOf_imm_ULNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "indexOf_imm_UL";}
#endif
};

class indexOf_UNode : public MachNode { 
private:
  MachOper *_opnd_array[8];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return indexOf_U_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_StrIndexOf; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges() + opnd_array(2)->num_edges() + opnd_array(3)->num_edges() + opnd_array(4)->num_edges(); }
  virtual uint           oper_input_base() const { return 2; }
public:
  indexOf_UNode() {  _num_opnds = 8; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(indexOf_UNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "indexOf_U";}
#endif
};

class indexOf_LNode : public MachNode { 
private:
  MachOper *_opnd_array[8];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return indexOf_L_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_StrIndexOf; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges() + opnd_array(2)->num_edges() + opnd_array(3)->num_edges() + opnd_array(4)->num_edges(); }
  virtual uint           oper_input_base() const { return 2; }
public:
  indexOf_LNode() {  _num_opnds = 8; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(indexOf_LNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "indexOf_L";}
#endif
};

class indexOf_ULNode : public MachNode { 
private:
  MachOper *_opnd_array[8];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return indexOf_UL_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_StrIndexOf; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges() + opnd_array(2)->num_edges() + opnd_array(3)->num_edges() + opnd_array(4)->num_edges(); }
  virtual uint           oper_input_base() const { return 2; }
public:
  indexOf_ULNode() {  _num_opnds = 8; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(indexOf_ULNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "indexOf_UL";}
#endif
};

class string_compressNode : public MachNode { 
private:
  MachOper *_opnd_array[14];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return string_compress_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_StrCompressedCopy; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges() + opnd_array(2)->num_edges() + opnd_array(3)->num_edges(); }
  virtual uint           oper_input_base() const { return 2; }
public:
  string_compressNode() {  _num_opnds = 14; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(string_compressNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "string_compress";}
#endif
};

class string_inflateNode : public MachTypeNode { 
private:
  MachOper *_opnd_array[11];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return string_inflate_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_StrInflatedCopy; }
  virtual uint           oper_input_base() const { return 2; }
public:
  string_inflateNode() {  _num_opnds = 11; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(string_inflateNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "string_inflate";}
#endif
};

class string_inflate_constNode : public MachTypeNode { 
private:
  MachOper *_opnd_array[11];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return string_inflate_const_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_StrInflatedCopy; }
  virtual uint           oper_input_base() const { return 2; }
public:
  string_inflate_constNode() {  _num_opnds = 11; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(string_inflate_constNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "string_inflate_const";}
#endif
};

class count_positivesNode : public MachNode { 
private:
  MachOper *_opnd_array[5];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return count_positives_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_CountPositives; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges() + opnd_array(2)->num_edges(); }
  virtual uint           oper_input_base() const { return 2; }
public:
  count_positivesNode() {  _num_opnds = 5; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(count_positivesNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "count_positives";}
#endif
};

class encode_iso_arrayNode : public MachNode { 
private:
  MachOper *_opnd_array[14];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return encode_iso_array_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_EncodeISOArray; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges() + opnd_array(2)->num_edges() + opnd_array(3)->num_edges(); }
  virtual uint           oper_input_base() const { return 2; }
public:
  encode_iso_arrayNode() {  _num_opnds = 14; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(encode_iso_arrayNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "encode_iso_array";}
#endif
};

class encode_ascii_arrayNode : public MachNode { 
private:
  MachOper *_opnd_array[14];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return encode_ascii_array_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_EncodeISOArray; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges() + opnd_array(2)->num_edges() + opnd_array(3)->num_edges(); }
  virtual uint           oper_input_base() const { return 2; }
public:
  encode_ascii_arrayNode() {  _num_opnds = 14; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(encode_ascii_arrayNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "encode_ascii_array";}
#endif
};

class expand_storeFNode : public MachNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return expand_storeF_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
public:
  expand_storeFNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(expand_storeFNode); }
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "expand_storeF";}
#endif
};

class expand_LoadLogical_I2LNode : public MachNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return expand_LoadLogical_I2L_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
public:
  expand_LoadLogical_I2LNode() {  _num_opnds = 2; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(expand_LoadLogical_I2LNode); }
  friend MachNode *State::MachNodeGenerator(int opcode);
  // Rematerialize expand_LoadLogical_I2L
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "expand_LoadLogical_I2L";}
#endif
};

class expand_Repl2I_regNode : public MachNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return expand_Repl2I_reg_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_ConvI2L; }
public:
  expand_Repl2I_regNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(expand_Repl2I_regNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "expand_Repl2I_reg";}
#endif
};

class Repl8B_reg_risbgNode : public MachTypeNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return Repl8B_reg_risbg_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_Replicate; }
  virtual uint           oper_input_base() const { return 1; }
public:
  Repl8B_reg_risbgNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(Repl8B_reg_risbgNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "Repl8B_reg_risbg";}
#endif
};

class Repl8B_immNode : public MachTypeNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return Repl8B_imm_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual int            ins_should_rematerialize() const { return true; }
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_Replicate; }
  virtual uint           oper_input_base() const { return 1; }
public:
  Repl8B_immNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(Repl8B_immNode); }
  // Rematerialize Repl8B_imm
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "Repl8B_imm";}
#endif
};

class Repl8B_imm0Node : public MachTypeNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return Repl8B_imm0_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual int            ins_should_rematerialize() const { return true; }
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_Replicate; }
  virtual uint           oper_input_base() const { return 1; }
public:
  Repl8B_imm0Node() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(Repl8B_imm0Node); }
  // Rematerialize Repl8B_imm0
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "Repl8B_imm0";}
#endif
};

class Repl8B_immm1Node : public MachTypeNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return Repl8B_immm1_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual int            ins_should_rematerialize() const { return true; }
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_Replicate; }
  virtual uint           oper_input_base() const { return 1; }
public:
  Repl8B_immm1Node() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(Repl8B_immm1Node); }
  // Rematerialize Repl8B_immm1
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "Repl8B_immm1";}
#endif
};

class Repl4S_reg_risbgNode : public MachTypeNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return Repl4S_reg_risbg_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_Replicate; }
  virtual uint           oper_input_base() const { return 1; }
public:
  Repl4S_reg_risbgNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(Repl4S_reg_risbgNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "Repl4S_reg_risbg";}
#endif
};

class Repl4S_immNode : public MachTypeNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return Repl4S_imm_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual int            ins_should_rematerialize() const { return true; }
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_Replicate; }
  virtual uint           oper_input_base() const { return 1; }
public:
  Repl4S_immNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(Repl4S_immNode); }
  // Rematerialize Repl4S_imm
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "Repl4S_imm";}
#endif
};

class Repl4S_imm0Node : public MachTypeNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return Repl4S_imm0_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual int            ins_should_rematerialize() const { return true; }
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_Replicate; }
  virtual uint           oper_input_base() const { return 1; }
public:
  Repl4S_imm0Node() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(Repl4S_imm0Node); }
  // Rematerialize Repl4S_imm0
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "Repl4S_imm0";}
#endif
};

class Repl4S_immm1Node : public MachTypeNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return Repl4S_immm1_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual int            ins_should_rematerialize() const { return true; }
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_Replicate; }
  virtual uint           oper_input_base() const { return 1; }
public:
  Repl4S_immm1Node() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(Repl4S_immm1Node); }
  // Rematerialize Repl4S_immm1
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "Repl4S_immm1";}
#endif
};

class repl8S_reg_ExNode : public MachTypeNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return repl8S_reg_Ex_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_Replicate; }
  virtual uint           oper_input_base() const { return 1; }
public:
  repl8S_reg_ExNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(repl8S_reg_ExNode); }
  // Rematerialize repl8S_reg_Ex
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "repl8S_reg_Ex";}
#endif
};

class repl8S_immIminus1Node : public MachTypeNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return repl8S_immIminus1_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_Replicate; }
  virtual uint           oper_input_base() const { return 1; }
public:
  repl8S_immIminus1Node() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(repl8S_immIminus1Node); }
  // Rematerialize repl8S_immIminus1
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "repl8S_immIminus1";}
#endif
};

class repl8S_immI0Node : public MachTypeNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return repl8S_immI0_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_Replicate; }
  virtual uint           oper_input_base() const { return 1; }
public:
  repl8S_immI0Node() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(repl8S_immI0Node); }
  // Rematerialize repl8S_immI0
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "repl8S_immI0";}
#endif
};

class Repl2I_reg_risbgNode : public MachTypeNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return Repl2I_reg_risbg_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_Replicate; }
  virtual uint           oper_input_base() const { return 1; }
public:
  Repl2I_reg_risbgNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(Repl2I_reg_risbgNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "Repl2I_reg_risbg";}
#endif
};

class Repl2I_immNode : public MachTypeNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return Repl2I_imm_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual int            ins_should_rematerialize() const { return true; }
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_Replicate; }
  virtual uint           oper_input_base() const { return 1; }
public:
  Repl2I_immNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(Repl2I_immNode); }
  // Rematerialize Repl2I_imm
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "Repl2I_imm";}
#endif
};

class Repl2I_imm0Node : public MachTypeNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return Repl2I_imm0_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual int            ins_should_rematerialize() const { return true; }
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_Replicate; }
  virtual uint           oper_input_base() const { return 1; }
public:
  Repl2I_imm0Node() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(Repl2I_imm0Node); }
  // Rematerialize Repl2I_imm0
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "Repl2I_imm0";}
#endif
};

class Repl2I_immm1Node : public MachTypeNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return Repl2I_immm1_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual int            ins_should_rematerialize() const { return true; }
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_Replicate; }
  virtual uint           oper_input_base() const { return 1; }
public:
  Repl2I_immm1Node() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(Repl2I_immm1Node); }
  // Rematerialize Repl2I_immm1
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "Repl2I_immm1";}
#endif
};

class repl4I_reg_ExNode : public MachTypeNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return repl4I_reg_Ex_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_Replicate; }
  virtual uint           oper_input_base() const { return 1; }
public:
  repl4I_reg_ExNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(repl4I_reg_ExNode); }
  // Rematerialize repl4I_reg_Ex
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "repl4I_reg_Ex";}
#endif
};

class repl4I_immI0Node : public MachTypeNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return repl4I_immI0_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_Replicate; }
  virtual uint           oper_input_base() const { return 1; }
public:
  repl4I_immI0Node() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(repl4I_immI0Node); }
  // Rematerialize repl4I_immI0
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "repl4I_immI0";}
#endif
};

class repl4I_immIminus1Node : public MachTypeNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return repl4I_immIminus1_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_Replicate; }
  virtual uint           oper_input_base() const { return 1; }
public:
  repl4I_immIminus1Node() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(repl4I_immIminus1Node); }
  // Rematerialize repl4I_immIminus1
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "repl4I_immIminus1";}
#endif
};

class Repl2F_reg_indirectNode : public MachTypeNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return Repl2F_reg_indirect_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual int            ideal_Opcode() const { return Op_Replicate; }
  virtual uint           oper_input_base() const { return 1; }
public:
  Repl2F_reg_indirectNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(Repl2F_reg_indirectNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "Repl2F_reg_indirect";}
#endif
};

class Repl2F_reg_directNode : public MachTypeNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return Repl2F_reg_direct_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_Replicate; }
  virtual uint           oper_input_base() const { return 1; }
public:
  Repl2F_reg_directNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(Repl2F_reg_directNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "Repl2F_reg_direct";}
#endif
};

class Repl2F_immNode : public MachTypeNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return Repl2F_imm_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual int            ins_should_rematerialize() const { return true; }
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_Replicate; }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 1; }
public:
  Repl2F_immNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(Repl2F_immNode); }
  // Rematerialize Repl2F_imm
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "Repl2F_imm";}
#endif
};

class Repl2F_imm0Node : public MachTypeNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return Repl2F_imm0_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual int            ins_should_rematerialize() const { return true; }
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_Replicate; }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 1; }
public:
  Repl2F_imm0Node() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(Repl2F_imm0Node); }
  // Rematerialize Repl2F_imm0
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "Repl2F_imm0";}
#endif
};

class repl4F_reg_ExNode : public MachTypeNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return repl4F_reg_Ex_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_Replicate; }
  virtual uint           oper_input_base() const { return 1; }
public:
  repl4F_reg_ExNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(repl4F_reg_ExNode); }
  // Rematerialize repl4F_reg_Ex
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "repl4F_reg_Ex";}
#endif
};

class repl4F_immF0Node : public MachTypeNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return repl4F_immF0_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_Replicate; }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 1; }
public:
  repl4F_immF0Node() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(repl4F_immF0Node); }
  // Rematerialize repl4F_immF0
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "repl4F_immF0";}
#endif
};

class repl2D_reg_ExNode : public MachTypeNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return repl2D_reg_Ex_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_Replicate; }
  virtual uint           oper_input_base() const { return 1; }
public:
  repl2D_reg_ExNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(repl2D_reg_ExNode); }
  // Rematerialize repl2D_reg_Ex
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "repl2D_reg_Ex";}
#endif
};

class repl2D_immD0Node : public MachTypeNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return repl2D_immD0_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_Replicate; }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 1; }
public:
  repl2D_immD0Node() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(repl2D_immD0Node); }
  // Rematerialize repl2D_immD0
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "repl2D_immD0";}
#endif
};

class repl16B_reg_ExNode : public MachTypeNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return repl16B_reg_Ex_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_Replicate; }
  virtual uint           oper_input_base() const { return 1; }
public:
  repl16B_reg_ExNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(repl16B_reg_ExNode); }
  // Rematerialize repl16B_reg_Ex
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "repl16B_reg_Ex";}
#endif
};

class repl16B_immIminus1Node : public MachTypeNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return repl16B_immIminus1_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_Replicate; }
  virtual uint           oper_input_base() const { return 1; }
public:
  repl16B_immIminus1Node() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(repl16B_immIminus1Node); }
  // Rematerialize repl16B_immIminus1
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "repl16B_immIminus1";}
#endif
};

class repl16B_immI0Node : public MachTypeNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return repl16B_immI0_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_Replicate; }
  virtual uint           oper_input_base() const { return 1; }
public:
  repl16B_immI0Node() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(repl16B_immI0Node); }
  // Rematerialize repl16B_immI0
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "repl16B_immI0";}
#endif
};

class repl2L_reg_ExNode : public MachTypeNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return repl2L_reg_Ex_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_Replicate; }
  virtual uint           oper_input_base() const { return 1; }
public:
  repl2L_reg_ExNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(repl2L_reg_ExNode); }
  // Rematerialize repl2L_reg_Ex
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "repl2L_reg_Ex";}
#endif
};

class repl2L_immIminus1Node : public MachTypeNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return repl2L_immIminus1_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_Replicate; }
  virtual uint           oper_input_base() const { return 1; }
public:
  repl2L_immIminus1Node() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(repl2L_immIminus1Node); }
  // Rematerialize repl2L_immIminus1
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "repl2L_immIminus1";}
#endif
};

class repl2L_immI0Node : public MachTypeNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return repl2L_immI0_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_Replicate; }
  virtual uint           oper_input_base() const { return 1; }
public:
  repl2L_immI0Node() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(repl2L_immI0Node); }
  // Rematerialize repl2L_immI0
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "repl2L_immI0";}
#endif
};

class storeA8BNode : public MachTypeNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return storeA8B_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_StoreVector; }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  storeA8BNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(storeA8BNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "storeA8B";}
#endif
};

class storeV16Node : public MachTypeNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return storeV16_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_StoreVector; }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  storeV16Node() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(storeV16Node); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "storeV16";}
#endif
};

class loadV8Node : public MachTypeNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return loadV8_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_LoadVector; }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  loadV8Node() {  _num_opnds = 2; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(loadV8Node); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "loadV8";}
#endif
};

class loadV16Node : public MachTypeNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return loadV16_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_LoadVector; }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  loadV16Node() {  _num_opnds = 2; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(loadV16Node); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "loadV16";}
#endif
};

class reinterpretNode : public MachTypeNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return reinterpret_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_VectorReinterpret; }
  virtual uint           two_adr() const  { return oper_input_base(); }
  virtual uint           oper_input_base() const { return 1; }
public:
  reinterpretNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(reinterpretNode); }
  // Rematerialize reinterpret
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "reinterpret";}
#endif
};

class reinterpretXNode : public MachTypeNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return reinterpretX_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_VectorReinterpret; }
  virtual uint           two_adr() const  { return oper_input_base(); }
  virtual uint           oper_input_base() const { return 1; }
public:
  reinterpretXNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(reinterpretXNode); }
  // Rematerialize reinterpretX
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "reinterpretX";}
#endif
};

class vadd16B_regNode : public MachTypeNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return vadd16B_reg_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_AddVB; }
  virtual uint           oper_input_base() const { return 1; }
public:
  vadd16B_regNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(vadd16B_regNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "vadd16B_reg";}
#endif
};

class vadd8S_regNode : public MachTypeNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return vadd8S_reg_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_AddVS; }
  virtual uint           oper_input_base() const { return 1; }
public:
  vadd8S_regNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(vadd8S_regNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "vadd8S_reg";}
#endif
};

class vadd4I_regNode : public MachTypeNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return vadd4I_reg_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_AddVI; }
  virtual uint           oper_input_base() const { return 1; }
public:
  vadd4I_regNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(vadd4I_regNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "vadd4I_reg";}
#endif
};

class vadd2L_regNode : public MachTypeNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return vadd2L_reg_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_AddVL; }
  virtual uint           oper_input_base() const { return 1; }
public:
  vadd2L_regNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(vadd2L_regNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "vadd2L_reg";}
#endif
};

class vmul16B_regNode : public MachTypeNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return vmul16B_reg_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_MulVB; }
  virtual uint           oper_input_base() const { return 1; }
public:
  vmul16B_regNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(vmul16B_regNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "vmul16B_reg";}
#endif
};

class vmul8S_regNode : public MachTypeNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return vmul8S_reg_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_MulVS; }
  virtual uint           oper_input_base() const { return 1; }
public:
  vmul8S_regNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(vmul8S_regNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "vmul8S_reg";}
#endif
};

class vmul4I_regNode : public MachTypeNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return vmul4I_reg_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_MulVI; }
  virtual uint           oper_input_base() const { return 1; }
public:
  vmul4I_regNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(vmul4I_regNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "vmul4I_reg";}
#endif
};

class vsub16B_regNode : public MachTypeNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return vsub16B_reg_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_SubVB; }
  virtual uint           oper_input_base() const { return 1; }
public:
  vsub16B_regNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(vsub16B_regNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "vsub16B_reg";}
#endif
};

class vsub8S_regNode : public MachTypeNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return vsub8S_reg_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_SubVS; }
  virtual uint           oper_input_base() const { return 1; }
public:
  vsub8S_regNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(vsub8S_regNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "vsub8S_reg";}
#endif
};

class vsub4I_regNode : public MachTypeNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return vsub4I_reg_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_SubVI; }
  virtual uint           oper_input_base() const { return 1; }
public:
  vsub4I_regNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(vsub4I_regNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "vsub4I_reg";}
#endif
};

class vsub2L_regNode : public MachTypeNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return vsub2L_reg_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_SubVL; }
  virtual uint           oper_input_base() const { return 1; }
public:
  vsub2L_regNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(vsub2L_regNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "vsub2L_reg";}
#endif
};

class vadd4F_regNode : public MachTypeNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return vadd4F_reg_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_AddVF; }
  virtual uint           oper_input_base() const { return 1; }
public:
  vadd4F_regNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(vadd4F_regNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "vadd4F_reg";}
#endif
};

class vadd2D_regNode : public MachTypeNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return vadd2D_reg_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_AddVD; }
  virtual uint           oper_input_base() const { return 1; }
public:
  vadd2D_regNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(vadd2D_regNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "vadd2D_reg";}
#endif
};

class vsub4F_regNode : public MachTypeNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return vsub4F_reg_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_SubVF; }
  virtual uint           oper_input_base() const { return 1; }
public:
  vsub4F_regNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(vsub4F_regNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "vsub4F_reg";}
#endif
};

class vsub2D_regNode : public MachTypeNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return vsub2D_reg_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_SubVD; }
  virtual uint           oper_input_base() const { return 1; }
public:
  vsub2D_regNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(vsub2D_regNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "vsub2D_reg";}
#endif
};

class vmul4F_regNode : public MachTypeNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return vmul4F_reg_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_MulVF; }
  virtual uint           oper_input_base() const { return 1; }
public:
  vmul4F_regNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(vmul4F_regNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "vmul4F_reg";}
#endif
};

class vmul2D_regNode : public MachTypeNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return vmul2D_reg_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_MulVD; }
  virtual uint           oper_input_base() const { return 1; }
public:
  vmul2D_regNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(vmul2D_regNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "vmul2D_reg";}
#endif
};

class vdiv4F_regNode : public MachTypeNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return vdiv4F_reg_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_DivVF; }
  virtual uint           oper_input_base() const { return 1; }
public:
  vdiv4F_regNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(vdiv4F_regNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "vdiv4F_reg";}
#endif
};

class vdiv2D_regNode : public MachTypeNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return vdiv2D_reg_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_DivVD; }
  virtual uint           oper_input_base() const { return 1; }
public:
  vdiv2D_regNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(vdiv2D_regNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "vdiv2D_reg";}
#endif
};

class vsqrt4F_regNode : public MachTypeNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return vsqrt4F_reg_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_SqrtVF; }
  virtual uint           oper_input_base() const { return 1; }
public:
  vsqrt4F_regNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(vsqrt4F_regNode); }
  // Rematerialize vsqrt4F_reg
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "vsqrt4F_reg";}
#endif
};

class vsqrt2D_regNode : public MachTypeNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return vsqrt2D_reg_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_SqrtVD; }
  virtual uint           oper_input_base() const { return 1; }
public:
  vsqrt2D_regNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(vsqrt2D_regNode); }
  // Rematerialize vsqrt2D_reg
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "vsqrt2D_reg";}
#endif
};

class vpopcnt_regNode : public MachTypeNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return vpopcnt_reg_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_PopCountVI; }
  virtual uint           oper_input_base() const { return 1; }
public:
  vpopcnt_regNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(vpopcnt_regNode); }
  // Rematerialize vpopcnt_reg
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "vpopcnt_reg";}
#endif
};

class vround2D_regNode : public MachTypeNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return vround2D_reg_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_RoundDoubleModeV; }
  virtual uint           oper_input_base() const { return 1; }
public:
  vround2D_regNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(vround2D_regNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "vround2D_reg";}
#endif
};

class bytes_reverse_shortNode : public MachNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return bytes_reverse_short_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_ReverseBytesS; }
public:
  bytes_reverse_shortNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(bytes_reverse_shortNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "bytes_reverse_short";}
#endif
};

class bytes_reverse_unsigned_shortNode : public MachNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return bytes_reverse_unsigned_short_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_ReverseBytesUS; }
public:
  bytes_reverse_unsigned_shortNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(bytes_reverse_unsigned_shortNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "bytes_reverse_unsigned_short";}
#endif
};

class bytes_reverse_intNode : public MachNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return bytes_reverse_int_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_ReverseBytesI; }
public:
  bytes_reverse_intNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(bytes_reverse_intNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "bytes_reverse_int";}
#endif
};

class bytes_reverse_longNode : public MachNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return bytes_reverse_long_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_ReverseBytesL; }
public:
  bytes_reverse_longNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(bytes_reverse_longNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "bytes_reverse_long";}
#endif
};

class countLeadingZerosINode : public MachNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return countLeadingZerosI_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_CountLeadingZerosI; }
public:
  countLeadingZerosINode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(countLeadingZerosINode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "countLeadingZerosI";}
#endif
};

class countLeadingZerosLNode : public MachNode { 
private:
  MachOper *_opnd_array[2];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return countLeadingZerosL_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_CountLeadingZerosL; }
public:
  countLeadingZerosLNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(countLeadingZerosLNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "countLeadingZerosL";}
#endif
};

class countTrailingZerosINode : public MachNode { 
private:
  MachOper *_opnd_array[4];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return countTrailingZerosI_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_CountTrailingZerosI; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges(); }
public:
  countTrailingZerosINode() {  _num_opnds = 4; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(countTrailingZerosINode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "countTrailingZerosI";}
#endif
};

class countTrailingZerosLNode : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return countTrailingZerosL_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_CountTrailingZerosL; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges(); }
public:
  countTrailingZerosLNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(countTrailingZerosLNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "countTrailingZerosL";}
#endif
};

class popCountI_Ext3Node : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return popCountI_Ext3_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_PopCountI; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges(); }
public:
  popCountI_Ext3Node() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(popCountI_Ext3Node); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "popCountI_Ext3";}
#endif
};

class popCountL_Ext3Node : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return popCountL_Ext3_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_PopCountL; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges(); }
public:
  popCountL_Ext3Node() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(popCountL_Ext3Node); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "popCountL_Ext3";}
#endif
};

class popCountINode : public MachNode { 
private:
  MachOper *_opnd_array[4];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return popCountI_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_PopCountI; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges(); }
public:
  popCountINode() {  _num_opnds = 4; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(popCountINode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "popCountI";}
#endif
};

class popCountLNode : public MachNode { 
private:
  MachOper *_opnd_array[4];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return popCountL_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_PopCountL; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges(); }
public:
  popCountLNode() {  _num_opnds = 4; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(popCountLNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "popCountL";}
#endif
};

class g1StorePNode : public MachTypeNode { 
private:
  MachOper *_opnd_array[5];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return g1StoreP_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_StoreP; }
  virtual uint           oper_input_base() const { return 2; }
public:
  g1StorePNode() {  _num_opnds = 5; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(g1StorePNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "g1StoreP";}
#endif
};

class g1StoreNNode : public MachTypeNode { 
private:
  MachOper *_opnd_array[6];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return g1StoreN_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_StoreN; }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  g1StoreNNode() {  _num_opnds = 6; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(g1StoreNNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "g1StoreN";}
#endif
};

class g1CompareAndSwapNNode : public MachNode { 
private:
  MachOper *_opnd_array[8];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return g1CompareAndSwapN_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_CompareAndSwapN; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges() + opnd_array(2)->num_edges() + opnd_array(3)->num_edges(); }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  g1CompareAndSwapNNode() {  _num_opnds = 8; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(g1CompareAndSwapNNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "g1CompareAndSwapN";}
#endif
};

class g1CompareAndSwapN_0Node : public MachNode { 
private:
  MachOper *_opnd_array[8];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return g1CompareAndSwapN_0_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_WeakCompareAndSwapN; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges() + opnd_array(2)->num_edges() + opnd_array(3)->num_edges(); }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  g1CompareAndSwapN_0Node() {  _num_opnds = 8; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(g1CompareAndSwapN_0Node); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "g1CompareAndSwapN_0";}
#endif
};

class g1CompareAndExchangeNNode : public MachTypeNode { 
private:
  MachOper *_opnd_array[8];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return g1CompareAndExchangeN_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_CompareAndExchangeN; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges() + opnd_array(2)->num_edges() + opnd_array(3)->num_edges(); }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  g1CompareAndExchangeNNode() {  _num_opnds = 8; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(g1CompareAndExchangeNNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "g1CompareAndExchangeN";}
#endif
};

class g1LoadNNode : public MachTypeNode { 
private:
  MachOper *_opnd_array[5];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return g1LoadN_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_LoadN; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges(); }
  virtual uint           oper_input_base() const { return 2; }
public:
  g1LoadNNode() {  _num_opnds = 5; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(g1LoadNNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "g1LoadN";}
#endif
};

class g1GetAndSetNNode : public MachTypeNode { 
private:
  MachOper *_opnd_array[7];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return g1GetAndSetN_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_GetAndSetN; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges(); }
  virtual uint           oper_input_base() const { return 2; }
public:
  g1GetAndSetNNode() {  _num_opnds = 7; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(g1GetAndSetNNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "g1GetAndSetN";}
#endif
};

class g1CompareAndSwapPNode : public MachNode { 
private:
  MachOper *_opnd_array[7];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return g1CompareAndSwapP_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_CompareAndSwapP; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges() + opnd_array(2)->num_edges() + opnd_array(3)->num_edges(); }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  g1CompareAndSwapPNode() {  _num_opnds = 7; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(g1CompareAndSwapPNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "g1CompareAndSwapP";}
#endif
};

class g1CompareAndSwapP_0Node : public MachNode { 
private:
  MachOper *_opnd_array[7];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return g1CompareAndSwapP_0_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_WeakCompareAndSwapP; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges() + opnd_array(2)->num_edges() + opnd_array(3)->num_edges(); }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  g1CompareAndSwapP_0Node() {  _num_opnds = 7; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(g1CompareAndSwapP_0Node); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "g1CompareAndSwapP_0";}
#endif
};

class g1CompareAndExchangePNode : public MachTypeNode { 
private:
  MachOper *_opnd_array[7];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return g1CompareAndExchangeP_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_CompareAndExchangeP; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges() + opnd_array(2)->num_edges() + opnd_array(3)->num_edges(); }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  g1CompareAndExchangePNode() {  _num_opnds = 7; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(g1CompareAndExchangePNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "g1CompareAndExchangeP";}
#endif
};

class g1LoadPNode : public MachTypeNode { 
private:
  MachOper *_opnd_array[4];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return g1LoadP_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_LoadP; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges(); }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  g1LoadPNode() {  _num_opnds = 4; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(g1LoadPNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "g1LoadP";}
#endif
};

class g1GetAndSetPNode : public MachTypeNode { 
private:
  MachOper *_opnd_array[6];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return g1GetAndSetP_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_GetAndSetP; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges(); }
  virtual uint           oper_input_base() const { return 2; }
public:
  g1GetAndSetPNode() {  _num_opnds = 6; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(g1GetAndSetPNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "g1GetAndSetP";}
#endif
};

class g1EncodePAndStoreNNode : public MachTypeNode { 
private:
  MachOper *_opnd_array[5];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
  virtual uint           rule() const { return g1EncodePAndStoreN_rule; }
private:
  virtual const RegMask &out_RegMask() const;
  virtual void           emit(C2_MacroAssembler *masm, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_StoreN; }
  virtual uint           oper_input_base() const { return 2; }
public:
  g1EncodePAndStoreNNode() {  _num_opnds = 5; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(g1EncodePAndStoreNNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "g1EncodePAndStoreN";}
#endif
};

//HeaderForm

#line 1584 "/work/jdk/src/hotspot/cpu/s390/s390.ad"


// Header information of the source block.
// Method declarations/definitions which are used outside
// the ad-scope can conveniently be defined here.
//
// To keep related declarations/definitions/uses close together,
// we switch between source %{ }% and source_hpp %{ }% freely as needed.
#include "opto/convertnode.hpp"
#include "oops/klass.inline.hpp"

//--------------------------------------------------------------
// Used for optimization in Compile::Shorten_branches
//--------------------------------------------------------------

class CallStubImpl {
 public:

  // call trampolines
  // Size of call trampoline stub. For add'l comments, see size_java_to_interp().
  static uint size_call_trampoline() {
    return 0; // no call trampolines on this platform
  }

  // call trampolines
  // Number of relocations needed by a call trampoline stub.
  static uint reloc_call_trampoline() {
    return 0; // No call trampolines on this platform.
  }
};


#line 23644 "ad_s390.hpp"


//HeaderForm

#line 1647 "/work/jdk/src/hotspot/cpu/s390/s390.ad"


class HandlerImpl {
 public:

  static int emit_deopt_handler(C2_MacroAssembler* masm);

  static uint size_deopt_handler() {
    return NativeCall::max_instruction_size() + MacroAssembler::jump_pcrelative_size();
  }
};

class Node::PD {
public:
  enum NodeFlags {
    _last_flag = Node::_last_flag
  };
};


#line 23670 "ad_s390.hpp"


//HeaderForm

#line 25 "/work/jdk/src/hotspot/cpu/s390/gc/g1/g1_s390.ad"


#include "gc/g1/c2/g1BarrierSetC2.hpp"
#include "gc/shared/gc_globals.hpp"


#line 23682 "ad_s390.hpp"


extern const char  register_save_policy[];
extern const char  c_reg_save_policy[];
extern const int   register_save_type[];

extern const int   reduceOp[];
extern const int   leftOp[];
extern const int   rightOp[];
extern const char *ruleName[];
extern const bool  swallowed[];
// Mapping from machine-independent opcode to boolean
// Flag cases where machine needs cloned values or instructions
extern const char must_clone[];


// Enumeration of register class names
enum machRegisterClass {
  Z_INT_REG,
  Z_NO_ODD_INT_REG,
  Z_NO_ARG_INT_REG,
  Z_RARG1_INT_REG,
  Z_RARG2_INT_REG,
  Z_RARG3_INT_REG,
  Z_RARG4_INT_REG,
  Z_RARG5_INT_REG,
  Z_RARG5_PTRN_REG,
  Z_RARG1_PTR_REG,
  Z_RARG2_PTR_REG,
  Z_RARG3_PTR_REG,
  Z_RARG4_PTR_REG,
  Z_RARG5_PTR_REG,
  Z_THREAD_PTR_REG,
  Z_R10_PTR_REG,
  Z_R11_PTR_REG,
  Z_PTR_REG,
  Z_LOCK_PTR_REG,
  Z_NO_ARG_PTR_REG,
  Z_MEMORY_PTR_REG,
  Z_R1_REGP,
  Z_R9_REGP,
  Z_RARG1_LONG_REG,
  Z_RARG2_LONG_REG,
  Z_RARG3_LONG_REG,
  Z_RARG4_LONG_REG,
  Z_RARG5_LONG_REG,
  Z_LONG_REG,
  Z_LONG_ODD_REG,
  Z_CONDITION_REG,
  Z_RSCRATCH2_BITS64_REG,
  Z_FLT_REG,
  Z_RSCRATCH1_FLT_REG,
  Z_DBL_REG,
  Z_RSCRATCH1_DBL_REG,
  Z_V_REG,
  Z_VREG_16,
  Z_VREG_17,
  Z_VREG_18,
  Z_VREG_19,
  Z_VREG_20,
  Z_VREG_21,
  Z_VREG_22,
  Z_VREG_23,
  Z_VREG_24,
  Z_VREG_25,
  STACK_SLOTS,
  DYNAMIC,
  _last_Mach_Reg_Class
};

// Register masks, one for each register class.
extern const RegMask _Z_INT_REG_mask;
inline const RegMask &Z_INT_REG_mask() { return _Z_INT_REG_mask; }
extern const RegMask _STACK_OR_Z_INT_REG_mask;
inline const RegMask &STACK_OR_Z_INT_REG_mask() { return _STACK_OR_Z_INT_REG_mask; }
extern const RegMask _Z_NO_ODD_INT_REG_mask;
inline const RegMask &Z_NO_ODD_INT_REG_mask() { return _Z_NO_ODD_INT_REG_mask; }
extern const RegMask _Z_NO_ARG_INT_REG_mask;
inline const RegMask &Z_NO_ARG_INT_REG_mask() { return _Z_NO_ARG_INT_REG_mask; }
extern const RegMask _Z_RARG1_INT_REG_mask;
inline const RegMask &Z_RARG1_INT_REG_mask() { return _Z_RARG1_INT_REG_mask; }
extern const RegMask _Z_RARG2_INT_REG_mask;
inline const RegMask &Z_RARG2_INT_REG_mask() { return _Z_RARG2_INT_REG_mask; }
extern const RegMask _Z_RARG3_INT_REG_mask;
inline const RegMask &Z_RARG3_INT_REG_mask() { return _Z_RARG3_INT_REG_mask; }
extern const RegMask _Z_RARG4_INT_REG_mask;
inline const RegMask &Z_RARG4_INT_REG_mask() { return _Z_RARG4_INT_REG_mask; }
extern const RegMask _Z_RARG5_INT_REG_mask;
inline const RegMask &Z_RARG5_INT_REG_mask() { return _Z_RARG5_INT_REG_mask; }
extern const RegMask _Z_RARG5_PTRN_REG_mask;
inline const RegMask &Z_RARG5_PTRN_REG_mask() { return _Z_RARG5_PTRN_REG_mask; }
extern const RegMask _Z_RARG1_PTR_REG_mask;
inline const RegMask &Z_RARG1_PTR_REG_mask() { return _Z_RARG1_PTR_REG_mask; }
extern const RegMask _Z_RARG2_PTR_REG_mask;
inline const RegMask &Z_RARG2_PTR_REG_mask() { return _Z_RARG2_PTR_REG_mask; }
extern const RegMask _Z_RARG3_PTR_REG_mask;
inline const RegMask &Z_RARG3_PTR_REG_mask() { return _Z_RARG3_PTR_REG_mask; }
extern const RegMask _Z_RARG4_PTR_REG_mask;
inline const RegMask &Z_RARG4_PTR_REG_mask() { return _Z_RARG4_PTR_REG_mask; }
extern const RegMask _Z_RARG5_PTR_REG_mask;
inline const RegMask &Z_RARG5_PTR_REG_mask() { return _Z_RARG5_PTR_REG_mask; }
extern const RegMask _Z_THREAD_PTR_REG_mask;
inline const RegMask &Z_THREAD_PTR_REG_mask() { return _Z_THREAD_PTR_REG_mask; }
extern const RegMask _Z_R10_PTR_REG_mask;
inline const RegMask &Z_R10_PTR_REG_mask() { return _Z_R10_PTR_REG_mask; }
extern const RegMask _Z_R11_PTR_REG_mask;
inline const RegMask &Z_R11_PTR_REG_mask() { return _Z_R11_PTR_REG_mask; }
extern const RegMask _Z_PTR_REG_mask;
inline const RegMask &Z_PTR_REG_mask() { return _Z_PTR_REG_mask; }
extern const RegMask _Z_LOCK_PTR_REG_mask;
inline const RegMask &Z_LOCK_PTR_REG_mask() { return _Z_LOCK_PTR_REG_mask; }
extern const RegMask _Z_NO_ARG_PTR_REG_mask;
inline const RegMask &Z_NO_ARG_PTR_REG_mask() { return _Z_NO_ARG_PTR_REG_mask; }
extern const RegMask _Z_MEMORY_PTR_REG_mask;
inline const RegMask &Z_MEMORY_PTR_REG_mask() { return _Z_MEMORY_PTR_REG_mask; }
extern const RegMask _Z_R1_REGP_mask;
inline const RegMask &Z_R1_REGP_mask() { return _Z_R1_REGP_mask; }
extern const RegMask _Z_R9_REGP_mask;
inline const RegMask &Z_R9_REGP_mask() { return _Z_R9_REGP_mask; }
extern const RegMask _Z_RARG1_LONG_REG_mask;
inline const RegMask &Z_RARG1_LONG_REG_mask() { return _Z_RARG1_LONG_REG_mask; }
extern const RegMask _Z_RARG2_LONG_REG_mask;
inline const RegMask &Z_RARG2_LONG_REG_mask() { return _Z_RARG2_LONG_REG_mask; }
extern const RegMask _Z_RARG3_LONG_REG_mask;
inline const RegMask &Z_RARG3_LONG_REG_mask() { return _Z_RARG3_LONG_REG_mask; }
extern const RegMask _Z_RARG4_LONG_REG_mask;
inline const RegMask &Z_RARG4_LONG_REG_mask() { return _Z_RARG4_LONG_REG_mask; }
extern const RegMask _Z_RARG5_LONG_REG_mask;
inline const RegMask &Z_RARG5_LONG_REG_mask() { return _Z_RARG5_LONG_REG_mask; }
extern const RegMask _Z_LONG_REG_mask;
inline const RegMask &Z_LONG_REG_mask() { return _Z_LONG_REG_mask; }
extern const RegMask _STACK_OR_Z_LONG_REG_mask;
inline const RegMask &STACK_OR_Z_LONG_REG_mask() { return _STACK_OR_Z_LONG_REG_mask; }
extern const RegMask _Z_LONG_ODD_REG_mask;
inline const RegMask &Z_LONG_ODD_REG_mask() { return _Z_LONG_ODD_REG_mask; }
extern const RegMask _Z_CONDITION_REG_mask;
inline const RegMask &Z_CONDITION_REG_mask() { return _Z_CONDITION_REG_mask; }
extern const RegMask _Z_RSCRATCH2_BITS64_REG_mask;
inline const RegMask &Z_RSCRATCH2_BITS64_REG_mask() { return _Z_RSCRATCH2_BITS64_REG_mask; }
extern const RegMask _Z_FLT_REG_mask;
inline const RegMask &Z_FLT_REG_mask() { return _Z_FLT_REG_mask; }
extern const RegMask _STACK_OR_Z_FLT_REG_mask;
inline const RegMask &STACK_OR_Z_FLT_REG_mask() { return _STACK_OR_Z_FLT_REG_mask; }
extern const RegMask _Z_RSCRATCH1_FLT_REG_mask;
inline const RegMask &Z_RSCRATCH1_FLT_REG_mask() { return _Z_RSCRATCH1_FLT_REG_mask; }
extern const RegMask _Z_DBL_REG_mask;
inline const RegMask &Z_DBL_REG_mask() { return _Z_DBL_REG_mask; }
extern const RegMask _STACK_OR_Z_DBL_REG_mask;
inline const RegMask &STACK_OR_Z_DBL_REG_mask() { return _STACK_OR_Z_DBL_REG_mask; }
extern const RegMask _Z_RSCRATCH1_DBL_REG_mask;
inline const RegMask &Z_RSCRATCH1_DBL_REG_mask() { return _Z_RSCRATCH1_DBL_REG_mask; }
extern const RegMask _Z_V_REG_mask;
inline const RegMask &Z_V_REG_mask() { return _Z_V_REG_mask; }
extern const RegMask _Z_VREG_16_mask;
inline const RegMask &Z_VREG_16_mask() { return _Z_VREG_16_mask; }
extern const RegMask _Z_VREG_17_mask;
inline const RegMask &Z_VREG_17_mask() { return _Z_VREG_17_mask; }
extern const RegMask _Z_VREG_18_mask;
inline const RegMask &Z_VREG_18_mask() { return _Z_VREG_18_mask; }
extern const RegMask _Z_VREG_19_mask;
inline const RegMask &Z_VREG_19_mask() { return _Z_VREG_19_mask; }
extern const RegMask _Z_VREG_20_mask;
inline const RegMask &Z_VREG_20_mask() { return _Z_VREG_20_mask; }
extern const RegMask _Z_VREG_21_mask;
inline const RegMask &Z_VREG_21_mask() { return _Z_VREG_21_mask; }
extern const RegMask _Z_VREG_22_mask;
inline const RegMask &Z_VREG_22_mask() { return _Z_VREG_22_mask; }
extern const RegMask _Z_VREG_23_mask;
inline const RegMask &Z_VREG_23_mask() { return _Z_VREG_23_mask; }
extern const RegMask _Z_VREG_24_mask;
inline const RegMask &Z_VREG_24_mask() { return _Z_VREG_24_mask; }
extern const RegMask _Z_VREG_25_mask;
inline const RegMask &Z_VREG_25_mask() { return _Z_VREG_25_mask; }
extern const RegMask _STACK_SLOTS_mask;
inline const RegMask &STACK_SLOTS_mask() { return _STACK_SLOTS_mask; }
extern const RegMask _STACK_OR_STACK_SLOTS_mask;
inline const RegMask &STACK_OR_STACK_SLOTS_mask() { return _STACK_OR_STACK_SLOTS_mask; }
extern const RegMask _DYNAMIC_mask;
inline const RegMask &DYNAMIC_mask() { return _DYNAMIC_mask; }

#endif // GENERATED_ADFILES_AD_HPP
