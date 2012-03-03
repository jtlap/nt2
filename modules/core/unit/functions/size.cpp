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

  NT2_TEST_EQUAL( std::size_t( size( 3 )(1)), 1u);
  NT2_TEST_EQUAL( std::size_t( size( 3 )(2)), 1u);
  NT2_TEST_EQUAL( size( 3 , 1 ), 1u);
  NT2_TEST_EQUAL( size( 3 , 2 ), 1u);
}

////////////////////////////////////////////////////////////////////////////////
// size of tables
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( size_table )
{
  using nt2::table;

  table<float, nt2::settings(nt2::_3D)> x( nt2::of_size(4,5,6) );

  NT2_TEST_EQUAL( std::size_t(nt2::size( x )(1)), 4u);
  NT2_TEST_EQUAL( std::size_t(nt2::size( x )(2)), 5u);
  NT2_TEST_EQUAL( std::size_t(nt2::size( x )(3)), 6u);

  NT2_TEST_EQUAL( nt2::size( x , 1), 4u);
  NT2_TEST_EQUAL( nt2::size( x , 2), 5u);
  NT2_TEST_EQUAL( nt2::size( x , 3), 6u);
}

////////////////////////////////////////////////////////////////////////////////
// size of expression
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( size_expression )
{
  using nt2::table;

  table<float, nt2::settings(nt2::_3D)> x( nt2::of_size(4,5,6) );

  NT2_TEST_EQUAL( std::size_t(nt2::size( x+x/3.f )(1)), 4u);
  NT2_TEST_EQUAL( std::size_t(nt2::size( x+x/3.f )(2)), 5u);
  NT2_TEST_EQUAL( std::size_t(nt2::size( x+x/3.f )(3)), 6u);

  NT2_TEST_EQUAL( nt2::size( x+x/3.f , 1), 4u);
  NT2_TEST_EQUAL( nt2::size( x+x/3.f , 2), 5u);
  NT2_TEST_EQUAL( nt2::size( x+x/3.f , 3), 6u);
}

////////////////////////////////////////////////////////////////////////////////
// size of size
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( size_size )
{
  using nt2::table;
  table<float, nt2::settings(nt2::_3D)> x( nt2::of_size(4,5,6) );

  NT2_TEST_EQUAL( std::size_t(nt2::size( nt2::size(x) )(1)), 1u);
  NT2_TEST_EQUAL( std::size_t(nt2::size( nt2::size(x) )(2)), 3u);

  NT2_TEST_EQUAL( nt2::size( nt2::size(x) , 1), 1u);
  NT2_TEST_EQUAL( nt2::size( nt2::size(x) , 2), 3u);

  NT2_TEST_EQUAL( std::size_t(nt2::size( nt2::size( nt2::size(x) ) )(1)), 1u);
  NT2_TEST_EQUAL( std::size_t(nt2::size( nt2::size( nt2::size(x) ) )(2)), 2u);

  NT2_TEST_EQUAL( nt2::size( nt2::size( nt2::size(x) ) , 1), 1u);
  NT2_TEST_EQUAL( nt2::size( nt2::size( nt2::size(x) ) , 2), 2u);
}

////////////////////////////////////////////////////////////////////////////////
// size of static table 2D
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( size_static_table2D )
{
  using nt2::of_size_;
  using nt2::table;
  table < float, nt2::settings(of_size_<5, 2>) > x;

  NT2_TEST_EQUAL( std::size_t(nt2::size(x)(1)), 5u);
  NT2_TEST_EQUAL( std::size_t(nt2::size(x)(2)), 2u);

  NT2_TEST_EQUAL( nt2::size(x, 1), 5u);
  NT2_TEST_EQUAL( nt2::size(x, 2), 2u);
}
////////////////////////////////////////////////////////////////////////////////
// size of container
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( size_cont )
{
  using nt2::meta::make_container;
  using nt2::of_size_;
  using nt2::table;
  typedef typename make_container<nt2::tag::table_, float, of_size_<5> >::type cont;
  cont x;

  NT2_TEST_EQUAL( std::size_t(nt2::size(x)(1)), 5u);
  NT2_TEST_EQUAL( std::size_t(nt2::size(x)(2)), 1u);

  NT2_TEST_EQUAL( nt2::size(x, 1), 5u);
  NT2_TEST_EQUAL( nt2::size(x, 2), 1u);

}
////////////////////////////////////////////////////////////////////////////////
// size of static table 1D
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( size_static_table )
{
  using nt2::of_size_;
  using nt2::table;
  table < float, nt2::settings(of_size_<5>) > x;

  NT2_TEST_EQUAL( std::size_t(nt2::size(x)(1)), 5u);
  NT2_TEST_EQUAL( std::size_t(nt2::size(x)(2)), 1u);

  NT2_TEST_EQUAL( nt2::size(x, 1), 5u);
  NT2_TEST_EQUAL( nt2::size(x, 2), 1u);
}
