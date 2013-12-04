//==============================================================================
//         Copyright 2003 - 2013   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/cot.hpp>

#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <complex>
#include <nt2/sdk/complex/complex.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>

#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/minf.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/include/constants/i.hpp>

NT2_TEST_CASE_TPL ( cot_real,  NT2_REAL_TYPES)
{
  using nt2::cot;
  using nt2::tag::cot_;
  typedef typename std::complex<T> cT;
  typedef typename nt2::meta::call<cot_(cT)>::type r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, cT);

  // specific values tests
#ifndef BOOST_SIMD_NO_INVALIDS
  NT2_TEST_ULP_EQUAL(nt2::cot(cT(nt2::Inf<T>())), cT(nt2::Nan<T>()), 1);
  NT2_TEST_ULP_EQUAL(nt2::cot(cT(nt2::Minf<T>())), cT(nt2::Nan<T>()), 1);
#endif
  NT2_TEST_ULP_EQUAL(nt2::cot(cT(1, 1)),nt2::rec(nt2::tan(cT(1.0, 1.0))), 1);
  NT2_TEST_ULP_EQUAL(nt2::cot(cT(1, 10)),nt2::rec(nt2::tan(cT(1.0, 10.0))), 1);
  NT2_TEST_ULP_EQUAL(nt2::cot(cT(10, 1)),nt2::rec(nt2::tan(cT(10.0, 1.0))), 1);
  NT2_TEST_ULP_EQUAL(nt2::cot(cT(10, 10)),nt2::rec(nt2::tan(cT(10.0, 10.0))), 1);
  NT2_TEST_ULP_EQUAL(nt2::cot(cT(0, 1)),nt2::rec(nt2::tan(cT(0.0, 1.0))), 1);
  NT2_TEST_ULP_EQUAL(nt2::cot(cT(0, 10)),nt2::rec(nt2::tan(cT(0.0, 10.0))), 1);
  NT2_TEST_ULP_EQUAL(nt2::cot(cT(10, 0)),nt2::rec(nt2::tan(cT(10.0, 0.0))), 1);
}
