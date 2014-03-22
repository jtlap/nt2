//==============================================================================
//         Copyright 2003 - 2013   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/euler/include/functions/digamma.hpp>

#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>
#include <boost/math/special_functions/digamma.hpp>

#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/mzero.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/minf.hpp>
#include <nt2/include/constants/nan.hpp>

NT2_TEST_CASE_TPL ( digamma_real, NT2_REAL_TYPES)
{
  using nt2::digamma;
  using nt2::tag::digamma_;
  typedef typename nt2::meta::call<digamma_(T)>::type r_t;
  typedef T wished_r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
  NT2_TEST_ULP_EQUAL(digamma(nt2::Zero<T>()), nt2::Inf<T>(), 0.5);
  NT2_TEST_ULP_EQUAL(digamma(nt2::Mzero<T>()), nt2::Minf<T>(), 0.5);
  NT2_TEST_ULP_EQUAL(digamma(nt2::One<T>()),  boost::math::digamma(nt2::One<T>()), 0.5);
  NT2_TEST_ULP_EQUAL(digamma(T(1.4669020846486091614)),T(boost::math::digamma(double(T(1.4669020846486091614)))), 0.5);
  NT2_TEST_ULP_EQUAL(digamma(T(1.461632133e+00)),  T(boost::math::digamma(double(T(1.461632133e+00)))), 7.5);
  NT2_TEST_ULP_EQUAL(digamma(T(-3.5)),             T(boost::math::digamma(double(T(-3.5)))), 0.5);
  NT2_TEST_ULP_EQUAL(digamma(T(-3.51)),             T(boost::math::digamma(double(T(-3.51)))), 0.5);
  NT2_TEST_ULP_EQUAL(digamma(T(-6)),  nt2::Nan<T>(), 0.5);
  NT2_TEST_ULP_EQUAL(digamma(T(6)) ,    T(1.706117668431801e+00), 1);
//  NT2_TEST_ULP_EQUAL(digamma(T(-1.221245221e-15)), T(8.188363203e+14), 0.5);
//  NT2_TEST_ULP_EQUAL(digamma(T(-1.221245221e-15)), T(boost::math::digamma(double(T(-1.221245221e-15)))), 0.5);

}

