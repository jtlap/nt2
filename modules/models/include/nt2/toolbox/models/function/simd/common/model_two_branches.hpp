//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_MODELS_FUNCTION_SIMD_COMMON_MODEL_TWO_BRANCHES_HPP_INCLUDED
#define NT2_TOOLBOX_MODELS_FUNCTION_SIMD_COMMON_MODEL_TWO_BRANCHES_HPP_INCLUDED
#include <nt2/sdk/simd/meta/is_real_convertible.hpp>
#include <nt2/sdk/constant/digits.hpp>
#include <nt2/sdk/constant/real.hpp>
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/include/functions/tofloat.hpp>
#include <nt2/include/functions/is_nan.hpp>
#include <nt2/include/functions/nbtrue.hpp>
#include <nt2/include/functions/bitwise_ornot.hpp>


namespace nt2 { namespace functors
{
  template<class Extension,class Info>
  struct validate<model_two_branches_,tag::simd_<tag::arithmetic_,Extension),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : meta::is_real_convertible<A0>{}; 
  };
  /////////////////////////////////////////////////////////////////////////////
  // Compute model_two_branches(const A0& a0)
  /////////////////////////////////////////////////////////////////////////////
  template<class Extension,class Info>
  struct call<model_two_branches_,
              tag::simd_<tag::arithmetic_,Extension),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : 
      std::tr1::result_of<meta::floating(A0)>{};

    NT2_FUNCTOR_CALL_DISPATCH(
      1,
      typename nt2::meta::scalar_of<A0>::type,
      (2, (real_,arithmetic_))
    )
    NT2_FUNCTOR_CALL_EVAL_IF(1,       real_)
    {
      A0 r =  Nan<A0>(); 
      A0 test1 = is_lt(a0, One<A0>()); // any test
      int32_t nb = 0; 
      if (nb = nbtrue(test1) > 0)
	{
	  A0 y1 = One<A0>();  // computation result if test1
	  r = b_ornot(y1, test1);
	  if (nb >= meta::cardinal_of<A0>::value) return r;	  
	}
      A0 y2 =  Two<A0>(); // computation result if ~test1
      r &= b_or(y2, test1);
      return b_or(r, isnan(a0));
    }
    NT2_FUNCTOR_CALL_EVAL_IF(1,       arithmetic_)
    {
      typedef typename NT2_CALL_RETURN_TYPE(1)::type type;
      return model_two_branches(tofloat(a0));
    }

  };
} }

      
#endif
