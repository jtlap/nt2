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
#include <nt2/sdk/meta/as_real.hpp>

namespace nt2 { namespace functors
{
  //  no special validate for splatted_maximum


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is float
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct  call<splatted_maximum_,tag::simd_(tag::arithmetic_),float,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)>
      : meta::strip<A0>{};//

    NT2_FUNCTOR_CALL(1)
    {
      A0 max1 = {max(a0,simd::native_cast<A0>(_mm_shuffle_ps(a0, a0, _MM_SHUFFLE(1, 0, 3, 2))))};
      A0 that = {max(max1, simd::native_cast<A0>(_mm_shuffle_ps(max1, max1, _MM_SHUFFLE(2, 3, 0, 1))))};
      return that;
    }
  };


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is double
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct  call<splatted_maximum_,tag::simd_(tag::arithmetic_),double,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)>
      : meta::strip<A0>{};//

    NT2_FUNCTOR_CALL(1)
    {
      A0 that = {_mm_max_sd(a0, _mm_unpackhi_pd(a0,a0))};
      return simd::native_cast<A0>(_mm_unpacklo_pd(that, that));
    }
  };


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is int64_
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct  call<splatted_maximum_,tag::simd_(tag::arithmetic_),int64_,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)>
      : meta::strip<A0>{};//

    NT2_FUNCTOR_CALL(1)
    {
      typedef typename meta::as_real<A0>::type ftype; 
      A0 a00  =  simd::native_cast<A0>(_mm_shuffle_pd(simd::native_cast<ftype>(a0),
						      simd::native_cast<ftype>(a0),0x01));     
      return  max(a0, a00); 
    }
  };


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is int32_
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct  call<splatted_maximum_,tag::simd_(tag::arithmetic_),int32_,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)>
      : meta::strip<A0>{};//

    NT2_FUNCTOR_CALL(1)
    {
      A0 max1 = {max(a0,simd::native_cast<A0>(_mm_shuffle_epi32(a0, _MM_SHUFFLE(1, 0, 3, 2))))};
      A0 that = {max(max1, simd::native_cast<A0>(_mm_shuffle_epi32(max1, _MM_SHUFFLE(2, 3, 0, 1))))};
      return that;
    }
  };


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is int16_
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct  call<splatted_maximum_,tag::simd_(tag::arithmetic_),int16_,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)>
      : meta::strip<A0>{};//

    NT2_FUNCTOR_CALL(1)
    {
      typedef typename simd::native<float, Extension> ftype;
      A0 max1 = {_mm_shufflehi_epi16(a0  , _MM_SHUFFLE(1, 0, 3, 2))};
         max1 = _mm_shufflelo_epi16(max1, _MM_SHUFFLE(1, 0, 3, 2));
         max1 = max(a0, max1);
      A0 max2 = {_mm_shuffle_epi32  (max1, _MM_SHUFFLE(1, 0, 3, 2))};
         max2 = _mm_shufflelo_epi16(max2, _MM_SHUFFLE(1, 0, 3, 2));
         max2 = max(max1, max2);
      A0 max3 = {_mm_shuffle_epi32(max2, _MM_SHUFFLE(3, 2, 1, 0))};
      A0 max4 = {_mm_shufflelo_epi16(max3, _MM_SHUFFLE(0, 1, 2, 3))};
      ftype max5 = {simd::native_cast<ftype>(nt2::max(max3, max4))};
      A0 that = {simd::native_cast<A0>(_mm_unpacklo_ps(max5, max5))}; 
      return that;
    }
  };


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is int8_
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct  call<splatted_maximum_,tag::simd_(tag::arithmetic_),int8_,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)>
      : meta::strip<A0>{};//

    NT2_FUNCTOR_CALL(1)
    {
      return splat<A0>(maximum(a0)); 
    }
  };

} }

#endif
/// Revised by jt the 15/11/2010
