//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define BOOST_SIMD_UNIT_MODULE "nt2 bitwise toolbox - seladd/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of bitwise components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 18/02/2011
/// 
#include <boost/simd/toolbox/bitwise/include/seladd.hpp>
#include <boost/simd/include/functions/ulpdist.hpp>
#include <boost/simd/toolbox/predicates/include/is_nez.hpp>

#include <boost/type_traits/is_same.hpp>
#include <boost/simd/sdk/functor/meta/call.hpp>
#include <boost/simd/sdk/unit/tests.hpp>
#include <boost/simd/sdk/unit/module.hpp>
#include <boost/simd/sdk/memory/buffer.hpp>
#include <boost/simd/include/constants/real.hpp>
#include <boost/simd/include/constants/infinites.hpp>


BOOST_SIMD_TEST_CASE_TPL ( seladd_real__3_0,  BOOST_SIMD_REAL_TYPES)
{
  
  using boost::simd::seladd;
  using boost::simd::tag::seladd_;
  typedef typename boost::simd::meta::as_integer<T>::type iT;
  typedef typename boost::simd::meta::call<seladd_(T,T,T)>::type r_t;
  typedef typename boost::simd::meta::upgrade<T>::type u_t;
  typedef typename boost::result_of<boost::simd::meta::arithmetic(T,T)>::type wished_r_t;


  // return type conformity test 
  BOOST_SIMD_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl; 
  double ulpd;
  ulpd=0.0;


  // specific values tests
  BOOST_SIMD_TEST_EQUAL(seladd(T(0),T(1),T(2)), T(1));
  BOOST_SIMD_TEST_EQUAL(seladd(boost::simd::Nan<T>(),T(1),T(2)), T(3));
  BOOST_SIMD_TEST_EQUAL(seladd(boost::simd::Nan<T>(),boost::simd::Inf<T>(),boost::simd::Inf<T>()), boost::simd::Inf<r_t>());
  BOOST_SIMD_TEST_EQUAL(seladd(boost::simd::Nan<T>(),boost::simd::Minf<T>(),boost::simd::Minf<T>()), boost::simd::Minf<r_t>());
  BOOST_SIMD_TEST_EQUAL(seladd(boost::simd::Nan<T>(),boost::simd::Nan<T>(),boost::simd::Nan<T>()), boost::simd::Nan<r_t>());
  BOOST_SIMD_TEST_EQUAL(seladd(boost::simd::Nan<T>(),boost::simd::Zero<T>(),boost::simd::Zero<T>()), boost::simd::Zero<r_t>());
} // end of test for real_

BOOST_SIMD_TEST_CASE_TPL ( seladd_integer__3_0,  BOOST_SIMD_INTEGRAL_TYPES)
{
  
  using boost::simd::seladd;
  using boost::simd::tag::seladd_;
  typedef typename boost::simd::meta::as_integer<T>::type iT;
  typedef typename boost::simd::meta::call<seladd_(T,T,T)>::type r_t;
  typedef typename boost::simd::meta::upgrade<T>::type u_t;
  typedef typename boost::result_of<boost::simd::meta::arithmetic(T,T)>::type wished_r_t;


  // return type conformity test 
  BOOST_SIMD_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl; 
  double ulpd;
  ulpd=0.0;


  // specific values tests
  BOOST_SIMD_TEST_EQUAL(seladd(T(-1),T(1),T(2)), T(3));
  BOOST_SIMD_TEST_EQUAL(seladd(T(0),T(1),T(2)), T(1));
  BOOST_SIMD_TEST_EQUAL(seladd(boost::simd::Zero<T>(),boost::simd::Zero<T>(),boost::simd::Zero<T>()), boost::simd::Zero<r_t>());
} // end of test for integer_
