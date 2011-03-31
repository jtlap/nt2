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
#include <nt2/sdk/simd/native_cast.hpp>




/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is type8_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::cumsum_, tag::cpu_,
                         (A0),
                         ((simd_<type8_<A0>,tag::sse_>))
                        );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::cumsum_(tag::simd_<tag::type8_, tag::sse_> ),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)>
      : meta::strip<A0>{};//

    NT2_FUNCTOR_CALL(1)
    {
      typedef typename meta::as_integer<A0>::type sint;
      A0 a = a0;
      sint tmp = simd::native_cast<sint>(a0);
      sint tmp1 = { _mm_slli_si128(tmp,1)}; 
      a = a+simd::native_cast<A0>(tmp1);
      tmp1 = _mm_slli_si128(tmp,2); 
      a = a+simd::native_cast<A0>(tmp1);
      tmp1 = _mm_slli_si128(tmp,3); 
      a = a+simd::native_cast<A0>(tmp1);
      tmp1 = _mm_slli_si128(tmp,4); 
      a = a+simd::native_cast<A0>(tmp1);
      tmp1 = _mm_slli_si128(tmp,5); 
      a = a+simd::native_cast<A0>(tmp1);
      tmp1 = _mm_slli_si128(tmp,6); 
      a = a+simd::native_cast<A0>(tmp1);
      tmp1 = _mm_slli_si128(tmp,7); 
      a = a+simd::native_cast<A0>(tmp1);
      tmp1 = _mm_slli_si128(tmp,8); 
      a = a+simd::native_cast<A0>(tmp1);
      tmp1 = _mm_slli_si128(tmp,9); 
      a = a+simd::native_cast<A0>(tmp1);
      tmp1 = _mm_slli_si128(tmp,10); 
      a = a+simd::native_cast<A0>(tmp1);
      tmp1 = _mm_slli_si128(tmp,11); 
      a = a+simd::native_cast<A0>(tmp1);
      tmp1 = _mm_slli_si128(tmp,12); 
      a = a+simd::native_cast<A0>(tmp1);
      tmp1 = _mm_slli_si128(tmp,13); 
      a = a+simd::native_cast<A0>(tmp1);
      tmp1 = _mm_slli_si128(tmp,14); 
      a = a+simd::native_cast<A0>(tmp1);
      tmp1 = _mm_slli_si128(tmp, 15); 
      a += simd::native_cast<A0>(tmp1);
      return a; 
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is type64_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::cumsum_, tag::cpu_,
                         (A0),
                         ((simd_<type64_<A0>,tag::sse_>))
                        );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::cumsum_(tag::simd_<tag::type64_, tag::sse_> ),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)>
      : meta::strip<A0>{};//

    NT2_FUNCTOR_CALL(1)
    {
      typedef typename meta::as_integer<A0>::type sint;
      sint tmp = simd::native_cast<sint>(a0); 
      sint tmp1 = { _mm_slli_si128(tmp,8)}; 
      return a0+simd::native_cast<A0>(tmp1);
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is type16_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::cumsum_, tag::cpu_,
                         (A0),
                         ((simd_<type16_<A0>,tag::sse_>))
                        );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::cumsum_(tag::simd_<tag::type16_, tag::sse_> ),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)>
      : meta::strip<A0>{};//

    NT2_FUNCTOR_CALL(1)
    {
      typedef typename meta::as_integer<A0>::type sint;
      A0 a = a0;
      sint tmp = simd::native_cast<sint>(a0); 
      sint tmp1 = { _mm_slli_si128(tmp,2)}; 
      a = a+simd::native_cast<A0>(tmp1);
      tmp1 = _mm_slli_si128(tmp,4); 
      a = a+simd::native_cast<A0>(tmp1);
      tmp1 = _mm_slli_si128(tmp, 6); 
      a = a+simd::native_cast<A0>(tmp1);
      tmp1 = _mm_slli_si128(tmp,8); 
      a = a+simd::native_cast<A0>(tmp1);
      tmp1 = _mm_slli_si128(tmp,10); 
      a = a+simd::native_cast<A0>(tmp1);
      tmp1 = _mm_slli_si128(tmp,12); 
      a = a+simd::native_cast<A0>(tmp1);
      tmp1 = _mm_slli_si128(tmp,14); 
      return a+simd::native_cast<A0>(tmp1);

    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is type32_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::cumsum_, tag::cpu_,
                         (A0),
                         ((simd_<type32_<A0>,tag::sse_>))
                        );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::cumsum_(tag::simd_<tag::type32_, tag::sse_> ),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)>
      : meta::strip<A0>{};//

    NT2_FUNCTOR_CALL(1)
    {
      typedef typename meta::as_integer<A0>::type sint;
      A0 a = a0;
      sint tmp = simd::native_cast<sint>(a0);
      sint tmp1 = {_mm_slli_si128(tmp, 4)}; 
      a = a+simd::native_cast<A0>(tmp1);
      tmp1 = _mm_slli_si128(tmp, 8); 
      a = a+simd::native_cast<A0>(tmp1);
      tmp1 = _mm_slli_si128(tmp, 12); 
      return a+simd::native_cast<A0>(tmp1);
    }
  };
} }

#endif
// modified by jt the 05/01/2011
