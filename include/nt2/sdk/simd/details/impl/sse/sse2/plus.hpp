/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_SIMD_DETAILS_IMPL_SSE_SSE2_PLUS_HPP_INCLUDED
#define NT2_SDK_SIMD_DETAILS_IMPL_SSE_SSE2_PLUS_HPP_INCLUDED

#include <nt2/sdk/meta/strip.hpp>

namespace nt2 { namespace functors
{
  template<class Info>
  struct  call<plus_,tag::simd_(tag::arithmetic_,tag::sse_),double,Info>
        : callable
  {
    template<class Sig> struct result;
    template<class This,class A> struct result<This(A,A)> : meta::strip<A> {};

    NT2_FUNCTOR_CALL(2) { A0 that = { _mm_add_pd(a0,a1)    }; return that; }
  };

  template<class Info>
  struct  call<plus_,tag::simd_(tag::arithmetic_,tag::sse_),float,Info>
        : callable
  {
    template<class Sig> struct result;
    template<class This,class A> struct result<This(A,A)> : meta::strip<A> {};

    NT2_FUNCTOR_CALL(2) { A0 that = { _mm_add_ps(a0,a1)    }; return that; }
  };

  template<class Info>
  struct  call<plus_,tag::simd_(tag::arithmetic_,tag::sse_),int8_,Info>
        : callable
  {
    template<class Sig> struct result;
    template<class This,class A> struct result<This(A,A)> : meta::strip<A> {};

    NT2_FUNCTOR_CALL(2) { A0 that = { _mm_add_epi8(a0,a1)  }; return that; }
  };

    template<class Info>
  struct  call<plus_,tag::simd_(tag::arithmetic_,tag::sse_),int16_,Info>
        : callable
  {
    template<class Sig> struct result;
    template<class This,class A> struct result<This(A,A)> : meta::strip<A> {};

    NT2_FUNCTOR_CALL(2) { A0 that = { _mm_add_epi16(a0,a1) }; return that; }
  };

    template<class Info>
  struct  call<plus_,tag::simd_(tag::arithmetic_,tag::sse_),int32_,Info>
        : callable
  {
    template<class Sig> struct result;
    template<class This,class A> struct result<This(A,A)> : meta::strip<A> {};

    NT2_FUNCTOR_CALL(2) { A0 that = { _mm_add_epi32(a0,a1) }; return that; }
  };

    template<class Info>
  struct  call<plus_,tag::simd_(tag::arithmetic_,tag::sse_),int64_,Info>
        : callable
  {
    template<class Sig> struct result;
    template<class This,class A> struct result<This(A,A)> : meta::strip<A> {};

    NT2_FUNCTOR_CALL(2) { A0 that = { _mm_add_epi64(a0,a1) }; return that; }
  };
} }

#endif
