//==============================================================================
//         Copyright 2003 - 2013   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/predicates/include/functions/is_gez.hpp>
#include <boost/simd/sdk/simd/logical.hpp>

#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>

#include <boost/simd/include/constants/false.hpp>
#include <boost/simd/include/constants/half.hpp>
#include <boost/simd/include/constants/mone.hpp>
#include <boost/simd/include/constants/one.hpp>
#include <boost/simd/include/constants/quarter.hpp>
#include <boost/simd/include/constants/true.hpp>
#include <boost/simd/include/constants/two.hpp>
#include <boost/simd/include/constants/zero.hpp>
#include <boost/simd/include/constants/inf.hpp>
#include <boost/simd/include/constants/minf.hpp>
#include <boost/simd/include/constants/nan.hpp>

NT2_TEST_CASE_TPL ( is_gez_real__1_0,  BOOST_SIMD_REAL_TYPES)
{
  using boost::simd::is_gez;
  using boost::simd::tag::is_gez_;
  typedef typename boost::dispatch::meta::call<is_gez_(T)>::type r_t;
  typedef boost::simd::logical<T> wished_r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
#ifndef BOOST_SIMD_NO_INVALIDS
  NT2_TEST_EQUAL(is_gez(boost::simd::Inf<T>()), boost::simd::True<r_t>());
  NT2_TEST_EQUAL(is_gez(boost::simd::Minf<T>()), boost::simd::False<r_t>());
  NT2_TEST_EQUAL(is_gez(boost::simd::Nan<T>()), boost::simd::False<r_t>());
#endif
  NT2_TEST_EQUAL(is_gez(-boost::simd::Zero<T>()), boost::simd::True<r_t>());
  NT2_TEST_EQUAL(is_gez(boost::simd::Half<T>()), boost::simd::True<r_t>());
  NT2_TEST_EQUAL(is_gez(boost::simd::Mone<T>()), boost::simd::False<r_t>());
  NT2_TEST_EQUAL(is_gez(boost::simd::One<T>()), boost::simd::True<r_t>());
  NT2_TEST_EQUAL(is_gez(boost::simd::Quarter<T>()), boost::simd::True<r_t>());
  NT2_TEST_EQUAL(is_gez(boost::simd::Two<T>()), boost::simd::True<r_t>());
  NT2_TEST_EQUAL(is_gez(boost::simd::Zero<T>()), boost::simd::True<r_t>());
}

NT2_TEST_CASE_TPL ( is_gez_signed_int__1_0,  BOOST_SIMD_INTEGRAL_SIGNED_TYPES)
{
  using boost::simd::is_gez;
  using boost::simd::tag::is_gez_;
  typedef typename boost::dispatch::meta::call<is_gez_(T)>::type r_t;
  typedef boost::simd::logical<T> wished_r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
  NT2_TEST_EQUAL(is_gez(boost::simd::Mone<T>()), boost::simd::False<r_t>());
  NT2_TEST_EQUAL(is_gez(boost::simd::One<T>()), boost::simd::True<r_t>());
  NT2_TEST_EQUAL(is_gez(boost::simd::Two<T>()), boost::simd::True<r_t>());
  NT2_TEST_EQUAL(is_gez(boost::simd::Zero<T>()), boost::simd::True<r_t>());
}

NT2_TEST_CASE_TPL ( is_gez_unsigned_int__1_0,  BOOST_SIMD_UNSIGNED_TYPES)
{
  using boost::simd::is_gez;
  using boost::simd::tag::is_gez_;
  typedef typename boost::dispatch::meta::call<is_gez_(T)>::type r_t;
  typedef boost::simd::logical<T> wished_r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
  NT2_TEST_EQUAL(is_gez(boost::simd::One<T>()), boost::simd::True<r_t>());
  NT2_TEST_EQUAL(is_gez(boost::simd::Two<T>()), boost::simd::True<r_t>());
  NT2_TEST_EQUAL(is_gez(boost::simd::Zero<T>()), boost::simd::True<r_t>());
}

NT2_TEST_CASE ( is_gez_bool)
{
  using boost::simd::is_gez;
  using boost::simd::tag::is_gez_;
  typedef boost::dispatch::meta::call<is_gez_(bool)>::type r_t;
  typedef bool wished_r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
  NT2_TEST_EQUAL(is_gez(true), true);
  NT2_TEST_EQUAL(is_gez(false), true);
}
