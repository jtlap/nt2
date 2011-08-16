/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "boost::simd::constants digits"

#include <boost/simd/include/constants/digits.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

#ifdef BOOST_MSVC
  #pragma warning(disable: 4309) // truncation of constant value
#endif

////////////////////////////////////////////////////////////////////////////////
// Test value of digit constant for every base types
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL( digit_value, BOOST_SIMD_TYPES )
{
  NT2_TEST_EQUAL( boost::simd::Mten<T>()            , static_cast<T>( -10) );
  NT2_TEST_EQUAL( boost::simd::Mnine<T>()           , static_cast<T>(  -9) );
  NT2_TEST_EQUAL( boost::simd::Meight<T>()          , static_cast<T>(  -8) );
  NT2_TEST_EQUAL( boost::simd::Mseven<T>()          , static_cast<T>(  -7) );
  NT2_TEST_EQUAL( boost::simd::Msix<T>()            , static_cast<T>(  -6) );
  NT2_TEST_EQUAL( boost::simd::Mfive<T>()           , static_cast<T>(  -5) );
  NT2_TEST_EQUAL( boost::simd::Mfour<T>()           , static_cast<T>(  -4) );
  NT2_TEST_EQUAL( boost::simd::Mthree<T>()          , static_cast<T>(  -3) );
  NT2_TEST_EQUAL( boost::simd::Mtwo<T>()            , static_cast<T>(  -2) );
  NT2_TEST_EQUAL( boost::simd::Mone<T>()            , static_cast<T>(  -1) );
  NT2_TEST_EQUAL( boost::simd::Zero<T>()            , static_cast<T>(   0) );
  NT2_TEST_EQUAL( boost::simd::One<T>()             , static_cast<T>(   1) );
  NT2_TEST_EQUAL( boost::simd::Two<T>()             , static_cast<T>(   2) );
  NT2_TEST_EQUAL( boost::simd::Three<T>()           , static_cast<T>(   3) );
  NT2_TEST_EQUAL( boost::simd::Four<T>()            , static_cast<T>(   4) );
  NT2_TEST_EQUAL( boost::simd::Five<T>()            , static_cast<T>(   5) );
  NT2_TEST_EQUAL( boost::simd::Six<T>()             , static_cast<T>(   6) );
  NT2_TEST_EQUAL( boost::simd::Seven<T>()           , static_cast<T>(   7) );
  NT2_TEST_EQUAL( boost::simd::Eight<T>()           , static_cast<T>(   8) );
  NT2_TEST_EQUAL( boost::simd::Nine<T>()            , static_cast<T>(   9) );
  NT2_TEST_EQUAL( boost::simd::Ten<T>()             , static_cast<T>(  10) );
}

////////////////////////////////////////////////////////////////////////////////
// Test integral_constant for every base types
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL( integral_constant,BOOST_SIMD_INTEGRAL_TYPES )
{
  NT2_TEST_EQUAL( (boost::simd::integral_constant<T,42>()), static_cast<T>(42) );
}
