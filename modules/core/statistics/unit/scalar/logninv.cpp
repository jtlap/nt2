//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/logninv.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/repnum.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>

#include <nt2/constant/constant.hpp>
#include <nt2/table.hpp>

NT2_TEST_CASE_TPL ( logninv_1,  NT2_REAL_TYPES)
{
  using nt2::logninv;
  using nt2::tag::logninv_;
  using nt2::_;
  // specific values tests
  NT2_TEST_ULP_EQUAL(logninv(nt2::Nan<T>()), nt2::Nan<T>(), 0.5);
  NT2_TEST_ULP_EQUAL(logninv(nt2::Half<T>()), nt2::One<T>(), 3);
  NT2_TEST_ULP_EQUAL(logninv(nt2::Zero<T>()), nt2::Zero<T>(), 0.5);
  NT2_TEST_ULP_EQUAL(logninv(nt2::One<T>()), nt2::Inf<T>(), 0.5);
} // end of test for floating_

// NT2_TEST_CASE_TPL ( logninv_2,  NT2_REAL_TYPES)
// {
//   using nt2::logninv;
//   using nt2::tag::logninv_;
//   using nt2::_;
//   // specific values tests
//   NT2_TEST_ULP_EQUAL(logninv(nt2::Nan<T>(), nt2::One<T>()), nt2::Nan<T>(), 0.5);
//   NT2_TEST_ULP_EQUAL(logninv(T(0.841344746068542948585232545632), nt2::One<T>()), nt2::Two<T>(), 3);
//   NT2_TEST_ULP_EQUAL(logninv(T(0.158655253931457051414767454368), nt2::One<T>()), nt2::Zero<T>(), 6.5);
//   NT2_TEST_ULP_EQUAL(logninv(nt2::One<T>(), nt2::One<T>()), nt2::Inf<T>(), 0.5);
//   NT2_TEST_ULP_EQUAL(logninv(nt2::Zero<T>(), nt2::One<T>()), nt2::Minf<T>(), 0.5);
// } // end of test for floating_

// NT2_TEST_CASE_TPL ( logninv_1v,  NT2_REAL_TYPES)
// {
//   using nt2::logninv;
//   using nt2::tag::logninv_;
//   using nt2::_;
//   // specific values tests
//   NT2_TEST_ULP_EQUAL(logninv(nt2::repnum(nt2::Nan<T>(), 10, 2)), nt2::repnum(nt2::Nan<T>(), 10, 2), 0.5);
//   NT2_TEST_ULP_EQUAL(logninv(nt2::repnum(T(0.841344746068542948585232545632), 10, 2)), nt2::repnum(nt2::One<T>(), 10, 2), 3);
//   NT2_TEST_ULP_EQUAL(logninv(nt2::repnum(T(0.158655253931457051414767454368), 10, 2)), nt2::repnum(nt2::Mone<T>(), 10, 2), 6.5);
//   NT2_TEST_ULP_EQUAL(logninv(nt2::repnum(nt2::Zero<T>(), 10, 2)), nt2::repnum(nt2::Minf<T>(), 10, 2), 0.5);
//   NT2_TEST_ULP_EQUAL(logninv(nt2::repnum(nt2::One<T>(), 10, 2)), nt2::repnum(nt2::Inf<T>(), 10, 2), 0.5);
// }

// NT2_TEST_CASE_TPL ( logninv_2v,  NT2_REAL_TYPES)
// {
//   using nt2::logninv;
//   using nt2::tag::logninv_;
//   using nt2::_;
//   // specific values tests
//   NT2_TEST_ULP_EQUAL(logninv(nt2::repnum(nt2::Nan<T>(), 10, 2), nt2::One<T>()),  nt2::repnum(nt2::Nan<T>(), 10, 2), 0.5);
//   NT2_TEST_ULP_EQUAL(logninv(nt2::repnum(T(0.841344746068542948585232545632), 10, 2), nt2::One<T>()),  nt2::repnum(nt2::Two<T>(), 10, 2), 3);
//   NT2_TEST_ULP_EQUAL(logninv(nt2::repnum(T(0.158655253931457051414767454368), 10, 2), nt2::One<T>()),  nt2::repnum(nt2::Zero<T>(), 10, 2), 6.5);
//   NT2_TEST_ULP_EQUAL(logninv(nt2::repnum(nt2::One<T>(), 10, 2), nt2::One<T>()),  nt2::repnum(nt2::Inf<T>(), 10, 2), 0.5);
//   NT2_TEST_ULP_EQUAL(logninv(nt2::repnum(nt2::Zero<T>(), 10, 2), nt2::One<T>()),  nt2::repnum(nt2::Minf<T>(), 10, 2), 0.5);
// } // end of test for floating_

