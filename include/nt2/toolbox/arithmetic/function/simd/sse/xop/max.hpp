//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_ARITHMETIC_FUNCTION_SIMD_SSE_XOP_MAX_HPP_INCLUDED
#define NT2_TOOLBOX_ARITHMETIC_FUNCTION_SIMD_SSE_XOP_MAX_HPP_INCLUDED
#include <nt2/sdk/meta/strip.hpp>

#include <nt2/include/functions/seladd.hpp>

namespace nt2 { namespace functors
{
  //  no special validate for max


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is float
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct call<max_,tag::simd_(tag::arithmetic_,tag::sse_),float,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0,A0)>
      : meta::strip<A0>{};//

    NT2_FUNCTOR_CALL(2)
    {
      A0 that =  {_mm256_max_ps(a0,a1)}; return that;
    }
  };


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is double
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct call<max_,tag::simd_(tag::arithmetic_,tag::sse_),double,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0,A0)>
      : meta::strip<A0>{};//

    NT2_FUNCTOR_CALL(2)
    {
      A0 that =  {_mm256_max_pd(a0,a1)}; return that;
    }
  };


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is int8_t
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct call<max_,tag::simd_(tag::arithmetic_,tag::sse_),int8_t,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0,A0)>
      : meta::strip<A0>{};//

    NT2_FUNCTOR_CALL(2)
    {
      NT2_XOP_JOIN128INT(that, _mm_max_epi8); return that;
    }
  };


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is int16_t
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct call<max_,tag::simd_(tag::arithmetic_,tag::sse_),int16_t,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0,A0)>
      : meta::strip<A0>{};//

    NT2_FUNCTOR_CALL(2)
    {
      NT2_XOP_JOIN128INT(that, _mm_max_epi16); return that;
    }
  };


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is int32_t
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct call<max_,tag::simd_(tag::arithmetic_,tag::sse_),int32_t,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0,A0)>
      : meta::strip<A0>{};//

    NT2_FUNCTOR_CALL(2)
    {
      NT2_XOP_JOIN128INT(that, _mm_max_epi32); return that;
    }
  };


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is uint8_t
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct call<max_,tag::simd_(tag::arithmetic_,tag::sse_),uint8_t,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0,A0)>
      : meta::strip<A0>{};//

    NT2_FUNCTOR_CALL(2)
    {
      NT2_XOP_JOIN128INT(that, _mm_max_epu8); return that;
    }
  };


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is uint16_t
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct call<max_,tag::simd_(tag::arithmetic_,tag::sse_),uint16_t,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0,A0)>
      : meta::strip<A0>{};//

    NT2_FUNCTOR_CALL(2)
    {
      NT2_XOP_JOIN128INT(that, _mm_max_epu16); return that;
    }
  };


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is uint32_t
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct call<max_,tag::simd_(tag::arithmetic_,tag::sse_),uint32_t,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0,A0)>
      : meta::strip<A0>{};//

    NT2_FUNCTOR_CALL(2)
    {
      NT2_XOP_JOIN128INT(that, _mm_max_epu32); return that;
    }
  };


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is arithmetic_
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct call<max_,tag::simd_(tag::arithmetic_,tag::sse_),arithmetic_,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0,A0)>
      : meta::strip<A0>{};//

    NT2_FUNCTOR_CALL(2)
    {
       return seladd( is_lt(a0,a1),a0,a1-a0);
    }
  };

} }

#endif
/// Revised by jt the 15/11/2010
