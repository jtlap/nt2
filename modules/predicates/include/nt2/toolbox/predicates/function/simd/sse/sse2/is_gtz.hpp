//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_PREDICATES_FUNCTION_SIMD_SSE_SSE2_IS_GTZ_HPP_INCLUDED
#define NT2_TOOLBOX_PREDICATES_FUNCTION_SIMD_SSE_SSE2_IS_GTZ_HPP_INCLUDED
#include <nt2/sdk/meta/templatize.hpp>
#include <nt2/sdk/constant/digits.hpp>
#include <nt2/sdk/meta/strip.hpp>

#include <nt2/include/functions/is_ltz.hpp>
#include <nt2/include/functions/is_nez.hpp>


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::is_gtz_, tag::cpu_,
                         (A0),
                         ((simd_<arithmetic_<A0>,tag::sse_>))
                        );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::is_gtz_(tag::simd_<tag::arithmetic_, tag::sse_> ),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0> struct result<This(A0)> : meta::strip<A0>{};//

    NT2_FUNCTOR_CALL(1){ return gt(a0,Zero<A0>()); }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is unsigned_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::is_gtz_, tag::cpu_,
                         (A0),
                         ((simd_<unsigned_<A0>,tag::sse_>))
                        );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::is_gtz_(tag::simd_<tag::unsigned_, tag::sse_> ),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0> struct result<This(A0)> : meta::strip<A0>{};//

    NT2_FUNCTOR_CALL(1){ return is_nez(a0); }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is int64_t
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::is_gtz_, tag::cpu_,
                         (A0),
                         ((simd_<int64_<A0>,tag::sse_>))
                        );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::is_gtz_(tag::simd_<tag::int64_, tag::sse_> ),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0> struct result<This(A0)> : meta::strip<A0>{};//

    NT2_FUNCTOR_CALL(1)
    {
      typedef simd::native<typename meta::int32_t_<A0>::type, tag::sse_> type;
      const type tmp1 = is_ltz(simd::native_cast<type>(a0));
      const type tmp = { _mm_shuffle_epi32(tmp1, _MM_SHUFFLE(3, 3, 1, 1))};
      return b_not(simd::native_cast<A0>(tmp)); 
    }
  };
} }

#endif
// modified by jt the 04/01/2011
