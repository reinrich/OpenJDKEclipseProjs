#line 1 "adGlobals_aarch64.hpp"
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


#ifndef GENERATED_ADFILES_ADGLOBALS_HPP
#define GENERATED_ADFILES_ADGLOBALS_HPP


// the number of reserved registers + machine registers.
#define REG_COUNT    337

// the number of save_on_entry + always_saved registers.
#define MAX_SAVED_ON_ENTRY_REG_COUNT    36
#define     SAVED_ON_ENTRY_REG_COUNT    0
#define   C_SAVED_ON_ENTRY_REG_COUNT    36

// Enumerate machine register numbers starting after reserved regs.
// in the order of occurrence in the register block.
enum MachRegisterNumbers {
  R10_num,                  // enum   0, regnum   0, reg encode  10
  R10_H_num,                // enum   1, regnum   1, reg encode  10
  R11_num,                  // enum   2, regnum   2, reg encode  11
  R11_H_num,                // enum   3, regnum   3, reg encode  11
  R12_num,                  // enum   4, regnum   4, reg encode  12
  R12_H_num,                // enum   5, regnum   5, reg encode  12
  R13_num,                  // enum   6, regnum   6, reg encode  13
  R13_H_num,                // enum   7, regnum   7, reg encode  13
  R14_num,                  // enum   8, regnum   8, reg encode  14
  R14_H_num,                // enum   9, regnum   9, reg encode  14
  R15_num,                  // enum  10, regnum  10, reg encode  15
  R15_H_num,                // enum  11, regnum  11, reg encode  15
  R16_num,                  // enum  12, regnum  12, reg encode  16
  R16_H_num,                // enum  13, regnum  13, reg encode  16
  R17_num,                  // enum  14, regnum  14, reg encode  17
  R17_H_num,                // enum  15, regnum  15, reg encode  17
  R18_num,                  // enum  16, regnum  16, reg encode  18
  R18_H_num,                // enum  17, regnum  17, reg encode  18
  R0_num,                   // enum  18, regnum  18, reg encode   0
  R0_H_num,                 // enum  19, regnum  19, reg encode   0
  R1_num,                   // enum  20, regnum  20, reg encode   1
  R1_H_num,                 // enum  21, regnum  21, reg encode   1
  R2_num,                   // enum  22, regnum  22, reg encode   2
  R2_H_num,                 // enum  23, regnum  23, reg encode   2
  R3_num,                   // enum  24, regnum  24, reg encode   3
  R3_H_num,                 // enum  25, regnum  25, reg encode   3
  R4_num,                   // enum  26, regnum  26, reg encode   4
  R4_H_num,                 // enum  27, regnum  27, reg encode   4
  R5_num,                   // enum  28, regnum  28, reg encode   5
  R5_H_num,                 // enum  29, regnum  29, reg encode   5
  R6_num,                   // enum  30, regnum  30, reg encode   6
  R6_H_num,                 // enum  31, regnum  31, reg encode   6
  R7_num,                   // enum  32, regnum  32, reg encode   7
  R7_H_num,                 // enum  33, regnum  33, reg encode   7
  R19_num,                  // enum  34, regnum  34, reg encode  19
  R19_H_num,                // enum  35, regnum  35, reg encode  19
  R20_num,                  // enum  36, regnum  36, reg encode  20
  R20_H_num,                // enum  37, regnum  37, reg encode  20
  R21_num,                  // enum  38, regnum  38, reg encode  21
  R21_H_num,                // enum  39, regnum  39, reg encode  21
  R22_num,                  // enum  40, regnum  40, reg encode  22
  R22_H_num,                // enum  41, regnum  41, reg encode  22
  R23_num,                  // enum  42, regnum  42, reg encode  23
  R23_H_num,                // enum  43, regnum  43, reg encode  23
  R24_num,                  // enum  44, regnum  44, reg encode  24
  R24_H_num,                // enum  45, regnum  45, reg encode  24
  R25_num,                  // enum  46, regnum  46, reg encode  25
  R25_H_num,                // enum  47, regnum  47, reg encode  25
  R26_num,                  // enum  48, regnum  48, reg encode  26
  R26_H_num,                // enum  49, regnum  49, reg encode  26
  R27_num,                  // enum  50, regnum  50, reg encode  27
  R27_H_num,                // enum  51, regnum  51, reg encode  27
  R28_num,                  // enum  52, regnum  52, reg encode  28
  R28_H_num,                // enum  53, regnum  53, reg encode  28
  R29_num,                  // enum  54, regnum  54, reg encode  29
  R29_H_num,                // enum  55, regnum  55, reg encode  29
  R30_num,                  // enum  56, regnum  56, reg encode  30
  R30_H_num,                // enum  57, regnum  57, reg encode  30
  R31_num,                  // enum  58, regnum  58, reg encode  31
  R31_H_num,                // enum  59, regnum  59, reg encode  31
  R8_num,                   // enum  60, regnum  60, reg encode   8
  R8_H_num,                 // enum  61, regnum  61, reg encode   8
  R9_num,                   // enum  62, regnum  62, reg encode   9
  R9_H_num,                 // enum  63, regnum  63, reg encode   9
  V16_num,                  // enum  64, regnum  64, reg encode  16
  V16_H_num,                // enum  65, regnum  65, reg encode  16
  V16_J_num,                // enum  66, regnum  66, reg encode  16
  V16_K_num,                // enum  67, regnum  67, reg encode  16
  V16_L_num,                // enum  68, regnum  68, reg encode  16
  V16_M_num,                // enum  69, regnum  69, reg encode  16
  V16_N_num,                // enum  70, regnum  70, reg encode  16
  V16_O_num,                // enum  71, regnum  71, reg encode  16
  V17_num,                  // enum  72, regnum  72, reg encode  17
  V17_H_num,                // enum  73, regnum  73, reg encode  17
  V17_J_num,                // enum  74, regnum  74, reg encode  17
  V17_K_num,                // enum  75, regnum  75, reg encode  17
  V17_L_num,                // enum  76, regnum  76, reg encode  17
  V17_M_num,                // enum  77, regnum  77, reg encode  17
  V17_N_num,                // enum  78, regnum  78, reg encode  17
  V17_O_num,                // enum  79, regnum  79, reg encode  17
  V18_num,                  // enum  80, regnum  80, reg encode  18
  V18_H_num,                // enum  81, regnum  81, reg encode  18
  V18_J_num,                // enum  82, regnum  82, reg encode  18
  V18_K_num,                // enum  83, regnum  83, reg encode  18
  V18_L_num,                // enum  84, regnum  84, reg encode  18
  V18_M_num,                // enum  85, regnum  85, reg encode  18
  V18_N_num,                // enum  86, regnum  86, reg encode  18
  V18_O_num,                // enum  87, regnum  87, reg encode  18
  V19_num,                  // enum  88, regnum  88, reg encode  19
  V19_H_num,                // enum  89, regnum  89, reg encode  19
  V19_J_num,                // enum  90, regnum  90, reg encode  19
  V19_K_num,                // enum  91, regnum  91, reg encode  19
  V19_L_num,                // enum  92, regnum  92, reg encode  19
  V19_M_num,                // enum  93, regnum  93, reg encode  19
  V19_N_num,                // enum  94, regnum  94, reg encode  19
  V19_O_num,                // enum  95, regnum  95, reg encode  19
  V20_num,                  // enum  96, regnum  96, reg encode  20
  V20_H_num,                // enum  97, regnum  97, reg encode  20
  V20_J_num,                // enum  98, regnum  98, reg encode  20
  V20_K_num,                // enum  99, regnum  99, reg encode  20
  V20_L_num,                // enum 100, regnum 100, reg encode  20
  V20_M_num,                // enum 101, regnum 101, reg encode  20
  V20_N_num,                // enum 102, regnum 102, reg encode  20
  V20_O_num,                // enum 103, regnum 103, reg encode  20
  V21_num,                  // enum 104, regnum 104, reg encode  21
  V21_H_num,                // enum 105, regnum 105, reg encode  21
  V21_J_num,                // enum 106, regnum 106, reg encode  21
  V21_K_num,                // enum 107, regnum 107, reg encode  21
  V21_L_num,                // enum 108, regnum 108, reg encode  21
  V21_M_num,                // enum 109, regnum 109, reg encode  21
  V21_N_num,                // enum 110, regnum 110, reg encode  21
  V21_O_num,                // enum 111, regnum 111, reg encode  21
  V22_num,                  // enum 112, regnum 112, reg encode  22
  V22_H_num,                // enum 113, regnum 113, reg encode  22
  V22_J_num,                // enum 114, regnum 114, reg encode  22
  V22_K_num,                // enum 115, regnum 115, reg encode  22
  V22_L_num,                // enum 116, regnum 116, reg encode  22
  V22_M_num,                // enum 117, regnum 117, reg encode  22
  V22_N_num,                // enum 118, regnum 118, reg encode  22
  V22_O_num,                // enum 119, regnum 119, reg encode  22
  V23_num,                  // enum 120, regnum 120, reg encode  23
  V23_H_num,                // enum 121, regnum 121, reg encode  23
  V23_J_num,                // enum 122, regnum 122, reg encode  23
  V23_K_num,                // enum 123, regnum 123, reg encode  23
  V23_L_num,                // enum 124, regnum 124, reg encode  23
  V23_M_num,                // enum 125, regnum 125, reg encode  23
  V23_N_num,                // enum 126, regnum 126, reg encode  23
  V23_O_num,                // enum 127, regnum 127, reg encode  23
  V24_num,                  // enum 128, regnum 128, reg encode  24
  V24_H_num,                // enum 129, regnum 129, reg encode  24
  V24_J_num,                // enum 130, regnum 130, reg encode  24
  V24_K_num,                // enum 131, regnum 131, reg encode  24
  V24_L_num,                // enum 132, regnum 132, reg encode  24
  V24_M_num,                // enum 133, regnum 133, reg encode  24
  V24_N_num,                // enum 134, regnum 134, reg encode  24
  V24_O_num,                // enum 135, regnum 135, reg encode  24
  V25_num,                  // enum 136, regnum 136, reg encode  25
  V25_H_num,                // enum 137, regnum 137, reg encode  25
  V25_J_num,                // enum 138, regnum 138, reg encode  25
  V25_K_num,                // enum 139, regnum 139, reg encode  25
  V25_L_num,                // enum 140, regnum 140, reg encode  25
  V25_M_num,                // enum 141, regnum 141, reg encode  25
  V25_N_num,                // enum 142, regnum 142, reg encode  25
  V25_O_num,                // enum 143, regnum 143, reg encode  25
  V26_num,                  // enum 144, regnum 144, reg encode  26
  V26_H_num,                // enum 145, regnum 145, reg encode  26
  V26_J_num,                // enum 146, regnum 146, reg encode  26
  V26_K_num,                // enum 147, regnum 147, reg encode  26
  V26_L_num,                // enum 148, regnum 148, reg encode  26
  V26_M_num,                // enum 149, regnum 149, reg encode  26
  V26_N_num,                // enum 150, regnum 150, reg encode  26
  V26_O_num,                // enum 151, regnum 151, reg encode  26
  V27_num,                  // enum 152, regnum 152, reg encode  27
  V27_H_num,                // enum 153, regnum 153, reg encode  27
  V27_J_num,                // enum 154, regnum 154, reg encode  27
  V27_K_num,                // enum 155, regnum 155, reg encode  27
  V27_L_num,                // enum 156, regnum 156, reg encode  27
  V27_M_num,                // enum 157, regnum 157, reg encode  27
  V27_N_num,                // enum 158, regnum 158, reg encode  27
  V27_O_num,                // enum 159, regnum 159, reg encode  27
  V28_num,                  // enum 160, regnum 160, reg encode  28
  V28_H_num,                // enum 161, regnum 161, reg encode  28
  V28_J_num,                // enum 162, regnum 162, reg encode  28
  V28_K_num,                // enum 163, regnum 163, reg encode  28
  V28_L_num,                // enum 164, regnum 164, reg encode  28
  V28_M_num,                // enum 165, regnum 165, reg encode  28
  V28_N_num,                // enum 166, regnum 166, reg encode  28
  V28_O_num,                // enum 167, regnum 167, reg encode  28
  V29_num,                  // enum 168, regnum 168, reg encode  29
  V29_H_num,                // enum 169, regnum 169, reg encode  29
  V29_J_num,                // enum 170, regnum 170, reg encode  29
  V29_K_num,                // enum 171, regnum 171, reg encode  29
  V29_L_num,                // enum 172, regnum 172, reg encode  29
  V29_M_num,                // enum 173, regnum 173, reg encode  29
  V29_N_num,                // enum 174, regnum 174, reg encode  29
  V29_O_num,                // enum 175, regnum 175, reg encode  29
  V30_num,                  // enum 176, regnum 176, reg encode  30
  V30_H_num,                // enum 177, regnum 177, reg encode  30
  V30_J_num,                // enum 178, regnum 178, reg encode  30
  V30_K_num,                // enum 179, regnum 179, reg encode  30
  V30_L_num,                // enum 180, regnum 180, reg encode  30
  V30_M_num,                // enum 181, regnum 181, reg encode  30
  V30_N_num,                // enum 182, regnum 182, reg encode  30
  V30_O_num,                // enum 183, regnum 183, reg encode  30
  V31_num,                  // enum 184, regnum 184, reg encode  31
  V31_H_num,                // enum 185, regnum 185, reg encode  31
  V31_J_num,                // enum 186, regnum 186, reg encode  31
  V31_K_num,                // enum 187, regnum 187, reg encode  31
  V31_L_num,                // enum 188, regnum 188, reg encode  31
  V31_M_num,                // enum 189, regnum 189, reg encode  31
  V31_N_num,                // enum 190, regnum 190, reg encode  31
  V31_O_num,                // enum 191, regnum 191, reg encode  31
  V0_num,                   // enum 192, regnum 192, reg encode   0
  V0_H_num,                 // enum 193, regnum 193, reg encode   0
  V0_J_num,                 // enum 194, regnum 194, reg encode   0
  V0_K_num,                 // enum 195, regnum 195, reg encode   0
  V0_L_num,                 // enum 196, regnum 196, reg encode   0
  V0_M_num,                 // enum 197, regnum 197, reg encode   0
  V0_N_num,                 // enum 198, regnum 198, reg encode   0
  V0_O_num,                 // enum 199, regnum 199, reg encode   0
  V1_num,                   // enum 200, regnum 200, reg encode   1
  V1_H_num,                 // enum 201, regnum 201, reg encode   1
  V1_J_num,                 // enum 202, regnum 202, reg encode   1
  V1_K_num,                 // enum 203, regnum 203, reg encode   1
  V1_L_num,                 // enum 204, regnum 204, reg encode   1
  V1_M_num,                 // enum 205, regnum 205, reg encode   1
  V1_N_num,                 // enum 206, regnum 206, reg encode   1
  V1_O_num,                 // enum 207, regnum 207, reg encode   1
  V2_num,                   // enum 208, regnum 208, reg encode   2
  V2_H_num,                 // enum 209, regnum 209, reg encode   2
  V2_J_num,                 // enum 210, regnum 210, reg encode   2
  V2_K_num,                 // enum 211, regnum 211, reg encode   2
  V2_L_num,                 // enum 212, regnum 212, reg encode   2
  V2_M_num,                 // enum 213, regnum 213, reg encode   2
  V2_N_num,                 // enum 214, regnum 214, reg encode   2
  V2_O_num,                 // enum 215, regnum 215, reg encode   2
  V3_num,                   // enum 216, regnum 216, reg encode   3
  V3_H_num,                 // enum 217, regnum 217, reg encode   3
  V3_J_num,                 // enum 218, regnum 218, reg encode   3
  V3_K_num,                 // enum 219, regnum 219, reg encode   3
  V3_L_num,                 // enum 220, regnum 220, reg encode   3
  V3_M_num,                 // enum 221, regnum 221, reg encode   3
  V3_N_num,                 // enum 222, regnum 222, reg encode   3
  V3_O_num,                 // enum 223, regnum 223, reg encode   3
  V4_num,                   // enum 224, regnum 224, reg encode   4
  V4_H_num,                 // enum 225, regnum 225, reg encode   4
  V4_J_num,                 // enum 226, regnum 226, reg encode   4
  V4_K_num,                 // enum 227, regnum 227, reg encode   4
  V4_L_num,                 // enum 228, regnum 228, reg encode   4
  V4_M_num,                 // enum 229, regnum 229, reg encode   4
  V4_N_num,                 // enum 230, regnum 230, reg encode   4
  V4_O_num,                 // enum 231, regnum 231, reg encode   4
  V5_num,                   // enum 232, regnum 232, reg encode   5
  V5_H_num,                 // enum 233, regnum 233, reg encode   5
  V5_J_num,                 // enum 234, regnum 234, reg encode   5
  V5_K_num,                 // enum 235, regnum 235, reg encode   5
  V5_L_num,                 // enum 236, regnum 236, reg encode   5
  V5_M_num,                 // enum 237, regnum 237, reg encode   5
  V5_N_num,                 // enum 238, regnum 238, reg encode   5
  V5_O_num,                 // enum 239, regnum 239, reg encode   5
  V6_num,                   // enum 240, regnum 240, reg encode   6
  V6_H_num,                 // enum 241, regnum 241, reg encode   6
  V6_J_num,                 // enum 242, regnum 242, reg encode   6
  V6_K_num,                 // enum 243, regnum 243, reg encode   6
  V6_L_num,                 // enum 244, regnum 244, reg encode   6
  V6_M_num,                 // enum 245, regnum 245, reg encode   6
  V6_N_num,                 // enum 246, regnum 246, reg encode   6
  V6_O_num,                 // enum 247, regnum 247, reg encode   6
  V7_num,                   // enum 248, regnum 248, reg encode   7
  V7_H_num,                 // enum 249, regnum 249, reg encode   7
  V7_J_num,                 // enum 250, regnum 250, reg encode   7
  V7_K_num,                 // enum 251, regnum 251, reg encode   7
  V7_L_num,                 // enum 252, regnum 252, reg encode   7
  V7_M_num,                 // enum 253, regnum 253, reg encode   7
  V7_N_num,                 // enum 254, regnum 254, reg encode   7
  V7_O_num,                 // enum 255, regnum 255, reg encode   7
  V8_num,                   // enum 256, regnum 256, reg encode   8
  V8_H_num,                 // enum 257, regnum 257, reg encode   8
  V8_J_num,                 // enum 258, regnum 258, reg encode   8
  V8_K_num,                 // enum 259, regnum 259, reg encode   8
  V8_L_num,                 // enum 260, regnum 260, reg encode   8
  V8_M_num,                 // enum 261, regnum 261, reg encode   8
  V8_N_num,                 // enum 262, regnum 262, reg encode   8
  V8_O_num,                 // enum 263, regnum 263, reg encode   8
  V9_num,                   // enum 264, regnum 264, reg encode   9
  V9_H_num,                 // enum 265, regnum 265, reg encode   9
  V9_J_num,                 // enum 266, regnum 266, reg encode   9
  V9_K_num,                 // enum 267, regnum 267, reg encode   9
  V9_L_num,                 // enum 268, regnum 268, reg encode   9
  V9_M_num,                 // enum 269, regnum 269, reg encode   9
  V9_N_num,                 // enum 270, regnum 270, reg encode   9
  V9_O_num,                 // enum 271, regnum 271, reg encode   9
  V10_num,                  // enum 272, regnum 272, reg encode  10
  V10_H_num,                // enum 273, regnum 273, reg encode  10
  V10_J_num,                // enum 274, regnum 274, reg encode  10
  V10_K_num,                // enum 275, regnum 275, reg encode  10
  V10_L_num,                // enum 276, regnum 276, reg encode  10
  V10_M_num,                // enum 277, regnum 277, reg encode  10
  V10_N_num,                // enum 278, regnum 278, reg encode  10
  V10_O_num,                // enum 279, regnum 279, reg encode  10
  V11_num,                  // enum 280, regnum 280, reg encode  11
  V11_H_num,                // enum 281, regnum 281, reg encode  11
  V11_J_num,                // enum 282, regnum 282, reg encode  11
  V11_K_num,                // enum 283, regnum 283, reg encode  11
  V11_L_num,                // enum 284, regnum 284, reg encode  11
  V11_M_num,                // enum 285, regnum 285, reg encode  11
  V11_N_num,                // enum 286, regnum 286, reg encode  11
  V11_O_num,                // enum 287, regnum 287, reg encode  11
  V12_num,                  // enum 288, regnum 288, reg encode  12
  V12_H_num,                // enum 289, regnum 289, reg encode  12
  V12_J_num,                // enum 290, regnum 290, reg encode  12
  V12_K_num,                // enum 291, regnum 291, reg encode  12
  V12_L_num,                // enum 292, regnum 292, reg encode  12
  V12_M_num,                // enum 293, regnum 293, reg encode  12
  V12_N_num,                // enum 294, regnum 294, reg encode  12
  V12_O_num,                // enum 295, regnum 295, reg encode  12
  V13_num,                  // enum 296, regnum 296, reg encode  13
  V13_H_num,                // enum 297, regnum 297, reg encode  13
  V13_J_num,                // enum 298, regnum 298, reg encode  13
  V13_K_num,                // enum 299, regnum 299, reg encode  13
  V13_L_num,                // enum 300, regnum 300, reg encode  13
  V13_M_num,                // enum 301, regnum 301, reg encode  13
  V13_N_num,                // enum 302, regnum 302, reg encode  13
  V13_O_num,                // enum 303, regnum 303, reg encode  13
  V14_num,                  // enum 304, regnum 304, reg encode  14
  V14_H_num,                // enum 305, regnum 305, reg encode  14
  V14_J_num,                // enum 306, regnum 306, reg encode  14
  V14_K_num,                // enum 307, regnum 307, reg encode  14
  V14_L_num,                // enum 308, regnum 308, reg encode  14
  V14_M_num,                // enum 309, regnum 309, reg encode  14
  V14_N_num,                // enum 310, regnum 310, reg encode  14
  V14_O_num,                // enum 311, regnum 311, reg encode  14
  V15_num,                  // enum 312, regnum 312, reg encode  15
  V15_H_num,                // enum 313, regnum 313, reg encode  15
  V15_J_num,                // enum 314, regnum 314, reg encode  15
  V15_K_num,                // enum 315, regnum 315, reg encode  15
  V15_L_num,                // enum 316, regnum 316, reg encode  15
  V15_M_num,                // enum 317, regnum 317, reg encode  15
  V15_N_num,                // enum 318, regnum 318, reg encode  15
  V15_O_num,                // enum 319, regnum 319, reg encode  15
  P0_num,                   // enum 320, regnum 320, reg encode   0
  P1_num,                   // enum 321, regnum 321, reg encode   1
  P2_num,                   // enum 322, regnum 322, reg encode   2
  P3_num,                   // enum 323, regnum 323, reg encode   3
  P4_num,                   // enum 324, regnum 324, reg encode   4
  P5_num,                   // enum 325, regnum 325, reg encode   5
  P6_num,                   // enum 326, regnum 326, reg encode   6
  P7_num,                   // enum 327, regnum 327, reg encode   7
  P8_num,                   // enum 328, regnum 328, reg encode   8
  P9_num,                   // enum 329, regnum 329, reg encode   9
  P10_num,                  // enum 330, regnum 330, reg encode  10
  P11_num,                  // enum 331, regnum 331, reg encode  11
  P12_num,                  // enum 332, regnum 332, reg encode  12
  P13_num,                  // enum 333, regnum 333, reg encode  13
  P14_num,                  // enum 334, regnum 334, reg encode  14
  P15_num,                  // enum 335, regnum 335, reg encode  15
  RFLAGS_num,               // enum 336, regnum 336, reg encode  32
  _last_Mach_Reg            // 337
};

// Size of register-mask in ints
#define RM_SIZE 14
// Unroll factor for loops over the data in a RegMask
#define FORALL_BODY BODY(0) BODY(1) BODY(2) BODY(3) BODY(4) BODY(5) BODY(6) BODY(7) BODY(8) BODY(9) BODY(10) BODY(11) BODY(12) BODY(13) 

class RegMask;

#endif // GENERATED_ADFILES_ADGLOBALS_HPP
