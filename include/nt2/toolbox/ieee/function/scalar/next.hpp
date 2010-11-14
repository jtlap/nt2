//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_IEEE_FUNCTION_SCALAR_NEXT_HPP_INCLUDED
#define NT2_TOOLBOX_IEEE_FUNCTION_SCALAR_NEXT_HPP_INCLUDED
#include <nt2/sdk/constant/digits.hpp>
#include <nt2/sdk/constant/infinites.hpp>
#include <nt2/sdk/meta/strip.hpp>


namespace nt2 { namespace functors
{

  //  no special validate for next

  /////////////////////////////////////////////////////////////////////////////
  // Compute next(const A0& a0)
  /////////////////////////////////////////////////////////////////////////////

  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is float
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct  call<next_,tag::scalar_(tag::arithmetic_),float,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
      struct result<This(A0)> : meta::strip<A0>{};

    NT2_FUNCTOR_CALL(1)
    {
      return ::nextafterf(a0, Inf<A0>());
    }
  };


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is double
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct  call<next_,tag::scalar_(tag::arithmetic_),double,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
      struct result<This(A0)> : meta::strip<A0>{};

    NT2_FUNCTOR_CALL(1)
    {
      return ::nextafter(a0, Inf<A0>());
    }
  };


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is arithmetic_
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct  call<next_,tag::scalar_(tag::arithmetic_),arithmetic_,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
      struct result<This(A0)> : meta::strip<A0>{};

    NT2_FUNCTOR_CALL(1)
    {
      return a0+One<A0>(); 
    }
  };

} }

#endif
/// Revised by jt the 13/11/2010
