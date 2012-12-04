//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at                x
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_REDUCTION_FUNCTIONS_SIMD_SSE_AVX_COMPARE_EQUAL_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_REDUCTION_FUNCTIONS_SIMD_SSE_AVX_COMPARE_EQUAL_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_AVX_SUPPORT

#include <boost/simd/toolbox/reduction/functions/compare_equal.hpp>
#include <boost/simd/sdk/simd/logical.hpp>
#include <boost/simd/sdk/meta/scalar_of.hpp>
#include <boost/simd/include/constants/false.hpp>
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::compare_equal_, boost::simd::tag::avx_
                            , (A0)
                            , ((simd_<double_<A0>,boost::simd::tag::avx_>))
                              ((simd_<double_<A0>,boost::simd::tag::avx_>))
                            )
  {
    typedef typename meta::scalar_of<A0>::type  sA0;
    typedef typename meta::as_logical<sA0>::type result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2) { return  result_type(_mm256_movemask_pd(eq(a0,a1)) == 0X0F); }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::compare_equal_, boost::simd::tag::avx_
                            , (A0)
                            , ((simd_<single_<A0>,boost::simd::tag::avx_>))
                              ((simd_<single_<A0>,boost::simd::tag::avx_>))
                            )
  {
    typedef typename meta::scalar_of<A0>::type  sA0;
    typedef typename meta::as_logical<sA0>::type result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2) { return  result_type(_mm256_movemask_ps(eq(a0,a1)) == 0X0FF); }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::compare_equal_, boost::simd::tag::avx_
                            , (A0)
                            , ((simd_<integer_<A0>,boost::simd::tag::avx_>))
                              ((simd_<integer_<A0>,boost::simd::tag::avx_>))
                            )
  {
    typedef typename meta::scalar_of<A0>::type  sA0;
    typedef typename meta::as_logical<sA0>::type result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      typedef typename dispatch::meta::scalar_of<A0>::type      stype;
      typedef native < stype,  boost::simd::tag::sse_>          htype;
      htype a00 = _mm256_extractf128_si256(a0, 0);
      htype a10 = _mm256_extractf128_si256(a1, 0);
      if (!compare_equal(a00, a10))
      {
        return  False<result_type>();
      }
      else
      {
        htype a01 = _mm256_extractf128_si256(a0, 1);
        htype a11 = _mm256_extractf128_si256(a1, 1);
        return  compare_equal(a01, a11);
      }
    }
  };
} } }

#endif
#endif
