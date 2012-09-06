/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::nanasum2 function"

#include <nt2/table.hpp>
#include <nt2/include/functions/nanasum2.hpp>
#include <nt2/include/functions/sum.hpp>
#include <nt2/include/functions/size.hpp>
#include <nt2/include/functions/firstnonsingleton.hpp>
#include <nt2/include/functions/is_nan.hpp>
#include <nt2/include/functions/if_zero_else.hpp>
#include <nt2/include/functions/sqr_abs.hpp>
#include <nt2/include/functions/isequal.hpp>
#include <nt2/include/constants/nan.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>

NT2_TEST_CASE_TPL( nanasum2_scalar, NT2_REAL_TYPES )
{
  T x = nt2::nanasum2(T(42));
  NT2_TEST_EQUAL( x, T(1764) );

  x = nt2::nanasum2(T(42),1);
  NT2_TEST_EQUAL( x, T(1764) );

  x = nt2::nanasum2(T(42),0);
  NT2_TEST_EQUAL( x, T(1764) );

  x = nt2::nanasum2(T(nt2::Nan<T>()),0);
  NT2_TEST_EQUAL( x, nt2::Zero<T>() );
}

NT2_TEST_CASE_TPL( nanasum2, NT2_REAL_TYPES )
{
  nt2::table<T> y( nt2::of_size(5,3) );
  nt2::table<T> sy;
  nt2::table<T> sy2;


  for(int j=1;j<=3;j++)
    for(int i=1;i<=5;i++)
      y(i,j) = i + 10*j;
  y(2, 3) = nt2::Nan<T>();
  display("y", y);
  sy = nt2::sum(nt2::if_zero_else(nt2::is_nan(y), nt2::sqr_abs(y)));
  sy2 = nt2::nanasum2(y);
  display("sy", sy);
  display("sy2", sy2);
  for(size_t j=1;j<=size(sy, 2);j++)
    for(size_t i=1;i<=size(sy, 1);i++)
      NT2_TEST_EQUAL(sy(i,j), sy2(i, j));

  sy = nt2::sum(nt2::if_zero_else(nt2::is_nan(y), nt2::sqr_abs(y)), 1);
  sy2 = nt2::nanasum2(y, 1);
  display("sy", sy);
  display("sy2", sy2);
  for(size_t j=1;j<=size(sy, 2);j++)
    for(size_t i=1;i<=size(sy, 1);i++)
      NT2_TEST_EQUAL(sy(i,j), sy2(i, j));

  sy = nt2::sum(nt2::if_zero_else(nt2::is_nan(y), nt2::sqr_abs(y)), 2);
  sy2 = nt2::nanasum2(y, 2);
  display("sy", sy);
  display("sy2", sy2);
  for(size_t j=1;j<=size(sy, 2);j++)
    for(size_t i=1;i<=size(sy, 1);i++)
      NT2_TEST_EQUAL(sy(i,j), sy2(i, j));

  sy = nt2::sum(nt2::if_zero_else(nt2::is_nan(y), nt2::sqr_abs(y)), 3);
  sy2 = nt2::nanasum2(y, 3);
  display("sy", sy);
  display("sy2", sy2);
  for(size_t j=1;j<=size(sy, 2);j++)
    for(size_t i=1;i<=size(sy, 1);i++)
      NT2_TEST_EQUAL(sy(i,j), sy2(i, j));


}

NT2_TEST_CASE_TPL( nanasum2_2, NT2_REAL_TYPES )
{
  nt2::table<T> y( nt2::of_size(5,3) );
  nt2::table<T> sy;
  nt2::table<T> sy2;


  for(int j=1;j<=3;j++)
    for(int i=1;i<=5;i++)
      y(i,j) = i + 10*j;
  y(2, 3) = nt2::Nan<T>();
  display("y", y);
  sy2 = nt2::nanasum2(y);
  NT2_TEST(nt2::isequal(sy2, nt2::nanasum2(y))); 
  sy2 = nt2::nanasum2(y, 1);
  NT2_TEST(nt2::isequal(sy2, nt2::nanasum2(y, 1))); 
  sy2 = nt2::nanasum2(y, 2);
  NT2_TEST(nt2::isequal(sy2, nt2::nanasum2(y, 2))); 
  sy2 = nt2::nanasum2(y, 3);
  NT2_TEST(nt2::isequal(sy2, nt2::nanasum2(y, 3))); 

}
