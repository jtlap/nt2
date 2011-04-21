//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_ARITHMETIC_FUNCTION_SIMD_SSE_SSSE3_ABS_HPP_INCLUDED
#define NT2_TOOLBOX_ARITHMETIC_FUNCTION_SIMD_SSE_SSSE3_ABS_HPP_INCLUDED
#include <nt2/sdk/constant/real.hpp>
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/constant/digits.hpp>
#include <nt2/sdk/constant/properties.hpp>
#include <nt2/include/functions/select.hpp>
#include <nt2/include/functions/is_lez.hpp>
#include <nt2/include/functions/bitwise_notand.hpp>
#include <nt2/include/functions/shri.hpp>


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is int32_t
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::abs_, tag::cpu_,
                      (A0),
                      ((simd_<int32_<A0>,tag::sse_>))
                     );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call < tag::abs_(tag::simd_<tag::int32_, tag::sse_>)
              , tag::cpu_, Dummy
              > : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : meta::strip<A0>{};

    NT2_FUNCTOR_CALL(1) { A0 that = {_mm_abs_epi32(a0) }; return that; }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is int8_t
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::abs_, tag::cpu_,
                      (A0),
                      ((simd_<int8_<A0>,tag::sse_>))
                     );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call < tag::abs_(tag::simd_<tag::int8_, tag::sse_>)
              , tag::cpu_, Dummy
              > : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : meta::strip<A0>{};

    NT2_FUNCTOR_CALL(1) { A0 that = {_mm_abs_epi8(a0) }; return that; }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is int16_t
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::abs_, tag::cpu_,
                      (A0),
                      ((simd_<int16_<A0>,tag::sse_>))
                     );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::abs_(tag::simd_<tag::int16_, tag::sse_>),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : meta::strip<A0>{};

    NT2_FUNCTOR_CALL(1){ A0 that = {_mm_abs_epi16(a0) };return that; }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is real_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::abs_, tag::cpu_,
                      (A0),
                      ((simd_<real_<A0>,tag::sse_>))
                     );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::abs_(tag::simd_<tag::real_, tag::sse_>),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : meta::strip<A0>{};

    NT2_FUNCTOR_CALL(1){ return b_notand(Mzero<A0>(),a0); }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is int64_t
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::abs_, tag::cpu_,
                      (A0),
                      ((simd_<int64_<A0>,tag::sse_>))
                     );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::abs_(tag::simd_<tag::int64_, tag::sse_>),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : meta::strip<A0>{};

    NT2_FUNCTOR_CALL(1)   {
       typedef typename meta::as_integer<A0, signed>::type int_type;
       typedef typename meta::scalar_of<int_type>::type   sint_type;
       A0 const s = shri(a0, 8*sizeof(sint_type)-1);
       return (a0-s)^(-s);
       //      return select(is_lez(a0),-a0,a0);
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is unsigned_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::abs_, tag::cpu_,
                      (A0),
                      ((simd_<unsigned_<A0>,tag::sse_>))
                     );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::abs_(tag::simd_<tag::unsigned_, tag::sse_>),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : meta::strip<A0>{};

    NT2_FUNCTOR_CALL(1){ return a0; }
  };
} }

#endif
// modified by jt the 04/01/2011
