//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_PREDICATES_FUNCTION_SIMD_SSE_AVX_IS_UNORD_HPP_INCLUDED
#define NT2_TOOLBOX_PREDICATES_FUNCTION_SIMD_SSE_AVX_IS_UNORD_HPP_INCLUDED
#include <nt2/sdk/constant/boolean.hpp>
#include <nt2/sdk/details/ignore_unused.hpp>
#include <nt2/sdk/meta/strip.hpp>

#include <nt2/include/functions/details/simd/sse/sse4_1/is_unord.hpp>


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::is_unord_, tag::cpu_,
                           (A0),
                           ((simd_<arithmetic_<A0>,tag::avx_>))
                           ((simd_<arithmetic_<A0>,tag::avx_>))
                          );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::is_unord_(tag::simd_<tag::arithmetic_, tag::avx_),
                             tag::simd_<tag::arithmetic_, tag::avx_)),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0,A0)>
      : meta::strip<A0>{};//

    NT2_FUNCTOR_CALL(2)
    {
      details::ignore_unused(a0);
      details::ignore_unused(a1);
      return False<A0>();
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is double
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::is_unord_, tag::cpu_,
                           (A0),
                           ((simd_<double_<A0>,tag::avx_>))
                           ((simd_<double_<A0>,tag::avx_>))
                          );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::is_unord_(tag::simd_<tag::double_, tag::avx_),
                             tag::simd_<tag::double_, tag::avx_)),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0,A0)>
      : meta::strip<A0>{};//

    NT2_FUNCTOR_CALL(2)
    {
      A0 that = {_mm256_cmp_pd(a0,a1, _CMP_UNORD_Q)};
      return that;
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is float
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::is_unord_, tag::cpu_,
                           (A0),
                           ((simd_<float_<A0>,tag::avx_>))
                           ((simd_<float_<A0>,tag::avx_>))
                          );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::is_unord_(tag::simd_<tag::float_, tag::avx_),
                             tag::simd_<tag::float_, tag::avx_)),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0,A0)>
      : meta::strip<A0>{};//

    NT2_FUNCTOR_CALL(2)
    {
      A0 that = {_mm256_cmp_ps(a0,a1, _CMP_UNORD_Q)};
      return that;
    }
  };
} }

#endif
// modified by jt the 04/01/2011