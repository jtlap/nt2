//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_SDK_SIMD_DETAILS_IMPL_SSE_SSE2_IS_LESS_EQUAL_HPP_INCLUDED
#define NT2_SDK_SIMD_DETAILS_IMPL_SSE_SSE2_IS_LESS_EQUAL_HPP_INCLUDED

#include <nt2/sdk/meta/strip.hpp>
#include <nt2/sdk/meta/scalar_of.hpp>

namespace nt2 { namespace functors
{
  template<class Info>
  struct  call< is_less_equal_, tag::simd_(tag::arithmetic_,tag::sse_)
              , double        , Info
              >
        : callable
  {
    template<class Sig> struct result;
    template<class This,class A> struct result<This(A,A)> : meta::strip<A> {};

    NT2_FUNCTOR_CALL(2)
    {
      A0 that = { _mm_cmple_pd(a0,a1) };
      return that;
    }
  };

  template<class Info>
  struct  call< is_less_equal_, tag::simd_(tag::arithmetic_,tag::sse_)
              , float         , Info
              >
        : callable
  {
    template<class Sig> struct result;
    template<class This,class A> struct result<This(A,A)> : meta::strip<A> {};

    NT2_FUNCTOR_CALL(2)
    {
      A0 that = { _mm_cmple_ps(a0,a1) };
      return that;
    }
  };

  template<class Info>
  struct  call< is_less_equal_, tag::simd_(tag::arithmetic_,tag::sse_)
              , arithmetic_   , Info
              >
        : callable
  {
    template<class Sig> struct result;
    template<class This,class A> struct result<This(A,A)> : meta::strip<A> {};

    NT2_FUNCTOR_CALL(2)
    {
      A0 that = { complement(gt(a0,a1) ) };
      return that;
    }
  };
} }

#endif
