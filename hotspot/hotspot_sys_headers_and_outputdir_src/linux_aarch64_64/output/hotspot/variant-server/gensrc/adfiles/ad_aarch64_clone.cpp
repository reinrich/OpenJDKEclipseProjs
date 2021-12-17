#line 1 "ad_aarch64_clone.cpp"
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
MachOper *UniverseOper::clone() const {
  return new UniverseOper();
}
MachOper *sRegIOper::clone() const {
  return new sRegIOper();
}
MachOper *sRegPOper::clone() const {
  return new sRegPOper();
}
MachOper *sRegFOper::clone() const {
  return new sRegFOper();
}
MachOper *sRegDOper::clone() const {
  return new sRegDOper();
}
MachOper *sRegLOper::clone() const {
  return new sRegLOper();
}
MachOper *immIOper::clone() const {
  return new immIOper(_c0);
}
MachOper *immI0Oper::clone() const {
  return new immI0Oper(_c0);
}
MachOper *immI_1Oper::clone() const {
  return new immI_1Oper(_c0);
}
MachOper *immI_M1Oper::clone() const {
  return new immI_M1Oper(_c0);
}
MachOper *immIExtOper::clone() const {
  return new immIExtOper(_c0);
}
MachOper *immI_gt_1Oper::clone() const {
  return new immI_gt_1Oper(_c0);
}
MachOper *immI_le_4Oper::clone() const {
  return new immI_le_4Oper(_c0);
}
MachOper *immI_31Oper::clone() const {
  return new immI_31Oper(_c0);
}
MachOper *immI_2Oper::clone() const {
  return new immI_2Oper(_c0);
}
MachOper *immI_4Oper::clone() const {
  return new immI_4Oper(_c0);
}
MachOper *immI_8Oper::clone() const {
  return new immI_8Oper(_c0);
}
MachOper *immI_16Oper::clone() const {
  return new immI_16Oper(_c0);
}
MachOper *immI_24Oper::clone() const {
  return new immI_24Oper(_c0);
}
MachOper *immI_32Oper::clone() const {
  return new immI_32Oper(_c0);
}
MachOper *immI_48Oper::clone() const {
  return new immI_48Oper(_c0);
}
MachOper *immI_56Oper::clone() const {
  return new immI_56Oper(_c0);
}
MachOper *immI_63Oper::clone() const {
  return new immI_63Oper(_c0);
}
MachOper *immI_64Oper::clone() const {
  return new immI_64Oper(_c0);
}
MachOper *immI_255Oper::clone() const {
  return new immI_255Oper(_c0);
}
MachOper *immI_65535Oper::clone() const {
  return new immI_65535Oper(_c0);
}
MachOper *immL_255Oper::clone() const {
  return new immL_255Oper(_c0);
}
MachOper *immL_65535Oper::clone() const {
  return new immL_65535Oper(_c0);
}
MachOper *immL_4294967295Oper::clone() const {
  return new immL_4294967295Oper(_c0);
}
MachOper *immL_bitmaskOper::clone() const {
  return new immL_bitmaskOper(_c0);
}
MachOper *immI_bitmaskOper::clone() const {
  return new immI_bitmaskOper(_c0);
}
MachOper *immL_positive_bitmaskIOper::clone() const {
  return new immL_positive_bitmaskIOper(_c0);
}
MachOper *immIScaleOper::clone() const {
  return new immIScaleOper(_c0);
}
MachOper *immI26Oper::clone() const {
  return new immI26Oper(_c0);
}
MachOper *immI19Oper::clone() const {
  return new immI19Oper(_c0);
}
MachOper *immIU12Oper::clone() const {
  return new immIU12Oper(_c0);
}
MachOper *immLU12Oper::clone() const {
  return new immLU12Oper(_c0);
}
MachOper *immIOffsetOper::clone() const {
  return new immIOffsetOper(_c0);
}
MachOper *immIOffset1Oper::clone() const {
  return new immIOffset1Oper(_c0);
}
MachOper *immIOffset2Oper::clone() const {
  return new immIOffset2Oper(_c0);
}
MachOper *immIOffset4Oper::clone() const {
  return new immIOffset4Oper(_c0);
}
MachOper *immIOffset8Oper::clone() const {
  return new immIOffset8Oper(_c0);
}
MachOper *immIOffset16Oper::clone() const {
  return new immIOffset16Oper(_c0);
}
MachOper *immLoffsetOper::clone() const {
  return new immLoffsetOper(_c0);
}
MachOper *immLoffset1Oper::clone() const {
  return new immLoffset1Oper(_c0);
}
MachOper *immLoffset2Oper::clone() const {
  return new immLoffset2Oper(_c0);
}
MachOper *immLoffset4Oper::clone() const {
  return new immLoffset4Oper(_c0);
}
MachOper *immLoffset8Oper::clone() const {
  return new immLoffset8Oper(_c0);
}
MachOper *immLoffset16Oper::clone() const {
  return new immLoffset16Oper(_c0);
}
MachOper *immI8Oper::clone() const {
  return new immI8Oper(_c0);
}
MachOper *immI8_shift8Oper::clone() const {
  return new immI8_shift8Oper(_c0);
}
MachOper *immL8_shift8Oper::clone() const {
  return new immL8_shift8Oper(_c0);
}
MachOper *immBAddSubVOper::clone() const {
  return new immBAddSubVOper(_c0);
}
MachOper *immIAddSubOper::clone() const {
  return new immIAddSubOper(_c0);
}
MachOper *immIAddSubVOper::clone() const {
  return new immIAddSubVOper(_c0);
}
MachOper *immBLogOper::clone() const {
  return new immBLogOper(_c0);
}
MachOper *immSLogOper::clone() const {
  return new immSLogOper(_c0);
}
MachOper *immILogOper::clone() const {
  return new immILogOper(_c0);
}
MachOper *immLOper::clone() const {
  return new immLOper(_c0);
}
MachOper *immL0Oper::clone() const {
  return new immL0Oper(_c0);
}
MachOper *immL_1Oper::clone() const {
  return new immL_1Oper(_c0);
}
MachOper *immL_M1Oper::clone() const {
  return new immL_M1Oper(_c0);
}
MachOper *immL_pc_offOper::clone() const {
  return new immL_pc_offOper(_c0);
}
MachOper *immLAddSubOper::clone() const {
  return new immLAddSubOper(_c0);
}
MachOper *immLAddSubVOper::clone() const {
  return new immLAddSubVOper(_c0);
}
MachOper *immLLogOper::clone() const {
  return new immLLogOper(_c0);
}
MachOper *immL_32bitsOper::clone() const {
  return new immL_32bitsOper(_c0);
}
MachOper *immPOper::clone() const {
  return new immPOper(_c0);
}
MachOper *immP0Oper::clone() const {
  return new immP0Oper(_c0);
}
MachOper *immP_1Oper::clone() const {
  return new immP_1Oper(_c0);
}
MachOper *immByteMapBaseOper::clone() const {
  return new immByteMapBaseOper(_c0);
}
MachOper *immP_M1Oper::clone() const {
  return new immP_M1Oper(_c0);
}
MachOper *immP_M2Oper::clone() const {
  return new immP_M2Oper(_c0);
}
MachOper *immDOper::clone() const {
  return new immDOper(_c0);
}
MachOper *immD0Oper::clone() const {
  return new immD0Oper(_c0);
}
MachOper *immDPackedOper::clone() const {
  return new immDPackedOper(_c0);
}
MachOper *immFOper::clone() const {
  return new immFOper(_c0);
}
MachOper *immF0Oper::clone() const {
  return new immF0Oper(_c0);
}
MachOper *immFPackedOper::clone() const {
  return new immFPackedOper(_c0);
}
MachOper *immNOper::clone() const {
  return new immNOper(_c0);
}
MachOper *immN0Oper::clone() const {
  return new immN0Oper(_c0);
}
MachOper *immNKlassOper::clone() const {
  return new immNKlassOper(_c0);
}
MachOper *iRegIOper::clone() const {
  return new iRegIOper();
}
MachOper *iRegINoSpOper::clone() const {
  return new iRegINoSpOper();
}
MachOper *iRegLOper::clone() const {
  return new iRegLOper();
}
MachOper *iRegLNoSpOper::clone() const {
  return new iRegLNoSpOper();
}
MachOper *iRegPOper::clone() const {
  return new iRegPOper();
}
MachOper *iRegPNoSpOper::clone() const {
  return new iRegPNoSpOper();
}
MachOper *iRegP_R0Oper::clone() const {
  return new iRegP_R0Oper();
}
MachOper *iRegP_R1Oper::clone() const {
  return new iRegP_R1Oper();
}
MachOper *iRegP_R2Oper::clone() const {
  return new iRegP_R2Oper();
}
MachOper *iRegP_R3Oper::clone() const {
  return new iRegP_R3Oper();
}
MachOper *iRegP_R4Oper::clone() const {
  return new iRegP_R4Oper();
}
MachOper *iRegP_R5Oper::clone() const {
  return new iRegP_R5Oper();
}
MachOper *iRegP_R10Oper::clone() const {
  return new iRegP_R10Oper();
}
MachOper *iRegL_R0Oper::clone() const {
  return new iRegL_R0Oper();
}
MachOper *iRegL_R2Oper::clone() const {
  return new iRegL_R2Oper();
}
MachOper *iRegL_R3Oper::clone() const {
  return new iRegL_R3Oper();
}
MachOper *iRegL_R11Oper::clone() const {
  return new iRegL_R11Oper();
}
MachOper *iRegP_FPOper::clone() const {
  return new iRegP_FPOper();
}
MachOper *iRegI_R0Oper::clone() const {
  return new iRegI_R0Oper();
}
MachOper *iRegI_R2Oper::clone() const {
  return new iRegI_R2Oper();
}
MachOper *iRegI_R3Oper::clone() const {
  return new iRegI_R3Oper();
}
MachOper *iRegI_R4Oper::clone() const {
  return new iRegI_R4Oper();
}
MachOper *iRegNOper::clone() const {
  return new iRegNOper();
}
MachOper *iRegN_R0Oper::clone() const {
  return new iRegN_R0Oper();
}
MachOper *iRegN_R2Oper::clone() const {
  return new iRegN_R2Oper();
}
MachOper *iRegN_R3Oper::clone() const {
  return new iRegN_R3Oper();
}
MachOper *iRegNNoSpOper::clone() const {
  return new iRegNNoSpOper();
}
MachOper *iRegIHeapbaseOper::clone() const {
  return new iRegIHeapbaseOper();
}
MachOper *vRegFOper::clone() const {
  return new vRegFOper();
}
MachOper *vRegDOper::clone() const {
  return new vRegDOper();
}
MachOper *vRegOper::clone() const {
  return new vRegOper();
}
MachOper *vecDOper::clone() const {
  return new vecDOper();
}
MachOper *vecXOper::clone() const {
  return new vecXOper();
}
MachOper *vRegD_V0Oper::clone() const {
  return new vRegD_V0Oper();
}
MachOper *vRegD_V1Oper::clone() const {
  return new vRegD_V1Oper();
}
MachOper *vRegD_V2Oper::clone() const {
  return new vRegD_V2Oper();
}
MachOper *vRegD_V3Oper::clone() const {
  return new vRegD_V3Oper();
}
MachOper *vRegD_V4Oper::clone() const {
  return new vRegD_V4Oper();
}
MachOper *vRegD_V5Oper::clone() const {
  return new vRegD_V5Oper();
}
MachOper *vRegD_V6Oper::clone() const {
  return new vRegD_V6Oper();
}
MachOper *vRegD_V7Oper::clone() const {
  return new vRegD_V7Oper();
}
MachOper *vRegD_V8Oper::clone() const {
  return new vRegD_V8Oper();
}
MachOper *vRegD_V9Oper::clone() const {
  return new vRegD_V9Oper();
}
MachOper *vRegD_V10Oper::clone() const {
  return new vRegD_V10Oper();
}
MachOper *vRegD_V11Oper::clone() const {
  return new vRegD_V11Oper();
}
MachOper *vRegD_V12Oper::clone() const {
  return new vRegD_V12Oper();
}
MachOper *vRegD_V13Oper::clone() const {
  return new vRegD_V13Oper();
}
MachOper *vRegD_V14Oper::clone() const {
  return new vRegD_V14Oper();
}
MachOper *vRegD_V15Oper::clone() const {
  return new vRegD_V15Oper();
}
MachOper *vRegD_V16Oper::clone() const {
  return new vRegD_V16Oper();
}
MachOper *vRegD_V17Oper::clone() const {
  return new vRegD_V17Oper();
}
MachOper *vRegD_V18Oper::clone() const {
  return new vRegD_V18Oper();
}
MachOper *vRegD_V19Oper::clone() const {
  return new vRegD_V19Oper();
}
MachOper *vRegD_V20Oper::clone() const {
  return new vRegD_V20Oper();
}
MachOper *vRegD_V21Oper::clone() const {
  return new vRegD_V21Oper();
}
MachOper *vRegD_V22Oper::clone() const {
  return new vRegD_V22Oper();
}
MachOper *vRegD_V23Oper::clone() const {
  return new vRegD_V23Oper();
}
MachOper *vRegD_V24Oper::clone() const {
  return new vRegD_V24Oper();
}
MachOper *vRegD_V25Oper::clone() const {
  return new vRegD_V25Oper();
}
MachOper *vRegD_V26Oper::clone() const {
  return new vRegD_V26Oper();
}
MachOper *vRegD_V27Oper::clone() const {
  return new vRegD_V27Oper();
}
MachOper *vRegD_V28Oper::clone() const {
  return new vRegD_V28Oper();
}
MachOper *vRegD_V29Oper::clone() const {
  return new vRegD_V29Oper();
}
MachOper *vRegD_V30Oper::clone() const {
  return new vRegD_V30Oper();
}
MachOper *vRegD_V31Oper::clone() const {
  return new vRegD_V31Oper();
}
MachOper *pRegOper::clone() const {
  return new pRegOper();
}
MachOper *pRegGovOper::clone() const {
  return new pRegGovOper();
}
MachOper *pRegGov_P0Oper::clone() const {
  return new pRegGov_P0Oper();
}
MachOper *pRegGov_P1Oper::clone() const {
  return new pRegGov_P1Oper();
}
MachOper *rFlagsRegOper::clone() const {
  return new rFlagsRegOper();
}
MachOper *rFlagsRegUOper::clone() const {
  return new rFlagsRegUOper();
}
MachOper *inline_cache_RegPOper::clone() const {
  return new inline_cache_RegPOper();
}
MachOper *thread_RegPOper::clone() const {
  return new thread_RegPOper();
}
MachOper *lr_RegPOper::clone() const {
  return new lr_RegPOper();
}
MachOper *indirectOper::clone() const {
  return new indirectOper();
}
MachOper *indIndexScaledI2LOper::clone() const {
  return new indIndexScaledI2LOper(_c0);
}
MachOper *indIndexScaledOper::clone() const {
  return new indIndexScaledOper(_c0);
}
MachOper *indIndexI2LOper::clone() const {
  return new indIndexI2LOper();
}
MachOper *indIndexOper::clone() const {
  return new indIndexOper();
}
MachOper *indOffIOper::clone() const {
  return new indOffIOper(_c0);
}
MachOper *indOffI1Oper::clone() const {
  return new indOffI1Oper(_c0);
}
MachOper *indOffI2Oper::clone() const {
  return new indOffI2Oper(_c0);
}
MachOper *indOffI4Oper::clone() const {
  return new indOffI4Oper(_c0);
}
MachOper *indOffI8Oper::clone() const {
  return new indOffI8Oper(_c0);
}
MachOper *indOffI16Oper::clone() const {
  return new indOffI16Oper(_c0);
}
MachOper *indOffLOper::clone() const {
  return new indOffLOper(_c0);
}
MachOper *indOffL1Oper::clone() const {
  return new indOffL1Oper(_c0);
}
MachOper *indOffL2Oper::clone() const {
  return new indOffL2Oper(_c0);
}
MachOper *indOffL4Oper::clone() const {
  return new indOffL4Oper(_c0);
}
MachOper *indOffL8Oper::clone() const {
  return new indOffL8Oper(_c0);
}
MachOper *indOffL16Oper::clone() const {
  return new indOffL16Oper(_c0);
}
MachOper *indirectNOper::clone() const {
  return new indirectNOper();
}
MachOper *indIndexScaledI2LNOper::clone() const {
  return new indIndexScaledI2LNOper(_c0);
}
MachOper *indIndexScaledNOper::clone() const {
  return new indIndexScaledNOper(_c0);
}
MachOper *indIndexI2LNOper::clone() const {
  return new indIndexI2LNOper();
}
MachOper *indIndexNOper::clone() const {
  return new indIndexNOper();
}
MachOper *indOffINOper::clone() const {
  return new indOffINOper(_c0);
}
MachOper *indOffLNOper::clone() const {
  return new indOffLNOper(_c0);
}
MachOper *thread_anchor_pcOper::clone() const {
  return new thread_anchor_pcOper(_c0);
}
MachOper *stackSlotPOper::clone() const {
  return new stackSlotPOper();
}
MachOper *stackSlotIOper::clone() const {
  return new stackSlotIOper();
}
MachOper *stackSlotFOper::clone() const {
  return new stackSlotFOper();
}
MachOper *stackSlotDOper::clone() const {
  return new stackSlotDOper();
}
MachOper *stackSlotLOper::clone() const {
  return new stackSlotLOper();
}
MachOper *cmpOpOper::clone() const {
  return new cmpOpOper(_c0);
}
MachOper *cmpOpUOper::clone() const {
  return new cmpOpUOper(_c0);
}
MachOper *cmpOpEqNeOper::clone() const {
  return new cmpOpEqNeOper(_c0);
}
MachOper *cmpOpLtGeOper::clone() const {
  return new cmpOpLtGeOper(_c0);
}
MachOper *cmpOpUEqNeLtGeOper::clone() const {
  return new cmpOpUEqNeLtGeOper(_c0);
}
MachOper *iRegL2IOper::clone() const {
  return new iRegL2IOper();
}
MachOper *vmemA_immIOffset4Oper::clone() const {
  return new vmemA_immIOffset4Oper(_c0);
}
MachOper *vmemA_immLOffset4Oper::clone() const {
  return new vmemA_immLOffset4Oper(_c0);
}
MachOper *vmemA_indOffI4Oper::clone() const {
  return new vmemA_indOffI4Oper(_c0);
}
MachOper *vmemA_indOffL4Oper::clone() const {
  return new vmemA_indOffL4Oper(_c0);
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
