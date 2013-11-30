//==============================================================================
//         Copyright 2003 - 2013   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/pow2.hpp>

#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <complex>
#include <nt2/sdk/complex/complex.hpp>
#include <nt2/sdk/complex/dry.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/complex/meta/as_dry.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>

#include <nt2/include/constants/half.hpp>
#include <nt2/include/constants/mone.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/two.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/minf.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/include/constants/i.hpp>

NT2_TEST_CASE_TPL ( pow2_real,  NT2_REAL_TYPES)
{
  using nt2::pow2;
  using nt2::tag::pow2_;
  typedef typename std::complex<T> cT;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef typename nt2::meta::as_dry<T>::type dT;
  typedef typename nt2::meta::call<pow2_(cT)>::type r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, cT);

  // specific values tests
#ifndef BOOST_SIMD_NO_INVALIDS
  NT2_TEST_ULP_EQUAL(pow2(cT(nt2::Inf<T>())), cT(nt2::Inf<T>()), 0);
  NT2_TEST_EQUAL(pow2(cT(nt2::Minf<T>())), cT(nt2::Zero<T>()));
  NT2_TEST_EQUAL(pow2(cT(nt2::Nan<T>())), cT(nt2::Nan<T>()));
#endif
  NT2_TEST_EQUAL(pow2(cT(nt2::Mone<T>())), cT(nt2::Half<T>()));
  NT2_TEST_EQUAL(pow2(cT(nt2::One<T>())), cT(nt2::Two<T>()));
  NT2_TEST_EQUAL(pow2(cT(nt2::Zero<T>())), cT(nt2::One<T>()));
  NT2_TEST_EQUAL(pow2(cT(nt2::One<T>(), nt2::One<T>()), iT(1)), dT(2));
}
