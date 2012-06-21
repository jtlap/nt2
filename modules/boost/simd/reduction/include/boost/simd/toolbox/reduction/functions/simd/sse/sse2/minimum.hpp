//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_REDUCTION_FUNCTIONS_SIMD_SSE_SSE2_MINIMUM_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_REDUCTION_FUNCTIONS_SIMD_SSE_SSE2_MINIMUM_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_SSE2_SUPPORT
#include <boost/simd/toolbox/reduction/functions/minimum.hpp>
#include <boost/dispatch/meta/strip.hpp>
#include <boost/simd/sdk/meta/make_dependent.hpp>
#include <boost/simd/include/functions/simd/min.hpp>

namespace boost { namespace simd { namespace ext
{
  //============================================================================
  // Implementation when type A0 is int16_
  //============================================================================
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::minimum_
                                    , boost::simd::tag::sse2_
                                    , (A0)
                                    , ((simd_<ints16_<A0>,boost::simd::tag::sse_>))
                                    )
  {
    typedef typename meta::scalar_of<A0 > ::type result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(1)
    {
      A0 min1 = _mm_shufflehi_epi16(a0  , _MM_SHUFFLE(1, 0, 3, 2));
         min1 = _mm_shufflelo_epi16(min1, _MM_SHUFFLE(1, 0, 3, 2));
         min1 = min(a0, min1);
      A0 min2 = _mm_shuffle_epi32  (min1, _MM_SHUFFLE(1, 0, 3, 2));
         min2 = _mm_shufflelo_epi16(min2, _MM_SHUFFLE(1, 0, 3, 2));
         min2 = min(min1, min2);
      A0 min3 = _mm_shuffle_epi32(min2, _MM_SHUFFLE(3, 2, 1, 0));
      A0 min4 = _mm_shufflelo_epi16(min3, _MM_SHUFFLE(0, 1, 2, 3));
      A0 that = boost::simd::min(min3, min4);
      return that[0];
    }
  };

  //============================================================================
  // Implementation when type A0 is double
  //============================================================================
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::minimum_
                                    , boost::simd::tag::sse2_
                                    , (A0)
                                    , ((simd_<double_<A0>,boost::simd::tag::sse_>))
                                    )
  {
    typedef typename meta::scalar_of<A0> ::type result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(1)
    {
      A0 that = _mm_min_sd(a0, _mm_unpackhi_pd(a0,a0));
      return that[0];
    }
  };

  //============================================================================
  // Implementation when type A0 is int64_
  //============================================================================
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::minimum_
                                    , boost::simd::tag::sse2_
                                    , (A0)
                                    , ((simd_<ints64_<A0>,boost::simd::tag::sse_>))
                                    )
  {
    typedef typename meta::scalar_of<A0 > ::type result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(1)
    {
      return boost::simd::min(a0[0], a0[1]);
    }
  };

  //============================================================================
  // Implementation when type A0 is float
  //============================================================================
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::minimum_
                                    , boost::simd::tag::sse2_
                                    ,(A0)
                                    , ((simd_<single_<A0>,boost::simd::tag::sse_>))
                                    )
  {
    typedef typename meta::scalar_of<A0 > ::type result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(1)
    {
      A0 min  = _mm_min_ps(a0, _mm_movehl_ps(a0,a0));
      A0 that = _mm_min_ss(min, _mm_shuffle_ps(min,min,0x01));
      return that[0];
    }
  };

  //============================================================================
  // Implementation when type A0 is int8_
  //============================================================================
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::minimum_
                                    , boost::simd::tag::sse2_
                                    , (A0)
                                    , ((simd_<ints8_<A0>,boost::simd::tag::sse_>))
                                    )
  {
    typedef typename meta::scalar_of<A0>::type              result_type;
    typedef typename meta::make_dependent<double,A0>::type  double_t;
    typedef simd::native<double_t,boost::simd::tag::sse_>   rtype;

    BOOST_SIMD_FUNCTOR_CALL_REPEAT(1)
    {
      rtype v0 = simd::bitwise_cast<rtype>(a0);
      A0 pack = simd::bitwise_cast<A0>(_mm_unpackhi_pd(v0,v0));
      A0 min1 = boost::simd::min(a0,pack);
      A0 min2 = {min(min1, simd::bitwise_cast<A0>(_mm_shufflelo_epi16(min1, _MM_SHUFFLE(0, 1, 2, 3))))};
         min2 = min(min2, simd::bitwise_cast<A0>(_mm_shuffle_epi32  (min2, _MM_SHUFFLE(2, 3, 0, 1))));
    return boost::simd::min(min2[0],min2[1]);
    }
  };

  //============================================================================
  // Implementation when type A0 is int32_
  //============================================================================
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::minimum_
                                    , boost::simd::tag::sse2_
                                    ,(A0)
                                    ,((simd_<ints32_<A0>,boost::simd::tag::sse_>))
                                    )
  {
    typedef typename meta::scalar_of<A0 > ::type result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(1)
    {
      A0 min1 = {min(a0,simd::bitwise_cast<A0>(_mm_shuffle_epi32(a0, _MM_SHUFFLE(1, 0, 3, 2))))};
      A0 that = {min(min1, simd::bitwise_cast<A0>(_mm_shuffle_epi32(min1, _MM_SHUFFLE(2, 3, 0, 1))))};
      return that[0];
    }
  };
} } }

#endif
#endif
