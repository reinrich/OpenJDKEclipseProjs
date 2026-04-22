#line 1 "adGlobals_s390.hpp"
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


#ifndef GENERATED_ADFILES_ADGLOBALS_HPP
#define GENERATED_ADFILES_ADGLOBALS_HPP


// the number of reserved registers + machine registers.
#define REG_COUNT    193

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
  Z_VR0_num,                // enum  64, regnum  64, reg encode   0
  Z_VR0_H_num,              // enum  65, regnum  65, reg encode   0
  Z_VR0_J_num,              // enum  66, regnum  66, reg encode   0
  Z_VR0_K_num,              // enum  67, regnum  67, reg encode   0
  Z_VR1_num,                // enum  68, regnum  68, reg encode   1
  Z_VR1_H_num,              // enum  69, regnum  69, reg encode   1
  Z_VR1_J_num,              // enum  70, regnum  70, reg encode   1
  Z_VR1_K_num,              // enum  71, regnum  71, reg encode   1
  Z_VR2_num,                // enum  72, regnum  72, reg encode   2
  Z_VR2_H_num,              // enum  73, regnum  73, reg encode   2
  Z_VR2_J_num,              // enum  74, regnum  74, reg encode   2
  Z_VR2_K_num,              // enum  75, regnum  75, reg encode   2
  Z_VR3_num,                // enum  76, regnum  76, reg encode   3
  Z_VR3_H_num,              // enum  77, regnum  77, reg encode   3
  Z_VR3_J_num,              // enum  78, regnum  78, reg encode   3
  Z_VR3_K_num,              // enum  79, regnum  79, reg encode   3
  Z_VR4_num,                // enum  80, regnum  80, reg encode   4
  Z_VR4_H_num,              // enum  81, regnum  81, reg encode   4
  Z_VR4_J_num,              // enum  82, regnum  82, reg encode   4
  Z_VR4_K_num,              // enum  83, regnum  83, reg encode   4
  Z_VR5_num,                // enum  84, regnum  84, reg encode   5
  Z_VR5_H_num,              // enum  85, regnum  85, reg encode   5
  Z_VR5_J_num,              // enum  86, regnum  86, reg encode   5
  Z_VR5_K_num,              // enum  87, regnum  87, reg encode   5
  Z_VR6_num,                // enum  88, regnum  88, reg encode   6
  Z_VR6_H_num,              // enum  89, regnum  89, reg encode   6
  Z_VR6_J_num,              // enum  90, regnum  90, reg encode   6
  Z_VR6_K_num,              // enum  91, regnum  91, reg encode   6
  Z_VR7_num,                // enum  92, regnum  92, reg encode   7
  Z_VR7_H_num,              // enum  93, regnum  93, reg encode   7
  Z_VR7_J_num,              // enum  94, regnum  94, reg encode   7
  Z_VR7_K_num,              // enum  95, regnum  95, reg encode   7
  Z_VR8_num,                // enum  96, regnum  96, reg encode   8
  Z_VR8_H_num,              // enum  97, regnum  97, reg encode   8
  Z_VR8_J_num,              // enum  98, regnum  98, reg encode   8
  Z_VR8_K_num,              // enum  99, regnum  99, reg encode   8
  Z_VR9_num,                // enum 100, regnum 100, reg encode   9
  Z_VR9_H_num,              // enum 101, regnum 101, reg encode   9
  Z_VR9_J_num,              // enum 102, regnum 102, reg encode   9
  Z_VR9_K_num,              // enum 103, regnum 103, reg encode   9
  Z_VR10_num,               // enum 104, regnum 104, reg encode  10
  Z_VR10_H_num,             // enum 105, regnum 105, reg encode  10
  Z_VR10_J_num,             // enum 106, regnum 106, reg encode  10
  Z_VR10_K_num,             // enum 107, regnum 107, reg encode  10
  Z_VR11_num,               // enum 108, regnum 108, reg encode  11
  Z_VR11_H_num,             // enum 109, regnum 109, reg encode  11
  Z_VR11_J_num,             // enum 110, regnum 110, reg encode  11
  Z_VR11_K_num,             // enum 111, regnum 111, reg encode  11
  Z_VR12_num,               // enum 112, regnum 112, reg encode  12
  Z_VR12_H_num,             // enum 113, regnum 113, reg encode  12
  Z_VR12_J_num,             // enum 114, regnum 114, reg encode  12
  Z_VR12_K_num,             // enum 115, regnum 115, reg encode  12
  Z_VR13_num,               // enum 116, regnum 116, reg encode  13
  Z_VR13_H_num,             // enum 117, regnum 117, reg encode  13
  Z_VR13_J_num,             // enum 118, regnum 118, reg encode  13
  Z_VR13_K_num,             // enum 119, regnum 119, reg encode  13
  Z_VR14_num,               // enum 120, regnum 120, reg encode  14
  Z_VR14_H_num,             // enum 121, regnum 121, reg encode  14
  Z_VR14_J_num,             // enum 122, regnum 122, reg encode  14
  Z_VR14_K_num,             // enum 123, regnum 123, reg encode  14
  Z_VR15_num,               // enum 124, regnum 124, reg encode  15
  Z_VR15_H_num,             // enum 125, regnum 125, reg encode  15
  Z_VR15_J_num,             // enum 126, regnum 126, reg encode  15
  Z_VR15_K_num,             // enum 127, regnum 127, reg encode  15
  Z_VR16_num,               // enum 128, regnum 128, reg encode  16
  Z_VR16_H_num,             // enum 129, regnum 129, reg encode  16
  Z_VR16_J_num,             // enum 130, regnum 130, reg encode  16
  Z_VR16_K_num,             // enum 131, regnum 131, reg encode  16
  Z_VR17_num,               // enum 132, regnum 132, reg encode  17
  Z_VR17_H_num,             // enum 133, regnum 133, reg encode  17
  Z_VR17_J_num,             // enum 134, regnum 134, reg encode  17
  Z_VR17_K_num,             // enum 135, regnum 135, reg encode  17
  Z_VR18_num,               // enum 136, regnum 136, reg encode  18
  Z_VR18_H_num,             // enum 137, regnum 137, reg encode  18
  Z_VR18_J_num,             // enum 138, regnum 138, reg encode  18
  Z_VR18_K_num,             // enum 139, regnum 139, reg encode  18
  Z_VR19_num,               // enum 140, regnum 140, reg encode  19
  Z_VR19_H_num,             // enum 141, regnum 141, reg encode  19
  Z_VR19_J_num,             // enum 142, regnum 142, reg encode  19
  Z_VR19_K_num,             // enum 143, regnum 143, reg encode  19
  Z_VR20_num,               // enum 144, regnum 144, reg encode  20
  Z_VR20_H_num,             // enum 145, regnum 145, reg encode  20
  Z_VR20_J_num,             // enum 146, regnum 146, reg encode  20
  Z_VR20_K_num,             // enum 147, regnum 147, reg encode  20
  Z_VR21_num,               // enum 148, regnum 148, reg encode  21
  Z_VR21_H_num,             // enum 149, regnum 149, reg encode  21
  Z_VR21_J_num,             // enum 150, regnum 150, reg encode  21
  Z_VR21_K_num,             // enum 151, regnum 151, reg encode  21
  Z_VR22_num,               // enum 152, regnum 152, reg encode  22
  Z_VR22_H_num,             // enum 153, regnum 153, reg encode  22
  Z_VR22_J_num,             // enum 154, regnum 154, reg encode  22
  Z_VR22_K_num,             // enum 155, regnum 155, reg encode  22
  Z_VR23_num,               // enum 156, regnum 156, reg encode  23
  Z_VR23_H_num,             // enum 157, regnum 157, reg encode  23
  Z_VR23_J_num,             // enum 158, regnum 158, reg encode  23
  Z_VR23_K_num,             // enum 159, regnum 159, reg encode  23
  Z_VR24_num,               // enum 160, regnum 160, reg encode  24
  Z_VR24_H_num,             // enum 161, regnum 161, reg encode  24
  Z_VR24_J_num,             // enum 162, regnum 162, reg encode  24
  Z_VR24_K_num,             // enum 163, regnum 163, reg encode  24
  Z_VR25_num,               // enum 164, regnum 164, reg encode  25
  Z_VR25_H_num,             // enum 165, regnum 165, reg encode  25
  Z_VR25_J_num,             // enum 166, regnum 166, reg encode  25
  Z_VR25_K_num,             // enum 167, regnum 167, reg encode  25
  Z_VR26_num,               // enum 168, regnum 168, reg encode  26
  Z_VR26_H_num,             // enum 169, regnum 169, reg encode  26
  Z_VR26_J_num,             // enum 170, regnum 170, reg encode  26
  Z_VR26_K_num,             // enum 171, regnum 171, reg encode  26
  Z_VR27_num,               // enum 172, regnum 172, reg encode  27
  Z_VR27_H_num,             // enum 173, regnum 173, reg encode  27
  Z_VR27_J_num,             // enum 174, regnum 174, reg encode  27
  Z_VR27_K_num,             // enum 175, regnum 175, reg encode  27
  Z_VR28_num,               // enum 176, regnum 176, reg encode  28
  Z_VR28_H_num,             // enum 177, regnum 177, reg encode  28
  Z_VR28_J_num,             // enum 178, regnum 178, reg encode  28
  Z_VR28_K_num,             // enum 179, regnum 179, reg encode  28
  Z_VR29_num,               // enum 180, regnum 180, reg encode  29
  Z_VR29_H_num,             // enum 181, regnum 181, reg encode  29
  Z_VR29_J_num,             // enum 182, regnum 182, reg encode  29
  Z_VR29_K_num,             // enum 183, regnum 183, reg encode  29
  Z_VR30_num,               // enum 184, regnum 184, reg encode  30
  Z_VR30_H_num,             // enum 185, regnum 185, reg encode  30
  Z_VR30_J_num,             // enum 186, regnum 186, reg encode  30
  Z_VR30_K_num,             // enum 187, regnum 187, reg encode  30
  Z_VR31_num,               // enum 188, regnum 188, reg encode  31
  Z_VR31_H_num,             // enum 189, regnum 189, reg encode  31
  Z_VR31_J_num,             // enum 190, regnum 190, reg encode  31
  Z_VR31_K_num,             // enum 191, regnum 191, reg encode  31
  Z_CR_num,                 // enum 192, regnum 192, reg encode   0
  _last_Mach_Reg            // 193
};

// Size of register-mask in ints
#define RM_SIZE_IN_INTS 12
// Minimum size of register-mask in ints
#define RM_SIZE_IN_INTS_MIN 7
// Unroll factor for loops over the data in a RegMask
#define FORALL_BODY BODY(0) BODY(1) BODY(2) BODY(3) BODY(4) BODY(5) BODY(6) BODY(7) BODY(8) BODY(9) BODY(10) BODY(11) 

class RegMask;

#endif // GENERATED_ADFILES_ADGLOBALS_HPP
