/* FUNCTION: __builtin_ia32_sfence */

#if defined(__i386__) || defined(__x86_64__)

void __builtin_ia32_sfence(void)
{
  __asm("sfence");
}

#endif

/* FUNCTION: __builtin_ia32_lfence */

#if defined(__i386__) || defined(__x86_64__)

void __builtin_ia32_lfence(void)
{
  __asm("lfence");
}

#endif

/* FUNCTION: __builtin_ia32_mfence */

#if defined(__i386__) || defined(__x86_64__)

void __builtin_ia32_mfence(void)
{
  __asm("mfence");
}

#endif

/* FUNCTION: __sync_synchronize */

void __sync_synchronize(void)
{
  // WARNING: this was a NOP before gcc 4.3.1,
  // but is now believed to be the strongest possible barrier.

  #if (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__) >= 40301
  __CPROVER_HIDE:;
  __CPROVER_fence("WWfence", "RRfence", "RWfence", "WRfence",
                  "WWcumul", "RRcumul", "RWcumul", "WRcumul");
  #endif
}

/* FUNCTION: __atomic_test_and_set */

void __atomic_thread_fence(int memorder);

_Bool __atomic_test_and_set(void *ptr, int memorder)
{
__CPROVER_HIDE:;
  __CPROVER_atomic_begin();
  _Bool result = *(char *)ptr == 1;
  *(char *)ptr = 1;
  __atomic_thread_fence(memorder);
  __CPROVER_atomic_end();
  return result;
}

/* FUNCTION: __atomic_clear */

void __atomic_thread_fence(int memorder);

void __atomic_clear(_Bool *ptr, int memorder)
{
__CPROVER_HIDE:;
  __CPROVER_atomic_begin();
  *(char *)ptr = 0;
  __atomic_thread_fence(memorder);
  __CPROVER_atomic_end();
}

/* FUNCTION: __atomic_thread_fence */

#if __STDC_VERSION__ >= 201112L
// GCC 4.8 did claim to support C++11, but failed to ship stdatomic.h
#  if !defined(__GNUC__) || (__GNUC__ * 100 + __GNUC_MINOR__) >= 409
#    include <stdatomic.h>
#  endif
#endif

#ifndef __ATOMIC_RELAXED
#  define __ATOMIC_RELAXED 0
#endif

#ifndef __ATOMIC_CONSUME
#  define __ATOMIC_CONSUME 1
#endif

#ifndef __ATOMIC_ACQUIRE
#  define __ATOMIC_ACQUIRE 2
#endif

#ifndef __ATOMIC_RELEASE
#  define __ATOMIC_RELEASE 3
#endif

#ifndef __ATOMIC_ACQ_REL
#  define __ATOMIC_ACQ_REL 4
#endif

#ifndef __ATOMIC_SEQ_CST
#  define __ATOMIC_SEQ_CST 5
#endif

void __atomic_thread_fence(int memorder)
{
__CPROVER_HIDE:;
  if(memorder == __ATOMIC_CONSUME || memorder == __ATOMIC_ACQUIRE)
    __CPROVER_fence("RRfence", "RWfence", "RRcumul", "RWcumul");
  else if(memorder == __ATOMIC_RELEASE)
    __CPROVER_fence("WRfence", "WWfence", "WRcumul", "WWcumul");
  else if(memorder == __ATOMIC_ACQ_REL || memorder == __ATOMIC_SEQ_CST)
    __CPROVER_fence(
      "WWfence",
      "RRfence",
      "RWfence",
      "WRfence",
      "WWcumul",
      "RRcumul",
      "RWcumul",
      "WRcumul");
}

/* FUNCTION: __atomic_signal_fence */

void __atomic_thread_fence(int memorder);

void __atomic_signal_fence(int memorder)
{
__CPROVER_HIDE:;
  __atomic_thread_fence(memorder);
}

/* FUNCTION: __atomic_always_lock_free */

_Bool __atomic_always_lock_free(__CPROVER_size_t size, void *ptr)
{
__CPROVER_HIDE:;
  (void)ptr;
  return size <= sizeof(__CPROVER_size_t);
}

/* FUNCTION: __atomic_is_lock_free */

_Bool __atomic_is_lock_free(__CPROVER_size_t size, void *ptr)
{
__CPROVER_HIDE:;
  (void)ptr;
  return size <= sizeof(__CPROVER_size_t);
}

/* FUNCTION: __builtin_ia32_vec_ext_v4hi */

typedef short __gcc_v4hi __attribute__((__vector_size__(8)));

short __builtin_ia32_vec_ext_v4hi(__gcc_v4hi vec, int offset)
{
  return *((short *)&vec + offset);
}

/* FUNCTION: __builtin_ia32_vec_ext_v8hi */

typedef short __gcc_v8hi __attribute__((__vector_size__(16)));

short __builtin_ia32_vec_ext_v8hi(__gcc_v8hi vec, int offset)
{
  return *((short *)&vec + offset);
}

/* FUNCTION: __builtin_ia32_vec_ext_v4si */

typedef int __gcc_v4si __attribute__((__vector_size__(16)));

int __builtin_ia32_vec_ext_v4si(__gcc_v4si vec, int offset)
{
  return *((int *)&vec + offset);
}

/* FUNCTION: __builtin_ia32_vec_ext_v2di */

typedef long long __gcc_v2di __attribute__((__vector_size__(16)));

long long __builtin_ia32_vec_ext_v2di(__gcc_v2di vec, int offset)
{
  return *((long long *)&vec + offset);
}

/* FUNCTION: __builtin_ia32_vec_ext_v16qi */

typedef char __gcc_v16qi __attribute__((__vector_size__(16)));

int __builtin_ia32_vec_ext_v16qi(__gcc_v16qi vec, int offset)
{
  return *((char *)&vec + offset);
}

/* FUNCTION: __builtin_ia32_vec_ext_v4sf */

typedef float __gcc_v4sf __attribute__((__vector_size__(16)));

float __builtin_ia32_vec_ext_v4sf(__gcc_v4sf vec, int offset)
{
  return *((float *)&vec + offset);
}

/* FUNCTION: __builtin_ia32_psubsw128 */

#ifndef LIBRARY_CHECK
typedef short __gcc_v8hi __attribute__((__vector_size__(16)));
#else
__gcc_v8hi __CPROVER_saturating_minus(__gcc_v8hi, __gcc_v8hi);
#endif

__gcc_v8hi __builtin_ia32_psubsw128(__gcc_v8hi a, __gcc_v8hi b)
{
  return __CPROVER_saturating_minus(a, b);
}

/* FUNCTION: __builtin_ia32_psubusw128 */

#ifndef LIBRARY_CHECK
typedef short __gcc_v8hi __attribute__((__vector_size__(16)));
#else
typedef unsigned short v8hi_u __attribute__((__vector_size__(16)));
__gcc_v8hi __CPROVER_saturating_minus_v8hi_u(v8hi_u, v8hi_u);
#  define __CPROVER_saturating_minus __CPROVER_saturating_minus_v8hi_u
#endif

__gcc_v8hi __builtin_ia32_psubusw128(__gcc_v8hi a, __gcc_v8hi b)
{
  typedef unsigned short v8hi_u __attribute__((__vector_size__(16)));
  return (__gcc_v8hi)__CPROVER_saturating_minus((v8hi_u)a, (v8hi_u)b);
}

/* FUNCTION: __builtin_ia32_paddsw */

#ifndef LIBRARY_CHECK
typedef short __gcc_v4hi __attribute__((__vector_size__(8)));
#else
__gcc_v4hi __CPROVER_saturating_plus(__gcc_v4hi, __gcc_v4hi);
#endif

__gcc_v4hi __builtin_ia32_paddsw(__gcc_v4hi a, __gcc_v4hi b)
{
  return __CPROVER_saturating_plus(a, b);
}

/* FUNCTION: __builtin_ia32_psubsw */

#ifndef LIBRARY_CHECK
typedef short __gcc_v4hi __attribute__((__vector_size__(8)));
#else
__gcc_v4hi __CPROVER_saturating_minus_v4hi(__gcc_v4hi, __gcc_v4hi);
#  undef __CPROVER_saturating_minus
#  define __CPROVER_saturating_minus __CPROVER_saturating_minus_v4hi
#endif

__gcc_v4hi __builtin_ia32_psubsw(__gcc_v4hi a, __gcc_v4hi b)
{
  return __CPROVER_saturating_minus(a, b);
}

#ifdef LIBRARY_CHECK
#  undef __CPROVER_saturating_minus
#endif

/* FUNCTION: __builtin_ia32_vec_init_v4hi */

#ifndef LIBRARY_CHECK
typedef short __gcc_v4hi __attribute__((__vector_size__(8)));
#endif

__gcc_v4hi __builtin_ia32_vec_init_v4hi(short e0, short e1, short e2, short e3)
{
  return (__gcc_v4hi){e0, e1, e2, e3};
}
