//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 boost.simd.operator toolbox - logical_not/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of boost.simd.operator components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 18/02/2011
/// 
#include <boost/simd/toolbox/operator/include/functions/logical_not.hpp>
#include <boost/simd/sdk/simd/logical.hpp>

#include <boost/type_traits/is_same.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/memory/buffer.hpp>
#include <boost/simd/toolbox/constant/constant.hpp>
#include <boost/dispatch/details/ignore_unused.hpp>


NT2_TEST_CASE_TPL ( logical_not_integer__1_0,  BOOST_SIMD_INTEGRAL_TYPES)
{
  
  using boost::simd::logical_not;
  using boost::simd::tag::logical_not_;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef typename boost::dispatch::meta::call<logical_not_(T)>::type r_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type sr_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type ssr_t;
  typedef typename boost::dispatch::meta::upgrade<T>::type u_t;
  typedef typename boost::simd::meta::as_logical<T>::type wished_r_t;


  // return type conformity test 
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl; 

  // specific values tests
  NT2_TEST_EQUAL(logical_not(boost::simd::False<T>()), boost::simd::True<r_t>());
  NT2_TEST_EQUAL(logical_not(boost::simd::True<T>()), boost::simd::False<r_t>());
} // end of test for integer_

NT2_TEST_CASE_TPL ( logical_not_real__1_0,  BOOST_SIMD_REAL_TYPES)
{
  
  using boost::simd::logical_not;
  using boost::simd::tag::logical_not_;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef typename boost::dispatch::meta::call<logical_not_(T)>::type r_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type sr_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type ssr_t;
  typedef typename boost::dispatch::meta::upgrade<T>::type u_t;
  typedef typename boost::simd::meta::as_logical<T>::type wished_r_t;


  // return type conformity test 
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl; 

  // specific values tests
  NT2_TEST_EQUAL(logical_not(boost::simd::False<T>()), boost::simd::True<r_t>());
  NT2_TEST_EQUAL(logical_not(boost::simd::True<T>()), boost::simd::False<r_t>());
} // end of test for real_
