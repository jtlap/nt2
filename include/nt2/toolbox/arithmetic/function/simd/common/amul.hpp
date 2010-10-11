//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_ARITHMETIC_FUNCTION_SIMD_COMMON_AMUL_HPP_INCLUDED
#define NT2_TOOLBOX_ARITHMETIC_FUNCTION_SIMD_COMMON_AMUL_HPP_INCLUDED
#include <nt2/sdk/meta/strip.hpp>


namespace nt2 { namespace functors
{
  //  no special validate for amul

  /////////////////////////////////////////////////////////////////////////////
  // Compute amul(const A0& a0, const A0& a1, const A0& a2)
  /////////////////////////////////////////////////////////////////////////////
  template<class Extension,class Info>
  struct call<amul_,
              tag::simd_(tag::arithmetic_,Extension),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0,A0,A0)>
      : meta::strip<A0>{};//

    NT2_FUNCTOR_CALL(3)
    {
      return a0+nt2::mul(a1, a2); 
    }
  };
} }

      
#endif
