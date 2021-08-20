/*
 * Copyright (c) 2021 Arm Limited.
 *
 * SPDX-License-Identifier: MIT
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <cstddef>
#include <cstdint>

#if defined(ARM_COMPUTE_ENABLE_SVE)

namespace arm_conv {
namespace depthwise {

void sve_fp32_nhwc_3x3_s1_output4x4_mla_depthfirst_indirect_impl(
  const float *const *const input_ptrs,
  float *const *const outptrs,
  const void *params,
  unsigned int n_channels,
  const float activation_min,
  const float activation_max
)
{
  struct Args
  {
    float *const *outptrs;
    const void *params;
    const float min, max;
    const float *inptrs[36];

    Args(
      const float *const *const input_ptrs,
      float *const *const outptrs,
      const void *const params,
      const float min,
      const float max
    ) : outptrs(outptrs), params(params), min(min), max(max)
    {
      inptrs[0] = input_ptrs[14];
      inptrs[1] = input_ptrs[0];
      inptrs[2] = input_ptrs[5];
      inptrs[3] = input_ptrs[15];
      inptrs[4] = input_ptrs[30];
      inptrs[5] = input_ptrs[35];
      inptrs[6] = input_ptrs[20];
      inptrs[7] = input_ptrs[1];
      inptrs[8] = input_ptrs[4];
      inptrs[9] = input_ptrs[21];
      inptrs[10] = input_ptrs[6];
      inptrs[11] = input_ptrs[11];
      inptrs[12] = input_ptrs[24];
      inptrs[13] = input_ptrs[8];
      inptrs[14] = input_ptrs[29];
      inptrs[15] = input_ptrs[9];
      inptrs[16] = input_ptrs[31];
      inptrs[17] = input_ptrs[13];
      inptrs[18] = input_ptrs[34];
      inptrs[19] = input_ptrs[16];
      inptrs[20] = input_ptrs[2];
      inptrs[21] = input_ptrs[19];
      inptrs[22] = input_ptrs[3];
      inptrs[23] = input_ptrs[12];
      inptrs[24] = input_ptrs[22];
      inptrs[25] = input_ptrs[17];
      inptrs[26] = input_ptrs[18];
      inptrs[27] = input_ptrs[26];
      inptrs[28] = input_ptrs[23];
      inptrs[29] = input_ptrs[32];
      inptrs[30] = input_ptrs[27];
      inptrs[31] = input_ptrs[33];
      inptrs[32] = input_ptrs[7];
      inptrs[33] = input_ptrs[10];
      inptrs[34] = input_ptrs[25];
      inptrs[35] = input_ptrs[28];

    }
  };

  Args params_struct(input_ptrs, outptrs, params,
                     activation_min, activation_max);

  __asm__ __volatile__(
    "ldr x5, [%x[params_struct], %[offsetof_args_outptrs]]\n"
    "ptrue p3.b\n"
    "ldr x6, [%x[params_struct], %[offsetof_args_params]]\n"
    "add x7, %x[params_struct], %[offsetof_Args_inptrs]\n"
    "ld1rw { z15.s }, p3/Z, [%x[params_struct], %[offsetof_args_min]]\n"
    "cntb x8, ALL, MUL #2\n"
    "ld1rw { z14.s }, p3/Z, [%x[params_struct], %[offsetof_args_max]]\n"
    "mov x17, #0x0\n"
    "ld1w { z13.s }, p3/Z, [x6]\n"
    "mov z31.d, z13.d\n"
    "ld1w { z0.s }, p3/Z, [x6, #1, MUL VL]\n"
    "cntw x16\n"
    "mov z30.d, z13.d\n"
    "ld1w { z1.s }, p3/Z, [x6, #2, MUL VL]\n"
    "sub x15, XZR, x16\n"
    "mov z29.d, z13.d\n"
    "ld1w { z2.s }, p3/Z, [x6, #3, MUL VL]\n"
    "whilelt p2.s, XZR, %x[n_channels]\n"
    "mov z28.d, z13.d\n"
    "ld1w { z3.s }, p3/Z, [x6, #4, MUL VL]\n"
    "cmp x16, %x[n_channels]\n"
    "mov z27.d, z13.d\n"
    "ld1w { z4.s }, p3/Z, [x6, #5, MUL VL]\n"
    "mov z26.d, z13.d\n"
    "ld1w { z5.s }, p3/Z, [x6, #6, MUL VL]\n"
    "mov z25.d, z13.d\n"
    "ld1w { z6.s }, p3/Z, [x6, #7, MUL VL]\n"
    "addvl x6, x6, #16\n"
    "mov z24.d, z13.d\n"
    "ld1w { z7.s }, p3/Z, [x6, #-8, MUL VL]\n"
    "mov z23.d, z13.d\n"
    "ld1w { z8.s }, p3/Z, [x6, #-7, MUL VL]\n"
    "addvl x6, x6, #-6\n"
    "mov z22.d, z13.d\n"
    "ldp x14, x13, [x7, #0x0]\n"
    "mov z21.d, z13.d\n"
    "ldp x12, x11, [x7, #0x10]\n"
    "mov z20.d, z13.d\n"
    "ld1w { z9.s }, p2/Z, [x14, x17, LSL #2]\n"
    "mov z19.d, z13.d\n"
    "mov z18.d, z13.d\n"
    "prfm pldl1keep, [x14, x8]\n"
    "mov z17.d, z13.d\n"
    "ld1w { z10.s }, p2/Z, [x13, x17, LSL #2]\n"
    "mov z16.d, z13.d\n"
    "prfm pldl1keep, [x13, x8]\n"
    "ld1w { z11.s }, p2/Z, [x12, x17, LSL #2]\n"
    "prfm pldl1keep, [x12, x8]\n"
    "ld1w { z12.s }, p2/Z, [x11, x17, LSL #2]\n"
    "prfm pldl1keep, [x11, x8]\n"
    "bge 2f\n"
    "1:"  // Channel loop
    "fmla z31.s, p3/M, z8.s, z9.s\n"
    "ldr x22, [x7, #0x20]\n"
    "whilelt p1.s, x16, %x[n_channels]\n"
    "fmla z30.s, p3/M, z7.s, z9.s\n"
    "ldr x21, [x7, #0x28]\n"
    "incw x15\n"
    "fmla z29.s, p3/M, z6.s, z9.s\n"
    "ldr x20, [x7, #0x30]\n"
    "mov p0.b, p2.b\n"
    "fmla z27.s, p3/M, z5.s, z9.s\n"
    "prfm pldl1keep, [x22, x8]\n"
    "fmla z26.s, p3/M, z4.s, z9.s\n"
    "prfm pldl1keep, [x21, x8]\n"
    "fmla z25.s, p3/M, z3.s, z9.s\n"
    "prfm pldl1keep, [x20, x8]\n"
    "fmla z23.s, p3/M, z2.s, z9.s\n"
    "ldr x19, [x7, #0x38]\n"
    "fmla z22.s, p3/M, z1.s, z9.s\n"
    "ldr x10, [x7, #0x40]\n"
    "fmla z21.s, p3/M, z0.s, z9.s\n"
    "ld1w { z9.s }, p2/Z, [x20, x17, LSL #2]\n"
    "fmla z31.s, p3/M, z0.s, z10.s\n"
    "ld1w { z10.s }, p2/Z, [x22, x17, LSL #2]\n"
    "fmla z28.s, p3/M, z2.s, z11.s\n"
    "ld1w { z11.s }, p2/Z, [x21, x17, LSL #2]\n"
    "fmla z30.s, p3/M, z8.s, z12.s\n"
    "prfm pldl1keep, [x19, x8]\n"
    "fmla z29.s, p3/M, z7.s, z12.s\n"
    "prfm pldl1keep, [x10, x8]\n"
    "fmla z26.s, p3/M, z5.s, z12.s\n"
    "ldr x9, [x7, #0x48]\n"
    "fmla z28.s, p3/M, z6.s, z12.s\n"
    "ldr x28, [x7, #0x50]\n"
    "fmla z25.s, p3/M, z4.s, z12.s\n"
    "ldr x27, [x7, #0x58]\n"
    "fmla z24.s, p3/M, z3.s, z12.s\n"
    "prfm pldl1keep, [x9, x8]\n"
    "fmla z22.s, p3/M, z2.s, z12.s\n"
    "prfm pldl1keep, [x28, x8]\n"
    "fmla z21.s, p3/M, z1.s, z12.s\n"
    "prfm pldl1keep, [x27, x8]\n"
    "fmla z20.s, p3/M, z0.s, z12.s\n"
    "ld1w { z12.s }, p2/Z, [x19, x17, LSL #2]\n"
    "fmla z19.s, p3/M, z6.s, z10.s\n"
    "ld1w { z10.s }, p2/Z, [x9, x17, LSL #2]\n"
    "fmla z16.s, p3/M, z8.s, z11.s\n"
    "ld1w { z11.s }, p2/Z, [x10, x17, LSL #2]\n"
    "fmla z27.s, p3/M, z8.s, z9.s\n"
    "ldr x26, [x7, #0x60]\n"
    "fmla z26.s, p3/M, z7.s, z9.s\n"
    "ldr x25, [x7, #0x68]\n"
    "fmla z25.s, p3/M, z6.s, z9.s\n"
    "ldr x24, [x7, #0x70]\n"
    "fmla z23.s, p3/M, z5.s, z9.s\n"
    "prfm pldl1keep, [x26, x8]\n"
    "fmla z22.s, p3/M, z4.s, z9.s\n"
    "prfm pldl1keep, [x25, x8]\n"
    "fmla z21.s, p3/M, z3.s, z9.s\n"
    "prfm pldl1keep, [x24, x8]\n"
    "fmla z19.s, p3/M, z2.s, z9.s\n"
    "ldr x23, [x7, #0x78]\n"
    "fmla z18.s, p3/M, z1.s, z9.s\n"
    "ldr x14, [x7, #0x80]\n"
    "fmla z17.s, p3/M, z0.s, z9.s\n"
    "ld1w { z9.s }, p2/Z, [x28, x17, LSL #2]\n"
    "fmla z31.s, p3/M, z1.s, z12.s\n"
    "prfm pldl1keep, [x23, x8]\n"
    "fmla z30.s, p3/M, z0.s, z12.s\n"
    "ld1w { z12.s }, p2/Z, [x27, x17, LSL #2]\n"
    "fmla z29.s, p3/M, z2.s, z11.s\n"
    "prfm pldl1keep, [x14, x8]\n"
    "fmla z28.s, p3/M, z1.s, z11.s\n"
    "ld1w { z11.s }, p2/Z, [x26, x17, LSL #2]\n"
    "fmla z26.s, p3/M, z8.s, z10.s\n"
    "ldr x13, [x7, #0x88]\n"
    "fmla z25.s, p3/M, z7.s, z10.s\n"
    "ldr x12, [x7, #0x90]\n"
    "fmla z24.s, p3/M, z6.s, z10.s\n"
    "ldr x11, [x7, #0x98]\n"
    "fmla z22.s, p3/M, z5.s, z10.s\n"
    "prfm pldl1keep, [x13, x8]\n"
    "fmla z21.s, p3/M, z4.s, z10.s\n"
    "prfm pldl1keep, [x12, x8]\n"
    "fmla z20.s, p3/M, z3.s, z10.s\n"
    "prfm pldl1keep, [x11, x8]\n"
    "fmla z18.s, p3/M, z2.s, z10.s\n"
    "ldr x22, [x7, #0xa0]\n"
    "fmla z17.s, p3/M, z1.s, z10.s\n"
    "ldr x21, [x7, #0xa8]\n"
    "fmla z16.s, p3/M, z0.s, z10.s\n"
    "ld1w { z10.s }, p2/Z, [x25, x17, LSL #2]\n"
    "fmla z31.s, p3/M, z3.s, z9.s\n"
    "prfm pldl1keep, [x22, x8]\n"
    "fmla z27.s, p3/M, z0.s, z9.s\n"
    "prfm pldl1keep, [x21, x8]\n"
    "fmla z28.s, p3/M, z5.s, z12.s\n"
    "ldr x20, [x7, #0xb0]\n"
    "fmla z24.s, p3/M, z2.s, z12.s\n"
    "ld1w { z12.s }, p2/Z, [x23, x17, LSL #2]\n"
    "fmla z23.s, p3/M, z6.s, z11.s\n"
    "ldr x19, [x7, #0xb8]\n"
    "fmla z19.s, p3/M, z3.s, z11.s\n"
    "ld1w { z11.s }, p2/Z, [x24, x17, LSL #2]\n"
    "fmla z31.s, p3/M, z5.s, z10.s\n"
    "prfm pldl1keep, [x20, x8]\n"
    "fmla z30.s, p3/M, z4.s, z10.s\n"
    "prfm pldl1keep, [x19, x8]\n"
    "fmla z29.s, p3/M, z3.s, z10.s\n"
    "ldr x10, [x7, #0xc0]\n"
    "fmla z27.s, p3/M, z2.s, z10.s\n"
    "ldr x9, [x7, #0xc8]\n"
    "fmla z26.s, p3/M, z1.s, z10.s\n"
    "ldr x28, [x7, #0xd0]\n"
    "fmla z25.s, p3/M, z0.s, z10.s\n"
    "ld1w { z10.s }, p2/Z, [x13, x17, LSL #2]\n"
    "fmla z20.s, p3/M, z8.s, z11.s\n"
    "prfm pldl1keep, [x10, x8]\n"
    "fmla z16.s, p3/M, z5.s, z11.s\n"
    "ld1w { z11.s }, p2/Z, [x14, x17, LSL #2]\n"
    "fmla z30.s, p3/M, z5.s, z12.s\n"
    "prfm pldl1keep, [x9, x8]\n"
    "fmla z29.s, p3/M, z4.s, z12.s\n"
    "prfm pldl1keep, [x28, x8]\n"
    "fmla z28.s, p3/M, z3.s, z12.s\n"
    "ldr x27, [x7, #0xd8]\n"
    "fmla z26.s, p3/M, z2.s, z12.s\n"
    "ldr x26, [x7, #0xe0]\n"
    "fmla z25.s, p3/M, z1.s, z12.s\n"
    "ldr x25, [x7, #0xe8]\n"
    "fmla z24.s, p3/M, z0.s, z12.s\n"
    "ld1w { z12.s }, p2/Z, [x11, x17, LSL #2]\n"
    "fmla z19.s, p3/M, z7.s, z11.s\n"
    "prfm pldl1keep, [x27, x8]\n"
    "fmla z18.s, p3/M, z6.s, z11.s\n"
    "ld1w { z11.s }, p2/Z, [x12, x17, LSL #2]\n"
    "fmla z31.s, p3/M, z7.s, z10.s\n"
    "prfm pldl1keep, [x26, x8]\n"
    "fmla z30.s, p3/M, z6.s, z10.s\n"
    "prfm pldl1keep, [x25, x8]\n"
    "fmla z27.s, p3/M, z4.s, z10.s\n"
    "ldr x24, [x7, #0xf0]\n"
    "fmla z26.s, p3/M, z3.s, z10.s\n"
    "ldr x23, [x7, #0xf8]\n"
    "fmla z23.s, p3/M, z1.s, z10.s\n"
    "ldr x14, [x7, #0x100]\n"
    "fmla z22.s, p3/M, z0.s, z10.s\n"
    "ld1w { z10.s }, p2/Z, [x22, x17, LSL #2]\n"
    "fmla z17.s, p3/M, z8.s, z11.s\n"
    "prfm pldl1keep, [x24, x8]\n"
    "fmla z16.s, p3/M, z7.s, z11.s\n"
    "ld1w { z11.s }, p2/Z, [x21, x17, LSL #2]\n"
    "fmla z29.s, p3/M, z8.s, z12.s\n"
    "prfm pldl1keep, [x23, x8]\n"
    "fmla z28.s, p3/M, z7.s, z12.s\n"
    "prfm pldl1keep, [x14, x8]\n"
    "fmla z25.s, p3/M, z5.s, z12.s\n"
    "ldr x13, [x7, #0x108]\n"
    "fmla z24.s, p3/M, z4.s, z12.s\n"
    "ldr x12, [x7, #0x110]\n"
    "fmla z21.s, p3/M, z2.s, z12.s\n"
    "ldr x11, [x7, #0x118]\n"
    "fmla z20.s, p3/M, z1.s, z12.s\n"
    "ld1w { z12.s }, p2/Z, [x20, x17, LSL #2]\n"
    "fmla z31.s, p3/M, z2.s, z10.s\n"
    "prfm pldl1keep, [x13, x8]\n"
    "fmla z30.s, p3/M, z1.s, z10.s\n"
    "prfm pldl1keep, [x12, x8]\n"
    "fmla z29.s, p3/M, z0.s, z10.s\n"
    "ld1w { z10.s }, p2/Z, [x19, x17, LSL #2]\n"
    "fmla z27.s, p3/M, z7.s, z11.s\n"
    "prfm pldl1keep, [x11, x8]\n"
    "addvl x8, x8, #1\n"
    "fmla z26.s, p3/M, z6.s, z11.s\n"
    "ldr x22, [x5, #0x0]\n"
    "fmla z23.s, p3/M, z4.s, z11.s\n"
    "ldr x21, [x5, #0x8]\n"
    "fmla z22.s, p3/M, z3.s, z11.s\n"
    "ldr x20, [x5, #0x10]\n"
    "fmla z19.s, p3/M, z1.s, z11.s\n"
    "ldr x19, [x5, #0x18]\n"
    "fmla z18.s, p3/M, z0.s, z11.s\n"
    "ld1w { z11.s }, p2/Z, [x10, x17, LSL #2]\n"
    "fmla z30.s, p3/M, z2.s, z12.s\n"
    "ld1w { z13.s }, p3/Z, [x6]\n"
    "fmla z29.s, p3/M, z1.s, z12.s\n"
    "fmla z28.s, p3/M, z0.s, z12.s\n"
    "ld1w { z12.s }, p2/Z, [x9, x17, LSL #2]\n"
    "fmla z31.s, p3/M, z6.s, z10.s\n"
    "fmla z27.s, p3/M, z3.s, z10.s\n"
    "fmla z23.s, p3/M, z0.s, z10.s\n"
    "ld1w { z10.s }, p2/Z, [x28, x17, LSL #2]\n"
    "fmla z25.s, p3/M, z8.s, z11.s\n"
    "fmla z24.s, p3/M, z7.s, z11.s\n"
    "fmla z21.s, p3/M, z5.s, z11.s\n"
    "fmla z20.s, p3/M, z4.s, z11.s\n"
    "fmla z17.s, p3/M, z2.s, z11.s\n"
    "fmla z16.s, p3/M, z1.s, z11.s\n"
    "ld1w { z11.s }, p2/Z, [x27, x17, LSL #2]\n"
    "fmla z28.s, p3/M, z8.s, z12.s\n"
    "fmla z24.s, p3/M, z5.s, z12.s\n"
    "fmla z20.s, p3/M, z2.s, z12.s\n"
    "ld1w { z12.s }, p2/Z, [x26, x17, LSL #2]\n"
    "fmla z27.s, p3/M, z6.s, z10.s\n"
    "fmla z23.s, p3/M, z3.s, z10.s\n"
    "fmla z19.s, p3/M, z0.s, z10.s\n"
    "ld1w { z10.s }, p2/Z, [x25, x17, LSL #2]\n"
    "fmla z22.s, p3/M, z7.s, z11.s\n"
    "fmla z21.s, p3/M, z6.s, z11.s\n"
    "fmla z23.s, p3/M, z8.s, z11.s\n"
    "fmla z19.s, p3/M, z5.s, z11.s\n"
    "fmla z18.s, p3/M, z4.s, z11.s\n"
    "fmla z17.s, p3/M, z3.s, z11.s\n"
    "ld1w { z11.s }, p2/Z, [x24, x17, LSL #2]\n"
    "fmla z24.s, p3/M, z8.s, z12.s\n"
    "fmla z20.s, p3/M, z5.s, z12.s\n"
    "fmla z16.s, p3/M, z2.s, z12.s\n"
    "ld1w { z12.s }, p2/Z, [x23, x17, LSL #2]\n"
    "fmla z19.s, p3/M, z8.s, z10.s\n"
    "fmla z18.s, p3/M, z7.s, z10.s\n"
    "fmla z17.s, p3/M, z6.s, z10.s\n"
    "ld1w { z10.s }, p2/Z, [x14, x17, LSL #2]\n"
    "fmla z22.s, p3/M, z8.s, z11.s\n"
    "fmla z21.s, p3/M, z7.s, z11.s\n"
    "fmla z20.s, p3/M, z6.s, z11.s\n"
    "fmla z18.s, p3/M, z5.s, z11.s\n"
    "fmla z17.s, p3/M, z4.s, z11.s\n"
    "fmla z16.s, p3/M, z3.s, z11.s\n"
    "ld1w { z11.s }, p2/Z, [x13, x17, LSL #2]\n"
    "fmla z31.s, p3/M, z4.s, z10.s\n"
    "ldp x14, x13, [x7, #0x0]\n"
    "fmla z18.s, p3/M, z8.s, z12.s\n"
    "ld1w { z9.s }, p1/Z, [x14, x16, LSL #2]\n"
    "fmla z17.s, p3/M, z7.s, z12.s\n"
    "fmla z16.s, p3/M, z6.s, z12.s\n"
    "ld1w { z12.s }, p2/Z, [x12, x17, LSL #2]\n"
    "fmla z30.s, p3/M, z3.s, z10.s\n"
    "prfm pldl1keep, [x14, x8]\n"
    "fmla z27.s, p3/M, z1.s, z10.s\n"
    "prfm pldl1keep, [x13, x8]\n"
    "fmla z26.s, p3/M, z0.s, z10.s\n"
    "ld1w { z10.s }, p2/Z, [x11, x17, LSL #2]\n"
    "incw x17\n"
    "fmla z29.s, p3/M, z5.s, z11.s\n"
    "ldp x12, x11, [x7, #0x10]\n"
    "whilelt p2.s, x17, %x[n_channels]\n"
    "fmla z28.s, p3/M, z4.s, z11.s\n"
    "ld1w { z0.s }, p3/Z, [x6, #1, MUL VL]\n"
    "fmla z25.s, p3/M, z2.s, z11.s\n"
    "ld1w { z2.s }, p3/Z, [x6, #3, MUL VL]\n"
    "fmla z24.s, p3/M, z1.s, z11.s\n"
    "ld1w { z11.s }, p1/Z, [x12, x16, LSL #2]\n"
    "fmla z23.s, p3/M, z7.s, z12.s\n"
    "prfm pldl1keep, [x12, x8]\n"
    "fmla z22.s, p3/M, z6.s, z12.s\n"
    "prfm pldl1keep, [x11, x8]\n"
    "fmla z19.s, p3/M, z4.s, z12.s\n"
    "ld1w { z1.s }, p3/Z, [x6, #2, MUL VL]\n"
    "fmla z18.s, p3/M, z3.s, z12.s\n"
    "ld1w { z12.s }, p1/Z, [x11, x16, LSL #2]\n"
    "fmla z21.s, p3/M, z8.s, z10.s\n"
    "ld1w { z3.s }, p3/Z, [x6, #4, MUL VL]\n"
    "fmla z20.s, p3/M, z7.s, z10.s\n"
    "ld1w { z6.s }, p3/Z, [x6, #7, MUL VL]\n"
    "fmla z17.s, p3/M, z5.s, z10.s\n"
    "ld1w { z5.s }, p3/Z, [x6, #6, MUL VL]\n"
    "fmla z16.s, p3/M, z4.s, z10.s\n"
    "ld1w { z10.s }, p1/Z, [x13, x16, LSL #2]\n"
    "incw x16\n"
    "fmax z31.s, p3/M, z31.s, z15.s\n"
    "ld1w { z4.s }, p3/Z, [x6, #5, MUL VL]\n"
    "addvl x6, x6, #16\n"
    "fmax z30.s, p3/M, z30.s, z15.s\n"
    "ld1w { z7.s }, p3/Z, [x6, #-8, MUL VL]\n"
    "cmp x16, %x[n_channels]\n"
    "fmax z29.s, p3/M, z29.s, z15.s\n"
    "ld1w { z8.s }, p3/Z, [x6, #-7, MUL VL]\n"
    "addvl x6, x6, #-6\n"
    "fmax z28.s, p3/M, z28.s, z15.s\n"
    "fmax z27.s, p3/M, z27.s, z15.s\n"
    "fmin z31.s, p3/M, z31.s, z14.s\n"
    "st1w { z31.s }, p0, [x22, x15, LSL #2]\n"
    "mov z31.d, z13.d\n"
    "fmin z30.s, p3/M, z30.s, z14.s\n"
    "ldr x22, [x5, #0x20]\n"
    "fmin z29.s, p3/M, z29.s, z14.s\n"
    "st1w { z30.s }, p0, [x21, x15, LSL #2]\n"
    "mov z30.d, z13.d\n"
    "fmin z28.s, p3/M, z28.s, z14.s\n"
    "st1w { z29.s }, p0, [x20, x15, LSL #2]\n"
    "mov z29.d, z13.d\n"
    "ldr x21, [x5, #0x28]\n"
    "fmin z27.s, p3/M, z27.s, z14.s\n"
    "ldr x20, [x5, #0x30]\n"
    "fmax z26.s, p3/M, z26.s, z15.s\n"
    "st1w { z28.s }, p0, [x19, x15, LSL #2]\n"
    "mov z28.d, z13.d\n"
    "ldr x19, [x5, #0x38]\n"
    "fmax z25.s, p3/M, z25.s, z15.s\n"
    "st1w { z27.s }, p0, [x22, x15, LSL #2]\n"
    "mov z27.d, z13.d\n"
    "ldr x22, [x5, #0x40]\n"
    "fmin z26.s, p3/M, z26.s, z14.s\n"
    "st1w { z26.s }, p0, [x21, x15, LSL #2]\n"
    "mov z26.d, z13.d\n"
    "fmin z25.s, p3/M, z25.s, z14.s\n"
    "ldr x21, [x5, #0x48]\n"
    "fmax z24.s, p3/M, z24.s, z15.s\n"
    "st1w { z25.s }, p0, [x20, x15, LSL #2]\n"
    "mov z25.d, z13.d\n"
    "fmax z23.s, p3/M, z23.s, z15.s\n"
    "ldr x20, [x5, #0x50]\n"
    "fmin z24.s, p3/M, z24.s, z14.s\n"
    "st1w { z24.s }, p0, [x19, x15, LSL #2]\n"
    "mov z24.d, z13.d\n"
    "fmin z23.s, p3/M, z23.s, z14.s\n"
    "ldr x19, [x5, #0x58]\n"
    "fmax z22.s, p3/M, z22.s, z15.s\n"
    "st1w { z23.s }, p0, [x22, x15, LSL #2]\n"
    "mov z23.d, z13.d\n"
    "fmax z21.s, p3/M, z21.s, z15.s\n"
    "ldr x22, [x5, #0x60]\n"
    "fmin z22.s, p3/M, z22.s, z14.s\n"
    "st1w { z22.s }, p0, [x21, x15, LSL #2]\n"
    "mov z22.d, z13.d\n"
    "fmin z21.s, p3/M, z21.s, z14.s\n"
    "ldr x21, [x5, #0x68]\n"
    "fmax z20.s, p3/M, z20.s, z15.s\n"
    "st1w { z21.s }, p0, [x20, x15, LSL #2]\n"
    "mov z21.d, z13.d\n"
    "fmax z19.s, p3/M, z19.s, z15.s\n"
    "ldr x20, [x5, #0x70]\n"
    "fmin z20.s, p3/M, z20.s, z14.s\n"
    "st1w { z20.s }, p0, [x19, x15, LSL #2]\n"
    "mov z20.d, z13.d\n"
    "fmin z19.s, p3/M, z19.s, z14.s\n"
    "ldr x19, [x5, #0x78]\n"
    "fmax z18.s, p3/M, z18.s, z15.s\n"
    "st1w { z19.s }, p0, [x22, x15, LSL #2]\n"
    "mov z19.d, z13.d\n"
    "fmax z17.s, p3/M, z17.s, z15.s\n"
    "fmin z18.s, p3/M, z18.s, z14.s\n"
    "st1w { z18.s }, p0, [x21, x15, LSL #2]\n"
    "mov z18.d, z13.d\n"
    "fmin z17.s, p3/M, z17.s, z14.s\n"
    "st1w { z17.s }, p0, [x20, x15, LSL #2]\n"
    "mov z17.d, z13.d\n"
    "fmax z16.s, p3/M, z16.s, z15.s\n"
    "fmin z16.s, p3/M, z16.s, z14.s\n"
    "st1w { z16.s }, p0, [x19, x15, LSL #2]\n"
    "mov z16.d, z13.d\n"
    "blt 1b\n"
    "2:"  // Channel tail
    "fmla z31.s, p3/M, z8.s, z9.s\n"
    "ldr x22, [x7, #0x20]\n"
    "incw x15\n"
    "fmla z30.s, p3/M, z7.s, z9.s\n"
    "ldr x21, [x7, #0x28]\n"
    "mov p0.b, p2.b\n"
    "fmla z29.s, p3/M, z6.s, z9.s\n"
    "ldr x20, [x7, #0x30]\n"
    "fmla z27.s, p3/M, z5.s, z9.s\n"
    "prfm pldl1keep, [x22, x8]\n"
    "fmla z26.s, p3/M, z4.s, z9.s\n"
    "prfm pldl1keep, [x21, x8]\n"
    "fmla z25.s, p3/M, z3.s, z9.s\n"
    "prfm pldl1keep, [x20, x8]\n"
    "fmla z23.s, p3/M, z2.s, z9.s\n"
    "ldr x19, [x7, #0x38]\n"
    "fmla z22.s, p3/M, z1.s, z9.s\n"
    "ldr x10, [x7, #0x40]\n"
    "fmla z21.s, p3/M, z0.s, z9.s\n"
    "ld1w { z9.s }, p2/Z, [x20, x17, LSL #2]\n"
    "fmla z31.s, p3/M, z0.s, z10.s\n"
    "ld1w { z10.s }, p2/Z, [x22, x17, LSL #2]\n"
    "fmla z28.s, p3/M, z2.s, z11.s\n"
    "ld1w { z11.s }, p2/Z, [x21, x17, LSL #2]\n"
    "fmla z30.s, p3/M, z8.s, z12.s\n"
    "prfm pldl1keep, [x19, x8]\n"
    "fmla z29.s, p3/M, z7.s, z12.s\n"
    "prfm pldl1keep, [x10, x8]\n"
    "fmla z26.s, p3/M, z5.s, z12.s\n"
    "ldr x9, [x7, #0x48]\n"
    "fmla z28.s, p3/M, z6.s, z12.s\n"
    "ldr x28, [x7, #0x50]\n"
    "fmla z25.s, p3/M, z4.s, z12.s\n"
    "ldr x27, [x7, #0x58]\n"
    "fmla z24.s, p3/M, z3.s, z12.s\n"
    "prfm pldl1keep, [x9, x8]\n"
    "fmla z22.s, p3/M, z2.s, z12.s\n"
    "prfm pldl1keep, [x28, x8]\n"
    "fmla z21.s, p3/M, z1.s, z12.s\n"
    "prfm pldl1keep, [x27, x8]\n"
    "fmla z20.s, p3/M, z0.s, z12.s\n"
    "ld1w { z12.s }, p2/Z, [x19, x17, LSL #2]\n"
    "fmla z19.s, p3/M, z6.s, z10.s\n"
    "ld1w { z10.s }, p2/Z, [x9, x17, LSL #2]\n"
    "fmla z16.s, p3/M, z8.s, z11.s\n"
    "ld1w { z11.s }, p2/Z, [x10, x17, LSL #2]\n"
    "fmla z27.s, p3/M, z8.s, z9.s\n"
    "ldr x26, [x7, #0x60]\n"
    "fmla z26.s, p3/M, z7.s, z9.s\n"
    "ldr x25, [x7, #0x68]\n"
    "fmla z25.s, p3/M, z6.s, z9.s\n"
    "ldr x24, [x7, #0x70]\n"
    "fmla z23.s, p3/M, z5.s, z9.s\n"
    "prfm pldl1keep, [x26, x8]\n"
    "fmla z22.s, p3/M, z4.s, z9.s\n"
    "prfm pldl1keep, [x25, x8]\n"
    "fmla z21.s, p3/M, z3.s, z9.s\n"
    "prfm pldl1keep, [x24, x8]\n"
    "fmla z19.s, p3/M, z2.s, z9.s\n"
    "ldr x23, [x7, #0x78]\n"
    "fmla z18.s, p3/M, z1.s, z9.s\n"
    "ldr x14, [x7, #0x80]\n"
    "fmla z17.s, p3/M, z0.s, z9.s\n"
    "ld1w { z9.s }, p2/Z, [x28, x17, LSL #2]\n"
    "fmla z31.s, p3/M, z1.s, z12.s\n"
    "prfm pldl1keep, [x23, x8]\n"
    "fmla z30.s, p3/M, z0.s, z12.s\n"
    "ld1w { z12.s }, p2/Z, [x27, x17, LSL #2]\n"
    "fmla z29.s, p3/M, z2.s, z11.s\n"
    "prfm pldl1keep, [x14, x8]\n"
    "fmla z28.s, p3/M, z1.s, z11.s\n"
    "ld1w { z11.s }, p2/Z, [x26, x17, LSL #2]\n"
    "fmla z26.s, p3/M, z8.s, z10.s\n"
    "ldr x13, [x7, #0x88]\n"
    "fmla z25.s, p3/M, z7.s, z10.s\n"
    "ldr x12, [x7, #0x90]\n"
    "fmla z24.s, p3/M, z6.s, z10.s\n"
    "ldr x11, [x7, #0x98]\n"
    "fmla z22.s, p3/M, z5.s, z10.s\n"
    "prfm pldl1keep, [x13, x8]\n"
    "fmla z21.s, p3/M, z4.s, z10.s\n"
    "prfm pldl1keep, [x12, x8]\n"
    "fmla z20.s, p3/M, z3.s, z10.s\n"
    "prfm pldl1keep, [x11, x8]\n"
    "fmla z18.s, p3/M, z2.s, z10.s\n"
    "ldr x22, [x7, #0xa0]\n"
    "fmla z17.s, p3/M, z1.s, z10.s\n"
    "ldr x21, [x7, #0xa8]\n"
    "fmla z16.s, p3/M, z0.s, z10.s\n"
    "ld1w { z10.s }, p2/Z, [x25, x17, LSL #2]\n"
    "fmla z31.s, p3/M, z3.s, z9.s\n"
    "prfm pldl1keep, [x22, x8]\n"
    "fmla z27.s, p3/M, z0.s, z9.s\n"
    "prfm pldl1keep, [x21, x8]\n"
    "fmla z28.s, p3/M, z5.s, z12.s\n"
    "ldr x20, [x7, #0xb0]\n"
    "fmla z24.s, p3/M, z2.s, z12.s\n"
    "ld1w { z12.s }, p2/Z, [x23, x17, LSL #2]\n"
    "fmla z23.s, p3/M, z6.s, z11.s\n"
    "ldr x19, [x7, #0xb8]\n"
    "fmla z19.s, p3/M, z3.s, z11.s\n"
    "ld1w { z11.s }, p2/Z, [x24, x17, LSL #2]\n"
    "fmla z31.s, p3/M, z5.s, z10.s\n"
    "prfm pldl1keep, [x20, x8]\n"
    "fmla z30.s, p3/M, z4.s, z10.s\n"
    "prfm pldl1keep, [x19, x8]\n"
    "fmla z29.s, p3/M, z3.s, z10.s\n"
    "ldr x10, [x7, #0xc0]\n"
    "fmla z27.s, p3/M, z2.s, z10.s\n"
    "ldr x9, [x7, #0xc8]\n"
    "fmla z26.s, p3/M, z1.s, z10.s\n"
    "ldr x28, [x7, #0xd0]\n"
    "fmla z25.s, p3/M, z0.s, z10.s\n"
    "ld1w { z10.s }, p2/Z, [x13, x17, LSL #2]\n"
    "fmla z20.s, p3/M, z8.s, z11.s\n"
    "prfm pldl1keep, [x10, x8]\n"
    "fmla z16.s, p3/M, z5.s, z11.s\n"
    "ld1w { z11.s }, p2/Z, [x14, x17, LSL #2]\n"
    "fmla z30.s, p3/M, z5.s, z12.s\n"
    "prfm pldl1keep, [x9, x8]\n"
    "fmla z29.s, p3/M, z4.s, z12.s\n"
    "prfm pldl1keep, [x28, x8]\n"
    "fmla z28.s, p3/M, z3.s, z12.s\n"
    "ldr x27, [x7, #0xd8]\n"
    "fmla z26.s, p3/M, z2.s, z12.s\n"
    "ldr x26, [x7, #0xe0]\n"
    "fmla z25.s, p3/M, z1.s, z12.s\n"
    "ldr x25, [x7, #0xe8]\n"
    "fmla z24.s, p3/M, z0.s, z12.s\n"
    "ld1w { z12.s }, p2/Z, [x11, x17, LSL #2]\n"
    "fmla z19.s, p3/M, z7.s, z11.s\n"
    "prfm pldl1keep, [x27, x8]\n"
    "fmla z18.s, p3/M, z6.s, z11.s\n"
    "ld1w { z11.s }, p2/Z, [x12, x17, LSL #2]\n"
    "fmla z31.s, p3/M, z7.s, z10.s\n"
    "prfm pldl1keep, [x26, x8]\n"
    "fmla z30.s, p3/M, z6.s, z10.s\n"
    "prfm pldl1keep, [x25, x8]\n"
    "fmla z27.s, p3/M, z4.s, z10.s\n"
    "ldr x24, [x7, #0xf0]\n"
    "fmla z26.s, p3/M, z3.s, z10.s\n"
    "ldr x23, [x7, #0xf8]\n"
    "fmla z23.s, p3/M, z1.s, z10.s\n"
    "ldr x14, [x7, #0x100]\n"
    "fmla z22.s, p3/M, z0.s, z10.s\n"
    "ld1w { z10.s }, p2/Z, [x22, x17, LSL #2]\n"
    "fmla z17.s, p3/M, z8.s, z11.s\n"
    "prfm pldl1keep, [x24, x8]\n"
    "fmla z16.s, p3/M, z7.s, z11.s\n"
    "ld1w { z11.s }, p2/Z, [x21, x17, LSL #2]\n"
    "fmla z29.s, p3/M, z8.s, z12.s\n"
    "prfm pldl1keep, [x23, x8]\n"
    "fmla z28.s, p3/M, z7.s, z12.s\n"
    "prfm pldl1keep, [x14, x8]\n"
    "fmla z25.s, p3/M, z5.s, z12.s\n"
    "ldr x13, [x7, #0x108]\n"
    "fmla z24.s, p3/M, z4.s, z12.s\n"
    "ldr x12, [x7, #0x110]\n"
    "fmla z21.s, p3/M, z2.s, z12.s\n"
    "ldr x11, [x7, #0x118]\n"
    "fmla z20.s, p3/M, z1.s, z12.s\n"
    "ld1w { z12.s }, p2/Z, [x20, x17, LSL #2]\n"
    "fmla z31.s, p3/M, z2.s, z10.s\n"
    "prfm pldl1keep, [x13, x8]\n"
    "fmla z30.s, p3/M, z1.s, z10.s\n"
    "prfm pldl1keep, [x12, x8]\n"
    "fmla z29.s, p3/M, z0.s, z10.s\n"
    "ld1w { z10.s }, p2/Z, [x19, x17, LSL #2]\n"
    "fmla z27.s, p3/M, z7.s, z11.s\n"
    "prfm pldl1keep, [x11, x8]\n"
    "fmla z26.s, p3/M, z6.s, z11.s\n"
    "ldr x22, [x5, #0x0]\n"
    "fmla z23.s, p3/M, z4.s, z11.s\n"
    "ldr x21, [x5, #0x8]\n"
    "fmla z22.s, p3/M, z3.s, z11.s\n"
    "ldr x20, [x5, #0x10]\n"
    "fmla z19.s, p3/M, z1.s, z11.s\n"
    "ldr x19, [x5, #0x18]\n"
    "fmla z18.s, p3/M, z0.s, z11.s\n"
    "ld1w { z11.s }, p2/Z, [x10, x17, LSL #2]\n"
    "fmla z30.s, p3/M, z2.s, z12.s\n"
    "fmla z29.s, p3/M, z1.s, z12.s\n"
    "fmla z28.s, p3/M, z0.s, z12.s\n"
    "ld1w { z12.s }, p2/Z, [x9, x17, LSL #2]\n"
    "fmla z31.s, p3/M, z6.s, z10.s\n"
    "fmla z27.s, p3/M, z3.s, z10.s\n"
    "fmla z23.s, p3/M, z0.s, z10.s\n"
    "ld1w { z10.s }, p2/Z, [x28, x17, LSL #2]\n"
    "fmla z25.s, p3/M, z8.s, z11.s\n"
    "fmla z24.s, p3/M, z7.s, z11.s\n"
    "fmla z21.s, p3/M, z5.s, z11.s\n"
    "fmla z20.s, p3/M, z4.s, z11.s\n"
    "fmla z17.s, p3/M, z2.s, z11.s\n"
    "fmla z16.s, p3/M, z1.s, z11.s\n"
    "ld1w { z11.s }, p2/Z, [x27, x17, LSL #2]\n"
    "fmla z28.s, p3/M, z8.s, z12.s\n"
    "fmla z24.s, p3/M, z5.s, z12.s\n"
    "fmla z20.s, p3/M, z2.s, z12.s\n"
    "ld1w { z12.s }, p2/Z, [x26, x17, LSL #2]\n"
    "fmla z27.s, p3/M, z6.s, z10.s\n"
    "fmla z23.s, p3/M, z3.s, z10.s\n"
    "fmla z19.s, p3/M, z0.s, z10.s\n"
    "ld1w { z10.s }, p2/Z, [x25, x17, LSL #2]\n"
    "fmla z22.s, p3/M, z7.s, z11.s\n"
    "fmla z21.s, p3/M, z6.s, z11.s\n"
    "fmla z23.s, p3/M, z8.s, z11.s\n"
    "fmla z19.s, p3/M, z5.s, z11.s\n"
    "fmla z18.s, p3/M, z4.s, z11.s\n"
    "fmla z17.s, p3/M, z3.s, z11.s\n"
    "ld1w { z11.s }, p2/Z, [x24, x17, LSL #2]\n"
    "fmla z24.s, p3/M, z8.s, z12.s\n"
    "fmla z20.s, p3/M, z5.s, z12.s\n"
    "fmla z16.s, p3/M, z2.s, z12.s\n"
    "ld1w { z12.s }, p2/Z, [x23, x17, LSL #2]\n"
    "fmla z19.s, p3/M, z8.s, z10.s\n"
    "fmla z18.s, p3/M, z7.s, z10.s\n"
    "fmla z17.s, p3/M, z6.s, z10.s\n"
    "ld1w { z10.s }, p2/Z, [x14, x17, LSL #2]\n"
    "fmla z22.s, p3/M, z8.s, z11.s\n"
    "fmla z21.s, p3/M, z7.s, z11.s\n"
    "fmla z20.s, p3/M, z6.s, z11.s\n"
    "fmla z18.s, p3/M, z5.s, z11.s\n"
    "fmla z17.s, p3/M, z4.s, z11.s\n"
    "fmla z16.s, p3/M, z3.s, z11.s\n"
    "ld1w { z11.s }, p2/Z, [x13, x17, LSL #2]\n"
    "fmla z31.s, p3/M, z4.s, z10.s\n"
    "fmla z18.s, p3/M, z8.s, z12.s\n"
    "fmla z17.s, p3/M, z7.s, z12.s\n"
    "fmla z16.s, p3/M, z6.s, z12.s\n"
    "ld1w { z12.s }, p2/Z, [x12, x17, LSL #2]\n"
    "fmla z30.s, p3/M, z3.s, z10.s\n"
    "fmla z27.s, p3/M, z1.s, z10.s\n"
    "fmla z26.s, p3/M, z0.s, z10.s\n"
    "ld1w { z10.s }, p2/Z, [x11, x17, LSL #2]\n"
    "fmla z29.s, p3/M, z5.s, z11.s\n"
    "fmla z28.s, p3/M, z4.s, z11.s\n"
    "fmla z25.s, p3/M, z2.s, z11.s\n"
    "fmla z24.s, p3/M, z1.s, z11.s\n"
    "fmla z23.s, p3/M, z7.s, z12.s\n"
    "fmla z22.s, p3/M, z6.s, z12.s\n"
    "fmla z19.s, p3/M, z4.s, z12.s\n"
    "fmla z18.s, p3/M, z3.s, z12.s\n"
    "fmla z21.s, p3/M, z8.s, z10.s\n"
    "fmla z20.s, p3/M, z7.s, z10.s\n"
    "fmla z17.s, p3/M, z5.s, z10.s\n"
    "fmla z16.s, p3/M, z4.s, z10.s\n"
    "fmax z31.s, p3/M, z31.s, z15.s\n"
    "fmax z30.s, p3/M, z30.s, z15.s\n"
    "fmax z29.s, p3/M, z29.s, z15.s\n"
    "fmax z28.s, p3/M, z28.s, z15.s\n"
    "fmin z31.s, p3/M, z31.s, z14.s\n"
    "st1w { z31.s }, p0, [x22, x15, LSL #2]\n"
    "fmin z30.s, p3/M, z30.s, z14.s\n"
    "fmin z29.s, p3/M, z29.s, z14.s\n"
    "ldr x22, [x5, #0x20]\n"
    "fmin z28.s, p3/M, z28.s, z14.s\n"
    "st1w { z30.s }, p0, [x21, x15, LSL #2]\n"
    "fmax z27.s, p3/M, z27.s, z15.s\n"
    "fmax z26.s, p3/M, z26.s, z15.s\n"
    "st1w { z29.s }, p0, [x20, x15, LSL #2]\n"
    "fmax z25.s, p3/M, z25.s, z15.s\n"
    "st1w { z28.s }, p0, [x19, x15, LSL #2]\n"
    "fmax z24.s, p3/M, z24.s, z15.s\n"
    "ldr x21, [x5, #0x28]\n"
    "fmax z23.s, p3/M, z23.s, z15.s\n"
    "ldr x20, [x5, #0x30]\n"
    "fmin z27.s, p3/M, z27.s, z14.s\n"
    "ldr x19, [x5, #0x38]\n"
    "fmin z26.s, p3/M, z26.s, z14.s\n"
    "st1w { z27.s }, p0, [x22, x15, LSL #2]\n"
    "fmin z25.s, p3/M, z25.s, z14.s\n"
    "fmin z24.s, p3/M, z24.s, z14.s\n"
    "st1w { z26.s }, p0, [x21, x15, LSL #2]\n"
    "fmin z23.s, p3/M, z23.s, z14.s\n"
    "ldr x22, [x5, #0x40]\n"
    "fmax z22.s, p3/M, z22.s, z15.s\n"
    "ldr x21, [x5, #0x48]\n"
    "fmax z21.s, p3/M, z21.s, z15.s\n"
    "st1w { z25.s }, p0, [x20, x15, LSL #2]\n"
    "fmax z20.s, p3/M, z20.s, z15.s\n"
    "st1w { z24.s }, p0, [x19, x15, LSL #2]\n"
    "fmax z19.s, p3/M, z19.s, z15.s\n"
    "st1w { z23.s }, p0, [x22, x15, LSL #2]\n"
    "fmin z22.s, p3/M, z22.s, z14.s\n"
    "ldr x20, [x5, #0x50]\n"
    "fmin z21.s, p3/M, z21.s, z14.s\n"
    "ldr x19, [x5, #0x58]\n"
    "fmin z20.s, p3/M, z20.s, z14.s\n"
    "ldr x22, [x5, #0x60]\n"
    "fmin z19.s, p3/M, z19.s, z14.s\n"
    "st1w { z22.s }, p0, [x21, x15, LSL #2]\n"
    "fmax z18.s, p3/M, z18.s, z15.s\n"
    "st1w { z21.s }, p0, [x20, x15, LSL #2]\n"
    "fmax z17.s, p3/M, z17.s, z15.s\n"
    "st1w { z20.s }, p0, [x19, x15, LSL #2]\n"
    "fmax z16.s, p3/M, z16.s, z15.s\n"
    "st1w { z19.s }, p0, [x22, x15, LSL #2]\n"
    "ldr x21, [x5, #0x68]\n"
    "fmin z18.s, p3/M, z18.s, z14.s\n"
    "ldr x20, [x5, #0x70]\n"
    "fmin z17.s, p3/M, z17.s, z14.s\n"
    "ldr x19, [x5, #0x78]\n"
    "fmin z16.s, p3/M, z16.s, z14.s\n"
    "st1w { z18.s }, p0, [x21, x15, LSL #2]\n"
    "st1w { z17.s }, p0, [x20, x15, LSL #2]\n"
    "st1w { z16.s }, p0, [x19, x15, LSL #2]\n"
    :
    : [n_channels] "r" ((unsigned long) n_channels), [offsetof_Args_inptrs] "I" (offsetof(Args, inptrs)), [offsetof_args_max] "I" (offsetof(Args, max)), [offsetof_args_min] "I" (offsetof(Args, min)), [offsetof_args_outptrs] "I" (offsetof(Args, outptrs)), [offsetof_args_params] "I" (offsetof(Args, params)), [params_struct] "r" (&params_struct)
    : "cc", "memory", "p0", "p1", "p2", "p3", "x5", "x6", "x7", "x8", "x9", "x10", "x11", "x12", "x13", "x14", "x15", "x16", "x17", "x19", "x20", "x21", "x22", "x23", "x24", "x25", "x26", "x27", "x28", "z0", "z1", "z2", "z3", "z4", "z5", "z6", "z7", "z8", "z9", "z10", "z11", "z12", "z13", "z14", "z15", "z16", "z17", "z18", "z19", "z20", "z21", "z22", "z23", "z24", "z25", "z26", "z27", "z28", "z29", "z30", "z31"
  );
}

}  // namespace depthwise
}  // namespace arm_conv

#endif  // defined(ARM_COMPUTE_ENABLE_SVE)
