//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_CONSTANT_CONSTANTS_SIMD_SSE_SSE2_ZERO_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_CONSTANT_CONSTANTS_SIMD_SSE_SSE2_ZERO_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_SSE2_SUPPORT

#include <boost/simd/toolbox/constant/constants/zero.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( simd::tag::Zero, boost::simd::tag::sse2_, (A0)
                                    , ((target_< simd_< single_<A0>, boost::simd::tag::sse_> >))
                                    )
  {
    typedef typename A0::type result_type;

    BOOST_DISPATCH_FORCE_INLINE result_type operator()(A0 const&) const
    {
      return _mm_setzero_ps();
    }
  };
  
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( simd::tag::Zero, boost::simd::tag::sse2_, (A0)
                                    , ((target_< simd_< double_<A0>, boost::simd::tag::sse_> >))
                                    )
  {
    typedef typename A0::type result_type;

    BOOST_DISPATCH_FORCE_INLINE result_type operator()(A0 const&) const
    {
      return _mm_setzero_pd();
    }
  };
} } }

#endif
#endif
