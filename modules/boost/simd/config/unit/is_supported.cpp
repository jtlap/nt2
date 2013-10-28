//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/sdk/config/arch.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/sdk/simd/extensions/meta/tags.hpp>
#include <boost/simd/sdk/config/is_supported.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

static inline const char* msg(int i)
{
  switch(i)
  {
    case 1:
      return "true";
    case -1:
      return "false";
    default:
      return "unknown";
  }
}

////////////////////////////////////////////////////////////////////////////////
// Test if the runtime detection of SIMD extensions works according to
// the highest SIMD level detected statically
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(is_supported)
{
  std::cout << "Altivec : " << msg(boost::simd::is_supported("vmx")) << std::endl;
  std::cout << "NEON    : " << msg(boost::simd::is_supported("neon")) << std::endl;
  std::cout << "AVX2    : " << msg(boost::simd::is_supported("avx2")) << std::endl;
  std::cout << "FMA     : " << msg(boost::simd::is_supported("fma")) << std::endl;
  std::cout << "XOP     : " << msg(boost::simd::is_supported("xop")) << std::endl;
  std::cout << "FMA4    : " << msg(boost::simd::is_supported("fma4")) << std::endl;
  std::cout << "AVX     : " << msg(boost::simd::is_supported("avx")) << std::endl;
  std::cout << "SSE4.2  : " << msg(boost::simd::is_supported("sse4.2")) << std::endl;
  std::cout << "SSE4.1  : " << msg(boost::simd::is_supported("sse4.1")) << std::endl;
  std::cout << "SSE4A   : " << msg(boost::simd::is_supported("sse4a")) << std::endl;
  std::cout << "SSSE3   : " << msg(boost::simd::is_supported("ssse3")) << std::endl;
  std::cout << "SSE3    : " << msg(boost::simd::is_supported("sse3")) << std::endl;
  std::cout << "SSE2    : " << msg(boost::simd::is_supported("sse2")) << std::endl;
  std::cout << "SSE     : " << msg(boost::simd::is_supported("sse")) << std::endl;

  NT2_TEST_COMPLETE("SIMD extensions detection");
}
