/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::rows function"

#include <nt2/table.hpp>
#include <nt2/include/functions/size.hpp>
#include <nt2/include/functions/rows.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>


NT2_TEST_CASE( rows_size )
{
  NT2_TEST( nt2::extent( nt2::rows(4, 4, 1.0) ) == nt2::of_size(4,4 ));
  NT2_TEST_EQUAL( nt2::size( nt2::rows(4, 4, 1.0), 1 ), 4 );
  NT2_TEST_EQUAL( nt2::size( nt2::rows(4, 4, 1.0), 2 ), 4 );
  NT2_TEST( nt2::extent( nt2::rows(4, 5, 1.0) ) == nt2::of_size(4,5 ));
  NT2_TEST_EQUAL( nt2::size( nt2::rows(4, 5, 1.0), 1 ), 4 );
  NT2_TEST_EQUAL( nt2::size( nt2::rows(4, 5, 1.0), 2 ), 5 );
  NT2_TEST( nt2::extent( nt2::rows(nt2::of_size(4,5), 1.0) ) == nt2::of_size(4,5) );
  NT2_TEST_EQUAL( nt2::size( nt2::rows(nt2::of_size(4,5),1.0), 1 ), 4 );
  NT2_TEST_EQUAL( nt2::size( nt2::rows(nt2::of_size(4,5),1.0), 2 ), 5 );
  NT2_TEST( nt2::extent( nt2::rows(nt2::of_size(4,1),1.0) ) == nt2::of_size(4,1) );
  NT2_TEST_EQUAL( nt2::size( nt2::rows(nt2::of_size(4,1),1.0), 1 ), 4 );
  NT2_TEST_EQUAL( nt2::size( nt2::rows(nt2::of_size(4,1),1.0), 2 ), 1 );
  NT2_TEST( nt2::extent( nt2::rows(nt2::of_size(1,4),1.0) ) == nt2::of_size(1,4) );
  NT2_TEST_EQUAL( nt2::size( nt2::rows(nt2::of_size(1,4),1.0), 1 ), 1 );
  NT2_TEST_EQUAL( nt2::size( nt2::rows(nt2::of_size(1,4),1.0), 2 ), 4 );
}

////NT2_TEST_CASE( rows_nd_untyped )
////{
  ////nt2::table<double> x0 = nt2::rows(3, 3, 0.0);
////
  ////for(int i=1;i<= 3;++i)
    ////for(int j=1;j<= 3;++j)
      ////NT2_TEST_EQUAL( double(i), double(x0(i, j)) );
////
  ////for(int i=1;i<= 3;++i)
  ////{
    ////for(int j=1;j<= 3;++j)
      ////std::cout << double(x0(i, j)) << " ";
    ////std::cout << std::endl;
  ////}
////
  ////nt2::table<double, nt2::C_index_> x1 = nt2::rows(3, 3, 0.0);
  ////for(int i=0;i<3;++i)
    ////for(int j=0;j<3;++j)
      ////NT2_TEST_EQUAL( double(i), double(x1(i, j)) );
////
  ////for(int i=0;i< 3;++i)
  ////{
    ////for(int j=0;j< 3;++j)
      ////std::cout << double(x1(i, j)) << " ";
    ////std::cout << std::endl;
  ////}
   ////nt2::table<double> x2 = nt2::rows(8, 4, 0.0);
   ////for(int i=1;i<=8;++i) for(int j=1;j<=4;++j)NT2_TEST_EQUAL( double(i), double(x2(i, j)) );
   ////nt2::table<double> x3 = nt2::rows(2, 4, 0.0);
   ////for(int i=1;i<=2;++i) for(int j=1;j<=4;++j)NT2_TEST_EQUAL( double(i), double(x3(i, j)) );
   ////nt2::table<double> x4 = nt2::rows(1, 4, 0.0);
   ////for(int j=1;j<=4;++j)NT2_TEST_EQUAL( double(1), double(x4(1, j)) );
   ////nt2::table<double> x5 = nt2::rows(2, 1, 0.0);
   ////for(int i=1;i<=2;++i) NT2_TEST_EQUAL( double(i), double(x5(i, 1)) );
   ////nt2::table<double> x6 = nt2::rows(nt2::of_size(8, 6), 4.0);
   ////for(int i=1;i<=8;++i) for(int j=1;j<=6;++j)NT2_TEST_EQUAL( double(i+4), double(x6(i, j)) );
////}

////NT2_TEST_CASE_TPL( rows_nd_typed, NT2_TYPES )
 ////{
   ////nt2::table<T> x2 = nt2::rows(8,4, T(22.5) );
   ////for(int i=1;i<=8;++i) for(int j=1;j<=4;++j) NT2_TEST_EQUAL( T(22.5+i), T(x2(i, j)) );
   ////nt2::table<T> x3 = nt2::rows(2,4, T(22.5) );
   ////for(int i=1;i<=2;++i) for(int j=1;j<=4;++j) NT2_TEST_EQUAL( T(22.5+i), T(x3(i, j)) );
   ////nt2::table<T> x4 = nt2::rows(nt2::of_size(8, 6), T(22.5) );
   ////for(int i=1;i<=8;++i) for(int j=1;j<=6;++j) NT2_TEST_EQUAL( T(22.5+i), T(x4(i, j)) );
////
////
 ////}
////
////NT2_TEST_CASE( rows_expr )
////{
  ////nt2::table<int> a( nt2::of_size(4,5) );
  ////nt2::table<double> x1 = nt2::rows( nt2::size(a), 22.5);
  ////for(int i=1;i<=4;++i) for(int j=1;j<=5;++j) NT2_TEST_EQUAL(  double(i+22.5), double(x1(i, j)) );
  ////NT2_TEST_ASSERT( x1 = nt2::rows(a, 2.0) );
////}
////
////// NT2_TEST_CASE_TPL( rows_typed_expr, NT2_TYPES )
////// {
//////   nt2::table<int> t(nt2::of_size(1, 2) );
//////   t(1) = 3;
//////   t(2) = 4;
//////   nt2::table<T> x1 = nt2::rows( t, nt2::meta::as_<T>() );
//////   for(int i=1;i<=3;++i) for(int j=1;j<=4;++j) NT2_TEST_EQUAL( T(i), T(x1(i, j)));
//////   nt2::table<int> a( nt2::of_size(4,5) );
//////   nt2::table<T> x2 = nt2::rows( nt2::size(a), nt2::meta::as_<T>() );
//////   for(int i=1;i<=4;++i) for(int j=1;j<=5;++j) NT2_TEST_EQUAL( T(i), T(x2(i, j)));
////
////// }
////
////
////// NT2_TEST_CASE_TPL( rows_scaled, NT2_REAL_TYPES )
//////  {
//////    nt2::table<T> x2 = nt2::rows(nt2::of_size(4,4), T(4), T(-1));
//////    for(int i=1;i<=8;++i) for(int j=1;j<=4;++j) NT2_TEST_EQUAL( T(22.5+i), T(x2(i, j)) );
//////  }
