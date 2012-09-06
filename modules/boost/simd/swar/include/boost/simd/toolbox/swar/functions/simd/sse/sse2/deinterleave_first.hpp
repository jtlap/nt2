//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_SWAR_FUNCTIONS_SIMD_SSE_SSE2_DEINTERLEAVE_FIRST_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_SWAR_FUNCTIONS_SIMD_SSE_SSE2_DEINTERLEAVE_FIRST_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_SSE2_SUPPORT

#include <boost/simd/toolbox/swar/functions/deinterleave_first.hpp>
#include <boost/simd/toolbox/swar/functions/details/shuffle.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::deinterleave_first_
                                   , boost::simd::tag::sse2_
                                   , (A0)(A1)
                                   , ((simd_<single_<A0>,boost::simd::tag::sse_>))
                                     ((simd_<single_<A1>,boost::simd::tag::sse_>))
                                   )
  {
    typedef A0 result_type;

    result_type operator()(__m128 const a0, __m128 const a1) const
    {
      return details::shuffle<0, 2, 0, 2>(a0,a1);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::deinterleave_first_
                                   , boost::simd::tag::sse2_
                                   , (A0)(A1)
                                   , ((simd_<double_<A0>,boost::simd::tag::sse_>))
                                     ((simd_<double_<A1>,boost::simd::tag::sse_>))
                                   )
  {
    typedef A0 result_type;

    result_type operator()(__m128d const a0, __m128d const a1) const
    {
      return details::shuffle<0, 0>(a0,a1);
    }
  };
} } }

#endif
#endif