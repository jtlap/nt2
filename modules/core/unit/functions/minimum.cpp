/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::minimum function"

#include <nt2/table.hpp>
#include <nt2/include/functions/min.hpp>
#include <nt2/include/functions/of_size.hpp>
#include <nt2/include/functions/minimum.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>

NT2_TEST_CASE_TPL( minimum_scalar, NT2_TYPES )
{
  T x = nt2::minimum(T(42));
  NT2_TEST_EQUAL( x, (T(42)) );

  x = nt2::minimum(T(42),1);
  NT2_TEST_EQUAL( x, T(42) );

  x = nt2::minimum(T(42),2);
  NT2_TEST_EQUAL( x, (T(42)) );
}

NT2_TEST_CASE_TPL( minimum_expr, NT2_TYPES )
{
  using nt2::_;
  nt2::table<T> y( nt2::of_size(5,3) );
  nt2::table<T> sy( nt2::of_size(1,3) );
  for(int j=1;j<=3;j++)
    for(int i=1;i<=5;i++)
      y(i,j) = i + 10*j;
  display("y", y);
  sy = nt2::minimum(y);
  // sy = nt2::min(y);
  sy = nt2::min(y, _(), 1);

  for(int j=1;j<=3;j++)
    for(int i=1;i<=5;i++)
      NT2_TEST_GREATER_EQUAL(y(i, j), sy(j));

  display("sy", sy);
  sy = nt2::minimum(y, 1);
  for(int j=1;j<=3;j++)
    for(int i=1;i<=5;i++)
      NT2_TEST_GREATER_EQUAL(y(i, j), sy(j));
  display("sy", sy);
  sy = nt2::minimum(y, 2);
  for(int j=1;j<=3;j++)
    for(int i=1;i<=5;i++)
      NT2_TEST_GREATER_EQUAL(y(i, j), sy(i));
  display("sy", sy);
  sy = nt2::minimum(y, 3);
  for(int j=1;j<=3;j++)
    for(int i=1;i<=5;i++)
      NT2_TEST_GREATER_EQUAL(y(i, j), sy(i, j));
  sy = minimum(y(_));
  display("sy", sy);
  NT2_TEST_EQUAL(sy(1), 11);
}

