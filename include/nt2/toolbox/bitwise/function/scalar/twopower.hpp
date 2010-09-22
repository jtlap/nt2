//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_BITWISE_FUNCTION_SCALAR_TWOPOWER_HPP_INCLUDED
#define NT2_TOOLBOX_BITWISE_FUNCTION_SCALAR_TWOPOWER_HPP_INCLUDED
#include <nt2/sdk/constant/digits.hpp>
#include <nt2/sdk/meta/adapted_traits.hpp>
#include <nt2/include/functions/is_ltz.hpp>

namespace nt2 { namespace functors
{

  template<class Info>
  struct validate<twopower_,tag::scalar_(tag::arithmetic_),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> :
     meta::is_integral<A0>{}; 
  };

  /////////////////////////////////////////////////////////////////////////////
  // Compute twopower(const A0& a0)
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct call<twopower_,tag::scalar_(tag::arithmetic_),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : 
      boost::result_of<meta::arithmetic(A0)>{};

    NT2_FUNCTOR_CALL_DISPATCH(
      1,
      A0,
      (2, (unsigned,arithmetic_))
    )

    NT2_FUNCTOR_CALL_EVAL_IF(1,    unsigned)
    {
       return One<A0>()<<a0;
    }
    NT2_FUNCTOR_CALL_EVAL_IF(1, arithmetic_)
    {
       return (isltz(a0))?Zero<A0>():(One<A0>()<<a0);
    }
  };
} }


      
#endif
