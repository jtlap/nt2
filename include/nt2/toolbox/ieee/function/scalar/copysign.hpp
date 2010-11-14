//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_IEEE_FUNCTION_SCALAR_COPYSIGN_HPP_INCLUDED
#define NT2_TOOLBOX_IEEE_FUNCTION_SCALAR_COPYSIGN_HPP_INCLUDED
#include <nt2/sdk/meta/strip.hpp>

#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/signnz.hpp>

namespace nt2 { namespace functors
{

  //  no special validate for copysign

  /////////////////////////////////////////////////////////////////////////////
  // Compute copysign(const A0& a0, const A1& a1)
  /////////////////////////////////////////////////////////////////////////////

  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is float
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct  call<copysign_,tag::scalar_(tag::arithmetic_),float,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
      struct result<This(A0,A1)> : meta::strip<A0>{}; 

    NT2_FUNCTOR_CALL(2)
    {
      return ::copysignf(a0, a1);
    }
  };


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is double
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct  call<copysign_,tag::scalar_(tag::arithmetic_),double,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
      struct result<This(A0,A1)> : meta::strip<A0>{}; 

    NT2_FUNCTOR_CALL(2)
    {
      return ::copysign(a0, a1);
    }
  };


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is arithmetic_
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct  call<copysign_,tag::scalar_(tag::arithmetic_),arithmetic_,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
      struct result<This(A0,A1)> : meta::strip<A0>{}; 

    NT2_FUNCTOR_CALL(2)
    {
      return nt2::abs(a0)*signnz(a1);
    }
  };

} }

#endif
/// Revised by jt the 13/11/2010
