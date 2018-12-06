#line 1 "ad_s390_format.cpp"
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
void immB_minus1Oper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print("#%d", _c0);
}
void immB_minus1Oper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print("#%d", _c0);
}
#endif

#ifndef PRODUCT
void immB_n0m1Oper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print("#%d", _c0);
}
void immB_n0m1Oper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print("#%d", _c0);
}
#endif

#ifndef PRODUCT
void immS_minus1Oper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print("#%d", _c0);
}
void immS_minus1Oper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print("#%d", _c0);
}
#endif

#ifndef PRODUCT
void immS_n0m1Oper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print("#%d", _c0);
}
void immS_n0m1Oper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print("#%d", _c0);
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
void immI20Oper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print("#%d", _c0);
}
void immI20Oper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print("#%d", _c0);
}
#endif

#ifndef PRODUCT
void immI16Oper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print("#%d", _c0);
}
void immI16Oper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print("#%d", _c0);
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
void immI_0Oper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print("#%d", _c0);
}
void immI_0Oper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print("#%d", _c0);
}
#endif

#ifndef PRODUCT
void immI_minus1Oper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print("#%d", _c0);
}
void immI_minus1Oper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print("#%d", _c0);
}
#endif

#ifndef PRODUCT
void immI_n0m1Oper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print("#%d", _c0);
}
void immI_n0m1Oper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print("#%d", _c0);
}
#endif

#ifndef PRODUCT
void uimmIOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print("#%d", _c0);
}
void uimmIOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print("#%d", _c0);
}
#endif

#ifndef PRODUCT
void uimmI16Oper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print("#%d", _c0);
}
void uimmI16Oper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print("#%d", _c0);
}
#endif

#ifndef PRODUCT
void uimmI12Oper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print("#%d", _c0);
}
void uimmI12Oper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print("#%d", _c0);
}
#endif

#ifndef PRODUCT
void uimmI8Oper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print("#%d", _c0);
}
void uimmI8Oper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print("#%d", _c0);
}
#endif

#ifndef PRODUCT
void uimmI6Oper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print("#%d", _c0);
}
void uimmI6Oper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print("#%d", _c0);
}
#endif

#ifndef PRODUCT
void uimmI5Oper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print("#%d", _c0);
}
void uimmI5Oper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print("#%d", _c0);
}
#endif

#ifndef PRODUCT
void SSlenDWOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print("#" INT64_FORMAT, (int64_t)_c0);
}
void SSlenDWOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print("#" INT64_FORMAT, (int64_t)_c0);
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
void immI_255Oper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print("#%d", _c0);
}
void immI_255Oper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print("#%d", _c0);
}
#endif

#ifndef PRODUCT
void immI_32_63Oper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print("#%d", _c0);
}
void immI_32_63Oper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print("#%d", _c0);
}
#endif

#ifndef PRODUCT
void uimmI_LL1Oper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print("#%d", _c0);
}
void uimmI_LL1Oper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print("#%d", _c0);
}
#endif

#ifndef PRODUCT
void uimmI_LH1Oper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print("#%d", _c0);
}
void uimmI_LH1Oper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
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
void immL32Oper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print("#" INT64_FORMAT, (int64_t)_c0);
}
void immL32Oper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print("#" INT64_FORMAT, (int64_t)_c0);
}
#endif

#ifndef PRODUCT
void immL20Oper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print("#" INT64_FORMAT, (int64_t)_c0);
}
void immL20Oper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print("#" INT64_FORMAT, (int64_t)_c0);
}
#endif

#ifndef PRODUCT
void immL16Oper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print("#" INT64_FORMAT, (int64_t)_c0);
}
void immL16Oper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print("#" INT64_FORMAT, (int64_t)_c0);
}
#endif

#ifndef PRODUCT
void immL8Oper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print("#" INT64_FORMAT, (int64_t)_c0);
}
void immL8Oper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print("#" INT64_FORMAT, (int64_t)_c0);
}
#endif

#ifndef PRODUCT
void uimmL32Oper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print("#" INT64_FORMAT, (int64_t)_c0);
}
void uimmL32Oper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print("#" INT64_FORMAT, (int64_t)_c0);
}
#endif

#ifndef PRODUCT
void uimmL16Oper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print("#" INT64_FORMAT, (int64_t)_c0);
}
void uimmL16Oper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print("#" INT64_FORMAT, (int64_t)_c0);
}
#endif

#ifndef PRODUCT
void uimmL12Oper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print("#" INT64_FORMAT, (int64_t)_c0);
}
void uimmL12Oper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print("#" INT64_FORMAT, (int64_t)_c0);
}
#endif

#ifndef PRODUCT
void uimmL8Oper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print("#" INT64_FORMAT, (int64_t)_c0);
}
void uimmL8Oper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print("#" INT64_FORMAT, (int64_t)_c0);
}
#endif

#ifndef PRODUCT
void immL_FFOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print("#" INT64_FORMAT, (int64_t)_c0);
}
void immL_FFOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print("#" INT64_FORMAT, (int64_t)_c0);
}
#endif

#ifndef PRODUCT
void immL_FFFFOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print("#" INT64_FORMAT, (int64_t)_c0);
}
void immL_FFFFOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print("#" INT64_FORMAT, (int64_t)_c0);
}
#endif

#ifndef PRODUCT
void immL_FFFFFFFFOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print("#" INT64_FORMAT, (int64_t)_c0);
}
void immL_FFFFFFFFOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print("#" INT64_FORMAT, (int64_t)_c0);
}
#endif

#ifndef PRODUCT
void immL_0Oper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print("#" INT64_FORMAT, (int64_t)_c0);
}
void immL_0Oper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print("#" INT64_FORMAT, (int64_t)_c0);
}
#endif

#ifndef PRODUCT
void uimmL_LL1Oper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print("#" INT64_FORMAT, (int64_t)_c0);
}
void uimmL_LL1Oper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print("#" INT64_FORMAT, (int64_t)_c0);
}
#endif

#ifndef PRODUCT
void uimmL_LH1Oper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print("#" INT64_FORMAT, (int64_t)_c0);
}
void uimmL_LH1Oper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print("#" INT64_FORMAT, (int64_t)_c0);
}
#endif

#ifndef PRODUCT
void uimmL_HL1Oper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print("#" INT64_FORMAT, (int64_t)_c0);
}
void uimmL_HL1Oper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print("#" INT64_FORMAT, (int64_t)_c0);
}
#endif

#ifndef PRODUCT
void uimmL_HH1Oper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print("#" INT64_FORMAT, (int64_t)_c0);
}
void uimmL_HH1Oper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
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
void immP32Oper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  if (_c0) _c0->dump_on(st);
}
void immP32Oper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  if (_c0) _c0->dump_on(st);
}
#endif

#ifndef PRODUCT
void immP16Oper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  if (_c0) _c0->dump_on(st);
}
void immP16Oper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  if (_c0) _c0->dump_on(st);
}
#endif

#ifndef PRODUCT
void immP8Oper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  if (_c0) _c0->dump_on(st);
}
void immP8Oper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
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
void immNOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  if (_c0) _c0->dump_on(st);
}
void immNOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
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
void immN8Oper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  if (_c0) _c0->dump_on(st);
}
void immN8Oper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
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
void immDOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print("#%f", _c0);
}
void immDOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print("#%f", _c0);
}
#endif

#ifndef PRODUCT
void immDpm0Oper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print("#%f", _c0);
}
void immDpm0Oper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print("#%f", _c0);
}
#endif

#ifndef PRODUCT
void immDp0Oper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print("#%f", _c0);
}
void immDp0Oper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
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
void immFpm0Oper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print("#%f", _c0);
}
void immFpm0Oper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print("#%f", _c0);
}
#endif

#ifndef PRODUCT
void immFp0Oper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print("#%f", _c0);
}
void immFp0Oper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print("#%f", _c0);
}
#endif

#ifndef PRODUCT
void iRegIOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node,reg_str);
    st->print("%s",reg_str);
  }
}
void iRegIOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str);
    st->print("%s",reg_str);
  }
}
#endif

#ifndef PRODUCT
void noArg_iRegIOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node,reg_str);
    st->print("%s",reg_str);
  }
}
void noArg_iRegIOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str);
    st->print("%s",reg_str);
  }
}
#endif

#ifndef PRODUCT
void revenRegIOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node,reg_str);
    st->print("%s",reg_str);
  }
}
void revenRegIOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str);
    st->print("%s",reg_str);
  }
}
#endif

#ifndef PRODUCT
void roddRegIOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node,reg_str);
    st->print("%s",reg_str);
  }
}
void roddRegIOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str);
    st->print("%s",reg_str);
  }
}
#endif

#ifndef PRODUCT
void rarg1RegIOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node,reg_str);
    st->print("%s",reg_str);
  }
}
void rarg1RegIOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str);
    st->print("%s",reg_str);
  }
}
#endif

#ifndef PRODUCT
void rarg2RegIOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node,reg_str);
    st->print("%s",reg_str);
  }
}
void rarg2RegIOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str);
    st->print("%s",reg_str);
  }
}
#endif

#ifndef PRODUCT
void rarg3RegIOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node,reg_str);
    st->print("%s",reg_str);
  }
}
void rarg3RegIOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str);
    st->print("%s",reg_str);
  }
}
#endif

#ifndef PRODUCT
void rarg4RegIOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node,reg_str);
    st->print("%s",reg_str);
  }
}
void rarg4RegIOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str);
    st->print("%s",reg_str);
  }
}
#endif

#ifndef PRODUCT
void rarg5RegIOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node,reg_str);
    st->print("%s",reg_str);
  }
}
void rarg5RegIOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str);
    st->print("%s",reg_str);
  }
}
#endif

#ifndef PRODUCT
void noOdd_iRegIOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node,reg_str);
    st->print("%s",reg_str);
  }
}
void noOdd_iRegIOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str);
    st->print("%s",reg_str);
  }
}
#endif

#ifndef PRODUCT
void iRegPOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node,reg_str);
    st->print("%s",reg_str);
  }
}
void iRegPOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str);
    st->print("%s",reg_str);
  }
}
#endif

#ifndef PRODUCT
void threadRegPOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print_raw("Z_THREAD");
}
void threadRegPOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print_raw("Z_THREAD");
}
#endif

#ifndef PRODUCT
void noArg_iRegPOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node,reg_str);
    st->print("%s",reg_str);
  }
}
void noArg_iRegPOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str);
    st->print("%s",reg_str);
  }
}
#endif

#ifndef PRODUCT
void rarg1RegPOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node,reg_str);
    st->print("%s",reg_str);
  }
}
void rarg1RegPOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str);
    st->print("%s",reg_str);
  }
}
#endif

#ifndef PRODUCT
void rarg2RegPOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node,reg_str);
    st->print("%s",reg_str);
  }
}
void rarg2RegPOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str);
    st->print("%s",reg_str);
  }
}
#endif

#ifndef PRODUCT
void rarg3RegPOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node,reg_str);
    st->print("%s",reg_str);
  }
}
void rarg3RegPOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str);
    st->print("%s",reg_str);
  }
}
#endif

#ifndef PRODUCT
void rarg4RegPOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node,reg_str);
    st->print("%s",reg_str);
  }
}
void rarg4RegPOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str);
    st->print("%s",reg_str);
  }
}
#endif

#ifndef PRODUCT
void rarg5RegPOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node,reg_str);
    st->print("%s",reg_str);
  }
}
void rarg5RegPOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str);
    st->print("%s",reg_str);
  }
}
#endif

#ifndef PRODUCT
void memoryRegPOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node,reg_str);
    st->print("%s",reg_str);
  }
}
void memoryRegPOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str);
    st->print("%s",reg_str);
  }
}
#endif

#ifndef PRODUCT
void revenRegPOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node,reg_str);
    st->print("%s",reg_str);
  }
}
void revenRegPOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str);
    st->print("%s",reg_str);
  }
}
#endif

#ifndef PRODUCT
void roddRegPOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node,reg_str);
    st->print("%s",reg_str);
  }
}
void roddRegPOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str);
    st->print("%s",reg_str);
  }
}
#endif

#ifndef PRODUCT
void lock_ptr_RegPOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node,reg_str);
    st->print("%s",reg_str);
  }
}
void lock_ptr_RegPOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str);
    st->print("%s",reg_str);
  }
}
#endif

#ifndef PRODUCT
void rscratch2RegPOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node,reg_str);
    st->print("%s",reg_str);
  }
}
void rscratch2RegPOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str);
    st->print("%s",reg_str);
  }
}
#endif

#ifndef PRODUCT
void iRegNOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node,reg_str);
    st->print("%s",reg_str);
  }
}
void iRegNOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str);
    st->print("%s",reg_str);
  }
}
#endif

#ifndef PRODUCT
void noArg_iRegNOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node,reg_str);
    st->print("%s",reg_str);
  }
}
void noArg_iRegNOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str);
    st->print("%s",reg_str);
  }
}
#endif

#ifndef PRODUCT
void rarg1RegNOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node,reg_str);
    st->print("%s",reg_str);
  }
}
void rarg1RegNOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str);
    st->print("%s",reg_str);
  }
}
#endif

#ifndef PRODUCT
void rarg2RegNOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node,reg_str);
    st->print("%s",reg_str);
  }
}
void rarg2RegNOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str);
    st->print("%s",reg_str);
  }
}
#endif

#ifndef PRODUCT
void rarg3RegNOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node,reg_str);
    st->print("%s",reg_str);
  }
}
void rarg3RegNOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str);
    st->print("%s",reg_str);
  }
}
#endif

#ifndef PRODUCT
void rarg4RegNOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node,reg_str);
    st->print("%s",reg_str);
  }
}
void rarg4RegNOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str);
    st->print("%s",reg_str);
  }
}
#endif

#ifndef PRODUCT
void rarg5RegNOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node,reg_str);
    st->print("%s",reg_str);
  }
}
void rarg5RegNOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str);
    st->print("%s",reg_str);
  }
}
#endif

#ifndef PRODUCT
void iRegLOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node,reg_str);
    st->print("%s",reg_str);
  }
}
void iRegLOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str);
    st->print("%s",reg_str);
  }
}
#endif

#ifndef PRODUCT
void revenRegLOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node,reg_str);
    st->print("%s",reg_str);
  }
}
void revenRegLOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str);
    st->print("%s",reg_str);
  }
}
#endif

#ifndef PRODUCT
void roddRegLOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node,reg_str);
    st->print("%s",reg_str);
  }
}
void roddRegLOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str);
    st->print("%s",reg_str);
  }
}
#endif

#ifndef PRODUCT
void rarg1RegLOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node,reg_str);
    st->print("%s",reg_str);
  }
}
void rarg1RegLOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str);
    st->print("%s",reg_str);
  }
}
#endif

#ifndef PRODUCT
void rarg5RegLOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node,reg_str);
    st->print("%s",reg_str);
  }
}
void rarg5RegLOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str);
    st->print("%s",reg_str);
  }
}
#endif

#ifndef PRODUCT
void flagsRegOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print_raw("CR");
}
void flagsRegOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print_raw("CR");
}
#endif

#ifndef PRODUCT
void TD_flagsRegOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print_raw("CR");
}
void TD_flagsRegOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print_raw("CR");
}
#endif

#ifndef PRODUCT
void regDOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node,reg_str);
    st->print("%s",reg_str);
  }
}
void regDOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str);
    st->print("%s",reg_str);
  }
}
#endif

#ifndef PRODUCT
void rscratchRegDOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node,reg_str);
    st->print("%s",reg_str);
  }
}
void rscratchRegDOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str);
    st->print("%s",reg_str);
  }
}
#endif

#ifndef PRODUCT
void regFOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node,reg_str);
    st->print("%s",reg_str);
  }
}
void regFOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str);
    st->print("%s",reg_str);
  }
}
#endif

#ifndef PRODUCT
void rscratchRegFOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node,reg_str);
    st->print("%s",reg_str);
  }
}
void rscratchRegFOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str);
    st->print("%s",reg_str);
  }
}
#endif

#ifndef PRODUCT
void inline_cache_regPOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node,reg_str);
    st->print("%s",reg_str);
  }
}
void inline_cache_regPOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str);
    st->print("%s",reg_str);
  }
}
#endif

#ifndef PRODUCT
void compiler_method_oop_regPOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node,reg_str);
    st->print("%s",reg_str);
  }
}
void compiler_method_oop_regPOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str);
    st->print("%s",reg_str);
  }
}
#endif

#ifndef PRODUCT
void interpreter_method_oop_regPOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node,reg_str);
    st->print("%s",reg_str);
  }
}
void interpreter_method_oop_regPOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str);
    st->print("%s",reg_str);
  }
}
#endif

#ifndef PRODUCT
void iRegP2NOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node,reg_str);
    st->print("%s",reg_str);
  }
}
void iRegP2NOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str);
    st->print("%s",reg_str);
  }
}
#endif

#ifndef PRODUCT
void iRegN2POper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node,reg_str);
    st->print("%s",reg_str);
  }
}
void iRegN2POper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str);
    st->print("%s",reg_str);
  }
}
#endif

#ifndef PRODUCT
void indirectOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print_raw("#0[,");
  { char reg_str[128];
    ra->dump_register(node,reg_str);
    st->print("%s",reg_str);
  }
  st->print_raw("]");
}
void indirectOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print_raw("#0[,");
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str);
    st->print("%s",reg_str);
  }
  st->print_raw("]");
}
#endif

#ifndef PRODUCT
void indOffset20Oper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print("#" INT64_FORMAT, (int64_t)_c0);
  st->print_raw("[,");
  { char reg_str[128];
    ra->dump_register(node,reg_str);
    st->print("%s",reg_str);
  }
  st->print_raw("]");
}
void indOffset20Oper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print("#" INT64_FORMAT, (int64_t)_c0);
  st->print_raw("[,");
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str);
    st->print("%s",reg_str);
  }
  st->print_raw("]");
}
#endif

#ifndef PRODUCT
void indOffset20NarrowOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print("#" INT64_FORMAT, (int64_t)_c0);
  st->print_raw("[,");
  { char reg_str[128];
    ra->dump_register(node,reg_str);
    st->print("%s",reg_str);
  }
  st->print_raw("]");
}
void indOffset20NarrowOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print("#" INT64_FORMAT, (int64_t)_c0);
  st->print_raw("[,");
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str);
    st->print("%s",reg_str);
  }
  st->print_raw("]");
}
#endif

#ifndef PRODUCT
void indOffset12Oper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print("#" INT64_FORMAT, (int64_t)_c0);
  st->print_raw("[[,");
  { char reg_str[128];
    ra->dump_register(node,reg_str);
    st->print("%s",reg_str);
  }
  st->print_raw("]]");
}
void indOffset12Oper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print("#" INT64_FORMAT, (int64_t)_c0);
  st->print_raw("[[,");
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str);
    st->print("%s",reg_str);
  }
  st->print_raw("]]");
}
#endif

#ifndef PRODUCT
void indOffset12NarrowOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print("#" INT64_FORMAT, (int64_t)_c0);
  st->print_raw("[[,");
  { char reg_str[128];
    ra->dump_register(node,reg_str);
    st->print("%s",reg_str);
  }
  st->print_raw("]]");
}
void indOffset12NarrowOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print("#" INT64_FORMAT, (int64_t)_c0);
  st->print_raw("[[,");
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str);
    st->print("%s",reg_str);
  }
  st->print_raw("]]");
}
#endif

#ifndef PRODUCT
void indIndexOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print_raw("#0[(");
  { char reg_str[128];
    ra->dump_register(node,reg_str);
    st->print("%s",reg_str);
  }
  st->print_raw(",");
  { char reg_str[128];
    ra->dump_register(node,reg_str);
    st->print("%s",reg_str);
  }
  st->print_raw(")]");
}
void indIndexOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print_raw("#0[(");
  { char reg_str[128];
    ra->dump_register(node->in(idx+1),reg_str);
    st->print("%s",reg_str);
  }
  st->print_raw(",");
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str);
    st->print("%s",reg_str);
  }
  st->print_raw(")]");
}
#endif

#ifndef PRODUCT
void indOffset20indexOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print("#" INT64_FORMAT, (int64_t)_c0);
  st->print_raw("[(");
  { char reg_str[128];
    ra->dump_register(node,reg_str);
    st->print("%s",reg_str);
  }
  st->print_raw(",");
  { char reg_str[128];
    ra->dump_register(node,reg_str);
    st->print("%s",reg_str);
  }
  st->print_raw(")]");
}
void indOffset20indexOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print("#" INT64_FORMAT, (int64_t)_c0);
  st->print_raw("[(");
  { char reg_str[128];
    ra->dump_register(node->in(idx+1),reg_str);
    st->print("%s",reg_str);
  }
  st->print_raw(",");
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str);
    st->print("%s",reg_str);
  }
  st->print_raw(")]");
}
#endif

#ifndef PRODUCT
void indOffset20indexNarrowOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print("#" INT64_FORMAT, (int64_t)_c0);
  st->print_raw("[(");
  { char reg_str[128];
    ra->dump_register(node,reg_str);
    st->print("%s",reg_str);
  }
  st->print_raw(",");
  { char reg_str[128];
    ra->dump_register(node,reg_str);
    st->print("%s",reg_str);
  }
  st->print_raw(")]");
}
void indOffset20indexNarrowOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print("#" INT64_FORMAT, (int64_t)_c0);
  st->print_raw("[(");
  { char reg_str[128];
    ra->dump_register(node->in(idx+1),reg_str);
    st->print("%s",reg_str);
  }
  st->print_raw(",");
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str);
    st->print("%s",reg_str);
  }
  st->print_raw(")]");
}
#endif

#ifndef PRODUCT
void indOffset12indexOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print("#" INT64_FORMAT, (int64_t)_c0);
  st->print_raw("[[(");
  { char reg_str[128];
    ra->dump_register(node,reg_str);
    st->print("%s",reg_str);
  }
  st->print_raw(",");
  { char reg_str[128];
    ra->dump_register(node,reg_str);
    st->print("%s",reg_str);
  }
  st->print_raw(")]]");
}
void indOffset12indexOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print("#" INT64_FORMAT, (int64_t)_c0);
  st->print_raw("[[(");
  { char reg_str[128];
    ra->dump_register(node->in(idx+1),reg_str);
    st->print("%s",reg_str);
  }
  st->print_raw(",");
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str);
    st->print("%s",reg_str);
  }
  st->print_raw(")]]");
}
#endif

#ifndef PRODUCT
void indOffset12indexNarrowOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print("#" INT64_FORMAT, (int64_t)_c0);
  st->print_raw("[[(");
  { char reg_str[128];
    ra->dump_register(node,reg_str);
    st->print("%s",reg_str);
  }
  st->print_raw(",");
  { char reg_str[128];
    ra->dump_register(node,reg_str);
    st->print("%s",reg_str);
  }
  st->print_raw(")]]");
}
void indOffset12indexNarrowOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print("#" INT64_FORMAT, (int64_t)_c0);
  st->print_raw("[[(");
  { char reg_str[128];
    ra->dump_register(node->in(idx+1),reg_str);
    st->print("%s",reg_str);
  }
  st->print_raw(",");
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str);
    st->print("%s",reg_str);
  }
  st->print_raw(")]]");
}
#endif

#ifndef PRODUCT
void stackSlotIOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print_raw("[");
  { char reg_str[128];
    ra->dump_register(node,reg_str);
    st->print("%s",reg_str);
  }
  st->print_raw("(stackSlotI)]");
}
void stackSlotIOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print_raw("[");
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str);
    st->print("%s",reg_str);
  }
  st->print_raw("(stackSlotI)]");
}
#endif

#ifndef PRODUCT
void stackSlotPOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print_raw("[");
  { char reg_str[128];
    ra->dump_register(node,reg_str);
    st->print("%s",reg_str);
  }
  st->print_raw("(stackSlotP)]");
}
void stackSlotPOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print_raw("[");
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str);
    st->print("%s",reg_str);
  }
  st->print_raw("(stackSlotP)]");
}
#endif

#ifndef PRODUCT
void stackSlotFOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print_raw("[");
  { char reg_str[128];
    ra->dump_register(node,reg_str);
    st->print("%s",reg_str);
  }
  st->print_raw("(stackSlotF)]");
}
void stackSlotFOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print_raw("[");
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str);
    st->print("%s",reg_str);
  }
  st->print_raw("(stackSlotF)]");
}
#endif

#ifndef PRODUCT
void stackSlotDOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print_raw("[");
  { char reg_str[128];
    ra->dump_register(node,reg_str);
    st->print("%s",reg_str);
  }
  st->print_raw("(stackSlotD)]");
}
void stackSlotDOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print_raw("[");
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str);
    st->print("%s",reg_str);
  }
  st->print_raw("(stackSlotD)]");
}
#endif

#ifndef PRODUCT
void stackSlotLOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print_raw("[");
  { char reg_str[128];
    ra->dump_register(node,reg_str);
    st->print("%s",reg_str);
  }
  st->print_raw("(stackSlotL)]");
}
void stackSlotLOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print_raw("[");
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str);
    st->print("%s",reg_str);
  }
  st->print_raw("(stackSlotL)]");
}
#endif

#ifndef PRODUCT
void cmpOpTOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print_raw("");
       if( _c0 == BoolTest::eq ) st->print_raw("eq");
  else if( _c0 == BoolTest::ne ) st->print_raw("ne");
  else if( _c0 == BoolTest::le ) st->print_raw("le");
  else if( _c0 == BoolTest::ge ) st->print_raw("ge");
  else if( _c0 == BoolTest::lt ) st->print_raw("lt");
  else if( _c0 == BoolTest::gt ) st->print_raw("gt");
  else if( _c0 == BoolTest::overflow ) st->print_raw("o");
  else if( _c0 == BoolTest::no_overflow ) st->print_raw("no");
}
void cmpOpTOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print_raw("");
       if( _c0 == BoolTest::eq ) st->print_raw("eq");
  else if( _c0 == BoolTest::ne ) st->print_raw("ne");
  else if( _c0 == BoolTest::le ) st->print_raw("le");
  else if( _c0 == BoolTest::ge ) st->print_raw("ge");
  else if( _c0 == BoolTest::lt ) st->print_raw("lt");
  else if( _c0 == BoolTest::gt ) st->print_raw("gt");
  else if( _c0 == BoolTest::overflow ) st->print_raw("o");
  else if( _c0 == BoolTest::no_overflow ) st->print_raw("no");
}
#endif

#ifndef PRODUCT
void cmpOpFOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print_raw("");
       if( _c0 == BoolTest::eq ) st->print_raw("eq");
  else if( _c0 == BoolTest::ne ) st->print_raw("ne");
  else if( _c0 == BoolTest::le ) st->print_raw("le");
  else if( _c0 == BoolTest::ge ) st->print_raw("ge");
  else if( _c0 == BoolTest::lt ) st->print_raw("lt");
  else if( _c0 == BoolTest::gt ) st->print_raw("gt");
  else if( _c0 == BoolTest::overflow ) st->print_raw("o");
  else if( _c0 == BoolTest::no_overflow ) st->print_raw("no");
}
void cmpOpFOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print_raw("");
       if( _c0 == BoolTest::eq ) st->print_raw("eq");
  else if( _c0 == BoolTest::ne ) st->print_raw("ne");
  else if( _c0 == BoolTest::le ) st->print_raw("le");
  else if( _c0 == BoolTest::ge ) st->print_raw("ge");
  else if( _c0 == BoolTest::lt ) st->print_raw("lt");
  else if( _c0 == BoolTest::gt ) st->print_raw("gt");
  else if( _c0 == BoolTest::overflow ) st->print_raw("o");
  else if( _c0 == BoolTest::no_overflow ) st->print_raw("no");
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
  else if( _c0 == BoolTest::overflow ) st->print_raw("o");
  else if( _c0 == BoolTest::no_overflow ) st->print_raw("no");
}
void cmpOpOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print_raw("");
       if( _c0 == BoolTest::eq ) st->print_raw("eq");
  else if( _c0 == BoolTest::ne ) st->print_raw("ne");
  else if( _c0 == BoolTest::le ) st->print_raw("le");
  else if( _c0 == BoolTest::ge ) st->print_raw("ge");
  else if( _c0 == BoolTest::lt ) st->print_raw("lt");
  else if( _c0 == BoolTest::gt ) st->print_raw("gt");
  else if( _c0 == BoolTest::overflow ) st->print_raw("o");
  else if( _c0 == BoolTest::no_overflow ) st->print_raw("no");
}
#endif
#ifndef PRODUCT
void stkI_to_regINode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("L       ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\t # stk reload int");
}
#endif
#ifndef PRODUCT
void regI_to_stkINode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("ST      ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(",");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw("\t # stk spill int");
}
#endif
#ifndef PRODUCT
void stkL_to_regLNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("LG      ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\t # stk reload long");
}
#endif
#ifndef PRODUCT
void regL_to_stkLNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("STG     ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(",");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw("\t # stk spill long");
}
#endif
#ifndef PRODUCT
void stkP_to_regPNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("LG      ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\t # stk reload ptr");
}
#endif
#ifndef PRODUCT
void regP_to_stkPNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("STG     ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(",");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw("\t # stk spill ptr");
}
#endif
#ifndef PRODUCT
void stkF_to_regFNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("LE(Y)   ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\t # stk reload float");
}
#endif
#ifndef PRODUCT
void regF_to_stkFNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("STE(Y)  ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(",");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw("\t # stk spill float");
}
#endif
#ifndef PRODUCT
void stkD_to_regDNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("LD(Y)   ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\t # stk reload double");
}
#endif
#ifndef PRODUCT
void regD_to_stkDNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("STD(Y)  ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(",");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw("\t # stk spill double");
}
#endif
#ifndef PRODUCT
void loadBNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  st->print_raw("LB      ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("\t # sign-extend byte to int");
  if (ra->C->alias_type(adr_type())->field() != NULL) {
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
  st->print_raw("LGB     ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("\t # sign-extend byte to long");
}
#endif
#ifndef PRODUCT
void loadUBNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  st->print_raw("LLGC    ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("\t # zero-extend byte to int");
  if (ra->C->alias_type(adr_type())->field() != NULL) {
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
  st->print_raw("LLGC    ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("\t # zero-extend byte to long");
}
#endif
#ifndef PRODUCT
void loadSNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  st->print_raw("LH(Y)   ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("\t # sign-extend short to int");
  if (ra->C->alias_type(adr_type())->field() != NULL) {
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
  st->print_raw("LGH     ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("\t # sign-extend short to long");
}
#endif
#ifndef PRODUCT
void loadUSNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  st->print_raw("LLGH    ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("\t # zero-extend short to int");
  if (ra->C->alias_type(adr_type())->field() != NULL) {
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
  st->print_raw("LLGH    ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("\t # zero-extend short to long");
}
#endif
#ifndef PRODUCT
void loadINode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  st->print_raw("L(Y)    ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("\t #");
  if (ra->C->alias_type(adr_type())->field() != NULL) {
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
  st->print_raw("LGF     ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("\t #");
}
#endif
#ifndef PRODUCT
void loadUI2LNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// mask
  st->print_raw("LLGF    ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("\t # zero-extend int to long");
}
#endif
#ifndef PRODUCT
void loadRangeNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  st->print_raw("L(Y)    ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("\t # range");
  if (ra->C->alias_type(adr_type())->field() != NULL) {
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
void loadLNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  st->print_raw("LG      ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("\t # long");
  if (ra->C->alias_type(adr_type())->field() != NULL) {
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
void loadL_unalignedNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  st->print_raw("LG      ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("\t # unaligned long");
  if (ra->C->alias_type(adr_type())->field() != NULL) {
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
  st->print_raw("LG      ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("\t # ptr");
  if (ra->C->alias_type(adr_type())->field() != NULL) {
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
void castP2X_loadPNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  st->print_raw("LG      ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("\t # ptr + p2x");
}
#endif
#ifndef PRODUCT
void loadKlassNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  st->print_raw("LG      ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("\t # klass ptr");
  if (ra->C->alias_type(adr_type())->field() != NULL) {
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
void loadTOCNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// 
  st->print_raw("LARL    ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", &constant_pool\t; load dynTOC");
}
#endif
#ifndef PRODUCT
void loadFNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  st->print_raw("LE(Y)    ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  if (ra->C->alias_type(adr_type())->field() != NULL) {
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
  st->print_raw("LD(Y)    ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  if (ra->C->alias_type(adr_type())->field() != NULL) {
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
void loadD_unalignedNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  st->print_raw("LD(Y)    ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  if (ra->C->alias_type(adr_type())->field() != NULL) {
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
  st->print_raw("LGFI     ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\t # (int)");
}
#endif
#ifndef PRODUCT
void loadConI16Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("LGHI     ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\t # (int)");
}
#endif
#ifndef PRODUCT
void loadConI_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("loadConI ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\t # (int) XGR because ZERO is loaded");
}
#endif
#ifndef PRODUCT
void loadConUI16Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("LLILL    ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
}
#endif
#ifndef PRODUCT
void loadConL_pcrelTOCNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("LGRL    ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",[pcrelTOC]\t # load long ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(" from table");
}
#endif
#ifndef PRODUCT
void loadConL32Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("LGFI     ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\t # (long)");
}
#endif
#ifndef PRODUCT
void loadConL16Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("LGHI     ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\t # (long)");
}
#endif
#ifndef PRODUCT
void loadConL_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("LoadConL    ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\t # (long) XGR because ZERO is loaded");
}
#endif
#ifndef PRODUCT
void loadConP_pcrelTOCNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("LGRL    ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",[pcrelTOC]\t # load ptr ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(" from table");
}
#endif
#ifndef PRODUCT
void loadConP0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("XGR     ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw("\t # NULL ptr");
}
#endif
#ifndef PRODUCT
void loadConF_dynTOCNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("LE(Y)    ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  st->print("#%d", constant_offset_unchecked());
  st->print_raw("[,");
  char reg[128];  ra->dump_register(in(mach_constant_base_node_input()), reg);
    st->print("%s", reg);
  st->print_raw("]\t # load FLOAT ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(" from table");
}
#endif
#ifndef PRODUCT
void loadConD_dynTOCNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("LD(Y)    ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  st->print("#%d", constant_offset_unchecked());
  st->print_raw("[,");
  char reg[128];  ra->dump_register(in(mach_constant_base_node_input()), reg);
    st->print("%s", reg);
  st->print_raw("]\t # load DOUBLE ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(" from table");
}
#endif
#ifndef PRODUCT
void loadConF0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("LZER     ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\t # clear to zero");
}
#endif
#ifndef PRODUCT
void loadConD0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("LZDR     ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\t # clear to zero");
}
#endif
#ifndef PRODUCT
void storeBNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  st->print_raw("STC(Y)  ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("\t # byte");
  if (ra->C->alias_type(adr_type())->field() != NULL) {
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
void storeCMNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  st->print_raw("STC(Y)  ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("\t # CMS card-mark byte (must be 0!)");
  if (ra->C->alias_type(adr_type())->field() != NULL) {
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
  st->print_raw("STH(Y)  ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("\t # short");
  if (ra->C->alias_type(adr_type())->field() != NULL) {
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
  st->print_raw("ST(Y)   ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("\t # int");
  if (ra->C->alias_type(adr_type())->field() != NULL) {
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
  st->print_raw("STG     ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("\t # long");
  if (ra->C->alias_type(adr_type())->field() != NULL) {
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
  unsigned idx1 = 2; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  st->print_raw("STG     ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst
  st->print_raw("\t # ptr");
  if (ra->C->alias_type(adr_type())->field() != NULL) {
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
  st->print_raw("STE(Y)   ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("\t # float");
  if (ra->C->alias_type(adr_type())->field() != NULL) {
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
  st->print_raw("STD(Y)   ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("\t # double");
  if (ra->C->alias_type(adr_type())->field() != NULL) {
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
void prefetchAllocNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// 
  st->print_raw("PREFETCH 2, ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("\t # Prefetch allocation, z10 only");
}
#endif
#ifndef PRODUCT
void memInitBNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  st->print_raw("MVI     ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
  st->print_raw("\t # direct mem init 1");
  if (ra->C->alias_type(adr_type())->field() != NULL) {
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
void memInitCNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  st->print_raw("MVHHI   ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
  st->print_raw("\t # direct mem init 2");
  if (ra->C->alias_type(adr_type())->field() != NULL) {
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
void memInitINode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  st->print_raw("MVHI    ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
  st->print_raw("\t # direct mem init 4");
  if (ra->C->alias_type(adr_type())->field() != NULL) {
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
void memInitLNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  st->print_raw("MVGHI   ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
  st->print_raw("\t # direct mem init 8");
  if (ra->C->alias_type(adr_type())->field() != NULL) {
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
void memInitPNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  st->print_raw("MVGHI   ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
  st->print_raw("\t # direct mem init 8");
  if (ra->C->alias_type(adr_type())->field() != NULL) {
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
void negL_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// zero
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  st->print_raw("NEG     ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
  st->print_raw("\t # long");
}
#endif
#ifndef PRODUCT
void loadNNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  st->print_raw("LoadN  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("\t# (cOop)");
  if (ra->C->alias_type(adr_type())->field() != NULL) {
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
  st->print_raw("LoadNKlass ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("\t# (klass cOop)");
  if (ra->C->alias_type(adr_type())->field() != NULL) {
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
void loadConNNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("loadConN    ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\t # (cOop)");
}
#endif
#ifndef PRODUCT
void loadConN0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("loadConN    ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\t # (cOop) XGR because ZERO is loaded");
}
#endif
#ifndef PRODUCT
void loadConNKlassNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("loadConNKlass ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\t # (cKlass)");
}
#endif
#ifndef PRODUCT
void decodeLoadNNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  st->print_raw("DecodeLoadN  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("\t# (cOop Load+Decode)");
}
#endif
#ifndef PRODUCT
void decodeLoadNKlassNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  st->print_raw("DecodeLoadNKlass  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("\t# (load/decode NKlass)");
}
#endif
#ifndef PRODUCT
void decodeLoadConNKlassNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("DecodeLoadConNKlass  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\t # decode(cKlass)");
}
#endif
#ifndef PRODUCT
void decodeNNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("decodeN  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\t# (decode cOop)");
}
#endif
#ifndef PRODUCT
void decodeKlassNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("decode_klass ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
}
#endif
#ifndef PRODUCT
void decodeN_NNNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("decodeN  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\t# (decode cOop NN)");
}
#endif
#ifndef PRODUCT
void loadBaseNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// baseImm
  st->print_raw("llihl    ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw("=");
  opnd_array(1)->ext_format(ra, this,idx1, st); // baseImm
  st->print_raw(" \t// load heap base");
}
#endif
#ifndef PRODUCT
void decodeN_baseNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// base
  st->print_raw("decodeN  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(" = (");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(" == 0) ? NULL : (");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(" << 3) + ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // base
  st->print_raw(" + pow2_offset\t# (decode cOop)");
}
#endif
#ifndef PRODUCT
void decodeN_NN_baseNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// base
  st->print_raw("decodeN  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(" = (");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(" << 3) + ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // base
  st->print_raw(" + pow2_offset\t# (decode cOop)");
}
#endif
#ifndef PRODUCT
void decodeN_ExNode::format(PhaseRegAlloc *ra, outputStream *st) const {
}
#endif
#ifndef PRODUCT
void decodeN_NN_ExNode::format(PhaseRegAlloc *ra, outputStream *st) const {
}
#endif
#ifndef PRODUCT
void encodePNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("encodeP  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\t# (encode cOop)");
}
#endif
#ifndef PRODUCT
void encodeKlassNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("encode_klass ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
}
#endif
#ifndef PRODUCT
void encodeP_NNNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("encodeP  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\t# (encode cOop)");
}
#endif
#ifndef PRODUCT
void encodeP_baseNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// base
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// dst
  st->print_raw("encodeP  ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // dst
  st->print_raw(" = (");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(">>3) +");
  opnd_array(2)->ext_format(ra, this,idx2, st); // base
  st->print_raw(" + pow2_offset\t# (encode cOop)");
}
#endif
#ifndef PRODUCT
void encodeP_NN_baseNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// base
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// pow2_offset
  st->print_raw("encodeP  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(" = (");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(">>3) +");
  opnd_array(2)->ext_format(ra, this,idx2, st); // base
  st->print_raw(" + ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // pow2_offset
  st->print_raw("\t# (encode cOop)");
}
#endif
#ifndef PRODUCT
void encodeP_ExNode::format(PhaseRegAlloc *ra, outputStream *st) const {
}
#endif
#ifndef PRODUCT
void encodeP_NN_ExNode::format(PhaseRegAlloc *ra, outputStream *st) const {
}
#endif
#ifndef PRODUCT
void storeNNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  st->print_raw("ST      ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("\t# (cOop)");
  if (ra->C->alias_type(adr_type())->field() != NULL) {
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
  st->print_raw("ST      ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("\t# (cKlass)");
  if (ra->C->alias_type(adr_type())->field() != NULL) {
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
void compN_iRegNNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("CLR     ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw("\t# (cOop)");
}
#endif
#ifndef PRODUCT
void compN_iRegN_immNNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("CLFI    ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw("\t# (cOop) compare immediate narrow");
}
#endif
#ifndef PRODUCT
void compNKlass_iRegN_immNNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("CLFI    ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw("\t# (NKlass) compare immediate narrow");
}
#endif
#ifndef PRODUCT
void compN_iRegN_immN0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("LTR     ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw("\t# (cOop) LTR because comparing against zero");
}
#endif
#ifndef PRODUCT
void membar_acquireNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  st->print_raw("MEMBAR-acquire");
}
#endif
#ifndef PRODUCT
void membar_acquire_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  st->print_raw("MEMBAR-acquire");
}
#endif
#ifndef PRODUCT
void membar_acquire_lockNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  st->print_raw("MEMBAR-acquire (CAS in prior FastLock so empty encoding)");
}
#endif
#ifndef PRODUCT
void membar_releaseNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  st->print_raw("MEMBAR-release");
}
#endif
#ifndef PRODUCT
void membar_release_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  st->print_raw("MEMBAR-release");
}
#endif
#ifndef PRODUCT
void membar_release_lockNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  st->print_raw("MEMBAR-release (CAS in succeeding FastUnlock so empty encoding)");
}
#endif
#ifndef PRODUCT
void membar_volatileNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  st->print_raw("MEMBAR-volatile");
}
#endif
#ifndef PRODUCT
void unnecessary_membar_volatileNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  st->print_raw("# MEMBAR-volatile (empty)");
}
#endif
#ifndef PRODUCT
void membar_CPUOrderNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  st->print_raw("MEMBAR-CPUOrder (empty)");
}
#endif
#ifndef PRODUCT
void membar_storestoreNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  st->print_raw("MEMBAR-storestore (empty)");
}
#endif
#ifndef PRODUCT
void roundDouble_nopNode::format(PhaseRegAlloc *ra, outputStream *st) const {
}
#endif
#ifndef PRODUCT
void roundFloat_nopNode::format(PhaseRegAlloc *ra, outputStream *st) const {
}
#endif
#ifndef PRODUCT
void castX2PNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("LGR     ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\t # CastX2P");
}
#endif
#ifndef PRODUCT
void castP2XNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("LGR     ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\t # CastP2X");
}
#endif
#ifndef PRODUCT
void stfSSDNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw(" STD   ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(",");
  opnd_array(0)->int_format(ra, this, st); // stkSlot
  st->print_raw("\t # stk");
}
#endif
#ifndef PRODUCT
void stfSSFNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("STE   ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(",");
  opnd_array(0)->int_format(ra, this, st); // stkSlot
  st->print_raw("\t # stk");
}
#endif
#ifndef PRODUCT
void cmovN_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// cmp
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// cr
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// dst
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src
  st->print_raw("CMoveN,");
  opnd_array(1)->ext_format(ra, this,idx1, st); // cmp
  st->print_raw("   ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // dst
  st->print_raw(",");
  opnd_array(4)->ext_format(ra, this,idx4, st); // src
}
#endif
#ifndef PRODUCT
void cmovN_immNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// cmp
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// cr
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// dst
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src
  st->print_raw("CMoveN,");
  opnd_array(1)->ext_format(ra, this,idx1, st); // cmp
  st->print_raw("   ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // dst
  st->print_raw(",");
  opnd_array(4)->ext_format(ra, this,idx4, st); // src
}
#endif
#ifndef PRODUCT
void cmovI_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// cmp
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// cr
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// dst
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src
  st->print_raw("CMoveI,");
  opnd_array(1)->ext_format(ra, this,idx1, st); // cmp
  st->print_raw("   ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // dst
  st->print_raw(",");
  opnd_array(4)->ext_format(ra, this,idx4, st); // src
}
#endif
#ifndef PRODUCT
void cmovI_immNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// cmp
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// cr
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// dst
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src
  st->print_raw("CMoveI,");
  opnd_array(1)->ext_format(ra, this,idx1, st); // cmp
  st->print_raw("   ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // dst
  st->print_raw(",");
  opnd_array(4)->ext_format(ra, this,idx4, st); // src
}
#endif
#ifndef PRODUCT
void cmovP_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// cmp
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// cr
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// dst
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src
  st->print_raw("CMoveP,");
  opnd_array(1)->ext_format(ra, this,idx1, st); // cmp
  st->print_raw("    ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // dst
  st->print_raw(",");
  opnd_array(4)->ext_format(ra, this,idx4, st); // src
}
#endif
#ifndef PRODUCT
void cmovP_immNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// cmp
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// cr
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// dst
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src
  st->print_raw("CMoveP,");
  opnd_array(1)->ext_format(ra, this,idx1, st); // cmp
  st->print_raw("  ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // dst
  st->print_raw(",");
  opnd_array(4)->ext_format(ra, this,idx4, st); // src
}
#endif
#ifndef PRODUCT
void cmovF_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// cmp
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// cr
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// dst
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src
  st->print_raw("CMoveF,");
  opnd_array(1)->ext_format(ra, this,idx1, st); // cmp
  st->print_raw("   ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // dst
  st->print_raw(",");
  opnd_array(4)->ext_format(ra, this,idx4, st); // src
}
#endif
#ifndef PRODUCT
void cmovD_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// cmp
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// cr
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// dst
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src
  st->print_raw("CMoveD,");
  opnd_array(1)->ext_format(ra, this,idx1, st); // cmp
  st->print_raw("   ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // dst
  st->print_raw(",");
  opnd_array(4)->ext_format(ra, this,idx4, st); // src
}
#endif
#ifndef PRODUCT
void cmovL_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// cmp
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// cr
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// dst
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src
  st->print_raw("CMoveL,");
  opnd_array(1)->ext_format(ra, this,idx1, st); // cmp
  st->print_raw("  ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // dst
  st->print_raw(",");
  opnd_array(4)->ext_format(ra, this,idx4, st); // src
}
#endif
#ifndef PRODUCT
void cmovL_immNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// cmp
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// cr
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// dst
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src
  st->print_raw("CMoveL,");
  opnd_array(1)->ext_format(ra, this,idx1, st); // cmp
  st->print_raw("  ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // dst
  st->print_raw(",");
  opnd_array(4)->ext_format(ra, this,idx4, st); // src
}
#endif
#ifndef PRODUCT
void tlsLoadPNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// 
  st->print_raw("# ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw("=ThreadLocal");
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
void loadPLockedNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  st->print_raw("LG      ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("\t # LoadPLocked");
  if (ra->C->alias_type(adr_type())->field() != NULL) {
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
void storePConditionalNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem_ptr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// oldval
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// newval
  st->print_raw("storePConditional ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // oldval
  st->print_raw(",");
  opnd_array(3)->ext_format(ra, this,idx3, st); // newval
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem_ptr
}
#endif
#ifndef PRODUCT
void storeLConditionalNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem_ptr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// oldval
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// newval
  st->print_raw("storePConditional ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // oldval
  st->print_raw(",");
  opnd_array(3)->ext_format(ra, this,idx3, st); // newval
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem_ptr
}
#endif
#ifndef PRODUCT
void compareAndSwapI_boolNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem_ptr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// oldval
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// newval
  opnd_array(0)->int_format(ra, this, st); // res
  st->print_raw(" = CompareAndSwapI ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // oldval
  st->print_raw(",");
  opnd_array(3)->ext_format(ra, this,idx3, st); // newval
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem_ptr
}
#endif
#ifndef PRODUCT
void compareAndSwapL_boolNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem_ptr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// oldval
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// newval
  opnd_array(0)->int_format(ra, this, st); // res
  st->print_raw(" = CompareAndSwapL ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // oldval
  st->print_raw(",");
  opnd_array(3)->ext_format(ra, this,idx3, st); // newval
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem_ptr
}
#endif
#ifndef PRODUCT
void compareAndSwapP_boolNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem_ptr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// oldval
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// newval
  opnd_array(0)->int_format(ra, this, st); // res
  st->print_raw(" = CompareAndSwapP ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // oldval
  st->print_raw(",");
  opnd_array(3)->ext_format(ra, this,idx3, st); // newval
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem_ptr
}
#endif
#ifndef PRODUCT
void compareAndSwapN_boolNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem_ptr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// oldval
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// newval
  opnd_array(0)->int_format(ra, this, st); // res
  st->print_raw(" = CompareAndSwapN ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // oldval
  st->print_raw(",");
  opnd_array(3)->ext_format(ra, this,idx3, st); // newval
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem_ptr
}
#endif
#ifndef PRODUCT
void addI_mem_imm8_atomic_no_resNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  st->print_raw("ASI     [");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("],");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
  st->print_raw("\t # GetAndAddI (atomic)");
}
#endif
#ifndef PRODUCT
void addI_mem_imm16_atomicNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// dst
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// tmp
  st->print_raw("BEGIN ATOMIC {\n\t");
  st->print_raw("  LGF     ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // dst
  st->print_raw(",[");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("]\n\t");
  st->print_raw("  AHIK    ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // tmp
  st->print_raw(",");
  opnd_array(3)->ext_format(ra, this,idx3, st); // dst
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
  st->print_raw("\n\t");
  st->print_raw("  CSY     ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // dst
  st->print_raw(",");
  opnd_array(4)->ext_format(ra, this,idx4, st); // tmp
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("\n\t");
  st->print_raw("  retry if failed\n\t");
  st->print_raw("} END ATOMIC");
}
#endif
#ifndef PRODUCT
void addI_mem_imm32_atomicNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// dst
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// tmp
  st->print_raw("BEGIN ATOMIC {\n\t");
  st->print_raw("  LGF     ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // dst
  st->print_raw(",[");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("]\n\t");
  st->print_raw("  LGR     ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // tmp
  st->print_raw(",");
  opnd_array(3)->ext_format(ra, this,idx3, st); // dst
  st->print_raw("\n\t");
  st->print_raw("  AFI     ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // tmp
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
  st->print_raw("\n\t");
  st->print_raw("  CSY     ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // dst
  st->print_raw(",");
  opnd_array(4)->ext_format(ra, this,idx4, st); // tmp
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("\n\t");
  st->print_raw("  retry if failed\n\t");
  st->print_raw("} END ATOMIC");
}
#endif
#ifndef PRODUCT
void addI_mem_reg_atomicNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// dst
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// tmp
  st->print_raw("BEGIN ATOMIC {\n\t");
  st->print_raw("  LGF     ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // dst
  st->print_raw(",[");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("]\n\t");
  st->print_raw("  ARK     ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // tmp
  st->print_raw(",");
  opnd_array(3)->ext_format(ra, this,idx3, st); // dst
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
  st->print_raw("\n\t");
  st->print_raw("  CSY     ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // dst
  st->print_raw(",");
  opnd_array(4)->ext_format(ra, this,idx4, st); // tmp
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("\n\t");
  st->print_raw("  retry if failed\n\t");
  st->print_raw("} END ATOMIC");
}
#endif
#ifndef PRODUCT
void addL_mem_imm8_atomic_no_resNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  st->print_raw("AGSI    [");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("],");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
  st->print_raw("\t # GetAndAddL (atomic)");
}
#endif
#ifndef PRODUCT
void addL_mem_imm16_atomicNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// dst
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// tmp
  st->print_raw("BEGIN ATOMIC {\n\t");
  st->print_raw("  LG      ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // dst
  st->print_raw(",[");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("]\n\t");
  st->print_raw("  AGHIK   ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // tmp
  st->print_raw(",");
  opnd_array(3)->ext_format(ra, this,idx3, st); // dst
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
  st->print_raw("\n\t");
  st->print_raw("  CSG     ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // dst
  st->print_raw(",");
  opnd_array(4)->ext_format(ra, this,idx4, st); // tmp
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("\n\t");
  st->print_raw("  retry if failed\n\t");
  st->print_raw("} END ATOMIC");
}
#endif
#ifndef PRODUCT
void addL_mem_imm32_atomicNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// dst
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// tmp
  st->print_raw("BEGIN ATOMIC {\n\t");
  st->print_raw("  LG      ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // dst
  st->print_raw(",[");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("]\n\t");
  st->print_raw("  LGR     ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // tmp
  st->print_raw(",");
  opnd_array(3)->ext_format(ra, this,idx3, st); // dst
  st->print_raw("\n\t");
  st->print_raw("  AGFI    ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // tmp
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
  st->print_raw("\n\t");
  st->print_raw("  CSG     ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // dst
  st->print_raw(",");
  opnd_array(4)->ext_format(ra, this,idx4, st); // tmp
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("\n\t");
  st->print_raw("  retry if failed\n\t");
  st->print_raw("} END ATOMIC");
}
#endif
#ifndef PRODUCT
void addL_mem_reg_atomicNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// dst
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// tmp
  st->print_raw("BEGIN ATOMIC {\n\t");
  st->print_raw("  LG      ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // dst
  st->print_raw(",[");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("]\n\t");
  st->print_raw("  AGRK    ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // tmp
  st->print_raw(",");
  opnd_array(3)->ext_format(ra, this,idx3, st); // dst
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
  st->print_raw("\n\t");
  st->print_raw("  CSG     ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // dst
  st->print_raw(",");
  opnd_array(4)->ext_format(ra, this,idx4, st); // tmp
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("\n\t");
  st->print_raw("  retry if failed\n\t");
  st->print_raw("} END ATOMIC");
}
#endif
#ifndef PRODUCT
void addI_mem_reg_atomic_z196Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  st->print_raw("LAA     ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
  st->print_raw(",[");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("]");
}
#endif
#ifndef PRODUCT
void addL_mem_reg_atomic_z196Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  st->print_raw("LAAG    ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
  st->print_raw(",[");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("]");
}
#endif
#ifndef PRODUCT
void xchgI_reg_memNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// tmp
  st->print_raw("XCHGI   ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // dst
  st->print_raw(",[");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("]\t # EXCHANGE (int, atomic), temp ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // tmp
}
#endif
#ifndef PRODUCT
void xchgL_reg_memNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// tmp
  st->print_raw("XCHGL   ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // dst
  st->print_raw(",[");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("]\t # EXCHANGE (long, atomic), temp ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // tmp
}
#endif
#ifndef PRODUCT
void xchgN_reg_memNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// tmp
  st->print_raw("XCHGN   ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // dst
  st->print_raw(",[");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("]\t # EXCHANGE (coop, atomic), temp ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // tmp
}
#endif
#ifndef PRODUCT
void xchgP_reg_memNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// tmp
  st->print_raw("XCHGP   ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // dst
  st->print_raw(",[");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("]\t # EXCHANGE (oop, atomic), temp ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // tmp
}
#endif
#ifndef PRODUCT
void addI_reg_reg_CISCNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  st->print_raw("AR      ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
  st->print_raw("\t # int  CISC ALU");
}
#endif
#ifndef PRODUCT
void addI_reg_reg_RISCNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("ARK     ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw("\t # int  RISC ALU");
}
#endif
#ifndef PRODUCT
void addI_reg_imm16_CISCNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// con
  st->print_raw("AHI     ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // con
  st->print_raw("\t # int  CISC ALU");
}
#endif
#ifndef PRODUCT
void addI_reg_imm16_RISCNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// con
  st->print_raw("AHIK    ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // con
  st->print_raw("\t # int  RISC ALU");
}
#endif
#ifndef PRODUCT
void addI_reg_imm32Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  st->print_raw("AFI     ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
}
#endif
#ifndef PRODUCT
void addI_reg_imm12Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// con
  st->print_raw("LA      ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // con
  st->print_raw("(,");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(")\t # int d12(,b)");
}
#endif
#ifndef PRODUCT
void addI_reg_imm20Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// con
  st->print_raw("LAY     ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // con
  st->print_raw("(,");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(")\t # int d20(,b)");
}
#endif
#ifndef PRODUCT
void addI_reg_reg_imm12Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// con
  st->print_raw("LA      ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(3)->ext_format(ra, this,idx3, st); // con
  st->print_raw("(");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(")\t # int d12(x,b)");
}
#endif
#ifndef PRODUCT
void addI_reg_reg_imm20Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// con
  st->print_raw("LAY     ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(3)->ext_format(ra, this,idx3, st); // con
  st->print_raw("(");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(")\t # int d20(x,b)");
}
#endif
#ifndef PRODUCT
void addI_Reg_memNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  st->print_raw("A(Y)    ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
  st->print_raw("\t # int");
}
#endif
#ifndef PRODUCT
void addI_Reg_mem_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst
  st->print_raw("A(Y)    ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\t # int");
}
#endif
#ifndef PRODUCT
void addI_mem_immNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  st->print_raw("ASI     ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
  st->print_raw("\t # direct mem add 4");
  if (ra->C->alias_type(adr_type())->field() != NULL) {
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
void addL_reg_regINode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  st->print_raw("AGFR    ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
  st->print_raw("\t # long<-int CISC ALU");
}
#endif
#ifndef PRODUCT
void addL_reg_regI_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst
  st->print_raw("AGFR    ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // dst
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\t # long<-int CISC ALU");
}
#endif
#ifndef PRODUCT
void addL_reg_reg_CISCNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  st->print_raw("AGR     ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
  st->print_raw("\t # long CISC ALU");
}
#endif
#ifndef PRODUCT
void addL_reg_reg_RISCNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("AGRK    ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw("\t # long RISC ALU");
}
#endif
#ifndef PRODUCT
void addL_reg_imm12Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// con
  st->print_raw("LA      ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // con
  st->print_raw("(,");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(")\t # long d12(,b)");
}
#endif
#ifndef PRODUCT
void addL_reg_imm20Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// con
  st->print_raw("LAY     ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // con
  st->print_raw("(,");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(")\t # long d20(,b)");
}
#endif
#ifndef PRODUCT
void addL_reg_imm32Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// con
  st->print_raw("AGFI    ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // con
  st->print_raw("\t # long CISC ALU");
}
#endif
#ifndef PRODUCT
void addL_reg_imm16_CISCNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// con
  st->print_raw("AGHI    ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // con
  st->print_raw("\t # long CISC ALU");
}
#endif
#ifndef PRODUCT
void addL_reg_imm16_RISCNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// con
  st->print_raw("AGHIK   ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // con
  st->print_raw("\t # long RISC ALU");
}
#endif
#ifndef PRODUCT
void addL_Reg_memINode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  st->print_raw("AGF     ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
  st->print_raw("\t # long/int");
}
#endif
#ifndef PRODUCT
void addL_Reg_memI_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst
  st->print_raw("AGF     ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\t # long/int");
}
#endif
#ifndef PRODUCT
void addL_Reg_memNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  st->print_raw("AG      ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
  st->print_raw("\t # long");
}
#endif
#ifndef PRODUCT
void addL_Reg_mem_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst
  st->print_raw("AG      ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\t # long");
}
#endif
#ifndef PRODUCT
void addL_reg_reg_imm12Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// con
  st->print_raw("LA     ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(3)->ext_format(ra, this,idx3, st); // con
  st->print_raw("(");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(")\t # long d12(x,b)");
}
#endif
#ifndef PRODUCT
void addL_reg_reg_imm20Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// con
  st->print_raw("LAY    ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(3)->ext_format(ra, this,idx3, st); // con
  st->print_raw("(");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(")\t # long d20(x,b)");
}
#endif
#ifndef PRODUCT
void addL_mem_immNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  st->print_raw("AGSI    ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
  st->print_raw("\t # direct mem add 8");
  if (ra->C->alias_type(adr_type())->field() != NULL) {
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
void addP_reg_reg_LANode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("LA      ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",#0(");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(")\t # ptr 0(x,b)");
}
#endif
#ifndef PRODUCT
void addP_reg_reg_CISCNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  st->print_raw("ALGR    ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
  st->print_raw("\t # ptr CICS ALU");
}
#endif
#ifndef PRODUCT
void addP_reg_reg_RISCNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("ALGRK   ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw("\t # ptr RISC ALU");
}
#endif
#ifndef PRODUCT
void addP_reg_imm12Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// con
  st->print_raw("LA      ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // con
  st->print_raw("(,");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(")\t # ptr d12(,b)");
}
#endif
#ifndef PRODUCT
void addP_reg_imm16_CISCNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  st->print_raw("AGHI    ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
  st->print_raw("\t # ptr CISC ALU");
}
#endif
#ifndef PRODUCT
void addP_reg_imm16_RISCNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// con
  st->print_raw("ALGHSIK ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // con
  st->print_raw("\t # ptr RISC ALU");
}
#endif
#ifndef PRODUCT
void addP_reg_imm20Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// con
  st->print_raw("LAY     ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // con
  st->print_raw("(,");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(")\t # ptr d20(,b)");
}
#endif
#ifndef PRODUCT
void addP_reg_imm32Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  st->print_raw("AGFI    ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
  st->print_raw("\t # ptr");
}
#endif
#ifndef PRODUCT
void addP_reg_reg_imm12Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// con
  st->print_raw("LA      ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(3)->ext_format(ra, this,idx3, st); // con
  st->print_raw("(");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(")\t # ptr d12(x,b)");
}
#endif
#ifndef PRODUCT
void addP_regN_reg_imm12Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// con
  st->print_raw("LA      ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(3)->ext_format(ra, this,idx3, st); // con
  st->print_raw("(");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(")\t # ptr d12(x,b)");
}
#endif
#ifndef PRODUCT
void addP_reg_reg_imm20Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// con
  st->print_raw("LAY     ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(3)->ext_format(ra, this,idx3, st); // con
  st->print_raw("(");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(")\t # ptr d20(x,b)");
}
#endif
#ifndef PRODUCT
void addP_regN_reg_imm20Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// con
  st->print_raw("LAY     ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(3)->ext_format(ra, this,idx3, st); // con
  st->print_raw("(");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(")\t # ptr d20(x,b)");
}
#endif
#ifndef PRODUCT
void addP_mem_immNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  st->print_raw("AGSI    ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
  st->print_raw("\t # direct mem add 8 (ptr)");
  if (ra->C->alias_type(adr_type())->field() != NULL) {
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
void subI_reg_reg_CISCNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  st->print_raw("SR      ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
  st->print_raw("\t # int  CISC ALU");
}
#endif
#ifndef PRODUCT
void subI_reg_reg_RISCNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("SRK     ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw("\t # int  RISC ALU");
}
#endif
#ifndef PRODUCT
void subI_Reg_memNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  st->print_raw("S(Y)    ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
  st->print_raw("\t # int");
}
#endif
#ifndef PRODUCT
void subI_zero_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// zero
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  st->print_raw("NEG     ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
}
#endif
#ifndef PRODUCT
void subL_reg_reg_CISCNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  st->print_raw("SGR     ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
  st->print_raw("\t # int  CISC ALU");
}
#endif
#ifndef PRODUCT
void subL_reg_reg_RISCNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("SGRK    ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw("\t # int  RISC ALU");
}
#endif
#ifndef PRODUCT
void subL_reg_regI_CISCNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  st->print_raw("SGFR    ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
  st->print_raw("\t # int  CISC ALU");
}
#endif
#ifndef PRODUCT
void subL_Reg_memINode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  st->print_raw("SGF     ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
  st->print_raw("\t # long/int");
}
#endif
#ifndef PRODUCT
void subL_Reg_memNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  st->print_raw("SG      ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
  st->print_raw("\t # long");
}
#endif
#ifndef PRODUCT
void mulI_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  st->print_raw("MSR     ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
}
#endif
#ifndef PRODUCT
void mulI_reg_imm16Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// con
  st->print_raw("MHI     ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // con
}
#endif
#ifndef PRODUCT
void mulI_reg_imm32Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// con
  st->print_raw("MSFI    ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // con
}
#endif
#ifndef PRODUCT
void mulI_Reg_memNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  st->print_raw("MS(Y)   ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
  st->print_raw("\t # int");
}
#endif
#ifndef PRODUCT
void mulI_Reg_mem_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst
  st->print_raw("MS(Y)   ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\t # int");
}
#endif
#ifndef PRODUCT
void mulL_reg_regINode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  st->print_raw("MSGFR   ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst
  st->print_raw(" ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
  st->print_raw("\t # long/int");
}
#endif
#ifndef PRODUCT
void mulL_reg_regI_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst
  st->print_raw("MSGFR   ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // dst
  st->print_raw(" ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\t # long/int");
}
#endif
#ifndef PRODUCT
void mulL_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  st->print_raw("MSGR    ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst
  st->print_raw(" ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
  st->print_raw("\t # long");
}
#endif
#ifndef PRODUCT
void mulL_reg_imm16Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  st->print_raw("MGHI    ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
  st->print_raw("\t # long");
}
#endif
#ifndef PRODUCT
void mulL_reg_imm32Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// con
  st->print_raw("MSGFI   ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // con
}
#endif
#ifndef PRODUCT
void mulL_Reg_memINode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  st->print_raw("MSGF    ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
  st->print_raw("\t # long");
}
#endif
#ifndef PRODUCT
void mulL_Reg_memI_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst
  st->print_raw("MSGF    ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\t # long");
}
#endif
#ifndef PRODUCT
void mulL_Reg_memNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  st->print_raw("MSG     ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
  st->print_raw("\t # long");
}
#endif
#ifndef PRODUCT
void mulL_Reg_mem_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst
  st->print_raw("MSG     ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\t # long");
}
#endif
#ifndef PRODUCT
void mulHiL_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// Rsrc1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// Rsrc2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// Rdst
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// Rtmp1
  st->print_raw("MulHiL  ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // Rdst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // Rsrc1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // Rsrc2
  st->print_raw("\t # Multiply High Long");
}
#endif
#ifndef PRODUCT
void divModI_reg_divmodNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src2
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst2
  st->print_raw("DIVMODI (");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst1src1
  st->print_raw(", ");
      st->print_raw("Z_R4");
  st->print_raw(") ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void divI_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("DIV_checked ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw("\t # treats special case 0x80../-1");
}
#endif
#ifndef PRODUCT
void divI_reg_imm16Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("DIV_const  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void divModL_reg_divmodNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src2
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst2
  st->print_raw("DIVMODL (");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst1src1
  st->print_raw(", ");
      st->print_raw("Z_R4");
  st->print_raw(") ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void divL_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  st->print_raw("DIVG_checked  ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
  st->print_raw("\t # long, treats special case 0x80../-1");
}
#endif
#ifndef PRODUCT
void divL_reg_imm16Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("DIVG_const  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw("\t # long");
}
#endif
#ifndef PRODUCT
void modI_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("MOD_checked   ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void modI_reg_imm16Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("MOD_const  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",src1,");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void modL_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("MODG_checked   ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void modL_reg_imm16Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("MODG_const  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",src1,");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw("\t # long");
}
#endif
#ifndef PRODUCT
void sllI_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// nbits
  st->print_raw("SLL     ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(",[");
  opnd_array(2)->ext_format(ra, this,idx2, st); // nbits
  st->print_raw("] & 31\t# use RISC-like SLLG also for int");
}
#endif
#ifndef PRODUCT
void sllI_reg_immNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// nbits
  st->print_raw("SLL     ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // nbits
  st->print_raw("\t# use RISC-like SLLG also for int");
}
#endif
#ifndef PRODUCT
void sllI_reg_imm_1Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// nbits
  st->print_raw("LA      ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",#0(");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(")\t # SLL by 1 (int)");
}
#endif
#ifndef PRODUCT
void sllL_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// nbits
  st->print_raw("SLLG    ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(",[");
  opnd_array(2)->ext_format(ra, this,idx2, st); // nbits
  st->print_raw("]");
}
#endif
#ifndef PRODUCT
void sllL_reg_immNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// nbits
  st->print_raw("SLLG    ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // nbits
}
#endif
#ifndef PRODUCT
void sllL_reg_imm_1Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// nbits
  st->print_raw("LA      ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",#0(");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(")\t # SLLG by 1 (long)");
}
#endif
#ifndef PRODUCT
void sraI_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  st->print_raw("SRA     ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst
  st->print_raw(",[");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
  st->print_raw("] & 31");
}
#endif
#ifndef PRODUCT
void sraI_reg_immNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  st->print_raw("SRA     ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
}
#endif
#ifndef PRODUCT
void sraL_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("SRAG    ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(",[");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw("]");
}
#endif
#ifndef PRODUCT
void sraL_reg_immNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("SRAG    ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void srlI_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  st->print_raw("SRL     ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst
  st->print_raw(",[");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
  st->print_raw("] & 31");
}
#endif
#ifndef PRODUCT
void srlI_reg_immNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  st->print_raw("SRL     ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
}
#endif
#ifndef PRODUCT
void srlL_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("SRLG    ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(",[");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw("]");
}
#endif
#ifndef PRODUCT
void srlL_reg_immNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("SRLG    ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void srlP_reg_immNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("SRLG    ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw("\t # Cast ptr ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(" to long and shift");
}
#endif
#ifndef PRODUCT
void rotlI_reg_immI8Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// lshift
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// rshift
  st->print_raw("RLL     ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // lshift
  st->print_raw("\t # ROTL32");
}
#endif
#ifndef PRODUCT
void rotlI_reg_immI8_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// rshift
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// lshift
  st->print_raw("RLL     ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(",");
  opnd_array(3)->ext_format(ra, this,idx3, st); // lshift
  st->print_raw("\t # ROTL32");
}
#endif
#ifndef PRODUCT
void rotlL_reg_immI8Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// lshift
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// rshift
  st->print_raw("RLLG    ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // lshift
  st->print_raw("\t # ROTL64");
}
#endif
#ifndef PRODUCT
void rotlL_reg_immI8_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// rshift
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// lshift
  st->print_raw("RLLG    ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(",");
  opnd_array(3)->ext_format(ra, this,idx3, st); // lshift
  st->print_raw("\t # ROTL64");
}
#endif
#ifndef PRODUCT
void rotrI_reg_immI8Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// rshift
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// lshift
  st->print_raw("RLL     ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // rshift
  st->print_raw("\t # ROTR32");
}
#endif
#ifndef PRODUCT
void rotrI_reg_immI8_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// lshift
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// rshift
  st->print_raw("RLL     ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(",");
  opnd_array(3)->ext_format(ra, this,idx3, st); // rshift
  st->print_raw("\t # ROTR32");
}
#endif
#ifndef PRODUCT
void rotrL_reg_immI8Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// rshift
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// lshift
  st->print_raw("RLLG    ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // rshift
  st->print_raw("\t # ROTR64");
}
#endif
#ifndef PRODUCT
void rotrL_reg_immI8_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// lshift
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// rshift
  st->print_raw("RLLG    ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(",");
  opnd_array(3)->ext_format(ra, this,idx3, st); // rshift
  st->print_raw("\t # ROTR64");
}
#endif
#ifndef PRODUCT
void overflowAddI_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// op1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// op2
  st->print_raw("AR      ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // op1
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // op2
  st->print_raw("\t # overflow check int");
}
#endif
#ifndef PRODUCT
void overflowAddI_reg_immNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// op1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// op2
  st->print_raw("AR      ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // op1
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // op2
  st->print_raw("\t # overflow check int");
}
#endif
#ifndef PRODUCT
void overflowAddL_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// op1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// op2
  st->print_raw("AGR     ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // op1
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // op2
  st->print_raw("\t # overflow check long");
}
#endif
#ifndef PRODUCT
void overflowAddL_reg_immNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// op1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// op2
  st->print_raw("AGR     ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // op1
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // op2
  st->print_raw("\t # overflow check long");
}
#endif
#ifndef PRODUCT
void overflowSubI_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// op1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// op2
  st->print_raw("SR      ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // op1
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // op2
  st->print_raw("\t # overflow check int");
}
#endif
#ifndef PRODUCT
void overflowSubI_reg_immNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// op1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// op2
  st->print_raw("SR      ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // op1
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // op2
  st->print_raw("\t # overflow check int");
}
#endif
#ifndef PRODUCT
void overflowSubL_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// op1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// op2
  st->print_raw("SGR     ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // op1
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // op2
  st->print_raw("\t # overflow check long");
}
#endif
#ifndef PRODUCT
void overflowSubL_reg_immNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// op1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// op2
  st->print_raw("SGR     ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // op1
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // op2
  st->print_raw("\t # overflow check long");
}
#endif
#ifndef PRODUCT
void overflowNegI_rRegNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// zero
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// op2
  st->print_raw("NEG    ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // op2
  st->print_raw("\t# overflow check int");
}
#endif
#ifndef PRODUCT
void overflowNegL_rRegNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// zero
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// op2
  st->print_raw("NEGG    ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // op2
  st->print_raw("\t# overflow check long");
}
#endif
#ifndef PRODUCT
void addF_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  st->print_raw("AEBR     ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
}
#endif
#ifndef PRODUCT
void addF_reg_memNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  st->print_raw("AEB      ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
  st->print_raw("\t # floatMemory");
}
#endif
#ifndef PRODUCT
void addF_reg_mem_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst
  st->print_raw("AEB      ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // dst
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\t # floatMemory");
}
#endif
#ifndef PRODUCT
void addD_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  st->print_raw("ADBR     ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
}
#endif
#ifndef PRODUCT
void addD_reg_memNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  st->print_raw("ADB      ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
  st->print_raw("\t # doubleMemory");
}
#endif
#ifndef PRODUCT
void addD_reg_mem_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst
  st->print_raw("ADB      ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // dst
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\t # doubleMemory");
}
#endif
#ifndef PRODUCT
void subF_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  st->print_raw("SEBR     ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
}
#endif
#ifndef PRODUCT
void subF_reg_memNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  st->print_raw("SEB      ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
  st->print_raw("\t # floatMemory");
}
#endif
#ifndef PRODUCT
void subD_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  st->print_raw("SDBR     ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
}
#endif
#ifndef PRODUCT
void subD_reg_memNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  st->print_raw("SDB      ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
  st->print_raw("\t # doubleMemory");
}
#endif
#ifndef PRODUCT
void mulF_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  st->print_raw("MEEBR    ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
}
#endif
#ifndef PRODUCT
void mulF_reg_memNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  st->print_raw("MEEB     ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
  st->print_raw("\t # floatMemory");
}
#endif
#ifndef PRODUCT
void mulF_reg_mem_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst
  st->print_raw("MEEB     ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // dst
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\t # floatMemory");
}
#endif
#ifndef PRODUCT
void mulD_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  st->print_raw("MDBR     ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
}
#endif
#ifndef PRODUCT
void mulD_reg_memNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  st->print_raw("MDB      ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
  st->print_raw("\t # doubleMemory");
}
#endif
#ifndef PRODUCT
void mulD_reg_mem_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst
  st->print_raw("MDB      ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // dst
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\t # doubleMemory");
}
#endif
#ifndef PRODUCT
void maddF_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  st->print_raw("MAEBR    ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src1
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src2
}
#endif
#ifndef PRODUCT
void maddD_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  st->print_raw("MADBR    ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src1
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src2
}
#endif
#ifndef PRODUCT
void msubF_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  st->print_raw("MSEBR    ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src1
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src2
}
#endif
#ifndef PRODUCT
void msubD_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  st->print_raw("MSDBR    ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src1
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src2
}
#endif
#ifndef PRODUCT
void maddF_reg_memNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  st->print_raw("MAEB     ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src1
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src2
}
#endif
#ifndef PRODUCT
void maddD_reg_memNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  st->print_raw("MADB     ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src1
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src2
}
#endif
#ifndef PRODUCT
void msubF_reg_memNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  st->print_raw("MSEB     ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src1
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src2
}
#endif
#ifndef PRODUCT
void msubD_reg_memNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  st->print_raw("MSDB    ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src1
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src2
}
#endif
#ifndef PRODUCT
void maddF_mem_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  st->print_raw("MAEB     ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src1
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src2
}
#endif
#ifndef PRODUCT
void maddD_mem_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  st->print_raw("MADB     ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src1
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src2
}
#endif
#ifndef PRODUCT
void msubF_mem_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  st->print_raw("MSEB     ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src1
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src2
}
#endif
#ifndef PRODUCT
void msubD_mem_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  st->print_raw("MSDB    ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src1
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src2
}
#endif
#ifndef PRODUCT
void divF_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  st->print_raw("DEBR     ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
}
#endif
#ifndef PRODUCT
void divF_reg_memNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  st->print_raw("DEB      ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
  st->print_raw("\t # floatMemory");
}
#endif
#ifndef PRODUCT
void divD_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  st->print_raw("DDBR     ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
}
#endif
#ifndef PRODUCT
void divD_reg_memNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  st->print_raw("DDB      ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
  st->print_raw("\t # doubleMemory");
}
#endif
#ifndef PRODUCT
void absF_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("LPEBR    ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\t float");
}
#endif
#ifndef PRODUCT
void absD_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("LPDBR    ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\t double");
}
#endif
#ifndef PRODUCT
void nabsF_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("LNEBR    ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\t float");
}
#endif
#ifndef PRODUCT
void nabsD_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("LNDBR    ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\t double");
}
#endif
#ifndef PRODUCT
void negF_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("NegF     ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\t float");
}
#endif
#ifndef PRODUCT
void negD_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("NegD     ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\t double");
}
#endif
#ifndef PRODUCT
void sqrtF_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("SQEBR    ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
}
#endif
#ifndef PRODUCT
void sqrtD_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("SQDBR    ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
}
#endif
#ifndef PRODUCT
void sqrtF_memNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("SQEB     ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\t # floatMemory");
}
#endif
#ifndef PRODUCT
void sqrtD_memNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("SQDB     ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\t # doubleMemory");
}
#endif
#ifndef PRODUCT
void andI_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  st->print_raw("NR      ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
  st->print_raw("\t # int");
}
#endif
#ifndef PRODUCT
void andI_Reg_memNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  st->print_raw("N(Y)    ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
  st->print_raw("\t # int");
}
#endif
#ifndef PRODUCT
void andI_Reg_mem_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst
  st->print_raw("N(Y)    ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\t # int");
}
#endif
#ifndef PRODUCT
void andI_reg_uimm32Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  st->print_raw("NILF    ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
}
#endif
#ifndef PRODUCT
void andI_reg_uimmI_LH1Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  st->print_raw("NILH    ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
}
#endif
#ifndef PRODUCT
void andI_reg_uimmI_LL1Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  st->print_raw("NILL    ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
}
#endif
#ifndef PRODUCT
void andL_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  st->print_raw("NGR     ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
  st->print_raw("\t # long");
}
#endif
#ifndef PRODUCT
void andL_Reg_memNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  st->print_raw("NG      ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
  st->print_raw("\t # long");
}
#endif
#ifndef PRODUCT
void andL_Reg_mem_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst
  st->print_raw("NG      ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\t # long");
}
#endif
#ifndef PRODUCT
void andL_reg_uimmL_LL1Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  st->print_raw("NILL    ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
  st->print_raw("\t # long");
}
#endif
#ifndef PRODUCT
void andL_reg_uimmL_LH1Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  st->print_raw("NILH    ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
  st->print_raw("\t # long");
}
#endif
#ifndef PRODUCT
void andL_reg_uimmL_HL1Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  st->print_raw("NIHL    ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
  st->print_raw("\t # long");
}
#endif
#ifndef PRODUCT
void andL_reg_uimmL_HH1Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  st->print_raw("NIHH    ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
  st->print_raw("\t # long");
}
#endif
#ifndef PRODUCT
void orI_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  st->print_raw("OR      ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
}
#endif
#ifndef PRODUCT
void orI_Reg_memNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  st->print_raw("O(Y)    ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
  st->print_raw("\t # int");
}
#endif
#ifndef PRODUCT
void orI_Reg_mem_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst
  st->print_raw("O(Y)    ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\t # int");
}
#endif
#ifndef PRODUCT
void orI_reg_uimm16Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// con
  st->print_raw("OILL    ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // con
}
#endif
#ifndef PRODUCT
void orI_reg_uimm32Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// con
  st->print_raw("OILF    ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // con
}
#endif
#ifndef PRODUCT
void orL_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  st->print_raw("OGR      ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
  st->print_raw("\t # long");
}
#endif
#ifndef PRODUCT
void orL_Reg_memNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  st->print_raw("OG      ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
  st->print_raw("\t # long");
}
#endif
#ifndef PRODUCT
void orL_Reg_mem_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst
  st->print_raw("OG      ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\t # long");
}
#endif
#ifndef PRODUCT
void orL_reg_uimm16Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// con
  st->print_raw("OILL    ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // con
  st->print_raw("\t # long");
}
#endif
#ifndef PRODUCT
void orL_reg_uimm32Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// con
  st->print_raw("OILF    ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // con
  st->print_raw("\t # long");
}
#endif
#ifndef PRODUCT
void xorI_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  st->print_raw("XR      ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
}
#endif
#ifndef PRODUCT
void xorI_Reg_memNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  st->print_raw("X(Y)    ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
  st->print_raw("\t # int");
}
#endif
#ifndef PRODUCT
void xorI_Reg_mem_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst
  st->print_raw("X(Y)    ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\t # int");
}
#endif
#ifndef PRODUCT
void xorI_reg_uimm32Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  st->print_raw("XILF    ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
}
#endif
#ifndef PRODUCT
void xorL_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  st->print_raw("XGR     ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
  st->print_raw("\t # long");
}
#endif
#ifndef PRODUCT
void xorL_Reg_memNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  st->print_raw("XG      ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
  st->print_raw("\t # long");
}
#endif
#ifndef PRODUCT
void xorL_Reg_mem_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst
  st->print_raw("XG      ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\t # long");
}
#endif
#ifndef PRODUCT
void xorL_reg_uimm32Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// con
  st->print_raw("XILF    ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // con
  st->print_raw("\t # long");
}
#endif
#ifndef PRODUCT
void convI2BNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("convI2B ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
}
#endif
#ifndef PRODUCT
void convP2BNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("convP2B ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
}
#endif
#ifndef PRODUCT
void cmpLTMask_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  st->print_raw("Set ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst
  st->print_raw(" CmpLTMask ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
}
#endif
#ifndef PRODUCT
void cmpLTMask_reg_zeroNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// zero
  st->print_raw("Set ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst
  st->print_raw(" CmpLTMask ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // zero
}
#endif
#ifndef PRODUCT
void convD2F_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("LEDBR   ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
}
#endif
#ifndef PRODUCT
void convF2I_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("convF2I  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
}
#endif
#ifndef PRODUCT
void convD2I_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("convD2I  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
}
#endif
#ifndef PRODUCT
void convF2L_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("convF2L  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
}
#endif
#ifndef PRODUCT
void convD2L_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("convD2L  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
}
#endif
#ifndef PRODUCT
void convF2D_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("LDEBR   ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
}
#endif
#ifndef PRODUCT
void convF2D_memNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("LDEB    ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
}
#endif
#ifndef PRODUCT
void convI2D_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("CDFBR   ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
}
#endif
#ifndef PRODUCT
void convI2F_iregNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("CEFBR   ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\t # convert int to float");
}
#endif
#ifndef PRODUCT
void convI2L_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("LGFR    ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\t # int->long");
}
#endif
#ifndef PRODUCT
void convI2L_reg_zexNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// mask
  st->print_raw("LLGFR   ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(" \t # zero-extend int to long");
}
#endif
#ifndef PRODUCT
void convI2L_mem_zexNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// mask
  st->print_raw("LLGF    ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(" \t # zero-extend int to long");
}
#endif
#ifndef PRODUCT
void zeroExtend_longNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// mask
  st->print_raw("LLGFR   ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(" \t # zero-extend long to long");
}
#endif
#ifndef PRODUCT
void rShiftI16_lShiftI16_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// amount
  st->print_raw("LHR     ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\t short->int");
}
#endif
#ifndef PRODUCT
void rShiftI24_lShiftI24_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// amount
  st->print_raw("LBR     ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\t byte->int");
}
#endif
#ifndef PRODUCT
void MoveF2I_stack_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("L       ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\t # MoveF2I");
}
#endif
#ifndef PRODUCT
void MoveI2F_stack_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("LE      ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\t # MoveI2F");
}
#endif
#ifndef PRODUCT
void MoveD2L_stack_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("LG      ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(",");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw("\t # MoveD2L");
}
#endif
#ifndef PRODUCT
void MoveL2D_stack_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("LD      ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\t # MoveL2D");
}
#endif
#ifndef PRODUCT
void MoveI2F_reg_stackNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("ST      ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(",");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw("\t # MoveI2F");
}
#endif
#ifndef PRODUCT
void MoveD2L_reg_stackNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("STD     ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(",");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw("\t # MoveD2L");
}
#endif
#ifndef PRODUCT
void MoveL2D_reg_stackNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("STG     ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(",");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw("\t # MoveL2D");
}
#endif
#ifndef PRODUCT
void convL2F_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("CEGBR   ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
}
#endif
#ifndef PRODUCT
void convL2D_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("CDGBR   ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
}
#endif
#ifndef PRODUCT
void convL2I_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("LR      ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\t # long->int (if needed)");
}
#endif
#ifndef PRODUCT
void shrL_reg_imm6_L2INode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// cnt
  st->print_raw("SRAG    ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // cnt
}
#endif
#ifndef PRODUCT
void rangeCheck_iReg_uimmI16Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// length
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// index
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// labl
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// 
  st->print_raw("RangeCheck len=");
  opnd_array(2)->ext_format(ra, this,idx2, st); // length
  st->print_raw(" cmp=");
  opnd_array(1)->ext_format(ra, this,idx1, st); // cmp
  st->print_raw(" idx=");
  opnd_array(3)->ext_format(ra, this,idx3, st); // index
  st->print_raw(" => trap ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // labl
  st->print("  P=%f C=%f",_prob,_fcnt);
}
#endif
#ifndef PRODUCT
void rangeCheck_iReg_iRegNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// index
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// length
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// labl
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// cr
  st->print_raw("RangeCheck idx=");
  opnd_array(2)->ext_format(ra, this,idx2, st); // index
  st->print_raw(" cmp=");
  opnd_array(1)->ext_format(ra, this,idx1, st); // cmp
  st->print_raw(" len=");
  opnd_array(3)->ext_format(ra, this,idx3, st); // length
  st->print_raw(" => trap ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // labl
  st->print("  P=%f C=%f",_prob,_fcnt);
}
#endif
#ifndef PRODUCT
void rangeCheck_uimmI16_iRegNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// index
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// length
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// labl
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// 
  st->print_raw("RangeCheck idx=");
  opnd_array(2)->ext_format(ra, this,idx2, st); // index
  st->print_raw(" cmp=");
  opnd_array(1)->ext_format(ra, this,idx1, st); // cmp
  st->print_raw(" len= ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // length
  st->print_raw(" => trap ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // labl
  st->print("  P=%f C=%f",_prob,_fcnt);
}
#endif
#ifndef PRODUCT
void zeroCheckP_iReg_imm0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// value
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// zero
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// labl
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// 
  st->print_raw("ZeroCheckP value=");
  opnd_array(2)->ext_format(ra, this,idx2, st); // value
  st->print_raw(" cmp=");
  opnd_array(1)->ext_format(ra, this,idx1, st); // cmp
  st->print_raw(" zero=");
  opnd_array(3)->ext_format(ra, this,idx3, st); // zero
  st->print_raw(" => trap ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // labl
  st->print("  P=%f C=%f",_prob,_fcnt);
}
#endif
#ifndef PRODUCT
void zeroCheckN_iReg_imm0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// value
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// zero
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// labl
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// 
  st->print_raw("ZeroCheckN value=");
  opnd_array(2)->ext_format(ra, this,idx2, st); // value
  st->print_raw(" cmp=");
  opnd_array(1)->ext_format(ra, this,idx1, st); // cmp
  st->print_raw(" zero=");
  opnd_array(3)->ext_format(ra, this,idx3, st); // zero
  st->print_raw(" => trap ");
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
  st->print_raw("CR      ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // op1
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // op2
}
#endif
#ifndef PRODUCT
void compI_reg_immNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// op1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// op2
  st->print_raw("CFI     ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // op1
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // op2
}
#endif
#ifndef PRODUCT
void compI_reg_imm16Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// op1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// op2
  st->print_raw("CHI     ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // op1
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // op2
}
#endif
#ifndef PRODUCT
void compI_reg_imm0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// op1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// zero
  st->print_raw("LTR     ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // op1
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // op1
}
#endif
#ifndef PRODUCT
void compI_reg_memNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// op1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// op2
  st->print_raw("C(Y)    ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // op1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // op2
  st->print_raw("\t # int");
}
#endif
#ifndef PRODUCT
void compU_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// op1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// op2
  st->print_raw("CLR     ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // op1
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // op2
  st->print_raw("\t # unsigned");
}
#endif
#ifndef PRODUCT
void compU_reg_uimmNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// op1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// op2
  st->print_raw("CLFI    ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // op1
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // op2
  st->print_raw("\t # unsigned");
}
#endif
#ifndef PRODUCT
void compU_reg_memNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// op1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// op2
  st->print_raw("CL(Y)   ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // op1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // op2
  st->print_raw("\t # unsigned");
}
#endif
#ifndef PRODUCT
void compL_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// op1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// op2
  st->print_raw("CGR     ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // op1
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // op2
  st->print_raw("\t # long");
}
#endif
#ifndef PRODUCT
void compL_reg_regINode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// op1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// op2
  st->print_raw("CGFR    ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // op1
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // op2
  st->print_raw("\t # long/int");
}
#endif
#ifndef PRODUCT
void compL_reg_imm32Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// op1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// con
  st->print_raw("CGFI    ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // op1
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // con
}
#endif
#ifndef PRODUCT
void compL_reg_imm16Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// op1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// con
  st->print_raw("CGHI    ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // op1
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // con
}
#endif
#ifndef PRODUCT
void compL_reg_imm0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// op1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// con
  st->print_raw("LTGR    ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // op1
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // op1
}
#endif
#ifndef PRODUCT
void compL_conv_reg_imm0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// op1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// con
  st->print_raw("LTGFR    ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // op1
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // op1
}
#endif
#ifndef PRODUCT
void compL_reg_memNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  st->print_raw("CG      ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
  st->print_raw("\t # long");
}
#endif
#ifndef PRODUCT
void compL_reg_memINode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  st->print_raw("CGF     ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
  st->print_raw("\t # long/int");
}
#endif
#ifndef PRODUCT
void compUL_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// op1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// op2
  st->print_raw("CLGR    ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // op1
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // op2
  st->print_raw("\t # long");
}
#endif
#ifndef PRODUCT
void compUL_reg_imm32Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// op1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// con
  st->print_raw("CLGFI   ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // op1
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // con
}
#endif
#ifndef PRODUCT
void compP_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// op1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// op2
  st->print_raw("CLGR    ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // op1
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // op2
  st->print_raw("\t # ptr");
}
#endif
#ifndef PRODUCT
void compP_reg_imm0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// op1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// op2
  st->print_raw("LTGR    ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // op1
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // op1
  st->print_raw("\t # ptr");
}
#endif
#ifndef PRODUCT
void compP_decode_reg_imm0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// op1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// op2
  st->print_raw("LTR    ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // op1
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // op1
  st->print_raw("\t # ptr");
}
#endif
#ifndef PRODUCT
void compP_reg_memNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  st->print_raw("CLG     ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
  st->print_raw("\t # ptr");
}
#endif
#ifndef PRODUCT
void z196_minI_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("MinI ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(" ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw("\t MinI (z196 only)");
}
#endif
#ifndef PRODUCT
void z10_minI_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("MinI ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(" ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw("\t MinI (z10 only)");
}
#endif
#ifndef PRODUCT
void minI_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("MinI ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(" ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw("\t MinI");
}
#endif
#ifndef PRODUCT
void z196_minI_reg_imm32Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("MinI ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(" ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw("\t MinI const32 (z196 only)");
}
#endif
#ifndef PRODUCT
void minI_reg_imm32Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("MinI ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(" ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw("\t MinI const32");
}
#endif
#ifndef PRODUCT
void z196_minI_reg_imm16Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("MinI ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(" ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw("\t MinI const16 (z196 only)");
}
#endif
#ifndef PRODUCT
void minI_reg_imm16Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("MinI ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(" ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw("\t MinI const16");
}
#endif
#ifndef PRODUCT
void z10_minI_reg_imm8Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("MinI ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(" ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw("\t MinI const8 (z10 only)");
}
#endif
#ifndef PRODUCT
void z196_maxI_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("MaxI ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(" ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw("\t MaxI (z196 only)");
}
#endif
#ifndef PRODUCT
void z10_maxI_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("MaxI ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(" ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw("\t MaxI (z10 only)");
}
#endif
#ifndef PRODUCT
void maxI_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("MaxI ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(" ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw("\t MaxI");
}
#endif
#ifndef PRODUCT
void z196_maxI_reg_imm32Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("MaxI ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(" ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw("\t MaxI const32 (z196 only)");
}
#endif
#ifndef PRODUCT
void maxI_reg_imm32Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("MaxI ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(" ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw("\t MaxI const32");
}
#endif
#ifndef PRODUCT
void z196_maxI_reg_imm16Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("MaxI ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(" ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw("\t MaxI const16 (z196 only)");
}
#endif
#ifndef PRODUCT
void maxI_reg_imm16Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("MaxI ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(" ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw("\t MaxI const16");
}
#endif
#ifndef PRODUCT
void z10_maxI_reg_imm8Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("MaxI ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(" ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw("\t MaxI const8");
}
#endif
#ifndef PRODUCT
void absI_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("LPR     ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
}
#endif
#ifndef PRODUCT
void negabsI_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// zero
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  st->print_raw("LNR     ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
}
#endif
#ifndef PRODUCT
void cmpF_ccNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("FCMPcc   ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw("\t # float");
}
#endif
#ifndef PRODUCT
void cmpD_ccNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("FCMPcc   ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(" \t # double");
}
#endif
#ifndef PRODUCT
void cmpF_cc_memNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("FCMPcc_mem ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw("\t # floatMemory");
}
#endif
#ifndef PRODUCT
void cmpD_cc_memNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("DCMPcc_mem ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw("\t # doubleMemory");
}
#endif
#ifndef PRODUCT
void cmpF0_ccNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("LTEBR    ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw("\t # float");
}
#endif
#ifndef PRODUCT
void cmpD0_ccNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("LTDBR    ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(" \t # double");
}
#endif
#ifndef PRODUCT
void cmpF_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("CmpF3    ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void cmpD_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("CmpD3    ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void branchNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// 
  st->print_raw("BRU     ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // labl
}
#endif
#ifndef PRODUCT
void branchFarNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// 
  st->print_raw("BRUL   ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // labl
}
#endif
#ifndef PRODUCT
void branchConNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// cr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// lbl
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// 
  st->print_raw("branch_con_short,");
  opnd_array(1)->ext_format(ra, this,idx1, st); // cmp
  st->print_raw("   ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // cr
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // lbl
  st->print("  P=%f C=%f",_prob,_fcnt);
}
#endif
#ifndef PRODUCT
void branchConFarNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// cr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// lbl
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// 
  st->print_raw("branch_con_far,");
  opnd_array(1)->ext_format(ra, this,idx1, st); // cmp
  st->print_raw("   ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // cr
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // lbl
  st->print("  P=%f C=%f",_prob,_fcnt);
}
#endif
#ifndef PRODUCT
void branchLoopEndNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// cr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// labl
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// 
  st->print_raw("branch_con_short,");
  opnd_array(1)->ext_format(ra, this,idx1, st); // cmp
  st->print_raw("   ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // labl
  st->print_raw("\t # counted loop end");
  st->print("  P=%f C=%f",_prob,_fcnt);
}
#endif
#ifndef PRODUCT
void branchLoopEndFarNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// cr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// labl
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// 
  st->print_raw("branch_con_far,");
  opnd_array(1)->ext_format(ra, this,idx1, st); // cmp
  st->print_raw("   ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // labl
  st->print_raw("\t # counted loop end");
  st->print("  P=%f C=%f",_prob,_fcnt);
}
#endif
#ifndef PRODUCT
void testAndBranchLoopEnd_RegNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// labl
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// cr
  st->print_raw("test_and_branch_loop_end,");
  opnd_array(1)->ext_format(ra, this,idx1, st); // boolnode
  st->print_raw("  ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src1
  st->print_raw(",");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src2
  st->print_raw(",");
  opnd_array(4)->ext_format(ra, this,idx4, st); // labl
  st->print_raw("\t # counted loop end SHORT");
  st->print("  P=%f C=%f",_prob,_fcnt);
}
#endif
#ifndef PRODUCT
void cmpb_RegINode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// labl
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// cr
  st->print_raw("CRJ,");
  opnd_array(1)->ext_format(ra, this,idx1, st); // boolnode
  st->print_raw("  ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src1
  st->print_raw(",");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src2
  st->print_raw(",");
  opnd_array(4)->ext_format(ra, this,idx4, st); // labl
  st->print_raw("\t # SHORT");
  st->print("  P=%f C=%f",_prob,_fcnt);
}
#endif
#ifndef PRODUCT
void cmpbU_RegINode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// labl
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// cr
  st->print_raw("CLRJ,");
  opnd_array(1)->ext_format(ra, this,idx1, st); // boolnode
  st->print_raw("  ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src1
  st->print_raw(",");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src2
  st->print_raw(",");
  opnd_array(4)->ext_format(ra, this,idx4, st); // labl
  st->print_raw("\t # SHORT");
  st->print("  P=%f C=%f",_prob,_fcnt);
}
#endif
#ifndef PRODUCT
void cmpb_RegLNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// labl
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// cr
  st->print_raw("CGRJ,");
  opnd_array(1)->ext_format(ra, this,idx1, st); // boolnode
  st->print_raw(" ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src1
  st->print_raw(",");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src2
  st->print_raw(",");
  opnd_array(4)->ext_format(ra, this,idx4, st); // labl
  st->print_raw("\t # SHORT");
  st->print("  P=%f C=%f",_prob,_fcnt);
}
#endif
#ifndef PRODUCT
void cmpb_RegPPNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// labl
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// cr
  st->print_raw("CLGRJ,");
  opnd_array(1)->ext_format(ra, this,idx1, st); // boolnode
  st->print_raw(" ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src1
  st->print_raw(",");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src2
  st->print_raw(",");
  opnd_array(4)->ext_format(ra, this,idx4, st); // labl
  st->print_raw("\t # SHORT");
  st->print("  P=%f C=%f",_prob,_fcnt);
}
#endif
#ifndef PRODUCT
void cmpb_RegNNNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// labl
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// cr
  st->print_raw("CLGRJ,");
  opnd_array(1)->ext_format(ra, this,idx1, st); // boolnode
  st->print_raw(" ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src1
  st->print_raw(",");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src2
  st->print_raw(",");
  opnd_array(4)->ext_format(ra, this,idx4, st); // labl
  st->print_raw("\t # SHORT");
  st->print("  P=%f C=%f",_prob,_fcnt);
}
#endif
#ifndef PRODUCT
void testAndBranchLoopEnd_ImmNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// labl
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// cr
  st->print_raw("test_and_branch_loop_end,");
  opnd_array(1)->ext_format(ra, this,idx1, st); // boolnode
  st->print_raw("  ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src1
  st->print_raw(",");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src2
  st->print_raw(",");
  opnd_array(4)->ext_format(ra, this,idx4, st); // labl
  st->print_raw("\t # counted loop end SHORT");
  st->print("  P=%f C=%f",_prob,_fcnt);
}
#endif
#ifndef PRODUCT
void cmpb_RegI_immNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// labl
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// cr
  st->print_raw("CIJ,");
  opnd_array(1)->ext_format(ra, this,idx1, st); // boolnode
  st->print_raw("  ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src1
  st->print_raw(",");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src2
  st->print_raw(",");
  opnd_array(4)->ext_format(ra, this,idx4, st); // labl
  st->print_raw("\t # SHORT");
  st->print("  P=%f C=%f",_prob,_fcnt);
}
#endif
#ifndef PRODUCT
void cmpbU_RegI_immNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// labl
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// cr
  st->print_raw("CLIJ,");
  opnd_array(1)->ext_format(ra, this,idx1, st); // boolnode
  st->print_raw(" ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src1
  st->print_raw(",");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src2
  st->print_raw(",");
  opnd_array(4)->ext_format(ra, this,idx4, st); // labl
  st->print_raw("\t # SHORT");
  st->print("  P=%f C=%f",_prob,_fcnt);
}
#endif
#ifndef PRODUCT
void cmpb_RegL_immNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// labl
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// cr
  st->print_raw("CGIJ,");
  opnd_array(1)->ext_format(ra, this,idx1, st); // boolnode
  st->print_raw(" ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src1
  st->print_raw(",");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src2
  st->print_raw(",");
  opnd_array(4)->ext_format(ra, this,idx4, st); // labl
  st->print_raw("\t # SHORT");
  st->print("  P=%f C=%f",_prob,_fcnt);
}
#endif
#ifndef PRODUCT
void cmpb_RegP_immPNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// labl
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// cr
  st->print_raw("CLGIJ,");
  opnd_array(1)->ext_format(ra, this,idx1, st); // boolnode
  st->print_raw(" ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src1
  st->print_raw(",");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src2
  st->print_raw(",");
  opnd_array(4)->ext_format(ra, this,idx4, st); // labl
  st->print_raw("\t # SHORT");
  st->print("  P=%f C=%f",_prob,_fcnt);
}
#endif
#ifndef PRODUCT
void cmpb_RegN_immP0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// labl
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// cr
  st->print_raw("CLGIJ,");
  opnd_array(1)->ext_format(ra, this,idx1, st); // boolnode
  st->print_raw(" ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src1
  st->print_raw(",");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src2
  st->print_raw(",");
  opnd_array(4)->ext_format(ra, this,idx4, st); // labl
  st->print_raw("\t # SHORT");
  st->print("  P=%f C=%f",_prob,_fcnt);
}
#endif
#ifndef PRODUCT
void cmpb_RegN_immNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// labl
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// cr
  st->print_raw("CLGIJ,");
  opnd_array(1)->ext_format(ra, this,idx1, st); // boolnode
  st->print_raw(" ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src1
  st->print_raw(",");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src2
  st->print_raw(",");
  opnd_array(4)->ext_format(ra, this,idx4, st); // labl
  st->print_raw("\t # SHORT");
  st->print("  P=%f C=%f",_prob,_fcnt);
}
#endif
#ifndef PRODUCT
void testAndBranchLoopEnd_RegFarNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// labl
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// cr
  st->print_raw("test_and_branch_loop_end,");
  opnd_array(1)->ext_format(ra, this,idx1, st); // boolnode
  st->print_raw("  ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src1
  st->print_raw(",");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src2
  st->print_raw(",");
  opnd_array(4)->ext_format(ra, this,idx4, st); // labl
  st->print_raw("\t # counted loop end FAR");
  st->print("  P=%f C=%f",_prob,_fcnt);
}
#endif
#ifndef PRODUCT
void cmpb_RegI_FarNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// labl
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// cr
  st->print_raw("CRJ,");
  opnd_array(1)->ext_format(ra, this,idx1, st); // boolnode
  st->print_raw("   ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src1
  st->print_raw(",");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src2
  st->print_raw(",");
  opnd_array(4)->ext_format(ra, this,idx4, st); // labl
  st->print_raw("\t # FAR(substituted)");
  st->print("  P=%f C=%f",_prob,_fcnt);
}
#endif
#ifndef PRODUCT
void cmpbU_RegI_FarNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// labl
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// cr
  st->print_raw("CLRJ,");
  opnd_array(1)->ext_format(ra, this,idx1, st); // boolnode
  st->print_raw("   ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src1
  st->print_raw(",");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src2
  st->print_raw(",");
  opnd_array(4)->ext_format(ra, this,idx4, st); // labl
  st->print_raw("\t # FAR(substituted)");
  st->print("  P=%f C=%f",_prob,_fcnt);
}
#endif
#ifndef PRODUCT
void cmpb_RegL_FarNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// labl
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// cr
  st->print_raw("CGRJ,");
  opnd_array(1)->ext_format(ra, this,idx1, st); // boolnode
  st->print_raw("   ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src1
  st->print_raw(",");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src2
  st->print_raw(",");
  opnd_array(4)->ext_format(ra, this,idx4, st); // labl
  st->print_raw("\t # FAR(substituted)");
  st->print("  P=%f C=%f",_prob,_fcnt);
}
#endif
#ifndef PRODUCT
void cmpb_RegPP_FarNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// labl
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// cr
  st->print_raw("CLGRJ,");
  opnd_array(1)->ext_format(ra, this,idx1, st); // boolnode
  st->print_raw("   ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src1
  st->print_raw(",");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src2
  st->print_raw(",");
  opnd_array(4)->ext_format(ra, this,idx4, st); // labl
  st->print_raw("\t # FAR(substituted)");
  st->print("  P=%f C=%f",_prob,_fcnt);
}
#endif
#ifndef PRODUCT
void cmpb_RegNN_FarNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// labl
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// cr
  st->print_raw("CLGRJ,");
  opnd_array(1)->ext_format(ra, this,idx1, st); // boolnode
  st->print_raw("   ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src1
  st->print_raw(",");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src2
  st->print_raw(",");
  opnd_array(4)->ext_format(ra, this,idx4, st); // labl
  st->print_raw("\t # FAR(substituted)");
  st->print("  P=%f C=%f",_prob,_fcnt);
}
#endif
#ifndef PRODUCT
void testAndBranchLoopEnd_ImmFarNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// labl
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// cr
  st->print_raw("test_and_branch_loop_end,");
  opnd_array(1)->ext_format(ra, this,idx1, st); // boolnode
  st->print_raw("  ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src1
  st->print_raw(",");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src2
  st->print_raw(",");
  opnd_array(4)->ext_format(ra, this,idx4, st); // labl
  st->print_raw("\t # counted loop end FAR");
  st->print("  P=%f C=%f",_prob,_fcnt);
}
#endif
#ifndef PRODUCT
void cmpb_RegI_imm_FarNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// labl
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// cr
  st->print_raw("CIJ,");
  opnd_array(1)->ext_format(ra, this,idx1, st); // boolnode
  st->print_raw("   ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src1
  st->print_raw(",");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src2
  st->print_raw(",");
  opnd_array(4)->ext_format(ra, this,idx4, st); // labl
  st->print_raw("\t # FAR(substituted)");
  st->print("  P=%f C=%f",_prob,_fcnt);
}
#endif
#ifndef PRODUCT
void cmpbU_RegI_imm_FarNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// labl
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// cr
  st->print_raw("CLIJ,");
  opnd_array(1)->ext_format(ra, this,idx1, st); // boolnode
  st->print_raw("   ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src1
  st->print_raw(",");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src2
  st->print_raw(",");
  opnd_array(4)->ext_format(ra, this,idx4, st); // labl
  st->print_raw("\t # FAR(substituted)");
  st->print("  P=%f C=%f",_prob,_fcnt);
}
#endif
#ifndef PRODUCT
void cmpb_RegL_imm_FarNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// labl
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// cr
  st->print_raw("CGIJ,");
  opnd_array(1)->ext_format(ra, this,idx1, st); // boolnode
  st->print_raw("   ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src1
  st->print_raw(",");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src2
  st->print_raw(",");
  opnd_array(4)->ext_format(ra, this,idx4, st); // labl
  st->print_raw("\t # FAR(substituted)");
  st->print("  P=%f C=%f",_prob,_fcnt);
}
#endif
#ifndef PRODUCT
void cmpb_RegP_immP_FarNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// labl
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// cr
  st->print_raw("CLGIJ,");
  opnd_array(1)->ext_format(ra, this,idx1, st); // boolnode
  st->print_raw("   ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src1
  st->print_raw(",");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src2
  st->print_raw(",");
  opnd_array(4)->ext_format(ra, this,idx4, st); // labl
  st->print_raw("\t # FAR(substituted)");
  st->print("  P=%f C=%f",_prob,_fcnt);
}
#endif
#ifndef PRODUCT
void cmpb_RegN_immP0_FarNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// labl
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// cr
  st->print_raw("CLGIJ,");
  opnd_array(1)->ext_format(ra, this,idx1, st); // boolnode
  st->print_raw("   ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src1
  st->print_raw(",");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src2
  st->print_raw(",");
  opnd_array(4)->ext_format(ra, this,idx4, st); // labl
  st->print_raw("\t # FAR(substituted)");
  st->print("  P=%f C=%f",_prob,_fcnt);
}
#endif
#ifndef PRODUCT
void cmpb_RegN_immN_FarNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// labl
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// cr
  st->print_raw("CLGIJ,");
  opnd_array(1)->ext_format(ra, this,idx1, st); // boolnode
  st->print_raw("   ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src1
  st->print_raw(",");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src2
  st->print_raw(",");
  opnd_array(4)->ext_format(ra, this,idx4, st); // labl
  st->print_raw("\t # FAR(substituted)");
  st->print("  P=%f C=%f",_prob,_fcnt);
}
#endif
#ifndef PRODUCT
void cmpL3_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("CmpL3 ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void safePointNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  st->print_raw("UNIMPLEMENTED Safepoint_ ");
  st->print_raw("");
  if (_jvms) _jvms->format(ra, this, st); else st->print_cr("        No JVM State Info");
  st->print("        # ");
  if( _jvms && _oop_map ) _oop_map->print_on(st);
}
#endif
#ifndef PRODUCT
void safePoint_pollNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 5;
  unsigned idx1 = 5; 	// cr
  st->print_raw("TM      #0[,");
  opnd_array(1)->ext_format(ra, this,idx1, st); // poll
  st->print_raw("],#111\t # Safepoint: poll for GC");
  st->print_raw("");
  if (_jvms) _jvms->format(ra, this, st); else st->print_cr("        No JVM State Info");
  st->print("        # ");
  if( _jvms && _oop_map ) _oop_map->print_on(st);
}
#endif
#ifndef PRODUCT
void CallStaticJavaDirect_dynTOCNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// 
  st->print_raw("CALL,static dynTOC ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // meth
  st->print_raw("; ==> ");
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
void CallDynamicJavaDirect_dynTOCNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// 
  st->print_raw("CALL,dynamic dynTOC ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // meth
  st->print_raw("; ==> ");
  _method->print_short_name(st);
  st->cr();
  if (_jvms) _jvms->format(ra, this, st); else st->print_cr("        No JVM State Info");
  st->print("        # ");
  if( _jvms && _oop_map ) _oop_map->print_on(st);
}
#endif
#ifndef PRODUCT
void CallRuntimeDirectNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  st->print_raw("CALL,runtime");
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
  st->print_raw("CALL,runtime leaf ");
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
  st->print_raw("CALL,runtime leaf nofp ");
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
  unsigned idx1 = 5; 	// method_oop
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// 
  st->print_raw("Jmp     ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // jump_target
  st->print_raw("\t# ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // method_oop
  st->print_raw(" holds method oop");
}
#endif
#ifndef PRODUCT
void RetNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  st->print_raw("BR(Z_R14) // branch to link register");
}
#endif
#ifndef PRODUCT
void tailjmpIndNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 5;
  unsigned idx1 = 5; 	// ex_oop
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// 
  st->print_raw("TailJump ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // jump_target
}
#endif
#ifndef PRODUCT
void CreateExceptionNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  st->print_raw("# exception oop; no code emitted");
}
#endif
#ifndef PRODUCT
void RethrowExceptionNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  st->print_raw("Jmp    rethrow_stub");
}
#endif
#ifndef PRODUCT
void ShouldNotReachHereNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  st->print_raw("ILLTRAP; ShouldNotReachHere");
}
#endif
#ifndef PRODUCT
void partialSubtypeCheckNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  st->print_raw("  CALL   PartialSubtypeCheck\n");
}
#endif
#ifndef PRODUCT
void partialSubtypeCheck_vs_zeroNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  st->print_raw("CALL   PartialSubtypeCheck_vs_zero\n");
}
#endif
#ifndef PRODUCT
void cmpFastLockNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// oop
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// box
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// tmp1
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// tmp2
  st->print_raw("FASTLOCK  ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // oop
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // box
  st->print_raw("; KILL Z_ARG4, Z_ARG5");
}
#endif
#ifndef PRODUCT
void cmpFastUnlockNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// oop
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// box
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// tmp1
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// tmp2
  st->print_raw("FASTUNLOCK  ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // oop
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // box
  st->print_raw("; KILL Z_ARG4, Z_ARG5");
}
#endif
#ifndef PRODUCT
void inlineCallClearArrayConstNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// cnt
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// base
  st->print_raw("ClearArrayConst ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // cnt
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // base
}
#endif
#ifndef PRODUCT
void inlineCallClearArrayConstBigNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// cnt
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// base
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// srcA
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// srcL
  st->print_raw("ClearArrayConstBig ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // cnt
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // base
}
#endif
#ifndef PRODUCT
void inlineCallClearArrayNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// cnt
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// base
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// srcA
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// srcL
  st->print_raw("ClearArrayVar ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // cnt
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // base
}
#endif
#ifndef PRODUCT
void string_equalsLNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// str1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// str2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// cnt
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// oddReg
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// evenReg
  st->print_raw("String Equals byte[] ");
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
void string_equalsUNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// str1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// str2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// cnt
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// oddReg
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// evenReg
  st->print_raw("String Equals char[] ");
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
void string_equals_immNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// str1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// str2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// cnt
  st->print_raw("String Equals byte[] ");
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
void string_equalsC_immNode::format(PhaseRegAlloc *ra, outputStream *st) const {
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
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// oddReg
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// evenReg
  st->print_raw("Array Equals ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // ary1
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // ary2
  st->print_raw(" -> ");
  opnd_array(0)->int_format(ra, this, st); // result
}
#endif
#ifndef PRODUCT
void array_equalsCNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// ary1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// ary2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// oddReg
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// evenReg
  st->print_raw("Array Equals ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // ary1
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // ary2
  st->print_raw(" -> ");
  opnd_array(0)->int_format(ra, this, st); // result
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
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// result
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// oddReg
  unsigned idx7 = idx6 + opnd_array(6)->num_edges(); 	// evenReg
  st->print_raw("String Compare byte[] ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // str1
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // cnt1
  st->print_raw(",");
  opnd_array(3)->ext_format(ra, this,idx3, st); // str2
  st->print_raw(",");
  opnd_array(4)->ext_format(ra, this,idx4, st); // cnt2
  st->print_raw(" -> ");
  opnd_array(5)->ext_format(ra, this,idx5, st); // result
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
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// result
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// oddReg
  unsigned idx7 = idx6 + opnd_array(6)->num_edges(); 	// evenReg
  st->print_raw("String Compare char[] ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // str1
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // cnt1
  st->print_raw(",");
  opnd_array(3)->ext_format(ra, this,idx3, st); // str2
  st->print_raw(",");
  opnd_array(4)->ext_format(ra, this,idx4, st); // cnt2
  st->print_raw(" -> ");
  opnd_array(5)->ext_format(ra, this,idx5, st); // result
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
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// result
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// oddReg
  unsigned idx7 = idx6 + opnd_array(6)->num_edges(); 	// evenReg
  st->print_raw("String Compare byte[],char[] ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // str1
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // cnt1
  st->print_raw(",");
  opnd_array(3)->ext_format(ra, this,idx3, st); // str2
  st->print_raw(",");
  opnd_array(4)->ext_format(ra, this,idx4, st); // cnt2
  st->print_raw(" -> ");
  opnd_array(5)->ext_format(ra, this,idx5, st); // result
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
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// result
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// oddReg
  unsigned idx7 = idx6 + opnd_array(6)->num_edges(); 	// evenReg
  st->print_raw("String Compare char[],byte[] ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // str1
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // cnt1
  st->print_raw(",");
  opnd_array(3)->ext_format(ra, this,idx3, st); // str2
  st->print_raw(",");
  opnd_array(4)->ext_format(ra, this,idx4, st); // cnt2
  st->print_raw(" -> ");
  opnd_array(5)->ext_format(ra, this,idx5, st); // result
}
#endif
#ifndef PRODUCT
void indexOfChar_UNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// haystack
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// haycnt
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// ch
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// result
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// oddReg
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// evenReg
  st->print_raw("String IndexOfChar [0..");
  opnd_array(2)->ext_format(ra, this,idx2, st); // haycnt
  st->print_raw("](");
  opnd_array(1)->ext_format(ra, this,idx1, st); // haystack
  st->print_raw("), ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // ch
  st->print_raw(" -> ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // result
}
#endif
#ifndef PRODUCT
void indexOf_imm1_UNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// haystack
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// haycnt
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// needle
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// needlecnt
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// result
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// oddReg
  unsigned idx7 = idx6 + opnd_array(6)->num_edges(); 	// evenReg
  st->print_raw("String IndexOf UL [0..");
  opnd_array(2)->ext_format(ra, this,idx2, st); // haycnt
  st->print_raw("](");
  opnd_array(1)->ext_format(ra, this,idx1, st); // haystack
  st->print_raw("), [0](");
  opnd_array(3)->ext_format(ra, this,idx3, st); // needle
  st->print_raw(") -> ");
  opnd_array(5)->ext_format(ra, this,idx5, st); // result
}
#endif
#ifndef PRODUCT
void indexOf_imm1_LNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// haystack
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// haycnt
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// needle
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// needlecnt
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// result
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// oddReg
  unsigned idx7 = idx6 + opnd_array(6)->num_edges(); 	// evenReg
  st->print_raw("String IndexOf L [0..");
  opnd_array(2)->ext_format(ra, this,idx2, st); // haycnt
  st->print_raw("](");
  opnd_array(1)->ext_format(ra, this,idx1, st); // haystack
  st->print_raw("), [0](");
  opnd_array(3)->ext_format(ra, this,idx3, st); // needle
  st->print_raw(") -> ");
  opnd_array(5)->ext_format(ra, this,idx5, st); // result
}
#endif
#ifndef PRODUCT
void indexOf_imm1_ULNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// haystack
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// haycnt
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// needle
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// needlecnt
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// result
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// oddReg
  unsigned idx7 = idx6 + opnd_array(6)->num_edges(); 	// evenReg
  st->print_raw("String IndexOf UL [0..");
  opnd_array(2)->ext_format(ra, this,idx2, st); // haycnt
  st->print_raw("](");
  opnd_array(1)->ext_format(ra, this,idx1, st); // haystack
  st->print_raw("), [0](");
  opnd_array(3)->ext_format(ra, this,idx3, st); // needle
  st->print_raw(") -> ");
  opnd_array(5)->ext_format(ra, this,idx5, st); // result
}
#endif
#ifndef PRODUCT
void indexOf_imm_UNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// haystack
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// haycnt
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// needle
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// needlecntImm
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// result
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// oddReg
  unsigned idx7 = idx6 + opnd_array(6)->num_edges(); 	// evenReg
  st->print_raw("String IndexOf U [0..");
  opnd_array(4)->ext_format(ra, this,idx4, st); // needlecntImm
  st->print_raw("](");
  opnd_array(3)->ext_format(ra, this,idx3, st); // needle
  st->print_raw(") .in. [0..");
  opnd_array(2)->ext_format(ra, this,idx2, st); // haycnt
  st->print_raw("](");
  opnd_array(1)->ext_format(ra, this,idx1, st); // haystack
  st->print_raw(") -> ");
  opnd_array(5)->ext_format(ra, this,idx5, st); // result
}
#endif
#ifndef PRODUCT
void indexOf_imm_LNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// haystack
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// haycnt
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// needle
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// needlecntImm
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// result
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// oddReg
  unsigned idx7 = idx6 + opnd_array(6)->num_edges(); 	// evenReg
  st->print_raw("String IndexOf L [0..");
  opnd_array(4)->ext_format(ra, this,idx4, st); // needlecntImm
  st->print_raw("](");
  opnd_array(3)->ext_format(ra, this,idx3, st); // needle
  st->print_raw(") .in. [0..");
  opnd_array(2)->ext_format(ra, this,idx2, st); // haycnt
  st->print_raw("](");
  opnd_array(1)->ext_format(ra, this,idx1, st); // haystack
  st->print_raw(") -> ");
  opnd_array(5)->ext_format(ra, this,idx5, st); // result
}
#endif
#ifndef PRODUCT
void indexOf_imm_ULNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// haystack
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// haycnt
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// needle
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// needlecntImm
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// result
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// oddReg
  unsigned idx7 = idx6 + opnd_array(6)->num_edges(); 	// evenReg
  st->print_raw("String IndexOf UL [0..");
  opnd_array(4)->ext_format(ra, this,idx4, st); // needlecntImm
  st->print_raw("](");
  opnd_array(3)->ext_format(ra, this,idx3, st); // needle
  st->print_raw(") .in. [0..");
  opnd_array(2)->ext_format(ra, this,idx2, st); // haycnt
  st->print_raw("](");
  opnd_array(1)->ext_format(ra, this,idx1, st); // haystack
  st->print_raw(") -> ");
  opnd_array(5)->ext_format(ra, this,idx5, st); // result
}
#endif
#ifndef PRODUCT
void indexOf_UNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// haystack
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// haycnt
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// needle
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// needlecnt
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// result
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// oddReg
  unsigned idx7 = idx6 + opnd_array(6)->num_edges(); 	// evenReg
  st->print_raw("String IndexOf U [0..");
  opnd_array(4)->ext_format(ra, this,idx4, st); // needlecnt
  st->print_raw("](");
  opnd_array(3)->ext_format(ra, this,idx3, st); // needle
  st->print_raw(") .in. [0..");
  opnd_array(2)->ext_format(ra, this,idx2, st); // haycnt
  st->print_raw("](");
  opnd_array(1)->ext_format(ra, this,idx1, st); // haystack
  st->print_raw(") -> ");
  opnd_array(5)->ext_format(ra, this,idx5, st); // result
}
#endif
#ifndef PRODUCT
void indexOf_LNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// haystack
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// haycnt
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// needle
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// needlecnt
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// result
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// oddReg
  unsigned idx7 = idx6 + opnd_array(6)->num_edges(); 	// evenReg
  st->print_raw("String IndexOf L [0..");
  opnd_array(4)->ext_format(ra, this,idx4, st); // needlecnt
  st->print_raw("](");
  opnd_array(3)->ext_format(ra, this,idx3, st); // needle
  st->print_raw(") .in. [0..");
  opnd_array(2)->ext_format(ra, this,idx2, st); // haycnt
  st->print_raw("](");
  opnd_array(1)->ext_format(ra, this,idx1, st); // haystack
  st->print_raw(") -> ");
  opnd_array(5)->ext_format(ra, this,idx5, st); // result
}
#endif
#ifndef PRODUCT
void indexOf_ULNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// haystack
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// haycnt
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// needle
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// needlecnt
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// result
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// oddReg
  unsigned idx7 = idx6 + opnd_array(6)->num_edges(); 	// evenReg
  st->print_raw("String IndexOf UL [0..");
  opnd_array(4)->ext_format(ra, this,idx4, st); // needlecnt
  st->print_raw("](");
  opnd_array(3)->ext_format(ra, this,idx3, st); // needle
  st->print_raw(") .in. [0..");
  opnd_array(2)->ext_format(ra, this,idx2, st); // haycnt
  st->print_raw("](");
  opnd_array(1)->ext_format(ra, this,idx1, st); // haystack
  st->print_raw(") -> ");
  opnd_array(5)->ext_format(ra, this,idx5, st); // result
}
#endif
#ifndef PRODUCT
void string_compressNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// len
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// result
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// tmp
  st->print_raw("String Compress ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("->");
  opnd_array(2)->ext_format(ra, this,idx2, st); // dst
  st->print_raw("(");
  opnd_array(3)->ext_format(ra, this,idx3, st); // len
  st->print_raw(") -> ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // result
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
  st->print_raw("String Inflate ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("->");
  opnd_array(2)->ext_format(ra, this,idx2, st); // dst
  st->print_raw("(");
  opnd_array(3)->ext_format(ra, this,idx3, st); // len
  st->print_raw(")");
}
#endif
#ifndef PRODUCT
void string_inflate_constNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// len
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// tmp
  st->print_raw("String Inflate (constLen) ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("->");
  opnd_array(2)->ext_format(ra, this,idx2, st); // dst
  st->print_raw("(");
  opnd_array(3)->ext_format(ra, this,idx3, st); // len
  st->print_raw(")");
}
#endif
#ifndef PRODUCT
void has_negativesNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// ary1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// len
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// result
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// oddReg
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// evenReg
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// tmp
  st->print_raw("has negatives byte[] ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // ary1
  st->print_raw("(");
  opnd_array(2)->ext_format(ra, this,idx2, st); // len
  st->print_raw(") -> ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // result
}
#endif
#ifndef PRODUCT
void encode_iso_arrayNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// len
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// result
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// tmp
  st->print_raw("Encode array ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("->");
  opnd_array(2)->ext_format(ra, this,idx2, st); // dst
  st->print_raw("(");
  opnd_array(3)->ext_format(ra, this,idx3, st); // len
  st->print_raw(") -> ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // result
}
#endif
#ifndef PRODUCT
void expand_storeFNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("STE      ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(",");
  opnd_array(0)->int_format(ra, this, st); // mem
  st->print_raw("\t # replicate(float2stack)");
}
#endif
#ifndef PRODUCT
void expand_LoadLogical_I2LNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// mem
  st->print_raw("LLGF     ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("\t # replicate(stack2reg(unsigned))");
}
#endif
#ifndef PRODUCT
void expand_Repl2I_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("REPLIC2F ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\t # replicate(pack2F)");
}
#endif
#ifndef PRODUCT
void Repl8B_reg_risbgNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("REPLIC8B ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\t # pack8B");
}
#endif
#ifndef PRODUCT
void Repl8B_immNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("REPLIC8B ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\t # pack8B imm");
}
#endif
#ifndef PRODUCT
void Repl8B_imm0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("REPLIC8B ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\t # pack8B imm0");
}
#endif
#ifndef PRODUCT
void Repl8B_immm1Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("REPLIC8B ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\t # pack8B immm1");
}
#endif
#ifndef PRODUCT
void Repl4S_reg_risbgNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("REPLIC4S ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\t # pack4S");
}
#endif
#ifndef PRODUCT
void Repl4S_immNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("REPLIC4S ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\t # pack4S imm");
}
#endif
#ifndef PRODUCT
void Repl4S_imm0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("REPLIC4S ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\t # pack4S imm0");
}
#endif
#ifndef PRODUCT
void Repl4S_immm1Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("REPLIC4S ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\t # pack4S immm1");
}
#endif
#ifndef PRODUCT
void Repl2I_reg_risbgNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("REPLIC2I ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\t # pack2I");
}
#endif
#ifndef PRODUCT
void Repl2I_immNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("REPLIC2I ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\t # pack2I imm");
}
#endif
#ifndef PRODUCT
void Repl2I_imm0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("REPLIC2I ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\t # pack2I imm0");
}
#endif
#ifndef PRODUCT
void Repl2I_immm1Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("REPLIC2I ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\t # pack2I immm1");
}
#endif
#ifndef PRODUCT
void Repl2F_reg_indirectNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("REPLIC2F ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\t # pack2F indirect");
}
#endif
#ifndef PRODUCT
void Repl2F_reg_directNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("REPLIC2F ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\t # pack2F direct");
}
#endif
#ifndef PRODUCT
void Repl2F_immNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("REPLIC2F ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\t # pack2F imm");
}
#endif
#ifndef PRODUCT
void Repl2F_imm0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("REPLIC2F ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\t # pack2F imm0");
}
#endif
#ifndef PRODUCT
void storeA8BNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  st->print_raw("STG     ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("\t # ST(packed8B)");
  if (ra->C->alias_type(adr_type())->field() != NULL) {
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
  st->print_raw("LG      ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("\t # L(packed8B)");
  if (ra->C->alias_type(adr_type())->field() != NULL) {
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
void bytes_reverse_intNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("LRVR    ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\t# byte reverse int");
}
#endif
#ifndef PRODUCT
void bytes_reverse_longNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("LRVGR   ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\t# byte reverse long");
}
#endif
#ifndef PRODUCT
void countLeadingZerosINode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("SLLG    ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(",32\t# no need to always count 32 zeroes first\n\t");
  st->print_raw("IILH    ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",0x8000 \t# insert \"stop bit\" to force result 32 for zero src.\n\t");
  st->print_raw("FLOGR   ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(0)->int_format(ra, this, st); // dst
}
#endif
#ifndef PRODUCT
void countLeadingZerosLNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("FLOGR   ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(" \t# count leading zeros (long)\n\t");
}
#endif
#ifndef PRODUCT
void countTrailingZerosINode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// tmp
  st->print_raw("LLGFR   ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // dst
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("  \t# clear upper 32 bits (we are dealing with int)\n\t");
  st->print_raw("LCGFR   ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // tmp
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("  \t# load 2's complement (32->64 bit)\n\t");
  st->print_raw("AGHI    ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // dst
  st->print_raw(",-1    \t# tmp1 = src-1\n\t");
  st->print_raw("AGHI    ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // tmp
  st->print_raw(",-1    \t# tmp2 = -src-1 = ~src\n\t");
  st->print_raw("NGR     ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // dst
  st->print_raw(",");
  opnd_array(3)->ext_format(ra, this,idx3, st); // tmp
  st->print_raw("  \t# tmp3 = tmp1&tmp2\n\t");
  st->print_raw("FLOGR   ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // dst
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // dst
  st->print_raw("  \t# count trailing zeros (int)\n\t");
  st->print_raw("AHI     ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // dst
  st->print_raw(",-64   \t# tmp4 = 64-(trailing zeroes)-64\n\t");
  st->print_raw("LCR     ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // dst
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // dst
  st->print_raw("  \t# res = -tmp4");
}
#endif
#ifndef PRODUCT
void countTrailingZerosLNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst
  st->print_raw("LCGR    ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // dst
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("  \t# preserve src\n\t");
  st->print_raw("NGR     ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // dst
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("  \t#");
  st->print_raw("AGHI    ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // dst
  st->print_raw(",-1    \t# tmp1 = src-1\n\t");
  st->print_raw("FLOGR   ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // dst
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // dst
  st->print_raw("  \t# count trailing zeros (long), kill ");
      st->print_raw("Z_R5");
  st->print_raw("\n\t");
  st->print_raw("AHI     ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // dst
  st->print_raw(",-64   \t# tmp4 = 64-(trailing zeroes)-64\n\t");
  st->print_raw("LCR     ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // dst
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // dst
  st->print_raw("  \t#");
}
#endif
#ifndef PRODUCT
void popCountINode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// tmp
  st->print_raw("POPCNT  ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // dst
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\t# pop count int");
}
#endif
#ifndef PRODUCT
void popCountLNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// tmp
  st->print_raw("POPCNT  ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // dst
  st->print_raw(",");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\t# pop count long");
}
#endif
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
