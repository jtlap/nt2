//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_SWAR_FUNCTIONS_SIMD_SSE_AVX_DEINTERLEAVE_SECOND_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_SWAR_FUNCTIONS_SIMD_SSE_AVX_DEINTERLEAVE_SECOND_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_AVX_SUPPORT

#include <boost/simd/include/functions/deinterleave_second.hpp>
#include <boost/simd/toolbox/swar/functions/details/shuffle.hpp>
#include <boost/simd/include/functions/bitwise_select.hpp>
#include <boost/simd/include/functions/make.hpp>
#include <boost/simd/include/constants/zero.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::deinterleave_second_
                                   , boost::simd::tag::avx_
                                   , (A0)
                                   , ((simd_<single_<A0>,boost::simd::tag::avx_>))
                                     ((simd_<single_<A0>,boost::simd::tag::avx_>))
                                   )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A0 const& a1) const
    {
      typedef typename meta::scalar_of<A0>::type                  sctype;
      typedef simd::native<sctype, boost::simd::tag::sse_ >       svtype;

      svtype a00 = _mm256_extractf128_ps(a0, 0);
      svtype a01 = _mm256_extractf128_ps(a0, 1);
      svtype a10 = _mm256_extractf128_ps(a1, 0);
      svtype a11 = _mm256_extractf128_ps(a1, 1);
      result_type that = _mm256_insertf128_ps(that,boost::simd::deinterleave_second(a00, a01), 0);
      return _mm256_insertf128_ps(that,  boost::simd::deinterleave_second(a10, a11), 1);
     }
  };
  
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::deinterleave_second_
                                   , boost::simd::tag::avx_
                                   , (A0)
                                   , ((simd_<double_<A0>,boost::simd::tag::avx_>))
                                     ((simd_<double_<A0>,boost::simd::tag::avx_>))
                                   )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A0 const& a1) const
    {
      typedef typename meta::scalar_of<A0>::type                  sctype;
      typedef simd::native<sctype, boost::simd::tag::sse_ >       svtype;
      typedef simd::native<sctype, boost::simd::tag::avx_ >        vtype;

      svtype a00 = _mm256_extractf128_pd(a0, 0);
      svtype a01 = _mm256_extractf128_pd(a0, 1);
      svtype a10 = _mm256_extractf128_pd(a1, 0);
      svtype a11 = _mm256_extractf128_pd(a1, 1);
      result_type that = _mm256_insertf128_pd(that,boost::simd::deinterleave_second(a00, a01), 0);
      return  _mm256_insertf128_pd(that,  boost::simd::deinterleave_second(a10, a11), 1);
     }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::deinterleave_second_
                                   , boost::simd::tag::avx_
                                   , (A0)
                                   , ((simd_<arithmetic_<A0>,boost::simd::tag::avx_>))
                                     ((simd_<arithmetic_<A0>,boost::simd::tag::avx_>))
                                   )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A0 const& a1) const
    {
      typedef typename meta::scalar_of<A0>::type                  sctype;
      typedef simd::native<sctype, boost::simd::tag::sse_ >       svtype;
      typedef simd::native<sctype, boost::simd::tag::avx_ >        vtype;

      svtype a00 = _mm256_extractf128_si256(a0, 0);
      svtype a01 = _mm256_extractf128_si256(a0, 1);
      svtype a10 = _mm256_extractf128_si256(a1, 0);
      svtype a11 = _mm256_extractf128_si256(a1, 1);
      result_type that = _mm256_insertf128_si256(that,boost::simd::deinterleave_second(a00, a01), 0);
      return  _mm256_insertf128_si256(that,  boost::simd::deinterleave_second(a10, a11), 1);

     }
  };
  

} } }

#endif
#endif
