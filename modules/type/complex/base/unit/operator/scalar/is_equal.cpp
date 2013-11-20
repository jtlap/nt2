//==============================================================================
//         Copyright 2003 - 2013   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/is_equal.hpp>

#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <complex>
#include <nt2/sdk/complex/complex.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>

#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/minf.hpp>
#include <nt2/include/constants/nan.hpp>

NT2_TEST_CASE_TPL ( is_equal_real,  BOOST_SIMD_REAL_TYPES)
{
  using nt2::is_equal;
  using nt2::tag::is_equal_;
  typedef typename std::complex<T> cT;
  typedef typename boost::dispatch::meta::call<is_equal_(T,T)>::type r_t;
  typedef nt2::logical<T> wished_r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
#ifndef BOOST_SIMD_NO_INVALIDS
  NT2_TEST_EQUAL(is_equal(cT(nt2::Inf<T>()),  cT(nt2::Inf<T>())),  r_t(true));
  NT2_TEST_EQUAL(is_equal(cT(nt2::Minf<T>()), cT(nt2::Minf<T>())), r_t(true));
  NT2_TEST_EQUAL(is_equal(cT(nt2::Nan<T>()),  cT(nt2::Nan<T>())),  r_t(false));
#endif
  NT2_TEST_EQUAL(is_equal(cT(nt2::One<T>()),  cT(nt2::Zero<T>())), r_t(false));
  NT2_TEST_EQUAL(is_equal(cT(nt2::Zero<T>()), cT(nt2::Zero<T>())), r_t(true));
  NT2_TEST_EQUAL(is_equal(cT(0, 1), cT(0, 1)), r_t(true));
  NT2_TEST_EQUAL(is_equal(cT(1, 0), T(1))    , r_t(true));
  NT2_TEST_EQUAL(is_equal(cT(0, 2), cT(0, 1)), r_t(false));
}
