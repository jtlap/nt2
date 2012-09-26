//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_SWAR_FUNCTIONS_SIMD_SSE_SSE2_INTERLEAVE_ODD_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_SWAR_FUNCTIONS_SIMD_SSE_SSE2_INTERLEAVE_ODD_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_SSE2_SUPPORT

#include <boost/simd/toolbox/swar/functions/interleave_odd.hpp>
#include <boost/simd/toolbox/swar/functions/details/shuffle.hpp>
#include <boost/simd/include/functions/bitwise_cast.hpp>
#include <boost/dispatch/meta/as_floating.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::interleave_odd_
                                   , boost::simd::tag::sse2_
                                   , (A0)(A1)
                                   , ((simd_<single_<A0>,boost::simd::tag::sse_>))
                                     ((simd_<single_<A1>,boost::simd::tag::sse_>))
                                   )
  {
    typedef A0 result_type;

    result_type operator()(__m128 const a0, __m128 const a1) const
    {
      result_type that0 =  details::shuffle<1, 3, 1, 3>(a0,a0);
      result_type that1 =  details::shuffle<1, 3, 1, 3>(a1,a1);
      return _mm_unpackhi_ps(that0, that1);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::interleave_odd_
                                   , boost::simd::tag::sse2_
                                   , (A0)(A1)
                                   , ((simd_<double_<A0>,boost::simd::tag::sse_>))
                                     ((simd_<double_<A1>,boost::simd::tag::sse_>))
                                   )
  {
    typedef A0 result_type;

    result_type operator()(__m128d const a0, __m128d const a1) const
    {
      return _mm_unpackhi_pd(a0,a1);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::interleave_odd_
                                   , boost::simd::tag::sse2_
                                   , (A0)(A1)
                                   , ((simd_<type32_<A0>,boost::simd::tag::sse_>))
                                     ((simd_<type32_<A1>,boost::simd::tag::sse_>))
                                   )
  {
    typedef A0 result_type;

    result_type operator()(__m128i const a0, __m128i const a1) const
    {
      typedef typename boost::dispatch::meta::as_floating<A0>::type  ftype;
      return  bitwise_cast<result_type>(interleave_odd(bitwise_cast<ftype>(a0), bitwise_cast<ftype>(a1))); 
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::interleave_odd_
                                   , boost::simd::tag::sse2_
                                   , (A0)(A1)
                                   , ((simd_<type64_<A0>,boost::simd::tag::sse_>))
                                     ((simd_<type64_<A1>,boost::simd::tag::sse_>))
                                   )
  {
    typedef A0 result_type;

    result_type operator()(A0 const a0, A1 const a1) const
    {
      return _mm_unpackhi_epi64(a0,a1); //does this exists with 32bits systems
//       typedef typename boost::dispatch::meta::as_floating<A0>::type  ftype;
//       return bitwise_cast<result_type>(interleave_odd(bitwise_cast<ftype>(a0), bitwise_cast<ftype>(a1))); 
    }
  };
    
} } }

#endif
#endif
