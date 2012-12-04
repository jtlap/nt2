/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::linesstride function"

#include <nt2/table.hpp>
#include <nt2/include/functions/linesstride.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

////////////////////////////////////////////////////////////////////////////////
// linesstride of arithmetic types
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( fundamental_linesstride )
{
  using nt2::linesstride;

  NT2_TEST_EQUAL( linesstride( 3 , 1 ), 1u);
  NT2_TEST_EQUAL( linesstride( 3 , 2 ), 1u);
  NT2_TEST_EQUAL( linesstride( 3 , 3 ), 1u);
}

////////////////////////////////////////////////////////////////////////////////
// linesstride of tables
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( linesstride_table )
{
  using nt2::table;

  table<float, nt2::settings(nt2::_3D)> x( nt2::of_size(4,5,6) );

  NT2_TEST_EQUAL( nt2::linesstride( x , 1), 1u);
  NT2_TEST_EQUAL( nt2::linesstride( x , 2), 4u);
  NT2_TEST_EQUAL( nt2::linesstride( x , 3), 20u);
  NT2_TEST_EQUAL( nt2::linesstride( x , 4), 120u);
}

////////////////////////////////////////////////////////////////////////////////
// linesstride of expression
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( linesstride_expression )
{
  using nt2::table;

  table<float, nt2::settings(nt2::_3D)> x( nt2::of_size(4,5,6) );

  NT2_TEST_EQUAL( nt2::linesstride( x+x/3.f, 1),  1u);
  NT2_TEST_EQUAL( nt2::linesstride( x+x/3.f, 2),  4u);
  NT2_TEST_EQUAL( nt2::linesstride( x+x/3.f, 3),  20u);
  NT2_TEST_EQUAL( nt2::linesstride( x+x/3.f, 4),  120u);
}


