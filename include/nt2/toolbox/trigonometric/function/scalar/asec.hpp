//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_TRIGONOMETRIC_FUNCTION_SCALAR_ASEC_HPP_INCLUDED
#define NT2_TOOLBOX_TRIGONOMETRIC_FUNCTION_SCALAR_ASEC_HPP_INCLUDED
#include <nt2/sdk/constant/digits.hpp>

#include <nt2/include/functions/acsc.hpp>
#include <nt2/include/functions/is_eqz.hpp>

namespace nt2 { namespace functors
{

  //  no special validate for asec

  /////////////////////////////////////////////////////////////////////////////
  // Compute asec(const A0& a0)
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct call<asec_,tag::scalar_(tag::arithmetic_),Info>
  {
      template<class Sig> struct result;
      template<class This,class A0>
      struct result<This(A0)> : boost::result_of<meta::floating(A0)>{};

      NT2_FUNCTOR_CALL_DISPATCH ( 1
                                , A0
                                , (3, (float,double,arithmetic_))
                                )

      NT2_FUNCTOR_CALL_EVAL_IF(1,  float)
      {
	return Pio_2<A0>()-nt2::acsc(a0);
      }
      
      NT2_FUNCTOR_CALL_EVAL_IF(1, double)
      {
        //                                  6.123233995736765886130E-17
        return (Pio_2<A0>()-nt2::acsc(a0))+integral_constant<A0, 0x3c91a62633145c07ll>();
      }

      NT2_FUNCTOR_CALL_EVAL_IF(1, arithmetic_)
      {
	typedef typename NT2_CALL_RETURN_TYPE(1)::type type; 
        return nt2::asec(type(a0));
      }
    };
} }


      
#endif
