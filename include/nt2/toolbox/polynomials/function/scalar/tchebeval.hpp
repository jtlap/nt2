//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_POLYNOMIALS_FUNCTION_SCALAR_TCHEBEVAL_HPP_INCLUDED
#define NT2_TOOLBOX_POLYNOMIALS_FUNCTION_SCALAR_TCHEBEVAL_HPP_INCLUDED
#include <nt2/sdk/constant/digits.hpp>

namespace nt2 { namespace functors
{

  /////////////////////////////////////////////////////////////////////////////
  // Compute tchebeval(const A0& a0, const A1& a1)
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct call<tchebeval_,tag::scalar_(tag::arithmetic_),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0,A1)> : 
      boost::result_of<meta::floating(A0,A1)>{};

    NT2_FUNCTOR_CALL_DISPATCH(
      2,
      A1,
      (2, (real_, arithmetic_))
    )

    NT2_FUNCTOR_CALL_EVAL_IF(2,  real_)
    {
      typename A1::const_iterator p = a1.begin();
      A0 b0 = *p++;
      A0 b1 =  Zero<A0>();
      A0 b2; 
      while (p != a1.end())
	{ 
	  b2 = -b1;
	  b1 = b0;
	  b0 = fma(a0, b1, b2)  + *p++;
	}
      return average(b0, b2); 
    }
    NT2_FUNCTOR_CALL_EVAL_IF(2, arithmetic_)
    {
      typedef typename NT2_CALL_RETURN_TYPE(2)::type type; 
      return tchebeval(a0, type(a1)); 
    }

  };
} }


      
#endif
