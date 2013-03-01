//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 boost.simd.bitwise toolbox - ilog2/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of boost.simd.bitwise components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 18/02/2011
///
#include <boost/simd/toolbox/bitwise/include/functions/ilog2.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/toolbox/constant/constant.hpp>
#include <boost/dispatch/details/ignore_unused.hpp>


NT2_TEST_CASE_TPL ( ilog2_real__1_0,  BOOST_SIMD_REAL_TYPES)
{

  using boost::simd::ilog2;
  using boost::simd::tag::ilog2_;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef typename boost::dispatch::meta::call<ilog2_(T)>::type r_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type sr_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type ssr_t;
  typedef typename boost::dispatch::meta::as_integer<T>::type wished_r_t;


  // return type conformity test
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl;

  // specific values tests
  NT2_TEST_EQUAL(ilog2(boost::simd::Two<T>()), 1);
  NT2_TEST_EQUAL(ilog2(boost::simd::Three<T>()), 1);
  NT2_TEST_EQUAL(ilog2(boost::simd::Four<T> ()), 2);
  NT2_TEST_EQUAL(ilog2(boost::simd::Pi<T> ()), 1);
  NT2_TEST_EQUAL(ilog2(boost::simd::One<T>()), 0);
} // end of test for real_

NT2_TEST_CASE_TPL ( ilog2_signed_int__1_0,  BOOST_SIMD_INTEGRAL_SIGNED_TYPES)
{

  using boost::simd::ilog2;
  using boost::simd::tag::ilog2_;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef typename boost::dispatch::meta::call<ilog2_(T)>::type r_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type sr_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type ssr_t;
  typedef typename boost::dispatch::meta::as_integer<T>::type wished_r_t;


  // return type conformity test
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl;

  // specific values tests
  NT2_TEST_EQUAL(ilog2(boost::simd::One<T>()), 0);
  NT2_TEST_EQUAL(ilog2(boost::simd::Two<T>()), 1);
} // end of test for signed_int_

 NT2_TEST_CASE_TPL ( ilog2_unsigned_int__1_0,  BOOST_SIMD_UNSIGNED_TYPES)
 {

  using boost::simd::ilog2;
  using boost::simd::tag::ilog2_;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef typename boost::dispatch::meta::call<ilog2_(T)>::type r_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type sr_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type ssr_t;
  typedef typename boost::dispatch::meta::as_integer<T, unsigned>::type wished_r_t;


  // return type conformity test
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl;

  // specific values tests
  NT2_TEST_EQUAL(ilog2(boost::simd::One<T>()), 0u);
  NT2_TEST_EQUAL(ilog2(boost::simd::Two<T>()),1u);

  T j = 1;
  for(T i=2; i < boost::simd::Valmax<T>()/2; i*= 2)
    {
      std::cout << "i = " << i << " j = " <<  j << std::endl;
      NT2_TEST_EQUAL(ilog2(T(i)),j);
      NT2_TEST_EQUAL(ilog2(T(i+1)),j);
      ++j;
    }
 } // end of test for unsigned_int_
