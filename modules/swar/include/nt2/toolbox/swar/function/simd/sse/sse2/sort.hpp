//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_SWAR_FUNCTION_SIMD_SSE_SSE2_SORT_HPP_INCLUDED
#define NT2_TOOLBOX_SWAR_FUNCTION_SIMD_SSE_SSE2_SORT_HPP_INCLUDED
#include <nt2/sdk/meta/as_real.hpp>
#include <nt2/sdk/meta/strip.hpp>

#include <nt2/include/functions/minimum.hpp>
#include <nt2/include/functions/maximum.hpp>

#define NT2_SH(a, b, c, d) (_MM_SHUFFLE(d, c, b, a))
#define NT2_CAST(T, a)   simd::native_cast<T>(a)    


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is type32_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::sort_, tag::cpu_,
                       (A0),
                       ((simd_<type32_<A0>,tag::sse_>))
                      );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::sort_(tag::simd_<tag::type32_, tag::sse_> ),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)>
      : meta::strip<A0>{};//

    NT2_FUNCTOR_CALL(1)
    {
      typedef typename meta::as_real<A0>::type flt;
      A0 a =  {a0};
      A0 b =  {NT2_CAST(A0, _mm_movehl_ps(NT2_CAST(flt, a0), NT2_CAST(flt, a0)))};
      comp(a, b);
      a = NT2_CAST(A0, _mm_movelh_ps(NT2_CAST(flt, a), NT2_CAST(flt, b)));
      b = NT2_CAST(A0, _mm_shuffle_ps(NT2_CAST(flt, a), NT2_CAST(flt, b), NT2_SH(1, 3, 1, 3)));
      comp(a, b);
      A0 c = {NT2_CAST(A0, _mm_movelh_ps(NT2_CAST(flt, b), NT2_CAST(flt, b)))};
      A0 d = {a};
      comp(c, d);
      a = NT2_CAST(A0, _mm_shuffle_ps(NT2_CAST(flt, c), NT2_CAST(flt, a), NT2_SH(3, 2, 0, 0)));
      b = NT2_CAST(A0, _mm_movehl_ps(NT2_CAST(flt, b), NT2_CAST(flt, d)));
      b = NT2_CAST(A0, _mm_shuffle_ps(NT2_CAST(flt, a), NT2_CAST(flt, b), NT2_SH(3, 1, 0, 2)));
      return b;
    }
  private :
    template < class T > static inline void comp(T & a,T & b)
    {
      T c =  nt2::min(a, b);
      b = nt2::max(a, b);
      a = c;
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is type64_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::sort_, tag::cpu_,
                       (A0),
                       ((simd_<type64_<A0>,tag::sse_>))
                      );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::sort_(tag::simd_<tag::type64_, tag::sse_> ),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)>
      : meta::strip<A0>{};//

    NT2_FUNCTOR_CALL(1)
    {
      A0 that = {{minimum(a0), maximum(a0)}};
      return that;
    }
  };
} }

#endif
// modified by jt the 05/01/2011
