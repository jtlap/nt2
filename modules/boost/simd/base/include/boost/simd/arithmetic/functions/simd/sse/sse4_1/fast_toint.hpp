//==============================================================================
//         Copyright 2014        LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2014        LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2014        NumScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_SIMD_SSE_SSE4_1_FAST_TOINT_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_SIMD_SSE_SSE4_1_FAST_TOINT_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_SSE4_1_SUPPORT
#include <boost/simd/arithmetic/functions/fast_toint.hpp>
#include <boost/dispatch/meta/as_integer.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::fast_toint_
                                    , boost::simd::tag::sse4_1_
                                    , (A0)
                                    , ((simd_<double_<A0>,boost::simd::tag::sse_>))
                                    )
  {
    typedef typename dispatch::meta::as_integer<A0>::type result_type;
    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL(1)
    {
      return _mm_cvtepi32_epi64( _mm_cvttpd_epi32(a0));
    }
  };
} } }

#endif
#endif


