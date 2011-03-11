/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::constants digits"

#include <nt2/sdk/constant/digits.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

#ifdef BOOST_MSVC
  #pragma warning(disable: 4309) // truncation of constant value
#endif

////////////////////////////////////////////////////////////////////////////////
// Test value of digit constant for every base types
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL( digit_value, NT2_TYPES )
{
  NT2_TEST_EQUAL( nt2::Mten<T>()            , static_cast<T>( -10) );
  NT2_TEST_EQUAL( nt2::Mnine<T>()           , static_cast<T>(  -9) );
  NT2_TEST_EQUAL( nt2::Meight<T>()          , static_cast<T>(  -8) );
  NT2_TEST_EQUAL( nt2::Mseven<T>()          , static_cast<T>(  -7) );
  NT2_TEST_EQUAL( nt2::Msix<T>()            , static_cast<T>(  -6) );
  NT2_TEST_EQUAL( nt2::Mfive<T>()           , static_cast<T>(  -5) );
  NT2_TEST_EQUAL( nt2::Mfour<T>()           , static_cast<T>(  -4) );
  NT2_TEST_EQUAL( nt2::Mthree<T>()          , static_cast<T>(  -3) );
  NT2_TEST_EQUAL( nt2::Mtwo<T>()            , static_cast<T>(  -2) );
  NT2_TEST_EQUAL( nt2::Mone<T>()            , static_cast<T>(  -1) );
  NT2_TEST_EQUAL( nt2::Zero<T>()            , static_cast<T>(   0) );
  NT2_TEST_EQUAL( nt2::One<T>()             , static_cast<T>(   1) );
  NT2_TEST_EQUAL( nt2::Two<T>()             , static_cast<T>(   2) );
  NT2_TEST_EQUAL( nt2::Three<T>()           , static_cast<T>(   3) );
  NT2_TEST_EQUAL( nt2::Four<T>()            , static_cast<T>(   4) );
  NT2_TEST_EQUAL( nt2::Five<T>()            , static_cast<T>(   5) );
  NT2_TEST_EQUAL( nt2::Six<T>()             , static_cast<T>(   6) );
  NT2_TEST_EQUAL( nt2::Seven<T>()           , static_cast<T>(   7) );
  NT2_TEST_EQUAL( nt2::Eight<T>()           , static_cast<T>(   8) );
  NT2_TEST_EQUAL( nt2::Nine<T>()            , static_cast<T>(   9) );
  NT2_TEST_EQUAL( nt2::Ten<T>()             , static_cast<T>(  10) );
  NT2_TEST_EQUAL( nt2::Fortyfive<T>()       , static_cast<T>(  45) );
  NT2_TEST_EQUAL( nt2::Ninety<T>()          , static_cast<T>(  90) );
  NT2_TEST_EQUAL( nt2::Hundred<T>()         , static_cast<T>( 100) );
  NT2_TEST_EQUAL( nt2::Onehundredeighty<T>(), static_cast<T>( 180) );
  NT2_TEST_EQUAL( nt2::Thousand<T>()        , static_cast<T>(1000) );
}

////////////////////////////////////////////////////////////////////////////////
// Test integral_constant for every base types
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL( integral_constant,NT2_TYPES )
{
  NT2_TEST_EQUAL( (nt2::integral_constant<T,42>()), static_cast<T>(42) );
}
