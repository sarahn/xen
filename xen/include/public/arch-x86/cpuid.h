/******************************************************************************
 * arch-x86/cpuid.h
 * 
 * CPUID interface to Xen.
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 * 
 * Copyright (c) 2007 Citrix Systems, Inc.
 * 
 * Authors:
 *    Keir Fraser <keir@xen.org>
 */

#ifndef __XEN_PUBLIC_ARCH_X86_CPUID_H__
#define __XEN_PUBLIC_ARCH_X86_CPUID_H__

/* Xen identification leaves start at 0x40000000. */
#define XEN_CPUID_FIRST_LEAF 0x40000000
#define XEN_CPUID_LEAF(i)    (XEN_CPUID_FIRST_LEAF + (i))

/*
 * Leaf 1 (0x40000000)
 * EAX: Largest Xen-information leaf. All leaves up to an including @EAX
 *      are supported by the Xen host.
 * EBX-EDX: "XenVMMXenVMM" signature, allowing positive identification
 *      of a Xen host.
 */
#define XEN_CPUID_SIGNATURE_EBX 0x566e6558 /* "XenV" */
#define XEN_CPUID_SIGNATURE_ECX 0x65584d4d /* "MMXe" */
#define XEN_CPUID_SIGNATURE_EDX 0x4d4d566e /* "nVMM" */

/*
 * Leaf 2 (0x40000001)
 * EAX[31:16]: Xen major version.
 * EAX[15: 0]: Xen minor version.
 * EBX-EDX: Reserved (currently all zeroes).
 */

/*
 * Leaf 3 (0x40000002)
 * EAX: Number of hypercall transfer pages. This register is always guaranteed
 *      to specify one hypercall page.
 * EBX: Base address of Xen-specific MSRs.
 * ECX: Features 1. Unused bits are set to zero.
 * EDX: Features 2. Unused bits are set to zero.
 */

/* Does the host support MMU_PT_UPDATE_PRESERVE_AD for this guest? */
#define _XEN_CPUID_FEAT1_MMU_PT_UPDATE_PRESERVE_AD 0
#define XEN_CPUID_FEAT1_MMU_PT_UPDATE_PRESERVE_AD  (1u<<0)

/* Will the host not automatically clear CR0.TS after exiting ? */
#define _XEN_CPUID_FEAT1_DEV_NA_TS_ALLOWED 1
#define XEN_CPUID_FEAT1_DEV_NA_TS_ALLOWED \
    (1u<<_XEN_CPUID_FEAT1_DEV_NA_TS_ALLOWED)

#endif /* __XEN_PUBLIC_ARCH_X86_CPUID_H__ */
