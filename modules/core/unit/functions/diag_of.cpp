/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::diag_of function"

#include <nt2/table.hpp>
#include <nt2/include/functions/length.hpp>
#include <nt2/include/functions/diag_of.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

NT2_TEST_CASE_TPL( diag_of, NT2_TYPES )
{
  nt2::table<T> x,y( nt2::of_size(4,5) );

  for(int j=1;j<=5;j++)
    for(int i=1;i<=4;i++)
      y(i,j) = i + 10*j;

  x = nt2::diag_of(y);

  for(int i=1;i<=nt2::length(x);i++)
    NT2_TEST_EQUAL( x(i), y(i,i) );
}

NT2_TEST_CASE_TPL( diag_of_scalar, NT2_TYPES )
{
  T x,y = 42;
  x = nt2::diag_of(y);
  NT2_TEST_EQUAL(x, y);
}

NT2_TEST_CASE_TPL( diag_of_expr, NT2_TYPES )
{
  nt2::table<T> x,y( nt2::of_size(7,7) );

  for(int j=1;j<=7;j++)
    for(int i=1;i<=7;i++)
      y(i,j) = i + 10*j;

  x = nt2::diag_of(y+y-T(1));

  for(int i=1;i<=nt2::length(x);i++)
    NT2_TEST_EQUAL( x(i), (y+y-T(1))(i,i) );
}

