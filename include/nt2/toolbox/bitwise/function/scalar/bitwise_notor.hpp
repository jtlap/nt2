//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_BITWISE_FUNCTION_SCALAR_BITWISE_NOTOR_HPP_INCLUDED
#define NT2_TOOLBOX_BITWISE_FUNCTION_SCALAR_BITWISE_NOTOR_HPP_INCLUDED
#include <nt2/sdk/meta/size.hpp>
#include <nt2/sdk/meta/as_bits.hpp>
#include <nt2/sdk/meta/size.hpp>

namespace nt2 { namespace functors
{

  template<class Info>
  struct validate<bitwise_notor_,tag::scalar_(tag::arithmetic_),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0,A1)> : meta::has_same_size<A0,A1>{};
  };
  /////////////////////////////////////////////////////////////////////////////
  // Compute bitwise_notor(const A0& a0, const A1& a1)
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct call<bitwise_notor_,tag::scalar_(tag::arithmetic_),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0,A1)>  : meta::strip<A0>{};//

    NT2_FUNCTOR_CALL(2)
    {
      typename meta::as_bits<A0>::type t0 = {a0};
      typename meta::as_bits<A1>::type t1 = {a1};
      t0.bits = b_or(b_not(t0.bits),t1.bits);
      return t0.value;
    }
  };
} }


      
#endif
