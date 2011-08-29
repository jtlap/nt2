/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#include <boost/simd/sdk/config/details/cpuid.hpp>
#include <boost/simd/sdk/config/os.hpp>
#include <string>

#if defined(BOOST_SIMD_OS_MAC_OS)
#include <sys/sysctl.h>
#include <sys/types.h>
#elif defined(BOOST_SIMD_OS_LINUX)
#include <unistd.h>
#include <sys/syscall.h>
#include <linux/sysctl.h>
#endif

namespace boost { namespace simd { namespace config{ namespace details {

  bool has_bit_set(int value, int bit)
  {
    return (value & (1<<bit)) != 0;
  }

  bool str_match(const int abcd[4], const char* vendor)
  {
    return (abcd[1] == ((int*)(vendor))[0] && abcd[2] == ((int*)(vendor))[2] && abcd[3] == ((int*)(vendor))[1]);
  }

#ifdef BOOST_SIMD_COMPILER_GNU_C

  void __cpuid( int CPUInfo[4],int InfoType)
  {
#if !defined(BOOST_SIMD_ARCH_POWERPC)
    __asm__ __volatile__
    (
      "cpuid":\
      "=a" (CPUInfo[eax]), "=b" (CPUInfo[ebx])
    , "=c" (CPUInfo[ecx]), "=d" (CPUInfo[edx])
    : "a" (InfoType)
    );
#endif
  }

  void __cpuidex(int CPUInfo[4],int InfoType,int ECXValue)
  {
#if !defined(BOOST_SIMD_ARCH_POWERPC)
    __asm__ __volatile__
    (
      "cpuid":\
      "=a" (CPUInfo[eax]), "=b" (CPUInfo[ebx])
    , "=c" (CPUInfo[ecx]), "=d" (CPUInfo[edx])
    : "a" (InfoType), "c" (ECXValue)
    );
#endif
  }

#elif defined(BOOST_SIMD_COMPILER_MSVC)
#include <intrin.h>
#endif

} } } }
