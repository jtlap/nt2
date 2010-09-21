//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_SWAR_FUNCTION_SIMD_SSE_SSE2_SPLATTED_MAXIMUM_HPP_INCLUDED
#define NT2_TOOLBOX_SWAR_FUNCTION_SIMD_SSE_SSE2_SPLATTED_MAXIMUM_HPP_INCLUDED
#include <nt2/sdk/meta/strip.hpp>

#include <nt2/include/functions/max.hpp>

#include <nt2/include/functions/maximum.hpp>

namespace nt2 { namespace functors
{
  //  no special validate for splatted_maximum

  template<class Extension,class Info>
  struct call<splatted_maximum_,tag::simd_(tag::arithmetic_,Extension),Info>
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
      A0 max1 = {max(a0,simd::native_cast<A0>(_mm_shuffle_ps(a0, a0, _MM_SHUFFLE(1, 0, 3, 2))))};
      A0 that = {max(max1, simd::native_cast<A0>(_mm_shuffle_ps(max1, max1, _MM_SHUFFLE(2, 3, 0, 1))))};
      return that;
    }
    NT2_FUNCTOR_CALL_EVAL_IF(1,      double)
    {
      A0 that = {_mm_max_sd(a0, _mm_unpackhi_pd(a0,a0))};
      return simd::native_cast<A0>(_mm_unpacklo_pd(that, that));
    }
    NT2_FUNCTOR_CALL_EVAL_IF(1,     int64_)
    {
      typedef typename simd::native<double, typename meta::category_of<A0>::type::type> ftype; 
      A0 a00  =  simd::native_cast<A0>(_mm_shuffle_pd(simd::native_cast<ftype>(a0),
						      simd::native_cast<ftype>(a0),0x01));     
      return  max(a0, a00); 
    }
    NT2_FUNCTOR_CALL_EVAL_IF(1,     int32_)
    {
      A0 max1 = {max(a0,simd::native_cast<A0>(_mm_shuffle_epi32(a0, _MM_SHUFFLE(1, 0, 3, 2))))};
      A0 that = {max(max1, simd::native_cast<A0>(_mm_shuffle_epi32(max1, _MM_SHUFFLE(2, 3, 0, 1))))};
      return that;
    }
    NT2_FUNCTOR_CALL_EVAL_IF(1,     int16_)
    {
      typedef typename simd::native<float, typename meta::category_of<A0>::type::type> ftype; 
      A0 max1 = {_mm_shufflehi_epi16(a0  , _MM_SHUFFLE(1, 0, 3, 2))};
         max1 = _mm_shufflelo_epi16(max1, _MM_SHUFFLE(1, 0, 3, 2));
         max1 = max(a0, max1);
      A0 max2 = {_mm_shuffle_epi32  (max1, _MM_SHUFFLE(1, 0, 3, 2))};
         max2 = _mm_shufflelo_epi16(max2, _MM_SHUFFLE(1, 0, 3, 2));
         max2 = max(max1, max2);
      A0 max3 = {_mm_shuffle_epi32(max2, _MM_SHUFFLE(3, 2, 1, 0))};
      A0 max4 = {_mm_shufflelo_epi16(max3, _MM_SHUFFLE(0, 1, 2, 3))};
      ftype max5 = simd::native_cast<ftype>(nt2::max(max3, max4));
      ftype that = {_mm_unpacklo_ps(max5, max5)}; 
         
      return simd::native_cast<A0>(that);
    }
    NT2_FUNCTOR_CALL_EVAL_IF(1,      int8_)
    {
      return splat<A0>(maximum(a0)); 
    }
  };
} }

#endif