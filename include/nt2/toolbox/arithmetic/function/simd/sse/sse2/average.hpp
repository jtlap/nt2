//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_ARITHMETIC_FUNCTION_SIMD_SSE_SSE2_AVERAGE_HPP_INCLUDED
#define NT2_TOOLBOX_ARITHMETIC_FUNCTION_SIMD_SSE_SSE2_AVERAGE_HPP_INCLUDED
#include <nt2/sdk/constant/real.hpp>
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/include/functions/shrai.hpp>

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::average_, tag::cpu_,
                          (A0),
                          ((simd_<arithmetic_<A0>,tag::sse_>))
                          ((simd_<arithmetic_<A0>,tag::sse_>))
                         );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::average_(tag::simd_<tag::arithmetic_, tag::sse_>,
                            tag::simd_<tag::arithmetic_, tag::sse_>),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0,A0)>
      : meta::strip<A0>{};//

    NT2_FUNCTOR_CALL(2)
    {
      return b_and(a0, a1)+shrai(b_xor(a0, a1),1);
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is uint16_t
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::average_, tag::cpu_,
                          (A0),
                          ((simd_<uint16_<A0>,tag::sse_>))
                          ((simd_<uint16_<A0>,tag::sse_>))
                         );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::average_(tag::simd_<tag::uint16_, tag::sse_>,
                            tag::simd_<tag::uint16_, tag::sse_>),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0,A0)>
      : meta::strip<A0>{};//

    NT2_FUNCTOR_CALL(2)
    {
      return b_and(a0, a1)+shrai(b_xor(a0, a1),1);
      //     A0 that = {_mm_avg_epu16(a0,a1)}; return that; //(a+b + 1) >> 1;
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is uint8_t
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::average_, tag::cpu_,
                          (A0),
                          ((simd_<uint8_<A0>,tag::sse_>))
                          ((simd_<uint8_<A0>,tag::sse_>))
                         );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::average_(tag::simd_<tag::uint8_, tag::sse_>,
                            tag::simd_<tag::uint8_, tag::sse_>),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0,A0)>
      : meta::strip<A0>{};//

    NT2_FUNCTOR_CALL(2)
    {
      return b_and(a0, a1)+shrai(b_xor(a0, a1),1);
      //     A0 that = {_mm_avg_epu8(a0,a1)}; return that; //  (a+b + 1) >> 1;
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is real_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::average_, tag::cpu_,
                          (A0),
                          ((simd_<real_<A0>,tag::sse_>))
                          ((simd_<real_<A0>,tag::sse_>))
                         );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::average_(tag::simd_<tag::real_, tag::sse_>,
                            tag::simd_<tag::real_, tag::sse_>),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0,A0)>
      : meta::strip<A0>{};//

    NT2_FUNCTOR_CALL(2)
    {
       return (a0+a1)*Half<A0>();
    }
  };
} }

#endif
// modified by jt the 04/01/2011
