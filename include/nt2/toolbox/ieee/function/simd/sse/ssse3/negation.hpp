//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_IEEE_FUNCTION_SIMD_SSE_SSSE3_NEGATION_HPP_INCLUDED
#define NT2_TOOLBOX_IEEE_FUNCTION_SIMD_SSE_SSSE3_NEGATION_HPP_INCLUDED
#include <nt2/sdk/meta/strip.hpp>


namespace nt2 { namespace functors
{
  //  no special validate for negation


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is real_
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct  call<negation_,tag::simd_(tag::arithmetic_),real_,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0,A0)>
      : meta::strip<A0>{};//

    NT2_FUNCTOR_CALL(2)
    {
       /*PUT CODE HERE*/
    }
  };


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is int32_t
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct  call<negation_,tag::simd_(tag::arithmetic_),int32_t,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0,A0)>
      : meta::strip<A0>{};//

    NT2_FUNCTOR_CALL(2)
    {
       /*PUT CODE HERE*/
    }
  };


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is int16_t
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct  call<negation_,tag::simd_(tag::arithmetic_),int16_t,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0,A0)>
      : meta::strip<A0>{};//

    NT2_FUNCTOR_CALL(2)
    {
       /*PUT CODE HERE*/
    }
  };


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is int8_t
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct  call<negation_,tag::simd_(tag::arithmetic_),int8_t,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0,A0)>
      : meta::strip<A0>{};//

    NT2_FUNCTOR_CALL(2)
    {
       /*PUT CODE HERE*/
    }
  };


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is uint32_t
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct  call<negation_,tag::simd_(tag::arithmetic_),uint32_t,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0,A0)>
      : meta::strip<A0>{};//

    NT2_FUNCTOR_CALL(2)
    {
       /*PUT CODE HERE*/
    }
  };

} }

#endif
/// Revised by jt the 15/11/2010
