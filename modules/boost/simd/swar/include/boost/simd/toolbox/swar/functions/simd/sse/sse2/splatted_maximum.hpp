//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_SWAR_FUNCTIONS_SIMD_SSE_SSE2_SPLATTED_MAXIMUM_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_SWAR_FUNCTIONS_SIMD_SSE_SSE2_SPLATTED_MAXIMUM_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_SSE2_SUPPORT
#include <boost/simd/include/functions/simd/max.hpp>
#include <boost/simd/include/functions/simd/maximum.hpp>
#include <boost/dispatch/meta/as_floating.hpp>

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is int16_
/////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::splatted_maximum_, boost::simd::tag::sse2_
                            , (A0)
                            , ((simd_<ints16_<A0>,boost::simd::tag::sse_>))
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      typedef simd::native<float, boost::simd::tag::sse_> ftype;
      A0 max1 = {_mm_shufflehi_epi16(a0  , _MM_SHUFFLE(1, 0, 3, 2))};
         max1 = _mm_shufflelo_epi16(max1, _MM_SHUFFLE(1, 0, 3, 2));
         max1 = max(a0, max1);
      A0 max2 = {_mm_shuffle_epi32  (max1, _MM_SHUFFLE(1, 0, 3, 2))};
         max2 = _mm_shufflelo_epi16(max2, _MM_SHUFFLE(1, 0, 3, 2));
         max2 = max(max1, max2);
      A0 max3 = {_mm_shuffle_epi32(max2, _MM_SHUFFLE(3, 2, 1, 0))};
      A0 max4 = {_mm_shufflelo_epi16(max3, _MM_SHUFFLE(0, 1, 2, 3))};
      ftype max5 = {simd::bitwise_cast<ftype>(boost::simd::max(max3, max4))};
      A0 that = {simd::bitwise_cast<A0>(_mm_unpacklo_ps(max5, max5))};
      return that;
    }
  };
  
  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is double
  /////////////////////////////////////////////////////////////////////////////
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::splatted_maximum_, boost::simd::tag::sse2_,
			     (A0),
			     ((simd_<double_<A0>,boost::simd::tag::sse_>))
			     )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
      {
	A0 that = {_mm_max_sd(a0, _mm_unpackhi_pd(a0,a0))};
	return simd::bitwise_cast<A0>(_mm_unpacklo_pd(that, that));
      }
  };
  
  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is int64_
  /////////////////////////////////////////////////////////////////////////////
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::splatted_maximum_, boost::simd::tag::sse2_
			      , (A0)
			      , ((simd_<ints64_<A0>,boost::simd::tag::sse_>))
			      )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
      {
	//       typedef typename dispatch::meta::as_floating<A0>::type ftype;
	//       A0 a00  =  simd::bitwise_cast<A0>(_mm_shuffle_pd(simd::bitwise_cast<ftype>(a0),
	//                                           simd::bitwise_cast<ftype>(a0),0x01));
	//       return  max(a0, a00);
	return boost::simd::splat<A0>(maximum(a0)); 
      }
  };
  
  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is float
  /////////////////////////////////////////////////////////////////////////////
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::splatted_maximum_, boost::simd::tag::sse2_,
			     (A0),
			     ((simd_<single_<A0>,boost::simd::tag::sse_>))
			     )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
      {
	A0 tmp = {_mm_shuffle_ps(a0, a0, _MM_SHUFFLE(1, 0, 3, 2))}; 
	A0 max1 = boost::simd::max(a0,tmp);
	A0 tmp1 ={_mm_shuffle_ps(max1, max1, _MM_SHUFFLE(2, 3, 0, 1))}; 
	A0 that = boost::simd::max(max1,tmp1);
	return that;
      }
  };
  
  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is int8_
  /////////////////////////////////////////////////////////////////////////////
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::splatted_maximum_, boost::simd::tag::sse2_,
			     (A0),
			     ((simd_<ints8_<A0>,boost::simd::tag::sse_>))
			     )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
      {
	return boost::simd::splat<A0>(maximum(a0));
      }
  };
  
  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is int32_
  /////////////////////////////////////////////////////////////////////////////
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::splatted_maximum_, boost::simd::tag::sse2_,
                                   (A0),
                                   ((simd_<ints32_<A0>,boost::simd::tag::sse_>))
                                  )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
      {
	A0 max1 = {max(a0,simd::bitwise_cast<A0>(_mm_shuffle_epi32(a0, _MM_SHUFFLE(1, 0, 3, 2))))};
	A0 that = {max(max1, simd::bitwise_cast<A0>(_mm_shuffle_epi32(max1, _MM_SHUFFLE(2, 3, 0, 1))))};
	return that;
      }
  }; 
} } }

#endif
#endif
