//==============================================================================
//         Copyright 2003 - 2013   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/combinatorial/include/functions/cnp.hpp>

#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>

#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/nan.hpp>

NT2_TEST_CASE_TPL ( cnp_real__2_0,  NT2_REAL_TYPES)
{
  using nt2::cnp;
  using nt2::tag::cnp_;
  typedef typename nt2::meta::call<cnp_(T,T)>::type r_t;
  typedef T wished_r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
#ifndef BOOST_SIMD_NO_INVALIDS
  NT2_TEST_ULP_EQUAL(cnp(nt2::Inf<T>(), nt2::Inf<T>()), nt2::Nan<T>(), 0);
  NT2_TEST_ULP_EQUAL(cnp(nt2::Nan<T>(), nt2::Nan<T>()), nt2::Nan<T>(), 0);
#endif
  NT2_TEST_ULP_EQUAL(cnp(T(10),T(1)), T(10), 0);
  NT2_TEST_ULP_EQUAL(cnp(T(10),T(2)), T(45), 0);
  NT2_TEST_ULP_EQUAL(cnp(T(10),T(8)), T(45), 0);
  NT2_TEST_ULP_EQUAL(cnp(T(2),T(1)), T(2), 0);
  NT2_TEST_ULP_EQUAL(cnp(T(2),T(2)), T(1), 0);
  NT2_TEST_ULP_EQUAL(cnp(nt2::One<T>(), nt2::One<T>()), nt2::One<T>(), 0);
  NT2_TEST_ULP_EQUAL(cnp(nt2::Zero<T>(), nt2::Zero<T>()), nt2::One<T>(), 0);
}

NT2_TEST_CASE_TPL ( cnp_unsigned_int__2_0,  NT2_UNSIGNED_TYPES)
{
  using nt2::cnp;
  using nt2::tag::cnp_;
  typedef typename nt2::meta::call<cnp_(T,T)>::type r_t;
  typedef T wished_r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
  NT2_TEST_ULP_EQUAL(cnp(nt2::One<T>(), nt2::One<T>()), nt2::One<T>(), 0);
  NT2_TEST_ULP_EQUAL(cnp(nt2::Zero<T>(), nt2::Zero<T>()), nt2::One<T>(), 0);
}

NT2_TEST_CASE_TPL ( cnp_signed_int__2_0,  NT2_INTEGRAL_SIGNED_TYPES)
{
  using nt2::cnp;
  using nt2::tag::cnp_;
  typedef typename nt2::meta::call<cnp_(T,T)>::type r_t;
  typedef T wished_r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
  NT2_TEST_ULP_EQUAL(cnp(nt2::One<T>(), nt2::One<T>()), nt2::One<T>(), 0);
  NT2_TEST_ULP_EQUAL(cnp(nt2::Zero<T>(), nt2::Zero<T>()), nt2::One<T>(), 0);
}
