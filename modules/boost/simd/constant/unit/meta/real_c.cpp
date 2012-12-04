/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "boost::simd::meta real_c"

#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/meta/real_c.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

////////////////////////////////////////////////////////////////////////////////
// Test value of real_c constants for every base real types
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( real_c )
{
  using boost::simd::meta::real_c;

  real_c< boost::simd::uint32_t, 0x3F800000UL>          one_fc;
  real_c< boost::simd::uint64_t, 0x3FF0000000000000ULL> one_dc;

  float  one_f = 1.f;
  double one_d = 1.;

  NT2_TEST_EQUAL( one_f, float(one_fc)  );
  NT2_TEST_EQUAL( one_d, double(one_dc) );
}
