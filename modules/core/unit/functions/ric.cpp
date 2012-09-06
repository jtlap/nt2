/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::ric function"

#include <nt2/table.hpp>
#include <nt2/include/functions/size.hpp>
#include <nt2/include/functions/ric.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>

NT2_TEST_CASE( ric_size )
{
  NT2_TEST_EQUAL( nt2::extent( nt2::ric(4) ), nt2::of_size(4,4 ));
  NT2_TEST_EQUAL( nt2::size( nt2::ric(4), 1 ), 4u );
  NT2_TEST_EQUAL( nt2::size( nt2::ric(4), 2 ), 4u );
  NT2_TEST_EQUAL( nt2::extent( nt2::ric(4, 5) ), nt2::of_size(4,5 ));
  NT2_TEST_EQUAL( nt2::size( nt2::ric(4, 5), 1 ), 4u );
  NT2_TEST_EQUAL( nt2::size( nt2::ric(4, 5), 2 ), 5u );
  NT2_TEST_EQUAL( nt2::extent( nt2::ric(nt2::of_size(4,5)) ), nt2::of_size(4,5 ) );
  NT2_TEST_EQUAL( nt2::size( nt2::ric(nt2::of_size(4,5)), 1 ), 4u );
  NT2_TEST_EQUAL( nt2::size( nt2::ric(nt2::of_size(4,5)), 2 ), 5u );
  NT2_TEST_EQUAL( nt2::extent( nt2::ric(nt2::of_size(4,1)) ), nt2::of_size(4,1 ) );
  NT2_TEST_EQUAL( nt2::size( nt2::ric(nt2::of_size(4,1)), 1 ), 4u );
  NT2_TEST_EQUAL( nt2::size( nt2::ric(nt2::of_size(4,1)), 2 ), 1u );
  NT2_TEST_EQUAL( nt2::extent( nt2::ric(nt2::of_size(1,4)) ), nt2::of_size(1,4 ) );
  NT2_TEST_EQUAL( nt2::size( nt2::ric(nt2::of_size(1,4)), 1 ), 1u );
  NT2_TEST_EQUAL( nt2::size( nt2::ric(nt2::of_size(1,4)), 2 ), 4u );
}

NT2_TEST_CASE( ric_untyped_square )
{
  nt2::table<double> x0 = nt2::ric(3);

  for(int i=1;i<= 3;++i)
    for(int j=1;j<= 3;++j)
      NT2_TEST_EQUAL( i-1, x0(i, j) );

  nt2::table<double, nt2::C_index_> x1 = nt2::ric(3);

  for(int i=0;i< 3;++i)
    for(int j=0;j< 3;++j)
      NT2_TEST_EQUAL( i, x1(i, j) );
}

NT2_TEST_CASE( ric_nd_untyped )
{
 nt2::table<double> x2 = nt2::ric(8, 4);
 for(int i=1;i<=8;++i)
  for(int j=1;j<=4;++j)
    NT2_TEST_EQUAL( i-1, x2(i, j) );

 nt2::table<double> x3 = nt2::ric(2, 4);
 for(int i=1;i<=2;++i)
  for(int j=1;j<=4;++j)
    NT2_TEST_EQUAL( i-1, x3(i, j) );

  nt2::table<double> x4 = nt2::ric(1, 4);
  for(int j=1;j<=4;++j) NT2_TEST_EQUAL( 0, x4(1, j) );

 nt2::table<double> x5 = nt2::ric(2, 1);
 for(int i=1;i<=2;++i) NT2_TEST_EQUAL( i-1, x5(i, 1) );

 nt2::table<double> x6 = nt2::ric(nt2::of_size(8, 6));
 for(int i=1;i<=8;++i)
  for(int j=1;j<=6;++j)
  NT2_TEST_EQUAL( i-1, x6(i, j) );
}

NT2_TEST_CASE_TPL( ric_nd_typed, NT2_TYPES )
{
  nt2::table<T> x1 = nt2::ric(8, nt2::meta::as_<T>() );
  for(int i=1;i<=8;++i) for(int j=1;j<=8;++j) NT2_TEST_EQUAL( T(i-1), x1(i, j) );

  nt2::table<T> x2 = nt2::ric(8,4, nt2::meta::as_<T>() );
  for(int i=1;i<=8;++i) for(int j=1;j<=4;++j) NT2_TEST_EQUAL( T(i-1), x2(i, j) );

  nt2::table<T> x3 = nt2::ric(2,4, nt2::meta::as_<T>() );
  for(int i=1;i<=2;++i) for(int j=1;j<=4;++j) NT2_TEST_EQUAL( T(i-1), x3(i, j) );

  nt2::table<T> x4 = nt2::ric(nt2::of_size(8, 6), nt2::meta::as_<T>() );
  for(int i=1;i<=8;++i) for(int j=1;j<=6;++j) NT2_TEST_EQUAL( T(i-1), x4(i, j) );
}

NT2_TEST_CASE( ric_expr )
{
  nt2::table<int> t(nt2::of_size(1, 2) );
  t(1) = 3;
  t(2) = 4;

  nt2::table<double> x1 = nt2::ric( t );
  for(int i=1;i<=3;++i)
    for(int j=1;j<=4;++j)
      NT2_TEST_EQUAL( i-1, x1(i, j) );

  nt2::table<int> a( nt2::of_size(4,5) );
  nt2::table<double> x2 = nt2::ric( nt2::size(a) );

  for(int i=1;i<=4;++i)
    for(int j=1;j<=5;++j)
      NT2_TEST_EQUAL( i-1, x2(i, j) );

  NT2_TEST_ASSERT( x1 = nt2::ric(a) );
}

NT2_TEST_CASE_TPL( ric_typed_expr, NT2_TYPES )
{
  nt2::table<int> t(nt2::of_size(1, 2) );
  t(1) = 3;
  t(2) = 4;

  nt2::table<T> x1 = nt2::ric( t, nt2::meta::as_<T>() );
  for(int i=1;i<=3;++i)
    for(int j=1;j<=4;++j)
      NT2_TEST_EQUAL( T(i-1), x1(i, j) );

  nt2::table<int> a( nt2::of_size(4,5) );
  nt2::table<T> x2 = nt2::ric( nt2::size(a), nt2::meta::as_<T>() );

  for(int i=1;i<=4;++i)
    for(int j=1;j<=5;++j)
      NT2_TEST_EQUAL(T(i-1), x2(i, j) );

  NT2_TEST_ASSERT( x1 = nt2::ric(a, nt2::meta::as_<T>() ) );
}
