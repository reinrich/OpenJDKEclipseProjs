#line 1 "adGlobals_s390.hpp"
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


#ifndef GENERATED_ADFILES_ADGLOBALS_HPP
#define GENERATED_ADFILES_ADGLOBALS_HPP


// the number of reserved registers + machine registers.
#define REG_COUNT    65

// the number of save_on_entry + always_saved registers.
#define MAX_SAVED_ON_ENTRY_REG_COUNT    32
#define     SAVED_ON_ENTRY_REG_COUNT    0
#define   C_SAVED_ON_ENTRY_REG_COUNT    32

// Enumerate machine register numbers starting after reserved regs.
// in the order of occurrence in the register block.
enum MachRegisterNumbers {
  Z_R13_num,                // enum   0, regnum   0, reg encode  13
  Z_R13_H_num,              // enum   1, regnum   1, reg encode  99
  Z_R12_num,                // enum   2, regnum   2, reg encode  12
  Z_R12_H_num,              // enum   3, regnum   3, reg encode  99
  Z_R11_num,                // enum   4, regnum   4, reg encode  11
  Z_R11_H_num,              // enum   5, regnum   5, reg encode  99
  Z_R10_num,                // enum   6, regnum   6, reg encode  10
  Z_R10_H_num,              // enum   7, regnum   7, reg encode  99
  Z_R9_num,                 // enum   8, regnum   8, reg encode   9
  Z_R9_H_num,               // enum   9, regnum   9, reg encode  99
  Z_R8_num,                 // enum  10, regnum  10, reg encode   8
  Z_R8_H_num,               // enum  11, regnum  11, reg encode  99
  Z_R7_num,                 // enum  12, regnum  12, reg encode   7
  Z_R7_H_num,               // enum  13, regnum  13, reg encode  99
  Z_R1_num,                 // enum  14, regnum  14, reg encode   1
  Z_R1_H_num,               // enum  15, regnum  15, reg encode  99
  Z_R0_num,                 // enum  16, regnum  16, reg encode   0
  Z_R0_H_num,               // enum  17, regnum  17, reg encode  99
  Z_R6_num,                 // enum  18, regnum  18, reg encode   6
  Z_R6_H_num,               // enum  19, regnum  19, reg encode  99
  Z_R5_num,                 // enum  20, regnum  20, reg encode   5
  Z_R5_H_num,               // enum  21, regnum  21, reg encode  99
  Z_R4_num,                 // enum  22, regnum  22, reg encode   4
  Z_R4_H_num,               // enum  23, regnum  23, reg encode  99
  Z_R3_num,                 // enum  24, regnum  24, reg encode   3
  Z_R3_H_num,               // enum  25, regnum  25, reg encode  99
  Z_R2_num,                 // enum  26, regnum  26, reg encode   2
  Z_R2_H_num,               // enum  27, regnum  27, reg encode  99
  Z_R14_num,                // enum  28, regnum  28, reg encode  14
  Z_R14_H_num,              // enum  29, regnum  29, reg encode  99
  Z_R15_num,                // enum  30, regnum  30, reg encode  15
  Z_R15_H_num,              // enum  31, regnum  31, reg encode  99
  Z_F15_num,                // enum  32, regnum  32, reg encode  15
  Z_F15_H_num,              // enum  33, regnum  33, reg encode  99
  Z_F14_num,                // enum  34, regnum  34, reg encode  14
  Z_F14_H_num,              // enum  35, regnum  35, reg encode  99
  Z_F13_num,                // enum  36, regnum  36, reg encode  13
  Z_F13_H_num,              // enum  37, regnum  37, reg encode  99
  Z_F12_num,                // enum  38, regnum  38, reg encode  12
  Z_F12_H_num,              // enum  39, regnum  39, reg encode  99
  Z_F11_num,                // enum  40, regnum  40, reg encode  11
  Z_F11_H_num,              // enum  41, regnum  41, reg encode  99
  Z_F10_num,                // enum  42, regnum  42, reg encode  10
  Z_F10_H_num,              // enum  43, regnum  43, reg encode  99
  Z_F9_num,                 // enum  44, regnum  44, reg encode   9
  Z_F9_H_num,               // enum  45, regnum  45, reg encode  99
  Z_F8_num,                 // enum  46, regnum  46, reg encode   8
  Z_F8_H_num,               // enum  47, regnum  47, reg encode  99
  Z_F7_num,                 // enum  48, regnum  48, reg encode   7
  Z_F7_H_num,               // enum  49, regnum  49, reg encode  99
  Z_F5_num,                 // enum  50, regnum  50, reg encode   5
  Z_F5_H_num,               // enum  51, regnum  51, reg encode  99
  Z_F3_num,                 // enum  52, regnum  52, reg encode   3
  Z_F3_H_num,               // enum  53, regnum  53, reg encode  99
  Z_F1_num,                 // enum  54, regnum  54, reg encode   1
  Z_F1_H_num,               // enum  55, regnum  55, reg encode  99
  Z_F6_num,                 // enum  56, regnum  56, reg encode   6
  Z_F6_H_num,               // enum  57, regnum  57, reg encode  99
  Z_F4_num,                 // enum  58, regnum  58, reg encode   4
  Z_F4_H_num,               // enum  59, regnum  59, reg encode  99
  Z_F2_num,                 // enum  60, regnum  60, reg encode   2
  Z_F2_H_num,               // enum  61, regnum  61, reg encode  99
  Z_F0_num,                 // enum  62, regnum  62, reg encode   0
  Z_F0_H_num,               // enum  63, regnum  63, reg encode  99
  Z_CR_num,                 // enum  64, regnum  64, reg encode   0
  _last_Mach_Reg            // 65
};

// Size of register-mask in ints
#define RM_SIZE 6
// Unroll factor for loops over the data in a RegMask
#define FORALL_BODY BODY(0) BODY(1) BODY(2) BODY(3) BODY(4) BODY(5) 

class RegMask;

#endif // GENERATED_ADFILES_ADGLOBALS_HPP
