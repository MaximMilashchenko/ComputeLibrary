/*
 * Copyright (c) 2019-2021 Arm Limited.
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
#ifndef ARM_COMPUTE_CPU_CONVERTQUANTIZEDSIGNEDNESS_KERNEL_H
#define ARM_COMPUTE_CPU_CONVERTQUANTIZEDSIGNEDNESS_KERNEL_H

#include "src/core/common/Macros.h"
#include "src/core/cpu/ICpuKernel.h"

namespace arm_compute
{
namespace cpu
{
namespace kernels
{
/** Kernel to convert asymmetric signed to asymmetric signed and vice-versa */
class CpuConvertQuantizedSignednessKernel : public ICpuKernel
{
public:
    CpuConvertQuantizedSignednessKernel() = default;
    ARM_COMPUTE_DISALLOW_COPY_ALLOW_MOVE(CpuConvertQuantizedSignednessKernel);
    /** Initialize the kernel input and output info.
     *
     * @param[in]  src Source tensor info. Data types supported: QASYMM8/QASYMM8_SIGNED.
     * @param[out] dst Destination tensor info. Data types supported: opposite of @p src.
     */
    void configure(const ITensorInfo *src, ITensorInfo *dst);
    /** Static function to check if given info will lead to a valid configuration
     *
     * Similar to CpuConvertQuantizedSignednessKernel::configure()
     *
     * @return a status
     */
    static Status validate(const ITensorInfo *src, const ITensorInfo *dst);

    // Inherited methods overridden:
    void run_op(ITensorPack &tensors, const Window &window, const ThreadInfo &info) override;
    const char *name() const override;
};
} // namespace kernels
} // namespace cpu
} // namespace arm_compute
#endif /*ARM_COMPUTE_CPU_CONVERTQUANTIZEDSIGNEDNESS_KERNEL_H */
