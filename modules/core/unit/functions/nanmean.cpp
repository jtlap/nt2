/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::nanmean function"

#include <nt2/table.hpp>
#include <nt2/include/functions/nanmean.hpp>
#include <nt2/include/functions/sum.hpp>
#include <nt2/include/functions/size.hpp>
#include <nt2/include/functions/firstnonsingleton.hpp>
#include <nt2/include/functions/nansum.hpp>
#include <nt2/include/functions/nbtrue.hpp>
#include <nt2/include/functions/rec.hpp>
#include <nt2/include/functions/is_nan.hpp>
#include <nt2/include/functions/isequal.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>

NT2_TEST_CASE_TPL( nanmean_scalar, (float)(double))//NT2_TYPES )
{
  T x = nt2::nanmean(T(42));
  NT2_TEST_EQUAL( x, T(42) );

  x = nt2::nanmean(T(42),1);
  NT2_TEST_EQUAL( x, T(42) );

  x = nt2::nanmean(T(42),0);
  NT2_TEST_EQUAL( x, T(42) );


  x = nt2::nanmean(T(nt2::Nan<T>()),0);
  NT2_TEST_EQUAL( x, nt2::Nan<T>() );
}

NT2_TEST_CASE_TPL( nanmean, (float)(double))//NT2_TYPES )
{
  nt2::table<T> y( nt2::of_size(5,3) );
  nt2::table<T> sy;
  nt2::table<T> sy2;
  
  for(size_t j=1;j<=3;j++)
    for(size_t i=1;i<=5;i++)
      y(i,j) = i + 10*j;
  y(2, 3) = nt2::Nan<T> ();
  display("y", y);
  nt2::table<T> y1 = y;
  y1(2, 3) =  nt2::Zero<T> ();
  sy = nt2::nansum(y)*nt2::rec(nt2::nbtrue(y1));
  sy2 = nt2::nanmean(y);
  NT2_TEST(nt2::isequal(sy, sy2));
  NT2_TEST(nt2::isequal(sy2, nt2::nanmean(y))); 
  sy2 = nt2::nanmean(y, 1);
  NT2_TEST(nt2::isequal(sy2, nt2::nanmean(y, 1))); 
  sy2 = nt2::nanmean(y, 2);
  NT2_TEST(nt2::isequal(sy2, nt2::nanmean(y, 2))); 
  sy2 = nt2::nanmean(y, 3);
  NT2_TEST(nt2::isequal(sy2, nt2::nanmean(y, 3))); 
}

