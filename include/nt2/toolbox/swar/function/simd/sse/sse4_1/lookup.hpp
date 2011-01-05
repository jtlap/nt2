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



/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::lookup_, tag::cpu_,
                         (A0),
                         ((simd_<arithmetic_<A0>,tag::sse_>))
                         ((simd_<arithmetic_<A0>,tag::sse_>))
                        );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::lookup_(tag::simd_(tag::arithmetic_, tag::sse_),
                           tag::simd_(tag::arithmetic_, tag::sse_)),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0,A1)>
      : meta::strip<A0>{};//


  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is types8_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::lookup_, tag::cpu_,
                         (A0),
                         ((simd_<types8_<A0>,tag::sse_>))
                         ((simd_<types8_<A0>,tag::sse_>))
                        );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::lookup_(tag::simd_(tag::types8_, tag::sse_),
                           tag::simd_(tag::types8_, tag::sse_)),
              tag::cpu_, Dummy> : callable
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
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is types32_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::lookup_, tag::cpu_,
                         (A0),
                         ((simd_<types32_<A0>,tag::sse_>))
                         ((simd_<types32_<A0>,tag::sse_>))
                        );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::lookup_(tag::simd_(tag::types32_, tag::sse_),
                           tag::simd_(tag::types32_, tag::sse_)),
              tag::cpu_, Dummy> : callable
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
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is types64_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::lookup_, tag::cpu_,
                         (A0),
                         ((simd_<types64_<A0>,tag::sse_>))
                         ((simd_<types64_<A0>,tag::sse_>))
                        );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::lookup_(tag::simd_(tag::types64_, tag::sse_),
                           tag::simd_(tag::types64_, tag::sse_)),
              tag::cpu_, Dummy> : callable
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
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is types16_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::lookup_, tag::cpu_,
                         (A0),
                         ((simd_<types16_<A0>,tag::sse_>))
                         ((simd_<types16_<A0>,tag::sse_>))
                        );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::lookup_(tag::simd_(tag::types16_, tag::sse_),
                           tag::simd_(tag::types16_, tag::sse_)),
              tag::cpu_, Dummy> : callable
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
} }

#endif
// modified by jt the 04/01/2011