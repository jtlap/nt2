//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/table.hpp>
#include <nt2/include/functions/size.hpp>
#include <nt2/include/functions/cons.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

////////////////////////////////////////////////////////////////////////////////
// size of tables
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( size_table )
{
  using nt2::table;

  table<float, nt2::settings(nt2::_3D)> x( nt2::of_size(4,5,6) );

  table<std::size_t> sz  = nt2::size(x);
  table<std::size_t> ref = nt2::cons<std::size_t>( nt2::of_size(1,3),4,5,6);

  NT2_TEST_EQUAL( sz, ref );
}

////////////////////////////////////////////////////////////////////////////////
// size of expression
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( size_expression )
{
  using nt2::table;

  table<float, nt2::settings(nt2::_3D)> x( nt2::of_size(4,5,6) );

  table<std::size_t> sz  = nt2::size(1.f-x+x/3.f);
  table<std::size_t> ref = nt2::cons<std::size_t>( nt2::of_size(1,3),4,5,6);

  NT2_TEST_EQUAL( sz, ref );
}

////////////////////////////////////////////////////////////////////////////////
// size of size
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( size_size )
{
  using nt2::table;

  table<float, nt2::settings(nt2::_3D)> x( nt2::of_size(4,5,6) );

  table<std::size_t> sz  = nt2::size(nt2::size(x));
  table<std::size_t> ref = nt2::cons<std::size_t>( nt2::of_size(1,2),1,3);

  NT2_TEST_EQUAL( sz, ref );
}
