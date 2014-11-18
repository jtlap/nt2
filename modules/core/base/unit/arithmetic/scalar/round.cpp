//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 arithmetic toolbox - round/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of arithmetic components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created by jt the 01/12/2010
///
#include <nt2/arithmetic/include/functions/round.hpp>
#include <boost/simd/sdk/simd/io.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/constant/constant.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/minf.hpp>
#include <nt2/include/constants/mone.hpp>
#include <nt2/include/constants/nan.hpp>


NT2_TEST_CASE_TPL ( round_real__1_0,  NT2_REAL_TYPES)
{

  using nt2::round;
  using nt2::tag::round_;
  typedef typename nt2::meta::call<round_(T)>::type r_t;
  typedef T wished_r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS( r_t, wished_r_t );

  // specific values tests
  NT2_TEST_ULP_EQUAL(round(T(1.4)), r_t(1), 0);
  NT2_TEST_ULP_EQUAL(round(T(1.5)), r_t(2), 0);
  NT2_TEST_ULP_EQUAL(round(T(1.6)), r_t(2), 0);
  NT2_TEST_ULP_EQUAL(round(T(2.5)), r_t(3), 0);
  NT2_TEST_ULP_EQUAL(round(nt2::Half<T>()), nt2::One<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(round(nt2::Inf<T>()), nt2::Inf<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(round(nt2::Mhalf<T>()), nt2::Mone<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(round(nt2::Minf<T>()), nt2::Minf<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(round(nt2::Mone<T>()), nt2::Mone<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(round(nt2::Nan<T>()), nt2::Nan<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(round(nt2::One<T>()), nt2::One<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(round(nt2::Zero<T>()), nt2::Zero<r_t>(), 0);
} // end of test for floating_

NT2_TEST_CASE_TPL ( round_unsigned_int__1_0,  NT2_UNSIGNED_TYPES)
{

  using nt2::round;
  using nt2::tag::round_;
  typedef typename nt2::meta::call<round_(T)>::type r_t;
  typedef T wished_r_t;


  // return type conformity test
  NT2_TEST_TYPE_IS( r_t, wished_r_t );

  // specific values tests
  NT2_TEST_ULP_EQUAL(round(nt2::One<T>()), nt2::One<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(round(nt2::Zero<T>()), nt2::Zero<r_t>(), 0);
} // end of test for unsigned_int_

NT2_TEST_CASE_TPL ( round_signed_int__1_0,  NT2_INTEGRAL_SIGNED_TYPES)
{

  using nt2::round;
  using nt2::tag::round_;
  typedef typename nt2::meta::call<round_(T)>::type r_t;
  typedef T wished_r_t;


  // return type conformity test
  NT2_TEST_TYPE_IS( r_t, wished_r_t );

  // specific values tests
  NT2_TEST_ULP_EQUAL(round(nt2::Mone<T>()), nt2::Mone<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(round(nt2::One<T>()), nt2::One<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(round(nt2::Zero<T>()), nt2::Zero<T>(), 0);
} // end of test for signed_int_
