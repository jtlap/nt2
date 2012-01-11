/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::size function"

#include <iostream>
#include <nt2/include/functions/size.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

////////////////////////////////////////////////////////////////////////////////
// size of arithmetic types
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( fundamental_size )
{
  using nt2::size;

  NT2_TEST_EQUAL( std::size_t( size( 3 )(1)), 1);
  NT2_TEST_EQUAL( std::size_t( size( 3 )(2)), 1);
}

////////////////////////////////////////////////////////////////////////////////
// size of tables
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( size_table )
{
  using nt2::size;
  using nt2::table;

  table<float, nt2::settings(nt2::_3D)> x( nt2::of_size(4,5,6) );

  NT2_TEST_EQUAL( std::size_t(size( x )(1)), 4);
  NT2_TEST_EQUAL( std::size_t(size( x )(2)), 5);
  NT2_TEST_EQUAL( std::size_t(size( x )(3)), 6);
}

////////////////////////////////////////////////////////////////////////////////
// size of expression
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( size_expression )
{
  using nt2::size;
  using nt2::table;

  table<float, nt2::settings(nt2::_3D)> x( nt2::of_size(4,5,6) );

  NT2_TEST_EQUAL( std::size_t(size( x+x/3.f )(1)), 4);
  NT2_TEST_EQUAL( std::size_t(size( x+x/3.f )(2)), 5);
  NT2_TEST_EQUAL( std::size_t(size( x+x/3.f )(3)), 6);
}

////////////////////////////////////////////////////////////////////////////////
// size of expression
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( size_size )
{
  using nt2::size;
  using nt2::table;

  table<float, nt2::settings(nt2::_3D)> x( nt2::of_size(4,5,6) );

  NT2_TEST_EQUAL( std::size_t(size( size(x) )(1)), 1);
  NT2_TEST_EQUAL( std::size_t(size( size(x) )(2)), 3);

  NT2_TEST_EQUAL( std::size_t(size( size( size(x) ) )(1)), 1);
  NT2_TEST_EQUAL( std::size_t(size( size( size(x) ) )(2)), 2);

}
