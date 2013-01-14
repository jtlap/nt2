//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_SWAR_FUNCTIONS_SIMD_SSE_SSSE3_REVERSE_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_SWAR_FUNCTIONS_SIMD_SSE_SSSE3_REVERSE_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_SSSE3_SUPPORT

#include <boost/simd/toolbox/swar/functions/reverse.hpp>
#include <boost/simd/include/functions/simd/bitwise_cast.hpp>
#include <boost/simd/sdk/meta/make_dependent.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::reverse_, boost::simd::tag::ssse3_
                                   , (A0)
                                   , ((simd_<type8_<A0>,boost::simd::tag::sse_>))
                                   )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      result_type indices = make<result_type>(15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0);
      return simd::bitwise_cast<A0>(_mm_shuffle_epi8(a0, indices));
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::reverse_, boost::simd::tag::ssse3_
                                   , (A0)
                                   , ((simd_<type16_<A0>,boost::simd::tag::sse_>))
                                   )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      typedef typename meta::make_dependent<int8_t, A0>::type int8;
      typedef simd::native<int8, boost::simd::tag::sse_> type8;
      type8 indices = make<type8>(14, 15, 12, 13, 10, 11, 8, 9, 6, 7, 4, 5, 2, 3, 0, 1);
      return simd::bitwise_cast<A0>(_mm_shuffle_epi8(simd::bitwise_cast<type8>(a0), indices));
    }
  };
} } }

#endif
#endif
