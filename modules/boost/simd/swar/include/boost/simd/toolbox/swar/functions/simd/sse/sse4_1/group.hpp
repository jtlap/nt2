//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_SWAR_FUNCTIONS_SIMD_SSE_SSE4_1_GROUP_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_SWAR_FUNCTIONS_SIMD_SSE_SSE4_1_GROUP_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_SSE4_1_SUPPORT

#include <boost/simd/toolbox/swar/functions/group.hpp>
#include <boost/simd/include/functions/simd/bitwise_cast.hpp>
#include <boost/dispatch/meta/downgrade.hpp>
#include <boost/simd/include/functions/simd/saturate.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::group_, boost::simd::tag::sse4_1_, (A0)
                            , ((simd_<uint32_<A0>,boost::simd::tag::sse_>))
                              ((simd_<uint32_<A0>,boost::simd::tag::sse_>))
                            )
  {
    typedef typename dispatch::meta::downgrade<A0>::type result_type;

    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      A0 aa0 = boost::simd::saturate<result_type>(a0);
      A0 aa1 = boost::simd::saturate<result_type>(a1);
      return simd::bitwise_cast<result_type>(_mm_packus_epi32(aa0, aa1));
    }
  };
} } }

#endif
#endif
