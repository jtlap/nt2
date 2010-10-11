//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_IEEE_FUNCTION_SIMD_COMMON_SIGN_HPP_INCLUDED
#define NT2_TOOLBOX_IEEE_FUNCTION_SIMD_COMMON_SIGN_HPP_INCLUDED
#include <nt2/sdk/constant/digits.hpp>
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/include/functions/seladd.hpp>
#include <nt2/include/functions/is_nan.hpp>
#include <nt2/include/functions/is_ltz.hpp>
#include <nt2/include/functions/is_gtz.hpp>
#include <nt2/include/functions/is_nez.hpp>
#include <nt2/include/functions/negation.hpp>


namespace nt2 { namespace functors
{
  //  no special validate for sign

  /////////////////////////////////////////////////////////////////////////////
  // Compute sign(const A0& a0)
  /////////////////////////////////////////////////////////////////////////////
  template<class Extension,class Info>
  struct call<sign_,
              tag::simd_(tag::arithmetic_,Extension),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)>
      : meta::strip<A0>{};//

    NT2_FUNCTOR_CALL_DISPATCH(
      1,
      typename nt2::meta::scalar_of<A0>::type,
      (3, (real_,unsigned,arithmetic_))
    )

    NT2_FUNCTOR_CALL_EVAL_IF(1,       real_)
    {
      return seladd(isnan(a0),nt2::negation(One<A0>(),a0),a0);
    }
    NT2_FUNCTOR_CALL_EVAL_IF(1,    unsigned)
    {
      return -isnez(a0);    
    }
    NT2_FUNCTOR_CALL_EVAL_IF(1, arithmetic_)
    {
      return isltz(a0)-isgtz(a0);
    }
  };
} }

      
#endif
