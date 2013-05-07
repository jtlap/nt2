//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "boost::simd::meta double"

#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/sdk/meta/double.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

////////////////////////////////////////////////////////////////////////////////
// Test value of real_c constants for every base real types
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( double_ )
{
  using boost::simd::meta::double_;

  double_<0x3FF0000000000000ULL>          one_dc;
  double one_d = 1.;

  NT2_TEST_EQUAL( one_d, double(one_dc)  );
}
