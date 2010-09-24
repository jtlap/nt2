//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_HYPERBOLIC_FUNCTION_SCALAR_ACOSH_HPP_INCLUDED
#define NT2_TOOLBOX_HYPERBOLIC_FUNCTION_SCALAR_ACOSH_HPP_INCLUDED
#include <nt2/sdk/constant/digits.hpp>
#include <nt2/sdk/constant/infinites.hpp>
#include <nt2/sdk/constant/real.hpp>

#include <nt2/include/functions/minusone.hpp>
#include <nt2/include/functions/log1p.hpp>
#include <nt2/include/functions/sqrt.hpp>
#include <nt2/include/functions/sqr.hpp>
#include <nt2/include/functions/oneminus.hpp>

namespace nt2 { namespace functors
{

  //  no special validate for acosh

  /////////////////////////////////////////////////////////////////////////////
  // Compute acosh(const A0& a0)
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct call<acosh_,tag::scalar_(tag::arithmetic_),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : 
      boost::result_of<meta::floating(A0)>{};

    NT2_FUNCTOR_CALL_DISPATCH(
      1,
      A0,
      (2, (real_,arithmetic_))
    )
    NT2_FUNCTOR_CALL_EVAL_IF(1,  real_)
    {
      typedef typename NT2_CALL_RETURN_TYPE(1)::type type; 
      if (a0 < One<A0>()) return Nan<A0>();
      if (a0 == Inf<A0>()) return a0;
      type t = minusone(a0);
//       if (t < 16*Sqrteps<A0>()){
// 	return sqrt(Two<A0>()*t)*(oneminus(t/12)); //A0 y =  nt2::sqrt(minusone(a0));
//       }
      return nt2::log1p(t+nt2::sqrt((t+t)+sqr(t)));  
    }
    NT2_FUNCTOR_CALL_EVAL_IF(1, arithmetic_)
    {
      typedef typename NT2_CALL_RETURN_TYPE(1)::type type; 
      return nt2::acosh(type(a0)); 
    }
  };
} }


      
#endif
