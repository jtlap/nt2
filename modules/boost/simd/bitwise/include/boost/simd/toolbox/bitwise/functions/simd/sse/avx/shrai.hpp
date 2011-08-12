//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_BITWISE_FUNCTIONS_SIMD_SSE_AVX_SHRAI_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_BITWISE_FUNCTIONS_SIMD_SSE_AVX_SHRAI_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_AVX_SUPPORT

#include <boost/dispatch/meta/strip.hpp>

#include <boost/simd/include/functions/details/simd/sse/sse4_1/shrai.hpp>


/////////////////////////////////////////////////////////////////////////////
// Implementation when type  is arithmetic_
/////////////////////////////////////////////////////////////////////////////
BOOST_SIMD_REGISTER_DISPATCH(boost::simd::tag::shrai_, boost::simd::tag::avx_,
                        (A0),
                        ((simd_<arithmetic_<A0>,boost::simd::tag::avx_>))
                        ((simd_<arithmetic_<A0>,boost::simd::tag::avx_>))
                       );

namespace boost { namespace simd { namespace ext
{
  template<class Dummy>
  struct call<boost::simd::tag::shrai_(tag::simd_<tag::arithmetic_, tag::avx_),
                          boost::simd::tag::simd_<tag::arithmetic_, tag::avx_)),
              boost::simd::boost::simd::tag::avx_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0, class A1>
    struct result<This(A0,A1)> : meta::strip<A0>{};//

    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      typedef typename meta::scalar_of<A0>::type sctype;
      typedef typename simd::native<sctype, boost::simd::tag::sse_ >  svtype;
      svtype a00 = { _mm256_extractf128_si256(a0, 0)};
      svtype a01 = { _mm256_extractf128_si256(a0, 1)};
      A0 that = { _mm256_insertf128_si256(that,boost::simd::shrai( a00, a1), 0)};
      that =  _mm256_insertf128_si256(that, boost::simd::shrai(a01, a1), 1);
      return that;
     }

  };
} } }

#endif
#endif
