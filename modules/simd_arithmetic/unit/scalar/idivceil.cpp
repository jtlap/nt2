//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define BOOST_SIMD_UNIT_MODULE "nt2 arithmetic toolbox - idivceil/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of arithmetic components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created by jt the 01/12/2010
/// 
#include <boost/simd/toolbox/arithmetic/include/idivceil.hpp>
#include <boost/simd/include/functions/ulpdist.hpp>
#include <boost/simd/include/functions/ceil.hpp>

#include <boost/type_traits/is_same.hpp>
#include <boost/simd/sdk/functor/meta/call.hpp>
#include <boost/simd/sdk/unit/tests.hpp>
#include <boost/simd/sdk/unit/module.hpp>
#include <boost/simd/sdk/memory/buffer.hpp>
#include <boost/simd/include/constants/real.hpp>
#include <boost/simd/include/constants/infinites.hpp>


BOOST_SIMD_TEST_CASE_TPL ( idivceil_real__2_0,  BOOST_SIMD_REAL_TYPES)
{
  
  using boost::simd::idivceil;
  using boost::simd::tag::idivceil_;
  typedef typename boost::simd::meta::as_integer<T>::type iT;
  typedef typename boost::simd::meta::call<idivceil_(T,T)>::type r_t;
  typedef typename boost::simd::meta::upgrade<T>::type u_t;
  typedef typename boost::simd::meta::as_integer<typename boost::result_of<boost::simd::meta::arithmetic(T,T)>::type>::type wished_r_t;


  // return type conformity test 
  BOOST_SIMD_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl; 
  double ulpd;
  ulpd=0.0;


  // specific values tests
  BOOST_SIMD_TEST_ULP_EQUAL(idivceil(T(4),T(3)), T(2), 0);
  BOOST_SIMD_TEST_ULP_EQUAL(idivceil(boost::simd::Inf<T>(), boost::simd::Inf<T>()), boost::simd::Zero<r_t>(), 0);
  BOOST_SIMD_TEST_ULP_EQUAL(idivceil(boost::simd::Minf<T>(), boost::simd::Minf<T>()), boost::simd::Zero<r_t>(), 0);
  BOOST_SIMD_TEST_ULP_EQUAL(idivceil(boost::simd::Mone<T>(), boost::simd::Mone<T>()), boost::simd::One<r_t>(), 0);
  BOOST_SIMD_TEST_ULP_EQUAL(idivceil(boost::simd::Mone<T>(),boost::simd::Zero<T>()), boost::simd::Minf<r_t>(), 0);
  BOOST_SIMD_TEST_ULP_EQUAL(idivceil(boost::simd::Nan<T>(), boost::simd::Nan<T>()), boost::simd::Zero<r_t>(), 0);
  BOOST_SIMD_TEST_ULP_EQUAL(idivceil(boost::simd::One<T>(), boost::simd::One<T>()), boost::simd::One<r_t>(), 0);
  BOOST_SIMD_TEST_ULP_EQUAL(idivceil(boost::simd::One<T>(),boost::simd::Zero<T>()), boost::simd::Inf<r_t>(), 0);
  BOOST_SIMD_TEST_ULP_EQUAL(idivceil(boost::simd::Zero<T>(),boost::simd::Zero<T>()), boost::simd::Zero<r_t>(), 0);
} // end of test for real_

BOOST_SIMD_TEST_CASE_TPL ( idivceil_unsigned_int__2_0,  BOOST_SIMD_UNSIGNED_TYPES)
{
  
  using boost::simd::idivceil;
  using boost::simd::tag::idivceil_;
  typedef typename boost::simd::meta::as_integer<T>::type iT;
  typedef typename boost::simd::meta::call<idivceil_(T,T)>::type r_t;
  typedef typename boost::simd::meta::upgrade<T>::type u_t;
  typedef typename boost::simd::meta::as_integer<typename boost::result_of<boost::simd::meta::arithmetic(T,T)>::type>::type wished_r_t;


  // return type conformity test 
  BOOST_SIMD_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl; 
  double ulpd;
  ulpd=0.0;


  // specific values tests
  BOOST_SIMD_TEST_ULP_EQUAL(idivceil(T(4),T(3)), T(2), 0);
  BOOST_SIMD_TEST_ULP_EQUAL(idivceil(boost::simd::One<T>(), boost::simd::One<T>()), boost::simd::One<r_t>(), 0);
} // end of test for unsigned_int_

BOOST_SIMD_TEST_CASE_TPL ( idivceil_signed_int__2_0,  BOOST_SIMD_INTEGRAL_SIGNED_TYPES)
{
  
  using boost::simd::idivceil;
  using boost::simd::tag::idivceil_;
  typedef typename boost::simd::meta::as_integer<T>::type iT;
  typedef typename boost::simd::meta::call<idivceil_(T,T)>::type r_t;
  typedef typename boost::simd::meta::upgrade<T>::type u_t;
  typedef typename boost::simd::meta::as_integer<typename boost::result_of<boost::simd::meta::arithmetic(T,T)>::type>::type wished_r_t;


  // return type conformity test 
  BOOST_SIMD_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl; 
  double ulpd;
  ulpd=0.0;


  // specific values tests
  BOOST_SIMD_TEST_ULP_EQUAL(idivceil(T(4),T(3)), T(2), 0);
  BOOST_SIMD_TEST_ULP_EQUAL(idivceil(boost::simd::Mone<T>(), boost::simd::Mone<T>()), boost::simd::One<r_t>(), 0);
  BOOST_SIMD_TEST_ULP_EQUAL(idivceil(boost::simd::One<T>(), boost::simd::One<T>()), boost::simd::One<r_t>(), 0);
} // end of test for signed_int_
