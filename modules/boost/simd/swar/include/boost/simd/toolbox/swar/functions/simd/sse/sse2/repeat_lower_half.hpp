//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_SWAR_FUNCTIONS_SIMD_SSE_SSE2_REPEAT_LOWER_HALF_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_SWAR_FUNCTIONS_SIMD_SSE_SSE2_REPEAT_LOWER_HALF_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_SSE2_SUPPORT

#include <boost/simd/toolbox/swar/functions/repeat_lower_half.hpp>
#include <boost/simd/include/functions/bitwise_cast.hpp>
#include <boost/simd/include/functions/interleave_first.hpp>
#include <boost/dispatch/meta/as_floating.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::repeat_lower_half_
                                   , boost::simd::tag::sse2_
                                   , (A0)
                                   , ((simd_<single_<A0>,boost::simd::tag::sse_>))
                                   )
  {
    typedef A0 result_type;

    result_type operator()(__m128 const a0) const
    {
      return _mm_movelh_ps(a0,a0);
    }
  };
  
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::repeat_lower_half_
                                   , boost::simd::tag::sse2_
                                   , (A0)
                                   , ((simd_<type32_<A0>,boost::simd::tag::sse_>))
                                   )
  {
    typedef A0 result_type;

    result_type operator()(__m128i const a0) const
    {
      typedef typename boost::dispatch::meta::as_floating<A0>::type  ftype;
      return bitwise_cast<result_type>(repeat_lower_half(bitwise_cast<ftype>(a0)));
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::repeat_lower_half_
                                   , boost::simd::tag::sse2_
                                   , (A0)
                                   , ((simd_<type64_<A0>,boost::simd::tag::sse_>))
                                   )
  {
    typedef A0 result_type;

    result_type operator()(__m128i const a0) const
    {
      return  bitwise_cast<result_type>(interleave_first(bitwise_cast<result_type>(a0), bitwise_cast<result_type>(a0))); 
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::repeat_lower_half_
                                   , boost::simd::tag::sse2_
                                   , (A0)
                                   , ((simd_<double_<A0>,boost::simd::tag::sse_>))
                                   )
  {
    typedef A0 result_type;

    result_type operator()(__m128d const a0) const
    {
      return  bitwise_cast<result_type>(interleave_first(bitwise_cast<result_type>(a0), bitwise_cast<result_type>(a0))); 
    }
  };   
} } }

#endif
#endif
