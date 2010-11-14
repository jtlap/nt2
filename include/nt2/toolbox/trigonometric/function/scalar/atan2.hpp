//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_TRIGONOMETRIC_FUNCTION_SCALAR_ATAN2_HPP_INCLUDED
#define NT2_TOOLBOX_TRIGONOMETRIC_FUNCTION_SCALAR_ATAN2_HPP_INCLUDED
#include <nt2/toolbox/trigonometric/function/scalar/impl/constants.hpp>
#include <cmath>

namespace nt2 { namespace functors
{

  //  no special validate for atan2

  /////////////////////////////////////////////////////////////////////////////
  // Compute atan2(const A0& a0, const A1& a1)
  /////////////////////////////////////////////////////////////////////////////

  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type  is fundamental_
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct  call<atan2_,tag::scalar_(tag::arithmetic_),fundamental_,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0,A1)> : 
      boost::result_of<meta::floating(A0,A1)>{};

    NT2_FUNCTOR_CALL(2)
    {
        typedef typename NT2_CALL_RETURN_TYPE(2)::type rtype;
        return std::atan2(rtype(a0),rtype(a1));
    }

  };
} }

#endif
/// Revised by jt the 13/11/2010
