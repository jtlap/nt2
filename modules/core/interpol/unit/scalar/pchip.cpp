//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/table.hpp>
#include <nt2/include/functions/pchip.hpp>
#include <nt2/include/functions/linspace.hpp>
#include <nt2/include/functions/sqr.hpp>
#include <boost/core/ignore_unused.hpp>

#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>

NT2_TEST_CASE_TPL( pchip, NT2_REAL_TYPES)
{
  using nt2::_;
  nt2::table<T> x =  nt2::linspace(T(1),  T(4), 4);
  nt2::table<T> y =  nt2::sqr(nt2::linspace(T(2),  T(8), 4));
  nt2::table<T> xi=  nt2::linspace(T(1),  T(4), 7);
  T tr0[] = { T(4.) , T(9.1250), T(16.), T(24.95833333333333333)
            , T(36.), T(48.9166666666666666), T(64.)
            };

  nt2::table<T> r0(nt2::of_size(1, 7), &tr0[0], &tr0[7]);

  nt2::table<T> yi;

  yi =nt2::pchip(x, y, xi);
  NT2_TEST_ULP_EQUAL(yi, r0, 10.0);

  yi =nt2::pchip(x, y, xi, false);
  NT2_TEST_ULP_EQUAL(yi, r0, 10.0);

  yi =nt2::pchip(x, y, xi, true);
  NT2_TEST_ULP_EQUAL(yi, r0, 10.0);

  T z =  33;
  yi =nt2::pchip(x, y, xi, z);
  NT2_TEST_ULP_EQUAL(yi, r0, 10.0);

  yi =nt2::pchip(x, y, xi, T(33));
  NT2_TEST_ULP_EQUAL(yi, r0, 10.0);
}

NT2_TEST_CASE_TPL( pchip2, NT2_REAL_TYPES )
{
  using nt2::_;
  nt2::table<T> x =  nt2::linspace(T(1),  T(4), 4);
  nt2::table<T> y =  nt2::linspace(T(2),  T(8), 4);
  nt2::table<T> xi=  nt2::linspace(T(1),  T(4), 11);
  NT2_DISPLAY(x);
  NT2_DISPLAY(y);
  NT2_DISPLAY(xi);
  nt2::table<T> y0 =nt2::pchip(x, y, xi), yi;
  std::cout << "extrap " <<  false <<  " extrapval " << "-" << std::endl;
  NT2_DISPLAY(y0);
  y0 =nt2::pchip(x, y, xi, false);
  std::cout << "extrap " <<  false <<  " extrapval " << "-" << std::endl;
  NT2_DISPLAY(yi);
  std::cout << "extrap " <<  true <<  " extrapval " << "-" << std::endl;
  yi =nt2::pchip(x, y, xi, true);
  NT2_TEST_EQUAL(y0, yi);
  NT2_DISPLAY(yi);
  T z =  33;
  std::cout << "extrap " <<  "-" <<  " extrapval " << "33" << std::endl;
  yi =nt2::pchip(x, y, xi, z);
  NT2_DISPLAY(yi);
  NT2_TEST_EQUAL(y0, yi);
  std::cout << "extrap " <<  "-" <<  " extrapval " << "33" << std::endl;
  yi =nt2::pchip(x, y, xi, T(33));
  NT2_DISPLAY(yi);
  NT2_TEST_EQUAL(y0, yi);
}

NT2_TEST_CASE_TPL( pchip3, NT2_REAL_TYPES )
{
  using nt2::_;
  T x = 3;
  T y = 2;
  nt2::table<T> xi=  nt2::linspace(T(1),  T(4), 4);
  NT2_DISPLAY(x);
  NT2_DISPLAY(y);
  NT2_DISPLAY(xi);
  nt2::table<T> y0;
  boost::ignore_unused(y0);
  NT2_TEST_ASSERT(y0=nt2::pchip(x, y, xi));
  NT2_TEST_ASSERT(y0=nt2::pchip(T(3), y, xi));
  NT2_TEST_ASSERT(y0=nt2::pchip(T(3), y, xi, T(32)));
  NT2_TEST_ASSERT(y0=nt2::pchip(T(3), y, xi, true));
  NT2_TEST_ASSERT(T(nt2::pchip(x, y, T(25), true)));
  NT2_TEST_ASSERT(T(nt2::pchip(x, y, T(25), false)));
  NT2_TEST_ASSERT(T(nt2::pchip(x, y, T(25), T(32))));
}
NT2_TEST_CASE_TPL( pchip4, NT2_REAL_TYPES )
{
  using nt2::_;
  nt2::table<T> x =  T(3);
  nt2::table<T> y =  T(2);
  nt2::table<T> xi=  nt2::linspace(T(1),  T(4),4);
  nt2::table<T> y0;
  boost::ignore_unused(y0);
  NT2_TEST_ASSERT(y0=nt2::pchip(x, y, xi));
  NT2_TEST_ASSERT(y0=nt2::pchip(x, y, xi, T(32)));
  NT2_TEST_ASSERT(y0=nt2::pchip(x, y, xi, true));

}

