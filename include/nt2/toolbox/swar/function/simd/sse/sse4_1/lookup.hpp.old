//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_SWAR_FUNCTION_SIMD_SSE_SSE4_1_LOOKUP_HPP_INCLUDED
#define NT2_TOOLBOX_SWAR_FUNCTION_SIMD_SSE_SSE4_1_LOOKUP_HPP_INCLUDED
#include <nt2/sdk/meta/as_real.hpp>
#include <nt2/sdk/meta/size.hpp>
#include <nt2/sdk/meta/strip.hpp>


namespace nt2 { namespace functors
{
  template<class Extension,class Info>
  struct validate<lookup_,tag::simd_(tag::arithmetic_,Extension),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0,A1)> :
      boost::mpl::and_<meta::is_integral<A1>,
		       meta::has_same_size<A0, A1, meta::scalar_of < boost::mpl::_> >
      > {};
  };

  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is types64_
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct call<lookup_,tag::simd_(tag::arithmetic_,tag::sse_),types64_,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0,A1)>
      : meta::strip<A0>{};//

    NT2_FUNCTOR_CALL(2)
    {
      typedef typename meta::as_real<A0>::type real_type;
      const int32_t N = meta::cardinal_of<A0>::value;
      int32_t mask = _mm_movemask_pd(is_lt(a1, N));
      return simd::native_cast<A0>(_mm_blend_pd(simd::native_cast<real_type>(a0), mask));
    }
  };


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is types32_
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct call<lookup_,tag::simd_(tag::arithmetic_,tag::sse_),types32_,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0,A1)>
      : meta::strip<A0>{};//

    NT2_FUNCTOR_CALL(2)
    {
      typedef typename meta::as_real<A0>::type real_type;
      const int32_t N = meta::cardinal_of<A0>::value;
      int32_t mask = _mm_movemask_ps(is_lt(a1, N));
      return simd::native_cast<A0>(_mm_blend_ps(simd::native_cast<real_type>(a0), mask));
    }
  };


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is types16_
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct call<lookup_,tag::simd_(tag::arithmetic_,tag::sse_),types16_,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0,A1)>
      : meta::strip<A0>{};//

    NT2_FUNCTOR_CALL(2)
    {
      const int32_t N = meta::cardinal_of<A0>::value;
      int32_t mask = _mm_movemask_epi16(is_lt(a1, N));
      return simd::native_cast<A0>(_mm_blend_epi16(a0, mask));
    }
  };


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is types8_
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct call<lookup_,tag::simd_(tag::arithmetic_,tag::sse_),types8_,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0,A1)>
      : meta::strip<A0>{};//

    NT2_FUNCTOR_CALL(2)
    {
      const int32_t N = meta::cardinal_of<A0>::value;
      int32_t mask = _mm_movemask_epi8(is_lt(a1, N));
      return simd::native_cast<A0>(_mm_blend_epi8(a0, mask));
    }
  };


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is arithmetic_
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct call<lookup_,tag::simd_(tag::arithmetic_,tag::sse_),arithmetic_,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0,A1)>
      : meta::strip<A0>{};//


  };

} }

#endif
/// Revised by jt the 15/11/2010
