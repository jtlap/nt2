/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_SIMD_DETAILS_IMPL_SSE_COMMON_LOGICAL_AND_HPP_INCLUDED
#define NT2_SDK_SIMD_DETAILS_IMPL_SSE_COMMON_LOGICAL_AND_HPP_INCLUDED

namespace nt2 { namespace functors
{
  template<class C, class X,class Info>
  struct call<logical_and_,tag::simd_(C,X),Info>
  {
    template<class Sig> struct result;
    template<class This,class A>
    struct result<This(A,A)> : meta::strip<A> {};

    NT2_FUNCTOR_CALL(2)
    {
      return neq(a0, Zero<A0>()) & neq(a1, Zero<A0>());
    }
  };
} }

#endif
