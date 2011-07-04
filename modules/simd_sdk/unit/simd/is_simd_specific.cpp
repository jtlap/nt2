/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::meta::is_simd_specific SIMD"

#include <nt2/sdk/simd/native.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/module.hpp>

////////////////////////////////////////////////////////////////////////////////
// Test that as_real on SIMD
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL(as_real_simd, NT2_SIMD_REAL_TYPES)
{
  using nt2::meta::is_simd_specific;

  #if defined(NT2_SIMD_SSE_FAMILY)
  NT2_TEST( (is_simd_specific<__m128,nt2::tag::sse_>::value) );
  NT2_TEST( (is_simd_specific<__m128d,nt2::tag::sse_>::value) );
  NT2_TEST( (is_simd_specific<__m128i,nt2::tag::sse_>::value) );
  #endif

  #if defined(NT2_SIMD_VMX_FAMILY)
  NT2_TEST( (is_simd_specific<__vector float,nt2::tag::altivec_>::value) );
  NT2_TEST( (is_simd_specific<__vector signed int,nt2::tag::altivec_>::value) );
  NT2_TEST( (is_simd_specific<__vector signed short,nt2::tag::altivec_>::value) );
  NT2_TEST( (is_simd_specific<__vector signed char,nt2::tag::altivec_>::value) );
  NT2_TEST( (is_simd_specific<__vector unsigned int,nt2::tag::altivec_>::value) );
  NT2_TEST( (is_simd_specific<__vector unsigned short,nt2::tag::altivec_>::value) );
  NT2_TEST( (is_simd_specific<__vector unsigned char,nt2::tag::altivec_>::value) );
  NT2_TEST( (is_simd_specific<__vector __bool int,nt2::tag::altivec_>::value) );
  NT2_TEST( (is_simd_specific<__vector __bool short,nt2::tag::altivec_>::value) );
  NT2_TEST( (is_simd_specific<__vector __bool char,nt2::tag::altivec_>::value) );
  #endif


}
