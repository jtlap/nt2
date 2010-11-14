//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_HYPERBOLIC_FUNCTION_SCALAR_SINH_HPP_INCLUDED
#define NT2_TOOLBOX_HYPERBOLIC_FUNCTION_SCALAR_SINH_HPP_INCLUDED
#include <nt2/sdk/constant/digits.hpp>
#include <nt2/sdk/constant/real.hpp>

#include <nt2/include/functions/exp.hpp>
#include <nt2/include/functions/expm1.hpp>
#include <nt2/include/functions/rec.hpp>

namespace nt2 { namespace functors
{

  //  no special validate for sinh

  /////////////////////////////////////////////////////////////////////////////
  // Compute sinh(const A0& a0)
  /////////////////////////////////////////////////////////////////////////////

  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is real_
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct  call<sinh_,tag::scalar_(tag::arithmetic_),real_,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : 
      boost::result_of<meta::floating(A0)>{};

    NT2_FUNCTOR_CALL(1)
    {
      typedef typename NT2_CALL_RETURN_TYPE(1)::type type;
      type tmp = nt2::exp(a0); 
      if ( abs(a0) > 0.6)
	{
	  return (tmp-rec(tmp))*Half<A0>();
	}
      else
	{
	  return -tmp*nt2::expm1(-(a0+a0))*Half<A0>();
	}
    }
  };


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is arithmetic_
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct  call<sinh_,tag::scalar_(tag::arithmetic_),arithmetic_,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : 
      boost::result_of<meta::floating(A0)>{};

    NT2_FUNCTOR_CALL(1)
    {
      typedef typename NT2_CALL_RETURN_TYPE(1)::type type;
      if (is_eqz(a0)) return Zero<type>(); 
      type tmp = nt2::exp(a0);
      return (tmp-rec(tmp))*Half<type>();
    }
  };

} }

#endif
/// Revised by jt the 13/11/2010
