//==============================================================================
//         Copyright 2003 - 2013   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/combinatorial/include/functions/lcm.hpp>

#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>

#include <nt2/include/constants/mone.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/minf.hpp>
#include <nt2/include/constants/nan.hpp>

NT2_TEST_CASE_TPL ( lcm_real__2_0,  NT2_REAL_TYPES)
{
  using nt2::lcm;
  using nt2::tag::lcm_;
  typedef typename nt2::meta::call<lcm_(T,T)>::type r_t;
  typedef T wished_r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
#ifndef BOOST_SIMD_NO_INVALIDS
  NT2_TEST_ULP_EQUAL(lcm(nt2::Inf<T>(), nt2::Inf<T>()), nt2::Nan<T>(), 0);
  NT2_TEST_ULP_EQUAL(lcm(nt2::Inf<T>(),T(5)), nt2::Nan<T>(), 0);
  NT2_TEST_ULP_EQUAL(lcm(nt2::Minf<T>(), nt2::Minf<T>()), nt2::Nan<T>(), 0);
  NT2_TEST_ULP_EQUAL(lcm(nt2::Nan<T>(), nt2::Nan<T>()), nt2::Nan<T>(), 0);
  NT2_TEST_ULP_EQUAL(lcm(nt2::Zero<T>(), nt2::Zero<T>()), nt2::Nan<T>(), 0);
#endif
  NT2_TEST_ULP_EQUAL(lcm(T(120),T(80)), T(240), 0);
  NT2_TEST_ULP_EQUAL(lcm(T(3),T(15)), T(15), 0);
  NT2_TEST_ULP_EQUAL(lcm(T(3),T(5)), T(15), 0);
  NT2_TEST_ULP_EQUAL(lcm(T(6),T(15)), T(30), 0);
  NT2_TEST_ULP_EQUAL(lcm(nt2::Mone<T>(), nt2::Mone<T>()), nt2::One<T>(), 0);
  NT2_TEST_ULP_EQUAL(lcm(nt2::One<T>(), nt2::One<T>()), nt2::One<T>(), 0);
}

NT2_TEST_CASE_TPL ( lcm_unsigned_int__2_0,  NT2_UNSIGNED_TYPES)
{
  using nt2::lcm;
  using nt2::tag::lcm_;
  typedef typename nt2::meta::call<lcm_(T,T)>::type r_t;
  typedef T wished_r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
  NT2_TEST_ULP_EQUAL(lcm(T(28), T(16)), T(112), 0);
  NT2_TEST_ULP_EQUAL(lcm(nt2::One<T>(), nt2::One<T>()), nt2::One<T>(), 0);
  NT2_TEST_ULP_EQUAL(lcm(nt2::Zero<T>(), nt2::Zero<T>()), nt2::Zero<T>(), 0);
}

NT2_TEST_CASE_TPL ( lcm_signed_int__2_0,  NT2_INTEGRAL_SIGNED_TYPES)
{
  using nt2::lcm;
  using nt2::tag::lcm_;
  typedef typename nt2::meta::call<lcm_(T,T)>::type r_t;
  typedef T wished_r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
  NT2_TEST_ULP_EQUAL(lcm(T(28), T(16)), T(112), 0);
  NT2_TEST_ULP_EQUAL(lcm(nt2::Mone<T>(), nt2::Mone<T>()), nt2::One<T>(), 0);
  NT2_TEST_ULP_EQUAL(lcm(nt2::One<T>(), nt2::One<T>()), nt2::One<T>(), 0);
  NT2_TEST_ULP_EQUAL(lcm(nt2::Zero<T>(), nt2::Zero<T>()), nt2::Zero<T>(), 0);
}
