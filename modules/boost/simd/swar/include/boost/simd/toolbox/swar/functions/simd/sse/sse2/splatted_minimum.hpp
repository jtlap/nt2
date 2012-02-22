//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_SWAR_FUNCTIONS_SIMD_SSE_SSE2_SPLATTED_MINIMUM_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_SWAR_FUNCTIONS_SIMD_SSE_SSE2_SPLATTED_MINIMUM_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_SSE2_SUPPORT
#include <boost/dispatch/meta/as_floating.hpp>
#include <boost/simd/include/functions/min.hpp>
#include <boost/simd/include/functions/minimum.hpp>

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is int16_
/////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::splatted_minimum_, boost::simd::tag::sse2_
                                     , (A0)
                                     , ((simd_<ints16_<A0>,boost::simd::tag::sse_>))
                                     )
  {

    typedef A0 result_type;

    BOOST_SIMD_FUNCTOR_CALL(1)
      {
        typedef simd::native<float, boost::simd::tag::sse_> ftype;
        A0 min1 = {_mm_shufflehi_epi16(a0  , _MM_SHUFFLE(1, 0, 3, 2))};
        min1 = _mm_shufflelo_epi16(min1, _MM_SHUFFLE(1, 0, 3, 2));
        min1 = min(a0, min1);
        A0 min2 = {_mm_shuffle_epi32  (min1, _MM_SHUFFLE(1, 0, 3, 2))};
        min2 = _mm_shufflelo_epi16(min2, _MM_SHUFFLE(1, 0, 3, 2));
        min2 = min(min1, min2);
        A0 min3 = {_mm_shuffle_epi32(min2, _MM_SHUFFLE(3, 2, 1, 0))};
        A0 min4 = {_mm_shufflelo_epi16(min3, _MM_SHUFFLE(0, 1, 2, 3))};
        ftype min5 = {simd::bitwise_cast<ftype>(boost::simd::min(min3, min4))};
        A0 that = {simd::bitwise_cast<A0>(_mm_unpacklo_ps(min5, min5))};

        return that;
      }
  };
  
  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is double
  /////////////////////////////////////////////////////////////////////////////
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::splatted_minimum_, boost::simd::tag::sse2_
                                     , (A0)
                                     , ((simd_<double_<A0>,boost::simd::tag::sse_>))
                                     )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
      {
        A0 that = {_mm_min_sd(a0, _mm_unpackhi_pd(a0,a0))};
        return simd::bitwise_cast<A0>(_mm_unpacklo_pd(that, that));
      }
  };
  
  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is int64_
  /////////////////////////////////////////////////////////////////////////////
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::splatted_minimum_, boost::simd::tag::sse2_,
                                    (A0),
                                    ((simd_<ints64_<A0>,boost::simd::tag::sse_>))
                                    )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
      {
        typedef typename dispatch::meta::as_floating<A0>::type ftype;
        A0 a00  =  simd::bitwise_cast<A0>(_mm_shuffle_pd(simd::bitwise_cast<ftype>(a0),
                                                         simd::bitwise_cast<ftype>(a0),0x01));
        return  min(a0, a00);
      }
  };
  
  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is float
  /////////////////////////////////////////////////////////////////////////////
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::splatted_minimum_, boost::simd::tag::sse2_,
                                    (A0),
                                    ((simd_<single_<A0>,boost::simd::tag::sse_>))
                                    )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
      {
        return boost::simd::splat<A0>(minimum(a0)); 
        //       A0 min1 = {min(a0,simd::bitwise_cast<A0>(_mm_shuffle_ps(a0, a0, _MM_SHUFFLE(1, 0, 3, 2))))};
        //       A0 that = {min(min1, simd::bitwise_cast<A0>(_mm_shuffle_ps(min1, min1, _MM_SHUFFLE(2, 3, 0, 1))))};
        //       return that;
      }
  };
  
  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is int8_
  /////////////////////////////////////////////////////////////////////////////
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::splatted_minimum_, boost::simd::tag::sse2_,
                                    (A0),
                                    ((simd_<ints8_<A0>,boost::simd::tag::sse_>))
                                    )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
      {
        return boost::simd::splat<A0>(minimum(a0));
      }
  };
  
  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is int32_
  /////////////////////////////////////////////////////////////////////////////
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::splatted_minimum_, boost::simd::tag::sse2_,
                                    (A0),
                                    ((simd_<ints32_<A0>,boost::simd::tag::sse_>))
                                    )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
      {
        A0 min1 = {min(a0,simd::bitwise_cast<A0>(_mm_shuffle_epi32(a0, _MM_SHUFFLE(1, 0, 3, 2))))};
        A0 that = {min(min1, simd::bitwise_cast<A0>(_mm_shuffle_epi32(min1, _MM_SHUFFLE(2, 3, 0, 1))))};
        return that;
      }
  };
} } }

#endif
#endif
 
