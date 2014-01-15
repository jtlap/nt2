//==============================================================================
//         Copyright 2003 - 2013   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/trigonometric/include/functions/acot.hpp>

#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>

#include <nt2/include/constants/eps.hpp>
#include <nt2/include/constants/half.hpp>
#include <nt2/include/constants/mhalf.hpp>
#include <nt2/include/constants/mone.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/minf.hpp>
#include <nt2/include/constants/nan.hpp>

NT2_TEST_CASE_TPL ( acot_real,  NT2_REAL_TYPES)
{
  using nt2::acot;
  using nt2::tag::acot_;

  typedef typename nt2::meta::call<acot_(T)>::type r_t;
  typedef T wished_r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
#ifndef BOOST_SIMD_NO_INVALIDS
  NT2_TEST_ULP_EQUAL(acot(nt2::Inf<T>()), 0, 1.5);
  NT2_TEST_ULP_EQUAL(acot(nt2::Minf<T>()), 0, 1.5);
  NT2_TEST_ULP_EQUAL(acot(nt2::Nan<T>()), nt2::Nan<r_t>(), 1.5);
#endif
  NT2_TEST_ULP_EQUAL(acot(nt2::Half<T>()), 1.107148717794090e+00, 1.5);
  NT2_TEST_ULP_EQUAL(acot(nt2::Mhalf<T>()), -1.107148717794090e+00, 1.5);
  NT2_TEST_ULP_EQUAL(acot(nt2::Mone<T>()), -7.853981633974483e-01, 1.5);
  NT2_TEST_ULP_EQUAL(acot(nt2::One<T>()), 7.853981633974483e-01, 1.5);
  NT2_TEST_ULP_EQUAL(acot(nt2::Zero<T>()), 1.570796326794897e+00, 1.5);
  NT2_TEST_ULP_EQUAL(acot(nt2::rec(nt2::Eps<T>())), nt2::Eps<T>(), 1.5);
}
