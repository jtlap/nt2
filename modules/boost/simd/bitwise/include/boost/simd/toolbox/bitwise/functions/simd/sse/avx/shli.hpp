//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_BITWISE_FUNCTIONS_SIMD_SSE_AVX_SHLI_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_BITWISE_FUNCTIONS_SIMD_SSE_AVX_SHLI_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_AVX_SUPPORT
#include <boost/simd/toolbox/bitwise/functions/shli.hpp>
#include <boost/dispatch/meta/as_integer.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::shli_, boost::simd::tag::avx_
                            , (A0)(A1)
                            , ((simd_<arithmetic_<A0>,boost::simd::tag::avx_>))
                              (scalar_< integer_<A1> >)
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      typedef typename meta::scalar_of<A0>::type                  sctype;
      typedef typename dispatch::meta::as_integer<sctype>::type   sitype;
      typedef simd::native<sitype, boost::simd::tag::sse_ >      isvtype;
      typedef typename dispatch::meta::as_integer<A0>::type        itype;

      isvtype a00 = _mm256_extractf128_si256(simd::bitwise_cast<itype>(a0), 0);
      isvtype a01 = _mm256_extractf128_si256(simd::bitwise_cast<itype>(a0), 1);
      itype that = _mm256_insertf128_si256(that,boost::simd::shli( a00, a1), 0);
      return  simd::bitwise_cast<A0>(_mm256_insertf128_si256(that, boost::simd::shli(a01, a1), 1));
     }
  };
} } }

#endif
#endif
