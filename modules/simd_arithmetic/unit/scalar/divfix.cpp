//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define BOOST_SIMD_UNIT_MODULE "nt2 arithmetic toolbox - divfix/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of arithmetic components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created by jt the 01/12/2010
/// 
#include <boost/simd/toolbox/arithmetic/include/divfix.hpp>
#include <boost/simd/include/functions/ulpdist.hpp>
#include <boost/simd/include/functions/trunc.hpp>

#include <boost/type_traits/is_same.hpp>
#include <boost/simd/sdk/functor/meta/call.hpp>
#include <boost/simd/sdk/unit/tests.hpp>
#include <boost/simd/sdk/unit/module.hpp>
#include <boost/simd/sdk/memory/buffer.hpp>
#include <boost/simd/include/constants/real.hpp>
#include <boost/simd/include/constants/infinites.hpp>


BOOST_SIMD_TEST_CASE_TPL ( divfix_real__2_0,  BOOST_SIMD_REAL_TYPES)
{
  
  using boost::simd::divfix;
  using boost::simd::tag::divfix_;
  typedef typename boost::simd::meta::as_integer<T>::type iT;
  typedef typename boost::simd::meta::call<divfix_(T,T)>::type r_t;
  typedef typename boost::simd::meta::upgrade<T>::type u_t;
  typedef typename boost::result_of<boost::simd::meta::arithmetic(T,T)>::type wished_r_t;


  // return type conformity test 
  BOOST_SIMD_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl; 
  double ulpd;
  ulpd=0.0;


  // specific values tests
  BOOST_SIMD_TEST_ULP_EQUAL(divfix(T(4),T(3)), T(1), 0);
  BOOST_SIMD_TEST_ULP_EQUAL(divfix(boost::simd::Inf<T>(), boost::simd::Inf<T>()), boost::simd::Nan<T>(), 0);
  BOOST_SIMD_TEST_ULP_EQUAL(divfix(boost::simd::Minf<T>(), boost::simd::Minf<T>()), boost::simd::Nan<T>(), 0);
  BOOST_SIMD_TEST_ULP_EQUAL(divfix(boost::simd::Mone<T>(), boost::simd::Mone<T>()), boost::simd::One<T>(), 0);
  BOOST_SIMD_TEST_ULP_EQUAL(divfix(boost::simd::Nan<T>(), boost::simd::Nan<T>()), boost::simd::Nan<T>(), 0);
  BOOST_SIMD_TEST_ULP_EQUAL(divfix(boost::simd::One<T>(), boost::simd::One<T>()), boost::simd::One<T>(), 0);
  BOOST_SIMD_TEST_ULP_EQUAL(divfix(boost::simd::Zero<T>(), boost::simd::Zero<T>()), boost::simd::Nan<T>(), 0);
} // end of test for real_

BOOST_SIMD_TEST_CASE_TPL ( divfix_unsigned_int__2_0,  BOOST_SIMD_UNSIGNED_TYPES)
{
  
  using boost::simd::divfix;
  using boost::simd::tag::divfix_;
  typedef typename boost::simd::meta::as_integer<T>::type iT;
  typedef typename boost::simd::meta::call<divfix_(T,T)>::type r_t;
  typedef typename boost::simd::meta::upgrade<T>::type u_t;
  typedef typename boost::result_of<boost::simd::meta::arithmetic(T,T)>::type wished_r_t;


  // return type conformity test 
  BOOST_SIMD_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl; 
  double ulpd;
  ulpd=0.0;


  // specific values tests
  BOOST_SIMD_TEST_ULP_EQUAL(divfix(T(4),T(3)), T(1), 0);
  BOOST_SIMD_TEST_ULP_EQUAL(divfix(boost::simd::One<T>(), boost::simd::One<T>()), boost::simd::One<T>(), 0);
  BOOST_SIMD_TEST_ULP_EQUAL(divfix(boost::simd::Zero<T>(), boost::simd::Zero<T>()), boost::simd::Zero<T>(), 0);
} // end of test for unsigned_int_

BOOST_SIMD_TEST_CASE_TPL ( divfix_signed_int__2_0,  BOOST_SIMD_INTEGRAL_SIGNED_TYPES)
{
  
  using boost::simd::divfix;
  using boost::simd::tag::divfix_;
  typedef typename boost::simd::meta::as_integer<T>::type iT;
  typedef typename boost::simd::meta::call<divfix_(T,T)>::type r_t;
  typedef typename boost::simd::meta::upgrade<T>::type u_t;
  typedef typename boost::result_of<boost::simd::meta::arithmetic(T,T)>::type wished_r_t;


  // return type conformity test 
  BOOST_SIMD_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl; 
  double ulpd;
  ulpd=0.0;


  // specific values tests
  BOOST_SIMD_TEST_ULP_EQUAL(divfix(T(4),T(3)), T(1), 0);
  BOOST_SIMD_TEST_ULP_EQUAL(divfix(boost::simd::Mone<T>(), boost::simd::Mone<T>()), boost::simd::One<T>(), 0);
  BOOST_SIMD_TEST_ULP_EQUAL(divfix(boost::simd::One<T>(), boost::simd::One<T>()), boost::simd::One<T>(), 0);
  BOOST_SIMD_TEST_ULP_EQUAL(divfix(boost::simd::Zero<T>(), boost::simd::Zero<T>()), boost::simd::Zero<T>(), 0);
} // end of test for signed_int_
