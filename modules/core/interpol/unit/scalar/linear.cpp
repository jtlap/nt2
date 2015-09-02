//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/table.hpp>
#include <nt2/include/functions/linear.hpp>
#include <nt2/include/functions/linspace.hpp>
#include <nt2/include/functions/isequal.hpp>
#include <nt2/include/functions/colvect.hpp>
#include <nt2/include/functions/repmat.hpp>
#include <boost/core/ignore_unused.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>


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
  nt2::table<T> yi =nt2::linear(x, y, xi);
  NT2_TEST_EQUAL(yi, r1);
  yi =nt2::linear(x, y, xi, false);
  NT2_TEST_EQUAL(yi, r1);
  yi =nt2::linear(x, y, xi, true);
  T z =  33;
  yi =nt2::linear(x, y, xi, z);
  NT2_TEST_EQUAL(yi, r2);
  yi =nt2::linear(x, y, xi, T(33));
  NT2_TEST_EQUAL(yi, r2);
}

NT2_TEST_CASE_TPL( linear2, NT2_REAL_TYPES )
{
  using nt2::_;
  nt2::table<T> x =  nt2::linspace(T(1),  T(4), 4);
  nt2::table<T> y =  nt2::linspace(T(2),  T(8), 4);
  nt2::table<T> xi=  nt2::linspace(T(1),  T(4), 11);
  nt2::table<T> y0 =nt2::linear(x, y, xi), yi;
  y0 =nt2::linear(x, y, xi, false);
  yi =nt2::linear(x, y, xi, true);
  NT2_TEST_EQUAL(y0, yi);
  T z =  33;
  yi =nt2::linear(x, y, xi, z);
  NT2_TEST_EQUAL(y0, yi);
  yi =nt2::linear(x, y, xi, T(33));
  NT2_TEST_EQUAL(y0, yi);
}
NT2_TEST_CASE_TPL( linear3, NT2_REAL_TYPES )
{
  using nt2::_;
  T x = 3;
  T y = 2;
  nt2::table<T> xi=  nt2::linspace(T(1),  T(4), 4);
  nt2::table<T> y0;
  boost::ignore_unused(y0);
  NT2_TEST_ASSERT(y0=nt2::linear(x, y, xi));
  NT2_TEST_ASSERT(y0=nt2::linear(T(3), y, xi));
  NT2_TEST_ASSERT(y0=nt2::linear(T(3), y, xi, T(32)));
  NT2_TEST_ASSERT(y0=nt2::linear(T(3), y, xi, true));
  NT2_TEST_ASSERT(T(nt2::linear(x, y, T(25), true)));
  NT2_TEST_ASSERT(T(nt2::linear(x, y, T(25), false)));
  NT2_TEST_ASSERT(T(nt2::linear(x, y, T(25), T(32))));
}


NT2_TEST_CASE_TPL( linear4, NT2_REAL_TYPES )
{
  using nt2::_;
  nt2::table<T> x =  nt2::colvect(nt2::linspace(T(1),  T(4), 4));
  nt2::table<T> y =  nt2::colvect(nt2::linspace(T(2),  T(8), 4));
  nt2::table<T> xi=  nt2::colvect(nt2::linspace(T(0),  T(5), 11));
  nt2::table<T> r0 = nt2::colvect(_(T(0), T(10)));
  T nan =  nt2::Nan<T>();
  nt2::table<T> r1 = r0;  r1(_(1, 2)) = nan;  r1(_(10, 11)) = nan;
  nt2::table<T> r2 = r0;  r2(_(1, 2)) = T(33);r2(_(10, 11)) = T(33);
  nt2::table<T> yi =nt2::linear(x, y, xi);
  NT2_TEST_EQUAL(yi, r1);
  yi =nt2::linear(x, y, xi, false);
  NT2_TEST_EQUAL(yi, r1);
  yi =nt2::linear(x, y, xi, true);
  T z =  33;
  yi =nt2::linear(x, y, xi, z);
  NT2_TEST_EQUAL(yi, r2);
  yi =nt2::linear(x, y, xi, T(33));
  NT2_TEST_EQUAL(yi, r2);
}


NT2_TEST_CASE_TPL( linear5, NT2_REAL_TYPES )
{
  using nt2::_;
  nt2::table<T> x =  nt2::colvect(nt2::linspace(T(1),  T(4), 4));
  nt2::table<T> y =  nt2::repmat(nt2::colvect(nt2::linspace(T(2),  T(8), 4)), 1, 3);
  // NT2_DISPLAY(y);
  nt2::table<T> xi=  nt2::colvect(nt2::linspace(T(0),  T(5), 11));
  nt2::table<T> r0 = nt2::colvect(_(T(0), T(10)));
  T nan =  nt2::Nan<T>();
  nt2::table<T> r10 = r0;  r10(_(1, 2)) = nan;  r10(_(10, 11)) = nan;
  nt2::table<T> r1 =  nt2::repmat(r10, 1, 3);
  nt2::table<T> r20 = r0;  r20(_(1, 2)) = T(33);r20(_(10, 11)) = T(33);
  nt2::table<T> r2 =  nt2::repmat(r20, 1, 3);
  nt2::table<T> yi =nt2::linear(x, y, xi);
  NT2_TEST_EQUAL(yi, r1);
  yi =nt2::linear(x, y, xi, false);
  NT2_TEST_EQUAL(yi, r1);
  yi =nt2::linear(x, y, xi, true);
  T z =  33;
  yi =nt2::linear(x, y, xi, z);
  NT2_TEST_EQUAL(yi, r2);
  yi =nt2::linear(x, y, xi, T(33));
  NT2_TEST_EQUAL(yi, r2);
}
