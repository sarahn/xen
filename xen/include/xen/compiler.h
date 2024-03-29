#ifndef __LINUX_COMPILER_H
#define __LINUX_COMPILER_H

#if !defined(__GNUC__) || (__GNUC__ < 4)
#error Sorry, your compiler is too old/not recognized.
#endif

#define barrier()     __asm__ __volatile__("": : :"memory")

#define likely(x)     __builtin_expect((x),1)
#define unlikely(x)   __builtin_expect((x),0)

#define inline        __inline__
#define always_inline __inline__ __attribute__ ((always_inline))
#define noinline      __attribute__((noinline))

#define noreturn      __attribute__((noreturn))

#if (!defined(__clang__) && (__GNUC__ == 4) && (__GNUC_MINOR__ < 5))
#define unreachable() do {} while (1)
#else
#define unreachable() __builtin_unreachable()
#endif

#ifdef __clang__
/* Clang can replace some vars with new automatic ones that go in .data;
 * mark all explicit-segment vars 'used' to prevent that. */
#define __section(s)      __used __attribute__((__section__(s)))
#else
#define __section(s)      __attribute__((__section__(s)))
#endif
#define __used_section(s) __used __attribute__((__section__(s)))
#define __text_section(s) __attribute__((__section__(s)))

#ifdef INIT_SECTIONS_ONLY
/*
 * For sources indicated to have only init code, make sure even
 * inline functions not expanded inline get placed in .init.text.
 */
#include <xen/init.h>
#define __inline__ __inline__ __init
#endif

#define __attribute_pure__  __attribute__((pure))
#define __attribute_const__ __attribute__((__const__))

/*
 * The difference between the following two attributes is that __used is
 * intended to be used in cases where a reference to an identifier may be
 * invisible to the compiler (e.g. an inline assembly operand not listed
 * in the asm()'s operands), preventing the compiler from eliminating the
 * variable or function.
 * __maybe_unused otoh is to be used to merely prevent warnings (e.g. when
 * an identifier is used only inside a preprocessor conditional, yet putting
 * its declaration/definition inside another conditional would harm code
 * readability).
 */
#define __used         __attribute__((__used__))
#define __maybe_unused __attribute__((__unused__))

#define __must_check __attribute__((warn_unused_result))

#define offsetof(a,b) __builtin_offsetof(a,b)

#if !defined(__STDC_VERSION__) || __STDC_VERSION__ < 201112L
#define alignof __alignof__
#endif

/* &a[0] degrades to a pointer: a different type from an array */
#define __must_be_array(a) \
  BUILD_BUG_ON_ZERO(__builtin_types_compatible_p(typeof(a), typeof(&a[0])))

#ifdef GCC_HAS_VISIBILITY_ATTRIBUTE
/* Results in more efficient PIC code (no indirections through GOT or PLT). */
#pragma GCC visibility push(hidden)
#endif

/* This macro obfuscates arithmetic on a variable address so that gcc
   shouldn't recognize the original var, and make assumptions about it */
/*
 * Versions of the ppc64 compiler before 4.1 had a bug where use of
 * RELOC_HIDE could trash r30. The bug can be worked around by changing
 * the inline assembly constraint from =g to =r, in this particular
 * case either is valid.
 */
#define RELOC_HIDE(ptr, off)                    \
  ({ unsigned long __ptr;                       \
    __asm__ ("" : "=r"(__ptr) : "0"(ptr));      \
    (typeof(ptr)) (__ptr + (off)); })

#endif /* __LINUX_COMPILER_H */
