//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/hyperbolic/include/functions/sinhc.hpp>
#include <nt2/exponential/constants.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/module.hpp>

NT2_TEST_CASE_TPL ( sinhc_real__1_0,  NT2_REAL_TYPES)
{

  using nt2::sinhc;
  using nt2::tag::sinhc_;
  typedef typename nt2::meta::call<sinhc_(T)>::type r_t;
  typedef typename boost::dispatch::meta::as_floating<T>::type wished_r_t;

  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
#ifndef BOOST_SIMD_NO_INVALIDS
  NT2_TEST_ULP_EQUAL(sinhc(nt2::Inf<T>()), nt2::Inf<r_t>(), 0.5);
  NT2_TEST_ULP_EQUAL(sinhc(nt2::Minf<T>()), nt2::Inf<r_t>(), 0.5);
  NT2_TEST_ULP_EQUAL(sinhc(nt2::Nan<T>()), nt2::Nan<r_t>(), 0.5);
#endif
  NT2_TEST_ULP_EQUAL(sinhc(nt2::Zero<T>()), nt2::One<r_t>(), 0.5);
} // end of test for floating_

NT2_TEST_CASE_TPL ( sinhc_unsigned_int__1_0,  NT2_UNSIGNED_TYPES)
{
  using nt2::sinhc;
  using nt2::tag::sinhc_;
  typedef typename nt2::meta::call<sinhc_(T)>::type r_t;
  typedef typename boost::dispatch::meta::as_floating<T>::type wished_r_t;

  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
  NT2_TEST_ULP_EQUAL(sinhc(nt2::Zero<T>()), nt2::One<r_t>(), 0.5);
} // end of test for unsigned_int_

NT2_TEST_CASE_TPL ( sinhc_signed_int__1_0,  NT2_INTEGRAL_SIGNED_TYPES)
{
  using nt2::sinhc;
  using nt2::tag::sinhc_;
  typedef typename nt2::meta::call<sinhc_(T)>::type r_t;
  typedef typename boost::dispatch::meta::as_floating<T>::type wished_r_t;

  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
  NT2_TEST_ULP_EQUAL(sinhc(nt2::Zero<T>()), nt2::One<r_t>(), 0.5);
} // end of test for signed_int_
