//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_HYPERBOLIC_FUNCTION_SIMD_COMMON_ASECH_HPP_INCLUDED
#define NT2_TOOLBOX_HYPERBOLIC_FUNCTION_SIMD_COMMON_ASECH_HPP_INCLUDED
#include <nt2/sdk/meta/as_real.hpp>
#include <nt2/sdk/simd/meta/is_real_convertible.hpp>
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/include/functions/tofloat.hpp>


namespace nt2 { namespace functors
{
  template<class Extension,class Info>
  struct validate<asech_,tag::simd_(tag::arithmetic_,Extension),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : 
      meta::is_real_convertible<A0>{};
  };
  /////////////////////////////////////////////////////////////////////////////
  // Compute asech(const A0& a0)
  /////////////////////////////////////////////////////////////////////////////
  template<class Extension,class Info>
  struct call<asech_,
              tag::simd_(tag::arithmetic_,Extension),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : meta::as_real<A0>{};

    NT2_FUNCTOR_CALL_DISPATCH(
      1,
      typename nt2::meta::scalar_of<A0>::type,
      (3, (float,double, arithmetic_))
    )

    NT2_FUNCTOR_CALL_EVAL_IF(1,  float)
    {
        return acosh(rec(a0));
    }
    NT2_FUNCTOR_CALL_EVAL_IF(1, double)
    {
       A0 r;
       map(functor<asech_>(), a0, r);
       return r; 
    }
    NT2_FUNCTOR_CALL_EVAL_IF(1,  arithmetic_)
    {
      return nt2::acosh(rec(tofloat(a0)));
    }
  };
} }

      
#endif
