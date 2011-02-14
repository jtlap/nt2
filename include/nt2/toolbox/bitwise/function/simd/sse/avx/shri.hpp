//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_BITWISE_FUNCTION_SIMD_SSE_AVX_SHRI_HPP_INCLUDED
#define NT2_TOOLBOX_BITWISE_FUNCTION_SIMD_SSE_AVX_SHRI_HPP_INCLUDED

#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/meta/strip.hpp>

#include <nt2/include/functions/details/simd/sse/sse4_1/shri.hpp>


/////////////////////////////////////////////////////////////////////////////
// Implementation when type  is arithmetic_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::shri_, tag::cpu_,
                       (A0),
                       ((simd_<arithmetic_<A0>,tag::avx_>))
                       ((simd_<arithmetic_<A0>,tag::avx_>))
                      );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::shri_(tag::simd_<tag::arithmetic_, tag::avx_),
                         tag::simd_<tag::arithmetic_, tag::avx_)),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0,A1)> : meta::strip<A0>{};//

    NT2_FUNCTOR_CALL(2)
    {
      typedef typename meta::scalar_of<A0>::type sctype;
      typedef typename meta::as_integer<sctype>::type sitype;
      typedef typename simd::native<sitype, tag::sse_ >  isvtype;
      typedef typename meta::as_integer<A0>::type  itype;

      isvtype a00 = { _mm256_extractf128_si256(simd::native_cast<itype>(a0), 0)};
      isvtype a01 = { _mm256_extractf128_si256(simd::native_cast<itype>(a0), 1)};
      itype that = { _mm256_insertf128_si256(that,nt2::shri( a00, a1), 0)};
      return  simd::native_cast<A0>(_mm256_insertf128_si256(that, nt2::shri(a01, a1), 1));

     }

  };
} }

#endif
// modified by jt the 04/01/2011