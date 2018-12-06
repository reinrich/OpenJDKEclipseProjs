#line 1 "ad_ppc_clone.cpp"
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

#include "precompiled.hpp"
#include "adfiles/ad_ppc.hpp"
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
MachOper *vecXOper::clone() const {
  return new vecXOper();
}
MachOper *immIOper::clone() const {
  return new immIOper(_c0);
}
MachOper *immI8Oper::clone() const {
  return new immI8Oper(_c0);
}
MachOper *immI16Oper::clone() const {
  return new immI16Oper(_c0);
}
MachOper *immIhi16Oper::clone() const {
  return new immIhi16Oper(_c0);
}
MachOper *immInegpow2Oper::clone() const {
  return new immInegpow2Oper(_c0);
}
MachOper *immIpow2minus1Oper::clone() const {
  return new immIpow2minus1Oper(_c0);
}
MachOper *immIpowerOf2Oper::clone() const {
  return new immIpowerOf2Oper(_c0);
}
MachOper *uimmI5Oper::clone() const {
  return new uimmI5Oper(_c0);
}
MachOper *uimmI6Oper::clone() const {
  return new uimmI6Oper(_c0);
}
MachOper *uimmI6_ge32Oper::clone() const {
  return new uimmI6_ge32Oper(_c0);
}
MachOper *uimmI15Oper::clone() const {
  return new uimmI15Oper(_c0);
}
MachOper *uimmI16Oper::clone() const {
  return new uimmI16Oper(_c0);
}
MachOper *immI_0Oper::clone() const {
  return new immI_0Oper(_c0);
}
MachOper *immI_1Oper::clone() const {
  return new immI_1Oper(_c0);
}
MachOper *immI_minus1Oper::clone() const {
  return new immI_minus1Oper(_c0);
}
MachOper *immI_16Oper::clone() const {
  return new immI_16Oper(_c0);
}
MachOper *immI_24Oper::clone() const {
  return new immI_24Oper(_c0);
}
MachOper *immNOper::clone() const {
  return new immNOper(_c0);
}
MachOper *immN_0Oper::clone() const {
  return new immN_0Oper(_c0);
}
MachOper *immNKlassOper::clone() const {
  return new immNKlassOper(_c0);
}
MachOper *immNKlass_NMOper::clone() const {
  return new immNKlass_NMOper(_c0);
}
MachOper *immPOper::clone() const {
  return new immPOper(_c0);
}
MachOper *immP_NMOper::clone() const {
  return new immP_NMOper(_c0);
}
MachOper *immP_0Oper::clone() const {
  return new immP_0Oper(_c0);
}
MachOper *immP_0or1Oper::clone() const {
  return new immP_0or1Oper(_c0);
}
MachOper *immLOper::clone() const {
  return new immLOper(_c0);
}
MachOper *immLmax30Oper::clone() const {
  return new immLmax30Oper(_c0);
}
MachOper *immL16Oper::clone() const {
  return new immL16Oper(_c0);
}
MachOper *immL16Alg4Oper::clone() const {
  return new immL16Alg4Oper(_c0);
}
MachOper *immL32hi16Oper::clone() const {
  return new immL32hi16Oper(_c0);
}
MachOper *immL32Oper::clone() const {
  return new immL32Oper(_c0);
}
MachOper *immLhighest16Oper::clone() const {
  return new immLhighest16Oper(_c0);
}
MachOper *immLnegpow2Oper::clone() const {
  return new immLnegpow2Oper(_c0);
}
MachOper *immLpow2minus1Oper::clone() const {
  return new immLpow2minus1Oper(_c0);
}
MachOper *immL_0Oper::clone() const {
  return new immL_0Oper(_c0);
}
MachOper *immL_minus1Oper::clone() const {
  return new immL_minus1Oper(_c0);
}
MachOper *immL_32bitsOper::clone() const {
  return new immL_32bitsOper(_c0);
}
MachOper *uimmL16Oper::clone() const {
  return new uimmL16Oper(_c0);
}
MachOper *immFOper::clone() const {
  return new immFOper(_c0);
}
MachOper *immF_0Oper::clone() const {
  return new immF_0Oper(_c0);
}
MachOper *immDOper::clone() const {
  return new immDOper(_c0);
}
MachOper *iRegIdstOper::clone() const {
  return new iRegIdstOper();
}
MachOper *iRegIsrcOper::clone() const {
  return new iRegIsrcOper();
}
MachOper *rscratch1RegIOper::clone() const {
  return new rscratch1RegIOper();
}
MachOper *rscratch2RegIOper::clone() const {
  return new rscratch2RegIOper();
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
MachOper *rarg1RegLOper::clone() const {
  return new rarg1RegLOper();
}
MachOper *rarg2RegLOper::clone() const {
  return new rarg2RegLOper();
}
MachOper *rarg3RegLOper::clone() const {
  return new rarg3RegLOper();
}
MachOper *rarg4RegLOper::clone() const {
  return new rarg4RegLOper();
}
MachOper *iRegPdstOper::clone() const {
  return new iRegPdstOper();
}
MachOper *iRegPdstNoScratchOper::clone() const {
  return new iRegPdstNoScratchOper();
}
MachOper *iRegPsrcOper::clone() const {
  return new iRegPsrcOper();
}
MachOper *threadRegPOper::clone() const {
  return new threadRegPOper();
}
MachOper *rscratch1RegPOper::clone() const {
  return new rscratch1RegPOper();
}
MachOper *rscratch2RegPOper::clone() const {
  return new rscratch2RegPOper();
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
MachOper *iRegNsrcOper::clone() const {
  return new iRegNsrcOper();
}
MachOper *iRegNdstOper::clone() const {
  return new iRegNdstOper();
}
MachOper *iRegLdstOper::clone() const {
  return new iRegLdstOper();
}
MachOper *iRegLsrcOper::clone() const {
  return new iRegLsrcOper();
}
MachOper *iRegL2IsrcOper::clone() const {
  return new iRegL2IsrcOper();
}
MachOper *rscratch1RegLOper::clone() const {
  return new rscratch1RegLOper();
}
MachOper *rscratch2RegLOper::clone() const {
  return new rscratch2RegLOper();
}
MachOper *flagsRegOper::clone() const {
  return new flagsRegOper();
}
MachOper *flagsRegSrcOper::clone() const {
  return new flagsRegSrcOper();
}
MachOper *flagsRegCR0Oper::clone() const {
  return new flagsRegCR0Oper();
}
MachOper *flagsRegCR1Oper::clone() const {
  return new flagsRegCR1Oper();
}
MachOper *flagsRegCR6Oper::clone() const {
  return new flagsRegCR6Oper();
}
MachOper *regCTROper::clone() const {
  return new regCTROper();
}
MachOper *regDOper::clone() const {
  return new regDOper();
}
MachOper *regFOper::clone() const {
  return new regFOper();
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
MachOper *iRegN2P_klassOper::clone() const {
  return new iRegN2P_klassOper();
}
MachOper *indirectOper::clone() const {
  return new indirectOper();
}
MachOper *indOffset16Oper::clone() const {
  return new indOffset16Oper(_c0);
}
MachOper *indOffset16Alg4Oper::clone() const {
  return new indOffset16Alg4Oper(_c0);
}
MachOper *indirectNarrowOper::clone() const {
  return new indirectNarrowOper();
}
MachOper *indirectNarrow_klassOper::clone() const {
  return new indirectNarrow_klassOper();
}
MachOper *indOffset16NarrowOper::clone() const {
  return new indOffset16NarrowOper(_c0);
}
MachOper *indOffset16Narrow_klassOper::clone() const {
  return new indOffset16Narrow_klassOper(_c0);
}
MachOper *indOffset16NarrowAlg4Oper::clone() const {
  return new indOffset16NarrowAlg4Oper(_c0);
}
MachOper *indOffset16NarrowAlg4_klassOper::clone() const {
  return new indOffset16NarrowAlg4_klassOper(_c0);
}
MachOper *stackSlotIOper::clone() const {
  return new stackSlotIOper();
}
MachOper *stackSlotLOper::clone() const {
  return new stackSlotLOper();
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
// Check adlc -DPPC64=1
#ifndef PPC64
#  error "PPC64 must be defined"
#endif // PPC64
// Check adlc -D_LP64=1
#ifndef _LP64
#  error "_LP64 must be defined"
#endif // _LP64
