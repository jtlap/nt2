//==============================================================================
//         Copyright 2003 - 2013   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/min.hpp>

#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <complex>
#include <nt2/sdk/complex/meta/as_dry.hpp>
#include <nt2/sdk/complex/complex.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>

#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/inf.hpp>

NT2_TEST_CASE_TPL ( min_real,  BOOST_SIMD_REAL_TYPES)
{
  using nt2::min;
  using nt2::tag::min_;
  typedef typename std::complex<T> cT;
  typedef typename nt2::meta::as_dry<T>::type dT;
  typedef typename boost::dispatch::meta::call<min_(cT, cT)>::type r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, cT);

  // specific values tests
  NT2_TEST_ULP_EQUAL(nt2::min(cT(nt2::Inf<T>()), cT(nt2::Inf<T>())), cT(nt2::Inf<T>()), 0);
  NT2_TEST_EQUAL(nt2::min(cT(nt2::One<T>()), cT(nt2::Zero<T>())), cT(nt2::Zero<T>()));
  NT2_TEST_EQUAL(nt2::min(cT(nt2::Zero<T>()), cT(nt2::Zero<T>())),cT(nt2::Zero<T>()));
  NT2_TEST_EQUAL(nt2::min(cT(0, 1), cT(1, 0)), cT(1, 0));
  NT2_TEST_EQUAL(nt2::min(cT(2, 1), cT(2, 2)), cT(2, 1));
  NT2_TEST_EQUAL(nt2::min(dT(1),dT(-1)), dT(1));
  NT2_TEST_EQUAL(nt2::min(dT(1),T(-1)), dT(1));
  NT2_TEST_EQUAL(nt2::min(T(1),dT(-1)), dT(1));
}
