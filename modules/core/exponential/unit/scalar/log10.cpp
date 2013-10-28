//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/exponential/include/functions/log10.hpp>
#include <nt2/exponential/include/functions/cbrt.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/module.hpp>

#include <nt2/constant/constant.hpp>


NT2_TEST_CASE_TPL ( log10_real__1_0,  NT2_REAL_TYPES)
{

  using nt2::log10;
  using nt2::tag::log10_;
  typedef typename nt2::meta::call<log10_(T)>::type r_t;
  typedef T wished_r_t;

  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
#ifndef BOOST_SIMD_NO_INVALIDS
  NT2_TEST_ULP_EQUAL(log10(nt2::Inf<T>()), nt2::Inf<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(log10(nt2::Minf<T>()), nt2::Nan<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(log10(nt2::Nan<T>()), nt2::Nan<r_t>(), 0);
#endif
  NT2_TEST_ULP_EQUAL(log10(nt2::Mone<T>()), nt2::Nan<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(log10(nt2::One<T>()), nt2::Zero<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(log10(nt2::Zero<T>()), nt2::Minf<r_t>(), 0);
} // end of test for floating_

NT2_TEST_CASE_TPL ( log10_unsigned_uint8,  (uint8_t))//NT2_UNSIGNED_TYPES)
{

  using nt2::log10;
  using nt2::tag::log10_;
  typedef typename nt2::meta::call<log10_(T)>::type r_t;
  typedef T wished_r_t;

  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
  NT2_TEST_ULP_EQUAL(log10(nt2::One<T>()), nt2::Zero<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(log10(nt2::Ten<T>()), nt2::One<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(log10(T(100)), T(2), 0);
 } // end of test for unsigned_int_

NT2_TEST_CASE_TPL ( log10_unsigned_int__1_0,  (uint16_t))//NT2_UNSIGNED_TYPES)
{

  using nt2::log10;
  using nt2::tag::log10_;
  typedef typename nt2::meta::call<log10_(T)>::type r_t;
  typedef T wished_r_t;

  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
  NT2_TEST_ULP_EQUAL(log10(nt2::One<T>()), nt2::Zero<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(log10(nt2::Ten<T>()), nt2::One<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(log10(T(100)), T(2), 0);
  NT2_TEST_ULP_EQUAL(log10(T(1000)), T(3), 0);
  NT2_TEST_ULP_EQUAL(log10(T(10000)), T(4), 0);
 } // end of test for unsigned_int_

NT2_TEST_CASE_TPL ( log10_unsigned_uint32,  (uint32_t))//NT2_UNSIGNED_TYPES)
{

  using nt2::log10;
  using nt2::tag::log10_;
  typedef typename nt2::meta::call<log10_(T)>::type r_t;
  typedef T wished_r_t;

  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
  NT2_TEST_ULP_EQUAL(log10(nt2::One<T>()), nt2::Zero<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(log10(nt2::Ten<T>()), nt2::One<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(log10(T(100)), T(2), 0);
  NT2_TEST_ULP_EQUAL(log10(T(1000)), T(3), 0);
  NT2_TEST_ULP_EQUAL(log10(T(10000)), T(4), 0);
  NT2_TEST_ULP_EQUAL(log10(T(100000)), T(5), 0);
  NT2_TEST_ULP_EQUAL(log10(T(1000000)), T(6), 0);
  NT2_TEST_ULP_EQUAL(log10(T(10000000)), T(7), 0);
  NT2_TEST_ULP_EQUAL(log10(T(100000000)), T(8), 0);
  NT2_TEST_ULP_EQUAL(log10(T(1000000000)), T(9), 0);
} // end of test for unsigned_int_


NT2_TEST_CASE_TPL ( log10_unsigned_uint64,  (uint64_t))//NT2_UNSIGNED_TYPES)
{

  using nt2::log10;
  using nt2::tag::log10_;
  typedef typename nt2::meta::call<log10_(T)>::type r_t;
  typedef T wished_r_t;

  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
  NT2_TEST_ULP_EQUAL(log10(nt2::One<T>()), nt2::Zero<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(log10(nt2::Ten<T>()), nt2::One<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(log10(T(100ull)), T(2), 0);
  NT2_TEST_ULP_EQUAL(log10(T(1000ull)), T(3), 0);
  NT2_TEST_ULP_EQUAL(log10(T(10000ull)), T(4), 0);
  NT2_TEST_ULP_EQUAL(log10(T(100000ull)), T(5), 0);
  NT2_TEST_ULP_EQUAL(log10(T(1000000ull)), T(6), 0);
  NT2_TEST_ULP_EQUAL(log10(T(10000000ull)), T(7), 0);
  NT2_TEST_ULP_EQUAL(log10(T(100000000ull)), T(8), 0);
  NT2_TEST_ULP_EQUAL(log10(T(1000000000ull)), T(9), 0);
  NT2_TEST_ULP_EQUAL(log10(T(10000000000ull)), T(10), 0);
  NT2_TEST_ULP_EQUAL(log10(T(100000000000ull)), T(11), 0);
  NT2_TEST_ULP_EQUAL(log10(T(1000000000000ull)), T(12), 0);
  NT2_TEST_ULP_EQUAL(log10(T(10000000000000ull)), T(13), 0);
  NT2_TEST_ULP_EQUAL(log10(T(100000000000000ull)), T(14), 0);
  NT2_TEST_ULP_EQUAL(log10(T(1000000000000000ull)), T(15), 0);
  NT2_TEST_ULP_EQUAL(log10(T(10000000000000000ull)), T(16), 0);
  NT2_TEST_ULP_EQUAL(log10(T(100000000000000000ull)), T(17), 0);
  NT2_TEST_ULP_EQUAL(log10(T(1000000000000000000ull)), T(18), 0);
  NT2_TEST_ULP_EQUAL(log10(T(10000000000000000000ull)), T(19), 0);
} // end of test for unsigned_int_

NT2_TEST_CASE_TPL ( log10_signed_int__1_0,  NT2_INTEGRAL_SIGNED_TYPES)
{

  using nt2::log10;
  using nt2::tag::log10_;
  typedef typename nt2::meta::call<log10_(T)>::type r_t;
  typedef T wished_r_t;

  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
  NT2_TEST_ULP_EQUAL(log10(nt2::One<T>()), nt2::Zero<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(log10(nt2::Ten<T>()), nt2::One<r_t>(), 0);
} // end of test for signed_int_
