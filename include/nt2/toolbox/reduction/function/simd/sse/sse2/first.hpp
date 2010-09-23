//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_REDUCTION_FUNCTION_SIMD_SSE_SSE2_FIRST_HPP_INCLUDED
#define NT2_TOOLBOX_REDUCTION_FUNCTION_SIMD_SSE_SSE2_FIRST_HPP_INCLUDED

#include <nt2/sdk/meta/strip.hpp>
#include <nt2/sdk/meta/as_bits.hpp>
#include <nt2/sdk/meta/as_real.hpp>
#include <nt2/sdk/meta/from_bits.hpp>
#include <nt2/sdk/meta/as_integer.hpp>

namespace nt2 { namespace functors
{
  template<class Extension,class Info>
  struct call<first_,tag::simd_(tag::arithmetic_,Extension),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct  result<This(A0)>
          : meta::scalar_of<typename meta::strip<A0>::type> {};

    NT2_FUNCTOR_CALL_DISPATCH ( 1
                              , typename nt2::meta::scalar_of<A0>::type
                              , ( 6
                                , (types8_,types16_,float,types32_,double, types64_)
                                )
                              )

    NT2_FUNCTOR_CALL_EVAL_IF(1,    types8_)
    {
      typedef typename NT2_CALL_RETURN_TYPE(1)::type type;
      int that = _mm_extract_epi16(a0, 0);
      printf("%d\n",that);
      return that & 0xFF;
    }
    NT2_FUNCTOR_CALL_EVAL_IF(1,    types16_)
    {
      return _mm_extract_epi16(a0, 0);
    }
    NT2_FUNCTOR_CALL_EVAL_IF(1,    float)
    {
      typedef typename meta::as_integer<A0>::type type;
      meta::from_bits<float>::type t = {_mm_cvtsi128_si32(simd::native_cast<type>(a0))};
      return t.value;
    }
    NT2_FUNCTOR_CALL_EVAL_IF(1,    types32_)
    {
      typedef typename meta::as_integer<A0>::type type;
      return _mm_cvtsi128_si32(simd::native_cast<type>(a0));
    }
    NT2_FUNCTOR_CALL_EVAL_IF(1,    double)
    {
      return _mm_cvtsd_f64(a0);
    }
    NT2_FUNCTOR_CALL_EVAL_IF(1,    types64_)
    {
      typedef typename meta::as_integer<A0>::type type;
      typedef typename meta::as_real<A0>::type rtype;
      meta::as_bits<double>::type t = {_mm_cvtsd_f64(simd::native_cast<rtype>(a0))};
      return t.bits;
    }

  };
} }

#endif
