//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 boost.simd.boolean toolbox - selsub/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of boost.simd.boolean components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 18/02/2011
///
#include <boost/simd/toolbox/boolean/include/functions/selsub.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/toolbox/predicates/include/functions/is_nez.hpp>

#include <boost/type_traits/is_same.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/toolbox/constant/constant.hpp>


NT2_TEST_CASE_TPL ( selsub_real__3_0,  BOOST_SIMD_REAL_TYPES)
{

  using boost::simd::selsub;
  using boost::simd::tag::selsub_;
  using boost::simd::logical;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef typename boost::dispatch::meta::call<selsub_(logical<T>,T,T)>::type r_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type sr_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type ssr_t;
  typedef typename boost::dispatch::meta::upgrade<T>::type u_t;
  typedef T wished_r_t;


  // return type conformity test
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl;

  // specific values tests
  NT2_TEST_EQUAL(selsub(logical<T>(T(0)),T(1),T(2)), T(1));
  NT2_TEST_EQUAL(selsub(logical<T>(boost::simd::Nan<T>()),T(1),T(2)), T(-1));
  NT2_TEST_EQUAL(selsub(logical<T>(boost::simd::Nan<T>()),boost::simd::Inf<T>(),boost::simd::Inf<T>()), boost::simd::Nan<r_t>());
  NT2_TEST_EQUAL(selsub(logical<T>(boost::simd::Nan<T>()),boost::simd::Minf<T>(),boost::simd::Minf<T>()), boost::simd::Nan<r_t>());
  NT2_TEST_EQUAL(selsub(logical<T>(boost::simd::Nan<T>()),boost::simd::Nan<T>(),boost::simd::Nan<T>()), boost::simd::Nan<r_t>());
  NT2_TEST_EQUAL(selsub(logical<T>(boost::simd::Nan<T>()),boost::simd::Zero<T>(),boost::simd::Zero<T>()), boost::simd::Zero<r_t>());
} // end of test for floating_

NT2_TEST_CASE_TPL ( selsub_signed_int__3_0,  BOOST_SIMD_INTEGRAL_SIGNED_TYPES)
{

  using boost::simd::selsub;
  using boost::simd::tag::selsub_;
  using boost::simd::logical;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef typename boost::dispatch::meta::call<selsub_(logical<T>,T,T)>::type r_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type sr_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type ssr_t;
  typedef typename boost::dispatch::meta::upgrade<T>::type u_t;
  typedef T wished_r_t;


  // return type conformity test
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl;

  // specific values tests
  NT2_TEST_EQUAL(selsub(logical<T>(T(-1)),T(4),T(2)), T(2));
  NT2_TEST_EQUAL(selsub(logical<T>(T(0)),T(4),T(2)), T(4));
  NT2_TEST_EQUAL(selsub(logical<T>(boost::simd::Zero<T>()), boost::simd::Zero<T>(), boost::simd::Zero<T>()), boost::simd::Zero<r_t>());
} // end of test for signed_int_

NT2_TEST_CASE_TPL ( selsub_unsigned_int__3_0,  BOOST_SIMD_UNSIGNED_TYPES)
{

  using boost::simd::selsub;
  using boost::simd::tag::selsub_;
  using boost::simd::logical;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef typename boost::dispatch::meta::call<selsub_(logical<T>,T,T)>::type r_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type sr_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type ssr_t;
  typedef typename boost::dispatch::meta::upgrade<T>::type u_t;
  typedef T wished_r_t;


  // return type conformity test
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl;

  // specific values tests
  NT2_TEST_EQUAL(selsub(logical<T>(T(-1)),T(4),T(2)), T(2));
  NT2_TEST_EQUAL(selsub(logical<T>(T(0)),T(4),T(2)), T(4));
  NT2_TEST_EQUAL(selsub(logical<T>(boost::simd::Zero<T>()), boost::simd::Zero<T>(), boost::simd::Zero<T>()), boost::simd::Zero<r_t>());
} // end of test for unsigned_int_
