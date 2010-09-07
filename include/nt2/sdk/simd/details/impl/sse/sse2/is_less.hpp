/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_SIMD_NATIVE_DETAILS_IMPL_SSE_SSE2_IS_LESS_HPP_INCLUDED
#define NT2_SDK_SIMD_NATIVE_DETAILS_IMPL_SSE_SSE2_IS_LESS_HPP_INCLUDED

#include <nt2/sdk/meta/strip.hpp>
#include <nt2/sdk/meta/scalar_of.hpp>
#include <nt2/sdk/simd/native_cast.hpp>
#include <nt2/sdk/meta/make_integer.hpp>
#include <nt2/sdk/constant/properties.hpp>

namespace nt2 { namespace functors
{
  template<class Info>
  struct call<is_less_,tag::simd_(tag::arithmetic_,tag::sse_),Info>
  {
    template<class Sig> struct result;
    template<class This,class A>
    struct result<This(A,A)> : meta::strip<A> {};

    NT2_FUNCTOR_CALL_DISPATCH( 2
                             , typename nt2::meta::scalar_of<A0>::type
                             , (7,(double,float,uint_,int8_,int16_,int32_,int64_))
                             )

    NT2_FUNCTOR_CALL_EVAL_IF(2, uint_)
    {
      typedef typename meta::as_integer<A0, signed>::type stype;
      stype tmp1 = simd::native_cast<stype>(a0)-Signmask<stype>();
      stype tmp2 = simd::native_cast<stype>(a1)-Signmask<stype>();
      stype tmp  = lt(tmp1,tmp2);
      return simd::native_cast<A0>(tmp);
    }

    NT2_FUNCTOR_CALL_EVAL_IF(2,double)
    {
      A0 that = { _mm_cmplt_pd(a0,a1) };
      return that;
    }

    NT2_FUNCTOR_CALL_EVAL_IF(2,float )
    {
      A0 that = { _mm_cmplt_ps(a0,a1) };
      return that;
    }

    NT2_FUNCTOR_CALL_EVAL_IF(2,int8_)
    {
      A0 that = { _mm_cmplt_epi8(a0,a1) };
      return that;
    }

    NT2_FUNCTOR_CALL_EVAL_IF(2,int16_)
    {
      A0 that = { _mm_cmplt_epi16(a0,a1) };
      return that;
    }

    NT2_FUNCTOR_CALL_EVAL_IF(2,int32_)
    {
      A0 that = { _mm_cmplt_epi32(a0,a1) };
      return that;
    }

    NT2_FUNCTOR_CALL_EVAL_IF(2,int64_)
    {
      typedef typename meta::scalar_of<A0>::type stype;
      typedef typename meta::make_integer <  4, signed
                                          , simd::native< boost::mpl::_
                                                        , tag::sse_
                                                        >
                                          >::type type;
      type sa0 = { a0 };
      type sa1 = { a1 };

      type al = {_mm_shuffle_epi32(sa0, _MM_SHUFFLE(2, 2, 0, 0))};
      type bl = {_mm_shuffle_epi32(sa1, _MM_SHUFFLE(2, 2, 0, 0))};
      type ah = {_mm_shuffle_epi32(sa0, _MM_SHUFFLE(3, 3, 1, 1))};
      type bh = {_mm_shuffle_epi32(sa1, _MM_SHUFFLE(3, 3, 1, 1))};
      A0 that = { lt(ah, bh) | (eq(ah,bh) & lt(al,bl)) };
      return that;
    }
  };
} }

#endif
