//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_IEEE_FUNCTION_SCALAR_ILOGB_HPP_INCLUDED
#define NT2_TOOLBOX_IEEE_FUNCTION_SCALAR_ILOGB_HPP_INCLUDED
#include <nt2/sdk/meta/as_real.hpp>
#include <nt2/sdk/constant/real.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/include/functions/is_lez.hpp>

namespace nt2 { namespace functors
{

  //  no special validate for ilogb

  /////////////////////////////////////////////////////////////////////////////
  // Compute ilogb(const A0& a0)
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct call<ilogb_,tag::scalar_(tag::arithmetic_),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : 
      meta::as_integer<A0, signed>{};

    NT2_FUNCTOR_CALL_DISPATCH(
      1,
      A0,
      (3, (float,double, arithmetic_))
    )

    NT2_FUNCTOR_CALL_EVAL_IF(1,  float)
    {
      return is_lez(a0)? 0: ::ilogbf(a0);
    }
    NT2_FUNCTOR_CALL_EVAL_IF(1, double)
    {
       return is_lez(a0)? 0: ::ilogb(a0); 
    }
    NT2_FUNCTOR_CALL_EVAL_IF(1, arithmetic_)
    {
      typedef typename  meta::as_real<A0>::type type;
      return nt2::ilogb(type(a0)); 
    }
  };
} }


      
#endif
