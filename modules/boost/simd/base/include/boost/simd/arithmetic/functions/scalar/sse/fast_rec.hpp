//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_SCALAR_SSE_REC_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_SCALAR_SSE_REC_HPP_INCLUDED

#if defined(BOOST_SIMD_HAS_SSE2_SUPPORT)

#include <boost/simd/arithmetic/functions/fast_rec.hpp>
#include <boost/simd/sdk/config.hpp>

#if !defined(BOOST_SIMD_NO_INFINITIES)
#include <boost/simd/include/functions/is_not_infinite.hpp>
#include <boost/simd/include/functions/if_else_zero.hpp>
#endif

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::fast_rec_
                                    , boost::simd::tag::sse_
                                    , (A0)
                                    , (scalar_< single_<A0> >)
                                    )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE result_type operator()(A0 a0) const
    {
      float inv;
      _mm_store_ss( &inv, _mm_rcp_ps( _mm_load_ss( &a0 ) ) );

      // Square and filter out 1/+-0
      A0  invs  = a0 ? (a0 * (inv*inv)) : a0;

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
