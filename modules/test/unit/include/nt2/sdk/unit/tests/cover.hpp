//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012        MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_UNIT_TESTS_COVER_HPP_INCLUDED
#define NT2_SDK_UNIT_TESTS_COVER_HPP_INCLUDED

// Temporary fix before cover tests disappear

#include <vector>
#include <nt2/sdk/unit/details/prng.hpp>

/// INTERNAL ONLY
#if !defined(NT2_NB_RANDOM_TEST)
#define NT2_NB_RANDOM_TEST 128
#endif

/// INTERNAL ONLY
#define NT2_CREATE_BUF(Name,Type,Size,Min,Max)                                 \
std::vector<Type,boost::simd::memory::allocator<Type> > Name(Size);            \
nt2::roll( Name, Min, Max )                                                    \
/**/

/// INTERNAL ONLY
#define NT2_CREATE_LOGICAL_BUF(Name,Type,Size)                                 \
std::vector<Type,boost::simd::memory::allocator<Type> > Name(Size);            \
do                                                                             \
{                                                                              \
  for(std::size_t i=0;i<Name.size();++i) Name[i] = Type(rand() % 2);           \
}                                                                              \
while(0)                                                                       \
/**/

#endif
