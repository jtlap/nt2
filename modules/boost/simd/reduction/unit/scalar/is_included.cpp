//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 boost.simd.reduction toolbox - is_included/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of boost.simd.reduction components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 18/02/2011
///
#include <boost/simd/toolbox/reduction/include/functions/is_included.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/toolbox/constant/constant.hpp>
#include <boost/simd/sdk/simd/logical.hpp>


NT2_TEST_CASE_TPL ( is_included_integer__2_0,  BOOST_SIMD_INTEGRAL_TYPES)
{

  using boost::simd::is_included;
  using boost::simd::tag::is_included_;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef typename boost::dispatch::meta::call<is_included_(T,T)>::type r_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type sr_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type ssr_t;
  typedef boost::simd::logical<T> wished_r_t;

  // return type conformity test
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl;
  double ulpd;
  ulpd=0.0;


  // specific values tests
  NT2_TEST_EQUAL(is_included(boost::simd::Mone<T>(),boost::simd::Zero<T>()), ssr_t(false));
  NT2_TEST_EQUAL(is_included(boost::simd::One<T>(), boost::simd::One<T>()), ssr_t(true));
  NT2_TEST_EQUAL(is_included(boost::simd::One<T>(),boost::simd::Mone<T>()), ssr_t(true));
  NT2_TEST_EQUAL(is_included(boost::simd::One<T>(),boost::simd::Three<T>()), ssr_t(true));
  NT2_TEST_EQUAL(is_included(boost::simd::One<T>(),boost::simd::Two<T>()), ssr_t(false));
  NT2_TEST_EQUAL(is_included(boost::simd::One<T>(),boost::simd::Zero<T>()), ssr_t(false));
  NT2_TEST_EQUAL(is_included(boost::simd::Zero<T>(), boost::simd::Zero<T>()), ssr_t(true));
} // end of test for integer_
