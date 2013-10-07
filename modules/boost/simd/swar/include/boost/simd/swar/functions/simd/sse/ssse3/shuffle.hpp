//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SWAR_FUNCTIONS_SIMD_SSE_SSSE3_SHUFFLE_HPP_INCLUDED
#define BOOST_SIMD_SWAR_FUNCTIONS_SIMD_SSE_SSSE3_SHUFFLE_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_SSSE3_SUPPORT
#include <boost/simd/swar/functions/shuffle.hpp>
#include <boost/simd/include/functions/bitwise_cast.hpp>
#include <boost/simd/sdk/meta/cardinal_of.hpp>
#include <boost/simd/swar/functions/details/perm.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::shuffle_
                                    , boost::simd::tag::ssse3_
                                    , (A0)(P)
                                    , ((simd_ < type16_<A0>
                                              , boost::simd::tag::sse_
                                              >
                                      ))
                                      (target_< unspecified_<P> >)
                                    )
  {
    typedef A0                              result_type;
    typedef P                               permutation_t;
    typedef meta::cardinal_of<result_type>  card_t;

    typedef typename A0::template rebind<unsigned char>::type mask_type;

    result_type operator()(__m128i a, P const&) const
    {
      return  _mm_shuffle_epi8( a
                              , details::permute< P
                                                , mask_type
                                                , card_t::value
                                                >::call()
                              );
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::shuffle_
                                    , boost::simd::tag::ssse3_
                                    , (A0)(P)
                                    , ((simd_ < type8_<A0>
                                              , boost::simd::tag::sse_
                                              >
                                      ))
                                      (target_< unspecified_<P> >)
                                    )
  {
    typedef A0                              result_type;
    typedef P                               permutation_t;
    typedef meta::cardinal_of<result_type>  card_t;
    result_type operator()(__m128i a, P const&) const
    {
      return  _mm_shuffle_epi8( a
                              , details::permute< P
                                                , result_type
                                                , card_t::value
                                                >::call()
                              );
    }
  };
} } }

#endif
#endif
