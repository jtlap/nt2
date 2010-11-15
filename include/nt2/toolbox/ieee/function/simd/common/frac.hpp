//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_IEEE_FUNCTION_SIMD_COMMON_FRAC_HPP_INCLUDED
#define NT2_TOOLBOX_IEEE_FUNCTION_SIMD_COMMON_FRAC_HPP_INCLUDED
#include <nt2/sdk/constant/real.hpp>
#include <nt2/sdk/details/ignore_unused.hpp>
#include <nt2/sdk/constant/digits.hpp>
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/include/functions/is_invalid.hpp>
#include <nt2/include/functions/select.hpp>
#include <nt2/include/functions/trunc.hpp>


namespace nt2 { namespace functors
{
  //  no special validate for frac

  /////////////////////////////////////////////////////////////////////////////
  // Compute frac(const A0& a0)
  /////////////////////////////////////////////////////////////////////////////

  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is real_
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct  call<frac_,tag::simd_(tag::arithmetic_),real_,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0> struct result<This(A0)> : meta::strip<A0>{};//

    NT2_FUNCTOR_CALL(1)
    {
      return sel(is_invalid(a0), Nan<A0>(), a0-nt2::trunc(a0));
    }
  };


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is arithmetic_
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct  call<frac_,tag::simd_(tag::arithmetic_),arithmetic_,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0> struct result<This(A0)> : meta::strip<A0>{};//

    NT2_FUNCTOR_CALL(1)
    {
      details::ignore_unused(a0);
      return Zero<A0>();
    }
  };

} }

#endif
/// Revised by jt the 15/11/2010
