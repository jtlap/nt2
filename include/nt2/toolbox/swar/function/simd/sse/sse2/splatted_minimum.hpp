//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_SWAR_FUNCTION_SIMD_SSE_SSE2_SPLATTED_MINIMUM_HPP_INCLUDED
#define NT2_TOOLBOX_SWAR_FUNCTION_SIMD_SSE_SSE2_SPLATTED_MINIMUM_HPP_INCLUDED
#include <nt2/sdk/meta/strip.hpp>

#include <nt2/include/functions/min.hpp>

#include <nt2/include/functions/minimum.hpp>

namespace nt2 { namespace functors
{
  //  no special validate for splatted_minimum

  template<class Extension,class Info>
  struct call<splatted_minimum_,tag::simd_(tag::arithmetic_,Extension),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)>
      : meta::strip<A0>{};//

    NT2_FUNCTOR_CALL_DISPATCH(
      1,
      typename nt2::meta::scalar_of<A0>::type,
      (6, (float,double,int64_,int32_,int16_,int8_))
    )

    NT2_FUNCTOR_CALL_EVAL_IF(1,       float)
    {
      A0 min1 = {min(a0,simd::native_cast<A0>(_mm_shuffle_ps(a0, a0, _MM_SHUFFLE(1, 0, 3, 2))))};
      A0 that = {min(min1, simd::native_cast<A0>(_mm_shuffle_ps(min1, min1, _MM_SHUFFLE(2, 3, 0, 1))))};
      return that;
    }
    NT2_FUNCTOR_CALL_EVAL_IF(1,      double)
    {
      A0 that = {_mm_min_sd(a0, _mm_unpackhi_pd(a0,a0))};
      return simd::native_cast<A0>(_mm_unpacklo_pd(that, that));
    }
    NT2_FUNCTOR_CALL_EVAL_IF(1,     int64_)
    {
      typedef typename meta::as_real<A0>::type ftype; 
      A0 a00  =  simd::native_cast<A0>(_mm_shuffle_pd(simd::native_cast<ftype>(a0),
						      simd::native_cast<ftype>(a0),0x01));     
      return  min(a0, a00); 
    }
    NT2_FUNCTOR_CALL_EVAL_IF(1,     int32_)
    {
      A0 min1 = {min(a0,simd::native_cast<A0>(_mm_shuffle_epi32(a0, _MM_SHUFFLE(1, 0, 3, 2))))};
      A0 that = {min(min1, simd::native_cast<A0>(_mm_shuffle_epi32(min1, _MM_SHUFFLE(2, 3, 0, 1))))};
      return that;
    }
    NT2_FUNCTOR_CALL_EVAL_IF(1,     int16_)
    {
      typedef typename simd::native<float, Extension> ftype; 
      A0 min1 = {_mm_shufflehi_epi16(a0  , _MM_SHUFFLE(1, 0, 3, 2))};
         min1 = _mm_shufflelo_epi16(min1, _MM_SHUFFLE(1, 0, 3, 2));
         min1 = min(a0, min1);
      A0 min2 = {_mm_shuffle_epi32  (min1, _MM_SHUFFLE(1, 0, 3, 2))};
         min2 = _mm_shufflelo_epi16(min2, _MM_SHUFFLE(1, 0, 3, 2));
         min2 = min(min1, min2);
      A0 min3 = {_mm_shuffle_epi32(min2, _MM_SHUFFLE(3, 2, 1, 0))};
      A0 min4 = {_mm_shufflelo_epi16(min3, _MM_SHUFFLE(0, 1, 2, 3))};
      ftype min5 = {simd::native_cast<ftype>(nt2::min(min3, min4))};
      A0 that = {simd::native_cast<A0>(_mm_unpacklo_ps(min5, min5))}; 
         
      return that; 
    }
    NT2_FUNCTOR_CALL_EVAL_IF(1,      int8_)
    {
      return splat<A0>(minimum(a0)); 
    }
  };
} }

#endif
