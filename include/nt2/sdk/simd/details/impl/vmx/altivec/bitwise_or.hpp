/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_SIMD_DETAILS_IMPL_VMX_ALTIVEC_BITWISE_OR_HPP_INCLUDED
#define NT2_SDK_SIMD_DETAILS_IMPL_VMX_ALTIVEC_BITWISE_OR_HPP_INCLUDED

#include <nt2/sdk/meta/strip.hpp>

namespace nt2 { namespace functors
{
  //////////////////////////////////////////////////////////////////////////////
  // Bitwise operators requires same bits size
  //////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct validate<bitwise_or_,tag::simd_(tag::arithmetic_,tag::altivec_),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct  result<This(A0,A1)>
          : boost::mpl::bool_< sizeof(A0) == sizeof(A1) > {};
  };

  template<class Info,class C>
  struct call<bitwise_or_,tag::simd_(C,tag::altivec_),Info>
  {
    template<class Sig> struct result;
    template<class This,class A>
    struct result<This(A,A)> : meta::strip<A> {};

    NT2_FUNCTOR_CALL(2) 
    { 
      A0 that = { a1 }; 
      that = vec_or(a0,that);
      return that; 
    }
  };
} }

#endif
