/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define BOOST_SIMD_UNIT_MODULE "boost::simd::constants digits"

#include <boost/simd/include/constants/digits.hpp>
#include <boost/simd/sdk/unit/module.hpp>
#include <boost/simd/sdk/unit/tests/relation.hpp>

#ifdef BOOST_MSVC
  #pragma warning(disable: 4309) // truncation of constant value
#endif

////////////////////////////////////////////////////////////////////////////////
// Test value of digit constant for every base types
////////////////////////////////////////////////////////////////////////////////
BOOST_SIMD_TEST_CASE_TPL( digit_value, BOOST_SIMD_TYPES )
{
  BOOST_SIMD_TEST_EQUAL( boost::simd::Mten<T>()            , static_cast<T>( -10) );
  BOOST_SIMD_TEST_EQUAL( boost::simd::Mnine<T>()           , static_cast<T>(  -9) );
  BOOST_SIMD_TEST_EQUAL( boost::simd::Meight<T>()          , static_cast<T>(  -8) );
  BOOST_SIMD_TEST_EQUAL( boost::simd::Mseven<T>()          , static_cast<T>(  -7) );
  BOOST_SIMD_TEST_EQUAL( boost::simd::Msix<T>()            , static_cast<T>(  -6) );
  BOOST_SIMD_TEST_EQUAL( boost::simd::Mfive<T>()           , static_cast<T>(  -5) );
  BOOST_SIMD_TEST_EQUAL( boost::simd::Mfour<T>()           , static_cast<T>(  -4) );
  BOOST_SIMD_TEST_EQUAL( boost::simd::Mthree<T>()          , static_cast<T>(  -3) );
  BOOST_SIMD_TEST_EQUAL( boost::simd::Mtwo<T>()            , static_cast<T>(  -2) );
  BOOST_SIMD_TEST_EQUAL( boost::simd::Mone<T>()            , static_cast<T>(  -1) );
  BOOST_SIMD_TEST_EQUAL( boost::simd::Zero<T>()            , static_cast<T>(   0) );
  BOOST_SIMD_TEST_EQUAL( boost::simd::One<T>()             , static_cast<T>(   1) );
  BOOST_SIMD_TEST_EQUAL( boost::simd::Two<T>()             , static_cast<T>(   2) );
  BOOST_SIMD_TEST_EQUAL( boost::simd::Three<T>()           , static_cast<T>(   3) );
  BOOST_SIMD_TEST_EQUAL( boost::simd::Four<T>()            , static_cast<T>(   4) );
  BOOST_SIMD_TEST_EQUAL( boost::simd::Five<T>()            , static_cast<T>(   5) );
  BOOST_SIMD_TEST_EQUAL( boost::simd::Six<T>()             , static_cast<T>(   6) );
  BOOST_SIMD_TEST_EQUAL( boost::simd::Seven<T>()           , static_cast<T>(   7) );
  BOOST_SIMD_TEST_EQUAL( boost::simd::Eight<T>()           , static_cast<T>(   8) );
  BOOST_SIMD_TEST_EQUAL( boost::simd::Nine<T>()            , static_cast<T>(   9) );
  BOOST_SIMD_TEST_EQUAL( boost::simd::Ten<T>()             , static_cast<T>(  10) );
  BOOST_SIMD_TEST_EQUAL( boost::simd::Fortyfive<T>()       , static_cast<T>(  45) );
  BOOST_SIMD_TEST_EQUAL( boost::simd::Ninety<T>()          , static_cast<T>(  90) );
  BOOST_SIMD_TEST_EQUAL( boost::simd::Hundred<T>()         , static_cast<T>( 100) );
  BOOST_SIMD_TEST_EQUAL( boost::simd::Onehundredeighty<T>(), static_cast<T>( 180) );
  BOOST_SIMD_TEST_EQUAL( boost::simd::Thousand<T>()        , static_cast<T>(1000) );
}

////////////////////////////////////////////////////////////////////////////////
// Test integral_constant for every base types
////////////////////////////////////////////////////////////////////////////////
BOOST_SIMD_TEST_CASE_TPL( integral_constant,BOOST_SIMD_TYPES )
{
  BOOST_SIMD_TEST_EQUAL( (boost::simd::integral_constant<T,42>()), static_cast<T>(42) );
}
