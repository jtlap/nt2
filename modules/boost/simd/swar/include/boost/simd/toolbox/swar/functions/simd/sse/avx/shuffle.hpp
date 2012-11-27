//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_SWAR_FUNCTIONS_SIMD_SSE_AVX_SHUFFLE_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_SWAR_FUNCTIONS_SIMD_SSE_AVX_SHUFFLE_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_AVX_SUPPORT
#include <boost/simd/toolbox/swar/functions/shuffle.hpp>
#include <boost/simd/toolbox/swar/functions/details/shuffle.hpp>
#include <boost/simd/toolbox/swar/functions/details/perm.hpp>
#include <boost/simd/toolbox/operator/functions/bitwise_cast.hpp>
#include <boost/simd/toolbox/operator/functions/bitwise_and.hpp>
#include <boost/simd/include/constants/zero.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/mpl/integral_c.hpp>
#include <boost/mpl/range_c.hpp>
#include <boost/mpl/contains.hpp>
#include <boost/mpl/transform.hpp>
#include <boost/mpl/copy.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/back_inserter.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/apply_wrap.hpp>

namespace boost { namespace simd
{
  namespace ext
  {
    BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::shuffle_
                                      , boost::simd::tag::avx_
                                      , (A0)(P)
                                      , ((simd_ < type64_<A0>
                                                , boost::simd::tag::avx_
                                                >
                                        ))
                                        (target_< unspecified_<P> >)
                                      )
    {
      typedef A0                                     result_type;
      typedef typename meta::scalar_of<A0>::type     scalar_t;
      typedef P                                      permutation_t;
      typedef typename P::type                       permutation_t_;
      typedef meta::cardinal_of<result_type>         card_t;
      typedef mpl::vector<>                          empty_t;
      typedef typename mpl::copy< mpl::range_c<int,0,card_t::value>
                                , mpl::back_inserter<empty_t> 
                                >::type range_t;

      typedef typename mpl::transform< range_t
                                     , mpl::apply_wrap2< typename 
                                                         permutation_t::type
                                                       , mpl::_1
                                                       , card_t
                                                       >
                                     >::type result_t;

      template<std::size_t I>
      struct mask_t
      {
        static const 
        char value =  mpl::if_< mpl::equal_to< typename 
                                               mpl::
                                               at< result_t
                                                 , mpl::size_t<I/sizeof(scalar_t)> 
                                                 >::type
                                             , mpl::int_<-1> 
                                             >
                              , mpl::char_<0x00>
                              , mpl::char_<0xFF>
                              >::type::value; 
      };

      template< int I0,int I1,int I2,int I3
              , bool NoNull = (I0 != -1) && (I1 !=-1) && (I2 != -1) && (I3 !=-1)
              > struct sel {};

      BOOST_FORCEINLINE result_type operator()(A0 const& a0,P const&) const
      {
        typedef typename boost::mpl::apply< permutation_t_
                                          , boost::mpl::int_<0>
                                          , boost::mpl::int_<4>
                                          >::type               i0_t;
        typedef typename boost::mpl::apply< permutation_t_
                                          , boost::mpl::int_<1>
                                          , boost::mpl::int_<4>
                                          >::type               i1_t;
        typedef typename boost::mpl::apply< permutation_t_
                                          , boost::mpl::int_<2>
                                          , boost::mpl::int_<4>
                                          >::type               i2_t;
        typedef typename boost::mpl::apply< permutation_t_
                                          , boost::mpl::int_<3>
                                          , boost::mpl::int_<4>
                                          >::type               i3_t;

        return eval(a0,sel<i0_t::value,i1_t::value,i2_t::value,i3_t::value>());
      }

      BOOST_FORCEINLINE result_type eval(A0 const& a0, sel<0,1,2,3> const&) const
      {
        return a0;
      }

      BOOST_FORCEINLINE result_type eval(A0 const& , sel<-1,-1,-1,-1> const&) const
      {
        return Zero<result_type>();
      }

      template<int I0, int I1>
      BOOST_FORCEINLINE __m256d eval(__m256d a0, sel<I0,I1,-1,-1> const&) const
      {
        return details::shuffle<I0,I1,0,1>(a0,Zero<result_type>());
      }

      template<int I2, int I3>
      BOOST_FORCEINLINE __m256d eval(__m256d a0, sel<-1,-1,I2,I3> const&) const
      {
        return details::shuffle<0,1,I2,I3>(Zero<result_type>(), a0);
      }

      template<int I0, int I1, int I2, int I3>
      BOOST_FORCEINLINE __m256d eval(__m256d a0, sel<I0,I1,I2,I3,true> const&) const
      {
        return details::shuffle<I0,I1,I2,I3>(a0);
      }

      template<int I0, int I1, int I2, int I3>
      BOOST_FORCEINLINE __m256i eval(__m256i a0, sel<I0,I1,I2,I3,true> const&) const
      {
        return details::shuffle<I0,I1,I2,I3>(a0,a0);
      }

      template<int I0, int I1, int I2, int I3>
      BOOST_FORCEINLINE __m256d eval(__m256d a0, sel<I0,I1,I2,I3,false> const&) const
      {
        __m256i mask = _mm256_set_epi8(
                         mask_t<0 >::value, mask_t<1 >::value
                       , mask_t<2 >::value, mask_t<3 >::value
                       , mask_t<4 >::value, mask_t<5 >::value
                       , mask_t<6 >::value, mask_t<7 >::value
                       , mask_t<8 >::value, mask_t<9 >::value
                       , mask_t<10>::value, mask_t<11>::value
                       , mask_t<12>::value, mask_t<13>::value
                       , mask_t<14>::value, mask_t<15>::value
                       , mask_t<16>::value, mask_t<17>::value
                       , mask_t<18>::value, mask_t<19>::value
                       , mask_t<20>::value, mask_t<21>::value
                       , mask_t<22>::value, mask_t<23>::value
                       , mask_t<24>::value, mask_t<25>::value
                       , mask_t<26>::value, mask_t<27>::value
                       , mask_t<28>::value, mask_t<29>::value
                       , mask_t<30>::value, mask_t<31>::value
                       );
        __m256d that = details::shuffle<I0,I1,I2,I3>(a0);
        return _mm256_and_pd(_mm256_castsi256_pd(mask),that);
      }

      template<int I0, int I1, int I2, int I3>
      BOOST_FORCEINLINE __m256i eval(__m256i a0, sel<I0,I1,I2,I3,false> const&) const
      {
        return _mm256_castpd_si256(eval(_mm256_castsi256_pd(a0),sel<I0,I1,I2,I3,false>()));
      }

      BOOST_FORCEINLINE __m256d eval(__m256d a0, sel<0,-1, 2,-1> const&) const
      {
        return _mm256_unpacklo_pd(a0, Zero<result_type>());
      }

      BOOST_FORCEINLINE __m256d eval(__m256d a0, sel<-1,5,-1,7> const&) const
      {
        return _mm256_unpackhi_pd(a0, Zero<result_type>());
      }
    };

    BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::shuffle_
                                      , boost::simd::tag::avx_
                                      , (A0)(P)
                                      , ((simd_ < type64_<A0>
                                                , boost::simd::tag::avx_
                                                >
                                        ))
                                        ((simd_ < type64_<A0>
                                                , boost::simd::tag::avx_
                                                >
                                        ))
                                        (target_< unspecified_<P> >)
                                      )
    {
      typedef A0                                     result_type;
      typedef typename meta::scalar_of<A0>::type     scalar_t;
      typedef P                                      permutation_t;
      typedef typename P::type                       permutation_t_;
      typedef meta::cardinal_of<result_type>         card_t;
      typedef mpl::vector<>                          empty_t;
      typedef typename mpl::copy< mpl::range_c<int,0,card_t::value>
                                , mpl::back_inserter<empty_t> 
                                >::type range_t;

      typedef typename mpl::transform< range_t
                                     , mpl::apply_wrap2< typename 
                                                         permutation_t::type
                                                       , mpl::_1
                                                       , card_t
                                                       >
                                     >::type result_t;

      template<std::size_t I>
      struct mask_t
      {
        static const 
        char value =  mpl::if_< mpl::equal_to< typename 
                                               mpl::
                                               at< result_t
                                                 , mpl::size_t<I/sizeof(scalar_t)> 
                                                 >::type
                                             , mpl::int_<-1> 
                                             >
                              , mpl::char_<0x00>
                              , mpl::char_<0xFF>
                              >::type::value; 
      };

      template< int I0,int I1,int I2,int I3
              , bool NoNull = (I0 != -1) && (I1 !=-1) && (I2 != -1) && (I3 !=-1)
              > struct sel {};

      BOOST_FORCEINLINE result_type operator()( A0 const& a0
                                              , A0 const& a1
                                              , P const&) const
      {
        typedef typename boost::mpl::apply< permutation_t_
                                          , boost::mpl::int_<0>
                                          , boost::mpl::int_<4>
                                          >::type               i0_t;
        typedef typename boost::mpl::apply< permutation_t_
                                          , boost::mpl::int_<1>
                                          , boost::mpl::int_<4>
                                          >::type               i1_t;
        typedef typename boost::mpl::apply< permutation_t_
                                          , boost::mpl::int_<2>
                                          , boost::mpl::int_<4>
                                          >::type               i2_t;
        typedef typename boost::mpl::apply< permutation_t_
                                          , boost::mpl::int_<3>
                                          , boost::mpl::int_<4>
                                          >::type               i3_t;

        return eval(a0,sel<i0_t::value,i1_t::value,i2_t::value,i3_t::value>());
      }

      template<int I0, int I1, int I2, int I3>
      BOOST_FORCEINLINE __m256d eval(__m256d a0, __m256d a1, sel<I0,I1,I2,I3,true> const&) const
      {
        return details::shuffle<I0,I1,I2,I3>(a0,a1);
      }

      template<int I0, int I1, int I2, int I3>
      BOOST_FORCEINLINE __m256i eval(__m256i a0, __m256i a1, sel<I0,I1,I2,I3,true> const&) const
      {
        return details::shuffle<I0,I1,I2,I3>(a0,a1);
      }

      template<int I0, int I1, int I2, int I3>
      BOOST_FORCEINLINE __m256d eval(__m256d a0, __m256d a1, sel<I0,I1,I2,I3,false> const&) const
      {
        __m256i mask = _mm256_set_epi8(
                         mask_t<0 >::value, mask_t<1 >::value
                       , mask_t<2 >::value, mask_t<3 >::value
                       , mask_t<4 >::value, mask_t<5 >::value
                       , mask_t<6 >::value, mask_t<7 >::value
                       , mask_t<8 >::value, mask_t<9 >::value
                       , mask_t<10>::value, mask_t<11>::value
                       , mask_t<12>::value, mask_t<13>::value
                       , mask_t<14>::value, mask_t<15>::value
                       , mask_t<16>::value, mask_t<17>::value
                       , mask_t<18>::value, mask_t<19>::value
                       , mask_t<20>::value, mask_t<21>::value
                       , mask_t<22>::value, mask_t<23>::value
                       , mask_t<24>::value, mask_t<25>::value
                       , mask_t<26>::value, mask_t<27>::value
                       , mask_t<28>::value, mask_t<29>::value
                       , mask_t<30>::value, mask_t<31>::value
                       );
        __m256d that = details::shuffle<I0,I1,I2,I3>(a0,a1);
        return _mm256_and_pd(_mm256_castsi256_pd(mask),that);
      }

      template<int I0, int I1, int I2, int I3>
      BOOST_FORCEINLINE __m256i eval(__m256i a0, __m256i a1, sel<I0,I1,I2,I3,false> const&) const
      {
        return _mm256_castpd_si256(eval( _mm256_castsi256_pd(a0)
                                       , _mm256_castsi256_pd(a1)
                                       ,sel<I0,I1,I2,I3,false>()
                                       )
                                  );
      }
    };
  }
} }

#endif
#endif
