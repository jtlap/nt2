/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_SIMD_DETAILS_IMPL_SSE_SSE2_STORE_HPP_INCLUDED
#define NT2_SDK_SIMD_DETAILS_IMPL_SSE_SSE2_STORE_HPP_INCLUDED

#include <nt2/sdk/meta/strip.hpp>
#include <nt2/sdk/simd/category.hpp>
#include <boost/type_traits/remove_pointer.hpp>
#include <nt2/sdk/functor/preprocessor/call.hpp>

namespace nt2 { namespace functors
{
  //////////////////////////////////////////////////////////////////////////////
  // Store a vector
  //////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct  call< store_, tag::simd_(tag::arithmetic_,tag::sse_)
              ,double , Info
              >
        : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1, class A2>
    struct  result<This(A0,A1,A2)> : meta::strip<A0> {};

    NT2_FUNCTOR_CALL(3)
    {
      _mm_store_pd(a1+2*a2,a0);
      return a0;
    }
  };

  template<class Info>
  struct  call< store_, tag::simd_(tag::arithmetic_,tag::sse_)
              , float , Info
              >
        : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1, class A2>
    struct  result<This(A0,A1,A2)> : meta::strip<A0> {};

    NT2_FUNCTOR_CALL(3)
    {
      _mm_store_ps(a1+4*a2,a0);
      return a0;
    }
  };

  template<class Info>
  struct  call< store_  , tag::simd_(tag::arithmetic_,tag::sse_)
              , integer_, Info
              >
        : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1, class A2>
    struct  result<This(A0,A1,A2)> : meta::strip<A0> {};

    NT2_FUNCTOR_CALL(3)
    {
      _mm_store_si128(reinterpret_cast<__m128i*>(a1)+a2, a0);
      return a0;
    }
  };
} }

#endif
