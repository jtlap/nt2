/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_SIMD_DETAILS_IMPL_COMMON_MODULO_HPP_INCLUDED
#define NT2_SDK_SIMD_DETAILS_IMPL_COMMON_MODULO_HPP_INCLUDED

namespace nt2 { namespace functors
{
  //////////////////////////////////////////////////////////////////////////////
  // Modulo operates on integers only
  //////////////////////////////////////////////////////////////////////////////
  template<class C,class X,class Info>
  struct validate<modulo_,tag::simd_(C,X),Info>
  {
    template<class Sig> struct result;
    template<class This,class A>
    struct  result<This(A,A)>
          : meta::is_integral<typename meta::strip<A>::type> {};
  };
} }

#endif
