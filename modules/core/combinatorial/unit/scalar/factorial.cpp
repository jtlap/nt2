//==============================================================================
//         Copyright 2003 - 2013   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/combinatorial/include/functions/factorial.hpp>

#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>
#include <nt2/include/functions/min.hpp>
#include <nt2/include/functions/saturate.hpp>

#include <nt2/include/constants/eight.hpp>
#include <nt2/include/constants/eleven.hpp>
#include <nt2/include/constants/five.hpp>
#include <nt2/include/constants/four.hpp>
#include <nt2/include/constants/nine.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/seven.hpp>
#include <nt2/include/constants/six.hpp>
#include <nt2/include/constants/ten.hpp>
#include <nt2/include/constants/three.hpp>
#include <nt2/include/constants/twelve.hpp>
#include <nt2/include/constants/two.hpp>
#include <nt2/include/constants/valmax.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/nan.hpp>

NT2_TEST_CASE_TPL ( factorial_real__1_0,  NT2_REAL_TYPES)
{
  using nt2::factorial;
  using nt2::tag::factorial_;
  typedef typename nt2::meta::call<factorial_(T)>::type r_t;
  typedef T wished_r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
#ifndef BOOST_SIMD_NO_INVALIDS
  NT2_TEST_ULP_EQUAL(factorial(nt2::Inf<T>()), nt2::Inf<T>(), 0);
  NT2_TEST_ULP_EQUAL(factorial(nt2::Nan<T>()), nt2::Nan<T>(), 0);
#endif
  NT2_TEST_ULP_EQUAL(factorial(nt2::Eight<T>()), nt2::min((T(40320ll    )),nt2::Valmax<T>()), 0);
  NT2_TEST_ULP_EQUAL(factorial(nt2::Eleven<T>()), nt2::min((T(39916800ll )),nt2::Valmax<T>()), 0);
  NT2_TEST_ULP_EQUAL(factorial(nt2::Five<T>()), T(120), 0);
  NT2_TEST_ULP_EQUAL(factorial(nt2::Four<T>()), T(24), 0);
  NT2_TEST_ULP_EQUAL(factorial(nt2::Nine<T>()), nt2::min((T(362880ll   )),nt2::Valmax<T>()), 0);
  NT2_TEST_ULP_EQUAL(factorial(nt2::One<T>()), nt2::One<T>(), 0);
  NT2_TEST_ULP_EQUAL(factorial(nt2::Seven<T>()), nt2::min((T(5040ll     )),nt2::Valmax<T>()), 0);
  NT2_TEST_ULP_EQUAL(factorial(nt2::Six<T>()), nt2::min((T(720ll      )),nt2::Valmax<T>()), 0);
  NT2_TEST_ULP_EQUAL(factorial(nt2::Ten<T>()), nt2::min((T(3628800ll  )),nt2::Valmax<T>()), 0);
  NT2_TEST_ULP_EQUAL(factorial(nt2::Three<T>()), nt2::Six<T>(), 0);
  NT2_TEST_ULP_EQUAL(factorial(nt2::Twelve<T>()), nt2::min((T(479001600ll)),nt2::Valmax<T>()), 0);
  NT2_TEST_ULP_EQUAL(factorial(nt2::Two<T>()), nt2::Two<T>(), 0);
  NT2_TEST_ULP_EQUAL(factorial(nt2::Zero<T>()), nt2::One<T>(), 0);
}

NT2_TEST_CASE_TPL ( factorial_integer__1_0,  NT2_INTEGRAL_TYPES)
{
  using nt2::factorial;
  using nt2::tag::factorial_;
  typedef typename nt2::meta::call<factorial_(T)>::type r_t;
  typedef T wished_r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
  NT2_TEST_ULP_EQUAL(factorial(nt2::Eight<T>()), T(nt2::saturate<T>(40320ull    )), 0);
  NT2_TEST_ULP_EQUAL(factorial(nt2::Eleven<T>()), T(nt2::saturate<T>(39916800ull)), 0);
  NT2_TEST_ULP_EQUAL(factorial(nt2::Five<T>()), T(nt2::saturate<T>(120)), 0);
  NT2_TEST_ULP_EQUAL(factorial(nt2::Four<T>()), T(nt2::saturate<T>(24)), 0);
  NT2_TEST_ULP_EQUAL(factorial(nt2::Nine<T>()), T(nt2::saturate<T>(362880ull   )), 0);
  NT2_TEST_ULP_EQUAL(factorial(nt2::One<T>()), nt2::One<T>(), 0);
  NT2_TEST_ULP_EQUAL(factorial(nt2::Seven<T>()), T(nt2::saturate<T>(5040ull     )), 0);
  NT2_TEST_ULP_EQUAL(factorial(nt2::Six<T>()), T(nt2::saturate<T>(720ull      )), 0);
  NT2_TEST_ULP_EQUAL(factorial(nt2::Ten<T>()), T(nt2::saturate<T>(3628800ull  )), 0);
  NT2_TEST_ULP_EQUAL(factorial(nt2::Three<T>()), nt2::Six<T>(), 0);
  NT2_TEST_ULP_EQUAL(factorial(nt2::Twelve<T>()), T(nt2::saturate<T>(479001600ull)), 0);
  NT2_TEST_ULP_EQUAL(factorial(nt2::Zero<T>()), nt2::One<T>(), 0);
}
