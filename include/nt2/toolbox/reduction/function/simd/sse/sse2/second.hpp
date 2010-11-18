//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_REDUCTION_FUNCTION_SIMD_SSE_SSE2_SECOND_HPP_INCLUDED
#define NT2_TOOLBOX_REDUCTION_FUNCTION_SIMD_SSE_SSE2_SECOND_HPP_INCLUDED

#include <nt2/sdk/meta/strip.hpp>
#include <nt2/sdk/meta/as_real.hpp>
#include <nt2/sdk/meta/as_bits.hpp>
#include <nt2/sdk/meta/from_bits.hpp>
#include <nt2/sdk/meta/as_integer.hpp>

namespace nt2 { namespace functors
{

  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is types8_
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct call<second_,tag::simd_(tag::arithmetic_,tag::sse_),types8_,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct  result<This(A0)>
          : meta::scalar_of<typename meta::strip<A0>::type> {};
          

    NT2_FUNCTOR_CALL(1)
    {
      typedef typename NT2_CALL_RETURN_TYPE(1)::type type;
      int that = _mm_extract_epi16(a0, 0);
      return (that >> 8) & 0xFF;
    }
  };


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is types16_
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct call<second_,tag::simd_(tag::arithmetic_,tag::sse_),types16_,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct  result<This(A0)>
          : meta::scalar_of<typename meta::strip<A0>::type> {};
          

    NT2_FUNCTOR_CALL(1)
    {
      return _mm_extract_epi16(a0, 1);
    }
  };


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is float
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct call<second_,tag::simd_(tag::arithmetic_,tag::sse_),float,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct  result<This(A0)>
          : meta::scalar_of<typename meta::strip<A0>::type> {};
          

    NT2_FUNCTOR_CALL(1)
    {
      typedef typename meta::as_integer<A0>::type type;
      meta::from_bits<float>::type t = {_mm_cvtsi128_si32(_mm_srli_si128(simd::native_cast<type>(a0), 4))};
      return t.value;
    }
  };


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is types32_
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct call<second_,tag::simd_(tag::arithmetic_,tag::sse_),types32_,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct  result<This(A0)>
          : meta::scalar_of<typename meta::strip<A0>::type> {};
          

    NT2_FUNCTOR_CALL(1)
    {
      typedef typename meta::as_integer<A0>::type type;
      return _mm_cvtsi128_si32(_mm_srli_si128(simd::native_cast<type>(a0), 4));
    }
  };


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is double
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct call<second_,tag::simd_(tag::arithmetic_,tag::sse_),double,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct  result<This(A0)>
          : meta::scalar_of<typename meta::strip<A0>::type> {};
          

    NT2_FUNCTOR_CALL(1)
    {
      typedef typename meta::as_integer<A0>::type type;
      typedef typename meta::as_real<A0>::type rtype;
      return _mm_cvtsd_f64(simd::native_cast<rtype>(_mm_srli_si128(simd::native_cast<type>(a0), 8)));
    }
  };


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is types64_
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct call<second_,tag::simd_(tag::arithmetic_,tag::sse_),types64_,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct  result<This(A0)>
          : meta::scalar_of<typename meta::strip<A0>::type> {};
          

    NT2_FUNCTOR_CALL(1)
    {
      typedef typename meta::as_integer<A0>::type type;
      typedef typename meta::as_real<A0>::type rtype;
      meta::as_bits<double>::type t = {_mm_cvtsd_f64(simd::native_cast<rtype>(_mm_srli_si128(simd::native_cast<type>(a0), 8)))};
      return t.bits;
    }
  };

} }

#endif
/// Revised by jt the 15/11/2010
