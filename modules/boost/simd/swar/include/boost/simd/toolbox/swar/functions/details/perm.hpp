//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_SWAR_FUNCTIONS_DETAILS_PERM_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_SWAR_FUNCTIONS_DETAILS_PERM_HPP_INCLUDED
#include <iostream>

#define BOOST_SIMD_MM_PERM2(i0, i1) (i0+(i1 << 4))

namespace boost { namespace simd { namespace details
{

#ifdef BOOST_SIMD_HAS_AVX_SUPPORT
template< unsigned int i0, unsigned int i1>
BOOST_FORCEINLINE
__m256 perm2(__m256 const lower, __m256 const upper)
{
  return _mm256_permute2f128_ps( lower, upper
                          , BOOST_SIMD_MM_PERM2(i0, i1)
                          );
}
template< unsigned int i0, unsigned int i1>
BOOST_FORCEINLINE
__m256d perm2(__m256d const lower, __m256d const upper)
{
  return _mm256_permute2f128_pd( lower, upper
                          , BOOST_SIMD_MM_PERM2(i0, i1)
                          );
}
template< unsigned int i0, unsigned int i1>
BOOST_FORCEINLINE
__m256i perm2(__m256i const lower, __m256i const upper)
{
  return _mm256_permute2f128_si256( lower, upper
                          , BOOST_SIMD_MM_PERM2(i0, i1)
                          );
}

#undef BOOST_SIMD_MM_PERM2
#endif
} } }

#endif
