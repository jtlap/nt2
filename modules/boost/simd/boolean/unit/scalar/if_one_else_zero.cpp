//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 boost.simd.boolean toolbox - if_one_else_zero/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of boost.simd.boolean components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 18/02/2011
///
#include <boost/simd/boolean/include/functions/if_one_else_zero.hpp>
#include <boost/simd/sdk/simd/io.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

#include <boost/simd/constant/constant.hpp>
#include <boost/simd/include/constants/one.hpp>
#include <boost/simd/include/constants/inf.hpp>
#include <boost/simd/include/constants/zero.hpp>
#include <boost/simd/include/constants/minf.hpp>
#include <boost/simd/include/constants/mone.hpp>
#include <boost/simd/include/constants/nan.hpp>


NT2_TEST_CASE_TPL ( if_one_else_zero_real__2_0,  BOOST_SIMD_REAL_TYPES)
{

  using boost::simd::if_one_else_zero;
  using boost::simd::tag::if_one_else_zero_;
  using boost::simd::logical;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef typename boost::dispatch::meta::call<if_one_else_zero_(T)>::type r_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type sr_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type ssr_t;
  typedef typename boost::common_type<T>::type wished_r_t;


  // return type conformity test
  NT2_TEST_TYPE_IS( r_t, wished_r_t );

  // specific values tests
  NT2_TEST_EQUAL(if_one_else_zero(T(0)), 0);
  NT2_TEST_EQUAL(if_one_else_zero(T(1)), 1);
  NT2_TEST_EQUAL(if_one_else_zero(boost::simd::Inf<T>()) , 1);
  NT2_TEST_EQUAL(if_one_else_zero(boost::simd::Minf<T>()),1);
  NT2_TEST_EQUAL(if_one_else_zero(boost::simd::Nan<T>()) , 1);
  NT2_TEST_EQUAL(if_one_else_zero(boost::simd::Zero<T>()),0);
  NT2_TEST_EQUAL(if_one_else_zero(boost::simd::True< boost::simd::logical<T> >()), 1);
  NT2_TEST_EQUAL(if_one_else_zero(boost::simd::False< boost::simd::logical<T> >()), 0);
} // end of test for floating_

NT2_TEST_CASE_TPL ( if_one_else_zero_signed_int__2_0,  BOOST_SIMD_INTEGRAL_SIGNED_TYPES)
{

  using boost::simd::if_one_else_zero;
  using boost::simd::tag::if_one_else_zero_;
  using boost::simd::logical;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef typename boost::dispatch::meta::call<if_one_else_zero_(T)>::type r_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type sr_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type ssr_t;
  typedef typename boost::common_type<T>::type wished_r_t;


  // return type conformity test
  NT2_TEST_TYPE_IS( r_t, wished_r_t );

  // specific values tests
  NT2_TEST_EQUAL(if_one_else_zero(T(0)), 0);
  NT2_TEST_EQUAL(if_one_else_zero(T(1)), 1);
  NT2_TEST_EQUAL(if_one_else_zero(boost::simd::True< boost::simd::logical<T> >()), 1);
  NT2_TEST_EQUAL(if_one_else_zero(boost::simd::False< boost::simd::logical<T> >()), 0);
} // end of test for signed_int_

NT2_TEST_CASE_TPL ( if_one_else_zero_real__1_0,  BOOST_SIMD_REAL_TYPES)
{

  using boost::simd::if_one_else_zero;
  using boost::simd::tag::if_one_else_zero_;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef typename boost::dispatch::meta::call<if_one_else_zero_(T)>::type r_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type sr_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type ssr_t;
  typedef T wished_r_t;


  // return type conformity test
  NT2_TEST_TYPE_IS( r_t, wished_r_t );

  // specific values tests
  NT2_TEST_EQUAL(if_one_else_zero(-boost::simd::Zero<T>()), r_t(false));
  NT2_TEST_EQUAL(if_one_else_zero(boost::simd::Half<T>()), r_t(true));
  NT2_TEST_EQUAL(if_one_else_zero(boost::simd::Inf<T>()), r_t(true));
  NT2_TEST_EQUAL(if_one_else_zero(boost::simd::Minf<T>()), r_t(true));
  NT2_TEST_EQUAL(if_one_else_zero(boost::simd::Mone<T>()), r_t(true));
  NT2_TEST_EQUAL(if_one_else_zero(boost::simd::Nan<T>()), r_t(true));
  NT2_TEST_EQUAL(if_one_else_zero(boost::simd::One<T>()), r_t(true));
  NT2_TEST_EQUAL(if_one_else_zero(boost::simd::Quarter<T>()), r_t(true));
  NT2_TEST_EQUAL(if_one_else_zero(boost::simd::Two<T>()), r_t(true));
  NT2_TEST_EQUAL(if_one_else_zero(boost::simd::Zero<T>()), r_t(false));
} // end of test for floating_

NT2_TEST_CASE_TPL ( if_one_else_zero_signed_int__1_0,  BOOST_SIMD_INTEGRAL_SIGNED_TYPES)
{

  using boost::simd::if_one_else_zero;
  using boost::simd::tag::if_one_else_zero_;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef typename boost::dispatch::meta::call<if_one_else_zero_(T)>::type r_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type sr_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type ssr_t;
  typedef T wished_r_t;


  // return type conformity test
  NT2_TEST_TYPE_IS( r_t, wished_r_t );

  // specific values tests
  NT2_TEST_EQUAL(if_one_else_zero(boost::simd::Mone<T>()), r_t(true));
  NT2_TEST_EQUAL(if_one_else_zero(boost::simd::One<T>()), r_t(true));
  NT2_TEST_EQUAL(if_one_else_zero(boost::simd::Two<T>()), r_t(true));
  NT2_TEST_EQUAL(if_one_else_zero(boost::simd::Zero<T>()), r_t(false));
} // end of test for signed_int_

NT2_TEST_CASE_TPL ( if_one_else_zero_unsigned_int__1_0,  BOOST_SIMD_UNSIGNED_TYPES)
{

  using boost::simd::if_one_else_zero;
  using boost::simd::tag::if_one_else_zero_;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef typename boost::dispatch::meta::call<if_one_else_zero_(T)>::type r_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type sr_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type ssr_t;
  typedef T wished_r_t;


  // return type conformity test
  NT2_TEST_TYPE_IS( r_t, wished_r_t );

  // specific values tests
  NT2_TEST_EQUAL(if_one_else_zero(boost::simd::One<T>()), r_t(true));
  NT2_TEST_EQUAL(if_one_else_zero(boost::simd::Two<T>()), r_t(true));
  NT2_TEST_EQUAL(if_one_else_zero(boost::simd::Zero<T>()), r_t(false));
} // end of test for unsigned_int_

NT2_TEST_CASE_TPL ( if_one_else_zerol,  BOOST_SIMD_SIMD_TYPES)
{

  using boost::simd::if_one_else_zero;
  using boost::simd::tag::if_one_else_zero_;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef typename boost::dispatch::meta::call<if_one_else_zero_(T)>::type r_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type sr_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type ssr_t;
  typedef T wished_r_t;


  // return type conformity test
  NT2_TEST_TYPE_IS( r_t, wished_r_t );

  // specific values tests
  NT2_TEST_EQUAL(if_one_else_zero(boost::simd::True< boost::simd::logical<T> >()), r_t(true));
  NT2_TEST_EQUAL(if_one_else_zero(boost::simd::False< boost::simd::logical<T> >()), r_t(false));
} // end of test for unsigned_int_
