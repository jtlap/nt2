/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_SIMD_DETAILS_IMPL_SSE_SSE2_DIVIDES_HPP_INCLUDED
#define NT2_SDK_SIMD_DETAILS_IMPL_SSE_SSE2_DIVIDES_HPP_INCLUDED

#include <nt2/sdk/meta/strip.hpp>

namespace nt2 { namespace functors
{
  template<class Info>
  struct  call<divides_,tag::simd_(tag::arithmetic_,tag::sse_),double,Info>
        : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0,A1)> : meta::strip<A0> {};

    NT2_FUNCTOR_CALL(2)
    {
      A0 that =  { _mm_div_pd(a0, a1) };
      return that;
    }
  };

  template<class Info>
  struct  call<divides_,tag::simd_(tag::arithmetic_,tag::sse_),float,Info>
        : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0,A1)> : meta::strip<A0> {};

    NT2_FUNCTOR_CALL(2)
    {
      A0 that =  { _mm_div_ps(a0, a1) };
      return that;
    }
  };

  template<class Info>
  struct  call< divides_, tag::simd_(tag::arithmetic_,tag::sse_)
              , arithmetic_ , Info
              >
        : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0,A1)> : meta::strip<A0> {};

    NT2_FUNCTOR_CALL(2)
    {
      A0 that;
      that = map(functor<divides_>(), a0, a1);
      return that;
    }
  };
} }

#endif

