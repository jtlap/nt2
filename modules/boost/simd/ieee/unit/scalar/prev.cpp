//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 boost.simd.ieee toolbox - prev/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of boost.simd.ieee components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created by jt the 04/12/2010
///
#include <boost/simd/toolbox/ieee/include/functions/prev.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/include/functions/ulpdist.hpp>
#include <boost/simd/include/functions/predecessor.hpp>
#include <boost/simd/include/constants/eps_related.hpp>

#include <boost/type_traits/is_same.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/toolbox/constant/constant.hpp>


NT2_TEST_CASE_TPL ( prev_real__1_0,  BOOST_SIMD_REAL_TYPES)
{

  using boost::simd::prev;
  using boost::simd::tag::prev_;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef typename boost::dispatch::meta::call<prev_(T)>::type r_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type sr_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type ssr_t;
  typedef typename boost::dispatch::meta::upgrade<T>::type u_t;
  typedef T wished_r_t;


  // return type conformity test
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl;

  // specific values tests
  NT2_TEST_EQUAL(prev(boost::simd::Inf<T>()), boost::simd::Valmax<r_t>());
  NT2_TEST_EQUAL(prev(boost::simd::Minf<T>()), boost::simd::Minf<r_t>());
  NT2_TEST_EQUAL(prev(boost::simd::Mone<T>()), boost::simd::Mone<r_t>()-boost::simd::Eps<r_t>());
  NT2_TEST_EQUAL(prev(boost::simd::Nan<T>()), boost::simd::Nan<r_t>());
  NT2_TEST_EQUAL(prev(boost::simd::One<T>()), boost::simd::One<r_t>()-boost::simd::Eps<r_t>()/2);
  NT2_TEST_EQUAL(prev(boost::simd::Valmin<T>()), boost::simd::Minf<r_t>());
  NT2_TEST_EQUAL(prev(boost::simd::Zero<T>()), -boost::simd::Bitincrement<T>());
} // end of test for floating_

NT2_TEST_CASE_TPL ( prev_unsigned_int__1_0,  BOOST_SIMD_UNSIGNED_TYPES)
{

  using boost::simd::prev;
  using boost::simd::tag::prev_;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef typename boost::dispatch::meta::call<prev_(T)>::type r_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type sr_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type ssr_t;
  typedef typename boost::dispatch::meta::upgrade<T>::type u_t;
  typedef T wished_r_t;


  // return type conformity test
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl;

  // specific values tests
  NT2_TEST_EQUAL(prev(boost::simd::One<T>()), boost::simd::Zero<r_t>());
  NT2_TEST_EQUAL(prev(boost::simd::Valmin<T>()), boost::simd::Valmin<r_t>());
  NT2_TEST_EQUAL(prev(boost::simd::Zero<T>()), boost::simd::Zero<r_t>());
} // end of test for unsigned_int_

NT2_TEST_CASE_TPL ( prev_signed_int__1_0,  BOOST_SIMD_INTEGRAL_SIGNED_TYPES)
{

  using boost::simd::prev;
  using boost::simd::tag::prev_;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef typename boost::dispatch::meta::call<prev_(T)>::type r_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type sr_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type ssr_t;
  typedef typename boost::dispatch::meta::upgrade<T>::type u_t;
  typedef T wished_r_t;


  // return type conformity test
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl;

  // specific values tests
  NT2_TEST_EQUAL(prev(boost::simd::Mone<T>()), -boost::simd::Two<r_t>());
  NT2_TEST_EQUAL(prev(boost::simd::One<T>()), boost::simd::Zero<r_t>());
  NT2_TEST_EQUAL(prev(boost::simd::Valmin<T>()), boost::simd::Valmin<r_t>());
  NT2_TEST_EQUAL(prev(boost::simd::Zero<T>()), boost::simd::Mone<r_t>());
} // end of test for signed_int_
