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
#include <nt2/sdk/simd/native_cast.hpp>


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is int16_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::splatted_maximum_, tag::cpu_,
                                   (A0),
                                   ((simd_<ints16_<A0>,tag::sse_>))
                                  );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::splatted_maximum_(tag::simd_<tag::ints16_, tag::sse_> ),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : meta::strip<A0>{};

    NT2_FUNCTOR_CALL(1)
    {
      typedef typename simd::native<float, tag::sse_> ftype;
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
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is double
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::splatted_maximum_, tag::cpu_,
                                   (A0),
                                   ((simd_<double_<A0>,tag::sse_>))
                                  );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::splatted_maximum_(tag::simd_<tag::double_, tag::sse_> ),
              tag::cpu_, Dummy> : callable
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
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is int64_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::splatted_maximum_, tag::cpu_,
                                   (A0),
                                   ((simd_<ints64_<A0>,tag::sse_>))
                                  );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::splatted_maximum_(tag::simd_<tag::ints64_, tag::sse_> ),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : meta::strip<A0>{};

    NT2_FUNCTOR_CALL(1)
    {
//       typedef typename meta::as_real<A0>::type ftype;
//       A0 a00  =  simd::native_cast<A0>(_mm_shuffle_pd(simd::native_cast<ftype>(a0),
//                                           simd::native_cast<ftype>(a0),0x01));
//       return  max(a0, a00);
      return splat<A0>(maximum(a0)); 
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is float
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::splatted_maximum_, tag::cpu_,
                                   (A0),
                                   ((simd_<float_<A0>,tag::sse_>))
                                  );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::splatted_maximum_(tag::simd_<tag::float_, tag::sse_> ),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)>
      : meta::strip<A0>{};//

    NT2_FUNCTOR_CALL(1)
    {
      A0 tmp = {_mm_shuffle_ps(a0, a0, _MM_SHUFFLE(1, 0, 3, 2))}; 
      A0 max1 = nt2::max(a0,tmp);
      A0 tmp1 ={_mm_shuffle_ps(max1, max1, _MM_SHUFFLE(2, 3, 0, 1))}; 
      A0 that = nt2::max(max1,tmp1);
      return that;
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is int8_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::splatted_maximum_, tag::cpu_,
                                   (A0),
                                   ((simd_<ints8_<A0>,tag::sse_>))
                                  );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::splatted_maximum_(tag::simd_<tag::ints8_, tag::sse_> ),
              tag::cpu_, Dummy> : callable
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

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is int32_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::splatted_maximum_, tag::cpu_,
                                   (A0),
                                   ((simd_<ints32_<A0>,tag::sse_>))
                                  );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::splatted_maximum_(tag::simd_<tag::ints32_, tag::sse_> ),
              tag::cpu_, Dummy> : callable
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
} }

#endif
// modified by jt the 05/01/2011
