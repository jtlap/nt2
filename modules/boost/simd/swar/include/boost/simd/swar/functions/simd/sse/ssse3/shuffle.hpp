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
#include <boost/simd/sdk/meta/cardinal_of.hpp>
#include <boost/simd/swar/functions/simd/sse/sse2/details/patterns.hpp>
#include <boost/simd/include/functions/simd/bitwise_cast.hpp>
#include <boost/simd/include/functions/simd/bitwise_or.hpp>
#include <boost/simd/swar/functions/details/perm.hpp>
#include <boost/simd/sdk/meta/cardinal_of.hpp>
#include <boost/dispatch/attributes.hpp>
#include <boost/dispatch/meta/as.hpp>

//==============================================================================
// SSSE3 shuffle use the SSE2 pattern matcher optimizer but has a specific
// permutation unit that is able to perform single argument permutation. We use
// this for shuffle<?>(a0) and we use bit tricks for the shuffle<?>(a0,a1) case:
// two meta-permutation adapter compute the two part that get bit-ORed.
//==============================================================================
namespace boost { namespace simd { namespace ext
{
  // SSSE3 has a full permute unit
  template<std::size_t N> struct ssse3_permute
  {
    template<typename T,typename P>
    BOOST_FORCEINLINE static T call(T const& a0, P const&)
    {
      typedef typename T::template rebind<unsigned char>::type m_t;
      m_t const that = _mm_shuffle_epi8( bitwise_cast<m_t>(a0)
                                       , details::permute<P,m_t,N>::call()
                                       );
      return bitwise_cast<T>(that);
    }

    // Keep a0 indexing, zero out the other
    template<typename P> struct force_left
    {
      template<typename I, typename C> struct apply
      {
        typedef typename boost::mpl::apply<P,I,C>::type base_t;

        //  make -1 if it was outside [0,C[ and let as if if inside
        typedef boost::mpl::int_< !(base_t::value >= C::value)
                                ? base_t::value
                                : -1
                                >                       type;
      };
    };

    // Keep a1 reduced indexing, zero out the other
    template<typename P> struct force_right
    {
      template<typename I, typename C> struct apply
      {
        typedef typename boost::mpl::apply<P,I,C>::type base_t;

        //  make -1 if it was inside [0,C[ and shift if outside
        typedef boost::mpl::int_< (base_t::value >= C::value)
                                ? (base_t::value - C::value)
                                : -1
                                >                       type;
      };
    };

    template<typename T,typename P>
    BOOST_FORCEINLINE static T call(T const& a0, T const& a1, P const&)
    {
      // double permute + bitwise or
      return  call(a0, force_left <P>() ) | call(a1, force_right<P>() );
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::shuffle_
                                    , boost::simd::tag::ssse3_
                                    , (T)(P)
                                    , ((simd_ < arithmetic_<T>
                                              , boost::simd::tag::sse_
                                              >
                                      ))
                                      (target_< unspecified_<P> >)
                                    )
  {
    typedef T  result_type;

    BOOST_FORCEINLINE result_type operator()(T const& a0,P const&) const
    {
      typename P::type p;

      return details::shuffler< sse2_matcher
                              , ssse3_permute<meta::cardinal_of<T>::value>
                              , meta::cardinal_of<T>::value
                              , 16
                              >::process(a0,p);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::shuffle_
                                    , boost::simd::tag::ssse3_
                                    , (T)(P)
                                    , ((simd_ < arithmetic_<T>
                                              , boost::simd::tag::sse_
                                              >
                                      ))
                                      ((simd_ < arithmetic_<T>
                                              , boost::simd::tag::sse_
                                              >
                                      ))
                                      (target_< unspecified_<P> >)
                                    )
  {
    typedef T  result_type;

    BOOST_FORCEINLINE
    result_type operator()(T const& a0,T const& a1, P const&) const
    {
      typename P::type p;

      return details::shuffler< sse2_matcher
                              , ssse3_permute<meta::cardinal_of<T>::value>
                              , meta::cardinal_of<T>::value
                              , 16
                              >::process(a0,a1,p);
    }
  };
} } }

#endif
#endif
