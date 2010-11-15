//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_IEEE_FUNCTION_SIMD_COMMON_MAXNUMMAG_HPP_INCLUDED
#define NT2_TOOLBOX_IEEE_FUNCTION_SIMD_COMMON_MAXNUMMAG_HPP_INCLUDED
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/include/functions/max.hpp>
#include <nt2/include/functions/select.hpp>
#include <nt2/include/functions/is_nan.hpp>
#include <nt2/include/functions/abs.hpp>


namespace nt2 { namespace functors
{
  //  no special validate for maxnummag

  /////////////////////////////////////////////////////////////////////////////
  // Compute maxnummag(const A0& a0, const A0& a1)
  /////////////////////////////////////////////////////////////////////////////

  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is real_
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct  call<maxnummag_,tag::simd_(tag::arithmetic_),real_,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0,A0)>
      : meta::strip<A0>{};//

    NT2_FUNCTOR_CALL(2)
    {
      const A0 a = select(is_nan(a0),a1,a0);
      const A0 b = select(is_nan(a1),a0,a1);
      return sel(gt(abs(a), abs(b)), a0, a1);
    }
  };


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is arithmetic_
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct  call<maxnummag_,tag::simd_(tag::arithmetic_),arithmetic_,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0,A0)>
      : meta::strip<A0>{};//

    NT2_FUNCTOR_CALL(2)
    {
      return sel(gt(abs(a0), abs(a1)), a0, a1);
    }
  };

} }

#endif
/// Revised by jt the 15/11/2010
