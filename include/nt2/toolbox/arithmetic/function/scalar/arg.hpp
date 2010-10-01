//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_ARITHMETIC_FUNCTION_SCALAR_ARG_HPP_INCLUDED
#define NT2_TOOLBOX_ARITHMETIC_FUNCTION_SCALAR_ARG_HPP_INCLUDED
#include <nt2/sdk/constant/real.hpp>
#include <nt2/sdk/constant/digits.hpp>

#include <nt2/include/functions/is_gez.hpp>
#include <nt2/include/functions/is_ltz.hpp>
#include <nt2/include/functions/is_nan.hpp>
#include <iostream>
namespace nt2 { namespace functors
{

  //  no special validate for arg

  /////////////////////////////////////////////////////////////////////////////
  // Compute arg(const A0& a0)
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct call<arg_,tag::scalar_(tag::arithmetic_),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : 
      boost::result_of<meta::floating(A0)>{};

    NT2_FUNCTOR_CALL_DISPATCH(
      1,
      A0,
      (3, (real_,unsigned_,signed_))
    )

    NT2_FUNCTOR_CALL_EVAL_IF(1,       real_)
    {
      std::cout << "--------------"<< nt2::type_id(a0) <<  std::endl; 
      if (is_nan(a0)) return a0;
      if (is_gez(a0)) return Zero<A0>();
      return Pi<A0>();
    }
    NT2_FUNCTOR_CALL_EVAL_IF(1,   unsigned_)
    {
      return Zero<A0>();
    }
    NT2_FUNCTOR_CALL_EVAL_IF(1,     signed_)
    {
      typedef typename NT2_CALL_RETURN_TYPE(1)::type rtype; 
      return (is_ltz(a0))*Pi<rtype>();
    }
 
  };
} }


      
#endif
