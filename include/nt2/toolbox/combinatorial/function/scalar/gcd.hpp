//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_COMBINATORIAL_FUNCTION_SCALAR_GCD_HPP_INCLUDED
#define NT2_TOOLBOX_COMBINATORIAL_FUNCTION_SCALAR_GCD_HPP_INCLUDED

#include <nt2/include/functions/is_flint.hpp>
#include <nt2/include/functions/is_not_finite.hpp>

namespace nt2 { namespace functors
{

  //  no special validate for gcd

  /////////////////////////////////////////////////////////////////////////////
  // Compute gcd(const A0& a0, const A1& a1)
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct call<gcd_,tag::scalar_(tag::arithmetic_),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0,A1)> : 
      boost::result_of<meta::arithmetic(A0,A1)>{};

    NT2_FUNCTOR_CALL_DISPATCH(
      2,
      A0,
      (2, (real_,arithmetic_))
    )

    NT2_FUNCTOR_CALL_EVAL_IF(2,  real_)
    {
      typedef typename NT2_CALL_RETURN_TYPE(2)::type type;
      type a(a0);
      type b(a1);
      if (!b) return a;
      if (is_not_finite(a+b)||!isflint(a)||!isflint(b)) return Nan <type>();
      while (b) {
	type  r  = rem(a, b);
	a = b;
	b = r;
      }
      return a;
    }
    NT2_FUNCTOR_CALL_EVAL_IF(2, arithmetic_)
    {
      typedef typename NT2_CALL_RETURN_TYPE(2)::type type;
      type a(a0);
      type b(a1);
      if (iseqz(b)) return a;
      while (isnez(b)) {
	const type  r = a % b;
	a = b;
	b = r;
      }
      return a;
    }
  };
} }


      
#endif
