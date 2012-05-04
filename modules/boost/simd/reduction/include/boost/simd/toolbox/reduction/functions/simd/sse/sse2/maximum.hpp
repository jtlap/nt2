//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_REDUCTION_FUNCTIONS_SIMD_SSE_SSE2_MAXIMUM_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_REDUCTION_FUNCTIONS_SIMD_SSE_SSE2_MAXIMUM_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_SSE2_SUPPORT
#include <boost/simd/toolbox/reduction/functions/maximum.hpp>
#include <boost/simd/sdk/meta/templatize.hpp>
#include <boost/simd/include/functions/simd/max.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::maximum_, boost::simd::tag::sse2_, (A0)
                            , ((simd_<ints16_<A0>,boost::simd::tag::sse_>))
                            )
  {
    typedef typename meta::scalar_of<A0>::type result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      A0 max1 = {_mm_shufflehi_epi16(a0  , _MM_SHUFFLE(1, 0, 3, 2))};
         max1 = _mm_shufflelo_epi16(max1, _MM_SHUFFLE(1, 0, 3, 2));
         max1 = max(a0, max1);
      A0 max2 = {_mm_shuffle_epi32  (max1, _MM_SHUFFLE(1, 0, 3, 2))};
         max2 = _mm_shufflelo_epi16(max2, _MM_SHUFFLE(1, 0, 3, 2));
         max2 = max(max1, max2);
      A0 max3 = {_mm_shuffle_epi32(max2, _MM_SHUFFLE(3, 2, 1, 0))};
      A0 max4 = {_mm_shufflelo_epi16(max3, _MM_SHUFFLE(0, 1, 2, 3))};
      A0 that = boost::simd::max(max3, max4);
      return that[0];
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::maximum_, boost::simd::tag::sse2_, (A0)
                            , ((simd_<double_<A0>,boost::simd::tag::sse_>))
                            )
  {
    typedef typename meta::scalar_of<A0>::type result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      A0 that = {_mm_max_sd(a0, _mm_unpackhi_pd(a0,a0))};
      return that[0];
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::maximum_, boost::simd::tag::sse2_, (A0)
                            , ((simd_<ints64_<A0>,boost::simd::tag::sse_>))
                            )
  {
    typedef typename meta::scalar_of<A0>::type result_type;
    BOOST_SIMD_FUNCTOR_CALL(1) { return boost::simd::max(a0[0], a0[1]); }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::maximum_, boost::simd::tag::sse2_, (A0)
                            , ((simd_<single_<A0>,boost::simd::tag::sse_>))
                            )
  {
    typedef typename meta::scalar_of<A0>::type result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      A0 max  = {_mm_max_ps(a0, _mm_movehl_ps(a0,a0))};
      A0 that = {_mm_max_ss(max, _mm_shuffle_ps(max,max,0x01))};
      return that[0];
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::maximum_, boost::simd::tag::sse2_, (A0)
                            , ((simd_<ints8_<A0>,boost::simd::tag::sse_>))
                            )
  {
    typedef typename meta::scalar_of<A0>::type result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      typedef simd::native<typename boost::simd::meta::double__<A0>::type,boost::simd::tag::sse_> rtype;
      rtype v0 = simd::bitwise_cast<rtype>(a0);
      A0 pack = simd::bitwise_cast<A0>(_mm_unpackhi_pd(v0,v0));
      A0 max1 = boost::simd::max(a0,pack);
      A0 max2 = {max(max1, simd::bitwise_cast<A0>(_mm_shufflelo_epi16(max1, _MM_SHUFFLE(0, 1, 2, 3))))};
         max2 = max(max2, simd::bitwise_cast<A0>(_mm_shuffle_epi32  (max2, _MM_SHUFFLE(2, 3, 0, 1))));
      return boost::simd::max(max2[0],max2[1]);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::maximum_, boost::simd::tag::sse2_, (A0)
                            , ((simd_<ints32_<A0>,boost::simd::tag::sse_>))
                            )
  {
    typedef typename meta::scalar_of<A0>::type result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      A0 max1 = {max(a0,simd::bitwise_cast<A0>(_mm_shuffle_epi32(a0, _MM_SHUFFLE(1, 0, 3, 2))))};
      A0 that = {max(max1, simd::bitwise_cast<A0>(_mm_shuffle_epi32(max1, _MM_SHUFFLE(2, 3, 0, 1))))};
      return that[0];
    }
  };
} } }

#endif
#endif
