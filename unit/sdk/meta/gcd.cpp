/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::meta::gcd"

#include <nt2/sdk/meta/gcd.hpp>

#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>

////////////////////////////////////////////////////////////////////////////////
// Test gcd with 1 argument
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(unary_gcd)
{
  using nt2::meta::gcd;

  NT2_TEST_EQUAL( gcd<0>::value , 0 );
  NT2_TEST_EQUAL( gcd<42>::value, 42);
}

////////////////////////////////////////////////////////////////////////////////
// Test gcd with 2 arguments
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(binary_gcd)
{
  using nt2::meta::gcd;

  NT2_TEST_EQUAL( (gcd<0,0>::value) , 0  );
  NT2_TEST_EQUAL( (gcd<0,42>::value), 42 );
  NT2_TEST_EQUAL( (gcd<42,0>::value), 42 );
  NT2_TEST_EQUAL( (gcd<2,5>::value) , 1  );
  NT2_TEST_EQUAL( (gcd<2,8>::value) , 2  );
  NT2_TEST_EQUAL( (gcd<12,8>::value), 4  );
}
