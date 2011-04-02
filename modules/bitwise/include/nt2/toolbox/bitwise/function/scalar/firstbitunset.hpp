//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_BITWISE_FUNCTION_SCALAR_FIRSTBITUNSET_HPP_INCLUDED
#define NT2_TOOLBOX_BITWISE_FUNCTION_SCALAR_FIRSTBITUNSET_HPP_INCLUDED
#include <nt2/sdk/constant/digits.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/meta/as_bits.hpp>



/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::firstbitunset_, tag::cpu_,
                               (A0),
                               (arithmetic_<A0>)
                              )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::firstbitunset_(tag::arithmetic_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> :
      meta::as_integer<A0, unsigned>{};

    NT2_FUNCTOR_CALL(1)
    {
      return ~a0 & (a0+One<A0>());
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is real_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::firstbitunset_, tag::cpu_,
                               (A0),
                               (real_<A0>)
                              )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::firstbitunset_(tag::real_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> :
      meta::as_integer<A0, unsigned>{};

    NT2_FUNCTOR_CALL(1)
    {
      typedef typename meta::as_bits<A0, signed>::type type;
      type that = {a0};
      return firstbitunset(that.bits);
    }
  };
} }

#endif
// modified by jt the 26/12/2010