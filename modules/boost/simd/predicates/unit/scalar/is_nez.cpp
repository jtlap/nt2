//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 boost.simd.predicates toolbox - is_nez/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of boost.simd.predicates components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 21/02/2011
///
#include <boost/simd/toolbox/predicates/include/functions/is_nez.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/sdk/simd/logical.hpp>

#include <boost/type_traits/is_same.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/toolbox/constant/constant.hpp>


NT2_TEST_CASE_TPL ( is_nez_real__1_0,  BOOST_SIMD_REAL_TYPES)
{

  using boost::simd::is_nez;
  using boost::simd::tag::is_nez_;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef typename boost::dispatch::meta::call<is_nez_(T)>::type r_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type sr_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type ssr_t;
  typedef boost::simd::logical<T> wished_r_t;


  // return type conformity test
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl;

  // specific values tests
  NT2_TEST_EQUAL(is_nez(-boost::simd::Zero<T>()), r_t(false));
  NT2_TEST_EQUAL(is_nez(boost::simd::Half<T>()), r_t(true));
  NT2_TEST_EQUAL(is_nez(boost::simd::Inf<T>()), r_t(true));
  NT2_TEST_EQUAL(is_nez(boost::simd::Minf<T>()), r_t(true));
  NT2_TEST_EQUAL(is_nez(boost::simd::Mone<T>()), r_t(true));
  NT2_TEST_EQUAL(is_nez(boost::simd::Nan<T>()), r_t(true));
  NT2_TEST_EQUAL(is_nez(boost::simd::One<T>()), r_t(true));
  NT2_TEST_EQUAL(is_nez(boost::simd::Quarter<T>()), r_t(true));
  NT2_TEST_EQUAL(is_nez(boost::simd::Two<T>()), r_t(true));
  NT2_TEST_EQUAL(is_nez(boost::simd::Zero<T>()), r_t(false));
} // end of test for floating_

NT2_TEST_CASE_TPL ( is_nez_signed_int__1_0,  BOOST_SIMD_INTEGRAL_SIGNED_TYPES)
{

  using boost::simd::is_nez;
  using boost::simd::tag::is_nez_;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef typename boost::dispatch::meta::call<is_nez_(T)>::type r_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type sr_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type ssr_t;
  typedef boost::simd::logical<T> wished_r_t;


  // return type conformity test
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl;

  // specific values tests
  NT2_TEST_EQUAL(is_nez(boost::simd::Mone<T>()), r_t(true));
  NT2_TEST_EQUAL(is_nez(boost::simd::One<T>()), r_t(true));
  NT2_TEST_EQUAL(is_nez(boost::simd::Two<T>()), r_t(true));
  NT2_TEST_EQUAL(is_nez(boost::simd::Zero<T>()), r_t(false));
} // end of test for signed_int_

NT2_TEST_CASE_TPL ( is_nez_unsigned_int__1_0,  BOOST_SIMD_UNSIGNED_TYPES)
{

  using boost::simd::is_nez;
  using boost::simd::tag::is_nez_;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef typename boost::dispatch::meta::call<is_nez_(T)>::type r_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type sr_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type ssr_t;
  typedef boost::simd::logical<T> wished_r_t;


  // return type conformity test
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl;

  // specific values tests
  NT2_TEST_EQUAL(is_nez(boost::simd::One<T>()), r_t(true));
  NT2_TEST_EQUAL(is_nez(boost::simd::Two<T>()), r_t(true));
  NT2_TEST_EQUAL(is_nez(boost::simd::Zero<T>()), r_t(false));
} // end of test for unsigned_int_
