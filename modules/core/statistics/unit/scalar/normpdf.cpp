//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 statistics toolbox - normpdf/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of statistics components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 22/02/2011
///
#include <nt2/include/functions/normpdf.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/memory/buffer.hpp>
#include <nt2/toolbox/constant/constant.hpp>
#include <nt2/include/constants/invsqrt_2pi.hpp>
#include <nt2/table.hpp>

NT2_TEST_CASE_TPL ( normpdf_1,  (float)(double))//NT2_REAL_TYPES)
{

  using nt2::normpdf;
  using nt2::tag::normpdf_;
  using nt2::_;


  // specific values tests
  NT2_TEST_ULP_EQUAL(normpdf(nt2::Nan<T>()), nt2::Nan<T>(), 0.5);
  NT2_TEST_ULP_EQUAL(normpdf(nt2::One<T>()), T(0.24197072451914334979783019293556), 0.5);
  NT2_TEST_ULP_EQUAL(normpdf(nt2::Mone<T>()), T(0.24197072451914334979783019293556), 0.5);
  NT2_TEST_ULP_EQUAL(normpdf(nt2::Zero<T>()), nt2::Invsqrt_2pi<T>(), 0);
  NT2_TEST_ULP_EQUAL(normpdf(nt2::Inf<T>()), nt2::Zero<T>(), 0.5);
  NT2_TEST_ULP_EQUAL(normpdf(nt2::Minf<T>()), nt2::Zero<T>(), 0.5);

  nt2::table<T> a = _(T(-5), T(1), T(5));
  NT2_DISPLAY(a);
  NT2_DISPLAY(normpdf(a));
} // end of test for floating_

NT2_TEST_CASE_TPL ( normpdf_2,  NT2_REAL_TYPES)
{

  using nt2::normpdf;
  using nt2::tag::normpdf_;
  using nt2::_;


  // specific values tests
  NT2_TEST_ULP_EQUAL(normpdf(nt2::Nan<T>(), nt2::One<T>()), nt2::Nan<T>(), 0.5);
  NT2_TEST_ULP_EQUAL(normpdf(nt2::Zero<T>(), nt2::One<T>() ), T(0.24197072451914334979783019293556), 0.5);
  NT2_TEST_ULP_EQUAL(normpdf(nt2::Mone<T>(), nt2::One<T>()),  T(0.053990966513188051950564200410714), 1);
  NT2_TEST_ULP_EQUAL(normpdf(nt2::Inf<T>(), nt2::One<T>()), nt2::Zero<T>(), 0.5);
  NT2_TEST_ULP_EQUAL(normpdf(nt2::Minf<T>(), nt2::One<T>()), nt2::Zero<T>(), 0.5);

  nt2::table<T> a = _(T(-5), T(1), T(5));
  NT2_DISPLAY(a);
  NT2_DISPLAY(normpdf(a, nt2::One<T>()));
  a = nt2::reshape(_(T(1), T(16)), 4, 4);
//   NT2_DISPLAY(normpdf(a, a(_, 1)));
//   NT2_DISPLAY(normpdf(a, a(1, _)));
  NT2_DISPLAY(normpdf(a, a));
  NT2_DISPLAY(normpdf(a, a, nt2::abs(a)));
} // end of test for floating_

