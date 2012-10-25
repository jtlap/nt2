//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_SWAR_FUNCTIONS_SIMD_SSE_SSE2_SHUFFLE_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_SWAR_FUNCTIONS_SIMD_SSE_SSE2_SHUFFLE_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_SSE2_SUPPORT
#include <boost/simd/toolbox/swar/functions/shuffle.hpp>
#include <boost/simd/toolbox/swar/functions/details/shuffle.hpp>
#include <boost/simd/include/constants/zero.hpp>
#include <boost/dispatch/meta/as_integer.hpp>

namespace boost { namespace simd
{
  namespace ext
  {
    BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::shuffle_
                                      , boost::simd::tag::sse_
                                      , (A0)(P)
                                      , ((simd_ < type64_<A0>
                                                , boost::simd::tag::sse_
                                                >
                                        ))
                                        (target_< unspecified_<P> >)
                                      )
    {
      typedef A0                              result_type;
      typedef typename P::type                permutation_t;

      template< int I0,int I1
              , bool NoNull = (I0 != -1) && (I1 !=-1)
              > struct sel {};

      BOOST_FORCEINLINE result_type operator()(A0 const& a0,P const&) const
      {
        typedef typename boost::mpl::apply< permutation_t
                                          , boost::mpl::int_<0>
                                          , boost::mpl::int_<2>
                                          >::type               i0_t;
        typedef typename boost::mpl::apply< permutation_t
                                          , boost::mpl::int_<1>
                                          , boost::mpl::int_<2>
                                          >::type               i1_t;

        return eval(a0,sel<i0_t::value,i1_t::value>());
      }

      BOOST_FORCEINLINE result_type eval(A0 const& a0, sel<0,1> const&) const
      {
        return a0;
      }

      BOOST_FORCEINLINE result_type eval(A0 const& , sel<-1,-1> const&) const
      {
        return Zero<result_type>();
      }

      template<int I0>
      BOOST_FORCEINLINE __m128d eval(__m128d a0, sel<I0,-1> const&) const
      {
        return details::shuffle<I0,0>(a0,Zero<result_type>());
      }

      template<int I1>
      BOOST_FORCEINLINE __m128d eval(__m128d a0, sel<-1,I1> const&) const
      {
        return details::shuffle<0,I1>(Zero<result_type>(), a0);
      }

      template<int I0, int I1>
      BOOST_FORCEINLINE __m128d eval(__m128d a0, sel<I0,I1,true> const&) const
      {
        return details::shuffle<I0,I1>(a0);
      }

      BOOST_FORCEINLINE __m128i eval(__m128i a0, sel<0,0> const&) const
      {
        return _mm_unpacklo_epi64(a0, a0);
      }

      BOOST_FORCEINLINE __m128i eval(__m128i a0, sel<1,1> const&) const
      {
        return _mm_unpackhi_epi64(a0, a0);
      }

      BOOST_FORCEINLINE __m128i eval(__m128i a0, sel<1,0> const&) const
      {
        return details::shuffle<2,3,0,1>(a0);
      }

      BOOST_FORCEINLINE __m128i eval(__m128i a0, sel<0,-1> const&) const
      {
        return _mm_unpacklo_epi64(a0, Zero<result_type>());
      }

      BOOST_FORCEINLINE __m128i eval(__m128i a0, sel<1,-1> const&) const
      {
        return _mm_srli_si128(a0, 8);
      }

      BOOST_FORCEINLINE __m128i eval(__m128i a0, sel<-1,0> const&) const
      {
        return _mm_slli_si128(a0, 8);
      }

      BOOST_FORCEINLINE __m128i eval(__m128i a0, sel<-1,1> const&) const
      {
        return _mm_unpackhi_epi64(Zero<result_type>(), a0);
      }
    };

   BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::shuffle_
                                      , boost::simd::tag::sse_
                                      , (A0)(P)
                                      , ((simd_ < type32_<A0>
                                                , boost::simd::tag::sse_
                                                >
                                        ))
                                        (target_< unspecified_<P> >)
                                      )
    {
      typedef A0                              result_type;
      typedef typename P::type                permutation_t;

      template< int I0,int I1,int I2,int I3
              , bool Some0 = (I0==-1) || (I1==-1) || (I2==-1) || (I3==-1)
              >
      struct sel
      {};

      BOOST_FORCEINLINE result_type operator()(A0 const& a0,P const&) const
      {
        typedef typename boost::mpl::apply< permutation_t
                                          , boost::mpl::int_<0>
                                          , boost::mpl::int_<4>
                                          >::type               i0_t;
        typedef typename boost::mpl::apply< permutation_t
                                          , boost::mpl::int_<1>
                                          , boost::mpl::int_<4>
                                          >::type               i1_t;
        typedef typename boost::mpl::apply< permutation_t
                                          , boost::mpl::int_<2>
                                          , boost::mpl::int_<4>
                                          >::type               i2_t;
        typedef typename boost::mpl::apply< permutation_t
                                          , boost::mpl::int_<3>
                                          , boost::mpl::int_<4>
                                          >::type               i3_t;

        return eval(a0,sel<i0_t::value,i1_t::value,i2_t::value,i3_t::value>());
      }

      BOOST_FORCEINLINE result_type eval(A0 const& a0, sel<0,1,2,3> const&) const
      {
        return a0;
      }

      BOOST_FORCEINLINE result_type eval(A0 const&, sel<-1,-1,-1,-1> const&) const
      {
        return Zero<result_type>();
      }

      template<int I0,int I1,int I2,int I3> BOOST_FORCEINLINE
      result_type eval(A0 const& a0, sel<I0,I1,I2,I3,false> const&) const
      {
        return details::shuffle<I0&3, I1&3, I2&3, I3&3>(a0);
      }

      template<int I0,int I1,int I2,int I3> BOOST_FORCEINLINE
      result_type eval(A0 const& a0, sel<I0,I1,I2,I3,true> const&) const
      {
        typedef typename dispatch::meta::as_integer<A0,unsigned>::type i_t;

        // Mask the shuffled equivalent
        return  simd::bitwise_and
                ( eval( a0, sel<I0<0?0:I0,I1<0?1:I1,I2<0?2:I2,I3<0?3:I3>() )
                , simd::make<i_t> ( -int(I0>=0), -int(I1>=0)
                                  , -int(I2>=0), -int(I3>=0)
                                  )
                );
      }

      template<int I0,int I1> BOOST_FORCEINLINE
      result_type eval(A0 const& a0, sel<I0,I1,-1,-1,true> const&) const
      {
        return details::shuffle<(I0&3), (I1&3),2,3>(a0,Zero<result_type>());
      }

      template<int I2,int I3> BOOST_FORCEINLINE
      result_type eval(A0 const& a0, sel<-1,-1,I2,I3,true> const&) const
      {
        return details::shuffle<0, 1, (I2&3), (I3&3)>(Zero<result_type>(), a0);
      }
    };
  }
} }

#endif
#endif
