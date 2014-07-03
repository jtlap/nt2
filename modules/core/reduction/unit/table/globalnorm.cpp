//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/table.hpp>
#include <nt2/include/functions/globalnorm.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/sqrt.hpp>
#include <nt2/include/functions/pow.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/ten.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/minf.hpp>

#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>

NT2_TEST_CASE_TPL(globalnorm, NT2_REAL_TYPES)
{
  using nt2::globalnorm;
  using nt2::tag::globalnorm_;
  nt2::table<T> n = nt2::ones(10, 1, nt2::meta::as_<T>());
  NT2_TEST_ULP_EQUAL(globalnorm(n, 1), nt2::Ten<T>(), 0);
  NT2_TEST_ULP_EQUAL(globalnorm(n, 2), nt2::sqrt(nt2::Ten<T>()), 0);
  NT2_TEST_ULP_EQUAL(globalnorm(n)   , nt2::sqrt(nt2::Ten<T>()), 0);
  NT2_TEST_ULP_EQUAL(globalnorm(n, 3), nt2::pow(nt2::Ten<T>(), 1/T(3)), 0);
  NT2_TEST_ULP_EQUAL(globalnorm(n, nt2::Inf<T>()), nt2::One<T>(), 0);
  NT2_TEST_ULP_EQUAL(globalnorm(n, nt2::Minf<T>()), nt2::One<T>(), 0);
  // statically taged with constants
  NT2_TEST_ULP_EQUAL(globalnorm(n, nt2::meta::as_<nt2::tag::Minf>()), nt2::One<T>(), 0);
  NT2_TEST_ULP_EQUAL(globalnorm<nt2::tag::Minf>(n), nt2::One<T>(), 0);
  NT2_TEST_ULP_EQUAL(globalnorm(n, nt2::meta::as_<nt2::tag::Inf>()), nt2::One<T>(), 0);
  NT2_TEST_ULP_EQUAL(globalnorm<nt2::tag::Inf>(n), nt2::One<T>(), 0);
  NT2_TEST_ULP_EQUAL(globalnorm(n, nt2::meta::as_<nt2::tag::One>()), nt2::Ten<T>(), 0);
  NT2_TEST_ULP_EQUAL(globalnorm<nt2::tag::One>(n), nt2::Ten<T>(), 0);
  NT2_TEST_ULP_EQUAL(globalnorm(n, nt2::meta::as_<nt2::tag::Two>()), nt2::sqrt(nt2::Ten<T>()), 0);
  NT2_TEST_ULP_EQUAL(globalnorm<nt2::tag::Two>(n), nt2::sqrt(nt2::Ten<T>()), 0);
  NT2_TEST_ULP_EQUAL(globalnorm(n, nt2::meta::as_<nt2::tag::Two>()), nt2::sqrt(nt2::Ten<T>()), 0);
  NT2_TEST_ULP_EQUAL(globalnorm<nt2::tag::Three>(n), nt2::pow(nt2::Ten<T>(), 1/T(3)), 0);
  // statically taged with int
  NT2_TEST_ULP_EQUAL(globalnorm<1>(n), nt2::Ten<T>(), 0);
  NT2_TEST_ULP_EQUAL(globalnorm<2>(n), nt2::sqrt(nt2::Ten<T>()), 0);
  NT2_TEST_ULP_EQUAL(globalnorm<3>(n), nt2::pow(nt2::Ten<T>(), 1/T(3)), 0);

}
