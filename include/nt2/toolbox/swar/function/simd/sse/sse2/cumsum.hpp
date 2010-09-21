//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_SWAR_FUNCTION_SIMD_SSE_SSE2_CUMSUM_HPP_INCLUDED
#define NT2_TOOLBOX_SWAR_FUNCTION_SIMD_SSE_SSE2_CUMSUM_HPP_INCLUDED
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/meta/strip.hpp>


namespace nt2 { namespace functors
{
  //  no special validate for cumsum

  template<class Extension,class Info>
  struct call<cumsum_,tag::simd_(tag::arithmetic_,Extension),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)>
      : meta::strip<A0>{};//

    NT2_FUNCTOR_CALL_DISPATCH(
      1,
      typename nt2::meta::scalar_of<A0>::type,
      (4, (types8_,types16_,types32_,types64_))
    )
      
      NT2_FUNCTOR_CALL_EVAL_IF(1,      types32_)
    {
      typedef typename meta::as_integer<A0>::type sint;
      A0 a = a0;
      a = a+simd::native_cast<A0>(_mm_slli_si128(simd::native_cast<sint>(a0), 4));
      a = a+simd::native_cast<A0>(_mm_slli_si128(simd::native_cast<sint>(a0), 8));
      return a+simd::native_cast<A0>(_mm_slli_si128(simd::native_cast<sint>(a0), 12));
    }
    NT2_FUNCTOR_CALL_EVAL_IF(1,      types64_)
    {
      typedef typename meta::as_integer<A0>::type sint;
      return a0+simd::native_cast<A0>(_mm_slli_si128(simd::native_cast<sint>(a0), 8));
    }
    NT2_FUNCTOR_CALL_EVAL_IF(1,      types8_)
    {
      typedef typename meta::as_integer<A0>::type sint;
      A0 a = a0;
      a = a+simd::native_cast<A0>(_mm_slli_si128(simd::native_cast<sint>(a0), 1));
      a = a+simd::native_cast<A0>(_mm_slli_si128(simd::native_cast<sint>(a0), 2));
      a = a+simd::native_cast<A0>(_mm_slli_si128(simd::native_cast<sint>(a0), 3));
      a = a+simd::native_cast<A0>(_mm_slli_si128(simd::native_cast<sint>(a0), 4));
      a = a+simd::native_cast<A0>(_mm_slli_si128(simd::native_cast<sint>(a0), 5));
      a = a+simd::native_cast<A0>(_mm_slli_si128(simd::native_cast<sint>(a0), 6));
      a = a+simd::native_cast<A0>(_mm_slli_si128(simd::native_cast<sint>(a0), 7));
      a = a+simd::native_cast<A0>(_mm_slli_si128(simd::native_cast<sint>(a0), 8));
      a = a+simd::native_cast<A0>(_mm_slli_si128(simd::native_cast<sint>(a0), 9));
      a = a+simd::native_cast<A0>(_mm_slli_si128(simd::native_cast<sint>(a0), 10));
      a = a+simd::native_cast<A0>(_mm_slli_si128(simd::native_cast<sint>(a0), 11));
      a = a+simd::native_cast<A0>(_mm_slli_si128(simd::native_cast<sint>(a0), 12));
      a = a+simd::native_cast<A0>(_mm_slli_si128(simd::native_cast<sint>(a0), 13));
      a = a+simd::native_cast<A0>(_mm_slli_si128(simd::native_cast<sint>(a0), 14));
      return a+simd::native_cast<A0>(_mm_slli_si128(simd::native_cast<sint>(a0), 15));
    }
    NT2_FUNCTOR_CALL_EVAL_IF(1,     types16_)
    {
      typedef typename meta::as_integer<A0>::type sint;
      A0 a = a0;
      a = a+simd::native_cast<A0>(_mm_slli_si128(simd::native_cast<sint>(a0), 2));
      a = a+simd::native_cast<A0>(_mm_slli_si128(simd::native_cast<sint>(a0), 4));
      a = a+simd::native_cast<A0>(_mm_slli_si128(simd::native_cast<sint>(a0), 6));
      a = a+simd::native_cast<A0>(_mm_slli_si128(simd::native_cast<sint>(a0), 8));
      a = a+simd::native_cast<A0>(_mm_slli_si128(simd::native_cast<sint>(a0), 10));
      a = a+simd::native_cast<A0>(_mm_slli_si128(simd::native_cast<sint>(a0), 12));
      return a+simd::native_cast<A0>(_mm_slli_si128(simd::native_cast<sint>(a0), 14));
    }
  };
} }

#endif