//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 boost.simd.arithmetic toolbox - fast_hypot/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of boost.simd.arithmetic components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created by jt the 01/12/2010
///
#include <boost/simd/toolbox/arithmetic/include/functions/fast_hypot.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/toolbox/arithmetic/include/functions/hypot.hpp>

#include <boost/type_traits/is_same.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/toolbox/constant/constant.hpp>


NT2_TEST_CASE_TPL ( fast_hypot_real__2_0,  BOOST_SIMD_REAL_TYPES)
{

  using boost::simd::fast_hypot;
  using boost::simd::tag::fast_hypot_;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef typename boost::dispatch::meta::call<fast_hypot_(T,T)>::type r_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type sr_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type ssr_t;
  typedef typename boost::dispatch::meta::as_floating<T,T>::type wished_r_t;


  // return type conformity test
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl;

  // specific values tests
  NT2_TEST_ULP_EQUAL(fast_hypot(boost::simd::Inf<T>(), boost::simd::Inf<T>()), boost::simd::Inf<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(fast_hypot(boost::simd::Minf<T>(), boost::simd::Minf<T>()), boost::simd::Inf<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(fast_hypot(boost::simd::Mone<T>(), boost::simd::Mone<T>()), boost::simd::Sqrt_2<r_t>(), 0.5);
  NT2_TEST_ULP_EQUAL(fast_hypot(boost::simd::Nan<T>(), boost::simd::Nan<T>()), boost::simd::Nan<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(fast_hypot(boost::simd::One<T>(), boost::simd::One<T>()), boost::simd::Sqrt_2<r_t>(), 0.5);
  NT2_TEST_ULP_EQUAL(fast_hypot(boost::simd::Zero<T>(), boost::simd::Zero<T>()), boost::simd::Zero<T>(), 0);
} // end of test for floating_

NT2_TEST_CASE_TPL ( fast_hypot_unsigned_int__2_0,  BOOST_SIMD_UNSIGNED_TYPES)
{

  using boost::simd::fast_hypot;
  using boost::simd::tag::fast_hypot_;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef typename boost::dispatch::meta::call<fast_hypot_(T,T)>::type r_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type sr_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type ssr_t;
  typedef typename boost::dispatch::meta::as_floating<T,T>::type wished_r_t;


  // return type conformity test
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl;

  // specific values tests
  NT2_TEST_ULP_EQUAL(fast_hypot(boost::simd::One<T>(), boost::simd::One<T>()), boost::simd::Sqrt_2<r_t>(), 0.5);
  NT2_TEST_ULP_EQUAL(fast_hypot(boost::simd::Zero<T>(), boost::simd::Zero<T>()), boost::simd::Zero<r_t>(), 0);
} // end of test for unsigned_int_

NT2_TEST_CASE_TPL ( fast_hypot_signed_int__2_0,  BOOST_SIMD_INTEGRAL_SIGNED_TYPES)
{

  using boost::simd::fast_hypot;
  using boost::simd::tag::fast_hypot_;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef typename boost::dispatch::meta::call<fast_hypot_(T,T)>::type r_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type sr_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type ssr_t;
  typedef typename boost::dispatch::meta::as_floating<T,T>::type wished_r_t;


  // return type conformity test
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl;

  // specific values tests
  NT2_TEST_ULP_EQUAL(fast_hypot(boost::simd::Mone<T>(), boost::simd::Mone<T>()), boost::simd::Sqrt_2<r_t>(), 0.5);
  NT2_TEST_ULP_EQUAL(fast_hypot(boost::simd::One<T>(), boost::simd::One<T>()), boost::simd::Sqrt_2<r_t>(), 0.5);
  NT2_TEST_ULP_EQUAL(fast_hypot(boost::simd::Zero<T>(), boost::simd::Zero<T>()), boost::simd::Zero<r_t>(), 0);
} // end of test for signed_int_
