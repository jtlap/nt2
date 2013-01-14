//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 boost.simd.boolean toolbox - if_one_else_zero/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of boost.simd.boolean components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 18/02/2011
///
#include <boost/simd/toolbox/boolean/include/functions/if_one_else_zero.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/include/functions/ulpdist.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/toolbox/constant/constant.hpp>


NT2_TEST_CASE_TPL ( if_one_else_zero_real__2_0,  BOOST_SIMD_REAL_TYPES)
{

  using boost::simd::if_one_else_zero;
  using boost::simd::tag::if_one_else_zero_;
  using boost::simd::logical;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef typename boost::dispatch::meta::call<if_one_else_zero_(T)>::type r_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type sr_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type ssr_t;
  typedef typename boost::dispatch::meta::upgrade<T>::type u_t;
  typedef typename boost::common_type<T>::type wished_r_t;


  // return type conformity test
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl;

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
  typedef typename boost::dispatch::meta::upgrade<T>::type u_t;
  typedef typename boost::common_type<T>::type wished_r_t;


  // return type conformity test
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl;

  // specific values tests
  NT2_TEST_EQUAL(if_one_else_zero(T(0)), 0);
  NT2_TEST_EQUAL(if_one_else_zero(T(1)), 1);
  NT2_TEST_EQUAL(if_one_else_zero(boost::simd::True< boost::simd::logical<T> >()), 1);
  NT2_TEST_EQUAL(if_one_else_zero(boost::simd::False< boost::simd::logical<T> >()), 0);
} // end of test for signed_int_
