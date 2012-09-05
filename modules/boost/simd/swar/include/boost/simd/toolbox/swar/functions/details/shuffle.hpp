//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_SWAR_FUNCTIONS_DETAILS_SHUFFLE_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_SWAR_FUNCTIONS_DETAILS_SHUFFLE_HPP_INCLUDED

namespace boost { namespace simd { namespace details
{
#ifdef BOOST_SIMD_HAS_SSE2_SUPPORT

  template< unsigned int lower_i0, unsigned int lower_i1
          , unsigned int upper_i0, unsigned int upper_i1>
  BOOST_FORCEINLINE
  __m128 shuffle(__m128 const lower, __m128 const upper)
  {
    return _mm_shuffle_ps( lower, upper
                         , _MM_SHUFFLE(upper_i1, upper_i0, lower_i1, lower_i0)
                         );
  }

  template<unsigned int lower_i0, unsigned int upper_i0>
  BOOST_FORCEINLINE
  __m128d shuffle(__m128d const lower, __m128d const upper)
  {
    return _mm_shuffle_pd(lower, upper, _MM_SHUFFLE2(upper_i0, lower_i0));
  }

  template< unsigned int lower_i0, unsigned int lower_i1
          , unsigned int upper_i0, unsigned int upper_i1>
  BOOST_FORCEINLINE
  __m128 shuffle(__m128 const input)
  {
    return shuffle<lower_i0, lower_i1, upper_i0, upper_i1>(input, input);
  }

  template<unsigned int lower_i0, unsigned int upper_i0>
  BOOST_FORCEINLINE
  __m128d shuffle(__m128d const input)
  {
    return shuffle<lower_i0, upper_i0>(input, input);
  }

#endif

#ifdef BOOST_SIMD_HAS_AVX_SUPPORT
template< unsigned int lower_i0, unsigned int lower_i1
        , unsigned int upper_i0, unsigned int upper_i1>
BOOST_FORCEINLINE
__m256 shuffle(__m256 const lower, __m256 const upper)
{
  return _mm256_shuffle_ps( lower, upper
                          , _MM_SHUFFLE(upper_i1, upper_i0, lower_i1, lower_i0)
                          );
}

template< unsigned int lower_i0, unsigned int lower_i1
        , unsigned int upper_i0, unsigned int upper_i1>
BOOST_FORCEINLINE
__m256d shuffle(__m256d const lower, __m256d const upper)
{
  return _mm256_shuffle_pd( lower, upper
                          , _MM_SHUFFLE(upper_i1, upper_i0, lower_i1, lower_i0)
                          );
}

template< unsigned int lower_i0, unsigned int lower_i1
        , unsigned int upper_i0, unsigned int upper_i1>
BOOST_FORCEINLINE
__m256d shuffle(__m256d const input)
{
  return shuffle<lower_i0, lower_i1, upper_i0, upper_i1>(input, input);
}

template< unsigned int lower_i0, unsigned int lower_i1
        , unsigned int upper_i0, unsigned int upper_i1>
BOOST_FORCEINLINE
__m128 shuffle(__m256d const input)
{
  return shuffle<lower_i0, lower_i1, upper_i0, upper_i1>(input, input);
}
#endif
} } }

#endif