//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/sdk/config/details/cpuid.hpp>
#include <boost/simd/sdk/config/os.hpp>

#if defined(BOOST_SIMD_COMPILER_MSVC)
#include <intrin.h>
#endif

namespace boost { namespace simd { namespace config{ namespace details {

  bool has_bit_set(int value, int bit)
  {
    return (value & (1<<bit)) != 0;
  }

  void cpuid(int CPUInfo[4],int InfoType)
  {
#if defined(BOOST_SIMD_ARCH_X86)

#if defined(BOOST_SIMD_COMPILER_GCC)
    enum { eax,ebx,ecx,edx };
    
#ifndef __PIC__
    __asm__ __volatile__
    (
      "cpuid"
    : "=a" (CPUInfo[eax]), "=b" (CPUInfo[ebx])
    , "=c" (CPUInfo[ecx]), "=d" (CPUInfo[edx])
    : "a" (InfoType)
    : "cc"
    );
#else
    __asm__ __volatile__
    (
      "pushl %%ebx      \n\t" /* save %ebx */
      "cpuid            \n\t"
      "movl %%ebx, %1   \n\t" /* save what cpuid just put in %ebx */
      "popl %%ebx       \n\t" /* restore the old %ebx */
    : "=a"(CPUInfo[eax]), "=r"(CPUInfo[ebx])
    , "=c"(CPUInfo[ecx]), "=d"(CPUInfo[edx])
    : "a"(InfoType)
    : "cc"
    );
#endif
    
#elif defined(BOOST_SIMD_COMPILER_MSVC)
    __cpuid(CPUInfo,InfoType);
#endif

#endif
  }

} } } }


