//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_TRIGONOMETRIC_FUNCTION_SCALAR_ACOT_HPP_INCLUDED
#define NT2_TOOLBOX_TRIGONOMETRIC_FUNCTION_SCALAR_ACOT_HPP_INCLUDED
#include <nt2/sdk/constant/real.hpp>
#include <nt2/sdk/constant/digits.hpp>
#include <nt2/sdk/constant/infinites.hpp>
#include <nt2/include/functions/atan.hpp>
#include <nt2/include/functions/rec.hpp>
#include <nt2/include/functions/bitofsign.hpp>
#include <nt2/include/functions/is_inf.hpp>
#include <iostream>

namespace nt2 { namespace functors
{

  //  no special validate for acot

  /////////////////////////////////////////////////////////////////////////////
  // Compute acot(const A0& a0)
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct call<acot_,tag::scalar_(tag::arithmetic_),Info>
  {
      template<class Sig> struct result;
      template<class This,class A0>
      struct result<This(A0)> : boost::result_of<meta::floating(A0)>{};

      NT2_FUNCTOR_CALL_DISPATCH ( 1,
                                  A0,
                                  (3, (float,double,arithmetic_))
                                )

      NT2_FUNCTOR_CALL_EVAL_IF(1,  float)
      {
	if(!a0)  return b_or(Inf<A0>(), bitofsign(a0));;
	if(is_inf(a0)) return b_or(Zero<A0>(), bitofsign(a0));
	return b_or(Pio_2<A0>()-nt2::atan(abs(a0)), bitofsign(a0));
      }

      NT2_FUNCTOR_CALL_EVAL_IF(1, double)
      {
	if(!a0)  return b_or(Inf<A0>(), bitofsign(a0));;
	if(is_inf(a0)) return b_or(Zero<A0>(), bitofsign(a0));
        //                                 6.123233995736765886130E-17
        return  b_or((Pio_2<A0>()-nt2::atan(abs(a0)))+double_constant<A0,0x3c91a62633145c07ll>(), bitofsign(a0));
      }

      NT2_FUNCTOR_CALL_EVAL_IF(1, arithmetic_)
      {
	typedef typename NT2_CALL_RETURN_TYPE(1)::type type; 
        return nt2::acot(type(a0));
      }
     };
} }


      
#endif
