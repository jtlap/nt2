//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_SIMD_SSE_SSE2_REC_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_SIMD_SSE_SSE2_REC_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_SSE2_SUPPORT

#include <boost/simd/arithmetic/functions/rec.hpp>

#include <boost/simd/sdk/config.hpp>
#if !defined(BOOST_SIMD_NO_INFINITIES)
#include <boost/simd/include/functions/is_not_infinite.hpp>
#include <boost/simd/include/functions/if_else_zero.hpp>
#endif

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::rec_
                                    , boost::simd::tag::sse2_
                                    , (A0)
                                    , ((simd_< single_<A0>
                                            , boost::simd::tag::sse_
                                            >
                                      ))
                                    )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE result_type operator()(__m128 a0) const
    {
      // Estimation x ~= 1/X
      __m128  inv   = _mm_rcp_ps( a0 );

      // Newton-Raphson:
      // 1/X ~= (2*x - (a0*x^2)
      __m128  invs  = _mm_mul_ps( a0, _mm_mul_ps( inv, inv ) );
      __m128  rcp2  = _mm_add_ps( inv, inv );

      // Filter out 1/+-0
      invs = _mm_and_ps(invs,_mm_cmpneq_ps(a0,_mm_setzero_ps()) );

    #if defined(BOOST_SIMD_NO_INFINITIES)
      return _mm_sub_ps( rcp2, invs );
    #else
      // handle 1/+-inf
      return if_else_zero ( is_not_infinite(result_type(a0))
                          , result_type(_mm_sub_ps( rcp2, invs ))
                          );
    #endif
    }
  };
} } }

#endif
#endif
