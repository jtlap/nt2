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
#include <nt2/include/functions/linear.hpp>
#include <nt2/include/functions/linspace.hpp>
#include <nt2/include/functions/isequal.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>


NT2_TEST_CASE_TPL( linear, NT2_REAL_TYPES )
{
  using nt2::_;
  nt2::table<T> x =  nt2::linspace(T(1),  T(4), 4);
  nt2::table<T> y =  nt2::linspace(T(2),  T(8), 4);
  nt2::table<T> xi=  nt2::linspace(T(0),  T(5), 11);
  nt2::table<T> r0 = _(T(0), T(10));
  T nan =  nt2::Nan<T>();
  nt2::table<T> r1 = r0;  r1(_(1, 2)) = nan;  r1(_(10, 11)) = nan;
  nt2::table<T> r2 = r0;  r2(_(1, 2)) = T(33);r2(_(10, 11)) = T(33);
  NT2_DISPLAY(x);
  NT2_DISPLAY(y);
  NT2_DISPLAY(xi);
  nt2::table<T> yi =nt2::linear(x, y, xi);
  std::cout << "extrap " <<  false <<  " extrapval " << "-" << std::endl;
  NT2_DISPLAY(yi);
  NT2_TEST_EQUAL(yi, r1);
  yi =nt2::linear(x, y, xi, false);
  std::cout << "extrap " <<  false <<  " extrapval " << "-" << std::endl;
  NT2_DISPLAY(yi);
  NT2_TEST_EQUAL(yi, r1);
  std::cout << "extrap " <<  true <<  " extrapval " << "-" << std::endl;
  yi =nt2::linear(x, y, xi, true);
  NT2_DISPLAY(yi);
  T z =  33;
  std::cout << "extrap " <<  "-" <<  " extrapval " << "33" << std::endl;
  yi =nt2::linear(x, y, xi, z);
  NT2_TEST_EQUAL(yi, r2);
  NT2_DISPLAY(yi);
  std::cout << "extrap " <<  "-" <<  " extrapval " << "33" << std::endl;
  yi =nt2::linear(x, y, xi, T(33));
  NT2_TEST_EQUAL(yi, r2);
  NT2_DISPLAY(yi);
}

NT2_TEST_CASE_TPL( linear2, NT2_REAL_TYPES )
{
  using nt2::_;
  nt2::table<T> x =  nt2::linspace(T(1),  T(4), 4);
  nt2::table<T> y =  nt2::linspace(T(2),  T(8), 4);
  nt2::table<T> xi=  nt2::linspace(T(1),  T(4), 11);
  NT2_DISPLAY(x);
  NT2_DISPLAY(y);
  NT2_DISPLAY(xi);
  nt2::table<T> y0 =nt2::linear(x, y, xi), yi;
  std::cout << "extrap " <<  false <<  " extrapval " << "-" << std::endl;
  NT2_DISPLAY(y0);
  y0 =nt2::linear(x, y, xi, false);
  std::cout << "extrap " <<  false <<  " extrapval " << "-" << std::endl;
  NT2_DISPLAY(yi);
  std::cout << "extrap " <<  true <<  " extrapval " << "-" << std::endl;
  yi =nt2::linear(x, y, xi, true);
  NT2_TEST_EQUAL(y0, yi);
  NT2_DISPLAY(yi);
  T z =  33;
  std::cout << "extrap " <<  "-" <<  " extrapval " << "33" << std::endl;
  yi =nt2::linear(x, y, xi, z);
  NT2_DISPLAY(yi);
  NT2_TEST_EQUAL(y0, yi);
  std::cout << "extrap " <<  "-" <<  " extrapval " << "33" << std::endl;
  yi =nt2::linear(x, y, xi, T(33));
  NT2_DISPLAY(yi);
  NT2_TEST_EQUAL(y0, yi);
}
