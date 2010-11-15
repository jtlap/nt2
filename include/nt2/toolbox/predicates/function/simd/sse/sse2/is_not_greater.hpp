//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_PREDICATES_FUNCTION_SIMD_SSE_SSE2_IS_NOT_GREATER_HPP_INCLUDED
#define NT2_TOOLBOX_PREDICATES_FUNCTION_SIMD_SSE_SSE2_IS_NOT_GREATER_HPP_INCLUDED
#include <nt2/sdk/meta/strip.hpp>


namespace nt2 { namespace functors
{
  //  no special validate for is_not_greater


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is float
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct  call<is_not_greater_,tag::simd_(tag::arithmetic_),float,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0, A0)> : meta::strip<A0>{};//

    NT2_FUNCTOR_CALL(2)
    {
      A0 that =  { _mm_cmpngt_ps(a0,a1)}; return that; 
    }
  };


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is double
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct  call<is_not_greater_,tag::simd_(tag::arithmetic_),double,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0, A0)> : meta::strip<A0>{};//

    NT2_FUNCTOR_CALL(2)
    {
      A0 that =  { _mm_cmpngt_pd(a0,a1)}; return that; 
    }
  };


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is arithmetic_
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct  call<is_not_greater_,tag::simd_(tag::arithmetic_),arithmetic_,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0, A0)> : meta::strip<A0>{};//

    NT2_FUNCTOR_CALL(2)
    {
      return le(a0,a1);
    }
  };

} }

#endif
/// Revised by jt the 15/11/2010
