/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::table resize checks"

#include <nt2/table.hpp>
#include <nt2/include/functions/extent.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

NT2_TEST_CASE( resize_bigger )
{
  using nt2::table;
  using nt2::of_size;

  table<float> x( of_size(1,2) );
  NT2_TEST( nt2::extent(x) == of_size(1,2) );

  x.resize( of_size(4,4) );
  NT2_TEST( nt2::extent(x) == of_size(4,4) );

  float u = 0;
  for(int j=1;j<=4;++j)
   for(int i=1;i<=4;++i)
    x(i,j) = u++;

  u = 0;
  for(int j=1;j<=4;++j)
   for(int i=1;i<=4;++i)
    NT2_TEST_EQUAL(float(x(i,j)), u++);
}

NT2_TEST_CASE( resize_smaller )
{
  using nt2::table;
  using nt2::of_size;

  table<float> x( of_size(3,3) );
  NT2_TEST( nt2::extent(x) == of_size(3,3) );

  x.resize( of_size(1,2) );

  NT2_TEST( nt2::extent(x) == of_size(1,2) );

  float u = 0;
  for(int j=1;j<=2;++j)
   for(int i=1;i<=1;++i)
    x(i,j) = u++;

  u = 0;
  for(int j=1;j<=2;++j)
   for(int i=1;i<=1;++i)
    NT2_TEST_EQUAL(float(x(i,j)), u++);
}

/*
NT2_TEST_CASE( resize_more_dims )
{
  using nt2::table;
  using nt2::of_size;

  table<float> x( of_size(3,3) );
  NT2_TEST( nt2::extent(x) == of_size(3,3) );

  x.resize( of_size(2,2,2) );
  NT2_TEST( nt2::extent(x) == of_size(2,2,2) );

  float u = 0;
  for(int k=1;k<=2;++k)
   for(int j=1;j<=2;++j)
    for(int i=1;i<=2;++i)
      x(i,j,k) = u++;

  u = 0;
  for(int k=1;k<=2;++k)
   for(int j=1;j<=2;++j)
    for(int i=1;i<=2;++i)
      NT2_TEST_EQUAL(float(x(i,j,k)), u++);
}

NT2_TEST_CASE( resize_less_dims )
{
  using nt2::table;
  using nt2::of_size;

  table<float> x( of_size(3,3,3) );
  NT2_TEST( nt2::extent(x) == of_size(3,3,3) );

  x.resize( of_size(9) );
  NT2_TEST( nt2::extent(x) == of_size(9) );

  float u = 0;
  for(int i=1;i<=9;++i)
    x(i) = u++;

  u = 0;
  for(int i=1;i<=9;++i)
    NT2_TEST_EQUAL(float(x(i)), u++);
}
*/
