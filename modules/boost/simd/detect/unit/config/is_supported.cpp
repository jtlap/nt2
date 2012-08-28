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
#include <boost/simd/sdk/simd/extensions/meta/tags.hpp>
#include <boost/simd/sdk/config/is_supported.hpp>
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
  std::cout << "Altivec : " << boost::simd::is_supported<boost::simd::tag::altivec_>() << std::endl;
  std::cout << "Neon    : " << boost::simd::is_supported<boost::simd::tag::neon_>() << std::endl;
  std::cout << "AVX     : " << boost::simd::is_supported<boost::simd::tag::avx_>() << std::endl;
  std::cout << "SSE4.2  : " << boost::simd::is_supported<boost::simd::tag::sse4_2_>() << std::endl;
  std::cout << "SSE4.1  : " << boost::simd::is_supported<boost::simd::tag::sse4_1_>() << std::endl;
  std::cout << "SSE4A   : " << boost::simd::is_supported<boost::simd::tag::sse4a_>() << std::endl;
  std::cout << "SSSE3   : " << boost::simd::is_supported<boost::simd::tag::ssse3_>() << std::endl;
  std::cout << "SSE3    : " << boost::simd::is_supported<boost::simd::tag::sse3_>() << std::endl;
  std::cout << "SSE2    : " << boost::simd::is_supported<boost::simd::tag::sse2_>() << std::endl;

  NT2_TEST_COMPLETE("SIMD extensions detection");
}
