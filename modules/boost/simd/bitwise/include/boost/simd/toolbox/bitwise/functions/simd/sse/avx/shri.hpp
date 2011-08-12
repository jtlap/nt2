//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_BITWISE_FUNCTIONS_SIMD_SSE_AVX_SHRI_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_BITWISE_FUNCTIONS_SIMD_SSE_AVX_SHRI_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_AVX_SUPPORT

#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/dispatch/meta/strip.hpp>

#include <boost/simd/include/functions/details/simd/sse/sse4_1/shri.hpp>


/////////////////////////////////////////////////////////////////////////////
// Implementation when type  is arithmetic_
/////////////////////////////////////////////////////////////////////////////
BOOST_SIMD_REGISTER_DISPATCH(boost::simd::tag::shri_, boost::simd::tag::avx_,
                       (A0),
                       ((simd_<arithmetic_<A0>,boost::simd::tag::avx_>))
                       ((simd_<arithmetic_<A0>,boost::simd::tag::avx_>))
                      );

namespace boost { namespace simd { namespace ext
{
  template<class Dummy>
  struct call<boost::simd::tag::shri_(tag::simd_<tag::arithmetic_, tag::avx_),
                         boost::simd::tag::simd_<tag::arithmetic_, tag::avx_)),
              boost::simd::boost::simd::tag::avx_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0,A1)> : meta::strip<A0>{};//

    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      typedef typename meta::scalar_of<A0>::type sctype;
      typedef typename dispatch::meta::as_integer<sctype>::type sitype;
      typedef typename simd::native<sitype, boost::simd::tag::sse_ >  isvtype;
      typedef typename dispatch::meta::as_integer<A0>::type  itype;

      isvtype a00 = { _mm256_extractf128_si256(simd::native_cast<itype>(a0), 0)};
      isvtype a01 = { _mm256_extractf128_si256(simd::native_cast<itype>(a0), 1)};
      itype that = { _mm256_insertf128_si256(that,boost::simd::shri( a00, a1), 0)};
      return  simd::native_cast<A0>(_mm256_insertf128_si256(that, boost::simd::shri(a01, a1), 1));

     }

  };
} } }

#endif
#endif
