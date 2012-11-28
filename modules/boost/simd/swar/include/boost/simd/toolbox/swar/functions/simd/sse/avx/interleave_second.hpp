//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_SWAR_FUNCTIONS_SIMD_SSE_AVX_INTERLEAVE_SECOND_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_SWAR_FUNCTIONS_SIMD_SSE_AVX_INTERLEAVE_SECOND_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_AVX_SUPPORT

#include <boost/simd/toolbox/swar/functions/interleave_second.hpp>
#include <boost/simd/include/functions/bitwise_cast.hpp>
#include <boost/simd/toolbox/swar/functions/details/shuffle.hpp>
#include <boost/simd/toolbox/swar/functions/details/perm.hpp>
#include <boost/dispatch/meta/as_floating.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::interleave_second_
                                   , boost::simd::tag::avx_
                                   , (A0)(A1)
                                   , ((simd_<single_<A0>,boost::simd::tag::avx_>))
                                     ((simd_<single_<A1>,boost::simd::tag::avx_>))
                                   )
  {
    typedef A0 result_type;

    result_type operator()(__m256 const a0, __m256 const a1) const
    {
      result_type that0 = details::perm2<1, 1>(a0, a0);
      that0 = details::shuffle_pairs<0, 1, 1, 3>(that0, that0);
      result_type that1 = details::perm2<1, 1>(a1, a1);
      that1 = details::shuffle_pairs<0, 1, 1, 3>(that1, that1);
      return _mm256_unpacklo_ps(that0,that1);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::interleave_second_
                                   , boost::simd::tag::avx_
                                   , (A0)(A1)
                                   , ((simd_<double_<A0>,boost::simd::tag::avx_>))
                                     ((simd_<double_<A1>,boost::simd::tag::avx_>))
                                   )
  {
    typedef A0 result_type;

    result_type operator()(__m256d const a0, __m256d const a1) const
    {
      result_type that0 = details::perm2<1, 1>(a0, a0);
      that0 = details::shuffle<0, 1, 1, 3>(that0, that0);
      result_type that1 = details::perm2<1, 1>(a1, a1);
      that1 = details::shuffle<0, 1, 1, 3>(that1, that1);
      return _mm256_unpacklo_pd(that0,that1);

    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::interleave_second_
                                   , boost::simd::tag::avx_
                                   , (A0)(A1)
                                   , ((simd_<type32_<A0>,boost::simd::tag::avx_>))
                                     ((simd_<type32_<A1>,boost::simd::tag::avx_>))
                                   )
  {
    typedef A0 result_type;

    result_type operator()(__m256i const a0, __m256i const a1) const
    {
      typedef typename boost::dispatch::meta::as_floating<A0>::type  ftype;
      return  bitwise_cast<result_type>(interleave_second(bitwise_cast<ftype>(a0), bitwise_cast<ftype>(a1)));
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::interleave_second_
                                   , boost::simd::tag::avx_
                                   , (A0)(A1)
                                   , ((simd_<type64_<A0>,boost::simd::tag::avx_>))
                                     ((simd_<type64_<A1>,boost::simd::tag::avx_>))
                                   )
  {
    typedef A0 result_type;

    result_type operator()(A0 const a0, A1 const a1) const
    {
      typedef typename boost::dispatch::meta::as_floating<A0>::type  ftype;
      return bitwise_cast<result_type>(interleave_second(bitwise_cast<ftype>(a0), bitwise_cast<ftype>(a1)));
    }
  };

} } }

#endif
#endif
