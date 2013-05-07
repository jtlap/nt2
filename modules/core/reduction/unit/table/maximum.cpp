//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2::maximum function"

#include <nt2/table.hpp>
#include <nt2/include/functions/toint.hpp>
#include <nt2/include/functions/of_size.hpp>
#include <nt2/include/functions/maximum.hpp>
#include <nt2/include/functions/max.hpp>
#include <nt2/include/functions/isequal.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>

NT2_TEST_CASE_TPL( maximum_scalar, (float)(double))//NT2_TYPES )
{
  T x = nt2::maximum(T(42));
  NT2_TEST_EQUAL( x, (T(42)) );

  x = nt2::maximum(T(42),1);
  NT2_TEST_EQUAL( x, T(42) );

  x = nt2::maximum(T(42),2);
  NT2_TEST_EQUAL( x, (T(42)) );

}

NT2_TEST_CASE_TPL( maximum_expr, (float)(double) )
{
  using nt2::_;
  nt2::table<T> y( nt2::of_size(5,3) );
  nt2::table<T> sy( nt2::of_size(1,3) );
  for(int j=1;j<=3;j++)
    for(int i=1;i<=5;i++)
      y(i,j) = i + 10*j;
  display("y", y);
  sy = nt2::maximum(y);
  sy = nt2::max(y);
  sy = nt2::max(y, _(), 1);
  for(int j=1;j<=3;j++)
    for(int i=1;i<=5;i++)
      NT2_TEST_LESSER_EQUAL(y(i, j), sy(j));

  display("sy", sy);
  sy = nt2::maximum(y, 1);
  for(int j=1;j<=3;j++)
    for(int i=1;i<=5;i++)
      NT2_TEST_LESSER_EQUAL(y(i, j), sy(j));
  display("sy", sy);
  sy = nt2::maximum(y, 2);
  for(int j=1;j<=3;j++)
    for(int i=1;i<=5;i++)
      NT2_TEST_LESSER_EQUAL(y(i, j), sy(i));
  display("sy", sy);
  sy = nt2::maximum(y, 3);
  for(int j=1;j<=3;j++)
    for(int i=1;i<=5;i++)
      NT2_TEST_LESSER_EQUAL(y(i, j), sy(i, j));
  display("sy", sy);
  sy = nt2::maximum(y(_));
  display(sy);
  NT2_TEST_EQUAL(sy(1), 35);
}

NT2_TEST_CASE_TPL( maximum_2, (float)(double) )
{
  using nt2::_;
  nt2::table<T> y( nt2::of_size(5,3) );
  nt2::table<T> sy( nt2::of_size(1,3) );
  for(int j=1;j<=3;j++)
    for(int i=1;i<=5;i++)
      y(i,j) = i + 10*j;
  display("y", y);
  sy = nt2::maximum(y);
  NT2_TEST(nt2::isequal(sy,  nt2::maximum(y)));
  sy = nt2::maximum(y, 1);
  NT2_TEST(nt2::isequal(sy,  nt2::maximum(y, 1)));
  sy = nt2::maximum(y, 2);
  NT2_TEST(nt2::isequal(sy,  nt2::maximum(y, 2)));
  sy = nt2::maximum(y, 3);
  NT2_TEST(nt2::isequal(sy,  nt2::maximum(y, 3)));

}
