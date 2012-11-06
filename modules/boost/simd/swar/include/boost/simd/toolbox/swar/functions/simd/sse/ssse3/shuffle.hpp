//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_SWAR_FUNCTIONS_SIMD_SSE_SSSE3_SHUFFLE_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_SWAR_FUNCTIONS_SIMD_SSE_SSSE3_SHUFFLE_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_SSSE3_SUPPORT
#include <boost/simd/toolbox/swar/functions/shuffle.hpp>
#include <boost/simd/include/functions/bitwise_cast.hpp>
#include <boost/simd/sdk/meta/cardinal_of.hpp>
#include <boost/simd/toolbox/swar/functions/details/perm.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::shuffle_
                                    , boost::simd::tag::ssse3_
                                    , (A0)(P)
                                    , ((simd_<arithmetic_<A0>,boost::simd::tag::sse_>))
                                      (target_< unspecified_<P> >)
                                    )
  {
    typedef A0                              result_type;
    typedef P                               permutation_t;
    typedef meta::cardinal_of<result_type>  card_t;

    result_type operator()(A0 const& a, P const&) const
    {
      std::cout << "arithmetic_";
      return  bitwise_cast<A0>
              ( _mm_shuffle_epi8( bitwise_cast<__m128i>(a)
                                , details::permute<P,card_t::value>::call()
                                )
              );
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::shuffle_
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
            std::cout << "type64_";
      return  bitwise_cast<A0>
              ( _mm_shuffle_epi8( bitwise_cast<__m128i>(a)
                                , details::permute<P,card_t::value>::call()
                                )
              );
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::shuffle_
                                    , boost::simd::tag::ssse3_
                                    , (A0)(P)
                                    , ((simd_<type32_<A0>,boost::simd::tag::sse_>))
                                      (target_< unspecified_<P> >)
                                    )
  {
    typedef A0                              result_type;
    typedef typename P::type                permutation_t;
    typedef meta::cardinal_of<result_type>  card_t;

    result_type operator()(A0 const& a, P const&) const
    {
            std::cout << "type32_";
      return  bitwise_cast<A0>
              ( _mm_shuffle_epi8( bitwise_cast<__m128i>(a)
                                , details::permute<P,card_t::value>::call()
                                )
              );
    }
  };

} } }

#endif
#endif
