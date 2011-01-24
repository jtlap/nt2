/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_FUNCTOR_DETAILS_COMPLEMENT_HPP_INCLUDED
#define NT2_SDK_FUNCTOR_DETAILS_COMPLEMENT_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// bitwise complement extended implementation
////////////////////////////////////////////////////////////////////////////////
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/sdk/meta/as_bits.hpp>
#include <nt2/sdk/functor/preprocessor/call.hpp>

NT2_REGISTER_DISPATCH(tag::complement_,tag::cpu_,(A0),(fundamental_<A0>));
NT2_REGISTER_DISPATCH(tag::complement_,tag::cpu_,(A0),(real_<A0>));

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::complement_(tag::fundamental_), tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : meta::strip<A0> {};

    NT2_FUNCTOR_CALL(1) { return ~a0; }
  };


  template<class Dummy>
  struct call<tag::complement_(tag::real_), tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : meta::strip<A0> {};

    NT2_FUNCTOR_CALL(1)
    {
      typename meta::as_bits<A0>::type t0 = {a0};
      t0.bits = ~t0.bits;
      return t0.value;
    }
  };
} }

#endif
