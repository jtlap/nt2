//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_REDUCTION_FUNCTIONS_SIMD_SSE_AVX_SUM_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_REDUCTION_FUNCTIONS_SIMD_SSE_AVX_SUM_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_AVX_SUPPORT

#include <boost/simd/toolbox/reduction/functions/sum.hpp>
#include <boost/simd/include/functions/simd/sum.hpp>
#include <boost/simd/include/functions/simd/multiplies.hpp>

// /////////////////////////////////////////////////////////////////////////////
// // Implementation when type  is arithmetic_
// /////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::sum_, boost::simd::tag::avx_,
                                    (A0),
                                    ((simd_<double_<A0>,boost::simd::tag::sse_>))
                                    ((simd_<double_<A0>,boost::simd::tag::sse_>))
                                    )
  {
    typedef typename meta::scalar_of<A0>::type result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
      {
        A0 r = _mm256_dp_pd(a0, One<A0>(), 0x3);
        return r[0];
      }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::sum_, boost::simd::tag::avx_,
                                    (A0),
                                    ((simd_<single_<A0>,boost::simd::tag::avx_>))
                                    ((simd_<single_<A0>,boost::simd::tag::avx_>))
                                    )
  {
    typedef typename meta::scalar_of<A0>::type result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
      {
        A0 r = _mm256_dp_ps(a0, One<A0>(), 0xFF);
        return r[0]+r[4];
// this in another solution for floats,  perhaps speedier ?
// x3 = _mm256_add_ps(x0, _mm256_movehdup_ps(x0));
// x4 = _mm256_unpackhi_ps(x3, x3)  ;
// x4 = _mm256_add_ps(x3, x4)  ;
// x5 = _mm256_permute2f128_ps(x4, x4, 0x01)  ;
// x5 = _mm256_add_ps(x5, x4)  ;
      }
  };

} } }
#endif
#endif
