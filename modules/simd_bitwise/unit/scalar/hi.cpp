//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define BOOST_SIMD_UNIT_MODULE "nt2 bitwise toolbox - hi/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of bitwise components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 18/02/2011
/// 
#include <boost/simd/toolbox/bitwise/include/hi.hpp>
#include <boost/simd/include/functions/ulpdist.hpp>
#include <boost/simd/sdk/meta/downgrade.hpp>

#include <boost/type_traits/is_same.hpp>
#include <boost/simd/sdk/functor/meta/call.hpp>
#include <boost/simd/sdk/unit/tests.hpp>
#include <boost/simd/sdk/unit/module.hpp>
#include <boost/simd/sdk/memory/buffer.hpp>
#include <boost/simd/include/constants/real.hpp>
#include <boost/simd/include/constants/infinites.hpp>


BOOST_SIMD_TEST_CASE_TPL ( hi_real__1_0,  BOOST_SIMD_REAL_TYPES)
{
  
  using boost::simd::hi;
  using boost::simd::tag::hi_;
  typedef typename boost::simd::meta::as_integer<T,unsigned>::type ir_t;
  typedef typename boost::simd::meta::as_integer<T>::type iT;
  typedef typename boost::simd::meta::call<hi_(T)>::type r_t;
  typedef typename boost::simd::meta::upgrade<T>::type u_t;
  typedef typename boost::simd::meta::downgrade<ir_t>::type wished_r_t;


  // return type conformity test 
  BOOST_SIMD_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl; 
  double ulpd;
  ulpd=0.0;


  // specific values tests
  BOOST_SIMD_TEST_EQUAL(hi(boost::simd::Nan<T>()), boost::simd::Mone<r_t>());
  BOOST_SIMD_TEST_EQUAL(hi(boost::simd::Zero<T>()), boost::simd::Zero<r_t>());
} // end of test for real_

BOOST_SIMD_TEST_CASE_TPL ( hi_int64__1_0,  (boost::simd::int64_t)(boost::simd::uint64_t))
{
  
  using boost::simd::hi;
  using boost::simd::tag::hi_;
  typedef typename boost::simd::meta::as_integer<T,unsigned>::type ir_t;
  typedef typename boost::simd::meta::as_integer<T>::type iT;
  typedef typename boost::simd::meta::call<hi_(T)>::type r_t;
  typedef typename boost::simd::meta::upgrade<T>::type u_t;
  typedef typename boost::simd::meta::downgrade<ir_t>::type wished_r_t;


  // return type conformity test 
  BOOST_SIMD_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl; 
  double ulpd;
  ulpd=0.0;


  // specific values tests
  BOOST_SIMD_TEST_EQUAL(hi(boost::simd::One<T>()), boost::simd::Zero<r_t>());
  BOOST_SIMD_TEST_EQUAL(hi(boost::simd::Zero<T>()), boost::simd::Zero<r_t>());
} // end of test for int64_

BOOST_SIMD_TEST_CASE_TPL ( hi_int32__1_0,  (boost::simd::int32_t)(boost::simd::uint32_t))
{
  
  using boost::simd::hi;
  using boost::simd::tag::hi_;
  typedef typename boost::simd::meta::as_integer<T,unsigned>::type ir_t;
  typedef typename boost::simd::meta::as_integer<T>::type iT;
  typedef typename boost::simd::meta::call<hi_(T)>::type r_t;
  typedef typename boost::simd::meta::upgrade<T>::type u_t;
  typedef typename boost::simd::meta::downgrade<ir_t>::type wished_r_t;


  // return type conformity test 
  BOOST_SIMD_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl; 
  double ulpd;
  ulpd=0.0;


  // specific values tests
  BOOST_SIMD_TEST_EQUAL(hi(boost::simd::One<T>()), boost::simd::Zero<r_t>());
  BOOST_SIMD_TEST_EQUAL(hi(boost::simd::Zero<T>()), boost::simd::Zero<r_t>());
} // end of test for int32_

BOOST_SIMD_TEST_CASE_TPL ( hi_int16__1_0,  (boost::simd::int16_t)(boost::simd::uint16_t))
{
  
  using boost::simd::hi;
  using boost::simd::tag::hi_;
  typedef typename boost::simd::meta::as_integer<T,unsigned>::type ir_t;
  typedef typename boost::simd::meta::as_integer<T>::type iT;
  typedef typename boost::simd::meta::call<hi_(T)>::type r_t;
  typedef typename boost::simd::meta::upgrade<T>::type u_t;
  typedef typename boost::simd::meta::downgrade<ir_t>::type wished_r_t;


  // return type conformity test 
  BOOST_SIMD_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl; 
  double ulpd;
  ulpd=0.0;


  // specific values tests
  BOOST_SIMD_TEST_EQUAL(hi(boost::simd::One<T>()), boost::simd::Zero<r_t>());
  BOOST_SIMD_TEST_EQUAL(hi(boost::simd::Zero<T>()), boost::simd::Zero<r_t>());
} // end of test for int16_
