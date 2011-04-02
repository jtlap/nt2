//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_ARITHMETIC_FUNCTION_SIMD_SSE_SSE2_ADDS_HPP_INCLUDED
#define NT2_TOOLBOX_ARITHMETIC_FUNCTION_SIMD_SSE_SSE2_ADDS_HPP_INCLUDED
#include <nt2/include/functions/saturate.hpp>
#include <nt2/include/functions/bitwise_andnot.hpp>
#include <nt2/include/functions/is_gtz.hpp>
#include <nt2/include/functions/max.hpp>
#include <nt2/include/functions/min.hpp>

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is uint64_t
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::adds_, tag::cpu_,
                          (A0),
                          ((simd_<uint64_<A0>,tag::sse_>))
                          ((simd_<uint64_<A0>,tag::sse_>))
                         );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::adds_(tag::simd_<tag::uint64_, tag::sse_>,
			 tag::simd_<tag::uint64_, tag::sse_>),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0,A0)>
      : meta::strip<A0>{};//

    NT2_FUNCTOR_CALL(2)
    {
      A0 a0pa1 = a0+a1;
      return b_or(a0pa1, lt(a0pa1, a0)); 
     //      return sel(lt(a0pa1, nt2::max(a0, a1)), Valmax<A0>(), a0pa1); 
    }
  };
} }
/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is int64_t
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::adds_, tag::cpu_,
                          (A0),
                          ((simd_<int64_<A0>,tag::sse_>))
                          ((simd_<int64_<A0>,tag::sse_>))
                         );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::adds_(tag::simd_<tag::int64_, tag::sse_>,
			 tag::simd_<tag::int64_, tag::sse_>),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0,A0)>
      : meta::strip<A0>{};//

    NT2_FUNCTOR_CALL(2)
    {
      A0 gtza0 = is_gtz(a0);
      A0 gtza1 = is_gtz(a1);
      A0 a0pa1 = a0+a1;
      A0 test1 = b_and(gtza0, b_and(gtza1, (lt(a0pa1, nt2::max(a0, a1))))); 
      A0 test2 = b_andnot(b_andnot(b_or(is_gtz(a0pa1),gt(a0pa1, nt2::min(a0, a1))),gtza0),gtza1);
      return sel(test1,Valmax<A0>(),sel(test2,Valmin<A0>(),a0pa1)); 
    }
  };
} }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is uint32_t
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::adds_, tag::cpu_,
                          (A0),
                          ((simd_<uint32_<A0>,tag::sse_>))
                          ((simd_<uint32_<A0>,tag::sse_>))
                         );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::adds_(tag::simd_<tag::uint32_, tag::sse_>,
			 tag::simd_<tag::uint32_, tag::sse_>),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0,A0)>
      : meta::strip<A0>{};//

    NT2_FUNCTOR_CALL(2)
    {
     A0 a0pa1 = a0+a1;
     return b_or(a0pa1, lt(a0pa1, a0)); 
     //     return sel(lt(a0pa1, nt2::max(a0, a1)), Valmax<A0>(), a0pa1); 
    }
  };
} }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is int32_t
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::adds_, tag::cpu_,
                          (A0),
                          ((simd_<int32_<A0>,tag::sse_>))
                          ((simd_<int32_<A0>,tag::sse_>))
                         );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::adds_(tag::simd_<tag::int32_, tag::sse_>,
                            tag::simd_<tag::int32_, tag::sse_>),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0,A0)>
      : meta::strip<A0>{};//

    NT2_FUNCTOR_CALL(2)
    {
      A0 gtza0 = is_gtz(a0);
      A0 gtza1 = is_gtz(a1);
      A0 a0pa1 = a0+a1;
      A0 test1 = b_and(gtza0, b_and(gtza1, (lt(a0pa1, nt2::max(a0, a1))))); 
      A0 test2 = b_andnot(b_andnot(b_or(is_gtz(a0pa1),gt(a0pa1, nt2::min(a0, a1))),gtza0),gtza1);
      return sel(test1,Valmax<A0>(),sel(test2,Valmin<A0>(),a0pa1)); 
    }
  };
} }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is uint16_t
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::adds_, tag::cpu_,
                          (A0),
                          ((simd_<uint16_<A0>,tag::sse_>))
                          ((simd_<uint16_<A0>,tag::sse_>))
                         );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::adds_(tag::simd_<tag::uint16_, tag::sse_>,
                            tag::simd_<tag::uint16_, tag::sse_>),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0,A0)>
      : meta::strip<A0>{};//

    NT2_FUNCTOR_CALL(2)
    {
      return simd::native_cast<A0>(_mm_adds_epu16(a0, a1)); 
    }
  };
} }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is int16_t
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::adds_, tag::cpu_,
                          (A0),
                          ((simd_<int16_<A0>,tag::sse_>))
                          ((simd_<int16_<A0>,tag::sse_>))
                         );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::adds_(tag::simd_<tag::int16_, tag::sse_>,
                            tag::simd_<tag::int16_, tag::sse_>),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0,A0)>
      : meta::strip<A0>{};//

    NT2_FUNCTOR_CALL(2)
    {
      return simd::native_cast<A0>(_mm_adds_epi16(a0, a1)); 
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is uint8_t
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::adds_, tag::cpu_,
                          (A0),
                          ((simd_<uint8_<A0>,tag::sse_>))
                          ((simd_<uint8_<A0>,tag::sse_>))
                         );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::adds_(tag::simd_<tag::uint8_, tag::sse_>,
                            tag::simd_<tag::uint8_, tag::sse_>),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0,A0)> : meta::strip<A0>{};

    NT2_FUNCTOR_CALL(2)
    {
      return simd::native_cast<A0>(_mm_adds_epu8(a0, a1)); 
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is int8_t
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::adds_, tag::cpu_,
                          (A0),
                          ((simd_<int8_<A0>,tag::sse_>))
                          ((simd_<int8_<A0>,tag::sse_>))
                         );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::adds_(tag::simd_<tag::int8_, tag::sse_>,
                            tag::simd_<tag::int8_, tag::sse_>),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0,A0)> : meta::strip<A0>{};

    NT2_FUNCTOR_CALL(2)
    {
      return simd::native_cast<A0>(_mm_adds_epi8(a0, a1)); 
    }
  };
} }

#endif

