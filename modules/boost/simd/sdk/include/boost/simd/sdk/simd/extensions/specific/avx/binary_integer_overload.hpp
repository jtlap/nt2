//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_SDK_SIMD_EXTENSIONS_SPECIFIC_AVX_BINARY_INTEGER_OVERLOAD_HPP_INCLUDED
#define BOOST_SIMD_SDK_SIMD_EXTENSIONS_SPECIFIC_AVX_BINARY_INTEGER_OVERLOAD_HPP_INCLUDED

#include <boost/simd/sdk/meta/scalar_of.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(Tag, boost::simd::tag::avx_,
                      (Tag)(A0),
                      ((simd_<arithmetic_<A0>,boost::simd::tag::avx_>))
                      ((simd_<arithmetic_<A0>,boost::simd::tag::avx_>))
                     )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      dispatch::functor<Tag> callee;
      native<typename meta::scalar_of<A0>::type,tag::sse_> a00,a01,a10,a11;
      native<typename meta::scalar_of<A0>::type,tag::sse_> r0,r1;
      
      // Extract m128i from the first m256i
      a00 = _mm256_extractf128_si256(a0,0);
      a01 = _mm256_extractf128_si256(a0,1);
      
      // Extract m128i from the second m256i
      a10 = _mm256_extractf128_si256(a1,0);
      a11 = _mm256_extractf128_si256(a1,1);
      
      // Perform computation
      r0 = callee(a00,a10);
      r1 = callee(a01,a11);
      
      // Merge back to m256
      result_type that;
      that = _mm256_insertf128_si256(that,r0(),0);
      that = _mm256_insertf128_si256(that,r1(),1);
      
      return that; 
    }
  };
} } }

#endif
