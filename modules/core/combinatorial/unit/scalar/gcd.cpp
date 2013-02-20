//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 combinatorial toolbox - gcd/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of combinatorial components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created by jt the 30/11/2010
///
#include <nt2/toolbox/combinatorial/include/functions/gcd.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/mone.hpp>
#include <nt2/include/constants/minf.hpp>

NT2_TEST_CASE_TPL ( gcd_real__2_0,  NT2_REAL_TYPES)
{

  using nt2::gcd;
  using nt2::tag::gcd_;

  // specific values tests
  NT2_TEST_ULP_EQUAL(gcd(T(120),T(80)), 40, 0);
  NT2_TEST_ULP_EQUAL(gcd(T(3),T(15)), 3, 0);
  NT2_TEST_ULP_EQUAL(gcd(T(3),T(5)), 1, 0);
  NT2_TEST_ULP_EQUAL(gcd(T(6),T(15)), 3, 0);
  NT2_TEST_ULP_EQUAL(gcd(nt2::Inf<T>(), nt2::Inf<T>()), nt2::Nan<T>(), 0);
  NT2_TEST_ULP_EQUAL(gcd(nt2::Minf<T>(), nt2::Minf<T>()), nt2::Nan<T>(), 0);
  NT2_TEST_ULP_EQUAL(gcd(nt2::Mone<T>(), nt2::Mone<T>()), nt2::Mone<T>(), 0);
  NT2_TEST_ULP_EQUAL(gcd(nt2::Nan<T>(), nt2::Nan<T>()), nt2::Nan<T>(), 0);
  NT2_TEST_ULP_EQUAL(gcd(nt2::One<T>(), nt2::One<T>()), nt2::One<T>(), 0);
  NT2_TEST_ULP_EQUAL(gcd(nt2::Zero<T>(), nt2::Zero<T>()), nt2::Zero<T>(), 0);
} // end of test for floating_

NT2_TEST_CASE_TPL ( gcd_unsigned_int__2_0,  NT2_UNSIGNED_TYPES)
{

  using nt2::gcd;
  using nt2::tag::gcd_;

  // specific values tests
  NT2_TEST_ULP_EQUAL(gcd(T(120),T(80)), 40, 0);
  NT2_TEST_ULP_EQUAL(gcd(T(3),T(15)), 3, 0);
  NT2_TEST_ULP_EQUAL(gcd(T(3),T(5)), 1, 0);
  NT2_TEST_ULP_EQUAL(gcd(T(6),T(15)), 3, 0);
  NT2_TEST_ULP_EQUAL(gcd(nt2::One<T>(), nt2::One<T>()), nt2::One<T>(), 0);
  NT2_TEST_ULP_EQUAL(gcd(nt2::Zero<T>(), nt2::Zero<T>()), nt2::Zero<T>(), 0);
} // end of test for unsigned_int_

NT2_TEST_CASE_TPL ( gcd_signed_int__2_0,  NT2_INTEGRAL_SIGNED_TYPES)
{

  using nt2::gcd;
  using nt2::tag::gcd_;

  // specific values tests
  NT2_TEST_ULP_EQUAL(gcd(T(120),T(80)), 40, 0);
  NT2_TEST_ULP_EQUAL(gcd(T(3),T(15)), 3, 0);
  NT2_TEST_ULP_EQUAL(gcd(T(3),T(5)), 1, 0);
  NT2_TEST_ULP_EQUAL(gcd(T(6),T(15)), 3, 0);
  NT2_TEST_ULP_EQUAL(gcd(nt2::Mone<T>(), nt2::Mone<T>()), nt2::Mone<T>(), 0);
  NT2_TEST_ULP_EQUAL(gcd(nt2::One<T>(), nt2::One<T>()), nt2::One<T>(), 0);
  NT2_TEST_ULP_EQUAL(gcd(nt2::Zero<T>(), nt2::Zero<T>()), nt2::Zero<T>(), 0);
} // end of test for signed_int_
