//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/evinv.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/functions/repnum.hpp>
#include <nt2/include/functions/linspace.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>

#include <nt2/constant/constant.hpp>
#include <nt2/table.hpp>

NT2_TEST_CASE_TPL ( evinv_1,  NT2_REAL_TYPES)
{
  using nt2::evinv;
  using nt2::tag::evinv_;
  using nt2::_;
  // specific values tests
  NT2_TEST_ULP_EQUAL(evinv(nt2::Nan<T>()), nt2::Nan<T>(), 0.5);
  NT2_TEST_ULP_EQUAL(evinv(T(9.340119641546875e-01)), nt2::One<T>(), 0.5);
  NT2_TEST_ULP_EQUAL(evinv(T(3.077993724446537e-01)), nt2::Mone<T>(), 0.75);
  NT2_TEST_ULP_EQUAL(evinv(nt2::Zero<T>()), nt2::Minf<T>(), 0.5);
  NT2_TEST_ULP_EQUAL(evinv(nt2::One<T>()), nt2::Inf<T>(), 0.5);
  nt2::table<T> a = nt2::linspace(T(0), T(1), 5);
  nt2::table<T> r, plo, pup;
  nt2::table<T> cov = nt2::eye(2, nt2::meta::as_<T>());
  nt2::tie(r, plo, pup) = nt2::evinv(a, nt2::ones(size(a), nt2::meta::as_<T>()), T(1), cov, T(0.05));
  nt2::table<T> rr = nt2::cons<T>(-nt2::Inf<T>(),          -2.458993237072382e-01,
                                 6.334870794183356e-01,     1.326634259978281e+00,
                                 nt2::Inf<T>());


 nt2::table<T> pplo = nt2::cons<T>(-nt2::Inf<T>(),           -3.377100591027390e+00,
                                   -1.453972763320971e+00,   -7.352347540441273e-01,
                                   nt2::Nan<T>());


 nt2::table<T> ppup = nt2::cons<T>(nt2::Nan<T>(),             2.885301943612914e+00,
                                   2.720946922157642e+00,     3.388503274000689e+00,
                                   nt2::Inf<T>());
  NT2_TEST_ULP_EQUAL(r, rr, 10);
  NT2_TEST_ULP_EQUAL(plo, pplo, 600);
  NT2_TEST_ULP_EQUAL(pup, ppup, 1);
} // end of test for floating_

