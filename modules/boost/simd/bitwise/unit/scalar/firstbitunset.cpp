//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 boost.simd.bitwise toolbox - firstbitunset/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of boost.simd.bitwise components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 18/02/2011
/// 
#include <boost/simd/toolbox/bitwise/include/functions/firstbitunset.hpp>
#include <boost/simd/include/functions/ulpdist.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/memory/buffer.hpp>
#include <boost/simd/toolbox/constant/constant.hpp>


NT2_TEST_CASE_TPL ( firstbitunset_real__1_0,  BOOST_SIMD_REAL_TYPES)
{
  
  using boost::simd::firstbitunset;
  using boost::simd::tag::firstbitunset_;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef typename boost::dispatch::meta::call<firstbitunset_(T)>::type r_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type sr_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type ssr_t;
  typedef typename boost::dispatch::meta::upgrade<T>::type u_t;
  typedef typename boost::dispatch::meta::as_integer<T, unsigned>::type wished_r_t;


  // return type conformity test 
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl; 

  // specific values tests
  NT2_TEST_EQUAL(firstbitunset(boost::simd::Inf<T>()), boost::simd::One<r_t>());
  NT2_TEST_EQUAL(firstbitunset(boost::simd::Minf<T>()), boost::simd::One<r_t>());
  NT2_TEST_EQUAL(firstbitunset(boost::simd::Nan<T>()), boost::simd::Zero<r_t>());
  NT2_TEST_EQUAL(firstbitunset(boost::simd::Signmask<T>()), boost::simd::One<r_t>());
  NT2_TEST_EQUAL(firstbitunset(boost::simd::Zero<T>()), boost::simd::One<r_t>());
} // end of test for floating_

NT2_TEST_CASE_TPL ( firstbitunset_signed_int__1_0,  BOOST_SIMD_INTEGRAL_SIGNED_TYPES)
{
  
  using boost::simd::firstbitunset;
  using boost::simd::tag::firstbitunset_;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef typename boost::dispatch::meta::call<firstbitunset_(T)>::type r_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type sr_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type ssr_t;
  typedef typename boost::dispatch::meta::upgrade<T>::type u_t;
  typedef typename boost::dispatch::meta::as_integer<T, unsigned>::type wished_r_t;


  // return type conformity test 
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl; 

  // specific values tests
  NT2_TEST_EQUAL(firstbitunset(boost::simd::One<T>()), boost::simd::Two<r_t>());
  NT2_TEST_EQUAL(firstbitunset(boost::simd::Signmask<T>()), boost::simd::One<r_t>());
  NT2_TEST_EQUAL(firstbitunset(boost::simd::Zero<T>()), boost::simd::One<r_t>());
} // end of test for signed_int_

NT2_TEST_CASE_TPL ( firstbitunset_unsigned_int__1_0,  BOOST_SIMD_UNSIGNED_TYPES)
{
  
  using boost::simd::firstbitunset;
  using boost::simd::tag::firstbitunset_;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef typename boost::dispatch::meta::call<firstbitunset_(T)>::type r_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type sr_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type ssr_t;
  typedef typename boost::dispatch::meta::upgrade<T>::type u_t;
  typedef typename boost::dispatch::meta::as_integer<T, unsigned>::type wished_r_t;


  // return type conformity test 
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl; 

  // specific values tests
  NT2_TEST_EQUAL(firstbitunset(boost::simd::One<T>()), boost::simd::Two<r_t>());
  NT2_TEST_EQUAL(firstbitunset(boost::simd::Zero<T>()), boost::simd::One<r_t>());
} // end of test for unsigned_int_
