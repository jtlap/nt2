//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_IEEE_FUNCTION_SCALAR_EPS_HPP_INCLUDED
#define NT2_TOOLBOX_IEEE_FUNCTION_SCALAR_EPS_HPP_INCLUDED
#include <nt2/sdk/constant/properties.hpp>
#include <nt2/sdk/constant/digits.hpp>
#include <nt2/sdk/constant/real.hpp>
#include <nt2/sdk/constant/eps_related.hpp>
#include <nt2/sdk/details/ignore_unused.hpp>

#include <nt2/include/functions/is_not_finite.hpp>
#include <nt2/include/functions/fast_ldexp.hpp>
#include <nt2/include/functions/exponent.hpp>
#include <iostream>

namespace nt2 { namespace functors
{

  //  no special validate for eps

  /////////////////////////////////////////////////////////////////////////////
  // Compute eps(const A0& a0)
  /////////////////////////////////////////////////////////////////////////////

  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is real_
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct  call<eps_,tag::scalar_(tag::arithmetic_),real_,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : 
      boost::result_of<meta::arithmetic(A0)>{};

    NT2_FUNCTOR_CALL(1)
    {
      typedef typename NT2_CALL_RETURN_TYPE(1)::type value_type;
      typedef std::numeric_limits<A0> lim;
      const A0 a = abs(a0);
      if (is_not_finite(a))
	{
	  return value_type(Nan<A0>());
	}
      else if (a < lim::min())
	{
	  return Mindenormal<A0>(); 
	}
      else
	{
	  return nt2::fast_ldexp(One<A0>(), exponent(a) -lim::digits+1);
	}
    }
  };


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is arithmetic_
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct  call<eps_,tag::scalar_(tag::arithmetic_),arithmetic_,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : 
      boost::result_of<meta::arithmetic(A0)>{};

    NT2_FUNCTOR_CALL(1)
    {
      details::ignore_unused(a0);
      return One<A0>();
    }
  };

} }

#endif
/// Revised by jt the 13/11/2010
