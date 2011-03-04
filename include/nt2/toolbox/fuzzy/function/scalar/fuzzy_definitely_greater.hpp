//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_FUZZY_FUNCTION_SCALAR_FUZZY_DEFINITELY_GREATER_HPP_INCLUDED
#define NT2_TOOLBOX_FUZZY_FUNCTION_SCALAR_FUZZY_DEFINITELY_GREATER_HPP_INCLUDED

#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/max.hpp>


/////////////////////////////////////////////////////////////////////////////
// Implementation when type  is fundamental_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::fuzzy_definitely_greater_, tag::cpu_,
                                          (A0)(A1)(A2),
                                          (arithmetic_<A0>)(arithmetic_<A1>)(arithmetic_<A2>)
                                         )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::fuzzy_definitely_greater_(tag::arithmetic_,tag::arithmetic_,tag::arithmetic_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1,class A2>
    struct result<This(A0,A1,A2)> {typedef bool type; };

    NT2_FUNCTOR_CALL(3)
    {
       return a0 > a1+a2*nt2::max(nt2::abs(a0),nt2::abs(a1));
    }

  };
} }

#endif
// modified by jt the 26/12/2010
