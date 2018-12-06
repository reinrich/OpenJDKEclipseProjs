#line 1 "ad_ppc_format.cpp"
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
void vecXOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node,reg_str);
    st->print("%s",reg_str);
  }
}
void vecXOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str);
    st->print("%s",reg_str);
  }
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
void immI8Oper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print("#%d", _c0);
}
void immI8Oper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
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
void immIhi16Oper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print("#%d", _c0);
}
void immIhi16Oper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print("#%d", _c0);
}
#endif

#ifndef PRODUCT
void immInegpow2Oper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print("#%d", _c0);
}
void immInegpow2Oper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print("#%d", _c0);
}
#endif

#ifndef PRODUCT
void immIpow2minus1Oper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print("#%d", _c0);
}
void immIpow2minus1Oper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print("#%d", _c0);
}
#endif

#ifndef PRODUCT
void immIpowerOf2Oper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print("#%d", _c0);
}
void immIpowerOf2Oper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
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
void uimmI6Oper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print("#%d", _c0);
}
void uimmI6Oper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print("#%d", _c0);
}
#endif

#ifndef PRODUCT
void uimmI6_ge32Oper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print("#%d", _c0);
}
void uimmI6_ge32Oper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print("#%d", _c0);
}
#endif

#ifndef PRODUCT
void uimmI15Oper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print("#%d", _c0);
}
void uimmI15Oper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
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
void immI_0Oper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print("#%d", _c0);
}
void immI_0Oper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
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
void immI_minus1Oper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print("#%d", _c0);
}
void immI_minus1Oper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
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
void immNOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  if (_c0) _c0->dump_on(st);
}
void immNOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  if (_c0) _c0->dump_on(st);
}
#endif

#ifndef PRODUCT
void immN_0Oper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  if (_c0) _c0->dump_on(st);
}
void immN_0Oper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
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
void immNKlass_NMOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  if (_c0) _c0->dump_on(st);
}
void immNKlass_NMOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  if (_c0) _c0->dump_on(st);
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
void immP_NMOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  if (_c0) _c0->dump_on(st);
}
void immP_NMOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  if (_c0) _c0->dump_on(st);
}
#endif

#ifndef PRODUCT
void immP_0Oper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  if (_c0) _c0->dump_on(st);
}
void immP_0Oper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  if (_c0) _c0->dump_on(st);
}
#endif

#ifndef PRODUCT
void immP_0or1Oper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  if (_c0) _c0->dump_on(st);
}
void immP_0or1Oper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  if (_c0) _c0->dump_on(st);
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
void immLmax30Oper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print("#" INT64_FORMAT, (int64_t)_c0);
}
void immLmax30Oper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
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
void immL16Alg4Oper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print("#" INT64_FORMAT, (int64_t)_c0);
}
void immL16Alg4Oper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print("#" INT64_FORMAT, (int64_t)_c0);
}
#endif

#ifndef PRODUCT
void immL32hi16Oper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print("#" INT64_FORMAT, (int64_t)_c0);
}
void immL32hi16Oper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
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
void immLhighest16Oper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print("#" INT64_FORMAT, (int64_t)_c0);
}
void immLhighest16Oper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print("#" INT64_FORMAT, (int64_t)_c0);
}
#endif

#ifndef PRODUCT
void immLnegpow2Oper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print("#" INT64_FORMAT, (int64_t)_c0);
}
void immLnegpow2Oper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print("#" INT64_FORMAT, (int64_t)_c0);
}
#endif

#ifndef PRODUCT
void immLpow2minus1Oper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print("#" INT64_FORMAT, (int64_t)_c0);
}
void immLpow2minus1Oper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
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
void immL_minus1Oper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print("#" INT64_FORMAT, (int64_t)_c0);
}
void immL_minus1Oper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
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
void uimmL16Oper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print("#" INT64_FORMAT, (int64_t)_c0);
}
void uimmL16Oper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print("#" INT64_FORMAT, (int64_t)_c0);
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
void immF_0Oper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print("#%f", _c0);
}
void immF_0Oper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print("#%f", _c0);
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
void iRegIdstOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node,reg_str);
    st->print("%s",reg_str);
  }
}
void iRegIdstOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str);
    st->print("%s",reg_str);
  }
}
#endif

#ifndef PRODUCT
void iRegIsrcOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node,reg_str);
    st->print("%s",reg_str);
  }
}
void iRegIsrcOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str);
    st->print("%s",reg_str);
  }
}
#endif

#ifndef PRODUCT
void rscratch1RegIOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node,reg_str);
    st->print("%s",reg_str);
  }
}
void rscratch1RegIOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str);
    st->print("%s",reg_str);
  }
}
#endif

#ifndef PRODUCT
void rscratch2RegIOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node,reg_str);
    st->print("%s",reg_str);
  }
}
void rscratch2RegIOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
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
void rarg2RegLOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node,reg_str);
    st->print("%s",reg_str);
  }
}
void rarg2RegLOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str);
    st->print("%s",reg_str);
  }
}
#endif

#ifndef PRODUCT
void rarg3RegLOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node,reg_str);
    st->print("%s",reg_str);
  }
}
void rarg3RegLOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str);
    st->print("%s",reg_str);
  }
}
#endif

#ifndef PRODUCT
void rarg4RegLOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node,reg_str);
    st->print("%s",reg_str);
  }
}
void rarg4RegLOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str);
    st->print("%s",reg_str);
  }
}
#endif

#ifndef PRODUCT
void iRegPdstOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node,reg_str);
    st->print("%s",reg_str);
  }
}
void iRegPdstOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str);
    st->print("%s",reg_str);
  }
}
#endif

#ifndef PRODUCT
void iRegPdstNoScratchOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node,reg_str);
    st->print("%s",reg_str);
  }
}
void iRegPdstNoScratchOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str);
    st->print("%s",reg_str);
  }
}
#endif

#ifndef PRODUCT
void iRegPsrcOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node,reg_str);
    st->print("%s",reg_str);
  }
}
void iRegPsrcOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str);
    st->print("%s",reg_str);
  }
}
#endif

#ifndef PRODUCT
void threadRegPOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print_raw("R16");
}
void threadRegPOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print_raw("R16");
}
#endif

#ifndef PRODUCT
void rscratch1RegPOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print_raw("R11");
}
void rscratch1RegPOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print_raw("R11");
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
void iRegNsrcOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node,reg_str);
    st->print("%s",reg_str);
  }
}
void iRegNsrcOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str);
    st->print("%s",reg_str);
  }
}
#endif

#ifndef PRODUCT
void iRegNdstOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node,reg_str);
    st->print("%s",reg_str);
  }
}
void iRegNdstOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str);
    st->print("%s",reg_str);
  }
}
#endif

#ifndef PRODUCT
void iRegLdstOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node,reg_str);
    st->print("%s",reg_str);
  }
}
void iRegLdstOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str);
    st->print("%s",reg_str);
  }
}
#endif

#ifndef PRODUCT
void iRegLsrcOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node,reg_str);
    st->print("%s",reg_str);
  }
}
void iRegLsrcOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str);
    st->print("%s",reg_str);
  }
}
#endif

#ifndef PRODUCT
void iRegL2IsrcOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print_raw("ConvL2I(");
  { char reg_str[128];
    ra->dump_register(node,reg_str);
    st->print("%s",reg_str);
  }
  st->print_raw(")");
}
void iRegL2IsrcOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print_raw("ConvL2I(");
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str);
    st->print("%s",reg_str);
  }
  st->print_raw(")");
}
#endif

#ifndef PRODUCT
void rscratch1RegLOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node,reg_str);
    st->print("%s",reg_str);
  }
}
void rscratch1RegLOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str);
    st->print("%s",reg_str);
  }
}
#endif

#ifndef PRODUCT
void rscratch2RegLOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node,reg_str);
    st->print("%s",reg_str);
  }
}
void rscratch2RegLOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str);
    st->print("%s",reg_str);
  }
}
#endif

#ifndef PRODUCT
void flagsRegOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node,reg_str);
    st->print("%s",reg_str);
  }
}
void flagsRegOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str);
    st->print("%s",reg_str);
  }
}
#endif

#ifndef PRODUCT
void flagsRegSrcOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node,reg_str);
    st->print("%s",reg_str);
  }
}
void flagsRegSrcOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str);
    st->print("%s",reg_str);
  }
}
#endif

#ifndef PRODUCT
void flagsRegCR0Oper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print_raw("CR0");
}
void flagsRegCR0Oper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print_raw("CR0");
}
#endif

#ifndef PRODUCT
void flagsRegCR1Oper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print_raw("CR1");
}
void flagsRegCR1Oper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print_raw("CR1");
}
#endif

#ifndef PRODUCT
void flagsRegCR6Oper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print_raw("CR6");
}
void flagsRegCR6Oper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print_raw("CR6");
}
#endif

#ifndef PRODUCT
void regCTROper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print_raw("SR_CTR");
}
void regCTROper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print_raw("SR_CTR");
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
void iRegN2P_klassOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node,reg_str);
    st->print("%s",reg_str);
  }
}
void iRegN2P_klassOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str);
    st->print("%s",reg_str);
  }
}
#endif

#ifndef PRODUCT
void indirectOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print_raw("[");
  { char reg_str[128];
    ra->dump_register(node,reg_str);
    st->print("%s",reg_str);
  }
  st->print_raw("]");
}
void indirectOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print_raw("[");
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str);
    st->print("%s",reg_str);
  }
  st->print_raw("]");
}
#endif

#ifndef PRODUCT
void indOffset16Oper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print_raw("[");
  { char reg_str[128];
    ra->dump_register(node,reg_str);
    st->print("%s",reg_str);
  }
  st->print_raw(" + ");
  st->print("#" INT64_FORMAT, (int64_t)_c0);
  st->print_raw("]");
}
void indOffset16Oper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print_raw("[");
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str);
    st->print("%s",reg_str);
  }
  st->print_raw(" + ");
  st->print("#" INT64_FORMAT, (int64_t)_c0);
  st->print_raw("]");
}
#endif

#ifndef PRODUCT
void indOffset16Alg4Oper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print_raw("[");
  { char reg_str[128];
    ra->dump_register(node,reg_str);
    st->print("%s",reg_str);
  }
  st->print_raw(" + ");
  st->print("#" INT64_FORMAT, (int64_t)_c0);
  st->print_raw("]");
}
void indOffset16Alg4Oper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print_raw("[");
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str);
    st->print("%s",reg_str);
  }
  st->print_raw(" + ");
  st->print("#" INT64_FORMAT, (int64_t)_c0);
  st->print_raw("]");
}
#endif

#ifndef PRODUCT
void indirectNarrowOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print_raw("[");
  { char reg_str[128];
    ra->dump_register(node,reg_str);
    st->print("%s",reg_str);
  }
  st->print_raw("]");
}
void indirectNarrowOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print_raw("[");
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str);
    st->print("%s",reg_str);
  }
  st->print_raw("]");
}
#endif

#ifndef PRODUCT
void indirectNarrow_klassOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print_raw("[");
  { char reg_str[128];
    ra->dump_register(node,reg_str);
    st->print("%s",reg_str);
  }
  st->print_raw("]");
}
void indirectNarrow_klassOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print_raw("[");
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str);
    st->print("%s",reg_str);
  }
  st->print_raw("]");
}
#endif

#ifndef PRODUCT
void indOffset16NarrowOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print_raw("[");
  { char reg_str[128];
    ra->dump_register(node,reg_str);
    st->print("%s",reg_str);
  }
  st->print_raw(" + ");
  st->print("#" INT64_FORMAT, (int64_t)_c0);
  st->print_raw("]");
}
void indOffset16NarrowOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print_raw("[");
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str);
    st->print("%s",reg_str);
  }
  st->print_raw(" + ");
  st->print("#" INT64_FORMAT, (int64_t)_c0);
  st->print_raw("]");
}
#endif

#ifndef PRODUCT
void indOffset16Narrow_klassOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print_raw("[");
  { char reg_str[128];
    ra->dump_register(node,reg_str);
    st->print("%s",reg_str);
  }
  st->print_raw(" + ");
  st->print("#" INT64_FORMAT, (int64_t)_c0);
  st->print_raw("]");
}
void indOffset16Narrow_klassOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print_raw("[");
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str);
    st->print("%s",reg_str);
  }
  st->print_raw(" + ");
  st->print("#" INT64_FORMAT, (int64_t)_c0);
  st->print_raw("]");
}
#endif

#ifndef PRODUCT
void indOffset16NarrowAlg4Oper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print_raw("[");
  { char reg_str[128];
    ra->dump_register(node,reg_str);
    st->print("%s",reg_str);
  }
  st->print_raw(" + ");
  st->print("#" INT64_FORMAT, (int64_t)_c0);
  st->print_raw("]");
}
void indOffset16NarrowAlg4Oper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print_raw("[");
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str);
    st->print("%s",reg_str);
  }
  st->print_raw(" + ");
  st->print("#" INT64_FORMAT, (int64_t)_c0);
  st->print_raw("]");
}
#endif

#ifndef PRODUCT
void indOffset16NarrowAlg4_klassOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print_raw("[");
  { char reg_str[128];
    ra->dump_register(node,reg_str);
    st->print("%s",reg_str);
  }
  st->print_raw(" + ");
  st->print("#" INT64_FORMAT, (int64_t)_c0);
  st->print_raw("]");
}
void indOffset16NarrowAlg4_klassOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print_raw("[");
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str);
    st->print("%s",reg_str);
  }
  st->print_raw(" + ");
  st->print("#" INT64_FORMAT, (int64_t)_c0);
  st->print_raw("]");
}
#endif

#ifndef PRODUCT
void stackSlotIOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print_raw("[sp+");
  { char reg_str[128];
    ra->dump_register(node,reg_str);
    st->print("%s",reg_str);
  }
  st->print_raw("]");
}
void stackSlotIOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print_raw("[sp+");
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str);
    st->print("%s",reg_str);
  }
  st->print_raw("]");
}
#endif

#ifndef PRODUCT
void stackSlotLOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print_raw("[sp+");
  { char reg_str[128];
    ra->dump_register(node,reg_str);
    st->print("%s",reg_str);
  }
  st->print_raw("]");
}
void stackSlotLOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print_raw("[sp+");
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str);
    st->print("%s",reg_str);
  }
  st->print_raw("]");
}
#endif

#ifndef PRODUCT
void stackSlotPOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print_raw("[sp+");
  { char reg_str[128];
    ra->dump_register(node,reg_str);
    st->print("%s",reg_str);
  }
  st->print_raw("]");
}
void stackSlotPOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print_raw("[sp+");
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str);
    st->print("%s",reg_str);
  }
  st->print_raw("]");
}
#endif

#ifndef PRODUCT
void stackSlotFOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print_raw("[sp+");
  { char reg_str[128];
    ra->dump_register(node,reg_str);
    st->print("%s",reg_str);
  }
  st->print_raw("]");
}
void stackSlotFOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print_raw("[sp+");
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str);
    st->print("%s",reg_str);
  }
  st->print_raw("]");
}
#endif

#ifndef PRODUCT
void stackSlotDOper::int_format(PhaseRegAlloc *ra, const MachNode *node, outputStream *st) const {
  st->print_raw("[sp+");
  { char reg_str[128];
    ra->dump_register(node,reg_str);
    st->print("%s",reg_str);
  }
  st->print_raw("]");
}
void stackSlotDOper::ext_format(PhaseRegAlloc *ra, const MachNode *node, int idx, outputStream *st) const {
  st->print_raw("[sp+");
  { char reg_str[128];
    ra->dump_register(node->in(idx),reg_str);
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
void convB2I_reg_2Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("EXTSB   ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(" \t// byte->int");
}
#endif
#ifndef PRODUCT
void loadUB_indirectNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  st->print_raw("LBZ     ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  if (ra->C->alias_type(adr_type())->field() != NULL) {
    ciField* f = ra->C->alias_type(adr_type())->field();
    st->print(" 	// Field: ");
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
void loadUB_indirect_acNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  st->print_raw("LBZ     ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("\n\t");
  st->print_raw("TWI     ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw("\n\t");
  st->print_raw("ISYNC");
  if (ra->C->alias_type(adr_type())->field() != NULL) {
    ciField* f = ra->C->alias_type(adr_type())->field();
    st->print(" 	// Field: ");
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
void loadB_indirect_ExNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  if (ra->C->alias_type(adr_type())->field() != NULL) {
    ciField* f = ra->C->alias_type(adr_type())->field();
    st->print(" 	// Field: ");
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
void loadB_indirect_ac_ExNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  if (ra->C->alias_type(adr_type())->field() != NULL) {
    ciField* f = ra->C->alias_type(adr_type())->field();
    st->print(" 	// Field: ");
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
void loadUB_indOffset16Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  st->print_raw("LBZ     ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  if (ra->C->alias_type(adr_type())->field() != NULL) {
    ciField* f = ra->C->alias_type(adr_type())->field();
    st->print(" 	// Field: ");
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
void loadUB_indOffset16_acNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  st->print_raw("LBZ     ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("\n\t");
  st->print_raw("TWI     ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw("\n\t");
  st->print_raw("ISYNC");
  if (ra->C->alias_type(adr_type())->field() != NULL) {
    ciField* f = ra->C->alias_type(adr_type())->field();
    st->print(" 	// Field: ");
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
void loadB_indOffset16_ExNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  if (ra->C->alias_type(adr_type())->field() != NULL) {
    ciField* f = ra->C->alias_type(adr_type())->field();
    st->print(" 	// Field: ");
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
void loadB_indOffset16_ac_ExNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  if (ra->C->alias_type(adr_type())->field() != NULL) {
    ciField* f = ra->C->alias_type(adr_type())->field();
    st->print(" 	// Field: ");
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
void loadUBNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  st->print_raw("LBZ     ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(" \t// byte, zero-extend to int");
  if (ra->C->alias_type(adr_type())->field() != NULL) {
    ciField* f = ra->C->alias_type(adr_type())->field();
    st->print(" 	// Field: ");
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
void loadUB_acNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  st->print_raw("LBZ     ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(" \t// byte, zero-extend to int, acquire\n\t");
  st->print_raw("TWI     ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw("\n\t");
  st->print_raw("ISYNC");
  if (ra->C->alias_type(adr_type())->field() != NULL) {
    ciField* f = ra->C->alias_type(adr_type())->field();
    st->print(" 	// Field: ");
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
  st->print_raw("LBZ     ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(" \t// byte, zero-extend to long");
}
#endif
#ifndef PRODUCT
void loadUB2L_acNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  st->print_raw("LBZ     ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(" \t// byte, zero-extend to long, acquire\n\t");
  st->print_raw("TWI     ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw("\n\t");
  st->print_raw("ISYNC");
}
#endif
#ifndef PRODUCT
void loadSNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  st->print_raw("LHA     ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  if (ra->C->alias_type(adr_type())->field() != NULL) {
    ciField* f = ra->C->alias_type(adr_type())->field();
    st->print(" 	// Field: ");
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
void loadS_acNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  st->print_raw("LHA     ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw("\t acquire\n\t");
  st->print_raw("TWI     ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw("\n\t");
  st->print_raw("ISYNC");
  if (ra->C->alias_type(adr_type())->field() != NULL) {
    ciField* f = ra->C->alias_type(adr_type())->field();
    st->print(" 	// Field: ");
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
void loadUSNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  st->print_raw("LHZ     ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  if (ra->C->alias_type(adr_type())->field() != NULL) {
    ciField* f = ra->C->alias_type(adr_type())->field();
    st->print(" 	// Field: ");
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
void loadUS_acNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  st->print_raw("LHZ     ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(" \t// acquire\n\t");
  st->print_raw("TWI     ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw("\n\t");
  st->print_raw("ISYNC");
  if (ra->C->alias_type(adr_type())->field() != NULL) {
    ciField* f = ra->C->alias_type(adr_type())->field();
    st->print(" 	// Field: ");
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
  st->print_raw("LHZ     ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(" \t// short, zero-extend to long");
}
#endif
#ifndef PRODUCT
void loadUS2L_acNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  st->print_raw("LHZ     ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(" \t// short, zero-extend to long, acquire\n\t");
  st->print_raw("TWI     ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw("\n\t");
  st->print_raw("ISYNC");
}
#endif
#ifndef PRODUCT
void loadINode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  st->print_raw("LWZ     ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  if (ra->C->alias_type(adr_type())->field() != NULL) {
    ciField* f = ra->C->alias_type(adr_type())->field();
    st->print(" 	// Field: ");
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
void loadI_acNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  st->print_raw("LWZ     ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(" \t// load acquire\n\t");
  st->print_raw("TWI     ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw("\n\t");
  st->print_raw("ISYNC");
  if (ra->C->alias_type(adr_type())->field() != NULL) {
    ciField* f = ra->C->alias_type(adr_type())->field();
    st->print(" 	// Field: ");
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
void loadUI2LNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// mask
  st->print_raw("LWZ     ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(" \t// zero-extend to long");
}
#endif
#ifndef PRODUCT
void loadI2LNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  st->print_raw("LWA     ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(" \t// loadI2L");
}
#endif
#ifndef PRODUCT
void loadI2L_acNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  st->print_raw("LWA     ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(" \t// loadI2L acquire");
  st->print_raw("TWI     ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw("\n\t");
  st->print_raw("ISYNC");
}
#endif
#ifndef PRODUCT
void loadLNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  st->print_raw("LD      ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(" \t// long");
  if (ra->C->alias_type(adr_type())->field() != NULL) {
    ciField* f = ra->C->alias_type(adr_type())->field();
    st->print(" 	// Field: ");
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
void loadL_acNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  st->print_raw("LD      ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(" \t// long acquire\n\t");
  st->print_raw("TWI     ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw("\n\t");
  st->print_raw("ISYNC");
  if (ra->C->alias_type(adr_type())->field() != NULL) {
    ciField* f = ra->C->alias_type(adr_type())->field();
    st->print(" 	// Field: ");
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
  st->print_raw("LD      ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(" \t// unaligned long");
  if (ra->C->alias_type(adr_type())->field() != NULL) {
    ciField* f = ra->C->alias_type(adr_type())->field();
    st->print(" 	// Field: ");
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
  st->print_raw("LD      ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(" \t// load 8-byte Vector");
  if (ra->C->alias_type(adr_type())->field() != NULL) {
    ciField* f = ra->C->alias_type(adr_type())->field();
    st->print(" 	// Field: ");
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
  st->print_raw("LXVD2X      ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(" \t// load 16-byte Vector");
  if (ra->C->alias_type(adr_type())->field() != NULL) {
    ciField* f = ra->C->alias_type(adr_type())->field();
    st->print(" 	// Field: ");
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
  st->print_raw("LWZ     ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(" \t// range");
  if (ra->C->alias_type(adr_type())->field() != NULL) {
    ciField* f = ra->C->alias_type(adr_type())->field();
    st->print(" 	// Field: ");
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
  st->print_raw("LWZ     ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(" \t// load compressed ptr");
  if (ra->C->alias_type(adr_type())->field() != NULL) {
    ciField* f = ra->C->alias_type(adr_type())->field();
    st->print(" 	// Field: ");
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
void loadN_acNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  st->print_raw("LWZ     ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(" \t// load acquire compressed ptr\n\t");
  st->print_raw("TWI     ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw("\n\t");
  st->print_raw("ISYNC");
  if (ra->C->alias_type(adr_type())->field() != NULL) {
    ciField* f = ra->C->alias_type(adr_type())->field();
    st->print(" 	// Field: ");
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
void loadN2P_unscaledNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  st->print_raw("LWZ     ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(" \t// DecodeN (unscaled)");
}
#endif
#ifndef PRODUCT
void loadN2P_klass_unscaledNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  st->print_raw("LWZ     ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(" \t// DecodeN (unscaled)");
}
#endif
#ifndef PRODUCT
void loadPNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  st->print_raw("LD      ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(" \t// ptr");
  if (ra->C->alias_type(adr_type())->field() != NULL) {
    ciField* f = ra->C->alias_type(adr_type())->field();
    st->print(" 	// Field: ");
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
void loadP_acNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  st->print_raw("LD      ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(" \t// ptr acquire\n\t");
  st->print_raw("TWI     ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw("\n\t");
  st->print_raw("ISYNC");
  if (ra->C->alias_type(adr_type())->field() != NULL) {
    ciField* f = ra->C->alias_type(adr_type())->field();
    st->print(" 	// Field: ");
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
void loadP2XNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  st->print_raw("LD      ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(" \t// ptr + p2x");
}
#endif
#ifndef PRODUCT
void loadNKlassNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  st->print_raw("LWZ     ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(" \t// compressed klass ptr");
  if (ra->C->alias_type(adr_type())->field() != NULL) {
    ciField* f = ra->C->alias_type(adr_type())->field();
    st->print(" 	// Field: ");
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
  st->print_raw("LD      ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(" \t// klass ptr");
  if (ra->C->alias_type(adr_type())->field() != NULL) {
    ciField* f = ra->C->alias_type(adr_type())->field();
    st->print(" 	// Field: ");
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
  st->print_raw("LFS     ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  if (ra->C->alias_type(adr_type())->field() != NULL) {
    ciField* f = ra->C->alias_type(adr_type())->field();
    st->print(" 	// Field: ");
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
void loadF_acNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// cr0
  st->print_raw("LFS     ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(" \t// acquire\n\t");
  st->print_raw("FCMPU   cr0, ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw("\n\t");
  st->print_raw("BNE     cr0, next\n");
  st->print_raw("next:\n\t");
  st->print_raw("ISYNC");
  if (ra->C->alias_type(adr_type())->field() != NULL) {
    ciField* f = ra->C->alias_type(adr_type())->field();
    st->print(" 	// Field: ");
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
  st->print_raw("LFD     ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  if (ra->C->alias_type(adr_type())->field() != NULL) {
    ciField* f = ra->C->alias_type(adr_type())->field();
    st->print(" 	// Field: ");
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
void loadD_acNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// cr0
  st->print_raw("LFD     ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(" \t// acquire\n\t");
  st->print_raw("FCMPU   cr0, ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw("\n\t");
  st->print_raw("BNE     cr0, next\n");
  st->print_raw("next:\n\t");
  st->print_raw("ISYNC");
  if (ra->C->alias_type(adr_type())->field() != NULL) {
    ciField* f = ra->C->alias_type(adr_type())->field();
    st->print(" 	// Field: ");
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
  st->print_raw("LFD     ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  if (ra->C->alias_type(adr_type())->field() != NULL) {
    ciField* f = ra->C->alias_type(adr_type())->field();
    st->print(" 	// Field: ");
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
void loadToc_hiNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// 
  st->print_raw("ADDIS   ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", R29, DISP.hi \t// load TOC hi");
}
#endif
#ifndef PRODUCT
void loadToc_loNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("ADDI    ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(", DISP.lo \t// load TOC lo");
}
#endif
#ifndef PRODUCT
void loadConI16Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("LI      ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
}
#endif
#ifndef PRODUCT
void loadConIhi16Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("LIS     ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(".hi");
}
#endif
#ifndef PRODUCT
void loadConI32_lo16Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("ORI     ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(".hi, ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(".lo");
}
#endif
#ifndef PRODUCT
void loadConI_ExNode::format(PhaseRegAlloc *ra, outputStream *st) const {
}
#endif
#ifndef PRODUCT
void loadConL16Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("LI      ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(" \t// long");
}
#endif
#ifndef PRODUCT
void loadConL32hi16Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("LIS     ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(".hi \t// long");
}
#endif
#ifndef PRODUCT
void loadConL32_lo16Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("ORI     ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(".lo");
}
#endif
#ifndef PRODUCT
void loadConL32_ExNode::format(PhaseRegAlloc *ra, outputStream *st) const {
}
#endif
#ifndef PRODUCT
void loadConLhighest16_ExNode::format(PhaseRegAlloc *ra, outputStream *st) const {
}
#endif
#ifndef PRODUCT
void loadConLNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// toc
  st->print_raw("LD      ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", offset, ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // toc
  st->print_raw(" \t// load long ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(" from TOC");
}
#endif
#ifndef PRODUCT
void loadConL_hiNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// toc
  st->print_raw("ADDIS   ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // toc
  st->print_raw(", offset \t// load long ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(" from TOC (hi)");
}
#endif
#ifndef PRODUCT
void loadConL_loNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// base
  st->print_raw("LD      ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", offset, ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // base
  st->print_raw(" \t// load long ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(" from TOC (lo)");
}
#endif
#ifndef PRODUCT
void loadConL_ExNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("LD      ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", offset, ");
  char reg[128];  ra->dump_register(in(mach_constant_base_node_input()), reg);
    st->print("%s", reg);
  st->print_raw("\t// load long ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(" from table, postalloc expanded");
}
#endif
#ifndef PRODUCT
void loadConN0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("LI      ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(" \t// compressed ptr");
}
#endif
#ifndef PRODUCT
void loadConN_hiNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("LIS     ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(" \t// narrow oop hi");
}
#endif
#ifndef PRODUCT
void loadConN_loNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("ORI     ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(" \t// narrow oop lo");
}
#endif
#ifndef PRODUCT
void rldiclNode::format(PhaseRegAlloc *ra, outputStream *st) const {
}
#endif
#ifndef PRODUCT
void clearMs32bNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("MASK    ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(", 0xFFFFFFFF");
}
#endif
#ifndef PRODUCT
void loadBaseNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// 
  st->print_raw("LoadConst ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", heapbase");
}
#endif
#ifndef PRODUCT
void loadConN_ExNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("LoadN   ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(" \t// postalloc expanded");
}
#endif
#ifndef PRODUCT
void loadConNKlass_hiNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("LIS     ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(" \t// narrow klass hi");
}
#endif
#ifndef PRODUCT
void loadConNKlass_maskNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("MASK    ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", 0xFFFFFFFF");
}
#endif
#ifndef PRODUCT
void loadConNKlass_loNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("ORI     ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(" \t// narrow klass lo");
}
#endif
#ifndef PRODUCT
void loadConNKlass_ExNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("LoadN   ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(" \t// postalloc expanded");
}
#endif
#ifndef PRODUCT
void loadConP0or1Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("LI      ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(" \t// ptr");
}
#endif
#ifndef PRODUCT
void loadConPNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// toc
  st->print_raw("LD      ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", offset, ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // toc
  st->print_raw(" \t// load ptr ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(" from TOC");
}
#endif
#ifndef PRODUCT
void loadConP_hiNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// toc
  st->print_raw("ADDIS   ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // toc
  st->print_raw(", offset \t// load ptr ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(" from TOC (hi)");
}
#endif
#ifndef PRODUCT
void loadConP_loNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// base
  st->print_raw("LD      ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", offset, ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // base
  st->print_raw(" \t// load ptr ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(" from TOC (lo)");
}
#endif
#ifndef PRODUCT
void loadConP_ExNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("LD    ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", offset, ");
  char reg[128];  ra->dump_register(in(mach_constant_base_node_input()), reg);
    st->print("%s", reg);
  st->print_raw(" \t//  load ptr ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(" from table, postalloc expanded");
}
#endif
#ifndef PRODUCT
void loadConFNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// toc
  st->print_raw("LFS     ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", offset, ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // toc
  st->print_raw(" \t// load float ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(" from TOC");
}
#endif
#ifndef PRODUCT
void loadConFCompNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// toc
  st->print_raw("ADDIS   ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // toc
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // toc
  st->print_raw(", offset_hi\n\t");
  st->print_raw("LFS     ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", offset_lo, ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // toc
  st->print_raw(" \t// load float ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(" from TOC (hi/lo)\n\t");
  st->print_raw("ADDIS   ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // toc
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // toc
  st->print_raw(", -offset_hi");
}
#endif
#ifndef PRODUCT
void loadConF_ExNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("LFS     ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", offset, ");
  char reg[128];  ra->dump_register(in(mach_constant_base_node_input()), reg);
    st->print("%s", reg);
  st->print_raw(" \t// load ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(" from table, postalloc expanded");
}
#endif
#ifndef PRODUCT
void loadConDNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// toc
  st->print_raw("LFD     ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", offset, ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // toc
  st->print_raw(" \t// load double ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(" from TOC");
}
#endif
#ifndef PRODUCT
void loadConDCompNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// toc
  st->print_raw("ADDIS   ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // toc
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // toc
  st->print_raw(", offset_hi\n\t");
  st->print_raw("LFD     ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", offset_lo, ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // toc
  st->print_raw(" \t// load double ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(" from TOC (hi/lo)\n\t");
  st->print_raw("ADDIS   ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // toc
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // toc
  st->print_raw(", -offset_hi");
}
#endif
#ifndef PRODUCT
void loadConD_ExNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("ConD    ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", offset, ");
  char reg[128];  ra->dump_register(in(mach_constant_base_node_input()), reg);
    st->print("%s", reg);
  st->print_raw(" \t// load ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(" from table, postalloc expanded");
}
#endif
#ifndef PRODUCT
void prefetch_alloc_zeroNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// 
  st->print_raw("PREFETCH ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(", 2, ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
  st->print_raw(" \t// Prefetch write-many with zero");
}
#endif
#ifndef PRODUCT
void prefetch_alloc_zero_no_offsetNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// 
  st->print_raw("PREFETCH ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(", 2 \t// Prefetch write-many with zero");
}
#endif
#ifndef PRODUCT
void prefetch_allocNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// 
  st->print_raw("PREFETCH ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(", 2, ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
  st->print_raw(" \t// Prefetch write-many");
}
#endif
#ifndef PRODUCT
void prefetch_alloc_no_offsetNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// 
  st->print_raw("PREFETCH ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(", 2 \t// Prefetch write-many");
}
#endif
#ifndef PRODUCT
void storeBNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  st->print_raw("STB     ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(" \t// byte");
  if (ra->C->alias_type(adr_type())->field() != NULL) {
    ciField* f = ra->C->alias_type(adr_type())->field();
    st->print(" 	// Field: ");
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
  st->print_raw("STH     ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(" \t// short");
  if (ra->C->alias_type(adr_type())->field() != NULL) {
    ciField* f = ra->C->alias_type(adr_type())->field();
    st->print(" 	// Field: ");
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
  st->print_raw("STW     ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  if (ra->C->alias_type(adr_type())->field() != NULL) {
    ciField* f = ra->C->alias_type(adr_type())->field();
    st->print(" 	// Field: ");
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
void storeI_convL2INode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  st->print_raw("STW     l2i(");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
  st->print_raw("), ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  if (ra->C->alias_type(adr_type())->field() != NULL) {
    ciField* f = ra->C->alias_type(adr_type())->field();
    st->print(" 	// Field: ");
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
  st->print_raw("STD     ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(" \t// long");
  if (ra->C->alias_type(adr_type())->field() != NULL) {
    ciField* f = ra->C->alias_type(adr_type())->field();
    st->print(" 	// Field: ");
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
void storeA8BNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  st->print_raw("STD     ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
  st->print_raw(" \t// packed8B");
  if (ra->C->alias_type(adr_type())->field() != NULL) {
    ciField* f = ra->C->alias_type(adr_type())->field();
    st->print(" 	// Field: ");
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
  st->print_raw("STXVD2X     ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
  st->print_raw(" \t// store 16-byte Vector");
  if (ra->C->alias_type(adr_type())->field() != NULL) {
    ciField* f = ra->C->alias_type(adr_type())->field();
    st->print(" 	// Field: ");
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
  unsigned idx1 = 2; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  st->print_raw("STW     ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst
  st->print_raw(" \t// compressed oop");
  if (ra->C->alias_type(adr_type())->field() != NULL) {
    ciField* f = ra->C->alias_type(adr_type())->field();
    st->print(" 	// Field: ");
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
  unsigned idx1 = 2; 	// dst
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  st->print_raw("STW     ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst
  st->print_raw(" \t// compressed klass");
  if (ra->C->alias_type(adr_type())->field() != NULL) {
    ciField* f = ra->C->alias_type(adr_type())->field();
    st->print(" 	// Field: ");
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
  st->print_raw("STD     ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst
  st->print_raw(" \t// ptr");
  if (ra->C->alias_type(adr_type())->field() != NULL) {
    ciField* f = ra->C->alias_type(adr_type())->field();
    st->print(" 	// Field: ");
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
  st->print_raw("STFS    ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  if (ra->C->alias_type(adr_type())->field() != NULL) {
    ciField* f = ra->C->alias_type(adr_type())->field();
    st->print(" 	// Field: ");
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
  st->print_raw("STFD    ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  if (ra->C->alias_type(adr_type())->field() != NULL) {
    ciField* f = ra->C->alias_type(adr_type())->field();
    st->print(" 	// Field: ");
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
void storeCM_CMSNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// releaseFieldAddr
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// crx
  st->print_raw("STB     #0, ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(" \t// CMS card-mark byte (must be 0!), checking requires_release in [");
  opnd_array(2)->ext_format(ra, this,idx2, st); // releaseFieldAddr
  st->print_raw("]");
  if (ra->C->alias_type(adr_type())->field() != NULL) {
    ciField* f = ra->C->alias_type(adr_type())->field();
    st->print(" 	// Field: ");
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
void storeCM_CMS_ExExNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  if (ra->C->alias_type(adr_type())->field() != NULL) {
    ciField* f = ra->C->alias_type(adr_type())->field();
    st->print(" 	// Field: ");
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
void storeCM_G1Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// zero
  st->print_raw("STB     #0, ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(" \t// CMS card-mark byte store (G1)");
  if (ra->C->alias_type(adr_type())->field() != NULL) {
    ciField* f = ra->C->alias_type(adr_type())->field();
    st->print(" 	// Field: ");
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
void encodeP_shiftNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("SRDI    ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(", 3 \t// encode");
}
#endif
#ifndef PRODUCT
void encodeP_subNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("SUB     ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(", oop_base \t// encode");
}
#endif
#ifndef PRODUCT
void cond_sub_baseNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// crx
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  st->print_raw("BEQ     ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // crx
  st->print_raw(", done\n\t");
  st->print_raw("SUB     ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src1
  st->print_raw(", heapbase \t// encode: subtract base if != NULL\n");
  st->print_raw("done:");
}
#endif
#ifndef PRODUCT
void cond_set_0_oopNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// crx
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  st->print_raw("CMOVE   ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // crx
  st->print_raw(" eq, 0, ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src1
  st->print_raw(" \t// encode: preserve 0");
}
#endif
#ifndef PRODUCT
void encodeP_DisjointNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("EXTRDI  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(", #32, #3 \t// encode with disjoint base");
}
#endif
#ifndef PRODUCT
void encodeP_ExNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// crx
  st->print_raw("EncodeP ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // crx
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(" \t// postalloc expanded");
}
#endif
#ifndef PRODUCT
void encodeP_not_null_ExNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("EncodeP ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("\t// ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(" != Null, postalloc expanded");
}
#endif
#ifndef PRODUCT
void encodeP_not_null_base_nullNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("SRDI    ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(", #3 \t// encodeP, ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(" != NULL");
}
#endif
#ifndef PRODUCT
void encodeP_narrow_oop_shift_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("MR      ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(" \t// Ptr->Narrow");
}
#endif
#ifndef PRODUCT
void decodeN_shiftNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("SLDI    ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(", #3 \t// DecodeN");
}
#endif
#ifndef PRODUCT
void decodeN_addNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("ADD     ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(", heapbase \t// DecodeN, add oop base");
}
#endif
#ifndef PRODUCT
void cond_add_baseNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// crx
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  st->print_raw("BEQ     ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // crx
  st->print_raw(", done\n\t");
  st->print_raw("ADD     ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
  st->print_raw(", heapbase \t// DecodeN: add oop base if ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
  st->print_raw(" != NULL\n");
  st->print_raw("done:");
}
#endif
#ifndef PRODUCT
void cond_set_0_ptrNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// crx
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  st->print_raw("CMOVE   ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // crx
  st->print_raw(" eq, 0, ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src1
  st->print_raw(" \t// decode: preserve 0");
}
#endif
#ifndef PRODUCT
void decodeN_ExNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// crx
  st->print_raw("DecodeN ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(" \t// Kills ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // crx
  st->print_raw(", postalloc expanded");
}
#endif
#ifndef PRODUCT
void decodeN_nullBaseNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("SLDI    ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(", #3 \t// DecodeN (zerobased)");
}
#endif
#ifndef PRODUCT
void decodeN_mergeDisjointNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// base
  st->print_raw("RLDIMI  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(", shift, 32-shift \t// DecodeN (disjoint base)");
}
#endif
#ifndef PRODUCT
void decodeN_Disjoint_notNull_ExNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst
  st->print_raw("MOV     ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // dst
  st->print_raw(", heapbase \t\n");
  st->print_raw("RLDIMI  ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(", shift, 32-shift \t// decode with disjoint base");
}
#endif
#ifndef PRODUCT
void decodeN_Disjoint_isel_ExNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// crx
  st->print_raw("DecodeN  ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(" \t// decode with disjoint base using isel");
}
#endif
#ifndef PRODUCT
void decodeN_notNull_addBase_ExNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("DecodeN ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(" \t// ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(" != NULL, postalloc expanded");
}
#endif
#ifndef PRODUCT
void decodeN_unscaledNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("MR      ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(" \t// DecodeN (unscaled)");
}
#endif
#ifndef PRODUCT
void decodeN2I_unscaledNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("MR      ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(" \t// (int)DecodeN (unscaled)");
}
#endif
#ifndef PRODUCT
void encodePKlass_shiftNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("SRDI    ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(", 3 \t// encode");
}
#endif
#ifndef PRODUCT
void encodePKlass_sub_baseNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// base
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  st->print_raw("SUB     ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // base
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
  st->print_raw(" \t// encode");
}
#endif
#ifndef PRODUCT
void encodePKlass_DisjointNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("EXTRDI  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(", #32, #3 \t// encode with disjoint base");
}
#endif
#ifndef PRODUCT
void encodePKlass_not_null_ExNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// base
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  st->print_raw("EncodePKlass ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
  st->print_raw("\t// ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
  st->print_raw(" != Null, postalloc expanded");
}
#endif
#ifndef PRODUCT
void encodePKlass_not_null_ExExNode::format(PhaseRegAlloc *ra, outputStream *st) const {
}
#endif
#ifndef PRODUCT
void decodeNKlass_shiftNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("SLDI    ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(", #3 \t// DecodeNKlass");
}
#endif
#ifndef PRODUCT
void decodeNKlass_add_baseNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// base
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  st->print_raw("ADD     ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // base
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
  st->print_raw(" \t// DecodeNKlass, add klass base");
}
#endif
#ifndef PRODUCT
void decodeNKlass_notNull_addBase_ExNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// base
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  st->print_raw("DecodeNKlass ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(" =  ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // base
  st->print_raw(" + (");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
  st->print_raw(" << 3) \t// ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
  st->print_raw(" != NULL, postalloc expanded");
}
#endif
#ifndef PRODUCT
void decodeNKlass_notNull_addBase_ExExNode::format(PhaseRegAlloc *ra, outputStream *st) const {
}
#endif
#ifndef PRODUCT
void membar_acquireNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  st->print_raw("MEMBAR-acquire");
}
#endif
#ifndef PRODUCT
void unnecessary_membar_acquireNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  st->print_raw(" -- \t// redundant MEMBAR-acquire - empty");
}
#endif
#ifndef PRODUCT
void membar_acquire_lockNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  st->print_raw(" -- \t// redundant MEMBAR-acquire - empty (acquire as part of CAS in prior FastLock)");
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
void membar_storestoreNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  st->print_raw("MEMBAR-store-store");
}
#endif
#ifndef PRODUCT
void membar_release_lockNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  st->print_raw(" -- \t// redundant MEMBAR-release - empty (release in FastUnlock)");
}
#endif
#ifndef PRODUCT
void membar_volatileNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  st->print_raw("MEMBAR-volatile");
}
#endif
#ifndef PRODUCT
void membar_CPUOrderNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  st->print_raw(" -- \t// MEMBAR-CPUOrder - empty: PPC64 processors are self-consistent.");
}
#endif
#ifndef PRODUCT
void cmovI_reg_iselNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// cmp
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// crx
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// dst
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src
  st->print_raw("CMOVE   ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // cmp
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // crx
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // dst
  st->print_raw(", ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // src
  st->print_raw("\n\t");
}
#endif
#ifndef PRODUCT
void cmovI_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// cmp
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// crx
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// dst
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src
  st->print_raw("CMOVE   ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // cmp
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // crx
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // dst
  st->print_raw(", ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // src
  st->print_raw("\n\t");
}
#endif
#ifndef PRODUCT
void cmovI_immNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// cmp
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// crx
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// dst
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src
  st->print_raw("CMOVE   ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // cmp
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // crx
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // dst
  st->print_raw(", ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // src
  st->print_raw("\n\t");
}
#endif
#ifndef PRODUCT
void cmovL_reg_iselNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// cmp
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// crx
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// dst
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src
  st->print_raw("CMOVE   ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // cmp
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // crx
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // dst
  st->print_raw(", ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // src
  st->print_raw("\n\t");
}
#endif
#ifndef PRODUCT
void cmovL_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// cmp
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// crx
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// dst
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src
  st->print_raw("CMOVE   ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // cmp
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // crx
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // dst
  st->print_raw(", ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // src
  st->print_raw("\n\t");
}
#endif
#ifndef PRODUCT
void cmovL_immNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// cmp
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// crx
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// dst
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src
  st->print_raw("CMOVE   ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // cmp
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // crx
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // dst
  st->print_raw(", ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // src
  st->print_raw("\n\t");
}
#endif
#ifndef PRODUCT
void cmovN_reg_iselNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// cmp
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// crx
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// dst
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src
  st->print_raw("CMOVE   ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // cmp
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // crx
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // dst
  st->print_raw(", ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // src
  st->print_raw("\n\t");
}
#endif
#ifndef PRODUCT
void cmovN_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// cmp
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// crx
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// dst
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src
  st->print_raw("CMOVE   ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // cmp
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // crx
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // dst
  st->print_raw(", ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // src
  st->print_raw("\n\t");
}
#endif
#ifndef PRODUCT
void cmovN_immNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// cmp
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// crx
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// dst
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src
  st->print_raw("CMOVE   ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // cmp
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // crx
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // dst
  st->print_raw(", ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // src
  st->print_raw("\n\t");
}
#endif
#ifndef PRODUCT
void cmovP_reg_iselNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// cmp
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// crx
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// dst
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src
  st->print_raw("CMOVE   ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // cmp
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // crx
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // dst
  st->print_raw(", ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // src
  st->print_raw("\n\t");
}
#endif
#ifndef PRODUCT
void cmovP_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// cmp
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// crx
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// dst
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src
  st->print_raw("CMOVE   ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // cmp
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // crx
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // dst
  st->print_raw(", ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // src
  st->print_raw("\n\t");
}
#endif
#ifndef PRODUCT
void cmovP_immNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// cmp
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// crx
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// dst
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src
  st->print_raw("CMOVE   ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // cmp
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // crx
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // dst
  st->print_raw(", ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // src
  st->print_raw("\n\t");
}
#endif
#ifndef PRODUCT
void cmovF_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// cmp
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// crx
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// dst
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src
  st->print_raw("CMOVEF  ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // cmp
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // crx
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // dst
  st->print_raw(", ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // src
  st->print_raw("\n\t");
}
#endif
#ifndef PRODUCT
void cmovD_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// cmp
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// crx
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// dst
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// src
  st->print_raw("CMOVEF  ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // cmp
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // crx
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // dst
  st->print_raw(", ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // src
  st->print_raw("\n\t");
}
#endif
#ifndef PRODUCT
void storeLConditional_regP_regL_regLNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem_ptr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// oldVal
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// newVal
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// cr0
  st->print_raw("CMPXCHGD if (");
  opnd_array(0)->int_format(ra, this, st); // crx
  st->print_raw(" = (");
  opnd_array(2)->ext_format(ra, this,idx2, st); // oldVal
  st->print_raw(" == *");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem_ptr
  st->print_raw(")) *mem_ptr = ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // newVal
  st->print_raw("; as bool");
}
#endif
#ifndef PRODUCT
void storePConditional_regP_regP_regPNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem_ptr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// oldVal
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// newVal
  st->print_raw("STDCX_  if (");
  opnd_array(0)->int_format(ra, this, st); // cr0
  st->print_raw(" = (");
  opnd_array(2)->ext_format(ra, this,idx2, st); // oldVal
  st->print_raw(" == *");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem_ptr
  st->print_raw(")) *mem_ptr = ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // newVal
  st->print_raw("; as bool");
}
#endif
#ifndef PRODUCT
void loadPLockedNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem
  st->print_raw("LDARX   ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem
  st->print_raw(" \t// loadPLocked\n\t");
  if (ra->C->alias_type(adr_type())->field() != NULL) {
    ciField* f = ra->C->alias_type(adr_type())->field();
    st->print(" 	// Field: ");
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
void compareAndSwapB_regP_regI_regINode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem_ptr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// res
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// cr0
  st->print_raw("CMPXCHGB ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // res
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem_ptr
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src1
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src2
  st->print_raw("; as bool");
}
#endif
#ifndef PRODUCT
void compareAndSwapB4_regP_regI_regINode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem_ptr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// res
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// tmp1
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// tmp2
  unsigned idx7 = idx6 + opnd_array(6)->num_edges(); 	// cr0
  st->print_raw("CMPXCHGB ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // res
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem_ptr
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src1
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src2
  st->print_raw("; as bool");
}
#endif
#ifndef PRODUCT
void compareAndSwapS_regP_regI_regINode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem_ptr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// res
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// cr0
  st->print_raw("CMPXCHGH ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // res
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem_ptr
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src1
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src2
  st->print_raw("; as bool");
}
#endif
#ifndef PRODUCT
void compareAndSwapS4_regP_regI_regINode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem_ptr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// res
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// tmp1
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// tmp2
  unsigned idx7 = idx6 + opnd_array(6)->num_edges(); 	// cr0
  st->print_raw("CMPXCHGH ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // res
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem_ptr
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src1
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src2
  st->print_raw("; as bool");
}
#endif
#ifndef PRODUCT
void compareAndSwapI_regP_regI_regINode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem_ptr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// res
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// cr0
  st->print_raw("CMPXCHGW ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // res
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem_ptr
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src1
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src2
  st->print_raw("; as bool");
}
#endif
#ifndef PRODUCT
void compareAndSwapN_regP_regN_regNNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem_ptr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// res
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// cr0
  st->print_raw("CMPXCHGW ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // res
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem_ptr
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src1
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src2
  st->print_raw("; as bool");
}
#endif
#ifndef PRODUCT
void compareAndSwapL_regP_regL_regLNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem_ptr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// res
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// cr0
  st->print_raw("CMPXCHGD ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // res
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem_ptr
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src1
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src2
  st->print_raw("; as bool");
}
#endif
#ifndef PRODUCT
void compareAndSwapP_regP_regP_regPNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem_ptr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// res
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// cr0
  st->print_raw("CMPXCHGD ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // res
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem_ptr
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src1
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src2
  st->print_raw("; as bool; ptr");
}
#endif
#ifndef PRODUCT
void weakCompareAndSwapB_regP_regI_regINode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem_ptr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// res
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// cr0
  st->print_raw("weak CMPXCHGB ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // res
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem_ptr
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src1
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src2
  st->print_raw("; as bool");
}
#endif
#ifndef PRODUCT
void weakCompareAndSwapB4_regP_regI_regINode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem_ptr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// res
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// tmp1
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// tmp2
  unsigned idx7 = idx6 + opnd_array(6)->num_edges(); 	// cr0
  st->print_raw("weak CMPXCHGB ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // res
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem_ptr
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src1
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src2
  st->print_raw("; as bool");
}
#endif
#ifndef PRODUCT
void weakCompareAndSwapB_acq_regP_regI_regINode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem_ptr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// res
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// cr0
  st->print_raw("weak CMPXCHGB acq ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // res
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem_ptr
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src1
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src2
  st->print_raw("; as bool");
}
#endif
#ifndef PRODUCT
void weakCompareAndSwapB4_acq_regP_regI_regINode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem_ptr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// res
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// tmp1
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// tmp2
  unsigned idx7 = idx6 + opnd_array(6)->num_edges(); 	// cr0
  st->print_raw("weak CMPXCHGB acq ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // res
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem_ptr
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src1
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src2
  st->print_raw("; as bool");
}
#endif
#ifndef PRODUCT
void weakCompareAndSwapS_regP_regI_regINode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem_ptr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// res
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// cr0
  st->print_raw("weak CMPXCHGH ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // res
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem_ptr
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src1
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src2
  st->print_raw("; as bool");
}
#endif
#ifndef PRODUCT
void weakCompareAndSwapS4_regP_regI_regINode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem_ptr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// res
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// tmp1
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// tmp2
  unsigned idx7 = idx6 + opnd_array(6)->num_edges(); 	// cr0
  st->print_raw("weak CMPXCHGH ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // res
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem_ptr
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src1
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src2
  st->print_raw("; as bool");
}
#endif
#ifndef PRODUCT
void weakCompareAndSwapS_acq_regP_regI_regINode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem_ptr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// res
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// cr0
  st->print_raw("weak CMPXCHGH acq ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // res
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem_ptr
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src1
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src2
  st->print_raw("; as bool");
}
#endif
#ifndef PRODUCT
void weakCompareAndSwapS4_acq_regP_regI_regINode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem_ptr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// res
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// tmp1
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// tmp2
  unsigned idx7 = idx6 + opnd_array(6)->num_edges(); 	// cr0
  st->print_raw("weak CMPXCHGH acq ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // res
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem_ptr
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src1
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src2
  st->print_raw("; as bool");
}
#endif
#ifndef PRODUCT
void weakCompareAndSwapI_regP_regI_regINode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem_ptr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// res
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// cr0
  st->print_raw("weak CMPXCHGW ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // res
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem_ptr
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src1
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src2
  st->print_raw("; as bool");
}
#endif
#ifndef PRODUCT
void weakCompareAndSwapI_acq_regP_regI_regINode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem_ptr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// res
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// cr0
  st->print_raw("weak CMPXCHGW acq ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // res
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem_ptr
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src1
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src2
  st->print_raw("; as bool");
}
#endif
#ifndef PRODUCT
void weakCompareAndSwapN_regP_regN_regNNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem_ptr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// res
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// cr0
  st->print_raw("weak CMPXCHGW ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // res
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem_ptr
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src1
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src2
  st->print_raw("; as bool");
}
#endif
#ifndef PRODUCT
void weakCompareAndSwapN_acq_regP_regN_regNNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem_ptr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// res
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// cr0
  st->print_raw("weak CMPXCHGW acq ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // res
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem_ptr
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src1
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src2
  st->print_raw("; as bool");
}
#endif
#ifndef PRODUCT
void weakCompareAndSwapL_regP_regL_regLNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem_ptr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// res
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// cr0
  st->print_raw("weak CMPXCHGD ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // res
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem_ptr
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src1
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src2
  st->print_raw("; as bool");
}
#endif
#ifndef PRODUCT
void weakCompareAndSwapL_acq_regP_regL_regLNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem_ptr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// res
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// cr0
  st->print_raw("weak CMPXCHGD acq ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // res
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem_ptr
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src1
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src2
  st->print_raw("; as bool");
}
#endif
#ifndef PRODUCT
void weakCompareAndSwapP_regP_regP_regPNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem_ptr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// res
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// cr0
  st->print_raw("weak CMPXCHGD ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // res
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem_ptr
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src1
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src2
  st->print_raw("; as bool; ptr");
}
#endif
#ifndef PRODUCT
void weakCompareAndSwapP_acq_regP_regP_regPNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem_ptr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// res
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// cr0
  st->print_raw("weak CMPXCHGD acq ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // res
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem_ptr
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src1
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src2
  st->print_raw("; as bool; ptr");
}
#endif
#ifndef PRODUCT
void compareAndExchangeB_regP_regI_regINode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem_ptr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// res
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// cr0
  st->print_raw("CMPXCHGB ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // res
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem_ptr
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src1
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src2
  st->print_raw("; as int");
}
#endif
#ifndef PRODUCT
void compareAndExchangeB4_regP_regI_regINode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem_ptr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// res
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// tmp1
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// cr0
  st->print_raw("CMPXCHGB ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // res
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem_ptr
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src1
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src2
  st->print_raw("; as int");
}
#endif
#ifndef PRODUCT
void compareAndExchangeB_acq_regP_regI_regINode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem_ptr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// res
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// cr0
  st->print_raw("CMPXCHGB acq ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // res
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem_ptr
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src1
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src2
  st->print_raw("; as int");
}
#endif
#ifndef PRODUCT
void compareAndExchangeB4_acq_regP_regI_regINode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem_ptr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// res
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// tmp1
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// cr0
  st->print_raw("CMPXCHGB acq ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // res
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem_ptr
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src1
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src2
  st->print_raw("; as int");
}
#endif
#ifndef PRODUCT
void compareAndExchangeS_regP_regI_regINode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem_ptr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// res
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// cr0
  st->print_raw("CMPXCHGH ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // res
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem_ptr
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src1
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src2
  st->print_raw("; as int");
}
#endif
#ifndef PRODUCT
void compareAndExchangeS4_regP_regI_regINode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem_ptr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// res
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// tmp1
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// cr0
  st->print_raw("CMPXCHGH ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // res
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem_ptr
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src1
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src2
  st->print_raw("; as int");
}
#endif
#ifndef PRODUCT
void compareAndExchangeS_acq_regP_regI_regINode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem_ptr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// res
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// cr0
  st->print_raw("CMPXCHGH acq ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // res
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem_ptr
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src1
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src2
  st->print_raw("; as int");
}
#endif
#ifndef PRODUCT
void compareAndExchangeS4_acq_regP_regI_regINode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem_ptr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// res
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// tmp1
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// cr0
  st->print_raw("CMPXCHGH acq ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // res
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem_ptr
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src1
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src2
  st->print_raw("; as int");
}
#endif
#ifndef PRODUCT
void compareAndExchangeI_regP_regI_regINode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem_ptr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// res
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// cr0
  st->print_raw("CMPXCHGW ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // res
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem_ptr
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src1
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src2
  st->print_raw("; as int");
}
#endif
#ifndef PRODUCT
void compareAndExchangeI_acq_regP_regI_regINode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem_ptr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// res
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// cr0
  st->print_raw("CMPXCHGW acq ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // res
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem_ptr
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src1
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src2
  st->print_raw("; as int");
}
#endif
#ifndef PRODUCT
void compareAndExchangeN_regP_regN_regNNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem_ptr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// res
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// cr0
  st->print_raw("CMPXCHGW ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // res
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem_ptr
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src1
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src2
  st->print_raw("; as narrow oop");
}
#endif
#ifndef PRODUCT
void compareAndExchangeN_acq_regP_regN_regNNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem_ptr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// res
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// cr0
  st->print_raw("CMPXCHGW acq ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // res
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem_ptr
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src1
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src2
  st->print_raw("; as narrow oop");
}
#endif
#ifndef PRODUCT
void compareAndExchangeL_regP_regL_regLNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem_ptr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// res
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// cr0
  st->print_raw("CMPXCHGD ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // res
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem_ptr
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src1
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src2
  st->print_raw("; as long");
}
#endif
#ifndef PRODUCT
void compareAndExchangeL_acq_regP_regL_regLNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem_ptr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// res
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// cr0
  st->print_raw("CMPXCHGD acq ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // res
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem_ptr
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src1
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src2
  st->print_raw("; as long");
}
#endif
#ifndef PRODUCT
void compareAndExchangeP_regP_regP_regPNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem_ptr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// res
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// cr0
  st->print_raw("CMPXCHGD ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // res
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem_ptr
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src1
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src2
  st->print_raw("; as ptr; ptr");
}
#endif
#ifndef PRODUCT
void compareAndExchangeP_acq_regP_regP_regPNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem_ptr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// res
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// cr0
  st->print_raw("CMPXCHGD acq ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // res
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem_ptr
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src1
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src2
  st->print_raw("; as ptr; ptr");
}
#endif
#ifndef PRODUCT
void getAndAddBNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem_ptr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// res
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// cr0
  st->print_raw("GetAndAddB ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // res
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem_ptr
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
}
#endif
#ifndef PRODUCT
void getAndAddB4Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem_ptr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// res
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// tmp1
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// tmp2
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// cr0
  st->print_raw("GetAndAddB ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // res
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem_ptr
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
}
#endif
#ifndef PRODUCT
void getAndAddSNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem_ptr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// res
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// cr0
  st->print_raw("GetAndAddS ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // res
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem_ptr
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
}
#endif
#ifndef PRODUCT
void getAndAddS4Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem_ptr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// res
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// tmp1
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// tmp2
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// cr0
  st->print_raw("GetAndAddS ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // res
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem_ptr
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
}
#endif
#ifndef PRODUCT
void getAndAddINode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem_ptr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// res
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// cr0
  st->print_raw("GetAndAddI ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // res
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem_ptr
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
}
#endif
#ifndef PRODUCT
void getAndAddLNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem_ptr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// res
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// cr0
  st->print_raw("GetAndAddL ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // res
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem_ptr
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
}
#endif
#ifndef PRODUCT
void getAndSetBNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem_ptr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// res
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// cr0
  st->print_raw("GetAndSetB ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // res
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem_ptr
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
}
#endif
#ifndef PRODUCT
void getAndSetB4Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem_ptr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// res
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// tmp1
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// tmp2
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// cr0
  st->print_raw("GetAndSetB ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // res
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem_ptr
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
}
#endif
#ifndef PRODUCT
void getAndSetSNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem_ptr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// res
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// cr0
  st->print_raw("GetAndSetS ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // res
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem_ptr
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
}
#endif
#ifndef PRODUCT
void getAndSetS4Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem_ptr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// res
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// tmp1
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// tmp2
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// cr0
  st->print_raw("GetAndSetS ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // res
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem_ptr
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
}
#endif
#ifndef PRODUCT
void getAndSetINode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem_ptr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// res
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// cr0
  st->print_raw("GetAndSetI ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // res
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem_ptr
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
}
#endif
#ifndef PRODUCT
void getAndSetLNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem_ptr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// res
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// cr0
  st->print_raw("GetAndSetL ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // res
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem_ptr
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
}
#endif
#ifndef PRODUCT
void getAndSetPNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem_ptr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// res
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// cr0
  st->print_raw("GetAndSetP ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // res
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem_ptr
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
}
#endif
#ifndef PRODUCT
void getAndSetNNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// mem_ptr
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// res
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// cr0
  st->print_raw("GetAndSetN ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // res
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // mem_ptr
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
}
#endif
#ifndef PRODUCT
void addI_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("ADD     ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void addI_reg_reg_2Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("ADD     ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void tree_addI_addI_addI_reg_reg_ExNode::format(PhaseRegAlloc *ra, outputStream *st) const {
}
#endif
#ifndef PRODUCT
void tree_addI_addI_addI_reg_reg_Ex_1Node::format(PhaseRegAlloc *ra, outputStream *st) const {
}
#endif
#ifndef PRODUCT
void tree_addI_addI_addI_reg_reg_Ex_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
}
#endif
#ifndef PRODUCT
void tree_addI_addI_addI_reg_reg_Ex_2Node::format(PhaseRegAlloc *ra, outputStream *st) const {
}
#endif
#ifndef PRODUCT
void addI_reg_imm16Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("ADDI    ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void addI_reg_immhi16Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("ADDIS   ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void addL_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("ADD     ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(" \t// long");
}
#endif
#ifndef PRODUCT
void addL_reg_reg_2Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("ADD     ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(" \t// long");
}
#endif
#ifndef PRODUCT
void tree_addL_addL_addL_reg_reg_ExNode::format(PhaseRegAlloc *ra, outputStream *st) const {
}
#endif
#ifndef PRODUCT
void tree_addL_addL_addL_reg_reg_Ex_1Node::format(PhaseRegAlloc *ra, outputStream *st) const {
}
#endif
#ifndef PRODUCT
void tree_addL_addL_addL_reg_reg_Ex_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
}
#endif
#ifndef PRODUCT
void tree_addL_addL_addL_reg_reg_Ex_2Node::format(PhaseRegAlloc *ra, outputStream *st) const {
}
#endif
#ifndef PRODUCT
void addI_regL_regLNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("ADD     ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(" \t// long + l2i");
}
#endif
#ifndef PRODUCT
void addL_reg_imm16Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("ADDI    ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void addL_reg_immhi16Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("ADDIS   ");
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
  st->print_raw("ADD     ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void addP_reg_imm16Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("ADDI    ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void addP_reg_immhi16Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("ADDIS   ");
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
  st->print_raw("SUBF    ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
}
#endif
#ifndef PRODUCT
void subI_imm16_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("SUBI    ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void signmask32I_regINode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("SRAWI   ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(", #31");
}
#endif
#ifndef PRODUCT
void absI_reg_ExNode::format(PhaseRegAlloc *ra, outputStream *st) const {
}
#endif
#ifndef PRODUCT
void negI_regINode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// zero
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("NEG     ");
  opnd_array(0)->int_format(ra, this, st); // dst
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
  st->print_raw("SUBF    ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(" \t// long");
}
#endif
#ifndef PRODUCT
void subI_regL_regLNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("SUBF    ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(" \t// long + l2i");
}
#endif
#ifndef PRODUCT
void signmask64I_regLNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("SRADI   ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(", #63");
}
#endif
#ifndef PRODUCT
void signmask64L_regLNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("SRADI   ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(", #63");
}
#endif
#ifndef PRODUCT
void negL_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// zero
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("NEG     ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(" \t// long");
}
#endif
#ifndef PRODUCT
void negI_con0_regLNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// zero
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("NEG     ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(" \t// long + l2i");
}
#endif
#ifndef PRODUCT
void mulI_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("MULLW   ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void mulI_reg_imm16Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("MULLI   ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void mulL_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("MULLD   ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(" ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(" \t// long");
}
#endif
#ifndef PRODUCT
void mulHighL_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("MULHD   ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(" ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(" \t// long");
}
#endif
#ifndef PRODUCT
void mulL_reg_imm16Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("MULLI   ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void divI_reg_immIvalueMinus1Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("NEG     ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(" \t// /-1");
}
#endif
#ifndef PRODUCT
void divI_reg_regnotMinus1Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("DIVW    ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(" \t// /not-1");
}
#endif
#ifndef PRODUCT
void cmovI_bne_negI_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// crx
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// 
  st->print_raw("CMOVE   ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst
  st->print_raw(", neg(");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src1
  st->print_raw("), ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // crx
}
#endif
#ifndef PRODUCT
void divI_reg_reg_ExNode::format(PhaseRegAlloc *ra, outputStream *st) const {
}
#endif
#ifndef PRODUCT
void divL_reg_immLvalueMinus1Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("NEG     ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(" \t// /-1, long");
}
#endif
#ifndef PRODUCT
void divL_reg_regnotMinus1Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("DIVD    ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(" \t// /not-1, long");
}
#endif
#ifndef PRODUCT
void cmovL_bne_negL_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// crx
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// 
  st->print_raw("CMOVE   ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst
  st->print_raw(", neg(");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src1
  st->print_raw("), ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // crx
}
#endif
#ifndef PRODUCT
void divL_reg_reg_ExNode::format(PhaseRegAlloc *ra, outputStream *st) const {
}
#endif
#ifndef PRODUCT
void modI_reg_reg_ExNode::format(PhaseRegAlloc *ra, outputStream *st) const {
}
#endif
#ifndef PRODUCT
void modL_reg_reg_ExNode::format(PhaseRegAlloc *ra, outputStream *st) const {
}
#endif
#ifndef PRODUCT
void maskI_reg_immNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// mask
  st->print_raw("MASK    ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // mask
  st->print_raw(" \t// clear ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // mask
  st->print_raw(" upper bits");
}
#endif
#ifndef PRODUCT
void lShiftI_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("SLW     ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void lShiftI_reg_reg_ExNode::format(PhaseRegAlloc *ra, outputStream *st) const {
}
#endif
#ifndef PRODUCT
void lShiftI_reg_immNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("SLWI    ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", (");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(" & 0x1f)");
}
#endif
#ifndef PRODUCT
void lShiftI_andI_immInegpow2_imm5Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src3
  st->print_raw("RLWINM  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", lShiftI(AndI(");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw("), ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src3
  st->print_raw(")");
}
#endif
#ifndef PRODUCT
void lShiftI_andI_immInegpow2_rShiftI_imm5Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src3
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  st->print_raw("RLWINM  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", lShiftI(AndI(RShiftI(");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src3
  st->print_raw("), ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src2
  st->print_raw("), ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src3
  st->print_raw(")");
}
#endif
#ifndef PRODUCT
void lShiftL_regL_regINode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("SLD     ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void lShiftL_regL_regI_ExNode::format(PhaseRegAlloc *ra, outputStream *st) const {
}
#endif
#ifndef PRODUCT
void lshiftL_regL_immINode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("SLDI    ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", (");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(" & 0x3f)");
}
#endif
#ifndef PRODUCT
void lShiftL_regI_immGE32Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("SLDI    ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", i2l(");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw("), ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void scaledPositiveI2L_lShiftL_convI2L_reg_imm6Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("SLDI    ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", i2l(positive_int(");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(")), ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void arShiftI_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("SRAW    ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void arShiftI_reg_reg_ExNode::format(PhaseRegAlloc *ra, outputStream *st) const {
}
#endif
#ifndef PRODUCT
void arShiftI_reg_immNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("SRAWI   ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", (");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(" & 0x1f)");
}
#endif
#ifndef PRODUCT
void arShiftL_regL_regINode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("SRAD    ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void arShiftL_regL_regI_ExNode::format(PhaseRegAlloc *ra, outputStream *st) const {
}
#endif
#ifndef PRODUCT
void arShiftL_regL_immINode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("SRADI   ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", (");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(" & 0x3f)");
}
#endif
#ifndef PRODUCT
void convL2I_arShiftL_regL_immINode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("SRADI   ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", (");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(" & 0x3f) \t// long + l2i");
}
#endif
#ifndef PRODUCT
void urShiftI_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("SRW     ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void urShiftI_reg_reg_ExNode::format(PhaseRegAlloc *ra, outputStream *st) const {
}
#endif
#ifndef PRODUCT
void urShiftI_reg_immNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("SRWI    ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", (");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(" & 0x1f)");
}
#endif
#ifndef PRODUCT
void urShiftL_regL_regINode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("SRD     ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void urShiftL_regL_regI_ExNode::format(PhaseRegAlloc *ra, outputStream *st) const {
}
#endif
#ifndef PRODUCT
void urShiftL_regL_immINode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("SRDI    ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", (");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(" & 0x3f)");
}
#endif
#ifndef PRODUCT
void convL2I_urShiftL_regL_immINode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("SRDI    ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", (");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(" & 0x3f) \t// long + l2i");
}
#endif
#ifndef PRODUCT
void shrP_convP2X_reg_imm6Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("SRDI    ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(" \t// Cast ptr ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(" to long and shift");
}
#endif
#ifndef PRODUCT
void andI_urShiftI_regI_immI_immIpow2minus1Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src3
  st->print_raw("EXTRDI  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", shift=");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", mask=");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src3
  st->print_raw(" \t// int bitfield extract");
}
#endif
#ifndef PRODUCT
void andL_urShiftL_regL_immI_immLpow2minus1Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src3
  st->print_raw("EXTRDI  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", shift=");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", mask=");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src3
  st->print_raw(" \t// long bitfield extract");
}
#endif
#ifndef PRODUCT
void sxtI_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("EXTSW   ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(" \t// int->int");
}
#endif
#ifndef PRODUCT
void rotlI_reg_immi8Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// lshift
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// rshift
  st->print_raw("ROTLWI  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // lshift
}
#endif
#ifndef PRODUCT
void rotlI_reg_immi8_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// rshift
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// lshift
  st->print_raw("ROTLWI  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // lshift
}
#endif
#ifndef PRODUCT
void rotrI_reg_immi8Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// rshift
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// lshift
  st->print_raw("ROTRWI  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // rshift
}
#endif
#ifndef PRODUCT
void rotrI_reg_immi8_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// lshift
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// rshift
  st->print_raw("ROTRWI  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // rshift
}
#endif
#ifndef PRODUCT
void addF_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("FADDS   ");
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
  st->print_raw("FADD    ");
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
  st->print_raw("FSUBS   ");
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
  st->print_raw("FSUB    ");
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
  st->print_raw("FMULS   ");
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
  st->print_raw("FMUL    ");
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
  st->print_raw("FDIVS   ");
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
  st->print_raw("FDIV    ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void absF_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("FABS    ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(" \t// float");
}
#endif
#ifndef PRODUCT
void absD_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("FABS    ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(" \t// double");
}
#endif
#ifndef PRODUCT
void negF_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("FNEG    ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(" \t// float");
}
#endif
#ifndef PRODUCT
void negD_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("FNEG    ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(" \t// double");
}
#endif
#ifndef PRODUCT
void negF_absF_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("FNABS   ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(" \t// float");
}
#endif
#ifndef PRODUCT
void negD_absD_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("FNABS   ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(" \t// double");
}
#endif
#ifndef PRODUCT
void sqrtD_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("FSQRT   ");
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
  st->print_raw("FSQRTS  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
}
#endif
#ifndef PRODUCT
void roundDouble_nopNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  st->print_raw(" -- \t// RoundDouble not needed - empty");
}
#endif
#ifndef PRODUCT
void roundFloat_nopNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  st->print_raw(" -- \t// RoundFloat not needed - empty");
}
#endif
#ifndef PRODUCT
void maddF_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src3
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  st->print_raw("FMADDS  ");
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
  st->print_raw("FMADD   ");
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
  st->print_raw("FNMSUBS ");
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
void mnsubF_reg_reg_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src3
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  st->print_raw("FNMSUBS ");
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
  st->print_raw("FNMSUB  ");
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
void mnsubD_reg_reg_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src3
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  st->print_raw("FNMSUB  ");
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
  st->print_raw("FNMADDS ");
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
void mnaddF_reg_reg_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src3
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  st->print_raw("FNMADDS ");
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
  st->print_raw("FNMADD  ");
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
void mnaddD_reg_reg_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src3
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  st->print_raw("FNMADD  ");
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
  st->print_raw("FMSUBS  ");
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
  st->print_raw("FMSUB   ");
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
void andI_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("AND     ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void andI_reg_immIhi16Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("ANDIS   ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(".hi");
}
#endif
#ifndef PRODUCT
void andI_reg_uimm16Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("ANDI    ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void andI_reg_immInegpow2Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("ANDWI   ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void andI_reg_immIpow2minus1Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("ANDWI   ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void andI_reg_immIpowerOf2Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("ANDWI   ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void andL_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("AND     ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(" \t// long");
}
#endif
#ifndef PRODUCT
void andL_reg_uimm16Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("ANDI    ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(" \t// long");
}
#endif
#ifndef PRODUCT
void andL_reg_immLnegpow2Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("ANDDI   ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void andL_reg_immLpow2minus1Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("ANDDI   ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void convL2I_andL_reg_immLpow2minus1Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("ANDDI   ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(" \t// long + l2i");
}
#endif
#ifndef PRODUCT
void orI_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("OR      ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void orI_reg_reg_2Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("OR      ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void tree_orI_orI_orI_reg_reg_ExNode::format(PhaseRegAlloc *ra, outputStream *st) const {
}
#endif
#ifndef PRODUCT
void tree_orI_orI_orI_reg_reg_Ex_1Node::format(PhaseRegAlloc *ra, outputStream *st) const {
}
#endif
#ifndef PRODUCT
void tree_orI_orI_orI_reg_reg_Ex_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
}
#endif
#ifndef PRODUCT
void tree_orI_orI_orI_reg_reg_Ex_2Node::format(PhaseRegAlloc *ra, outputStream *st) const {
}
#endif
#ifndef PRODUCT
void orI_reg_uimm16Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("ORI     ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void orL_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("OR      ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(" \t// long");
}
#endif
#ifndef PRODUCT
void orI_regL_regLNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("OR      ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(" \t// long + l2i");
}
#endif
#ifndef PRODUCT
void orL_reg_uimm16Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// con
  st->print_raw("ORI     ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // con
  st->print_raw(" \t// long");
}
#endif
#ifndef PRODUCT
void xorI_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("XOR     ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void xorI_reg_reg_2Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("XOR     ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void tree_xorI_xorI_xorI_reg_reg_ExNode::format(PhaseRegAlloc *ra, outputStream *st) const {
}
#endif
#ifndef PRODUCT
void tree_xorI_xorI_xorI_reg_reg_Ex_1Node::format(PhaseRegAlloc *ra, outputStream *st) const {
}
#endif
#ifndef PRODUCT
void tree_xorI_xorI_xorI_reg_reg_Ex_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
}
#endif
#ifndef PRODUCT
void tree_xorI_xorI_xorI_reg_reg_Ex_2Node::format(PhaseRegAlloc *ra, outputStream *st) const {
}
#endif
#ifndef PRODUCT
void xorI_reg_uimm16Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("XORI    ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void xorL_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("XOR     ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(" \t// long");
}
#endif
#ifndef PRODUCT
void xorI_regL_regLNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("XOR     ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(" \t// long + l2i");
}
#endif
#ifndef PRODUCT
void xorL_reg_uimm16Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("XORI    ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(" \t// long");
}
#endif
#ifndef PRODUCT
void notI_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("NOT     ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(" (");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(")");
}
#endif
#ifndef PRODUCT
void notL_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("NOT     ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(" (");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(") \t// long");
}
#endif
#ifndef PRODUCT
void andcI_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src3
  st->print_raw("ANDW    ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", xori(");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw("), ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src3
}
#endif
#ifndef PRODUCT
void andcI_reg_reg_0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src3
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// src2
  st->print_raw("ANDW    ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", xori(");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src1
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src2
  st->print_raw("), ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src3
}
#endif
#ifndef PRODUCT
void andcL_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("ANDC    ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void moveL2D_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("MTFPRD  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
}
#endif
#ifndef PRODUCT
void moveI2D_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("MTFPRWA ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
}
#endif
#ifndef PRODUCT
void stkI_to_regINode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("LWZ     ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
}
#endif
#ifndef PRODUCT
void regI_to_stkINode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("STW     ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(", ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(" \t// stk");
}
#endif
#ifndef PRODUCT
void stkL_to_regLNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("LD      ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(" \t// long");
}
#endif
#ifndef PRODUCT
void regL_to_stkLNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("STD     ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(", ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(" \t// long");
}
#endif
#ifndef PRODUCT
void moveF2I_stack_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("LWZ     ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(" \t// MoveF2I");
}
#endif
#ifndef PRODUCT
void moveF2I_reg_stackNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("STFS    ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(", ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(" \t// MoveF2I");
}
#endif
#ifndef PRODUCT
void moveI2F_stack_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("LFS     ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(" \t// MoveI2F");
}
#endif
#ifndef PRODUCT
void moveI2F_reg_stackNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("STW     ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(", ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(" \t// MoveI2F");
}
#endif
#ifndef PRODUCT
void moveF2L_reg_stackNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("storeD  ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(", ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(" \t// STACK");
}
#endif
#ifndef PRODUCT
void moveD2L_stack_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("LD      ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(" \t// MoveD2L");
}
#endif
#ifndef PRODUCT
void moveD2L_reg_stackNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("STFD    ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(", ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(" \t// MoveD2L");
}
#endif
#ifndef PRODUCT
void moveL2D_stack_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("LFD     ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(" \t// MoveL2D");
}
#endif
#ifndef PRODUCT
void moveL2D_reg_stackNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("STD     ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(", ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(" \t// MoveL2D");
}
#endif
#ifndef PRODUCT
void moveRegNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("MR      ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(" \t// replicate ");
}
#endif
#ifndef PRODUCT
void castX2PNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("MR      ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(" \t// Long->Ptr");
}
#endif
#ifndef PRODUCT
void castP2XNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("MR      ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(" \t// Ptr->Long");
}
#endif
#ifndef PRODUCT
void castPPNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  st->print_raw(" -- \t// castPP of ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst
}
#endif
#ifndef PRODUCT
void castIINode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  st->print_raw(" -- \t// castII of ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst
}
#endif
#ifndef PRODUCT
void checkCastPPNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// dst
  st->print_raw(" -- \t// checkcastPP of ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst
}
#endif
#ifndef PRODUCT
void convI2Bool_reg__cntlz_ExNode::format(PhaseRegAlloc *ra, outputStream *st) const {
}
#endif
#ifndef PRODUCT
void convI2Bool_reg__cmoveNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// crx
  st->print_raw("CMPWI   ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // crx
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(", #0 \t// convI2B");
  st->print_raw("LI      ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", #0\n\t");
  st->print_raw("BEQ     ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // crx
  st->print_raw(", done\n\t");
  st->print_raw("LI      ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", #1\n");
  st->print_raw("done:");
}
#endif
#ifndef PRODUCT
void xorI_convI2Bool_reg_immIvalue1__cntlz_ExNode::format(PhaseRegAlloc *ra, outputStream *st) const {
}
#endif
#ifndef PRODUCT
void xorI_convI2Bool_reg_immIvalue1__cmoveNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// mask
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// crx
  st->print_raw("CMPWI   ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // crx
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(", #0 \t// Xor(convI2B(");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("), ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // mask
  st->print_raw(")");
  st->print_raw("LI      ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", #1\n\t");
  st->print_raw("BEQ     ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // crx
  st->print_raw(", done\n\t");
  st->print_raw("LI      ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", #0\n");
  st->print_raw("done:");
}
#endif
#ifndef PRODUCT
void convI2Bool_andI_reg_immIpowerOf2Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// mask
  st->print_raw("RLWINM  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // mask
  st->print_raw(" \t// convI2B(AndI(");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // mask
  st->print_raw("))");
}
#endif
#ifndef PRODUCT
void convP2Bool_reg__cntlz_ExNode::format(PhaseRegAlloc *ra, outputStream *st) const {
}
#endif
#ifndef PRODUCT
void convP2Bool_reg__cmoveNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// crx
  st->print_raw("CMPDI   ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // crx
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(", #0 \t// convP2B");
  st->print_raw("LI      ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", #0\n\t");
  st->print_raw("BEQ     ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // crx
  st->print_raw(", done\n\t");
  st->print_raw("LI      ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", #1\n");
  st->print_raw("done:");
}
#endif
#ifndef PRODUCT
void xorI_convP2Bool_reg__cntlz_ExNode::format(PhaseRegAlloc *ra, outputStream *st) const {
}
#endif
#ifndef PRODUCT
void xorI_convP2Bool_reg_immIvalue1__cmoveNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// mask
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// crx
  st->print_raw("CMPDI   ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // crx
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(", #0 \t// XorI(convP2B(");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw("), ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // mask
  st->print_raw(")");
  st->print_raw("LI      ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", #1\n\t");
  st->print_raw("BEQ     ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // crx
  st->print_raw(", done\n\t");
  st->print_raw("LI      ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", #0\n");
  st->print_raw("done:");
}
#endif
#ifndef PRODUCT
void cmpLTMask_reg_reg_ExNode::format(PhaseRegAlloc *ra, outputStream *st) const {
}
#endif
#ifndef PRODUCT
void cmpLTMask_reg_immI0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("SRAWI   ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(" \t// CmpLTMask");
}
#endif
#ifndef PRODUCT
void convB2I_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// amount
  st->print_raw("EXTSB   ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(" \t// byte->int");
}
#endif
#ifndef PRODUCT
void extshNode::format(PhaseRegAlloc *ra, outputStream *st) const {
}
#endif
#ifndef PRODUCT
void convS2I_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// amount
  st->print_raw("EXTSH   ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(" \t// short->int");
}
#endif
#ifndef PRODUCT
void sxtI_L2L_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("EXTSW   ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(" \t// long->long");
}
#endif
#ifndef PRODUCT
void convL2I_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("MR      ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(" \t// long->int");
}
#endif
#ifndef PRODUCT
void convD2IRaw_regDNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("FCTIWZ ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(" \t// convD2I, ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(" != NaN");
}
#endif
#ifndef PRODUCT
void cmovI_bso_stackSlotLNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// crx
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  st->print_raw("cmovI   ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // crx
  st->print_raw(", ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
}
#endif
#ifndef PRODUCT
void cmovI_bso_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// crx
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  st->print_raw("cmovI   ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // crx
  st->print_raw(", ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
}
#endif
#ifndef PRODUCT
void cmovI_bso_stackSlotL_conLvalue0_ExNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// crx
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// mem
  st->print_raw("CmovI   ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // crx
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // mem
  st->print_raw(" \t// postalloc expanded");
}
#endif
#ifndef PRODUCT
void cmovI_bso_reg_conLvalue0_ExNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// crx
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  st->print_raw("CmovI   ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // crx
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
  st->print_raw(" \t// postalloc expanded");
}
#endif
#ifndef PRODUCT
void convD2I_reg_ExExNode::format(PhaseRegAlloc *ra, outputStream *st) const {
}
#endif
#ifndef PRODUCT
void convD2I_reg_mffprd_ExExNode::format(PhaseRegAlloc *ra, outputStream *st) const {
}
#endif
#ifndef PRODUCT
void convF2IRaw_regFNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("FCTIWZ ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(" \t// convF2I, ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(" != NaN");
}
#endif
#ifndef PRODUCT
void convF2I_regF_ExExNode::format(PhaseRegAlloc *ra, outputStream *st) const {
}
#endif
#ifndef PRODUCT
void convF2I_regF_mffprd_ExExNode::format(PhaseRegAlloc *ra, outputStream *st) const {
}
#endif
#ifndef PRODUCT
void convI2L_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("EXTSW   ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(" \t// int->long");
}
#endif
#ifndef PRODUCT
void zeroExtendL_regINode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// mask
  st->print_raw("CLRLDI  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(", #32 \t// zero-extend int to long");
}
#endif
#ifndef PRODUCT
void zeroExtendL_regLNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// mask
  st->print_raw("CLRLDI  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(", #32 \t// zero-extend int to long");
}
#endif
#ifndef PRODUCT
void convF2LRaw_regFNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("FCTIDZ ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(" \t// convF2L, ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(" != NaN");
}
#endif
#ifndef PRODUCT
void cmovL_bso_stackSlotLNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// crx
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  st->print_raw("cmovL   ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // crx
  st->print_raw(", ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
}
#endif
#ifndef PRODUCT
void cmovL_bso_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// crx
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  st->print_raw("cmovL   ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // crx
  st->print_raw(", ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
}
#endif
#ifndef PRODUCT
void cmovL_bso_stackSlotL_conLvalue0_ExNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// crx
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// mem
  st->print_raw("CmovL   ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // crx
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // mem
  st->print_raw(" \t// postalloc expanded");
}
#endif
#ifndef PRODUCT
void cmovL_bso_reg_conLvalue0_ExNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// crx
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src
  st->print_raw("CmovL   ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // crx
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
  st->print_raw(" \t// postalloc expanded");
}
#endif
#ifndef PRODUCT
void convF2L_reg_ExExNode::format(PhaseRegAlloc *ra, outputStream *st) const {
}
#endif
#ifndef PRODUCT
void convF2L_reg_mffprd_ExExNode::format(PhaseRegAlloc *ra, outputStream *st) const {
}
#endif
#ifndef PRODUCT
void convD2LRaw_regDNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("FCTIDZ ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(" \t// convD2L ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(" != NaN");
}
#endif
#ifndef PRODUCT
void convD2L_reg_ExExNode::format(PhaseRegAlloc *ra, outputStream *st) const {
}
#endif
#ifndef PRODUCT
void convD2L_reg_mffprd_ExExNode::format(PhaseRegAlloc *ra, outputStream *st) const {
}
#endif
#ifndef PRODUCT
void convL2DRaw_regDNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("FCFID ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(" \t// convL2D");
}
#endif
#ifndef PRODUCT
void convD2F_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("FRSP    ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(" \t// convD2F");
}
#endif
#ifndef PRODUCT
void convI2F_ireg_ExNode::format(PhaseRegAlloc *ra, outputStream *st) const {
}
#endif
#ifndef PRODUCT
void convL2FRaw_regFNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("FCFIDS ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(" \t// convL2F");
}
#endif
#ifndef PRODUCT
void convI2F_ireg_fcfids_ExNode::format(PhaseRegAlloc *ra, outputStream *st) const {
}
#endif
#ifndef PRODUCT
void convI2F_ireg_mtfprd_ExNode::format(PhaseRegAlloc *ra, outputStream *st) const {
}
#endif
#ifndef PRODUCT
void convL2F_ireg_fcfids_ExNode::format(PhaseRegAlloc *ra, outputStream *st) const {
}
#endif
#ifndef PRODUCT
void convL2F_ireg_mtfprd_ExNode::format(PhaseRegAlloc *ra, outputStream *st) const {
}
#endif
#ifndef PRODUCT
void convI2D_reg_ExNode::format(PhaseRegAlloc *ra, outputStream *st) const {
}
#endif
#ifndef PRODUCT
void convI2D_reg_mtfprd_ExNode::format(PhaseRegAlloc *ra, outputStream *st) const {
}
#endif
#ifndef PRODUCT
void convL2D_reg_ExNode::format(PhaseRegAlloc *ra, outputStream *st) const {
}
#endif
#ifndef PRODUCT
void convL2D_reg_mtfprd_ExNode::format(PhaseRegAlloc *ra, outputStream *st) const {
}
#endif
#ifndef PRODUCT
void convF2D_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("FMR     ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(" \t// float->double");
}
#endif
#ifndef PRODUCT
void cmpI_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("CMPW    ");
  opnd_array(0)->int_format(ra, this, st); // crx
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void cmpI_reg_imm16Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("CMPWI   ");
  opnd_array(0)->int_format(ra, this, st); // crx
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void testI_reg_immNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// zero
  st->print_raw("ANDI    R0, ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(" \t// BTST int");
}
#endif
#ifndef PRODUCT
void cmpL_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("CMPD    ");
  opnd_array(0)->int_format(ra, this, st); // crx
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void cmpL_reg_imm16Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("CMPDI   ");
  opnd_array(0)->int_format(ra, this, st); // crx
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void cmpUL_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("CMPLD   ");
  opnd_array(0)->int_format(ra, this, st); // crx
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void cmpUL_reg_imm16Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("CMPLDI  ");
  opnd_array(0)->int_format(ra, this, st); // crx
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void testL_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// zero
  st->print_raw("AND     R0, ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(" \t// BTST long");
}
#endif
#ifndef PRODUCT
void testL_reg_immNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// zero
  st->print_raw("ANDI    R0, ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(" \t// BTST long");
}
#endif
#ifndef PRODUCT
void cmovI_conIvalueMinus1_conIvalue1Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// crx
  st->print_raw("cmovI   ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // crx
  st->print_raw(", ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", -1, 0, +1");
}
#endif
#ifndef PRODUCT
void cmovI_conIvalueMinus1_conIvalue0_conIvalue1_ExNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// crx
  st->print_raw("CmovI    ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // crx
  st->print_raw(", ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", -1, 0, +1 \t// postalloc expanded");
}
#endif
#ifndef PRODUCT
void cmpL3_reg_reg_ExExNode::format(PhaseRegAlloc *ra, outputStream *st) const {
}
#endif
#ifndef PRODUCT
void rangeCheck_iReg_uimm15Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src_length
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// index
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// labl
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// 
  st->print_raw("TWI     ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // index
  st->print_raw(" ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // cmp
  st->print_raw(" ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src_length
  st->print_raw(" \t// RangeCheck => trap ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // labl
  st->print("  P=%f C=%f",_prob,_fcnt);
}
#endif
#ifndef PRODUCT
void rangeCheck_iReg_iRegNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src_index
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src_length
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// labl
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// 
  st->print_raw("TW      ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src_index
  st->print_raw(" ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // cmp
  st->print_raw(" ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // src_length
  st->print_raw(" \t// RangeCheck => trap ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // labl
  st->print("  P=%f C=%f",_prob,_fcnt);
}
#endif
#ifndef PRODUCT
void rangeCheck_uimm15_iRegNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src_index
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// length
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// labl
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// 
  st->print_raw("TWI     ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src_index
  st->print_raw(" ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // cmp
  st->print_raw(" ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // length
  st->print_raw(" \t// RangeCheck => trap ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // labl
  st->print("  P=%f C=%f",_prob,_fcnt);
}
#endif
#ifndef PRODUCT
void compU_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("CMPLW   ");
  opnd_array(0)->int_format(ra, this, st); // crx
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(" \t// unsigned");
}
#endif
#ifndef PRODUCT
void compU_reg_uimm16Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("CMPLWI  ");
  opnd_array(0)->int_format(ra, this, st); // crx
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
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
  st->print_raw("TDI     ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // value
  st->print_raw(" ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // cmp
  st->print_raw(" ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // zero
  st->print_raw(" \t// ZeroCheckN => trap ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // labl
  st->print("  P=%f C=%f",_prob,_fcnt);
}
#endif
#ifndef PRODUCT
void cmpN_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("CMPLW   ");
  opnd_array(0)->int_format(ra, this, st); // crx
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(" \t// compressed ptr");
}
#endif
#ifndef PRODUCT
void cmpN_reg_imm0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("CMPLWI  ");
  opnd_array(0)->int_format(ra, this, st); // crx
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(" \t// compressed ptr");
}
#endif
#ifndef PRODUCT
void zeroCheckP_reg_imm0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// value
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// zero
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// labl
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// 
  st->print_raw("TDI     ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // value
  st->print_raw(" ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // cmp
  st->print_raw(" ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // zero
  st->print_raw(" \t// ZeroCheckP => trap ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // labl
  st->print("  P=%f C=%f",_prob,_fcnt);
}
#endif
#ifndef PRODUCT
void cmpP_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("CMPLD   ");
  opnd_array(0)->int_format(ra, this, st); // crx
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(" \t// ptr");
}
#endif
#ifndef PRODUCT
void cmpP_reg_nullNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("CMPLDI   ");
  opnd_array(0)->int_format(ra, this, st); // crx
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(" \t// ptr");
}
#endif
#ifndef PRODUCT
void cmpP_reg_imm16Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("CMPDI   ");
  opnd_array(0)->int_format(ra, this, st); // crx
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void cmpFUnordered_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("cmpFUrd ");
  opnd_array(0)->int_format(ra, this, st); // crx
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void cmov_bns_lessNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// 
  st->print_raw("cmov    ");
  opnd_array(0)->int_format(ra, this, st); // crx
}
#endif
#ifndef PRODUCT
void cmpF_reg_reg_ExNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("CmpF    ");
  opnd_array(0)->int_format(ra, this, st); // crx
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(" \t// postalloc expanded");
}
#endif
#ifndef PRODUCT
void cmpF3_reg_reg_ExExNode::format(PhaseRegAlloc *ra, outputStream *st) const {
}
#endif
#ifndef PRODUCT
void cmpDUnordered_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("cmpFUrd ");
  opnd_array(0)->int_format(ra, this, st); // crx
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
}
#endif
#ifndef PRODUCT
void cmpD_reg_reg_ExNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  st->print_raw("CmpD    ");
  opnd_array(0)->int_format(ra, this, st); // crx
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(" \t// postalloc expanded");
}
#endif
#ifndef PRODUCT
void cmpD3_reg_reg_ExExNode::format(PhaseRegAlloc *ra, outputStream *st) const {
}
#endif
#ifndef PRODUCT
void branchNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// 
  st->print_raw("B       ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // labl
}
#endif
#ifndef PRODUCT
void branchConNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// crx
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// lbl
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// 
  st->print_raw("B");
  opnd_array(1)->ext_format(ra, this,idx1, st); // cmp
  st->print_raw("     ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // crx
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // lbl
  st->print("  P=%f C=%f",_prob,_fcnt);
}
#endif
#ifndef PRODUCT
void branchConFarNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// crx
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// lbl
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// 
  st->print_raw("B_FAR");
  opnd_array(1)->ext_format(ra, this,idx1, st); // cmp
  st->print_raw(" ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // crx
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // lbl
  st->print("  P=%f C=%f",_prob,_fcnt);
}
#endif
#ifndef PRODUCT
void branchConSchedNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// crx
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// lbl
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// 
  st->print_raw("B_FAR");
  opnd_array(1)->ext_format(ra, this,idx1, st); // cmp
  st->print_raw(" ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // crx
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // lbl
  st->print("  P=%f C=%f",_prob,_fcnt);
}
#endif
#ifndef PRODUCT
void branchLoopEndNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// crx
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// labl
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// 
  st->print_raw("B");
  opnd_array(1)->ext_format(ra, this,idx1, st); // cmp
  st->print_raw("     ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // crx
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // labl
  st->print_raw(" \t// counted loop end");
  st->print("  P=%f C=%f",_prob,_fcnt);
}
#endif
#ifndef PRODUCT
void branchLoopEndFarNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// crx
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// labl
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// 
  st->print_raw("B_FAR");
  opnd_array(1)->ext_format(ra, this,idx1, st); // cmp
  st->print_raw(" ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // crx
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // labl
  st->print_raw(" \t// counted loop end");
  st->print("  P=%f C=%f",_prob,_fcnt);
}
#endif
#ifndef PRODUCT
void branchLoopEndSchedNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// crx
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// labl
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// 
  st->print_raw("B_FAR");
  opnd_array(1)->ext_format(ra, this,idx1, st); // cmp
  st->print_raw(" ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // crx
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // labl
  st->print_raw(" \t// counted loop end");
  st->print("  P=%f C=%f",_prob,_fcnt);
}
#endif
#ifndef PRODUCT
void partialSubtypeCheckNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// subklass
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// superklass
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// result
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// tmp_klass
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// tmp_arrayptr
  st->print_raw("PartialSubtypeCheck ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // result
  st->print_raw(" = (");
  opnd_array(1)->ext_format(ra, this,idx1, st); // subklass
  st->print_raw(" instanceOf ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // superklass
  st->print_raw(") tmp: ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // tmp_klass
  st->print_raw(", ");
  opnd_array(5)->ext_format(ra, this,idx5, st); // tmp_arrayptr
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
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // tmp1
  st->print_raw(", ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // tmp2
}
#endif
#ifndef PRODUCT
void cmpFastLock_tmNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// oop
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// box
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// tmp1
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// tmp2
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// tmp3
  st->print_raw("FASTLOCK  ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // oop
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // box
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // tmp1
  st->print_raw(", ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // tmp2
  st->print_raw(", ");
  opnd_array(5)->ext_format(ra, this,idx5, st); // tmp3
  st->print_raw(" (TM)");
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
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// tmp3
  st->print_raw("FASTUNLOCK  ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // oop
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // box
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // tmp1
  st->print_raw(", ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // tmp2
}
#endif
#ifndef PRODUCT
void cmpFastUnlock_tmNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// oop
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// box
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// tmp1
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// tmp2
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// tmp3
  st->print_raw("FASTUNLOCK  ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // oop
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // box
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // tmp1
  st->print_raw(", ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // tmp2
  st->print_raw(" (TM)");
}
#endif
#ifndef PRODUCT
void align_addrNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// mask
  st->print_raw("ANDDI   ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // mask
  st->print_raw(" \t// next aligned address");
}
#endif
#ifndef PRODUCT
void array_sizeNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// end
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// start
  st->print_raw("SUB     ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // end
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // start
  st->print_raw(" \t// array size in bytes");
}
#endif
#ifndef PRODUCT
void inlineCallClearArrayShortNode::format(PhaseRegAlloc *ra, outputStream *st) const {
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
void inlineCallClearArrayLargeNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// cnt
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// base
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// tmp
  st->print_raw("ClearArray ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // cnt
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // base
  st->print_raw(" \t// KILL ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // tmp
}
#endif
#ifndef PRODUCT
void inlineCallClearArrayNode::format(PhaseRegAlloc *ra, outputStream *st) const {
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
void string_compareLNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// str1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// cnt1
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// str2
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// cnt2
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// result
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// tmp
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
  st->print_raw(" \t// KILL ");
  opnd_array(6)->ext_format(ra, this,idx6, st); // tmp
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
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// tmp
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
  st->print_raw(" \t// KILL ");
  opnd_array(6)->ext_format(ra, this,idx6, st); // tmp
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
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// tmp
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
  st->print_raw(" \t// KILL ");
  opnd_array(6)->ext_format(ra, this,idx6, st); // tmp
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
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// tmp
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
  st->print_raw(" \t// KILL ");
  opnd_array(6)->ext_format(ra, this,idx6, st); // tmp
}
#endif
#ifndef PRODUCT
void string_equalsLNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// str1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// str2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// cnt
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// result
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// tmp
  st->print_raw("String Equals byte[] ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // str1
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // str2
  st->print_raw(",");
  opnd_array(3)->ext_format(ra, this,idx3, st); // cnt
  st->print_raw(" -> ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // result
  st->print_raw(" \t// KILL ");
  opnd_array(5)->ext_format(ra, this,idx5, st); // tmp
}
#endif
#ifndef PRODUCT
void string_equalsUNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// str1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// str2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// cnt
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// result
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// tmp
  st->print_raw("String Equals char[]  ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // str1
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // str2
  st->print_raw(",");
  opnd_array(3)->ext_format(ra, this,idx3, st); // cnt
  st->print_raw(" -> ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // result
  st->print_raw(" \t// KILL ");
  opnd_array(5)->ext_format(ra, this,idx5, st); // tmp
}
#endif
#ifndef PRODUCT
void array_equalsBNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// ary1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// ary2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// result
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// tmp1
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// tmp2
  st->print_raw("Array Equals ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // ary1
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // ary2
  st->print_raw(" -> ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // result
  st->print_raw(" \t// KILL ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // tmp1
  st->print_raw(",");
  opnd_array(5)->ext_format(ra, this,idx5, st); // tmp2
}
#endif
#ifndef PRODUCT
void array_equalsCNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// ary1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// ary2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// result
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// tmp1
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// tmp2
  st->print_raw("Array Equals ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // ary1
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // ary2
  st->print_raw(" -> ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // result
  st->print_raw(" \t// KILL ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // tmp1
  st->print_raw(",");
  opnd_array(5)->ext_format(ra, this,idx5, st); // tmp2
}
#endif
#ifndef PRODUCT
void indexOf_imm1_char_UNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// haystack
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// haycnt
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// needleImm
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// offsetImm
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// needlecntImm
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// tmp1
  unsigned idx7 = idx6 + opnd_array(6)->num_edges(); 	// tmp2
  st->print_raw("String IndexOf CSCL1 ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // haystack
  st->print_raw("[0..");
  opnd_array(2)->ext_format(ra, this,idx2, st); // haycnt
  st->print_raw("], ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // needleImm
  st->print_raw("+");
  opnd_array(4)->ext_format(ra, this,idx4, st); // offsetImm
  st->print_raw("[0..");
  opnd_array(5)->ext_format(ra, this,idx5, st); // needlecntImm
  st->print_raw("]");
  st->print_raw("-> ");
  opnd_array(0)->int_format(ra, this, st); // result
  st->print_raw(" \t// KILL ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // haycnt
  st->print_raw(", ");
  opnd_array(6)->ext_format(ra, this,idx6, st); // tmp1
  st->print_raw(", ");
  opnd_array(7)->ext_format(ra, this,idx7, st); // tmp2
  st->print_raw(", ");
      st->print_raw("CCR0");
  st->print_raw(", ");
      st->print_raw("CCR1");
}
#endif
#ifndef PRODUCT
void indexOf_imm1_char_LNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// haystack
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// haycnt
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// needleImm
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// offsetImm
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// needlecntImm
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// tmp1
  unsigned idx7 = idx6 + opnd_array(6)->num_edges(); 	// tmp2
  st->print_raw("String IndexOf CSCL1 ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // haystack
  st->print_raw("[0..");
  opnd_array(2)->ext_format(ra, this,idx2, st); // haycnt
  st->print_raw("], ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // needleImm
  st->print_raw("+");
  opnd_array(4)->ext_format(ra, this,idx4, st); // offsetImm
  st->print_raw("[0..");
  opnd_array(5)->ext_format(ra, this,idx5, st); // needlecntImm
  st->print_raw("]");
  st->print_raw("-> ");
  opnd_array(0)->int_format(ra, this, st); // result
  st->print_raw(" \t// KILL ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // haycnt
  st->print_raw(", ");
  opnd_array(6)->ext_format(ra, this,idx6, st); // tmp1
  st->print_raw(", ");
  opnd_array(7)->ext_format(ra, this,idx7, st); // tmp2
  st->print_raw(", ");
      st->print_raw("CCR0");
  st->print_raw(", ");
      st->print_raw("CCR1");
}
#endif
#ifndef PRODUCT
void indexOf_imm1_char_ULNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// haystack
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// haycnt
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// needleImm
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// offsetImm
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// needlecntImm
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// tmp1
  unsigned idx7 = idx6 + opnd_array(6)->num_edges(); 	// tmp2
  st->print_raw("String IndexOf CSCL1 ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // haystack
  st->print_raw("[0..");
  opnd_array(2)->ext_format(ra, this,idx2, st); // haycnt
  st->print_raw("], ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // needleImm
  st->print_raw("+");
  opnd_array(4)->ext_format(ra, this,idx4, st); // offsetImm
  st->print_raw("[0..");
  opnd_array(5)->ext_format(ra, this,idx5, st); // needlecntImm
  st->print_raw("]");
  st->print_raw("-> ");
  opnd_array(0)->int_format(ra, this, st); // result
  st->print_raw(" \t// KILL ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // haycnt
  st->print_raw(", ");
  opnd_array(6)->ext_format(ra, this,idx6, st); // tmp1
  st->print_raw(", ");
  opnd_array(7)->ext_format(ra, this,idx7, st); // tmp2
  st->print_raw(", ");
      st->print_raw("CCR0");
  st->print_raw(", ");
      st->print_raw("CCR1");
}
#endif
#ifndef PRODUCT
void indexOf_imm1_UNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// haystack
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// haycnt
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// needle
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// needlecntImm
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// tmp1
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// tmp2
  st->print_raw("String IndexOf SCL1 ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // haystack
  st->print_raw("[0..");
  opnd_array(2)->ext_format(ra, this,idx2, st); // haycnt
  st->print_raw("], ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // needle
  st->print_raw("[0..");
  opnd_array(4)->ext_format(ra, this,idx4, st); // needlecntImm
  st->print_raw("]");
  st->print_raw(" -> ");
  opnd_array(0)->int_format(ra, this, st); // result
  st->print_raw(" \t// KILL ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // haycnt
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // needle
  st->print_raw(", ");
  opnd_array(5)->ext_format(ra, this,idx5, st); // tmp1
  st->print_raw(", ");
  opnd_array(6)->ext_format(ra, this,idx6, st); // tmp2
  st->print_raw(", ");
      st->print_raw("CCR0");
  st->print_raw(", ");
      st->print_raw("CCR1");
}
#endif
#ifndef PRODUCT
void indexOf_imm1_LNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// haystack
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// haycnt
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// needle
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// needlecntImm
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// tmp1
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// tmp2
  st->print_raw("String IndexOf SCL1 ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // haystack
  st->print_raw("[0..");
  opnd_array(2)->ext_format(ra, this,idx2, st); // haycnt
  st->print_raw("], ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // needle
  st->print_raw("[0..");
  opnd_array(4)->ext_format(ra, this,idx4, st); // needlecntImm
  st->print_raw("]");
  st->print_raw(" -> ");
  opnd_array(0)->int_format(ra, this, st); // result
  st->print_raw(" \t// KILL ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // haycnt
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // needle
  st->print_raw(", ");
  opnd_array(5)->ext_format(ra, this,idx5, st); // tmp1
  st->print_raw(", ");
  opnd_array(6)->ext_format(ra, this,idx6, st); // tmp2
  st->print_raw(", ");
      st->print_raw("CCR0");
  st->print_raw(", ");
      st->print_raw("CCR1");
}
#endif
#ifndef PRODUCT
void indexOf_imm1_ULNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// haystack
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// haycnt
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// needle
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// needlecntImm
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// tmp1
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// tmp2
  st->print_raw("String IndexOf SCL1 ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // haystack
  st->print_raw("[0..");
  opnd_array(2)->ext_format(ra, this,idx2, st); // haycnt
  st->print_raw("], ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // needle
  st->print_raw("[0..");
  opnd_array(4)->ext_format(ra, this,idx4, st); // needlecntImm
  st->print_raw("]");
  st->print_raw(" -> ");
  opnd_array(0)->int_format(ra, this, st); // result
  st->print_raw(" \t// KILL ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // haycnt
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // needle
  st->print_raw(", ");
  opnd_array(5)->ext_format(ra, this,idx5, st); // tmp1
  st->print_raw(", ");
  opnd_array(6)->ext_format(ra, this,idx6, st); // tmp2
  st->print_raw(", ");
      st->print_raw("CCR0");
  st->print_raw(", ");
      st->print_raw("CCR1");
}
#endif
#ifndef PRODUCT
void indexOfChar_UNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// haystack
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// haycnt
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// ch
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// tmp1
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// tmp2
  st->print_raw("String IndexOfChar ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // haystack
  st->print_raw("[0..");
  opnd_array(2)->ext_format(ra, this,idx2, st); // haycnt
  st->print_raw("], ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // ch
  st->print_raw(" -> ");
  opnd_array(0)->int_format(ra, this, st); // result
  st->print_raw(" \t// KILL ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // haycnt
  st->print_raw(", ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // tmp1
  st->print_raw(", ");
  opnd_array(5)->ext_format(ra, this,idx5, st); // tmp2
  st->print_raw(", ");
      st->print_raw("CCR0");
  st->print_raw(", ");
      st->print_raw("CCR1");
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
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// tmp1
  unsigned idx7 = idx6 + opnd_array(6)->num_edges(); 	// tmp2
  unsigned idx8 = idx7 + opnd_array(7)->num_edges(); 	// tmp3
  unsigned idx9 = idx8 + opnd_array(8)->num_edges(); 	// tmp4
  unsigned idx10 = idx9 + opnd_array(9)->num_edges(); 	// tmp5
  st->print_raw("String IndexOf SCL ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // haystack
  st->print_raw("[0..");
  opnd_array(2)->ext_format(ra, this,idx2, st); // haycnt
  st->print_raw("], ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // needle
  st->print_raw("[0..");
  opnd_array(4)->ext_format(ra, this,idx4, st); // needlecntImm
  st->print_raw("]");
  st->print_raw(" -> ");
  opnd_array(5)->ext_format(ra, this,idx5, st); // result
  st->print_raw(" \t// KILL ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // haycnt
  st->print_raw(", ");
  opnd_array(6)->ext_format(ra, this,idx6, st); // tmp1
  st->print_raw(", ");
  opnd_array(7)->ext_format(ra, this,idx7, st); // tmp2
  st->print_raw(", ");
  opnd_array(8)->ext_format(ra, this,idx8, st); // tmp3
  st->print_raw(", ");
  opnd_array(9)->ext_format(ra, this,idx9, st); // tmp4
  st->print_raw(", ");
  opnd_array(10)->ext_format(ra, this,idx10, st); // tmp5
  st->print_raw(", ");
      st->print_raw("CCR0");
  st->print_raw(", ");
      st->print_raw("CCR1");
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
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// tmp1
  unsigned idx7 = idx6 + opnd_array(6)->num_edges(); 	// tmp2
  unsigned idx8 = idx7 + opnd_array(7)->num_edges(); 	// tmp3
  unsigned idx9 = idx8 + opnd_array(8)->num_edges(); 	// tmp4
  unsigned idx10 = idx9 + opnd_array(9)->num_edges(); 	// tmp5
  st->print_raw("String IndexOf SCL ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // haystack
  st->print_raw("[0..");
  opnd_array(2)->ext_format(ra, this,idx2, st); // haycnt
  st->print_raw("], ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // needle
  st->print_raw("[0..");
  opnd_array(4)->ext_format(ra, this,idx4, st); // needlecntImm
  st->print_raw("]");
  st->print_raw(" -> ");
  opnd_array(5)->ext_format(ra, this,idx5, st); // result
  st->print_raw(" \t// KILL ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // haycnt
  st->print_raw(", ");
  opnd_array(6)->ext_format(ra, this,idx6, st); // tmp1
  st->print_raw(", ");
  opnd_array(7)->ext_format(ra, this,idx7, st); // tmp2
  st->print_raw(", ");
  opnd_array(8)->ext_format(ra, this,idx8, st); // tmp3
  st->print_raw(", ");
  opnd_array(9)->ext_format(ra, this,idx9, st); // tmp4
  st->print_raw(", ");
  opnd_array(10)->ext_format(ra, this,idx10, st); // tmp5
  st->print_raw(", ");
      st->print_raw("CCR0");
  st->print_raw(", ");
      st->print_raw("CCR1");
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
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// tmp1
  unsigned idx7 = idx6 + opnd_array(6)->num_edges(); 	// tmp2
  unsigned idx8 = idx7 + opnd_array(7)->num_edges(); 	// tmp3
  unsigned idx9 = idx8 + opnd_array(8)->num_edges(); 	// tmp4
  unsigned idx10 = idx9 + opnd_array(9)->num_edges(); 	// tmp5
  st->print_raw("String IndexOf SCL ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // haystack
  st->print_raw("[0..");
  opnd_array(2)->ext_format(ra, this,idx2, st); // haycnt
  st->print_raw("], ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // needle
  st->print_raw("[0..");
  opnd_array(4)->ext_format(ra, this,idx4, st); // needlecntImm
  st->print_raw("]");
  st->print_raw(" -> ");
  opnd_array(5)->ext_format(ra, this,idx5, st); // result
  st->print_raw(" \t// KILL ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // haycnt
  st->print_raw(", ");
  opnd_array(6)->ext_format(ra, this,idx6, st); // tmp1
  st->print_raw(", ");
  opnd_array(7)->ext_format(ra, this,idx7, st); // tmp2
  st->print_raw(", ");
  opnd_array(8)->ext_format(ra, this,idx8, st); // tmp3
  st->print_raw(", ");
  opnd_array(9)->ext_format(ra, this,idx9, st); // tmp4
  st->print_raw(", ");
  opnd_array(10)->ext_format(ra, this,idx10, st); // tmp5
  st->print_raw(", ");
      st->print_raw("CCR0");
  st->print_raw(", ");
      st->print_raw("CCR1");
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
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// tmp1
  unsigned idx7 = idx6 + opnd_array(6)->num_edges(); 	// tmp2
  unsigned idx8 = idx7 + opnd_array(7)->num_edges(); 	// tmp3
  unsigned idx9 = idx8 + opnd_array(8)->num_edges(); 	// tmp4
  st->print_raw("String IndexOf ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // haystack
  st->print_raw("[0..");
  opnd_array(2)->ext_format(ra, this,idx2, st); // haycnt
  st->print_raw("], ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // needle
  st->print_raw("[0..");
  opnd_array(4)->ext_format(ra, this,idx4, st); // needlecnt
  st->print_raw("]");
  st->print_raw(" -> ");
  opnd_array(5)->ext_format(ra, this,idx5, st); // result
  st->print_raw(" \t// KILL ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // haycnt
  st->print_raw(", ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // needlecnt
  st->print_raw(", ");
  opnd_array(6)->ext_format(ra, this,idx6, st); // tmp1
  st->print_raw(", ");
  opnd_array(7)->ext_format(ra, this,idx7, st); // tmp2
  st->print_raw(", ");
  opnd_array(8)->ext_format(ra, this,idx8, st); // tmp3
  st->print_raw(", ");
  opnd_array(9)->ext_format(ra, this,idx9, st); // tmp4
  st->print_raw(", ");
      st->print_raw("CCR0");
  st->print_raw(", ");
      st->print_raw("CCR1");
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
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// tmp1
  unsigned idx7 = idx6 + opnd_array(6)->num_edges(); 	// tmp2
  unsigned idx8 = idx7 + opnd_array(7)->num_edges(); 	// tmp3
  unsigned idx9 = idx8 + opnd_array(8)->num_edges(); 	// tmp4
  st->print_raw("String IndexOf ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // haystack
  st->print_raw("[0..");
  opnd_array(2)->ext_format(ra, this,idx2, st); // haycnt
  st->print_raw("], ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // needle
  st->print_raw("[0..");
  opnd_array(4)->ext_format(ra, this,idx4, st); // needlecnt
  st->print_raw("]");
  st->print_raw(" -> ");
  opnd_array(5)->ext_format(ra, this,idx5, st); // result
  st->print_raw(" \t// KILL ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // haycnt
  st->print_raw(", ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // needlecnt
  st->print_raw(", ");
  opnd_array(6)->ext_format(ra, this,idx6, st); // tmp1
  st->print_raw(", ");
  opnd_array(7)->ext_format(ra, this,idx7, st); // tmp2
  st->print_raw(", ");
  opnd_array(8)->ext_format(ra, this,idx8, st); // tmp3
  st->print_raw(", ");
  opnd_array(9)->ext_format(ra, this,idx9, st); // tmp4
  st->print_raw(", ");
      st->print_raw("CCR0");
  st->print_raw(", ");
      st->print_raw("CCR1");
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
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// tmp1
  unsigned idx7 = idx6 + opnd_array(6)->num_edges(); 	// tmp2
  unsigned idx8 = idx7 + opnd_array(7)->num_edges(); 	// tmp3
  unsigned idx9 = idx8 + opnd_array(8)->num_edges(); 	// tmp4
  st->print_raw("String IndexOf ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // haystack
  st->print_raw("[0..");
  opnd_array(2)->ext_format(ra, this,idx2, st); // haycnt
  st->print_raw("], ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // needle
  st->print_raw("[0..");
  opnd_array(4)->ext_format(ra, this,idx4, st); // needlecnt
  st->print_raw("]");
  st->print_raw(" -> ");
  opnd_array(5)->ext_format(ra, this,idx5, st); // result
  st->print_raw(" \t// KILL ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // haycnt
  st->print_raw(", ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // needlecnt
  st->print_raw(", ");
  opnd_array(6)->ext_format(ra, this,idx6, st); // tmp1
  st->print_raw(", ");
  opnd_array(7)->ext_format(ra, this,idx7, st); // tmp2
  st->print_raw(", ");
  opnd_array(8)->ext_format(ra, this,idx8, st); // tmp3
  st->print_raw(", ");
  opnd_array(9)->ext_format(ra, this,idx9, st); // tmp4
  st->print_raw(", ");
      st->print_raw("CCR0");
  st->print_raw(", ");
      st->print_raw("CCR1");
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
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// tmp1
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// tmp2
  unsigned idx7 = idx6 + opnd_array(6)->num_edges(); 	// tmp3
  unsigned idx8 = idx7 + opnd_array(7)->num_edges(); 	// tmp4
  unsigned idx9 = idx8 + opnd_array(8)->num_edges(); 	// tmp5
  st->print_raw("String Compress ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // dst
  st->print_raw(",");
  opnd_array(3)->ext_format(ra, this,idx3, st); // len
  st->print_raw(" -> ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // result
  st->print_raw(" \t// KILL ");
  opnd_array(5)->ext_format(ra, this,idx5, st); // tmp1
  st->print_raw(", ");
  opnd_array(6)->ext_format(ra, this,idx6, st); // tmp2
  st->print_raw(", ");
  opnd_array(7)->ext_format(ra, this,idx7, st); // tmp3
  st->print_raw(", ");
  opnd_array(8)->ext_format(ra, this,idx8, st); // tmp4
  st->print_raw(", ");
  opnd_array(9)->ext_format(ra, this,idx9, st); // tmp5
}
#endif
#ifndef PRODUCT
void string_inflateNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// dst
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// len
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// tmp1
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// tmp2
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// tmp3
  unsigned idx7 = idx6 + opnd_array(6)->num_edges(); 	// tmp4
  unsigned idx8 = idx7 + opnd_array(7)->num_edges(); 	// tmp5
  st->print_raw("String Inflate ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // dst
  st->print_raw(",");
  opnd_array(3)->ext_format(ra, this,idx3, st); // len
  st->print_raw(" \t// KILL ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // tmp1
  st->print_raw(", ");
  opnd_array(5)->ext_format(ra, this,idx5, st); // tmp2
  st->print_raw(", ");
  opnd_array(6)->ext_format(ra, this,idx6, st); // tmp3
  st->print_raw(", ");
  opnd_array(7)->ext_format(ra, this,idx7, st); // tmp4
  st->print_raw(", ");
  opnd_array(8)->ext_format(ra, this,idx8, st); // tmp5
}
#endif
#ifndef PRODUCT
void has_negativesNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 2;
  unsigned idx1 = 2; 	// ary1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// len
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// result
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// tmp1
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// tmp2
  st->print_raw("has negatives byte[] ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // ary1
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // len
  st->print_raw(" -> ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // result
  st->print_raw(" \t// KILL ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // tmp1
  st->print_raw(", ");
  opnd_array(5)->ext_format(ra, this,idx5, st); // tmp2
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
  unsigned idx5 = idx4 + opnd_array(4)->num_edges(); 	// tmp1
  unsigned idx6 = idx5 + opnd_array(5)->num_edges(); 	// tmp2
  unsigned idx7 = idx6 + opnd_array(6)->num_edges(); 	// tmp3
  unsigned idx8 = idx7 + opnd_array(7)->num_edges(); 	// tmp4
  unsigned idx9 = idx8 + opnd_array(8)->num_edges(); 	// tmp5
  st->print_raw("Encode array ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(",");
  opnd_array(2)->ext_format(ra, this,idx2, st); // dst
  st->print_raw(",");
  opnd_array(3)->ext_format(ra, this,idx3, st); // len
  st->print_raw(" -> ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // result
  st->print_raw(" \t// KILL ");
  opnd_array(5)->ext_format(ra, this,idx5, st); // tmp1
  st->print_raw(", ");
  opnd_array(6)->ext_format(ra, this,idx6, st); // tmp2
  st->print_raw(", ");
  opnd_array(7)->ext_format(ra, this,idx7, st); // tmp3
  st->print_raw(", ");
  opnd_array(8)->ext_format(ra, this,idx8, st); // tmp4
  st->print_raw(", ");
  opnd_array(9)->ext_format(ra, this,idx9, st); // tmp5
}
#endif
#ifndef PRODUCT
void minI_reg_reg_ExNode::format(PhaseRegAlloc *ra, outputStream *st) const {
}
#endif
#ifndef PRODUCT
void minI_reg_reg_iselNode::format(PhaseRegAlloc *ra, outputStream *st) const {
}
#endif
#ifndef PRODUCT
void maxI_reg_reg_ExNode::format(PhaseRegAlloc *ra, outputStream *st) const {
}
#endif
#ifndef PRODUCT
void maxI_reg_reg_iselNode::format(PhaseRegAlloc *ra, outputStream *st) const {
}
#endif
#ifndef PRODUCT
void popCountINode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("POPCNTW ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
}
#endif
#ifndef PRODUCT
void popCountLNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("POPCNTD ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
}
#endif
#ifndef PRODUCT
void countLeadingZerosINode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("CNTLZW  ");
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
  st->print_raw("CNTLZD  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
}
#endif
#ifndef PRODUCT
void countLeadingZerosPNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("CNTLZD  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
}
#endif
#ifndef PRODUCT
void countTrailingZerosI_ExNode::format(PhaseRegAlloc *ra, outputStream *st) const {
}
#endif
#ifndef PRODUCT
void countTrailingZerosL_ExNode::format(PhaseRegAlloc *ra, outputStream *st) const {
}
#endif
#ifndef PRODUCT
void insrwi_aNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// pos
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// shift
  st->print_raw("INSRWI  ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // pos
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // shift
}
#endif
#ifndef PRODUCT
void insrwiNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// pos
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// shift
  unsigned idx4 = idx3 + opnd_array(3)->num_edges(); 	// 
  st->print_raw("INSRWI  ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // pos
  st->print_raw(", ");
  opnd_array(4)->ext_format(ra, this,idx4, st); // shift
}
#endif
#ifndef PRODUCT
void bytes_reverse_int_ExNode::format(PhaseRegAlloc *ra, outputStream *st) const {
}
#endif
#ifndef PRODUCT
void bytes_reverse_long_ExNode::format(PhaseRegAlloc *ra, outputStream *st) const {
}
#endif
#ifndef PRODUCT
void bytes_reverse_ushort_ExNode::format(PhaseRegAlloc *ra, outputStream *st) const {
}
#endif
#ifndef PRODUCT
void bytes_reverse_short_ExNode::format(PhaseRegAlloc *ra, outputStream *st) const {
}
#endif
#ifndef PRODUCT
void loadI_reversedNode::format(PhaseRegAlloc *ra, outputStream *st) const {
}
#endif
#ifndef PRODUCT
void loadL_reversedNode::format(PhaseRegAlloc *ra, outputStream *st) const {
}
#endif
#ifndef PRODUCT
void loadUS_reversedNode::format(PhaseRegAlloc *ra, outputStream *st) const {
}
#endif
#ifndef PRODUCT
void loadS_reversedNode::format(PhaseRegAlloc *ra, outputStream *st) const {
}
#endif
#ifndef PRODUCT
void storeI_reversedNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  if (ra->C->alias_type(adr_type())->field() != NULL) {
    ciField* f = ra->C->alias_type(adr_type())->field();
    st->print(" 	// Field: ");
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
void storeL_reversedNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  if (ra->C->alias_type(adr_type())->field() != NULL) {
    ciField* f = ra->C->alias_type(adr_type())->field();
    st->print(" 	// Field: ");
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
void storeUS_reversedNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  if (ra->C->alias_type(adr_type())->field() != NULL) {
    ciField* f = ra->C->alias_type(adr_type())->field();
    st->print(" 	// Field: ");
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
void storeS_reversedNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  if (ra->C->alias_type(adr_type())->field() != NULL) {
    ciField* f = ra->C->alias_type(adr_type())->field();
    st->print(" 	// Field: ");
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
void mtvsrwzNode::format(PhaseRegAlloc *ra, outputStream *st) const {
}
#endif
#ifndef PRODUCT
void xxspltwNode::format(PhaseRegAlloc *ra, outputStream *st) const {
}
#endif
#ifndef PRODUCT
void repl32Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// 
  st->print_raw("INSRDI  ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst
  st->print_raw(", #0, ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst
  st->print_raw(", #32 \t// replicate");
}
#endif
#ifndef PRODUCT
void repl48Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// 
  st->print_raw("INSRDI  ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst
  st->print_raw(", #0, ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst
  st->print_raw(", #48 \t// replicate");
}
#endif
#ifndef PRODUCT
void repl56Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// 
  st->print_raw("INSRDI  ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst
  st->print_raw(", #0, ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // dst
  st->print_raw(", #56 \t// replicate");
}
#endif
#ifndef PRODUCT
void repl8B_reg_ExNode::format(PhaseRegAlloc *ra, outputStream *st) const {
}
#endif
#ifndef PRODUCT
void repl8B_immI0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// zero
  st->print_raw("LI      ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", #0 \t// replicate8B");
}
#endif
#ifndef PRODUCT
void repl8B_immIminus1Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("LI      ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", #-1 \t// replicate8B");
}
#endif
#ifndef PRODUCT
void repl16B_reg_ExNode::format(PhaseRegAlloc *ra, outputStream *st) const {
}
#endif
#ifndef PRODUCT
void repl16B_immI0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// zero
  st->print_raw("XXLXOR      ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // zero
  st->print_raw(" \t// replicate16B");
}
#endif
#ifndef PRODUCT
void repl16B_immIminus1Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("XXLEQV      ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(" \t// replicate16B");
}
#endif
#ifndef PRODUCT
void repl4S_reg_ExNode::format(PhaseRegAlloc *ra, outputStream *st) const {
}
#endif
#ifndef PRODUCT
void repl4S_immI0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// zero
  st->print_raw("LI      ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", #0 \t// replicate4C");
}
#endif
#ifndef PRODUCT
void repl4S_immIminus1Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("LI      ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", -1 \t// replicate4C");
}
#endif
#ifndef PRODUCT
void repl8S_reg_ExNode::format(PhaseRegAlloc *ra, outputStream *st) const {
}
#endif
#ifndef PRODUCT
void repl8S_immI0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// zero
  st->print_raw("XXLXOR      ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // zero
  st->print_raw(" \t// replicate8S");
}
#endif
#ifndef PRODUCT
void repl8S_immIminus1Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("XXLEQV      ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(" \t// replicate16B");
}
#endif
#ifndef PRODUCT
void repl2I_reg_ExNode::format(PhaseRegAlloc *ra, outputStream *st) const {
}
#endif
#ifndef PRODUCT
void repl2I_immI0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// zero
  st->print_raw("LI      ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", #0 \t// replicate4C");
}
#endif
#ifndef PRODUCT
void repl2I_immIminus1Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("LI      ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", -1 \t// replicate4C");
}
#endif
#ifndef PRODUCT
void repl4I_reg_ExNode::format(PhaseRegAlloc *ra, outputStream *st) const {
}
#endif
#ifndef PRODUCT
void repl4I_immI0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// zero
  st->print_raw("XXLXOR      ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // zero
  st->print_raw(" \t// replicate4I");
}
#endif
#ifndef PRODUCT
void repl4I_immIminus1Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("XXLEQV      ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(" \t// replicate4I");
}
#endif
#ifndef PRODUCT
void repl2F_reg_ExNode::format(PhaseRegAlloc *ra, outputStream *st) const {
}
#endif
#ifndef PRODUCT
void repl2F_immF_ExNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("LD      ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", offset, ");
  char reg[128];  ra->dump_register(in(mach_constant_base_node_input()), reg);
    st->print("%s", reg);
  st->print_raw("\t// load replicated float ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(" ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(" from table, postalloc expanded");
}
#endif
#ifndef PRODUCT
void repl2F_immF0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// zero
  st->print_raw("LI      ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", #0 \t// replicate2F");
}
#endif
#ifndef PRODUCT
void overflowAddL_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// op1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// op2
  st->print_raw("add_    ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // op1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // op2
  st->print_raw("\t# overflow check long");
}
#endif
#ifndef PRODUCT
void overflowSubL_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// op1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// op2
  st->print_raw("subfo_  R0, ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // op2
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // op1
  st->print_raw("\t# overflow check long");
}
#endif
#ifndef PRODUCT
void overflowNegL_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// zero
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// op2
  st->print_raw("nego_   R0, ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // op2
  st->print_raw("\t# overflow check long");
}
#endif
#ifndef PRODUCT
void overflowMulL_reg_regNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// op1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// op2
  st->print_raw("mulldo_ R0, ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // op1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // op2
  st->print_raw("\t# overflow check long");
}
#endif
#ifndef PRODUCT
void repl4F_reg_ExNode::format(PhaseRegAlloc *ra, outputStream *st) const {
}
#endif
#ifndef PRODUCT
void repl4F_immF_ExNode::format(PhaseRegAlloc *ra, outputStream *st) const {
}
#endif
#ifndef PRODUCT
void repl4F_immF0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// zero
  st->print_raw("XXLXOR      ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // zero
  st->print_raw(" \t// replicate4F");
}
#endif
#ifndef PRODUCT
void repl2D_reg_ExNode::format(PhaseRegAlloc *ra, outputStream *st) const {
}
#endif
#ifndef PRODUCT
void repl2D_immI0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// zero
  st->print_raw("XXLXOR      ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // zero
  st->print_raw(" \t// replicate2D");
}
#endif
#ifndef PRODUCT
void repl2D_immIminus1Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("XXLEQV      ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(" \t// replicate16B");
}
#endif
#ifndef PRODUCT
void mtvsrdNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("MTVSRD      ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(" \t// Move to 16-byte register");
}
#endif
#ifndef PRODUCT
void xxspltdNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// zero
  st->print_raw("XXSPLATD      ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // zero
  st->print_raw(" \t// Permute 16-byte register");
}
#endif
#ifndef PRODUCT
void xxpermdiNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src1
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// src2
  unsigned idx3 = idx2 + opnd_array(2)->num_edges(); 	// zero
  st->print_raw("XXPERMDI      ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src1
  st->print_raw(", ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // src2
  st->print_raw(", ");
  opnd_array(3)->ext_format(ra, this,idx3, st); // zero
  st->print_raw(" \t// Permute 16-byte register");
}
#endif
#ifndef PRODUCT
void repl2L_reg_ExNode::format(PhaseRegAlloc *ra, outputStream *st) const {
}
#endif
#ifndef PRODUCT
void repl2L_immI0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// zero
  st->print_raw("XXLXOR      ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // zero
  st->print_raw(" \t// replicate2L");
}
#endif
#ifndef PRODUCT
void repl2L_immIminus1Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("XXLEQV      ");
  opnd_array(0)->int_format(ra, this, st); // dst
  st->print_raw(", ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
  st->print_raw(" \t// replicate16B");
}
#endif
#ifndef PRODUCT
void safePoint_pollNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 5;
  unsigned idx1 = 5; 	// 
  st->print_raw("LD      R0, #0, ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // poll
  st->print_raw(" \t// Safepoint poll for GC");
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
  st->print_raw("CALL,static ");
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
void CallDynamicJavaDirectSchedNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// 
  st->print_raw("BL        \t// dynamic ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // meth
  st->print_raw(" ==> ");
  _method->print_short_name(st);
  st->cr();
  if (_jvms) _jvms->format(ra, this, st); else st->print_cr("        No JVM State Info");
  st->print("        # ");
  if( _jvms && _oop_map ) _oop_map->print_on(st);
}
#endif
#ifndef PRODUCT
void CallDynamicJavaDirectSched_ExNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// 
  st->print_raw("CALL,dynamic ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // meth
  st->print_raw(" \t// postalloc expanded");
  _method->print_short_name(st);
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
  st->print_raw("CALL,runtime");
  st->print(" %s", _name);  st->cr();
  if (_jvms) _jvms->format(ra, this, st); else st->print_cr("        No JVM State Info");
  st->print("        # ");
  if( _jvms && _oop_map ) _oop_map->print_on(st);
}
#endif
#ifndef PRODUCT
void CallLeafDirect_mtctrNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// src
  st->print_raw("MTCTR   ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // src
}
#endif
#ifndef PRODUCT
void CallLeafDirectNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// 
  st->print_raw("BCTRL     \t// leaf call ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // meth
  st->print_raw(" ==> ");
  st->print(" %s", _name);  st->cr();
  if (_jvms) _jvms->format(ra, this, st); else st->print_cr("        No JVM State Info");
  st->print("        # ");
  if( _jvms && _oop_map ) _oop_map->print_on(st);
}
#endif
#ifndef PRODUCT
void CallLeafDirect_ExNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// 
  st->print_raw("CALL,runtime leaf ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // meth
  st->print_raw(" \t// postalloc expanded");
  st->print(" %s", _name);  st->cr();
  if (_jvms) _jvms->format(ra, this, st); else st->print_cr("        No JVM State Info");
  st->print("        # ");
  if( _jvms && _oop_map ) _oop_map->print_on(st);
}
#endif
#ifndef PRODUCT
void CallLeafNoFPDirect_ExNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 1;
  unsigned idx1 = 1; 	// 
  st->print_raw("CALL,runtime leaf nofp ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // meth
  st->print_raw(" \t// postalloc expanded");
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
  st->print_raw("MTCTR   ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // jump_target
  st->print_raw(" \t// ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // method_oop
  st->print_raw(" holds method oop\n\t");
  st->print_raw("BCTR         \t// tail call");
}
#endif
#ifndef PRODUCT
void RetNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  st->print_raw("BLR      \t// branch to link register");
}
#endif
#ifndef PRODUCT
void tailjmpIndNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  // Start at oper_input_base() and count operands
  unsigned idx0 = 5;
  unsigned idx1 = 5; 	// ex_oop
  unsigned idx2 = idx1 + opnd_array(1)->num_edges(); 	// 
  st->print_raw("LD      R4_ARG2 = LR\n\t");
  st->print_raw("MTCTR   ");
  opnd_array(1)->ext_format(ra, this,idx1, st); // jump_target
  st->print_raw("\n\t");
  st->print_raw("BCTR     \t// TailJump, exception oop: ");
  opnd_array(2)->ext_format(ra, this,idx2, st); // ex_oop
}
#endif
#ifndef PRODUCT
void CreateExceptionNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  st->print_raw(" -- \t// exception oop; no code emitted");
}
#endif
#ifndef PRODUCT
void RethrowExceptionNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  st->print_raw("Jmp     rethrow_stub");
}
#endif
#ifndef PRODUCT
void ShouldNotReachHereNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  st->print_raw("ShouldNotReachHere");
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
void endGroupNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  st->print_raw("End Bundle (ori r1, r1, 0)");
}
#endif
#ifndef PRODUCT
void fxNopNode::format(PhaseRegAlloc *ra, outputStream *st) const {
  st->print_raw("fxNop");
}
#endif
#ifndef PRODUCT
void fpNop0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  st->print_raw("fpNop0");
}
#endif
#ifndef PRODUCT
void fpNop1Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  st->print_raw("fpNop1");
}
#endif
#ifndef PRODUCT
void brNop0Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  st->print_raw("brNop0");
}
#endif
#ifndef PRODUCT
void brNop1Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  st->print_raw("brNop1");
}
#endif
#ifndef PRODUCT
void brNop2Node::format(PhaseRegAlloc *ra, outputStream *st) const {
  st->print_raw("brNop2");
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
// Check adlc -DPPC64=1
#ifndef PPC64
#  error "PPC64 must be defined"
#endif // PPC64
// Check adlc -D_LP64=1
#ifndef _LP64
#  error "_LP64 must be defined"
#endif // _LP64
