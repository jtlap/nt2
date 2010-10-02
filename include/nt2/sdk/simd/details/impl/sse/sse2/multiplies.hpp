//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_SDK_SIMD_DETAILS_IMPL_SSE_SSE2_MULTIPLIES_HPP_INCLUDED
#define NT2_SDK_SIMD_DETAILS_IMPL_SSE_SSE2_MULTIPLIES_HPP_INCLUDED

#include <nt2/sdk/meta/strip.hpp>
#include <nt2/sdk/meta/scalar_of.hpp>
#include <nt2/sdk/simd/native_cast.hpp>

namespace nt2 { namespace functors
{
  template<class Info>
  struct call<multiplies_,tag::simd_(tag::arithmetic_,tag::sse_),Info>
  {
    template<class Sig> struct result;
    template<class This,class A>
    struct result<This(A,A)> : meta::strip<A> {};

    NT2_FUNCTOR_CALL_DISPATCH ( 2
                              , typename nt2::meta::scalar_of<A0>::type
                              , (7, ( double,float
                                    , int8_,int16_,int32_t,uint32_t
                                    , arithmetic_
                                )   )
                              )

    NT2_FUNCTOR_CALL_EVAL_IF(2,double)
    {
      A0 that = { _mm_mul_pd(a0,a1) };
      return that;
    }

    NT2_FUNCTOR_CALL_EVAL_IF(2,float )
    {
      A0 that = { _mm_mul_ps(a0,a1) };
      return that;
    }

    NT2_FUNCTOR_CALL_EVAL_IF(2,uint32_t)
    {
      A0 that =  { _mm_mul_epu32(a0, a1) };
      return that;
    }

    NT2_FUNCTOR_CALL_EVAL_IF(2,int16_)
    {
      A0 that = { _mm_mullo_epi16(a0,a1) };
      return that;
    }

    NT2_FUNCTOR_CALL_EVAL_IF(2,arithmetic_)
    {
      A0 that = map(functor<multiplies_>(), a0, a1);
      return that;
    }

    NT2_FUNCTOR_CALL_EVAL_IF(2,int8_)
    {
      typedef typename meta::make_integer < 2,signed
                                          , simd::native< boost::mpl::_
                                                        , tag::sse_
                                                        >
                                          >::type             type;

      type mask1 = integral_constant<type,0x00FF>();
      type a0_16 = {a0};
      type a1_16 = {a1};
      type al    = {_mm_srli_epi16(a0_16, 8)};
      type bl    = {_mm_srli_epi16(a1_16, 8)};
      type abh   = {_mm_and_si128(mask1, _mm_mullo_epi16(a0,a1))};
      type ab    = {_mm_mullo_epi16(al,bl)};
      type abl   = {_mm_slli_epi16(_mm_and_si128(mask1, ab), 8)};
      A0 r       = { abh | abl };
      return r;
    }

    NT2_FUNCTOR_CALL_EVAL_IF(2,int32_t)
    {
      A0 that = { _mm_or_si128(
                    _mm_and_si128 (
                       _mm_mul_epu32(a0,a1),
                       _mm_setr_epi32(0xffffffff,0,0xffffffff,0)
                                  )
                  , _mm_slli_si128(
                        _mm_and_si128 (
                            _mm_mul_epu32 ( _mm_srli_si128(a0,4)
                                          , _mm_srli_si128(a1,4)
                                          )
                          , _mm_setr_epi32(0xffffffff,0,0xffffffff,0)
                                      )
                        , 4       )
                              )
                };
      return that;
    }
  };
} }

#endif

