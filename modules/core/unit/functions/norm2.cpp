/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::norm2 function"

#include <nt2/table.hpp>
#include <nt2/include/functions/norm2.hpp>
#include <nt2/include/functions/sum.hpp>
#include <nt2/include/functions/sqr_abs.hpp>
#include <nt2/include/functions/sqrt.hpp>
#include <nt2/include/functions/size.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

NT2_TEST_CASE_TPL( norm2_scalar, (float)(double))//NT2_TYPES )
{
  T x = nt2::norm2(T(42));
  NT2_TEST_EQUAL( x, nt2::abs(T(42)) );

  x = nt2::norm2(T(42),1);
  NT2_TEST_EQUAL( x, nt2::abs(T(42)) );

  x = nt2::norm2(T(42),0);
  NT2_TEST_EQUAL( x, nt2::abs(T(42)) );

}

NT2_TEST_CASE_TPL( norm2, (float)(double))//NT2_TYPES )
{
  using nt2::_;
  nt2::table<T> y( nt2::of_size(5,3) );
  nt2::table<T> sy( nt2::of_size(1,3) );
  nt2::table<T> sz( nt2::of_size(1,3) );


  for(size_t j=1;j<=size(y, 2);j++)
    for(size_t i=1;i<=size(y, 1);i++)
      y(i,j) = i - j;
  display("y", y);

  sy = nt2::norm2(y);
  sz = nt2::sqrt(nt2::sum(nt2::sqr_abs(y)));

  for(size_t j=1;j<=size(y, 2);j++)
      NT2_TEST_EQUAL(sz(j), sy(j));
  sy = nt2::norm2(y, 1);
  sz = nt2::sqrt(nt2::sum(nt2::sqr_abs(y), 1));

  for(size_t j=1;j<=size(y, 2);j++)
      NT2_TEST_EQUAL(sz(j), sy(j));
  sy =nt2::norm2(y, 2);
  sz = nt2::sqrt(nt2::sum(nt2::sqr_abs(y), 2));
  for(size_t i=1;i<=size(y, 1);i++)
    NT2_TEST_EQUAL(sz(i), sy(i));

  sy = nt2::norm2(y, 3);
  sz =nt2::sqrt( nt2::sum(nt2::sqr_abs(y), 3));
  for(size_t j=1;j<=size(y, 2);j++)
    for(size_t i=1;i<=size(y, 1);i++)
      NT2_TEST_EQUAL(sz(i, j), sy(i, j));

  sy = nt2::norm2(y(_));
  sz =nt2::sqrt( nt2::sum(nt2::sqr_abs(y(_))));
  NT2_TEST_EQUAL(sy(1), sz(1));
}

