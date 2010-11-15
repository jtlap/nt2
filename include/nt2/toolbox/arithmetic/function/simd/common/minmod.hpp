//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_ARITHMETIC_FUNCTION_SIMD_COMMON_MINMOD_HPP_INCLUDED
#define NT2_TOOLBOX_ARITHMETIC_FUNCTION_SIMD_COMMON_MINMOD_HPP_INCLUDED
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/include/functions/is_gez.hpp>
#include <nt2/include/functions/seladd.hpp>
#include <nt2/include/functions/min.hpp>
#include <nt2/include/functions/sign.hpp>
#include <iostream>

namespace nt2 { namespace functors
{
  //  no special validate for minmod

  /////////////////////////////////////////////////////////////////////////////
  // Compute minmod(const A0& a0, const A0& a1)
  /////////////////////////////////////////////////////////////////////////////

  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is real_
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct  call<minmod_,tag::simd_(tag::arithmetic_),real_,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0,A0)> : meta::strip<A0>{};

    NT2_FUNCTOR_CALL(2)
    {
        return b_and(nt2::min(a0,a1), is_gez(a0*a1));
    }
  };


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is unsigned
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct  call<minmod_,tag::simd_(tag::arithmetic_),unsigned,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0,A0)> : meta::strip<A0>{};

    NT2_FUNCTOR_CALL(2)
    {
	return  nt2::min(a0,a1);
    }
  };


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is arithmetic_
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct  call<minmod_,tag::simd_(tag::arithmetic_),arithmetic_,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0,A0)> : meta::strip<A0>{};

    NT2_FUNCTOR_CALL(2)
    {
      return b_and(nt2::min(a0, a1), is_gez(b_xor(a0, a1)));
    }
  };

} }

#endif
/// Revised by jt the 15/11/2010
