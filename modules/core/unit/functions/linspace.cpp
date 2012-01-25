/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::linspace function"

#include <nt2/table.hpp>
#include <nt2/include/functions/size.hpp>
#include <nt2/include/functions/linspace.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests.hpp>

NT2_TEST_CASE_TPL( linspace, (double)(float) )
{
  typedef T r_t;
  double ulpd;

  nt2::table<T> xd = nt2::linspace(T(0),T(1));

  NT2_TEST( xd.extent() == nt2::of_size(1,100) );

  for(int i=1;i<=100;++i)
    NT2_TEST_ULP_EQUAL( T(xd(i)), 0. + (T(1)/99)*(i-1), 0.5 );

  nt2::table<T> xr = nt2::linspace(T(1),T(0));

  NT2_TEST( xr.extent() == nt2::of_size(1,100) );

  for(int i=1;i<=100;++i)
    NT2_TEST_ULP_EQUAL( T(xr(i)), 1. + ((T(0)-T(1))/99)*(i-1),0.5 );
}

NT2_TEST_CASE_TPL( linspace_with_size, (double)(float) )
{
  typedef T r_t;
  double ulpd;

  nt2::table<T> xd = nt2::linspace(T(0),T(1),7);

  NT2_TEST( xd.extent() == nt2::of_size(1,7) );

  for(int i=1;i<=7;++i)
    NT2_TEST_ULP_EQUAL( T(xd(i)), 0. + (T(1)/6)*(i-1),0.5 );

  nt2::table<T> xr = nt2::linspace(T(1),T(0),5);

  NT2_TEST( xr.extent() == nt2::of_size(1,5) );

  for(int i=1;i<=5;++i)
    NT2_TEST_ULP_EQUAL( T(xr(i)), 1. + ((T(0)-T(1))/4)*(i-1),0.5 );
}
