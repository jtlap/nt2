/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_SIMD_DETAILS_IMPL_SSE_SSE2_MINUS_HPP_INCLUDED
#define NT2_SDK_SIMD_DETAILS_IMPL_SSE_SSE2_MINUS_HPP_INCLUDED

#include <nt2/sdk/meta/strip.hpp>

namespace nt2 { namespace functors
{
  template<class Info>
  struct call<minus_,tag::simd_(tag::arithmetic_,tag::sse_),Info>
  {
    template<class Sig> struct result;
    template<class This,class A>
    struct result<This(A,A)> : meta::strip<A> {};

    NT2_FUNCTOR_CALL_DISPATCH( 2
                             , typename nt2::meta::scalar_of<A0>::type
                             , (6,(double,float,int8_,int16_,int32_,int64_))
                             )

    NT2_FUNCTOR_CALL_EVAL_IF(2,double) { A0 that = { _mm_sub_pd(a0,a1)    }; return that; }
    NT2_FUNCTOR_CALL_EVAL_IF(2,float ) { A0 that = { _mm_sub_ps(a0,a1)    }; return that; }
    NT2_FUNCTOR_CALL_EVAL_IF(2,int64_) { A0 that = { _mm_sub_epi64(a0,a1) }; return that; }
    NT2_FUNCTOR_CALL_EVAL_IF(2,int32_) { A0 that = { _mm_sub_epi32(a0,a1) }; return that; }
    NT2_FUNCTOR_CALL_EVAL_IF(2,int16_) { A0 that = { _mm_sub_epi16(a0,a1) }; return that; }
    NT2_FUNCTOR_CALL_EVAL_IF(2,int8_ ) { A0 that = { _mm_sub_epi8(a0,a1)  }; return that; }
  };
} }

#endif
