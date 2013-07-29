//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 statistics toolbox - normpdf/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of statistics components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 22/02/2011
///
#include <nt2/include/functions/normpdf.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/functions/repnum.hpp>
#include <nt2/include/functions/reshape.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/module.hpp>

#include <nt2/constant/constant.hpp>
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
} // end of test for floating_

NT2_TEST_CASE_TPL ( normpdf_2,  NT2_REAL_TYPES)
{

  using nt2::normpdf;
  using nt2::tag::normpdf_;
  using nt2::_;
  nt2::table<T> a = _(T(-5), T(1), T(5));
  nt2::table<T> r = nt2::cons<T>(6.0758828498232860873e-09, 1.4867195147342976779e-06, 0.00013383022576488536764, 0.0044318484119380075273,
                                 0.053990966513188062836, 0.24197072451914336533, 0.39894228040143270286, 0.24197072451914336533,
                                 0.053990966513188062836, 0.0044318484119380075273, 0.00013383022576488536764);
  NT2_TEST_ULP_EQUAL(normpdf(a, nt2::One<T>()), r, 1);
  a = nt2::reshape(_(T(1), T(16)), 4, 4);
  NT2_TEST_ULP_EQUAL(normpdf(a, a), nt2::repnum(0.39894228040143270286, 4, 4), 1);
  NT2_TEST_ULP_EQUAL(normpdf(a, a, nt2::abs(a)), nt2::repnum(0.39894228040143270286, 4, 4), 1);
} // end of test for floating_

