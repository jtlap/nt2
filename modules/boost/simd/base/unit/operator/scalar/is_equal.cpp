//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/operator/include/functions/is_equal.hpp>

#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>
#include <boost/simd/sdk/simd/io.hpp>

#include <boost/simd/include/constants/one.hpp>
#include <boost/simd/include/constants/mone.hpp>
#include <boost/simd/include/constants/zero.hpp>
#include <boost/simd/include/constants/three.hpp>
#include <boost/simd/include/constants/inf.hpp>
#include <boost/simd/include/constants/minf.hpp>
#include <boost/simd/include/constants/nan.hpp>
#include <boost/simd/include/constants/valmax.hpp>
#include <boost/simd/include/constants/true.hpp>
#include <boost/simd/include/constants/false.hpp>

NT2_TEST_CASE_TPL ( is_equal_integer,  BOOST_SIMD_INTEGRAL_TYPES)
{

  using boost::simd::is_equal;
  using boost::simd::tag::is_equal_;
  typedef typename boost::dispatch::meta::call<is_equal_(T,T)>::type r_t;
  typedef boost::simd::logical<T> wished_r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
  NT2_TEST_EQUAL(is_equal(boost::simd::One<T>(), boost::simd::One<T>()), r_t(true));
  NT2_TEST_EQUAL(is_equal(boost::simd::One<T>(),boost::simd::Zero<T>()), r_t(false));
  NT2_TEST_EQUAL(is_equal(boost::simd::Zero<T>(), boost::simd::Zero<T>()), r_t(true));
} // end of test for integer_

NT2_TEST_CASE_TPL ( is_equal_real,  BOOST_SIMD_REAL_TYPES)
{

  using boost::simd::is_equal;
  using boost::simd::tag::is_equal_;
  typedef typename boost::dispatch::meta::call<is_equal_(T,T)>::type r_t;
  typedef boost::simd::logical<T> wished_r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
  NT2_TEST_EQUAL(is_equal(boost::simd::Inf<T>(), boost::simd::Inf<T>()), r_t(true));
  NT2_TEST_EQUAL(is_equal(boost::simd::Minf<T>(), boost::simd::Minf<T>()), r_t(true));
  NT2_TEST_EQUAL(is_equal(boost::simd::Nan<T>(), boost::simd::Nan<T>()), r_t(false));
  NT2_TEST_EQUAL(is_equal(boost::simd::One<T>(),boost::simd::Zero<T>()), r_t(false));
  NT2_TEST_EQUAL(is_equal(boost::simd::Zero<T>(), boost::simd::Zero<T>()), r_t(true));
} // end of test for floating_

NT2_TEST_CASE_TPL ( is_equall,  BOOST_SIMD_SIMD_TYPES)
{

  using boost::simd::is_equal;
  using boost::simd::tag::is_equal_;
  typedef typename boost::dispatch::meta::call<is_equal_(T,T)>::type r_t;
  typedef boost::simd::logical<T> wished_r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  NT2_TEST_EQUAL(is_equal(boost::simd::True< boost::simd::logical<T> >(), boost::simd::True< boost::simd::logical<T> >()), r_t(true));
  NT2_TEST_EQUAL(is_equal(boost::simd::False< boost::simd::logical<T> >(), boost::simd::False< boost::simd::logical<T> >()), r_t(true));
  NT2_TEST_EQUAL(is_equal(boost::simd::True< boost::simd::logical<T> >(), boost::simd::False< boost::simd::logical<T> >()), r_t(false));
  NT2_TEST_EQUAL(is_equal(boost::simd::False< boost::simd::logical<T> >(), boost::simd::True< boost::simd::logical<T> >()), r_t(false));
}

NT2_TEST_CASE ( is_equal_bool)
{
  using boost::simd::is_equal;
  using boost::simd::tag::is_equal_;
  typedef  boost::dispatch::meta::call<is_equal_(bool, bool)>::type r_t;
  typedef bool wished_r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
  NT2_TEST_EQUAL(is_equal(true, false), false);
  NT2_TEST_EQUAL(is_equal(false, true), false);
  NT2_TEST_EQUAL(is_equal(true, true), true);
  NT2_TEST_EQUAL(is_equal(false, false), true);
}
