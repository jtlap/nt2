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


/////////////////////////////////////////////////////////////////////////////
// Implementation when type  is fundamental_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::bitwise_notor_, tag::cpu_,
                               (A0)(A1),
                               (fundamental_<A0>)(fundamental_<A1>)
                              )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::bitwise_notor_(tag::fundamental_,tag::fundamental_),
              tag::cpu_, Dummy> : callable
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
// modified by jt the 26/12/2010