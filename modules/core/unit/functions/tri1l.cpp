/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::tri1l function"

#include <nt2/table.hpp>
#include <nt2/include/functions/tri1l.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

NT2_TEST_CASE_TPL( tri1l_scalar, NT2_TYPES )
{
  T x = nt2::tri1l(T(42));
  NT2_TEST_EQUAL( x, T(1) );

  x = nt2::tri1l(T(42),1);
  NT2_TEST_EQUAL( x, T(42) );

  x = nt2::tri1l(T(42),0);
  NT2_TEST_EQUAL( x, T(1) );

  x = nt2::tri1l(T(42),-1);
  NT2_TEST_EQUAL( x, T(0) );
}

NT2_TEST_CASE_TPL( tri1l_scalar_table, NT2_TYPES )
{
  nt2::table<T> tx,ty( nt2::of_size(1, 1) );
  ty(1) = T(42);
  tx= nt2::tri1l(ty);
  NT2_TEST_EQUAL( tx(1), T(1) );

  tx= nt2::tri1l(ty, 1);
  NT2_TEST_EQUAL( tx(1), T(42) );

  tx= nt2::tri1l(ty, 0);
  NT2_TEST_EQUAL( tx(1), T(1) );

  tx= nt2::tri1l(ty, -1);
  NT2_TEST_EQUAL( tx(1), T(0) );
}

NT2_TEST_CASE_TPL( tri1l, NT2_TYPES )
{
  nt2::table<T> x,y( nt2::of_size(5,3) );

  for(int j=1;j<=3;j++)
    for(int i=1;i<=5;i++)
      y(i,j) = i + 10*j;

  x = nt2::tri1l(y);

  for(int j=1;j<=3;j++)
    for(int i=1;i<=5;i++)
      NT2_TEST_EQUAL( x(i,j), (i == j) ? T(1) : (i>=j) ? y(i,j) : T(0));
}

NT2_TEST_CASE_TPL( offset_tri1l, NT2_TYPES )
{
  nt2::table<T> x,y( nt2::of_size(5,3) );

  for(int j=1;j<=3;j++)
    for(int i=1;i<=5;i++)
      y(i,j) = i + 10*j;

  x = nt2::tri1l(y,1);

  for(int j=1;j<=3;j++)
    for(int i=1;i<=5;i++)
      NT2_TEST_EQUAL( x(i,j), (i+1 == j) ? T(1) : (i+1>j) ? y(i,j) : T(0));

  x = nt2::tri1l(y,-1);

  for(int j=1;j<=3;j++)
    for(int i=1;i<=5;i++)
      NT2_TEST_EQUAL( x(i,j), (i-1 == j) ? T(1) : (i-1>j) ? y(i,j) : T(0));
}
