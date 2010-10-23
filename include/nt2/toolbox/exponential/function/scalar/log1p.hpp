//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_EXPONENTIAL_FUNCTION_SCALAR_LOG1P_HPP_INCLUDED
#define NT2_TOOLBOX_EXPONENTIAL_FUNCTION_SCALAR_LOG1P_HPP_INCLUDED
#include <nt2/sdk/constant/eps_related.hpp>
#include <nt2/sdk/constant/digits.hpp>
#include <nt2/sdk/constant/infinites.hpp>
#include <nt2/sdk/constant/real.hpp>

#include <nt2/include/functions/log.hpp>
#include <nt2/include/functions/minusone.hpp>
#include <nt2/include/functions/oneplus.hpp>

namespace nt2 { namespace functors
{

  //  no special validate for log1p

  /////////////////////////////////////////////////////////////////////////////
  // Compute log1p(const A0& a0)
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct call<log1p_,tag::scalar_(tag::arithmetic_),Info>
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

    NT2_FUNCTOR_CALL_EVAL_IF(1,       float)
    {
      typedef typename NT2_CALL_RETURN_TYPE(1)::type type;
      if (a0 < -One<A0>())   return Nan<A0>();
      if (a0 == Inf<A0>())   return Inf<A0>();
      if (abs(a0) <  Eps<A0>()) return a0;
      if (abs(a0) <  0.4f )
	{
	  float n = horner< NT2_HORNER_COEFF(float, 4, (0x3e4c280f, 
							0x3f84468b, 
							0x3f800000,
							0x13261e6e	
							)) > (a0); 
	  float d = horner< NT2_HORNER_COEFF(float, 4, (0x3d622235, 
							0x3f21fb6f, 
							0x3fc44692, 
							0x3f800000
							)) > (a0);
          return n/d;
      }
      //      if (abs(a0) <  0.4f ) return nt2::log1p(double(a0)); //a0*(One<A0>()-a0*(Half<A0>()+a0*(Third<A0>()-a0*Quarter<A0>()))); 
      type u = oneplus(a0);
      type r =nt2::log(u); 
      return r; 
    }
    // P = {    0.20967148907e-26L,
    //     1.00000002L,
    //     1.0334027807L,
    //     0.19937156488L,
    //   }
    // Q = {    1L,
    //     1.5334036279L,
    //     0.63274283378L,
    //     0.055208404043L,
    //   }
    NT2_FUNCTOR_CALL_EVAL_IF(1,       real_)
    {
      typedef typename NT2_CALL_RETURN_TYPE(1)::type type;
      if (a0 < Mone<A0>())   return Nan<A0>();
      if (a0 == Inf<A0>())   return Inf<A0>();
      volatile type u = oneplus(a0);
      volatile type t =(minusone(u)-a0);
      type r =nt2::log(u); 
      if (t) 
	return r*(a0/minusone(u)); //-t/u; /* cancels errors with IEEE arithmetic */
      else
	return r; 
    }
    NT2_FUNCTOR_CALL_EVAL_IF(1, arithmetic_)
    {
      typedef typename NT2_CALL_RETURN_TYPE(1)::type type; 
      return nt2::log(oneplus(type(a0))); 
    }
  };
} }


      
#endif
