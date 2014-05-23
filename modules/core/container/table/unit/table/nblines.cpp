//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/table.hpp>
#include <nt2/include/functions/nblines.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

////////////////////////////////////////////////////////////////////////////////
// nblines of tables
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( nblines_table )
{
  using nt2::table;

  table<float, nt2::settings(nt2::_3D)> x( nt2::of_size(4,5,6) );

  NT2_TEST_EQUAL( nt2::nblines( x , 1), 30u);
  NT2_TEST_EQUAL( nt2::nblines( x , 2), 24u);
  NT2_TEST_EQUAL( nt2::nblines( x , 3), 20u);
  NT2_TEST_EQUAL( nt2::nblines( x , 4), 120u);
}

////////////////////////////////////////////////////////////////////////////////
// nblines of expression
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( nblines_expression )
{
  using nt2::table;

  table<float, nt2::settings(nt2::_3D)> x( nt2::of_size(4,5,6) );

  NT2_TEST_EQUAL( nt2::nblines( x+x/3.f, 1),  30u);
  NT2_TEST_EQUAL( nt2::nblines( x+x/3.f, 2),  24u);
  NT2_TEST_EQUAL( nt2::nblines( x+x/3.f, 3),  20u);
  NT2_TEST_EQUAL( nt2::nblines( x+x/3.f, 4),  120u);
}
