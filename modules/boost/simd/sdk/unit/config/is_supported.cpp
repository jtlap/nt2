//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "boost::simd::memory::is_supported"

#include <boost/simd/sdk/config/arch.hpp>
#include <boost/simd/sdk/simd/extensions.hpp>
#include <boost/simd/sdk/config/is_supported.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

#define BOOST_IS_SUPPORTED_CALL(tag) boost::simd::is_supported<tag>();

////////////////////////////////////////////////////////////////////////////////
// Test if the runtime detection of SIMD extensions works according to 
// the highest SIMD level detected statically  
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(is_supported)
{
#ifdef BOOST_SIMD_HAS_ALTIVEC_SUPPORT
  NT2_TEST_EQUAL( boost::simd::is_supported<boost::simd::tag::altivec_>(), true);
#else
  NT2_TEST_EQUAL( boost::simd::is_supported<boost::simd::tag::altivec_>(), false);
#endif
#if defined(BOOST_SIMD_HAS_SSE4_2_SUPPORT)
  NT2_TEST_EQUAL( boost::simd::is_supported<boost::simd::tag::sse4_2_>(), true);
#else
  NT2_TEST_EQUAL( boost::simd::is_supported<boost::simd::tag::sse4_2_>(), false);
#endif
#if defined(BOOST_SIMD_HAS_SSE4_1_SUPPORT)
  NT2_TEST_EQUAL( boost::simd::is_supported<boost::simd::tag::sse4_1_>(), true);
#else
  NT2_TEST_EQUAL( boost::simd::is_supported<boost::simd::tag::sse4_1_>(), false);
#endif
#if defined(BOOST_SIMD_HAS_SSE4a_SUPPORT)
  NT2_TEST_EQUAL( boost::simd::is_supported<boost::simd::tag::sse4a_>(), true);
#else
  NT2_TEST_EQUAL( boost::simd::is_supported<boost::simd::tag::sse4a_>(), false);
#endif
#if defined(BOOST_SIMD_HAS_SSSE3_SUPPORT)
  NT2_TEST_EQUAL( boost::simd::is_supported<boost::simd::tag::ssse3_>(), true);  
#else
  NT2_TEST_EQUAL( boost::simd::is_supported<boost::simd::tag::ssse3_>(), false);
#endif
#if defined(BOOST_SIMD_HAS_SSE3_SUPPORT)
  NT2_TEST_EQUAL( boost::simd::is_supported<boost::simd::tag::sse3_>(), true);
#else
  NT2_TEST_EQUAL( boost::simd::is_supported<boost::simd::tag::sse3_>(), false);
#endif
#if defined(BOOST_SIMD_HAS_SSE4_2_SUPPORT)
  NT2_TEST_EQUAL( boost::simd::is_supported<boost::simd::tag::sse2_>(), true);
#else
  NT2_TEST_EQUAL( boost::simd::is_supported<boost::simd::tag::sse2_>(), false);
#endif
}
