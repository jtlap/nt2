//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_IEEE_FUNCTION_SCALAR_NEXTAFTER_HPP_INCLUDED
#define NT2_TOOLBOX_IEEE_FUNCTION_SCALAR_NEXTAFTER_HPP_INCLUDED

#include <nt2/include/functions/sign.hpp>
#include <nt2/sdk/constant/digits.hpp>

namespace nt2 { namespace functors
{

  //  no special validate for nextafter

  /////////////////////////////////////////////////////////////////////////////
  // Compute nextafter(const A0& a0, const A1& a1)
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct call<nextafter_,tag::scalar_(tag::arithmetic_),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0,A1)> : 
      meta::strip<A0>{};

    NT2_FUNCTOR_CALL_DISPATCH(
      2,
      A0,
      (4, (float,double,unsigned_, arithmetic_))
    )

    NT2_FUNCTOR_CALL_EVAL_IF(2,  float)
    {
      return ::nextafterf(a0, a1);
    }
    NT2_FUNCTOR_CALL_EVAL_IF(2, double)
    {
      return ::nextafter(a0, a1);
    }
    NT2_FUNCTOR_CALL_EVAL_IF(2, unsigned_)
    {
      return (a1 == a0) ? a0 : (a1 > a0) ? a0+One<A0>() : a0-One<A0>(); 
    }
    NT2_FUNCTOR_CALL_EVAL_IF(2, arithmetic_)
    {
      return a0+sign(a1-a0); 
    }
  };
} }


      
#endif
