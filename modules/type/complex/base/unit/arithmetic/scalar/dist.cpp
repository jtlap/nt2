//==============================================================================
//         Copyright 2003 - 2013   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/dist.hpp>

#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <complex>
#include <nt2/sdk/complex/complex.hpp>
#include <nt2/sdk/complex/dry.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>

#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/sqrt_2.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/nan.hpp>

NT2_TEST_CASE_TPL ( dist_real,  BOOST_SIMD_REAL_TYPES)
{
  using nt2::dist;
  using nt2::tag::dist_;
  typedef typename std::complex<T> cT;
  typedef typename nt2::dry<T> dT;
  typedef typename boost::dispatch::meta::call<dist_(cT, cT)>::type r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, T);

  // specific values tests
#ifndef BOOST_SIMD_NO_INVALIDS
  NT2_TEST_EQUAL(dist(cT(nt2::Inf<T>()), cT(nt2::Inf<T>())), nt2::Nan<T>());
  NT2_TEST_ULP_EQUAL(dist(cT(0, nt2::Inf<T>()), cT(nt2::Inf<T>(), 0)), nt2::Inf<T>(), 0.5);
  NT2_TEST_ULP_EQUAL(dist(nt2::Inf<dT>(),nt2::Inf<dT>()), nt2::Nan<T>(), 0.5);
#endif
  NT2_TEST_EQUAL(dist(cT(nt2::One<T>()), cT(nt2::Zero<T>())), nt2::One<T>());
  NT2_TEST_EQUAL(dist(cT(nt2::Zero<T>()), cT(nt2::Zero<T>())),nt2::Zero<T>());
  NT2_TEST_ULP_EQUAL(dist(cT(0, 1), cT(1, 0)), nt2::Sqrt_2<T>(), 0.5);
  NT2_TEST_EQUAL(dist(cT(1, 0), cT(1, 0)), nt2::Zero<T>());
}
