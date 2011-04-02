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


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is type8_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::first_, tag::cpu_,
                        (A0),
                        ((simd_<type8_<A0>,tag::sse_>))
                       );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::first_(tag::simd_<tag::type8_, tag::sse_> ),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct  result<This(A0)>
          : meta::scalar_of<typename meta::strip<A0>::type> {};

    NT2_FUNCTOR_CALL(1)
    {
      typedef typename NT2_RETURN_TYPE(1)::type type;
      int that = _mm_extract_epi16(a0, 0);
      printf("%d\n",that);
      return that & 0xFF;
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is double
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::first_, tag::cpu_,
                        (A0),
                        ((simd_<double_<A0>,tag::sse_>))
                       );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::first_(tag::simd_<tag::double_, tag::sse_> ),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct  result<This(A0)>
          : meta::scalar_of<typename meta::strip<A0>::type> {};

    NT2_FUNCTOR_CALL(1)
    {
      return _mm_cvtsd_f64(a0);
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is float
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::first_, tag::cpu_,
                        (A0),
                        ((simd_<float_<A0>,tag::sse_>))
                       );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::first_(tag::simd_<tag::float_, tag::sse_> ),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct  result<This(A0)>
          : meta::scalar_of<typename meta::strip<A0>::type> {};

    NT2_FUNCTOR_CALL(1)
    {
      typedef typename meta::as_integer<A0>::type type;
      meta::from_bits<float>::type t = {_mm_cvtsi128_si32(simd::native_cast<type>(a0))};
      return t.value;
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is type32_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::first_, tag::cpu_,
                        (A0),
                        ((simd_<type32_<A0>,tag::sse_>))
                       );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::first_(tag::simd_<tag::type32_, tag::sse_> ),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct  result<This(A0)>
          : meta::scalar_of<typename meta::strip<A0>::type> {};

    NT2_FUNCTOR_CALL(1)
    {
      typedef typename meta::as_integer<A0>::type type;
      return _mm_cvtsi128_si32(simd::native_cast<type>(a0));
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is type64_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::first_, tag::cpu_,
                        (A0),
                        ((simd_<type64_<A0>,tag::sse_>))
                       );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::first_(tag::simd_<tag::type64_, tag::sse_> ),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct  result<This(A0)>
          : meta::scalar_of<typename meta::strip<A0>::type> {};

    NT2_FUNCTOR_CALL(1)
    {
      typedef typename meta::as_integer<A0>::type type;
      typedef typename meta::as_real<A0>::type rtype;
      meta::as_bits<double>::type t = {_mm_cvtsd_f64(simd::native_cast<rtype>(a0))};
      return t.bits;
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is type16_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::first_, tag::cpu_,
                        (A0),
                        ((simd_<type16_<A0>,tag::sse_>))
                       );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::first_(tag::simd_<tag::type16_, tag::sse_> ),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct  result<This(A0)>
          : meta::scalar_of<typename meta::strip<A0>::type> {};

    NT2_FUNCTOR_CALL(1)
    {
      return _mm_extract_epi16(a0, 0);
    }
  };
} }

#endif
// modified by jt the 05/01/2011