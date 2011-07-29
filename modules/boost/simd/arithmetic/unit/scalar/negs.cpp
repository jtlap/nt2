//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define BOOST_SIMD_UNIT_MODULE "nt2 arithmetic toolbox - negs/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of arithmetic components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created by jt the 30/11/2010
/// 
#include <boost/simd/toolbox/arithmetic/include/negs.hpp>
#include <boost/simd/include/functions/ulpdist.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <boost/simd/sdk/unit/tests.hpp>
#include <boost/simd/sdk/unit/module.hpp>
#include <boost/simd/sdk/memory/buffer.hpp>
#include <boost/simd/include/constants/real.hpp>
#include <boost/simd/include/constants/infinites.hpp>


BOOST_SIMD_TEST_CASE_TPL ( negs_real__1_0,  BOOST_SIMD_REAL_TYPES)
{
  
  using boost::simd::negs;
  using boost::simd::tag::negs_;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef typename boost::dispatch::meta::call<negs_(T)>::type r_t;
  typedef typename boost::dispatch::meta::upgrade<T>::type u_t;
  typedef T wished_r_t;


  // return type conformity test 
  BOOST_SIMD_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl; 
  double ulpd;
  ulpd=0.0;


  // specific values tests
  BOOST_SIMD_TEST_EQUAL(negs(T(100)), T(-100));
  BOOST_SIMD_TEST_EQUAL(negs(boost::simd::Inf<T>()), boost::simd::Minf<T>());
  BOOST_SIMD_TEST_EQUAL(negs(boost::simd::Minf<T>()), boost::simd::Inf<T>());
  BOOST_SIMD_TEST_EQUAL(negs(boost::simd::Mone<T>()), boost::simd::One<T>());
  BOOST_SIMD_TEST_EQUAL(negs(boost::simd::Nan<T>()), boost::simd::Nan<T>());
  BOOST_SIMD_TEST_EQUAL(negs(boost::simd::One<T>()), boost::simd::Mone<T>());
  BOOST_SIMD_TEST_EQUAL(negs(boost::simd::Valmax<T>()), boost::simd::Valmin<T>());
  BOOST_SIMD_TEST_EQUAL(negs(boost::simd::Valmin<T>()), boost::simd::Valmax<T>());
  BOOST_SIMD_TEST_EQUAL(negs(boost::simd::Zero<T>()), boost::simd::Zero<T>());
} // end of test for real_

BOOST_SIMD_TEST_CASE_TPL ( negs_signed_int__1_0,  BOOST_SIMD_INTEGRAL_SIGNED_TYPES)
{
  
  using boost::simd::negs;
  using boost::simd::tag::negs_;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef typename boost::dispatch::meta::call<negs_(T)>::type r_t;
  typedef typename boost::dispatch::meta::upgrade<T>::type u_t;
  typedef T wished_r_t;


  // return type conformity test 
  BOOST_SIMD_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl; 
  double ulpd;
  ulpd=0.0;


  // specific values tests
  BOOST_SIMD_TEST_EQUAL(negs(T(100)), T(-100));
  BOOST_SIMD_TEST_EQUAL(negs(boost::simd::Mone<T>()), boost::simd::One<T>());
  BOOST_SIMD_TEST_EQUAL(negs(boost::simd::One<T>()), boost::simd::Mone<T>());
  BOOST_SIMD_TEST_EQUAL(negs(boost::simd::Valmax<T>()), -boost::simd::Valmax<T>());
  BOOST_SIMD_TEST_EQUAL(negs(boost::simd::Valmin<T>()), boost::simd::Valmax<T>());
  BOOST_SIMD_TEST_EQUAL(negs(boost::simd::Zero<T>()), boost::simd::Zero<T>());
} // end of test for signed_int_
