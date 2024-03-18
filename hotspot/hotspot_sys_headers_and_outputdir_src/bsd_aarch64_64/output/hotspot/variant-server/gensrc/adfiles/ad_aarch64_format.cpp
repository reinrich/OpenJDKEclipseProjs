#line 1 "ad_aarch64_format.cpp"
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
#include "compiler/oopMap.hpp"

#ifndef PRODUCT
void UniverseOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print("$$univ");
}
void UniverseOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print("$$univ");
}
#endif

#ifndef PRODUCT
void sRegIOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
}
void sRegIOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
}
#endif

#ifndef PRODUCT
void sRegPOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
}
void sRegPOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
}
#endif

#ifndef PRODUCT
void sRegFOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
}
void sRegFOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
}
#endif

#ifndef PRODUCT
void sRegDOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
}
void sRegDOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
}
#endif

#ifndef PRODUCT
void sRegLOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
}
void sRegLOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
}
#endif

#ifndef PRODUCT
void immIOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print("#%d", _c0);
}
void immIOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print("#%d", _c0);
}
#endif

#ifndef PRODUCT
void immI0Oper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print("#%d", _c0);
}
void immI0Oper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print("#%d", _c0);
}
#endif

#ifndef PRODUCT
void immI_1Oper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print("#%d", _c0);
}
void immI_1Oper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print("#%d", _c0);
}
#endif

#ifndef PRODUCT
void immI_M1Oper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print("#%d", _c0);
}
void immI_M1Oper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print("#%d", _c0);
}
#endif

#ifndef PRODUCT
void immIExtOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print("#%d", _c0);
}
void immIExtOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print("#%d", _c0);
}
#endif

#ifndef PRODUCT
void immI_gt_1Oper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print("#%d", _c0);
}
void immI_gt_1Oper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print("#%d", _c0);
}
#endif

#ifndef PRODUCT
void immI_le_4Oper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print("#%d", _c0);
}
void immI_le_4Oper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print("#%d", _c0);
}
#endif

#ifndef PRODUCT
void immI_16Oper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print("#%d", _c0);
}
void immI_16Oper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print("#%d", _c0);
}
#endif

#ifndef PRODUCT
void immI_24Oper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print("#%d", _c0);
}
void immI_24Oper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print("#%d", _c0);
}
#endif

#ifndef PRODUCT
void immI_32Oper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print("#%d", _c0);
}
void immI_32Oper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print("#%d", _c0);
}
#endif

#ifndef PRODUCT
void immI_48Oper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print("#%d", _c0);
}
void immI_48Oper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print("#%d", _c0);
}
#endif

#ifndef PRODUCT
void immI_56Oper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print("#%d", _c0);
}
void immI_56Oper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print("#%d", _c0);
}
#endif

#ifndef PRODUCT
void immI_255Oper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print("#%d", _c0);
}
void immI_255Oper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print("#%d", _c0);
}
#endif

#ifndef PRODUCT
void immI_65535Oper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print("#%d", _c0);
}
void immI_65535Oper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print("#%d", _c0);
}
#endif

#ifndef PRODUCT
void immI_positiveOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print("#%d", _c0);
}
void immI_positiveOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print("#%d", _c0);
}
#endif

#ifndef PRODUCT
void immI_cmp_condOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print("#%d", _c0);
}
void immI_cmp_condOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print("#%d", _c0);
}
#endif

#ifndef PRODUCT
void immI_cmpU_condOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print("#%d", _c0);
}
void immI_cmpU_condOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print("#%d", _c0);
}
#endif

#ifndef PRODUCT
void immL_255Oper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print("#" INT64_FORMAT, (int64_t)_c0);
}
void immL_255Oper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print("#" INT64_FORMAT, (int64_t)_c0);
}
#endif

#ifndef PRODUCT
void immL_65535Oper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print("#" INT64_FORMAT, (int64_t)_c0);
}
void immL_65535Oper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print("#" INT64_FORMAT, (int64_t)_c0);
}
#endif

#ifndef PRODUCT
void immL_4294967295Oper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print("#" INT64_FORMAT, (int64_t)_c0);
}
void immL_4294967295Oper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print("#" INT64_FORMAT, (int64_t)_c0);
}
#endif

#ifndef PRODUCT
void immL_bitmaskOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print("#" INT64_FORMAT, (int64_t)_c0);
}
void immL_bitmaskOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print("#" INT64_FORMAT, (int64_t)_c0);
}
#endif

#ifndef PRODUCT
void immI_bitmaskOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print("#%d", _c0);
}
void immI_bitmaskOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print("#%d", _c0);
}
#endif

#ifndef PRODUCT
void immL_positive_bitmaskIOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print("#" INT64_FORMAT, (int64_t)_c0);
}
void immL_positive_bitmaskIOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print("#" INT64_FORMAT, (int64_t)_c0);
}
#endif

#ifndef PRODUCT
void immIScaleOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print("#%d", _c0);
}
void immIScaleOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print("#%d", _c0);
}
#endif

#ifndef PRODUCT
void immI5Oper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print("#%d", _c0);
}
void immI5Oper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print("#%d", _c0);
}
#endif

#ifndef PRODUCT
void immIU7Oper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print("#%d", _c0);
}
void immIU7Oper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print("#%d", _c0);
}
#endif

#ifndef PRODUCT
void immIOffsetOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print("#%d", _c0);
}
void immIOffsetOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print("#%d", _c0);
}
#endif

#ifndef PRODUCT
void immIOffset1Oper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print("#%d", _c0);
}
void immIOffset1Oper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print("#%d", _c0);
}
#endif

#ifndef PRODUCT
void immIOffset2Oper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print("#%d", _c0);
}
void immIOffset2Oper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print("#%d", _c0);
}
#endif

#ifndef PRODUCT
void immIOffset4Oper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print("#%d", _c0);
}
void immIOffset4Oper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print("#%d", _c0);
}
#endif

#ifndef PRODUCT
void immIOffset8Oper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print("#%d", _c0);
}
void immIOffset8Oper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print("#%d", _c0);
}
#endif

#ifndef PRODUCT
void immIOffset16Oper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print("#%d", _c0);
}
void immIOffset16Oper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print("#%d", _c0);
}
#endif

#ifndef PRODUCT
void immLoffsetOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print("#" INT64_FORMAT, (int64_t)_c0);
}
void immLoffsetOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print("#" INT64_FORMAT, (int64_t)_c0);
}
#endif

#ifndef PRODUCT
void immLoffset1Oper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print("#" INT64_FORMAT, (int64_t)_c0);
}
void immLoffset1Oper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print("#" INT64_FORMAT, (int64_t)_c0);
}
#endif

#ifndef PRODUCT
void immLoffset2Oper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print("#" INT64_FORMAT, (int64_t)_c0);
}
void immLoffset2Oper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print("#" INT64_FORMAT, (int64_t)_c0);
}
#endif

#ifndef PRODUCT
void immLoffset4Oper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print("#" INT64_FORMAT, (int64_t)_c0);
}
void immLoffset4Oper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print("#" INT64_FORMAT, (int64_t)_c0);
}
#endif

#ifndef PRODUCT
void immLoffset8Oper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print("#" INT64_FORMAT, (int64_t)_c0);
}
void immLoffset8Oper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print("#" INT64_FORMAT, (int64_t)_c0);
}
#endif

#ifndef PRODUCT
void immLoffset16Oper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print("#" INT64_FORMAT, (int64_t)_c0);
}
void immLoffset16Oper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print("#" INT64_FORMAT, (int64_t)_c0);
}
#endif

#ifndef PRODUCT
void immL5Oper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print("#" INT64_FORMAT, (int64_t)_c0);
}
void immL5Oper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print("#" INT64_FORMAT, (int64_t)_c0);
}
#endif

#ifndef PRODUCT
void immLU7Oper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print("#" INT64_FORMAT, (int64_t)_c0);
}
void immLU7Oper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print("#" INT64_FORMAT, (int64_t)_c0);
}
#endif

#ifndef PRODUCT
void immI8Oper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print("#%d", _c0);
}
void immI8Oper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print("#%d", _c0);
}
#endif

#ifndef PRODUCT
void immI8_shift8Oper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print("#%d", _c0);
}
void immI8_shift8Oper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print("#%d", _c0);
}
#endif

#ifndef PRODUCT
void immL8_shift8Oper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print("#" INT64_FORMAT, (int64_t)_c0);
}
void immL8_shift8Oper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print("#" INT64_FORMAT, (int64_t)_c0);
}
#endif

#ifndef PRODUCT
void immBAddSubVOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print("#%d", _c0);
}
void immBAddSubVOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print("#%d", _c0);
}
#endif

#ifndef PRODUCT
void immIAddSubOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print("#%d", _c0);
}
void immIAddSubOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print("#%d", _c0);
}
#endif

#ifndef PRODUCT
void immIAddSubVOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print("#%d", _c0);
}
void immIAddSubVOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print("#%d", _c0);
}
#endif

#ifndef PRODUCT
void immBLogOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print("#%d", _c0);
}
void immBLogOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print("#%d", _c0);
}
#endif

#ifndef PRODUCT
void immSLogOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print("#%d", _c0);
}
void immSLogOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print("#%d", _c0);
}
#endif

#ifndef PRODUCT
void immILogOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print("#%d", _c0);
}
void immILogOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print("#%d", _c0);
}
#endif

#ifndef PRODUCT
void immLOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print("#" INT64_FORMAT, (int64_t)_c0);
}
void immLOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print("#" INT64_FORMAT, (int64_t)_c0);
}
#endif

#ifndef PRODUCT
void immL0Oper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print("#" INT64_FORMAT, (int64_t)_c0);
}
void immL0Oper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print("#" INT64_FORMAT, (int64_t)_c0);
}
#endif

#ifndef PRODUCT
void immL_M1Oper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print("#" INT64_FORMAT, (int64_t)_c0);
}
void immL_M1Oper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print("#" INT64_FORMAT, (int64_t)_c0);
}
#endif

#ifndef PRODUCT
void immLAddSubOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print("#" INT64_FORMAT, (int64_t)_c0);
}
void immLAddSubOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print("#" INT64_FORMAT, (int64_t)_c0);
}
#endif

#ifndef PRODUCT
void immLAddSubVOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print("#" INT64_FORMAT, (int64_t)_c0);
}
void immLAddSubVOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print("#" INT64_FORMAT, (int64_t)_c0);
}
#endif

#ifndef PRODUCT
void immLLogOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print("#" INT64_FORMAT, (int64_t)_c0);
}
void immLLogOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print("#" INT64_FORMAT, (int64_t)_c0);
}
#endif

#ifndef PRODUCT
void immL_32bitsOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print("#" INT64_FORMAT, (int64_t)_c0);
}
void immL_32bitsOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print("#" INT64_FORMAT, (int64_t)_c0);
}
#endif

#ifndef PRODUCT
void immPOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  if (_c0) _c0->dump_on(st);
}
void immPOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  if (_c0) _c0->dump_on(st);
}
#endif

#ifndef PRODUCT
void immP0Oper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  if (_c0) _c0->dump_on(st);
}
void immP0Oper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  if (_c0) _c0->dump_on(st);
}
#endif

#ifndef PRODUCT
void immP_1Oper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  if (_c0) _c0->dump_on(st);
}
void immP_1Oper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  if (_c0) _c0->dump_on(st);
}
#endif

#ifndef PRODUCT
void immByteMapBaseOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  if (_c0) _c0->dump_on(st);
}
void immByteMapBaseOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  if (_c0) _c0->dump_on(st);
}
#endif

#ifndef PRODUCT
void immDOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print("#%f", _c0);
}
void immDOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print("#%f", _c0);
}
#endif

#ifndef PRODUCT
void immD0Oper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print("#%f", _c0);
}
void immD0Oper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print("#%f", _c0);
}
#endif

#ifndef PRODUCT
void immDPackedOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print("#%f", _c0);
}
void immDPackedOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print("#%f", _c0);
}
#endif

#ifndef PRODUCT
void immFOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print("#%f", _c0);
}
void immFOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print("#%f", _c0);
}
#endif

#ifndef PRODUCT
void immF0Oper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print("#%f", _c0);
}
void immF0Oper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print("#%f", _c0);
}
#endif

#ifndef PRODUCT
void immFPackedOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print("#%f", _c0);
}
void immFPackedOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print("#%f", _c0);
}
#endif

#ifndef PRODUCT
void immNOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  if (_c0) _c0->dump_on(st);
}
void immNOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  if (_c0) _c0->dump_on(st);
}
#endif

#ifndef PRODUCT
void immN0Oper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  if (_c0) _c0->dump_on(st);
}
void immN0Oper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  if (_c0) _c0->dump_on(st);
}
#endif

#ifndef PRODUCT
void immNKlassOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  if (_c0) _c0->dump_on(st);
}
void immNKlassOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  if (_c0) _c0->dump_on(st);
}
#endif

#ifndef PRODUCT
void iRegIOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node,reg_str, sizeof(reg_str));
    st->print("%s",reg_str);
  }
}
void iRegIOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str,sizeof(reg_str));
    st->print("%s",reg_str);
  }
}
#endif

#ifndef PRODUCT
void iRegINoSpOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node,reg_str, sizeof(reg_str));
    st->print("%s",reg_str);
  }
}
void iRegINoSpOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str,sizeof(reg_str));
    st->print("%s",reg_str);
  }
}
#endif

#ifndef PRODUCT
void iRegLOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node,reg_str, sizeof(reg_str));
    st->print("%s",reg_str);
  }
}
void iRegLOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str,sizeof(reg_str));
    st->print("%s",reg_str);
  }
}
#endif

#ifndef PRODUCT
void iRegLNoSpOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node,reg_str, sizeof(reg_str));
    st->print("%s",reg_str);
  }
}
void iRegLNoSpOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str,sizeof(reg_str));
    st->print("%s",reg_str);
  }
}
#endif

#ifndef PRODUCT
void iRegPOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node,reg_str, sizeof(reg_str));
    st->print("%s",reg_str);
  }
}
void iRegPOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str,sizeof(reg_str));
    st->print("%s",reg_str);
  }
}
#endif

#ifndef PRODUCT
void iRegPNoSpOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node,reg_str, sizeof(reg_str));
    st->print("%s",reg_str);
  }
}
void iRegPNoSpOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str,sizeof(reg_str));
    st->print("%s",reg_str);
  }
}
#endif

#ifndef PRODUCT
void iRegP_R0Oper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node,reg_str, sizeof(reg_str));
    st->print("%s",reg_str);
  }
}
void iRegP_R0Oper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str,sizeof(reg_str));
    st->print("%s",reg_str);
  }
}
#endif

#ifndef PRODUCT
void iRegP_R1Oper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node,reg_str, sizeof(reg_str));
    st->print("%s",reg_str);
  }
}
void iRegP_R1Oper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str,sizeof(reg_str));
    st->print("%s",reg_str);
  }
}
#endif

#ifndef PRODUCT
void iRegP_R2Oper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node,reg_str, sizeof(reg_str));
    st->print("%s",reg_str);
  }
}
void iRegP_R2Oper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str,sizeof(reg_str));
    st->print("%s",reg_str);
  }
}
#endif

#ifndef PRODUCT
void iRegP_R3Oper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node,reg_str, sizeof(reg_str));
    st->print("%s",reg_str);
  }
}
void iRegP_R3Oper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str,sizeof(reg_str));
    st->print("%s",reg_str);
  }
}
#endif

#ifndef PRODUCT
void iRegP_R4Oper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node,reg_str, sizeof(reg_str));
    st->print("%s",reg_str);
  }
}
void iRegP_R4Oper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str,sizeof(reg_str));
    st->print("%s",reg_str);
  }
}
#endif

#ifndef PRODUCT
void iRegP_R5Oper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node,reg_str, sizeof(reg_str));
    st->print("%s",reg_str);
  }
}
void iRegP_R5Oper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str,sizeof(reg_str));
    st->print("%s",reg_str);
  }
}
#endif

#ifndef PRODUCT
void iRegP_R10Oper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node,reg_str, sizeof(reg_str));
    st->print("%s",reg_str);
  }
}
void iRegP_R10Oper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str,sizeof(reg_str));
    st->print("%s",reg_str);
  }
}
#endif

#ifndef PRODUCT
void iRegL_R0Oper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node,reg_str, sizeof(reg_str));
    st->print("%s",reg_str);
  }
}
void iRegL_R0Oper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str,sizeof(reg_str));
    st->print("%s",reg_str);
  }
}
#endif

#ifndef PRODUCT
void iRegL_R11Oper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node,reg_str, sizeof(reg_str));
    st->print("%s",reg_str);
  }
}
void iRegL_R11Oper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str,sizeof(reg_str));
    st->print("%s",reg_str);
  }
}
#endif

#ifndef PRODUCT
void iRegI_R0Oper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node,reg_str, sizeof(reg_str));
    st->print("%s",reg_str);
  }
}
void iRegI_R0Oper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str,sizeof(reg_str));
    st->print("%s",reg_str);
  }
}
#endif

#ifndef PRODUCT
void iRegI_R2Oper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node,reg_str, sizeof(reg_str));
    st->print("%s",reg_str);
  }
}
void iRegI_R2Oper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str,sizeof(reg_str));
    st->print("%s",reg_str);
  }
}
#endif

#ifndef PRODUCT
void iRegI_R3Oper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node,reg_str, sizeof(reg_str));
    st->print("%s",reg_str);
  }
}
void iRegI_R3Oper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str,sizeof(reg_str));
    st->print("%s",reg_str);
  }
}
#endif

#ifndef PRODUCT
void iRegI_R4Oper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node,reg_str, sizeof(reg_str));
    st->print("%s",reg_str);
  }
}
void iRegI_R4Oper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str,sizeof(reg_str));
    st->print("%s",reg_str);
  }
}
#endif

#ifndef PRODUCT
void iRegNOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node,reg_str, sizeof(reg_str));
    st->print("%s",reg_str);
  }
}
void iRegNOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str,sizeof(reg_str));
    st->print("%s",reg_str);
  }
}
#endif

#ifndef PRODUCT
void iRegNNoSpOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node,reg_str, sizeof(reg_str));
    st->print("%s",reg_str);
  }
}
void iRegNNoSpOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str,sizeof(reg_str));
    st->print("%s",reg_str);
  }
}
#endif

#ifndef PRODUCT
void vRegFOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node,reg_str, sizeof(reg_str));
    st->print("%s",reg_str);
  }
}
void vRegFOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str,sizeof(reg_str));
    st->print("%s",reg_str);
  }
}
#endif

#ifndef PRODUCT
void vRegDOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node,reg_str, sizeof(reg_str));
    st->print("%s",reg_str);
  }
}
void vRegDOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str,sizeof(reg_str));
    st->print("%s",reg_str);
  }
}
#endif

#ifndef PRODUCT
void vRegOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node,reg_str, sizeof(reg_str));
    st->print("%s",reg_str);
  }
}
void vRegOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str,sizeof(reg_str));
    st->print("%s",reg_str);
  }
}
#endif

#ifndef PRODUCT
void vecAOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node,reg_str, sizeof(reg_str));
    st->print("%s",reg_str);
  }
}
void vecAOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str,sizeof(reg_str));
    st->print("%s",reg_str);
  }
}
#endif

#ifndef PRODUCT
void vecDOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node,reg_str, sizeof(reg_str));
    st->print("%s",reg_str);
  }
}
void vecDOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str,sizeof(reg_str));
    st->print("%s",reg_str);
  }
}
#endif

#ifndef PRODUCT
void vecXOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node,reg_str, sizeof(reg_str));
    st->print("%s",reg_str);
  }
}
void vecXOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str,sizeof(reg_str));
    st->print("%s",reg_str);
  }
}
#endif

#ifndef PRODUCT
void vRegD_V0Oper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node,reg_str, sizeof(reg_str));
    st->print("%s",reg_str);
  }
}
void vRegD_V0Oper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str,sizeof(reg_str));
    st->print("%s",reg_str);
  }
}
#endif

#ifndef PRODUCT
void vRegD_V1Oper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node,reg_str, sizeof(reg_str));
    st->print("%s",reg_str);
  }
}
void vRegD_V1Oper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str,sizeof(reg_str));
    st->print("%s",reg_str);
  }
}
#endif

#ifndef PRODUCT
void vRegD_V2Oper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node,reg_str, sizeof(reg_str));
    st->print("%s",reg_str);
  }
}
void vRegD_V2Oper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str,sizeof(reg_str));
    st->print("%s",reg_str);
  }
}
#endif

#ifndef PRODUCT
void vRegD_V3Oper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node,reg_str, sizeof(reg_str));
    st->print("%s",reg_str);
  }
}
void vRegD_V3Oper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str,sizeof(reg_str));
    st->print("%s",reg_str);
  }
}
#endif

#ifndef PRODUCT
void vRegD_V4Oper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node,reg_str, sizeof(reg_str));
    st->print("%s",reg_str);
  }
}
void vRegD_V4Oper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str,sizeof(reg_str));
    st->print("%s",reg_str);
  }
}
#endif

#ifndef PRODUCT
void vRegD_V5Oper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node,reg_str, sizeof(reg_str));
    st->print("%s",reg_str);
  }
}
void vRegD_V5Oper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str,sizeof(reg_str));
    st->print("%s",reg_str);
  }
}
#endif

#ifndef PRODUCT
void vRegD_V6Oper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node,reg_str, sizeof(reg_str));
    st->print("%s",reg_str);
  }
}
void vRegD_V6Oper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str,sizeof(reg_str));
    st->print("%s",reg_str);
  }
}
#endif

#ifndef PRODUCT
void vRegD_V7Oper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node,reg_str, sizeof(reg_str));
    st->print("%s",reg_str);
  }
}
void vRegD_V7Oper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str,sizeof(reg_str));
    st->print("%s",reg_str);
  }
}
#endif

#ifndef PRODUCT
void pRegOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node,reg_str, sizeof(reg_str));
    st->print("%s",reg_str);
  }
}
void pRegOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str,sizeof(reg_str));
    st->print("%s",reg_str);
  }
}
#endif

#ifndef PRODUCT
void pRegGovOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node,reg_str, sizeof(reg_str));
    st->print("%s",reg_str);
  }
}
void pRegGovOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str,sizeof(reg_str));
    st->print("%s",reg_str);
  }
}
#endif

#ifndef PRODUCT
void pRegGov_P0Oper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node,reg_str, sizeof(reg_str));
    st->print("%s",reg_str);
  }
}
void pRegGov_P0Oper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str,sizeof(reg_str));
    st->print("%s",reg_str);
  }
}
#endif

#ifndef PRODUCT
void pRegGov_P1Oper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node,reg_str, sizeof(reg_str));
    st->print("%s",reg_str);
  }
}
void pRegGov_P1Oper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str,sizeof(reg_str));
    st->print("%s",reg_str);
  }
}
#endif

#ifndef PRODUCT
void rFlagsRegOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print_raw("RFLAGS");
}
void rFlagsRegOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print_raw("RFLAGS");
}
#endif

#ifndef PRODUCT
void rFlagsRegUOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print_raw("RFLAGSU");
}
void rFlagsRegUOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print_raw("RFLAGSU");
}
#endif

#ifndef PRODUCT
void inline_cache_RegPOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node,reg_str, sizeof(reg_str));
    st->print("%s",reg_str);
  }
}
void inline_cache_RegPOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str,sizeof(reg_str));
    st->print("%s",reg_str);
  }
}
#endif

#ifndef PRODUCT
void thread_RegPOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node,reg_str, sizeof(reg_str));
    st->print("%s",reg_str);
  }
}
void thread_RegPOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str,sizeof(reg_str));
    st->print("%s",reg_str);
  }
}
#endif

#ifndef PRODUCT
void indirectOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print_raw("[");
  { char reg_str[128];
    ra->dump_register(node,reg_str, sizeof(reg_str));
    st->print("%s",reg_str);
  }
  st->print_raw("]");
}
void indirectOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print_raw("[");
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str,sizeof(reg_str));
    st->print("%s",reg_str);
  }
  st->print_raw("]");
}
#endif

#ifndef PRODUCT
void indIndexScaledI2LOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node,reg_str, sizeof(reg_str));
    st->print("%s",reg_str);
  }
  st->print_raw(", ");
  { char reg_str[128];
    ra->dump_register(node,reg_str, sizeof(reg_str));
    st->print("%s",reg_str);
  }
  st->print_raw(" sxtw(");
  st->print("#%d", _c0);
  st->print_raw("), 0, I2L");
}
void indIndexScaledI2LOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str,sizeof(reg_str));
    st->print("%s",reg_str);
  }
  st->print_raw(", ");
  { char reg_str[128];
    ra->dump_register(node->in(idx+1),reg_str,sizeof(reg_str));
    st->print("%s",reg_str);
  }
  st->print_raw(" sxtw(");
  st->print("#%d", _c0);
  st->print_raw("), 0, I2L");
}
#endif

#ifndef PRODUCT
void indIndexScaledOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node,reg_str, sizeof(reg_str));
    st->print("%s",reg_str);
  }
  st->print_raw(", ");
  { char reg_str[128];
    ra->dump_register(node,reg_str, sizeof(reg_str));
    st->print("%s",reg_str);
  }
  st->print_raw(" lsl(");
  st->print("#%d", _c0);
  st->print_raw(")");
}
void indIndexScaledOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str,sizeof(reg_str));
    st->print("%s",reg_str);
  }
  st->print_raw(", ");
  { char reg_str[128];
    ra->dump_register(node->in(idx+1),reg_str,sizeof(reg_str));
    st->print("%s",reg_str);
  }
  st->print_raw(" lsl(");
  st->print("#%d", _c0);
  st->print_raw(")");
}
#endif

#ifndef PRODUCT
void indIndexI2LOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node,reg_str, sizeof(reg_str));
    st->print("%s",reg_str);
  }
  st->print_raw(", ");
  { char reg_str[128];
    ra->dump_register(node,reg_str, sizeof(reg_str));
    st->print("%s",reg_str);
  }
  st->print_raw(", 0, I2L");
}
void indIndexI2LOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str,sizeof(reg_str));
    st->print("%s",reg_str);
  }
  st->print_raw(", ");
  { char reg_str[128];
    ra->dump_register(node->in(idx+1),reg_str,sizeof(reg_str));
    st->print("%s",reg_str);
  }
  st->print_raw(", 0, I2L");
}
#endif

#ifndef PRODUCT
void indIndexOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node,reg_str, sizeof(reg_str));
    st->print("%s",reg_str);
  }
  st->print_raw(", ");
  { char reg_str[128];
    ra->dump_register(node,reg_str, sizeof(reg_str));
    st->print("%s",reg_str);
  }
}
void indIndexOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str,sizeof(reg_str));
    st->print("%s",reg_str);
  }
  st->print_raw(", ");
  { char reg_str[128];
    ra->dump_register(node->in(idx+1),reg_str,sizeof(reg_str));
    st->print("%s",reg_str);
  }
}
#endif

#ifndef PRODUCT
void indOffI1Oper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print_raw("[");
  { char reg_str[128];
    ra->dump_register(node,reg_str, sizeof(reg_str));
    st->print("%s",reg_str);
  }
  st->print_raw(", ");
  st->print("#%d", _c0);
  st->print_raw("]");
}
void indOffI1Oper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print_raw("[");
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str,sizeof(reg_str));
    st->print("%s",reg_str);
  }
  st->print_raw(", ");
  st->print("#%d", _c0);
  st->print_raw("]");
}
#endif

#ifndef PRODUCT
void indOffI2Oper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print_raw("[");
  { char reg_str[128];
    ra->dump_register(node,reg_str, sizeof(reg_str));
    st->print("%s",reg_str);
  }
  st->print_raw(", ");
  st->print("#%d", _c0);
  st->print_raw("]");
}
void indOffI2Oper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print_raw("[");
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str,sizeof(reg_str));
    st->print("%s",reg_str);
  }
  st->print_raw(", ");
  st->print("#%d", _c0);
  st->print_raw("]");
}
#endif

#ifndef PRODUCT
void indOffI4Oper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print_raw("[");
  { char reg_str[128];
    ra->dump_register(node,reg_str, sizeof(reg_str));
    st->print("%s",reg_str);
  }
  st->print_raw(", ");
  st->print("#%d", _c0);
  st->print_raw("]");
}
void indOffI4Oper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print_raw("[");
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str,sizeof(reg_str));
    st->print("%s",reg_str);
  }
  st->print_raw(", ");
  st->print("#%d", _c0);
  st->print_raw("]");
}
#endif

#ifndef PRODUCT
void indOffI8Oper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print_raw("[");
  { char reg_str[128];
    ra->dump_register(node,reg_str, sizeof(reg_str));
    st->print("%s",reg_str);
  }
  st->print_raw(", ");
  st->print("#%d", _c0);
  st->print_raw("]");
}
void indOffI8Oper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print_raw("[");
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str,sizeof(reg_str));
    st->print("%s",reg_str);
  }
  st->print_raw(", ");
  st->print("#%d", _c0);
  st->print_raw("]");
}
#endif

#ifndef PRODUCT
void indOffI16Oper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print_raw("[");
  { char reg_str[128];
    ra->dump_register(node,reg_str, sizeof(reg_str));
    st->print("%s",reg_str);
  }
  st->print_raw(", ");
  st->print("#%d", _c0);
  st->print_raw("]");
}
void indOffI16Oper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print_raw("[");
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str,sizeof(reg_str));
    st->print("%s",reg_str);
  }
  st->print_raw(", ");
  st->print("#%d", _c0);
  st->print_raw("]");
}
#endif

#ifndef PRODUCT
void indOffL1Oper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print_raw("[");
  { char reg_str[128];
    ra->dump_register(node,reg_str, sizeof(reg_str));
    st->print("%s",reg_str);
  }
  st->print_raw(", ");
  st->print("#" INT64_FORMAT, (int64_t)_c0);
  st->print_raw("]");
}
void indOffL1Oper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print_raw("[");
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str,sizeof(reg_str));
    st->print("%s",reg_str);
  }
  st->print_raw(", ");
  st->print("#" INT64_FORMAT, (int64_t)_c0);
  st->print_raw("]");
}
#endif

#ifndef PRODUCT
void indOffL2Oper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print_raw("[");
  { char reg_str[128];
    ra->dump_register(node,reg_str, sizeof(reg_str));
    st->print("%s",reg_str);
  }
  st->print_raw(", ");
  st->print("#" INT64_FORMAT, (int64_t)_c0);
  st->print_raw("]");
}
void indOffL2Oper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print_raw("[");
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str,sizeof(reg_str));
    st->print("%s",reg_str);
  }
  st->print_raw(", ");
  st->print("#" INT64_FORMAT, (int64_t)_c0);
  st->print_raw("]");
}
#endif

#ifndef PRODUCT
void indOffL4Oper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print_raw("[");
  { char reg_str[128];
    ra->dump_register(node,reg_str, sizeof(reg_str));
    st->print("%s",reg_str);
  }
  st->print_raw(", ");
  st->print("#" INT64_FORMAT, (int64_t)_c0);
  st->print_raw("]");
}
void indOffL4Oper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print_raw("[");
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str,sizeof(reg_str));
    st->print("%s",reg_str);
  }
  st->print_raw(", ");
  st->print("#" INT64_FORMAT, (int64_t)_c0);
  st->print_raw("]");
}
#endif

#ifndef PRODUCT
void indOffL8Oper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print_raw("[");
  { char reg_str[128];
    ra->dump_register(node,reg_str, sizeof(reg_str));
    st->print("%s",reg_str);
  }
  st->print_raw(", ");
  st->print("#" INT64_FORMAT, (int64_t)_c0);
  st->print_raw("]");
}
void indOffL8Oper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print_raw("[");
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str,sizeof(reg_str));
    st->print("%s",reg_str);
  }
  st->print_raw(", ");
  st->print("#" INT64_FORMAT, (int64_t)_c0);
  st->print_raw("]");
}
#endif

#ifndef PRODUCT
void indOffL16Oper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print_raw("[");
  { char reg_str[128];
    ra->dump_register(node,reg_str, sizeof(reg_str));
    st->print("%s",reg_str);
  }
  st->print_raw(", ");
  st->print("#" INT64_FORMAT, (int64_t)_c0);
  st->print_raw("]");
}
void indOffL16Oper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print_raw("[");
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str,sizeof(reg_str));
    st->print("%s",reg_str);
  }
  st->print_raw(", ");
  st->print("#" INT64_FORMAT, (int64_t)_c0);
  st->print_raw("]");
}
#endif

#ifndef PRODUCT
void indirectNOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print_raw("[");
  { char reg_str[128];
    ra->dump_register(node,reg_str, sizeof(reg_str));
    st->print("%s",reg_str);
  }
  st->print_raw("]\t# narrow");
}
void indirectNOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print_raw("[");
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str,sizeof(reg_str));
    st->print("%s",reg_str);
  }
  st->print_raw("]\t# narrow");
}
#endif

#ifndef PRODUCT
void indIndexScaledI2LNOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node,reg_str, sizeof(reg_str));
    st->print("%s",reg_str);
  }
  st->print_raw(", ");
  { char reg_str[128];
    ra->dump_register(node,reg_str, sizeof(reg_str));
    st->print("%s",reg_str);
  }
  st->print_raw(" sxtw(");
  st->print("#%d", _c0);
  st->print_raw("), 0, I2L\t# narrow");
}
void indIndexScaledI2LNOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str,sizeof(reg_str));
    st->print("%s",reg_str);
  }
  st->print_raw(", ");
  { char reg_str[128];
    ra->dump_register(node->in(idx+1),reg_str,sizeof(reg_str));
    st->print("%s",reg_str);
  }
  st->print_raw(" sxtw(");
  st->print("#%d", _c0);
  st->print_raw("), 0, I2L\t# narrow");
}
#endif

#ifndef PRODUCT
void indIndexScaledNOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node,reg_str, sizeof(reg_str));
    st->print("%s",reg_str);
  }
  st->print_raw(", ");
  { char reg_str[128];
    ra->dump_register(node,reg_str, sizeof(reg_str));
    st->print("%s",reg_str);
  }
  st->print_raw(" lsl(");
  st->print("#%d", _c0);
  st->print_raw(")\t# narrow");
}
void indIndexScaledNOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str,sizeof(reg_str));
    st->print("%s",reg_str);
  }
  st->print_raw(", ");
  { char reg_str[128];
    ra->dump_register(node->in(idx+1),reg_str,sizeof(reg_str));
    st->print("%s",reg_str);
  }
  st->print_raw(" lsl(");
  st->print("#%d", _c0);
  st->print_raw(")\t# narrow");
}
#endif

#ifndef PRODUCT
void indIndexI2LNOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node,reg_str, sizeof(reg_str));
    st->print("%s",reg_str);
  }
  st->print_raw(", ");
  { char reg_str[128];
    ra->dump_register(node,reg_str, sizeof(reg_str));
    st->print("%s",reg_str);
  }
  st->print_raw(", 0, I2L\t# narrow");
}
void indIndexI2LNOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str,sizeof(reg_str));
    st->print("%s",reg_str);
  }
  st->print_raw(", ");
  { char reg_str[128];
    ra->dump_register(node->in(idx+1),reg_str,sizeof(reg_str));
    st->print("%s",reg_str);
  }
  st->print_raw(", 0, I2L\t# narrow");
}
#endif

#ifndef PRODUCT
void indIndexNOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node,reg_str, sizeof(reg_str));
    st->print("%s",reg_str);
  }
  st->print_raw(", ");
  { char reg_str[128];
    ra->dump_register(node,reg_str, sizeof(reg_str));
    st->print("%s",reg_str);
  }
  st->print_raw("\t# narrow");
}
void indIndexNOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str,sizeof(reg_str));
    st->print("%s",reg_str);
  }
  st->print_raw(", ");
  { char reg_str[128];
    ra->dump_register(node->in(idx+1),reg_str,sizeof(reg_str));
    st->print("%s",reg_str);
  }
  st->print_raw("\t# narrow");
}
#endif

#ifndef PRODUCT
void indOffINOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print_raw("[");
  { char reg_str[128];
    ra->dump_register(node,reg_str, sizeof(reg_str));
    st->print("%s",reg_str);
  }
  st->print_raw(", ");
  st->print("#%d", _c0);
  st->print_raw("]\t# narrow");
}
void indOffINOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print_raw("[");
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str,sizeof(reg_str));
    st->print("%s",reg_str);
  }
  st->print_raw(", ");
  st->print("#%d", _c0);
  st->print_raw("]\t# narrow");
}
#endif

#ifndef PRODUCT
void indOffLNOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print_raw("[");
  { char reg_str[128];
    ra->dump_register(node,reg_str, sizeof(reg_str));
    st->print("%s",reg_str);
  }
  st->print_raw(", ");
  st->print("#" INT64_FORMAT, (int64_t)_c0);
  st->print_raw("]\t# narrow");
}
void indOffLNOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print_raw("[");
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str,sizeof(reg_str));
    st->print("%s",reg_str);
  }
  st->print_raw(", ");
  st->print("#" INT64_FORMAT, (int64_t)_c0);
  st->print_raw("]\t# narrow");
}
#endif

#ifndef PRODUCT
void stackSlotPOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print_raw("[");
  { char reg_str[128];
    ra->dump_register(node,reg_str, sizeof(reg_str));
    st->print("%s",reg_str);
  }
  st->print_raw("]");
}
void stackSlotPOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print_raw("[");
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str,sizeof(reg_str));
    st->print("%s",reg_str);
  }
  st->print_raw("]");
}
#endif

#ifndef PRODUCT
void stackSlotIOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print_raw("[");
  { char reg_str[128];
    ra->dump_register(node,reg_str, sizeof(reg_str));
    st->print("%s",reg_str);
  }
  st->print_raw("]");
}
void stackSlotIOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print_raw("[");
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str,sizeof(reg_str));
    st->print("%s",reg_str);
  }
  st->print_raw("]");
}
#endif

#ifndef PRODUCT
void stackSlotFOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print_raw("[");
  { char reg_str[128];
    ra->dump_register(node,reg_str, sizeof(reg_str));
    st->print("%s",reg_str);
  }
  st->print_raw("]");
}
void stackSlotFOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print_raw("[");
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str,sizeof(reg_str));
    st->print("%s",reg_str);
  }
  st->print_raw("]");
}
#endif

#ifndef PRODUCT
void stackSlotDOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print_raw("[");
  { char reg_str[128];
    ra->dump_register(node,reg_str, sizeof(reg_str));
    st->print("%s",reg_str);
  }
  st->print_raw("]");
}
void stackSlotDOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print_raw("[");
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str,sizeof(reg_str));
    st->print("%s",reg_str);
  }
  st->print_raw("]");
}
#endif

#ifndef PRODUCT
void stackSlotLOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print_raw("[");
  { char reg_str[128];
    ra->dump_register(node,reg_str, sizeof(reg_str));
    st->print("%s",reg_str);
  }
  st->print_raw("]");
}
void stackSlotLOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print_raw("[");
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str,sizeof(reg_str));
    st->print("%s",reg_str);
  }
  st->print_raw("]");
}
#endif

#ifndef PRODUCT
void cmpOpOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print_raw("");
       if( _c0 == BoolTest::eq ) st->print_raw("eq");
  else if( _c0 == BoolTest::ne ) st->print_raw("ne");
  else if( _c0 == BoolTest::le ) st->print_raw("le");
  else if( _c0 == BoolTest::ge ) st->print_raw("ge");
  else if( _c0 == BoolTest::lt ) st->print_raw("lt");
  else if( _c0 == BoolTest::gt ) st->print_raw("gt");
  else if( _c0 == BoolTest::overflow ) st->print_raw("vs");
  else if( _c0 == BoolTest::no_overflow ) st->print_raw("vc");
}
void cmpOpOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print_raw("");
       if( _c0 == BoolTest::eq ) st->print_raw("eq");
  else if( _c0 == BoolTest::ne ) st->print_raw("ne");
  else if( _c0 == BoolTest::le ) st->print_raw("le");
  else if( _c0 == BoolTest::ge ) st->print_raw("ge");
  else if( _c0 == BoolTest::lt ) st->print_raw("lt");
  else if( _c0 == BoolTest::gt ) st->print_raw("gt");
  else if( _c0 == BoolTest::overflow ) st->print_raw("vs");
  else if( _c0 == BoolTest::no_overflow ) st->print_raw("vc");
}
#endif

#ifndef PRODUCT
void cmpOpUOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print_raw("");
       if( _c0 == BoolTest::eq ) st->print_raw("eq");
  else if( _c0 == BoolTest::ne ) st->print_raw("ne");
  else if( _c0 == BoolTest::le ) st->print_raw("ls");
  else if( _c0 == BoolTest::ge ) st->print_raw("hs");
  else if( _c0 == BoolTest::lt ) st->print_raw("lo");
  else if( _c0 == BoolTest::gt ) st->print_raw("hi");
  else if( _c0 == BoolTest::overflow ) st->print_raw("vs");
  else if( _c0 == BoolTest::no_overflow ) st->print_raw("vc");
}
void cmpOpUOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print_raw("");
       if( _c0 == BoolTest::eq ) st->print_raw("eq");
  else if( _c0 == BoolTest::ne ) st->print_raw("ne");
  else if( _c0 == BoolTest::le ) st->print_raw("ls");
  else if( _c0 == BoolTest::ge ) st->print_raw("hs");
  else if( _c0 == BoolTest::lt ) st->print_raw("lo");
  else if( _c0 == BoolTest::gt ) st->print_raw("hi");
  else if( _c0 == BoolTest::overflow ) st->print_raw("vs");
  else if( _c0 == BoolTest::no_overflow ) st->print_raw("vc");
}
#endif

#ifndef PRODUCT
void cmpOpEqNeOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print_raw("");
       if( _c0 == BoolTest::eq ) st->print_raw("eq");
  else if( _c0 == BoolTest::ne ) st->print_raw("ne");
  else if( _c0 == BoolTest::le ) st->print_raw("le");
  else if( _c0 == BoolTest::ge ) st->print_raw("ge");
  else if( _c0 == BoolTest::lt ) st->print_raw("lt");
  else if( _c0 == BoolTest::gt ) st->print_raw("gt");
  else if( _c0 == BoolTest::overflow ) st->print_raw("vs");
  else if( _c0 == BoolTest::no_overflow ) st->print_raw("vc");
}
void cmpOpEqNeOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print_raw("");
       if( _c0 == BoolTest::eq ) st->print_raw("eq");
  else if( _c0 == BoolTest::ne ) st->print_raw("ne");
  else if( _c0 == BoolTest::le ) st->print_raw("le");
  else if( _c0 == BoolTest::ge ) st->print_raw("ge");
  else if( _c0 == BoolTest::lt ) st->print_raw("lt");
  else if( _c0 == BoolTest::gt ) st->print_raw("gt");
  else if( _c0 == BoolTest::overflow ) st->print_raw("vs");
  else if( _c0 == BoolTest::no_overflow ) st->print_raw("vc");
}
#endif

#ifndef PRODUCT
void cmpOpLtGeOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print_raw("");
       if( _c0 == BoolTest::eq ) st->print_raw("eq");
  else if( _c0 == BoolTest::ne ) st->print_raw("ne");
  else if( _c0 == BoolTest::le ) st->print_raw("le");
  else if( _c0 == BoolTest::ge ) st->print_raw("ge");
  else if( _c0 == BoolTest::lt ) st->print_raw("lt");
  else if( _c0 == BoolTest::gt ) st->print_raw("gt");
  else if( _c0 == BoolTest::overflow ) st->print_raw("vs");
  else if( _c0 == BoolTest::no_overflow ) st->print_raw("vc");
}
void cmpOpLtGeOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print_raw("");
       if( _c0 == BoolTest::eq ) st->print_raw("eq");
  else if( _c0 == BoolTest::ne ) st->print_raw("ne");
  else if( _c0 == BoolTest::le ) st->print_raw("le");
  else if( _c0 == BoolTest::ge ) st->print_raw("ge");
  else if( _c0 == BoolTest::lt ) st->print_raw("lt");
  else if( _c0 == BoolTest::gt ) st->print_raw("gt");
  else if( _c0 == BoolTest::overflow ) st->print_raw("vs");
  else if( _c0 == BoolTest::no_overflow ) st->print_raw("vc");
}
#endif

#ifndef PRODUCT
void cmpOpUEqNeLtGeOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print_raw("");
       if( _c0 == BoolTest::eq ) st->print_raw("eq");
  else if( _c0 == BoolTest::ne ) st->print_raw("ne");
  else if( _c0 == BoolTest::le ) st->print_raw("le");
  else if( _c0 == BoolTest::ge ) st->print_raw("ge");
  else if( _c0 == BoolTest::lt ) st->print_raw("lt");
  else if( _c0 == BoolTest::gt ) st->print_raw("gt");
  else if( _c0 == BoolTest::overflow ) st->print_raw("vs");
  else if( _c0 == BoolTest::no_overflow ) st->print_raw("vc");
}
void cmpOpUEqNeLtGeOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print_raw("");
       if( _c0 == BoolTest::eq ) st->print_raw("eq");
  else if( _c0 == BoolTest::ne ) st->print_raw("ne");
  else if( _c0 == BoolTest::le ) st->print_raw("le");
  else if( _c0 == BoolTest::ge ) st->print_raw("ge");
  else if( _c0 == BoolTest::lt ) st->print_raw("lt");
  else if( _c0 == BoolTest::gt ) st->print_raw("gt");
  else if( _c0 == BoolTest::overflow ) st->print_raw("vs");
  else if( _c0 == BoolTest::no_overflow ) st->print_raw("vc");
}
#endif

#ifndef PRODUCT
void iRegL2IOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print_raw("l2i(");
  { char reg_str[128];
    ra->dump_register(node,reg_str, sizeof(reg_str));
    st->print("%s",reg_str);
  }
  st->print_raw(")");
}
void iRegL2IOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print_raw("l2i(");
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str,sizeof(reg_str));
    st->print("%s",reg_str);
  }
  st->print_raw(")");
}
#endif

#ifndef PRODUCT
void vmemA_immIOffset4Oper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print("#%d", _c0);
}
void vmemA_immIOffset4Oper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print("#%d", _c0);
}
#endif

#ifndef PRODUCT
void vmemA_immLOffset4Oper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print("#" INT64_FORMAT, (int64_t)_c0);
}
void vmemA_immLOffset4Oper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print("#" INT64_FORMAT, (int64_t)_c0);
}
#endif

#ifndef PRODUCT
void vmemA_indOffI4Oper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print_raw("[");
  { char reg_str[128];
    ra->dump_register(node,reg_str, sizeof(reg_str));
    st->print("%s",reg_str);
  }
  st->print_raw(", ");
  st->print("#%d", _c0);
  st->print_raw("]");
}
void vmemA_indOffI4Oper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print_raw("[");
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str,sizeof(reg_str));
    st->print("%s",reg_str);
  }
  st->print_raw(", ");
  st->print("#%d", _c0);
  st->print_raw("]");
}
#endif

#ifndef PRODUCT
void vmemA_indOffL4Oper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print_raw("[");
  { char reg_str[128];
    ra->dump_register(node,reg_str, sizeof(reg_str));
    st->print("%s",reg_str);
  }
  st->print_raw(", ");
  st->print("#" INT64_FORMAT, (int64_t)_c0);
  st->print_raw("]");
}
void vmemA_indOffL4Oper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print_raw("[");
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str,sizeof(reg_str));
    st->print("%s",reg_str);
  }
  st->print_raw(", ");
  st->print("#" INT64_FORMAT, (int64_t)_c0);
  st->print_raw("]");
}
#endif
#ifndef PRODUCT
void loadBNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  st->print_raw("ldrsbw  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("\t# byte");
  if (ra->C->alias_type(adr_type())->field() != nullptr) {
    ciField* f = ra->C->alias_type(adr_type())->field();
    st->print(" ! Field: ");
    if (f->is_volatile())
      st->print("volatile ");
    f->holder()->name()->print_symbol_on(st);
    st->print(".");
    f->name()->print_symbol_on(st);
    if (f->is_constant())
      st->print(" (constant)");
  } else {
    if (ra->C->alias_type(adr_type())->is_volatile())
      st->print(" volatile!");
  }
}
#endif
#ifndef PRODUCT
void loadB2LNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  st->print_raw("ldrsb  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("\t# byte");
}
#endif
#ifndef PRODUCT
void loadUBNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  st->print_raw("ldrbw  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("\t# byte");
  if (ra->C->alias_type(adr_type())->field() != nullptr) {
    ciField* f = ra->C->alias_type(adr_type())->field();
    st->print(" ! Field: ");
    if (f->is_volatile())
      st->print("volatile ");
    f->holder()->name()->print_symbol_on(st);
    st->print(".");
    f->name()->print_symbol_on(st);
    if (f->is_constant())
      st->print(" (constant)");
  } else {
    if (ra->C->alias_type(adr_type())->is_volatile())
      st->print(" volatile!");
  }
}
#endif
#ifndef PRODUCT
void loadUB2LNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  st->print_raw("ldrb  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("\t# byte");
}
#endif
#ifndef PRODUCT
void loadSNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  st->print_raw("ldrshw  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("\t# short");
  if (ra->C->alias_type(adr_type())->field() != nullptr) {
    ciField* f = ra->C->alias_type(adr_type())->field();
    st->print(" ! Field: ");
    if (f->is_volatile())
      st->print("volatile ");
    f->holder()->name()->print_symbol_on(st);
    st->print(".");
    f->name()->print_symbol_on(st);
    if (f->is_constant())
      st->print(" (constant)");
  } else {
    if (ra->C->alias_type(adr_type())->is_volatile())
      st->print(" volatile!");
  }
}
#endif
#ifndef PRODUCT
void loadS2LNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  st->print_raw("ldrsh  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("\t# short");
}
#endif
#ifndef PRODUCT
void loadUSNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  st->print_raw("ldrh  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("\t# short");
  if (ra->C->alias_type(adr_type())->field() != nullptr) {
    ciField* f = ra->C->alias_type(adr_type())->field();
    st->print(" ! Field: ");
    if (f->is_volatile())
      st->print("volatile ");
    f->holder()->name()->print_symbol_on(st);
    st->print(".");
    f->name()->print_symbol_on(st);
    if (f->is_constant())
      st->print(" (constant)");
  } else {
    if (ra->C->alias_type(adr_type())->is_volatile())
      st->print(" volatile!");
  }
}
#endif
#ifndef PRODUCT
void loadUS2LNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  st->print_raw("ldrh  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("\t# short");
}
#endif
#ifndef PRODUCT
void loadINode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  st->print_raw("ldrw  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("\t# int");
  if (ra->C->alias_type(adr_type())->field() != nullptr) {
    ciField* f = ra->C->alias_type(adr_type())->field();
    st->print(" ! Field: ");
    if (f->is_volatile())
      st->print("volatile ");
    f->holder()->name()->print_symbol_on(st);
    st->print(".");
    f->name()->print_symbol_on(st);
    if (f->is_constant())
      st->print(" (constant)");
  } else {
    if (ra->C->alias_type(adr_type())->is_volatile())
      st->print(" volatile!");
  }
}
#endif
#ifndef PRODUCT
void loadI2LNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  st->print_raw("ldrsw  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("\t# int");
}
#endif
#ifndef PRODUCT
void loadUI2LNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// mask
  st->print_raw("ldrw  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("\t# int");
}
#endif
#ifndef PRODUCT
void loadLNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  st->print_raw("ldr  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("\t# int");
  if (ra->C->alias_type(adr_type())->field() != nullptr) {
    ciField* f = ra->C->alias_type(adr_type())->field();
    st->print(" ! Field: ");
    if (f->is_volatile())
      st->print("volatile ");
    f->holder()->name()->print_symbol_on(st);
    st->print(".");
    f->name()->print_symbol_on(st);
    if (f->is_constant())
      st->print(" (constant)");
  } else {
    if (ra->C->alias_type(adr_type())->is_volatile())
      st->print(" volatile!");
  }
}
#endif
#ifndef PRODUCT
void loadRangeNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  st->print_raw("ldrw  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("\t# range");
  if (ra->C->alias_type(adr_type())->field() != nullptr) {
    ciField* f = ra->C->alias_type(adr_type())->field();
    st->print(" ! Field: ");
    if (f->is_volatile())
      st->print("volatile ");
    f->holder()->name()->print_symbol_on(st);
    st->print(".");
    f->name()->print_symbol_on(st);
    if (f->is_constant())
      st->print(" (constant)");
  } else {
    if (ra->C->alias_type(adr_type())->is_volatile())
      st->print(" volatile!");
  }
}
#endif
#ifndef PRODUCT
void loadPNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  st->print_raw("ldr  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("\t# ptr");
  if (ra->C->alias_type(adr_type())->field() != nullptr) {
    ciField* f = ra->C->alias_type(adr_type())->field();
    st->print(" ! Field: ");
    if (f->is_volatile())
      st->print("volatile ");
    f->holder()->name()->print_symbol_on(st);
    st->print(".");
    f->name()->print_symbol_on(st);
    if (f->is_constant())
      st->print(" (constant)");
  } else {
    if (ra->C->alias_type(adr_type())->is_volatile())
      st->print(" volatile!");
  }
}
#endif
#ifndef PRODUCT
void loadNNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  st->print_raw("ldrw  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("\t# compressed ptr");
  if (ra->C->alias_type(adr_type())->field() != nullptr) {
    ciField* f = ra->C->alias_type(adr_type())->field();
    st->print(" ! Field: ");
    if (f->is_volatile())
      st->print("volatile ");
    f->holder()->name()->print_symbol_on(st);
    st->print(".");
    f->name()->print_symbol_on(st);
    if (f->is_constant())
      st->print(" (constant)");
  } else {
    if (ra->C->alias_type(adr_type())->is_volatile())
      st->print(" volatile!");
  }
}
#endif
#ifndef PRODUCT
void loadKlassNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  st->print_raw("ldr  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("\t# class");
  if (ra->C->alias_type(adr_type())->field() != nullptr) {
    ciField* f = ra->C->alias_type(adr_type())->field();
    st->print(" ! Field: ");
    if (f->is_volatile())
      st->print("volatile ");
    f->holder()->name()->print_symbol_on(st);
    st->print(".");
    f->name()->print_symbol_on(st);
    if (f->is_constant())
      st->print(" (constant)");
  } else {
    if (ra->C->alias_type(adr_type())->is_volatile())
      st->print(" volatile!");
  }
}
#endif
#ifndef PRODUCT
void loadNKlassNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  st->print_raw("ldrw  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("\t# compressed class ptr");
  if (ra->C->alias_type(adr_type())->field() != nullptr) {
    ciField* f = ra->C->alias_type(adr_type())->field();
    st->print(" ! Field: ");
    if (f->is_volatile())
      st->print("volatile ");
    f->holder()->name()->print_symbol_on(st);
    st->print(".");
    f->name()->print_symbol_on(st);
    if (f->is_constant())
      st->print(" (constant)");
  } else {
    if (ra->C->alias_type(adr_type())->is_volatile())
      st->print(" volatile!");
  }
}
#endif
#ifndef PRODUCT
void loadFNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  st->print_raw("ldrs  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("\t# float");
  if (ra->C->alias_type(adr_type())->field() != nullptr) {
    ciField* f = ra->C->alias_type(adr_type())->field();
    st->print(" ! Field: ");
    if (f->is_volatile())
      st->print("volatile ");
    f->holder()->name()->print_symbol_on(st);
    st->print(".");
    f->name()->print_symbol_on(st);
    if (f->is_constant())
      st->print(" (constant)");
  } else {
    if (ra->C->alias_type(adr_type())->is_volatile())
      st->print(" volatile!");
  }
}
#endif
#ifndef PRODUCT
void loadDNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  st->print_raw("ldrd  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("\t# double");
  if (ra->C->alias_type(adr_type())->field() != nullptr) {
    ciField* f = ra->C->alias_type(adr_type())->field();
    st->print(" ! Field: ");
    if (f->is_volatile())
      st->print("volatile ");
    f->holder()->name()->print_symbol_on(st);
    st->print(".");
    f->name()->print_symbol_on(st);
    if (f->is_constant())
      st->print(" (constant)");
  } else {
    if (ra->C->alias_type(adr_type())->is_volatile())
      st->print(" volatile!");
  }
}
#endif
#ifndef PRODUCT
void loadConINode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("mov ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\t# int");
}
#endif
#ifndef PRODUCT
void loadConLNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("mov ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\t# long");
}
#endif
#ifndef PRODUCT
void loadConPNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// con
  st->print_raw("mov  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // con
  st->print_raw("\t# ptr\n\t");
}
#endif
#ifndef PRODUCT
void loadConP0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// con
  st->print_raw("mov  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // con
  st->print_raw("\t# null pointer");
}
#endif
#ifndef PRODUCT
void loadConP1Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// con
  st->print_raw("mov  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // con
  st->print_raw("\t# null pointer");
}
#endif
#ifndef PRODUCT
void loadByteMapBaseNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// con
  st->print_raw("adr  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // con
  st->print_raw("\t# Byte Map Base");
}
#endif
#ifndef PRODUCT
void loadConNNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// con
  st->print_raw("mov  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // con
  st->print_raw("\t# compressed ptr");
}
#endif
#ifndef PRODUCT
void loadConN0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// con
  st->print_raw("mov  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // con
  st->print_raw("\t# compressed null pointer");
}
#endif
#ifndef PRODUCT
void loadConNKlassNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// con
  st->print_raw("mov  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // con
  st->print_raw("\t# compressed klass ptr");
}
#endif
#ifndef PRODUCT
void loadConF_packedNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// con
  st->print_raw("fmovs  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // con
}
#endif
#ifndef PRODUCT
void loadConFNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// con
  st->print_raw("ldrs ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", [");
  st->print("constant table base + #%d", constant_offset_unchecked());
  st->print_raw("]\t# load from constant table: float=");
  opnd_array(1)->ext_format(ra, this,idx1, st); // con
  st->print_raw("\n\t");
}
#endif
#ifndef PRODUCT
void loadConD_packedNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// con
  st->print_raw("fmovd  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // con
}
#endif
#ifndef PRODUCT
void loadConDNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// con
  st->print_raw("ldrd ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", [");
  st->print("constant table base + #%d", constant_offset_unchecked());
  st->print_raw("]\t# load from constant table: float=");
  opnd_array(1)->ext_format(ra, this,idx1, st); // con
  st->print_raw("\n\t");
}
#endif
#ifndef PRODUCT
void storeimmCM0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// zero
  st->print_raw("storestore (elided)\n\t");
  st->print_raw("strb zr, ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("\t# byte");
  if (ra->C->alias_type(adr_type())->field() != nullptr) {
    ciField* f = ra->C->alias_type(adr_type())->field();
    st->print(" ! Field: ");
    if (f->is_volatile())
      st->print("volatile ");
    f->holder()->name()->print_symbol_on(st);
    st->print(".");
    f->name()->print_symbol_on(st);
    if (f->is_constant())
      st->print(" (constant)");
  } else {
    if (ra->C->alias_type(adr_type())->is_volatile())
      st->print(" volatile!");
  }
}
#endif
#ifndef PRODUCT
void storeimmCM0_orderedNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// zero
  st->print_raw("storestore\n\t");
  st->print_raw("dmb ishst");
  st->print_raw("\n\tstrb zr, ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("\t# byte");
  if (ra->C->alias_type(adr_type())->field() != nullptr) {
    ciField* f = ra->C->alias_type(adr_type())->field();
    st->print(" ! Field: ");
    if (f->is_volatile())
      st->print("volatile ");
    f->holder()->name()->print_symbol_on(st);
    st->print(".");
    f->name()->print_symbol_on(st);
    if (f->is_constant())
      st->print(" (constant)");
  } else {
    if (ra->C->alias_type(adr_type())->is_volatile())
      st->print(" volatile!");
  }
}
#endif
#ifndef PRODUCT
void storeBNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  st->print_raw("strb  ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("\t# byte");
  if (ra->C->alias_type(adr_type())->field() != nullptr) {
    ciField* f = ra->C->alias_type(adr_type())->field();
    st->print(" ! Field: ");
    if (f->is_volatile())
      st->print("volatile ");
    f->holder()->name()->print_symbol_on(st);
    st->print(".");
    f->name()->print_symbol_on(st);
    if (f->is_constant())
      st->print(" (constant)");
  } else {
    if (ra->C->alias_type(adr_type())->is_volatile())
      st->print(" volatile!");
  }
}
#endif
#ifndef PRODUCT
void storeimmB0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// zero
  st->print_raw("strb rscractch2, ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("\t# byte");
  if (ra->C->alias_type(adr_type())->field() != nullptr) {
    ciField* f = ra->C->alias_type(adr_type())->field();
    st->print(" ! Field: ");
    if (f->is_volatile())
      st->print("volatile ");
    f->holder()->name()->print_symbol_on(st);
    st->print(".");
    f->name()->print_symbol_on(st);
    if (f->is_constant())
      st->print(" (constant)");
  } else {
    if (ra->C->alias_type(adr_type())->is_volatile())
      st->print(" volatile!");
  }
}
#endif
#ifndef PRODUCT
void storeCNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  st->print_raw("strh  ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("\t# short");
  if (ra->C->alias_type(adr_type())->field() != nullptr) {
    ciField* f = ra->C->alias_type(adr_type())->field();
    st->print(" ! Field: ");
    if (f->is_volatile())
      st->print("volatile ");
    f->holder()->name()->print_symbol_on(st);
    st->print(".");
    f->name()->print_symbol_on(st);
    if (f->is_constant())
      st->print(" (constant)");
  } else {
    if (ra->C->alias_type(adr_type())->is_volatile())
      st->print(" volatile!");
  }
}
#endif
#ifndef PRODUCT
void storeimmC0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// zero
  st->print_raw("strh  zr, ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("\t# short");
  if (ra->C->alias_type(adr_type())->field() != nullptr) {
    ciField* f = ra->C->alias_type(adr_type())->field();
    st->print(" ! Field: ");
    if (f->is_volatile())
      st->print("volatile ");
    f->holder()->name()->print_symbol_on(st);
    st->print(".");
    f->name()->print_symbol_on(st);
    if (f->is_constant())
      st->print(" (constant)");
  } else {
    if (ra->C->alias_type(adr_type())->is_volatile())
      st->print(" volatile!");
  }
}
#endif
#ifndef PRODUCT
void storeINode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  st->print_raw("strw  ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("\t# int");
  if (ra->C->alias_type(adr_type())->field() != nullptr) {
    ciField* f = ra->C->alias_type(adr_type())->field();
    st->print(" ! Field: ");
    if (f->is_volatile())
      st->print("volatile ");
    f->holder()->name()->print_symbol_on(st);
    st->print(".");
    f->name()->print_symbol_on(st);
    if (f->is_constant())
      st->print(" (constant)");
  } else {
    if (ra->C->alias_type(adr_type())->is_volatile())
      st->print(" volatile!");
  }
}
#endif
#ifndef PRODUCT
void storeimmI0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// zero
  st->print_raw("strw  zr, ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("\t# int");
  if (ra->C->alias_type(adr_type())->field() != nullptr) {
    ciField* f = ra->C->alias_type(adr_type())->field();
    st->print(" ! Field: ");
    if (f->is_volatile())
      st->print("volatile ");
    f->holder()->name()->print_symbol_on(st);
    st->print(".");
    f->name()->print_symbol_on(st);
    if (f->is_constant())
      st->print(" (constant)");
  } else {
    if (ra->C->alias_type(adr_type())->is_volatile())
      st->print(" volatile!");
  }
}
#endif
#ifndef PRODUCT
void storeLNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  st->print_raw("str  ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("\t# int");
  if (ra->C->alias_type(adr_type())->field() != nullptr) {
    ciField* f = ra->C->alias_type(adr_type())->field();
    st->print(" ! Field: ");
    if (f->is_volatile())
      st->print("volatile ");
    f->holder()->name()->print_symbol_on(st);
    st->print(".");
    f->name()->print_symbol_on(st);
    if (f->is_constant())
      st->print(" (constant)");
  } else {
    if (ra->C->alias_type(adr_type())->is_volatile())
      st->print(" volatile!");
  }
}
#endif
#ifndef PRODUCT
void storeimmL0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// zero
  st->print_raw("str  zr, ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("\t# int");
  if (ra->C->alias_type(adr_type())->field() != nullptr) {
    ciField* f = ra->C->alias_type(adr_type())->field();
    st->print(" ! Field: ");
    if (f->is_volatile())
      st->print("volatile ");
    f->holder()->name()->print_symbol_on(st);
    st->print(".");
    f->name()->print_symbol_on(st);
    if (f->is_constant())
      st->print(" (constant)");
  } else {
    if (ra->C->alias_type(adr_type())->is_volatile())
      st->print(" volatile!");
  }
}
#endif
#ifndef PRODUCT
void storePNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  st->print_raw("str  ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("\t# ptr");
  if (ra->C->alias_type(adr_type())->field() != nullptr) {
    ciField* f = ra->C->alias_type(adr_type())->field();
    st->print(" ! Field: ");
    if (f->is_volatile())
      st->print("volatile ");
    f->holder()->name()->print_symbol_on(st);
    st->print(".");
    f->name()->print_symbol_on(st);
    if (f->is_constant())
      st->print(" (constant)");
  } else {
    if (ra->C->alias_type(adr_type())->is_volatile())
      st->print(" volatile!");
  }
}
#endif
#ifndef PRODUCT
void storeimmP0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// zero
  st->print_raw("str zr, ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("\t# ptr");
  if (ra->C->alias_type(adr_type())->field() != nullptr) {
    ciField* f = ra->C->alias_type(adr_type())->field();
    st->print(" ! Field: ");
    if (f->is_volatile())
      st->print("volatile ");
    f->holder()->name()->print_symbol_on(st);
    st->print(".");
    f->name()->print_symbol_on(st);
    if (f->is_constant())
      st->print(" (constant)");
  } else {
    if (ra->C->alias_type(adr_type())->is_volatile())
      st->print(" volatile!");
  }
}
#endif
#ifndef PRODUCT
void storeNNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  st->print_raw("strw  ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("\t# compressed ptr");
  if (ra->C->alias_type(adr_type())->field() != nullptr) {
    ciField* f = ra->C->alias_type(adr_type())->field();
    st->print(" ! Field: ");
    if (f->is_volatile())
      st->print("volatile ");
    f->holder()->name()->print_symbol_on(st);
    st->print(".");
    f->name()->print_symbol_on(st);
    if (f->is_constant())
      st->print(" (constant)");
  } else {
    if (ra->C->alias_type(adr_type())->is_volatile())
      st->print(" volatile!");
  }
}
#endif
#ifndef PRODUCT
void storeImmN0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// zero
  st->print_raw("strw  zr, ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("\t# compressed ptr");
  if (ra->C->alias_type(adr_type())->field() != nullptr) {
    ciField* f = ra->C->alias_type(adr_type())->field();
    st->print(" ! Field: ");
    if (f->is_volatile())
      st->print("volatile ");
    f->holder()->name()->print_symbol_on(st);
    st->print(".");
    f->name()->print_symbol_on(st);
    if (f->is_constant())
      st->print(" (constant)");
  } else {
    if (ra->C->alias_type(adr_type())->is_volatile())
      st->print(" volatile!");
  }
}
#endif
#ifndef PRODUCT
void storeFNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  st->print_raw("strs  ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("\t# float");
  if (ra->C->alias_type(adr_type())->field() != nullptr) {
    ciField* f = ra->C->alias_type(adr_type())->field();
    st->print(" ! Field: ");
    if (f->is_volatile())
      st->print("volatile ");
    f->holder()->name()->print_symbol_on(st);
    st->print(".");
    f->name()->print_symbol_on(st);
    if (f->is_constant())
      st->print(" (constant)");
  } else {
    if (ra->C->alias_type(adr_type())->is_volatile())
      st->print(" volatile!");
  }
}
#endif
#ifndef PRODUCT
void storeDNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  st->print_raw("strd  ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("\t# double");
  if (ra->C->alias_type(adr_type())->field() != nullptr) {
    ciField* f = ra->C->alias_type(adr_type())->field();
    st->print(" ! Field: ");
    if (f->is_volatile())
      st->print("volatile ");
    f->holder()->name()->print_symbol_on(st);
    st->print(".");
    f->name()->print_symbol_on(st);
    if (f->is_constant())
      st->print(" (constant)");
  } else {
    if (ra->C->alias_type(adr_type())->is_volatile())
      st->print(" volatile!");
  }
}
#endif
#ifndef PRODUCT
void storeNKlassNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  st->print_raw("strw  ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("\t# compressed klass ptr");
  if (ra->C->alias_type(adr_type())->field() != nullptr) {
    ciField* f = ra->C->alias_type(adr_type())->field();
    st->print(" ! Field: ");
    if (f->is_volatile())
      st->print("volatile ");
    f->holder()->name()->print_symbol_on(st);
    st->print(".");
    f->name()->print_symbol_on(st);
    if (f->is_constant())
      st->print(" (constant)");
  } else {
    if (ra->C->alias_type(adr_type())->is_volatile())
      st->print(" volatile!");
  }
}
#endif
#ifndef PRODUCT
void prefetchallocNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// 
  st->print_raw("prfm ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(", PSTL1KEEP\t# Prefetch into level 1 cache write keep");
}
#endif
#ifndef PRODUCT
void loadB_volatileNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  st->print_raw("ldarsb  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("\t# byte");
  if (ra->C->alias_type(adr_type())->field() != nullptr) {
    ciField* f = ra->C->alias_type(adr_type())->field();
    st->print(" ! Field: ");
    if (f->is_volatile())
      st->print("volatile ");
    f->holder()->name()->print_symbol_on(st);
    st->print(".");
    f->name()->print_symbol_on(st);
    if (f->is_constant())
      st->print(" (constant)");
  } else {
    if (ra->C->alias_type(adr_type())->is_volatile())
      st->print(" volatile!");
  }
}
#endif
#ifndef PRODUCT
void loadB2L_volatileNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  st->print_raw("ldarsb  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("\t# byte");
}
#endif
#ifndef PRODUCT
void loadUB_volatileNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  st->print_raw("ldarb  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("\t# byte");
  if (ra->C->alias_type(adr_type())->field() != nullptr) {
    ciField* f = ra->C->alias_type(adr_type())->field();
    st->print(" ! Field: ");
    if (f->is_volatile())
      st->print("volatile ");
    f->holder()->name()->print_symbol_on(st);
    st->print(".");
    f->name()->print_symbol_on(st);
    if (f->is_constant())
      st->print(" (constant)");
  } else {
    if (ra->C->alias_type(adr_type())->is_volatile())
      st->print(" volatile!");
  }
}
#endif
#ifndef PRODUCT
void loadUB2L_volatileNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  st->print_raw("ldarb  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("\t# byte");
}
#endif
#ifndef PRODUCT
void loadS_volatileNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  st->print_raw("ldarshw  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("\t# short");
  if (ra->C->alias_type(adr_type())->field() != nullptr) {
    ciField* f = ra->C->alias_type(adr_type())->field();
    st->print(" ! Field: ");
    if (f->is_volatile())
      st->print("volatile ");
    f->holder()->name()->print_symbol_on(st);
    st->print(".");
    f->name()->print_symbol_on(st);
    if (f->is_constant())
      st->print(" (constant)");
  } else {
    if (ra->C->alias_type(adr_type())->is_volatile())
      st->print(" volatile!");
  }
}
#endif
#ifndef PRODUCT
void loadUS_volatileNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  st->print_raw("ldarhw  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("\t# short");
  if (ra->C->alias_type(adr_type())->field() != nullptr) {
    ciField* f = ra->C->alias_type(adr_type())->field();
    st->print(" ! Field: ");
    if (f->is_volatile())
      st->print("volatile ");
    f->holder()->name()->print_symbol_on(st);
    st->print(".");
    f->name()->print_symbol_on(st);
    if (f->is_constant())
      st->print(" (constant)");
  } else {
    if (ra->C->alias_type(adr_type())->is_volatile())
      st->print(" volatile!");
  }
}
#endif
#ifndef PRODUCT
void loadUS2L_volatileNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  st->print_raw("ldarh  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("\t# short");
}
#endif
#ifndef PRODUCT
void loadS2L_volatileNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  st->print_raw("ldarh  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("\t# short");
}
#endif
#ifndef PRODUCT
void loadI_volatileNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  st->print_raw("ldarw  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("\t# int");
  if (ra->C->alias_type(adr_type())->field() != nullptr) {
    ciField* f = ra->C->alias_type(adr_type())->field();
    st->print(" ! Field: ");
    if (f->is_volatile())
      st->print("volatile ");
    f->holder()->name()->print_symbol_on(st);
    st->print(".");
    f->name()->print_symbol_on(st);
    if (f->is_constant())
      st->print(" (constant)");
  } else {
    if (ra->C->alias_type(adr_type())->is_volatile())
      st->print(" volatile!");
  }
}
#endif
#ifndef PRODUCT
void loadUI2L_volatileNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// mask
  st->print_raw("ldarw  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("\t# int");
}
#endif
#ifndef PRODUCT
void loadL_volatileNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  st->print_raw("ldar  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("\t# int");
  if (ra->C->alias_type(adr_type())->field() != nullptr) {
    ciField* f = ra->C->alias_type(adr_type())->field();
    st->print(" ! Field: ");
    if (f->is_volatile())
      st->print("volatile ");
    f->holder()->name()->print_symbol_on(st);
    st->print(".");
    f->name()->print_symbol_on(st);
    if (f->is_constant())
      st->print(" (constant)");
  } else {
    if (ra->C->alias_type(adr_type())->is_volatile())
      st->print(" volatile!");
  }
}
#endif
#ifndef PRODUCT
void loadP_volatileNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  st->print_raw("ldar  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("\t# ptr");
  if (ra->C->alias_type(adr_type())->field() != nullptr) {
    ciField* f = ra->C->alias_type(adr_type())->field();
    st->print(" ! Field: ");
    if (f->is_volatile())
      st->print("volatile ");
    f->holder()->name()->print_symbol_on(st);
    st->print(".");
    f->name()->print_symbol_on(st);
    if (f->is_constant())
      st->print(" (constant)");
  } else {
    if (ra->C->alias_type(adr_type())->is_volatile())
      st->print(" volatile!");
  }
}
#endif
#ifndef PRODUCT
void loadN_volatileNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  st->print_raw("ldarw  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("\t# compressed ptr");
  if (ra->C->alias_type(adr_type())->field() != nullptr) {
    ciField* f = ra->C->alias_type(adr_type())->field();
    st->print(" ! Field: ");
    if (f->is_volatile())
      st->print("volatile ");
    f->holder()->name()->print_symbol_on(st);
    st->print(".");
    f->name()->print_symbol_on(st);
    if (f->is_constant())
      st->print(" (constant)");
  } else {
    if (ra->C->alias_type(adr_type())->is_volatile())
      st->print(" volatile!");
  }
}
#endif
#ifndef PRODUCT
void loadF_volatileNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  st->print_raw("ldars  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("\t# float");
  if (ra->C->alias_type(adr_type())->field() != nullptr) {
    ciField* f = ra->C->alias_type(adr_type())->field();
    st->print(" ! Field: ");
    if (f->is_volatile())
      st->print("volatile ");
    f->holder()->name()->print_symbol_on(st);
    st->print(".");
    f->name()->print_symbol_on(st);
    if (f->is_constant())
      st->print(" (constant)");
  } else {
    if (ra->C->alias_type(adr_type())->is_volatile())
      st->print(" volatile!");
  }
}
#endif
#ifndef PRODUCT
void loadD_volatileNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  st->print_raw("ldard  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("\t# double");
  if (ra->C->alias_type(adr_type())->field() != nullptr) {
    ciField* f = ra->C->alias_type(adr_type())->field();
    st->print(" ! Field: ");
    if (f->is_volatile())
      st->print("volatile ");
    f->holder()->name()->print_symbol_on(st);
    st->print(".");
    f->name()->print_symbol_on(st);
    if (f->is_constant())
      st->print(" (constant)");
  } else {
    if (ra->C->alias_type(adr_type())->is_volatile())
      st->print(" volatile!");
  }
}
#endif
#ifndef PRODUCT
void storeB_volatileNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  st->print_raw("stlrb  ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("\t# byte");
  if (ra->C->alias_type(adr_type())->field() != nullptr) {
    ciField* f = ra->C->alias_type(adr_type())->field();
    st->print(" ! Field: ");
    if (f->is_volatile())
      st->print("volatile ");
    f->holder()->name()->print_symbol_on(st);
    st->print(".");
    f->name()->print_symbol_on(st);
    if (f->is_constant())
      st->print(" (constant)");
  } else {
    if (ra->C->alias_type(adr_type())->is_volatile())
      st->print(" volatile!");
  }
}
#endif
#ifndef PRODUCT
void storeimmB0_volatileNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// zero
  st->print_raw("stlrb  zr, ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("\t# byte");
  if (ra->C->alias_type(adr_type())->field() != nullptr) {
    ciField* f = ra->C->alias_type(adr_type())->field();
    st->print(" ! Field: ");
    if (f->is_volatile())
      st->print("volatile ");
    f->holder()->name()->print_symbol_on(st);
    st->print(".");
    f->name()->print_symbol_on(st);
    if (f->is_constant())
      st->print(" (constant)");
  } else {
    if (ra->C->alias_type(adr_type())->is_volatile())
      st->print(" volatile!");
  }
}
#endif
#ifndef PRODUCT
void storeC_volatileNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  st->print_raw("stlrh  ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("\t# short");
  if (ra->C->alias_type(adr_type())->field() != nullptr) {
    ciField* f = ra->C->alias_type(adr_type())->field();
    st->print(" ! Field: ");
    if (f->is_volatile())
      st->print("volatile ");
    f->holder()->name()->print_symbol_on(st);
    st->print(".");
    f->name()->print_symbol_on(st);
    if (f->is_constant())
      st->print(" (constant)");
  } else {
    if (ra->C->alias_type(adr_type())->is_volatile())
      st->print(" volatile!");
  }
}
#endif
#ifndef PRODUCT
void storeimmC0_volatileNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// zero
  st->print_raw("stlrh  zr, ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("\t# short");
  if (ra->C->alias_type(adr_type())->field() != nullptr) {
    ciField* f = ra->C->alias_type(adr_type())->field();
    st->print(" ! Field: ");
    if (f->is_volatile())
      st->print("volatile ");
    f->holder()->name()->print_symbol_on(st);
    st->print(".");
    f->name()->print_symbol_on(st);
    if (f->is_constant())
      st->print(" (constant)");
  } else {
    if (ra->C->alias_type(adr_type())->is_volatile())
      st->print(" volatile!");
  }
}
#endif
#ifndef PRODUCT
void storeI_volatileNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  st->print_raw("stlrw  ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("\t# int");
  if (ra->C->alias_type(adr_type())->field() != nullptr) {
    ciField* f = ra->C->alias_type(adr_type())->field();
    st->print(" ! Field: ");
    if (f->is_volatile())
      st->print("volatile ");
    f->holder()->name()->print_symbol_on(st);
    st->print(".");
    f->name()->print_symbol_on(st);
    if (f->is_constant())
      st->print(" (constant)");
  } else {
    if (ra->C->alias_type(adr_type())->is_volatile())
      st->print(" volatile!");
  }
}
#endif
#ifndef PRODUCT
void storeimmI0_volatileNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// zero
  st->print_raw("stlrw  zr, ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("\t# int");
  if (ra->C->alias_type(adr_type())->field() != nullptr) {
    ciField* f = ra->C->alias_type(adr_type())->field();
    st->print(" ! Field: ");
    if (f->is_volatile())
      st->print("volatile ");
    f->holder()->name()->print_symbol_on(st);
    st->print(".");
    f->name()->print_symbol_on(st);
    if (f->is_constant())
      st->print(" (constant)");
  } else {
    if (ra->C->alias_type(adr_type())->is_volatile())
      st->print(" volatile!");
  }
}
#endif
#ifndef PRODUCT
void storeL_volatileNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  st->print_raw("stlr  ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("\t# int");
  if (ra->C->alias_type(adr_type())->field() != nullptr) {
    ciField* f = ra->C->alias_type(adr_type())->field();
    st->print(" ! Field: ");
    if (f->is_volatile())
      st->print("volatile ");
    f->holder()->name()->print_symbol_on(st);
    st->print(".");
    f->name()->print_symbol_on(st);
    if (f->is_constant())
      st->print(" (constant)");
  } else {
    if (ra->C->alias_type(adr_type())->is_volatile())
      st->print(" volatile!");
  }
}
#endif
#ifndef PRODUCT
void storeimmL0_volatileNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// zero
  st->print_raw("stlr  zr, ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("\t# int");
  if (ra->C->alias_type(adr_type())->field() != nullptr) {
    ciField* f = ra->C->alias_type(adr_type())->field();
    st->print(" ! Field: ");
    if (f->is_volatile())
      st->print("volatile ");
    f->holder()->name()->print_symbol_on(st);
    st->print(".");
    f->name()->print_symbol_on(st);
    if (f->is_constant())
      st->print(" (constant)");
  } else {
    if (ra->C->alias_type(adr_type())->is_volatile())
      st->print(" volatile!");
  }
}
#endif
#ifndef PRODUCT
void storeP_volatileNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  st->print_raw("stlr  ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("\t# ptr");
  if (ra->C->alias_type(adr_type())->field() != nullptr) {
    ciField* f = ra->C->alias_type(adr_type())->field();
    st->print(" ! Field: ");
    if (f->is_volatile())
      st->print("volatile ");
    f->holder()->name()->print_symbol_on(st);
    st->print(".");
    f->name()->print_symbol_on(st);
    if (f->is_constant())
      st->print(" (constant)");
  } else {
    if (ra->C->alias_type(adr_type())->is_volatile())
      st->print(" volatile!");
  }
}
#endif
#ifndef PRODUCT
void storeimmP0_volatileNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// zero
  st->print_raw("stlr  zr, ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("\t# ptr");
  if (ra->C->alias_type(adr_type())->field() != nullptr) {
    ciField* f = ra->C->alias_type(adr_type())->field();
    st->print(" ! Field: ");
    if (f->is_volatile())
      st->print("volatile ");
    f->holder()->name()->print_symbol_on(st);
    st->print(".");
    f->name()->print_symbol_on(st);
    if (f->is_constant())
      st->print(" (constant)");
  } else {
    if (ra->C->alias_type(adr_type())->is_volatile())
      st->print(" volatile!");
  }
}
#endif
#ifndef PRODUCT
void storeN_volatileNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  st->print_raw("stlrw  ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("\t# compressed ptr");
  if (ra->C->alias_type(adr_type())->field() != nullptr) {
    ciField* f = ra->C->alias_type(adr_type())->field();
    st->print(" ! Field: ");
    if (f->is_volatile())
      st->print("volatile ");
    f->holder()->name()->print_symbol_on(st);
    st->print(".");
    f->name()->print_symbol_on(st);
    if (f->is_constant())
      st->print(" (constant)");
  } else {
    if (ra->C->alias_type(adr_type())->is_volatile())
      st->print(" volatile!");
  }
}
#endif
#ifndef PRODUCT
void storeimmN0_volatileNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// zero
  st->print_raw("stlrw  zr, ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("\t# compressed ptr");
  if (ra->C->alias_type(adr_type())->field() != nullptr) {
    ciField* f = ra->C->alias_type(adr_type())->field();
    st->print(" ! Field: ");
    if (f->is_volatile())
      st->print("volatile ");
    f->holder()->name()->print_symbol_on(st);
    st->print(".");
    f->name()->print_symbol_on(st);
    if (f->is_constant())
      st->print(" (constant)");
  } else {
    if (ra->C->alias_type(adr_type())->is_volatile())
      st->print(" volatile!");
  }
}
#endif
#ifndef PRODUCT
void storeF_volatileNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  st->print_raw("stlrs  ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("\t# float");
  if (ra->C->alias_type(adr_type())->field() != nullptr) {
    ciField* f = ra->C->alias_type(adr_type())->field();
    st->print(" ! Field: ");
    if (f->is_volatile())
      st->print("volatile ");
    f->holder()->name()->print_symbol_on(st);
    st->print(".");
    f->name()->print_symbol_on(st);
    if (f->is_constant())
      st->print(" (constant)");
  } else {
    if (ra->C->alias_type(adr_type())->is_volatile())
      st->print(" volatile!");
  }
}
#endif
#ifndef PRODUCT
void storeD_volatileNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  st->print_raw("stlrd  ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("\t# double");
  if (ra->C->alias_type(adr_type())->field() != nullptr) {
    ciField* f = ra->C->alias_type(adr_type())->field();
    st->print(" ! Field: ");
    if (f->is_volatile())
      st->print("volatile ");
    f->holder()->name()->print_symbol_on(st);
    st->print(".");
    f->name()->print_symbol_on(st);
    if (f->is_constant())
      st->print(" (constant)");
  } else {
    if (ra->C->alias_type(adr_type())->is_volatile())
      st->print(" volatile!");
  }
}
#endif
#ifndef PRODUCT
void cacheWBNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// 
  st->print_raw("cache wb ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // addr
}
#endif
#ifndef PRODUCT
void cacheWBPreSyncNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  st->print_raw("cache wb presync");
}
#endif
#ifndef PRODUCT
void cacheWBPostSyncNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  st->print_raw("cache wb postsync");
}
#endif
#ifndef PRODUCT
void bytes_reverse_intNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("revw  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
}
#endif
#ifndef PRODUCT
void bytes_reverse_longNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("rev  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
}
#endif
#ifndef PRODUCT
void bytes_reverse_unsigned_shortNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("rev16w  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
}
#endif
#ifndef PRODUCT
void bytes_reverse_shortNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("rev16w  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\n\t");
  st->print_raw("sbfmw ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", #0, #15");
}
#endif
#ifndef PRODUCT
void countLeadingZerosINode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("clzw  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
}
#endif
#ifndef PRODUCT
void countLeadingZerosLNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("clz   ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
}
#endif
#ifndef PRODUCT
void countTrailingZerosINode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("rbitw  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\n\t");
  st->print_raw("clzw   ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(0)->int_format(ra, this, st); // dst
}
#endif
#ifndef PRODUCT
void countTrailingZerosLNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("rbit   ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\n\t");
  st->print_raw("clz    ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(0)->int_format(ra, this, st); // dst
}
#endif
#ifndef PRODUCT
void popCountINode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// tmp
  st->print_raw("movw   ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\n\t");
  st->print_raw("mov    ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // tmp
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\t# vector (1D)\n\t");
  st->print_raw("cnt    ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // tmp
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // tmp
  st->print_raw("\t# vector (8B)\n\t");
  st->print_raw("addv   ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // tmp
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // tmp
  st->print_raw("\t# vector (8B)\n\t");
  st->print_raw("mov    ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // tmp
  st->print_raw("\t# vector (1D)");
}
#endif
#ifndef PRODUCT
void popCountI_memNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// tmp
  st->print_raw("ldrs   ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // tmp
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("\n\t");
  st->print_raw("cnt    ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // tmp
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // tmp
  st->print_raw("\t# vector (8B)\n\t");
  st->print_raw("addv   ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // tmp
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // tmp
  st->print_raw("\t# vector (8B)\n\t");
  st->print_raw("mov    ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // tmp
  st->print_raw("\t# vector (1D)");
}
#endif
#ifndef PRODUCT
void popCountLNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// tmp
  st->print_raw("mov    ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // tmp
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\t# vector (1D)\n\t");
  st->print_raw("cnt    ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // tmp
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // tmp
  st->print_raw("\t# vector (8B)\n\t");
  st->print_raw("addv   ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // tmp
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // tmp
  st->print_raw("\t# vector (8B)\n\t");
  st->print_raw("mov    ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // tmp
  st->print_raw("\t# vector (1D)");
}
#endif
#ifndef PRODUCT
void popCountL_memNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// tmp
  st->print_raw("ldrd   ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // tmp
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("\n\t");
  st->print_raw("cnt    ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // tmp
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // tmp
  st->print_raw("\t# vector (8B)\n\t");
  st->print_raw("addv   ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // tmp
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // tmp
  st->print_raw("\t# vector (8B)\n\t");
  st->print_raw("mov    ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // tmp
  st->print_raw("\t# vector (1D)");
}
#endif
#ifndef PRODUCT
void verify_vector_alignmentNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// addr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// mask
  st->print_raw("verify_vector_alignment ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // addr
  st->print_raw(" ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // mask
  st->print_raw(" \t! verify alignment");
}
#endif
#ifndef PRODUCT
void load_fenceNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  st->print_raw("load_fence");
}
#endif
#ifndef PRODUCT
void unnecessary_membar_acquireNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  st->print_raw("membar_acquire (elided)");
}
#endif
#ifndef PRODUCT
void membar_acquireNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  st->print_raw("membar_acquire\n\t");
  st->print_raw("dmb ish");
}
#endif
#ifndef PRODUCT
void membar_acquire_lockNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  st->print_raw("membar_acquire_lock (elided)");
}
#endif
#ifndef PRODUCT
void store_fenceNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  st->print_raw("store_fence");
}
#endif
#ifndef PRODUCT
void unnecessary_membar_releaseNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  st->print_raw("membar_release (elided)");
}
#endif
#ifndef PRODUCT
void membar_releaseNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  st->print_raw("membar_release\n\t");
  st->print_raw("dmb ish");
}
#endif
#ifndef PRODUCT
void membar_storestoreNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  st->print_raw("MEMBAR-store-store");
}
#endif
#ifndef PRODUCT
void membar_storestore_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  st->print_raw("MEMBAR-store-store");
}
#endif
#ifndef PRODUCT
void membar_release_lockNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  st->print_raw("membar_release_lock (elided)");
}
#endif
#ifndef PRODUCT
void unnecessary_membar_volatileNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  st->print_raw("membar_volatile (elided)");
}
#endif
#ifndef PRODUCT
void membar_volatileNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  st->print_raw("membar_volatile\n\t");
  st->print_raw("dmb ish");
}
#endif
#ifndef PRODUCT
void castX2PNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("mov ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\t# long -> ptr");
}
#endif
#ifndef PRODUCT
void castP2XNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("mov ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\t# ptr -> long");
}
#endif
#ifndef PRODUCT
void convP2INode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("movw ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\t# ptr -> int");
}
#endif
#ifndef PRODUCT
void convN2INode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("mov dst, ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\t# compressed ptr -> int");
}
#endif
#ifndef PRODUCT
void encodeHeapOopNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("encode_heap_oop ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
}
#endif
#ifndef PRODUCT
void encodeHeapOop_not_nullNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("encode_heap_oop_not_null ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
}
#endif
#ifndef PRODUCT
void decodeHeapOopNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("decode_heap_oop ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
}
#endif
#ifndef PRODUCT
void decodeHeapOop_not_nullNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("decode_heap_oop_not_null ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
}
#endif
#ifndef PRODUCT
void encodeKlass_not_nullNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("encode_klass_not_null ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
}
#endif
#ifndef PRODUCT
void decodeKlass_not_nullNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("decode_klass_not_null ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
}
#endif
#ifndef PRODUCT
void checkCastPPNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  st->print_raw("# checkcastPP of ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst
}
#endif
#ifndef PRODUCT
void castPPNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  st->print_raw("# castPP of ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst
}
#endif
#ifndef PRODUCT
void castIINode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  st->print_raw("# castII of ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst
}
#endif
#ifndef PRODUCT
void castLLNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  st->print_raw("# castLL of ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst
}
#endif
#ifndef PRODUCT
void castFFNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  st->print_raw("# castFF of ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst
}
#endif
#ifndef PRODUCT
void castDDNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  st->print_raw("# castDD of ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst
}
#endif
#ifndef PRODUCT
void castVVNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  st->print_raw("# castVV of ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst
}
#endif
#ifndef PRODUCT
void castVVMaskNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  st->print_raw("# castVV of ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst
}
#endif
#ifndef PRODUCT
void compareAndSwapBNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// oldval
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// newval
  st->print_raw("cmpxchgb ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // oldval
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // newval
  st->print_raw("\t# (int) if ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(" == ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // oldval
  st->print_raw(" then ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(" <-- ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // newval
  st->print_raw("cset ");
  opnd_array(0)->int_format(ra, this, st); // res
  st->print_raw(", EQ\t# ");
  opnd_array(0)->int_format(ra, this, st); // res
  st->print_raw(" <-- (EQ ? 1 : 0)");
}
#endif
#ifndef PRODUCT
void compareAndSwapSNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// oldval
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// newval
  st->print_raw("cmpxchgs ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // oldval
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // newval
  st->print_raw("\t# (int) if ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(" == ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // oldval
  st->print_raw(" then ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(" <-- ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // newval
  st->print_raw("cset ");
  opnd_array(0)->int_format(ra, this, st); // res
  st->print_raw(", EQ\t# ");
  opnd_array(0)->int_format(ra, this, st); // res
  st->print_raw(" <-- (EQ ? 1 : 0)");
}
#endif
#ifndef PRODUCT
void compareAndSwapINode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// oldval
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// newval
  st->print_raw("cmpxchgw ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // oldval
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // newval
  st->print_raw("\t# (int) if ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(" == ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // oldval
  st->print_raw(" then ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(" <-- ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // newval
  st->print_raw("cset ");
  opnd_array(0)->int_format(ra, this, st); // res
  st->print_raw(", EQ\t# ");
  opnd_array(0)->int_format(ra, this, st); // res
  st->print_raw(" <-- (EQ ? 1 : 0)");
}
#endif
#ifndef PRODUCT
void compareAndSwapLNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// oldval
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// newval
  st->print_raw("cmpxchg ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // oldval
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // newval
  st->print_raw("\t# (long) if ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(" == ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // oldval
  st->print_raw(" then ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(" <-- ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // newval
  st->print_raw("cset ");
  opnd_array(0)->int_format(ra, this, st); // res
  st->print_raw(", EQ\t# ");
  opnd_array(0)->int_format(ra, this, st); // res
  st->print_raw(" <-- (EQ ? 1 : 0)");
}
#endif
#ifndef PRODUCT
void compareAndSwapPNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// oldval
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// newval
  st->print_raw("cmpxchg ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // oldval
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // newval
  st->print_raw("\t# (ptr) if ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(" == ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // oldval
  st->print_raw(" then ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(" <-- ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // newval
  st->print_raw("cset ");
  opnd_array(0)->int_format(ra, this, st); // res
  st->print_raw(", EQ\t# ");
  opnd_array(0)->int_format(ra, this, st); // res
  st->print_raw(" <-- (EQ ? 1 : 0)");
}
#endif
#ifndef PRODUCT
void compareAndSwapNNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// oldval
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// newval
  st->print_raw("cmpxchgw ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // oldval
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // newval
  st->print_raw("\t# (narrow oop) if ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(" == ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // oldval
  st->print_raw(" then ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(" <-- ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // newval
  st->print_raw("cset ");
  opnd_array(0)->int_format(ra, this, st); // res
  st->print_raw(", EQ\t# ");
  opnd_array(0)->int_format(ra, this, st); // res
  st->print_raw(" <-- (EQ ? 1 : 0)");
}
#endif
#ifndef PRODUCT
void compareAndSwapBAcqNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// oldval
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// newval
  st->print_raw("cmpxchgb_acq ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // oldval
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // newval
  st->print_raw("\t# (int) if ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(" == ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // oldval
  st->print_raw(" then ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(" <-- ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // newval
  st->print_raw("cset ");
  opnd_array(0)->int_format(ra, this, st); // res
  st->print_raw(", EQ\t# ");
  opnd_array(0)->int_format(ra, this, st); // res
  st->print_raw(" <-- (EQ ? 1 : 0)");
}
#endif
#ifndef PRODUCT
void compareAndSwapSAcqNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// oldval
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// newval
  st->print_raw("cmpxchgs_acq ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // oldval
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // newval
  st->print_raw("\t# (int) if ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(" == ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // oldval
  st->print_raw(" then ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(" <-- ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // newval
  st->print_raw("cset ");
  opnd_array(0)->int_format(ra, this, st); // res
  st->print_raw(", EQ\t# ");
  opnd_array(0)->int_format(ra, this, st); // res
  st->print_raw(" <-- (EQ ? 1 : 0)");
}
#endif
#ifndef PRODUCT
void compareAndSwapIAcqNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// oldval
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// newval
  st->print_raw("cmpxchgw_acq ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // oldval
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // newval
  st->print_raw("\t# (int) if ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(" == ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // oldval
  st->print_raw(" then ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(" <-- ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // newval
  st->print_raw("cset ");
  opnd_array(0)->int_format(ra, this, st); // res
  st->print_raw(", EQ\t# ");
  opnd_array(0)->int_format(ra, this, st); // res
  st->print_raw(" <-- (EQ ? 1 : 0)");
}
#endif
#ifndef PRODUCT
void compareAndSwapLAcqNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// oldval
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// newval
  st->print_raw("cmpxchg_acq ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // oldval
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // newval
  st->print_raw("\t# (long) if ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(" == ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // oldval
  st->print_raw(" then ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(" <-- ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // newval
  st->print_raw("cset ");
  opnd_array(0)->int_format(ra, this, st); // res
  st->print_raw(", EQ\t# ");
  opnd_array(0)->int_format(ra, this, st); // res
  st->print_raw(" <-- (EQ ? 1 : 0)");
}
#endif
#ifndef PRODUCT
void compareAndSwapPAcqNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// oldval
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// newval
  st->print_raw("cmpxchg_acq ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // oldval
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // newval
  st->print_raw("\t# (ptr) if ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(" == ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // oldval
  st->print_raw(" then ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(" <-- ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // newval
  st->print_raw("cset ");
  opnd_array(0)->int_format(ra, this, st); // res
  st->print_raw(", EQ\t# ");
  opnd_array(0)->int_format(ra, this, st); // res
  st->print_raw(" <-- (EQ ? 1 : 0)");
}
#endif
#ifndef PRODUCT
void compareAndSwapNAcqNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// oldval
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// newval
  st->print_raw("cmpxchgw_acq ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // oldval
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // newval
  st->print_raw("\t# (narrow oop) if ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(" == ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // oldval
  st->print_raw(" then ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(" <-- ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // newval
  st->print_raw("cset ");
  opnd_array(0)->int_format(ra, this, st); // res
  st->print_raw(", EQ\t# ");
  opnd_array(0)->int_format(ra, this, st); // res
  st->print_raw(" <-- (EQ ? 1 : 0)");
}
#endif
#ifndef PRODUCT
void compareAndExchangeBNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// oldval
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// newval
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// res
  st->print_raw("cmpxchgb ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // res
  st->print_raw(" = ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // oldval
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // newval
  st->print_raw("\t# (byte, weak) if ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(" == ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // oldval
  st->print_raw(" then ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(" <-- ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // newval
}
#endif
#ifndef PRODUCT
void compareAndExchangeSNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// oldval
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// newval
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// res
  st->print_raw("cmpxchgs ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // res
  st->print_raw(" = ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // oldval
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // newval
  st->print_raw("\t# (short, weak) if ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(" == ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // oldval
  st->print_raw(" then ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(" <-- ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // newval
}
#endif
#ifndef PRODUCT
void compareAndExchangeINode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// oldval
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// newval
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// res
  st->print_raw("cmpxchgw ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // res
  st->print_raw(" = ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // oldval
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // newval
  st->print_raw("\t# (int, weak) if ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(" == ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // oldval
  st->print_raw(" then ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(" <-- ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // newval
}
#endif
#ifndef PRODUCT
void compareAndExchangeLNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// oldval
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// newval
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// res
  st->print_raw("cmpxchg ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // res
  st->print_raw(" = ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // oldval
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // newval
  st->print_raw("\t# (long, weak) if ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(" == ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // oldval
  st->print_raw(" then ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(" <-- ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // newval
}
#endif
#ifndef PRODUCT
void compareAndExchangeNNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// oldval
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// newval
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// res
  st->print_raw("cmpxchgw ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // res
  st->print_raw(" = ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // oldval
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // newval
  st->print_raw("\t# (narrow oop, weak) if ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(" == ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // oldval
  st->print_raw(" then ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(" <-- ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // newval
}
#endif
#ifndef PRODUCT
void compareAndExchangePNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// oldval
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// newval
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// res
  st->print_raw("cmpxchg ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // res
  st->print_raw(" = ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // oldval
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // newval
  st->print_raw("\t# (ptr, weak) if ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(" == ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // oldval
  st->print_raw(" then ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(" <-- ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // newval
}
#endif
#ifndef PRODUCT
void compareAndExchangeBAcqNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// oldval
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// newval
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// res
  st->print_raw("cmpxchgb_acq ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // res
  st->print_raw(" = ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // oldval
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // newval
  st->print_raw("\t# (byte, weak) if ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(" == ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // oldval
  st->print_raw(" then ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(" <-- ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // newval
}
#endif
#ifndef PRODUCT
void compareAndExchangeSAcqNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// oldval
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// newval
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// res
  st->print_raw("cmpxchgs_acq ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // res
  st->print_raw(" = ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // oldval
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // newval
  st->print_raw("\t# (short, weak) if ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(" == ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // oldval
  st->print_raw(" then ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(" <-- ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // newval
}
#endif
#ifndef PRODUCT
void compareAndExchangeIAcqNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// oldval
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// newval
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// res
  st->print_raw("cmpxchgw_acq ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // res
  st->print_raw(" = ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // oldval
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // newval
  st->print_raw("\t# (int, weak) if ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(" == ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // oldval
  st->print_raw(" then ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(" <-- ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // newval
}
#endif
#ifndef PRODUCT
void compareAndExchangeLAcqNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// oldval
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// newval
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// res
  st->print_raw("cmpxchg_acq ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // res
  st->print_raw(" = ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // oldval
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // newval
  st->print_raw("\t# (long, weak) if ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(" == ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // oldval
  st->print_raw(" then ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(" <-- ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // newval
}
#endif
#ifndef PRODUCT
void compareAndExchangeNAcqNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// oldval
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// newval
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// res
  st->print_raw("cmpxchgw_acq ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // res
  st->print_raw(" = ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // oldval
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // newval
  st->print_raw("\t# (narrow oop, weak) if ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(" == ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // oldval
  st->print_raw(" then ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(" <-- ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // newval
}
#endif
#ifndef PRODUCT
void compareAndExchangePAcqNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// oldval
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// newval
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// res
  st->print_raw("cmpxchg_acq ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // res
  st->print_raw(" = ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // oldval
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // newval
  st->print_raw("\t# (ptr, weak) if ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(" == ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // oldval
  st->print_raw(" then ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(" <-- ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // newval
}
#endif
#ifndef PRODUCT
void weakCompareAndSwapBNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// oldval
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// newval
  st->print_raw("cmpxchgb ");
  opnd_array(0)->int_format(ra, this, st); // res
  st->print_raw(" = ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // oldval
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // newval
  st->print_raw("\t# (byte, weak) if ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(" == ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // oldval
  st->print_raw(" then ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(" <-- ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // newval
  st->print_raw("csetw ");
  opnd_array(0)->int_format(ra, this, st); // res
  st->print_raw(", EQ\t# ");
  opnd_array(0)->int_format(ra, this, st); // res
  st->print_raw(" <-- (EQ ? 1 : 0)");
}
#endif
#ifndef PRODUCT
void weakCompareAndSwapSNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// oldval
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// newval
  st->print_raw("cmpxchgs ");
  opnd_array(0)->int_format(ra, this, st); // res
  st->print_raw(" = ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // oldval
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // newval
  st->print_raw("\t# (short, weak) if ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(" == ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // oldval
  st->print_raw(" then ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(" <-- ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // newval
  st->print_raw("csetw ");
  opnd_array(0)->int_format(ra, this, st); // res
  st->print_raw(", EQ\t# ");
  opnd_array(0)->int_format(ra, this, st); // res
  st->print_raw(" <-- (EQ ? 1 : 0)");
}
#endif
#ifndef PRODUCT
void weakCompareAndSwapINode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// oldval
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// newval
  st->print_raw("cmpxchgw ");
  opnd_array(0)->int_format(ra, this, st); // res
  st->print_raw(" = ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // oldval
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // newval
  st->print_raw("\t# (int, weak) if ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(" == ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // oldval
  st->print_raw(" then ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(" <-- ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // newval
  st->print_raw("csetw ");
  opnd_array(0)->int_format(ra, this, st); // res
  st->print_raw(", EQ\t# ");
  opnd_array(0)->int_format(ra, this, st); // res
  st->print_raw(" <-- (EQ ? 1 : 0)");
}
#endif
#ifndef PRODUCT
void weakCompareAndSwapLNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// oldval
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// newval
  st->print_raw("cmpxchg ");
  opnd_array(0)->int_format(ra, this, st); // res
  st->print_raw(" = ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // oldval
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // newval
  st->print_raw("\t# (long, weak) if ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(" == ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // oldval
  st->print_raw(" then ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(" <-- ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // newval
  st->print_raw("csetw ");
  opnd_array(0)->int_format(ra, this, st); // res
  st->print_raw(", EQ\t# ");
  opnd_array(0)->int_format(ra, this, st); // res
  st->print_raw(" <-- (EQ ? 1 : 0)");
}
#endif
#ifndef PRODUCT
void weakCompareAndSwapNNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// oldval
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// newval
  st->print_raw("cmpxchgw ");
  opnd_array(0)->int_format(ra, this, st); // res
  st->print_raw(" = ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // oldval
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // newval
  st->print_raw("\t# (narrow oop, weak) if ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(" == ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // oldval
  st->print_raw(" then ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(" <-- ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // newval
  st->print_raw("csetw ");
  opnd_array(0)->int_format(ra, this, st); // res
  st->print_raw(", EQ\t# ");
  opnd_array(0)->int_format(ra, this, st); // res
  st->print_raw(" <-- (EQ ? 1 : 0)");
}
#endif
#ifndef PRODUCT
void weakCompareAndSwapPNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// oldval
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// newval
  st->print_raw("cmpxchg ");
  opnd_array(0)->int_format(ra, this, st); // res
  st->print_raw(" = ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // oldval
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // newval
  st->print_raw("\t# (ptr, weak) if ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(" == ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // oldval
  st->print_raw(" then ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(" <-- ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // newval
  st->print_raw("csetw ");
  opnd_array(0)->int_format(ra, this, st); // res
  st->print_raw(", EQ\t# ");
  opnd_array(0)->int_format(ra, this, st); // res
  st->print_raw(" <-- (EQ ? 1 : 0)");
}
#endif
#ifndef PRODUCT
void weakCompareAndSwapBAcqNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// oldval
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// newval
  st->print_raw("cmpxchgb_acq ");
  opnd_array(0)->int_format(ra, this, st); // res
  st->print_raw(" = ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // oldval
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // newval
  st->print_raw("\t# (byte, weak) if ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(" == ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // oldval
  st->print_raw(" then ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(" <-- ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // newval
  st->print_raw("csetw ");
  opnd_array(0)->int_format(ra, this, st); // res
  st->print_raw(", EQ\t# ");
  opnd_array(0)->int_format(ra, this, st); // res
  st->print_raw(" <-- (EQ ? 1 : 0)");
}
#endif
#ifndef PRODUCT
void weakCompareAndSwapSAcqNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// oldval
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// newval
  st->print_raw("cmpxchgs_acq ");
  opnd_array(0)->int_format(ra, this, st); // res
  st->print_raw(" = ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // oldval
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // newval
  st->print_raw("\t# (short, weak) if ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(" == ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // oldval
  st->print_raw(" then ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(" <-- ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // newval
  st->print_raw("csetw ");
  opnd_array(0)->int_format(ra, this, st); // res
  st->print_raw(", EQ\t# ");
  opnd_array(0)->int_format(ra, this, st); // res
  st->print_raw(" <-- (EQ ? 1 : 0)");
}
#endif
#ifndef PRODUCT
void weakCompareAndSwapIAcqNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// oldval
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// newval
  st->print_raw("cmpxchgw_acq ");
  opnd_array(0)->int_format(ra, this, st); // res
  st->print_raw(" = ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // oldval
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // newval
  st->print_raw("\t# (int, weak) if ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(" == ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // oldval
  st->print_raw(" then ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(" <-- ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // newval
  st->print_raw("csetw ");
  opnd_array(0)->int_format(ra, this, st); // res
  st->print_raw(", EQ\t# ");
  opnd_array(0)->int_format(ra, this, st); // res
  st->print_raw(" <-- (EQ ? 1 : 0)");
}
#endif
#ifndef PRODUCT
void weakCompareAndSwapLAcqNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// oldval
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// newval
  st->print_raw("cmpxchg_acq ");
  opnd_array(0)->int_format(ra, this, st); // res
  st->print_raw(" = ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // oldval
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // newval
  st->print_raw("\t# (long, weak) if ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(" == ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // oldval
  st->print_raw(" then ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(" <-- ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // newval
  st->print_raw("csetw ");
  opnd_array(0)->int_format(ra, this, st); // res
  st->print_raw(", EQ\t# ");
  opnd_array(0)->int_format(ra, this, st); // res
  st->print_raw(" <-- (EQ ? 1 : 0)");
}
#endif
#ifndef PRODUCT
void weakCompareAndSwapNAcqNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// oldval
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// newval
  st->print_raw("cmpxchgw_acq ");
  opnd_array(0)->int_format(ra, this, st); // res
  st->print_raw(" = ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // oldval
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // newval
  st->print_raw("\t# (narrow oop, weak) if ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(" == ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // oldval
  st->print_raw(" then ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(" <-- ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // newval
  st->print_raw("csetw ");
  opnd_array(0)->int_format(ra, this, st); // res
  st->print_raw(", EQ\t# ");
  opnd_array(0)->int_format(ra, this, st); // res
  st->print_raw(" <-- (EQ ? 1 : 0)");
}
#endif
#ifndef PRODUCT
void weakCompareAndSwapPAcqNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// oldval
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// newval
  st->print_raw("cmpxchg_acq ");
  opnd_array(0)->int_format(ra, this, st); // res
  st->print_raw(" = ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // oldval
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // newval
  st->print_raw("\t# (ptr, weak) if ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(" == ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // oldval
  st->print_raw(" then ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(" <-- ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // newval
  st->print_raw("csetw ");
  opnd_array(0)->int_format(ra, this, st); // res
  st->print_raw(", EQ\t# ");
  opnd_array(0)->int_format(ra, this, st); // res
  st->print_raw(" <-- (EQ ? 1 : 0)");
}
#endif
#ifndef PRODUCT
void get_and_setINode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// newv
  st->print_raw("atomic_xchgw  ");
  opnd_array(0)->int_format(ra, this, st); // prev
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // newv
  st->print_raw(", [");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("]");
}
#endif
#ifndef PRODUCT
void get_and_setLNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// newv
  st->print_raw("atomic_xchg  ");
  opnd_array(0)->int_format(ra, this, st); // prev
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // newv
  st->print_raw(", [");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("]");
}
#endif
#ifndef PRODUCT
void get_and_setNNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// newv
  st->print_raw("atomic_xchgw ");
  opnd_array(0)->int_format(ra, this, st); // prev
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // newv
  st->print_raw(", [");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("]");
}
#endif
#ifndef PRODUCT
void get_and_setPNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// newv
  st->print_raw("atomic_xchg  ");
  opnd_array(0)->int_format(ra, this, st); // prev
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // newv
  st->print_raw(", [");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("]");
}
#endif
#ifndef PRODUCT
void get_and_setIAcqNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// newv
  st->print_raw("atomic_xchgw_acq  ");
  opnd_array(0)->int_format(ra, this, st); // prev
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // newv
  st->print_raw(", [");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("]");
}
#endif
#ifndef PRODUCT
void get_and_setLAcqNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// newv
  st->print_raw("atomic_xchg_acq  ");
  opnd_array(0)->int_format(ra, this, st); // prev
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // newv
  st->print_raw(", [");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("]");
}
#endif
#ifndef PRODUCT
void get_and_setNAcqNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// newv
  st->print_raw("atomic_xchgw_acq ");
  opnd_array(0)->int_format(ra, this, st); // prev
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // newv
  st->print_raw(", [");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("]");
}
#endif
#ifndef PRODUCT
void get_and_setPAcqNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// newv
  st->print_raw("atomic_xchg_acq  ");
  opnd_array(0)->int_format(ra, this, st); // prev
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // newv
  st->print_raw(", [");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("]");
}
#endif
#ifndef PRODUCT
void get_and_addLNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// incr
  st->print_raw("get_and_addL ");
  opnd_array(0)->int_format(ra, this, st); // newval
  st->print_raw(", [");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("], ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // incr
}
#endif
#ifndef PRODUCT
void get_and_addL_no_resNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// incr
  st->print_raw("get_and_addL [");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("], ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // incr
}
#endif
#ifndef PRODUCT
void get_and_addLiNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// incr
  st->print_raw("get_and_addL ");
  opnd_array(0)->int_format(ra, this, st); // newval
  st->print_raw(", [");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("], ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // incr
}
#endif
#ifndef PRODUCT
void get_and_addLi_no_resNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// incr
  st->print_raw("get_and_addL [");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("], ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // incr
}
#endif
#ifndef PRODUCT
void get_and_addINode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// incr
  st->print_raw("get_and_addI ");
  opnd_array(0)->int_format(ra, this, st); // newval
  st->print_raw(", [");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("], ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // incr
}
#endif
#ifndef PRODUCT
void get_and_addI_no_resNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// incr
  st->print_raw("get_and_addI [");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("], ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // incr
}
#endif
#ifndef PRODUCT
void get_and_addIiNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// incr
  st->print_raw("get_and_addI ");
  opnd_array(0)->int_format(ra, this, st); // newval
  st->print_raw(", [");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("], ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // incr
}
#endif
#ifndef PRODUCT
void get_and_addIi_no_resNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// incr
  st->print_raw("get_and_addI [");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("], ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // incr
}
#endif
#ifndef PRODUCT
void get_and_addLAcqNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// incr
  st->print_raw("get_and_addL_acq ");
  opnd_array(0)->int_format(ra, this, st); // newval
  st->print_raw(", [");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("], ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // incr
}
#endif
#ifndef PRODUCT
void get_and_addL_no_resAcqNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// incr
  st->print_raw("get_and_addL_acq [");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("], ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // incr
}
#endif
#ifndef PRODUCT
void get_and_addLiAcqNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// incr
  st->print_raw("get_and_addL_acq ");
  opnd_array(0)->int_format(ra, this, st); // newval
  st->print_raw(", [");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("], ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // incr
}
#endif
#ifndef PRODUCT
void get_and_addLi_no_resAcqNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// incr
  st->print_raw("get_and_addL_acq [");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("], ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // incr
}
#endif
#ifndef PRODUCT
void get_and_addIAcqNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// incr
  st->print_raw("get_and_addI_acq ");
  opnd_array(0)->int_format(ra, this, st); // newval
  st->print_raw(", [");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("], ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // incr
}
#endif
#ifndef PRODUCT
void get_and_addI_no_resAcqNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// incr
  st->print_raw("get_and_addI_acq [");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("], ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // incr
}
#endif
#ifndef PRODUCT
void get_and_addIiAcqNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// incr
  st->print_raw("get_and_addI_acq ");
  opnd_array(0)->int_format(ra, this, st); // newval
  st->print_raw(", [");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("], ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // incr
}
#endif
#ifndef PRODUCT
void get_and_addIi_no_resAcqNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// incr
  st->print_raw("get_and_addI_acq [");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("], ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // incr
}
#endif
#ifndef PRODUCT
void cmpU3_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("cmpw ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw("\n\t");
  st->print_raw("csetw ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ne\n\t");
  st->print_raw("cnegw ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", lo\t# CmpU3(reg)");
}
#endif
#ifndef PRODUCT
void cmpU3_reg_immNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("subsw zr, ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw("\n\t");
  st->print_raw("csetw ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ne\n\t");
  st->print_raw("cnegw ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", lo\t# CmpU3(imm)");
}
#endif
#ifndef PRODUCT
void cmpUL3_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("cmp ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw("\n\t");
  st->print_raw("csetw ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ne\n\t");
  st->print_raw("cnegw ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", lo\t# CmpUL3(reg)");
}
#endif
#ifndef PRODUCT
void cmpUL3_reg_immNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("subs zr, ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw("\n\t");
  st->print_raw("csetw ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ne\n\t");
  st->print_raw("cnegw ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", lo\t# CmpUL3(imm)");
}
#endif
#ifndef PRODUCT
void cmpL3_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("cmp ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw("\n\t");
  st->print_raw("csetw ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ne\n\t");
  st->print_raw("cnegw ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", lt\t# CmpL3(reg)");
}
#endif
#ifndef PRODUCT
void cmpL3_reg_immNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("subs zr, ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw("\n\t");
  st->print_raw("csetw ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ne\n\t");
  st->print_raw("cnegw ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", lt\t# CmpL3(imm)");
}
#endif
#ifndef PRODUCT
void cmovI_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// cmp
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// cr
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src1
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src2
  st->print_raw("cselw ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // src2
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src1
  st->print_raw(" ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // cmp
  st->print_raw("\t# signed, int");
}
#endif
#ifndef PRODUCT
void cmovUI_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// cmp
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// cr
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src1
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src2
  st->print_raw("cselw ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // src2
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src1
  st->print_raw(" ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // cmp
  st->print_raw("\t# unsigned, int");
}
#endif
#ifndef PRODUCT
void cmovI_zero_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// cmp
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// cr
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// zero
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src
  st->print_raw("cselw ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // src
  st->print_raw(", zr ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // cmp
  st->print_raw("\t# signed, int");
}
#endif
#ifndef PRODUCT
void cmovUI_zero_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// cmp
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// cr
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// zero
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src
  st->print_raw("cselw ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // src
  st->print_raw(", zr ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // cmp
  st->print_raw("\t# unsigned, int");
}
#endif
#ifndef PRODUCT
void cmovI_reg_zeroNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// cmp
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// cr
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// zero
  st->print_raw("cselw ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", zr, ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src
  st->print_raw(" ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // cmp
  st->print_raw("\t# signed, int");
}
#endif
#ifndef PRODUCT
void cmovUI_reg_zeroNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// cmp
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// cr
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// zero
  st->print_raw("cselw ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", zr, ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src
  st->print_raw(" ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // cmp
  st->print_raw("\t# unsigned, int");
}
#endif
#ifndef PRODUCT
void cmovI_reg_zero_oneNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// cmp
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// cr
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// one
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// zero
  st->print_raw("csincw ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", zr, zr ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // cmp
  st->print_raw("\t# signed, int");
}
#endif
#ifndef PRODUCT
void cmovUI_reg_zero_oneNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// cmp
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// cr
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// one
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// zero
  st->print_raw("csincw ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", zr, zr ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // cmp
  st->print_raw("\t# unsigned, int");
}
#endif
#ifndef PRODUCT
void cmovL_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// cmp
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// cr
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src1
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src2
  st->print_raw("csel ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // src2
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src1
  st->print_raw(" ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // cmp
  st->print_raw("\t# signed, long");
}
#endif
#ifndef PRODUCT
void cmovUL_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// cmp
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// cr
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src1
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src2
  st->print_raw("csel ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // src2
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src1
  st->print_raw(" ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // cmp
  st->print_raw("\t# unsigned, long");
}
#endif
#ifndef PRODUCT
void cmovL_reg_zeroNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// cmp
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// cr
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// zero
  st->print_raw("csel ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", zr, ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src
  st->print_raw(" ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // cmp
  st->print_raw("\t# signed, long");
}
#endif
#ifndef PRODUCT
void cmovUL_reg_zeroNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// cmp
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// cr
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// zero
  st->print_raw("csel ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", zr, ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src
  st->print_raw(" ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // cmp
  st->print_raw("\t# unsigned, long");
}
#endif
#ifndef PRODUCT
void cmovL_zero_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// cmp
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// cr
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// zero
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src
  st->print_raw("csel ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // src
  st->print_raw(", zr ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // cmp
  st->print_raw("\t# signed, long");
}
#endif
#ifndef PRODUCT
void cmovUL_zero_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// cmp
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// cr
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// zero
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src
  st->print_raw("csel ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // src
  st->print_raw(", zr ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // cmp
  st->print_raw("\t# unsigned, long");
}
#endif
#ifndef PRODUCT
void cmovP_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// cmp
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// cr
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src1
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src2
  st->print_raw("csel ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // src2
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src1
  st->print_raw(" ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // cmp
  st->print_raw("\t# signed, ptr");
}
#endif
#ifndef PRODUCT
void cmovUP_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// cmp
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// cr
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src1
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src2
  st->print_raw("csel ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // src2
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src1
  st->print_raw(" ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // cmp
  st->print_raw("\t# unsigned, ptr");
}
#endif
#ifndef PRODUCT
void cmovP_reg_zeroNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// cmp
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// cr
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// zero
  st->print_raw("csel ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", zr, ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src
  st->print_raw(" ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // cmp
  st->print_raw("\t# signed, ptr");
}
#endif
#ifndef PRODUCT
void cmovUP_reg_zeroNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// cmp
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// cr
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// zero
  st->print_raw("csel ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", zr, ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src
  st->print_raw(" ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // cmp
  st->print_raw("\t# unsigned, ptr");
}
#endif
#ifndef PRODUCT
void cmovP_zero_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// cmp
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// cr
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// zero
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src
  st->print_raw("csel ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // src
  st->print_raw(", zr ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // cmp
  st->print_raw("\t# signed, ptr");
}
#endif
#ifndef PRODUCT
void cmovUP_zero_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// cmp
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// cr
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// zero
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src
  st->print_raw("csel ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // src
  st->print_raw(", zr ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // cmp
  st->print_raw("\t# unsigned, ptr");
}
#endif
#ifndef PRODUCT
void cmovN_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// cmp
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// cr
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src1
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src2
  st->print_raw("cselw ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // src2
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src1
  st->print_raw(" ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // cmp
  st->print_raw("\t# signed, compressed ptr");
}
#endif
#ifndef PRODUCT
void cmovUN_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// cmp
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// cr
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src1
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src2
  st->print_raw("cselw ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // src2
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src1
  st->print_raw(" ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // cmp
  st->print_raw("\t# signed, compressed ptr");
}
#endif
#ifndef PRODUCT
void cmovN_reg_zeroNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// cmp
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// cr
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// zero
  st->print_raw("cselw ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", zr, ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src
  st->print_raw(" ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // cmp
  st->print_raw("\t# signed, compressed ptr");
}
#endif
#ifndef PRODUCT
void cmovUN_reg_zeroNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// cmp
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// cr
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// zero
  st->print_raw("cselw ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", zr, ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src
  st->print_raw(" ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // cmp
  st->print_raw("\t# unsigned, compressed ptr");
}
#endif
#ifndef PRODUCT
void cmovN_zero_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// cmp
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// cr
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// zero
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src
  st->print_raw("cselw ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // src
  st->print_raw(", zr ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // cmp
  st->print_raw("\t# signed, compressed ptr");
}
#endif
#ifndef PRODUCT
void cmovUN_zero_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// cmp
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// cr
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// zero
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src
  st->print_raw("cselw ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // src
  st->print_raw(", zr ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // cmp
  st->print_raw("\t# unsigned, compressed ptr");
}
#endif
#ifndef PRODUCT
void cmovF_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// cmp
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// cr
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src1
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src2
  st->print_raw("fcsels ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src1
  st->print_raw(", ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // src2
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // cmp
  st->print_raw("\t# signed cmove float\n\t");
}
#endif
#ifndef PRODUCT
void cmovUF_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// cmp
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// cr
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src1
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src2
  st->print_raw("fcsels ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src1
  st->print_raw(", ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // src2
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // cmp
  st->print_raw("\t# unsigned cmove float\n\t");
}
#endif
#ifndef PRODUCT
void cmovD_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// cmp
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// cr
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src1
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src2
  st->print_raw("fcseld ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src1
  st->print_raw(", ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // src2
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // cmp
  st->print_raw("\t# signed cmove float\n\t");
}
#endif
#ifndef PRODUCT
void cmovUD_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// cmp
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// cr
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src1
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src2
  st->print_raw("fcseld ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src1
  st->print_raw(", ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // src2
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // cmp
  st->print_raw("\t# unsigned cmove float\n\t");
}
#endif
#ifndef PRODUCT
void addI_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("addw  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void addI_reg_immNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("addw ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void addI_reg_imm_i2lNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("addw ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void addP_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("add ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw("\t# ptr");
}
#endif
#ifndef PRODUCT
void addP_reg_reg_extNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("add ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", sxtw\t# ptr");
}
#endif
#ifndef PRODUCT
void addP_reg_reg_lslNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// scale
  st->print_raw("add ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", LShiftL ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // scale
  st->print_raw("\t# ptr");
}
#endif
#ifndef PRODUCT
void addP_reg_reg_ext_shiftNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// scale
  st->print_raw("add ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", I2L ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // scale
  st->print_raw("\t# ptr");
}
#endif
#ifndef PRODUCT
void lshift_extNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// scale
  st->print_raw("sbfiz ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // scale
  st->print_raw(" & 63, -");
  opnd_array(2)->ext_format(ra, this,idx2, st); // scale
  st->print_raw(" & 63\t");
}
#endif
#ifndef PRODUCT
void addP_reg_immNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("add ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw("\t# ptr");
}
#endif
#ifndef PRODUCT
void addL_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("add  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void addL_reg_immNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("add ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void subI_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("subw  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void subI_reg_immNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("subw ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void subL_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("sub  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void subL_reg_immNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("sub");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void negI_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// zero
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  st->print_raw("negw ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
  st->print_raw("\t# int");
}
#endif
#ifndef PRODUCT
void negL_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// zero
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  st->print_raw("neg ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
  st->print_raw("\t# long");
}
#endif
#ifndef PRODUCT
void mulINode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("mulw  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void smulINode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("smull  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void smulI_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src2
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  st->print_raw("smull  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src1
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src2
}
#endif
#ifndef PRODUCT
void mulLNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("mul  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void mulHiL_rRegNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("smulh   ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw("\t# mulhi");
}
#endif
#ifndef PRODUCT
void umulHiL_rRegNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("umulh   ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw("\t# umulhi");
}
#endif
#ifndef PRODUCT
void maddINode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src3
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  st->print_raw("madd  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src1
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src2
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src3
}
#endif
#ifndef PRODUCT
void maddI_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src3
  st->print_raw("madd  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src3
}
#endif
#ifndef PRODUCT
void msubINode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src3
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  st->print_raw("msub  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src1
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src2
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src3
}
#endif
#ifndef PRODUCT
void mnegINode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// zero
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  st->print_raw("mneg  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src1
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src2
}
#endif
#ifndef PRODUCT
void mnegI_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src2
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// zero
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src1
  st->print_raw("mneg  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src1
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src2
}
#endif
#ifndef PRODUCT
void maddLNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src3
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  st->print_raw("madd  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src1
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src2
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src3
}
#endif
#ifndef PRODUCT
void maddL_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src3
  st->print_raw("madd  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src3
}
#endif
#ifndef PRODUCT
void msubLNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src3
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  st->print_raw("msub  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src1
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src2
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src3
}
#endif
#ifndef PRODUCT
void mnegLNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// zero
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  st->print_raw("mneg  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src1
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src2
}
#endif
#ifndef PRODUCT
void mnegL_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src2
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// zero
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src1
  st->print_raw("mneg  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src1
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src2
}
#endif
#ifndef PRODUCT
void smaddLNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src3
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  st->print_raw("smaddl  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src1
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src2
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src3
}
#endif
#ifndef PRODUCT
void smaddL_1Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src3
  st->print_raw("smaddl  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src3
}
#endif
#ifndef PRODUCT
void smaddL_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src3
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src1
  st->print_raw("smaddl  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src3
}
#endif
#ifndef PRODUCT
void smaddL_2Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src2
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src3
  st->print_raw("smaddl  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src1
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src2
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src3
}
#endif
#ifndef PRODUCT
void smsubLNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src3
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  st->print_raw("smsubl  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src1
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src2
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src3
}
#endif
#ifndef PRODUCT
void smsubL_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src3
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src1
  st->print_raw("smsubl  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src3
}
#endif
#ifndef PRODUCT
void smnegLNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// zero
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  st->print_raw("smnegl  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src1
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src2
}
#endif
#ifndef PRODUCT
void smnegL_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src2
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// zero
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src1
  st->print_raw("smnegl  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src1
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src2
}
#endif
#ifndef PRODUCT
void muladdS2INode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src3
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src4
  st->print_raw("mulw  rscratch1, ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw("\n\t");
  st->print_raw("maddw ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src3
  st->print_raw(", ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // src4
  st->print_raw(", rscratch1");
}
#endif
#ifndef PRODUCT
void divINode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("sdivw  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void divLNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("sdiv   ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void modINode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("sdivw  rscratch1, ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw("\n\t");
  st->print_raw("msubw  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", rscratch1, ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
}
#endif
#ifndef PRODUCT
void modLNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("sdiv   rscratch1, ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw("\n");
  st->print_raw("msub   ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", rscratch1, ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
}
#endif
#ifndef PRODUCT
void UdivI_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("udivw  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void UdivL_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("udiv   ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void UmodI_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("udivw  rscratch1, ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw("\n\t");
  st->print_raw("msubw  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", rscratch1, ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
}
#endif
#ifndef PRODUCT
void UModL_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("udiv   rscratch1, ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw("\n");
  st->print_raw("msub   ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", rscratch1, ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
}
#endif
#ifndef PRODUCT
void lShiftI_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("lslvw  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void lShiftI_reg_immNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("lslw ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", (");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(" & 0x1f)");
}
#endif
#ifndef PRODUCT
void urShiftI_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("lsrvw  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void urShiftI_reg_immNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("lsrw ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", (");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(" & 0x1f)");
}
#endif
#ifndef PRODUCT
void rShiftI_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("asrvw  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void rShiftI_reg_immNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("asrw ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", (");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(" & 0x1f)");
}
#endif
#ifndef PRODUCT
void lShiftL_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("lslv  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void lShiftL_reg_immNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("lsl ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", (");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(" & 0x3f)");
}
#endif
#ifndef PRODUCT
void urShiftL_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("lsrv  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void urShiftL_reg_immNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("lsr ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", (");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(" & 0x3f)");
}
#endif
#ifndef PRODUCT
void urShiftP_reg_immNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("lsr ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", p2x(");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw("), (");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(" & 0x3f)");
}
#endif
#ifndef PRODUCT
void rShiftL_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("asrv  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void rShiftL_reg_immNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("asr ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", (");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(" & 0x3f)");
}
#endif
#ifndef PRODUCT
void regL_not_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// m1
  st->print_raw("eon  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", zr");
}
#endif
#ifndef PRODUCT
void regI_not_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// m1
  st->print_raw("eonw  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", zr");
}
#endif
#ifndef PRODUCT
void NegI_reg_URShift_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// zero
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  st->print_raw("negw  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src1
  st->print_raw(", LSR ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src2
}
#endif
#ifndef PRODUCT
void NegI_reg_RShift_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// zero
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  st->print_raw("negw  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src1
  st->print_raw(", ASR ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src2
}
#endif
#ifndef PRODUCT
void NegI_reg_LShift_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// zero
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  st->print_raw("negw  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src1
  st->print_raw(", LSL ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src2
}
#endif
#ifndef PRODUCT
void NegL_reg_URShift_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// zero
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  st->print_raw("neg  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src1
  st->print_raw(", LSR ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src2
}
#endif
#ifndef PRODUCT
void NegL_reg_RShift_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// zero
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  st->print_raw("neg  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src1
  st->print_raw(", ASR ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src2
}
#endif
#ifndef PRODUCT
void NegL_reg_LShift_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// zero
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  st->print_raw("neg  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src1
  st->print_raw(", LSL ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src2
}
#endif
#ifndef PRODUCT
void AndI_reg_not_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// m1
  st->print_raw("bicw  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void AndI_reg_not_reg_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src2
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// m1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src1
  st->print_raw("bicw  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src1
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src2
}
#endif
#ifndef PRODUCT
void AndL_reg_not_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// m1
  st->print_raw("bic  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void AndL_reg_not_reg_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src2
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// m1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src1
  st->print_raw("bic  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src1
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src2
}
#endif
#ifndef PRODUCT
void OrI_reg_not_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// m1
  st->print_raw("ornw  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void OrI_reg_not_reg_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src2
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// m1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src1
  st->print_raw("ornw  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src1
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src2
}
#endif
#ifndef PRODUCT
void OrL_reg_not_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// m1
  st->print_raw("orn  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void OrL_reg_not_reg_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src2
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// m1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src1
  st->print_raw("orn  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src1
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src2
}
#endif
#ifndef PRODUCT
void XorI_reg_not_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// m1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src1
  st->print_raw("eonw  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void XorI_reg_not_reg_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src2
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// m1
  st->print_raw("eonw  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src1
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src2
}
#endif
#ifndef PRODUCT
void XorL_reg_not_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// m1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src1
  st->print_raw("eon  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void XorL_reg_not_reg_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src2
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// m1
  st->print_raw("eon  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src1
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src2
}
#endif
#ifndef PRODUCT
void AndI_reg_URShift_not_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src3
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src4
  st->print_raw("bicw  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", LSR ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src3
}
#endif
#ifndef PRODUCT
void AndI_reg_URShift_not_reg_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src2
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src3
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src4
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src1
  st->print_raw("bicw  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // src1
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src2
  st->print_raw(", LSR ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src3
}
#endif
#ifndef PRODUCT
void AndL_reg_URShift_not_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src3
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src4
  st->print_raw("bic  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", LSR ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src3
}
#endif
#ifndef PRODUCT
void AndL_reg_URShift_not_reg_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src2
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src3
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src4
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src1
  st->print_raw("bic  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // src1
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src2
  st->print_raw(", LSR ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src3
}
#endif
#ifndef PRODUCT
void AndI_reg_RShift_not_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src3
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src4
  st->print_raw("bicw  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", ASR ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src3
}
#endif
#ifndef PRODUCT
void AndI_reg_RShift_not_reg_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src2
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src3
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src4
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src1
  st->print_raw("bicw  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // src1
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src2
  st->print_raw(", ASR ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src3
}
#endif
#ifndef PRODUCT
void AndL_reg_RShift_not_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src3
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src4
  st->print_raw("bic  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", ASR ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src3
}
#endif
#ifndef PRODUCT
void AndL_reg_RShift_not_reg_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src2
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src3
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src4
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src1
  st->print_raw("bic  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // src1
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src2
  st->print_raw(", ASR ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src3
}
#endif
#ifndef PRODUCT
void AndI_reg_RotateRight_not_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src3
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src4
  st->print_raw("bicw  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", ROR ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src3
}
#endif
#ifndef PRODUCT
void AndI_reg_RotateRight_not_reg_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src2
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src3
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src4
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src1
  st->print_raw("bicw  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // src1
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src2
  st->print_raw(", ROR ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src3
}
#endif
#ifndef PRODUCT
void AndL_reg_RotateRight_not_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src3
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src4
  st->print_raw("bic  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", ROR ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src3
}
#endif
#ifndef PRODUCT
void AndL_reg_RotateRight_not_reg_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src2
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src3
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src4
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src1
  st->print_raw("bic  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // src1
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src2
  st->print_raw(", ROR ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src3
}
#endif
#ifndef PRODUCT
void AndI_reg_LShift_not_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src3
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src4
  st->print_raw("bicw  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", LSL ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src3
}
#endif
#ifndef PRODUCT
void AndI_reg_LShift_not_reg_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src2
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src3
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src4
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src1
  st->print_raw("bicw  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // src1
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src2
  st->print_raw(", LSL ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src3
}
#endif
#ifndef PRODUCT
void AndL_reg_LShift_not_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src3
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src4
  st->print_raw("bic  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", LSL ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src3
}
#endif
#ifndef PRODUCT
void AndL_reg_LShift_not_reg_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src2
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src3
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src4
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src1
  st->print_raw("bic  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // src1
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src2
  st->print_raw(", LSL ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src3
}
#endif
#ifndef PRODUCT
void XorI_reg_URShift_not_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src4
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src3
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src1
  st->print_raw("eonw  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", LSR ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src3
}
#endif
#ifndef PRODUCT
void XorI_reg_URShift_not_reg_1Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src2
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src3
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src1
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src4
  st->print_raw("eonw  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src1
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src2
  st->print_raw(", LSR ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src3
}
#endif
#ifndef PRODUCT
void XorI_reg_URShift_not_reg_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src4
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src3
  st->print_raw("eonw  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src1
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src2
  st->print_raw(", LSR ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // src3
}
#endif
#ifndef PRODUCT
void XorI_reg_URShift_not_reg_2Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src3
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src4
  st->print_raw("eonw  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", LSR ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src3
}
#endif
#ifndef PRODUCT
void XorL_reg_URShift_not_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src4
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src3
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src1
  st->print_raw("eon  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", LSR ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src3
}
#endif
#ifndef PRODUCT
void XorL_reg_URShift_not_reg_1Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src2
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src3
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src1
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src4
  st->print_raw("eon  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src1
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src2
  st->print_raw(", LSR ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src3
}
#endif
#ifndef PRODUCT
void XorL_reg_URShift_not_reg_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src4
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src3
  st->print_raw("eon  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src1
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src2
  st->print_raw(", LSR ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // src3
}
#endif
#ifndef PRODUCT
void XorL_reg_URShift_not_reg_2Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src3
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src4
  st->print_raw("eon  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", LSR ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src3
}
#endif
#ifndef PRODUCT
void XorI_reg_RShift_not_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src4
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src3
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src1
  st->print_raw("eonw  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", ASR ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src3
}
#endif
#ifndef PRODUCT
void XorI_reg_RShift_not_reg_1Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src2
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src3
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src1
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src4
  st->print_raw("eonw  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src1
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src2
  st->print_raw(", ASR ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src3
}
#endif
#ifndef PRODUCT
void XorI_reg_RShift_not_reg_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src4
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src3
  st->print_raw("eonw  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src1
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src2
  st->print_raw(", ASR ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // src3
}
#endif
#ifndef PRODUCT
void XorI_reg_RShift_not_reg_2Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src3
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src4
  st->print_raw("eonw  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", ASR ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src3
}
#endif
#ifndef PRODUCT
void XorL_reg_RShift_not_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src4
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src3
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src1
  st->print_raw("eon  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", ASR ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src3
}
#endif
#ifndef PRODUCT
void XorL_reg_RShift_not_reg_1Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src2
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src3
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src1
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src4
  st->print_raw("eon  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src1
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src2
  st->print_raw(", ASR ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src3
}
#endif
#ifndef PRODUCT
void XorL_reg_RShift_not_reg_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src4
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src3
  st->print_raw("eon  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src1
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src2
  st->print_raw(", ASR ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // src3
}
#endif
#ifndef PRODUCT
void XorL_reg_RShift_not_reg_2Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src3
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src4
  st->print_raw("eon  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", ASR ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src3
}
#endif
#ifndef PRODUCT
void XorI_reg_RotateRight_not_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src4
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src3
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src1
  st->print_raw("eonw  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", ROR ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src3
}
#endif
#ifndef PRODUCT
void XorI_reg_RotateRight_not_reg_1Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src2
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src3
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src1
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src4
  st->print_raw("eonw  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src1
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src2
  st->print_raw(", ROR ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src3
}
#endif
#ifndef PRODUCT
void XorI_reg_RotateRight_not_reg_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src4
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src3
  st->print_raw("eonw  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src1
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src2
  st->print_raw(", ROR ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // src3
}
#endif
#ifndef PRODUCT
void XorI_reg_RotateRight_not_reg_2Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src3
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src4
  st->print_raw("eonw  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", ROR ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src3
}
#endif
#ifndef PRODUCT
void XorL_reg_RotateRight_not_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src4
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src3
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src1
  st->print_raw("eon  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", ROR ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src3
}
#endif
#ifndef PRODUCT
void XorL_reg_RotateRight_not_reg_1Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src2
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src3
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src1
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src4
  st->print_raw("eon  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src1
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src2
  st->print_raw(", ROR ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src3
}
#endif
#ifndef PRODUCT
void XorL_reg_RotateRight_not_reg_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src4
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src3
  st->print_raw("eon  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src1
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src2
  st->print_raw(", ROR ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // src3
}
#endif
#ifndef PRODUCT
void XorL_reg_RotateRight_not_reg_2Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src3
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src4
  st->print_raw("eon  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", ROR ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src3
}
#endif
#ifndef PRODUCT
void XorI_reg_LShift_not_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src4
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src3
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src1
  st->print_raw("eonw  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", LSL ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src3
}
#endif
#ifndef PRODUCT
void XorI_reg_LShift_not_reg_1Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src2
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src3
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src1
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src4
  st->print_raw("eonw  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src1
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src2
  st->print_raw(", LSL ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src3
}
#endif
#ifndef PRODUCT
void XorI_reg_LShift_not_reg_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src4
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src3
  st->print_raw("eonw  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src1
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src2
  st->print_raw(", LSL ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // src3
}
#endif
#ifndef PRODUCT
void XorI_reg_LShift_not_reg_2Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src3
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src4
  st->print_raw("eonw  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", LSL ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src3
}
#endif
#ifndef PRODUCT
void XorL_reg_LShift_not_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src4
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src3
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src1
  st->print_raw("eon  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", LSL ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src3
}
#endif
#ifndef PRODUCT
void XorL_reg_LShift_not_reg_1Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src2
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src3
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src1
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src4
  st->print_raw("eon  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src1
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src2
  st->print_raw(", LSL ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src3
}
#endif
#ifndef PRODUCT
void XorL_reg_LShift_not_reg_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src4
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src3
  st->print_raw("eon  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src1
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src2
  st->print_raw(", LSL ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // src3
}
#endif
#ifndef PRODUCT
void XorL_reg_LShift_not_reg_2Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src3
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src4
  st->print_raw("eon  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", LSL ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src3
}
#endif
#ifndef PRODUCT
void OrI_reg_URShift_not_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src3
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src4
  st->print_raw("ornw  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", LSR ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src3
}
#endif
#ifndef PRODUCT
void OrI_reg_URShift_not_reg_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src2
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src3
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src4
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src1
  st->print_raw("ornw  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // src1
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src2
  st->print_raw(", LSR ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src3
}
#endif
#ifndef PRODUCT
void OrL_reg_URShift_not_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src3
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src4
  st->print_raw("orn  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", LSR ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src3
}
#endif
#ifndef PRODUCT
void OrL_reg_URShift_not_reg_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src2
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src3
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src4
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src1
  st->print_raw("orn  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // src1
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src2
  st->print_raw(", LSR ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src3
}
#endif
#ifndef PRODUCT
void OrI_reg_RShift_not_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src3
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src4
  st->print_raw("ornw  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", ASR ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src3
}
#endif
#ifndef PRODUCT
void OrI_reg_RShift_not_reg_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src2
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src3
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src4
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src1
  st->print_raw("ornw  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // src1
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src2
  st->print_raw(", ASR ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src3
}
#endif
#ifndef PRODUCT
void OrL_reg_RShift_not_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src3
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src4
  st->print_raw("orn  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", ASR ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src3
}
#endif
#ifndef PRODUCT
void OrL_reg_RShift_not_reg_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src2
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src3
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src4
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src1
  st->print_raw("orn  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // src1
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src2
  st->print_raw(", ASR ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src3
}
#endif
#ifndef PRODUCT
void OrI_reg_RotateRight_not_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src3
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src4
  st->print_raw("ornw  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", ROR ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src3
}
#endif
#ifndef PRODUCT
void OrI_reg_RotateRight_not_reg_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src2
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src3
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src4
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src1
  st->print_raw("ornw  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // src1
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src2
  st->print_raw(", ROR ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src3
}
#endif
#ifndef PRODUCT
void OrL_reg_RotateRight_not_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src3
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src4
  st->print_raw("orn  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", ROR ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src3
}
#endif
#ifndef PRODUCT
void OrL_reg_RotateRight_not_reg_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src2
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src3
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src4
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src1
  st->print_raw("orn  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // src1
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src2
  st->print_raw(", ROR ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src3
}
#endif
#ifndef PRODUCT
void OrI_reg_LShift_not_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src3
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src4
  st->print_raw("ornw  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", LSL ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src3
}
#endif
#ifndef PRODUCT
void OrI_reg_LShift_not_reg_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src2
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src3
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src4
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src1
  st->print_raw("ornw  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // src1
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src2
  st->print_raw(", LSL ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src3
}
#endif
#ifndef PRODUCT
void OrL_reg_LShift_not_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src3
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src4
  st->print_raw("orn  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", LSL ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src3
}
#endif
#ifndef PRODUCT
void OrL_reg_LShift_not_reg_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src2
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src3
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src4
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src1
  st->print_raw("orn  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // src1
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src2
  st->print_raw(", LSL ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src3
}
#endif
#ifndef PRODUCT
void AndI_reg_URShift_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src3
  st->print_raw("andw  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", LSR ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src3
}
#endif
#ifndef PRODUCT
void AndI_reg_URShift_reg_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src2
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src3
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src1
  st->print_raw("andw  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src1
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src2
  st->print_raw(", LSR ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src3
}
#endif
#ifndef PRODUCT
void AndL_reg_URShift_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src3
  st->print_raw("andr  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", LSR ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src3
}
#endif
#ifndef PRODUCT
void AndL_reg_URShift_reg_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src2
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src3
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src1
  st->print_raw("andr  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src1
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src2
  st->print_raw(", LSR ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src3
}
#endif
#ifndef PRODUCT
void AndI_reg_RShift_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src3
  st->print_raw("andw  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", ASR ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src3
}
#endif
#ifndef PRODUCT
void AndI_reg_RShift_reg_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src2
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src3
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src1
  st->print_raw("andw  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src1
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src2
  st->print_raw(", ASR ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src3
}
#endif
#ifndef PRODUCT
void AndL_reg_RShift_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src3
  st->print_raw("andr  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", ASR ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src3
}
#endif
#ifndef PRODUCT
void AndL_reg_RShift_reg_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src2
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src3
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src1
  st->print_raw("andr  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src1
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src2
  st->print_raw(", ASR ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src3
}
#endif
#ifndef PRODUCT
void AndI_reg_LShift_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src3
  st->print_raw("andw  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", LSL ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src3
}
#endif
#ifndef PRODUCT
void AndI_reg_LShift_reg_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src2
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src3
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src1
  st->print_raw("andw  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src1
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src2
  st->print_raw(", LSL ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src3
}
#endif
#ifndef PRODUCT
void AndL_reg_LShift_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src3
  st->print_raw("andr  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", LSL ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src3
}
#endif
#ifndef PRODUCT
void AndL_reg_LShift_reg_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src2
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src3
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src1
  st->print_raw("andr  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src1
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src2
  st->print_raw(", LSL ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src3
}
#endif
#ifndef PRODUCT
void AndI_reg_RotateRight_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src3
  st->print_raw("andw  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", ROR ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src3
}
#endif
#ifndef PRODUCT
void AndI_reg_RotateRight_reg_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src2
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src3
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src1
  st->print_raw("andw  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src1
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src2
  st->print_raw(", ROR ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src3
}
#endif
#ifndef PRODUCT
void AndL_reg_RotateRight_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src3
  st->print_raw("andr  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", ROR ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src3
}
#endif
#ifndef PRODUCT
void AndL_reg_RotateRight_reg_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src2
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src3
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src1
  st->print_raw("andr  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src1
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src2
  st->print_raw(", ROR ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src3
}
#endif
#ifndef PRODUCT
void XorI_reg_URShift_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src3
  st->print_raw("eorw  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", LSR ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src3
}
#endif
#ifndef PRODUCT
void XorI_reg_URShift_reg_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src2
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src3
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src1
  st->print_raw("eorw  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src1
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src2
  st->print_raw(", LSR ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src3
}
#endif
#ifndef PRODUCT
void XorL_reg_URShift_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src3
  st->print_raw("eor  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", LSR ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src3
}
#endif
#ifndef PRODUCT
void XorL_reg_URShift_reg_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src2
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src3
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src1
  st->print_raw("eor  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src1
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src2
  st->print_raw(", LSR ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src3
}
#endif
#ifndef PRODUCT
void XorI_reg_RShift_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src3
  st->print_raw("eorw  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", ASR ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src3
}
#endif
#ifndef PRODUCT
void XorI_reg_RShift_reg_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src2
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src3
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src1
  st->print_raw("eorw  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src1
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src2
  st->print_raw(", ASR ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src3
}
#endif
#ifndef PRODUCT
void XorL_reg_RShift_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src3
  st->print_raw("eor  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", ASR ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src3
}
#endif
#ifndef PRODUCT
void XorL_reg_RShift_reg_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src2
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src3
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src1
  st->print_raw("eor  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src1
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src2
  st->print_raw(", ASR ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src3
}
#endif
#ifndef PRODUCT
void XorI_reg_LShift_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src3
  st->print_raw("eorw  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", LSL ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src3
}
#endif
#ifndef PRODUCT
void XorI_reg_LShift_reg_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src2
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src3
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src1
  st->print_raw("eorw  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src1
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src2
  st->print_raw(", LSL ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src3
}
#endif
#ifndef PRODUCT
void XorL_reg_LShift_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src3
  st->print_raw("eor  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", LSL ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src3
}
#endif
#ifndef PRODUCT
void XorL_reg_LShift_reg_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src2
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src3
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src1
  st->print_raw("eor  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src1
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src2
  st->print_raw(", LSL ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src3
}
#endif
#ifndef PRODUCT
void XorI_reg_RotateRight_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src3
  st->print_raw("eorw  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", ROR ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src3
}
#endif
#ifndef PRODUCT
void XorI_reg_RotateRight_reg_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src2
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src3
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src1
  st->print_raw("eorw  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src1
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src2
  st->print_raw(", ROR ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src3
}
#endif
#ifndef PRODUCT
void XorL_reg_RotateRight_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src3
  st->print_raw("eor  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", ROR ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src3
}
#endif
#ifndef PRODUCT
void XorL_reg_RotateRight_reg_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src2
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src3
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src1
  st->print_raw("eor  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src1
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src2
  st->print_raw(", ROR ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src3
}
#endif
#ifndef PRODUCT
void OrI_reg_URShift_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src3
  st->print_raw("orrw  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", LSR ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src3
}
#endif
#ifndef PRODUCT
void OrI_reg_URShift_reg_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src2
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src3
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src1
  st->print_raw("orrw  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src1
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src2
  st->print_raw(", LSR ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src3
}
#endif
#ifndef PRODUCT
void OrL_reg_URShift_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src3
  st->print_raw("orr  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", LSR ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src3
}
#endif
#ifndef PRODUCT
void OrL_reg_URShift_reg_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src2
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src3
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src1
  st->print_raw("orr  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src1
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src2
  st->print_raw(", LSR ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src3
}
#endif
#ifndef PRODUCT
void OrI_reg_RShift_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src3
  st->print_raw("orrw  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", ASR ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src3
}
#endif
#ifndef PRODUCT
void OrI_reg_RShift_reg_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src2
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src3
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src1
  st->print_raw("orrw  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src1
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src2
  st->print_raw(", ASR ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src3
}
#endif
#ifndef PRODUCT
void OrL_reg_RShift_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src3
  st->print_raw("orr  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", ASR ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src3
}
#endif
#ifndef PRODUCT
void OrL_reg_RShift_reg_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src2
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src3
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src1
  st->print_raw("orr  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src1
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src2
  st->print_raw(", ASR ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src3
}
#endif
#ifndef PRODUCT
void OrI_reg_LShift_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src3
  st->print_raw("orrw  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", LSL ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src3
}
#endif
#ifndef PRODUCT
void OrI_reg_LShift_reg_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src2
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src3
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src1
  st->print_raw("orrw  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src1
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src2
  st->print_raw(", LSL ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src3
}
#endif
#ifndef PRODUCT
void OrL_reg_LShift_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src3
  st->print_raw("orr  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", LSL ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src3
}
#endif
#ifndef PRODUCT
void OrL_reg_LShift_reg_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src2
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src3
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src1
  st->print_raw("orr  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src1
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src2
  st->print_raw(", LSL ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src3
}
#endif
#ifndef PRODUCT
void OrI_reg_RotateRight_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src3
  st->print_raw("orrw  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", ROR ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src3
}
#endif
#ifndef PRODUCT
void OrI_reg_RotateRight_reg_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src2
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src3
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src1
  st->print_raw("orrw  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src1
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src2
  st->print_raw(", ROR ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src3
}
#endif
#ifndef PRODUCT
void OrL_reg_RotateRight_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src3
  st->print_raw("orr  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", ROR ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src3
}
#endif
#ifndef PRODUCT
void OrL_reg_RotateRight_reg_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src2
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src3
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src1
  st->print_raw("orr  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src1
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src2
  st->print_raw(", ROR ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src3
}
#endif
#ifndef PRODUCT
void AddI_reg_URShift_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src3
  st->print_raw("addw  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", LSR ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src3
}
#endif
#ifndef PRODUCT
void AddI_reg_URShift_reg_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src2
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src3
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src1
  st->print_raw("addw  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src1
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src2
  st->print_raw(", LSR ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src3
}
#endif
#ifndef PRODUCT
void AddL_reg_URShift_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src3
  st->print_raw("add  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", LSR ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src3
}
#endif
#ifndef PRODUCT
void AddL_reg_URShift_reg_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src2
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src3
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src1
  st->print_raw("add  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src1
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src2
  st->print_raw(", LSR ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src3
}
#endif
#ifndef PRODUCT
void AddI_reg_RShift_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src3
  st->print_raw("addw  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", ASR ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src3
}
#endif
#ifndef PRODUCT
void AddI_reg_RShift_reg_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src2
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src3
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src1
  st->print_raw("addw  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src1
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src2
  st->print_raw(", ASR ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src3
}
#endif
#ifndef PRODUCT
void AddL_reg_RShift_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src3
  st->print_raw("add  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", ASR ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src3
}
#endif
#ifndef PRODUCT
void AddL_reg_RShift_reg_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src2
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src3
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src1
  st->print_raw("add  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src1
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src2
  st->print_raw(", ASR ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src3
}
#endif
#ifndef PRODUCT
void AddI_reg_LShift_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src3
  st->print_raw("addw  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", LSL ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src3
}
#endif
#ifndef PRODUCT
void AddI_reg_LShift_reg_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src2
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src3
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src1
  st->print_raw("addw  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src1
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src2
  st->print_raw(", LSL ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src3
}
#endif
#ifndef PRODUCT
void AddL_reg_LShift_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src3
  st->print_raw("add  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", LSL ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src3
}
#endif
#ifndef PRODUCT
void AddL_reg_LShift_reg_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src2
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src3
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src1
  st->print_raw("add  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src1
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src2
  st->print_raw(", LSL ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src3
}
#endif
#ifndef PRODUCT
void SubI_reg_URShift_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src3
  st->print_raw("subw  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", LSR ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src3
}
#endif
#ifndef PRODUCT
void SubL_reg_URShift_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src3
  st->print_raw("sub  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", LSR ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src3
}
#endif
#ifndef PRODUCT
void SubI_reg_RShift_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src3
  st->print_raw("subw  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", ASR ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src3
}
#endif
#ifndef PRODUCT
void SubL_reg_RShift_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src3
  st->print_raw("sub  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", ASR ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src3
}
#endif
#ifndef PRODUCT
void SubI_reg_LShift_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src3
  st->print_raw("subw  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", LSL ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src3
}
#endif
#ifndef PRODUCT
void SubL_reg_LShift_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src3
  st->print_raw("sub  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", LSL ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src3
}
#endif
#ifndef PRODUCT
void sbfmLNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// lshift_count
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// rshift_count
  st->print_raw("sbfm  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // rshift_count
  st->print_raw(" - ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // lshift_count
  st->print_raw(", #63 - ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // lshift_count
}
#endif
#ifndef PRODUCT
void sbfmwINode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// lshift_count
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// rshift_count
  st->print_raw("sbfmw  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // rshift_count
  st->print_raw(" - ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // lshift_count
  st->print_raw(", #31 - ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // lshift_count
}
#endif
#ifndef PRODUCT
void ubfmLNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// lshift_count
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// rshift_count
  st->print_raw("ubfm  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // rshift_count
  st->print_raw(" - ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // lshift_count
  st->print_raw(", #63 - ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // lshift_count
}
#endif
#ifndef PRODUCT
void ubfmwINode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// lshift_count
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// rshift_count
  st->print_raw("ubfmw  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // rshift_count
  st->print_raw(" - ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // lshift_count
  st->print_raw(", #31 - ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // lshift_count
}
#endif
#ifndef PRODUCT
void ubfxwINode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// rshift
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// mask
  st->print_raw("ubfxw ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // rshift
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // mask
}
#endif
#ifndef PRODUCT
void ubfxLNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// rshift
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// mask
  st->print_raw("ubfx ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // rshift
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // mask
}
#endif
#ifndef PRODUCT
void ubfxIConvI2LNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// rshift
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// mask
  st->print_raw("ubfx ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // rshift
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // mask
}
#endif
#ifndef PRODUCT
void ubfizwINode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// mask
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// lshift
  st->print_raw("ubfizw ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // lshift
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // mask
}
#endif
#ifndef PRODUCT
void ubfizLNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// mask
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// lshift
  st->print_raw("ubfiz ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // lshift
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // mask
}
#endif
#ifndef PRODUCT
void ubfizwIConvI2LNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// mask
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// lshift
  st->print_raw("ubfizw ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // lshift
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // mask
}
#endif
#ifndef PRODUCT
void ubfizLConvL2INode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// mask
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// lshift
  st->print_raw("ubfiz ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // lshift
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // mask
}
#endif
#ifndef PRODUCT
void ubfizIConvI2LNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// mask
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// lshift
  st->print_raw("ubfiz ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // lshift
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // mask
}
#endif
#ifndef PRODUCT
void ubfizLConvL2IxNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// mask
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// lshift
  st->print_raw("ubfiz ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // lshift
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // mask
}
#endif
#ifndef PRODUCT
void ubfizIConvI2LAndINode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// msk
  st->print_raw("ubfiz ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(", 0, exact_log2(");
  opnd_array(2)->ext_format(ra, this,idx2, st); // msk
  st->print_raw(" + 1) ");
}
#endif
#ifndef PRODUCT
void extrOrLNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// lshift
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// rshift
  st->print_raw("extr ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src2
  st->print_raw(", #");
  opnd_array(4)->ext_format(ra, this,idx4, st); // rshift
}
#endif
#ifndef PRODUCT
void extrOrL_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src2
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// rshift
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src1
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// lshift
  st->print_raw("extr ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src1
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src2
  st->print_raw(", #");
  opnd_array(2)->ext_format(ra, this,idx2, st); // rshift
}
#endif
#ifndef PRODUCT
void extrOrINode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// lshift
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// rshift
  st->print_raw("extr ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src2
  st->print_raw(", #");
  opnd_array(4)->ext_format(ra, this,idx4, st); // rshift
}
#endif
#ifndef PRODUCT
void extrOrI_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src2
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// rshift
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src1
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// lshift
  st->print_raw("extr ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src1
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src2
  st->print_raw(", #");
  opnd_array(2)->ext_format(ra, this,idx2, st); // rshift
}
#endif
#ifndef PRODUCT
void extrAddLNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// lshift
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// rshift
  st->print_raw("extr ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src2
  st->print_raw(", #");
  opnd_array(4)->ext_format(ra, this,idx4, st); // rshift
}
#endif
#ifndef PRODUCT
void extrAddL_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src2
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// rshift
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src1
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// lshift
  st->print_raw("extr ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src1
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src2
  st->print_raw(", #");
  opnd_array(2)->ext_format(ra, this,idx2, st); // rshift
}
#endif
#ifndef PRODUCT
void extrAddINode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// lshift
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// rshift
  st->print_raw("extr ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src2
  st->print_raw(", #");
  opnd_array(4)->ext_format(ra, this,idx4, st); // rshift
}
#endif
#ifndef PRODUCT
void extrAddI_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src2
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// rshift
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src1
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// lshift
  st->print_raw("extr ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src1
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src2
  st->print_raw(", #");
  opnd_array(2)->ext_format(ra, this,idx2, st); // rshift
}
#endif
#ifndef PRODUCT
void rorI_immNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// shift
  st->print_raw("ror    ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // shift
}
#endif
#ifndef PRODUCT
void rorL_immNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// shift
  st->print_raw("ror    ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // shift
}
#endif
#ifndef PRODUCT
void rorI_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// shift
  st->print_raw("ror    ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // shift
}
#endif
#ifndef PRODUCT
void rorL_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// shift
  st->print_raw("ror    ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // shift
}
#endif
#ifndef PRODUCT
void rolI_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// shift
  st->print_raw("rol    ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // shift
}
#endif
#ifndef PRODUCT
void rolL_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// shift
  st->print_raw("rol    ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // shift
}
#endif
#ifndef PRODUCT
void AddExtINode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("add  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", sxtw");
}
#endif
#ifndef PRODUCT
void AddExtI_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src2
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  st->print_raw("add  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src1
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src2
  st->print_raw(", sxtw");
}
#endif
#ifndef PRODUCT
void SubExtINode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("sub  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", sxtw");
}
#endif
#ifndef PRODUCT
void AddExtI_sxthNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// lshift
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// rshift
  st->print_raw("add  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", sxth");
}
#endif
#ifndef PRODUCT
void AddExtI_sxth_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src2
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// lshift
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// rshift
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src1
  st->print_raw("add  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // src1
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src2
  st->print_raw(", sxth");
}
#endif
#ifndef PRODUCT
void AddExtI_sxtbNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// lshift
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// rshift
  st->print_raw("add  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", sxtb");
}
#endif
#ifndef PRODUCT
void AddExtI_sxtb_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src2
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// lshift
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// rshift
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src1
  st->print_raw("add  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // src1
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src2
  st->print_raw(", sxtb");
}
#endif
#ifndef PRODUCT
void AddExtI_uxtbNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// lshift
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// rshift
  st->print_raw("add  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", uxtb");
}
#endif
#ifndef PRODUCT
void AddExtI_uxtb_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src2
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// lshift
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// rshift
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src1
  st->print_raw("add  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // src1
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src2
  st->print_raw(", uxtb");
}
#endif
#ifndef PRODUCT
void AddExtL_sxthNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// lshift
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// rshift
  st->print_raw("add  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", sxth");
}
#endif
#ifndef PRODUCT
void AddExtL_sxth_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src2
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// lshift
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// rshift
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src1
  st->print_raw("add  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // src1
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src2
  st->print_raw(", sxth");
}
#endif
#ifndef PRODUCT
void AddExtL_sxtwNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// lshift
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// rshift
  st->print_raw("add  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", sxtw");
}
#endif
#ifndef PRODUCT
void AddExtL_sxtw_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src2
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// lshift
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// rshift
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src1
  st->print_raw("add  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // src1
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src2
  st->print_raw(", sxtw");
}
#endif
#ifndef PRODUCT
void AddExtL_sxtbNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// lshift
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// rshift
  st->print_raw("add  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", sxtb");
}
#endif
#ifndef PRODUCT
void AddExtL_sxtb_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src2
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// lshift
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// rshift
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src1
  st->print_raw("add  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // src1
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src2
  st->print_raw(", sxtb");
}
#endif
#ifndef PRODUCT
void AddExtL_uxtbNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// lshift
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// rshift
  st->print_raw("add  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", uxtb");
}
#endif
#ifndef PRODUCT
void AddExtL_uxtb_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src2
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// lshift
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// rshift
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src1
  st->print_raw("add  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // src1
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src2
  st->print_raw(", uxtb");
}
#endif
#ifndef PRODUCT
void AddExtI_uxtb_andNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// mask
  st->print_raw("addw  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", uxtb");
}
#endif
#ifndef PRODUCT
void AddExtI_uxtb_and_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src2
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// mask
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src1
  st->print_raw("addw  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src1
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src2
  st->print_raw(", uxtb");
}
#endif
#ifndef PRODUCT
void AddExtI_uxth_andNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// mask
  st->print_raw("addw  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", uxth");
}
#endif
#ifndef PRODUCT
void AddExtI_uxth_and_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src2
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// mask
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src1
  st->print_raw("addw  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src1
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src2
  st->print_raw(", uxth");
}
#endif
#ifndef PRODUCT
void AddExtL_uxtb_andNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// mask
  st->print_raw("add  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", uxtb");
}
#endif
#ifndef PRODUCT
void AddExtL_uxtb_and_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src2
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// mask
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src1
  st->print_raw("add  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src1
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src2
  st->print_raw(", uxtb");
}
#endif
#ifndef PRODUCT
void AddExtL_uxth_andNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// mask
  st->print_raw("add  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", uxth");
}
#endif
#ifndef PRODUCT
void AddExtL_uxth_and_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src2
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// mask
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src1
  st->print_raw("add  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src1
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src2
  st->print_raw(", uxth");
}
#endif
#ifndef PRODUCT
void AddExtL_uxtw_andNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// mask
  st->print_raw("add  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", uxtw");
}
#endif
#ifndef PRODUCT
void AddExtL_uxtw_and_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src2
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// mask
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src1
  st->print_raw("add  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src1
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src2
  st->print_raw(", uxtw");
}
#endif
#ifndef PRODUCT
void SubExtI_uxtb_andNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// mask
  st->print_raw("subw  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", uxtb");
}
#endif
#ifndef PRODUCT
void SubExtI_uxth_andNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// mask
  st->print_raw("subw  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", uxth");
}
#endif
#ifndef PRODUCT
void SubExtL_uxtb_andNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// mask
  st->print_raw("sub  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", uxtb");
}
#endif
#ifndef PRODUCT
void SubExtL_uxth_andNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// mask
  st->print_raw("sub  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", uxth");
}
#endif
#ifndef PRODUCT
void SubExtL_uxtw_andNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// mask
  st->print_raw("sub  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", uxtw");
}
#endif
#ifndef PRODUCT
void AddExtL_sxtb_shiftNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// lshift1
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// rshift1
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// lshift2
  st->print_raw("add  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", sxtb #lshift2");
}
#endif
#ifndef PRODUCT
void AddExtL_sxtb_shift_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src2
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// lshift1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// rshift1
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// lshift2
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// src1
  st->print_raw("add  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(5)->ext_format(ra, this,idx5, st); // src1
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src2
  st->print_raw(", sxtb #lshift2");
}
#endif
#ifndef PRODUCT
void AddExtL_sxth_shiftNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// lshift1
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// rshift1
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// lshift2
  st->print_raw("add  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", sxth #lshift2");
}
#endif
#ifndef PRODUCT
void AddExtL_sxth_shift_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src2
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// lshift1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// rshift1
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// lshift2
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// src1
  st->print_raw("add  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(5)->ext_format(ra, this,idx5, st); // src1
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src2
  st->print_raw(", sxth #lshift2");
}
#endif
#ifndef PRODUCT
void AddExtL_sxtw_shiftNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// lshift1
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// rshift1
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// lshift2
  st->print_raw("add  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", sxtw #lshift2");
}
#endif
#ifndef PRODUCT
void AddExtL_sxtw_shift_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src2
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// lshift1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// rshift1
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// lshift2
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// src1
  st->print_raw("add  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(5)->ext_format(ra, this,idx5, st); // src1
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src2
  st->print_raw(", sxtw #lshift2");
}
#endif
#ifndef PRODUCT
void SubExtL_sxtb_shiftNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// lshift1
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// rshift1
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// lshift2
  st->print_raw("sub  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", sxtb #lshift2");
}
#endif
#ifndef PRODUCT
void SubExtL_sxth_shiftNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// lshift1
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// rshift1
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// lshift2
  st->print_raw("sub  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", sxth #lshift2");
}
#endif
#ifndef PRODUCT
void SubExtL_sxtw_shiftNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// lshift1
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// rshift1
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// lshift2
  st->print_raw("sub  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", sxtw #lshift2");
}
#endif
#ifndef PRODUCT
void AddExtI_sxtb_shiftNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// lshift1
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// rshift1
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// lshift2
  st->print_raw("addw  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", sxtb #lshift2");
}
#endif
#ifndef PRODUCT
void AddExtI_sxtb_shift_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src2
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// lshift1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// rshift1
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// lshift2
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// src1
  st->print_raw("addw  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(5)->ext_format(ra, this,idx5, st); // src1
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src2
  st->print_raw(", sxtb #lshift2");
}
#endif
#ifndef PRODUCT
void AddExtI_sxth_shiftNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// lshift1
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// rshift1
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// lshift2
  st->print_raw("addw  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", sxth #lshift2");
}
#endif
#ifndef PRODUCT
void AddExtI_sxth_shift_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src2
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// lshift1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// rshift1
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// lshift2
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// src1
  st->print_raw("addw  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(5)->ext_format(ra, this,idx5, st); // src1
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src2
  st->print_raw(", sxth #lshift2");
}
#endif
#ifndef PRODUCT
void SubExtI_sxtb_shiftNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// lshift1
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// rshift1
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// lshift2
  st->print_raw("subw  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", sxtb #lshift2");
}
#endif
#ifndef PRODUCT
void SubExtI_sxth_shiftNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// lshift1
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// rshift1
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// lshift2
  st->print_raw("subw  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", sxth #lshift2");
}
#endif
#ifndef PRODUCT
void AddExtI_shiftNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// lshift
  st->print_raw("add  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", sxtw #lshift");
}
#endif
#ifndef PRODUCT
void AddExtI_shift_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src2
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// lshift
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src1
  st->print_raw("add  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src1
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src2
  st->print_raw(", sxtw #lshift");
}
#endif
#ifndef PRODUCT
void SubExtI_shiftNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// lshift
  st->print_raw("sub  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", sxtw #lshift");
}
#endif
#ifndef PRODUCT
void AddExtL_uxtb_and_shiftNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// mask
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// lshift
  st->print_raw("add  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", uxtb #lshift");
}
#endif
#ifndef PRODUCT
void AddExtL_uxtb_and_shift_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src2
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// mask
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// lshift
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src1
  st->print_raw("add  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // src1
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src2
  st->print_raw(", uxtb #lshift");
}
#endif
#ifndef PRODUCT
void AddExtL_uxth_and_shiftNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// mask
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// lshift
  st->print_raw("add  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", uxth #lshift");
}
#endif
#ifndef PRODUCT
void AddExtL_uxth_and_shift_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src2
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// mask
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// lshift
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src1
  st->print_raw("add  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // src1
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src2
  st->print_raw(", uxth #lshift");
}
#endif
#ifndef PRODUCT
void AddExtL_uxtw_and_shiftNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// mask
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// lshift
  st->print_raw("add  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", uxtw #lshift");
}
#endif
#ifndef PRODUCT
void AddExtL_uxtw_and_shift_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src2
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// mask
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// lshift
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src1
  st->print_raw("add  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // src1
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src2
  st->print_raw(", uxtw #lshift");
}
#endif
#ifndef PRODUCT
void SubExtL_uxtb_and_shiftNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// mask
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// lshift
  st->print_raw("sub  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", uxtb #lshift");
}
#endif
#ifndef PRODUCT
void SubExtL_uxth_and_shiftNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// mask
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// lshift
  st->print_raw("sub  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", uxth #lshift");
}
#endif
#ifndef PRODUCT
void SubExtL_uxtw_and_shiftNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// mask
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// lshift
  st->print_raw("sub  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", uxtw #lshift");
}
#endif
#ifndef PRODUCT
void AddExtI_uxtb_and_shiftNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// mask
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// lshift
  st->print_raw("addw  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", uxtb #lshift");
}
#endif
#ifndef PRODUCT
void AddExtI_uxtb_and_shift_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src2
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// mask
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// lshift
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src1
  st->print_raw("addw  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // src1
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src2
  st->print_raw(", uxtb #lshift");
}
#endif
#ifndef PRODUCT
void AddExtI_uxth_and_shiftNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// mask
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// lshift
  st->print_raw("addw  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", uxth #lshift");
}
#endif
#ifndef PRODUCT
void AddExtI_uxth_and_shift_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src2
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// mask
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// lshift
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src1
  st->print_raw("addw  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // src1
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src2
  st->print_raw(", uxth #lshift");
}
#endif
#ifndef PRODUCT
void SubExtI_uxtb_and_shiftNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// mask
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// lshift
  st->print_raw("subw  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", uxtb #lshift");
}
#endif
#ifndef PRODUCT
void SubExtI_uxth_and_shiftNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// mask
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// lshift
  st->print_raw("subw  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", uxth #lshift");
}
#endif
#ifndef PRODUCT
void cmovI_reg_reg_ltNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// cr
  st->print_raw("cselw ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(" lt\t");
}
#endif
#ifndef PRODUCT
void cmovI_reg_reg_gtNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// cr
  st->print_raw("cselw ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(" gt\t");
}
#endif
#ifndef PRODUCT
void cmovI_reg_imm0_ltNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// cr
  st->print_raw("cselw ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", zr lt\t");
}
#endif
#ifndef PRODUCT
void cmovI_reg_imm0_gtNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// cr
  st->print_raw("cselw ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", zr gt\t");
}
#endif
#ifndef PRODUCT
void cmovI_reg_imm1_leNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// cr
  st->print_raw("csincw ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", zr le\t");
}
#endif
#ifndef PRODUCT
void cmovI_reg_imm1_gtNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// cr
  st->print_raw("csincw ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", zr gt\t");
}
#endif
#ifndef PRODUCT
void cmovI_reg_immM1_ltNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// cr
  st->print_raw("csinvw ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", zr lt\t");
}
#endif
#ifndef PRODUCT
void cmovI_reg_immM1_geNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// cr
  st->print_raw("csinvw ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", zr ge\t");
}
#endif
#ifndef PRODUCT
void minI_reg_imm0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
}
#endif
#ifndef PRODUCT
void minI_imm0_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
}
#endif
#ifndef PRODUCT
void minI_reg_imm1Node::format(PhaseRegAlloc *ra, outputStream *st) const {
}
#endif
#ifndef PRODUCT
void minI_imm1_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
}
#endif
#ifndef PRODUCT
void minI_reg_immM1Node::format(PhaseRegAlloc *ra, outputStream *st) const {
}
#endif
#ifndef PRODUCT
void minI_immM1_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
}
#endif
#ifndef PRODUCT
void maxI_reg_imm0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
}
#endif
#ifndef PRODUCT
void maxI_imm0_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
}
#endif
#ifndef PRODUCT
void maxI_reg_imm1Node::format(PhaseRegAlloc *ra, outputStream *st) const {
}
#endif
#ifndef PRODUCT
void maxI_imm1_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
}
#endif
#ifndef PRODUCT
void maxI_reg_immM1Node::format(PhaseRegAlloc *ra, outputStream *st) const {
}
#endif
#ifndef PRODUCT
void maxI_immM1_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
}
#endif
#ifndef PRODUCT
void bits_reverse_INode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("rbitw  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
}
#endif
#ifndef PRODUCT
void bits_reverse_LNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("rbit  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
}
#endif
#ifndef PRODUCT
void addF_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("fadds   ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void addD_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("faddd   ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void subF_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("fsubs   ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void subD_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("fsubd   ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void mulF_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("fmuls   ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void mulD_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("fmuld   ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void maddF_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src3
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  st->print_raw("fmadds   ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src1
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src2
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src3
}
#endif
#ifndef PRODUCT
void maddD_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src3
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  st->print_raw("fmaddd   ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src1
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src2
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src3
}
#endif
#ifndef PRODUCT
void msubF_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src3
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  st->print_raw("fmsubs   ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src1
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src2
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src3
}
#endif
#ifndef PRODUCT
void msubD_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src3
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  st->print_raw("fmsubd   ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src1
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src2
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src3
}
#endif
#ifndef PRODUCT
void mnaddF_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src3
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  st->print_raw("fnmadds  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src1
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src2
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src3
}
#endif
#ifndef PRODUCT
void mnaddD_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src3
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  st->print_raw("fnmaddd   ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src1
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src2
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src3
}
#endif
#ifndef PRODUCT
void mnsubF_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src3
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  st->print_raw("fnmsubs  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src1
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src2
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src3
}
#endif
#ifndef PRODUCT
void mnsubD_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src3
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  st->print_raw("fnmsubd   ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src1
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src2
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src3
}
#endif
#ifndef PRODUCT
void maxF_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("fmaxs   ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void minF_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("fmins   ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void maxD_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("fmaxd   ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void minD_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("fmind   ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void divF_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("fdivs   ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void divD_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("fdivd   ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void negF_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("fneg   ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
}
#endif
#ifndef PRODUCT
void negD_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("fnegd   ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
}
#endif
#ifndef PRODUCT
void absI_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("cmpw  ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(", zr\n\t");
  st->print_raw("cnegw ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(", Assembler::LT\t# int abs");
}
#endif
#ifndef PRODUCT
void absL_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("cmp  ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(", zr\n\t");
  st->print_raw("cneg ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(", Assembler::LT\t# long abs");
}
#endif
#ifndef PRODUCT
void absF_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("fabss   ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
}
#endif
#ifndef PRODUCT
void absD_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("fabsd   ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
}
#endif
#ifndef PRODUCT
void absdF_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("fabds   ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void absdD_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("fabdd   ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void sqrtD_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("fsqrtd  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
}
#endif
#ifndef PRODUCT
void sqrtF_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("fsqrts  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
}
#endif
#ifndef PRODUCT
void roundD_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// rmode
  st->print_raw("frint  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // rmode
}
#endif
#ifndef PRODUCT
void copySignD_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// zero
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// dst
  st->print_raw("CopySignD  ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // dst
  st->print_raw(" ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(" ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void copySignF_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// dst
  st->print_raw("CopySignF  ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // dst
  st->print_raw(" ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(" ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void signumD_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// zero
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// one
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// dst
  st->print_raw("signumD  ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
}
#endif
#ifndef PRODUCT
void signumF_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// zero
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// one
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// dst
  st->print_raw("signumF  ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
}
#endif
#ifndef PRODUCT
void onspinwaitNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  st->print_raw("onspinwait");
}
#endif
#ifndef PRODUCT
void andI_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("andw  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw("\t# int");
}
#endif
#ifndef PRODUCT
void andI_reg_immNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("andsw  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw("\t# int");
}
#endif
#ifndef PRODUCT
void orI_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("orrw  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw("\t# int");
}
#endif
#ifndef PRODUCT
void orI_reg_immNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("orrw  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw("\t# int");
}
#endif
#ifndef PRODUCT
void xorI_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("eorw  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw("\t# int");
}
#endif
#ifndef PRODUCT
void xorI_reg_immNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("eorw  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw("\t# int");
}
#endif
#ifndef PRODUCT
void andL_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("and  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw("\t# int");
}
#endif
#ifndef PRODUCT
void andL_reg_immNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("and  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw("\t# int");
}
#endif
#ifndef PRODUCT
void orL_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("orr  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw("\t# int");
}
#endif
#ifndef PRODUCT
void orL_reg_immNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("orr  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw("\t# int");
}
#endif
#ifndef PRODUCT
void xorL_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("eor  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw("\t# int");
}
#endif
#ifndef PRODUCT
void xorL_reg_immNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("eor  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw("\t# int");
}
#endif
#ifndef PRODUCT
void convI2L_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("sxtw  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\t# i2l");
}
#endif
#ifndef PRODUCT
void convUI2L_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// mask
  st->print_raw("ubfm  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(", 0, 31\t# ui2l");
}
#endif
#ifndef PRODUCT
void convL2I_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("movw  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(" \t// l2i");
}
#endif
#ifndef PRODUCT
void convD2F_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("fcvtd  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(" \t// d2f");
}
#endif
#ifndef PRODUCT
void convF2D_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("fcvts  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(" \t// f2d");
}
#endif
#ifndef PRODUCT
void convF2I_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("fcvtzsw  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(" \t// f2i");
}
#endif
#ifndef PRODUCT
void convF2L_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("fcvtzs  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(" \t// f2l");
}
#endif
#ifndef PRODUCT
void convF2HF_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// tmp
  st->print_raw("fcvt ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // tmp
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\t# convert single to half precision\n\t");
  st->print_raw("smov ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // tmp
  st->print_raw("\t# move result from ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // tmp
  st->print_raw(" to ");
  opnd_array(0)->int_format(ra, this, st); // dst
}
#endif
#ifndef PRODUCT
void convHF2F_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// tmp
  st->print_raw("mov ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // tmp
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\t# move source from ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(" to ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // tmp
  st->print_raw("\n\t");
  st->print_raw("fcvt ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // tmp
  st->print_raw("\t# convert half to single precision");
}
#endif
#ifndef PRODUCT
void convI2F_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("scvtfws  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(" \t// i2f");
}
#endif
#ifndef PRODUCT
void convL2F_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("scvtfs  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(" \t// l2f");
}
#endif
#ifndef PRODUCT
void convD2I_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("fcvtzdw  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(" \t// d2i");
}
#endif
#ifndef PRODUCT
void convD2L_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("fcvtzd  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(" \t// d2l");
}
#endif
#ifndef PRODUCT
void convI2D_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("scvtfwd  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(" \t// i2d");
}
#endif
#ifndef PRODUCT
void convL2D_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("scvtfd  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(" \t// l2d");
}
#endif
#ifndef PRODUCT
void round_double_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// ftmp
  st->print_raw("java_round_double ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // dst
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
}
#endif
#ifndef PRODUCT
void round_float_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// ftmp
  st->print_raw("java_round_float ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // dst
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
}
#endif
#ifndef PRODUCT
void MoveF2I_stack_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("ldrw ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\t# MoveF2I_stack_reg");
}
#endif
#ifndef PRODUCT
void MoveI2F_stack_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("ldrs ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\t# MoveI2F_stack_reg");
}
#endif
#ifndef PRODUCT
void MoveD2L_stack_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("ldr ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\t# MoveD2L_stack_reg");
}
#endif
#ifndef PRODUCT
void MoveL2D_stack_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("ldrd ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\t# MoveL2D_stack_reg");
}
#endif
#ifndef PRODUCT
void MoveF2I_reg_stackNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("strs ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(", ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw("\t# MoveF2I_reg_stack");
}
#endif
#ifndef PRODUCT
void MoveI2F_reg_stackNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("strw ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(", ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw("\t# MoveI2F_reg_stack");
}
#endif
#ifndef PRODUCT
void MoveD2L_reg_stackNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("strd ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\t# MoveD2L_reg_stack");
}
#endif
#ifndef PRODUCT
void MoveL2D_reg_stackNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("str ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(", ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw("\t# MoveL2D_reg_stack");
}
#endif
#ifndef PRODUCT
void MoveF2I_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("fmovs ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\t# MoveF2I_reg_reg");
}
#endif
#ifndef PRODUCT
void MoveI2F_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("fmovs ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\t# MoveI2F_reg_reg");
}
#endif
#ifndef PRODUCT
void MoveD2L_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("fmovd ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\t# MoveD2L_reg_reg");
}
#endif
#ifndef PRODUCT
void MoveL2D_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("fmovd ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\t# MoveL2D_reg_reg");
}
#endif
#ifndef PRODUCT
void clearArray_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// cnt
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// base
  st->print_raw("ClearArray ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // cnt
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // base
}
#endif
#ifndef PRODUCT
void clearArray_imm_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// cnt
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// base
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// temp
  st->print_raw("ClearArray ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // cnt
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // base
}
#endif
#ifndef PRODUCT
void overflowAddI_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// op1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// op2
  st->print_raw("cmnw  ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // op1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // op2
  st->print_raw("\t# overflow check int");
}
#endif
#ifndef PRODUCT
void overflowAddI_reg_immNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// op1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// op2
  st->print_raw("cmnw  ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // op1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // op2
  st->print_raw("\t# overflow check int");
}
#endif
#ifndef PRODUCT
void overflowAddL_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// op1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// op2
  st->print_raw("cmn   ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // op1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // op2
  st->print_raw("\t# overflow check long");
}
#endif
#ifndef PRODUCT
void overflowAddL_reg_immNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// op1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// op2
  st->print_raw("adds  zr, ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // op1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // op2
  st->print_raw("\t# overflow check long");
}
#endif
#ifndef PRODUCT
void overflowSubI_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// op1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// op2
  st->print_raw("cmpw  ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // op1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // op2
  st->print_raw("\t# overflow check int");
}
#endif
#ifndef PRODUCT
void overflowSubI_reg_immNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// op1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// op2
  st->print_raw("cmpw  ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // op1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // op2
  st->print_raw("\t# overflow check int");
}
#endif
#ifndef PRODUCT
void overflowSubL_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// op1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// op2
  st->print_raw("cmp   ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // op1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // op2
  st->print_raw("\t# overflow check long");
}
#endif
#ifndef PRODUCT
void overflowSubL_reg_immNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// op1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// op2
  st->print_raw("cmp   ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // op1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // op2
  st->print_raw("\t# overflow check long");
}
#endif
#ifndef PRODUCT
void overflowNegI_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// zero
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// op1
  st->print_raw("cmpw  zr, ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // op1
  st->print_raw("\t# overflow check int");
}
#endif
#ifndef PRODUCT
void overflowNegL_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// zero
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// op1
  st->print_raw("cmp   zr, ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // op1
  st->print_raw("\t# overflow check long");
}
#endif
#ifndef PRODUCT
void overflowMulI_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// op1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// op2
  st->print_raw("smull rscratch1, ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // op1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // op2
  st->print_raw("\t# overflow check int\n\t");
  st->print_raw("cmp   rscratch1, rscratch1, sxtw\n\t");
  st->print_raw("movw  rscratch1, #0x80000000\n\t");
  st->print_raw("cselw rscratch1, rscratch1, zr, NE\n\t");
  st->print_raw("cmpw  rscratch1, #1");
}
#endif
#ifndef PRODUCT
void overflowMulI_reg_branchNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// op1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// op2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// labl
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// cr
  st->print_raw("smull rscratch1, ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // op1
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // op2
  st->print_raw("\t# overflow check int\n\t");
  st->print_raw("cmp   rscratch1, rscratch1, sxtw\n\t");
  st->print_raw("b");
  opnd_array(1)->ext_format(ra, this,idx1, st); // cmp
  st->print_raw("   ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // labl
  st->print("  P=%f C=%f",_prob,_fcnt);
}
#endif
#ifndef PRODUCT
void overflowMulL_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// op1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// op2
  st->print_raw("mul   rscratch1, ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // op1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // op2
  st->print_raw("\t#overflow check long\n\t");
  st->print_raw("smulh rscratch2, ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // op1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // op2
  st->print_raw("\n\t");
  st->print_raw("cmp   rscratch2, rscratch1, ASR #63\n\t");
  st->print_raw("movw  rscratch1, #0x80000000\n\t");
  st->print_raw("cselw rscratch1, rscratch1, zr, NE\n\t");
  st->print_raw("cmpw  rscratch1, #1");
}
#endif
#ifndef PRODUCT
void overflowMulL_reg_branchNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// op1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// op2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// labl
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// cr
  st->print_raw("mul   rscratch1, ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // op1
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // op2
  st->print_raw("\t#overflow check long\n\t");
  st->print_raw("smulh rscratch2, ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // op1
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // op2
  st->print_raw("\n\t");
  st->print_raw("cmp   rscratch2, rscratch1, ASR #63\n\t");
  st->print_raw("b");
  opnd_array(1)->ext_format(ra, this,idx1, st); // cmp
  st->print_raw(" ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // labl
  st->print("  P=%f C=%f",_prob,_fcnt);
}
#endif
#ifndef PRODUCT
void compI_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// op1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// op2
  st->print_raw("cmpw  ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // op1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // op2
}
#endif
#ifndef PRODUCT
void compI_reg_immI0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// op1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// zero
  st->print_raw("cmpw ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // op1
  st->print_raw(", 0");
}
#endif
#ifndef PRODUCT
void compI_reg_immIAddSubNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// op1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// op2
  st->print_raw("cmpw  ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // op1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // op2
}
#endif
#ifndef PRODUCT
void compI_reg_immINode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// op1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// op2
  st->print_raw("cmpw  ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // op1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // op2
}
#endif
#ifndef PRODUCT
void compU_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// op1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// op2
  st->print_raw("cmpw  ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // op1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // op2
  st->print_raw("\t# unsigned");
}
#endif
#ifndef PRODUCT
void compU_reg_immI0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// op1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// zero
  st->print_raw("cmpw ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // op1
  st->print_raw(", #0\t# unsigned");
}
#endif
#ifndef PRODUCT
void compU_reg_immIAddSubNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// op1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// op2
  st->print_raw("cmpw  ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // op1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // op2
  st->print_raw("\t# unsigned");
}
#endif
#ifndef PRODUCT
void compU_reg_immINode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// op1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// op2
  st->print_raw("cmpw  ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // op1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // op2
  st->print_raw("\t# unsigned");
}
#endif
#ifndef PRODUCT
void compL_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// op1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// op2
  st->print_raw("cmp  ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // op1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // op2
}
#endif
#ifndef PRODUCT
void compL_reg_immL0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// op1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// zero
  st->print_raw("tst  ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // op1
}
#endif
#ifndef PRODUCT
void compL_reg_immLAddSubNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// op1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// op2
  st->print_raw("cmp  ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // op1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // op2
}
#endif
#ifndef PRODUCT
void compL_reg_immLNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// op1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// op2
  st->print_raw("cmp  ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // op1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // op2
}
#endif
#ifndef PRODUCT
void compUL_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// op1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// op2
  st->print_raw("cmp  ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // op1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // op2
}
#endif
#ifndef PRODUCT
void compUL_reg_immL0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// op1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// zero
  st->print_raw("tst  ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // op1
}
#endif
#ifndef PRODUCT
void compUL_reg_immLAddSubNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// op1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// op2
  st->print_raw("cmp  ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // op1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // op2
}
#endif
#ifndef PRODUCT
void compUL_reg_immLNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// op1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// op2
  st->print_raw("cmp  ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // op1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // op2
}
#endif
#ifndef PRODUCT
void compP_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// op1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// op2
  st->print_raw("cmp  ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // op1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // op2
  st->print_raw("\t // ptr");
}
#endif
#ifndef PRODUCT
void compN_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// op1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// op2
  st->print_raw("cmp  ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // op1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // op2
  st->print_raw("\t // compressed ptr");
}
#endif
#ifndef PRODUCT
void testP_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// op1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// zero
  st->print_raw("cmp  ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // op1
  st->print_raw(", 0\t // ptr");
}
#endif
#ifndef PRODUCT
void testN_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// op1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// zero
  st->print_raw("cmp  ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // op1
  st->print_raw(", 0\t // compressed ptr");
}
#endif
#ifndef PRODUCT
void compF_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("fcmps ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void compF_reg_zeroNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("fcmps ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", 0.0");
}
#endif
#ifndef PRODUCT
void compD_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("fcmpd ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void compD_reg_zeroNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("fcmpd ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", 0.0");
}
#endif
#ifndef PRODUCT
void compF3_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("fcmps ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw("\n\t");
  st->print_raw("csinvw(");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", zr, zr, eq\n\t");
  st->print_raw("csnegw(");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", lt)");
}
#endif
#ifndef PRODUCT
void compD3_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("fcmpd ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw("\n\t");
  st->print_raw("csinvw(");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", zr, zr, eq\n\t");
  st->print_raw("csnegw(");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", lt)");
}
#endif
#ifndef PRODUCT
void compF3_reg_immF0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// zero
  st->print_raw("fcmps ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", 0.0\n\t");
  st->print_raw("csinvw(");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", zr, zr, eq\n\t");
  st->print_raw("csnegw(");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", lt)");
}
#endif
#ifndef PRODUCT
void compD3_reg_immD0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// zero
  st->print_raw("fcmpd ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", 0.0\n\t");
  st->print_raw("csinvw(");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", zr, zr, eq\n\t");
  st->print_raw("csnegw(");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", lt)");
}
#endif
#ifndef PRODUCT
void cmpLTMask_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// p
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// q
  st->print_raw("cmpw ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // p
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // q
  st->print_raw("\t# cmpLTMask\n\t");
  st->print_raw("csetw ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", lt\n\t");
  st->print_raw("subw ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", zr, ");
  opnd_array(0)->int_format(ra, this, st); // dst
}
#endif
#ifndef PRODUCT
void cmpLTMask_reg_zeroNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// zero
  st->print_raw("asrw ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(", #31\t# cmpLTMask0");
}
#endif
#ifndef PRODUCT
void compI_reg_imm0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("cmpw ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(", 0");
}
#endif
#ifndef PRODUCT
void minI_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
}
#endif
#ifndef PRODUCT
void maxI_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
}
#endif
#ifndef PRODUCT
void branchNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// 
  st->print_raw("b  ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // lbl
}
#endif
#ifndef PRODUCT
void branchConNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// cr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// lbl
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// 
  st->print_raw("b");
  opnd_array(1)->ext_format(ra, this,idx1, st); // cmp
  st->print_raw("  ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // lbl
  st->print("  P=%f C=%f",_prob,_fcnt);
}
#endif
#ifndef PRODUCT
void branchConUNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// cr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// lbl
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// 
  st->print_raw("b");
  opnd_array(1)->ext_format(ra, this,idx1, st); // cmp
  st->print_raw("  ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // lbl
  st->print_raw("\t# unsigned");
  st->print("  P=%f C=%f",_prob,_fcnt);
}
#endif
#ifndef PRODUCT
void cmpI_imm0_branchNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// op1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// op2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// labl
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// cr
  st->print_raw("cbw");
  opnd_array(1)->ext_format(ra, this,idx1, st); // cmp
  st->print_raw("   ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // op1
  st->print_raw(", ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // labl
  st->print("  P=%f C=%f",_prob,_fcnt);
}
#endif
#ifndef PRODUCT
void cmpL_imm0_branchNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// op1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// op2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// labl
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// cr
  st->print_raw("cb");
  opnd_array(1)->ext_format(ra, this,idx1, st); // cmp
  st->print_raw("   ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // op1
  st->print_raw(", ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // labl
  st->print("  P=%f C=%f",_prob,_fcnt);
}
#endif
#ifndef PRODUCT
void cmpP_imm0_branchNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// op1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// op2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// labl
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// cr
  st->print_raw("cb");
  opnd_array(1)->ext_format(ra, this,idx1, st); // cmp
  st->print_raw("   ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // op1
  st->print_raw(", ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // labl
  st->print("  P=%f C=%f",_prob,_fcnt);
}
#endif
#ifndef PRODUCT
void cmpN_imm0_branchNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// op1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// op2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// labl
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// cr
  st->print_raw("cbw");
  opnd_array(1)->ext_format(ra, this,idx1, st); // cmp
  st->print_raw("   ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // op1
  st->print_raw(", ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // labl
  st->print("  P=%f C=%f",_prob,_fcnt);
}
#endif
#ifndef PRODUCT
void cmpP_narrowOop_imm0_branchNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// oop
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// zero
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// labl
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// cr
  st->print_raw("cb");
  opnd_array(1)->ext_format(ra, this,idx1, st); // cmp
  st->print_raw("   ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // oop
  st->print_raw(", ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // labl
  st->print("  P=%f C=%f",_prob,_fcnt);
}
#endif
#ifndef PRODUCT
void cmpUI_imm0_branchNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// op1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// op2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// labl
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// cr
  st->print_raw("cbw");
  opnd_array(1)->ext_format(ra, this,idx1, st); // cmp
  st->print_raw("   ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // op1
  st->print_raw(", ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // labl
  st->print("  P=%f C=%f",_prob,_fcnt);
}
#endif
#ifndef PRODUCT
void cmpUL_imm0_branchNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// op1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// op2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// labl
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// cr
  st->print_raw("cb");
  opnd_array(1)->ext_format(ra, this,idx1, st); // cmp
  st->print_raw("   ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // op1
  st->print_raw(", ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // labl
  st->print("  P=%f C=%f",_prob,_fcnt);
}
#endif
#ifndef PRODUCT
void cmpL_branch_signNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// op1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// op2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// labl
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// 
  st->print_raw("cb");
  opnd_array(1)->ext_format(ra, this,idx1, st); // cmp
  st->print_raw("   ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // op1
  st->print_raw(", ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // labl
  st->print_raw(" # long");
  st->print("  P=%f C=%f",_prob,_fcnt);
}
#endif
#ifndef PRODUCT
void cmpI_branch_signNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// op1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// op2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// labl
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// 
  st->print_raw("cb");
  opnd_array(1)->ext_format(ra, this,idx1, st); // cmp
  st->print_raw("   ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // op1
  st->print_raw(", ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // labl
  st->print_raw(" # int");
  st->print("  P=%f C=%f",_prob,_fcnt);
}
#endif
#ifndef PRODUCT
void cmpL_branch_bitNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// op1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// op2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// op3
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// labl
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// 
  st->print_raw("tb");
  opnd_array(1)->ext_format(ra, this,idx1, st); // cmp
  st->print_raw("   ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // op1
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // op2
  st->print_raw(", ");
  opnd_array(5)->ext_format(ra, this,idx5, st); // labl
  st->print("  P=%f C=%f",_prob,_fcnt);
}
#endif
#ifndef PRODUCT
void cmpI_branch_bitNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// op1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// op2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// op3
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// labl
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// 
  st->print_raw("tb");
  opnd_array(1)->ext_format(ra, this,idx1, st); // cmp
  st->print_raw("   ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // op1
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // op2
  st->print_raw(", ");
  opnd_array(5)->ext_format(ra, this,idx5, st); // labl
  st->print("  P=%f C=%f",_prob,_fcnt);
}
#endif
#ifndef PRODUCT
void far_cmpL_branch_signNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// op1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// op2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// labl
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// 
  st->print_raw("cb");
  opnd_array(1)->ext_format(ra, this,idx1, st); // cmp
  st->print_raw("   ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // op1
  st->print_raw(", ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // labl
  st->print_raw(" # long");
  st->print("  P=%f C=%f",_prob,_fcnt);
}
#endif
#ifndef PRODUCT
void far_cmpI_branch_signNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// op1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// op2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// labl
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// 
  st->print_raw("cb");
  opnd_array(1)->ext_format(ra, this,idx1, st); // cmp
  st->print_raw("   ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // op1
  st->print_raw(", ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // labl
  st->print_raw(" # int");
  st->print("  P=%f C=%f",_prob,_fcnt);
}
#endif
#ifndef PRODUCT
void far_cmpL_branch_bitNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// op1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// op2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// op3
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// labl
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// 
  st->print_raw("tb");
  opnd_array(1)->ext_format(ra, this,idx1, st); // cmp
  st->print_raw("   ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // op1
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // op2
  st->print_raw(", ");
  opnd_array(5)->ext_format(ra, this,idx5, st); // labl
  st->print("  P=%f C=%f",_prob,_fcnt);
}
#endif
#ifndef PRODUCT
void far_cmpI_branch_bitNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// op1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// op2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// op3
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// labl
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// 
  st->print_raw("tb");
  opnd_array(1)->ext_format(ra, this,idx1, st); // cmp
  st->print_raw("   ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // op1
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // op2
  st->print_raw(", ");
  opnd_array(5)->ext_format(ra, this,idx5, st); // labl
  st->print("  P=%f C=%f",_prob,_fcnt);
}
#endif
#ifndef PRODUCT
void cmpL_andNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// op1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// op2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// op3
  st->print_raw("tst ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // op1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // op2
  st->print_raw(" # long");
}
#endif
#ifndef PRODUCT
void cmpI_andNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// op1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// op2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// op3
  st->print_raw("tst ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // op1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // op2
  st->print_raw(" # int");
}
#endif
#ifndef PRODUCT
void cmpL_and_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// op1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// op2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// op3
  st->print_raw("tst ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // op1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // op2
  st->print_raw(" # long");
}
#endif
#ifndef PRODUCT
void cmpI_and_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// op1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// op2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// op3
  st->print_raw("tstw ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // op1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // op2
  st->print_raw(" # int");
}
#endif
#ifndef PRODUCT
void branchLoopEndNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// cr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// lbl
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// 
  st->print_raw("b");
  opnd_array(1)->ext_format(ra, this,idx1, st); // cmp
  st->print_raw(" ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // lbl
  st->print_raw(" \t// counted loop end");
  st->print("  P=%f C=%f",_prob,_fcnt);
}
#endif
#ifndef PRODUCT
void cmpFastLockNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// object
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// box
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// tmp
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// tmp2
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// tmp3
  st->print_raw("fastlock ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // object
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // box
  st->print_raw("\t! kills ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // tmp
  st->print_raw(",");
  opnd_array(4)->ext_format(ra, this,idx4, st); // tmp2
  st->print_raw(",");
  opnd_array(5)->ext_format(ra, this,idx5, st); // tmp3
}
#endif
#ifndef PRODUCT
void cmpFastUnlockNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// object
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// box
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// tmp
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// tmp2
  st->print_raw("fastunlock ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // object
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // box
  st->print_raw("\t! kills ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // tmp
  st->print_raw(", ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // tmp2
}
#endif
#ifndef PRODUCT
void cmpFastLockLightweightNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// object
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// box
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// tmp
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// tmp2
  st->print_raw("fastlock ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // object
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // box
  st->print_raw("\t! kills ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // tmp
  st->print_raw(",");
  opnd_array(4)->ext_format(ra, this,idx4, st); // tmp2
}
#endif
#ifndef PRODUCT
void cmpFastUnlockLightweightNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// object
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// box
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// tmp
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// tmp2
  st->print_raw("fastunlock ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // object
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // box
  st->print_raw("\t! kills ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // tmp
  st->print_raw(", ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // tmp2
}
#endif
#ifndef PRODUCT
void safePointNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 5;
  unsigned idx1 = 5; 	// cr
  st->print_raw("ldrw zr, [");
  opnd_array(1)->ext_format(ra, this,idx1, st); // poll
  st->print_raw("]\t# Safepoint: poll for GC");
  st->print_raw("");
  if (_jvms) _jvms->format(ra, this, st); else st->print_cr("        No JVM State Info");
  st->print("        # ");
  if( _jvms && _oop_map ) _oop_map->print_on(st);
}
#endif
#ifndef PRODUCT
void CallStaticJavaDirectNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// 
  st->print_raw("call,static ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // meth
  st->print_raw(" \t// ==> ");
  if( _method ) _method->print_short_name(st);
  else st->print(" wrapper for: %s", _name);
  if( !_method ) dump_trap_args(st);
  st->cr();
  if (_jvms) _jvms->format(ra, this, st); else st->print_cr("        No JVM State Info");
  st->print("        # ");
  if( _jvms && _oop_map ) _oop_map->print_on(st);
}
#endif
#ifndef PRODUCT
void CallDynamicJavaDirectNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// 
  st->print_raw("CALL,dynamic ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // meth
  st->print_raw(" \t// ==> ");
  _method->print_short_name(st);
  st->cr();
  if (_jvms) _jvms->format(ra, this, st); else st->print_cr("        No JVM State Info");
  st->print("        # ");
  if( _jvms && _oop_map ) _oop_map->print_on(st);
}
#endif
#ifndef PRODUCT
void CallRuntimeDirectNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// 
  st->print_raw("CALL, runtime ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // meth
  st->print(" %s", _name);  st->cr();
  if (_jvms) _jvms->format(ra, this, st); else st->print_cr("        No JVM State Info");
  st->print("        # ");
  if( _jvms && _oop_map ) _oop_map->print_on(st);
}
#endif
#ifndef PRODUCT
void CallLeafDirectNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// 
  st->print_raw("CALL, runtime leaf ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // meth
  st->print(" %s", _name);  st->cr();
  if (_jvms) _jvms->format(ra, this, st); else st->print_cr("        No JVM State Info");
  st->print("        # ");
  if( _jvms && _oop_map ) _oop_map->print_on(st);
}
#endif
#ifndef PRODUCT
void CallLeafNoFPDirectNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// 
  st->print_raw("CALL, runtime leaf nofp ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // meth
  st->print(" %s", _name);  st->cr();
  if (_jvms) _jvms->format(ra, this, st); else st->print_cr("        No JVM State Info");
  st->print("        # ");
  if( _jvms && _oop_map ) _oop_map->print_on(st);
}
#endif
#ifndef PRODUCT
void TailCalljmpIndNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 5;
  unsigned idx1 = 5; 	// method_ptr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// 
  st->print_raw("br ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // jump_target
  st->print_raw("\t# ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // method_ptr
  st->print_raw(" holds method");
}
#endif
#ifndef PRODUCT
void TailjmpIndNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 5;
  unsigned idx1 = 5; 	// ex_oop
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// 
  st->print_raw("br ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // jump_target
  st->print_raw("\t# ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // ex_oop
  st->print_raw(" holds exception oop");
}
#endif
#ifndef PRODUCT
void CreateExceptionNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  st->print_raw(" -- \t// exception oop; no code emitted");
}
#endif
#ifndef PRODUCT
void RethrowExceptionNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  st->print_raw("b rethrow_stub");
}
#endif
#ifndef PRODUCT
void RetNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  st->print_raw("ret\t// return register");
}
#endif
#ifndef PRODUCT
void ShouldNotReachHereNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  st->print_raw("ShouldNotReachHere");
}
#endif
#ifndef PRODUCT
void partialSubtypeCheckNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// sub
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// super
  st->print_raw("partialSubtypeCheck ");
  opnd_array(0)->int_format(ra, this, st); // result
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // sub
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // super
}
#endif
#ifndef PRODUCT
void partialSubtypeCheckVsZeroNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// sub
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// super
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// zero
  st->print_raw("partialSubtypeCheck ");
      st->print_raw("R5");
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // sub
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // super
  st->print_raw(" == 0");
}
#endif
#ifndef PRODUCT
void string_compareUNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// str1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// cnt1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// str2
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// cnt2
  st->print_raw("String Compare ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // str1
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // cnt1
  st->print_raw(",");
  opnd_array(3)->ext_format(ra, this,idx3, st); // str2
  st->print_raw(",");
  opnd_array(4)->ext_format(ra, this,idx4, st); // cnt2
  st->print_raw(" -> ");
  opnd_array(0)->int_format(ra, this, st); // result
  st->print_raw("   # KILL ");
      st->print_raw("R10");
}
#endif
#ifndef PRODUCT
void string_compareLNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// str1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// cnt1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// str2
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// cnt2
  st->print_raw("String Compare ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // str1
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // cnt1
  st->print_raw(",");
  opnd_array(3)->ext_format(ra, this,idx3, st); // str2
  st->print_raw(",");
  opnd_array(4)->ext_format(ra, this,idx4, st); // cnt2
  st->print_raw(" -> ");
  opnd_array(0)->int_format(ra, this, st); // result
  st->print_raw("   # KILL ");
      st->print_raw("R10");
}
#endif
#ifndef PRODUCT
void string_compareULNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// str1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// cnt1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// str2
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// cnt2
  st->print_raw("String Compare ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // str1
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // cnt1
  st->print_raw(",");
  opnd_array(3)->ext_format(ra, this,idx3, st); // str2
  st->print_raw(",");
  opnd_array(4)->ext_format(ra, this,idx4, st); // cnt2
  st->print_raw(" -> ");
  opnd_array(0)->int_format(ra, this, st); // result
  st->print_raw("   # KILL ");
      st->print_raw("R10");
  st->print_raw(", ");
      st->print_raw("R11");
  st->print_raw(", ");
      st->print_raw("V0");
  st->print_raw(", ");
      st->print_raw("V1");
  st->print_raw(", ");
      st->print_raw("V2");
}
#endif
#ifndef PRODUCT
void string_compareLUNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// str1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// cnt1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// str2
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// cnt2
  st->print_raw("String Compare ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // str1
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // cnt1
  st->print_raw(",");
  opnd_array(3)->ext_format(ra, this,idx3, st); // str2
  st->print_raw(",");
  opnd_array(4)->ext_format(ra, this,idx4, st); // cnt2
  st->print_raw(" -> ");
  opnd_array(0)->int_format(ra, this, st); // result
  st->print_raw("   # KILL ");
      st->print_raw("R10");
  st->print_raw(", ");
      st->print_raw("R11");
  st->print_raw(", ");
      st->print_raw("V0");
  st->print_raw(", ");
      st->print_raw("V1");
  st->print_raw(", ");
      st->print_raw("V2");
}
#endif
#ifndef PRODUCT
void string_compareLL_sveNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// str1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// cnt1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// str2
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// cnt2
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// tmp1
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// tmp2
  unsigned idx7 = idx6 + opnd_array(6)->num_edges(); 	// vtmp1
  unsigned idx8 = idx7 + opnd_array(7)->num_edges(); 	// vtmp2
  unsigned idx9 = idx8 + opnd_array(8)->num_edges(); 	// pgtmp1
  unsigned idx10 = idx9 + opnd_array(9)->num_edges(); 	// pgtmp2
  st->print_raw("String Compare ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // str1
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // cnt1
  st->print_raw(",");
  opnd_array(3)->ext_format(ra, this,idx3, st); // str2
  st->print_raw(",");
  opnd_array(4)->ext_format(ra, this,idx4, st); // cnt2
  st->print_raw(" -> ");
  opnd_array(0)->int_format(ra, this, st); // result
  st->print_raw("   # USE sve");
}
#endif
#ifndef PRODUCT
void string_compareLU_sveNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// str1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// cnt1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// str2
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// cnt2
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// tmp1
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// tmp2
  unsigned idx7 = idx6 + opnd_array(6)->num_edges(); 	// vtmp1
  unsigned idx8 = idx7 + opnd_array(7)->num_edges(); 	// vtmp2
  unsigned idx9 = idx8 + opnd_array(8)->num_edges(); 	// pgtmp1
  unsigned idx10 = idx9 + opnd_array(9)->num_edges(); 	// pgtmp2
  st->print_raw("String Compare ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // str1
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // cnt1
  st->print_raw(",");
  opnd_array(3)->ext_format(ra, this,idx3, st); // str2
  st->print_raw(",");
  opnd_array(4)->ext_format(ra, this,idx4, st); // cnt2
  st->print_raw(" -> ");
  opnd_array(0)->int_format(ra, this, st); // result
  st->print_raw("   # USE sve");
}
#endif
#ifndef PRODUCT
void string_compareUL_sveNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// str1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// cnt1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// str2
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// cnt2
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// tmp1
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// tmp2
  unsigned idx7 = idx6 + opnd_array(6)->num_edges(); 	// vtmp1
  unsigned idx8 = idx7 + opnd_array(7)->num_edges(); 	// vtmp2
  unsigned idx9 = idx8 + opnd_array(8)->num_edges(); 	// pgtmp1
  unsigned idx10 = idx9 + opnd_array(9)->num_edges(); 	// pgtmp2
  st->print_raw("String Compare ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // str1
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // cnt1
  st->print_raw(",");
  opnd_array(3)->ext_format(ra, this,idx3, st); // str2
  st->print_raw(",");
  opnd_array(4)->ext_format(ra, this,idx4, st); // cnt2
  st->print_raw(" -> ");
  opnd_array(0)->int_format(ra, this, st); // result
  st->print_raw("   # USE sve");
}
#endif
#ifndef PRODUCT
void string_compareUU_sveNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// str1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// cnt1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// str2
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// cnt2
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// tmp1
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// tmp2
  unsigned idx7 = idx6 + opnd_array(6)->num_edges(); 	// vtmp1
  unsigned idx8 = idx7 + opnd_array(7)->num_edges(); 	// vtmp2
  unsigned idx9 = idx8 + opnd_array(8)->num_edges(); 	// pgtmp1
  unsigned idx10 = idx9 + opnd_array(9)->num_edges(); 	// pgtmp2
  st->print_raw("String Compare ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // str1
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // cnt1
  st->print_raw(",");
  opnd_array(3)->ext_format(ra, this,idx3, st); // str2
  st->print_raw(",");
  opnd_array(4)->ext_format(ra, this,idx4, st); // cnt2
  st->print_raw(" -> ");
  opnd_array(0)->int_format(ra, this, st); // result
  st->print_raw("   # USE sve");
}
#endif
#ifndef PRODUCT
void string_indexofUUNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// str1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// cnt1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// str2
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// cnt2
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// tmp1
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// tmp2
  unsigned idx7 = idx6 + opnd_array(6)->num_edges(); 	// tmp3
  unsigned idx8 = idx7 + opnd_array(7)->num_edges(); 	// tmp4
  unsigned idx9 = idx8 + opnd_array(8)->num_edges(); 	// tmp5
  unsigned idx10 = idx9 + opnd_array(9)->num_edges(); 	// tmp6
  unsigned idx11 = idx10 + opnd_array(10)->num_edges(); 	// vtmp0
  unsigned idx12 = idx11 + opnd_array(11)->num_edges(); 	// vtmp1
  st->print_raw("String IndexOf ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // str1
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // cnt1
  st->print_raw(",");
  opnd_array(3)->ext_format(ra, this,idx3, st); // str2
  st->print_raw(",");
  opnd_array(4)->ext_format(ra, this,idx4, st); // cnt2
  st->print_raw(" -> ");
  opnd_array(0)->int_format(ra, this, st); // result
  st->print_raw(" (UU) ");
  st->print_raw("# KILL ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // str1
  st->print_raw(" ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // cnt1
  st->print_raw(" ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // str2
  st->print_raw(" ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // cnt2
  st->print_raw(" ");
  opnd_array(5)->ext_format(ra, this,idx5, st); // tmp1
  st->print_raw(" ");
  opnd_array(6)->ext_format(ra, this,idx6, st); // tmp2
  st->print_raw(" ");
  opnd_array(7)->ext_format(ra, this,idx7, st); // tmp3
  st->print_raw(" ");
  opnd_array(8)->ext_format(ra, this,idx8, st); // tmp4
  st->print_raw(" ");
  opnd_array(9)->ext_format(ra, this,idx9, st); // tmp5
  st->print_raw(" ");
  opnd_array(10)->ext_format(ra, this,idx10, st); // tmp6
  st->print_raw(" V0-V1 cr");
}
#endif
#ifndef PRODUCT
void string_indexofLLNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// str1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// cnt1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// str2
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// cnt2
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// tmp1
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// tmp2
  unsigned idx7 = idx6 + opnd_array(6)->num_edges(); 	// tmp3
  unsigned idx8 = idx7 + opnd_array(7)->num_edges(); 	// tmp4
  unsigned idx9 = idx8 + opnd_array(8)->num_edges(); 	// tmp5
  unsigned idx10 = idx9 + opnd_array(9)->num_edges(); 	// tmp6
  unsigned idx11 = idx10 + opnd_array(10)->num_edges(); 	// vtmp0
  unsigned idx12 = idx11 + opnd_array(11)->num_edges(); 	// vtmp1
  st->print_raw("String IndexOf ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // str1
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // cnt1
  st->print_raw(",");
  opnd_array(3)->ext_format(ra, this,idx3, st); // str2
  st->print_raw(",");
  opnd_array(4)->ext_format(ra, this,idx4, st); // cnt2
  st->print_raw(" -> ");
  opnd_array(0)->int_format(ra, this, st); // result
  st->print_raw(" (LL) ");
  st->print_raw("# KILL ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // str1
  st->print_raw(" ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // cnt1
  st->print_raw(" ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // str2
  st->print_raw(" ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // cnt2
  st->print_raw(" ");
  opnd_array(5)->ext_format(ra, this,idx5, st); // tmp1
  st->print_raw(" ");
  opnd_array(6)->ext_format(ra, this,idx6, st); // tmp2
  st->print_raw(" ");
  opnd_array(7)->ext_format(ra, this,idx7, st); // tmp3
  st->print_raw(" ");
  opnd_array(8)->ext_format(ra, this,idx8, st); // tmp4
  st->print_raw(" ");
  opnd_array(9)->ext_format(ra, this,idx9, st); // tmp5
  st->print_raw(" ");
  opnd_array(10)->ext_format(ra, this,idx10, st); // tmp6
  st->print_raw(" V0-V1 cr");
}
#endif
#ifndef PRODUCT
void string_indexofULNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// str1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// cnt1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// str2
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// cnt2
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// tmp1
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// tmp2
  unsigned idx7 = idx6 + opnd_array(6)->num_edges(); 	// tmp3
  unsigned idx8 = idx7 + opnd_array(7)->num_edges(); 	// tmp4
  unsigned idx9 = idx8 + opnd_array(8)->num_edges(); 	// tmp5
  unsigned idx10 = idx9 + opnd_array(9)->num_edges(); 	// tmp6
  unsigned idx11 = idx10 + opnd_array(10)->num_edges(); 	// vtmp0
  unsigned idx12 = idx11 + opnd_array(11)->num_edges(); 	// vtmp1
  st->print_raw("String IndexOf ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // str1
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // cnt1
  st->print_raw(",");
  opnd_array(3)->ext_format(ra, this,idx3, st); // str2
  st->print_raw(",");
  opnd_array(4)->ext_format(ra, this,idx4, st); // cnt2
  st->print_raw(" -> ");
  opnd_array(0)->int_format(ra, this, st); // result
  st->print_raw(" (UL) ");
  st->print_raw("# KILL ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // str1
  st->print_raw(" cnt1 ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // str2
  st->print_raw(" ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // cnt2
  st->print_raw(" ");
  opnd_array(5)->ext_format(ra, this,idx5, st); // tmp1
  st->print_raw(" ");
  opnd_array(6)->ext_format(ra, this,idx6, st); // tmp2
  st->print_raw(" ");
  opnd_array(7)->ext_format(ra, this,idx7, st); // tmp3
  st->print_raw(" ");
  opnd_array(8)->ext_format(ra, this,idx8, st); // tmp4
  st->print_raw(" ");
  opnd_array(9)->ext_format(ra, this,idx9, st); // tmp5
  st->print_raw(" ");
  opnd_array(10)->ext_format(ra, this,idx10, st); // tmp6
  st->print_raw(" V0-V1 cr");
}
#endif
#ifndef PRODUCT
void string_indexof_conUUNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// str1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// cnt1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// str2
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// int_cnt2
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// tmp1
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// tmp2
  unsigned idx7 = idx6 + opnd_array(6)->num_edges(); 	// tmp3
  unsigned idx8 = idx7 + opnd_array(7)->num_edges(); 	// tmp4
  st->print_raw("String IndexOf ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // str1
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // cnt1
  st->print_raw(",");
  opnd_array(3)->ext_format(ra, this,idx3, st); // str2
  st->print_raw(",");
  opnd_array(4)->ext_format(ra, this,idx4, st); // int_cnt2
  st->print_raw(" -> ");
  opnd_array(0)->int_format(ra, this, st); // result
  st->print_raw(" (UU) ");
  st->print_raw("# KILL ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // str1
  st->print_raw(" ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // cnt1
  st->print_raw(" ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // str2
  st->print_raw(" ");
  opnd_array(5)->ext_format(ra, this,idx5, st); // tmp1
  st->print_raw(" ");
  opnd_array(6)->ext_format(ra, this,idx6, st); // tmp2
  st->print_raw(" ");
  opnd_array(7)->ext_format(ra, this,idx7, st); // tmp3
  st->print_raw(" ");
  opnd_array(8)->ext_format(ra, this,idx8, st); // tmp4
  st->print_raw(" cr");
}
#endif
#ifndef PRODUCT
void string_indexof_conLLNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// str1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// cnt1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// str2
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// int_cnt2
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// tmp1
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// tmp2
  unsigned idx7 = idx6 + opnd_array(6)->num_edges(); 	// tmp3
  unsigned idx8 = idx7 + opnd_array(7)->num_edges(); 	// tmp4
  st->print_raw("String IndexOf ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // str1
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // cnt1
  st->print_raw(",");
  opnd_array(3)->ext_format(ra, this,idx3, st); // str2
  st->print_raw(",");
  opnd_array(4)->ext_format(ra, this,idx4, st); // int_cnt2
  st->print_raw(" -> ");
  opnd_array(0)->int_format(ra, this, st); // result
  st->print_raw(" (LL) ");
  st->print_raw("# KILL ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // str1
  st->print_raw(" ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // cnt1
  st->print_raw(" ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // str2
  st->print_raw(" ");
  opnd_array(5)->ext_format(ra, this,idx5, st); // tmp1
  st->print_raw(" ");
  opnd_array(6)->ext_format(ra, this,idx6, st); // tmp2
  st->print_raw(" ");
  opnd_array(7)->ext_format(ra, this,idx7, st); // tmp3
  st->print_raw(" ");
  opnd_array(8)->ext_format(ra, this,idx8, st); // tmp4
  st->print_raw(" cr");
}
#endif
#ifndef PRODUCT
void string_indexof_conULNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// str1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// cnt1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// str2
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// int_cnt2
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// tmp1
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// tmp2
  unsigned idx7 = idx6 + opnd_array(6)->num_edges(); 	// tmp3
  unsigned idx8 = idx7 + opnd_array(7)->num_edges(); 	// tmp4
  st->print_raw("String IndexOf ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // str1
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // cnt1
  st->print_raw(",");
  opnd_array(3)->ext_format(ra, this,idx3, st); // str2
  st->print_raw(",");
  opnd_array(4)->ext_format(ra, this,idx4, st); // int_cnt2
  st->print_raw(" -> ");
  opnd_array(0)->int_format(ra, this, st); // result
  st->print_raw(" (UL) ");
  st->print_raw("# KILL ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // str1
  st->print_raw(" ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // cnt1
  st->print_raw(" ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // str2
  st->print_raw(" ");
  opnd_array(5)->ext_format(ra, this,idx5, st); // tmp1
  st->print_raw(" ");
  opnd_array(6)->ext_format(ra, this,idx6, st); // tmp2
  st->print_raw(" ");
  opnd_array(7)->ext_format(ra, this,idx7, st); // tmp3
  st->print_raw(" ");
  opnd_array(8)->ext_format(ra, this,idx8, st); // tmp4
  st->print_raw(" cr");
}
#endif
#ifndef PRODUCT
void string_indexof_charNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// str1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// cnt1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// ch
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// tmp1
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// tmp2
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// tmp3
  st->print_raw("StringUTF16 IndexOf char[] ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // str1
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // cnt1
  st->print_raw(",");
  opnd_array(3)->ext_format(ra, this,idx3, st); // ch
  st->print_raw(" -> ");
  opnd_array(0)->int_format(ra, this, st); // result
}
#endif
#ifndef PRODUCT
void stringL_indexof_charNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// str1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// cnt1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// ch
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// tmp1
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// tmp2
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// tmp3
  st->print_raw("StringLatin1 IndexOf char[] ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // str1
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // cnt1
  st->print_raw(",");
  opnd_array(3)->ext_format(ra, this,idx3, st); // ch
  st->print_raw(" -> ");
  opnd_array(0)->int_format(ra, this, st); // result
}
#endif
#ifndef PRODUCT
void stringL_indexof_char_sveNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// str1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// cnt1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// ch
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// ztmp1
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// ztmp2
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// pgtmp
  unsigned idx7 = idx6 + opnd_array(6)->num_edges(); 	// ptmp
  st->print_raw("StringLatin1 IndexOf char[] ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // str1
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // cnt1
  st->print_raw(",");
  opnd_array(3)->ext_format(ra, this,idx3, st); // ch
  st->print_raw(" -> ");
  opnd_array(0)->int_format(ra, this, st); // result
  st->print_raw(" # use sve");
}
#endif
#ifndef PRODUCT
void stringU_indexof_char_sveNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// str1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// cnt1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// ch
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// ztmp1
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// ztmp2
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// pgtmp
  unsigned idx7 = idx6 + opnd_array(6)->num_edges(); 	// ptmp
  st->print_raw("StringUTF16 IndexOf char[] ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // str1
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // cnt1
  st->print_raw(",");
  opnd_array(3)->ext_format(ra, this,idx3, st); // ch
  st->print_raw(" -> ");
  opnd_array(0)->int_format(ra, this, st); // result
  st->print_raw(" # use sve");
}
#endif
#ifndef PRODUCT
void string_equalsLNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// str1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// str2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// cnt
  st->print_raw("String Equals ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // str1
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // str2
  st->print_raw(",");
  opnd_array(3)->ext_format(ra, this,idx3, st); // cnt
  st->print_raw(" -> ");
  opnd_array(0)->int_format(ra, this, st); // result
}
#endif
#ifndef PRODUCT
void array_equalsBNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// ary1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// ary2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// tmp1
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// tmp2
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// tmp3
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// vtmp0
  unsigned idx7 = idx6 + opnd_array(6)->num_edges(); 	// vtmp1
  unsigned idx8 = idx7 + opnd_array(7)->num_edges(); 	// vtmp2
  unsigned idx9 = idx8 + opnd_array(8)->num_edges(); 	// vtmp3
  unsigned idx10 = idx9 + opnd_array(9)->num_edges(); 	// vtmp4
  unsigned idx11 = idx10 + opnd_array(10)->num_edges(); 	// vtmp5
  unsigned idx12 = idx11 + opnd_array(11)->num_edges(); 	// vtmp6
  unsigned idx13 = idx12 + opnd_array(12)->num_edges(); 	// vtmp7
  st->print_raw("Array Equals ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // ary1
  st->print_raw(",ary2 -> ");
  opnd_array(0)->int_format(ra, this, st); // result
  st->print_raw(" # KILL ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // ary1
  st->print_raw(" ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // ary2
  st->print_raw(" ");
      st->print_raw("R10");
  st->print_raw(" ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // tmp1
  st->print_raw(" ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // tmp2
  st->print_raw(" ");
  opnd_array(5)->ext_format(ra, this,idx5, st); // tmp3
  st->print_raw(" V0-V7 cr");
}
#endif
#ifndef PRODUCT
void array_equalsCNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// ary1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// ary2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// tmp1
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// tmp2
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// tmp3
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// vtmp0
  unsigned idx7 = idx6 + opnd_array(6)->num_edges(); 	// vtmp1
  unsigned idx8 = idx7 + opnd_array(7)->num_edges(); 	// vtmp2
  unsigned idx9 = idx8 + opnd_array(8)->num_edges(); 	// vtmp3
  unsigned idx10 = idx9 + opnd_array(9)->num_edges(); 	// vtmp4
  unsigned idx11 = idx10 + opnd_array(10)->num_edges(); 	// vtmp5
  unsigned idx12 = idx11 + opnd_array(11)->num_edges(); 	// vtmp6
  unsigned idx13 = idx12 + opnd_array(12)->num_edges(); 	// vtmp7
  st->print_raw("Array Equals ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // ary1
  st->print_raw(",ary2 -> ");
  opnd_array(0)->int_format(ra, this, st); // result
  st->print_raw(" # KILL ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // ary1
  st->print_raw(" ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // ary2
  st->print_raw(" ");
      st->print_raw("R10");
  st->print_raw(" ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // tmp1
  st->print_raw(" ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // tmp2
  st->print_raw(" ");
  opnd_array(5)->ext_format(ra, this,idx5, st); // tmp3
  st->print_raw(" V0-V7 cr");
}
#endif
#ifndef PRODUCT
void count_positivesNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// ary1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// len
  st->print_raw("count positives byte[] ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // ary1
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // len
  st->print_raw(" -> ");
  opnd_array(0)->int_format(ra, this, st); // result
}
#endif
#ifndef PRODUCT
void string_compressNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// len
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// vtmp0
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// vtmp1
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// vtmp2
  unsigned idx7 = idx6 + opnd_array(6)->num_edges(); 	// vtmp3
  unsigned idx8 = idx7 + opnd_array(7)->num_edges(); 	// vtmp4
  unsigned idx9 = idx8 + opnd_array(8)->num_edges(); 	// vtmp5
  st->print_raw("String Compress ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // dst
  st->print_raw(",");
  opnd_array(3)->ext_format(ra, this,idx3, st); // len
  st->print_raw(" -> ");
  opnd_array(0)->int_format(ra, this, st); // result
  st->print_raw(" # KILL ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(" ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // dst
  st->print_raw(" V0-V5 cr");
}
#endif
#ifndef PRODUCT
void string_inflateNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// len
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// tmp
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// vtmp0
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// vtmp1
  unsigned idx7 = idx6 + opnd_array(6)->num_edges(); 	// vtmp2
  unsigned idx8 = idx7 + opnd_array(7)->num_edges(); 	// vtmp3
  unsigned idx9 = idx8 + opnd_array(8)->num_edges(); 	// vtmp4
  unsigned idx10 = idx9 + opnd_array(9)->num_edges(); 	// vtmp5
  unsigned idx11 = idx10 + opnd_array(10)->num_edges(); 	// vtmp6
  st->print_raw("String Inflate ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // dst
  st->print_raw(" # KILL ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // tmp
  st->print_raw(" ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(" ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // dst
  st->print_raw(" ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // len
  st->print_raw(" V0-V6 cr");
}
#endif
#ifndef PRODUCT
void encode_iso_arrayNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// len
  st->print_raw("Encode ISO array ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // dst
  st->print_raw(",");
  opnd_array(3)->ext_format(ra, this,idx3, st); // len
  st->print_raw(" -> ");
  opnd_array(0)->int_format(ra, this, st); // result
  st->print_raw(" # KILL ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(" ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // dst
  st->print_raw(" V0-V5 cr");
}
#endif
#ifndef PRODUCT
void encode_ascii_arrayNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// len
  st->print_raw("Encode ASCII array ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // dst
  st->print_raw(",");
  opnd_array(3)->ext_format(ra, this,idx3, st); // len
  st->print_raw(" -> ");
  opnd_array(0)->int_format(ra, this, st); // result
  st->print_raw(" # KILL ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(" ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // dst
  st->print_raw(" V0-V5 cr");
}
#endif
#ifndef PRODUCT
void compressBitsI_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// mask
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// tdst
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// tsrc
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// tmask
  st->print_raw("mov    ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // tsrc
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\n\t");
  st->print_raw("mov    ");
  opnd_array(5)->ext_format(ra, this,idx5, st); // tmask
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // mask
  st->print_raw("\n\t");
  st->print_raw("bext   ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // tdst
  st->print_raw(", ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // tsrc
  st->print_raw(", ");
  opnd_array(5)->ext_format(ra, this,idx5, st); // tmask
  st->print_raw("\n\t");
  st->print_raw("mov    ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // tdst
}
#endif
#ifndef PRODUCT
void compressBitsI_memconNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// mask
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// tdst
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// tsrc
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// tmask
  st->print_raw("ldrs   ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // tsrc
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("\n\t");
  st->print_raw("ldrs   ");
  opnd_array(5)->ext_format(ra, this,idx5, st); // tmask
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // mask
  st->print_raw("\n\t");
  st->print_raw("bext   ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // tdst
  st->print_raw(", ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // tsrc
  st->print_raw(", ");
  opnd_array(5)->ext_format(ra, this,idx5, st); // tmask
  st->print_raw("\n\t");
  st->print_raw("mov    ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // tdst
}
#endif
#ifndef PRODUCT
void compressBitsL_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// mask
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// tdst
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// tsrc
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// tmask
  st->print_raw("mov    ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // tsrc
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\n\t");
  st->print_raw("mov    ");
  opnd_array(5)->ext_format(ra, this,idx5, st); // tmask
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // mask
  st->print_raw("\n\t");
  st->print_raw("bext   ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // tdst
  st->print_raw(", ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // tsrc
  st->print_raw(", ");
  opnd_array(5)->ext_format(ra, this,idx5, st); // tmask
  st->print_raw("\n\t");
  st->print_raw("mov    ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // tdst
}
#endif
#ifndef PRODUCT
void compressBitsL_memconNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// mask
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// tdst
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// tsrc
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// tmask
  st->print_raw("ldrd   ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // tsrc
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("\n\t");
  st->print_raw("ldrd   ");
  opnd_array(5)->ext_format(ra, this,idx5, st); // tmask
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // mask
  st->print_raw("\n\t");
  st->print_raw("bext   ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // tdst
  st->print_raw(", ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // tsrc
  st->print_raw(", ");
  opnd_array(5)->ext_format(ra, this,idx5, st); // tmask
  st->print_raw("\n\t");
  st->print_raw("mov    ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // tdst
}
#endif
#ifndef PRODUCT
void expandBitsI_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// mask
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// tdst
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// tsrc
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// tmask
  st->print_raw("mov    ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // tsrc
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\n\t");
  st->print_raw("mov    ");
  opnd_array(5)->ext_format(ra, this,idx5, st); // tmask
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // mask
  st->print_raw("\n\t");
  st->print_raw("bdep   ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // tdst
  st->print_raw(", ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // tsrc
  st->print_raw(", ");
  opnd_array(5)->ext_format(ra, this,idx5, st); // tmask
  st->print_raw("\n\t");
  st->print_raw("mov    ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // tdst
}
#endif
#ifndef PRODUCT
void expandBitsI_memconNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// mask
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// tdst
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// tsrc
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// tmask
  st->print_raw("ldrs   ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // tsrc
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("\n\t");
  st->print_raw("ldrs   ");
  opnd_array(5)->ext_format(ra, this,idx5, st); // tmask
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // mask
  st->print_raw("\n\t");
  st->print_raw("bdep   ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // tdst
  st->print_raw(", ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // tsrc
  st->print_raw(", ");
  opnd_array(5)->ext_format(ra, this,idx5, st); // tmask
  st->print_raw("\n\t");
  st->print_raw("mov    ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // tdst
}
#endif
#ifndef PRODUCT
void expandBitsL_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// mask
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// tdst
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// tsrc
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// tmask
  st->print_raw("mov    ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // tsrc
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\n\t");
  st->print_raw("mov    ");
  opnd_array(5)->ext_format(ra, this,idx5, st); // tmask
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // mask
  st->print_raw("\n\t");
  st->print_raw("bdep   ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // tdst
  st->print_raw(", ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // tsrc
  st->print_raw(", ");
  opnd_array(5)->ext_format(ra, this,idx5, st); // tmask
  st->print_raw("\n\t");
  st->print_raw("mov    ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // tdst
}
#endif
#ifndef PRODUCT
void expandBitsL_memconNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// mask
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// tdst
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// tsrc
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// tmask
  st->print_raw("ldrd   ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // tsrc
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("\n\t");
  st->print_raw("ldrd   ");
  opnd_array(5)->ext_format(ra, this,idx5, st); // tmask
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // mask
  st->print_raw("\n\t");
  st->print_raw("bdep   ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // tdst
  st->print_raw(", ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // tsrc
  st->print_raw(", ");
  opnd_array(5)->ext_format(ra, this,idx5, st); // tmask
  st->print_raw("\n\t");
  st->print_raw("mov    ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // tdst
}
#endif
#ifndef PRODUCT
void tlsLoadPNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// 
  st->print_raw(" -- \t// ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw("=Thread::current(), empty");
}
#endif
#ifndef PRODUCT
void loadV2Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  st->print_raw("loadV2 ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("\t# vector (16 bits)");
  if (ra->C->alias_type(adr_type())->field() != nullptr) {
    ciField* f = ra->C->alias_type(adr_type())->field();
    st->print(" ! Field: ");
    if (f->is_volatile())
      st->print("volatile ");
    f->holder()->name()->print_symbol_on(st);
    st->print(".");
    f->name()->print_symbol_on(st);
    if (f->is_constant())
      st->print(" (constant)");
  } else {
    if (ra->C->alias_type(adr_type())->is_volatile())
      st->print(" volatile!");
  }
}
#endif
#ifndef PRODUCT
void storeV2Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  st->print_raw("storeV2 ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
  st->print_raw("\t# vector (16 bits)");
  if (ra->C->alias_type(adr_type())->field() != nullptr) {
    ciField* f = ra->C->alias_type(adr_type())->field();
    st->print(" ! Field: ");
    if (f->is_volatile())
      st->print("volatile ");
    f->holder()->name()->print_symbol_on(st);
    st->print(".");
    f->name()->print_symbol_on(st);
    if (f->is_constant())
      st->print(" (constant)");
  } else {
    if (ra->C->alias_type(adr_type())->is_volatile())
      st->print(" volatile!");
  }
}
#endif
#ifndef PRODUCT
void loadV4Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  st->print_raw("loadV4 ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("\t# vector (32 bits)");
  if (ra->C->alias_type(adr_type())->field() != nullptr) {
    ciField* f = ra->C->alias_type(adr_type())->field();
    st->print(" ! Field: ");
    if (f->is_volatile())
      st->print("volatile ");
    f->holder()->name()->print_symbol_on(st);
    st->print(".");
    f->name()->print_symbol_on(st);
    if (f->is_constant())
      st->print(" (constant)");
  } else {
    if (ra->C->alias_type(adr_type())->is_volatile())
      st->print(" volatile!");
  }
}
#endif
#ifndef PRODUCT
void storeV4Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  st->print_raw("storeV4 ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
  st->print_raw("\t# vector (32 bits)");
  if (ra->C->alias_type(adr_type())->field() != nullptr) {
    ciField* f = ra->C->alias_type(adr_type())->field();
    st->print(" ! Field: ");
    if (f->is_volatile())
      st->print("volatile ");
    f->holder()->name()->print_symbol_on(st);
    st->print(".");
    f->name()->print_symbol_on(st);
    if (f->is_constant())
      st->print(" (constant)");
  } else {
    if (ra->C->alias_type(adr_type())->is_volatile())
      st->print(" volatile!");
  }
}
#endif
#ifndef PRODUCT
void loadV8Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  st->print_raw("loadV8 ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("\t# vector (64 bits)");
  if (ra->C->alias_type(adr_type())->field() != nullptr) {
    ciField* f = ra->C->alias_type(adr_type())->field();
    st->print(" ! Field: ");
    if (f->is_volatile())
      st->print("volatile ");
    f->holder()->name()->print_symbol_on(st);
    st->print(".");
    f->name()->print_symbol_on(st);
    if (f->is_constant())
      st->print(" (constant)");
  } else {
    if (ra->C->alias_type(adr_type())->is_volatile())
      st->print(" volatile!");
  }
}
#endif
#ifndef PRODUCT
void storeV8Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  st->print_raw("storeV8 ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
  st->print_raw("\t# vector (64 bits)");
  if (ra->C->alias_type(adr_type())->field() != nullptr) {
    ciField* f = ra->C->alias_type(adr_type())->field();
    st->print(" ! Field: ");
    if (f->is_volatile())
      st->print("volatile ");
    f->holder()->name()->print_symbol_on(st);
    st->print(".");
    f->name()->print_symbol_on(st);
    if (f->is_constant())
      st->print(" (constant)");
  } else {
    if (ra->C->alias_type(adr_type())->is_volatile())
      st->print(" volatile!");
  }
}
#endif
#ifndef PRODUCT
void loadV16Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  st->print_raw("loadV16 ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("\t# vector (128 bits)");
  if (ra->C->alias_type(adr_type())->field() != nullptr) {
    ciField* f = ra->C->alias_type(adr_type())->field();
    st->print(" ! Field: ");
    if (f->is_volatile())
      st->print("volatile ");
    f->holder()->name()->print_symbol_on(st);
    st->print(".");
    f->name()->print_symbol_on(st);
    if (f->is_constant())
      st->print(" (constant)");
  } else {
    if (ra->C->alias_type(adr_type())->is_volatile())
      st->print(" volatile!");
  }
}
#endif
#ifndef PRODUCT
void storeV16Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  st->print_raw("storeV16 ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
  st->print_raw("\t# vector (128 bits)");
  if (ra->C->alias_type(adr_type())->field() != nullptr) {
    ciField* f = ra->C->alias_type(adr_type())->field();
    st->print(" ! Field: ");
    if (f->is_volatile())
      st->print("volatile ");
    f->holder()->name()->print_symbol_on(st);
    st->print(".");
    f->name()->print_symbol_on(st);
    if (f->is_constant())
      st->print(" (constant)");
  } else {
    if (ra->C->alias_type(adr_type())->is_volatile())
      st->print(" volatile!");
  }
}
#endif
#ifndef PRODUCT
void loadVNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  st->print_raw("loadV ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("\t# vector (sve)");
  if (ra->C->alias_type(adr_type())->field() != nullptr) {
    ciField* f = ra->C->alias_type(adr_type())->field();
    st->print(" ! Field: ");
    if (f->is_volatile())
      st->print("volatile ");
    f->holder()->name()->print_symbol_on(st);
    st->print(".");
    f->name()->print_symbol_on(st);
    if (f->is_constant())
      st->print(" (constant)");
  } else {
    if (ra->C->alias_type(adr_type())->is_volatile())
      st->print(" volatile!");
  }
}
#endif
#ifndef PRODUCT
void storeVNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  st->print_raw("storeV ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
  st->print_raw("\t# vector (sve)");
  if (ra->C->alias_type(adr_type())->field() != nullptr) {
    ciField* f = ra->C->alias_type(adr_type())->field();
    st->print(" ! Field: ");
    if (f->is_volatile())
      st->print("volatile ");
    f->holder()->name()->print_symbol_on(st);
    st->print(".");
    f->name()->print_symbol_on(st);
    if (f->is_constant())
      st->print(" (constant)");
  } else {
    if (ra->C->alias_type(adr_type())->is_volatile())
      st->print(" volatile!");
  }
}
#endif
#ifndef PRODUCT
void loadV_maskedNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// pg
  st->print_raw("loadV_masked ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // pg
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  if (ra->C->alias_type(adr_type())->field() != nullptr) {
    ciField* f = ra->C->alias_type(adr_type())->field();
    st->print(" ! Field: ");
    if (f->is_volatile())
      st->print("volatile ");
    f->holder()->name()->print_symbol_on(st);
    st->print(".");
    f->name()->print_symbol_on(st);
    if (f->is_constant())
      st->print(" (constant)");
  } else {
    if (ra->C->alias_type(adr_type())->is_volatile())
      st->print(" volatile!");
  }
}
#endif
#ifndef PRODUCT
void storeV_maskedNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// pg
  st->print_raw("storeV_masked ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // pg
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
  if (ra->C->alias_type(adr_type())->field() != nullptr) {
    ciField* f = ra->C->alias_type(adr_type())->field();
    st->print(" ! Field: ");
    if (f->is_volatile())
      st->print("volatile ");
    f->holder()->name()->print_symbol_on(st);
    st->print(".");
    f->name()->print_symbol_on(st);
    if (f->is_constant())
      st->print(" (constant)");
  } else {
    if (ra->C->alias_type(adr_type())->is_volatile())
      st->print(" volatile!");
  }
}
#endif
#ifndef PRODUCT
void vloadconNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("vloadcon ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\t# load/generate iota indices");
}
#endif
#ifndef PRODUCT
void vaddBNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("vaddB ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void vaddSNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("vaddS ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void vaddINode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("vaddI ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void vaddLNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("vaddL ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void vaddFNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("vaddF ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void vaddDNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("vaddD ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void vaddB_maskedNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// pg
  st->print_raw("vaddB_masked ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // pg
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void vaddS_maskedNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// pg
  st->print_raw("vaddS_masked ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // pg
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void vaddI_maskedNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// pg
  st->print_raw("vaddI_masked ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // pg
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void vaddL_maskedNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// pg
  st->print_raw("vaddL_masked ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // pg
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void vaddF_maskedNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// pg
  st->print_raw("vaddF_masked ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // pg
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void vaddD_maskedNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// pg
  st->print_raw("vaddD_masked ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // pg
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void vaddImmBNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// con
  st->print_raw("vaddImmB ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // con
}
#endif
#ifndef PRODUCT
void vaddImmB_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// con
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst_src
  st->print_raw("vaddImmB ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // dst_src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // dst_src
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // con
}
#endif
#ifndef PRODUCT
void vaddImmSNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// con
  st->print_raw("vaddImmS ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // con
}
#endif
#ifndef PRODUCT
void vaddImmS_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// con
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst_src
  st->print_raw("vaddImmS ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // dst_src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // dst_src
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // con
}
#endif
#ifndef PRODUCT
void vaddImmINode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// con
  st->print_raw("vaddImmI ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // con
}
#endif
#ifndef PRODUCT
void vaddImmI_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// con
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst_src
  st->print_raw("vaddImmI ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // dst_src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // dst_src
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // con
}
#endif
#ifndef PRODUCT
void vaddImmLNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// con
  st->print_raw("vaddImmL ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // con
}
#endif
#ifndef PRODUCT
void vaddImmL_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// con
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst_src
  st->print_raw("vaddImmL ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // dst_src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // dst_src
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // con
}
#endif
#ifndef PRODUCT
void vsubBNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("vsubB ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void vsubSNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("vsubS ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void vsubINode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("vsubI ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void vsubLNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("vsubL ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void vsubFNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("vsubF ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void vsubDNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("vsubD ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void vsubB_maskedNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// pg
  st->print_raw("vsubB_masked ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // pg
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void vsubS_maskedNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// pg
  st->print_raw("vsubS_masked ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // pg
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void vsubI_maskedNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// pg
  st->print_raw("vsubI_masked ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // pg
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void vsubL_maskedNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// pg
  st->print_raw("vsubL_masked ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // pg
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void vsubF_maskedNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// pg
  st->print_raw("vsubF_masked ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // pg
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void vsubD_maskedNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// pg
  st->print_raw("vsubD_masked ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // pg
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void vmulB_neonNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("vmulB_neon ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void vmulB_sveNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("vmulB_sve ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void vmulS_neonNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("vmulS_neon ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void vmulS_sveNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("vmulS_sve ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void vmulI_neonNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("vmulI_neon ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void vmulI_sveNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("vmulI_sve ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void vmulL_neonNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("vmulL_neon ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw("\t# 2L");
}
#endif
#ifndef PRODUCT
void vmulL_sveNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("vmulL_sve ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void vmulFNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("vmulF ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void vmulDNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("vmulD ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void vmulB_maskedNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// pg
  st->print_raw("vmulB_masked ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // pg
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void vmulS_maskedNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// pg
  st->print_raw("vmulS_masked ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // pg
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void vmulI_maskedNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// pg
  st->print_raw("vmulI_masked ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // pg
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void vmulL_maskedNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// pg
  st->print_raw("vmulL_masked ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // pg
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void vmulF_maskedNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// pg
  st->print_raw("vmulF_masked ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // pg
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void vmulD_maskedNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// pg
  st->print_raw("vmulD_masked ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // pg
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void vdivF_neonNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("vdivF_neon ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void vdivF_sveNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("vdivF_sve ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void vdivD_neonNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("vdivD_neon ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void vdivD_sveNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("vdivD_sve ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void vdivF_maskedNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// pg
  st->print_raw("vdivF_masked ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // pg
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void vdivD_maskedNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// pg
  st->print_raw("vdivD_masked ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // pg
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void vandNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("vand ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void vand_maskedNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// pg
  st->print_raw("vand_masked ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // pg
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void vandImmBNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// con
  st->print_raw("vandImmB ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // con
}
#endif
#ifndef PRODUCT
void vandImmB_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// con
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst_src
  st->print_raw("vandImmB ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // dst_src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // dst_src
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // con
}
#endif
#ifndef PRODUCT
void vandImmSNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// con
  st->print_raw("vandImmS ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // con
}
#endif
#ifndef PRODUCT
void vandImmS_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// con
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst_src
  st->print_raw("vandImmS ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // dst_src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // dst_src
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // con
}
#endif
#ifndef PRODUCT
void vandImmINode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// con
  st->print_raw("vandImmI ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // con
}
#endif
#ifndef PRODUCT
void vandImmI_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// con
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst_src
  st->print_raw("vandImmI ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // dst_src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // dst_src
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // con
}
#endif
#ifndef PRODUCT
void vandImmLNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// con
  st->print_raw("vandImmL ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // con
}
#endif
#ifndef PRODUCT
void vandImmL_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// con
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst_src
  st->print_raw("vandImmL ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // dst_src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // dst_src
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // con
}
#endif
#ifndef PRODUCT
void vorNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("vor ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void vor_maskedNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// pg
  st->print_raw("vor_masked ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // pg
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void vorImmBNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// con
  st->print_raw("vorImmB ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // con
}
#endif
#ifndef PRODUCT
void vorImmB_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// con
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst_src
  st->print_raw("vorImmB ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // dst_src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // dst_src
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // con
}
#endif
#ifndef PRODUCT
void vorImmSNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// con
  st->print_raw("vorImmS ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // con
}
#endif
#ifndef PRODUCT
void vorImmS_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// con
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst_src
  st->print_raw("vorImmS ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // dst_src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // dst_src
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // con
}
#endif
#ifndef PRODUCT
void vorImmINode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// con
  st->print_raw("vorImmI ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // con
}
#endif
#ifndef PRODUCT
void vorImmI_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// con
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst_src
  st->print_raw("vorImmI ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // dst_src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // dst_src
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // con
}
#endif
#ifndef PRODUCT
void vorImmLNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// con
  st->print_raw("vorImmL ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // con
}
#endif
#ifndef PRODUCT
void vorImmL_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// con
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst_src
  st->print_raw("vorImmL ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // dst_src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // dst_src
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // con
}
#endif
#ifndef PRODUCT
void vxorNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("vxor ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void vxor_maskedNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// pg
  st->print_raw("vxor_masked ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // pg
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void vxorImmBNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// con
  st->print_raw("vxorImmB ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // con
}
#endif
#ifndef PRODUCT
void vxorImmB_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// con
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst_src
  st->print_raw("vxorImmB ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // dst_src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // dst_src
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // con
}
#endif
#ifndef PRODUCT
void vxorImmSNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// con
  st->print_raw("vxorImmS ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // con
}
#endif
#ifndef PRODUCT
void vxorImmS_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// con
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst_src
  st->print_raw("vxorImmS ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // dst_src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // dst_src
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // con
}
#endif
#ifndef PRODUCT
void vxorImmINode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// con
  st->print_raw("vxorImmI ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // con
}
#endif
#ifndef PRODUCT
void vxorImmI_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// con
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst_src
  st->print_raw("vxorImmI ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // dst_src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // dst_src
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // con
}
#endif
#ifndef PRODUCT
void vxorImmLNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// con
  st->print_raw("vxorImmL ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // con
}
#endif
#ifndef PRODUCT
void vxorImmL_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// con
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst_src
  st->print_raw("vxorImmL ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // dst_src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // dst_src
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // con
}
#endif
#ifndef PRODUCT
void veor3_neonNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src3
  st->print_raw("veor3_neon ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src3
}
#endif
#ifndef PRODUCT
void veor3_neon_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src2
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src3
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src1
  st->print_raw("veor3_neon ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src1
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src2
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src3
}
#endif
#ifndef PRODUCT
void veor3_sveNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src3
  st->print_raw("veor3_sve ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src3
}
#endif
#ifndef PRODUCT
void veor3_sve_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src2
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src3
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// dst_src1
  st->print_raw("veor3_sve ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // dst_src1
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // dst_src1
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src2
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src3
}
#endif
#ifndef PRODUCT
void vnotINode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// m1
  st->print_raw("vnotI ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
}
#endif
#ifndef PRODUCT
void vnotI_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// m1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  st->print_raw("vnotI ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
}
#endif
#ifndef PRODUCT
void vnotLNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// m1
  st->print_raw("vnotL ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
}
#endif
#ifndef PRODUCT
void vnotL_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// m1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  st->print_raw("vnotL ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
}
#endif
#ifndef PRODUCT
void vnotI_maskedNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// m1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// pg
  st->print_raw("vnotI_masked ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // pg
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src
}
#endif
#ifndef PRODUCT
void vnotL_maskedNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// m1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// pg
  st->print_raw("vnotL_masked ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // pg
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src
}
#endif
#ifndef PRODUCT
void vand_notINode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// m1
  st->print_raw("vand_notI ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void vand_notI_1Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src2
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// m1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src1
  st->print_raw("vand_notI ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src1
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src2
}
#endif
#ifndef PRODUCT
void vand_notI_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// m1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  st->print_raw("vand_notI ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src2
}
#endif
#ifndef PRODUCT
void vand_notI_2Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// m1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src1
  st->print_raw("vand_notI ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void vand_notLNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// m1
  st->print_raw("vand_notL ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void vand_notL_1Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src2
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// m1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src1
  st->print_raw("vand_notL ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src1
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src2
}
#endif
#ifndef PRODUCT
void vand_notL_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// m1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  st->print_raw("vand_notL ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src2
}
#endif
#ifndef PRODUCT
void vand_notL_2Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// m1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src1
  st->print_raw("vand_notL ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void vand_notI_maskedNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// m1
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// pg
  st->print_raw("vand_notI_masked ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // pg
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void vand_notI_masked_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// m1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// pg
  st->print_raw("vand_notI_masked ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // pg
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src2
}
#endif
#ifndef PRODUCT
void vand_notL_maskedNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// m1
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// pg
  st->print_raw("vand_notL_masked ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // pg
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void vand_notL_masked_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// m1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// pg
  st->print_raw("vand_notL_masked ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // pg
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src2
}
#endif
#ifndef PRODUCT
void vabsBNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("vabsB ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
}
#endif
#ifndef PRODUCT
void vabsSNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("vabsS ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
}
#endif
#ifndef PRODUCT
void vabsINode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("vabsI ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
}
#endif
#ifndef PRODUCT
void vabsLNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("vabsL ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
}
#endif
#ifndef PRODUCT
void vabsFNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("vabsF ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
}
#endif
#ifndef PRODUCT
void vabsDNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("vabsD ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
}
#endif
#ifndef PRODUCT
void vabsB_maskedNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// pg
  st->print_raw("vabsB_masked ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // pg
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src
}
#endif
#ifndef PRODUCT
void vabsS_maskedNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// pg
  st->print_raw("vabsS_masked ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // pg
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src
}
#endif
#ifndef PRODUCT
void vabsI_maskedNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// pg
  st->print_raw("vabsI_masked ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // pg
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src
}
#endif
#ifndef PRODUCT
void vabsL_maskedNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// pg
  st->print_raw("vabsL_masked ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // pg
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src
}
#endif
#ifndef PRODUCT
void vabsF_maskedNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// pg
  st->print_raw("vabsF_masked ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // pg
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src
}
#endif
#ifndef PRODUCT
void vabsD_maskedNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// pg
  st->print_raw("vabsD_masked ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // pg
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src
}
#endif
#ifndef PRODUCT
void vfabd_neonNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("vfabd_neon ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void vfabd_neon_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("vfabd_neon ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void vfabd_sveNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("vfabd_sve ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void vfabd_sve_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("vfabd_sve ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void vfabd_maskedNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// pg
  st->print_raw("vfabd_masked ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // pg
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void vfabd_masked_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// pg
  st->print_raw("vfabd_masked ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // pg
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void vnegINode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("vnegI ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
}
#endif
#ifndef PRODUCT
void vnegLNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("vnegL ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
}
#endif
#ifndef PRODUCT
void vnegFNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("vnegF ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
}
#endif
#ifndef PRODUCT
void vnegDNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("vnegD ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
}
#endif
#ifndef PRODUCT
void vnegI_maskedNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// pg
  st->print_raw("vnegI_masked ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // pg
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src
}
#endif
#ifndef PRODUCT
void vnegL_maskedNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// pg
  st->print_raw("vnegL_masked ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // pg
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src
}
#endif
#ifndef PRODUCT
void vnegF_maskedNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// pg
  st->print_raw("vnegF_masked ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // pg
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src
}
#endif
#ifndef PRODUCT
void vnegD_maskedNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// pg
  st->print_raw("vnegD_masked ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // pg
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src
}
#endif
#ifndef PRODUCT
void vsqrtFNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("vsqrtF ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
}
#endif
#ifndef PRODUCT
void vsqrtDNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("vsqrtD ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
}
#endif
#ifndef PRODUCT
void vsqrtF_maskedNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// pg
  st->print_raw("vsqrtF_masked ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // pg
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src
}
#endif
#ifndef PRODUCT
void vsqrtD_maskedNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// pg
  st->print_raw("vsqrtD_masked ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // pg
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src
}
#endif
#ifndef PRODUCT
void vminL_neonNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// dst
  st->print_raw("vminL_neon ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw("\t# 2L");
}
#endif
#ifndef PRODUCT
void vminL_sveNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("vminL_sve ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void vmin_neonNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("vmin_neon ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw("\t# B/S/I/F/D");
}
#endif
#ifndef PRODUCT
void vmin_sveNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("vmin_sve ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw("\t# B/S/I/F/D");
}
#endif
#ifndef PRODUCT
void vmin_maskedNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// pg
  st->print_raw("vmin_masked ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // pg
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void vmaxL_neonNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// dst
  st->print_raw("vmaxL_neon ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw("\t# 2L");
}
#endif
#ifndef PRODUCT
void vmaxL_sveNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("vmaxL_sve ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void vmax_neonNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("vmax_neon ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw("\t# B/S/I/F/D");
}
#endif
#ifndef PRODUCT
void vmax_sveNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("vmax_sve ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw("\t# B/S/I/F/D");
}
#endif
#ifndef PRODUCT
void vmax_maskedNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// pg
  st->print_raw("vmax_masked ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // pg
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void vmlaNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src3
  st->print_raw("vmla ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src3
}
#endif
#ifndef PRODUCT
void vmla_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src2
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src3
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// dst_src1
  st->print_raw("vmla ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // dst_src1
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src2
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src3
}
#endif
#ifndef PRODUCT
void vmla_1Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src3
  st->print_raw("vmla ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src3
}
#endif
#ifndef PRODUCT
void vmla_2Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src2
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src3
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// dst_src1
  st->print_raw("vmla ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // dst_src1
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src2
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src3
}
#endif
#ifndef PRODUCT
void vmla_3Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src3
  st->print_raw("vmla ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src3
}
#endif
#ifndef PRODUCT
void vmla_4Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src2
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src3
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// dst_src1
  st->print_raw("vmla ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // dst_src1
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src2
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src3
}
#endif
#ifndef PRODUCT
void vmlaLNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src3
  st->print_raw("vmlaL ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src3
}
#endif
#ifndef PRODUCT
void vmlaL_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src2
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src3
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// dst_src1
  st->print_raw("vmlaL ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // dst_src1
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src2
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src3
}
#endif
#ifndef PRODUCT
void vmla_maskedNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src3
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// pg
  st->print_raw("vmla_masked ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // pg
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src3
}
#endif
#ifndef PRODUCT
void vmla_masked_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src3
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// pg
  st->print_raw("vmla_masked ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // pg
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src3
}
#endif
#ifndef PRODUCT
void vmla_masked_1Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src3
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// pg
  st->print_raw("vmla_masked ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // pg
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src3
}
#endif
#ifndef PRODUCT
void vmla_masked_2Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src3
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// pg
  st->print_raw("vmla_masked ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // pg
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src3
}
#endif
#ifndef PRODUCT
void vfmlaNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src3
  st->print_raw("vfmla ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src3
}
#endif
#ifndef PRODUCT
void vfmla_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src3
  st->print_raw("vfmla ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src3
}
#endif
#ifndef PRODUCT
void vfmad_maskedNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src3
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// pg
  st->print_raw("vfmad_masked ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // pg
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src3
}
#endif
#ifndef PRODUCT
void vfmad_masked_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src3
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// pg
  st->print_raw("vfmad_masked ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // pg
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src3
}
#endif
#ifndef PRODUCT
void vmlsNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src3
  st->print_raw("vmls ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src3
}
#endif
#ifndef PRODUCT
void vmls_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src3
  st->print_raw("vmls ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src3
}
#endif
#ifndef PRODUCT
void vmls_1Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src3
  st->print_raw("vmls ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src3
}
#endif
#ifndef PRODUCT
void vmlsLNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src3
  st->print_raw("vmlsL ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src3
}
#endif
#ifndef PRODUCT
void vmls_maskedNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src3
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// pg
  st->print_raw("vmls_masked ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // pg
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src3
}
#endif
#ifndef PRODUCT
void vmls_masked_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src3
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// pg
  st->print_raw("vmls_masked ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // pg
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src3
}
#endif
#ifndef PRODUCT
void vmls_masked_1Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src3
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// pg
  st->print_raw("vmls_masked ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // pg
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src3
}
#endif
#ifndef PRODUCT
void vmls_masked_2Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src3
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// pg
  st->print_raw("vmls_masked ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // pg
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src3
}
#endif
#ifndef PRODUCT
void vfmlsNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src3
  st->print_raw("vfmls ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src3
}
#endif
#ifndef PRODUCT
void vfmls_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src3
  st->print_raw("vfmls ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src3
}
#endif
#ifndef PRODUCT
void vfmsb_maskedNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src3
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// pg
  st->print_raw("vfmsb_masked ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // pg
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src3
}
#endif
#ifndef PRODUCT
void vfmsb_masked_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src3
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// pg
  st->print_raw("vfmsb_masked ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // pg
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src3
}
#endif
#ifndef PRODUCT
void vfnmlaNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src3
  st->print_raw("vfnmla ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src3
}
#endif
#ifndef PRODUCT
void vfnmla_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src3
  st->print_raw("vfnmla ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src3
}
#endif
#ifndef PRODUCT
void vfnmad_maskedNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src3
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// pg
  st->print_raw("vfnmad_masked ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // pg
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src3
}
#endif
#ifndef PRODUCT
void vfnmad_masked_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src3
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// pg
  st->print_raw("vfnmad_masked ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // pg
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src3
}
#endif
#ifndef PRODUCT
void vfnmlsNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src3
  st->print_raw("vfnmls ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src3
}
#endif
#ifndef PRODUCT
void vfnmls_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src3
  st->print_raw("vfnmls ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src3
}
#endif
#ifndef PRODUCT
void vfnmsb_maskedNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src3
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// pg
  st->print_raw("vfnmsb_masked ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // pg
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src3
}
#endif
#ifndef PRODUCT
void vfnmsb_masked_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src3
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// pg
  st->print_raw("vfnmsb_masked ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // pg
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src3
}
#endif
#ifndef PRODUCT
void vmuladdS2INode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// dst
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// tmp
  st->print_raw("vmuladdS2I ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw("\t# KILL ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // tmp
}
#endif
#ifndef PRODUCT
void vshiftcntLNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// cnt
  st->print_raw("vshiftcntL ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // cnt
}
#endif
#ifndef PRODUCT
void vshiftcntRNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// cnt
  st->print_raw("vshiftcntR ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // cnt
}
#endif
#ifndef PRODUCT
void vlsl_neonNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// shift
  st->print_raw("vlsl_neon ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // shift
}
#endif
#ifndef PRODUCT
void vlsl_neon_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// shift
  st->print_raw("vlsl_neon ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // shift
}
#endif
#ifndef PRODUCT
void vlsl_neon_1Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// shift
  st->print_raw("vlsl_neon ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // shift
}
#endif
#ifndef PRODUCT
void vlsl_neon_2Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// shift
  st->print_raw("vlsl_neon ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // shift
}
#endif
#ifndef PRODUCT
void vlsl_sveNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// shift
  st->print_raw("vlsl_sve ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // shift
}
#endif
#ifndef PRODUCT
void vlsl_sve_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// shift
  st->print_raw("vlsl_sve ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // shift
}
#endif
#ifndef PRODUCT
void vlsl_sve_1Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// shift
  st->print_raw("vlsl_sve ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // shift
}
#endif
#ifndef PRODUCT
void vlsl_sve_2Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// shift
  st->print_raw("vlsl_sve ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // shift
}
#endif
#ifndef PRODUCT
void vasr_neonNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// shift
  st->print_raw("vasr_neon ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // shift
  st->print_raw("\t# not variable shift");
}
#endif
#ifndef PRODUCT
void vasr_neon_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// shift
  st->print_raw("vasr_neon ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // shift
  st->print_raw("\t# not variable shift");
}
#endif
#ifndef PRODUCT
void vasr_neon_1Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// shift
  st->print_raw("vasr_neon ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // shift
  st->print_raw("\t# not variable shift");
}
#endif
#ifndef PRODUCT
void vasr_neon_2Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// shift
  st->print_raw("vasr_neon ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // shift
  st->print_raw("\t# not variable shift");
}
#endif
#ifndef PRODUCT
void vasr_neon_varNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// shift
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// dst
  st->print_raw("vasr_neon_var ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // shift
  st->print_raw("\t# variable shift");
}
#endif
#ifndef PRODUCT
void vasr_neon_var_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// shift
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// dst
  st->print_raw("vasr_neon_var ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // shift
  st->print_raw("\t# variable shift");
}
#endif
#ifndef PRODUCT
void vasr_neon_var_1Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// shift
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// dst
  st->print_raw("vasr_neon_var ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // shift
  st->print_raw("\t# variable shift");
}
#endif
#ifndef PRODUCT
void vasr_neon_var_2Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// shift
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// dst
  st->print_raw("vasr_neon_var ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // shift
  st->print_raw("\t# variable shift");
}
#endif
#ifndef PRODUCT
void vasr_sveNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// shift
  st->print_raw("vasr_sve ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // shift
}
#endif
#ifndef PRODUCT
void vasr_sve_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// shift
  st->print_raw("vasr_sve ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // shift
}
#endif
#ifndef PRODUCT
void vasr_sve_1Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// shift
  st->print_raw("vasr_sve ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // shift
}
#endif
#ifndef PRODUCT
void vasr_sve_2Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// shift
  st->print_raw("vasr_sve ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // shift
}
#endif
#ifndef PRODUCT
void vlsr_neonNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// shift
  st->print_raw("vlsr_neon ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // shift
  st->print_raw("\t# not variable shift");
}
#endif
#ifndef PRODUCT
void vlsr_neon_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// shift
  st->print_raw("vlsr_neon ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // shift
  st->print_raw("\t# not variable shift");
}
#endif
#ifndef PRODUCT
void vlsr_neon_1Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// shift
  st->print_raw("vlsr_neon ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // shift
  st->print_raw("\t# not variable shift");
}
#endif
#ifndef PRODUCT
void vlsr_neon_2Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// shift
  st->print_raw("vlsr_neon ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // shift
  st->print_raw("\t# not variable shift");
}
#endif
#ifndef PRODUCT
void vlsr_neon_varNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// shift
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// dst
  st->print_raw("vlsr_neon_var ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // shift
  st->print_raw("\t# variable shift");
}
#endif
#ifndef PRODUCT
void vlsr_neon_var_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// shift
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// dst
  st->print_raw("vlsr_neon_var ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // shift
  st->print_raw("\t# variable shift");
}
#endif
#ifndef PRODUCT
void vlsr_neon_var_1Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// shift
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// dst
  st->print_raw("vlsr_neon_var ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // shift
  st->print_raw("\t# variable shift");
}
#endif
#ifndef PRODUCT
void vlsr_neon_var_2Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// shift
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// dst
  st->print_raw("vlsr_neon_var ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // shift
  st->print_raw("\t# variable shift");
}
#endif
#ifndef PRODUCT
void vlsr_sveNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// shift
  st->print_raw("vlsr_sve ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // shift
}
#endif
#ifndef PRODUCT
void vlsr_sve_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// shift
  st->print_raw("vlsr_sve ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // shift
}
#endif
#ifndef PRODUCT
void vlsr_sve_1Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// shift
  st->print_raw("vlsr_sve ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // shift
}
#endif
#ifndef PRODUCT
void vlsr_sve_2Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// shift
  st->print_raw("vlsr_sve ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // shift
}
#endif
#ifndef PRODUCT
void vlsl_immNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// shift
  st->print_raw("vlsl_imm ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // shift
}
#endif
#ifndef PRODUCT
void vlsl_imm_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// shift
  st->print_raw("vlsl_imm ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // shift
}
#endif
#ifndef PRODUCT
void vlsl_imm_1Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// shift
  st->print_raw("vlsl_imm ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // shift
}
#endif
#ifndef PRODUCT
void vlsl_imm_2Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// shift
  st->print_raw("vlsl_imm ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // shift
}
#endif
#ifndef PRODUCT
void vasr_immNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// shift
  st->print_raw("vasr_imm ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // shift
}
#endif
#ifndef PRODUCT
void vasr_imm_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// shift
  st->print_raw("vasr_imm ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // shift
}
#endif
#ifndef PRODUCT
void vasr_imm_1Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// shift
  st->print_raw("vasr_imm ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // shift
}
#endif
#ifndef PRODUCT
void vasr_imm_2Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// shift
  st->print_raw("vasr_imm ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // shift
}
#endif
#ifndef PRODUCT
void vlsr_immNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// shift
  st->print_raw("vlsr_imm ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // shift
}
#endif
#ifndef PRODUCT
void vlsr_imm_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// shift
  st->print_raw("vlsr_imm ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // shift
}
#endif
#ifndef PRODUCT
void vlsr_imm_1Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// shift
  st->print_raw("vlsr_imm ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // shift
}
#endif
#ifndef PRODUCT
void vlsr_imm_2Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// shift
  st->print_raw("vlsr_imm ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // shift
}
#endif
#ifndef PRODUCT
void vasra_immNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// shift
  st->print_raw("vasra_imm ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // shift
}
#endif
#ifndef PRODUCT
void vasra_imm_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// shift
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// dst
  st->print_raw("vasra_imm ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // shift
}
#endif
#ifndef PRODUCT
void vasra_imm_1Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// shift
  st->print_raw("vasra_imm ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // shift
}
#endif
#ifndef PRODUCT
void vasra_imm_2Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// shift
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// dst
  st->print_raw("vasra_imm ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // shift
}
#endif
#ifndef PRODUCT
void vasra_imm_3Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// shift
  st->print_raw("vasra_imm ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // shift
}
#endif
#ifndef PRODUCT
void vasra_imm_4Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// shift
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// dst
  st->print_raw("vasra_imm ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // shift
}
#endif
#ifndef PRODUCT
void vasra_imm_5Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// shift
  st->print_raw("vasra_imm ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // shift
}
#endif
#ifndef PRODUCT
void vasra_imm_6Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// shift
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// dst
  st->print_raw("vasra_imm ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // shift
}
#endif
#ifndef PRODUCT
void vlsra_immNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// shift
  st->print_raw("vlsra_imm ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // shift
}
#endif
#ifndef PRODUCT
void vlsra_imm_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// shift
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// dst
  st->print_raw("vlsra_imm ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // shift
}
#endif
#ifndef PRODUCT
void vlsra_imm_1Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// shift
  st->print_raw("vlsra_imm ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // shift
}
#endif
#ifndef PRODUCT
void vlsra_imm_2Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// shift
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// dst
  st->print_raw("vlsra_imm ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // shift
}
#endif
#ifndef PRODUCT
void vlsra_imm_3Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// shift
  st->print_raw("vlsra_imm ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // shift
}
#endif
#ifndef PRODUCT
void vlsra_imm_4Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// shift
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// dst
  st->print_raw("vlsra_imm ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // shift
}
#endif
#ifndef PRODUCT
void vlsra_imm_5Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// shift
  st->print_raw("vlsra_imm ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // shift
}
#endif
#ifndef PRODUCT
void vlsra_imm_6Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// shift
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// dst
  st->print_raw("vlsra_imm ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // shift
}
#endif
#ifndef PRODUCT
void vlsl_maskedNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// pg
  st->print_raw("vlsl_masked ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // pg
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void vlsl_masked_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// pg
  st->print_raw("vlsl_masked ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // pg
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void vlsl_masked_1Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// pg
  st->print_raw("vlsl_masked ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // pg
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void vlsl_masked_2Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// pg
  st->print_raw("vlsl_masked ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // pg
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void vasr_maskedNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// pg
  st->print_raw("vasr_masked ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // pg
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void vasr_masked_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// pg
  st->print_raw("vasr_masked ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // pg
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void vasr_masked_1Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// pg
  st->print_raw("vasr_masked ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // pg
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void vasr_masked_2Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// pg
  st->print_raw("vasr_masked ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // pg
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void vlsr_maskedNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// pg
  st->print_raw("vlsr_masked ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // pg
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void vlsr_masked_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// pg
  st->print_raw("vlsr_masked ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // pg
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void vlsr_masked_1Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// pg
  st->print_raw("vlsr_masked ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // pg
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void vlsr_masked_2Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// pg
  st->print_raw("vlsr_masked ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // pg
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void vlsl_imm_maskedNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// shift
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// pg
  st->print_raw("vlsl_imm_masked ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // pg
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // shift
}
#endif
#ifndef PRODUCT
void vlsl_imm_masked_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// shift
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// pg
  st->print_raw("vlsl_imm_masked ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // pg
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // shift
}
#endif
#ifndef PRODUCT
void vlsl_imm_masked_1Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// shift
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// pg
  st->print_raw("vlsl_imm_masked ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // pg
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // shift
}
#endif
#ifndef PRODUCT
void vlsl_imm_masked_2Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// shift
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// pg
  st->print_raw("vlsl_imm_masked ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // pg
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // shift
}
#endif
#ifndef PRODUCT
void vasr_imm_maskedNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// shift
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// pg
  st->print_raw("vasr_imm_masked ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // pg
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // shift
}
#endif
#ifndef PRODUCT
void vasr_imm_masked_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// shift
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// pg
  st->print_raw("vasr_imm_masked ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // pg
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // shift
}
#endif
#ifndef PRODUCT
void vasr_imm_masked_1Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// shift
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// pg
  st->print_raw("vasr_imm_masked ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // pg
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // shift
}
#endif
#ifndef PRODUCT
void vasr_imm_masked_2Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// shift
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// pg
  st->print_raw("vasr_imm_masked ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // pg
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // shift
}
#endif
#ifndef PRODUCT
void vlsr_imm_maskedNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// shift
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// pg
  st->print_raw("vlsr_imm_masked ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // pg
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // shift
}
#endif
#ifndef PRODUCT
void vlsr_imm_masked_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// shift
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// pg
  st->print_raw("vlsr_imm_masked ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // pg
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // shift
}
#endif
#ifndef PRODUCT
void vlsr_imm_masked_1Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// shift
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// pg
  st->print_raw("vlsr_imm_masked ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // pg
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // shift
}
#endif
#ifndef PRODUCT
void vlsr_imm_masked_2Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// shift
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// pg
  st->print_raw("vlsr_imm_masked ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // pg
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // shift
}
#endif
#ifndef PRODUCT
void reduce_addI_neonNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// isrc
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// vsrc
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// dst
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// tmp
  st->print_raw("reduce_addI_neon ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // isrc
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // vsrc
  st->print_raw("\t# KILL ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // tmp
}
#endif
#ifndef PRODUCT
void reduce_addI_sveNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// isrc
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// vsrc
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// dst
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// tmp
  st->print_raw("reduce_addI_sve ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // isrc
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // vsrc
  st->print_raw("\t# KILL ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // tmp
}
#endif
#ifndef PRODUCT
void reduce_addL_neonNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// isrc
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// vsrc
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// dst
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// tmp
  st->print_raw("reduce_addL_neon ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // isrc
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // vsrc
  st->print_raw("\t# KILL ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // tmp
}
#endif
#ifndef PRODUCT
void reduce_addL_sveNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// isrc
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// vsrc
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// dst
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// tmp
  st->print_raw("reduce_addL_sve ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // isrc
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // vsrc
  st->print_raw("\t# KILL ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // tmp
}
#endif
#ifndef PRODUCT
void reduce_add2F_neonNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// fsrc
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// vsrc
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// dst
  st->print_raw("reduce_add2F_neon ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // fsrc
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // vsrc
}
#endif
#ifndef PRODUCT
void reduce_add4F_neonNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// fsrc
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// vsrc
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// dst
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// tmp
  st->print_raw("reduce_add4F_neon ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // fsrc
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // vsrc
  st->print_raw("\t# KILL ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // tmp
}
#endif
#ifndef PRODUCT
void reduce_addF_sveNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("reduce_addF_sve ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void reduce_addD_neonNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dsrc
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// vsrc
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// dst
  st->print_raw("reduce_addD_neon ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dsrc
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // vsrc
  st->print_raw("\t# 2D");
}
#endif
#ifndef PRODUCT
void reduce_addD_sveNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("reduce_addD_sve ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void reduce_addI_maskedNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// isrc
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// vsrc
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// pg
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// dst
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// tmp
  st->print_raw("reduce_addI_masked ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // isrc
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // pg
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // vsrc
  st->print_raw("\t# KILL ");
  opnd_array(5)->ext_format(ra, this,idx5, st); // tmp
}
#endif
#ifndef PRODUCT
void reduce_addL_maskedNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// isrc
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// vsrc
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// pg
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// dst
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// tmp
  st->print_raw("reduce_addL_masked ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // isrc
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // pg
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // vsrc
  st->print_raw("\t# KILL ");
  opnd_array(5)->ext_format(ra, this,idx5, st); // tmp
}
#endif
#ifndef PRODUCT
void reduce_addF_maskedNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// pg
  st->print_raw("reduce_addF_masked ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // pg
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void reduce_addD_maskedNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// pg
  st->print_raw("reduce_addD_masked ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // pg
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void reduce_mulINode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// isrc
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// vsrc
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// dst
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// tmp1
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// tmp2
  st->print_raw("reduce_mulI ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // isrc
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // vsrc
  st->print_raw("\t# vector (64/128 bits). KILL ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // tmp1
  st->print_raw(", ");
  opnd_array(5)->ext_format(ra, this,idx5, st); // tmp2
}
#endif
#ifndef PRODUCT
void reduce_mulLNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// isrc
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// vsrc
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// dst
  st->print_raw("reduce_mulL ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // isrc
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // vsrc
  st->print_raw("\t# 2L");
}
#endif
#ifndef PRODUCT
void reduce_mulFNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// fsrc
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// vsrc
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// dst
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// tmp
  st->print_raw("reduce_mulF ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // fsrc
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // vsrc
  st->print_raw("\t# 2F/4F. KILL ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // tmp
}
#endif
#ifndef PRODUCT
void reduce_mulDNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dsrc
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// vsrc
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// dst
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// tmp
  st->print_raw("reduce_mulD ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dsrc
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // vsrc
  st->print_raw("\t# 2D. KILL ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // tmp
}
#endif
#ifndef PRODUCT
void reduce_andI_neonNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// isrc
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// vsrc
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// dst
  st->print_raw("reduce_andI_neon ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // isrc
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // vsrc
}
#endif
#ifndef PRODUCT
void reduce_andI_sveNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// isrc
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// vsrc
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// dst
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// tmp
  st->print_raw("reduce_andI_sve ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // isrc
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // vsrc
  st->print_raw("\t# KILL ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // tmp
}
#endif
#ifndef PRODUCT
void reduce_andL_neonNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// isrc
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// vsrc
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// dst
  st->print_raw("reduce_andL_neon ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // isrc
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // vsrc
}
#endif
#ifndef PRODUCT
void reduce_andL_sveNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// isrc
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// vsrc
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// dst
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// tmp
  st->print_raw("reduce_andL_sve ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // isrc
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // vsrc
  st->print_raw("\t# KILL ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // tmp
}
#endif
#ifndef PRODUCT
void reduce_andI_maskedNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// isrc
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// vsrc
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// pg
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// dst
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// tmp
  st->print_raw("reduce_andI_masked ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // isrc
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // pg
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // vsrc
  st->print_raw("\t# KILL ");
  opnd_array(5)->ext_format(ra, this,idx5, st); // tmp
}
#endif
#ifndef PRODUCT
void reduce_andL_maskedNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// isrc
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// vsrc
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// pg
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// dst
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// tmp
  st->print_raw("reduce_andL_masked ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // isrc
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // pg
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // vsrc
  st->print_raw("\t# KILL ");
  opnd_array(5)->ext_format(ra, this,idx5, st); // tmp
}
#endif
#ifndef PRODUCT
void reduce_orI_neonNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// isrc
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// vsrc
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// dst
  st->print_raw("reduce_orI_neon ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // isrc
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // vsrc
}
#endif
#ifndef PRODUCT
void reduce_orI_sveNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// isrc
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// vsrc
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// dst
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// tmp
  st->print_raw("reduce_orI_sve ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // isrc
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // vsrc
  st->print_raw("\t# KILL ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // tmp
}
#endif
#ifndef PRODUCT
void reduce_orL_neonNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// isrc
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// vsrc
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// dst
  st->print_raw("reduce_orL_neon ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // isrc
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // vsrc
}
#endif
#ifndef PRODUCT
void reduce_orL_sveNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// isrc
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// vsrc
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// dst
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// tmp
  st->print_raw("reduce_orL_sve ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // isrc
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // vsrc
  st->print_raw("\t# KILL ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // tmp
}
#endif
#ifndef PRODUCT
void reduce_orI_maskedNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// isrc
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// vsrc
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// pg
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// dst
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// tmp
  st->print_raw("reduce_orI_masked ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // isrc
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // pg
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // vsrc
  st->print_raw("\t# KILL ");
  opnd_array(5)->ext_format(ra, this,idx5, st); // tmp
}
#endif
#ifndef PRODUCT
void reduce_orL_maskedNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// isrc
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// vsrc
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// pg
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// dst
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// tmp
  st->print_raw("reduce_orL_masked ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // isrc
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // pg
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // vsrc
  st->print_raw("\t# KILL ");
  opnd_array(5)->ext_format(ra, this,idx5, st); // tmp
}
#endif
#ifndef PRODUCT
void reduce_xorI_neonNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// isrc
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// vsrc
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// dst
  st->print_raw("reduce_xorI_neon ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // isrc
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // vsrc
}
#endif
#ifndef PRODUCT
void reduce_xorI_sveNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// isrc
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// vsrc
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// dst
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// tmp
  st->print_raw("reduce_xorI_sve ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // isrc
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // vsrc
  st->print_raw("\t# KILL ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // tmp
}
#endif
#ifndef PRODUCT
void reduce_xorL_neonNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// isrc
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// vsrc
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// dst
  st->print_raw("reduce_xorL_neon ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // isrc
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // vsrc
}
#endif
#ifndef PRODUCT
void reduce_xorL_sveNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// isrc
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// vsrc
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// dst
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// tmp
  st->print_raw("reduce_xorL_sve ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // isrc
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // vsrc
  st->print_raw("\t# KILL ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // tmp
}
#endif
#ifndef PRODUCT
void reduce_xorI_maskedNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// isrc
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// vsrc
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// pg
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// dst
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// tmp
  st->print_raw("reduce_xorI_masked ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // isrc
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // pg
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // vsrc
  st->print_raw("\t# KILL ");
  opnd_array(5)->ext_format(ra, this,idx5, st); // tmp
}
#endif
#ifndef PRODUCT
void reduce_xorL_maskedNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// isrc
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// vsrc
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// pg
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// dst
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// tmp
  st->print_raw("reduce_xorL_masked ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // isrc
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // pg
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // vsrc
  st->print_raw("\t# KILL ");
  opnd_array(5)->ext_format(ra, this,idx5, st); // tmp
}
#endif
#ifndef PRODUCT
void reduce_maxI_neonNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// isrc
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// vsrc
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// dst
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// tmp
  st->print_raw("reduce_maxI_neon ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // isrc
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // vsrc
  st->print_raw("\t# KILL ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // tmp
  st->print_raw(", cr");
}
#endif
#ifndef PRODUCT
void reduce_maxI_sveNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// isrc
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// vsrc
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// dst
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// tmp
  st->print_raw("reduce_maxI_sve ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // isrc
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // vsrc
  st->print_raw("\t# KILL ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // tmp
  st->print_raw(", cr");
}
#endif
#ifndef PRODUCT
void reduce_maxL_neonNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// isrc
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// vsrc
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// dst
  st->print_raw("reduce_maxL_neon ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // isrc
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // vsrc
  st->print_raw("\t# 2L. KILL cr");
}
#endif
#ifndef PRODUCT
void reduce_maxL_sveNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// isrc
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// vsrc
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// dst
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// tmp
  st->print_raw("reduce_maxL_sve ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // isrc
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // vsrc
  st->print_raw("\t# KILL ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // tmp
  st->print_raw(", cr");
}
#endif
#ifndef PRODUCT
void reduce_maxFNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// fsrc
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// vsrc
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// dst
  st->print_raw("reduce_maxF ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // fsrc
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // vsrc
}
#endif
#ifndef PRODUCT
void reduce_maxDNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dsrc
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// vsrc
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// dst
  st->print_raw("reduce_maxD ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dsrc
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // vsrc
}
#endif
#ifndef PRODUCT
void reduce_maxI_maskedNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// isrc
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// vsrc
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// pg
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// dst
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// tmp
  st->print_raw("reduce_maxI_masked ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // isrc
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // pg
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // vsrc
  st->print_raw("\t# KILL ");
  opnd_array(5)->ext_format(ra, this,idx5, st); // tmp
  st->print_raw(", cr");
}
#endif
#ifndef PRODUCT
void reduce_maxL_maskedNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// isrc
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// vsrc
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// pg
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// dst
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// tmp
  st->print_raw("reduce_maxL_masked ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // isrc
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // pg
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // vsrc
  st->print_raw("\t# KILL ");
  opnd_array(5)->ext_format(ra, this,idx5, st); // tmp
  st->print_raw(", cr");
}
#endif
#ifndef PRODUCT
void reduce_maxF_maskedNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// fsrc
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// vsrc
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// pg
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// dst
  st->print_raw("reduce_maxF_masked ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // fsrc
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // pg
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // vsrc
}
#endif
#ifndef PRODUCT
void reduce_maxD_maskedNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dsrc
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// vsrc
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// pg
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// dst
  st->print_raw("reduce_maxD_masked ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dsrc
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // pg
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // vsrc
}
#endif
#ifndef PRODUCT
void reduce_minI_neonNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// isrc
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// vsrc
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// dst
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// tmp
  st->print_raw("reduce_minI_neon ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // isrc
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // vsrc
  st->print_raw("\t# KILL ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // tmp
  st->print_raw(", cr");
}
#endif
#ifndef PRODUCT
void reduce_minI_sveNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// isrc
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// vsrc
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// dst
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// tmp
  st->print_raw("reduce_minI_sve ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // isrc
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // vsrc
  st->print_raw("\t# KILL ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // tmp
  st->print_raw(", cr");
}
#endif
#ifndef PRODUCT
void reduce_minL_neonNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// isrc
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// vsrc
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// dst
  st->print_raw("reduce_minL_neon ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // isrc
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // vsrc
  st->print_raw("\t# 2L. KILL cr");
}
#endif
#ifndef PRODUCT
void reduce_minL_sveNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// isrc
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// vsrc
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// dst
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// tmp
  st->print_raw("reduce_minL_sve ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // isrc
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // vsrc
  st->print_raw("\t# KILL ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // tmp
  st->print_raw(", cr");
}
#endif
#ifndef PRODUCT
void reduce_minFNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// fsrc
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// vsrc
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// dst
  st->print_raw("reduce_minF ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // fsrc
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // vsrc
}
#endif
#ifndef PRODUCT
void reduce_minDNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dsrc
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// vsrc
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// dst
  st->print_raw("reduce_minD ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dsrc
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // vsrc
}
#endif
#ifndef PRODUCT
void reduce_minI_maskedNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// isrc
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// vsrc
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// pg
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// dst
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// tmp
  st->print_raw("reduce_minI_masked ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // isrc
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // pg
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // vsrc
  st->print_raw("\t# KILL ");
  opnd_array(5)->ext_format(ra, this,idx5, st); // tmp
  st->print_raw(", cr");
}
#endif
#ifndef PRODUCT
void reduce_minL_maskedNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// isrc
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// vsrc
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// pg
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// dst
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// tmp
  st->print_raw("reduce_minL_masked ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // isrc
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // pg
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // vsrc
  st->print_raw("\t# KILL ");
  opnd_array(5)->ext_format(ra, this,idx5, st); // tmp
  st->print_raw(", cr");
}
#endif
#ifndef PRODUCT
void reduce_minF_maskedNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// fsrc
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// vsrc
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// pg
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// dst
  st->print_raw("reduce_minF_masked ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // fsrc
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // pg
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // vsrc
}
#endif
#ifndef PRODUCT
void reduce_minD_maskedNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dsrc
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// vsrc
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// pg
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// dst
  st->print_raw("reduce_minD_masked ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dsrc
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // pg
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // vsrc
}
#endif
#ifndef PRODUCT
void reinterpret_same_sizeNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src
  st->print_raw("reinterpret_same_size ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src
  st->print_raw("\t# do nothing");
}
#endif
#ifndef PRODUCT
void reinterpret_resize_le128bNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("reinterpret_resize_le128b ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\t# vector <= 128 bits.");
}
#endif
#ifndef PRODUCT
void reinterpret_resize_gt128bNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// ptmp
  st->print_raw("reinterpret_resize_gt128b ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\t# vector > 128 bits. KILL ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // ptmp
  st->print_raw(", cr");
}
#endif
#ifndef PRODUCT
void vzeroExtBtoXNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("vzeroExtBtoX ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
}
#endif
#ifndef PRODUCT
void vzeroExtStoXNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("vzeroExtStoX ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
}
#endif
#ifndef PRODUCT
void vzeroExtItoXNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("vzeroExtItoX ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
}
#endif
#ifndef PRODUCT
void vcvtBtoXNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("vcvtBtoX ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
}
#endif
#ifndef PRODUCT
void vcvtStoB_neonNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("vcvtStoB_neon ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
}
#endif
#ifndef PRODUCT
void vcvtStoB_sveNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// tmp
  st->print_raw("vcvtStoB_sve ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\t# KILL ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // tmp
}
#endif
#ifndef PRODUCT
void vcvtStoX_extendNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("vcvtStoX_extend ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
}
#endif
#ifndef PRODUCT
void vcvtItoX_narrow_neonNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst
  st->print_raw("vcvtItoX_narrow_neon ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
}
#endif
#ifndef PRODUCT
void vcvtItoX_narrow_sveNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// tmp
  st->print_raw("vcvtItoX_narrow_sve ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\t# KILL ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // tmp
}
#endif
#ifndef PRODUCT
void vcvtItoXNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("vcvtItoX ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
}
#endif
#ifndef PRODUCT
void vcvtLtoI_neonNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("vcvtLtoI_neon ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
}
#endif
#ifndef PRODUCT
void vcvtLtoI_sveNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// tmp
  st->print_raw("vcvtLtoI_sve ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\t# KILL ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // tmp
}
#endif
#ifndef PRODUCT
void vcvtLtoF_neonNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// tmp
  st->print_raw("vcvtLtoF_neon ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\t# 2L to 2F. KILL ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // tmp
}
#endif
#ifndef PRODUCT
void vcvtLtoF_sveNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// tmp
  st->print_raw("vcvtLtoF_sve ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\t# KILL ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // tmp
}
#endif
#ifndef PRODUCT
void vcvtLtoDNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("vcvtLtoD ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
}
#endif
#ifndef PRODUCT
void vcvtFtoX_narrow_neonNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst
  st->print_raw("vcvtFtoX_narrow_neon ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
}
#endif
#ifndef PRODUCT
void vcvtFtoX_narrow_sveNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// tmp
  st->print_raw("vcvtFtoX_narrow_sve ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\t# KILL ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // tmp
}
#endif
#ifndef PRODUCT
void vcvtFtoXNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("vcvtFtoX ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
}
#endif
#ifndef PRODUCT
void vcvtDtoI_neonNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst
  st->print_raw("vcvtDtoI_neon ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\t# 2D to 2I");
}
#endif
#ifndef PRODUCT
void vcvtDtoI_sveNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// tmp
  st->print_raw("vcvtDtoI_sve ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\t# KILL ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // tmp
}
#endif
#ifndef PRODUCT
void vcvtDtoLNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("vcvtDtoL ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
}
#endif
#ifndef PRODUCT
void vcvtDtoF_64bNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("vcvtDtoF_64b ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\t# 2D to 2F");
}
#endif
#ifndef PRODUCT
void vcvtDtoF_gt64bNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// tmp
  st->print_raw("vcvtDtoF_gt64b ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\t# vector > 64 bits. KILL ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // tmp
}
#endif
#ifndef PRODUCT
void vcvtHFtoFNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("vcvtHFtoF ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
}
#endif
#ifndef PRODUCT
void vcvtFtoHF_neonNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("vcvtFtoHF_neon ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\t# 4F to 4HF");
}
#endif
#ifndef PRODUCT
void vcvtFtoHF_sveNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// tmp
  st->print_raw("vcvtFtoHF_sve ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\t# KILL ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // tmp
}
#endif
#ifndef PRODUCT
void replicateINode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("replicateI ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
}
#endif
#ifndef PRODUCT
void replicateLNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("replicateL ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
}
#endif
#ifndef PRODUCT
void replicateFNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("replicateF ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
}
#endif
#ifndef PRODUCT
void replicateDNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("replicateD ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
}
#endif
#ifndef PRODUCT
void replicateI_imm_le128bNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// con
  st->print_raw("replicateI_imm_le128b ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // con
  st->print_raw("\t# vector <= 128 bits");
}
#endif
#ifndef PRODUCT
void replicateB_imm8_gt128bNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// con
  st->print_raw("replicateB_imm8_gt128b ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // con
  st->print_raw("\t# vector > 128 bits");
}
#endif
#ifndef PRODUCT
void replicateI_imm8_gt128bNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// con
  st->print_raw("replicateI_imm8_gt128b ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // con
  st->print_raw("\t# vector > 128 bits");
}
#endif
#ifndef PRODUCT
void replicateL_imm_128bNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// con
  st->print_raw("replicateL_imm_128b ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // con
  st->print_raw("\t# vector > 128 bits");
}
#endif
#ifndef PRODUCT
void replicateL_imm8_gt128bNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// con
  st->print_raw("replicateL_imm8_gt128b ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // con
  st->print_raw("\t# vector > 128 bits");
}
#endif
#ifndef PRODUCT
void insertI_le128bNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// val
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// idx
  st->print_raw("insertI_le128b ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // val
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // idx
  st->print_raw("\t# vector <= 128 bits");
}
#endif
#ifndef PRODUCT
void insertI_index_lt32Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// val
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// idx
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// tmp
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// pgtmp
  st->print_raw("insertI_index_lt32 ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // val
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // idx
  st->print_raw("\t# vector > 128 bits, index < 31. KILL ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // tmp
  st->print_raw(", ");
  opnd_array(5)->ext_format(ra, this,idx5, st); // pgtmp
  st->print_raw(", cr");
}
#endif
#ifndef PRODUCT
void insertI_index_ge32Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// val
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// idx
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// tmp1
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// tmp2
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// pgtmp
  st->print_raw("insertI_index_ge32 ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // val
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // idx
  st->print_raw("\t# index >= 32. KILL ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // tmp1
  st->print_raw(", ");
  opnd_array(5)->ext_format(ra, this,idx5, st); // tmp2
  st->print_raw(", ");
  opnd_array(6)->ext_format(ra, this,idx6, st); // pgtmp
  st->print_raw(", cr");
}
#endif
#ifndef PRODUCT
void insertL_128bNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// val
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// idx
  st->print_raw("insertL_128b ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // val
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // idx
  st->print_raw("\t# 2L");
}
#endif
#ifndef PRODUCT
void insertL_gt128bNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// val
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// idx
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// tmp
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// pgtmp
  st->print_raw("insertL_gt128b ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // val
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // idx
  st->print_raw("\t# vector > 128 bits. KILL ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // tmp
  st->print_raw(", ");
  opnd_array(5)->ext_format(ra, this,idx5, st); // pgtmp
  st->print_raw(", cr");
}
#endif
#ifndef PRODUCT
void insertF_le128bNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// val
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// idx
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// dst
  st->print_raw("insertF_le128b ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // val
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // idx
  st->print_raw("\t# vector <= 128 bits");
}
#endif
#ifndef PRODUCT
void insertF_index_lt32Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// val
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// idx
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// dst
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// pgtmp
  st->print_raw("insertF_index_lt32 ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // val
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // idx
  st->print_raw("\t# vector > 128 bits, index < 32. KILL ");
  opnd_array(5)->ext_format(ra, this,idx5, st); // pgtmp
  st->print_raw(", cr");
}
#endif
#ifndef PRODUCT
void insertF_index_ge32Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// val
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// idx
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// dst
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// tmp
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// pgtmp
  st->print_raw("insertF_index_ge32 ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // val
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // idx
  st->print_raw("\t# index >= 32. KILL ");
  opnd_array(5)->ext_format(ra, this,idx5, st); // tmp
  st->print_raw(", ");
  opnd_array(6)->ext_format(ra, this,idx6, st); // pgtmp
  st->print_raw(", cr");
}
#endif
#ifndef PRODUCT
void insertD_128bNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// val
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// idx
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// dst
  st->print_raw("insertD_128b ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // val
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // idx
  st->print_raw("\t# 2D");
}
#endif
#ifndef PRODUCT
void insertD_gt128bNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// val
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// idx
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// dst
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// pgtmp
  st->print_raw("insertD_gt128b ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // val
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // idx
  st->print_raw("\t# vector > 128 bits. KILL ");
  opnd_array(5)->ext_format(ra, this,idx5, st); // pgtmp
  st->print_raw(", cr");
}
#endif
#ifndef PRODUCT
void extractUB_iregNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// idx
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// tmp
  st->print_raw("extractUB_ireg ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // idx
  st->print_raw("\t# variable index. KILL ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // tmp
}
#endif
#ifndef PRODUCT
void extractUB_index_lt16Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// idx
  st->print_raw("extractUB_index_lt16 ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // idx
  st->print_raw("\t# index < 16");
}
#endif
#ifndef PRODUCT
void extractUB_index_ge16Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// idx
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// tmp
  st->print_raw("extractUB_index_ge16 ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // idx
  st->print_raw("\t# index >=16. KILL ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // tmp
}
#endif
#ifndef PRODUCT
void extractB_index_lt16Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// idx
  st->print_raw("extractB_index_lt16 ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // idx
  st->print_raw("\t# index < 16");
}
#endif
#ifndef PRODUCT
void extractB_index_ge16Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// idx
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// tmp
  st->print_raw("extractB_index_ge16 ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // idx
  st->print_raw("\t# index >=16. KILL ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // tmp
}
#endif
#ifndef PRODUCT
void extractS_index_lt8Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// idx
  st->print_raw("extractS_index_lt8 ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // idx
  st->print_raw("\t# index < 8");
}
#endif
#ifndef PRODUCT
void extractS_index_ge8Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// idx
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// tmp
  st->print_raw("extractS_index_ge8 ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // idx
  st->print_raw("\t# index >=8. KILL ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // tmp
}
#endif
#ifndef PRODUCT
void extractI_index_lt4Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// idx
  st->print_raw("extractI_index_lt4 ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // idx
  st->print_raw("\t# index < 4");
}
#endif
#ifndef PRODUCT
void extractI_index_ge4Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// idx
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// tmp
  st->print_raw("extractI_index_ge4 ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // idx
  st->print_raw("\t# index >=4. KILL ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // tmp
}
#endif
#ifndef PRODUCT
void extractL_index_lt2Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// idx
  st->print_raw("extractL_index_lt2 ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // idx
  st->print_raw("\t# index < 2");
}
#endif
#ifndef PRODUCT
void extractL_index_ge2Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// idx
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// tmp
  st->print_raw("extractL_index_ge2 ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // idx
  st->print_raw("\t# index >=2. KILL ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // tmp
}
#endif
#ifndef PRODUCT
void extractFNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// idx
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// dst
  st->print_raw("extractF ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // idx
}
#endif
#ifndef PRODUCT
void extractDNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// idx
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// dst
  st->print_raw("extractD ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // idx
}
#endif
#ifndef PRODUCT
void vloadmask_neonNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("vloadmask_neon ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
}
#endif
#ifndef PRODUCT
void vloadmaskB_sveNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("vloadmaskB_sve ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\t# KILL cr");
}
#endif
#ifndef PRODUCT
void vloadmask_extend_sveNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// tmp
  st->print_raw("vloadmask_extend_sve ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\t# KILL ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // tmp
  st->print_raw(", cr");
}
#endif
#ifndef PRODUCT
void vloadmaskB_maskedNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// pg
  st->print_raw("vloadmaskB_masked ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // pg
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\t# KILL cr");
}
#endif
#ifndef PRODUCT
void vloadmask_extend_maskedNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// pg
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// tmp
  st->print_raw("vloadmask_extend_masked ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // pg
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\t# KILL ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // tmp
  st->print_raw(", cr");
}
#endif
#ifndef PRODUCT
void vstoremaskB_neonNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// size
  st->print_raw("vstoremaskB_neon ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
}
#endif
#ifndef PRODUCT
void vstoremask_narrow_neonNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// size
  st->print_raw("vstoremask_narrow_neon ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
}
#endif
#ifndef PRODUCT
void vstoremaskB_sveNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// size
  st->print_raw("vstoremaskB_sve ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
}
#endif
#ifndef PRODUCT
void vstoremask_narrow_sveNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// size
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// dst
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// tmp
  st->print_raw("vstoremask_narrow_sve ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\t# KILL ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // tmp
}
#endif
#ifndef PRODUCT
void vloadmask_loadVNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// tmp
  st->print_raw("vloadmask_loadV ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("\t# KILL ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // tmp
  st->print_raw(", cr");
}
#endif
#ifndef PRODUCT
void vloadmask_loadV_maskedNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// pg
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// tmp
  st->print_raw("vloadmask_loadV_masked ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // pg
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("\t# KILL ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // tmp
  st->print_raw(", cr");
}
#endif
#ifndef PRODUCT
void vloadmask_loadVMaskedNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// pg
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// tmp
  st->print_raw("vloadmask_loadVMasked ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("\t# KILL ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // tmp
  st->print_raw(", cr");
}
#endif
#ifndef PRODUCT
void vloadmask_loadVMasked_maskedNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// pg1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// pg2
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// tmp
  st->print_raw("vloadmask_loadVMasked_masked ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // pg2
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("\t# KILL ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // tmp
  st->print_raw(", cr");
}
#endif
#ifndef PRODUCT
void storeV_vstoremaskNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// esize
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// tmp
  st->print_raw("storeV_vstoremask ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
  st->print_raw("\t# KILL ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // tmp
  if (ra->C->alias_type(adr_type())->field() != nullptr) {
    ciField* f = ra->C->alias_type(adr_type())->field();
    st->print(" ! Field: ");
    if (f->is_volatile())
      st->print("volatile ");
    f->holder()->name()->print_symbol_on(st);
    st->print(".");
    f->name()->print_symbol_on(st);
    if (f->is_constant())
      st->print(" (constant)");
  } else {
    if (ra->C->alias_type(adr_type())->is_volatile())
      st->print(" volatile!");
  }
}
#endif
#ifndef PRODUCT
void storeV_vstoremask_maskedNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// esize
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// tmp
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// pgtmp
  st->print_raw("storeV_vstoremask_masked ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
  st->print_raw("\t# KILL ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // tmp
  st->print_raw(", ");
  opnd_array(5)->ext_format(ra, this,idx5, st); // pgtmp
  st->print_raw(", cr");
  if (ra->C->alias_type(adr_type())->field() != nullptr) {
    ciField* f = ra->C->alias_type(adr_type())->field();
    st->print(" ! Field: ");
    if (f->is_volatile())
      st->print("volatile ");
    f->holder()->name()->print_symbol_on(st);
    st->print(".");
    f->name()->print_symbol_on(st);
    if (f->is_constant())
      st->print(" (constant)");
  } else {
    if (ra->C->alias_type(adr_type())->is_volatile())
      st->print(" volatile!");
  }
}
#endif
#ifndef PRODUCT
void storeVMasked_vstoremaskNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// esize
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// pg
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// tmp
  st->print_raw("storeVMasked_vstoremask ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
  st->print_raw("\t# KILL ");
  opnd_array(5)->ext_format(ra, this,idx5, st); // tmp
  if (ra->C->alias_type(adr_type())->field() != nullptr) {
    ciField* f = ra->C->alias_type(adr_type())->field();
    st->print(" ! Field: ");
    if (f->is_volatile())
      st->print("volatile ");
    f->holder()->name()->print_symbol_on(st);
    st->print(".");
    f->name()->print_symbol_on(st);
    if (f->is_constant())
      st->print(" (constant)");
  } else {
    if (ra->C->alias_type(adr_type())->is_volatile())
      st->print(" volatile!");
  }
}
#endif
#ifndef PRODUCT
void storeVMasked_vstoremask_maskedNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// esize
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// pg
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// tmp
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// pgtmp
  st->print_raw("storeVMasked_vstoremask_masked ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
  st->print_raw("\t# KILL ");
  opnd_array(5)->ext_format(ra, this,idx5, st); // tmp
  st->print_raw(", ");
  opnd_array(6)->ext_format(ra, this,idx6, st); // pgtmp
  st->print_raw(", cr");
  if (ra->C->alias_type(adr_type())->field() != nullptr) {
    ciField* f = ra->C->alias_type(adr_type())->field();
    st->print(" ! Field: ");
    if (f->is_volatile())
      st->print("volatile ");
    f->holder()->name()->print_symbol_on(st);
    st->print(".");
    f->name()->print_symbol_on(st);
    if (f->is_constant())
      st->print(" (constant)");
  } else {
    if (ra->C->alias_type(adr_type())->is_volatile())
      st->print(" volatile!");
  }
}
#endif
#ifndef PRODUCT
void vmask_andNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// pn
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// pm
  st->print_raw("vmask_and ");
  opnd_array(0)->int_format(ra, this, st); // pd
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // pn
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // pm
}
#endif
#ifndef PRODUCT
void vmask_orNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// pn
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// pm
  st->print_raw("vmask_or ");
  opnd_array(0)->int_format(ra, this, st); // pd
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // pn
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // pm
}
#endif
#ifndef PRODUCT
void vmask_xorNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// pn
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// pm
  st->print_raw("vmask_xor ");
  opnd_array(0)->int_format(ra, this, st); // pd
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // pn
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // pm
}
#endif
#ifndef PRODUCT
void vmask_and_notINode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// pn
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// pm
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// m1
  st->print_raw("vmask_and_notI ");
  opnd_array(0)->int_format(ra, this, st); // pd
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // pn
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // pm
}
#endif
#ifndef PRODUCT
void vmask_and_notLNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// pn
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// pm
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// m1
  st->print_raw("vmask_and_notL ");
  opnd_array(0)->int_format(ra, this, st); // pd
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // pn
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // pm
}
#endif
#ifndef PRODUCT
void vmaskcmp_neonNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// cond
  st->print_raw("vmaskcmp_neon ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // cond
}
#endif
#ifndef PRODUCT
void vmaskcmp_zeroI_neonNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// zero
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// cond
  st->print_raw("vmaskcmp_zeroI_neon ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(", #0, ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // cond
}
#endif
#ifndef PRODUCT
void vmaskcmp_zeroL_neonNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// zero
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// cond
  st->print_raw("vmaskcmp_zeroL_neon ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(", #0, ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // cond
}
#endif
#ifndef PRODUCT
void vmaskcmp_zeroF_neonNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// zero
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// cond
  st->print_raw("vmaskcmp_zeroF_neon ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(", #0, ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // cond
}
#endif
#ifndef PRODUCT
void vmaskcmp_zeroD_neonNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// zero
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// cond
  st->print_raw("vmaskcmp_zeroD_neon ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(", #0, ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // cond
}
#endif
#ifndef PRODUCT
void vmaskcmp_sveNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// cond
  st->print_raw("vmaskcmp_sve ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // cond
  st->print_raw("\t# KILL cr");
}
#endif
#ifndef PRODUCT
void vmaskcmp_immI_sveNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// imm
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// cond
  st->print_raw("vmaskcmp_immI_sve ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // imm
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // cond
  st->print_raw("\t# KILL cr");
}
#endif
#ifndef PRODUCT
void vmaskcmpU_immI_sveNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// imm
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// cond
  st->print_raw("vmaskcmpU_immI_sve ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // imm
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // cond
  st->print_raw("\t# KILL cr");
}
#endif
#ifndef PRODUCT
void vmaskcmp_immL_sveNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// imm
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// cond
  st->print_raw("vmaskcmp_immL_sve ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // imm
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // cond
  st->print_raw("\t# KILL cr");
}
#endif
#ifndef PRODUCT
void vmaskcmpU_immL_sveNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// imm
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// cond
  st->print_raw("vmaskcmpU_immL_sve ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // imm
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // cond
  st->print_raw("\t# KILL cr");
}
#endif
#ifndef PRODUCT
void vmaskcmp_maskedNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// cond
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// pg
  st->print_raw("vmaskcmp_masked ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // pg
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // cond
  st->print_raw("\t# KILL cr");
}
#endif
#ifndef PRODUCT
void vmaskcast_same_esize_neonNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src
  st->print_raw("vmaskcast_same_esize_neon ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src
  st->print_raw("\t# do nothing");
}
#endif
#ifndef PRODUCT
void vmaskcast_extend_neonNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("vmaskcast_extend_neon ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
}
#endif
#ifndef PRODUCT
void vmaskcast_narrow_neonNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("vmaskcast_narrow_neon ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
}
#endif
#ifndef PRODUCT
void vmaskcast_same_esize_sveNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src
  st->print_raw("vmaskcast_same_esize_sve ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src
  st->print_raw("\t# do nothing");
}
#endif
#ifndef PRODUCT
void vmaskcast_extend_sveNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("vmaskcast_extend_sve ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
}
#endif
#ifndef PRODUCT
void vmaskcast_narrow_sveNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// ptmp
  st->print_raw("vmaskcast_narrow_sve ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\t# KILL ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // ptmp
}
#endif
#ifndef PRODUCT
void vmask_reinterpret_same_esizeNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src
  st->print_raw("vmask_reinterpret_same_esize ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src
  st->print_raw("\t# do nothing");
}
#endif
#ifndef PRODUCT
void vmask_reinterpret_diff_esizeNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// tmp
  st->print_raw("vmask_reinterpret_diff_esize ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\t# KILL ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // tmp
  st->print_raw(", cr");
}
#endif
#ifndef PRODUCT
void vmask_truecount_neonNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// tmp
  st->print_raw("vmask_truecount_neon ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\t# KILL ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // tmp
}
#endif
#ifndef PRODUCT
void vmask_truecount_sveNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("vmask_truecount_sve ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
}
#endif
#ifndef PRODUCT
void vstoremask_truecount_neonNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// size
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// vtmp
  st->print_raw("vstoremask_truecount_neon ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\t# KILL ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // vtmp
}
#endif
#ifndef PRODUCT
void vmask_firsttrue_neonNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("vmask_firsttrue_neon ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
}
#endif
#ifndef PRODUCT
void vmask_firsttrue_sveNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// ptmp
  st->print_raw("vmask_firsttrue_sve ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\t# KILL ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // ptmp
}
#endif
#ifndef PRODUCT
void vmask_firsttrue_maskedNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// pg
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// ptmp
  st->print_raw("vmask_firsttrue_masked ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // pg
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\t# KILL ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // ptmp
}
#endif
#ifndef PRODUCT
void vmask_lasttrue_neonNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("vmask_lasttrue_neon ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
}
#endif
#ifndef PRODUCT
void vmask_lasttrue_sveNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// ptmp
  st->print_raw("vmask_lasttrue_sve ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\t# KILL ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // ptmp
}
#endif
#ifndef PRODUCT
void vmask_tolong_neonNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("vmask_tolong_neon ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
}
#endif
#ifndef PRODUCT
void vmask_tolong_sveNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// tmp1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// tmp2
  st->print_raw("vmask_tolong_sve ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\t# KILL ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // tmp1
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // tmp2
}
#endif
#ifndef PRODUCT
void vmask_fromlongNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// tmp1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// tmp2
  st->print_raw("vmask_fromlong ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\t# vector (sve2). KILL ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // tmp1
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // tmp2
}
#endif
#ifndef PRODUCT
void vmaskAll_immINode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("vmaskAll_immI ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\t# KILL cr");
}
#endif
#ifndef PRODUCT
void vmaskAllINode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// tmp
  st->print_raw("vmaskAllI ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\t# KILL ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // tmp
  st->print_raw(", cr");
}
#endif
#ifndef PRODUCT
void vmaskAllI_maskedNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// pg
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// tmp
  st->print_raw("vmaskAllI_masked ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // pg
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\t# KILL ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // tmp
  st->print_raw(", cr");
}
#endif
#ifndef PRODUCT
void vmaskAll_immLNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("vmaskAll_immL ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\t# KILL cr");
}
#endif
#ifndef PRODUCT
void vmaskAllLNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// tmp
  st->print_raw("vmaskAllL ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\t# KILL ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // tmp
  st->print_raw(", cr");
}
#endif
#ifndef PRODUCT
void vmaskAllL_maskedNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// pg
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// tmp
  st->print_raw("vmaskAllL_masked ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // pg
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\t# KILL ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // tmp
  st->print_raw(", cr");
}
#endif
#ifndef PRODUCT
void vmask_gen_INode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("vmask_gen_I ");
  opnd_array(0)->int_format(ra, this, st); // pd
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\t# KILL cr");
}
#endif
#ifndef PRODUCT
void vmask_gen_LNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("vmask_gen_L ");
  opnd_array(0)->int_format(ra, this, st); // pd
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\t# KILL cr");
}
#endif
#ifndef PRODUCT
void vmask_gen_immNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// con
  st->print_raw("vmask_gen_imm ");
  opnd_array(0)->int_format(ra, this, st); // pd
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // con
  st->print_raw("\t# KILL cr");
}
#endif
#ifndef PRODUCT
void vmask_gen_subNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("vmask_gen_sub ");
  opnd_array(0)->int_format(ra, this, st); // pd
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw("\t# KILL cr");
}
#endif
#ifndef PRODUCT
void vpopcountINode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("vpopcountI ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
}
#endif
#ifndef PRODUCT
void vpopcountLNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("vpopcountL ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
}
#endif
#ifndef PRODUCT
void vpopcountI_maskedNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// pg
  st->print_raw("vpopcountI_masked ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // pg
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src
}
#endif
#ifndef PRODUCT
void vpopcountL_maskedNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// pg
  st->print_raw("vpopcountL_masked ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // pg
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src
}
#endif
#ifndef PRODUCT
void vblend_neonNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// dst
  st->print_raw("vblend_neon ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void vblend_sveNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// pg
  st->print_raw("vblend_sve ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // pg
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void vround_le128bNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// tmp1
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// tmp2
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// tmp3
  st->print_raw("vround_le128b ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\t# vector <= 128 bits. KILL ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // tmp1
  st->print_raw(", ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // tmp2
  st->print_raw(", ");
  opnd_array(5)->ext_format(ra, this,idx5, st); // tmp3
  st->print_raw(", cr");
}
#endif
#ifndef PRODUCT
void vround_le128b_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// tmp1
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// tmp2
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// tmp3
  st->print_raw("vround_le128b ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\t# vector <= 128 bits. KILL ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // tmp1
  st->print_raw(", ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // tmp2
  st->print_raw(", ");
  opnd_array(5)->ext_format(ra, this,idx5, st); // tmp3
  st->print_raw(", cr");
}
#endif
#ifndef PRODUCT
void vround_gt128bNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// tmp1
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// tmp2
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// pgtmp
  st->print_raw("vround_gt128b ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\t# vector > 128 bits. KILL ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // tmp1
  st->print_raw(", ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // tmp2
  st->print_raw(", ");
  opnd_array(5)->ext_format(ra, this,idx5, st); // pgtmp
  st->print_raw(", cr");
}
#endif
#ifndef PRODUCT
void vround_gt128b_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// tmp1
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// tmp2
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// pgtmp
  st->print_raw("vround_gt128b ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\t# vector > 128 bits. KILL ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // tmp1
  st->print_raw(", ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // tmp2
  st->print_raw(", ");
  opnd_array(5)->ext_format(ra, this,idx5, st); // pgtmp
  st->print_raw(", cr");
}
#endif
#ifndef PRODUCT
void vroundDNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// rmode
  st->print_raw("vroundD ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // rmode
}
#endif
#ifndef PRODUCT
void vtest_anytrue_neonNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// tmp
  st->print_raw("vtest_anytrue_neon ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw("\t# KILL ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // tmp
}
#endif
#ifndef PRODUCT
void vtest_anytrue_sveNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("vtest_anytrue_sve ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
}
#endif
#ifndef PRODUCT
void vtest_alltrue_neonNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// tmp
  st->print_raw("vtest_alltrue_neon ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw("\t# KILL ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // tmp
}
#endif
#ifndef PRODUCT
void vtest_alltrue_sveNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// ptmp
  st->print_raw("vtest_alltrue_sve ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw("\t# KILL ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // ptmp
}
#endif
#ifndef PRODUCT
void loadshuffleNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("loadshuffle ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
}
#endif
#ifndef PRODUCT
void rearrange_HS_neonNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// shuffle
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// dst
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// tmp1
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// tmp2
  st->print_raw("rearrange_HS_neon ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // shuffle
  st->print_raw("\t# vector (4S/8S/4I/4F). KILL ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // tmp1
  st->print_raw(", ");
  opnd_array(5)->ext_format(ra, this,idx5, st); // tmp2
}
#endif
#ifndef PRODUCT
void rearrangeNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// shuffle
  st->print_raw("rearrange ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // shuffle
}
#endif
#ifndef PRODUCT
void gather_loadSNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// idx
  st->print_raw("gather_loadS ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // idx
  st->print_raw("\t# vector (sve)");
  if (ra->C->alias_type(adr_type())->field() != nullptr) {
    ciField* f = ra->C->alias_type(adr_type())->field();
    st->print(" ! Field: ");
    if (f->is_volatile())
      st->print("volatile ");
    f->holder()->name()->print_symbol_on(st);
    st->print(".");
    f->name()->print_symbol_on(st);
    if (f->is_constant())
      st->print(" (constant)");
  } else {
    if (ra->C->alias_type(adr_type())->is_volatile())
      st->print(" volatile!");
  }
}
#endif
#ifndef PRODUCT
void gather_loadDNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// idx
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// tmp
  st->print_raw("gather_loadD ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // idx
  st->print_raw("\t# vector (sve). KILL ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // tmp
  if (ra->C->alias_type(adr_type())->field() != nullptr) {
    ciField* f = ra->C->alias_type(adr_type())->field();
    st->print(" ! Field: ");
    if (f->is_volatile())
      st->print("volatile ");
    f->holder()->name()->print_symbol_on(st);
    st->print(".");
    f->name()->print_symbol_on(st);
    if (f->is_constant())
      st->print(" (constant)");
  } else {
    if (ra->C->alias_type(adr_type())->is_volatile())
      st->print(" volatile!");
  }
}
#endif
#ifndef PRODUCT
void gather_loadS_maskedNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// idx
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// pg
  st->print_raw("gather_loadS_masked ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // pg
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // idx
  if (ra->C->alias_type(adr_type())->field() != nullptr) {
    ciField* f = ra->C->alias_type(adr_type())->field();
    st->print(" ! Field: ");
    if (f->is_volatile())
      st->print("volatile ");
    f->holder()->name()->print_symbol_on(st);
    st->print(".");
    f->name()->print_symbol_on(st);
    if (f->is_constant())
      st->print(" (constant)");
  } else {
    if (ra->C->alias_type(adr_type())->is_volatile())
      st->print(" volatile!");
  }
}
#endif
#ifndef PRODUCT
void gather_loadD_maskedNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// idx
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// pg
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// tmp
  st->print_raw("gather_loadD_masked ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // pg
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // idx
  st->print_raw("\t# KILL ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // tmp
  if (ra->C->alias_type(adr_type())->field() != nullptr) {
    ciField* f = ra->C->alias_type(adr_type())->field();
    st->print(" ! Field: ");
    if (f->is_volatile())
      st->print("volatile ");
    f->holder()->name()->print_symbol_on(st);
    st->print(".");
    f->name()->print_symbol_on(st);
    if (f->is_constant())
      st->print(" (constant)");
  } else {
    if (ra->C->alias_type(adr_type())->is_volatile())
      st->print(" volatile!");
  }
}
#endif
#ifndef PRODUCT
void scatter_storeSNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// idx
  st->print_raw("scatter_storeS ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // idx
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
  st->print_raw("\t# vector (sve)");
  if (ra->C->alias_type(adr_type())->field() != nullptr) {
    ciField* f = ra->C->alias_type(adr_type())->field();
    st->print(" ! Field: ");
    if (f->is_volatile())
      st->print("volatile ");
    f->holder()->name()->print_symbol_on(st);
    st->print(".");
    f->name()->print_symbol_on(st);
    if (f->is_constant())
      st->print(" (constant)");
  } else {
    if (ra->C->alias_type(adr_type())->is_volatile())
      st->print(" volatile!");
  }
}
#endif
#ifndef PRODUCT
void scatter_storeDNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// idx
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// tmp
  st->print_raw("scatter_storeD ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // idx
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
  st->print_raw("\t# vector (sve). KILL ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // tmp
  if (ra->C->alias_type(adr_type())->field() != nullptr) {
    ciField* f = ra->C->alias_type(adr_type())->field();
    st->print(" ! Field: ");
    if (f->is_volatile())
      st->print("volatile ");
    f->holder()->name()->print_symbol_on(st);
    st->print(".");
    f->name()->print_symbol_on(st);
    if (f->is_constant())
      st->print(" (constant)");
  } else {
    if (ra->C->alias_type(adr_type())->is_volatile())
      st->print(" volatile!");
  }
}
#endif
#ifndef PRODUCT
void scatter_storeS_maskedNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// idx
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// pg
  st->print_raw("scatter_storeS_masked ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(", ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // pg
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // idx
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
  if (ra->C->alias_type(adr_type())->field() != nullptr) {
    ciField* f = ra->C->alias_type(adr_type())->field();
    st->print(" ! Field: ");
    if (f->is_volatile())
      st->print("volatile ");
    f->holder()->name()->print_symbol_on(st);
    st->print(".");
    f->name()->print_symbol_on(st);
    if (f->is_constant())
      st->print(" (constant)");
  } else {
    if (ra->C->alias_type(adr_type())->is_volatile())
      st->print(" volatile!");
  }
}
#endif
#ifndef PRODUCT
void scatter_storeD_maskedNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// idx
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// pg
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// tmp
  st->print_raw("scatter_storeD_masked ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(", ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // pg
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // idx
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
  st->print_raw("\t# KILL ");
  opnd_array(5)->ext_format(ra, this,idx5, st); // tmp
  if (ra->C->alias_type(adr_type())->field() != nullptr) {
    ciField* f = ra->C->alias_type(adr_type())->field();
    st->print(" ! Field: ");
    if (f->is_volatile())
      st->print("volatile ");
    f->holder()->name()->print_symbol_on(st);
    st->print(".");
    f->name()->print_symbol_on(st);
    if (f->is_constant())
      st->print(" (constant)");
  } else {
    if (ra->C->alias_type(adr_type())->is_volatile())
      st->print(" volatile!");
  }
}
#endif
#ifndef PRODUCT
void vcountLeadingZerosNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("vcountLeadingZeros ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
}
#endif
#ifndef PRODUCT
void vcountLeadingZeros_maskedNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// pg
  st->print_raw("vcountLeadingZeros_masked ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // pg
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src
}
#endif
#ifndef PRODUCT
void vcountTrailingZerosNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("vcountTrailingZeros ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
}
#endif
#ifndef PRODUCT
void vcountTrailingZeros_maskedNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// pg
  st->print_raw("vcountTrailingZeros_masked ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // pg
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src
}
#endif
#ifndef PRODUCT
void vreverseNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("vreverse ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
}
#endif
#ifndef PRODUCT
void vreverse_maskedNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// pg
  st->print_raw("vreverse_masked ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // pg
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src
}
#endif
#ifndef PRODUCT
void vreverseBytesNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("vreverseBytes ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
}
#endif
#ifndef PRODUCT
void vreverseBytes_maskedNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst_src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// pg
  st->print_raw("vreverseBytes_masked ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // pg
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst_src
}
#endif
#ifndef PRODUCT
void populateindexNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("populateindex ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw("\t # populate index (sve)");
}
#endif
#ifndef PRODUCT
void mcompressNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// pg
  st->print_raw("mcompress ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // pg
  st->print_raw("\t# KILL cr");
}
#endif
#ifndef PRODUCT
void vcompressNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// pg
  st->print_raw("vcompress ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // pg
}
#endif
#ifndef PRODUCT
void vcompressBNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// pg
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// dst
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// tmp1
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// tmp2
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// tmp3
  unsigned idx7 = idx6 + opnd_array(6)->num_edges(); 	// tmp4
  unsigned idx8 = idx7 + opnd_array(7)->num_edges(); 	// ptmp
  unsigned idx9 = idx8 + opnd_array(8)->num_edges(); 	// pgtmp
  st->print_raw("vcompressB ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // pg
  st->print_raw("\t# KILL ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // tmp1
  st->print_raw(", ");
  opnd_array(5)->ext_format(ra, this,idx5, st); // tmp2
  st->print_raw(", ");
  opnd_array(6)->ext_format(ra, this,idx6, st); // tmp3
  st->print_raw(", tmp4, ");
  opnd_array(8)->ext_format(ra, this,idx8, st); // ptmp
  st->print_raw(", ");
  opnd_array(9)->ext_format(ra, this,idx9, st); // pgtmp
}
#endif
#ifndef PRODUCT
void vcompressSNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// pg
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// dst
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// tmp1
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// tmp2
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// pgtmp
  st->print_raw("vcompressS ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // pg
  st->print_raw("\t# KILL ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // tmp1
  st->print_raw(", ");
  opnd_array(5)->ext_format(ra, this,idx5, st); // tmp2
  st->print_raw(", ");
  opnd_array(6)->ext_format(ra, this,idx6, st); // pgtmp
}
#endif
#ifndef PRODUCT
void vexpandNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// pg
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// dst
  st->print_raw("vexpand ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // dst
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // pg
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
}
#endif
#ifndef PRODUCT
void vsignum_le128bNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// zero
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// one
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// dst
  st->print_raw("vsignum_le128b ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\t# vector <= 128 bits");
}
#endif
#ifndef PRODUCT
void vsignum_le128b_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// zero
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// one
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// dst
  st->print_raw("vsignum_le128b ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\t# vector <= 128 bits");
}
#endif
#ifndef PRODUCT
void vsignum_gt128bNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// zero
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// one
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// dst
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// tmp
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// pgtmp
  st->print_raw("vsignum_gt128b ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\t# vector > 128 bits. KILL ");
  opnd_array(5)->ext_format(ra, this,idx5, st); // tmp
  st->print_raw(", ");
  opnd_array(6)->ext_format(ra, this,idx6, st); // pgtmp
}
#endif
#ifndef PRODUCT
void vsignum_gt128b_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// zero
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// one
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// dst
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// tmp
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// pgtmp
  st->print_raw("vsignum_gt128b ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\t# vector > 128 bits. KILL ");
  opnd_array(5)->ext_format(ra, this,idx5, st); // tmp
  st->print_raw(", ");
  opnd_array(6)->ext_format(ra, this,idx6, st); // pgtmp
}
#endif
#ifndef PRODUCT
void vcompressBitsNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("vcompressBits ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw("\t# vector (sve)");
}
#endif
#ifndef PRODUCT
void vexpandBitsNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("vexpandBits ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw("\t# vector (sve)");
}
#endif
#ifndef PRODUCT
void compareAndSwapP_shenandoahNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// oldval
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// newval
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// tmp
  st->print_raw("cmpxchg_shenandoah ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // oldval
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // newval
  st->print_raw("\t# (ptr) if ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(" == ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // oldval
  st->print_raw(" then ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(" <-- ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // newval
  st->print_raw(" with temp ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // tmp
}
#endif
#ifndef PRODUCT
void compareAndSwapN_shenandoahNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// oldval
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// newval
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// tmp
  st->print_raw("cmpxchgw_shenandoah ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // oldval
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // newval
  st->print_raw("\t# (ptr) if ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(" == ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // oldval
  st->print_raw(" then ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(" <-- ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // newval
  st->print_raw(" with temp ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // tmp
}
#endif
#ifndef PRODUCT
void compareAndSwapPAcq_shenandoahNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// oldval
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// newval
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// tmp
  st->print_raw("cmpxchg_acq_shenandoah_oop ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // oldval
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // newval
  st->print_raw("\t# (ptr) if ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(" == ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // oldval
  st->print_raw(" then ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(" <-- ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // newval
  st->print_raw(" with temp ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // tmp
}
#endif
#ifndef PRODUCT
void compareAndSwapNAcq_shenandoahNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// oldval
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// newval
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// tmp
  st->print_raw("cmpxchgw_acq_shenandoah_narrow_oop ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // oldval
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // newval
  st->print_raw("\t# (ptr) if ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(" == ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // oldval
  st->print_raw(" then ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(" <-- ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // newval
  st->print_raw(" with temp ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // tmp
}
#endif
#ifndef PRODUCT
void compareAndExchangeN_shenandoahNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// oldval
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// newval
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// res
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// tmp
  st->print_raw("cmpxchgw_shenandoah ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // res
  st->print_raw(" = ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // oldval
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // newval
  st->print_raw("\t# (narrow oop, weak) if ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(" == ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // oldval
  st->print_raw(" then ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(" <-- ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // newval
}
#endif
#ifndef PRODUCT
void compareAndExchangeP_shenandoahNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// oldval
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// newval
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// res
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// tmp
  st->print_raw("cmpxchg_shenandoah ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // oldval
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // newval
  st->print_raw("\t# (ptr) if ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(" == ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // oldval
  st->print_raw(" then ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(" <-- ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // newval
  st->print_raw(" with temp ");
  opnd_array(5)->ext_format(ra, this,idx5, st); // tmp
}
#endif
#ifndef PRODUCT
void compareAndExchangeNAcq_shenandoahNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// oldval
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// newval
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// res
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// tmp
  st->print_raw("cmpxchgw_acq_shenandoah ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // res
  st->print_raw(" = ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // oldval
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // newval
  st->print_raw("\t# (narrow oop, weak) if ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(" == ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // oldval
  st->print_raw(" then ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(" <-- ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // newval
}
#endif
#ifndef PRODUCT
void compareAndExchangePAcq_shenandoahNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// oldval
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// newval
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// res
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// tmp
  st->print_raw("cmpxchg_acq_shenandoah ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // oldval
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // newval
  st->print_raw("\t# (ptr) if ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(" == ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // oldval
  st->print_raw(" then ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(" <-- ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // newval
  st->print_raw(" with temp ");
  opnd_array(5)->ext_format(ra, this,idx5, st); // tmp
}
#endif
#ifndef PRODUCT
void weakCompareAndSwapN_shenandoahNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// oldval
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// newval
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// tmp
  st->print_raw("cmpxchgw_shenandoah ");
  opnd_array(0)->int_format(ra, this, st); // res
  st->print_raw(" = ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // oldval
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // newval
  st->print_raw("\t# (narrow oop, weak) if ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(" == ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // oldval
  st->print_raw(" then ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(" <-- ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // newval
  st->print_raw("csetw ");
  opnd_array(0)->int_format(ra, this, st); // res
  st->print_raw(", EQ\t# ");
  opnd_array(0)->int_format(ra, this, st); // res
  st->print_raw(" <-- (EQ ? 1 : 0)");
}
#endif
#ifndef PRODUCT
void weakCompareAndSwapP_shenandoahNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// oldval
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// newval
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// tmp
  st->print_raw("cmpxchg_shenandoah ");
  opnd_array(0)->int_format(ra, this, st); // res
  st->print_raw(" = ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // oldval
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // newval
  st->print_raw("\t# (ptr, weak) if ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(" == ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // oldval
  st->print_raw(" then ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(" <-- ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // newval
}
#endif
#ifndef PRODUCT
void weakCompareAndSwapNAcq_shenandoahNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// oldval
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// newval
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// tmp
  st->print_raw("cmpxchgw_acq_shenandoah ");
  opnd_array(0)->int_format(ra, this, st); // res
  st->print_raw(" = ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // oldval
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // newval
  st->print_raw("\t# (narrow oop, weak) if ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(" == ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // oldval
  st->print_raw(" then ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(" <-- ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // newval
  st->print_raw("csetw ");
  opnd_array(0)->int_format(ra, this, st); // res
  st->print_raw(", EQ\t# ");
  opnd_array(0)->int_format(ra, this, st); // res
  st->print_raw(" <-- (EQ ? 1 : 0)");
}
#endif
#ifndef PRODUCT
void weakCompareAndSwapPAcq_shenandoahNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// oldval
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// newval
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// tmp
  st->print_raw("cmpxchg_acq_shenandoah ");
  opnd_array(0)->int_format(ra, this, st); // res
  st->print_raw(" = ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // oldval
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // newval
  st->print_raw("\t# (ptr, weak) if ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(" == ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // oldval
  st->print_raw(" then ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(" <-- ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // newval
  st->print_raw("csetw ");
  opnd_array(0)->int_format(ra, this, st); // res
  st->print_raw(", EQ\t# ");
  opnd_array(0)->int_format(ra, this, st); // res
  st->print_raw(" <-- (EQ ? 1 : 0)");
}
#endif
#ifndef PRODUCT
void xLoadPNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst
  st->print_raw("ldr  ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  if (ra->C->alias_type(adr_type())->field() != nullptr) {
    ciField* f = ra->C->alias_type(adr_type())->field();
    st->print(" ! Field: ");
    if (f->is_volatile())
      st->print("volatile ");
    f->holder()->name()->print_symbol_on(st);
    st->print(".");
    f->name()->print_symbol_on(st);
    if (f->is_constant())
      st->print(" (constant)");
  } else {
    if (ra->C->alias_type(adr_type())->is_volatile())
      st->print(" volatile!");
  }
}
#endif
#ifndef PRODUCT
void xLoadPVolatileNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst
  st->print_raw("ldar  ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("\t");
  if (ra->C->alias_type(adr_type())->field() != nullptr) {
    ciField* f = ra->C->alias_type(adr_type())->field();
    st->print(" ! Field: ");
    if (f->is_volatile())
      st->print("volatile ");
    f->holder()->name()->print_symbol_on(st);
    st->print(".");
    f->name()->print_symbol_on(st);
    if (f->is_constant())
      st->print(" (constant)");
  } else {
    if (ra->C->alias_type(adr_type())->is_volatile())
      st->print(" volatile!");
  }
}
#endif
#ifndef PRODUCT
void xCompareAndSwapPNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// oldval
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// newval
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// res
  st->print_raw("cmpxchg ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // oldval
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // newval
  st->print_raw("\n\t");
  st->print_raw("cset    ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // res
  st->print_raw(", EQ");
}
#endif
#ifndef PRODUCT
void xCompareAndSwapP_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// oldval
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// newval
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// res
  st->print_raw("cmpxchg ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // oldval
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // newval
  st->print_raw("\n\t");
  st->print_raw("cset    ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // res
  st->print_raw(", EQ");
}
#endif
#ifndef PRODUCT
void xCompareAndSwapPAcqNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// oldval
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// newval
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// res
  st->print_raw("cmpxchg ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // oldval
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // newval
  st->print_raw("\n\t");
  st->print_raw("cset    ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // res
  st->print_raw(", EQ");
}
#endif
#ifndef PRODUCT
void xCompareAndSwapPAcq_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// oldval
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// newval
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// res
  st->print_raw("cmpxchg ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // oldval
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // newval
  st->print_raw("\n\t");
  st->print_raw("cset    ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // res
  st->print_raw(", EQ");
}
#endif
#ifndef PRODUCT
void xCompareAndExchangePNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// oldval
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// newval
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// res
  st->print_raw("cmpxchg ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // res
  st->print_raw(" = ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // oldval
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // newval
}
#endif
#ifndef PRODUCT
void xCompareAndExchangePAcqNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// oldval
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// newval
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// res
  st->print_raw("cmpxchg ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // res
  st->print_raw(" = ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // oldval
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // newval
}
#endif
#ifndef PRODUCT
void xGetAndSetPNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// newv
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// prev
  st->print_raw("atomic_xchg  ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // prev
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // newv
  st->print_raw(", [");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("]");
}
#endif
#ifndef PRODUCT
void xGetAndSetPAcqNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// newv
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// prev
  st->print_raw("atomic_xchg_acq  ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // prev
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // newv
  st->print_raw(", [");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("]");
}
#endif
#ifndef PRODUCT
void zLoadPNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst
  st->print_raw("ldr  ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  if (ra->C->alias_type(adr_type())->field() != nullptr) {
    ciField* f = ra->C->alias_type(adr_type())->field();
    st->print(" ! Field: ");
    if (f->is_volatile())
      st->print("volatile ");
    f->holder()->name()->print_symbol_on(st);
    st->print(".");
    f->name()->print_symbol_on(st);
    if (f->is_constant())
      st->print(" (constant)");
  } else {
    if (ra->C->alias_type(adr_type())->is_volatile())
      st->print(" volatile!");
  }
}
#endif
#ifndef PRODUCT
void zLoadPVolatileNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst
  st->print_raw("ldar  ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("\t");
  if (ra->C->alias_type(adr_type())->field() != nullptr) {
    ciField* f = ra->C->alias_type(adr_type())->field();
    st->print(" ! Field: ");
    if (f->is_volatile())
      st->print("volatile ");
    f->holder()->name()->print_symbol_on(st);
    st->print(".");
    f->name()->print_symbol_on(st);
    if (f->is_constant())
      st->print(" (constant)");
  } else {
    if (ra->C->alias_type(adr_type())->is_volatile())
      st->print(" volatile!");
  }
}
#endif
#ifndef PRODUCT
void zStorePNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// tmp
  st->print_raw("movq    ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
  st->print_raw("\t# ptr");
  if (ra->C->alias_type(adr_type())->field() != nullptr) {
    ciField* f = ra->C->alias_type(adr_type())->field();
    st->print(" ! Field: ");
    if (f->is_volatile())
      st->print("volatile ");
    f->holder()->name()->print_symbol_on(st);
    st->print(".");
    f->name()->print_symbol_on(st);
    if (f->is_constant())
      st->print(" (constant)");
  } else {
    if (ra->C->alias_type(adr_type())->is_volatile())
      st->print(" volatile!");
  }
}
#endif
#ifndef PRODUCT
void zStorePVolatileNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// tmp
  st->print_raw("movq    ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
  st->print_raw("\t# ptr");
  if (ra->C->alias_type(adr_type())->field() != nullptr) {
    ciField* f = ra->C->alias_type(adr_type())->field();
    st->print(" ! Field: ");
    if (f->is_volatile())
      st->print("volatile ");
    f->holder()->name()->print_symbol_on(st);
    st->print(".");
    f->name()->print_symbol_on(st);
    if (f->is_constant())
      st->print(" (constant)");
  } else {
    if (ra->C->alias_type(adr_type())->is_volatile())
      st->print(" volatile!");
  }
}
#endif
#ifndef PRODUCT
void zCompareAndSwapPNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// oldval
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// newval
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// res
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// oldval_tmp
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// newval_tmp
  st->print_raw("cmpxchg ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // oldval
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // newval
  st->print_raw("\n\t");
  st->print_raw("cset    ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // res
  st->print_raw(", EQ");
}
#endif
#ifndef PRODUCT
void zCompareAndSwapP_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// oldval
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// newval
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// res
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// oldval_tmp
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// newval_tmp
  st->print_raw("cmpxchg ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // oldval
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // newval
  st->print_raw("\n\t");
  st->print_raw("cset    ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // res
  st->print_raw(", EQ");
}
#endif
#ifndef PRODUCT
void zCompareAndSwapPAcqNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// oldval
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// newval
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// res
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// oldval_tmp
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// newval_tmp
  st->print_raw("cmpxchg ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // oldval
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // newval
  st->print_raw("\n\t");
  st->print_raw("cset    ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // res
  st->print_raw(", EQ");
}
#endif
#ifndef PRODUCT
void zCompareAndSwapPAcq_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// oldval
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// newval
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// res
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// oldval_tmp
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// newval_tmp
  st->print_raw("cmpxchg ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // oldval
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // newval
  st->print_raw("\n\t");
  st->print_raw("cset    ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // res
  st->print_raw(", EQ");
}
#endif
#ifndef PRODUCT
void zCompareAndExchangePNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// oldval
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// newval
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// res
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// oldval_tmp
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// newval_tmp
  st->print_raw("cmpxchg ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // oldval
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // newval
  st->print_raw("\n\t");
  st->print_raw("cset    ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // res
  st->print_raw(", EQ");
}
#endif
#ifndef PRODUCT
void zCompareAndExchangePAcqNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// oldval
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// newval
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// res
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// oldval_tmp
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// newval_tmp
  st->print_raw("cmpxchg ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // oldval
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // newval
  st->print_raw("\n\t");
  st->print_raw("cset    ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // res
  st->print_raw(", EQ");
}
#endif
#ifndef PRODUCT
void zGetAndSetPNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// newv
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// prev
  st->print_raw("atomic_xchg  ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // prev
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // newv
  st->print_raw(", [");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("]");
}
#endif
#ifndef PRODUCT
void zGetAndSetPAcqNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// newv
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// prev
  st->print_raw("atomic_xchg  ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // prev
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // newv
  st->print_raw(", [");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("]");
}
#endif
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
