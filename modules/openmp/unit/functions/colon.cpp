/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::colon function"

#include <nt2/table.hpp>
#include <nt2/include/functions/size.hpp>
#include <nt2/core/container/colon/colon.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests.hpp>

NT2_TEST_CASE_TPL( colon, NT2_TYPES )
{
  using nt2::_;

  nt2::table<T> xd = _(T(0),T(9));

  NT2_TEST( xd.extent() == nt2::of_size(1,10) );

  for(int i=1;i<=10;++i)
    NT2_TEST_EQUAL( T(xd(i)), T(0) + T(i-1) );

  nt2::table<T> xr = _(T(9),T(0));
  NT2_TEST( xr.extent() == nt2::of_size(1,0) );
}

NT2_TEST_CASE_TPL( colon_integers_step, NT2_INTEGRAL_SIGNED_TYPES )
{
  using nt2::_;

  nt2::table<T> xd = _(T(0),T(2),T(9));

  NT2_TEST( xd.extent() == nt2::of_size(1,5) );

  for(int i=1;i<=5;++i)
    NT2_TEST_EQUAL( T(xd(i)), T(0) + T(2)*T(i-1) );

  nt2::table<T> yd = _(T(9),T(-2),T(1));

  NT2_TEST( yd.extent() == nt2::of_size(1,5) );

  for(int i=1;i<=5;++i)
    NT2_TEST_EQUAL( T(yd(i)), T(9) + T(-2)*T(i-1) );
}

NT2_TEST_CASE_TPL( colon_unsigned_step, NT2_UNSIGNED_TYPES )
{
  using nt2::_;

  nt2::table<T> xd = _(T(0),T(2),T(9));

  NT2_TEST( xd.extent() == nt2::of_size(1,5) );

  for(int i=1;i<=5;++i)
    NT2_TEST_EQUAL( T(xd(i)), T(0) + T(2)*T(i-1) );

  nt2::table<T> yd = _(T(9),T(2),T(1));

  NT2_TEST( yd.extent() == nt2::of_size(1,0) );

  nt2::table<T> zd = _(T(0),T(0),T(9));

  NT2_TEST( zd.extent() == nt2::of_size(1,9) );

  for(int i=1;i<=9;++i)
    NT2_TEST_EQUAL( T(zd(i)), T(0) );

}

NT2_TEST_CASE_TPL( colon_real_step, NT2_REAL_TYPES )
{
  using nt2::_;

  typedef T r_t;
  double ulpd;

  nt2::table<T> xd = _(T(0),T(0.3),T(1));

  NT2_TEST( xd.extent() == nt2::of_size(1,4) );

  for(int i=1;i<=4;++i)
    NT2_TEST_ULP_EQUAL( T(xd(i)), T(0) + T(0.3)*T(i-1), 0.5 );

  nt2::table<T> yd = _(T(1),T(-0.3),T(0));

  NT2_TEST( yd.extent() == nt2::of_size(1,4) );

  for(int i=1;i<=4;++i)
    NT2_TEST_ULP_EQUAL( T(yd(i)), T(1) + T(-0.3)*T(i-1), 0.5 );

  nt2::table<T> zd = _(T(0.5),T(0),T(6));

  NT2_TEST( zd.extent() == nt2::of_size(1,6) );

  for(int i=1;i<=6;++i)
    NT2_TEST_ULP_EQUAL( T(zd(i)), T(0.5), 0.5 );
}
