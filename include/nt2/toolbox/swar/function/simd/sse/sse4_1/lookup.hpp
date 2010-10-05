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
  template<class Extension,class Info>
  struct call<lookup_,tag::simd_(tag::arithmetic_,Extension),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0,A1)>
      : meta::strip<A0>{};//

    NT2_FUNCTOR_CALL_DISPATCH(
      2,
      typename nt2::meta::scalar_of<A0>::type,
      (5, (               types64_, types32_, types16_, types8_, arithmetic_))
    )

    NT2_FUNCTOR_CALL_EVAL_IF(2,       types64_)
    {
      typedef typename meta::as_real<A0>::type real_type;
      const int32_t N = meta::cardinal_of<A0>::value;
      int32_t mask = _mm_movemask_pd(is_lt(a1, N));
      return simd::native_cast<A0>(_mm_blend_pd(simd::native_cast<real_type>(a0), mask));
    }
    NT2_FUNCTOR_CALL_EVAL_IF(2,       types32_)
    {
      typedef typename meta::as_real<A0>::type real_type;
      const int32_t N = meta::cardinal_of<A0>::value;
      int32_t mask = _mm_movemask_ps(is_lt(a1, N));
      return simd::native_cast<A0>(_mm_blend_ps(simd::native_cast<real_type>(a0), mask));
    }
    NT2_FUNCTOR_CALL_EVAL_IF(2,       types16_)
    {
      const int32_t N = meta::cardinal_of<A0>::value;
      int32_t mask = _mm_movemask_epi16(is_lt(a1, N));
      return simd::native_cast<A0>(_mm_blend_epi16(a0, mask));
    }
    NT2_FUNCTOR_CALL_EVAL_IF(2,       types8_)
    {
      const int32_t N = meta::cardinal_of<A0>::value;
      int32_t mask = _mm_movemask_epi8(is_lt(a1, N));
      return simd::native_cast<A0>(_mm_blend_epi8(a0, mask));
    }

  };
} }

#endif
