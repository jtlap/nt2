//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_ARITHMETIC_FUNCTION_SIMD_SSE_XOP_MAX_HPP_INCLUDED
#define NT2_TOOLBOX_ARITHMETIC_FUNCTION_SIMD_SSE_XOP_MAX_HPP_INCLUDED
#include <nt2/sdk/meta/strip.hpp>

#include <nt2/include/functions/seladd.hpp>


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is uint8_t
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::max_, tag::cpu_,
                      (A0),
                      ((simd_<uint8_<A0>,tag::xop_>))
                      ((simd_<uint8_<A0>,tag::xop_>))
                     );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::max_(tag::simd_<tag::uint8_, tag::xop_),
                        tag::simd_<tag::uint8_, tag::xop_)),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0,A0)>
      : meta::strip<A0>{};//

    NT2_FUNCTOR_CALL(2)
    {
      NT2_XOP_JOIN128INT(that, _mm_max_epu8); return that;
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::max_, tag::cpu_,
                      (A0),
                      ((simd_<arithmetic_<A0>,tag::xop_>))
                      ((simd_<arithmetic_<A0>,tag::xop_>))
                     );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::max_(tag::simd_<tag::arithmetic_, tag::xop_),
                        tag::simd_<tag::arithmetic_, tag::xop_)),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0,A0)>
      : meta::strip<A0>{};//

    NT2_FUNCTOR_CALL(2)
    {
       return seladd( is_lt(a0,a1),a0,a1-a0);
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is double
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::max_, tag::cpu_,
                      (A0),
                      ((simd_<double_<A0>,tag::xop_>))
                      ((simd_<double_<A0>,tag::xop_>))
                     );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::max_(tag::simd_<tag::double_, tag::xop_),
                        tag::simd_<tag::double_, tag::xop_)),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0,A0)>
      : meta::strip<A0>{};//

    NT2_FUNCTOR_CALL(2)
    {
      A0 that =  {_mm256_max_pd(a0,a1)}; return that;
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is int32_t
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::max_, tag::cpu_,
                      (A0),
                      ((simd_<int32_<A0>,tag::xop_>))
                      ((simd_<int32_<A0>,tag::xop_>))
                     );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::max_(tag::simd_<tag::int32_, tag::xop_),
                        tag::simd_<tag::int32_, tag::xop_)),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0,A0)>
      : meta::strip<A0>{};//

    NT2_FUNCTOR_CALL(2)
    {
      NT2_XOP_JOIN128INT(that, _mm_max_epi32); return that;
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is float
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::max_, tag::cpu_,
                      (A0),
                      ((simd_<float_<A0>,tag::xop_>))
                      ((simd_<float_<A0>,tag::xop_>))
                     );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::max_(tag::simd_<tag::float_, tag::xop_),
                        tag::simd_<tag::float_, tag::xop_)),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0,A0)>
      : meta::strip<A0>{};//

    NT2_FUNCTOR_CALL(2)
    {
      A0 that =  {_mm256_max_ps(a0,a1)}; return that;
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is int8_t
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::max_, tag::cpu_,
                      (A0),
                      ((simd_<int8_<A0>,tag::xop_>))
                      ((simd_<int8_<A0>,tag::xop_>))
                     );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::max_(tag::simd_<tag::int8_, tag::xop_),
                        tag::simd_<tag::int8_, tag::xop_)),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0,A0)>
      : meta::strip<A0>{};//

    NT2_FUNCTOR_CALL(2)
    {
      NT2_XOP_JOIN128INT(that, _mm_max_epi8); return that;
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is int16_t
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::max_, tag::cpu_,
                      (A0),
                      ((simd_<int16_<A0>,tag::xop_>))
                      ((simd_<int16_<A0>,tag::xop_>))
                     );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::max_(tag::simd_<tag::int16_, tag::xop_),
                        tag::simd_<tag::int16_, tag::xop_)),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0,A0)>
      : meta::strip<A0>{};//

    NT2_FUNCTOR_CALL(2)
    {
      NT2_XOP_JOIN128INT(that, _mm_max_epi16); return that;
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is uint32_t
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::max_, tag::cpu_,
                      (A0),
                      ((simd_<uint32_<A0>,tag::xop_>))
                      ((simd_<uint32_<A0>,tag::xop_>))
                     );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::max_(tag::simd_<tag::uint32_, tag::xop_),
                        tag::simd_<tag::uint32_, tag::xop_)),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0,A0)>
      : meta::strip<A0>{};//

    NT2_FUNCTOR_CALL(2)
    {
      NT2_XOP_JOIN128INT(that, _mm_max_epu32); return that;
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is uint16_t
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::max_, tag::cpu_,
                      (A0),
                      ((simd_<uint16_<A0>,tag::xop_>))
                      ((simd_<uint16_<A0>,tag::xop_>))
                     );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::max_(tag::simd_<tag::uint16_, tag::xop_),
                        tag::simd_<tag::uint16_, tag::xop_)),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0,A0)>
      : meta::strip<A0>{};//

    NT2_FUNCTOR_CALL(2)
    {
      NT2_XOP_JOIN128INT(that, _mm_max_epu16); return that;
    }
  };
} }

#endif
// modified by jt the 04/01/2011