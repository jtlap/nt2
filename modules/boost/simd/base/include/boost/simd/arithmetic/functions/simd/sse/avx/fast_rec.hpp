//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_SIMD_SSE_AVX_FAST_REC_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_SIMD_SSE_AVX_FAST_REC_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_AVX_SUPPORT

#include <boost/simd/arithmetic/functions/rec.hpp>
#include <boost/simd/include/functions/sqr.hpp>
#include <boost/simd/include/functions/plus.hpp>
#include <boost/simd/include/functions/minus.hpp>
#include <boost/simd/include/functions/times.hpp>
#include <boost/simd/include/functions/genmask.hpp>
#include <boost/simd/include/functions/bitwise_and.hpp>
#include <boost/simd/sdk/config.hpp>

#if !defined(BOOST_SIMD_NO_INFINITIES)
#include <boost/simd/include/functions/is_not_infinite.hpp>
#include <boost/simd/include/functions/if_else_zero.hpp>
#endif

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::rec_
                                    , boost::simd::tag::avx_
                                    , (A0)
                                    , ((simd_< single_<A0>
                                            , boost::simd::tag::avx_
                                            >
                                      ))
                                    )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      // Estimation x ~= 1/X
      A0  inv   = _mm256_rcp_ps( a0 );

      // Square and filter out 1/+-0
      A0  invs  = (a0 * sqr(inv)) & genmask(a0);

    #if defined(BOOST_SIMD_NO_INFINITIES)
      // Newton-Raphson: 1/X ~= (2*x - (a0*x^2)
      return (inv+inv) - invs;
    #else
      // handle 1/+-inf
      return if_else_zero( is_not_infinite(a0), (inv+inv) - invs );
    #endif
    }
  };
} } }

#endif
#endif
