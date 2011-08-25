//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_REDUCTION_FUNCTIONS_SIMD_SSE_SSE2_BITWISE_ALL_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_REDUCTION_FUNCTIONS_SIMD_SSE_SSE2_BITWISE_ALL_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_SSE2_SUPPORT
#include <boost/dispatch/meta/as_real.hpp>
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::bitwise_all_, boost::simd::tag::sse2_,
				    (A0),
				    ((simd_<type8_<A0>,boost::simd::tag::sse_>))
				    )
  {
    typedef bool result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(1)
      {
	return _mm_movemask_epi8(a0) == 0xFFFF;
      }
  };
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::bitwise_all_, boost::simd::tag::sse2_,
				    (A0),
				    ((simd_<type16_<A0>,boost::simd::tag::sse_>))
				    )
  {
    typedef bool result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(1)
      {
	return _mm_movemask_epi8(a0) == 0xFFFF;
      }
  };
  
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::bitwise_all_, boost::simd::tag::sse2_,
				    (A0),
				    ((simd_<type64_<A0>,boost::simd::tag::sse_>))
				    )
  {
    typedef bool result_type;
    BOOST_SIMD_FUNCTOR_CALL(1){
      typedef typename dispatch::meta::as_real<A0> ::type fA0; 
      return _mm_movemask_pd(bitwise_cast<fA0>(a0)) == 0x3;
    }
  };
  
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::bitwise_all_, boost::simd::tag::sse2_,
				    (A0),
				    ((simd_<type32_<A0>,boost::simd::tag::sse_>))
				    )
  {
    typedef bool result_type;
    BOOST_SIMD_FUNCTOR_CALL(1){
      typedef typename dispatch::meta::as_real<A0> ::type fA0; 
      return _mm_movemask_ps(bitwise_cast<fA0>(a0)) == 0xF;
    }
  };
} } }  
#endif
#endif
