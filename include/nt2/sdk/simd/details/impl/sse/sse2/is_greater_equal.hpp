/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_SIMD_NATIVE_DETAILS_IMPL_SSE_SSE2_GREATER_EQUAL_HPP_INCLUDED
#define NT2_SDK_SIMD_NATIVE_DETAILS_IMPL_SSE_SSE2_GREATER_EQUAL_HPP_INCLUDED

#include <nt2/sdk/meta/strip.hpp>
#include <nt2/sdk/meta/scalar_of.hpp>

namespace nt2 { namespace functors
{
  template<class Info>
  struct call<is_greater_equal_,tag::simd_(tag::arithmetic_,tag::sse_),Info>
  {
    template<class Sig> struct result;
    template<class This,class A>
    struct result<This(A,A)> : meta::strip<A> {};

    NT2_FUNCTOR_CALL_DISPATCH( 2
                             , typename nt2::meta::scalar_of<A0>::type
                             , (3,(double,float,integer_))
                             )

    NT2_FUNCTOR_CALL_EVAL_IF(2,double)
    {
      A0 that = { _mm_cmpge_pd(a0,a1) };
      return that;
    }

    NT2_FUNCTOR_CALL_EVAL_IF(2,float )
    {
      A0 that = { _mm_cmpge_ps(a0,a1) };
      return that;
    }

    NT2_FUNCTOR_CALL_EVAL_IF(2,integer_)
    {
      A0 that = { complement(lt(a0,a1) ) };
      return that;
    }
  };
} }

#endif
