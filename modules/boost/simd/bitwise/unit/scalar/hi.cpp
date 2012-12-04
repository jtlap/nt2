//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 boost.simd.bitwise toolbox - hi/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of boost.simd.bitwise components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 18/02/2011
///
#include <boost/simd/toolbox/bitwise/include/functions/hi.hpp>
#include <boost/simd/include/functions/ulpdist.hpp>
#include <boost/dispatch/meta/downgrade.hpp>

#include <boost/type_traits/is_same.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/toolbox/constant/constant.hpp>


NT2_TEST_CASE_TPL ( hi_real__1_0,  BOOST_SIMD_REAL_TYPES)
{

  using boost::simd::hi;
  using boost::simd::tag::hi_;
  typedef typename boost::dispatch::meta::as_integer<T,unsigned>::type ir_t;
  typedef typename boost::dispatch::meta::downgrade<ir_t>::type dtype;
  typedef typename boost::simd::meta::scalar_of<ir_t>::type scal;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef typename boost::dispatch::meta::call<hi_(T)>::type r_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type sr_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type ssr_t;
  typedef typename boost::dispatch::meta::upgrade<T>::type u_t;
  typedef typename boost::dispatch::meta::downgrade<ir_t>::type wished_r_t;


  // return type conformity test
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl;

  // specific values tests
  NT2_TEST_EQUAL(hi(boost::simd::Nan<T>()), boost::simd::Mone<dtype>());
  NT2_TEST_EQUAL(hi(boost::simd::Zero<T>()), boost::simd::Zero<dtype>());
} // end of test for floating_

NT2_TEST_CASE_TPL ( hi_int64__1_0,  BOOST_SIMD_INT_64_TYPES)
{

  using boost::simd::hi;
  using boost::simd::tag::hi_;
  typedef typename boost::dispatch::meta::as_integer<T,unsigned>::type ir_t;
  typedef typename boost::dispatch::meta::downgrade<ir_t>::type dtype;
  typedef typename boost::simd::meta::scalar_of<ir_t>::type scal;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef typename boost::dispatch::meta::call<hi_(T)>::type r_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type sr_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type ssr_t;
  typedef typename boost::dispatch::meta::upgrade<T>::type u_t;
  typedef typename boost::dispatch::meta::downgrade<ir_t>::type wished_r_t;


  // return type conformity test
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl;

  // specific values tests
  NT2_TEST_EQUAL(hi(boost::simd::One<T>()), boost::simd::Zero<dtype>());
  NT2_TEST_EQUAL(hi(boost::simd::Zero<T>()), boost::simd::Zero<dtype>());
} // end of test for int64_

NT2_TEST_CASE_TPL ( hi_int32__1_0,  BOOST_SIMD_INT_32_TYPES)
{

  using boost::simd::hi;
  using boost::simd::tag::hi_;
  typedef typename boost::dispatch::meta::as_integer<T,unsigned>::type ir_t;
  typedef typename boost::dispatch::meta::downgrade<ir_t>::type dtype;
  typedef typename boost::simd::meta::scalar_of<ir_t>::type scal;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef typename boost::dispatch::meta::call<hi_(T)>::type r_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type sr_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type ssr_t;
  typedef typename boost::dispatch::meta::upgrade<T>::type u_t;
  typedef typename boost::dispatch::meta::downgrade<ir_t>::type wished_r_t;


  // return type conformity test
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl;

  // specific values tests
  NT2_TEST_EQUAL(hi(boost::simd::One<T>()), boost::simd::Zero<dtype>());
  NT2_TEST_EQUAL(hi(boost::simd::Zero<T>()), boost::simd::Zero<dtype>());
} // end of test for int32_

NT2_TEST_CASE_TPL ( hi_int16__1_0,  BOOST_SIMD_INT_16_TYPES)
{

  using boost::simd::hi;
  using boost::simd::tag::hi_;
  typedef typename boost::dispatch::meta::as_integer<T,unsigned>::type ir_t;
  typedef typename boost::dispatch::meta::downgrade<ir_t>::type dtype;
  typedef typename boost::simd::meta::scalar_of<ir_t>::type scal;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef typename boost::dispatch::meta::call<hi_(T)>::type r_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type sr_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type ssr_t;
  typedef typename boost::dispatch::meta::upgrade<T>::type u_t;
  typedef typename boost::dispatch::meta::downgrade<ir_t>::type wished_r_t;


  // return type conformity test
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl;

  // specific values tests
  NT2_TEST_EQUAL(hi(boost::simd::One<T>()), boost::simd::Zero<dtype>());
  NT2_TEST_EQUAL(hi(boost::simd::Zero<T>()), boost::simd::Zero<dtype>());
} // end of test for int16_
