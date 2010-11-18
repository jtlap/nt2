//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_BITWISE_FUNCTION_SCALAR_BITWISE_SELECT_HPP_INCLUDED
#define NT2_TOOLBOX_BITWISE_FUNCTION_SCALAR_BITWISE_SELECT_HPP_INCLUDED
#include <nt2/include/functions/bitwise_andnot.hpp>

namespace nt2 { namespace functors
{

  //  no special validate for bitwise_select

  /////////////////////////////////////////////////////////////////////////////
  // Compute bitwise_select(const A0& a0, const A1& a1, const A2& a2)
  /////////////////////////////////////////////////////////////////////////////

  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type  is fundamental_
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct  call<bitwise_select_,tag::scalar_(tag::arithmetic_),fundamental_,Info> : callable
  {
    template<class Sig> struct result;
    template<class This, class A0, class A1>
    struct result<This(A0,A1,A1)> : meta::strip<A1>{};//

    NT2_FUNCTOR_CALL(3)
    {
      return b_or(b_and(a1, a0), b_andnot(a2, a0));
    }

  };
} }

#endif
/// Revised by jt the 15/11/2010
