//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_MODELS_FUNCTION_SCALAR_MODEL_FOUR_BRANCHES_HPP_INCLUDED
#define NT2_TOOLBOX_MODELS_FUNCTION_SCALAR_MODEL_FOUR_BRANCHES_HPP_INCLUDED
#include <nt2/sdk/constant/digits.hpp>
#include <nt2/sdk/constant/real.hpp>

#include <nt2/include/functions/is_nan.hpp>

namespace nt2 { namespace functors
{

  //  no special validate for model_four_branches

  /////////////////////////////////////////////////////////////////////////////
  // Compute model_four_branches(const A0& a0)
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct call<model_four_branches_,tag::scalar_(tag::arithmetic_),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : 
      std::tr1::result_of<meta::floating(A0)>{};

    NT2_FUNCTOR_CALL_DISPATCH(
      1,
      A0,
      (2, (real_,arithmetic_))
    )
    NT2_FUNCTOR_CALL_EVAL_IF(1,       real_)
    {
      // test1/2/3 are supposed less and less restrictive 
      if(isnan(a0)) return Nan<A0>(); 
      bool test1 = is_le(a0, One<A0>()); //any test
      if (test1)
	{
	  return One<A0>();
	}
      else
	{
	  bool test2 = is_le(a0, Two<A0>()); //any test
	  if (test2)
	    {
	      return Two<A0>();
	    }
	  else
	    {
	      bool test3 = is_le(a0, Three<A0>()); //any test
	      if (test3)
		{
		  return Three<A0>();
		}
	      return Four<A0>(); //catch all
	    }
	}
    }
    NT2_FUNCTOR_CALL_EVAL_IF(1,       arithmetic_)
    {
      typedef typename NT2_CALL_RETURN_TYPE(1)::type type;
      return model_four_branches(type(a0));
    }

  };
} }


      
#endif
