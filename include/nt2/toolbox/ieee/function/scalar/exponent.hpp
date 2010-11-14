//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_IEEE_FUNCTION_SCALAR_EXPONENT_HPP_INCLUDED
#define NT2_TOOLBOX_IEEE_FUNCTION_SCALAR_EXPONENT_HPP_INCLUDED
#include <nt2/sdk/meta/adapted_traits.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/constant/digits.hpp>


namespace nt2 { namespace functors
{

  template<class Info>
  struct validate<exponent_,tag::scalar_(tag::arithmetic_),Info>
  {
    template<class Sig> struct result; 
    template<class This,class A0>
    struct result<This(A0)> :
      meta::is_floating_point<typename meta::strip<A0>::type>{};
  };
  /////////////////////////////////////////////////////////////////////////////
  // Compute exponent(const A0& a0)
  /////////////////////////////////////////////////////////////////////////////

  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is float
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct  call<exponent_,tag::scalar_(tag::arithmetic_),float,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : meta::as_integer<A0, signed>{};

    NT2_FUNCTOR_CALL(1)
    {
      return a0 ? ::ilogbf(a0) : Zero<A0>();
    }
  };


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is double
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct  call<exponent_,tag::scalar_(tag::arithmetic_),double,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : meta::as_integer<A0, signed>{};

    NT2_FUNCTOR_CALL(1)
    {
       return a0 ? ::ilogb(a0) : Zero<A0>();
    }
  };

} }

#endif
/// Revised by jt the 13/11/2010
