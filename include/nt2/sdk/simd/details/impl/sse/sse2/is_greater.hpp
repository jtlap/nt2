/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_SIMD_NATIVE_DETAILS_IMPL_SSE_SSE2_GREATER_HPP_INCLUDED
#define NT2_SDK_SIMD_NATIVE_DETAILS_IMPL_SSE_SSE2_GREATER_HPP_INCLUDED

#include <nt2/sdk/meta/strip.hpp>
#include <nt2/sdk/meta/scalar_of.hpp>
#include <nt2/sdk/simd/native_cast.hpp>
#include <nt2/sdk/meta/make_integer.hpp>

namespace nt2 { namespace functors
{
  template<class Info>
  struct call<is_greater_,tag::simd_(tag::arithmetic_,tag::sse_),Info>
  {
    template<class Sig> struct result;
    template<class This,class A>
    struct result<This(A,A)> : meta::strip<A> {};

    NT2_FUNCTOR_CALL_DISPATCH( 2
                             , typename nt2::meta::scalar_of<A0>::type
                             , (7,( double,float
                                  , int8_t,int16_t,int32_t,int64_t
                                  , uint_
                                ) )
                             )

    NT2_FUNCTOR_CALL_EVAL_IF(2,double)
    {
      A0 that = { _mm_cmpgt_pd(a0,a1) };
      return that;
    }

    NT2_FUNCTOR_CALL_EVAL_IF(2,float )
    {
      A0 that = { _mm_cmpgt_ps(a0,a1) };
      return that;
    }

    NT2_FUNCTOR_CALL_EVAL_IF(2,int8_t)
    {
      A0 that = { _mm_cmpgt_epi8(a0,a1)  };
      return that;
    }

    NT2_FUNCTOR_CALL_EVAL_IF(2,int16_t)
    {
      A0 that = { _mm_cmpgt_epi16(a0,a1) };
      return that;
    }

    NT2_FUNCTOR_CALL_EVAL_IF(2,int32_t)
    {
      A0 that = { _mm_cmpgt_epi32(a0,a1) };
      return that;
    }

    NT2_FUNCTOR_CALL_EVAL_IF(2, uint_)
    {
      typedef typename meta::as_integer<A0, signed>::type stype;
      stype tmp1 = simd::native_cast<stype>(a0) - Signmask<stype>();
      stype tmp2 = simd::native_cast<stype>(a1) - Signmask<stype>();
      stype tmp = gt(tmp1,tmp2);
      return simd::native_cast<A0>(tmp);
    }

    NT2_FUNCTOR_CALL_EVAL_IF(2,int64_t)
    {
      typedef typename meta::make_integer < 4, signed
                                          , simd::native< boost::mpl::_
                                                        , tag::sse_
                                                        >
                                          >::type type;
      type sa0 = { a0 };
      type sa1 = { a1 };

      type al = { _mm_shuffle_epi32(sa0, _MM_SHUFFLE(2, 2, 0, 0)) };
      type bl = { _mm_shuffle_epi32(sa1, _MM_SHUFFLE(2, 2, 0, 0)) };
      type ah = { _mm_shuffle_epi32(sa0, _MM_SHUFFLE(3, 3, 1, 1)) };
      type bh = { _mm_shuffle_epi32(sa1, _MM_SHUFFLE(3, 3, 1, 1)) };

      A0 that = { gt(ah,bh) | (eq(ah,bh) & gt(al,bl)) };
      return that;
    }
  };
} }

#endif
