//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/trigonometric/include/functions/scalar/sincpi.hpp>
#include <nt2/include/functions/sinpi.hpp>
#include <nt2/include/constants/pi.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/minf.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/eps.hpp>
#include <nt2/include/constants/mindenormal.hpp>
#include <nt2/sdk/functor/meta/call.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>


NT2_TEST_CASE_TPL ( sincpi_real,  NT2_REAL_TYPES)
{
  using nt2::sincpi;
  using nt2::tag::sincpi_;

  // return type conformity test
  NT2_TEST_TYPE_IS(typename nt2::meta::call<sincpi_(T)>::type,T);

  // specific values tests
  NT2_TEST_ULP_EQUAL(sincpi(-T(1)/T(2)), T(2)/(nt2::Pi<T>()), 1.0);
  NT2_TEST_ULP_EQUAL(sincpi(-T(1)/T(4)), nt2::sinpi(T(1)/T(4))*T(4)/(nt2::Pi<T>()), 1.0);
  NT2_TEST_ULP_EQUAL(sincpi(nt2::Inf<T>()), nt2::Zero<T>(), 1.0);
  NT2_TEST_ULP_EQUAL(sincpi(nt2::Minf<T>()), nt2::Zero<T>(), 1.0);
  NT2_TEST_ULP_EQUAL(sincpi(nt2::Nan<T>()), nt2::Nan<T>(), 1.0);
  NT2_TEST_ULP_EQUAL(sincpi(T(1)/T(2)),  T(2)/(nt2::Pi<T>()), 1.0);
  NT2_TEST_ULP_EQUAL(sincpi(T(1)/T(4)), nt2::sinpi(T(1)/T(4))*T(4)/(nt2::Pi<T>()), 1.0);
  NT2_TEST_ULP_EQUAL(sincpi(nt2::Eps<T>()), nt2::One<T>(), 1.0);
  NT2_TEST_ULP_EQUAL(sincpi(nt2::Mindenormal<T>()), nt2::One<T>(), 1.0);
  NT2_TEST_ULP_EQUAL(sincpi(nt2::Zero<T>()), nt2::One<T>(), 1.0);
}
