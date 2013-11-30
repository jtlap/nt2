//==============================================================================
//         Copyright 2003 - 2013   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/exp.hpp>

#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <complex>
#include <nt2/sdk/complex/complex.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>

#include <nt2/include/constants/mone.hpp>
#include <nt2/include/constants/mzero.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/pi.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/minf.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/include/constants/exp_1.hpp>
#include <nt2/include/constants/i.hpp>

NT2_TEST_CASE_TPL ( exp_real,  NT2_REAL_TYPES)
{
  using nt2::exp;
  using nt2::tag::exp_;
  typedef typename std::complex<T> cT;
  NT2_TEST_TYPE_IS( typename nt2::meta::call<exp_(cT)>::type, cT );

  // specific values tests
#ifndef BOOST_SIMD_NO_INVALIDS
  NT2_TEST_EQUAL(nt2::exp(cT(nt2::Inf<T>())), cT(nt2::Inf<T>()));
  NT2_TEST_ULP_EQUAL(nt2::exp(cT(nt2::Minf<T>())), cT(nt2::Zero<T>()), 0.75);
  NT2_TEST_ULP_EQUAL(nt2::exp(cT(nt2::Nan<T>())), cT(nt2::Nan<T>(), nt2::Zero<T>()), 0.75);
  NT2_TEST_ULP_EQUAL(nt2::exp(cT(nt2::Inf  <T>(), nt2::Zero<T>())), cT(nt2::Inf<T>(), nt2::Zero<T>()), 0.75);
  NT2_TEST_ULP_EQUAL(nt2::exp(cT(nt2::Nan  <T>(), nt2::Zero<T>())), cT(nt2::Nan <T>(), nt2::Zero<T>()), 0.75);
  NT2_TEST_ULP_EQUAL(nt2::exp(cT(nt2::One  <T>(), nt2::Inf <T>())), cT(nt2::Nan<T>(), nt2::Nan<T>()), 0.75);
  NT2_TEST_ULP_EQUAL(nt2::exp(cT(nt2::One  <T>(), nt2::Nan <T>())), cT(nt2::Nan<T>(), nt2::Nan<T>()), 0.75);
  NT2_TEST_ULP_EQUAL(nt2::exp(cT(nt2::Minf <T>(), nt2::One <T>())), cT(nt2::Zero<T>()), 0.75);
  NT2_TEST_ULP_EQUAL(nt2::exp(cT(nt2::Minf <T>(), nt2::Mone<T>())), cT(nt2::Zero<T>()), 0.75);
  NT2_TEST_ULP_EQUAL(nt2::exp(cT(nt2::Inf  <T>(), nt2::One <T>())), cT(nt2::Inf <T>()*exp(cT(nt2::Zero<T>(), nt2::One <T>()))), 0.75);
  NT2_TEST_ULP_EQUAL(nt2::exp(cT(nt2::Inf  <T>(), nt2::Mone<T>())), cT(nt2::Inf <T>()*exp(cT(nt2::Zero<T>(), nt2::Mone<T>()))), 0.75);
  NT2_TEST_ULP_EQUAL(nt2::exp(cT(nt2::Minf <T>(), nt2::Inf<T>())),  cT(nt2::Zero<T>()), 0.75);
  NT2_TEST_ULP_EQUAL(nt2::exp(cT(nt2::Inf  <T>(), nt2::Inf<T>())),  cT(nt2::Nan <T>(), nt2::Nan<T>()), 0.75);
  NT2_TEST_ULP_EQUAL(nt2::exp(cT(nt2::Minf <T>(), nt2::Nan<T>())),  cT(nt2::Zero<T>()), 0.75);
  NT2_TEST_ULP_EQUAL(nt2::exp(cT(nt2::Inf  <T>(), nt2::Nan<T>())),  cT(nt2::Nan <T>(), nt2::Nan<T>()), 0.75);
  NT2_TEST_ULP_EQUAL(nt2::exp(cT(nt2::Nan  <T>(), nt2::One<T>())),  cT(nt2::Nan <T>(), nt2::Nan<T>()), 0.75);
  NT2_TEST_ULP_EQUAL(nt2::exp(cT(nt2::Nan  <T>(), nt2::Nan<T>())),  cT(nt2::Nan <T>(), nt2::Nan<T>()), 0.75);
  NT2_TEST_ULP_EQUAL(nt2::exp(cT(nt2::One  <T>(), -nt2::Inf <T>())), cT(nt2::Nan<T>(), nt2::Nan<T>()), 0.75);
  NT2_TEST_ULP_EQUAL(nt2::exp(cT(nt2::One  <T>(), -nt2::Nan <T>())), cT(nt2::Nan<T>(), nt2::Nan<T>()), 0.75);
  NT2_TEST_ULP_EQUAL(nt2::exp(cT(nt2::Minf <T>(), -nt2::One <T>())), cT(nt2::Zero<T>()), 0.75);
  NT2_TEST_ULP_EQUAL(nt2::exp(cT(nt2::Minf <T>(), -nt2::Mone<T>())), cT(nt2::Zero<T>()), 0.75);
  NT2_TEST_ULP_EQUAL(nt2::exp(cT(nt2::Inf  <T>(), -nt2::One <T>())), cT(nt2::Inf <T>()*exp(cT(nt2::Zero<T>(), -nt2::One <T>()))), 0.75);
  NT2_TEST_ULP_EQUAL(nt2::exp(cT(nt2::Inf  <T>(), -nt2::Mone<T>())), cT(nt2::Inf <T>()*exp(cT(nt2::Zero<T>(), -nt2::Mone<T>()))), 0.75);
  NT2_TEST_ULP_EQUAL(nt2::exp(cT(nt2::Minf <T>(), -nt2::Inf<T>())),  cT(nt2::Zero<T>()), 0.75);
  NT2_TEST_ULP_EQUAL(nt2::exp(cT(nt2::Inf  <T>(), -nt2::Inf<T>())),  cT(nt2::Nan <T>(), -nt2::Nan<T>()), 0.75);
  NT2_TEST_ULP_EQUAL(nt2::exp(cT(nt2::Minf <T>(), -nt2::Nan<T>())),  cT(nt2::Zero<T>()), 0.75);
  NT2_TEST_ULP_EQUAL(nt2::exp(cT(nt2::Inf  <T>(), -nt2::Nan<T>())),  cT(nt2::Nan <T>(), -nt2::Nan<T>()), 0.75);
  NT2_TEST_ULP_EQUAL(nt2::exp(cT(nt2::Nan  <T>(), -nt2::One<T>())),  cT(nt2::Nan <T>(), -nt2::Nan<T>()), 0.75);
  NT2_TEST_ULP_EQUAL(nt2::exp(cT(nt2::Nan  <T>(), -nt2::Nan<T>())),  cT(nt2::Nan <T>(), -nt2::Nan<T>()), 0.75);
#endif
  NT2_TEST_ULP_EQUAL(nt2::exp(cT(nt2::Mone<T>())), cT(nt2::One<T>()/nt2::Exp_1<T>()), 0.75);
  NT2_TEST_ULP_EQUAL(nt2::exp(cT(nt2::One<T>())), cT(nt2::Exp_1<T>()), 0.75);
  NT2_TEST_ULP_EQUAL(nt2::exp(cT(nt2::Zero<T>())), cT(nt2::One<T>()), 0.75);
  NT2_TEST_ULP_EQUAL(nt2::exp(cT(0, nt2::Pi<T>())),  cT(nt2::Mone<T>()), 0.75);
  NT2_TEST_ULP_EQUAL(nt2::exp(cT(nt2::Zero<T>(),  nt2::Zero<T>())), cT(nt2::One<T>()), 0.75);
  NT2_TEST_ULP_EQUAL(nt2::exp(cT(nt2::Mzero<T>(), nt2::Zero<T>())), cT(nt2::One<T>()), 0.75);
}
