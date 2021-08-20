/*
 * Copyright (c) 2020-2021 Arm Limited.
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
#ifndef SRC_CORE_SVE_KERNELS_ADD_LIST_H
#define SRC_CORE_SVE_KERNELS_ADD_LIST_H

#if defined(ARM_COMPUTE_ENABLE_SVE)
#include "arm_compute/core/Types.h"
#include "arm_compute/core/utils/misc/Traits.h"
#include "src/core/NEON/SVEMath.h"
#include "src/core/NEON/wrapper/intrinsics/intrinsics.h"
#include "src/core/cpu/kernels/add/sve/impl.h"
#include <arm_sve.h>

namespace arm_compute
{
namespace cpu
{
#define DECLARE_ADD_KERNEL(func_name) \
    void func_name(const ITensor *src0, const ITensor *src1, ITensor *dst, const ConvertPolicy &policy, const Window &window)

DECLARE_ADD_KERNEL(add_qasymm8_sve);
DECLARE_ADD_KERNEL(add_qasymm8_signed_sve);
DECLARE_ADD_KERNEL(add_qsymm16_sve);

#undef DECLARE_ADD_KERNEL

} // namespace cpu
} // namespace arm_compute
#endif // defined(ARM_COMPUTE_ENABLE_SVE)
#endif // SRC_CORE_SVE_KERNELS_ADD_LIST_H