//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_ARITHMETIC_FUNCTION_SCALAR_IDIVCEIL_HPP_INCLUDED
#define NT2_TOOLBOX_ARITHMETIC_FUNCTION_SCALAR_IDIVCEIL_HPP_INCLUDED
#include <nt2/sdk/constant/digits.hpp>
#include <nt2/include/functions/sign.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/rdivide.hpp>

namespace nt2 { namespace functors
{

  //  no special validate for idivceil

  /////////////////////////////////////////////////////////////////////////////
  // Compute idivceil(const A0& a0, const A1& a1)
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct call<idivceil_,tag::scalar_(tag::arithmetic_),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0,A1)> : 
      boost::result_of<meta::arithmetic(A0,A1)>{};

    NT2_FUNCTOR_CALL_DISPATCH(
      2,
      A0,
      (3, (real_,unsigned_, arithmetic_))
    )

    NT2_FUNCTOR_CALL_EVAL_IF(2,       real_)
    {
      return ceil(a0/a1);
    }
    NT2_FUNCTOR_CALL_EVAL_IF(2, unsigned_)
    {
      typedef typename NT2_CALL_RETURN_TYPE(2)::type  type;
      return rdivide((a0+(a1-One<type>())), a1); 
    }
    NT2_FUNCTOR_CALL_EVAL_IF(2, arithmetic_)
    {
      return ceil(float(a0)/float(a1)); // TO DO
//       typedef typename NT2_CALL_RETURN_TYPE(2)::type  type;
//        if (a0 > 0)
//  	{
// 	  if (a1 > 0)
// 	      return rdivide((a0+(a1-One<type>())), a1);
// 	  else
// 	      return -rdivide((a0+(-a1-One<type>())), -a1);
//  	}
//        else
//  	{
// 	  if (a1 > 0)
// 	      return -rdivide((-a0+(a1+One<type>())), a1);
// 	  else
// 	      return rdivide((-a0+(-a1-One<type>())), -a1);
//  	}
    }

   };
} }


      
#endif
