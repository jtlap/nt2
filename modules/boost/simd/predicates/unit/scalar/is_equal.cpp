//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 boost.simd.operator toolbox - is_equal/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of boost.simd.operator components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 18/02/2011
/// 
#include <boost/simd/toolbox/predicates/include/functions/is_equal.hpp>
#include <boost/simd/include/functions/ulpdist.hpp>
#include <boost/simd/sdk/simd/logical.hpp>

#include <boost/type_traits/is_same.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/memory/buffer.hpp>
#include <boost/simd/toolbox/constant/constant.hpp>


NT2_TEST_CASE_TPL ( is_equal_integer__2_0,  BOOST_SIMD_INTEGRAL_TYPES)
{
  
  using boost::simd::is_equal;
  using boost::simd::tag::is_equal_;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef typename boost::dispatch::meta::call<is_equal_(T,T)>::type r_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type sr_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type ssr_t;
  typedef typename boost::dispatch::meta::upgrade<T>::type u_t;
  typedef boost::simd::logical<T> wished_r_t;


  // return type conformity test 
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl; 
  double ulpd;
  ulpd=0.0;


  // specific values tests
  NT2_TEST_EQUAL(is_equal(boost::simd::One<T>(), boost::simd::One<T>()), r_t(true));
  NT2_TEST_EQUAL(is_equal(boost::simd::One<T>(),boost::simd::Zero<T>()), r_t(false));
  NT2_TEST_EQUAL(is_equal(boost::simd::Zero<T>(), boost::simd::Zero<T>()), r_t(true));
} // end of test for integer_

NT2_TEST_CASE_TPL ( is_equal_real__2_0,  BOOST_SIMD_REAL_TYPES)
{
  
  using boost::simd::is_equal;
  using boost::simd::tag::is_equal_;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef typename boost::dispatch::meta::call<is_equal_(T,T)>::type r_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type sr_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type ssr_t;
  typedef typename boost::dispatch::meta::upgrade<T>::type u_t;
  typedef boost::simd::logical<T> wished_r_t;


  // return type conformity test 
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl; 
  double ulpd;
  ulpd=0.0;


  // specific values tests
  NT2_TEST_EQUAL(is_equal(boost::simd::Inf<T>(), boost::simd::Inf<T>()), r_t(true));
  NT2_TEST_EQUAL(is_equal(boost::simd::Minf<T>(), boost::simd::Minf<T>()), r_t(true));
  NT2_TEST_EQUAL(is_equal(boost::simd::Nan<T>(), boost::simd::Nan<T>()), r_t(false));
  NT2_TEST_EQUAL(is_equal(boost::simd::One<T>(),boost::simd::Zero<T>()), r_t(false));
  NT2_TEST_EQUAL(is_equal(boost::simd::Zero<T>(), boost::simd::Zero<T>()), r_t(true));
} // end of test for floating_
