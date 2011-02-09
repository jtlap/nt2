//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_REDUCTION_FUNCTION_SIMD_SSE_SSE2_MINIMUM_HPP_INCLUDED
#define NT2_TOOLBOX_REDUCTION_FUNCTION_SIMD_SSE_SSE2_MINIMUM_HPP_INCLUDED

#include <nt2/sdk/meta/strip.hpp>
#include <nt2/sdk/meta/templatize.hpp>
#include <nt2/include/functions/min.hpp>


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is int16_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::minimum_, tag::cpu_,
                          (A0),
                          ((simd_<ints16_<A0>,tag::sse_>))
                         );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::minimum_(tag::simd_<tag::ints16_, tag::sse_> ),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)>
          : meta::scalar_of<typename meta::strip<A0>::type> {};

    NT2_FUNCTOR_CALL(1)
    {
      A0 min1 = {_mm_shufflehi_epi16(a0  , _MM_SHUFFLE(1, 0, 3, 2))};
         min1 = _mm_shufflelo_epi16(min1, _MM_SHUFFLE(1, 0, 3, 2));
         min1 = min(a0, min1);
      A0 min2 = {_mm_shuffle_epi32  (min1, _MM_SHUFFLE(1, 0, 3, 2))};
         min2 = _mm_shufflelo_epi16(min2, _MM_SHUFFLE(1, 0, 3, 2));
         min2 = min(min1, min2);
      A0 min3 = {_mm_shuffle_epi32(min2, _MM_SHUFFLE(3, 2, 1, 0))};
      A0 min4 = {_mm_shufflelo_epi16(min3, _MM_SHUFFLE(0, 1, 2, 3))};
      A0 that = nt2::min(min3, min4);
      return that[0];
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is double
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::minimum_, tag::cpu_,
                          (A0),
                          ((simd_<double_<A0>,tag::sse_>))
                         );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::minimum_(tag::simd_<tag::double_, tag::sse_> ),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)>
          : meta::scalar_of<typename meta::strip<A0>::type> {};

    NT2_FUNCTOR_CALL(1)
    {
      A0 that = {_mm_min_sd(a0, _mm_unpackhi_pd(a0,a0))};
      return that[0];
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is int64_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::minimum_, tag::cpu_,
                          (A0),
                          ((simd_<ints64_<A0>,tag::sse_>))
                         );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::minimum_(tag::simd_<tag::ints64_, tag::sse_> ),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)>
          : meta::scalar_of<typename meta::strip<A0>::type> {};

    NT2_FUNCTOR_CALL(1)
    {
      return nt2::min(a0[0], a0[1]);
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is float
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::minimum_, tag::cpu_,
                          (A0),
                          ((simd_<float_<A0>,tag::sse_>))
                         );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::minimum_(tag::simd_<tag::float_, tag::sse_> ),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)>
          : meta::scalar_of<typename meta::strip<A0>::type> {};

    NT2_FUNCTOR_CALL(1)
    {
      A0 min  = {_mm_min_ps(a0, _mm_movehl_ps(a0,a0))};
      A0 that = {_mm_min_ss(min, _mm_shuffle_ps(min,min,0x01))};
      return that[0];
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is int8_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::minimum_, tag::cpu_,
                          (A0),
                          ((simd_<ints8_<A0>,tag::sse_>))
                         );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::minimum_(tag::simd_<tag::ints8_, tag::sse_> ),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)>
          : meta::scalar_of<typename meta::strip<A0>::type> {};

    NT2_FUNCTOR_CALL(1)
    {
      typedef simd::native<typename meta::double__<A0>::type,tag::sse_> rtype;
      rtype v0 = simd::native_cast<rtype>(a0);
      A0 pack = simd::native_cast<A0>(_mm_unpackhi_pd(v0,v0));
      A0 min1 = nt2::min(a0,pack);
      A0 min2 = {min(min1, simd::native_cast<A0>(_mm_shufflelo_epi16(min1, _MM_SHUFFLE(0, 1, 2, 3))))};
         min2 = min(min2, simd::native_cast<A0>(_mm_shuffle_epi32  (min2, _MM_SHUFFLE(2, 3, 0, 1))));
    return nt2::min(min2[0],min2[1]);
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is int32_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::minimum_, tag::cpu_,
                          (A0),
                          ((simd_<ints32_<A0>,tag::sse_>))
                         );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::minimum_(tag::simd_<tag::ints32_, tag::sse_> ),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)>
          : meta::scalar_of<typename meta::strip<A0>::type> {};

    NT2_FUNCTOR_CALL(1)
    {
      A0 min1 = {min(a0,simd::native_cast<A0>(_mm_shuffle_epi32(a0, _MM_SHUFFLE(1, 0, 3, 2))))};
      A0 that = {min(min1, simd::native_cast<A0>(_mm_shuffle_epi32(min1, _MM_SHUFFLE(2, 3, 0, 1))))};
      return that[0];
    }
  };
} }

#endif
// modified by jt the 05/01/2011
