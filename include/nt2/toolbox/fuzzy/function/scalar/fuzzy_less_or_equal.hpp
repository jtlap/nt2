//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_FUZZY_FUNCTION_SCALAR_FUZZY_LESS_OR_EQUAL_HPP_INCLUDED
#define NT2_TOOLBOX_FUZZY_FUNCTION_SCALAR_FUZZY_LESS_OR_EQUAL_HPP_INCLUDED

#include <nt2/include/functions/max.hpp>
#include <nt2/include/functions/abs.hpp>

namespace nt2 { namespace functors
{

  //  no special validate for fuzzy_less_or_equal

  /////////////////////////////////////////////////////////////////////////////
  // Compute fuzzy_less_or_equal(const A0& a0, const A1& a1, const A2& a2)
  /////////////////////////////////////////////////////////////////////////////

  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type  is fundamental_
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct  call<fuzzy_less_or_equal_,tag::scalar_(tag::arithmetic_),fundamental_,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1,class A2>
    struct result<This(A0,A1,A2)> {typedef bool type; }; 

    NT2_FUNCTOR_CALL(3)
    {
       return a0 <= a1+a2*nt2::max(nt2::abs(a0),nt2::abs(a1));
    }

  };
} }

#endif
/// Revised by jt the 15/11/2010
