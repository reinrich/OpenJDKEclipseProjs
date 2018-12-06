#line 1 "adGlobals_ppc.hpp"
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


#ifndef GENERATED_ADFILES_ADGLOBALS_HPP
#define GENERATED_ADFILES_ADGLOBALS_HPP


// the number of reserved registers + machine registers.
#define REG_COUNT    206

// the number of save_on_entry + always_saved registers.
#define MAX_SAVED_ON_ENTRY_REG_COUNT    72
#define     SAVED_ON_ENTRY_REG_COUNT    0
#define   C_SAVED_ON_ENTRY_REG_COUNT    72

// Enumerate machine register numbers starting after reserved regs.
// in the order of occurrence in the register block.
enum MachRegisterNumbers {
  R14_num,                  // enum   0, regnum   0, reg encode  14
  R14_H_num,                // enum   1, regnum   1, reg encode  99
  R15_num,                  // enum   2, regnum   2, reg encode  15
  R15_H_num,                // enum   3, regnum   3, reg encode  99
  R17_num,                  // enum   4, regnum   4, reg encode  17
  R17_H_num,                // enum   5, regnum   5, reg encode  99
  R18_num,                  // enum   6, regnum   6, reg encode  18
  R18_H_num,                // enum   7, regnum   7, reg encode  99
  R19_num,                  // enum   8, regnum   8, reg encode  19
  R19_H_num,                // enum   9, regnum   9, reg encode  99
  R20_num,                  // enum  10, regnum  10, reg encode  20
  R20_H_num,                // enum  11, regnum  11, reg encode  99
  R21_num,                  // enum  12, regnum  12, reg encode  21
  R21_H_num,                // enum  13, regnum  13, reg encode  99
  R22_num,                  // enum  14, regnum  14, reg encode  22
  R22_H_num,                // enum  15, regnum  15, reg encode  99
  R23_num,                  // enum  16, regnum  16, reg encode  23
  R23_H_num,                // enum  17, regnum  17, reg encode  99
  R24_num,                  // enum  18, regnum  18, reg encode  24
  R24_H_num,                // enum  19, regnum  19, reg encode  99
  R25_num,                  // enum  20, regnum  20, reg encode  25
  R25_H_num,                // enum  21, regnum  21, reg encode  99
  R26_num,                  // enum  22, regnum  22, reg encode  26
  R26_H_num,                // enum  23, regnum  23, reg encode  99
  R27_num,                  // enum  24, regnum  24, reg encode  27
  R27_H_num,                // enum  25, regnum  25, reg encode  99
  R28_num,                  // enum  26, regnum  26, reg encode  28
  R28_H_num,                // enum  27, regnum  27, reg encode  99
  R29_num,                  // enum  28, regnum  28, reg encode  29
  R29_H_num,                // enum  29, regnum  29, reg encode  99
  R30_num,                  // enum  30, regnum  30, reg encode  30
  R30_H_num,                // enum  31, regnum  31, reg encode  99
  R31_num,                  // enum  32, regnum  32, reg encode  31
  R31_H_num,                // enum  33, regnum  33, reg encode  99
  R11_num,                  // enum  34, regnum  34, reg encode  11
  R11_H_num,                // enum  35, regnum  35, reg encode  99
  R12_num,                  // enum  36, regnum  36, reg encode  12
  R12_H_num,                // enum  37, regnum  37, reg encode  99
  R10_num,                  // enum  38, regnum  38, reg encode  10
  R10_H_num,                // enum  39, regnum  39, reg encode  99
  R9_num,                   // enum  40, regnum  40, reg encode   9
  R9_H_num,                 // enum  41, regnum  41, reg encode  99
  R8_num,                   // enum  42, regnum  42, reg encode   8
  R8_H_num,                 // enum  43, regnum  43, reg encode  99
  R7_num,                   // enum  44, regnum  44, reg encode   7
  R7_H_num,                 // enum  45, regnum  45, reg encode  99
  R6_num,                   // enum  46, regnum  46, reg encode   6
  R6_H_num,                 // enum  47, regnum  47, reg encode  99
  R5_num,                   // enum  48, regnum  48, reg encode   5
  R5_H_num,                 // enum  49, regnum  49, reg encode  99
  R4_num,                   // enum  50, regnum  50, reg encode   4
  R4_H_num,                 // enum  51, regnum  51, reg encode  99
  R3_num,                   // enum  52, regnum  52, reg encode   3
  R3_H_num,                 // enum  53, regnum  53, reg encode  99
  R16_num,                  // enum  54, regnum  54, reg encode  16
  R16_H_num,                // enum  55, regnum  55, reg encode  99
  R13_num,                  // enum  56, regnum  56, reg encode  13
  R13_H_num,                // enum  57, regnum  57, reg encode  99
  R2_num,                   // enum  58, regnum  58, reg encode   2
  R2_H_num,                 // enum  59, regnum  59, reg encode  99
  R1_num,                   // enum  60, regnum  60, reg encode   1
  R1_H_num,                 // enum  61, regnum  61, reg encode  99
  R0_num,                   // enum  62, regnum  62, reg encode   0
  R0_H_num,                 // enum  63, regnum  63, reg encode  99
  F0_num,                   // enum  64, regnum  64, reg encode   0
  F0_H_num,                 // enum  65, regnum  65, reg encode  99
  F13_num,                  // enum  66, regnum  66, reg encode  13
  F13_H_num,                // enum  67, regnum  67, reg encode  99
  F12_num,                  // enum  68, regnum  68, reg encode  12
  F12_H_num,                // enum  69, regnum  69, reg encode  99
  F11_num,                  // enum  70, regnum  70, reg encode  11
  F11_H_num,                // enum  71, regnum  71, reg encode  99
  F10_num,                  // enum  72, regnum  72, reg encode  10
  F10_H_num,                // enum  73, regnum  73, reg encode  99
  F9_num,                   // enum  74, regnum  74, reg encode   9
  F9_H_num,                 // enum  75, regnum  75, reg encode  99
  F8_num,                   // enum  76, regnum  76, reg encode   8
  F8_H_num,                 // enum  77, regnum  77, reg encode  99
  F7_num,                   // enum  78, regnum  78, reg encode   7
  F7_H_num,                 // enum  79, regnum  79, reg encode  99
  F6_num,                   // enum  80, regnum  80, reg encode   6
  F6_H_num,                 // enum  81, regnum  81, reg encode  99
  F5_num,                   // enum  82, regnum  82, reg encode   5
  F5_H_num,                 // enum  83, regnum  83, reg encode  99
  F4_num,                   // enum  84, regnum  84, reg encode   4
  F4_H_num,                 // enum  85, regnum  85, reg encode  99
  F3_num,                   // enum  86, regnum  86, reg encode   3
  F3_H_num,                 // enum  87, regnum  87, reg encode  99
  F2_num,                   // enum  88, regnum  88, reg encode   2
  F2_H_num,                 // enum  89, regnum  89, reg encode  99
  F1_num,                   // enum  90, regnum  90, reg encode   1
  F1_H_num,                 // enum  91, regnum  91, reg encode  99
  F14_num,                  // enum  92, regnum  92, reg encode  14
  F14_H_num,                // enum  93, regnum  93, reg encode  99
  F15_num,                  // enum  94, regnum  94, reg encode  15
  F15_H_num,                // enum  95, regnum  95, reg encode  99
  F16_num,                  // enum  96, regnum  96, reg encode  16
  F16_H_num,                // enum  97, regnum  97, reg encode  99
  F17_num,                  // enum  98, regnum  98, reg encode  17
  F17_H_num,                // enum  99, regnum  99, reg encode  99
  F18_num,                  // enum 100, regnum 100, reg encode  18
  F18_H_num,                // enum 101, regnum 101, reg encode  99
  F19_num,                  // enum 102, regnum 102, reg encode  19
  F19_H_num,                // enum 103, regnum 103, reg encode  99
  F20_num,                  // enum 104, regnum 104, reg encode  20
  F20_H_num,                // enum 105, regnum 105, reg encode  99
  F21_num,                  // enum 106, regnum 106, reg encode  21
  F21_H_num,                // enum 107, regnum 107, reg encode  99
  F22_num,                  // enum 108, regnum 108, reg encode  22
  F22_H_num,                // enum 109, regnum 109, reg encode  99
  F23_num,                  // enum 110, regnum 110, reg encode  23
  F23_H_num,                // enum 111, regnum 111, reg encode  99
  F24_num,                  // enum 112, regnum 112, reg encode  24
  F24_H_num,                // enum 113, regnum 113, reg encode  99
  F25_num,                  // enum 114, regnum 114, reg encode  25
  F25_H_num,                // enum 115, regnum 115, reg encode  99
  F26_num,                  // enum 116, regnum 116, reg encode  26
  F26_H_num,                // enum 117, regnum 117, reg encode  99
  F27_num,                  // enum 118, regnum 118, reg encode  27
  F27_H_num,                // enum 119, regnum 119, reg encode  99
  F28_num,                  // enum 120, regnum 120, reg encode  28
  F28_H_num,                // enum 121, regnum 121, reg encode  99
  F29_num,                  // enum 122, regnum 122, reg encode  29
  F29_H_num,                // enum 123, regnum 123, reg encode  99
  F30_num,                  // enum 124, regnum 124, reg encode  30
  F30_H_num,                // enum 125, regnum 125, reg encode  99
  F31_num,                  // enum 126, regnum 126, reg encode  31
  F31_H_num,                // enum 127, regnum 127, reg encode  99
  CCR0_num,                 // enum 128, regnum 128, reg encode   0
  CCR1_num,                 // enum 129, regnum 129, reg encode   1
  CCR2_num,                 // enum 130, regnum 130, reg encode   2
  CCR3_num,                 // enum 131, regnum 131, reg encode   3
  CCR4_num,                 // enum 132, regnum 132, reg encode   4
  CCR5_num,                 // enum 133, regnum 133, reg encode   5
  CCR6_num,                 // enum 134, regnum 134, reg encode   6
  CCR7_num,                 // enum 135, regnum 135, reg encode   7
  VSR0_num,                 // enum 136, regnum 136, reg encode   0
  VSR1_num,                 // enum 137, regnum 137, reg encode   1
  VSR2_num,                 // enum 138, regnum 138, reg encode   2
  VSR3_num,                 // enum 139, regnum 139, reg encode   3
  VSR4_num,                 // enum 140, regnum 140, reg encode   4
  VSR5_num,                 // enum 141, regnum 141, reg encode   5
  VSR6_num,                 // enum 142, regnum 142, reg encode   6
  VSR7_num,                 // enum 143, regnum 143, reg encode   7
  VSR8_num,                 // enum 144, regnum 144, reg encode   8
  VSR9_num,                 // enum 145, regnum 145, reg encode   9
  VSR10_num,                // enum 146, regnum 146, reg encode  10
  VSR11_num,                // enum 147, regnum 147, reg encode  11
  VSR12_num,                // enum 148, regnum 148, reg encode  12
  VSR13_num,                // enum 149, regnum 149, reg encode  13
  VSR14_num,                // enum 150, regnum 150, reg encode  14
  VSR15_num,                // enum 151, regnum 151, reg encode  15
  VSR16_num,                // enum 152, regnum 152, reg encode  16
  VSR17_num,                // enum 153, regnum 153, reg encode  17
  VSR18_num,                // enum 154, regnum 154, reg encode  18
  VSR19_num,                // enum 155, regnum 155, reg encode  19
  VSR20_num,                // enum 156, regnum 156, reg encode  20
  VSR21_num,                // enum 157, regnum 157, reg encode  21
  VSR22_num,                // enum 158, regnum 158, reg encode  22
  VSR23_num,                // enum 159, regnum 159, reg encode  23
  VSR24_num,                // enum 160, regnum 160, reg encode  24
  VSR25_num,                // enum 161, regnum 161, reg encode  25
  VSR26_num,                // enum 162, regnum 162, reg encode  26
  VSR27_num,                // enum 163, regnum 163, reg encode  27
  VSR28_num,                // enum 164, regnum 164, reg encode  28
  VSR29_num,                // enum 165, regnum 165, reg encode  29
  VSR30_num,                // enum 166, regnum 166, reg encode  30
  VSR31_num,                // enum 167, regnum 167, reg encode  31
  VSR32_num,                // enum 168, regnum 168, reg encode  32
  VSR33_num,                // enum 169, regnum 169, reg encode  33
  VSR34_num,                // enum 170, regnum 170, reg encode  34
  VSR35_num,                // enum 171, regnum 171, reg encode  35
  VSR36_num,                // enum 172, regnum 172, reg encode  36
  VSR37_num,                // enum 173, regnum 173, reg encode  37
  VSR38_num,                // enum 174, regnum 174, reg encode  38
  VSR39_num,                // enum 175, regnum 175, reg encode  39
  VSR40_num,                // enum 176, regnum 176, reg encode  40
  VSR41_num,                // enum 177, regnum 177, reg encode  41
  VSR42_num,                // enum 178, regnum 178, reg encode  42
  VSR43_num,                // enum 179, regnum 179, reg encode  43
  VSR44_num,                // enum 180, regnum 180, reg encode  44
  VSR45_num,                // enum 181, regnum 181, reg encode  45
  VSR46_num,                // enum 182, regnum 182, reg encode  46
  VSR47_num,                // enum 183, regnum 183, reg encode  47
  VSR48_num,                // enum 184, regnum 184, reg encode  48
  VSR49_num,                // enum 185, regnum 185, reg encode  49
  VSR50_num,                // enum 186, regnum 186, reg encode  50
  VSR51_num,                // enum 187, regnum 187, reg encode  51
  VSR52_num,                // enum 188, regnum 188, reg encode  52
  VSR53_num,                // enum 189, regnum 189, reg encode  53
  VSR54_num,                // enum 190, regnum 190, reg encode  54
  VSR55_num,                // enum 191, regnum 191, reg encode  55
  VSR56_num,                // enum 192, regnum 192, reg encode  56
  VSR57_num,                // enum 193, regnum 193, reg encode  57
  VSR58_num,                // enum 194, regnum 194, reg encode  58
  VSR59_num,                // enum 195, regnum 195, reg encode  59
  VSR60_num,                // enum 196, regnum 196, reg encode  60
  VSR61_num,                // enum 197, regnum 197, reg encode  61
  VSR62_num,                // enum 198, regnum 198, reg encode  62
  VSR63_num,                // enum 199, regnum 199, reg encode  63
  SR_XER_num,               // enum 200, regnum 200, reg encode   0
  SR_LR_num,                // enum 201, regnum 201, reg encode   1
  SR_CTR_num,               // enum 202, regnum 202, reg encode   2
  SR_VRSAVE_num,            // enum 203, regnum 203, reg encode   3
  SR_SPEFSCR_num,           // enum 204, regnum 204, reg encode   4
  SR_PPR_num,               // enum 205, regnum 205, reg encode   5
  _last_Mach_Reg            // 206
};

// Size of register-mask in ints
#define RM_SIZE 10
// Unroll factor for loops over the data in a RegMask
#define FORALL_BODY BODY(0) BODY(1) BODY(2) BODY(3) BODY(4) BODY(5) BODY(6) BODY(7) BODY(8) BODY(9) 

class RegMask;

#endif // GENERATED_ADFILES_ADGLOBALS_HPP
