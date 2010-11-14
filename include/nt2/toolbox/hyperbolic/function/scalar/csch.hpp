//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_HYPERBOLIC_FUNCTION_SCALAR_CSCH_HPP_INCLUDED
#define NT2_TOOLBOX_HYPERBOLIC_FUNCTION_SCALAR_CSCH_HPP_INCLUDED

#include <nt2/include/functions/sinh.hpp>

namespace nt2 { namespace functors
{

  //  no special validate for csch

  /////////////////////////////////////////////////////////////////////////////
  // Compute csch(const A0& a0)
  /////////////////////////////////////////////////////////////////////////////

  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is arithmetic_
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct  call<csch_,tag::scalar_(tag::arithmetic_),arithmetic_,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : 
      boost::result_of<meta::floating(A0)>{};

    NT2_FUNCTOR_CALL(1)
    {
       return rec(nt2::sinh(a0));
    }
  };

} }

#endif
/// Revised by jt the 13/11/2010
