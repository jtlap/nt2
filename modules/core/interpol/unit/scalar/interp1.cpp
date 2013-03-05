//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2::sum1 function"

#include <nt2/table.hpp>
#include <nt2/include/functions/interp1.hpp>
#include <nt2/include/functions/linspace.hpp>
#include <nt2/include/functions/isequal.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>


NT2_TEST_CASE_TPL( interp1, (float)(double))//NT2_TYPES )
{
  using nt2::_;
  nt2::table<T> x =  nt2::linspace(T(1),  T(4), 4);
  nt2::table<T> y =  nt2::linspace(T(2),  T(8), 4);
  nt2::table<T> xi=  nt2::linspace(T(1),  T(4), 4);
  NT2_DISPLAY(x);
  NT2_DISPLAY(y);
  NT2_DISPLAY(xi);
  nt2::table<T> y0 =nt2::interp1(x, y, xi), yi;
  std::cout << "extrap " <<  false <<  " extrapval " << "-" << std::endl;
  NT2_DISPLAY(y0);
  yi =nt2::interp1(x, y, xi, 'l', false);
  NT2_TEST(isequal(y0, yi));
  std::cout << "extrap " <<  false <<  " extrapval " << "-" << std::endl;
  NT2_DISPLAY(yi);
  std::cout << "extrap " <<  true <<  " extrapval " << "-" << std::endl;
  yi =nt2::interp1(x, y, xi, 'l', true);
  NT2_TEST(isequal(y0, yi));
  NT2_DISPLAY(yi);
  T z =  33;
  std::cout << "extrap " <<  "-" <<  " extrapval " << "33" << std::endl;
  yi =nt2::interp1(x, y, xi, 'l', z);
  NT2_TEST(isequal(y0, yi));
  NT2_DISPLAY(yi);
  std::cout << "extrap " <<  "-" <<  " extrapval " << "33" << std::endl;
  yi =nt2::interp1(x, y, xi, 'l', T(33));
  NT2_DISPLAY(yi);
  yi =nt2::interp1(x, y, xi, 'n', false);
  NT2_TEST(isequal(y0, yi));
  std::cout << "extrap " <<  false <<  " extrapval " << "-" << std::endl;
  NT2_DISPLAY(yi);
  std::cout << "extrap " <<  true <<  " extrapval " << "-" << std::endl;
  yi =nt2::interp1(x, y, xi, 'n', true);
  NT2_TEST(isequal(y0, yi));
  NT2_DISPLAY(yi);
  std::cout << "extrap " <<  "-" <<  " extrapval " << "33" << std::endl;
  yi =nt2::interp1(x, y, xi, 'n', z);
  NT2_TEST(isequal(y0, yi));
  NT2_DISPLAY(yi);
  std::cout << "extrap " <<  "-" <<  " extrapval " << "33" << std::endl;
  yi =nt2::interp1(x, y, xi, 'n', T(33));
  NT2_TEST(isequal(y0, yi));
  NT2_DISPLAY(yi);



}

NT2_TEST_CASE_TPL( interp1_2, (float)(double))//NT2_TYPES )
{
  using nt2::_;
  nt2::table<T> x =  nt2::linspace(T(1),  T(4), 4);
  nt2::table<T> y =  nt2::linspace(T(2),  T(8), 4);
  nt2::table<T> xi=  nt2::linspace(T(0),  T(5), 11);
  nt2::table<T> r0 = _(T(0), T(10));
  T nan =  nt2::Nan<T>();
  nt2::table<T> r1 = r0;  r1(_(1, 2)) = nan;  r1(_(10, 11)) = nan;
  nt2::table<T> r2 = r0;  r2(_(1, 2)) = T(33);r2(_(10, 11)) = T(33);

  T tr0[] = {2 ,2 ,2 ,4 ,4 ,6 ,6 ,8 ,8 ,8 ,8};
  nt2::table<T> r0n(nt2::of_size(1, 11), &tr0[0], &tr0[11]);
  nt2::table<T> r1n = r0n;  r1n(_(1, 2)) = nan; r1n(_(10, 11)) = nan;
  nt2::table<T> r2n = r0n;  r2n(_(1, 2)) = T(33); r2n(_(10, 11))= T(33);

  NT2_DISPLAY(x);
  NT2_DISPLAY(y);
  NT2_DISPLAY(xi);
  nt2::table<T> yi =nt2::interp1(x, y, xi);
  std::cout << "extrap " <<  false <<  " extrapval " << "-" << std::endl;
  NT2_DISPLAY(yi);
  NT2_TEST_EQUAL(yi, r1n);
  yi =nt2::interp1(x, y, xi, 'l', false);
  std::cout << "extrap " <<  false <<  " extrapval " << "-" << std::endl;
  NT2_DISPLAY(yi);
  NT2_TEST_EQUAL(yi, r1);
  std::cout << "extrap " <<  true <<  " extrapval " << "-" << std::endl;
  yi =nt2::interp1(x, y, xi, 'l', true);
  NT2_DISPLAY(yi);
  NT2_TEST_EQUAL(yi, r0);
  T z =  33;
  std::cout << "extrap " <<  "-" <<  " extrapval " << "33" << std::endl;
  yi =nt2::interp1(x, y, xi, 'l', z);
  NT2_DISPLAY(yi);
  NT2_TEST_EQUAL(yi, r2);
  std::cout << "extrap " <<  "-" <<  " extrapval " << "33" << std::endl;
  yi =nt2::interp1(x, y, xi, 'l', T(33));
  NT2_DISPLAY(yi);
  NT2_TEST_EQUAL(yi, r2);
  yi =nt2::interp1(x, y, xi, 'n', false);
  std::cout << "extrap " <<  false <<  " extrapval " << "-" << std::endl;
  NT2_TEST_EQUAL(yi, r1n);
  NT2_DISPLAY(yi);
  std::cout << "extrap " <<  true <<  " extrapval " << "-" << std::endl;
  yi =nt2::interp1(x, y, xi, 'n', true);
  NT2_TEST_EQUAL(yi, r0n);
  NT2_DISPLAY(yi);
  std::cout << "extrap " <<  "-" <<  " extrapval " << "33" << std::endl;
  yi =nt2::interp1(x, y, xi, 'n', z);
  NT2_DISPLAY(yi);
  NT2_TEST_EQUAL(yi, r2n);
  std::cout << "extrap " <<  "-" <<  " extrapval " << "33" << std::endl;
  yi =nt2::interp1(x, y, xi, 'n', T(33));
  NT2_DISPLAY(yi);
  NT2_TEST_EQUAL(yi, r2n);



}
