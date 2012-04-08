//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2::squeeze function"

#include <nt2/table.hpp>
#include <nt2/include/functions/squeeze.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

//==============================================================================
// Squeezing 2D array is identity
//==============================================================================
NT2_TEST_CASE( squeeze_2D )
{
  nt2::table<double, nt2::_2D> x( nt2::of_size(1,5) ), sx;
  nt2::table<double, nt2::_2D> y( nt2::of_size(5,1) ), sy;
  nt2::table<double, nt2::_2D> z( nt2::of_size(1,1) ), sz;

  for(std::size_t i=1;i<=5;++i) x(i) = double(i);
  sx = nt2::squeeze(x);

  NT2_TEST( sx.extent() == x.extent() );
  for(std::size_t i=1;i<=5;++i) NT2_TEST_EQUAL( double(x(i)) , double(sx(i)) );

  for(std::size_t i=1;i<=5;++i) y(i) = double(i);
  sy = nt2::squeeze(y);

  NT2_TEST( sy.extent() == y.extent() );
  for(std::size_t i=1;i<=5;++i) NT2_TEST_EQUAL( double(y(i)) , double(sy(i)) );

  z(1) = double(1);
  sz = nt2::squeeze(z);

  NT2_TEST( sz.extent() == z.extent() );
  NT2_TEST_EQUAL( double(z(1)) , double(sy(1)) );
}

template<class S, class Z> void test_squeeze(S const& old_s, Z const& new_s)
{
  nt2::table<double, S> x(old_s);
  for(std::size_t i=1;i<=nt2::numel(old_s);++i) x(i) = double(i);

  nt2::table<double, S> sx = nt2::squeeze(x);

  NT2_TEST( sx.extent() == new_s );

  for(std::size_t i=1;i<=nt2::numel(old_s);++i)
    NT2_TEST_EQUAL( double(x(i)) , double(sx(i)) );
}

NT2_TEST_CASE( squeeze_3D )
{
  test_squeeze( nt2::of_size(1,3,3) , nt2::of_size(3,3) );
  test_squeeze( nt2::of_size(3,1,3) , nt2::of_size(3,3) );
  test_squeeze( nt2::of_size(3,3,1) , nt2::of_size(3,3) );
  test_squeeze( nt2::of_size(3,1,1) , nt2::of_size(3,1) );
  test_squeeze( nt2::of_size(1,3,1) , nt2::of_size(3,1) );
  test_squeeze( nt2::of_size(1,1,3) , nt2::of_size(3,1) );
  test_squeeze( nt2::of_size(1,1,1) , nt2::of_size(1,1) );
}

NT2_TEST_CASE( squeeze_4D )
{
  test_squeeze( nt2::of_size(1,3,3,3) , nt2::of_size(3,3,3) );
  test_squeeze( nt2::of_size(3,1,3,3) , nt2::of_size(3,3,3) );
  test_squeeze( nt2::of_size(3,3,1,3) , nt2::of_size(3,3,3) );
  test_squeeze( nt2::of_size(3,3,3,1) , nt2::of_size(3,3,3) );

  test_squeeze( nt2::of_size(1,1,3,3) , nt2::of_size(3,3) );
  test_squeeze( nt2::of_size(1,3,1,3) , nt2::of_size(3,3) );
  test_squeeze( nt2::of_size(1,3,3,1) , nt2::of_size(3,3) );
  test_squeeze( nt2::of_size(3,1,1,3) , nt2::of_size(3,3) );
  test_squeeze( nt2::of_size(3,1,3,1) , nt2::of_size(3,3) );
  test_squeeze( nt2::of_size(3,3,1,1) , nt2::of_size(3,3) );

  test_squeeze( nt2::of_size(3,1,1,1) , nt2::of_size(3,1) );
  test_squeeze( nt2::of_size(1,3,1,1) , nt2::of_size(3,1) );
  test_squeeze( nt2::of_size(1,1,3,1) , nt2::of_size(3,1) );
  test_squeeze( nt2::of_size(1,1,1,3) , nt2::of_size(3,1) );

  test_squeeze( nt2::of_size(1,1,1,1) , nt2::of_size(1,1) );
}
