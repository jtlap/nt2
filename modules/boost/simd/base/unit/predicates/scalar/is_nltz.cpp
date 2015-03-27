//==============================================================================
//         Copyright 2003 - 2013   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/predicates/include/functions/is_nltz.hpp>
#include <boost/simd/sdk/simd/logical.hpp>

#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>

#include <boost/simd/include/constants/half.hpp>
#include <boost/simd/include/constants/mone.hpp>
#include <boost/simd/include/constants/one.hpp>
#include <boost/simd/include/constants/quarter.hpp>
#include <boost/simd/include/constants/two.hpp>
#include <boost/simd/include/constants/zero.hpp>
#include <boost/simd/include/constants/inf.hpp>
#include <boost/simd/include/constants/minf.hpp>
#include <boost/simd/include/constants/nan.hpp>

NT2_TEST_CASE_TPL ( is_nltz_real__1_0,  BOOST_SIMD_REAL_TYPES)
{
  using boost::simd::is_nltz;
  using boost::simd::tag::is_nltz_;
  typedef typename boost::dispatch::meta::call<is_nltz_(T)>::type r_t;
  typedef boost::simd::logical<T> wished_r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
#ifndef BOOST_SIMD_NO_INVALIDS
  NT2_TEST_EQUAL(is_nltz(boost::simd::Inf<T>()), r_t(true));
  NT2_TEST_EQUAL(is_nltz(boost::simd::Minf<T>()), r_t(false));
  NT2_TEST_EQUAL(is_nltz(boost::simd::Nan<T>()), r_t(true));
#endif
  NT2_TEST_EQUAL(is_nltz(-boost::simd::Zero<T>()), r_t(true));
  NT2_TEST_EQUAL(is_nltz(boost::simd::Half<T>()), r_t(true));
  NT2_TEST_EQUAL(is_nltz(boost::simd::Mone<T>()), r_t(false));
  NT2_TEST_EQUAL(is_nltz(boost::simd::One<T>()), r_t(true));
  NT2_TEST_EQUAL(is_nltz(boost::simd::Quarter<T>()), r_t(true));
  NT2_TEST_EQUAL(is_nltz(boost::simd::Two<T>()), r_t(true));
  NT2_TEST_EQUAL(is_nltz(boost::simd::Zero<T>()), r_t(true));
}

NT2_TEST_CASE_TPL ( is_nltz_signed_int__1_0,  BOOST_SIMD_INTEGRAL_SIGNED_TYPES)
{
  using boost::simd::is_nltz;
  using boost::simd::tag::is_nltz_;
  typedef typename boost::dispatch::meta::call<is_nltz_(T)>::type r_t;
  typedef boost::simd::logical<T> wished_r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
  NT2_TEST_EQUAL(is_nltz(boost::simd::Mone<T>()), r_t(false));
  NT2_TEST_EQUAL(is_nltz(boost::simd::One<T>()), r_t(true));
  NT2_TEST_EQUAL(is_nltz(boost::simd::Two<T>()), r_t(true));
  NT2_TEST_EQUAL(is_nltz(boost::simd::Zero<T>()), r_t(true));
}

NT2_TEST_CASE_TPL ( is_nltz_unsigned_int__1_0,  BOOST_SIMD_UNSIGNED_TYPES)
{
  using boost::simd::is_nltz;
  using boost::simd::tag::is_nltz_;
  typedef typename boost::dispatch::meta::call<is_nltz_(T)>::type r_t;
  typedef boost::simd::logical<T> wished_r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
  NT2_TEST_EQUAL(is_nltz(boost::simd::One<T>()), r_t(true));
  NT2_TEST_EQUAL(is_nltz(boost::simd::Two<T>()), r_t(true));
  NT2_TEST_EQUAL(is_nltz(boost::simd::Zero<T>()), r_t(true));
}

NT2_TEST_CASE ( is_nltz_bool)
{
  using boost::simd::is_nltz;
  using boost::simd::tag::is_nltz_;
  typedef boost::dispatch::meta::call<is_nltz_(bool)>::type r_t;
  typedef bool wished_r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
  NT2_TEST_EQUAL(is_nltz(true), true);
  NT2_TEST_EQUAL(is_nltz(false), true);
}
