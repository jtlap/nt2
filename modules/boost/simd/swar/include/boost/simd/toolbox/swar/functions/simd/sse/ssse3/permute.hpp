//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_SWAR_FUNCTIONS_SIMD_SSE_SSSE3_PERMUTE_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_SWAR_FUNCTIONS_SIMD_SSE_SSSE3_PERMUTE_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_SSSE3_SUPPORT
#include <boost/simd/toolbox/swar/functions/permute.hpp>
#include <boost/simd/include/functions/bitwise_cast.hpp>
#include <boost/simd/toolbox/swar/functions/details/shuffle.hpp>
#include <boost/simd/sdk/meta/cardinal_of.hpp>
#include <boost/mpl/apply.hpp>

#define V(i) boost::mpl::apply<permutation_t,boost::mpl::int_<i>,card_t>::type::value
#define H1(i, inc) ((V(i) < 0) ? -1 : (H0(i)+inc))

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::permute_
                                    , boost::simd::tag::ssse3_
                                    , (A0)(P)
                                    , ((simd_<type64_<A0>,boost::simd::tag::sse_>))
                                      (target_< unspecified_<P> >)
                                    )
  {
    typedef A0                              result_type;
    typedef typename P::type                permutation_t;
    typedef meta::cardinal_of<result_type>  card_t;

    result_type operator()(A0 const& a, P const&) const
    {
#define H0(i) ((V(i) & 1) << 3)
      return  bitwise_cast<A0>
              ( _mm_shuffle_epi8( bitwise_cast<__m128i>(a)
                                , _mm_setr_epi8
                                  ( H1(0, 0), H1(0, 1) ,H1(0, 2), H1(0, 3)
                                  , H1(0, 4), H1(0, 5) ,H1(0, 6), H1(0, 7)
                                  , H1(1, 0), H1(1, 1) ,H1(1, 2), H1(1, 3)
                                  , H1(1, 4), H1(1, 5) ,H1(1, 6), H1(1, 7)
                                  )
                                )
              );
#undef H0
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::permute_, boost::simd::tag::ssse3_
                                    , (A0)(P)
                                    , ((simd_< type32_<A0>,boost::simd::tag::sse_>))
                                      (target_< unspecified_<P> >)
                                    )
  {
    typedef A0                              result_type;
    typedef typename P::type                permutation_t;
    typedef meta::cardinal_of<result_type>  card_t;

    result_type operator()(A0 const& a, P const&) const
    {
#define H0(i) ((V(i) & 3) << 2)
      return  bitwise_cast<A0>
              ( _mm_shuffle_epi8( bitwise_cast<__m128i>(a)
                                , _mm_setr_epi8
                                  ( H1(0, 0), H1(0, 1) ,H1(0, 2), H1(0, 3)
                                  , H1(1, 0), H1(1, 1) ,H1(1, 2), H1(1, 3)
                                  , H1(2, 0), H1(2, 1) ,H1(2, 2), H1(2, 3)
                                  , H1(3, 0), H1(3, 1) ,H1(3, 2), H1(3, 3)
                                  )
                                )
              );
#undef H0
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::permute_, boost::simd::tag::ssse3_
                                      , (A0)(P)
                                      , ((simd_< type16_<A0>,boost::simd::tag::sse_>))
                                        (target_< unspecified_<P> >)
                                      )
  {
    typedef A0                              result_type;
    typedef typename P::type                permutation_t;
    typedef meta::cardinal_of<result_type>  card_t;

    result_type operator()(A0 const& a, P const&) const
    {
#define H0(i) ((V(i) & 7) << 1)
      return  bitwise_cast<A0>
              ( _mm_shuffle_epi8( bitwise_cast<__m128i>(a)
                                , _mm_setr_epi8
                                  ( H1(0, 0), H1(0, 1) ,H1(1, 0), H1(1, 1)
                                  , H1(2, 0), H1(2, 1) ,H1(3, 0), H1(3, 1)
                                  , H1(4, 0), H1(4, 1) ,H1(5, 0), H1(5, 1)
                                  , H1(6, 0), H1(6, 1) ,H1(7, 0), H1(7, 1)
                                  )
                                )
              );
#undef H0
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::permute_, boost::simd::tag::ssse3_
                                    , (A0)(P)
                                    , ((simd_< type8_<A0>,boost::simd::tag::sse_>))
                                      (target_< unspecified_<P> >)
                                    )
  {
    typedef A0                              result_type;
    typedef typename P::type                permutation_t;
    typedef meta::cardinal_of<result_type>  card_t;

    result_type operator()(A0 const& a, P const&) const
    {
#define H(i) ((V(i) < 0) ? -1 : V(i))
      return  bitwise_cast<A0>
              ( _mm_shuffle_epi8( bitwise_cast<__m128i>(a)
                                , _mm_setr_epi8
                                  ( H( 0), H( 1), H( 2), H(3)
                                  , H( 4), H( 5), H( 6), H(7)
                                  , H( 8), H( 9), H(10), H(11)
                                  , H(12), H(13), H(14), H(15)
                                  )
                                )
              );
#undef H
    }
  };
} } }

#undef V
#undef H1

#endif
#endif
