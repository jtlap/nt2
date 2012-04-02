/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::tril function"

#include <nt2/table.hpp>
#include <nt2/include/functions/tril.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

NT2_TEST_CASE_TPL( tril_scalar, NT2_TYPES )
{
  T x = nt2::tril(T(42));
  NT2_TEST_EQUAL( x, T(42) );

  x = nt2::tril(T(42),1);
  NT2_TEST_EQUAL( x, T(42) );

  x = nt2::tril(T(42),0);
  NT2_TEST_EQUAL( x, T(42) );

  x = nt2::tril(T(42),-1);
  NT2_TEST_EQUAL( x, T(0) );
}

NT2_TEST_CASE_TPL( tril, NT2_TYPES )
{
  nt2::table<T> x,y( nt2::of_size(4,5) );

  for(int j=1;j<=5;j++)
    for(int i=1;i<=4;i++)
      y(i,j) = T(i + 10*j);

  x = nt2::tril(y);

  for(int j=1;j<=5;j++)
    for(int i=1;i<=4;i++)
      NT2_TEST_EQUAL( T(x(i,j)), (i>=j) ? T(y(i,j)) : T(0));
}

NT2_TEST_CASE_TPL( offset_tril, NT2_TYPES )
{
  nt2::table<T> x,y( nt2::of_size(4,5) );

  for(int j=1;j<=5;j++)
    for(int i=1;i<=4;i++)
      y(i,j) = T(i + 10*j);

  x = nt2::tril(y,1);

  for(int j=1;j<=5;j++)
    for(int i=1;i<=4;i++)
      NT2_TEST_EQUAL( T(x(i,j)), (i+1>=j) ? T(y(i,j)) : T(0));

  x = nt2::tril(y,-1);

  for(int j=1;j<=5;j++)
    for(int i=1;i<=4;i++)
      NT2_TEST_EQUAL( T(x(i,j)), (i-1>=j) ? T(y(i,j)) : T(0));
}
