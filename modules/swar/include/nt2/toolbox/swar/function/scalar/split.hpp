//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_SWAR_FUNCTION_SCALAR_SPLIT_HPP_INCLUDED
#define NT2_TOOLBOX_SWAR_FUNCTION_SCALAR_SPLIT_HPP_INCLUDED

/////////////////////////////////////////////////////////////////////////////
// split as currently no meaning in scalar mode
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// Implementation when type  is arithmetic_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::split_, tag::cpu_,
                              (A0),
                              (arithmetic_<A0>)
                             )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::split_(tag::arithmetic_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
      struct result<This(A0)> :  meta::strip<A0> {};

    NT2_FUNCTOR_CALL(1)
    {
      return a0;
    }

  };
} }

#endif
// modified by jt the 26/12/2010

