/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::indices function"

#include <nt2/table.hpp>
#include <nt2/options.hpp>
#include <nt2/include/functions/size.hpp>
#include <nt2/include/functions/indices.hpp>
#include <nt2/include/functions/cif.hpp>
#include <nt2/include/functions/rif.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>

NT2_TEST_CASE( indices_size )
{
  using nt2::along_; 
  NT2_TEST_EQUAL( nt2::extent( nt2::indices(4, along_, 1) ), nt2::of_size(4,4 ));
  NT2_TEST_EQUAL( nt2::size( nt2::indices(4, along_, 1), 1 ), 4u );
  NT2_TEST_EQUAL( nt2::size( nt2::indices(4, along_, 1), 2 ), 4u );
  NT2_TEST_EQUAL( nt2::extent( nt2::indices(4, 5, along_, 1) ), nt2::of_size(4,5 ));
  NT2_TEST_EQUAL( nt2::size( nt2::indices(4, 5, along_, 1), 1 ), 4u );
  NT2_TEST_EQUAL( nt2::size( nt2::indices(4, 5, along_, 1), 2 ), 5u );
  
//   NT2_TEST_EQUAL( nt2::extent( nt2::indices(nt2::of_size(4,5, along_, 1)) ), nt2::of_size(4,5 ) );
//   NT2_TEST_EQUAL( nt2::size( nt2::indices(nt2::of_size(4,5), along_, 1), 1 ), 4 );
//   NT2_TEST_EQUAL( nt2::size( nt2::indices(nt2::of_size(4,5), along_, 1), 2 ), 5 );
//   NT2_TEST_EQUAL( nt2::extent( nt2::indices(nt2::of_size(4,1), along_, 1) ), nt2::of_size(4,1 ) );
//   NT2_TEST_EQUAL( nt2::size( nt2::indices(nt2::of_size(4,1), along_, 1), 1 ), 4 );
//   NT2_TEST_EQUAL( nt2::size( nt2::indices(nt2::of_size(4,1), along_, 1), 2 ), 1 );
//   NT2_TEST_EQUAL( nt2::extent( nt2::indices(nt2::of_size(1,4, along_, 1)) ), nt2::of_size(1,4 ) );
//   NT2_TEST_EQUAL( nt2::size( nt2::indices(nt2::of_size(1,4), along_, 1), 1 ), 1 );
//   NT2_TEST_EQUAL( nt2::size( nt2::indices(nt2::of_size(1,4), along_, 1), 2 ), 4 );

  NT2_TEST_EQUAL( nt2::extent( nt2::indices(nt2::of_size(4,5), 1) ), nt2::of_size(4,5 ) );
  NT2_TEST_EQUAL( nt2::size( nt2::indices(nt2::of_size(4,5), 1), 1 ), 4u );
  NT2_TEST_EQUAL( nt2::size( nt2::indices(nt2::of_size(4,5), 1), 2 ), 5u );
  NT2_TEST_EQUAL( nt2::extent( nt2::indices(nt2::of_size(4,1), 1) ), nt2::of_size(4,1 ) );
  NT2_TEST_EQUAL( nt2::size( nt2::indices(nt2::of_size(4,1), 1), 1 ), 4u );
  NT2_TEST_EQUAL( nt2::size( nt2::indices(nt2::of_size(4,1), 1), 2 ), 1u );
  NT2_TEST_EQUAL( nt2::extent( nt2::indices(nt2::of_size(1,4), 1) ), nt2::of_size(1,4 ) );
  NT2_TEST_EQUAL( nt2::size( nt2::indices(nt2::of_size(1,4), 1), 1 ), 1u );
  NT2_TEST_EQUAL( nt2::size( nt2::indices(nt2::of_size(1,4), 1), 2 ), 4u );

  NT2_TEST_EQUAL( nt2::extent( nt2::indices(nt2::of_size(4,5,2), 1) ), nt2::of_size(4,5,2) );
  NT2_TEST_EQUAL( nt2::size( nt2::indices(nt2::of_size(4,5,2), 1), 1 ), 4u );
  NT2_TEST_EQUAL( nt2::size( nt2::indices(nt2::of_size(4,5,2), 1), 2 ), 5u );
  NT2_TEST_EQUAL( nt2::size( nt2::indices(nt2::of_size(4,5,2), 1), 3 ), 2u );
  
}

NT2_TEST_CASE( indices_untyped_square )
{
  nt2::table<double> x0 = nt2::indices(3, nt2::along_, 1);
  NT2_DISPLAY(x0);
  for(int i=1;i<= 3;++i)
    for(int j=1;j<= 3;++j)
      NT2_TEST_EQUAL( i, x0(i, j) );

  nt2::table<double, nt2::C_index_> x1 = nt2::indices(3, nt2::along_, 1);
  NT2_DISPLAY(x1);

  for(int i=0;i< 3;++i)
    for(int j=0;j< 3;++j)
      NT2_TEST_EQUAL( i+1, x1(i, j) );

  nt2::table<double> x02 = nt2::indices(3, nt2::along_, 2);
  NT2_DISPLAY(x02);

  for(int i=1;i<= 3;++i)
    for(int j=1;j<= 3;++j)
      NT2_TEST_EQUAL( j, x02(i, j) );

  nt2::table<double, nt2::C_index_> x12 = nt2::indices(3, nt2::along_, 2);
  NT2_DISPLAY(x12);

  for(int i=0;i< 3;++i)
    for(int j=0;j< 3;++j)
      NT2_TEST_EQUAL( j+1, x12(i, j) );

  nt2::table<double> x03 = nt2::indices(3, nt2::along_, 3);
  NT2_DISPLAY(x03);

  for(int i=1;i<= 3;++i)
    for(int j=1;j<= 3;++j)
      NT2_TEST_EQUAL( 1, x03(i, j) );

  nt2::table<double, nt2::C_index_> x13 = nt2::indices(3, nt2::along_, 3);
  NT2_DISPLAY(x13);

  for(int i=0;i< 3;++i)
    for(int j=0;j< 3;++j)
      NT2_TEST_EQUAL( 1, x13(i, j) );
}

NT2_TEST_CASE( indices_nd_untyped )
{
  nt2::table<double> x2 = nt2::indices(8, 4, nt2::along_, 1);
  for(int i=1;i<=8;++i)
    for(int j=1;j<=4;++j)
      NT2_TEST_EQUAL( i, x2(i, j) );
  
  nt2::table<double> x22 = nt2::indices(8, 4, nt2::along_, 2);
  for(int i=1;i<=8;++i)
    for(int j=1;j<=4;++j)
      NT2_TEST_EQUAL( j, x22(i, j) );

  nt2::table<double> x23 = nt2::indices(8, 4, nt2::along_, 3);
  for(int i=1;i<=8;++i)
    for(int j=1;j<=4;++j)
      NT2_TEST_EQUAL( 1, x23(i, j) );
 
}

NT2_TEST_CASE_TPL( indices_nd_typed, NT2_TYPES )
{
  nt2::table<T> x2 = nt2::indices(8, 4, nt2::along_, 1, nt2::meta::as_<T>());
  for(int i=1;i<=8;++i)
    for(int j=1;j<=4;++j)
      NT2_TEST_EQUAL( T(i), x2(i, j) );
  
  nt2::table<T> x22 = nt2::indices(8, 4, nt2::along_, 2, nt2::meta::as_<T>());
  for(int i=1;i<=8;++i)
    for(int j=1;j<=4;++j)
      NT2_TEST_EQUAL( T(j), x22(i, j) );

  nt2::table<T> x23 = nt2::indices(8, 4, nt2::along_, 3, nt2::meta::as_<T>());
  for(int i=1;i<=8;++i)
    for(int j=1;j<=4;++j)
      NT2_TEST_EQUAL( T(1), x23(i, j)); 
}

NT2_TEST_CASE_TPL( indices_expr, NT2_TYPES)
{
  nt2::table<T> t(nt2::of_size(1, 2) );
  t(1) = 8;
  t(2) = 4;

  nt2::table<T> x2 = nt2::indices(t, 1, nt2::meta::as_<T>());
  for(int i=1;i<=8;++i)
    for(int j=1;j<=4;++j)
      NT2_TEST_EQUAL( T(i), x2(i, j) );
  
  nt2::table<T> x22 = nt2::indices(t, 2, nt2::meta::as_<T>());
  for(int i=1;i<=8;++i)
    for(int j=1;j<=4;++j)
      NT2_TEST_EQUAL( T(j), x22(i, j) );

  nt2::table<T> x23 = nt2::indices(t, 3, nt2::meta::as_<T>());
  for(int i=1;i<=8;++i)
    for(int j=1;j<=4;++j)
      NT2_TEST_EQUAL( T(1), x23(i, j));
  {
    nt2::table<T> t(nt2::of_size(1, 3) );
    t(1) = 3;
    t(2) = 4;
    t(3) = 2;
    
    nt2::table<T> x2 = nt2::indices(t, 1, nt2::meta::as_<T>());
    for(int i=1;i<=3;++i)
      for(int j=1;j<=4;++j)
        for(int k = 1; k <= 2; ++k)
          NT2_TEST_EQUAL( T(i), x2(i, j, k) );
    
    nt2::table<T> x22 = nt2::indices(t, 2, nt2::meta::as_<T>());
    for(int i=1;i<=3;++i)
      for(int j=1;j<=4;++j)
        for(int k = 1; k <= 2; ++k)
          NT2_TEST_EQUAL( T(j), x22(i, j, k) );
    
    nt2::table<T> x23 = nt2::indices(t, 3, nt2::meta::as_<T>());
    for(int i=1;i<=3;++i)
      for(int j=1;j<=4;++j)
         for(int k = 1; k <= 2; ++k)
           NT2_TEST_EQUAL(T(k), x23(i, j, k));
  }

}

NT2_TEST_CASE( indices_expr1)
{
  typedef double T; 
  nt2::table<T> t(nt2::of_size(1, 2) );
  t(1) = 8;
  t(2) = 4;

  nt2::table<T> x2 = nt2::indices(t, 1);
  for(int i=1;i<=8;++i)
    for(int j=1;j<=4;++j)
      NT2_TEST_EQUAL( i, x2(i, j) );
  
  nt2::table<T> x22 = nt2::indices(t, 2);
  for(int i=1;i<=8;++i)
    for(int j=1;j<=4;++j)
      NT2_TEST_EQUAL( j, x22(i, j) );

  nt2::table<T> x23 = nt2::indices(t, 3);
  for(int i=1;i<=8;++i)
    for(int j=1;j<=4;++j)
      NT2_TEST_EQUAL( 1, x23(i, j));
  {
    nt2::table<T> t(nt2::of_size(1, 3) );
    t(1) = 3;
    t(2) = 4;
    t(3) = 2;
    
    nt2::table<T> x2 = nt2::indices(t, 1);
    for(int i=1;i<=3;++i)
      for(int j=1;j<=4;++j)
        for(int k = 1; k <= 2; ++k)
          NT2_TEST_EQUAL( i, x2(i, j, k) );
    
    nt2::table<T> x22 = nt2::indices(t, 2);
    for(int i=1;i<=3;++i)
      for(int j=1;j<=4;++j)
        for(int k = 1; k <= 2; ++k)
        NT2_TEST_EQUAL( j, x22(i, j, k) );
    
    nt2::table<T> x23 = nt2::indices(t, 3);
    for(int i=1;i<=3;++i)
      for(int j=1;j<=4;++j)
         for(int k = 1; k <= 2; ++k)
           NT2_TEST_EQUAL( k, x23(i, j, k));
  }

}

NT2_TEST_CASE( indices_Nd)
{
  typedef float T; 

  nt2::table<T> x1 = nt2::indices( nt2::of_size(3, 4, 2), 1, nt2::meta::as_<T>() );
  NT2_DISPLAY(x1); 
  for(int i=1;i<=3;++i)
    for(int j=1;j<=4;++j)
      for(int k=1;k<=2;++k)
      NT2_TEST_EQUAL( T(i), T(x1(i, j, k)));

  nt2::table<T> x2 = nt2::indices( nt2::of_size(3, 4, 2), 2, nt2::meta::as_<T>() );
  NT2_DISPLAY(x1); 
  for(int i=1;i<=3;++i)
    for(int j=1;j<=4;++j)
      for(int k=1;k<=2;++k)
      NT2_TEST_EQUAL( T(j), T(x2(i, j, k)));

  nt2::table<T> x3 = nt2::indices( nt2::of_size(3, 4, 2), 3, nt2::meta::as_<T>() );
  NT2_DISPLAY(x1); 
  for(int i=1;i<=3;++i)
    for(int j=1;j<=4;++j)
      for(int k=1;k<=2;++k)
      NT2_TEST_EQUAL( T(k), T(x3(i, j, k)));

}
