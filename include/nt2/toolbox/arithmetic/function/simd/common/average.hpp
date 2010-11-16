//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_ARITHMETIC_FUNCTION_SIMD_COMMON_AVERAGE_HPP_INCLUDED
#define NT2_TOOLBOX_ARITHMETIC_FUNCTION_SIMD_COMMON_AVERAGE_HPP_INCLUDED
#include <nt2/sdk/constant/real.hpp>
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/include/functions/shrai.hpp>


namespace nt2 { namespace functors
{
  //  no special validate for average

  /////////////////////////////////////////////////////////////////////////////
  // Compute average(const A0& a0, const A0& a1)
  /////////////////////////////////////////////////////////////////////////////

  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is real_
  /////////////////////////////////////////////////////////////////////////////
  template<class Extension, class Info>
  struct call<average_,tag::simd_(tag::arithmetic_,Extension),real_,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0,A0)>  : meta::strip<A0>{};

    NT2_FUNCTOR_CALL(2)
    {
       return (a0+a1)*Half<A0>(); 
    }
  };


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is arithmetic_
  /////////////////////////////////////////////////////////////////////////////
  template<class Extension, class Info>
  struct call<average_,tag::simd_(tag::arithmetic_,Extension),arithmetic_,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0,A0)>  : meta::strip<A0>{};

    NT2_FUNCTOR_CALL(2)
    {
      return (a0&a1)+shrai(a0^a1,1);
    } 
  };

} }

#endif
/// Revised by jt the 15/11/2010
