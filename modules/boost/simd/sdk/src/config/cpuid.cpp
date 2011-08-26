/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#include <boost/simd/sdk/config/details/cpuid.hpp>
#include <string>

namespace boost { namespace simd { namespace config{ namespace details {

  bool has_bit_set(int value, int bit)
  {
    return (value & (1<<bit)) != 0;
  }

#if !defined(BOOST_SIMD_ARCH_POWERPC)

#ifdef BOOST_SIMD_COMPILER_GNU_C

  void __cpuid( int CPUInfo[4],int InfoType)
  {
    __asm__ __volatile__
    (
      "cpuid":\
      "=a" (CPUInfo[eax]), "=b" (CPUInfo[ebx])
    , "=c" (CPUInfo[ecx]), "=d" (CPUInfo[edx])
    : "a" (InfoType)
    );
  }

  void __cpuidex(int CPUInfo[4],int InfoType,int ECXValue)
  {
    __asm__ __volatile__
    (
      "cpuid":\
      "=a" (CPUInfo[eax]), "=b" (CPUInfo[ebx])
    , "=c" (CPUInfo[ecx]), "=d" (CPUInfo[edx])
    : "a" (InfoType), "c" (ECXValue)
    );
  }

#elif defined(BOOST_SIMD_COMPILER_MSVC)
#include <intrin.h>
#endif

#elif defined(BOOST_SIMD_ARCH_POWERPC) 

#include <signal.h>



#endif

  

} } } }
