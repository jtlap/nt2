//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_CONFIG_DETAILS_CPUID_HPP_INCLUDED
#define BOOST_SIMD_SDK_CONFIG_DETAILS_CPUID_HPP_INCLUDED

/*!
 *\file cpuid.hpp
 *\brief cpuid function to get x86 processor infos
*/

#include <boost/simd/sdk/config/compiler.hpp>
#include <boost/simd/sdk/config/arch.hpp>

#define INTEL "GenuineIntel"
#define AMD   "AuthenticAMD"

namespace boost{ namespace simd{ namespace config{ namespace details{
  
  bool has_bit_set(int value, int bit);

////////////////////////////////////////////////////////////////////////////////
// Case of x86 processor. 
////////////////////////////////////////////////////////////////////////////////

  bool str_match(const int abcd[4], const char* vendor);

} } } }

#if defined(BOOST_SIMD_COMPILER_GNU_C)

  enum { eax,ebx,ecx,edx };

  void __cpuid( int CPUInfo[4],int InfoType);
  void __cpuidex(int CPUInfo[4],int InfoType,int ECXValue);

#elif defined(BOOST_SIMD_COMPILER_MSVC)
#include <intrin.h>
#endif

#endif
