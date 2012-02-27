/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::zeros function"

#include <nt2/table.hpp>
#include <nt2/include/functions/size.hpp>
#include <nt2/include/functions/zeros.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

NT2_TEST_CASE( zeros_untyped )
{
  nt2::table<double> x1 = nt2::zeros(64);
  for(int i=1;i<=64;++i) NT2_TEST_EQUAL( double(0), double(x1(i)) );

  nt2::table<double> x2 = nt2::zeros(8,8);
  for(int i=1;i<=64;++i) NT2_TEST_EQUAL( double(0), double(x2(i)) );

  nt2::table<double> x3 = nt2::zeros(8,4,2);
  for(int i=1;i<=64;++i) NT2_TEST_EQUAL( double(0), double(x3(i)) );

  nt2::table<double> x4 = nt2::zeros(4,4,2,2);
  for(int i=1;i<=64;++i) NT2_TEST_EQUAL( double(0), double(x4(i)) );
}

NT2_TEST_CASE( zeros_of_size )
{
/*
  nt2::table<double> x1 = nt2::zeros( nt2::of_size(64) );
  for(int i=1;i<=64;++i) NT2_TEST_EQUAL( double(0), double(x1(i)) );
*/
  nt2::table<double> x2 = nt2::zeros(nt2::of_size(8,8) );
  for(int i=1;i<=64;++i) NT2_TEST_EQUAL( double(0), double(x2(i)) );

  nt2::table<double> x3 = nt2::zeros(nt2::of_size(8,4,2) );
  for(int i=1;i<=64;++i) NT2_TEST_EQUAL( double(0), double(x3(i)) );

  nt2::table<double> x4 = nt2::zeros(nt2::of_size(4,4,2,2) );
  for(int i=1;i<=64;++i) NT2_TEST_EQUAL( double(0), double(x4(i)) );
}

NT2_TEST_CASE( zeros_expr )
{
  nt2::table<int> a( nt2::of_size(4,5) );

  nt2::table<double> x1 = nt2::zeros( nt2::size(a) );
  for(int i=1;i<=20;++i) NT2_TEST_EQUAL( double(0), double(x1(i)) );
}

NT2_TEST_CASE_TPL( zeros_typed_of_size, (float)(nt2::int32_t)(nt2::uint16_t) )
{
/*
  nt2::table<T> x1 = nt2::zeros( nt2::of_size(64), nt2::meta::as_<T>() );
  for(int i=1;i<=64;++i) NT2_TEST_EQUAL( T(0), T(x1(i)) );
*/
  nt2::table<T> x2 = nt2::zeros(nt2::of_size(8,8), nt2::meta::as_<T>() );
  for(int i=1;i<=64;++i) NT2_TEST_EQUAL( T(0), T(x2(i)) );

  nt2::table<T> x3 = nt2::zeros(nt2::of_size(8,4,2), nt2::meta::as_<T>() );
  for(int i=1;i<=64;++i) NT2_TEST_EQUAL( T(0), T(x3(i)) );

  nt2::table<T> x4 = nt2::zeros(nt2::of_size(4,4,2,2), nt2::meta::as_<T>() );
  for(int i=1;i<=64;++i) NT2_TEST_EQUAL( T(0), T(x4(i)) );
} 

NT2_TEST_CASE_TPL( zeros_typed_expr, (float)(nt2::int32_t)(nt2::uint16_t) )
{
  nt2::table<int> a( nt2::of_size(4,5) );

  nt2::table<T> x1 = nt2::zeros( nt2::size(a), nt2::meta::as_<T>() );
  for(int i=1;i<=20;++i) NT2_TEST_EQUAL( T(0), T(x1(i)) );
}

NT2_TEST_CASE_TPL( zeros_nd_typed, (float)(nt2::int32_t)(nt2::uint16_t) )
{
  nt2::table<T> x1 = nt2::zeros(64, nt2::meta::as_<T>() );
  for(int i=1;i<=64;++i) NT2_TEST_EQUAL( T(0), T(x1(i)) );

  nt2::table<T> x2 = nt2::zeros(8,8, nt2::meta::as_<T>() );
  for(int i=1;i<=64;++i) NT2_TEST_EQUAL( T(0), T(x2(i)) );

  nt2::table<T> x3 = nt2::zeros(8,4,2, nt2::meta::as_<T>() );
  for(int i=1;i<=64;++i) NT2_TEST_EQUAL( T(0), T(x3(i)) );

  nt2::table<T> x4 = nt2::zeros(4,4,2,2, nt2::meta::as_<T>() );
  for(int i=1;i<=64;++i) NT2_TEST_EQUAL( T(0), T(x1(i)) );
}
