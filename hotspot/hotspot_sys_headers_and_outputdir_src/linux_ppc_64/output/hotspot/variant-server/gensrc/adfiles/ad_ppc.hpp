#line 1 "ad_ppc.hpp"
//
// Copyright (c) 2011, 2017, Oracle and/or its affiliates. All rights reserved.
// Copyright (c) 2012, 2017 SAP SE. All rights reserved.
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


#ifndef GENERATED_ADFILES_AD_HPP
#define GENERATED_ADFILES_AD_HPP

#include "memory/allocation.hpp"
#include "code/nativeInst.hpp"
#include "opto/machnode.hpp"
#include "opto/node.hpp"
#include "opto/regalloc.hpp"
#include "opto/subnode.hpp"
#include "opto/vectornode.hpp"

#define  DEFAULT_COST_LOW  (30)  
// value == 30 
#define  DEFAULT_COST  (100)  
// value == 100 
#define  HUGE_COST  (1000000)  
// value == 1000000 
#define  MEMORY_REF_COST_LOW  (DEFAULT_COST * 2)  
// value == 200 
#define  MEMORY_REF_COST  (DEFAULT_COST * 3)  
// value == 300 
#define  BRANCH_COST  (DEFAULT_COST * 9)  
// value == 900 
#define  CALL_COST  (DEFAULT_COST * 13)  
// value == 1300 

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
  /*    9 */  IMMI,
  /*   10 */  IMMI8,
  /*   11 */  IMMI16,
  /*   12 */  IMMIHI16,
  /*   13 */  IMMINEGPOW2,
  /*   14 */  IMMIPOW2MINUS1,
  /*   15 */  IMMIPOWEROF2,
  /*   16 */  UIMMI5,
  /*   17 */  UIMMI6,
  /*   18 */  UIMMI6_GE32,
  /*   19 */  UIMMI15,
  /*   20 */  UIMMI16,
  /*   21 */  IMMI_0,
  /*   22 */  IMMI_1,
  /*   23 */  IMMI_MINUS1,
  /*   24 */  IMMI_16,
  /*   25 */  IMMI_24,
  /*   26 */  IMMN,
  /*   27 */  IMMN_0,
  /*   28 */  IMMNKLASS,
  /*   29 */  IMMNKLASS_NM,
  /*   30 */  IMMP,
  /*   31 */  IMMP_NM,
  /*   32 */  IMMP_0,
  /*   33 */  IMMP_0OR1,
  /*   34 */  IMML,
  /*   35 */  IMMLMAX30,
  /*   36 */  IMML16,
  /*   37 */  IMML16ALG4,
  /*   38 */  IMML32HI16,
  /*   39 */  IMML32,
  /*   40 */  IMMLHIGHEST16,
  /*   41 */  IMMLNEGPOW2,
  /*   42 */  IMMLPOW2MINUS1,
  /*   43 */  IMML_0,
  /*   44 */  IMML_MINUS1,
  /*   45 */  IMML_32BITS,
  /*   46 */  UIMML16,
  /*   47 */  IMMF,
  /*   48 */  IMMF_0,
  /*   49 */  IMMD,
  /*   50 */  IREGIDST,
  /*   51 */  IREGISRC,
  /*   52 */  RSCRATCH1REGI,
  /*   53 */  RSCRATCH2REGI,
  /*   54 */  RARG1REGI,
  /*   55 */  RARG2REGI,
  /*   56 */  RARG3REGI,
  /*   57 */  RARG4REGI,
  /*   58 */  RARG1REGL,
  /*   59 */  RARG2REGL,
  /*   60 */  RARG3REGL,
  /*   61 */  RARG4REGL,
  /*   62 */  IREGPDST,
  /*   63 */  IREGPDSTNOSCRATCH,
  /*   64 */  IREGPSRC,
  /*   65 */  THREADREGP,
  /*   66 */  RSCRATCH1REGP,
  /*   67 */  RSCRATCH2REGP,
  /*   68 */  RARG1REGP,
  /*   69 */  RARG2REGP,
  /*   70 */  RARG3REGP,
  /*   71 */  RARG4REGP,
  /*   72 */  IREGNSRC,
  /*   73 */  IREGNDST,
  /*   74 */  IREGLDST,
  /*   75 */  IREGLSRC,
  /*   76 */  IREGL2ISRC,
  /*   77 */  RSCRATCH1REGL,
  /*   78 */  RSCRATCH2REGL,
  /*   79 */  FLAGSREG,
  /*   80 */  FLAGSREGSRC,
  /*   81 */  FLAGSREGCR0,
  /*   82 */  FLAGSREGCR1,
  /*   83 */  FLAGSREGCR6,
  /*   84 */  REGCTR,
  /*   85 */  REGD,
  /*   86 */  REGF,
  /*   87 */  INLINE_CACHE_REGP,
  /*   88 */  COMPILER_METHOD_OOP_REGP,
  /*   89 */  INTERPRETER_METHOD_OOP_REGP,
  /*   90 */  IREGP2N,
  /*   91 */  IREGN2P,
  /*   92 */  IREGN2P_KLASS,
  /*   93 */  INDIRECT,
  /*   94 */  INDOFFSET16,
  /*   95 */  INDOFFSET16ALG4,
  /*   96 */  INDIRECTNARROW,
  /*   97 */  INDIRECTNARROW_KLASS,
  /*   98 */  INDOFFSET16NARROW,
  /*   99 */  INDOFFSET16NARROW_KLASS,
  /*  100 */  INDOFFSET16NARROWALG4,
  /*  101 */  INDOFFSET16NARROWALG4_KLASS,
  /*  102 */  STACKSLOTI,
  /*  103 */  STACKSLOTL,
  /*  104 */  STACKSLOTP,
  /*  105 */  STACKSLOTF,
  /*  106 */  STACKSLOTD,
  /*  107 */  CMPOP,
  // last operand
  /*  108 */  MEMORY,
  /*  109 */  MEMORYALG4,
  /*  110 */  INDIRECTMEMORY,
  /*  111 */  IREGISRC_IREGL2ISRC,
  /*  112 */  IREGN_P2N,
  /*  113 */  IREGP_N2P,
  // last operand class
  /*  114 */  _DECODEN_IREGNSRC_,
  /*  115 */  _DECODENKLASS_IREGNSRC_,
  /*  116 */  _LOADUB_MEMORY_,
  /*  117 */  _LOADUS_MEMORY_,
  /*  118 */  _LOADI_MEMORY_,
  /*  119 */  _CONVI2L__LOADI_MEMORY__,
  /*  120 */  _LOADI_MEMORYALG4_,
  /*  121 */  _LOADN_MEMORY_,
  /*  122 */  _LOADNKLASS_MEMORY_,
  /*  123 */  _LOADP_MEMORYALG4_,
  /*  124 */  _ADDP_INDIRECTMEMORY_IREGLSRC,
  /*  125 */  _CONVL2I_IREGLSRC_,
  /*  126 */  _BINARY_FLAGSREGSRC_IREGPSRC,
  /*  127 */  _CASTP2X__DECODEN_IREGNSRC__,
  /*  128 */  _BINARY_IREGLSRC_IREGPDST,
  /*  129 */  _BINARY_IREGLSRC_IREGPSRC,
  /*  130 */  _BINARY_IREGLSRC_IREGNSRC,
  /*  131 */  _BINARY_CMPOP_FLAGSREGSRC,
  /*  132 */  _BINARY_IREGIDST_IREGISRC,
  /*  133 */  _BINARY_IREGIDST_IMMI16,
  /*  134 */  _BINARY_IREGLDST_IREGLSRC,
  /*  135 */  _BINARY_IREGLDST_IMML16,
  /*  136 */  _BINARY_IREGNDST_IREGNSRC,
  /*  137 */  _BINARY_IREGNDST_IMMN_0,
  /*  138 */  _BINARY_IREGPDST_IREGPSRC,
  /*  139 */  _BINARY_IREGPDST_IREGP_N2P,
  /*  140 */  _BINARY_IREGPDST_IMMP_0,
  /*  141 */  _BINARY_REGF_REGF,
  /*  142 */  _BINARY_REGD_REGD,
  /*  143 */  _BINARY_IREGLSRC_IREGLSRC,
  /*  144 */  _BINARY_IREGPSRC_IREGPSRC,
  /*  145 */  _BINARY_IREGISRC_IREGISRC,
  /*  146 */  _BINARY_IREGISRC_RARG4REGI,
  /*  147 */  _BINARY_IREGNSRC_IREGNSRC,
  /*  148 */  _ADDI_IREGISRC_IREGISRC,
  /*  149 */  _ADDI__ADDI_IREGISRC_IREGISRC_IREGISRC,
  /*  150 */  _ADDI_IREGISRC__ADDI_IREGISRC_IREGISRC,
  /*  151 */  _ADDL_IREGLSRC_IREGLSRC,
  /*  152 */  _ADDL__ADDL_IREGLSRC_IREGLSRC_IREGLSRC,
  /*  153 */  _ADDL_IREGLSRC__ADDL_IREGLSRC_IREGLSRC,
  /*  154 */  _SUBL_IREGLSRC_IREGLSRC,
  /*  155 */  _SUBL_IMML_0_IREGLSRC,
  /*  156 */  _ANDI_IREGISRC_IMMINEGPOW2,
  /*  157 */  _RSHIFTI_IREGISRC_UIMMI5,
  /*  158 */  _ANDI__RSHIFTI_IREGISRC_UIMMI5_IMMINEGPOW2,
  /*  159 */  _CONVI2L_IREGISRC_,
  /*  160 */  _RSHIFTL_IREGLSRC_IMMI,
  /*  161 */  _URSHIFTL_IREGLSRC_IMMI,
  /*  162 */  _CASTP2X_IREGP_N2P_,
  /*  163 */  _URSHIFTI_IREGISRC_IMMI,
  /*  164 */  _LSHIFTI_IREGISRC_IMMI8,
  /*  165 */  _URSHIFTI_IREGISRC_IMMI8,
  /*  166 */  _ABSF_REGF_,
  /*  167 */  _ABSD_REGD_,
  /*  168 */  _CONVF2D_REGF_,
  /*  169 */  _SQRTD__CONVF2D_REGF__,
  /*  170 */  _NEGF_REGF_,
  /*  171 */  _BINARY__NEGF_REGF__REGF,
  /*  172 */  _BINARY_REGF__NEGF_REGF_,
  /*  173 */  _NEGD_REGD_,
  /*  174 */  _BINARY__NEGD_REGD__REGD,
  /*  175 */  _BINARY_REGD__NEGD_REGD_,
  /*  176 */  _ANDL_IREGLSRC_IMMLPOW2MINUS1,
  /*  177 */  _ORI_IREGISRC_IREGISRC,
  /*  178 */  _ORI__ORI_IREGISRC_IREGISRC_IREGISRC,
  /*  179 */  _ORI_IREGISRC__ORI_IREGISRC_IREGISRC,
  /*  180 */  _ORL_IREGLSRC_IREGLSRC,
  /*  181 */  _XORI_IREGISRC_IREGISRC,
  /*  182 */  _XORI__XORI_IREGISRC_IREGISRC_IREGISRC,
  /*  183 */  _XORI_IREGISRC__XORI_IREGISRC_IREGISRC,
  /*  184 */  _XORL_IREGLSRC_IREGLSRC,
  /*  185 */  _XORI_IREGISRC_IMMI_MINUS1,
  /*  186 */  _CONV2B_IREGISRC_,
  /*  187 */  _ANDI_IREGISRC_IMMIPOWEROF2,
  /*  188 */  _CONV2B_IREGP_N2P_,
  /*  189 */  _LSHIFTI_IREGISRC_IMMI_24,
  /*  190 */  _LSHIFTI_IREGISRC_IMMI_16,
  /*  191 */  _ANDI_IREGISRC_UIMMI16,
  /*  192 */  _ANDL_IREGLSRC_IREGLSRC,
  /*  193 */  _ANDL_IREGLSRC_UIMML16,
  /*  194 */  _CMPU_IREGISRC_UIMMI15,
  /*  195 */  _CMPU_IREGISRC_IREGISRC,
  /*  196 */  _CMPN_IREGNSRC_IMMN_0,
  /*  197 */  _CMPP_IREGP_N2P_IMMP_0,
  /*  198 */  _CASTP2X_IREGPSRC_,
  /*  199 */  _ANDL__CASTP2X_IREGPSRC__IMMLNEGPOW2,
  /*  200 */  _BINARY_RARG1REGP_RARG3REGI,
  /*  201 */  _BINARY_RARG2REGP_RARG4REGI,
  /*  202 */  _BINARY_RARG1REGP_RARG2REGP,
  /*  203 */  _BINARY_IREGPSRC_IREGISRC,
  /*  204 */  _ADDP_IMMP_IMML,
  /*  205 */  _BINARY__ADDP_IMMP_IMML_IMMI_1,
  /*  206 */  _BINARY_RSCRATCH2REGP_IMMI_1,
  /*  207 */  _BINARY_IREGPSRC_RSCRATCH1REGI,
  /*  208 */  _BINARY_IREGPSRC_UIMMI15,
  /*  209 */  _BINARY_IREGPSRC_RSCRATCH2REGI,
  /*  210 */  _BINARY_RARG2REGP_IREGISRC,
  /*  211 */  _LOADI_INDIRECT_,
  /*  212 */  _LOADL_INDIRECT_,
  /*  213 */  _LOADUS_INDIRECT_,
  /*  214 */  _LOADS_INDIRECT_,
  /*  215 */  _REVERSEBYTESI_IREGISRC_,
  /*  216 */  _REVERSEBYTESL_IREGLSRC_,
  /*  217 */  _REVERSEBYTESUS_IREGISRC_,
  /*  218 */  _REVERSEBYTESS_IREGISRC_,
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
  /*    9 */  immI_rule,
  /*   10 */  immI8_rule,
  /*   11 */  immI16_rule,
  /*   12 */  immIhi16_rule,
  /*   13 */  immInegpow2_rule,
  /*   14 */  immIpow2minus1_rule,
  /*   15 */  immIpowerOf2_rule,
  /*   16 */  uimmI5_rule,
  /*   17 */  uimmI6_rule,
  /*   18 */  uimmI6_ge32_rule,
  /*   19 */  uimmI15_rule,
  /*   20 */  uimmI16_rule,
  /*   21 */  immI_0_rule,
  /*   22 */  immI_1_rule,
  /*   23 */  immI_minus1_rule,
  /*   24 */  immI_16_rule,
  /*   25 */  immI_24_rule,
  /*   26 */  immN_rule,
  /*   27 */  immN_0_rule,
  /*   28 */  immNKlass_rule,
  /*   29 */  immNKlass_NM_rule,
  /*   30 */  immP_rule,
  /*   31 */  immP_NM_rule,
  /*   32 */  immP_0_rule,
  /*   33 */  immP_0or1_rule,
  /*   34 */  immL_rule,
  /*   35 */  immLmax30_rule,
  /*   36 */  immL16_rule,
  /*   37 */  immL16Alg4_rule,
  /*   38 */  immL32hi16_rule,
  /*   39 */  immL32_rule,
  /*   40 */  immLhighest16_rule,
  /*   41 */  immLnegpow2_rule,
  /*   42 */  immLpow2minus1_rule,
  /*   43 */  immL_0_rule,
  /*   44 */  immL_minus1_rule,
  /*   45 */  immL_32bits_rule,
  /*   46 */  uimmL16_rule,
  /*   47 */  immF_rule,
  /*   48 */  immF_0_rule,
  /*   49 */  immD_rule,
  /*   50 */  iRegIdst_rule,
  /*   51 */  iRegIsrc_rule,
  /*   52 */  rscratch1RegI_rule,
  /*   53 */  rscratch2RegI_rule,
  /*   54 */  rarg1RegI_rule,
  /*   55 */  rarg2RegI_rule,
  /*   56 */  rarg3RegI_rule,
  /*   57 */  rarg4RegI_rule,
  /*   58 */  rarg1RegL_rule,
  /*   59 */  rarg2RegL_rule,
  /*   60 */  rarg3RegL_rule,
  /*   61 */  rarg4RegL_rule,
  /*   62 */  iRegPdst_rule,
  /*   63 */  iRegPdstNoScratch_rule,
  /*   64 */  iRegPsrc_rule,
  /*   65 */  threadRegP_rule,
  /*   66 */  rscratch1RegP_rule,
  /*   67 */  rscratch2RegP_rule,
  /*   68 */  rarg1RegP_rule,
  /*   69 */  rarg2RegP_rule,
  /*   70 */  rarg3RegP_rule,
  /*   71 */  rarg4RegP_rule,
  /*   72 */  iRegNsrc_rule,
  /*   73 */  iRegNdst_rule,
  /*   74 */  iRegLdst_rule,
  /*   75 */  iRegLsrc_rule,
  /*   76 */  iRegL2Isrc_rule,
  /*   77 */  rscratch1RegL_rule,
  /*   78 */  rscratch2RegL_rule,
  /*   79 */  flagsReg_rule,
  /*   80 */  flagsRegSrc_rule,
  /*   81 */  flagsRegCR0_rule,
  /*   82 */  flagsRegCR1_rule,
  /*   83 */  flagsRegCR6_rule,
  /*   84 */  regCTR_rule,
  /*   85 */  regD_rule,
  /*   86 */  regF_rule,
  /*   87 */  inline_cache_regP_rule,
  /*   88 */  compiler_method_oop_regP_rule,
  /*   89 */  interpreter_method_oop_regP_rule,
  /*   90 */  iRegP2N_rule,
  /*   91 */  iRegN2P_rule,
  /*   92 */  iRegN2P_klass_rule,
  /*   93 */  indirect_rule,
  /*   94 */  indOffset16_rule,
  /*   95 */  indOffset16Alg4_rule,
  /*   96 */  indirectNarrow_rule,
  /*   97 */  indirectNarrow_klass_rule,
  /*   98 */  indOffset16Narrow_rule,
  /*   99 */  indOffset16Narrow_klass_rule,
  /*  100 */  indOffset16NarrowAlg4_rule,
  /*  101 */  indOffset16NarrowAlg4_klass_rule,
  /*  102 */  stackSlotI_rule,
  /*  103 */  stackSlotL_rule,
  /*  104 */  stackSlotP_rule,
  /*  105 */  stackSlotF_rule,
  /*  106 */  stackSlotD_rule,
  /*  107 */  cmpOp_rule,
  // last operand
  /*  108 */  memory_rule,
  /*  109 */  memoryAlg4_rule,
  /*  110 */  indirectMemory_rule,
  /*  111 */  iRegIsrc_iRegL2Isrc_rule,
  /*  112 */  iRegN_P2N_rule,
  /*  113 */  iRegP_N2P_rule,
  // last operand class
  /*  114 */  _DecodeN_iRegNsrc__rule,
  /*  115 */  _DecodeNKlass_iRegNsrc__rule,
  /*  116 */  _LoadUB_memory__rule,
  /*  117 */  _LoadUS_memory__rule,
  /*  118 */  _LoadI_memory__rule,
  /*  119 */  _ConvI2L__LoadI_memory___rule,
  /*  120 */  _LoadI_memoryAlg4__rule,
  /*  121 */  _LoadN_memory__rule,
  /*  122 */  _LoadNKlass_memory__rule,
  /*  123 */  _LoadP_memoryAlg4__rule,
  /*  124 */  _AddP_indirectMemory_iRegLsrc_rule,
  /*  125 */  _ConvL2I_iRegLsrc__rule,
  /*  126 */  _Binary_flagsRegSrc_iRegPsrc_rule,
  /*  127 */  _CastP2X__DecodeN_iRegNsrc___rule,
  /*  128 */  _Binary_iRegLsrc_iRegPdst_rule,
  /*  129 */  _Binary_iRegLsrc_iRegPsrc_rule,
  /*  130 */  _Binary_iRegLsrc_iRegNsrc_rule,
  /*  131 */  _Binary_cmpOp_flagsRegSrc_rule,
  /*  132 */  _Binary_iRegIdst_iRegIsrc_rule,
  /*  133 */  _Binary_iRegIdst_immI16_rule,
  /*  134 */  _Binary_iRegLdst_iRegLsrc_rule,
  /*  135 */  _Binary_iRegLdst_immL16_rule,
  /*  136 */  _Binary_iRegNdst_iRegNsrc_rule,
  /*  137 */  _Binary_iRegNdst_immN_0_rule,
  /*  138 */  _Binary_iRegPdst_iRegPsrc_rule,
  /*  139 */  _Binary_iRegPdst_iRegP_N2P_rule,
  /*  140 */  _Binary_iRegPdst_immP_0_rule,
  /*  141 */  _Binary_regF_regF_rule,
  /*  142 */  _Binary_regD_regD_rule,
  /*  143 */  _Binary_iRegLsrc_iRegLsrc_rule,
  /*  144 */  _Binary_iRegPsrc_iRegPsrc_rule,
  /*  145 */  _Binary_iRegIsrc_iRegIsrc_rule,
  /*  146 */  _Binary_iRegIsrc_rarg4RegI_rule,
  /*  147 */  _Binary_iRegNsrc_iRegNsrc_rule,
  /*  148 */  _AddI_iRegIsrc_iRegIsrc_rule,
  /*  149 */  _AddI__AddI_iRegIsrc_iRegIsrc_iRegIsrc_rule,
  /*  150 */  _AddI_iRegIsrc__AddI_iRegIsrc_iRegIsrc_rule,
  /*  151 */  _AddL_iRegLsrc_iRegLsrc_rule,
  /*  152 */  _AddL__AddL_iRegLsrc_iRegLsrc_iRegLsrc_rule,
  /*  153 */  _AddL_iRegLsrc__AddL_iRegLsrc_iRegLsrc_rule,
  /*  154 */  _SubL_iRegLsrc_iRegLsrc_rule,
  /*  155 */  _SubL_immL_0_iRegLsrc_rule,
  /*  156 */  _AndI_iRegIsrc_immInegpow2_rule,
  /*  157 */  _RShiftI_iRegIsrc_uimmI5_rule,
  /*  158 */  _AndI__RShiftI_iRegIsrc_uimmI5_immInegpow2_rule,
  /*  159 */  _ConvI2L_iRegIsrc__rule,
  /*  160 */  _RShiftL_iRegLsrc_immI_rule,
  /*  161 */  _URShiftL_iRegLsrc_immI_rule,
  /*  162 */  _CastP2X_iRegP_N2P__rule,
  /*  163 */  _URShiftI_iRegIsrc_immI_rule,
  /*  164 */  _LShiftI_iRegIsrc_immI8_rule,
  /*  165 */  _URShiftI_iRegIsrc_immI8_rule,
  /*  166 */  _AbsF_regF__rule,
  /*  167 */  _AbsD_regD__rule,
  /*  168 */  _ConvF2D_regF__rule,
  /*  169 */  _SqrtD__ConvF2D_regF___rule,
  /*  170 */  _NegF_regF__rule,
  /*  171 */  _Binary__NegF_regF__regF_rule,
  /*  172 */  _Binary_regF__NegF_regF__rule,
  /*  173 */  _NegD_regD__rule,
  /*  174 */  _Binary__NegD_regD__regD_rule,
  /*  175 */  _Binary_regD__NegD_regD__rule,
  /*  176 */  _AndL_iRegLsrc_immLpow2minus1_rule,
  /*  177 */  _OrI_iRegIsrc_iRegIsrc_rule,
  /*  178 */  _OrI__OrI_iRegIsrc_iRegIsrc_iRegIsrc_rule,
  /*  179 */  _OrI_iRegIsrc__OrI_iRegIsrc_iRegIsrc_rule,
  /*  180 */  _OrL_iRegLsrc_iRegLsrc_rule,
  /*  181 */  _XorI_iRegIsrc_iRegIsrc_rule,
  /*  182 */  _XorI__XorI_iRegIsrc_iRegIsrc_iRegIsrc_rule,
  /*  183 */  _XorI_iRegIsrc__XorI_iRegIsrc_iRegIsrc_rule,
  /*  184 */  _XorL_iRegLsrc_iRegLsrc_rule,
  /*  185 */  _XorI_iRegIsrc_immI_minus1_rule,
  /*  186 */  _Conv2B_iRegIsrc__rule,
  /*  187 */  _AndI_iRegIsrc_immIpowerOf2_rule,
  /*  188 */  _Conv2B_iRegP_N2P__rule,
  /*  189 */  _LShiftI_iRegIsrc_immI_24_rule,
  /*  190 */  _LShiftI_iRegIsrc_immI_16_rule,
  /*  191 */  _AndI_iRegIsrc_uimmI16_rule,
  /*  192 */  _AndL_iRegLsrc_iRegLsrc_rule,
  /*  193 */  _AndL_iRegLsrc_uimmL16_rule,
  /*  194 */  _CmpU_iRegIsrc_uimmI15_rule,
  /*  195 */  _CmpU_iRegIsrc_iRegIsrc_rule,
  /*  196 */  _CmpN_iRegNsrc_immN_0_rule,
  /*  197 */  _CmpP_iRegP_N2P_immP_0_rule,
  /*  198 */  _CastP2X_iRegPsrc__rule,
  /*  199 */  _AndL__CastP2X_iRegPsrc__immLnegpow2_rule,
  /*  200 */  _Binary_rarg1RegP_rarg3RegI_rule,
  /*  201 */  _Binary_rarg2RegP_rarg4RegI_rule,
  /*  202 */  _Binary_rarg1RegP_rarg2RegP_rule,
  /*  203 */  _Binary_iRegPsrc_iRegIsrc_rule,
  /*  204 */  _AddP_immP_immL_rule,
  /*  205 */  _Binary__AddP_immP_immL_immI_1_rule,
  /*  206 */  _Binary_rscratch2RegP_immI_1_rule,
  /*  207 */  _Binary_iRegPsrc_rscratch1RegI_rule,
  /*  208 */  _Binary_iRegPsrc_uimmI15_rule,
  /*  209 */  _Binary_iRegPsrc_rscratch2RegI_rule,
  /*  210 */  _Binary_rarg2RegP_iRegIsrc_rule,
  /*  211 */  _LoadI_indirect__rule,
  /*  212 */  _LoadL_indirect__rule,
  /*  213 */  _LoadUS_indirect__rule,
  /*  214 */  _LoadS_indirect__rule,
  /*  215 */  _ReverseBytesI_iRegIsrc__rule,
  /*  216 */  _ReverseBytesL_iRegLsrc__rule,
  /*  217 */  _ReverseBytesUS_iRegIsrc__rule,
  /*  218 */  _ReverseBytesS_iRegIsrc__rule,
  // last internally defined operand
  /*  219 */  regI_to_stkI_rule,
  /*  220 */  regL_to_stkL_rule,
  /*  221 */  loadConI16_rule,
  /*  222 */  loadConIhi16_rule,
  /*  223 */  loadConI_Ex_rule,
  /*  224 */  loadConL16_rule,
  /*  225 */  loadConL32hi16_rule,
  /*  226 */  loadConL32_Ex_rule,
  /*  227 */  loadConLhighest16_Ex_rule,
  /*  228 */  loadConL_Ex_rule,
  /*  229 */  loadConN0_rule,
  /*  230 */  loadConN_Ex_rule,
  /*  231 */  loadConNKlass_hi_rule,
  /*  232 */  loadConNKlass_mask_rule,
  /*  233 */  loadConNKlass_lo_rule,
  /*  234 */  loadConNKlass_Ex_rule,
  /*  235 */  loadConP0or1_rule,
  /*  236 */  loadConP_rule,
  /*  237 */  loadConP_lo_rule,
  /*  238 */  loadConP_Ex_rule,
  /*  239 */  loadConF_Ex_rule,
  /*  240 */  loadConD_Ex_rule,
  /*  241 */  stkI_to_regI_rule,
  /*  242 */  stkL_to_regL_rule,
  /*  243 */  convB2I_reg_2_rule,
  /*  244 */  loadP2X_rule,
  /*  245 */  loadToc_lo_rule,
  /*  246 */  loadConN_hi_rule,
  /*  247 */  clearMs32b_rule,
  /*  248 */  storeLConditional_regP_regL_regL_rule,
  /*  249 */  storePConditional_regP_regP_regP_rule,
  /*  250 */  signmask32I_regI_rule,
  /*  251 */  absI_reg_Ex_rule,
  /*  252 */  signmask64I_regL_rule,
  /*  253 */  signmask64L_regL_rule,
  /*  254 */  absF_reg_rule,
  /*  255 */  absD_reg_rule,
  /*  256 */  negF_reg_rule,
  /*  257 */  negD_reg_rule,
  /*  258 */  negF_absF_reg_rule,
  /*  259 */  negD_absD_reg_rule,
  /*  260 */  roundDouble_nop_rule,
  /*  261 */  roundFloat_nop_rule,
  /*  262 */  moveL2D_reg_rule,
  /*  263 */  moveI2D_reg_rule,
  /*  264 */  moveF2I_stack_reg_rule,
  /*  265 */  moveI2F_stack_reg_rule,
  /*  266 */  moveD2L_stack_reg_rule,
  /*  267 */  moveL2D_stack_reg_rule,
  /*  268 */  moveReg_rule,
  /*  269 */  castX2P_rule,
  /*  270 */  castP2X_rule,
  /*  271 */  castPP_rule,
  /*  272 */  castII_rule,
  /*  273 */  checkCastPP_rule,
  /*  274 */  convI2Bool_reg__cntlz_Ex_rule,
  /*  275 */  convP2Bool_reg__cntlz_Ex_rule,
  /*  276 */  extsh_rule,
  /*  277 */  convD2IRaw_regD_rule,
  /*  278 */  convF2IRaw_regF_rule,
  /*  279 */  convF2LRaw_regF_rule,
  /*  280 */  convD2LRaw_regD_rule,
  /*  281 */  convL2DRaw_regD_rule,
  /*  282 */  convL2FRaw_regF_rule,
  /*  283 */  cmpI_reg_reg_rule,
  /*  284 */  cmpI_reg_imm16_rule,
  /*  285 */  testI_reg_imm_rule,
  /*  286 */  cmpL_reg_reg_rule,
  /*  287 */  cmpL_reg_imm16_rule,
  /*  288 */  cmpUL_reg_reg_rule,
  /*  289 */  cmpUL_reg_imm16_rule,
  /*  290 */  testL_reg_reg_rule,
  /*  291 */  testL_reg_imm_rule,
  /*  292 */  cmovI_conIvalueMinus1_conIvalue1_rule,
  /*  293 */  cmovI_conIvalueMinus1_conIvalue0_conIvalue1_Ex_rule,
  /*  294 */  compU_reg_reg_rule,
  /*  295 */  compU_reg_uimm16_rule,
  /*  296 */  cmpN_reg_reg_rule,
  /*  297 */  cmpN_reg_imm0_rule,
  /*  298 */  cmpP_reg_reg_rule,
  /*  299 */  cmpP_reg_null_rule,
  /*  300 */  cmpP_reg_imm16_rule,
  /*  301 */  cmpFUnordered_reg_reg_rule,
  /*  302 */  cmov_bns_less_rule,
  /*  303 */  cmpF_reg_reg_Ex_rule,
  /*  304 */  cmpDUnordered_reg_reg_rule,
  /*  305 */  cmpD_reg_reg_Ex_rule,
  /*  306 */  cmpFastLock_rule,
  /*  307 */  cmpFastLock_tm_rule,
  /*  308 */  cmpFastUnlock_rule,
  /*  309 */  cmpFastUnlock_tm_rule,
  /*  310 */  popCountI_rule,
  /*  311 */  popCountL_rule,
  /*  312 */  countLeadingZerosI_rule,
  /*  313 */  countLeadingZerosL_rule,
  /*  314 */  countLeadingZerosP_rule,
  /*  315 */  countTrailingZerosI_Ex_rule,
  /*  316 */  countTrailingZerosL_Ex_rule,
  /*  317 */  mtvsrwz_rule,
  /*  318 */  repl32_rule,
  /*  319 */  repl48_rule,
  /*  320 */  repl56_rule,
  /*  321 */  overflowAddL_reg_reg_rule,
  /*  322 */  overflowSubL_reg_reg_rule,
  /*  323 */  overflowNegL_reg_rule,
  /*  324 */  overflowMulL_reg_reg_rule,
  /*  325 */  mtvsrd_rule,
  /*  326 */  CallLeafDirect_mtctr_rule,
  /*  327 */  tlsLoadP_rule,
  /*  328 */  loadUB_indirect_rule,
  /*  329 */  loadUB_indirect_ac_rule,
  /*  330 */  loadB_indirect_Ex_rule,
  /*  331 */  loadB_indirect_ac_Ex_rule,
  /*  332 */  loadUB_indOffset16_rule,
  /*  333 */  loadUB_indOffset16_ac_rule,
  /*  334 */  loadB_indOffset16_Ex_rule,
  /*  335 */  loadB_indOffset16_ac_Ex_rule,
  /*  336 */  loadUB_rule,
  /*  337 */  loadUB_ac_rule,
  /*  338 */  loadUB2L_rule,
  /*  339 */  loadUB2L_ac_rule,
  /*  340 */  loadS_rule,
  /*  341 */  loadS_ac_rule,
  /*  342 */  loadUS_rule,
  /*  343 */  loadUS_ac_rule,
  /*  344 */  loadUS2L_rule,
  /*  345 */  loadUS2L_ac_rule,
  /*  346 */  loadI_rule,
  /*  347 */  loadI_ac_rule,
  /*  348 */  loadUI2L_rule,
  /*  349 */  loadI2L_rule,
  /*  350 */  loadI2L_ac_rule,
  /*  351 */  loadL_rule,
  /*  352 */  loadL_ac_rule,
  /*  353 */  loadL_unaligned_rule,
  /*  354 */  loadV8_rule,
  /*  355 */  loadV16_rule,
  /*  356 */  loadRange_rule,
  /*  357 */  loadN_rule,
  /*  358 */  loadN_ac_rule,
  /*  359 */  loadN2P_unscaled_rule,
  /*  360 */  loadN2P_klass_unscaled_rule,
  /*  361 */  loadP_rule,
  /*  362 */  loadP_ac_rule,
  /*  363 */  loadNKlass_rule,
  /*  364 */  loadKlass_rule,
  /*  365 */  loadF_rule,
  /*  366 */  loadF_ac_rule,
  /*  367 */  loadD_rule,
  /*  368 */  loadD_ac_rule,
  /*  369 */  loadD_unaligned_rule,
  /*  370 */  loadToc_hi_rule,
  /*  371 */  loadConI32_lo16_rule,
  /*  372 */  loadConL32_lo16_rule,
  /*  373 */  loadConL_rule,
  /*  374 */  loadConL_hi_rule,
  /*  375 */  loadConL_lo_rule,
  /*  376 */  loadConN_lo_rule,
  /*  377 */  rldicl_rule,
  /*  378 */  loadBase_rule,
  /*  379 */  loadConP_hi_rule,
  /*  380 */  loadConF_rule,
  /*  381 */  loadConFComp_rule,
  /*  382 */  loadConD_rule,
  /*  383 */  loadConDComp_rule,
  /*  384 */  prefetch_alloc_zero_rule,
  /*  385 */  prefetch_alloc_zero_no_offset_rule,
  /*  386 */  prefetch_alloc_rule,
  /*  387 */  prefetch_alloc_no_offset_rule,
  /*  388 */  storeB_rule,
  /*  389 */  storeC_rule,
  /*  390 */  storeI_rule,
  /*  391 */  storeI_convL2I_rule,
  /*  392 */  storeL_rule,
  /*  393 */  storeA8B_rule,
  /*  394 */  storeV16_rule,
  /*  395 */  storeN_rule,
  /*  396 */  storeNKlass_rule,
  /*  397 */  storeP_rule,
  /*  398 */  storeF_rule,
  /*  399 */  storeD_rule,
  /*  400 */  storeCM_CMS_rule,
  /*  401 */  storeCM_CMS_ExEx_rule,
  /*  402 */  storeCM_G1_rule,
  /*  403 */  encodeP_shift_rule,
  /*  404 */  encodeP_sub_rule,
  /*  405 */  cond_sub_base_rule,
  /*  406 */  cond_set_0_oop_rule,
  /*  407 */  encodeP_Disjoint_rule,
  /*  408 */  encodeP_Ex_rule,
  /*  409 */  encodeP_not_null_Ex_rule,
  /*  410 */  encodeP_not_null_base_null_rule,
  /*  411 */  encodeP_narrow_oop_shift_0_rule,
  /*  412 */  decodeN_shift_rule,
  /*  413 */  decodeN_add_rule,
  /*  414 */  cond_add_base_rule,
  /*  415 */  cond_set_0_ptr_rule,
  /*  416 */  decodeN_Ex_rule,
  /*  417 */  decodeN_nullBase_rule,
  /*  418 */  decodeN_mergeDisjoint_rule,
  /*  419 */  decodeN_Disjoint_notNull_Ex_rule,
  /*  420 */  decodeN_Disjoint_isel_Ex_rule,
  /*  421 */  decodeN_notNull_addBase_Ex_rule,
  /*  422 */  decodeN_unscaled_rule,
  /*  423 */  decodeN2I_unscaled_rule,
  /*  424 */  encodePKlass_shift_rule,
  /*  425 */  encodePKlass_sub_base_rule,
  /*  426 */  encodePKlass_Disjoint_rule,
  /*  427 */  encodePKlass_not_null_Ex_rule,
  /*  428 */  encodePKlass_not_null_ExEx_rule,
  /*  429 */  decodeNKlass_shift_rule,
  /*  430 */  decodeNKlass_add_base_rule,
  /*  431 */  decodeNKlass_notNull_addBase_Ex_rule,
  /*  432 */  decodeNKlass_notNull_addBase_ExEx_rule,
  /*  433 */  membar_acquire_rule,
  /*  434 */  unnecessary_membar_acquire_rule,
  /*  435 */  membar_acquire_lock_rule,
  /*  436 */  membar_release_rule,
  /*  437 */  membar_release_0_rule,
  /*  438 */  membar_storestore_rule,
  /*  439 */  membar_release_lock_rule,
  /*  440 */  membar_volatile_rule,
  /*  441 */  membar_CPUOrder_rule,
  /*  442 */  cmovI_reg_isel_rule,
  /*  443 */  cmovI_reg_rule,
  /*  444 */  cmovI_imm_rule,
  /*  445 */  cmovL_reg_isel_rule,
  /*  446 */  cmovL_reg_rule,
  /*  447 */  cmovL_imm_rule,
  /*  448 */  cmovN_reg_isel_rule,
  /*  449 */  cmovN_reg_rule,
  /*  450 */  cmovN_imm_rule,
  /*  451 */  cmovP_reg_isel_rule,
  /*  452 */  cmovP_reg_rule,
  /*  453 */  cmovP_imm_rule,
  /*  454 */  cmovF_reg_rule,
  /*  455 */  cmovD_reg_rule,
  /*  456 */  loadPLocked_rule,
  /*  457 */  compareAndSwapB_regP_regI_regI_rule,
  /*  458 */  compareAndSwapB4_regP_regI_regI_rule,
  /*  459 */  compareAndSwapS_regP_regI_regI_rule,
  /*  460 */  compareAndSwapS4_regP_regI_regI_rule,
  /*  461 */  compareAndSwapI_regP_regI_regI_rule,
  /*  462 */  compareAndSwapN_regP_regN_regN_rule,
  /*  463 */  compareAndSwapL_regP_regL_regL_rule,
  /*  464 */  compareAndSwapP_regP_regP_regP_rule,
  /*  465 */  weakCompareAndSwapB_regP_regI_regI_rule,
  /*  466 */  weakCompareAndSwapB4_regP_regI_regI_rule,
  /*  467 */  weakCompareAndSwapB_acq_regP_regI_regI_rule,
  /*  468 */  weakCompareAndSwapB4_acq_regP_regI_regI_rule,
  /*  469 */  weakCompareAndSwapS_regP_regI_regI_rule,
  /*  470 */  weakCompareAndSwapS4_regP_regI_regI_rule,
  /*  471 */  weakCompareAndSwapS_acq_regP_regI_regI_rule,
  /*  472 */  weakCompareAndSwapS4_acq_regP_regI_regI_rule,
  /*  473 */  weakCompareAndSwapI_regP_regI_regI_rule,
  /*  474 */  weakCompareAndSwapI_acq_regP_regI_regI_rule,
  /*  475 */  weakCompareAndSwapN_regP_regN_regN_rule,
  /*  476 */  weakCompareAndSwapN_acq_regP_regN_regN_rule,
  /*  477 */  weakCompareAndSwapL_regP_regL_regL_rule,
  /*  478 */  weakCompareAndSwapL_acq_regP_regL_regL_rule,
  /*  479 */  weakCompareAndSwapP_regP_regP_regP_rule,
  /*  480 */  weakCompareAndSwapP_acq_regP_regP_regP_rule,
  /*  481 */  compareAndExchangeB_regP_regI_regI_rule,
  /*  482 */  compareAndExchangeB4_regP_regI_regI_rule,
  /*  483 */  compareAndExchangeB_acq_regP_regI_regI_rule,
  /*  484 */  compareAndExchangeB4_acq_regP_regI_regI_rule,
  /*  485 */  compareAndExchangeS_regP_regI_regI_rule,
  /*  486 */  compareAndExchangeS4_regP_regI_regI_rule,
  /*  487 */  compareAndExchangeS_acq_regP_regI_regI_rule,
  /*  488 */  compareAndExchangeS4_acq_regP_regI_regI_rule,
  /*  489 */  compareAndExchangeI_regP_regI_regI_rule,
  /*  490 */  compareAndExchangeI_acq_regP_regI_regI_rule,
  /*  491 */  compareAndExchangeN_regP_regN_regN_rule,
  /*  492 */  compareAndExchangeN_acq_regP_regN_regN_rule,
  /*  493 */  compareAndExchangeL_regP_regL_regL_rule,
  /*  494 */  compareAndExchangeL_acq_regP_regL_regL_rule,
  /*  495 */  compareAndExchangeP_regP_regP_regP_rule,
  /*  496 */  compareAndExchangeP_acq_regP_regP_regP_rule,
  /*  497 */  getAndAddB_rule,
  /*  498 */  getAndAddB4_rule,
  /*  499 */  getAndAddS_rule,
  /*  500 */  getAndAddS4_rule,
  /*  501 */  getAndAddI_rule,
  /*  502 */  getAndAddL_rule,
  /*  503 */  getAndSetB_rule,
  /*  504 */  getAndSetB4_rule,
  /*  505 */  getAndSetS_rule,
  /*  506 */  getAndSetS4_rule,
  /*  507 */  getAndSetI_rule,
  /*  508 */  getAndSetL_rule,
  /*  509 */  getAndSetP_rule,
  /*  510 */  getAndSetN_rule,
  /*  511 */  addI_reg_reg_rule,
  /*  512 */  addI_reg_reg_2_rule,
  /*  513 */  tree_addI_addI_addI_reg_reg_Ex_rule,
  /*  514 */  tree_addI_addI_addI_reg_reg_Ex_1_rule,
  /*  515 */  tree_addI_addI_addI_reg_reg_Ex_0_rule,
  /*  516 */  tree_addI_addI_addI_reg_reg_Ex_2_rule,
  /*  517 */  addI_reg_imm16_rule,
  /*  518 */  addI_reg_immhi16_rule,
  /*  519 */  addL_reg_reg_rule,
  /*  520 */  addL_reg_reg_2_rule,
  /*  521 */  tree_addL_addL_addL_reg_reg_Ex_rule,
  /*  522 */  tree_addL_addL_addL_reg_reg_Ex_1_rule,
  /*  523 */  tree_addL_addL_addL_reg_reg_Ex_0_rule,
  /*  524 */  tree_addL_addL_addL_reg_reg_Ex_2_rule,
  /*  525 */  addI_regL_regL_rule,
  /*  526 */  addL_reg_imm16_rule,
  /*  527 */  addL_reg_immhi16_rule,
  /*  528 */  addP_reg_reg_rule,
  /*  529 */  addP_reg_imm16_rule,
  /*  530 */  addP_reg_immhi16_rule,
  /*  531 */  subI_reg_reg_rule,
  /*  532 */  subI_imm16_reg_rule,
  /*  533 */  negI_regI_rule,
  /*  534 */  subL_reg_reg_rule,
  /*  535 */  subI_regL_regL_rule,
  /*  536 */  negL_reg_reg_rule,
  /*  537 */  negI_con0_regL_rule,
  /*  538 */  mulI_reg_reg_rule,
  /*  539 */  mulI_reg_imm16_rule,
  /*  540 */  mulL_reg_reg_rule,
  /*  541 */  mulHighL_reg_reg_rule,
  /*  542 */  mulL_reg_imm16_rule,
  /*  543 */  divI_reg_immIvalueMinus1_rule,
  /*  544 */  divI_reg_regnotMinus1_rule,
  /*  545 */  cmovI_bne_negI_reg_rule,
  /*  546 */  divI_reg_reg_Ex_rule,
  /*  547 */  divL_reg_immLvalueMinus1_rule,
  /*  548 */  divL_reg_regnotMinus1_rule,
  /*  549 */  cmovL_bne_negL_reg_rule,
  /*  550 */  divL_reg_reg_Ex_rule,
  /*  551 */  modI_reg_reg_Ex_rule,
  /*  552 */  modL_reg_reg_Ex_rule,
  /*  553 */  maskI_reg_imm_rule,
  /*  554 */  lShiftI_reg_reg_rule,
  /*  555 */  lShiftI_reg_reg_Ex_rule,
  /*  556 */  lShiftI_reg_imm_rule,
  /*  557 */  lShiftI_andI_immInegpow2_imm5_rule,
  /*  558 */  lShiftI_andI_immInegpow2_rShiftI_imm5_rule,
  /*  559 */  lShiftL_regL_regI_rule,
  /*  560 */  lShiftL_regL_regI_Ex_rule,
  /*  561 */  lshiftL_regL_immI_rule,
  /*  562 */  lShiftL_regI_immGE32_rule,
  /*  563 */  scaledPositiveI2L_lShiftL_convI2L_reg_imm6_rule,
  /*  564 */  arShiftI_reg_reg_rule,
  /*  565 */  arShiftI_reg_reg_Ex_rule,
  /*  566 */  arShiftI_reg_imm_rule,
  /*  567 */  arShiftL_regL_regI_rule,
  /*  568 */  arShiftL_regL_regI_Ex_rule,
  /*  569 */  arShiftL_regL_immI_rule,
  /*  570 */  convL2I_arShiftL_regL_immI_rule,
  /*  571 */  urShiftI_reg_reg_rule,
  /*  572 */  urShiftI_reg_reg_Ex_rule,
  /*  573 */  urShiftI_reg_imm_rule,
  /*  574 */  urShiftL_regL_regI_rule,
  /*  575 */  urShiftL_regL_regI_Ex_rule,
  /*  576 */  urShiftL_regL_immI_rule,
  /*  577 */  convL2I_urShiftL_regL_immI_rule,
  /*  578 */  shrP_convP2X_reg_imm6_rule,
  /*  579 */  andI_urShiftI_regI_immI_immIpow2minus1_rule,
  /*  580 */  andL_urShiftL_regL_immI_immLpow2minus1_rule,
  /*  581 */  sxtI_reg_rule,
  /*  582 */  rotlI_reg_immi8_rule,
  /*  583 */  rotlI_reg_immi8_0_rule,
  /*  584 */  rotrI_reg_immi8_rule,
  /*  585 */  rotrI_reg_immi8_0_rule,
  /*  586 */  addF_reg_reg_rule,
  /*  587 */  addD_reg_reg_rule,
  /*  588 */  subF_reg_reg_rule,
  /*  589 */  subD_reg_reg_rule,
  /*  590 */  mulF_reg_reg_rule,
  /*  591 */  mulD_reg_reg_rule,
  /*  592 */  divF_reg_reg_rule,
  /*  593 */  divD_reg_reg_rule,
  /*  594 */  sqrtD_reg_rule,
  /*  595 */  sqrtF_reg_rule,
  /*  596 */  maddF_reg_reg_rule,
  /*  597 */  maddD_reg_reg_rule,
  /*  598 */  mnsubF_reg_reg_rule,
  /*  599 */  mnsubF_reg_reg_0_rule,
  /*  600 */  mnsubD_reg_reg_rule,
  /*  601 */  mnsubD_reg_reg_0_rule,
  /*  602 */  mnaddF_reg_reg_rule,
  /*  603 */  mnaddF_reg_reg_0_rule,
  /*  604 */  mnaddD_reg_reg_rule,
  /*  605 */  mnaddD_reg_reg_0_rule,
  /*  606 */  msubF_reg_reg_rule,
  /*  607 */  msubD_reg_reg_rule,
  /*  608 */  andI_reg_reg_rule,
  /*  609 */  andI_reg_immIhi16_rule,
  /*  610 */  andI_reg_uimm16_rule,
  /*  611 */  andI_reg_immInegpow2_rule,
  /*  612 */  andI_reg_immIpow2minus1_rule,
  /*  613 */  andI_reg_immIpowerOf2_rule,
  /*  614 */  andL_reg_reg_rule,
  /*  615 */  andL_reg_uimm16_rule,
  /*  616 */  andL_reg_immLnegpow2_rule,
  /*  617 */  andL_reg_immLpow2minus1_rule,
  /*  618 */  convL2I_andL_reg_immLpow2minus1_rule,
  /*  619 */  orI_reg_reg_rule,
  /*  620 */  orI_reg_reg_2_rule,
  /*  621 */  tree_orI_orI_orI_reg_reg_Ex_rule,
  /*  622 */  tree_orI_orI_orI_reg_reg_Ex_1_rule,
  /*  623 */  tree_orI_orI_orI_reg_reg_Ex_0_rule,
  /*  624 */  tree_orI_orI_orI_reg_reg_Ex_2_rule,
  /*  625 */  orI_reg_uimm16_rule,
  /*  626 */  orL_reg_reg_rule,
  /*  627 */  orI_regL_regL_rule,
  /*  628 */  orL_reg_uimm16_rule,
  /*  629 */  xorI_reg_reg_rule,
  /*  630 */  xorI_reg_reg_2_rule,
  /*  631 */  tree_xorI_xorI_xorI_reg_reg_Ex_rule,
  /*  632 */  tree_xorI_xorI_xorI_reg_reg_Ex_1_rule,
  /*  633 */  tree_xorI_xorI_xorI_reg_reg_Ex_0_rule,
  /*  634 */  tree_xorI_xorI_xorI_reg_reg_Ex_2_rule,
  /*  635 */  xorI_reg_uimm16_rule,
  /*  636 */  xorL_reg_reg_rule,
  /*  637 */  xorI_regL_regL_rule,
  /*  638 */  xorL_reg_uimm16_rule,
  /*  639 */  notI_reg_rule,
  /*  640 */  notL_reg_rule,
  /*  641 */  andcI_reg_reg_rule,
  /*  642 */  andcI_reg_reg_0_rule,
  /*  643 */  andcL_reg_reg_rule,
  /*  644 */  moveF2I_reg_stack_rule,
  /*  645 */  moveI2F_reg_stack_rule,
  /*  646 */  moveF2L_reg_stack_rule,
  /*  647 */  moveD2L_reg_stack_rule,
  /*  648 */  moveL2D_reg_stack_rule,
  /*  649 */  convI2Bool_reg__cmove_rule,
  /*  650 */  xorI_convI2Bool_reg_immIvalue1__cntlz_Ex_rule,
  /*  651 */  xorI_convI2Bool_reg_immIvalue1__cmove_rule,
  /*  652 */  convI2Bool_andI_reg_immIpowerOf2_rule,
  /*  653 */  convP2Bool_reg__cmove_rule,
  /*  654 */  xorI_convP2Bool_reg__cntlz_Ex_rule,
  /*  655 */  xorI_convP2Bool_reg_immIvalue1__cmove_rule,
  /*  656 */  cmpLTMask_reg_reg_Ex_rule,
  /*  657 */  cmpLTMask_reg_immI0_rule,
  /*  658 */  convB2I_reg_rule,
  /*  659 */  convS2I_reg_rule,
  /*  660 */  sxtI_L2L_reg_rule,
  /*  661 */  convL2I_reg_rule,
  /*  662 */  cmovI_bso_stackSlotL_rule,
  /*  663 */  cmovI_bso_reg_rule,
  /*  664 */  cmovI_bso_stackSlotL_conLvalue0_Ex_rule,
  /*  665 */  cmovI_bso_reg_conLvalue0_Ex_rule,
  /*  666 */  convD2I_reg_ExEx_rule,
  /*  667 */  convD2I_reg_mffprd_ExEx_rule,
  /*  668 */  convF2I_regF_ExEx_rule,
  /*  669 */  convF2I_regF_mffprd_ExEx_rule,
  /*  670 */  convI2L_reg_rule,
  /*  671 */  zeroExtendL_regI_rule,
  /*  672 */  zeroExtendL_regL_rule,
  /*  673 */  cmovL_bso_stackSlotL_rule,
  /*  674 */  cmovL_bso_reg_rule,
  /*  675 */  cmovL_bso_stackSlotL_conLvalue0_Ex_rule,
  /*  676 */  cmovL_bso_reg_conLvalue0_Ex_rule,
  /*  677 */  convF2L_reg_ExEx_rule,
  /*  678 */  convF2L_reg_mffprd_ExEx_rule,
  /*  679 */  convD2L_reg_ExEx_rule,
  /*  680 */  convD2L_reg_mffprd_ExEx_rule,
  /*  681 */  convD2F_reg_rule,
  /*  682 */  convI2F_ireg_Ex_rule,
  /*  683 */  convI2F_ireg_fcfids_Ex_rule,
  /*  684 */  convI2F_ireg_mtfprd_Ex_rule,
  /*  685 */  convL2F_ireg_fcfids_Ex_rule,
  /*  686 */  convL2F_ireg_mtfprd_Ex_rule,
  /*  687 */  convI2D_reg_Ex_rule,
  /*  688 */  convI2D_reg_mtfprd_Ex_rule,
  /*  689 */  convL2D_reg_Ex_rule,
  /*  690 */  convL2D_reg_mtfprd_Ex_rule,
  /*  691 */  convF2D_reg_rule,
  /*  692 */  cmpL3_reg_reg_ExEx_rule,
  /*  693 */  rangeCheck_iReg_uimm15_rule,
  /*  694 */  rangeCheck_iReg_iReg_rule,
  /*  695 */  rangeCheck_uimm15_iReg_rule,
  /*  696 */  zeroCheckN_iReg_imm0_rule,
  /*  697 */  zeroCheckP_reg_imm0_rule,
  /*  698 */  cmpF3_reg_reg_ExEx_rule,
  /*  699 */  cmpD3_reg_reg_ExEx_rule,
  /*  700 */  branch_rule,
  /*  701 */  branchCon_rule,
  /*  702 */  branchConFar_rule,
  /*  703 */  branchConSched_rule,
  /*  704 */  branchLoopEnd_rule,
  /*  705 */  branchLoopEndFar_rule,
  /*  706 */  branchLoopEndSched_rule,
  /*  707 */  partialSubtypeCheck_rule,
  /*  708 */  align_addr_rule,
  /*  709 */  array_size_rule,
  /*  710 */  inlineCallClearArrayShort_rule,
  /*  711 */  inlineCallClearArrayLarge_rule,
  /*  712 */  inlineCallClearArray_rule,
  /*  713 */  string_compareL_rule,
  /*  714 */  string_compareU_rule,
  /*  715 */  string_compareLU_rule,
  /*  716 */  string_compareUL_rule,
  /*  717 */  string_equalsL_rule,
  /*  718 */  string_equalsU_rule,
  /*  719 */  array_equalsB_rule,
  /*  720 */  array_equalsC_rule,
  /*  721 */  indexOf_imm1_char_U_rule,
  /*  722 */  indexOf_imm1_char_L_rule,
  /*  723 */  indexOf_imm1_char_UL_rule,
  /*  724 */  indexOf_imm1_U_rule,
  /*  725 */  indexOf_imm1_L_rule,
  /*  726 */  indexOf_imm1_UL_rule,
  /*  727 */  indexOfChar_U_rule,
  /*  728 */  indexOf_imm_U_rule,
  /*  729 */  indexOf_imm_L_rule,
  /*  730 */  indexOf_imm_UL_rule,
  /*  731 */  indexOf_U_rule,
  /*  732 */  indexOf_L_rule,
  /*  733 */  indexOf_UL_rule,
  /*  734 */  string_compress_rule,
  /*  735 */  string_inflate_rule,
  /*  736 */  has_negatives_rule,
  /*  737 */  encode_iso_array_rule,
  /*  738 */  minI_reg_reg_Ex_rule,
  /*  739 */  minI_reg_reg_isel_rule,
  /*  740 */  maxI_reg_reg_Ex_rule,
  /*  741 */  maxI_reg_reg_isel_rule,
  /*  742 */  insrwi_a_rule,
  /*  743 */  insrwi_rule,
  /*  744 */  bytes_reverse_int_Ex_rule,
  /*  745 */  bytes_reverse_long_Ex_rule,
  /*  746 */  bytes_reverse_ushort_Ex_rule,
  /*  747 */  bytes_reverse_short_Ex_rule,
  /*  748 */  loadI_reversed_rule,
  /*  749 */  loadL_reversed_rule,
  /*  750 */  loadUS_reversed_rule,
  /*  751 */  loadS_reversed_rule,
  /*  752 */  storeI_reversed_rule,
  /*  753 */  storeL_reversed_rule,
  /*  754 */  storeUS_reversed_rule,
  /*  755 */  storeS_reversed_rule,
  /*  756 */  xxspltw_rule,
  /*  757 */  repl8B_reg_Ex_rule,
  /*  758 */  repl8B_immI0_rule,
  /*  759 */  repl8B_immIminus1_rule,
  /*  760 */  repl16B_reg_Ex_rule,
  /*  761 */  repl16B_immI0_rule,
  /*  762 */  repl16B_immIminus1_rule,
  /*  763 */  repl4S_reg_Ex_rule,
  /*  764 */  repl4S_immI0_rule,
  /*  765 */  repl4S_immIminus1_rule,
  /*  766 */  repl8S_reg_Ex_rule,
  /*  767 */  repl8S_immI0_rule,
  /*  768 */  repl8S_immIminus1_rule,
  /*  769 */  repl2I_reg_Ex_rule,
  /*  770 */  repl2I_immI0_rule,
  /*  771 */  repl2I_immIminus1_rule,
  /*  772 */  repl4I_reg_Ex_rule,
  /*  773 */  repl4I_immI0_rule,
  /*  774 */  repl4I_immIminus1_rule,
  /*  775 */  repl2F_reg_Ex_rule,
  /*  776 */  repl2F_immF_Ex_rule,
  /*  777 */  repl2F_immF0_rule,
  /*  778 */  repl4F_reg_Ex_rule,
  /*  779 */  repl4F_immF_Ex_rule,
  /*  780 */  repl4F_immF0_rule,
  /*  781 */  repl2D_reg_Ex_rule,
  /*  782 */  repl2D_immI0_rule,
  /*  783 */  repl2D_immIminus1_rule,
  /*  784 */  xxspltd_rule,
  /*  785 */  xxpermdi_rule,
  /*  786 */  repl2L_reg_Ex_rule,
  /*  787 */  repl2L_immI0_rule,
  /*  788 */  repl2L_immIminus1_rule,
  /*  789 */  safePoint_poll_rule,
  /*  790 */  CallStaticJavaDirect_rule,
  /*  791 */  CallDynamicJavaDirectSched_rule,
  /*  792 */  CallDynamicJavaDirectSched_Ex_rule,
  /*  793 */  CallDynamicJavaDirect_rule,
  /*  794 */  CallRuntimeDirect_rule,
  /*  795 */  CallLeafDirect_rule,
  /*  796 */  CallLeafDirect_Ex_rule,
  /*  797 */  CallLeafNoFPDirect_Ex_rule,
  /*  798 */  TailCalljmpInd_rule,
  /*  799 */  Ret_rule,
  /*  800 */  tailjmpInd_rule,
  /*  801 */  CreateException_rule,
  /*  802 */  RethrowException_rule,
  /*  803 */  ShouldNotReachHere_rule,
  /*  804 */  endGroup_rule,
  /*  805 */  fxNop_rule,
  /*  806 */  fpNop0_rule,
  /*  807 */  fpNop1_rule,
  /*  808 */  brNop0_rule,
  /*  809 */  brNop1_rule,
  /*  810 */  brNop2_rule,
  // last instruction
  _BEGIN_INST_CHAIN_RULE = 219,
  _END_INST_CHAIN_RULE  = 243,
  _BEGIN_REMATERIALIZE   = 221,
  _END_REMATERIALIZE    = 328,
  _last_Mach_Node  = 811 
};

// Enumerate machine registers starting after reserved regs.
// in the order of occurrence in the alloc_class(es).
enum MachRegisterEncodes {
  R14_enc        =  14,
  R14_H_enc      =  99,
  R15_enc        =  15,
  R15_H_enc      =  99,
  R17_enc        =  17,
  R17_H_enc      =  99,
  R18_enc        =  18,
  R18_H_enc      =  99,
  R19_enc        =  19,
  R19_H_enc      =  99,
  R20_enc        =  20,
  R20_H_enc      =  99,
  R21_enc        =  21,
  R21_H_enc      =  99,
  R22_enc        =  22,
  R22_H_enc      =  99,
  R23_enc        =  23,
  R23_H_enc      =  99,
  R24_enc        =  24,
  R24_H_enc      =  99,
  R25_enc        =  25,
  R25_H_enc      =  99,
  R26_enc        =  26,
  R26_H_enc      =  99,
  R27_enc        =  27,
  R27_H_enc      =  99,
  R28_enc        =  28,
  R28_H_enc      =  99,
  R29_enc        =  29,
  R29_H_enc      =  99,
  R30_enc        =  30,
  R30_H_enc      =  99,
  R31_enc        =  31,
  R31_H_enc      =  99,
  R11_enc        =  11,
  R11_H_enc      =  99,
  R12_enc        =  12,
  R12_H_enc      =  99,
  R10_enc        =  10,
  R10_H_enc      =  99,
  R9_enc         =   9,
  R9_H_enc       =  99,
  R8_enc         =   8,
  R8_H_enc       =  99,
  R7_enc         =   7,
  R7_H_enc       =  99,
  R6_enc         =   6,
  R6_H_enc       =  99,
  R5_enc         =   5,
  R5_H_enc       =  99,
  R4_enc         =   4,
  R4_H_enc       =  99,
  R3_enc         =   3,
  R3_H_enc       =  99,
  R16_enc        =  16,
  R16_H_enc      =  99,
  R13_enc        =  13,
  R13_H_enc      =  99,
  R2_enc         =   2,
  R2_H_enc       =  99,
  R1_enc         =   1,
  R1_H_enc       =  99,
  R0_enc         =   0,
  R0_H_enc       =  99,
  F0_enc         =   0,
  F0_H_enc       =  99,
  F13_enc        =  13,
  F13_H_enc      =  99,
  F12_enc        =  12,
  F12_H_enc      =  99,
  F11_enc        =  11,
  F11_H_enc      =  99,
  F10_enc        =  10,
  F10_H_enc      =  99,
  F9_enc         =   9,
  F9_H_enc       =  99,
  F8_enc         =   8,
  F8_H_enc       =  99,
  F7_enc         =   7,
  F7_H_enc       =  99,
  F6_enc         =   6,
  F6_H_enc       =  99,
  F5_enc         =   5,
  F5_H_enc       =  99,
  F4_enc         =   4,
  F4_H_enc       =  99,
  F3_enc         =   3,
  F3_H_enc       =  99,
  F2_enc         =   2,
  F2_H_enc       =  99,
  F1_enc         =   1,
  F1_H_enc       =  99,
  F14_enc        =  14,
  F14_H_enc      =  99,
  F15_enc        =  15,
  F15_H_enc      =  99,
  F16_enc        =  16,
  F16_H_enc      =  99,
  F17_enc        =  17,
  F17_H_enc      =  99,
  F18_enc        =  18,
  F18_H_enc      =  99,
  F19_enc        =  19,
  F19_H_enc      =  99,
  F20_enc        =  20,
  F20_H_enc      =  99,
  F21_enc        =  21,
  F21_H_enc      =  99,
  F22_enc        =  22,
  F22_H_enc      =  99,
  F23_enc        =  23,
  F23_H_enc      =  99,
  F24_enc        =  24,
  F24_H_enc      =  99,
  F25_enc        =  25,
  F25_H_enc      =  99,
  F26_enc        =  26,
  F26_H_enc      =  99,
  F27_enc        =  27,
  F27_H_enc      =  99,
  F28_enc        =  28,
  F28_H_enc      =  99,
  F29_enc        =  29,
  F29_H_enc      =  99,
  F30_enc        =  30,
  F30_H_enc      =  99,
  F31_enc        =  31,
  F31_H_enc      =  99,
  CCR0_enc       =   0,
  CCR1_enc       =   1,
  CCR2_enc       =   2,
  CCR3_enc       =   3,
  CCR4_enc       =   4,
  CCR5_enc       =   5,
  CCR6_enc       =   6,
  CCR7_enc       =   7,
  VSR0_enc       =   0,
  VSR1_enc       =   1,
  VSR2_enc       =   2,
  VSR3_enc       =   3,
  VSR4_enc       =   4,
  VSR5_enc       =   5,
  VSR6_enc       =   6,
  VSR7_enc       =   7,
  VSR8_enc       =   8,
  VSR9_enc       =   9,
  VSR10_enc      =  10,
  VSR11_enc      =  11,
  VSR12_enc      =  12,
  VSR13_enc      =  13,
  VSR14_enc      =  14,
  VSR15_enc      =  15,
  VSR16_enc      =  16,
  VSR17_enc      =  17,
  VSR18_enc      =  18,
  VSR19_enc      =  19,
  VSR20_enc      =  20,
  VSR21_enc      =  21,
  VSR22_enc      =  22,
  VSR23_enc      =  23,
  VSR24_enc      =  24,
  VSR25_enc      =  25,
  VSR26_enc      =  26,
  VSR27_enc      =  27,
  VSR28_enc      =  28,
  VSR29_enc      =  29,
  VSR30_enc      =  30,
  VSR31_enc      =  31,
  VSR32_enc      =  32,
  VSR33_enc      =  33,
  VSR34_enc      =  34,
  VSR35_enc      =  35,
  VSR36_enc      =  36,
  VSR37_enc      =  37,
  VSR38_enc      =  38,
  VSR39_enc      =  39,
  VSR40_enc      =  40,
  VSR41_enc      =  41,
  VSR42_enc      =  42,
  VSR43_enc      =  43,
  VSR44_enc      =  44,
  VSR45_enc      =  45,
  VSR46_enc      =  46,
  VSR47_enc      =  47,
  VSR48_enc      =  48,
  VSR49_enc      =  49,
  VSR50_enc      =  50,
  VSR51_enc      =  51,
  VSR52_enc      =  52,
  VSR53_enc      =  53,
  VSR54_enc      =  54,
  VSR55_enc      =  55,
  VSR56_enc      =  56,
  VSR57_enc      =  57,
  VSR58_enc      =  58,
  VSR59_enc      =  59,
  VSR60_enc      =  60,
  VSR61_enc      =  61,
  VSR62_enc      =  62,
  VSR63_enc      =  63,
  SR_XER_enc     =   0,
  SR_LR_enc      =   1,
  SR_CTR_enc     =   2,
  SR_VRSAVE_enc  =   3,
  SR_SPEFSCR_enc =   4,
  SR_PPR_enc     =   5
};

// Pipeline Stages
enum machPipelineStages {
   stage_undefined = 0,
   stage_PPC_IF    = 1,
   stage_PPC_IC    = 2,
   stage_PPC_D0    = 3,
   stage_PPC_D1    = 4,
   stage_PPC_D2    = 5,
   stage_PPC_D3    = 6,
   stage_PPC_Xfer1 = 7,
   stage_PPC_GD    = 8,
   stage_PPC_MP    = 9,
   stage_PPC_ISS   = 10,
   stage_PPC_RF    = 11,
   stage_PPC_EX1   = 12,
   stage_PPC_EX2   = 13,
   stage_PPC_EX3   = 14,
   stage_PPC_EX4   = 15,
   stage_PPC_EX5   = 16,
   stage_PPC_EX6   = 17,
   stage_PPC_WB    = 18,
   stage_PPC_Xfer2 = 19,
   stage_PPC_CP    = 20,
   stage_count     = 20
};

// Pipeline Resources
enum machPipelineResources {
   resource_PPC_BR    = 0,
   resource_PPC_CR    = 1,
   resource_PPC_FX1   = 2,
   resource_PPC_FX2   = 3,
   resource_PPC_LDST1 = 4,
   resource_PPC_LDST2 = 5,
   resource_PPC_FP1   = 6,
   resource_PPC_FP2   = 7,

   res_mask_PPC_BR    = 0x00000001,
   res_mask_PPC_CR    = 0x00000002,
   res_mask_PPC_FX1   = 0x00000004,
   res_mask_PPC_FX2   = 0x00000008,
   res_mask_PPC_LDST1 = 0x00000010,
   res_mask_PPC_LDST2 = 0x00000020,
   res_mask_PPC_FP1   = 0x00000040,
   res_mask_PPC_FP2   = 0x00000080,
   res_mask_PPC_LDST  = 0x00000030,
   res_mask_PPC_FX    = 0x0000000c,
   res_mask_PPC_FP    = 0x000000c0,

   resource_count = 8
};

// MACROS to inline and constant fold State::valid(index)...
// when given a constant 'index' in dfa_<arch>.cpp
//   uint word   = index >> 5;       // Shift out bit position
//   uint bitpos = index & 0x0001F;  // Mask off word bits
#define STATE__VALID(index)     (_valid[((uint)index) >> 5] &  (0x1 << (((uint)index) & 0x0001F)))

#define STATE__NOT_YET_VALID(index)   ( (_valid[((uint)index) >> 5] &  (0x1 << (((uint)index) & 0x0001F))) == 0 )

#define STATE__VALID_CHILD(state,index)   ( state && (state->_valid[((uint)index) >> 5] &  (0x1 << (((uint)index) & 0x0001F))) )

#define STATE__SET_VALID(index)   (_valid[((uint)index) >> 5] |= (0x1 << (((uint)index) & 0x0001F)))

//---------------------------State-------------------------------------------
// State contains an integral cost vector, indexed by machine operand opcodes,
// a rule vector consisting of machine operand/instruction opcodes, and also
// indexed by machine operand opcodes, pointers to the children in the label
// tree generated by the Label routines in ideal nodes (currently limited to
// two for convenience, but this could change).
class State : public ResourceObj {
public:
  int    _id;         // State identifier
  Node  *_leaf;       // Ideal (non-machine-node) leaf of match tree
  State *_kids[2];       // Children of state node in label tree
  unsigned int _cost[_LAST_MACH_OPER];  // Cost vector, indexed by operand opcodes
  unsigned int _rule[_LAST_MACH_OPER];  // Rule vector, indexed by operand opcodes
  unsigned int _valid[(_LAST_MACH_OPER/32)+1]; // Bit Map of valid Cost/Rule entries

  State(void);                      // Constructor
  DEBUG_ONLY( ~State(void); )       // Destructor

  // Methods created by ADLC and invoked by Reduce
  MachOper *MachOperGenerator(int opcode);
  MachNode *MachNodeGenerator(int opcode);

  // Assign a state to a node, definition of method produced by ADLC
  bool DFA( int opcode, const Node *ideal );

  // Access function for _valid bit vector
  bool valid(uint index) {
    return( STATE__VALID(index) != 0 );
  }

  // Set function for _valid bit vector
  void set_valid(uint index) {
    STATE__SET_VALID(index);
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
  void  _sub_Op_RegFlags(const Node *n);
  void  _sub_Op_VecX(const Node *n);
  void  _sub_Op_AbsD(const Node *n);
  void  _sub_Op_AbsF(const Node *n);
  void  _sub_Op_AbsI(const Node *n);
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
  void  _sub_Op_CastII(const Node *n);
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
  void  _sub_Op_CompareAndSwapB(const Node *n);
  void  _sub_Op_CompareAndSwapS(const Node *n);
  void  _sub_Op_CompareAndSwapI(const Node *n);
  void  _sub_Op_CompareAndSwapL(const Node *n);
  void  _sub_Op_CompareAndSwapP(const Node *n);
  void  _sub_Op_CompareAndSwapN(const Node *n);
  void  _sub_Op_WeakCompareAndSwapB(const Node *n);
  void  _sub_Op_WeakCompareAndSwapS(const Node *n);
  void  _sub_Op_WeakCompareAndSwapI(const Node *n);
  void  _sub_Op_WeakCompareAndSwapL(const Node *n);
  void  _sub_Op_WeakCompareAndSwapP(const Node *n);
  void  _sub_Op_WeakCompareAndSwapN(const Node *n);
  void  _sub_Op_CompareAndExchangeB(const Node *n);
  void  _sub_Op_CompareAndExchangeS(const Node *n);
  void  _sub_Op_CompareAndExchangeI(const Node *n);
  void  _sub_Op_CompareAndExchangeL(const Node *n);
  void  _sub_Op_CompareAndExchangeP(const Node *n);
  void  _sub_Op_CompareAndExchangeN(const Node *n);
  void  _sub_Op_GetAndAddB(const Node *n);
  void  _sub_Op_GetAndAddS(const Node *n);
  void  _sub_Op_GetAndAddI(const Node *n);
  void  _sub_Op_GetAndAddL(const Node *n);
  void  _sub_Op_GetAndSetB(const Node *n);
  void  _sub_Op_GetAndSetS(const Node *n);
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
  void  _sub_Op_EncodeISOArray(const Node *n);
  void  _sub_Op_EncodeP(const Node *n);
  void  _sub_Op_EncodePKlass(const Node *n);
  void  _sub_Op_FastLock(const Node *n);
  void  _sub_Op_FastUnlock(const Node *n);
  void  _sub_Op_FmaD(const Node *n);
  void  _sub_Op_FmaF(const Node *n);
  void  _sub_Op_Goto(const Node *n);
  void  _sub_Op_Halt(const Node *n);
  void  _sub_Op_HasNegatives(const Node *n);
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
  void  _sub_Op_LoadPLocked(const Node *n);
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
  void  _sub_Op_MemBarReleaseLock(const Node *n);
  void  _sub_Op_MemBarVolatile(const Node *n);
  void  _sub_Op_MemBarStoreStore(const Node *n);
  void  _sub_Op_MinI(const Node *n);
  void  _sub_Op_ModI(const Node *n);
  void  _sub_Op_ModL(const Node *n);
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
  void  _sub_Op_OverflowAddL(const Node *n);
  void  _sub_Op_OverflowSubL(const Node *n);
  void  _sub_Op_OverflowMulL(const Node *n);
  void  _sub_Op_PartialSubtypeCheck(const Node *n);
  void  _sub_Op_PopCountI(const Node *n);
  void  _sub_Op_PopCountL(const Node *n);
  void  _sub_Op_PrefetchAllocation(const Node *n);
  void  _sub_Op_RShiftI(const Node *n);
  void  _sub_Op_RShiftL(const Node *n);
  void  _sub_Op_Rethrow(const Node *n);
  void  _sub_Op_Return(const Node *n);
  void  _sub_Op_RoundDouble(const Node *n);
  void  _sub_Op_RoundFloat(const Node *n);
  void  _sub_Op_SafePoint(const Node *n);
  void  _sub_Op_SqrtD(const Node *n);
  void  _sub_Op_StoreB(const Node *n);
  void  _sub_Op_StoreC(const Node *n);
  void  _sub_Op_StoreCM(const Node *n);
  void  _sub_Op_StorePConditional(const Node *n);
  void  _sub_Op_StoreLConditional(const Node *n);
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
  void  _sub_Op_LoadVector(const Node *n);
  void  _sub_Op_StoreVector(const Node *n);
  void  _sub_Op_ReplicateB(const Node *n);
  void  _sub_Op_ReplicateS(const Node *n);
  void  _sub_Op_ReplicateI(const Node *n);
  void  _sub_Op_ReplicateL(const Node *n);
  void  _sub_Op_ReplicateF(const Node *n);
  void  _sub_Op_ReplicateD(const Node *n);
};



// Total number of operands defined in architecture definition
#define FIRST_OPERAND_CLASS   108
#define NUM_OPERANDS          114

// Total number of instructions defined in architecture definition
#define NUM_INSTRUCTIONS   517

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

class immIhi16Oper : public MachOper { 
private:
  virtual uint           num_edges() const { return 0; }
  int32_t        _c0;
public:
  immIhi16Oper(int32_t c0)  : _c0(c0) {}
  virtual MachOper      *clone() const;
  virtual void set_con( jint c0 ) { _c0 = c0; }
  virtual uint           opcode() const { return IMMIHI16; }
  virtual const Type    *type() const { return TypeInt::INT; }

  virtual intptr_t       constant() const { return (intptr_t)_c0;  }

#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual void           dump_spec(outputStream *st) const {
   st->print("#%d", _c0);
   st->print("/0x%08x", _c0);
  }
  virtual const char    *Name() const { return "immIhi16";}
#endif
};

class immInegpow2Oper : public MachOper { 
private:
  virtual uint           num_edges() const { return 0; }
  int32_t        _c0;
public:
  immInegpow2Oper(int32_t c0)  : _c0(c0) {}
  virtual MachOper      *clone() const;
  virtual void set_con( jint c0 ) { _c0 = c0; }
  virtual uint           opcode() const { return IMMINEGPOW2; }
  virtual const Type    *type() const { return TypeInt::INT; }

  virtual intptr_t       constant() const { return (intptr_t)_c0;  }

#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual void           dump_spec(outputStream *st) const {
   st->print("#%d", _c0);
   st->print("/0x%08x", _c0);
  }
  virtual const char    *Name() const { return "immInegpow2";}
#endif
};

class immIpow2minus1Oper : public MachOper { 
private:
  virtual uint           num_edges() const { return 0; }
  int32_t        _c0;
public:
  immIpow2minus1Oper(int32_t c0)  : _c0(c0) {}
  virtual MachOper      *clone() const;
  virtual void set_con( jint c0 ) { _c0 = c0; }
  virtual uint           opcode() const { return IMMIPOW2MINUS1; }
  virtual const Type    *type() const { return TypeInt::INT; }

  virtual intptr_t       constant() const { return (intptr_t)_c0;  }

#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual void           dump_spec(outputStream *st) const {
   st->print("#%d", _c0);
   st->print("/0x%08x", _c0);
  }
  virtual const char    *Name() const { return "immIpow2minus1";}
#endif
};

class immIpowerOf2Oper : public MachOper { 
private:
  virtual uint           num_edges() const { return 0; }
  int32_t        _c0;
public:
  immIpowerOf2Oper(int32_t c0)  : _c0(c0) {}
  virtual MachOper      *clone() const;
  virtual void set_con( jint c0 ) { _c0 = c0; }
  virtual uint           opcode() const { return IMMIPOWEROF2; }
  virtual const Type    *type() const { return TypeInt::INT; }

  virtual intptr_t       constant() const { return (intptr_t)_c0;  }

#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual void           dump_spec(outputStream *st) const {
   st->print("#%d", _c0);
   st->print("/0x%08x", _c0);
  }
  virtual const char    *Name() const { return "immIpowerOf2";}
#endif
};

class uimmI5Oper : public MachOper { 
private:
  virtual uint           num_edges() const { return 0; }
  int32_t        _c0;
public:
  uimmI5Oper(int32_t c0)  : _c0(c0) {}
  virtual MachOper      *clone() const;
  virtual void set_con( jint c0 ) { _c0 = c0; }
  virtual uint           opcode() const { return UIMMI5; }
  virtual const Type    *type() const { return TypeInt::INT; }

  virtual intptr_t       constant() const { return (intptr_t)_c0;  }

#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual void           dump_spec(outputStream *st) const {
   st->print("#%d", _c0);
   st->print("/0x%08x", _c0);
  }
  virtual const char    *Name() const { return "uimmI5";}
#endif
};

class uimmI6Oper : public MachOper { 
private:
  virtual uint           num_edges() const { return 0; }
  int32_t        _c0;
public:
  uimmI6Oper(int32_t c0)  : _c0(c0) {}
  virtual MachOper      *clone() const;
  virtual void set_con( jint c0 ) { _c0 = c0; }
  virtual uint           opcode() const { return UIMMI6; }
  virtual const Type    *type() const { return TypeInt::INT; }

  virtual intptr_t       constant() const { return (intptr_t)_c0;  }

#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual void           dump_spec(outputStream *st) const {
   st->print("#%d", _c0);
   st->print("/0x%08x", _c0);
  }
  virtual const char    *Name() const { return "uimmI6";}
#endif
};

class uimmI6_ge32Oper : public MachOper { 
private:
  virtual uint           num_edges() const { return 0; }
  int32_t        _c0;
public:
  uimmI6_ge32Oper(int32_t c0)  : _c0(c0) {}
  virtual MachOper      *clone() const;
  virtual void set_con( jint c0 ) { _c0 = c0; }
  virtual uint           opcode() const { return UIMMI6_GE32; }
  virtual const Type    *type() const { return TypeInt::INT; }

  virtual intptr_t       constant() const { return (intptr_t)_c0;  }

#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual void           dump_spec(outputStream *st) const {
   st->print("#%d", _c0);
   st->print("/0x%08x", _c0);
  }
  virtual const char    *Name() const { return "uimmI6_ge32";}
#endif
};

class uimmI15Oper : public MachOper { 
private:
  virtual uint           num_edges() const { return 0; }
  int32_t        _c0;
public:
  uimmI15Oper(int32_t c0)  : _c0(c0) {}
  virtual MachOper      *clone() const;
  virtual void set_con( jint c0 ) { _c0 = c0; }
  virtual uint           opcode() const { return UIMMI15; }
  virtual const Type    *type() const { return TypeInt::INT; }

  virtual intptr_t       constant() const { return (intptr_t)_c0;  }

#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual void           dump_spec(outputStream *st) const {
   st->print("#%d", _c0);
   st->print("/0x%08x", _c0);
  }
  virtual const char    *Name() const { return "uimmI15";}
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

class immN_0Oper : public MachOper { 
private:
  virtual uint           num_edges() const { return 0; }
  const TypeNarrowOop *_c0;
public:
  immN_0Oper(const TypeNarrowOop *c0)  : _c0(c0) {}
  virtual MachOper      *clone() const;
  virtual uint           opcode() const { return IMMN_0; }
  virtual const Type    *type() const { return _c0; }

  virtual intptr_t       constant() const { return _c0->get_ptrtype()->get_con(); }
  virtual relocInfo::relocType           constant_reloc() const { return _c0->get_ptrtype()->reloc(); }

#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual void           dump_spec(outputStream *st) const {
    _c0->dump_on(st);
  }
  virtual const char    *Name() const { return "immN_0";}
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

class immNKlass_NMOper : public MachOper { 
private:
  virtual uint           num_edges() const { return 0; }
  const TypeNarrowKlass *_c0;
public:
  immNKlass_NMOper(const TypeNarrowKlass *c0)  : _c0(c0) {}
  virtual MachOper      *clone() const;
  virtual uint           opcode() const { return IMMNKLASS_NM; }
  virtual const Type    *type() const { return _c0; }

  virtual intptr_t       constant() const { return _c0->get_ptrtype()->get_con(); }
  virtual relocInfo::relocType           constant_reloc() const { return _c0->get_ptrtype()->reloc(); }

#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual void           dump_spec(outputStream *st) const {
    _c0->dump_on(st);
  }
  virtual const char    *Name() const { return "immNKlass_NM";}
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

class immP_NMOper : public MachOper { 
private:
  virtual uint           num_edges() const { return 0; }
  const TypePtr *_c0;
public:
  immP_NMOper(const TypePtr *c0)  : _c0(c0) {}
  virtual MachOper      *clone() const;
  virtual uint           opcode() const { return IMMP_NM; }
  virtual const Type    *type() const { return _c0; }

  virtual intptr_t       constant() const { return _c0->get_con(); }
  virtual relocInfo::relocType           constant_reloc() const { return _c0->reloc(); }

#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual void           dump_spec(outputStream *st) const {
    _c0->dump_on(st);
  }
  virtual const char    *Name() const { return "immP_NM";}
#endif
};

class immP_0Oper : public MachOper { 
private:
  virtual uint           num_edges() const { return 0; }
  const TypePtr *_c0;
public:
  immP_0Oper(const TypePtr *c0)  : _c0(c0) {}
  virtual MachOper      *clone() const;
  virtual uint           opcode() const { return IMMP_0; }
  virtual const Type    *type() const { return _c0; }

  virtual intptr_t       constant() const { return _c0->get_con(); }
  virtual relocInfo::relocType           constant_reloc() const { return _c0->reloc(); }

#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual void           dump_spec(outputStream *st) const {
    _c0->dump_on(st);
  }
  virtual const char    *Name() const { return "immP_0";}
#endif
};

class immP_0or1Oper : public MachOper { 
private:
  virtual uint           num_edges() const { return 0; }
  const TypePtr *_c0;
public:
  immP_0or1Oper(const TypePtr *c0)  : _c0(c0) {}
  virtual MachOper      *clone() const;
  virtual uint           opcode() const { return IMMP_0OR1; }
  virtual const Type    *type() const { return _c0; }

  virtual intptr_t       constant() const { return _c0->get_con(); }
  virtual relocInfo::relocType           constant_reloc() const { return _c0->reloc(); }

#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual void           dump_spec(outputStream *st) const {
    _c0->dump_on(st);
  }
  virtual const char    *Name() const { return "immP_0or1";}
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
    st->print("/" PTR64_FORMAT, (uint64_t)_c0);
  }
  virtual const char    *Name() const { return "immL";}
#endif
};

class immLmax30Oper : public MachOper { 
private:
  virtual uint           num_edges() const { return 0; }
  jlong          _c0;
public:
  immLmax30Oper(jlong c0)  : _c0(c0) {}
  virtual MachOper      *clone() const;
  virtual void set_con( jint c0 ) { _c0 = c0; }
  virtual uint           opcode() const { return IMMLMAX30; }
  virtual const Type    *type() const { return TypeLong::LONG; }

  virtual intptr_t       constant() const {  return (intptr_t)_c0; }
  virtual jlong          constantL() const { return _c0; }

#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual void           dump_spec(outputStream *st) const {
    st->print("#" INT64_FORMAT, (int64_t)_c0);
    st->print("/" PTR64_FORMAT, (uint64_t)_c0);
  }
  virtual const char    *Name() const { return "immLmax30";}
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
    st->print("/" PTR64_FORMAT, (uint64_t)_c0);
  }
  virtual const char    *Name() const { return "immL16";}
#endif
};

class immL16Alg4Oper : public MachOper { 
private:
  virtual uint           num_edges() const { return 0; }
  jlong          _c0;
public:
  immL16Alg4Oper(jlong c0)  : _c0(c0) {}
  virtual MachOper      *clone() const;
  virtual void set_con( jint c0 ) { _c0 = c0; }
  virtual uint           opcode() const { return IMML16ALG4; }
  virtual const Type    *type() const { return TypeLong::LONG; }

  virtual intptr_t       constant() const {  return (intptr_t)_c0; }
  virtual jlong          constantL() const { return _c0; }

#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual void           dump_spec(outputStream *st) const {
    st->print("#" INT64_FORMAT, (int64_t)_c0);
    st->print("/" PTR64_FORMAT, (uint64_t)_c0);
  }
  virtual const char    *Name() const { return "immL16Alg4";}
#endif
};

class immL32hi16Oper : public MachOper { 
private:
  virtual uint           num_edges() const { return 0; }
  jlong          _c0;
public:
  immL32hi16Oper(jlong c0)  : _c0(c0) {}
  virtual MachOper      *clone() const;
  virtual void set_con( jint c0 ) { _c0 = c0; }
  virtual uint           opcode() const { return IMML32HI16; }
  virtual const Type    *type() const { return TypeLong::LONG; }

  virtual intptr_t       constant() const {  return (intptr_t)_c0; }
  virtual jlong          constantL() const { return _c0; }

#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual void           dump_spec(outputStream *st) const {
    st->print("#" INT64_FORMAT, (int64_t)_c0);
    st->print("/" PTR64_FORMAT, (uint64_t)_c0);
  }
  virtual const char    *Name() const { return "immL32hi16";}
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
    st->print("/" PTR64_FORMAT, (uint64_t)_c0);
  }
  virtual const char    *Name() const { return "immL32";}
#endif
};

class immLhighest16Oper : public MachOper { 
private:
  virtual uint           num_edges() const { return 0; }
  jlong          _c0;
public:
  immLhighest16Oper(jlong c0)  : _c0(c0) {}
  virtual MachOper      *clone() const;
  virtual void set_con( jint c0 ) { _c0 = c0; }
  virtual uint           opcode() const { return IMMLHIGHEST16; }
  virtual const Type    *type() const { return TypeLong::LONG; }

  virtual intptr_t       constant() const {  return (intptr_t)_c0; }
  virtual jlong          constantL() const { return _c0; }

#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual void           dump_spec(outputStream *st) const {
    st->print("#" INT64_FORMAT, (int64_t)_c0);
    st->print("/" PTR64_FORMAT, (uint64_t)_c0);
  }
  virtual const char    *Name() const { return "immLhighest16";}
#endif
};

class immLnegpow2Oper : public MachOper { 
private:
  virtual uint           num_edges() const { return 0; }
  jlong          _c0;
public:
  immLnegpow2Oper(jlong c0)  : _c0(c0) {}
  virtual MachOper      *clone() const;
  virtual void set_con( jint c0 ) { _c0 = c0; }
  virtual uint           opcode() const { return IMMLNEGPOW2; }
  virtual const Type    *type() const { return TypeLong::LONG; }

  virtual intptr_t       constant() const {  return (intptr_t)_c0; }
  virtual jlong          constantL() const { return _c0; }

#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual void           dump_spec(outputStream *st) const {
    st->print("#" INT64_FORMAT, (int64_t)_c0);
    st->print("/" PTR64_FORMAT, (uint64_t)_c0);
  }
  virtual const char    *Name() const { return "immLnegpow2";}
#endif
};

class immLpow2minus1Oper : public MachOper { 
private:
  virtual uint           num_edges() const { return 0; }
  jlong          _c0;
public:
  immLpow2minus1Oper(jlong c0)  : _c0(c0) {}
  virtual MachOper      *clone() const;
  virtual void set_con( jint c0 ) { _c0 = c0; }
  virtual uint           opcode() const { return IMMLPOW2MINUS1; }
  virtual const Type    *type() const { return TypeLong::LONG; }

  virtual intptr_t       constant() const {  return (intptr_t)_c0; }
  virtual jlong          constantL() const { return _c0; }

#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual void           dump_spec(outputStream *st) const {
    st->print("#" INT64_FORMAT, (int64_t)_c0);
    st->print("/" PTR64_FORMAT, (uint64_t)_c0);
  }
  virtual const char    *Name() const { return "immLpow2minus1";}
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
    st->print("/" PTR64_FORMAT, (uint64_t)_c0);
  }
  virtual const char    *Name() const { return "immL_0";}
#endif
};

class immL_minus1Oper : public MachOper { 
private:
  virtual uint           num_edges() const { return 0; }
  jlong          _c0;
public:
  immL_minus1Oper(jlong c0)  : _c0(c0) {}
  virtual MachOper      *clone() const;
  virtual void set_con( jint c0 ) { _c0 = c0; }
  virtual uint           opcode() const { return IMML_MINUS1; }
  virtual const Type    *type() const { return TypeLong::LONG; }

  virtual intptr_t       constant() const {  return (intptr_t)_c0; }
  virtual jlong          constantL() const { return _c0; }

#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual void           dump_spec(outputStream *st) const {
    st->print("#" INT64_FORMAT, (int64_t)_c0);
    st->print("/" PTR64_FORMAT, (uint64_t)_c0);
  }
  virtual const char    *Name() const { return "immL_minus1";}
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
    st->print("/" PTR64_FORMAT, (uint64_t)_c0);
  }
  virtual const char    *Name() const { return "immL_32bits";}
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
    st->print("/" PTR64_FORMAT, (uint64_t)_c0);
  }
  virtual const char    *Name() const { return "uimmL16";}
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

class immF_0Oper : public MachOper { 
private:
  virtual uint           num_edges() const { return 0; }
  jfloat         _c0;
public:
  immF_0Oper(jfloat c0)  : _c0(c0) {}
  virtual MachOper      *clone() const;
  virtual uint           opcode() const { return IMMF_0; }
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
  virtual const char    *Name() const { return "immF_0";}
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
    st->print("/" PTR64_FORMAT, (uint64_t)_c0l);
  }
  virtual const char    *Name() const { return "immD";}
#endif
};

class iRegIdstOper : public MachOper { 
private:
  virtual const RegMask *in_RegMask(int index) const;
public:
  iRegIdstOper() {}
  virtual MachOper      *clone() const;
  virtual uint           opcode() const { return IREGIDST; }
  virtual const Type    *type() const { return TypeInt::INT; }


#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual const char    *Name() const { return "iRegIdst";}
#endif
};

class iRegIsrcOper : public MachOper { 
private:
  virtual const RegMask *in_RegMask(int index) const;
public:
  iRegIsrcOper() {}
  virtual MachOper      *clone() const;
  virtual uint           opcode() const { return IREGISRC; }
  virtual const Type    *type() const { return TypeInt::INT; }


#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual const char    *Name() const { return "iRegIsrc";}
#endif
};

class rscratch1RegIOper : public MachOper { 
private:
  virtual const RegMask *in_RegMask(int index) const;
public:
  rscratch1RegIOper() {}
  virtual MachOper      *clone() const;
  virtual uint           opcode() const { return RSCRATCH1REGI; }
  virtual const Type    *type() const { return TypeInt::INT; }


#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual const char    *Name() const { return "rscratch1RegI";}
#endif
};

class rscratch2RegIOper : public MachOper { 
private:
  virtual const RegMask *in_RegMask(int index) const;
public:
  rscratch2RegIOper() {}
  virtual MachOper      *clone() const;
  virtual uint           opcode() const { return RSCRATCH2REGI; }
  virtual const Type    *type() const { return TypeInt::INT; }


#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual const char    *Name() const { return "rscratch2RegI";}
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

class rarg2RegLOper : public MachOper { 
private:
  virtual const RegMask *in_RegMask(int index) const;
public:
  rarg2RegLOper() {}
  virtual MachOper      *clone() const;
  virtual uint           opcode() const { return RARG2REGL; }
  virtual const Type    *type() const { return TypeLong::LONG; }


#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual const char    *Name() const { return "rarg2RegL";}
#endif
};

class rarg3RegLOper : public MachOper { 
private:
  virtual const RegMask *in_RegMask(int index) const;
public:
  rarg3RegLOper() {}
  virtual MachOper      *clone() const;
  virtual uint           opcode() const { return RARG3REGL; }
  virtual const Type    *type() const { return TypeLong::LONG; }


#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual const char    *Name() const { return "rarg3RegL";}
#endif
};

class rarg4RegLOper : public MachOper { 
private:
  virtual const RegMask *in_RegMask(int index) const;
public:
  rarg4RegLOper() {}
  virtual MachOper      *clone() const;
  virtual uint           opcode() const { return RARG4REGL; }
  virtual const Type    *type() const { return TypeLong::LONG; }


#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual const char    *Name() const { return "rarg4RegL";}
#endif
};

class iRegPdstOper : public MachOper { 
private:
  virtual const RegMask *in_RegMask(int index) const;
public:
  iRegPdstOper() {}
  virtual MachOper      *clone() const;
  virtual uint           opcode() const { return IREGPDST; }
  virtual const Type    *type() const { return TypePtr::BOTTOM; }


#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual const char    *Name() const { return "iRegPdst";}
#endif
};

class iRegPdstNoScratchOper : public MachOper { 
private:
  virtual const RegMask *in_RegMask(int index) const;
public:
  iRegPdstNoScratchOper() {}
  virtual MachOper      *clone() const;
  virtual uint           opcode() const { return IREGPDSTNOSCRATCH; }
  virtual const Type    *type() const { return TypePtr::BOTTOM; }


#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual const char    *Name() const { return "iRegPdstNoScratch";}
#endif
};

class iRegPsrcOper : public MachOper { 
private:
  virtual const RegMask *in_RegMask(int index) const;
public:
  iRegPsrcOper() {}
  virtual MachOper      *clone() const;
  virtual uint           opcode() const { return IREGPSRC; }
  virtual const Type    *type() const { return TypePtr::BOTTOM; }


#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual const char    *Name() const { return "iRegPsrc";}
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

class rscratch1RegPOper : public MachOper { 
private:
  virtual const RegMask *in_RegMask(int index) const;
public:
  rscratch1RegPOper() {}
  virtual MachOper      *clone() const;
  virtual uint           opcode() const { return RSCRATCH1REGP; }
  virtual const Type    *type() const { return TypePtr::BOTTOM; }


#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual const char    *Name() const { return "rscratch1RegP";}
#endif
};

class rscratch2RegPOper : public MachOper { 
private:
  virtual const RegMask *in_RegMask(int index) const;
public:
  rscratch2RegPOper() {}
  virtual MachOper      *clone() const;
  virtual uint           opcode() const { return RSCRATCH2REGP; }
  virtual const Type    *type() const { return TypePtr::BOTTOM; }


#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual const char    *Name() const { return "rscratch2RegP";}
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

class iRegNsrcOper : public MachOper { 
private:
  virtual const RegMask *in_RegMask(int index) const;
public:
  iRegNsrcOper() {}
  virtual MachOper      *clone() const;
  virtual uint           opcode() const { return IREGNSRC; }
  virtual const Type    *type() const { return TypeNarrowOop::BOTTOM; }


#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual const char    *Name() const { return "iRegNsrc";}
#endif
};

class iRegNdstOper : public MachOper { 
private:
  virtual const RegMask *in_RegMask(int index) const;
public:
  iRegNdstOper() {}
  virtual MachOper      *clone() const;
  virtual uint           opcode() const { return IREGNDST; }
  virtual const Type    *type() const { return TypeNarrowOop::BOTTOM; }


#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual const char    *Name() const { return "iRegNdst";}
#endif
};

class iRegLdstOper : public MachOper { 
private:
  virtual const RegMask *in_RegMask(int index) const;
public:
  iRegLdstOper() {}
  virtual MachOper      *clone() const;
  virtual uint           opcode() const { return IREGLDST; }
  virtual const Type    *type() const { return TypeLong::LONG; }


#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual const char    *Name() const { return "iRegLdst";}
#endif
};

class iRegLsrcOper : public MachOper { 
private:
  virtual const RegMask *in_RegMask(int index) const;
public:
  iRegLsrcOper() {}
  virtual MachOper      *clone() const;
  virtual uint           opcode() const { return IREGLSRC; }
  virtual const Type    *type() const { return TypeLong::LONG; }


#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual const char    *Name() const { return "iRegLsrc";}
#endif
};

class iRegL2IsrcOper : public MachOper { 
private:
  virtual const RegMask *in_RegMask(int index) const;
public:
  iRegL2IsrcOper() {}
  virtual MachOper      *clone() const;
  virtual uint           opcode() const { return IREGL2ISRC; }

#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual const char    *Name() const { return "iRegL2Isrc";}
#endif
};

class rscratch1RegLOper : public MachOper { 
private:
  virtual const RegMask *in_RegMask(int index) const;
public:
  rscratch1RegLOper() {}
  virtual MachOper      *clone() const;
  virtual uint           opcode() const { return RSCRATCH1REGL; }
  virtual const Type    *type() const { return TypeLong::LONG; }


#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual const char    *Name() const { return "rscratch1RegL";}
#endif
};

class rscratch2RegLOper : public MachOper { 
private:
  virtual const RegMask *in_RegMask(int index) const;
public:
  rscratch2RegLOper() {}
  virtual MachOper      *clone() const;
  virtual uint           opcode() const { return RSCRATCH2REGL; }
  virtual const Type    *type() const { return TypeLong::LONG; }


#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual const char    *Name() const { return "rscratch2RegL";}
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

class flagsRegSrcOper : public MachOper { 
private:
  virtual const RegMask *in_RegMask(int index) const;
public:
  flagsRegSrcOper() {}
  virtual MachOper      *clone() const;
  virtual uint           opcode() const { return FLAGSREGSRC; }
  virtual const Type    *type() const { return TypeInt::CC /*flags*/; }


#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual const char    *Name() const { return "flagsRegSrc";}
#endif
};

class flagsRegCR0Oper : public MachOper { 
private:
  virtual const RegMask *in_RegMask(int index) const;
public:
  flagsRegCR0Oper() {}
  virtual MachOper      *clone() const;
  virtual uint           opcode() const { return FLAGSREGCR0; }
  virtual const Type    *type() const { return TypeInt::CC /*flags*/; }


#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual const char    *Name() const { return "flagsRegCR0";}
#endif
};

class flagsRegCR1Oper : public MachOper { 
private:
  virtual const RegMask *in_RegMask(int index) const;
public:
  flagsRegCR1Oper() {}
  virtual MachOper      *clone() const;
  virtual uint           opcode() const { return FLAGSREGCR1; }
  virtual const Type    *type() const { return TypeInt::CC /*flags*/; }


#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual const char    *Name() const { return "flagsRegCR1";}
#endif
};

class flagsRegCR6Oper : public MachOper { 
private:
  virtual const RegMask *in_RegMask(int index) const;
public:
  flagsRegCR6Oper() {}
  virtual MachOper      *clone() const;
  virtual uint           opcode() const { return FLAGSREGCR6; }
  virtual const Type    *type() const { return TypeInt::CC /*flags*/; }


#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual const char    *Name() const { return "flagsRegCR6";}
#endif
};

class regCTROper : public MachOper { 
private:
  virtual const RegMask *in_RegMask(int index) const;
public:
  regCTROper() {}
  virtual MachOper      *clone() const;
  virtual uint           opcode() const { return REGCTR; }
  virtual const Type    *type() const { return TypeInt::CC /*flags*/; }


#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual const char    *Name() const { return "regCTR";}
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

class compiler_method_oop_regPOper : public MachOper { 
private:
  virtual const RegMask *in_RegMask(int index) const;
public:
  compiler_method_oop_regPOper() {}
  virtual MachOper      *clone() const;
  virtual uint           opcode() const { return COMPILER_METHOD_OOP_REGP; }
  virtual const Type    *type() const { return TypePtr::BOTTOM; }


#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual const char    *Name() const { return "compiler_method_oop_regP";}
#endif
};

class interpreter_method_oop_regPOper : public MachOper { 
private:
  virtual const RegMask *in_RegMask(int index) const;
public:
  interpreter_method_oop_regPOper() {}
  virtual MachOper      *clone() const;
  virtual uint           opcode() const { return INTERPRETER_METHOD_OOP_REGP; }
  virtual const Type    *type() const { return TypePtr::BOTTOM; }


#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual const char    *Name() const { return "interpreter_method_oop_regP";}
#endif
};

class iRegP2NOper : public MachOper { 
private:
  virtual const RegMask *in_RegMask(int index) const;
public:
  iRegP2NOper() {}
  virtual MachOper      *clone() const;
  virtual uint           opcode() const { return IREGP2N; }

#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual const char    *Name() const { return "iRegP2N";}
#endif
};

class iRegN2POper : public MachOper { 
private:
  virtual const RegMask *in_RegMask(int index) const;
public:
  iRegN2POper() {}
  virtual MachOper      *clone() const;
  virtual uint           opcode() const { return IREGN2P; }

#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual const char    *Name() const { return "iRegN2P";}
#endif
};

class iRegN2P_klassOper : public MachOper { 
private:
  virtual const RegMask *in_RegMask(int index) const;
public:
  iRegN2P_klassOper() {}
  virtual MachOper      *clone() const;
  virtual uint           opcode() const { return IREGN2P_KLASS; }

#ifndef PRODUCT
  virtual void           int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const;
  virtual void           ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const;
  virtual const char    *Name() const { return "iRegN2P_klass";}
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
    // Replacement variable: reg
    return (int)ra_->get_encode(node->in(idx));
  }
  virtual int            base_position() const { return 0; }
  virtual int            index(PhaseRegAlloc *ra_, const Node *node, int idx) const { 
    return 0x0;
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

class indOffset16Oper : public MachOper { 
private:
  virtual const RegMask *in_RegMask(int index) const;
  jlong            _c0;
public:
  indOffset16Oper(jlong c0)  : _c0(c0) {}
  virtual MachOper      *clone() const;
  virtual void set_con( jint c0 ) { _c0 = c0; }
  virtual uint           opcode() const { return INDOFFSET16; }

  virtual int            base(PhaseRegAlloc *ra_, const Node *node, int idx) const { 
    // Replacement variable: reg
    return (int)ra_->get_encode(node->in(idx));
  }
  virtual int            base_position() const { return 0; }
  virtual int            index(PhaseRegAlloc *ra_, const Node *node, int idx) const { 
    return 0x0;
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
    st->print("/" PTR64_FORMAT, (uint64_t)_c0);
  }
  virtual const char    *Name() const { return "indOffset16";}
#endif
};

class indOffset16Alg4Oper : public MachOper { 
private:
  virtual const RegMask *in_RegMask(int index) const;
  jlong            _c0;
public:
  indOffset16Alg4Oper(jlong c0)  : _c0(c0) {}
  virtual MachOper      *clone() const;
  virtual void set_con( jint c0 ) { _c0 = c0; }
  virtual uint           opcode() const { return INDOFFSET16ALG4; }

  virtual int            base(PhaseRegAlloc *ra_, const Node *node, int idx) const { 
    // Replacement variable: reg
    return (int)ra_->get_encode(node->in(idx));
  }
  virtual int            base_position() const { return 0; }
  virtual int            index(PhaseRegAlloc *ra_, const Node *node, int idx) const { 
    return 0x0;
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
    st->print("/" PTR64_FORMAT, (uint64_t)_c0);
  }
  virtual const char    *Name() const { return "indOffset16Alg4";}
#endif
};

class indirectNarrowOper : public MachOper { 
private:
  virtual const RegMask *in_RegMask(int index) const;
public:
  indirectNarrowOper() {}
  virtual MachOper      *clone() const;
  virtual uint           opcode() const { return INDIRECTNARROW; }

  virtual int            base(PhaseRegAlloc *ra_, const Node *node, int idx) const { 
    // Replacement variable: reg
    return (int)ra_->get_encode(node->in(idx));
  }
  virtual int            base_position() const { return 0; }
  virtual int            index(PhaseRegAlloc *ra_, const Node *node, int idx) const { 
    return 0x0;
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
  virtual const char    *Name() const { return "indirectNarrow";}
#endif
};

class indirectNarrow_klassOper : public MachOper { 
private:
  virtual const RegMask *in_RegMask(int index) const;
public:
  indirectNarrow_klassOper() {}
  virtual MachOper      *clone() const;
  virtual uint           opcode() const { return INDIRECTNARROW_KLASS; }

  virtual int            base(PhaseRegAlloc *ra_, const Node *node, int idx) const { 
    // Replacement variable: reg
    return (int)ra_->get_encode(node->in(idx));
  }
  virtual int            base_position() const { return 0; }
  virtual int            index(PhaseRegAlloc *ra_, const Node *node, int idx) const { 
    return 0x0;
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
  virtual const char    *Name() const { return "indirectNarrow_klass";}
#endif
};

class indOffset16NarrowOper : public MachOper { 
private:
  virtual const RegMask *in_RegMask(int index) const;
  jlong            _c0;
public:
  indOffset16NarrowOper(jlong c0)  : _c0(c0) {}
  virtual MachOper      *clone() const;
  virtual void set_con( jint c0 ) { _c0 = c0; }
  virtual uint           opcode() const { return INDOFFSET16NARROW; }

  virtual int            base(PhaseRegAlloc *ra_, const Node *node, int idx) const { 
    // Replacement variable: reg
    return (int)ra_->get_encode(node->in(idx));
  }
  virtual int            base_position() const { return 0; }
  virtual int            index(PhaseRegAlloc *ra_, const Node *node, int idx) const { 
    return 0x0;
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
    st->print("/" PTR64_FORMAT, (uint64_t)_c0);
  }
  virtual const char    *Name() const { return "indOffset16Narrow";}
#endif
};

class indOffset16Narrow_klassOper : public MachOper { 
private:
  virtual const RegMask *in_RegMask(int index) const;
  jlong            _c0;
public:
  indOffset16Narrow_klassOper(jlong c0)  : _c0(c0) {}
  virtual MachOper      *clone() const;
  virtual void set_con( jint c0 ) { _c0 = c0; }
  virtual uint           opcode() const { return INDOFFSET16NARROW_KLASS; }

  virtual int            base(PhaseRegAlloc *ra_, const Node *node, int idx) const { 
    // Replacement variable: reg
    return (int)ra_->get_encode(node->in(idx));
  }
  virtual int            base_position() const { return 0; }
  virtual int            index(PhaseRegAlloc *ra_, const Node *node, int idx) const { 
    return 0x0;
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
    st->print("/" PTR64_FORMAT, (uint64_t)_c0);
  }
  virtual const char    *Name() const { return "indOffset16Narrow_klass";}
#endif
};

class indOffset16NarrowAlg4Oper : public MachOper { 
private:
  virtual const RegMask *in_RegMask(int index) const;
  jlong            _c0;
public:
  indOffset16NarrowAlg4Oper(jlong c0)  : _c0(c0) {}
  virtual MachOper      *clone() const;
  virtual void set_con( jint c0 ) { _c0 = c0; }
  virtual uint           opcode() const { return INDOFFSET16NARROWALG4; }

  virtual int            base(PhaseRegAlloc *ra_, const Node *node, int idx) const { 
    // Replacement variable: reg
    return (int)ra_->get_encode(node->in(idx));
  }
  virtual int            base_position() const { return 0; }
  virtual int            index(PhaseRegAlloc *ra_, const Node *node, int idx) const { 
    return 0x0;
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
    st->print("/" PTR64_FORMAT, (uint64_t)_c0);
  }
  virtual const char    *Name() const { return "indOffset16NarrowAlg4";}
#endif
};

class indOffset16NarrowAlg4_klassOper : public MachOper { 
private:
  virtual const RegMask *in_RegMask(int index) const;
  jlong            _c0;
public:
  indOffset16NarrowAlg4_klassOper(jlong c0)  : _c0(c0) {}
  virtual MachOper      *clone() const;
  virtual void set_con( jint c0 ) { _c0 = c0; }
  virtual uint           opcode() const { return INDOFFSET16NARROWALG4_KLASS; }

  virtual int            base(PhaseRegAlloc *ra_, const Node *node, int idx) const { 
    // Replacement variable: reg
    return (int)ra_->get_encode(node->in(idx));
  }
  virtual int            base_position() const { return 0; }
  virtual int            index(PhaseRegAlloc *ra_, const Node *node, int idx) const { 
    return 0x0;
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
    st->print("/" PTR64_FORMAT, (uint64_t)_c0);
  }
  virtual const char    *Name() const { return "indOffset16NarrowAlg4_klass";}
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
    return 0x1;
  }
  virtual int            index(PhaseRegAlloc *ra_, const Node *node, int idx) const { 
    return 0x0;
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

class stackSlotLOper : public MachOper { 
private:
  virtual const RegMask *in_RegMask(int index) const;
public:
  stackSlotLOper() {}
  virtual MachOper      *clone() const;
  virtual uint           opcode() const { return STACKSLOTL; }
  virtual const Type    *type() const { return TypeLong::LONG; } // stackSlotX

  virtual int            base(PhaseRegAlloc *ra_, const Node *node, int idx) const { 
    return 0x1;
  }
  virtual int            index(PhaseRegAlloc *ra_, const Node *node, int idx) const { 
    return 0x0;
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

class stackSlotPOper : public MachOper { 
private:
  virtual const RegMask *in_RegMask(int index) const;
public:
  stackSlotPOper() {}
  virtual MachOper      *clone() const;
  virtual uint           opcode() const { return STACKSLOTP; }
  virtual const Type    *type() const { return TypePtr::BOTTOM; } // stackSlotX

  virtual int            base(PhaseRegAlloc *ra_, const Node *node, int idx) const { 
    return 0x1;
  }
  virtual int            index(PhaseRegAlloc *ra_, const Node *node, int idx) const { 
    return 0x0;
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
    return 0x1;
  }
  virtual int            index(PhaseRegAlloc *ra_, const Node *node, int idx) const { 
    return 0x0;
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
    return 0x1;
  }
  virtual int            index(PhaseRegAlloc *ra_, const Node *node, int idx) const { 
    return 0x0;
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
    return 0xA;
  }
  virtual int            not_equal() const {
    return 0x2;
  }
  virtual int            less() const {
    return 0x8;
  }
  virtual int            greater_equal() const {
    return 0x0;
  }
  virtual int            less_equal() const {
    return 0x1;
  }
  virtual int            greater() const {
    return 0x9;
  }
  virtual int            overflow() const {
    return 0xB;
  }
  virtual int            no_overflow() const {
    return 0x3;
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
  uint _mask;

public:
  Pipeline_Use_Cycle_Mask() : _mask(0) {}

  Pipeline_Use_Cycle_Mask(uint mask) : _mask(mask) {}

  Pipeline_Use_Cycle_Mask& operator=(const Pipeline_Use_Cycle_Mask &in) {
    _mask = in._mask;
    return *this;
  }

  bool overlaps(const Pipeline_Use_Cycle_Mask &in2) const {
    return ((_mask & in2._mask) != 0);
  }

  Pipeline_Use_Cycle_Mask& operator<<=(int n) {
    _mask <<= n;
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
    _variable_size_instructions = 0,
    _fixed_size_instructions = 1,
    _branch_has_delay_slot = 0,
    _max_instrs_per_bundle = 8,
    _max_bundles_per_cycle = 1,
    _max_instrs_per_cycle = 8
  };

  static bool instr_has_unit_size() { return true; }

// Bundling is not supported

  // Size of an instruction
  static uint instr_unit_size() { return 4; };

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
  const bool                            _has_branch_delay;
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
           bool                            has_branch_delay,
           bool                            has_multiple_bundles,
           bool                            force_serialization,
           bool                            may_have_no_code,
           enum machPipelineStages * const dst,
           enum machPipelineStages * const stage,
           uint                    * const cycles,
           Pipeline_Use                    resource_use)
  : _write_stage(write_stage)
  , _read_stage_count(count)
  , _has_fixed_latency(has_fixed_latency)
  , _fixed_latency(fixed_latency)
  , _read_stages(dst)
  , _resource_stage(stage)
  , _resource_cycles(cycles)
  , _resource_use(resource_use)
  , _instruction_count(instruction_count)
  , _has_branch_delay(has_branch_delay)
  , _has_multiple_bundles(has_multiple_bundles)
  , _force_serialization(force_serialization)
  , _may_have_no_code(may_have_no_code)
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

  bool hasBranchDelay() const {
    return (_has_branch_delay); }

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
  enum {
    _unused_delay                   = 0x0,
    _use_nop_delay                  = 0x1,
    _use_unconditional_delay        = 0x2,
    _use_conditional_delay          = 0x3,
    _used_in_conditional_delay      = 0x4,
    _used_in_unconditional_delay    = 0x5,
    _used_in_all_conditional_delays = 0x6,

    _use_delay                      = 0x3,
    _used_in_delay                  = 0x4
  };

  uint _flags          : 3,
       _starts_bundle  : 1,
       _instr_count    : 4,
       _resources_used : 8;
public:
  Bundle() : _flags(_unused_delay), _starts_bundle(0), _instr_count(0), _resources_used(0) {}

  void set_instr_count(uint i) { _instr_count  = i; }
  void set_resources_used(uint i) { _resources_used   = i; }
  void clear_usage() { _flags = _unused_delay; }
  void set_starts_bundle() { _starts_bundle = true; }
  uint flags() const { return (_flags); }
  uint instr_count() const { return (_instr_count); }
  uint resources_used() const { return (_resources_used); }
  bool starts_bundle() const { return (_starts_bundle != 0); }
  void set_use_nop_delay() { _flags = _use_nop_delay; }
  void set_use_unconditional_delay() { _flags = _use_unconditional_delay; }
  void set_use_conditional_delay() { _flags = _use_conditional_delay; }
  void set_used_in_unconditional_delay() { _flags = _used_in_unconditional_delay; }
  void set_used_in_conditional_delay() { _flags = _used_in_conditional_delay; }
  void set_used_in_all_conditional_delays() { _flags = _used_in_all_conditional_delays; }
  bool use_nop_delay() { return (_flags == _use_nop_delay); }
  bool use_unconditional_delay() { return (_flags == _use_unconditional_delay); }
  bool use_conditional_delay() { return (_flags == _use_conditional_delay); }
  bool used_in_unconditional_delay() { return (_flags == _used_in_unconditional_delay); }
  bool used_in_conditional_delay() { return (_flags == _used_in_conditional_delay); }
  bool used_in_all_conditional_delays() { return (_flags == _used_in_all_conditional_delays); }
  bool use_delay() { return ((_flags & _use_delay) != 0); }
  bool used_in_delay() { return ((_flags & _used_in_delay) != 0); }

  enum {
    _nop_count = 1
  };

  static void initialize_nops(MachNode *nop_list[1]);

#ifndef PRODUCT
  void dump(outputStream *st = tty) const;
#endif
};


//----------------------------Declare classes derived from MachNode----------

class convB2I_reg_2Node : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return convB2I_reg_2_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
public:
  convB2I_reg_2Node() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(convB2I_reg_2Node); }
  friend MachNode *State::MachNodeGenerator(int opcode);
  // Rematerialize convB2I_reg_2
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "convB2I_reg_2";}
#endif
};

class loadUB_indirectNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return loadUB_indirect_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_LoadB; }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  loadUB_indirectNode() {  _num_opnds = 2; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(loadUB_indirectNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "loadUB_indirect";}
#endif
};

class loadUB_indirect_acNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return loadUB_indirect_ac_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_LoadB; }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  loadUB_indirect_acNode() {  _num_opnds = 2; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(loadUB_indirect_acNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "loadUB_indirect_ac";}
#endif
};

class loadB_indirect_ExNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return loadB_indirect_Ex_rule; }
  virtual int            ideal_Opcode() const { return Op_LoadB; }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  loadB_indirect_ExNode() {  _num_opnds = 2; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(loadB_indirect_ExNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "loadB_indirect_Ex";}
#endif
};

class loadB_indirect_ac_ExNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return loadB_indirect_ac_Ex_rule; }
  virtual int            ideal_Opcode() const { return Op_LoadB; }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  loadB_indirect_ac_ExNode() {  _num_opnds = 2; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(loadB_indirect_ac_ExNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "loadB_indirect_ac_Ex";}
#endif
};

class loadUB_indOffset16Node : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return loadUB_indOffset16_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_LoadB; }
  virtual uint           oper_input_base() const { return 2; }
public:
  loadUB_indOffset16Node() {  _num_opnds = 2; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(loadUB_indOffset16Node); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "loadUB_indOffset16";}
#endif
};

class loadUB_indOffset16_acNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return loadUB_indOffset16_ac_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_LoadB; }
  virtual uint           oper_input_base() const { return 2; }
public:
  loadUB_indOffset16_acNode() {  _num_opnds = 2; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(loadUB_indOffset16_acNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "loadUB_indOffset16_ac";}
#endif
};

class loadB_indOffset16_ExNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return loadB_indOffset16_Ex_rule; }
  virtual int            ideal_Opcode() const { return Op_LoadB; }
  virtual uint           oper_input_base() const { return 2; }
public:
  loadB_indOffset16_ExNode() {  _num_opnds = 2; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(loadB_indOffset16_ExNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "loadB_indOffset16_Ex";}
#endif
};

class loadB_indOffset16_ac_ExNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return loadB_indOffset16_ac_Ex_rule; }
  virtual int            ideal_Opcode() const { return Op_LoadB; }
  virtual uint           oper_input_base() const { return 2; }
public:
  loadB_indOffset16_ac_ExNode() {  _num_opnds = 2; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(loadB_indOffset16_ac_ExNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "loadB_indOffset16_ac_Ex";}
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return loadUB_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
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

class loadUB_acNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return loadUB_ac_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_LoadUB; }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  loadUB_acNode() {  _num_opnds = 2; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(loadUB_acNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "loadUB_ac";}
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return loadUB2L_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
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

class loadUB2L_acNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return loadUB2L_ac_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_ConvI2L; }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  loadUB2L_acNode() {  _num_opnds = 2; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(loadUB2L_acNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "loadUB2L_ac";}
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return loadS_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
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

class loadS_acNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return loadS_ac_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_LoadS; }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  loadS_acNode() {  _num_opnds = 2; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(loadS_acNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "loadS_ac";}
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return loadUS_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
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

class loadUS_acNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return loadUS_ac_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_LoadUS; }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  loadUS_acNode() {  _num_opnds = 2; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(loadUS_acNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "loadUS_ac";}
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return loadUS2L_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
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

class loadUS2L_acNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return loadUS2L_ac_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_ConvI2L; }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  loadUS2L_acNode() {  _num_opnds = 2; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(loadUS2L_acNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "loadUS2L_ac";}
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return loadI_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_LoadI; }
  virtual MachNode      *peephole(Block *block, int block_index, PhaseRegAlloc *ra_, int &deleted);
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

class loadI_acNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return loadI_ac_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_LoadI; }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  loadI_acNode() {  _num_opnds = 2; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(loadI_acNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "loadI_ac";}
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return loadUI2L_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return loadI2L_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_ConvI2L; }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  loadI2LNode() {  _num_opnds = 2; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(loadI2LNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "loadI2L";}
#endif
};

class loadI2L_acNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return loadI2L_ac_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_ConvI2L; }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  loadI2L_acNode() {  _num_opnds = 2; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(loadI2L_acNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "loadI2L_ac";}
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return loadL_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_LoadL; }
  virtual MachNode      *peephole(Block *block, int block_index, PhaseRegAlloc *ra_, int &deleted);
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

class loadL_acNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return loadL_ac_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_LoadL; }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  loadL_acNode() {  _num_opnds = 2; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(loadL_acNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "loadL_ac";}
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return loadL_unaligned_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return loadV8_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return loadV16_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_LoadVector; }
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return loadRange_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return loadN_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
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

class loadN_acNode : public MachTypeNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return loadN_ac_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_LoadN; }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  loadN_acNode() {  _num_opnds = 2; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(loadN_acNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "loadN_ac";}
#endif
};

class loadN2P_unscaledNode : public MachTypeNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return loadN2P_unscaled_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_DecodeN; }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  loadN2P_unscaledNode() {  _num_opnds = 2; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(loadN2P_unscaledNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "loadN2P_unscaled";}
#endif
};

class loadN2P_klass_unscaledNode : public MachTypeNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return loadN2P_klass_unscaled_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_DecodeNKlass; }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  loadN2P_klass_unscaledNode() {  _num_opnds = 2; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(loadN2P_klass_unscaledNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "loadN2P_klass_unscaled";}
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return loadP_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_LoadP; }
  virtual MachNode      *peephole(Block *block, int block_index, PhaseRegAlloc *ra_, int &deleted);
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

class loadP_acNode : public MachTypeNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return loadP_ac_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_LoadP; }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  loadP_acNode() {  _num_opnds = 2; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(loadP_acNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "loadP_ac";}
#endif
};

class loadP2XNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return loadP2X_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_CastP2X; }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  loadP2XNode() {  _num_opnds = 2; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(loadP2XNode); }
  // Rematerialize loadP2X
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "loadP2X";}
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return loadNKlass_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return loadKlass_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return loadF_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
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

class loadF_acNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return loadF_ac_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_LoadF; }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  loadF_acNode() {  _num_opnds = 3; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(loadF_acNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "loadF_ac";}
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return loadD_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
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

class loadD_acNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return loadD_ac_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_LoadD; }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  loadD_acNode() {  _num_opnds = 3; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(loadD_acNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "loadD_ac";}
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return loadD_unaligned_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
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

class loadToc_hiNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return loadToc_hi_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
public:
  loadToc_hiNode() {  _num_opnds = 1; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(loadToc_hiNode); }
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "loadToc_hi";}
#endif
};

class loadToc_loNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return loadToc_lo_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
public:
  loadToc_loNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(loadToc_loNode); }
  friend MachNode *State::MachNodeGenerator(int opcode);
  // Rematerialize loadToc_lo
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "loadToc_lo";}
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return loadConI16_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
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

class loadConIhi16Node : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return loadConIhi16_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_ConI; }
public:
  loadConIhi16Node() {  _num_opnds = 2; _opnds = _opnd_array; init_flags(Flag_is_Con); }
  virtual uint           size_of() const { return sizeof(loadConIhi16Node); }
  friend MachNode *State::MachNodeGenerator(int opcode);
  // Rematerialize loadConIhi16
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const class Type *bottom_type() const {
    return  TypeInt::make(opnd_array(1)->constant());
  };
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "loadConIhi16";}
#endif
};

class loadConI32_lo16Node : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return loadConI32_lo16_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
public:
  loadConI32_lo16Node() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(loadConI32_lo16Node); }
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "loadConI32_lo16";}
#endif
};

class loadConI_ExNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return loadConI_Ex_rule; }
  virtual int            ideal_Opcode() const { return Op_ConI; }
public:
  loadConI_ExNode() {  _num_opnds = 2; _opnds = _opnd_array; init_flags(Flag_is_Con); }
  virtual uint           size_of() const { return sizeof(loadConI_ExNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  // Rematerialize loadConI_Ex
  virtual const class Type *bottom_type() const {
    return  TypeInt::make(opnd_array(1)->constant());
  };
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "loadConI_Ex";}
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return loadConL16_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
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

class loadConL32hi16Node : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return loadConL32hi16_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_ConL; }
public:
  loadConL32hi16Node() {  _num_opnds = 2; _opnds = _opnd_array; init_flags(Flag_is_Con); }
  virtual uint           size_of() const { return sizeof(loadConL32hi16Node); }
  friend MachNode *State::MachNodeGenerator(int opcode);
  // Rematerialize loadConL32hi16
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const class Type *bottom_type() const {
    return  TypeLong::make(opnd_array(1)->constantL());
  };
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "loadConL32hi16";}
#endif
};

class loadConL32_lo16Node : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return loadConL32_lo16_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
public:
  loadConL32_lo16Node() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(loadConL32_lo16Node); }
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "loadConL32_lo16";}
#endif
};

class loadConL32_ExNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return loadConL32_Ex_rule; }
  virtual int            ideal_Opcode() const { return Op_ConL; }
public:
  loadConL32_ExNode() {  _num_opnds = 2; _opnds = _opnd_array; init_flags(Flag_is_Con); }
  virtual uint           size_of() const { return sizeof(loadConL32_ExNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  // Rematerialize loadConL32_Ex
  virtual const class Type *bottom_type() const {
    return  TypeLong::make(opnd_array(1)->constantL());
  };
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "loadConL32_Ex";}
#endif
};

class loadConLhighest16_ExNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return loadConLhighest16_Ex_rule; }
  virtual int            ideal_Opcode() const { return Op_ConL; }
public:
  loadConLhighest16_ExNode() {  _num_opnds = 2; _opnds = _opnd_array; init_flags(Flag_is_Con); }
  virtual uint           size_of() const { return sizeof(loadConLhighest16_ExNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  // Rematerialize loadConLhighest16_Ex
  virtual const class Type *bottom_type() const {
    return  TypeLong::make(opnd_array(1)->constantL());
  };
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "loadConLhighest16_Ex";}
#endif
};

class loadConLNode : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  int _cbuf_insts_offset;
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return loadConL_rule; }
  virtual int            ins_num_consts() const { return 1; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
public:
  loadConLNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(loadConLNode); }
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "loadConL";}
#endif
};

class loadConL_hiNode : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  int _cbuf_insts_offset;
  int _const_toc_offset;
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return loadConL_hi_rule; }
  virtual int            ins_num_consts() const { return 1; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
public:
  loadConL_hiNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(loadConL_hiNode); }
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "loadConL_hi";}
#endif
};

class loadConL_loNode : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  loadConL_hiNode* _const_toc_offset_hi_node;
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return loadConL_lo_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
public:
  loadConL_loNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(loadConL_loNode); }
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "loadConL_lo";}
#endif
};

class loadConL_ExNode : public MachConstantNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return loadConL_Ex_rule; }
  virtual void           eval_constant(Compile* C);
  virtual bool           requires_postalloc_expand() const { return true; }
  virtual void           postalloc_expand(GrowableArray <Node *> *nodes, PhaseRegAlloc *ra_);
  virtual int            ideal_Opcode() const { return Op_ConL; }
  virtual uint           oper_input_base() const { return 1; }
public:
  loadConL_ExNode() {  _num_opnds = 2; _opnds = _opnd_array; init_flags(Flag_is_Con); }
  virtual uint           size_of() const { return sizeof(loadConL_ExNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  // Rematerialize loadConL_Ex
  virtual const class Type *bottom_type() const {
    return  TypeLong::make(opnd_array(1)->constantL());
  };
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "loadConL_Ex";}
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return loadConN0_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_ConN; }
public:
  loadConN0Node() {  _num_opnds = 2; _opnds = _opnd_array; init_flags(Flag_is_Con); }
  virtual uint           size_of() const { return sizeof(loadConN0Node); }
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

class loadConN_hiNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return loadConN_hi_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
public:
  loadConN_hiNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(loadConN_hiNode); }
  friend MachNode *State::MachNodeGenerator(int opcode);
  // Rematerialize loadConN_hi
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "loadConN_hi";}
#endif
};

class loadConN_loNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return loadConN_lo_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
public:
  loadConN_loNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(loadConN_loNode); }
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "loadConN_lo";}
#endif
};

class rldiclNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return rldicl_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
public:
  rldiclNode() {  _num_opnds = 4; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(rldiclNode); }
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "rldicl";}
#endif
};

class clearMs32bNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return clearMs32b_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
public:
  clearMs32bNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(clearMs32bNode); }
  friend MachNode *State::MachNodeGenerator(int opcode);
  // Rematerialize clearMs32b
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "clearMs32b";}
#endif
};

class loadBaseNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return loadBase_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
public:
  loadBaseNode() {  _num_opnds = 1; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(loadBaseNode); }
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "loadBase";}
#endif
};

class loadConN_ExNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return loadConN_Ex_rule; }
  virtual bool           requires_postalloc_expand() const { return true; }
  virtual void           postalloc_expand(GrowableArray <Node *> *nodes, PhaseRegAlloc *ra_);
  virtual int            ideal_Opcode() const { return Op_ConN; }
public:
  loadConN_ExNode() {  _num_opnds = 2; _opnds = _opnd_array; init_flags(Flag_is_Con); }
  virtual uint           size_of() const { return sizeof(loadConN_ExNode); }
  friend MachNode *State::MachNodeGenerator(int opcode);
  // Rematerialize loadConN_Ex
  virtual const class Type *bottom_type() const {
    return  opnd_array(1)->type();
  };
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "loadConN_Ex";}
#endif
};

class loadConNKlass_hiNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return loadConNKlass_hi_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_ConNKlass; }
public:
  loadConNKlass_hiNode() {  _num_opnds = 2; _opnds = _opnd_array; init_flags(Flag_is_Con); }
  virtual uint           size_of() const { return sizeof(loadConNKlass_hiNode); }
  friend MachNode *State::MachNodeGenerator(int opcode);
  // Rematerialize loadConNKlass_hi
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const class Type *bottom_type() const {
    return  opnd_array(1)->type();
  };
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "loadConNKlass_hi";}
#endif
};

class loadConNKlass_maskNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return loadConNKlass_mask_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_ConNKlass; }
public:
  loadConNKlass_maskNode() {  _num_opnds = 3; _opnds = _opnd_array; init_flags(Flag_is_Con); }
  virtual uint           size_of() const { return sizeof(loadConNKlass_maskNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  // Rematerialize loadConNKlass_mask
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const class Type *bottom_type() const {
    return  opnd_array(1)->type();
  };
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "loadConNKlass_mask";}
#endif
};

class loadConNKlass_loNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return loadConNKlass_lo_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_ConNKlass; }
public:
  loadConNKlass_loNode() {  _num_opnds = 3; _opnds = _opnd_array; init_flags(Flag_is_Con); }
  virtual uint           size_of() const { return sizeof(loadConNKlass_loNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  // Rematerialize loadConNKlass_lo
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const class Type *bottom_type() const {
    return  opnd_array(1)->type();
  };
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "loadConNKlass_lo";}
#endif
};

class loadConNKlass_ExNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return loadConNKlass_Ex_rule; }
  virtual bool           requires_postalloc_expand() const { return true; }
  virtual void           postalloc_expand(GrowableArray <Node *> *nodes, PhaseRegAlloc *ra_);
  virtual int            ideal_Opcode() const { return Op_ConNKlass; }
public:
  loadConNKlass_ExNode() {  _num_opnds = 2; _opnds = _opnd_array; init_flags(Flag_is_Con); }
  virtual uint           size_of() const { return sizeof(loadConNKlass_ExNode); }
  friend MachNode *State::MachNodeGenerator(int opcode);
  // Rematerialize loadConNKlass_Ex
  virtual const class Type *bottom_type() const {
    return  opnd_array(1)->type();
  };
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "loadConNKlass_Ex";}
#endif
};

class loadConP0or1Node : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return loadConP0or1_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_ConP; }
  virtual int            reloc() const;
public:
  loadConP0or1Node() {  _num_opnds = 2; _opnds = _opnd_array; init_flags(Flag_is_Con); }
  virtual uint           size_of() const { return sizeof(loadConP0or1Node); }
  friend MachNode *State::MachNodeGenerator(int opcode);
  // Rematerialize loadConP0or1
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const class Type *bottom_type() const {
    return  opnd_array(1)->type();
  };
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "loadConP0or1";}
#endif
};

class loadConPNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return loadConP_rule; }
  virtual int            ins_num_consts() const { return 1; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_ConP; }
  virtual int            reloc() const;
public:
  loadConPNode() {  _num_opnds = 3; _opnds = _opnd_array; init_flags(Flag_is_Con); }
  virtual uint           size_of() const { return sizeof(loadConPNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  // Rematerialize loadConP
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const class Type *bottom_type() const {
    return  opnd_array(1)->type();
  };
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "loadConP";}
#endif
};

class loadConP_hiNode : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  int _const_toc_offset;
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return loadConP_hi_rule; }
  virtual int            ins_num_consts() const { return 1; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
public:
  loadConP_hiNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(loadConP_hiNode); }
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "loadConP_hi";}
#endif
};

class loadConP_loNode : public MachNode { 
private:
  MachOper *_opnd_array[3];
public:
  loadConP_hiNode* _const_toc_offset_hi_node;
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return loadConP_lo_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_ConP; }
  virtual int            reloc() const;
public:
  loadConP_loNode() {  _num_opnds = 3; _opnds = _opnd_array; init_flags(Flag_is_Con); }
  virtual uint           size_of() const { return sizeof(loadConP_loNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  // Rematerialize loadConP_lo
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const class Type *bottom_type() const {
    return  opnd_array(1)->type();
  };
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "loadConP_lo";}
#endif
};

class loadConP_ExNode : public MachConstantNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return loadConP_Ex_rule; }
  virtual int            ins_cannot_rematerialize() const { return true; }
  virtual void           eval_constant(Compile* C);
  virtual bool           requires_postalloc_expand() const { return true; }
  virtual void           postalloc_expand(GrowableArray <Node *> *nodes, PhaseRegAlloc *ra_);
  virtual int            ideal_Opcode() const { return Op_ConP; }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 1; }
public:
  loadConP_ExNode() {  _num_opnds = 2; _opnds = _opnd_array; init_flags(Flag_is_Con); }
  virtual uint           size_of() const { return sizeof(loadConP_ExNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  // Rematerialize loadConP_Ex
  virtual const class Type *bottom_type() const {
    return  opnd_array(1)->type();
  };
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "loadConP_Ex";}
#endif
};

class loadConFNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return loadConF_rule; }
  virtual int            ins_num_consts() const { return 1; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            reloc() const;
public:
  loadConFNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(loadConFNode); }
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "loadConF";}
#endif
};

class loadConFCompNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return loadConFComp_rule; }
  virtual int            ins_num_consts() const { return 1; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            reloc() const;
public:
  loadConFCompNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(loadConFCompNode); }
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "loadConFComp";}
#endif
};

class loadConF_ExNode : public MachConstantNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return loadConF_Ex_rule; }
  virtual int            ins_cannot_rematerialize() const { return true; }
  virtual void           eval_constant(Compile* C);
  virtual bool           requires_postalloc_expand() const { return true; }
  virtual void           postalloc_expand(GrowableArray <Node *> *nodes, PhaseRegAlloc *ra_);
  virtual int            ideal_Opcode() const { return Op_ConF; }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 1; }
public:
  loadConF_ExNode() {  _num_opnds = 2; _opnds = _opnd_array; init_flags(Flag_is_Con); }
  virtual uint           size_of() const { return sizeof(loadConF_ExNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  // Rematerialize loadConF_Ex
  virtual const class Type *bottom_type() const {
    return  TypeF::make(opnd_array(1)->constantF());
  };
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "loadConF_Ex";}
#endif
};

class loadConDNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return loadConD_rule; }
  virtual int            ins_num_consts() const { return 1; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            reloc() const;
public:
  loadConDNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(loadConDNode); }
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "loadConD";}
#endif
};

class loadConDCompNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return loadConDComp_rule; }
  virtual int            ins_num_consts() const { return 1; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            reloc() const;
public:
  loadConDCompNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(loadConDCompNode); }
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "loadConDComp";}
#endif
};

class loadConD_ExNode : public MachConstantNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return loadConD_Ex_rule; }
  virtual int            ins_cannot_rematerialize() const { return true; }
  virtual void           eval_constant(Compile* C);
  virtual bool           requires_postalloc_expand() const { return true; }
  virtual void           postalloc_expand(GrowableArray <Node *> *nodes, PhaseRegAlloc *ra_);
  virtual int            ideal_Opcode() const { return Op_ConD; }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 1; }
public:
  loadConD_ExNode() {  _num_opnds = 2; _opnds = _opnd_array; init_flags(Flag_is_Con); }
  virtual uint           size_of() const { return sizeof(loadConD_ExNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  // Rematerialize loadConD_Ex
  virtual const class Type *bottom_type() const {
    return  TypeD::make(opnd_array(1)->constantD());
  };
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "loadConD_Ex";}
#endif
};

class prefetch_alloc_zeroNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return prefetch_alloc_zero_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_PrefetchAllocation; }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  prefetch_alloc_zeroNode() {  _num_opnds = 3; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(prefetch_alloc_zeroNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "prefetch_alloc_zero";}
#endif
};

class prefetch_alloc_zero_no_offsetNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return prefetch_alloc_zero_no_offset_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_PrefetchAllocation; }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  prefetch_alloc_zero_no_offsetNode() {  _num_opnds = 2; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(prefetch_alloc_zero_no_offsetNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "prefetch_alloc_zero_no_offset";}
#endif
};

class prefetch_allocNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return prefetch_alloc_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_PrefetchAllocation; }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  prefetch_allocNode() {  _num_opnds = 3; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(prefetch_allocNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "prefetch_alloc";}
#endif
};

class prefetch_alloc_no_offsetNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return prefetch_alloc_no_offset_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_PrefetchAllocation; }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  prefetch_alloc_no_offsetNode() {  _num_opnds = 2; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(prefetch_alloc_no_offsetNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "prefetch_alloc_no_offset";}
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return storeB_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return storeC_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return storeI_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
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

class storeI_convL2INode : public MachTypeNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return storeI_convL2I_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_StoreI; }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  storeI_convL2INode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(storeI_convL2INode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "storeI_convL2I";}
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return storeL_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return storeA8B_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return storeV16_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_StoreVector; }
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return storeN_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return storeNKlass_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return storeP_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return storeF_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return storeD_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
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

class storeCM_CMSNode : public MachTypeNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return storeCM_CMS_rule; }
  virtual int            ins_cannot_rematerialize() const { return true; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_StoreCM; }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  storeCM_CMSNode() {  _num_opnds = 4; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(storeCM_CMSNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "storeCM_CMS";}
#endif
};

class storeCM_CMS_ExExNode : public MachTypeNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return storeCM_CMS_ExEx_rule; }
  virtual int            ideal_Opcode() const { return Op_StoreCM; }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  storeCM_CMS_ExExNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(storeCM_CMS_ExExNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "storeCM_CMS_ExEx";}
#endif
};

class storeCM_G1Node : public MachTypeNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return storeCM_G1_rule; }
  virtual int            ins_cannot_rematerialize() const { return true; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_StoreCM; }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  storeCM_G1Node() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(storeCM_G1Node); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "storeCM_G1";}
#endif
};

class encodeP_shiftNode : public MachTypeNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return encodeP_shift_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_EncodeP; }
  virtual uint           oper_input_base() const { return 1; }
public:
  encodeP_shiftNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(encodeP_shiftNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "encodeP_shift";}
#endif
};

class encodeP_subNode : public MachTypeNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return encodeP_sub_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_EncodeP; }
  virtual uint           oper_input_base() const { return 1; }
public:
  encodeP_subNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(encodeP_subNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "encodeP_sub";}
#endif
};

class cond_sub_baseNode : public MachTypeNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return cond_sub_base_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_EncodeP; }
  virtual uint           oper_input_base() const { return 1; }
public:
  cond_sub_baseNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(cond_sub_baseNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "cond_sub_base";}
#endif
};

class cond_set_0_oopNode : public MachTypeNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return cond_set_0_oop_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_EncodeP; }
  virtual uint           oper_input_base() const { return 1; }
public:
  cond_set_0_oopNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(cond_set_0_oopNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "cond_set_0_oop";}
#endif
};

class encodeP_DisjointNode : public MachTypeNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return encodeP_Disjoint_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_EncodeP; }
  virtual uint           oper_input_base() const { return 1; }
public:
  encodeP_DisjointNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(encodeP_DisjointNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "encodeP_Disjoint";}
#endif
};

class encodeP_ExNode : public MachTypeNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return encodeP_Ex_rule; }
  virtual bool           requires_postalloc_expand() const { return true; }
  virtual void           postalloc_expand(GrowableArray <Node *> *nodes, PhaseRegAlloc *ra_);
  virtual int            ideal_Opcode() const { return Op_EncodeP; }
  virtual uint           oper_input_base() const { return 1; }
public:
  encodeP_ExNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(encodeP_ExNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "encodeP_Ex";}
#endif
};

class encodeP_not_null_ExNode : public MachTypeNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return encodeP_not_null_Ex_rule; }
  virtual bool           requires_postalloc_expand() const { return true; }
  virtual void           postalloc_expand(GrowableArray <Node *> *nodes, PhaseRegAlloc *ra_);
  virtual int            ideal_Opcode() const { return Op_EncodeP; }
  virtual uint           oper_input_base() const { return 1; }
public:
  encodeP_not_null_ExNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(encodeP_not_null_ExNode); }
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "encodeP_not_null_Ex";}
#endif
};

class encodeP_not_null_base_nullNode : public MachTypeNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return encodeP_not_null_base_null_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_EncodeP; }
  virtual uint           oper_input_base() const { return 1; }
public:
  encodeP_not_null_base_nullNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(encodeP_not_null_base_nullNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "encodeP_not_null_base_null";}
#endif
};

class encodeP_narrow_oop_shift_0Node : public MachTypeNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return encodeP_narrow_oop_shift_0_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_EncodeP; }
  virtual uint           oper_input_base() const { return 1; }
public:
  encodeP_narrow_oop_shift_0Node() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(encodeP_narrow_oop_shift_0Node); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "encodeP_narrow_oop_shift_0";}
#endif
};

class decodeN_shiftNode : public MachTypeNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return decodeN_shift_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_DecodeN; }
  virtual uint           oper_input_base() const { return 1; }
public:
  decodeN_shiftNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(decodeN_shiftNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "decodeN_shift";}
#endif
};

class decodeN_addNode : public MachTypeNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return decodeN_add_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_DecodeN; }
  virtual uint           oper_input_base() const { return 1; }
public:
  decodeN_addNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(decodeN_addNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "decodeN_add";}
#endif
};

class cond_add_baseNode : public MachTypeNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return cond_add_base_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_DecodeN; }
  virtual uint           oper_input_base() const { return 1; }
public:
  cond_add_baseNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(cond_add_baseNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "cond_add_base";}
#endif
};

class cond_set_0_ptrNode : public MachTypeNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return cond_set_0_ptr_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_DecodeN; }
  virtual uint           oper_input_base() const { return 1; }
public:
  cond_set_0_ptrNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(cond_set_0_ptrNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "cond_set_0_ptr";}
#endif
};

class decodeN_ExNode : public MachTypeNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return decodeN_Ex_rule; }
  virtual bool           requires_postalloc_expand() const { return true; }
  virtual void           postalloc_expand(GrowableArray <Node *> *nodes, PhaseRegAlloc *ra_);
  virtual int            ideal_Opcode() const { return Op_DecodeN; }
  virtual uint           oper_input_base() const { return 1; }
public:
  decodeN_ExNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(decodeN_ExNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "decodeN_Ex";}
#endif
};

class decodeN_nullBaseNode : public MachTypeNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return decodeN_nullBase_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_DecodeN; }
  virtual uint           oper_input_base() const { return 1; }
public:
  decodeN_nullBaseNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(decodeN_nullBaseNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "decodeN_nullBase";}
#endif
};

class decodeN_mergeDisjointNode : public MachTypeNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return decodeN_mergeDisjoint_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_DecodeN; }
  virtual uint           oper_input_base() const { return 1; }
public:
  decodeN_mergeDisjointNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(decodeN_mergeDisjointNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "decodeN_mergeDisjoint";}
#endif
};

class decodeN_Disjoint_notNull_ExNode : public MachTypeNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return decodeN_Disjoint_notNull_Ex_rule; }
  virtual bool           requires_postalloc_expand() const { return true; }
  virtual void           postalloc_expand(GrowableArray <Node *> *nodes, PhaseRegAlloc *ra_);
  virtual int            ideal_Opcode() const { return Op_DecodeN; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges(); }
  virtual uint           oper_input_base() const { return 1; }
public:
  decodeN_Disjoint_notNull_ExNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(decodeN_Disjoint_notNull_ExNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "decodeN_Disjoint_notNull_Ex";}
#endif
};

class decodeN_Disjoint_isel_ExNode : public MachTypeNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return decodeN_Disjoint_isel_Ex_rule; }
  virtual bool           requires_postalloc_expand() const { return true; }
  virtual void           postalloc_expand(GrowableArray <Node *> *nodes, PhaseRegAlloc *ra_);
  virtual int            ideal_Opcode() const { return Op_DecodeN; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges(); }
  virtual uint           oper_input_base() const { return 1; }
public:
  decodeN_Disjoint_isel_ExNode() {  _num_opnds = 4; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(decodeN_Disjoint_isel_ExNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "decodeN_Disjoint_isel_Ex";}
#endif
};

class decodeN_notNull_addBase_ExNode : public MachTypeNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return decodeN_notNull_addBase_Ex_rule; }
  virtual bool           requires_postalloc_expand() const { return true; }
  virtual void           postalloc_expand(GrowableArray <Node *> *nodes, PhaseRegAlloc *ra_);
  virtual int            ideal_Opcode() const { return Op_DecodeN; }
  virtual uint           oper_input_base() const { return 1; }
public:
  decodeN_notNull_addBase_ExNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(decodeN_notNull_addBase_ExNode); }
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "decodeN_notNull_addBase_Ex";}
#endif
};

class decodeN_unscaledNode : public MachTypeNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return decodeN_unscaled_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_DecodeN; }
  virtual uint           oper_input_base() const { return 1; }
public:
  decodeN_unscaledNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(decodeN_unscaledNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "decodeN_unscaled";}
#endif
};

class decodeN2I_unscaledNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return decodeN2I_unscaled_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_ConvL2I; }
public:
  decodeN2I_unscaledNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(decodeN2I_unscaledNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "decodeN2I_unscaled";}
#endif
};

class encodePKlass_shiftNode : public MachTypeNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return encodePKlass_shift_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_EncodePKlass; }
  virtual uint           oper_input_base() const { return 1; }
public:
  encodePKlass_shiftNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(encodePKlass_shiftNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "encodePKlass_shift";}
#endif
};

class encodePKlass_sub_baseNode : public MachTypeNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return encodePKlass_sub_base_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_EncodePKlass; }
  virtual uint           oper_input_base() const { return 1; }
public:
  encodePKlass_sub_baseNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(encodePKlass_sub_baseNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "encodePKlass_sub_base";}
#endif
};

class encodePKlass_DisjointNode : public MachTypeNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return encodePKlass_Disjoint_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_EncodePKlass; }
  virtual uint           oper_input_base() const { return 1; }
public:
  encodePKlass_DisjointNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(encodePKlass_DisjointNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "encodePKlass_Disjoint";}
#endif
};

class encodePKlass_not_null_ExNode : public MachTypeNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return encodePKlass_not_null_Ex_rule; }
  virtual bool           requires_postalloc_expand() const { return true; }
  virtual void           postalloc_expand(GrowableArray <Node *> *nodes, PhaseRegAlloc *ra_);
  virtual int            ideal_Opcode() const { return Op_EncodePKlass; }
  virtual uint           oper_input_base() const { return 1; }
public:
  encodePKlass_not_null_ExNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(encodePKlass_not_null_ExNode); }
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "encodePKlass_not_null_Ex";}
#endif
};

class encodePKlass_not_null_ExExNode : public MachTypeNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return encodePKlass_not_null_ExEx_rule; }
  virtual int            ideal_Opcode() const { return Op_EncodePKlass; }
  virtual uint           oper_input_base() const { return 1; }
public:
  encodePKlass_not_null_ExExNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(encodePKlass_not_null_ExExNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "encodePKlass_not_null_ExEx";}
#endif
};

class decodeNKlass_shiftNode : public MachTypeNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return decodeNKlass_shift_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_DecodeNKlass; }
  virtual uint           oper_input_base() const { return 1; }
public:
  decodeNKlass_shiftNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(decodeNKlass_shiftNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "decodeNKlass_shift";}
#endif
};

class decodeNKlass_add_baseNode : public MachTypeNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return decodeNKlass_add_base_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_DecodeNKlass; }
  virtual uint           oper_input_base() const { return 1; }
public:
  decodeNKlass_add_baseNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(decodeNKlass_add_baseNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "decodeNKlass_add_base";}
#endif
};

class decodeNKlass_notNull_addBase_ExNode : public MachTypeNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return decodeNKlass_notNull_addBase_Ex_rule; }
  virtual bool           requires_postalloc_expand() const { return true; }
  virtual void           postalloc_expand(GrowableArray <Node *> *nodes, PhaseRegAlloc *ra_);
  virtual int            ideal_Opcode() const { return Op_DecodeNKlass; }
  virtual uint           oper_input_base() const { return 1; }
public:
  decodeNKlass_notNull_addBase_ExNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(decodeNKlass_notNull_addBase_ExNode); }
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "decodeNKlass_notNull_addBase_Ex";}
#endif
};

class decodeNKlass_notNull_addBase_ExExNode : public MachTypeNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return decodeNKlass_notNull_addBase_ExEx_rule; }
  virtual int            ideal_Opcode() const { return Op_DecodeNKlass; }
  virtual uint           oper_input_base() const { return 1; }
public:
  decodeNKlass_notNull_addBase_ExExNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(decodeNKlass_notNull_addBase_ExExNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "decodeNKlass_notNull_addBase_ExEx";}
#endif
};

class membar_acquireNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return membar_acquire_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_LoadFence; }
public:
  membar_acquireNode() {  _num_opnds = 1; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(membar_acquireNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  const Type            *bottom_type() const { return TypeTuple::MEMBAR; } // matched MemBar
  virtual const TypePtr *adr_type() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "membar_acquire";}
#endif
};

class unnecessary_membar_acquireNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return unnecessary_membar_acquire_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_MemBarAcquire; }
public:
  unnecessary_membar_acquireNode() {  _num_opnds = 1; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(unnecessary_membar_acquireNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  const Type            *bottom_type() const { return TypeTuple::MEMBAR; } // matched MemBar
  virtual const TypePtr *adr_type() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "unnecessary_membar_acquire";}
#endif
};

class membar_acquire_lockNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return membar_acquire_lock_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_MemBarAcquireLock; }
public:
  membar_acquire_lockNode() {  _num_opnds = 1; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(membar_acquire_lockNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  const Type            *bottom_type() const { return TypeTuple::MEMBAR; } // matched MemBar
  virtual const TypePtr *adr_type() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "membar_acquire_lock";}
#endif
};

class membar_releaseNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return membar_release_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_MemBarRelease; }
public:
  membar_releaseNode() {  _num_opnds = 1; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(membar_releaseNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  const Type            *bottom_type() const { return TypeTuple::MEMBAR; } // matched MemBar
  virtual const TypePtr *adr_type() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "membar_release";}
#endif
};

class membar_release_0Node : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return membar_release_0_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_StoreFence; }
public:
  membar_release_0Node() {  _num_opnds = 1; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(membar_release_0Node); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  const Type            *bottom_type() const { return TypeTuple::MEMBAR; } // matched MemBar
  virtual const TypePtr *adr_type() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "membar_release_0";}
#endif
};

class membar_storestoreNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return membar_storestore_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_MemBarStoreStore; }
public:
  membar_storestoreNode() {  _num_opnds = 1; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(membar_storestoreNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  const Type            *bottom_type() const { return TypeTuple::MEMBAR; } // matched MemBar
  virtual const TypePtr *adr_type() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "membar_storestore";}
#endif
};

class membar_release_lockNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return membar_release_lock_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_MemBarReleaseLock; }
public:
  membar_release_lockNode() {  _num_opnds = 1; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(membar_release_lockNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  const Type            *bottom_type() const { return TypeTuple::MEMBAR; } // matched MemBar
  virtual const TypePtr *adr_type() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "membar_release_lock";}
#endif
};

class membar_volatileNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return membar_volatile_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_MemBarVolatile; }
public:
  membar_volatileNode() {  _num_opnds = 1; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(membar_volatileNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  const Type            *bottom_type() const { return TypeTuple::MEMBAR; } // matched MemBar
  virtual const TypePtr *adr_type() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "membar_volatile";}
#endif
};

class membar_CPUOrderNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return membar_CPUOrder_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_MemBarCPUOrder; }
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

class cmovI_reg_iselNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return cmovI_reg_isel_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_CMoveI; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges() + opnd_array(2)->num_edges(); }
public:
  cmovI_reg_iselNode() {  _num_opnds = 5; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(cmovI_reg_iselNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "cmovI_reg_isel";}
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return cmovI_reg_rule; }
  virtual int            ins_variable_size_depending_on_alignment() const { return true; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return cmovI_imm_rule; }
  virtual int            ins_variable_size_depending_on_alignment() const { return true; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
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

class cmovL_reg_iselNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return cmovL_reg_isel_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_CMoveL; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges() + opnd_array(2)->num_edges(); }
public:
  cmovL_reg_iselNode() {  _num_opnds = 5; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(cmovL_reg_iselNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "cmovL_reg_isel";}
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return cmovL_reg_rule; }
  virtual int            ins_variable_size_depending_on_alignment() const { return true; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return cmovL_imm_rule; }
  virtual int            ins_variable_size_depending_on_alignment() const { return true; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
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

class cmovN_reg_iselNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return cmovN_reg_isel_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_CMoveN; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges() + opnd_array(2)->num_edges(); }
public:
  cmovN_reg_iselNode() {  _num_opnds = 5; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(cmovN_reg_iselNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  const Type            *bottom_type() const { const Type *t = in(oper_input_base()+1)->bottom_type(); return (req() <= oper_input_base()+2) ? t : t->meet(in(oper_input_base()+2)->bottom_type()); } // CMoveN
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "cmovN_reg_isel";}
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return cmovN_reg_rule; }
  virtual int            ins_variable_size_depending_on_alignment() const { return true; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_CMoveN; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges() + opnd_array(2)->num_edges(); }
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return cmovN_imm_rule; }
  virtual int            ins_variable_size_depending_on_alignment() const { return true; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
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

class cmovP_reg_iselNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return cmovP_reg_isel_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_CMoveP; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges() + opnd_array(2)->num_edges(); }
public:
  cmovP_reg_iselNode() {  _num_opnds = 5; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(cmovP_reg_iselNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  const Type            *bottom_type() const { const Type *t = in(oper_input_base()+1)->bottom_type(); return (req() <= oper_input_base()+2) ? t : t->meet(in(oper_input_base()+2)->bottom_type()); } // CMoveP
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "cmovP_reg_isel";}
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return cmovP_reg_rule; }
  virtual int            ins_variable_size_depending_on_alignment() const { return true; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return cmovP_imm_rule; }
  virtual int            ins_variable_size_depending_on_alignment() const { return true; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return cmovF_reg_rule; }
  virtual int            ins_variable_size_depending_on_alignment() const { return true; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return cmovD_reg_rule; }
  virtual int            ins_variable_size_depending_on_alignment() const { return true; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
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

class storeLConditional_regP_regL_regLNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return storeLConditional_regP_regL_regL_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_StoreLConditional; }
  virtual uint           oper_input_base() const { return 2; }
public:
  storeLConditional_regP_regL_regLNode() {  _num_opnds = 5; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(storeLConditional_regP_regL_regLNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  // Rematerialize storeLConditional_regP_regL_regL
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "storeLConditional_regP_regL_regL";}
#endif
};

class storePConditional_regP_regP_regPNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return storePConditional_regP_regP_regP_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_StorePConditional; }
  virtual uint           oper_input_base() const { return 2; }
public:
  storePConditional_regP_regP_regPNode() {  _num_opnds = 4; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(storePConditional_regP_regP_regPNode); }
  // Rematerialize storePConditional_regP_regP_regP
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "storePConditional_regP_regP_regP";}
#endif
};

class loadPLockedNode : public MachTypeNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return loadPLocked_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_LoadPLocked; }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  loadPLockedNode() {  _num_opnds = 2; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(loadPLockedNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "loadPLocked";}
#endif
};

class compareAndSwapB_regP_regI_regINode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return compareAndSwapB_regP_regI_regI_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_CompareAndSwapB; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges() + opnd_array(2)->num_edges() + opnd_array(3)->num_edges(); }
  virtual uint           oper_input_base() const { return 2; }
public:
  compareAndSwapB_regP_regI_regINode() {  _num_opnds = 6; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(compareAndSwapB_regP_regI_regINode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "compareAndSwapB_regP_regI_regI";}
#endif
};

class compareAndSwapB4_regP_regI_regINode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return compareAndSwapB4_regP_regI_regI_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_CompareAndSwapB; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges() + opnd_array(2)->num_edges() + opnd_array(3)->num_edges(); }
  virtual uint           oper_input_base() const { return 2; }
public:
  compareAndSwapB4_regP_regI_regINode() {  _num_opnds = 8; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(compareAndSwapB4_regP_regI_regINode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "compareAndSwapB4_regP_regI_regI";}
#endif
};

class compareAndSwapS_regP_regI_regINode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return compareAndSwapS_regP_regI_regI_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_CompareAndSwapS; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges() + opnd_array(2)->num_edges() + opnd_array(3)->num_edges(); }
  virtual uint           oper_input_base() const { return 2; }
public:
  compareAndSwapS_regP_regI_regINode() {  _num_opnds = 6; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(compareAndSwapS_regP_regI_regINode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "compareAndSwapS_regP_regI_regI";}
#endif
};

class compareAndSwapS4_regP_regI_regINode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return compareAndSwapS4_regP_regI_regI_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_CompareAndSwapS; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges() + opnd_array(2)->num_edges() + opnd_array(3)->num_edges(); }
  virtual uint           oper_input_base() const { return 2; }
public:
  compareAndSwapS4_regP_regI_regINode() {  _num_opnds = 8; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(compareAndSwapS4_regP_regI_regINode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "compareAndSwapS4_regP_regI_regI";}
#endif
};

class compareAndSwapI_regP_regI_regINode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return compareAndSwapI_regP_regI_regI_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_CompareAndSwapI; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges() + opnd_array(2)->num_edges() + opnd_array(3)->num_edges(); }
  virtual uint           oper_input_base() const { return 2; }
public:
  compareAndSwapI_regP_regI_regINode() {  _num_opnds = 6; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(compareAndSwapI_regP_regI_regINode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "compareAndSwapI_regP_regI_regI";}
#endif
};

class compareAndSwapN_regP_regN_regNNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return compareAndSwapN_regP_regN_regN_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_CompareAndSwapN; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges() + opnd_array(2)->num_edges() + opnd_array(3)->num_edges(); }
  virtual uint           oper_input_base() const { return 2; }
public:
  compareAndSwapN_regP_regN_regNNode() {  _num_opnds = 6; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(compareAndSwapN_regP_regN_regNNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "compareAndSwapN_regP_regN_regN";}
#endif
};

class compareAndSwapL_regP_regL_regLNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return compareAndSwapL_regP_regL_regL_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_CompareAndSwapL; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges() + opnd_array(2)->num_edges() + opnd_array(3)->num_edges(); }
  virtual uint           oper_input_base() const { return 2; }
public:
  compareAndSwapL_regP_regL_regLNode() {  _num_opnds = 6; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(compareAndSwapL_regP_regL_regLNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "compareAndSwapL_regP_regL_regL";}
#endif
};

class compareAndSwapP_regP_regP_regPNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return compareAndSwapP_regP_regP_regP_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_CompareAndSwapP; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges() + opnd_array(2)->num_edges() + opnd_array(3)->num_edges(); }
  virtual uint           oper_input_base() const { return 2; }
public:
  compareAndSwapP_regP_regP_regPNode() {  _num_opnds = 6; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(compareAndSwapP_regP_regP_regPNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "compareAndSwapP_regP_regP_regP";}
#endif
};

class weakCompareAndSwapB_regP_regI_regINode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return weakCompareAndSwapB_regP_regI_regI_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_WeakCompareAndSwapB; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges() + opnd_array(2)->num_edges() + opnd_array(3)->num_edges(); }
  virtual uint           oper_input_base() const { return 2; }
public:
  weakCompareAndSwapB_regP_regI_regINode() {  _num_opnds = 6; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(weakCompareAndSwapB_regP_regI_regINode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "weakCompareAndSwapB_regP_regI_regI";}
#endif
};

class weakCompareAndSwapB4_regP_regI_regINode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return weakCompareAndSwapB4_regP_regI_regI_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_WeakCompareAndSwapB; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges() + opnd_array(2)->num_edges() + opnd_array(3)->num_edges(); }
  virtual uint           oper_input_base() const { return 2; }
public:
  weakCompareAndSwapB4_regP_regI_regINode() {  _num_opnds = 8; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(weakCompareAndSwapB4_regP_regI_regINode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "weakCompareAndSwapB4_regP_regI_regI";}
#endif
};

class weakCompareAndSwapB_acq_regP_regI_regINode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return weakCompareAndSwapB_acq_regP_regI_regI_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_WeakCompareAndSwapB; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges() + opnd_array(2)->num_edges() + opnd_array(3)->num_edges(); }
  virtual uint           oper_input_base() const { return 2; }
public:
  weakCompareAndSwapB_acq_regP_regI_regINode() {  _num_opnds = 6; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(weakCompareAndSwapB_acq_regP_regI_regINode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "weakCompareAndSwapB_acq_regP_regI_regI";}
#endif
};

class weakCompareAndSwapB4_acq_regP_regI_regINode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return weakCompareAndSwapB4_acq_regP_regI_regI_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_WeakCompareAndSwapB; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges() + opnd_array(2)->num_edges() + opnd_array(3)->num_edges(); }
  virtual uint           oper_input_base() const { return 2; }
public:
  weakCompareAndSwapB4_acq_regP_regI_regINode() {  _num_opnds = 8; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(weakCompareAndSwapB4_acq_regP_regI_regINode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "weakCompareAndSwapB4_acq_regP_regI_regI";}
#endif
};

class weakCompareAndSwapS_regP_regI_regINode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return weakCompareAndSwapS_regP_regI_regI_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_WeakCompareAndSwapS; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges() + opnd_array(2)->num_edges() + opnd_array(3)->num_edges(); }
  virtual uint           oper_input_base() const { return 2; }
public:
  weakCompareAndSwapS_regP_regI_regINode() {  _num_opnds = 6; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(weakCompareAndSwapS_regP_regI_regINode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "weakCompareAndSwapS_regP_regI_regI";}
#endif
};

class weakCompareAndSwapS4_regP_regI_regINode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return weakCompareAndSwapS4_regP_regI_regI_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_WeakCompareAndSwapS; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges() + opnd_array(2)->num_edges() + opnd_array(3)->num_edges(); }
  virtual uint           oper_input_base() const { return 2; }
public:
  weakCompareAndSwapS4_regP_regI_regINode() {  _num_opnds = 8; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(weakCompareAndSwapS4_regP_regI_regINode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "weakCompareAndSwapS4_regP_regI_regI";}
#endif
};

class weakCompareAndSwapS_acq_regP_regI_regINode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return weakCompareAndSwapS_acq_regP_regI_regI_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_WeakCompareAndSwapS; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges() + opnd_array(2)->num_edges() + opnd_array(3)->num_edges(); }
  virtual uint           oper_input_base() const { return 2; }
public:
  weakCompareAndSwapS_acq_regP_regI_regINode() {  _num_opnds = 6; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(weakCompareAndSwapS_acq_regP_regI_regINode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "weakCompareAndSwapS_acq_regP_regI_regI";}
#endif
};

class weakCompareAndSwapS4_acq_regP_regI_regINode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return weakCompareAndSwapS4_acq_regP_regI_regI_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_WeakCompareAndSwapS; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges() + opnd_array(2)->num_edges() + opnd_array(3)->num_edges(); }
  virtual uint           oper_input_base() const { return 2; }
public:
  weakCompareAndSwapS4_acq_regP_regI_regINode() {  _num_opnds = 8; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(weakCompareAndSwapS4_acq_regP_regI_regINode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "weakCompareAndSwapS4_acq_regP_regI_regI";}
#endif
};

class weakCompareAndSwapI_regP_regI_regINode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return weakCompareAndSwapI_regP_regI_regI_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_WeakCompareAndSwapI; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges() + opnd_array(2)->num_edges() + opnd_array(3)->num_edges(); }
  virtual uint           oper_input_base() const { return 2; }
public:
  weakCompareAndSwapI_regP_regI_regINode() {  _num_opnds = 6; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(weakCompareAndSwapI_regP_regI_regINode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "weakCompareAndSwapI_regP_regI_regI";}
#endif
};

class weakCompareAndSwapI_acq_regP_regI_regINode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return weakCompareAndSwapI_acq_regP_regI_regI_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_WeakCompareAndSwapI; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges() + opnd_array(2)->num_edges() + opnd_array(3)->num_edges(); }
  virtual uint           oper_input_base() const { return 2; }
public:
  weakCompareAndSwapI_acq_regP_regI_regINode() {  _num_opnds = 6; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(weakCompareAndSwapI_acq_regP_regI_regINode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "weakCompareAndSwapI_acq_regP_regI_regI";}
#endif
};

class weakCompareAndSwapN_regP_regN_regNNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return weakCompareAndSwapN_regP_regN_regN_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_WeakCompareAndSwapN; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges() + opnd_array(2)->num_edges() + opnd_array(3)->num_edges(); }
  virtual uint           oper_input_base() const { return 2; }
public:
  weakCompareAndSwapN_regP_regN_regNNode() {  _num_opnds = 6; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(weakCompareAndSwapN_regP_regN_regNNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "weakCompareAndSwapN_regP_regN_regN";}
#endif
};

class weakCompareAndSwapN_acq_regP_regN_regNNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return weakCompareAndSwapN_acq_regP_regN_regN_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_WeakCompareAndSwapN; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges() + opnd_array(2)->num_edges() + opnd_array(3)->num_edges(); }
  virtual uint           oper_input_base() const { return 2; }
public:
  weakCompareAndSwapN_acq_regP_regN_regNNode() {  _num_opnds = 6; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(weakCompareAndSwapN_acq_regP_regN_regNNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "weakCompareAndSwapN_acq_regP_regN_regN";}
#endif
};

class weakCompareAndSwapL_regP_regL_regLNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return weakCompareAndSwapL_regP_regL_regL_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_WeakCompareAndSwapL; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges() + opnd_array(2)->num_edges() + opnd_array(3)->num_edges(); }
  virtual uint           oper_input_base() const { return 2; }
public:
  weakCompareAndSwapL_regP_regL_regLNode() {  _num_opnds = 6; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(weakCompareAndSwapL_regP_regL_regLNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "weakCompareAndSwapL_regP_regL_regL";}
#endif
};

class weakCompareAndSwapL_acq_regP_regL_regLNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return weakCompareAndSwapL_acq_regP_regL_regL_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_WeakCompareAndSwapL; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges() + opnd_array(2)->num_edges() + opnd_array(3)->num_edges(); }
  virtual uint           oper_input_base() const { return 2; }
public:
  weakCompareAndSwapL_acq_regP_regL_regLNode() {  _num_opnds = 6; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(weakCompareAndSwapL_acq_regP_regL_regLNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "weakCompareAndSwapL_acq_regP_regL_regL";}
#endif
};

class weakCompareAndSwapP_regP_regP_regPNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return weakCompareAndSwapP_regP_regP_regP_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_WeakCompareAndSwapP; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges() + opnd_array(2)->num_edges() + opnd_array(3)->num_edges(); }
  virtual uint           oper_input_base() const { return 2; }
public:
  weakCompareAndSwapP_regP_regP_regPNode() {  _num_opnds = 6; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(weakCompareAndSwapP_regP_regP_regPNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "weakCompareAndSwapP_regP_regP_regP";}
#endif
};

class weakCompareAndSwapP_acq_regP_regP_regPNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return weakCompareAndSwapP_acq_regP_regP_regP_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_WeakCompareAndSwapP; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges() + opnd_array(2)->num_edges() + opnd_array(3)->num_edges(); }
  virtual uint           oper_input_base() const { return 2; }
public:
  weakCompareAndSwapP_acq_regP_regP_regPNode() {  _num_opnds = 6; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(weakCompareAndSwapP_acq_regP_regP_regPNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "weakCompareAndSwapP_acq_regP_regP_regP";}
#endif
};

class compareAndExchangeB_regP_regI_regINode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return compareAndExchangeB_regP_regI_regI_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_CompareAndExchangeB; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges() + opnd_array(2)->num_edges() + opnd_array(3)->num_edges(); }
  virtual uint           oper_input_base() const { return 2; }
public:
  compareAndExchangeB_regP_regI_regINode() {  _num_opnds = 6; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(compareAndExchangeB_regP_regI_regINode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "compareAndExchangeB_regP_regI_regI";}
#endif
};

class compareAndExchangeB4_regP_regI_regINode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return compareAndExchangeB4_regP_regI_regI_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_CompareAndExchangeB; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges() + opnd_array(2)->num_edges() + opnd_array(3)->num_edges(); }
  virtual uint           oper_input_base() const { return 2; }
public:
  compareAndExchangeB4_regP_regI_regINode() {  _num_opnds = 7; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(compareAndExchangeB4_regP_regI_regINode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "compareAndExchangeB4_regP_regI_regI";}
#endif
};

class compareAndExchangeB_acq_regP_regI_regINode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return compareAndExchangeB_acq_regP_regI_regI_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_CompareAndExchangeB; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges() + opnd_array(2)->num_edges() + opnd_array(3)->num_edges(); }
  virtual uint           oper_input_base() const { return 2; }
public:
  compareAndExchangeB_acq_regP_regI_regINode() {  _num_opnds = 6; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(compareAndExchangeB_acq_regP_regI_regINode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "compareAndExchangeB_acq_regP_regI_regI";}
#endif
};

class compareAndExchangeB4_acq_regP_regI_regINode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return compareAndExchangeB4_acq_regP_regI_regI_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_CompareAndExchangeB; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges() + opnd_array(2)->num_edges() + opnd_array(3)->num_edges(); }
  virtual uint           oper_input_base() const { return 2; }
public:
  compareAndExchangeB4_acq_regP_regI_regINode() {  _num_opnds = 7; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(compareAndExchangeB4_acq_regP_regI_regINode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "compareAndExchangeB4_acq_regP_regI_regI";}
#endif
};

class compareAndExchangeS_regP_regI_regINode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return compareAndExchangeS_regP_regI_regI_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_CompareAndExchangeS; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges() + opnd_array(2)->num_edges() + opnd_array(3)->num_edges(); }
  virtual uint           oper_input_base() const { return 2; }
public:
  compareAndExchangeS_regP_regI_regINode() {  _num_opnds = 6; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(compareAndExchangeS_regP_regI_regINode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "compareAndExchangeS_regP_regI_regI";}
#endif
};

class compareAndExchangeS4_regP_regI_regINode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return compareAndExchangeS4_regP_regI_regI_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_CompareAndExchangeS; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges() + opnd_array(2)->num_edges() + opnd_array(3)->num_edges(); }
  virtual uint           oper_input_base() const { return 2; }
public:
  compareAndExchangeS4_regP_regI_regINode() {  _num_opnds = 7; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(compareAndExchangeS4_regP_regI_regINode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "compareAndExchangeS4_regP_regI_regI";}
#endif
};

class compareAndExchangeS_acq_regP_regI_regINode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return compareAndExchangeS_acq_regP_regI_regI_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_CompareAndExchangeS; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges() + opnd_array(2)->num_edges() + opnd_array(3)->num_edges(); }
  virtual uint           oper_input_base() const { return 2; }
public:
  compareAndExchangeS_acq_regP_regI_regINode() {  _num_opnds = 6; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(compareAndExchangeS_acq_regP_regI_regINode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "compareAndExchangeS_acq_regP_regI_regI";}
#endif
};

class compareAndExchangeS4_acq_regP_regI_regINode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return compareAndExchangeS4_acq_regP_regI_regI_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_CompareAndExchangeS; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges() + opnd_array(2)->num_edges() + opnd_array(3)->num_edges(); }
  virtual uint           oper_input_base() const { return 2; }
public:
  compareAndExchangeS4_acq_regP_regI_regINode() {  _num_opnds = 7; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(compareAndExchangeS4_acq_regP_regI_regINode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "compareAndExchangeS4_acq_regP_regI_regI";}
#endif
};

class compareAndExchangeI_regP_regI_regINode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return compareAndExchangeI_regP_regI_regI_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_CompareAndExchangeI; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges() + opnd_array(2)->num_edges() + opnd_array(3)->num_edges(); }
  virtual uint           oper_input_base() const { return 2; }
public:
  compareAndExchangeI_regP_regI_regINode() {  _num_opnds = 6; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(compareAndExchangeI_regP_regI_regINode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "compareAndExchangeI_regP_regI_regI";}
#endif
};

class compareAndExchangeI_acq_regP_regI_regINode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return compareAndExchangeI_acq_regP_regI_regI_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_CompareAndExchangeI; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges() + opnd_array(2)->num_edges() + opnd_array(3)->num_edges(); }
  virtual uint           oper_input_base() const { return 2; }
public:
  compareAndExchangeI_acq_regP_regI_regINode() {  _num_opnds = 6; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(compareAndExchangeI_acq_regP_regI_regINode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "compareAndExchangeI_acq_regP_regI_regI";}
#endif
};

class compareAndExchangeN_regP_regN_regNNode : public MachTypeNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return compareAndExchangeN_regP_regN_regN_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_CompareAndExchangeN; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges() + opnd_array(2)->num_edges() + opnd_array(3)->num_edges(); }
  virtual uint           oper_input_base() const { return 2; }
public:
  compareAndExchangeN_regP_regN_regNNode() {  _num_opnds = 6; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(compareAndExchangeN_regP_regN_regNNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "compareAndExchangeN_regP_regN_regN";}
#endif
};

class compareAndExchangeN_acq_regP_regN_regNNode : public MachTypeNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return compareAndExchangeN_acq_regP_regN_regN_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_CompareAndExchangeN; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges() + opnd_array(2)->num_edges() + opnd_array(3)->num_edges(); }
  virtual uint           oper_input_base() const { return 2; }
public:
  compareAndExchangeN_acq_regP_regN_regNNode() {  _num_opnds = 6; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(compareAndExchangeN_acq_regP_regN_regNNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "compareAndExchangeN_acq_regP_regN_regN";}
#endif
};

class compareAndExchangeL_regP_regL_regLNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return compareAndExchangeL_regP_regL_regL_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_CompareAndExchangeL; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges() + opnd_array(2)->num_edges() + opnd_array(3)->num_edges(); }
  virtual uint           oper_input_base() const { return 2; }
public:
  compareAndExchangeL_regP_regL_regLNode() {  _num_opnds = 6; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(compareAndExchangeL_regP_regL_regLNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "compareAndExchangeL_regP_regL_regL";}
#endif
};

class compareAndExchangeL_acq_regP_regL_regLNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return compareAndExchangeL_acq_regP_regL_regL_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_CompareAndExchangeL; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges() + opnd_array(2)->num_edges() + opnd_array(3)->num_edges(); }
  virtual uint           oper_input_base() const { return 2; }
public:
  compareAndExchangeL_acq_regP_regL_regLNode() {  _num_opnds = 6; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(compareAndExchangeL_acq_regP_regL_regLNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "compareAndExchangeL_acq_regP_regL_regL";}
#endif
};

class compareAndExchangeP_regP_regP_regPNode : public MachTypeNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return compareAndExchangeP_regP_regP_regP_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_CompareAndExchangeP; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges() + opnd_array(2)->num_edges() + opnd_array(3)->num_edges(); }
  virtual uint           oper_input_base() const { return 2; }
public:
  compareAndExchangeP_regP_regP_regPNode() {  _num_opnds = 6; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(compareAndExchangeP_regP_regP_regPNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "compareAndExchangeP_regP_regP_regP";}
#endif
};

class compareAndExchangeP_acq_regP_regP_regPNode : public MachTypeNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return compareAndExchangeP_acq_regP_regP_regP_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_CompareAndExchangeP; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges() + opnd_array(2)->num_edges() + opnd_array(3)->num_edges(); }
  virtual uint           oper_input_base() const { return 2; }
public:
  compareAndExchangeP_acq_regP_regP_regPNode() {  _num_opnds = 6; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(compareAndExchangeP_acq_regP_regP_regPNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "compareAndExchangeP_acq_regP_regP_regP";}
#endif
};

class getAndAddBNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return getAndAddB_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_GetAndAddB; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges() + opnd_array(2)->num_edges(); }
  virtual uint           oper_input_base() const { return 2; }
public:
  getAndAddBNode() {  _num_opnds = 5; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(getAndAddBNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "getAndAddB";}
#endif
};

class getAndAddB4Node : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return getAndAddB4_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_GetAndAddB; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges() + opnd_array(2)->num_edges(); }
  virtual uint           oper_input_base() const { return 2; }
public:
  getAndAddB4Node() {  _num_opnds = 7; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(getAndAddB4Node); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "getAndAddB4";}
#endif
};

class getAndAddSNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return getAndAddS_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_GetAndAddS; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges() + opnd_array(2)->num_edges(); }
  virtual uint           oper_input_base() const { return 2; }
public:
  getAndAddSNode() {  _num_opnds = 5; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(getAndAddSNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "getAndAddS";}
#endif
};

class getAndAddS4Node : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return getAndAddS4_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_GetAndAddS; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges() + opnd_array(2)->num_edges(); }
  virtual uint           oper_input_base() const { return 2; }
public:
  getAndAddS4Node() {  _num_opnds = 7; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(getAndAddS4Node); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "getAndAddS4";}
#endif
};

class getAndAddINode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return getAndAddI_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_GetAndAddI; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges() + opnd_array(2)->num_edges(); }
  virtual uint           oper_input_base() const { return 2; }
public:
  getAndAddINode() {  _num_opnds = 5; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(getAndAddINode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "getAndAddI";}
#endif
};

class getAndAddLNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return getAndAddL_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_GetAndAddL; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges() + opnd_array(2)->num_edges(); }
  virtual uint           oper_input_base() const { return 2; }
public:
  getAndAddLNode() {  _num_opnds = 5; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(getAndAddLNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "getAndAddL";}
#endif
};

class getAndSetBNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return getAndSetB_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_GetAndSetB; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges() + opnd_array(2)->num_edges(); }
  virtual uint           oper_input_base() const { return 2; }
public:
  getAndSetBNode() {  _num_opnds = 5; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(getAndSetBNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "getAndSetB";}
#endif
};

class getAndSetB4Node : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return getAndSetB4_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_GetAndSetB; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges() + opnd_array(2)->num_edges(); }
  virtual uint           oper_input_base() const { return 2; }
public:
  getAndSetB4Node() {  _num_opnds = 7; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(getAndSetB4Node); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "getAndSetB4";}
#endif
};

class getAndSetSNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return getAndSetS_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_GetAndSetS; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges() + opnd_array(2)->num_edges(); }
  virtual uint           oper_input_base() const { return 2; }
public:
  getAndSetSNode() {  _num_opnds = 5; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(getAndSetSNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "getAndSetS";}
#endif
};

class getAndSetS4Node : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return getAndSetS4_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_GetAndSetS; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges() + opnd_array(2)->num_edges(); }
  virtual uint           oper_input_base() const { return 2; }
public:
  getAndSetS4Node() {  _num_opnds = 7; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(getAndSetS4Node); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "getAndSetS4";}
#endif
};

class getAndSetINode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return getAndSetI_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_GetAndSetI; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges() + opnd_array(2)->num_edges(); }
  virtual uint           oper_input_base() const { return 2; }
public:
  getAndSetINode() {  _num_opnds = 5; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(getAndSetINode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "getAndSetI";}
#endif
};

class getAndSetLNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return getAndSetL_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_GetAndSetL; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges() + opnd_array(2)->num_edges(); }
  virtual uint           oper_input_base() const { return 2; }
public:
  getAndSetLNode() {  _num_opnds = 5; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(getAndSetLNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "getAndSetL";}
#endif
};

class getAndSetPNode : public MachTypeNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return getAndSetP_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_GetAndSetP; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges() + opnd_array(2)->num_edges(); }
  virtual uint           oper_input_base() const { return 2; }
public:
  getAndSetPNode() {  _num_opnds = 5; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(getAndSetPNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "getAndSetP";}
#endif
};

class getAndSetNNode : public MachTypeNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return getAndSetN_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_GetAndSetN; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges() + opnd_array(2)->num_edges(); }
  virtual uint           oper_input_base() const { return 2; }
public:
  getAndSetNNode() {  _num_opnds = 5; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(getAndSetNNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "getAndSetN";}
#endif
};

class addI_reg_regNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return addI_reg_reg_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_AddI; }
  virtual int            reloc() const;
public:
  addI_reg_regNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(addI_reg_regNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "addI_reg_reg";}
#endif
};

class addI_reg_reg_2Node : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return addI_reg_reg_2_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
public:
  addI_reg_reg_2Node() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(addI_reg_reg_2Node); }
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "addI_reg_reg_2";}
#endif
};

class tree_addI_addI_addI_reg_reg_ExNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return tree_addI_addI_addI_reg_reg_Ex_rule; }
  virtual int            ideal_Opcode() const { return Op_AddI; }
public:
  tree_addI_addI_addI_reg_reg_ExNode() {  _num_opnds = 5; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(tree_addI_addI_addI_reg_reg_ExNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "tree_addI_addI_addI_reg_reg_Ex";}
#endif
};

class tree_addI_addI_addI_reg_reg_Ex_1Node : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return tree_addI_addI_addI_reg_reg_Ex_1_rule; }
  virtual int            ideal_Opcode() const { return Op_AddI; }
public:
  tree_addI_addI_addI_reg_reg_Ex_1Node() {  _num_opnds = 5; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(tree_addI_addI_addI_reg_reg_Ex_1Node); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "tree_addI_addI_addI_reg_reg_Ex_1";}
#endif
};

class tree_addI_addI_addI_reg_reg_Ex_0Node : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return tree_addI_addI_addI_reg_reg_Ex_0_rule; }
  virtual int            ideal_Opcode() const { return Op_AddI; }
public:
  tree_addI_addI_addI_reg_reg_Ex_0Node() {  _num_opnds = 5; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(tree_addI_addI_addI_reg_reg_Ex_0Node); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "tree_addI_addI_addI_reg_reg_Ex_0";}
#endif
};

class tree_addI_addI_addI_reg_reg_Ex_2Node : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return tree_addI_addI_addI_reg_reg_Ex_2_rule; }
  virtual int            ideal_Opcode() const { return Op_AddI; }
public:
  tree_addI_addI_addI_reg_reg_Ex_2Node() {  _num_opnds = 5; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(tree_addI_addI_addI_reg_reg_Ex_2Node); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "tree_addI_addI_addI_reg_reg_Ex_2";}
#endif
};

class addI_reg_imm16Node : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return addI_reg_imm16_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_AddI; }
public:
  addI_reg_imm16Node() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(addI_reg_imm16Node); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "addI_reg_imm16";}
#endif
};

class addI_reg_immhi16Node : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return addI_reg_immhi16_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_AddI; }
public:
  addI_reg_immhi16Node() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(addI_reg_immhi16Node); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "addI_reg_immhi16";}
#endif
};

class addL_reg_regNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return addL_reg_reg_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_AddL; }
public:
  addL_reg_regNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(addL_reg_regNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "addL_reg_reg";}
#endif
};

class addL_reg_reg_2Node : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return addL_reg_reg_2_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
public:
  addL_reg_reg_2Node() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(addL_reg_reg_2Node); }
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "addL_reg_reg_2";}
#endif
};

class tree_addL_addL_addL_reg_reg_ExNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return tree_addL_addL_addL_reg_reg_Ex_rule; }
  virtual int            ideal_Opcode() const { return Op_AddL; }
public:
  tree_addL_addL_addL_reg_reg_ExNode() {  _num_opnds = 5; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(tree_addL_addL_addL_reg_reg_ExNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "tree_addL_addL_addL_reg_reg_Ex";}
#endif
};

class tree_addL_addL_addL_reg_reg_Ex_1Node : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return tree_addL_addL_addL_reg_reg_Ex_1_rule; }
  virtual int            ideal_Opcode() const { return Op_AddL; }
public:
  tree_addL_addL_addL_reg_reg_Ex_1Node() {  _num_opnds = 5; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(tree_addL_addL_addL_reg_reg_Ex_1Node); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "tree_addL_addL_addL_reg_reg_Ex_1";}
#endif
};

class tree_addL_addL_addL_reg_reg_Ex_0Node : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return tree_addL_addL_addL_reg_reg_Ex_0_rule; }
  virtual int            ideal_Opcode() const { return Op_AddL; }
public:
  tree_addL_addL_addL_reg_reg_Ex_0Node() {  _num_opnds = 5; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(tree_addL_addL_addL_reg_reg_Ex_0Node); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "tree_addL_addL_addL_reg_reg_Ex_0";}
#endif
};

class tree_addL_addL_addL_reg_reg_Ex_2Node : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return tree_addL_addL_addL_reg_reg_Ex_2_rule; }
  virtual int            ideal_Opcode() const { return Op_AddL; }
public:
  tree_addL_addL_addL_reg_reg_Ex_2Node() {  _num_opnds = 5; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(tree_addL_addL_addL_reg_reg_Ex_2Node); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "tree_addL_addL_addL_reg_reg_Ex_2";}
#endif
};

class addI_regL_regLNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return addI_regL_regL_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_ConvL2I; }
public:
  addI_regL_regLNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(addI_regL_regLNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "addI_regL_regL";}
#endif
};

class addL_reg_imm16Node : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return addL_reg_imm16_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_AddL; }
public:
  addL_reg_imm16Node() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(addL_reg_imm16Node); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "addL_reg_imm16";}
#endif
};

class addL_reg_immhi16Node : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return addL_reg_immhi16_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_AddL; }
public:
  addL_reg_immhi16Node() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(addL_reg_immhi16Node); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "addL_reg_immhi16";}
#endif
};

class addP_reg_regNode : public MachTypeNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return addP_reg_reg_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_AddP; }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  addP_reg_regNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(addP_reg_regNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "addP_reg_reg";}
#endif
};

class addP_reg_imm16Node : public MachTypeNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return addP_reg_imm16_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_AddP; }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  addP_reg_imm16Node() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(addP_reg_imm16Node); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "addP_reg_imm16";}
#endif
};

class addP_reg_immhi16Node : public MachTypeNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return addP_reg_immhi16_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_AddP; }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  addP_reg_immhi16Node() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(addP_reg_immhi16Node); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "addP_reg_immhi16";}
#endif
};

class subI_reg_regNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return subI_reg_reg_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_SubI; }
public:
  subI_reg_regNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(subI_reg_regNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "subI_reg_reg";}
#endif
};

class subI_imm16_regNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return subI_imm16_reg_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_SubI; }
public:
  subI_imm16_regNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(subI_imm16_regNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "subI_imm16_reg";}
#endif
};

class signmask32I_regINode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return signmask32I_regI_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
public:
  signmask32I_regINode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(signmask32I_regINode); }
  friend MachNode *State::MachNodeGenerator(int opcode);
  // Rematerialize signmask32I_regI
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "signmask32I_regI";}
#endif
};

class absI_reg_ExNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return absI_reg_Ex_rule; }
  virtual int            ideal_Opcode() const { return Op_AbsI; }
public:
  absI_reg_ExNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(absI_reg_ExNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  // Rematerialize absI_reg_Ex
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "absI_reg_Ex";}
#endif
};

class negI_regINode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return negI_regI_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_SubI; }
public:
  negI_regINode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(negI_regINode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "negI_regI";}
#endif
};

class subL_reg_regNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return subL_reg_reg_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_SubL; }
public:
  subL_reg_regNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(subL_reg_regNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "subL_reg_reg";}
#endif
};

class subI_regL_regLNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return subI_regL_regL_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_ConvL2I; }
public:
  subI_regL_regLNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(subI_regL_regLNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "subI_regL_regL";}
#endif
};

class signmask64I_regLNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return signmask64I_regL_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
public:
  signmask64I_regLNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(signmask64I_regLNode); }
  friend MachNode *State::MachNodeGenerator(int opcode);
  // Rematerialize signmask64I_regL
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "signmask64I_regL";}
#endif
};

class signmask64L_regLNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return signmask64L_regL_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
public:
  signmask64L_regLNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(signmask64L_regLNode); }
  friend MachNode *State::MachNodeGenerator(int opcode);
  // Rematerialize signmask64L_regL
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "signmask64L_regL";}
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return negL_reg_reg_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_SubL; }
public:
  negL_reg_regNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(negL_reg_regNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "negL_reg_reg";}
#endif
};

class negI_con0_regLNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return negI_con0_regL_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_ConvL2I; }
public:
  negI_con0_regLNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(negI_con0_regLNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "negI_con0_regL";}
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return mulI_reg_reg_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_MulI; }
public:
  mulI_reg_regNode() {  _num_opnds = 3; _opnds = _opnd_array; }
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return mulI_reg_imm16_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_MulI; }
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return mulL_reg_reg_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_MulL; }
public:
  mulL_reg_regNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(mulL_reg_regNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "mulL_reg_reg";}
#endif
};

class mulHighL_reg_regNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return mulHighL_reg_reg_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_MulHiL; }
public:
  mulHighL_reg_regNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(mulHighL_reg_regNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "mulHighL_reg_reg";}
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return mulL_reg_imm16_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_MulL; }
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

class divI_reg_immIvalueMinus1Node : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return divI_reg_immIvalueMinus1_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_DivI; }
public:
  divI_reg_immIvalueMinus1Node() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(divI_reg_immIvalueMinus1Node); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "divI_reg_immIvalueMinus1";}
#endif
};

class divI_reg_regnotMinus1Node : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return divI_reg_regnotMinus1_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_DivI; }
public:
  divI_reg_regnotMinus1Node() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(divI_reg_regnotMinus1Node); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "divI_reg_regnotMinus1";}
#endif
};

class cmovI_bne_negI_regNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return cmovI_bne_negI_reg_rule; }
  virtual int            ins_variable_size_depending_on_alignment() const { return true; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual uint           two_adr() const  { return oper_input_base(); }
public:
  cmovI_bne_negI_regNode() {  _num_opnds = 4; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(cmovI_bne_negI_regNode); }
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "cmovI_bne_negI_reg";}
#endif
};

class divI_reg_reg_ExNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return divI_reg_reg_Ex_rule; }
  virtual int            ideal_Opcode() const { return Op_DivI; }
public:
  divI_reg_reg_ExNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(divI_reg_reg_ExNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "divI_reg_reg_Ex";}
#endif
};

class divL_reg_immLvalueMinus1Node : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return divL_reg_immLvalueMinus1_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_DivL; }
public:
  divL_reg_immLvalueMinus1Node() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(divL_reg_immLvalueMinus1Node); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "divL_reg_immLvalueMinus1";}
#endif
};

class divL_reg_regnotMinus1Node : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return divL_reg_regnotMinus1_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_DivL; }
public:
  divL_reg_regnotMinus1Node() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(divL_reg_regnotMinus1Node); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "divL_reg_regnotMinus1";}
#endif
};

class cmovL_bne_negL_regNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return cmovL_bne_negL_reg_rule; }
  virtual int            ins_variable_size_depending_on_alignment() const { return true; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual uint           two_adr() const  { return oper_input_base(); }
public:
  cmovL_bne_negL_regNode() {  _num_opnds = 4; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(cmovL_bne_negL_regNode); }
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "cmovL_bne_negL_reg";}
#endif
};

class divL_reg_reg_ExNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return divL_reg_reg_Ex_rule; }
  virtual int            ideal_Opcode() const { return Op_DivL; }
public:
  divL_reg_reg_ExNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(divL_reg_reg_ExNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "divL_reg_reg_Ex";}
#endif
};

class modI_reg_reg_ExNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return modI_reg_reg_Ex_rule; }
  virtual int            ideal_Opcode() const { return Op_ModI; }
public:
  modI_reg_reg_ExNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(modI_reg_reg_ExNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "modI_reg_reg_Ex";}
#endif
};

class modL_reg_reg_ExNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return modL_reg_reg_Ex_rule; }
  virtual int            ideal_Opcode() const { return Op_ModL; }
public:
  modL_reg_reg_ExNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(modL_reg_reg_ExNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "modL_reg_reg_Ex";}
#endif
};

class maskI_reg_immNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return maskI_reg_imm_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
public:
  maskI_reg_immNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(maskI_reg_immNode); }
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "maskI_reg_imm";}
#endif
};

class lShiftI_reg_regNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return lShiftI_reg_reg_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
public:
  lShiftI_reg_regNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(lShiftI_reg_regNode); }
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "lShiftI_reg_reg";}
#endif
};

class lShiftI_reg_reg_ExNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return lShiftI_reg_reg_Ex_rule; }
  virtual int            ideal_Opcode() const { return Op_LShiftI; }
public:
  lShiftI_reg_reg_ExNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(lShiftI_reg_reg_ExNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "lShiftI_reg_reg_Ex";}
#endif
};

class lShiftI_reg_immNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return lShiftI_reg_imm_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_LShiftI; }
public:
  lShiftI_reg_immNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(lShiftI_reg_immNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "lShiftI_reg_imm";}
#endif
};

class lShiftI_andI_immInegpow2_imm5Node : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return lShiftI_andI_immInegpow2_imm5_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_LShiftI; }
public:
  lShiftI_andI_immInegpow2_imm5Node() {  _num_opnds = 4; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(lShiftI_andI_immInegpow2_imm5Node); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "lShiftI_andI_immInegpow2_imm5";}
#endif
};

class lShiftI_andI_immInegpow2_rShiftI_imm5Node : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return lShiftI_andI_immInegpow2_rShiftI_imm5_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_LShiftI; }
public:
  lShiftI_andI_immInegpow2_rShiftI_imm5Node() {  _num_opnds = 5; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(lShiftI_andI_immInegpow2_rShiftI_imm5Node); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "lShiftI_andI_immInegpow2_rShiftI_imm5";}
#endif
};

class lShiftL_regL_regINode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return lShiftL_regL_regI_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
public:
  lShiftL_regL_regINode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(lShiftL_regL_regINode); }
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "lShiftL_regL_regI";}
#endif
};

class lShiftL_regL_regI_ExNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return lShiftL_regL_regI_Ex_rule; }
  virtual int            ideal_Opcode() const { return Op_LShiftL; }
public:
  lShiftL_regL_regI_ExNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(lShiftL_regL_regI_ExNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "lShiftL_regL_regI_Ex";}
#endif
};

class lshiftL_regL_immINode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return lshiftL_regL_immI_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_LShiftL; }
public:
  lshiftL_regL_immINode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(lshiftL_regL_immINode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "lshiftL_regL_immI";}
#endif
};

class lShiftL_regI_immGE32Node : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return lShiftL_regI_immGE32_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_LShiftL; }
public:
  lShiftL_regI_immGE32Node() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(lShiftL_regI_immGE32Node); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "lShiftL_regI_immGE32";}
#endif
};

class scaledPositiveI2L_lShiftL_convI2L_reg_imm6Node : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return scaledPositiveI2L_lShiftL_convI2L_reg_imm6_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_LShiftL; }
public:
  scaledPositiveI2L_lShiftL_convI2L_reg_imm6Node() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(scaledPositiveI2L_lShiftL_convI2L_reg_imm6Node); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "scaledPositiveI2L_lShiftL_convI2L_reg_imm6";}
#endif
};

class arShiftI_reg_regNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return arShiftI_reg_reg_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
public:
  arShiftI_reg_regNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(arShiftI_reg_regNode); }
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "arShiftI_reg_reg";}
#endif
};

class arShiftI_reg_reg_ExNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return arShiftI_reg_reg_Ex_rule; }
  virtual int            ideal_Opcode() const { return Op_RShiftI; }
public:
  arShiftI_reg_reg_ExNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(arShiftI_reg_reg_ExNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "arShiftI_reg_reg_Ex";}
#endif
};

class arShiftI_reg_immNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return arShiftI_reg_imm_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_RShiftI; }
public:
  arShiftI_reg_immNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(arShiftI_reg_immNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "arShiftI_reg_imm";}
#endif
};

class arShiftL_regL_regINode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return arShiftL_regL_regI_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
public:
  arShiftL_regL_regINode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(arShiftL_regL_regINode); }
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "arShiftL_regL_regI";}
#endif
};

class arShiftL_regL_regI_ExNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return arShiftL_regL_regI_Ex_rule; }
  virtual int            ideal_Opcode() const { return Op_RShiftL; }
public:
  arShiftL_regL_regI_ExNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(arShiftL_regL_regI_ExNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "arShiftL_regL_regI_Ex";}
#endif
};

class arShiftL_regL_immINode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return arShiftL_regL_immI_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_RShiftL; }
public:
  arShiftL_regL_immINode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(arShiftL_regL_immINode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "arShiftL_regL_immI";}
#endif
};

class convL2I_arShiftL_regL_immINode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return convL2I_arShiftL_regL_immI_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_ConvL2I; }
public:
  convL2I_arShiftL_regL_immINode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(convL2I_arShiftL_regL_immINode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "convL2I_arShiftL_regL_immI";}
#endif
};

class urShiftI_reg_regNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return urShiftI_reg_reg_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
public:
  urShiftI_reg_regNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(urShiftI_reg_regNode); }
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "urShiftI_reg_reg";}
#endif
};

class urShiftI_reg_reg_ExNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return urShiftI_reg_reg_Ex_rule; }
  virtual int            ideal_Opcode() const { return Op_URShiftI; }
public:
  urShiftI_reg_reg_ExNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(urShiftI_reg_reg_ExNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "urShiftI_reg_reg_Ex";}
#endif
};

class urShiftI_reg_immNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return urShiftI_reg_imm_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_URShiftI; }
public:
  urShiftI_reg_immNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(urShiftI_reg_immNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "urShiftI_reg_imm";}
#endif
};

class urShiftL_regL_regINode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return urShiftL_regL_regI_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
public:
  urShiftL_regL_regINode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(urShiftL_regL_regINode); }
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "urShiftL_regL_regI";}
#endif
};

class urShiftL_regL_regI_ExNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return urShiftL_regL_regI_Ex_rule; }
  virtual int            ideal_Opcode() const { return Op_URShiftL; }
public:
  urShiftL_regL_regI_ExNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(urShiftL_regL_regI_ExNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "urShiftL_regL_regI_Ex";}
#endif
};

class urShiftL_regL_immINode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return urShiftL_regL_immI_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_URShiftL; }
public:
  urShiftL_regL_immINode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(urShiftL_regL_immINode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "urShiftL_regL_immI";}
#endif
};

class convL2I_urShiftL_regL_immINode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return convL2I_urShiftL_regL_immI_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_ConvL2I; }
public:
  convL2I_urShiftL_regL_immINode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(convL2I_urShiftL_regL_immINode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "convL2I_urShiftL_regL_immI";}
#endif
};

class shrP_convP2X_reg_imm6Node : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return shrP_convP2X_reg_imm6_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_URShiftL; }
  virtual int            reloc() const;
public:
  shrP_convP2X_reg_imm6Node() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(shrP_convP2X_reg_imm6Node); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "shrP_convP2X_reg_imm6";}
#endif
};

class andI_urShiftI_regI_immI_immIpow2minus1Node : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return andI_urShiftI_regI_immI_immIpow2minus1_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_AndI; }
public:
  andI_urShiftI_regI_immI_immIpow2minus1Node() {  _num_opnds = 4; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(andI_urShiftI_regI_immI_immIpow2minus1Node); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "andI_urShiftI_regI_immI_immIpow2minus1";}
#endif
};

class andL_urShiftL_regL_immI_immLpow2minus1Node : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return andL_urShiftL_regL_immI_immLpow2minus1_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_AndL; }
public:
  andL_urShiftL_regL_immI_immLpow2minus1Node() {  _num_opnds = 4; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(andL_urShiftL_regL_immI_immLpow2minus1Node); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "andL_urShiftL_regL_immI_immLpow2minus1";}
#endif
};

class sxtI_regNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return sxtI_reg_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_ConvL2I; }
public:
  sxtI_regNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(sxtI_regNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "sxtI_reg";}
#endif
};

class rotlI_reg_immi8Node : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return rotlI_reg_immi8_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_OrI; }
public:
  rotlI_reg_immi8Node() {  _num_opnds = 5; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(rotlI_reg_immi8Node); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "rotlI_reg_immi8";}
#endif
};

class rotlI_reg_immi8_0Node : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return rotlI_reg_immi8_0_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_OrI; }
public:
  rotlI_reg_immi8_0Node() {  _num_opnds = 5; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(rotlI_reg_immi8_0Node); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "rotlI_reg_immi8_0";}
#endif
};

class rotrI_reg_immi8Node : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return rotrI_reg_immi8_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_OrI; }
public:
  rotrI_reg_immi8Node() {  _num_opnds = 5; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(rotrI_reg_immi8Node); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "rotrI_reg_immi8";}
#endif
};

class rotrI_reg_immi8_0Node : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return rotrI_reg_immi8_0_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_OrI; }
public:
  rotrI_reg_immi8_0Node() {  _num_opnds = 5; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(rotrI_reg_immi8_0Node); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "rotrI_reg_immi8_0";}
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return addF_reg_reg_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_AddF; }
public:
  addF_reg_regNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(addF_reg_regNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "addF_reg_reg";}
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return addD_reg_reg_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_AddD; }
public:
  addD_reg_regNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(addD_reg_regNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "addD_reg_reg";}
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return subF_reg_reg_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_SubF; }
public:
  subF_reg_regNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(subF_reg_regNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "subF_reg_reg";}
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return subD_reg_reg_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_SubD; }
public:
  subD_reg_regNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(subD_reg_regNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "subD_reg_reg";}
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return mulF_reg_reg_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_MulF; }
public:
  mulF_reg_regNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(mulF_reg_regNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "mulF_reg_reg";}
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return mulD_reg_reg_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_MulD; }
public:
  mulD_reg_regNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(mulD_reg_regNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "mulD_reg_reg";}
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return divF_reg_reg_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_DivF; }
public:
  divF_reg_regNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(divF_reg_regNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "divF_reg_reg";}
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return divD_reg_reg_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_DivD; }
public:
  divD_reg_regNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(divD_reg_regNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "divD_reg_reg";}
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return absF_reg_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_AbsF; }
public:
  absF_regNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(absF_regNode); }
  // Rematerialize absF_reg
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return absD_reg_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_AbsD; }
public:
  absD_regNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(absD_regNode); }
  // Rematerialize absD_reg
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "absD_reg";}
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return negF_reg_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_NegF; }
public:
  negF_regNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(negF_regNode); }
  // Rematerialize negF_reg
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return negD_reg_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_NegD; }
public:
  negD_regNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(negD_regNode); }
  // Rematerialize negD_reg
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "negD_reg";}
#endif
};

class negF_absF_regNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return negF_absF_reg_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_NegF; }
public:
  negF_absF_regNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(negF_absF_regNode); }
  // Rematerialize negF_absF_reg
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "negF_absF_reg";}
#endif
};

class negD_absD_regNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return negD_absD_reg_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_NegD; }
public:
  negD_absD_regNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(negD_absD_regNode); }
  // Rematerialize negD_absD_reg
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "negD_absD_reg";}
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return sqrtD_reg_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_SqrtD; }
public:
  sqrtD_regNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(sqrtD_regNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "sqrtD_reg";}
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return sqrtF_reg_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_ConvD2F; }
public:
  sqrtF_regNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(sqrtF_regNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "sqrtF_reg";}
#endif
};

class roundDouble_nopNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return roundDouble_nop_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_RoundDouble; }
  virtual uint           two_adr() const  { return oper_input_base(); }
public:
  roundDouble_nopNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(roundDouble_nopNode); }
  // Rematerialize roundDouble_nop
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "roundDouble_nop";}
#endif
};

class roundFloat_nopNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return roundFloat_nop_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_RoundFloat; }
  virtual uint           two_adr() const  { return oper_input_base(); }
public:
  roundFloat_nopNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(roundFloat_nopNode); }
  // Rematerialize roundFloat_nop
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "roundFloat_nop";}
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return maddF_reg_reg_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_FmaF; }
public:
  maddF_reg_regNode() {  _num_opnds = 4; _opnds = _opnd_array; }
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return maddD_reg_reg_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_FmaD; }
public:
  maddD_reg_regNode() {  _num_opnds = 4; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(maddD_reg_regNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "maddD_reg_reg";}
#endif
};

class mnsubF_reg_regNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return mnsubF_reg_reg_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_FmaF; }
public:
  mnsubF_reg_regNode() {  _num_opnds = 4; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(mnsubF_reg_regNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "mnsubF_reg_reg";}
#endif
};

class mnsubF_reg_reg_0Node : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return mnsubF_reg_reg_0_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_FmaF; }
public:
  mnsubF_reg_reg_0Node() {  _num_opnds = 4; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(mnsubF_reg_reg_0Node); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "mnsubF_reg_reg_0";}
#endif
};

class mnsubD_reg_regNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return mnsubD_reg_reg_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_FmaD; }
public:
  mnsubD_reg_regNode() {  _num_opnds = 4; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(mnsubD_reg_regNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "mnsubD_reg_reg";}
#endif
};

class mnsubD_reg_reg_0Node : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return mnsubD_reg_reg_0_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_FmaD; }
public:
  mnsubD_reg_reg_0Node() {  _num_opnds = 4; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(mnsubD_reg_reg_0Node); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "mnsubD_reg_reg_0";}
#endif
};

class mnaddF_reg_regNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return mnaddF_reg_reg_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_FmaF; }
public:
  mnaddF_reg_regNode() {  _num_opnds = 4; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(mnaddF_reg_regNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "mnaddF_reg_reg";}
#endif
};

class mnaddF_reg_reg_0Node : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return mnaddF_reg_reg_0_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_FmaF; }
public:
  mnaddF_reg_reg_0Node() {  _num_opnds = 4; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(mnaddF_reg_reg_0Node); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "mnaddF_reg_reg_0";}
#endif
};

class mnaddD_reg_regNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return mnaddD_reg_reg_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_FmaD; }
public:
  mnaddD_reg_regNode() {  _num_opnds = 4; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(mnaddD_reg_regNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "mnaddD_reg_reg";}
#endif
};

class mnaddD_reg_reg_0Node : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return mnaddD_reg_reg_0_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_FmaD; }
public:
  mnaddD_reg_reg_0Node() {  _num_opnds = 4; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(mnaddD_reg_reg_0Node); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "mnaddD_reg_reg_0";}
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return msubF_reg_reg_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_FmaF; }
public:
  msubF_reg_regNode() {  _num_opnds = 4; _opnds = _opnd_array; }
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return msubD_reg_reg_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_FmaD; }
public:
  msubD_reg_regNode() {  _num_opnds = 4; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(msubD_reg_regNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "msubD_reg_reg";}
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return andI_reg_reg_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_AndI; }
public:
  andI_reg_regNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(andI_reg_regNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "andI_reg_reg";}
#endif
};

class andI_reg_immIhi16Node : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return andI_reg_immIhi16_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_AndI; }
public:
  andI_reg_immIhi16Node() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(andI_reg_immIhi16Node); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "andI_reg_immIhi16";}
#endif
};

class andI_reg_uimm16Node : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return andI_reg_uimm16_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_AndI; }
public:
  andI_reg_uimm16Node() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(andI_reg_uimm16Node); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "andI_reg_uimm16";}
#endif
};

class andI_reg_immInegpow2Node : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return andI_reg_immInegpow2_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_AndI; }
public:
  andI_reg_immInegpow2Node() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(andI_reg_immInegpow2Node); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "andI_reg_immInegpow2";}
#endif
};

class andI_reg_immIpow2minus1Node : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return andI_reg_immIpow2minus1_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_AndI; }
public:
  andI_reg_immIpow2minus1Node() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(andI_reg_immIpow2minus1Node); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "andI_reg_immIpow2minus1";}
#endif
};

class andI_reg_immIpowerOf2Node : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return andI_reg_immIpowerOf2_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_AndI; }
public:
  andI_reg_immIpowerOf2Node() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(andI_reg_immIpowerOf2Node); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "andI_reg_immIpowerOf2";}
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return andL_reg_reg_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_AndL; }
public:
  andL_reg_regNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(andL_reg_regNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "andL_reg_reg";}
#endif
};

class andL_reg_uimm16Node : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return andL_reg_uimm16_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_AndL; }
public:
  andL_reg_uimm16Node() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(andL_reg_uimm16Node); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "andL_reg_uimm16";}
#endif
};

class andL_reg_immLnegpow2Node : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return andL_reg_immLnegpow2_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_AndL; }
public:
  andL_reg_immLnegpow2Node() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(andL_reg_immLnegpow2Node); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "andL_reg_immLnegpow2";}
#endif
};

class andL_reg_immLpow2minus1Node : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return andL_reg_immLpow2minus1_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_AndL; }
public:
  andL_reg_immLpow2minus1Node() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(andL_reg_immLpow2minus1Node); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "andL_reg_immLpow2minus1";}
#endif
};

class convL2I_andL_reg_immLpow2minus1Node : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return convL2I_andL_reg_immLpow2minus1_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_ConvL2I; }
public:
  convL2I_andL_reg_immLpow2minus1Node() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(convL2I_andL_reg_immLpow2minus1Node); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "convL2I_andL_reg_immLpow2minus1";}
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return orI_reg_reg_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_OrI; }
public:
  orI_reg_regNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(orI_reg_regNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "orI_reg_reg";}
#endif
};

class orI_reg_reg_2Node : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return orI_reg_reg_2_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
public:
  orI_reg_reg_2Node() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(orI_reg_reg_2Node); }
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "orI_reg_reg_2";}
#endif
};

class tree_orI_orI_orI_reg_reg_ExNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return tree_orI_orI_orI_reg_reg_Ex_rule; }
  virtual int            ideal_Opcode() const { return Op_OrI; }
public:
  tree_orI_orI_orI_reg_reg_ExNode() {  _num_opnds = 5; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(tree_orI_orI_orI_reg_reg_ExNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "tree_orI_orI_orI_reg_reg_Ex";}
#endif
};

class tree_orI_orI_orI_reg_reg_Ex_1Node : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return tree_orI_orI_orI_reg_reg_Ex_1_rule; }
  virtual int            ideal_Opcode() const { return Op_OrI; }
public:
  tree_orI_orI_orI_reg_reg_Ex_1Node() {  _num_opnds = 5; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(tree_orI_orI_orI_reg_reg_Ex_1Node); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "tree_orI_orI_orI_reg_reg_Ex_1";}
#endif
};

class tree_orI_orI_orI_reg_reg_Ex_0Node : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return tree_orI_orI_orI_reg_reg_Ex_0_rule; }
  virtual int            ideal_Opcode() const { return Op_OrI; }
public:
  tree_orI_orI_orI_reg_reg_Ex_0Node() {  _num_opnds = 5; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(tree_orI_orI_orI_reg_reg_Ex_0Node); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "tree_orI_orI_orI_reg_reg_Ex_0";}
#endif
};

class tree_orI_orI_orI_reg_reg_Ex_2Node : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return tree_orI_orI_orI_reg_reg_Ex_2_rule; }
  virtual int            ideal_Opcode() const { return Op_OrI; }
public:
  tree_orI_orI_orI_reg_reg_Ex_2Node() {  _num_opnds = 5; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(tree_orI_orI_orI_reg_reg_Ex_2Node); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "tree_orI_orI_orI_reg_reg_Ex_2";}
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return orI_reg_uimm16_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_OrI; }
public:
  orI_reg_uimm16Node() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(orI_reg_uimm16Node); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "orI_reg_uimm16";}
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return orL_reg_reg_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_OrL; }
public:
  orL_reg_regNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(orL_reg_regNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "orL_reg_reg";}
#endif
};

class orI_regL_regLNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return orI_regL_regL_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_ConvL2I; }
public:
  orI_regL_regLNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(orI_regL_regLNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "orI_regL_regL";}
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return orL_reg_uimm16_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_OrL; }
public:
  orL_reg_uimm16Node() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(orL_reg_uimm16Node); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "orL_reg_uimm16";}
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return xorI_reg_reg_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_XorI; }
public:
  xorI_reg_regNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(xorI_reg_regNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "xorI_reg_reg";}
#endif
};

class xorI_reg_reg_2Node : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return xorI_reg_reg_2_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
public:
  xorI_reg_reg_2Node() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(xorI_reg_reg_2Node); }
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "xorI_reg_reg_2";}
#endif
};

class tree_xorI_xorI_xorI_reg_reg_ExNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return tree_xorI_xorI_xorI_reg_reg_Ex_rule; }
  virtual int            ideal_Opcode() const { return Op_XorI; }
public:
  tree_xorI_xorI_xorI_reg_reg_ExNode() {  _num_opnds = 5; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(tree_xorI_xorI_xorI_reg_reg_ExNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "tree_xorI_xorI_xorI_reg_reg_Ex";}
#endif
};

class tree_xorI_xorI_xorI_reg_reg_Ex_1Node : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return tree_xorI_xorI_xorI_reg_reg_Ex_1_rule; }
  virtual int            ideal_Opcode() const { return Op_XorI; }
public:
  tree_xorI_xorI_xorI_reg_reg_Ex_1Node() {  _num_opnds = 5; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(tree_xorI_xorI_xorI_reg_reg_Ex_1Node); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "tree_xorI_xorI_xorI_reg_reg_Ex_1";}
#endif
};

class tree_xorI_xorI_xorI_reg_reg_Ex_0Node : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return tree_xorI_xorI_xorI_reg_reg_Ex_0_rule; }
  virtual int            ideal_Opcode() const { return Op_XorI; }
public:
  tree_xorI_xorI_xorI_reg_reg_Ex_0Node() {  _num_opnds = 5; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(tree_xorI_xorI_xorI_reg_reg_Ex_0Node); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "tree_xorI_xorI_xorI_reg_reg_Ex_0";}
#endif
};

class tree_xorI_xorI_xorI_reg_reg_Ex_2Node : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return tree_xorI_xorI_xorI_reg_reg_Ex_2_rule; }
  virtual int            ideal_Opcode() const { return Op_XorI; }
public:
  tree_xorI_xorI_xorI_reg_reg_Ex_2Node() {  _num_opnds = 5; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(tree_xorI_xorI_xorI_reg_reg_Ex_2Node); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "tree_xorI_xorI_xorI_reg_reg_Ex_2";}
#endif
};

class xorI_reg_uimm16Node : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return xorI_reg_uimm16_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_XorI; }
public:
  xorI_reg_uimm16Node() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(xorI_reg_uimm16Node); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "xorI_reg_uimm16";}
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return xorL_reg_reg_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_XorL; }
public:
  xorL_reg_regNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(xorL_reg_regNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "xorL_reg_reg";}
#endif
};

class xorI_regL_regLNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return xorI_regL_regL_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_ConvL2I; }
public:
  xorI_regL_regLNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(xorI_regL_regLNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "xorI_regL_regL";}
#endif
};

class xorL_reg_uimm16Node : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return xorL_reg_uimm16_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_XorL; }
public:
  xorL_reg_uimm16Node() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(xorL_reg_uimm16Node); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "xorL_reg_uimm16";}
#endif
};

class notI_regNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return notI_reg_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_XorI; }
public:
  notI_regNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(notI_regNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "notI_reg";}
#endif
};

class notL_regNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return notL_reg_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_XorL; }
public:
  notL_regNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(notL_regNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "notL_reg";}
#endif
};

class andcI_reg_regNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return andcI_reg_reg_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_AndI; }
public:
  andcI_reg_regNode() {  _num_opnds = 4; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(andcI_reg_regNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "andcI_reg_reg";}
#endif
};

class andcI_reg_reg_0Node : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return andcI_reg_reg_0_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_AndI; }
public:
  andcI_reg_reg_0Node() {  _num_opnds = 4; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(andcI_reg_reg_0Node); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "andcI_reg_reg_0";}
#endif
};

class andcL_reg_regNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return andcL_reg_reg_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
public:
  andcL_reg_regNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(andcL_reg_regNode); }
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "andcL_reg_reg";}
#endif
};

class moveL2D_regNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return moveL2D_reg_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_MoveL2D; }
public:
  moveL2D_regNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(moveL2D_regNode); }
  // Rematerialize moveL2D_reg
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "moveL2D_reg";}
#endif
};

class moveI2D_regNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return moveI2D_reg_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
public:
  moveI2D_regNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(moveI2D_regNode); }
  friend MachNode *State::MachNodeGenerator(int opcode);
  // Rematerialize moveI2D_reg
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "moveI2D_reg";}
#endif
};

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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return stkI_to_regI_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return regI_to_stkI_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return stkL_to_regL_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return regL_to_stkL_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
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

class moveF2I_stack_regNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return moveF2I_stack_reg_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_MoveF2I; }
public:
  moveF2I_stack_regNode() {  _num_opnds = 2; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(moveF2I_stack_regNode); }
  // Rematerialize moveF2I_stack_reg
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "moveF2I_stack_reg";}
#endif
};

class moveF2I_reg_stackNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return moveF2I_reg_stack_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_MoveF2I; }
public:
  moveF2I_reg_stackNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(moveF2I_reg_stackNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "moveF2I_reg_stack";}
#endif
};

class moveI2F_stack_regNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return moveI2F_stack_reg_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_MoveI2F; }
public:
  moveI2F_stack_regNode() {  _num_opnds = 2; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(moveI2F_stack_regNode); }
  // Rematerialize moveI2F_stack_reg
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "moveI2F_stack_reg";}
#endif
};

class moveI2F_reg_stackNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return moveI2F_reg_stack_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_MoveI2F; }
public:
  moveI2F_reg_stackNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(moveI2F_reg_stackNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "moveI2F_reg_stack";}
#endif
};

class moveF2L_reg_stackNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return moveF2L_reg_stack_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
public:
  moveF2L_reg_stackNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(moveF2L_reg_stackNode); }
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "moveF2L_reg_stack";}
#endif
};

class moveD2L_stack_regNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return moveD2L_stack_reg_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_MoveD2L; }
public:
  moveD2L_stack_regNode() {  _num_opnds = 2; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(moveD2L_stack_regNode); }
  // Rematerialize moveD2L_stack_reg
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "moveD2L_stack_reg";}
#endif
};

class moveD2L_reg_stackNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return moveD2L_reg_stack_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_MoveD2L; }
public:
  moveD2L_reg_stackNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(moveD2L_reg_stackNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "moveD2L_reg_stack";}
#endif
};

class moveL2D_stack_regNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return moveL2D_stack_reg_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_MoveL2D; }
public:
  moveL2D_stack_regNode() {  _num_opnds = 2; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(moveL2D_stack_regNode); }
  // Rematerialize moveL2D_stack_reg
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "moveL2D_stack_reg";}
#endif
};

class moveL2D_reg_stackNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return moveL2D_reg_stack_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_MoveL2D; }
public:
  moveL2D_reg_stackNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(moveL2D_reg_stackNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "moveL2D_reg_stack";}
#endif
};

class moveRegNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return moveReg_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
public:
  moveRegNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(moveRegNode); }
  friend MachNode *State::MachNodeGenerator(int opcode);
  // Rematerialize moveReg
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "moveReg";}
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return castX2P_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return castP2X_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return castPP_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
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

class castIINode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return castII_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_CastII; }
  virtual uint           two_adr() const  { return oper_input_base(); }
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return checkCastPP_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
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

class convI2Bool_reg__cntlz_ExNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return convI2Bool_reg__cntlz_Ex_rule; }
  virtual int            ideal_Opcode() const { return Op_Conv2B; }
public:
  convI2Bool_reg__cntlz_ExNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(convI2Bool_reg__cntlz_ExNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  // Rematerialize convI2Bool_reg__cntlz_Ex
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "convI2Bool_reg__cntlz_Ex";}
#endif
};

class convI2Bool_reg__cmoveNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return convI2Bool_reg__cmove_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_Conv2B; }
public:
  convI2Bool_reg__cmoveNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(convI2Bool_reg__cmoveNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "convI2Bool_reg__cmove";}
#endif
};

class xorI_convI2Bool_reg_immIvalue1__cntlz_ExNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return xorI_convI2Bool_reg_immIvalue1__cntlz_Ex_rule; }
  virtual int            ideal_Opcode() const { return Op_XorI; }
public:
  xorI_convI2Bool_reg_immIvalue1__cntlz_ExNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(xorI_convI2Bool_reg_immIvalue1__cntlz_ExNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "xorI_convI2Bool_reg_immIvalue1__cntlz_Ex";}
#endif
};

class xorI_convI2Bool_reg_immIvalue1__cmoveNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return xorI_convI2Bool_reg_immIvalue1__cmove_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_XorI; }
public:
  xorI_convI2Bool_reg_immIvalue1__cmoveNode() {  _num_opnds = 4; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(xorI_convI2Bool_reg_immIvalue1__cmoveNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "xorI_convI2Bool_reg_immIvalue1__cmove";}
#endif
};

class convI2Bool_andI_reg_immIpowerOf2Node : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return convI2Bool_andI_reg_immIpowerOf2_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_Conv2B; }
public:
  convI2Bool_andI_reg_immIpowerOf2Node() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(convI2Bool_andI_reg_immIpowerOf2Node); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "convI2Bool_andI_reg_immIpowerOf2";}
#endif
};

class convP2Bool_reg__cntlz_ExNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return convP2Bool_reg__cntlz_Ex_rule; }
  virtual int            ideal_Opcode() const { return Op_Conv2B; }
  virtual int            reloc() const;
public:
  convP2Bool_reg__cntlz_ExNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(convP2Bool_reg__cntlz_ExNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  // Rematerialize convP2Bool_reg__cntlz_Ex
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "convP2Bool_reg__cntlz_Ex";}
#endif
};

class convP2Bool_reg__cmoveNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return convP2Bool_reg__cmove_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_Conv2B; }
  virtual int            reloc() const;
public:
  convP2Bool_reg__cmoveNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(convP2Bool_reg__cmoveNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "convP2Bool_reg__cmove";}
#endif
};

class xorI_convP2Bool_reg__cntlz_ExNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return xorI_convP2Bool_reg__cntlz_Ex_rule; }
  virtual int            ideal_Opcode() const { return Op_XorI; }
  virtual int            reloc() const;
public:
  xorI_convP2Bool_reg__cntlz_ExNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(xorI_convP2Bool_reg__cntlz_ExNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "xorI_convP2Bool_reg__cntlz_Ex";}
#endif
};

class xorI_convP2Bool_reg_immIvalue1__cmoveNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return xorI_convP2Bool_reg_immIvalue1__cmove_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_XorI; }
  virtual int            reloc() const;
public:
  xorI_convP2Bool_reg_immIvalue1__cmoveNode() {  _num_opnds = 4; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(xorI_convP2Bool_reg_immIvalue1__cmoveNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "xorI_convP2Bool_reg_immIvalue1__cmove";}
#endif
};

class cmpLTMask_reg_reg_ExNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return cmpLTMask_reg_reg_Ex_rule; }
  virtual int            ideal_Opcode() const { return Op_CmpLTMask; }
public:
  cmpLTMask_reg_reg_ExNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(cmpLTMask_reg_reg_ExNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "cmpLTMask_reg_reg_Ex";}
#endif
};

class cmpLTMask_reg_immI0Node : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return cmpLTMask_reg_immI0_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_CmpLTMask; }
public:
  cmpLTMask_reg_immI0Node() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(cmpLTMask_reg_immI0Node); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "cmpLTMask_reg_immI0";}
#endif
};

class convB2I_regNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return convB2I_reg_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_RShiftI; }
public:
  convB2I_regNode() {  _num_opnds = 4; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(convB2I_regNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "convB2I_reg";}
#endif
};

class extshNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return extsh_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
public:
  extshNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(extshNode); }
  friend MachNode *State::MachNodeGenerator(int opcode);
  // Rematerialize extsh
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "extsh";}
#endif
};

class convS2I_regNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return convS2I_reg_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_RShiftI; }
public:
  convS2I_regNode() {  _num_opnds = 4; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(convS2I_regNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "convS2I_reg";}
#endif
};

class sxtI_L2L_regNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return sxtI_L2L_reg_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_ConvI2L; }
public:
  sxtI_L2L_regNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(sxtI_L2L_regNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "sxtI_L2L_reg";}
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return convL2I_reg_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
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

class convD2IRaw_regDNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return convD2IRaw_regD_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
public:
  convD2IRaw_regDNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(convD2IRaw_regDNode); }
  friend MachNode *State::MachNodeGenerator(int opcode);
  // Rematerialize convD2IRaw_regD
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "convD2IRaw_regD";}
#endif
};

class cmovI_bso_stackSlotLNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return cmovI_bso_stackSlotL_rule; }
  virtual int            ins_variable_size_depending_on_alignment() const { return true; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
public:
  cmovI_bso_stackSlotLNode() {  _num_opnds = 3; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(cmovI_bso_stackSlotLNode); }
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "cmovI_bso_stackSlotL";}
#endif
};

class cmovI_bso_regNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return cmovI_bso_reg_rule; }
  virtual int            ins_variable_size_depending_on_alignment() const { return true; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
public:
  cmovI_bso_regNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(cmovI_bso_regNode); }
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "cmovI_bso_reg";}
#endif
};

class cmovI_bso_stackSlotL_conLvalue0_ExNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return cmovI_bso_stackSlotL_conLvalue0_Ex_rule; }
  virtual bool           requires_postalloc_expand() const { return true; }
  virtual void           postalloc_expand(GrowableArray <Node *> *nodes, PhaseRegAlloc *ra_);
public:
  cmovI_bso_stackSlotL_conLvalue0_ExNode() {  _num_opnds = 3; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(cmovI_bso_stackSlotL_conLvalue0_ExNode); }
  friend MachNode *State::MachNodeGenerator(int opcode);
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "cmovI_bso_stackSlotL_conLvalue0_Ex";}
#endif
};

class cmovI_bso_reg_conLvalue0_ExNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return cmovI_bso_reg_conLvalue0_Ex_rule; }
  virtual bool           requires_postalloc_expand() const { return true; }
  virtual void           postalloc_expand(GrowableArray <Node *> *nodes, PhaseRegAlloc *ra_);
public:
  cmovI_bso_reg_conLvalue0_ExNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(cmovI_bso_reg_conLvalue0_ExNode); }
  friend MachNode *State::MachNodeGenerator(int opcode);
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "cmovI_bso_reg_conLvalue0_Ex";}
#endif
};

class convD2I_reg_ExExNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return convD2I_reg_ExEx_rule; }
  virtual int            ideal_Opcode() const { return Op_ConvD2I; }
public:
  convD2I_reg_ExExNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(convD2I_reg_ExExNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "convD2I_reg_ExEx";}
#endif
};

class convD2I_reg_mffprd_ExExNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return convD2I_reg_mffprd_ExEx_rule; }
  virtual int            ideal_Opcode() const { return Op_ConvD2I; }
public:
  convD2I_reg_mffprd_ExExNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(convD2I_reg_mffprd_ExExNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "convD2I_reg_mffprd_ExEx";}
#endif
};

class convF2IRaw_regFNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return convF2IRaw_regF_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
public:
  convF2IRaw_regFNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(convF2IRaw_regFNode); }
  friend MachNode *State::MachNodeGenerator(int opcode);
  // Rematerialize convF2IRaw_regF
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "convF2IRaw_regF";}
#endif
};

class convF2I_regF_ExExNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return convF2I_regF_ExEx_rule; }
  virtual int            ideal_Opcode() const { return Op_ConvF2I; }
public:
  convF2I_regF_ExExNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(convF2I_regF_ExExNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "convF2I_regF_ExEx";}
#endif
};

class convF2I_regF_mffprd_ExExNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return convF2I_regF_mffprd_ExEx_rule; }
  virtual int            ideal_Opcode() const { return Op_ConvF2I; }
public:
  convF2I_regF_mffprd_ExExNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(convF2I_regF_mffprd_ExExNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "convF2I_regF_mffprd_ExEx";}
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return convI2L_reg_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_ConvI2L; }
public:
  convI2L_regNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(convI2L_regNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "convI2L_reg";}
#endif
};

class zeroExtendL_regINode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return zeroExtendL_regI_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_AndL; }
public:
  zeroExtendL_regINode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(zeroExtendL_regINode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "zeroExtendL_regI";}
#endif
};

class zeroExtendL_regLNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return zeroExtendL_regL_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_AndL; }
public:
  zeroExtendL_regLNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(zeroExtendL_regLNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "zeroExtendL_regL";}
#endif
};

class convF2LRaw_regFNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return convF2LRaw_regF_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
public:
  convF2LRaw_regFNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(convF2LRaw_regFNode); }
  friend MachNode *State::MachNodeGenerator(int opcode);
  // Rematerialize convF2LRaw_regF
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "convF2LRaw_regF";}
#endif
};

class cmovL_bso_stackSlotLNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return cmovL_bso_stackSlotL_rule; }
  virtual int            ins_variable_size_depending_on_alignment() const { return true; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
public:
  cmovL_bso_stackSlotLNode() {  _num_opnds = 3; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(cmovL_bso_stackSlotLNode); }
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "cmovL_bso_stackSlotL";}
#endif
};

class cmovL_bso_regNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return cmovL_bso_reg_rule; }
  virtual int            ins_variable_size_depending_on_alignment() const { return true; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
public:
  cmovL_bso_regNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(cmovL_bso_regNode); }
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "cmovL_bso_reg";}
#endif
};

class cmovL_bso_stackSlotL_conLvalue0_ExNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return cmovL_bso_stackSlotL_conLvalue0_Ex_rule; }
  virtual bool           requires_postalloc_expand() const { return true; }
  virtual void           postalloc_expand(GrowableArray <Node *> *nodes, PhaseRegAlloc *ra_);
public:
  cmovL_bso_stackSlotL_conLvalue0_ExNode() {  _num_opnds = 3; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(cmovL_bso_stackSlotL_conLvalue0_ExNode); }
  friend MachNode *State::MachNodeGenerator(int opcode);
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "cmovL_bso_stackSlotL_conLvalue0_Ex";}
#endif
};

class cmovL_bso_reg_conLvalue0_ExNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return cmovL_bso_reg_conLvalue0_Ex_rule; }
  virtual bool           requires_postalloc_expand() const { return true; }
  virtual void           postalloc_expand(GrowableArray <Node *> *nodes, PhaseRegAlloc *ra_);
public:
  cmovL_bso_reg_conLvalue0_ExNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(cmovL_bso_reg_conLvalue0_ExNode); }
  friend MachNode *State::MachNodeGenerator(int opcode);
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "cmovL_bso_reg_conLvalue0_Ex";}
#endif
};

class convF2L_reg_ExExNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return convF2L_reg_ExEx_rule; }
  virtual int            ideal_Opcode() const { return Op_ConvF2L; }
public:
  convF2L_reg_ExExNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(convF2L_reg_ExExNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "convF2L_reg_ExEx";}
#endif
};

class convF2L_reg_mffprd_ExExNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return convF2L_reg_mffprd_ExEx_rule; }
  virtual int            ideal_Opcode() const { return Op_ConvF2L; }
public:
  convF2L_reg_mffprd_ExExNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(convF2L_reg_mffprd_ExExNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "convF2L_reg_mffprd_ExEx";}
#endif
};

class convD2LRaw_regDNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return convD2LRaw_regD_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
public:
  convD2LRaw_regDNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(convD2LRaw_regDNode); }
  friend MachNode *State::MachNodeGenerator(int opcode);
  // Rematerialize convD2LRaw_regD
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "convD2LRaw_regD";}
#endif
};

class convD2L_reg_ExExNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return convD2L_reg_ExEx_rule; }
  virtual int            ideal_Opcode() const { return Op_ConvD2L; }
public:
  convD2L_reg_ExExNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(convD2L_reg_ExExNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "convD2L_reg_ExEx";}
#endif
};

class convD2L_reg_mffprd_ExExNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return convD2L_reg_mffprd_ExEx_rule; }
  virtual int            ideal_Opcode() const { return Op_ConvD2L; }
public:
  convD2L_reg_mffprd_ExExNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(convD2L_reg_mffprd_ExExNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "convD2L_reg_mffprd_ExEx";}
#endif
};

class convL2DRaw_regDNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return convL2DRaw_regD_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
public:
  convL2DRaw_regDNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(convL2DRaw_regDNode); }
  friend MachNode *State::MachNodeGenerator(int opcode);
  // Rematerialize convL2DRaw_regD
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "convL2DRaw_regD";}
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return convD2F_reg_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
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

class convI2F_ireg_ExNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return convI2F_ireg_Ex_rule; }
  virtual int            ideal_Opcode() const { return Op_ConvI2F; }
public:
  convI2F_ireg_ExNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(convI2F_ireg_ExNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "convI2F_ireg_Ex";}
#endif
};

class convL2FRaw_regFNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return convL2FRaw_regF_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
public:
  convL2FRaw_regFNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(convL2FRaw_regFNode); }
  friend MachNode *State::MachNodeGenerator(int opcode);
  // Rematerialize convL2FRaw_regF
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "convL2FRaw_regF";}
#endif
};

class convI2F_ireg_fcfids_ExNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return convI2F_ireg_fcfids_Ex_rule; }
  virtual int            ideal_Opcode() const { return Op_ConvI2F; }
public:
  convI2F_ireg_fcfids_ExNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(convI2F_ireg_fcfids_ExNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "convI2F_ireg_fcfids_Ex";}
#endif
};

class convI2F_ireg_mtfprd_ExNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return convI2F_ireg_mtfprd_Ex_rule; }
  virtual int            ideal_Opcode() const { return Op_ConvI2F; }
public:
  convI2F_ireg_mtfprd_ExNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(convI2F_ireg_mtfprd_ExNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "convI2F_ireg_mtfprd_Ex";}
#endif
};

class convL2F_ireg_fcfids_ExNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return convL2F_ireg_fcfids_Ex_rule; }
  virtual int            ideal_Opcode() const { return Op_ConvL2F; }
public:
  convL2F_ireg_fcfids_ExNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(convL2F_ireg_fcfids_ExNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "convL2F_ireg_fcfids_Ex";}
#endif
};

class convL2F_ireg_mtfprd_ExNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return convL2F_ireg_mtfprd_Ex_rule; }
  virtual int            ideal_Opcode() const { return Op_ConvL2F; }
public:
  convL2F_ireg_mtfprd_ExNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(convL2F_ireg_mtfprd_ExNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "convL2F_ireg_mtfprd_Ex";}
#endif
};

class convI2D_reg_ExNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return convI2D_reg_Ex_rule; }
  virtual int            ideal_Opcode() const { return Op_ConvI2D; }
public:
  convI2D_reg_ExNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(convI2D_reg_ExNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "convI2D_reg_Ex";}
#endif
};

class convI2D_reg_mtfprd_ExNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return convI2D_reg_mtfprd_Ex_rule; }
  virtual int            ideal_Opcode() const { return Op_ConvI2D; }
public:
  convI2D_reg_mtfprd_ExNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(convI2D_reg_mtfprd_ExNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "convI2D_reg_mtfprd_Ex";}
#endif
};

class convL2D_reg_ExNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return convL2D_reg_Ex_rule; }
  virtual int            ideal_Opcode() const { return Op_ConvL2D; }
public:
  convL2D_reg_ExNode() {  _num_opnds = 2; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(convL2D_reg_ExNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "convL2D_reg_Ex";}
#endif
};

class convL2D_reg_mtfprd_ExNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return convL2D_reg_mtfprd_Ex_rule; }
  virtual int            ideal_Opcode() const { return Op_ConvL2D; }
public:
  convL2D_reg_mtfprd_ExNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(convL2D_reg_mtfprd_ExNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "convL2D_reg_mtfprd_Ex";}
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return convF2D_reg_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_ConvF2D; }
public:
  convF2D_regNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(convF2D_regNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "convF2D_reg";}
#endif
};

class cmpI_reg_regNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return cmpI_reg_reg_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_CmpI; }
public:
  cmpI_reg_regNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(cmpI_reg_regNode); }
  // Rematerialize cmpI_reg_reg
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "cmpI_reg_reg";}
#endif
};

class cmpI_reg_imm16Node : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return cmpI_reg_imm16_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_CmpI; }
public:
  cmpI_reg_imm16Node() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(cmpI_reg_imm16Node); }
  // Rematerialize cmpI_reg_imm16
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "cmpI_reg_imm16";}
#endif
};

class testI_reg_immNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return testI_reg_imm_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_CmpI; }
public:
  testI_reg_immNode() {  _num_opnds = 4; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(testI_reg_immNode); }
  // Rematerialize testI_reg_imm
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "testI_reg_imm";}
#endif
};

class cmpL_reg_regNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return cmpL_reg_reg_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_CmpL; }
public:
  cmpL_reg_regNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(cmpL_reg_regNode); }
  // Rematerialize cmpL_reg_reg
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "cmpL_reg_reg";}
#endif
};

class cmpL_reg_imm16Node : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return cmpL_reg_imm16_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_CmpL; }
public:
  cmpL_reg_imm16Node() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(cmpL_reg_imm16Node); }
  // Rematerialize cmpL_reg_imm16
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "cmpL_reg_imm16";}
#endif
};

class cmpUL_reg_regNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return cmpUL_reg_reg_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_CmpUL; }
public:
  cmpUL_reg_regNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(cmpUL_reg_regNode); }
  // Rematerialize cmpUL_reg_reg
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "cmpUL_reg_reg";}
#endif
};

class cmpUL_reg_imm16Node : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return cmpUL_reg_imm16_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_CmpUL; }
public:
  cmpUL_reg_imm16Node() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(cmpUL_reg_imm16Node); }
  // Rematerialize cmpUL_reg_imm16
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "cmpUL_reg_imm16";}
#endif
};

class testL_reg_regNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return testL_reg_reg_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_CmpL; }
public:
  testL_reg_regNode() {  _num_opnds = 4; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(testL_reg_regNode); }
  // Rematerialize testL_reg_reg
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "testL_reg_reg";}
#endif
};

class testL_reg_immNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return testL_reg_imm_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_CmpL; }
public:
  testL_reg_immNode() {  _num_opnds = 4; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(testL_reg_immNode); }
  // Rematerialize testL_reg_imm
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "testL_reg_imm";}
#endif
};

class cmovI_conIvalueMinus1_conIvalue1Node : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return cmovI_conIvalueMinus1_conIvalue1_rule; }
  virtual int            ins_variable_size_depending_on_alignment() const { return true; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
public:
  cmovI_conIvalueMinus1_conIvalue1Node() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(cmovI_conIvalueMinus1_conIvalue1Node); }
  friend MachNode *State::MachNodeGenerator(int opcode);
  // Rematerialize cmovI_conIvalueMinus1_conIvalue1
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "cmovI_conIvalueMinus1_conIvalue1";}
#endif
};

class cmovI_conIvalueMinus1_conIvalue0_conIvalue1_ExNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return cmovI_conIvalueMinus1_conIvalue0_conIvalue1_Ex_rule; }
  virtual bool           requires_postalloc_expand() const { return true; }
  virtual void           postalloc_expand(GrowableArray <Node *> *nodes, PhaseRegAlloc *ra_);
public:
  cmovI_conIvalueMinus1_conIvalue0_conIvalue1_ExNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(cmovI_conIvalueMinus1_conIvalue0_conIvalue1_ExNode); }
  friend MachNode *State::MachNodeGenerator(int opcode);
  // Rematerialize cmovI_conIvalueMinus1_conIvalue0_conIvalue1_Ex
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "cmovI_conIvalueMinus1_conIvalue0_conIvalue1_Ex";}
#endif
};

class cmpL3_reg_reg_ExExNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return cmpL3_reg_reg_ExEx_rule; }
  virtual int            ideal_Opcode() const { return Op_CmpL3; }
public:
  cmpL3_reg_reg_ExExNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(cmpL3_reg_reg_ExExNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "cmpL3_reg_reg_ExEx";}
#endif
};

class rangeCheck_iReg_uimm15Node : public MachIfNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return rangeCheck_iReg_uimm15_rule; }
  virtual void           label_set( Label* label, uint block_num );
  virtual void           save_label( Label** label, uint* block_num );
  virtual bool           is_TrapBasedCheckNode() const { return true; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_If; }
  virtual void           negate() { 
    opnd_array(1)->negate();
    _prob = 1.0f - _prob;
  };
  virtual uint           oper_input_base() const { return 1; }
public:
  rangeCheck_iReg_uimm15Node() {  _num_opnds = 5; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(rangeCheck_iReg_uimm15Node); }
  virtual bool           pinned() const { return true; }
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  const Type            *bottom_type() const { return TypeTuple::IFBOTH; } // matched IfNode
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "rangeCheck_iReg_uimm15";}
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return rangeCheck_iReg_iReg_rule; }
  virtual void           label_set( Label* label, uint block_num );
  virtual void           save_label( Label** label, uint* block_num );
  virtual bool           is_TrapBasedCheckNode() const { return true; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_If; }
  virtual void           negate() { 
    opnd_array(1)->negate();
    _prob = 1.0f - _prob;
  };
  virtual uint           oper_input_base() const { return 1; }
public:
  rangeCheck_iReg_iRegNode() {  _num_opnds = 5; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(rangeCheck_iReg_iRegNode); }
  virtual bool           pinned() const { return true; }
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  const Type            *bottom_type() const { return TypeTuple::IFBOTH; } // matched IfNode
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "rangeCheck_iReg_iReg";}
#endif
};

class rangeCheck_uimm15_iRegNode : public MachIfNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return rangeCheck_uimm15_iReg_rule; }
  virtual void           label_set( Label* label, uint block_num );
  virtual void           save_label( Label** label, uint* block_num );
  virtual bool           is_TrapBasedCheckNode() const { return true; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_If; }
  virtual void           negate() { 
    opnd_array(1)->negate();
    _prob = 1.0f - _prob;
  };
  virtual uint           oper_input_base() const { return 1; }
public:
  rangeCheck_uimm15_iRegNode() {  _num_opnds = 5; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(rangeCheck_uimm15_iRegNode); }
  virtual bool           pinned() const { return true; }
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  const Type            *bottom_type() const { return TypeTuple::IFBOTH; } // matched IfNode
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "rangeCheck_uimm15_iReg";}
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return compU_reg_reg_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_CmpU; }
public:
  compU_reg_regNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(compU_reg_regNode); }
  // Rematerialize compU_reg_reg
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "compU_reg_reg";}
#endif
};

class compU_reg_uimm16Node : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return compU_reg_uimm16_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_CmpU; }
public:
  compU_reg_uimm16Node() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(compU_reg_uimm16Node); }
  // Rematerialize compU_reg_uimm16
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "compU_reg_uimm16";}
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return zeroCheckN_iReg_imm0_rule; }
  virtual void           label_set( Label* label, uint block_num );
  virtual void           save_label( Label** label, uint* block_num );
  virtual bool           is_TrapBasedCheckNode() const { return true; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_If; }
  virtual void           negate() { 
    opnd_array(1)->negate();
    _prob = 1.0f - _prob;
  };
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

class cmpN_reg_regNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return cmpN_reg_reg_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_CmpN; }
public:
  cmpN_reg_regNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(cmpN_reg_regNode); }
  // Rematerialize cmpN_reg_reg
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "cmpN_reg_reg";}
#endif
};

class cmpN_reg_imm0Node : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return cmpN_reg_imm0_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_CmpN; }
public:
  cmpN_reg_imm0Node() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(cmpN_reg_imm0Node); }
  // Rematerialize cmpN_reg_imm0
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "cmpN_reg_imm0";}
#endif
};

class zeroCheckP_reg_imm0Node : public MachIfNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return zeroCheckP_reg_imm0_rule; }
  virtual void           label_set( Label* label, uint block_num );
  virtual void           save_label( Label** label, uint* block_num );
  virtual bool           is_TrapBasedCheckNode() const { return true; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_If; }
  virtual void           negate() { 
    opnd_array(1)->negate();
    _prob = 1.0f - _prob;
  };
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 1; }
public:
  zeroCheckP_reg_imm0Node() {  _num_opnds = 5; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(zeroCheckP_reg_imm0Node); }
  virtual bool           pinned() const { return true; }
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  const Type            *bottom_type() const { return TypeTuple::IFBOTH; } // matched IfNode
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "zeroCheckP_reg_imm0";}
#endif
};

class cmpP_reg_regNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return cmpP_reg_reg_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_CmpP; }
  virtual int            reloc() const;
public:
  cmpP_reg_regNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(cmpP_reg_regNode); }
  // Rematerialize cmpP_reg_reg
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "cmpP_reg_reg";}
#endif
};

class cmpP_reg_nullNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return cmpP_reg_null_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_CmpP; }
  virtual int            reloc() const;
public:
  cmpP_reg_nullNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(cmpP_reg_nullNode); }
  // Rematerialize cmpP_reg_null
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "cmpP_reg_null";}
#endif
};

class cmpP_reg_imm16Node : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return cmpP_reg_imm16_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_CmpP; }
public:
  cmpP_reg_imm16Node() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(cmpP_reg_imm16Node); }
  // Rematerialize cmpP_reg_imm16
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "cmpP_reg_imm16";}
#endif
};

class cmpFUnordered_reg_regNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return cmpFUnordered_reg_reg_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_CmpF; }
public:
  cmpFUnordered_reg_regNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(cmpFUnordered_reg_regNode); }
  // Rematerialize cmpFUnordered_reg_reg
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "cmpFUnordered_reg_reg";}
#endif
};

class cmov_bns_lessNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return cmov_bns_less_rule; }
  virtual int            ins_variable_size_depending_on_alignment() const { return true; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
public:
  cmov_bns_lessNode() {  _num_opnds = 1; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(cmov_bns_lessNode); }
  friend MachNode *State::MachNodeGenerator(int opcode);
  // Rematerialize cmov_bns_less
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "cmov_bns_less";}
#endif
};

class cmpF_reg_reg_ExNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return cmpF_reg_reg_Ex_rule; }
  virtual bool           requires_postalloc_expand() const { return true; }
  virtual void           postalloc_expand(GrowableArray <Node *> *nodes, PhaseRegAlloc *ra_);
  virtual int            ideal_Opcode() const { return Op_CmpF; }
public:
  cmpF_reg_reg_ExNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(cmpF_reg_reg_ExNode); }
  // Rematerialize cmpF_reg_reg_Ex
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "cmpF_reg_reg_Ex";}
#endif
};

class cmpF3_reg_reg_ExExNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return cmpF3_reg_reg_ExEx_rule; }
  virtual int            ideal_Opcode() const { return Op_CmpF3; }
public:
  cmpF3_reg_reg_ExExNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(cmpF3_reg_reg_ExExNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "cmpF3_reg_reg_ExEx";}
#endif
};

class cmpDUnordered_reg_regNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return cmpDUnordered_reg_reg_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_CmpD; }
public:
  cmpDUnordered_reg_regNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(cmpDUnordered_reg_regNode); }
  // Rematerialize cmpDUnordered_reg_reg
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "cmpDUnordered_reg_reg";}
#endif
};

class cmpD_reg_reg_ExNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return cmpD_reg_reg_Ex_rule; }
  virtual bool           requires_postalloc_expand() const { return true; }
  virtual void           postalloc_expand(GrowableArray <Node *> *nodes, PhaseRegAlloc *ra_);
  virtual int            ideal_Opcode() const { return Op_CmpD; }
public:
  cmpD_reg_reg_ExNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(cmpD_reg_reg_ExNode); }
  // Rematerialize cmpD_reg_reg_Ex
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "cmpD_reg_reg_Ex";}
#endif
};

class cmpD3_reg_reg_ExExNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return cmpD3_reg_reg_ExEx_rule; }
  virtual int            ideal_Opcode() const { return Op_CmpD3; }
public:
  cmpD3_reg_reg_ExExNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(cmpD3_reg_reg_ExExNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "cmpD3_reg_reg_ExEx";}
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return branch_rule; }
  virtual void           label_set( Label* label, uint block_num );
  virtual void           save_label( Label** label, uint* block_num );
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return branchCon_rule; }
  virtual void           label_set( Label* label, uint block_num );
  virtual void           save_label( Label** label, uint* block_num );
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return branchConFar_rule; }
  virtual void           label_set( Label* label, uint block_num );
  virtual void           save_label( Label** label, uint* block_num );
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
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

class branchConSchedNode : public MachIfNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return branchConSched_rule; }
  virtual void           label_set( Label* label, uint block_num );
  virtual void           save_label( Label** label, uint* block_num );
  virtual int            ins_variable_size_depending_on_alignment() const { return true; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_If; }
  virtual void           negate() { 
    opnd_array(1)->negate();
    _prob = 1.0f - _prob;
  };
  virtual uint           oper_input_base() const { return 1; }
public:
  branchConSchedNode() {  _num_opnds = 4; _opnds = _opnd_array; init_flags(Flag_may_be_short_branch); }
  virtual uint           size_of() const { return sizeof(branchConSchedNode); }
  virtual bool           pinned() const { return true; }
  friend MachNode *State::MachNodeGenerator(int opcode);
  virtual MachNode      *short_branch_version();
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  const Type            *bottom_type() const { return TypeTuple::IFBOTH; } // matched IfNode
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "branchConSched";}
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return branchLoopEnd_rule; }
  virtual void           label_set( Label* label, uint block_num );
  virtual void           save_label( Label** label, uint* block_num );
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return branchLoopEndFar_rule; }
  virtual void           label_set( Label* label, uint block_num );
  virtual void           save_label( Label** label, uint* block_num );
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
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

class branchLoopEndSchedNode : public MachIfNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return branchLoopEndSched_rule; }
  virtual void           label_set( Label* label, uint block_num );
  virtual void           save_label( Label** label, uint* block_num );
  virtual int            ins_variable_size_depending_on_alignment() const { return true; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_CountedLoopEnd; }
  virtual void           negate() { 
    opnd_array(1)->negate();
    _prob = 1.0f - _prob;
  };
  virtual uint           oper_input_base() const { return 1; }
public:
  branchLoopEndSchedNode() {  _num_opnds = 4; _opnds = _opnd_array; init_flags(Flag_may_be_short_branch); }
  virtual uint           size_of() const { return sizeof(branchLoopEndSchedNode); }
  virtual bool           pinned() const { return true; }
  friend MachNode *State::MachNodeGenerator(int opcode);
  virtual MachNode      *short_branch_version();
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  const Type            *bottom_type() const { return TypeTuple::IFBOTH; } // matched IfNode
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "branchLoopEndSched";}
#endif
};

class partialSubtypeCheckNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return partialSubtypeCheck_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_PartialSubtypeCheck; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges() + opnd_array(2)->num_edges(); }
  virtual int            reloc() const;
public:
  partialSubtypeCheckNode() {  _num_opnds = 6; _opnds = _opnd_array; }
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return cmpFastLock_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_FastLock; }
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

class cmpFastLock_tmNode : public MachFastLockNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return cmpFastLock_tm_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_FastLock; }
  virtual uint           oper_input_base() const { return 1; }
public:
  cmpFastLock_tmNode() {  _num_opnds = 6; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(cmpFastLock_tmNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  // Rematerialize cmpFastLock_tm
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "cmpFastLock_tm";}
#endif
};

class cmpFastUnlockNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return cmpFastUnlock_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_FastUnlock; }
public:
  cmpFastUnlockNode() {  _num_opnds = 6; _opnds = _opnd_array; }
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

class cmpFastUnlock_tmNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return cmpFastUnlock_tm_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_FastUnlock; }
public:
  cmpFastUnlock_tmNode() {  _num_opnds = 6; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(cmpFastUnlock_tmNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  // Rematerialize cmpFastUnlock_tm
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "cmpFastUnlock_tm";}
#endif
};

class align_addrNode : public MachTypeNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return align_addr_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_CastX2P; }
  virtual uint           oper_input_base() const { return 1; }
public:
  align_addrNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(align_addrNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "align_addr";}
#endif
};

class array_sizeNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return array_size_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_SubL; }
public:
  array_sizeNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(array_sizeNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "array_size";}
#endif
};

class inlineCallClearArrayShortNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return inlineCallClearArrayShort_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_ClearArray; }
  virtual uint           oper_input_base() const { return 2; }
public:
  inlineCallClearArrayShortNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(inlineCallClearArrayShortNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "inlineCallClearArrayShort";}
#endif
};

class inlineCallClearArrayLargeNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return inlineCallClearArrayLarge_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_ClearArray; }
  virtual uint           oper_input_base() const { return 2; }
public:
  inlineCallClearArrayLargeNode() {  _num_opnds = 4; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(inlineCallClearArrayLargeNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "inlineCallClearArrayLarge";}
#endif
};

class inlineCallClearArrayNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return inlineCallClearArray_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_ClearArray; }
  virtual uint           oper_input_base() const { return 2; }
public:
  inlineCallClearArrayNode() {  _num_opnds = 3; _opnds = _opnd_array; }
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

class string_compareLNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return string_compareL_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_StrComp; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges() + opnd_array(2)->num_edges() + opnd_array(3)->num_edges() + opnd_array(4)->num_edges(); }
  virtual uint           oper_input_base() const { return 2; }
public:
  string_compareLNode() {  _num_opnds = 7; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return string_compareU_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_StrComp; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges() + opnd_array(2)->num_edges() + opnd_array(3)->num_edges() + opnd_array(4)->num_edges(); }
  virtual uint           oper_input_base() const { return 2; }
public:
  string_compareUNode() {  _num_opnds = 7; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return string_compareLU_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_StrComp; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges() + opnd_array(2)->num_edges() + opnd_array(3)->num_edges() + opnd_array(4)->num_edges(); }
  virtual uint           oper_input_base() const { return 2; }
public:
  string_compareLUNode() {  _num_opnds = 7; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return string_compareUL_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_StrComp; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges() + opnd_array(2)->num_edges() + opnd_array(3)->num_edges() + opnd_array(4)->num_edges(); }
  virtual uint           oper_input_base() const { return 2; }
public:
  string_compareULNode() {  _num_opnds = 7; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return string_equalsL_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_StrEquals; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges() + opnd_array(2)->num_edges() + opnd_array(3)->num_edges(); }
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

class string_equalsUNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return string_equalsU_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_StrEquals; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges() + opnd_array(2)->num_edges() + opnd_array(3)->num_edges(); }
  virtual uint           oper_input_base() const { return 2; }
public:
  string_equalsUNode() {  _num_opnds = 6; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(string_equalsUNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "string_equalsU";}
#endif
};

class array_equalsBNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return array_equalsB_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_AryEq; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges() + opnd_array(2)->num_edges(); }
  virtual uint           oper_input_base() const { return 2; }
public:
  array_equalsBNode() {  _num_opnds = 6; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return array_equalsC_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_AryEq; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges() + opnd_array(2)->num_edges(); }
  virtual uint           oper_input_base() const { return 2; }
public:
  array_equalsCNode() {  _num_opnds = 6; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
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

class indexOf_imm1_char_UNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return indexOf_imm1_char_U_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_StrIndexOf; }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  indexOf_imm1_char_UNode() {  _num_opnds = 8; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(indexOf_imm1_char_UNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "indexOf_imm1_char_U";}
#endif
};

class indexOf_imm1_char_LNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return indexOf_imm1_char_L_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_StrIndexOf; }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  indexOf_imm1_char_LNode() {  _num_opnds = 8; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(indexOf_imm1_char_LNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "indexOf_imm1_char_L";}
#endif
};

class indexOf_imm1_char_ULNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return indexOf_imm1_char_UL_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_StrIndexOf; }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 2; }
public:
  indexOf_imm1_char_ULNode() {  _num_opnds = 8; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(indexOf_imm1_char_ULNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "indexOf_imm1_char_UL";}
#endif
};

class indexOf_imm1_UNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return indexOf_imm1_U_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_StrIndexOf; }
  virtual uint           oper_input_base() const { return 2; }
public:
  indexOf_imm1_UNode() {  _num_opnds = 7; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return indexOf_imm1_L_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_StrIndexOf; }
  virtual uint           oper_input_base() const { return 2; }
public:
  indexOf_imm1_LNode() {  _num_opnds = 7; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return indexOf_imm1_UL_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_StrIndexOf; }
  virtual uint           oper_input_base() const { return 2; }
public:
  indexOf_imm1_ULNode() {  _num_opnds = 7; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
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

class indexOfChar_UNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return indexOfChar_U_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_StrIndexOfChar; }
  virtual uint           oper_input_base() const { return 2; }
public:
  indexOfChar_UNode() {  _num_opnds = 6; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
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

class indexOf_imm_UNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return indexOf_imm_U_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_StrIndexOf; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges() + opnd_array(2)->num_edges() + opnd_array(3)->num_edges() + opnd_array(4)->num_edges(); }
  virtual uint           oper_input_base() const { return 2; }
public:
  indexOf_imm_UNode() {  _num_opnds = 11; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return indexOf_imm_L_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_StrIndexOf; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges() + opnd_array(2)->num_edges() + opnd_array(3)->num_edges() + opnd_array(4)->num_edges(); }
  virtual uint           oper_input_base() const { return 2; }
public:
  indexOf_imm_LNode() {  _num_opnds = 11; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return indexOf_imm_UL_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_StrIndexOf; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges() + opnd_array(2)->num_edges() + opnd_array(3)->num_edges() + opnd_array(4)->num_edges(); }
  virtual uint           oper_input_base() const { return 2; }
public:
  indexOf_imm_ULNode() {  _num_opnds = 11; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
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
  MachOper *_opnd_array[10];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return indexOf_U_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_StrIndexOf; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges() + opnd_array(2)->num_edges() + opnd_array(3)->num_edges() + opnd_array(4)->num_edges(); }
  virtual uint           oper_input_base() const { return 2; }
public:
  indexOf_UNode() {  _num_opnds = 10; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
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
  MachOper *_opnd_array[10];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return indexOf_L_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_StrIndexOf; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges() + opnd_array(2)->num_edges() + opnd_array(3)->num_edges() + opnd_array(4)->num_edges(); }
  virtual uint           oper_input_base() const { return 2; }
public:
  indexOf_LNode() {  _num_opnds = 10; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
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
  MachOper *_opnd_array[10];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return indexOf_UL_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_StrIndexOf; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges() + opnd_array(2)->num_edges() + opnd_array(3)->num_edges() + opnd_array(4)->num_edges(); }
  virtual uint           oper_input_base() const { return 2; }
public:
  indexOf_ULNode() {  _num_opnds = 10; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
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
  MachOper *_opnd_array[10];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return string_compress_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_StrCompressedCopy; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges() + opnd_array(2)->num_edges() + opnd_array(3)->num_edges(); }
  virtual uint           oper_input_base() const { return 2; }
public:
  string_compressNode() {  _num_opnds = 10; _opnds = _opnd_array; }
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

class string_inflateNode : public MachNode { 
private:
  MachOper *_opnd_array[9];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return string_inflate_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_StrInflatedCopy; }
  virtual uint           oper_input_base() const { return 2; }
public:
  string_inflateNode() {  _num_opnds = 9; _opnds = _opnd_array; }
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

class has_negativesNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return has_negatives_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_HasNegatives; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges() + opnd_array(2)->num_edges(); }
  virtual uint           oper_input_base() const { return 2; }
public:
  has_negativesNode() {  _num_opnds = 6; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(has_negativesNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "has_negatives";}
#endif
};

class encode_iso_arrayNode : public MachNode { 
private:
  MachOper *_opnd_array[10];
public:
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return encode_iso_array_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_EncodeISOArray; }
  virtual uint           two_adr() const  { return oper_input_base() + opnd_array(1)->num_edges() + opnd_array(2)->num_edges() + opnd_array(3)->num_edges(); }
  virtual uint           oper_input_base() const { return 2; }
public:
  encode_iso_arrayNode() {  _num_opnds = 10; _opnds = _opnd_array; }
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

class minI_reg_reg_ExNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return minI_reg_reg_Ex_rule; }
  virtual int            ideal_Opcode() const { return Op_MinI; }
public:
  minI_reg_reg_ExNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(minI_reg_reg_ExNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "minI_reg_reg_Ex";}
#endif
};

class minI_reg_reg_iselNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return minI_reg_reg_isel_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_MinI; }
public:
  minI_reg_reg_iselNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(minI_reg_reg_iselNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "minI_reg_reg_isel";}
#endif
};

class maxI_reg_reg_ExNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return maxI_reg_reg_Ex_rule; }
  virtual int            ideal_Opcode() const { return Op_MaxI; }
public:
  maxI_reg_reg_ExNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(maxI_reg_reg_ExNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "maxI_reg_reg_Ex";}
#endif
};

class maxI_reg_reg_iselNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return maxI_reg_reg_isel_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_MaxI; }
public:
  maxI_reg_reg_iselNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(maxI_reg_reg_iselNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "maxI_reg_reg_isel";}
#endif
};

class popCountINode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return popCountI_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_PopCountI; }
public:
  popCountINode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(popCountINode); }
  // Rematerialize popCountI
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "popCountI";}
#endif
};

class popCountLNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return popCountL_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_PopCountL; }
public:
  popCountLNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(popCountLNode); }
  // Rematerialize popCountL
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "popCountL";}
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return countLeadingZerosI_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_CountLeadingZerosI; }
public:
  countLeadingZerosINode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(countLeadingZerosINode); }
  // Rematerialize countLeadingZerosI
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return countLeadingZerosL_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_CountLeadingZerosL; }
public:
  countLeadingZerosLNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(countLeadingZerosLNode); }
  // Rematerialize countLeadingZerosL
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "countLeadingZerosL";}
#endif
};

class countLeadingZerosPNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return countLeadingZerosP_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
public:
  countLeadingZerosPNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(countLeadingZerosPNode); }
  friend MachNode *State::MachNodeGenerator(int opcode);
  // Rematerialize countLeadingZerosP
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "countLeadingZerosP";}
#endif
};

class countTrailingZerosI_ExNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return countTrailingZerosI_Ex_rule; }
  virtual int            ideal_Opcode() const { return Op_CountTrailingZerosI; }
public:
  countTrailingZerosI_ExNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(countTrailingZerosI_ExNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  // Rematerialize countTrailingZerosI_Ex
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "countTrailingZerosI_Ex";}
#endif
};

class countTrailingZerosL_ExNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return countTrailingZerosL_Ex_rule; }
  virtual int            ideal_Opcode() const { return Op_CountTrailingZerosL; }
public:
  countTrailingZerosL_ExNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(countTrailingZerosL_ExNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  // Rematerialize countTrailingZerosL_Ex
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "countTrailingZerosL_Ex";}
#endif
};

class insrwi_aNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return insrwi_a_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
public:
  insrwi_aNode() {  _num_opnds = 4; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(insrwi_aNode); }
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "insrwi_a";}
#endif
};

class insrwiNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return insrwi_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual uint           two_adr() const  { return oper_input_base(); }
public:
  insrwiNode() {  _num_opnds = 5; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(insrwiNode); }
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "insrwi";}
#endif
};

class bytes_reverse_int_ExNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return bytes_reverse_int_Ex_rule; }
  virtual int            ideal_Opcode() const { return Op_ReverseBytesI; }
public:
  bytes_reverse_int_ExNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(bytes_reverse_int_ExNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "bytes_reverse_int_Ex";}
#endif
};

class bytes_reverse_long_ExNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return bytes_reverse_long_Ex_rule; }
  virtual int            ideal_Opcode() const { return Op_ReverseBytesL; }
public:
  bytes_reverse_long_ExNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(bytes_reverse_long_ExNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "bytes_reverse_long_Ex";}
#endif
};

class bytes_reverse_ushort_ExNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return bytes_reverse_ushort_Ex_rule; }
  virtual int            ideal_Opcode() const { return Op_ReverseBytesUS; }
public:
  bytes_reverse_ushort_ExNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(bytes_reverse_ushort_ExNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "bytes_reverse_ushort_Ex";}
#endif
};

class bytes_reverse_short_ExNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return bytes_reverse_short_Ex_rule; }
  virtual int            ideal_Opcode() const { return Op_ReverseBytesS; }
public:
  bytes_reverse_short_ExNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(bytes_reverse_short_ExNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "bytes_reverse_short_Ex";}
#endif
};

class loadI_reversedNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return loadI_reversed_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_ReverseBytesI; }
  virtual uint           oper_input_base() const { return 2; }
public:
  loadI_reversedNode() {  _num_opnds = 2; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(loadI_reversedNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "loadI_reversed";}
#endif
};

class loadL_reversedNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return loadL_reversed_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_ReverseBytesL; }
  virtual uint           oper_input_base() const { return 2; }
public:
  loadL_reversedNode() {  _num_opnds = 2; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(loadL_reversedNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "loadL_reversed";}
#endif
};

class loadUS_reversedNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return loadUS_reversed_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_ReverseBytesUS; }
  virtual uint           oper_input_base() const { return 2; }
public:
  loadUS_reversedNode() {  _num_opnds = 2; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(loadUS_reversedNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "loadUS_reversed";}
#endif
};

class loadS_reversedNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return loadS_reversed_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_ReverseBytesS; }
  virtual uint           oper_input_base() const { return 2; }
public:
  loadS_reversedNode() {  _num_opnds = 2; _opnds = _opnd_array; init_flags(Flag_needs_anti_dependence_check); }
  virtual uint           size_of() const { return sizeof(loadS_reversedNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "loadS_reversed";}
#endif
};

class storeI_reversedNode : public MachTypeNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return storeI_reversed_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_StoreI; }
  virtual uint           oper_input_base() const { return 2; }
public:
  storeI_reversedNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(storeI_reversedNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "storeI_reversed";}
#endif
};

class storeL_reversedNode : public MachTypeNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return storeL_reversed_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_StoreL; }
  virtual uint           oper_input_base() const { return 2; }
public:
  storeL_reversedNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(storeL_reversedNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "storeL_reversed";}
#endif
};

class storeUS_reversedNode : public MachTypeNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return storeUS_reversed_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_StoreC; }
  virtual uint           oper_input_base() const { return 2; }
public:
  storeUS_reversedNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(storeUS_reversedNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "storeUS_reversed";}
#endif
};

class storeS_reversedNode : public MachTypeNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return storeS_reversed_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_StoreC; }
  virtual uint           oper_input_base() const { return 2; }
public:
  storeS_reversedNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(storeS_reversedNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
  virtual const MachOper *memory_operand() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "storeS_reversed";}
#endif
};

class mtvsrwzNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return mtvsrwz_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
public:
  mtvsrwzNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(mtvsrwzNode); }
  friend MachNode *State::MachNodeGenerator(int opcode);
  // Rematerialize mtvsrwz
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "mtvsrwz";}
#endif
};

class xxspltwNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return xxspltw_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
public:
  xxspltwNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(xxspltwNode); }
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "xxspltw";}
#endif
};

class repl32Node : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return repl32_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual uint           two_adr() const  { return oper_input_base(); }
public:
  repl32Node() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(repl32Node); }
  friend MachNode *State::MachNodeGenerator(int opcode);
  // Rematerialize repl32
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "repl32";}
#endif
};

class repl48Node : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return repl48_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual uint           two_adr() const  { return oper_input_base(); }
public:
  repl48Node() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(repl48Node); }
  friend MachNode *State::MachNodeGenerator(int opcode);
  // Rematerialize repl48
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "repl48";}
#endif
};

class repl56Node : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return repl56_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual uint           two_adr() const  { return oper_input_base(); }
public:
  repl56Node() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(repl56Node); }
  friend MachNode *State::MachNodeGenerator(int opcode);
  // Rematerialize repl56
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "repl56";}
#endif
};

class repl8B_reg_ExNode : public MachTypeNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return repl8B_reg_Ex_rule; }
  virtual int            ideal_Opcode() const { return Op_ReplicateB; }
  virtual uint           oper_input_base() const { return 1; }
public:
  repl8B_reg_ExNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(repl8B_reg_ExNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "repl8B_reg_Ex";}
#endif
};

class repl8B_immI0Node : public MachTypeNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return repl8B_immI0_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_ReplicateB; }
  virtual uint           oper_input_base() const { return 1; }
public:
  repl8B_immI0Node() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(repl8B_immI0Node); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "repl8B_immI0";}
#endif
};

class repl8B_immIminus1Node : public MachTypeNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return repl8B_immIminus1_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_ReplicateB; }
  virtual uint           oper_input_base() const { return 1; }
public:
  repl8B_immIminus1Node() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(repl8B_immIminus1Node); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "repl8B_immIminus1";}
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return repl16B_reg_Ex_rule; }
  virtual int            ideal_Opcode() const { return Op_ReplicateB; }
  virtual uint           oper_input_base() const { return 1; }
public:
  repl16B_reg_ExNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(repl16B_reg_ExNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "repl16B_reg_Ex";}
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return repl16B_immI0_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_ReplicateB; }
  virtual uint           oper_input_base() const { return 1; }
public:
  repl16B_immI0Node() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(repl16B_immI0Node); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "repl16B_immI0";}
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return repl16B_immIminus1_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_ReplicateB; }
  virtual uint           oper_input_base() const { return 1; }
public:
  repl16B_immIminus1Node() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(repl16B_immIminus1Node); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "repl16B_immIminus1";}
#endif
};

class repl4S_reg_ExNode : public MachTypeNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return repl4S_reg_Ex_rule; }
  virtual int            ideal_Opcode() const { return Op_ReplicateS; }
  virtual uint           oper_input_base() const { return 1; }
public:
  repl4S_reg_ExNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(repl4S_reg_ExNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "repl4S_reg_Ex";}
#endif
};

class repl4S_immI0Node : public MachTypeNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return repl4S_immI0_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_ReplicateS; }
  virtual uint           oper_input_base() const { return 1; }
public:
  repl4S_immI0Node() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(repl4S_immI0Node); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "repl4S_immI0";}
#endif
};

class repl4S_immIminus1Node : public MachTypeNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return repl4S_immIminus1_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_ReplicateS; }
  virtual uint           oper_input_base() const { return 1; }
public:
  repl4S_immIminus1Node() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(repl4S_immIminus1Node); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "repl4S_immIminus1";}
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return repl8S_reg_Ex_rule; }
  virtual int            ideal_Opcode() const { return Op_ReplicateS; }
  virtual uint           oper_input_base() const { return 1; }
public:
  repl8S_reg_ExNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(repl8S_reg_ExNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "repl8S_reg_Ex";}
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return repl8S_immI0_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_ReplicateS; }
  virtual uint           oper_input_base() const { return 1; }
public:
  repl8S_immI0Node() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(repl8S_immI0Node); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "repl8S_immI0";}
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return repl8S_immIminus1_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_ReplicateS; }
  virtual uint           oper_input_base() const { return 1; }
public:
  repl8S_immIminus1Node() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(repl8S_immIminus1Node); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "repl8S_immIminus1";}
#endif
};

class repl2I_reg_ExNode : public MachTypeNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return repl2I_reg_Ex_rule; }
  virtual int            ideal_Opcode() const { return Op_ReplicateI; }
  virtual uint           oper_input_base() const { return 1; }
public:
  repl2I_reg_ExNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(repl2I_reg_ExNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "repl2I_reg_Ex";}
#endif
};

class repl2I_immI0Node : public MachTypeNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return repl2I_immI0_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_ReplicateI; }
  virtual uint           oper_input_base() const { return 1; }
public:
  repl2I_immI0Node() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(repl2I_immI0Node); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "repl2I_immI0";}
#endif
};

class repl2I_immIminus1Node : public MachTypeNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return repl2I_immIminus1_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_ReplicateI; }
  virtual uint           oper_input_base() const { return 1; }
public:
  repl2I_immIminus1Node() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(repl2I_immIminus1Node); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "repl2I_immIminus1";}
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return repl4I_reg_Ex_rule; }
  virtual int            ideal_Opcode() const { return Op_ReplicateI; }
  virtual uint           oper_input_base() const { return 1; }
public:
  repl4I_reg_ExNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(repl4I_reg_ExNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return repl4I_immI0_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_ReplicateI; }
  virtual uint           oper_input_base() const { return 1; }
public:
  repl4I_immI0Node() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(repl4I_immI0Node); }
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return repl4I_immIminus1_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_ReplicateI; }
  virtual uint           oper_input_base() const { return 1; }
public:
  repl4I_immIminus1Node() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(repl4I_immIminus1Node); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "repl4I_immIminus1";}
#endif
};

class repl2F_reg_ExNode : public MachTypeNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return repl2F_reg_Ex_rule; }
  virtual int            ideal_Opcode() const { return Op_ReplicateF; }
  virtual uint           oper_input_base() const { return 1; }
public:
  repl2F_reg_ExNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(repl2F_reg_ExNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "repl2F_reg_Ex";}
#endif
};

class repl2F_immF_ExNode : public MachConstantNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return repl2F_immF_Ex_rule; }
  virtual void           eval_constant(Compile* C);
  virtual bool           requires_postalloc_expand() const { return true; }
  virtual void           postalloc_expand(GrowableArray <Node *> *nodes, PhaseRegAlloc *ra_);
  virtual int            ideal_Opcode() const { return Op_ReplicateF; }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 1; }
public:
  repl2F_immF_ExNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(repl2F_immF_ExNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "repl2F_immF_Ex";}
#endif
};

class repl2F_immF0Node : public MachTypeNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return repl2F_immF0_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_ReplicateF; }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 1; }
public:
  repl2F_immF0Node() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(repl2F_immF0Node); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "repl2F_immF0";}
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return overflowAddL_reg_reg_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return overflowSubL_reg_reg_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
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

class overflowNegL_regNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return overflowNegL_reg_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_OverflowSubL; }
public:
  overflowNegL_regNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(overflowNegL_regNode); }
  // Rematerialize overflowNegL_reg
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "overflowNegL_reg";}
#endif
};

class overflowMulL_reg_regNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return overflowMulL_reg_reg_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_OverflowMulL; }
public:
  overflowMulL_reg_regNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(overflowMulL_reg_regNode); }
  // Rematerialize overflowMulL_reg_reg
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "overflowMulL_reg_reg";}
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return repl4F_reg_Ex_rule; }
  virtual int            ideal_Opcode() const { return Op_ReplicateF; }
  virtual uint           oper_input_base() const { return 1; }
public:
  repl4F_reg_ExNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(repl4F_reg_ExNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "repl4F_reg_Ex";}
#endif
};

class repl4F_immF_ExNode : public MachConstantNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return repl4F_immF_Ex_rule; }
  virtual void           eval_constant(Compile* C);
  virtual bool           requires_postalloc_expand() const { return true; }
  virtual void           postalloc_expand(GrowableArray <Node *> *nodes, PhaseRegAlloc *ra_);
  virtual int            ideal_Opcode() const { return Op_ReplicateF; }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 1; }
public:
  repl4F_immF_ExNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(repl4F_immF_ExNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "repl4F_immF_Ex";}
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return repl4F_immF0_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_ReplicateF; }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 1; }
public:
  repl4F_immF0Node() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(repl4F_immF0Node); }
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return repl2D_reg_Ex_rule; }
  virtual int            ideal_Opcode() const { return Op_ReplicateD; }
  virtual uint           oper_input_base() const { return 1; }
public:
  repl2D_reg_ExNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(repl2D_reg_ExNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "repl2D_reg_Ex";}
#endif
};

class repl2D_immI0Node : public MachTypeNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return repl2D_immI0_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_ReplicateD; }
  virtual uint           oper_input_base() const { return 1; }
public:
  repl2D_immI0Node() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(repl2D_immI0Node); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "repl2D_immI0";}
#endif
};

class repl2D_immIminus1Node : public MachTypeNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return repl2D_immIminus1_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_ReplicateD; }
  virtual uint           oper_input_base() const { return 1; }
public:
  repl2D_immIminus1Node() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(repl2D_immIminus1Node); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "repl2D_immIminus1";}
#endif
};

class mtvsrdNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return mtvsrd_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
public:
  mtvsrdNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(mtvsrdNode); }
  friend MachNode *State::MachNodeGenerator(int opcode);
  // Rematerialize mtvsrd
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "mtvsrd";}
#endif
};

class xxspltdNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return xxspltd_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
public:
  xxspltdNode() {  _num_opnds = 3; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(xxspltdNode); }
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "xxspltd";}
#endif
};

class xxpermdiNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return xxpermdi_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
public:
  xxpermdiNode() {  _num_opnds = 4; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(xxpermdiNode); }
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "xxpermdi";}
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return repl2L_reg_Ex_rule; }
  virtual int            ideal_Opcode() const { return Op_ReplicateL; }
  virtual uint           oper_input_base() const { return 1; }
public:
  repl2L_reg_ExNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(repl2L_reg_ExNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "repl2L_reg_Ex";}
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return repl2L_immI0_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_ReplicateL; }
  virtual uint           oper_input_base() const { return 1; }
public:
  repl2L_immI0Node() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(repl2L_immI0Node); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "repl2L_immI0";}
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return repl2L_immIminus1_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_ReplicateL; }
  virtual uint           oper_input_base() const { return 1; }
public:
  repl2L_immIminus1Node() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(repl2L_immIminus1Node); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "repl2L_immIminus1";}
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return safePoint_poll_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_SafePoint; }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 5; }
public:
  safePoint_pollNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(safePoint_pollNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "safePoint_poll";}
#endif
};

class CallStaticJavaDirectNode : public MachCallStaticJavaNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return CallStaticJavaDirect_rule; }
  virtual void           method_set( intptr_t method );
  virtual int            ins_num_consts() const { return 3 /* up to 3 patchable constants: inline cache, 2 call targets. */; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_CallStaticJava; }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 1; }
public:
  CallStaticJavaDirectNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(CallStaticJavaDirectNode); }
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "CallStaticJavaDirect";}
#endif
};

class CallDynamicJavaDirectSchedNode : public MachCallDynamicJavaNode { 
private:
  MachOper *_opnd_array[2];
public:
  loadConLNode* _load_ic_node;
  loadConL_hiNode* _load_ic_hi_node;
  MachOper *opnd_array(uint operand_index) const {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    return _opnd_array[operand_index];
  }
  void      set_opnd_array(uint operand_index, MachOper *operand) {
    assert(operand_index < _num_opnds, "invalid _opnd_array index");
    _opnd_array[operand_index] = operand;
  }
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return CallDynamicJavaDirectSched_rule; }
  virtual void           method_set( intptr_t method );
  virtual int            ins_num_consts() const { return 1 /* 1 patchable constant: call destination */; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_CallDynamicJava; }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 1; }
public:
  CallDynamicJavaDirectSchedNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(CallDynamicJavaDirectSchedNode); }
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "CallDynamicJavaDirectSched";}
#endif
};

class CallDynamicJavaDirectSched_ExNode : public MachCallDynamicJavaNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return CallDynamicJavaDirectSched_Ex_rule; }
  virtual void           method_set( intptr_t method );
  virtual int            ins_num_consts() const { return 2 /* 2 patchable constants: inline cache, call destination. */; }
  virtual bool           requires_postalloc_expand() const { return true; }
  virtual void           postalloc_expand(GrowableArray <Node *> *nodes, PhaseRegAlloc *ra_);
  virtual int            ideal_Opcode() const { return Op_CallDynamicJava; }
  virtual uint           mach_constant_base_node_input() const { assert(tf() && tf()->domain(), ""); return tf()->domain()->cnt(); }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 1; }
public:
  CallDynamicJavaDirectSched_ExNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(CallDynamicJavaDirectSched_ExNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "CallDynamicJavaDirectSched_Ex";}
#endif
};

class CallDynamicJavaDirectNode : public MachCallDynamicJavaNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return CallDynamicJavaDirect_rule; }
  virtual void           method_set( intptr_t method );
  virtual int            ins_num_consts() const { return 4; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_CallDynamicJava; }
  virtual uint           mach_constant_base_node_input() const { assert(tf() && tf()->domain(), ""); return tf()->domain()->cnt(); }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 1; }
public:
  CallDynamicJavaDirectNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(CallDynamicJavaDirectNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "CallDynamicJavaDirect";}
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return CallRuntimeDirect_rule; }
  virtual void           method_set( intptr_t method );
  virtual int            ins_num_consts() const { return 3; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_CallRuntime; }
  virtual int            reloc() const;
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

class CallLeafDirect_mtctrNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return CallLeafDirect_mtctr_rule; }
  virtual int            ins_num_consts() const { return 1; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
public:
  CallLeafDirect_mtctrNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(CallLeafDirect_mtctrNode); }
  friend MachNode *State::MachNodeGenerator(int opcode);
  // Rematerialize CallLeafDirect_mtctr
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "CallLeafDirect_mtctr";}
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return CallLeafDirect_rule; }
  virtual void           method_set( intptr_t method );
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
  virtual int            ideal_Opcode() const { return Op_CallLeaf; }
  virtual int            reloc() const;
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

class CallLeafDirect_ExNode : public MachCallLeafNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return CallLeafDirect_Ex_rule; }
  virtual void           method_set( intptr_t method );
  virtual int            ins_num_consts() const { return 3; }
  virtual bool           requires_postalloc_expand() const { return true; }
  virtual void           postalloc_expand(GrowableArray <Node *> *nodes, PhaseRegAlloc *ra_);
  virtual int            ideal_Opcode() const { return Op_CallLeaf; }
  virtual uint           mach_constant_base_node_input() const { return req()-1; }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 1; }
public:
  CallLeafDirect_ExNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(CallLeafDirect_ExNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "CallLeafDirect_Ex";}
#endif
};

class CallLeafNoFPDirect_ExNode : public MachCallLeafNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return CallLeafNoFPDirect_Ex_rule; }
  virtual void           method_set( intptr_t method );
  virtual int            ins_num_consts() const { return 3; }
  virtual bool           requires_postalloc_expand() const { return true; }
  virtual void           postalloc_expand(GrowableArray <Node *> *nodes, PhaseRegAlloc *ra_);
  virtual int            ideal_Opcode() const { return Op_CallLeafNoFP; }
  virtual uint           mach_constant_base_node_input() const { return req()-1; }
  virtual int            reloc() const;
  virtual uint           oper_input_base() const { return 1; }
public:
  CallLeafNoFPDirect_ExNode() {  _num_opnds = 2; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(CallLeafNoFPDirect_ExNode); }
  virtual MachNode      *Expand(State *state, Node_List &proj_list, Node* mem);
  friend MachNode *State::MachNodeGenerator(int opcode);
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "CallLeafNoFPDirect_Ex";}
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return TailCalljmpInd_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return Ret_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return tailjmpInd_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return CreateException_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return RethrowException_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return ShouldNotReachHere_rule; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return tlsLoadP_rule; }
  virtual int            ins_should_rematerialize() const { return true; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
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

class endGroupNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return endGroup_rule; }
  virtual int            ins_is_nop() const { return true; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
public:
  endGroupNode() {  _num_opnds = 1; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(endGroupNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "endGroup";}
#endif
};

class fxNopNode : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return fxNop_rule; }
  virtual int            ins_is_nop() const { return true; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
public:
  fxNopNode() {  _num_opnds = 1; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(fxNopNode); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "fxNop";}
#endif
};

class fpNop0Node : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return fpNop0_rule; }
  virtual int            ins_is_nop() const { return true; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
public:
  fpNop0Node() {  _num_opnds = 1; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(fpNop0Node); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "fpNop0";}
#endif
};

class fpNop1Node : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return fpNop1_rule; }
  virtual int            ins_is_nop() const { return true; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
public:
  fpNop1Node() {  _num_opnds = 1; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(fpNop1Node); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "fpNop1";}
#endif
};

class brNop0Node : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return brNop0_rule; }
  virtual int            ins_is_nop() const { return true; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
public:
  brNop0Node() {  _num_opnds = 1; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(brNop0Node); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "brNop0";}
#endif
};

class brNop1Node : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return brNop1_rule; }
  virtual int            ins_is_nop() const { return true; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
public:
  brNop1Node() {  _num_opnds = 1; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(brNop1Node); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "brNop1";}
#endif
};

class brNop2Node : public MachNode { 
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
private:
  virtual const RegMask &out_RegMask() const;
  virtual uint           rule() const { return brNop2_rule; }
  virtual int            ins_is_nop() const { return true; }
  virtual void           emit(CodeBuffer &cbuf, PhaseRegAlloc *ra_) const;
  virtual uint           size(PhaseRegAlloc *ra_) const;
public:
  brNop2Node() {  _num_opnds = 1; _opnds = _opnd_array; }
  virtual uint           size_of() const { return sizeof(brNop2Node); }
  static  const Pipeline *pipeline_class();
  virtual const Pipeline *pipeline() const;
#ifndef PRODUCT
  virtual void           format(PhaseRegAlloc *ra, outputStream *st) const;
  virtual const char    *Name() const { return "brNop2";}
#endif
};

//HeaderForm

#line 977 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"

  // Header information of the source block.
  // Method declarations/definitions which are used outside
  // the ad-scope can conveniently be defined here.
  //
  // To keep related declarations/definitions/uses close together,
  // we switch between source %{ }% and source_hpp %{ }% freely as needed.

  // Returns true if Node n is followed by a MemBar node that
  // will do an acquire. If so, this node must not do the acquire
  // operation.
  bool followed_by_acquire(const Node *n);

#line 22379 "ad_ppc.hpp"


//HeaderForm

#line 1189 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"


//--------------------------------------------------------------
//---<  Used for optimization in Compile::Shorten_branches  >---
//--------------------------------------------------------------

class CallStubImpl {

 public:

  // Emit call stub, compiled java to interpreter.
  static void emit_trampoline_stub(MacroAssembler &_masm, int destination_toc_offset, int insts_call_instruction_offset);

  // Size of call trampoline stub.
  // This doesn't need to be accurate to the byte, but it
  // must be larger than or equal to the real size of the stub.
  static uint size_call_trampoline() {
    return MacroAssembler::trampoline_stub_size;
  }

  // number of relocations needed by a call trampoline stub
  static uint reloc_call_trampoline() {
    return 5;
  }

};


#line 22413 "ad_ppc.hpp"


//HeaderForm

#line 2146 "/usr/work/d038402/hg/jdk/src/hotspot/cpu/ppc/ppc.ad"


class HandlerImpl {

 public:

  static int emit_exception_handler(CodeBuffer &cbuf);
  static int emit_deopt_handler(CodeBuffer& cbuf);

  static uint size_exception_handler() {
    // The exception_handler is a b64_patchable.
    return MacroAssembler::b64_patchable_size;
  }

  static uint size_deopt_handler() {
    // The deopt_handler is a bl64_patchable.
    return MacroAssembler::bl64_patchable_size;
  }

};


#line 22441 "ad_ppc.hpp"


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
  BITS32_REG_RW,
  BITS32_REG_RO,
  RSCRATCH1_BITS32_REG,
  RSCRATCH2_BITS32_REG,
  RARG1_BITS32_REG,
  RARG2_BITS32_REG,
  RARG3_BITS32_REG,
  RARG4_BITS32_REG,
  RSCRATCH1_BITS64_REG,
  RSCRATCH2_BITS64_REG,
  RARG1_BITS64_REG,
  RARG2_BITS64_REG,
  RARG3_BITS64_REG,
  RARG4_BITS64_REG,
  THREAD_BITS64_REG,
  R19_BITS64_REG,
  BITS64_REG_RW,
  BITS64_REG_LEAF_CALL,
  BITS64_CONSTANT_TABLE_BASE,
  BITS64_REG_RO,
  INT_FLAGS,
  INT_FLAGS_RO,
  INT_FLAGS_CR0,
  INT_FLAGS_CR1,
  INT_FLAGS_CR6,
  CTR_REG,
  FLT_REG,
  DBL_REG,
  VS_REG,
  STACK_SLOTS,
  _last_Mach_Reg_Class
};

// Register masks, one for each register class.
extern const RegMask _BITS32_REG_RW_mask;
inline const RegMask &BITS32_REG_RW_mask() { return _BITS32_REG_RW_mask; }
extern const RegMask _BITS32_REG_RO_mask;
inline const RegMask &BITS32_REG_RO_mask() { return _BITS32_REG_RO_mask; }
extern const RegMask _RSCRATCH1_BITS32_REG_mask;
inline const RegMask &RSCRATCH1_BITS32_REG_mask() { return _RSCRATCH1_BITS32_REG_mask; }
extern const RegMask _RSCRATCH2_BITS32_REG_mask;
inline const RegMask &RSCRATCH2_BITS32_REG_mask() { return _RSCRATCH2_BITS32_REG_mask; }
extern const RegMask _RARG1_BITS32_REG_mask;
inline const RegMask &RARG1_BITS32_REG_mask() { return _RARG1_BITS32_REG_mask; }
extern const RegMask _RARG2_BITS32_REG_mask;
inline const RegMask &RARG2_BITS32_REG_mask() { return _RARG2_BITS32_REG_mask; }
extern const RegMask _RARG3_BITS32_REG_mask;
inline const RegMask &RARG3_BITS32_REG_mask() { return _RARG3_BITS32_REG_mask; }
extern const RegMask _RARG4_BITS32_REG_mask;
inline const RegMask &RARG4_BITS32_REG_mask() { return _RARG4_BITS32_REG_mask; }
extern const RegMask _RSCRATCH1_BITS64_REG_mask;
inline const RegMask &RSCRATCH1_BITS64_REG_mask() { return _RSCRATCH1_BITS64_REG_mask; }
extern const RegMask _RSCRATCH2_BITS64_REG_mask;
inline const RegMask &RSCRATCH2_BITS64_REG_mask() { return _RSCRATCH2_BITS64_REG_mask; }
extern const RegMask _RARG1_BITS64_REG_mask;
inline const RegMask &RARG1_BITS64_REG_mask() { return _RARG1_BITS64_REG_mask; }
extern const RegMask _RARG2_BITS64_REG_mask;
inline const RegMask &RARG2_BITS64_REG_mask() { return _RARG2_BITS64_REG_mask; }
extern const RegMask _RARG3_BITS64_REG_mask;
inline const RegMask &RARG3_BITS64_REG_mask() { return _RARG3_BITS64_REG_mask; }
extern const RegMask _RARG4_BITS64_REG_mask;
inline const RegMask &RARG4_BITS64_REG_mask() { return _RARG4_BITS64_REG_mask; }
extern const RegMask _THREAD_BITS64_REG_mask;
inline const RegMask &THREAD_BITS64_REG_mask() { return _THREAD_BITS64_REG_mask; }
extern const RegMask _R19_BITS64_REG_mask;
inline const RegMask &R19_BITS64_REG_mask() { return _R19_BITS64_REG_mask; }
extern const RegMask _BITS64_REG_RW_mask;
inline const RegMask &BITS64_REG_RW_mask() { return _BITS64_REG_RW_mask; }
extern const RegMask _BITS64_REG_LEAF_CALL_mask;
inline const RegMask &BITS64_REG_LEAF_CALL_mask() { return _BITS64_REG_LEAF_CALL_mask; }
extern const RegMask _BITS64_CONSTANT_TABLE_BASE_mask;
inline const RegMask &BITS64_CONSTANT_TABLE_BASE_mask() { return _BITS64_CONSTANT_TABLE_BASE_mask; }
extern const RegMask _BITS64_REG_RO_mask;
inline const RegMask &BITS64_REG_RO_mask() { return _BITS64_REG_RO_mask; }
extern const RegMask _INT_FLAGS_mask;
inline const RegMask &INT_FLAGS_mask() { return _INT_FLAGS_mask; }
extern const RegMask _INT_FLAGS_RO_mask;
inline const RegMask &INT_FLAGS_RO_mask() { return _INT_FLAGS_RO_mask; }
extern const RegMask _INT_FLAGS_CR0_mask;
inline const RegMask &INT_FLAGS_CR0_mask() { return _INT_FLAGS_CR0_mask; }
extern const RegMask _INT_FLAGS_CR1_mask;
inline const RegMask &INT_FLAGS_CR1_mask() { return _INT_FLAGS_CR1_mask; }
extern const RegMask _INT_FLAGS_CR6_mask;
inline const RegMask &INT_FLAGS_CR6_mask() { return _INT_FLAGS_CR6_mask; }
extern const RegMask _CTR_REG_mask;
inline const RegMask &CTR_REG_mask() { return _CTR_REG_mask; }
extern const RegMask _FLT_REG_mask;
inline const RegMask &FLT_REG_mask() { return _FLT_REG_mask; }
extern const RegMask _DBL_REG_mask;
inline const RegMask &DBL_REG_mask() { return _DBL_REG_mask; }
extern const RegMask _VS_REG_mask;
inline const RegMask &VS_REG_mask() { return _VS_REG_mask; }
extern const RegMask _STACK_SLOTS_mask;
inline const RegMask &STACK_SLOTS_mask() { return _STACK_SLOTS_mask; }
extern const RegMask _STACK_OR_STACK_SLOTS_mask;
inline const RegMask &STACK_OR_STACK_SLOTS_mask() { return _STACK_OR_STACK_SLOTS_mask; }

#endif // GENERATED_ADFILES_AD_HPP
