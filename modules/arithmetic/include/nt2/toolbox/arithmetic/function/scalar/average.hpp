//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_ARITHMETIC_FUNCTION_SCALAR_AVERAGE_HPP_INCLUDED
#define NT2_TOOLBOX_ARITHMETIC_FUNCTION_SCALAR_AVERAGE_HPP_INCLUDED
#include <nt2/sdk/constant/real.hpp>
#include <nt2/include/functions/shrai.hpp>

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::average_, tag::cpu_,
                         (A0),
                         (arithmetic_<A0>)(arithmetic_<A0>)
                        )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::average_(tag::arithmetic_,tag::arithmetic_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0,A0)> :  meta::strip<A0>{};

    NT2_FUNCTOR_CALL(2)
    {
      return b_and(a0, a1)+(shrai(b_xor(a0, a1), 1));
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is real_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::average_, tag::cpu_,
                         (A0),
                         (real_<A0>)(real_<A0>)
                        )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::average_(tag::real_,tag::real_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0,A0)> :  meta::strip<A0>{};

    NT2_FUNCTOR_CALL(2)
    {
      typedef typename NT2_RETURN_TYPE(2)::type type;
      return (a0+a1)*Half<type>();
    }
  };
} }

#endif
// modified by jt the 26/12/2010
