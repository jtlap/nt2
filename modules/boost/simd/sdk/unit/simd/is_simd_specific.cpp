//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "boost::simd::meta::is_simd_specific SIMD"

#include <boost/simd/sdk/simd/native.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/module.hpp>

////////////////////////////////////////////////////////////////////////////////
// Test that as_floating on SIMD
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL(as_real_simd, BOOST_SIMD_REAL_TYPES)
{
  using boost::simd::meta::is_simd_specific;

  #if defined(BOOST_SIMD_SSE_FAMILY)
  NT2_TEST( (is_simd_specific<__m128,boost::simd::tag::sse_>::value) );
  NT2_TEST( (is_simd_specific<__m128d,boost::simd::tag::sse_>::value) );
  NT2_TEST( (is_simd_specific<__m128i,boost::simd::tag::sse_>::value) );
  #endif

  #if defined(BOOST_SIMD_VMX_FAMILY)
  NT2_TEST( (is_simd_specific<__vector float,boost::simd::tag::altivec_>::value) );
  NT2_TEST( (is_simd_specific<__vector signed int,boost::simd::tag::altivec_>::value) );
  NT2_TEST( (is_simd_specific<__vector signed short,boost::simd::tag::altivec_>::value) );
  NT2_TEST( (is_simd_specific<__vector signed char,boost::simd::tag::altivec_>::value) );
  NT2_TEST( (is_simd_specific<__vector unsigned int,boost::simd::tag::altivec_>::value) );
  NT2_TEST( (is_simd_specific<__vector unsigned short,boost::simd::tag::altivec_>::value) );
  NT2_TEST( (is_simd_specific<__vector unsigned char,boost::simd::tag::altivec_>::value) );
  NT2_TEST( (is_simd_specific<__vector __bool int,boost::simd::tag::altivec_>::value) );
  NT2_TEST( (is_simd_specific<__vector __bool short,boost::simd::tag::altivec_>::value) );
  NT2_TEST( (is_simd_specific<__vector __bool char,boost::simd::tag::altivec_>::value) );
  #endif


}
