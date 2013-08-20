//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/exponential/include/functions/pow_abs.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/meta/as_floating.hpp>

#include <nt2/constant/constant.hpp>


NT2_TEST_CASE_TPL ( pow_abs_real__2_0,  NT2_REAL_TYPES)
{

  using nt2::pow_abs;
  using nt2::tag::pow_abs_;
  typedef typename nt2::meta::call<pow_abs_(T,T)>::type r_t;
  typedef typename boost::dispatch::meta::as_floating<T>::type wished_r_t;

  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
#ifndef BOOST_SIMD_NO_INVALIDS
  NT2_TEST_ULP_EQUAL(pow_abs(nt2::Inf<T>(), nt2::Inf<T>()), nt2::Inf<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(pow_abs(nt2::Minf<T>(), nt2::Minf<T>()), nt2::Zero<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(pow_abs(nt2::Nan<T>(), nt2::Nan<T>()), nt2::Nan<r_t>(), 0);
#endif
  NT2_TEST_ULP_EQUAL(pow_abs(nt2::Mone<T>(), nt2::Mone<T>()), nt2::One<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(pow_abs(nt2::One<T>(), nt2::One<T>()), nt2::One<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(pow_abs(nt2::Zero<T>(), nt2::Zero<T>()), nt2::One<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(pow_abs(T(-1),T(5)), T(1), 0);
  NT2_TEST_ULP_EQUAL(pow_abs(T(-1),T(6)), T(1), 0);
} // end of test for floating_

NT2_TEST_CASE_TPL ( pow_abs_unsigned_int__2_0,  NT2_UNSIGNED_TYPES)
{

  using nt2::pow_abs;
  using nt2::tag::pow_abs_;
  typedef typename nt2::meta::call<pow_abs_(T,T)>::type r_t;
  typedef typename boost::dispatch::meta::as_floating<T>::type wished_r_t;

  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
  NT2_TEST_ULP_EQUAL(pow_abs(nt2::One<T>(), nt2::One<T>()), nt2::One<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(pow_abs(nt2::Two<T>(),nt2::Three<T>()), nt2::Eight<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(pow_abs(nt2::Zero<T>(), nt2::Zero<T>()), nt2::One<r_t>(), 0);
} // end of test for unsigned_int_

NT2_TEST_CASE_TPL ( pow_abs_signed_int__2_0,  NT2_INTEGRAL_SIGNED_TYPES)
{

  using nt2::pow_abs;
  using nt2::tag::pow_abs_;
  typedef typename nt2::meta::call<pow_abs_(T,T)>::type r_t;
  typedef typename boost::dispatch::meta::as_floating<T>::type wished_r_t;

  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
  NT2_TEST_ULP_EQUAL(pow_abs(T(-2),T(3)), r_t(8), 0);
  NT2_TEST_ULP_EQUAL(pow_abs(nt2::Mone<T>(), nt2::Mone<T>()), nt2::One<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(pow_abs(nt2::One<T>(), nt2::One<T>()), nt2::One<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(pow_abs(nt2::Two<T>(),nt2::Three<T>()), nt2::Eight<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(pow_abs(nt2::Zero<T>(), nt2::Zero<T>()), nt2::One<r_t>(), 0);
} // end of test for signed_int_

NT2_TEST_CASE_TPL ( pow_abs_real__2_1,  NT2_REAL_TYPES)
{

  using nt2::pow_abs;
  using nt2::tag::pow_abs_;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef typename nt2::meta::call<pow_abs_(T,iT)>::type r_t;
  typedef typename boost::dispatch::meta::as_floating<T>::type wished_r_t;

  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
#ifndef BOOST_SIMD_NO_INVALIDS
  NT2_TEST_ULP_EQUAL(pow_abs(nt2::Inf<T>(),3), nt2::Inf<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(pow_abs(nt2::Minf<T>(),3), nt2::Inf<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(pow_abs(nt2::Nan<T>(),3), nt2::Nan<r_t>(), 0);
#endif
  NT2_TEST_ULP_EQUAL(pow_abs(nt2::Mone<T>(),3), T(1), 0);
  NT2_TEST_ULP_EQUAL(pow_abs(nt2::One<T>(),3), nt2::One<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(pow_abs(nt2::Two <T>(),3), T(8), 0);
  NT2_TEST_ULP_EQUAL(pow_abs(nt2::Zero<T>(),0), nt2::One<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(pow_abs(nt2::Zero<T>(),3), nt2::Zero<r_t>(), 0);
} // end of test for floating_
