//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/bitwise/include/functions/popcnt.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/include/constants/nan.hpp>
#include <boost/simd/include/constants/zero.hpp>
#include <boost/simd/include/constants/one.hpp>
#include <boost/simd/include/constants/mone.hpp>
#include <boost/simd/include/constants/nan.hpp>
#include <boost/simd/sdk/config.hpp>

NT2_TEST_CASE_TPL ( popcnt_real,  BOOST_SIMD_REAL_TYPES)
{

  using boost::simd::popcnt;
  using boost::simd::tag::popcnt_;
  typedef typename boost::dispatch::meta::call<popcnt_(T)>::type r_t;
  typedef typename boost::dispatch::meta::as_integer<T, unsigned>::type wished_r_t;


  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
#ifndef BOOST_SIMD_NO_INVALIDS
  NT2_TEST_EQUAL(popcnt(boost::simd::Nan<T>()), sizeof(T)*8);
#endif
  NT2_TEST_EQUAL(popcnt(boost::simd::Zero<T>()), boost::simd::Zero<r_t>());
} // end of test for floating_

NT2_TEST_CASE_TPL ( popcnt_integer,  BOOST_SIMD_INTEGRAL_TYPES)
{

  using boost::simd::popcnt;
  using boost::simd::tag::popcnt_;
  typedef typename boost::dispatch::meta::call<popcnt_(T)>::type r_t;
  typedef typename boost::dispatch::meta::as_integer<T, unsigned>::type wished_r_t;


  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
  NT2_TEST_EQUAL(popcnt(T(2)), boost::simd::One<r_t>());
  NT2_TEST_EQUAL(popcnt(T(3)), boost::simd::Two<r_t>());
  NT2_TEST_EQUAL(popcnt(boost::simd::Mone<T>()), sizeof(T)*8);
  NT2_TEST_EQUAL(popcnt(boost::simd::One<T>()), boost::simd::One<r_t>());
  NT2_TEST_EQUAL(popcnt(boost::simd::Zero<T>()), boost::simd::Zero<r_t>());
} // end of test for integer_
