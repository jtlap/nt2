/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef BOOST_SIMD_SDK_CONFIG_DETAILS_CPUID_HPP_INCLUDED
#define BOOST_SIMD_SDK_CONFIG_DETAILS_CPUID_HPP_INCLUDED

#include <boost/simd/sdk/config/compiler.hpp>
#include <boost/simd/sdk/config/arch.hpp>
#include <boost/simd/sdk/config/details/masks.hpp>

namespace boost{ namespace simd{ namespace config{ namespace details{
  
  bool has_bit_set(int value, int bit);

#if !defined(BOOST_SIMD_ARCH_POWERPC)

#define INTEL "GenuineIntel"
#define AMD   "AuthenticAMD"

#if defined(BOOST_SIMD_COMPILER_GNU_C)

  void __cpuid( int CPUInfo[4],int InfoType);
  void __cpuidex(int CPUInfo[4],int InfoType,int ECXValue);

  enum { eax,ebx,ecx,edx };

#elif defined(BOOST_SIMD_COMPILER_MSVC)
#include <intrin.h>
#endif
  
#elif defined(BOOST_SIMD_ARCH_POWERPC) 

  //TODO : Altivec runtime detection

#endif

  template<class Tag, class Vendor>
  bool is_vendor(const cpuid_mask<Tag, Vendor>& m, const char* vendor)
  {
    int abcd[4];
    __cpuid(abcd, m.function);
    return (abcd[1] == ((int*)(vendor))[0] && abcd[2] == ((int*)(vendor))[2] && abcd[3] == ((int*)(vendor))[1]);
  }

} } } }


#endif
