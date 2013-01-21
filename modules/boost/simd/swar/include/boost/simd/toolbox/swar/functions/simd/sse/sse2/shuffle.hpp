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
#include <boost/dispatch/functor/functor.hpp>
#include <boost/simd/include/constants/zero.hpp>
#include <boost/dispatch/meta/as_integer.hpp>

namespace boost { namespace simd
{
  namespace ext
  {
    BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::shuffle_
                                      , boost::simd::tag::sse2_
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
                                      , boost::simd::tag::sse2_
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

    BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::shuffle_
                                      , boost::simd::tag::sse2_
                                      , (A0)(P)
                                      , ((simd_ < type64_<A0>
                                                , boost::simd::tag::sse_
                                                >
                                        ))
                                        ((simd_ < type64_<A0>
                                                , boost::simd::tag::sse_
                                                >
                                        ))
                                        (target_< unspecified_<P> >)
                                      )
    {
      typedef A0                              result_type;
      typedef typename P::type                permutation_t;

      template< int  A
              , int  B
              , bool InfAB = A<2&&B<2
              , bool SupAB = (A>=2||A==-1)&&(B>=2||B==-1)
              > struct sel {};

      BOOST_FORCEINLINE result_type operator()(A0 const& a0, A0 const& a1, P const&) const
      {
        typedef typename boost::mpl::apply< permutation_t
                                          , boost::mpl::int_<0>
                                          , boost::mpl::int_<2>
                                          >::type               i0_t;
        typedef typename boost::mpl::apply< permutation_t
                                          , boost::mpl::int_<1>
                                          , boost::mpl::int_<2>
                                          >::type               i1_t;

        return eval(a0,a1,sel<i0_t::value,i1_t::value>());
      }

      BOOST_FORCEINLINE result_type eval( A0 const&, A0 const&
                                        , sel<-1,-1> const&) const
      {
        return Zero<result_type>();
      }

      template<int A, int B>
      BOOST_FORCEINLINE result_type eval( A0 const& a, A0 const&
                                        , sel<A,B,true,false> const&) const
      {
        return shuffle<A,B>(a);
      }

      template<int A, int B>
      BOOST_FORCEINLINE result_type eval( A0 const&, A0 const& b
                                        , sel<A,B,false,true> const&) const
      {
        return shuffle<(A==-1)?A:(A-2),(B==-1)?B:(B-2)>(b);
      }

      template<int A, int B>
      BOOST_FORCEINLINE result_type eval( __m128d const a, __m128d const b
                                        , sel<A,B,false,false> const&) const
      {
        return details::shuffle<(A>B?A-2:A),(A>B?B-2:B)>((A>B?b:a),(A>B?a:b));
      }

      BOOST_FORCEINLINE result_type eval( __m128i const a, __m128i const b
                                        , sel<0,2,false,false> const&) const
      {
        return _mm_unpacklo_epi64(a, b);
      }

      BOOST_FORCEINLINE result_type eval( __m128i const a, __m128i const b
                                        , sel<1,2,false,false> const&) const
      {
        return details::shuffle<2,3,0,1>(a,b);
      }

      BOOST_FORCEINLINE result_type eval( __m128i const a, __m128i const b
                                        , sel<0,3,false,false> const&) const
      {
        return details::shuffle<0,1,2,3>(a,b);
      }

      BOOST_FORCEINLINE result_type eval( __m128i const a, __m128i const b
                                        , sel<1,3,false,false> const&) const
      {
        return _mm_unpackhi_epi64(a, b);
      }

      BOOST_FORCEINLINE result_type eval( __m128i const a, __m128i const b
                                        , sel<2,0,false,false> const&) const
      {
        return _mm_unpacklo_epi64(b, a);
      }

      BOOST_FORCEINLINE result_type eval( __m128i const a, __m128i const b
                                        , sel<2,1,false,false> const&) const
      {
        return details::shuffle<0,1,2,3>(b,a);
      }

      BOOST_FORCEINLINE result_type eval( __m128i const a, __m128i const b
                                        , sel<3,0,false,false> const&) const
      {
        return details::shuffle<2,3,0,1>(b,a);
      }

      BOOST_FORCEINLINE result_type eval( __m128i const a, __m128i const b
                                        , sel<3,1,false,false> const&) const
      {
        return _mm_unpackhi_epi64(b, a);
      }
    };

    BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::shuffle_
                                      , boost::simd::tag::sse2_
                                      , (A0)(P)
                                      , ((simd_ < type32_<A0>
                                                , boost::simd::tag::sse_
                                                >
                                        ))
                                        ((simd_ < type32_<A0>
                                                , boost::simd::tag::sse_
                                                >
                                        ))
                                        (target_< unspecified_<P> >)
                                      )
    {
      typedef A0                              result_type;
      typedef typename P::type                permutation_t;

      template< int I0,int I1,int I2,int I3
              , int AorB   = (I0<4&&I1<4&&I2<4&&I3<4)
                            ? 1 : (I0>=4&&I1>=4&&I2>=4&&I3>=4)
                                    ? 2 : 0
              , bool assymetric = (AorB==0) && ((I0>3)||(I1>3)||(I2<4)||(I3<4))
              , bool Invert = (I0<4&&I1<4&&I2>=4&&I3>=4&&I0!=-1&&I1!=-1&&I2!=-1&&I3!=-1)
                            ? false : (I0>=4&&I1>=4&&I2<4&&I3<4&&I0!=-1&&I1!=-1&&I2!=-1&&I3!=-1)
                                    ? true : false
              , bool Some0  = (I0==-1) || (I1==-1) || (I2==-1) || (I3==-1)
              >
      struct sel {};

      BOOST_FORCEINLINE result_type
      operator()(A0 const& a0, A0 const& a1, P const&) const
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
        return eval(a0,a1,sel<i0_t::value,i1_t::value,i2_t::value,i3_t::value>());
      }

      template<int I0,int I1,int I2,int I3>
      BOOST_FORCEINLINE result_type eval( A0 const& a0, A0 const& a1
                                        , sel<I0,I1,I2,I3,0,true,false,false> const&) const
      {
        return dispatch::functor<tag::shuffle_, tag::cpu_>()(a0,a1,P());
      }

      template<int I0,int I1,int I2,int I3>
      BOOST_FORCEINLINE result_type eval( A0 const& a0, A0 const& a1
                                        , sel<I0,I1,I2,I3,0,true,true,false> const&) const
      {
        return dispatch::functor<tag::shuffle_, tag::cpu_>()(a0,a1,P());
      }

      template<int I0,int I1,int I2,int I3>
      BOOST_FORCEINLINE result_type eval( A0 const& a0, A0 const&
                                        , sel<I0,I1,I2,I3,1,false,false> const&) const
      {
        return shuffle<I0,I1,I2,I3>(a0);
      }

      template<int I0,int I1,int I2,int I3>
      BOOST_FORCEINLINE result_type eval( A0 const&, A0 const& a1
                                        , sel<I0,I1,I2,I3,2,false,false> const&) const
      {
        return shuffle<I0,I1,I2,I3>(a1);
      }

      BOOST_FORCEINLINE result_type eval( A0 const&, A0 const&
                                        , sel<-1,-1,-1,-1,1,false,false,true> const&) const
      {
        return Zero<result_type>();
      }

      template<int I0,int I1,int I2,int I3> BOOST_FORCEINLINE
      result_type eval( A0 const& a0, A0 const& a1
                      , sel<I0,I1,I2,I3,0,false,false,false> const&) const
      {
        return details::shuffle<I0&3, I1&3, I2&3, I3&3>(a0,a1);
      }

      template<int I0,int I1,int I2,int I3> BOOST_FORCEINLINE
      result_type eval( A0 const& a0, A0 const& a1
                      , sel<I0,I1,I2,I3,0,false,true,false> const&) const
      {
        return details::shuffle<I0&3, I1&3, I2&3, I3&3>(a1,a0);
      }

      template<int I0,int I1,int I2,int I3> BOOST_FORCEINLINE
      result_type eval( __m128 const a0, __m128 const a1
                      , sel<I0,I1,I2,I3,0,false,false,true> const&) const
      {
        typedef typename dispatch::meta::as_integer<A0,unsigned>::type i_t;
        // Mask the shuffled equivalent
        return  simd::bitwise_and
                ( eval( a0, a1, sel< I0<0?0:I0,I1<0?0:I1,I2<0?0:I2,I3<0?0:I3
                                   >() )
                , simd::make<i_t> ( -int(I0>=0), -int(I1>=0)
                                  , -int(I2>=0), -int(I3>=0)
                                  )
                );
      }

      template<int I0,int I1,int I2,int I3> BOOST_FORCEINLINE
      result_type eval( __m128 const a0, __m128 const a1
                      , sel<I0,I1,I2,I3,0,false,true,true> const&) const
      {
        typedef typename dispatch::meta::as_integer<A0,unsigned>::type i_t;
        // Mask the shuffled equivalent
        return  simd::bitwise_and
                ( eval( a0, a1, sel< I0<0?0:I0,I1<0?0:I1,I2<0?0:I2,I3<0?0:I3
                                   >() )
                , simd::make<i_t> ( -int(I0>=0), -int(I1>=0)
                                  , -int(I2>=0), -int(I3>=0)
                                  )
                );
      }

      template<int I0,int I1,int I2,int I3> BOOST_FORCEINLINE
      result_type eval( __m128 const a0, __m128 const a1
                      , sel<I0,I1,I2,I3,0,true,false,true> const&) const
      {
        typedef typename dispatch::meta::as_integer<A0,unsigned>::type i_t;
        // Mask the shuffled equivalent
        return  simd::bitwise_and
                ( eval( a0, a1, sel< I0<0?0:I0,I1<0?0:I1,I2<0?0:I2,I3<0?0:I3
                                   >() )
                , simd::make<i_t> ( -int(I0>=0), -int(I1>=0)
                                  , -int(I2>=0), -int(I3>=0)
                                  )
                );
      }

      template<int I0,int I1,int I2,int I3> BOOST_FORCEINLINE
      result_type eval( __m128 const a0, __m128 const a1
                      , sel<I0,I1,I2,I3,0,true,true,true> const&) const
      {
        typedef typename dispatch::meta::as_integer<A0,unsigned>::type i_t;
        // Mask the shuffled equivalent
        return  simd::bitwise_and
                ( eval( a0, a1, sel< I0<0?0:I0,I1<0?0:I1,I2<0?0:I2,I3<0?0:I3
                                   >() )
                , simd::make<i_t> ( -int(I0>=0), -int(I1>=0)
                                  , -int(I2>=0), -int(I3>=0)
                                  )
                );
      }

      template<int I0,int I1,int I2,int I3> BOOST_FORCEINLINE
      result_type eval( __m128i const a0, __m128i const a1
                      , sel<I0,I1,I2,I3,0,false,false,true> const&) const
      {
        typedef typename dispatch::meta::as_integer<A0,unsigned>::type i_t;
        // Mask the shuffled equivalent
        return  simd::bitwise_and
                ( eval( a0, a1, sel< I0<0?0:I0,I1<0?0:I1,I2<0?0:I2,I3<0?0:I3
                                   >() )
                , simd::make<i_t> ( -int(I0>=0), -int(I1>=0)
                                  , -int(I2>=0), -int(I3>=0)
                                  )
                );
      }

      template<int I0,int I1,int I2,int I3> BOOST_FORCEINLINE
      result_type eval( __m128i const a0, __m128i const a1
                      , sel<I0,I1,I2,I3,0,false,true,true> const&) const
      {
        typedef typename dispatch::meta::as_integer<A0,unsigned>::type i_t;
        // Mask the shuffled equivalent
        return  simd::bitwise_and
                ( eval( a0, a1, sel< I0<0?0:I0,I1<0?0:I1,I2<0?0:I2,I3<0?0:I3
                                   >() )
                , simd::make<i_t> ( -int(I0>=0), -int(I1>=0)
                                  , -int(I2>=0), -int(I3>=0)
                                  )
                );
      }

      template<int I0,int I1,int I2,int I3> BOOST_FORCEINLINE
      result_type eval( __m128i const a0, __m128i const a1
                      , sel<I0,I1,I2,I3,0,true,false,true> const&) const
      {
        typedef typename dispatch::meta::as_integer<A0,unsigned>::type i_t;
        // Mask the shuffled equivalent
        return  simd::bitwise_and
                ( eval( a0, a1, sel< I0<0?0:I0,I1<0?0:I1,I2<0?0:I2,I3<0?0:I3
                                   >() )
                , simd::make<i_t> ( -int(I0>=0), -int(I1>=0)
                                  , -int(I2>=0), -int(I3>=0)
                                  )
                );
      }

      template<int I0,int I1,int I2,int I3> BOOST_FORCEINLINE
      result_type eval( __m128i const a0, __m128i const a1
                      , sel<I0,I1,I2,I3,0,true,true,true> const&) const
      {
        typedef typename dispatch::meta::as_integer<A0,unsigned>::type i_t;
        // Mask the shuffled equivalent
        return  simd::bitwise_and
                ( eval( a0, a1, sel< I0<0?0:I0,I1<0?0:I1,I2<0?0:I2,I3<0?0:I3
                                   >() )
                , simd::make<i_t> ( -int(I0>=0), -int(I1>=0)
                                  , -int(I2>=0), -int(I3>=0)
                                  )
                );
      }

      BOOST_FORCEINLINE
      result_type eval( __m128 const a0, __m128 const a1
                      , sel<0,1,4,5,0,false,false,false> const&) const
      {
        return _mm_movelh_ps(a0,a1);
      }

      BOOST_FORCEINLINE
      result_type eval( __m128 const a0, __m128 const a1
                      , sel<2,3,6,7,0,false,false,false> const&) const
      {
        return _mm_movehl_ps(a1,a0);
      }

      BOOST_FORCEINLINE
      result_type eval( __m128 const a0, __m128 const a1
                      , sel<4,5,0,1,0,false,true,false> const&) const
      {
        return _mm_movelh_ps(a1,a0);
      }

      BOOST_FORCEINLINE
      result_type eval( __m128 const a0, __m128 const a1
                      , sel<6,7,2,3,0,false,true,false> const&) const
      {
        return _mm_movehl_ps(a1,a0);
      }

      BOOST_FORCEINLINE
      result_type eval( __m128 const a0, __m128 const a1
                      , sel<-1,-1,0,1,1,false,false,true> const&) const
      {
        return _mm_movelh_ps(Zero<result_type>(),a0);
      }

      BOOST_FORCEINLINE
      result_type eval( __m128 const a0, __m128 const a1
                      , sel<-1,-1,4,5,0,false,false,true> const&) const
      {
        return _mm_movelh_ps(Zero<result_type>(),a1);
      }

      BOOST_FORCEINLINE
      result_type eval( __m128 const a0, __m128 const a1
                      , sel<-1,-1,2,3,1,false,false,true> const&) const
      {
        return _mm_movehl_ps(Zero<result_type>(),a0);
      }

      BOOST_FORCEINLINE
      result_type eval( __m128 const a0, __m128 const a1
                      , sel<-1,-1,6,7,0,false,false,true> const&) const
      {
        return _mm_movehl_ps(a1,Zero<result_type>());
      }

      BOOST_FORCEINLINE
      result_type eval( __m128 const a0, __m128 const a1
                      , sel<0,1,-1,-1,1,false,false,true> const&) const
      {
        return _mm_movelh_ps(a0,Zero<result_type>());
      }

      BOOST_FORCEINLINE
      result_type eval( __m128 const a0, __m128 const a1
                      , sel<4,5,-1,-1,0,false,false,true> const&) const
      {
        return _mm_movelh_ps(a1,Zero<result_type>());
      }

      BOOST_FORCEINLINE
      result_type eval( __m128 const a0, __m128 const a1
                      , sel<2,3,-1,-1,1,false,false,true> const&) const
      {
        return _mm_movehl_ps(a0,Zero<result_type>());
      }

      BOOST_FORCEINLINE
      result_type eval( __m128 const a0, __m128 const a1
                      , sel<6,7,-1,-1,0,false,false,true> const&) const
      {
        return _mm_movehl_ps(a1,Zero<result_type>());
      }

      BOOST_FORCEINLINE
      result_type eval( __m128 const a0, __m128 const a1
                      , sel<0,4,1,5,0,false,false,false> const&) const
      {
        return _mm_unpacklo_ps(a0,a1);
      }

      BOOST_FORCEINLINE
      result_type eval( __m128 const a0, __m128 const a1
                      , sel<2,6,3,7,0,false,false,false> const&) const
      {
        return _mm_unpackhi_ps(a0,a1);
      }

      BOOST_FORCEINLINE
      result_type eval( __m128 const a0, __m128 const a1
                      , sel<4,0,5,1,0,false,false,false> const&) const
      {
        return _mm_unpacklo_ps(a1,a0);
      }

      BOOST_FORCEINLINE
      result_type eval( __m128 const a0, __m128 const a1
                      , sel<6,2,7,3,0,false,false,false> const&) const
      {
        return _mm_unpackhi_ps(a1,a0);
      }

      BOOST_FORCEINLINE
      result_type eval( __m128 const a0, __m128 const a1
                      , sel<0,-1,1,-1,1,false,true> const&) const
      {
        return _mm_unpacklo_ps(a0,Zero<result_type>());
      }

      BOOST_FORCEINLINE
      result_type eval( __m128 const a0, __m128 const a1
                      , sel<4,-1,5,-1,0,false,true> const&) const
      {
        return _mm_unpacklo_ps(a1,Zero<result_type>());
      }

      BOOST_FORCEINLINE
      result_type eval( __m128 const a0, __m128 const a1
                      , sel<2,-1,3,-1,1,false,true> const&) const
      {
        return _mm_unpackhi_ps(a0,Zero<result_type>());

      }

      BOOST_FORCEINLINE
      result_type eval( __m128 const a0, __m128 const a1
                      , sel<6,-1,7,-1,0,false,true> const&) const
      {
        return _mm_unpackhi_ps(a1,Zero<result_type>());

      }

      BOOST_FORCEINLINE
      result_type eval( __m128 const a0, __m128 const a1
                      , sel<-1,0,-1,1,1,false,true> const&) const
      {
        return _mm_unpacklo_ps(Zero<result_type>(),a0);
      }

      BOOST_FORCEINLINE
      result_type eval( __m128 const a0, __m128 const a1
                      , sel<-1,4,-1,5,0,false,true> const&) const
      {
        return _mm_unpacklo_ps(Zero<result_type>(),a1);
      }

      BOOST_FORCEINLINE
      result_type eval( __m128 const a0, __m128 const a1
                      , sel<-1,2,-1,3,1,false,true> const&) const
      {
        return _mm_unpackhi_ps(Zero<result_type>(),a0);
      }

      BOOST_FORCEINLINE
      result_type eval( __m128 const a0, __m128 const a1
                      , sel<-1,6,-1,7,0,false,true> const&) const
      {
        return _mm_unpackhi_ps(Zero<result_type>(),a1);
      }
    };
  }
} }

#endif
#endif
