//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_SWAR_FUNCTIONS_SIMD_SSE_AVX_REPEAT_UPPER_HALF_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_SWAR_FUNCTIONS_SIMD_SSE_AVX_REPEAT_UPPER_HALF_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_AVX_SUPPORT

#include <boost/simd/toolbox/swar/functions/repeat_upper_half.hpp>
#include <boost/simd/include/functions/bitwise_cast.hpp>
#include <boost/simd/include/functions/interleave_first.hpp>
#include <boost/dispatch/meta/as_floating.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::repeat_upper_half_
                                   , boost::simd::tag::avx_
                                   , (A0)
                                   , ((simd_<single_<A0>,boost::simd::tag::avx_>))
                                   )
  {
    typedef A0 result_type;

    result_type operator()(__m256 const a0) const
    {
      return _mm256_permute2f128_ps(a0,a0, 17);
    }
  };
  
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::repeat_upper_half_
                                   , boost::simd::tag::avx_
                                   , (A0)
                                   , ((simd_ < integer_<A0>,boost::simd::tag::avx_>))
                                   )
  {
    typedef A0 result_type;

    result_type operator()(__m256i const a0) const
    {
      return _mm256_permute2f128_si256(a0, a0, 17);
    }
  };
  
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::repeat_upper_half_
                                   , boost::simd::tag::avx_
                                   , (A0)
                                   , ((simd_<double_<A0>,boost::simd::tag::avx_>))
                                   )
  {
    typedef A0 result_type;

    result_type operator()(__m256d const a0) const
    {
      return  _mm256_permute2f128_pd(a0, a0, 17);
    }
  };
  
} } }

#endif
#endif
