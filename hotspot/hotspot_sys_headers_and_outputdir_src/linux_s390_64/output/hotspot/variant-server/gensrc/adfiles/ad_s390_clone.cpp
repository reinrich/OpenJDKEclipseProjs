#line 1 "ad_s390_clone.cpp"
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
MachOper *immB_minus1Oper::clone() const {
  return new immB_minus1Oper(_c0);
}
MachOper *immB_n0m1Oper::clone() const {
  return new immB_n0m1Oper(_c0);
}
MachOper *immS_minus1Oper::clone() const {
  return new immS_minus1Oper(_c0);
}
MachOper *immS_n0m1Oper::clone() const {
  return new immS_n0m1Oper(_c0);
}
MachOper *immIOper::clone() const {
  return new immIOper(_c0);
}
MachOper *immI20Oper::clone() const {
  return new immI20Oper(_c0);
}
MachOper *immI16Oper::clone() const {
  return new immI16Oper(_c0);
}
MachOper *immI8Oper::clone() const {
  return new immI8Oper(_c0);
}
MachOper *immI_0Oper::clone() const {
  return new immI_0Oper(_c0);
}
MachOper *immI_minus1Oper::clone() const {
  return new immI_minus1Oper(_c0);
}
MachOper *immI_n0m1Oper::clone() const {
  return new immI_n0m1Oper(_c0);
}
MachOper *uimmIOper::clone() const {
  return new uimmIOper(_c0);
}
MachOper *uimmI16Oper::clone() const {
  return new uimmI16Oper(_c0);
}
MachOper *uimmI12Oper::clone() const {
  return new uimmI12Oper(_c0);
}
MachOper *uimmI8Oper::clone() const {
  return new uimmI8Oper(_c0);
}
MachOper *uimmI6Oper::clone() const {
  return new uimmI6Oper(_c0);
}
MachOper *uimmI5Oper::clone() const {
  return new uimmI5Oper(_c0);
}
MachOper *SSlenDWOper::clone() const {
  return new SSlenDWOper(_c0);
}
MachOper *immI_1Oper::clone() const {
  return new immI_1Oper(_c0);
}
MachOper *immI_16Oper::clone() const {
  return new immI_16Oper(_c0);
}
MachOper *immI_24Oper::clone() const {
  return new immI_24Oper(_c0);
}
MachOper *immI_255Oper::clone() const {
  return new immI_255Oper(_c0);
}
MachOper *immI_32_63Oper::clone() const {
  return new immI_32_63Oper(_c0);
}
MachOper *uimmI_LL1Oper::clone() const {
  return new uimmI_LL1Oper(_c0);
}
MachOper *uimmI_LH1Oper::clone() const {
  return new uimmI_LH1Oper(_c0);
}
MachOper *immLOper::clone() const {
  return new immLOper(_c0);
}
MachOper *immL32Oper::clone() const {
  return new immL32Oper(_c0);
}
MachOper *immL20Oper::clone() const {
  return new immL20Oper(_c0);
}
MachOper *immL16Oper::clone() const {
  return new immL16Oper(_c0);
}
MachOper *immL8Oper::clone() const {
  return new immL8Oper(_c0);
}
MachOper *uimmL32Oper::clone() const {
  return new uimmL32Oper(_c0);
}
MachOper *uimmL16Oper::clone() const {
  return new uimmL16Oper(_c0);
}
MachOper *uimmL12Oper::clone() const {
  return new uimmL12Oper(_c0);
}
MachOper *uimmL8Oper::clone() const {
  return new uimmL8Oper(_c0);
}
MachOper *immL_FFOper::clone() const {
  return new immL_FFOper(_c0);
}
MachOper *immL_FFFFOper::clone() const {
  return new immL_FFFFOper(_c0);
}
MachOper *immL_FFFFFFFFOper::clone() const {
  return new immL_FFFFFFFFOper(_c0);
}
MachOper *immL_0Oper::clone() const {
  return new immL_0Oper(_c0);
}
MachOper *uimmL_LL1Oper::clone() const {
  return new uimmL_LL1Oper(_c0);
}
MachOper *uimmL_LH1Oper::clone() const {
  return new uimmL_LH1Oper(_c0);
}
MachOper *uimmL_HL1Oper::clone() const {
  return new uimmL_HL1Oper(_c0);
}
MachOper *uimmL_HH1Oper::clone() const {
  return new uimmL_HH1Oper(_c0);
}
MachOper *immL_32bitsOper::clone() const {
  return new immL_32bitsOper(_c0);
}
MachOper *immPOper::clone() const {
  return new immPOper(_c0);
}
MachOper *immP32Oper::clone() const {
  return new immP32Oper(_c0);
}
MachOper *immP16Oper::clone() const {
  return new immP16Oper(_c0);
}
MachOper *immP8Oper::clone() const {
  return new immP8Oper(_c0);
}
MachOper *immP0Oper::clone() const {
  return new immP0Oper(_c0);
}
MachOper *immNOper::clone() const {
  return new immNOper(_c0);
}
MachOper *immNKlassOper::clone() const {
  return new immNKlassOper(_c0);
}
MachOper *immN8Oper::clone() const {
  return new immN8Oper(_c0);
}
MachOper *immN0Oper::clone() const {
  return new immN0Oper(_c0);
}
MachOper *immDOper::clone() const {
  return new immDOper(_c0);
}
MachOper *immDpm0Oper::clone() const {
  return new immDpm0Oper(_c0);
}
MachOper *immDp0Oper::clone() const {
  return new immDp0Oper(_c0);
}
MachOper *immFOper::clone() const {
  return new immFOper(_c0);
}
MachOper *immFpm0Oper::clone() const {
  return new immFpm0Oper(_c0);
}
MachOper *immFp0Oper::clone() const {
  return new immFp0Oper(_c0);
}
MachOper *iRegIOper::clone() const {
  return new iRegIOper();
}
MachOper *noArg_iRegIOper::clone() const {
  return new noArg_iRegIOper();
}
MachOper *revenRegIOper::clone() const {
  return new revenRegIOper();
}
MachOper *roddRegIOper::clone() const {
  return new roddRegIOper();
}
MachOper *rarg1RegIOper::clone() const {
  return new rarg1RegIOper();
}
MachOper *rarg2RegIOper::clone() const {
  return new rarg2RegIOper();
}
MachOper *rarg3RegIOper::clone() const {
  return new rarg3RegIOper();
}
MachOper *rarg4RegIOper::clone() const {
  return new rarg4RegIOper();
}
MachOper *rarg5RegIOper::clone() const {
  return new rarg5RegIOper();
}
MachOper *noOdd_iRegIOper::clone() const {
  return new noOdd_iRegIOper();
}
MachOper *iRegPOper::clone() const {
  return new iRegPOper();
}
MachOper *threadRegPOper::clone() const {
  return new threadRegPOper();
}
MachOper *noArg_iRegPOper::clone() const {
  return new noArg_iRegPOper();
}
MachOper *rarg1RegPOper::clone() const {
  return new rarg1RegPOper();
}
MachOper *rarg2RegPOper::clone() const {
  return new rarg2RegPOper();
}
MachOper *rarg3RegPOper::clone() const {
  return new rarg3RegPOper();
}
MachOper *rarg4RegPOper::clone() const {
  return new rarg4RegPOper();
}
MachOper *rarg5RegPOper::clone() const {
  return new rarg5RegPOper();
}
MachOper *memoryRegPOper::clone() const {
  return new memoryRegPOper();
}
MachOper *revenRegPOper::clone() const {
  return new revenRegPOper();
}
MachOper *roddRegPOper::clone() const {
  return new roddRegPOper();
}
MachOper *lock_ptr_RegPOper::clone() const {
  return new lock_ptr_RegPOper();
}
MachOper *rscratch2RegPOper::clone() const {
  return new rscratch2RegPOper();
}
MachOper *iRegNOper::clone() const {
  return new iRegNOper();
}
MachOper *noArg_iRegNOper::clone() const {
  return new noArg_iRegNOper();
}
MachOper *rarg1RegNOper::clone() const {
  return new rarg1RegNOper();
}
MachOper *rarg2RegNOper::clone() const {
  return new rarg2RegNOper();
}
MachOper *rarg3RegNOper::clone() const {
  return new rarg3RegNOper();
}
MachOper *rarg4RegNOper::clone() const {
  return new rarg4RegNOper();
}
MachOper *rarg5RegNOper::clone() const {
  return new rarg5RegNOper();
}
MachOper *iRegLOper::clone() const {
  return new iRegLOper();
}
MachOper *revenRegLOper::clone() const {
  return new revenRegLOper();
}
MachOper *roddRegLOper::clone() const {
  return new roddRegLOper();
}
MachOper *rarg1RegLOper::clone() const {
  return new rarg1RegLOper();
}
MachOper *rarg5RegLOper::clone() const {
  return new rarg5RegLOper();
}
MachOper *flagsRegOper::clone() const {
  return new flagsRegOper();
}
MachOper *TD_flagsRegOper::clone() const {
  return new TD_flagsRegOper();
}
MachOper *regDOper::clone() const {
  return new regDOper();
}
MachOper *rscratchRegDOper::clone() const {
  return new rscratchRegDOper();
}
MachOper *regFOper::clone() const {
  return new regFOper();
}
MachOper *rscratchRegFOper::clone() const {
  return new rscratchRegFOper();
}
MachOper *inline_cache_regPOper::clone() const {
  return new inline_cache_regPOper();
}
MachOper *compiler_method_oop_regPOper::clone() const {
  return new compiler_method_oop_regPOper();
}
MachOper *interpreter_method_oop_regPOper::clone() const {
  return new interpreter_method_oop_regPOper();
}
MachOper *iRegP2NOper::clone() const {
  return new iRegP2NOper();
}
MachOper *iRegN2POper::clone() const {
  return new iRegN2POper();
}
MachOper *indirectOper::clone() const {
  return new indirectOper();
}
MachOper *indOffset20Oper::clone() const {
  return new indOffset20Oper(_c0);
}
MachOper *indOffset20NarrowOper::clone() const {
  return new indOffset20NarrowOper(_c0);
}
MachOper *indOffset12Oper::clone() const {
  return new indOffset12Oper(_c0);
}
MachOper *indOffset12NarrowOper::clone() const {
  return new indOffset12NarrowOper(_c0);
}
MachOper *indIndexOper::clone() const {
  return new indIndexOper();
}
MachOper *indOffset20indexOper::clone() const {
  return new indOffset20indexOper(_c0);
}
MachOper *indOffset20indexNarrowOper::clone() const {
  return new indOffset20indexNarrowOper(_c0);
}
MachOper *indOffset12indexOper::clone() const {
  return new indOffset12indexOper(_c0);
}
MachOper *indOffset12indexNarrowOper::clone() const {
  return new indOffset12indexNarrowOper(_c0);
}
MachOper *stackSlotIOper::clone() const {
  return new stackSlotIOper();
}
MachOper *stackSlotPOper::clone() const {
  return new stackSlotPOper();
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
MachOper *cmpOpTOper::clone() const {
  return new cmpOpTOper(_c0);
}
MachOper *cmpOpFOper::clone() const {
  return new cmpOpFOper(_c0);
}
MachOper *cmpOpOper::clone() const {
  return new cmpOpOper(_c0);
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
