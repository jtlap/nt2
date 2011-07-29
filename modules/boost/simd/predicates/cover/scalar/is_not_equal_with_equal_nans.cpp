//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define BOOST_SIMD_UNIT_MODULE "nt2 predicates toolbox - is_not_equal_with_equal_nans/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// cover test behavior of predicates components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 21/02/2011
/// 
#include <boost/simd/toolbox/predicates/include/is_not_equal_with_equal_nans.hpp>
#include <boost/simd/include/functions/ulpdist.hpp>
#include <boost/simd/include/functions/max.hpp>
#include <boost/simd/sdk/meta/logical.hpp>

#include <boost/type_traits/is_same.hpp>
#include <boost/simd/sdk/functor/meta/call.hpp>
#include <boost/simd/sdk/unit/tests.hpp>
#include <boost/simd/sdk/unit/module.hpp>
#include <boost/simd/sdk/memory/buffer.hpp>
#include <boost/simd/include/constants/real.hpp>
#include <boost/simd/include/constants/infinites.hpp>


BOOST_SIMD_TEST_CASE_TPL ( is_not_equal_with_equal_nans_real__2_0,  BOOST_SIMD_REAL_TYPES)
{
  
  using boost::simd::is_not_equal_with_equal_nans;
  using boost::simd::tag::is_not_equal_with_equal_nans_;
  typedef typename boost::simd::meta::as_integer<T>::type iT;
  typedef typename boost::simd::meta::call<is_not_equal_with_equal_nans_(T,T)>::type r_t;
  typedef typename boost::simd::meta::upgrade<T>::type u_t;
  typedef typename boost::simd::meta::logical<T>::type wished_r_t;


  // return type conformity test 
  BOOST_SIMD_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl; 
  double ulpd;
  ulpd=0.0;

  // random verifications
  static const boost::simd::uint32_t NR = BOOST_SIMD_NB_RANDOM_TEST;
  {
    BOOST_SIMD_CREATE_BUF(tab_a0,T, NR, T(-10000), T(10000));
    BOOST_SIMD_CREATE_BUF(tab_a1,T, NR, T(-10000), T(10000));
    double ulp0, ulpd ; ulpd=ulp0=0.0;
    T a0;
    T a1;
    for(boost::simd::uint32_t j =0; j < NR; ++j )
      {
        std::cout << "for params "
                  << "  a0 = "<< u_t(a0 = tab_a0[j])
                  << ", a1 = "<< u_t(a1 = tab_a1[j])
                  << std::endl;
        BOOST_SIMD_TEST_EQUAL( boost::simd::is_not_equal_with_equal_nans(a0,a1),boost::simd::is_not_equal_with_equal_nans(a0,a1));
     }
     
   }
} // end of test for real_

BOOST_SIMD_TEST_CASE_TPL ( is_not_equal_with_equal_nans_signed_int__2_0,  BOOST_SIMD_INTEGRAL_SIGNED_TYPES)
{
  
  using boost::simd::is_not_equal_with_equal_nans;
  using boost::simd::tag::is_not_equal_with_equal_nans_;
  typedef typename boost::simd::meta::as_integer<T>::type iT;
  typedef typename boost::simd::meta::call<is_not_equal_with_equal_nans_(T,T)>::type r_t;
  typedef typename boost::simd::meta::upgrade<T>::type u_t;
  typedef typename boost::simd::meta::logical<T>::type wished_r_t;


  // return type conformity test 
  BOOST_SIMD_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl; 
  double ulpd;
  ulpd=0.0;

  // random verifications
  static const boost::simd::uint32_t NR = BOOST_SIMD_NB_RANDOM_TEST;
  {
    BOOST_SIMD_CREATE_BUF(tab_a0,T, NR, T(-10000), T(10000));
    BOOST_SIMD_CREATE_BUF(tab_a1,T, NR, T(-10000), T(10000));
    double ulp0, ulpd ; ulpd=ulp0=0.0;
    T a0;
    T a1;
    for(boost::simd::uint32_t j =0; j < NR; ++j )
      {
        std::cout << "for params "
                  << "  a0 = "<< u_t(a0 = tab_a0[j])
                  << ", a1 = "<< u_t(a1 = tab_a1[j])
                  << std::endl;
        BOOST_SIMD_TEST_EQUAL( boost::simd::is_not_equal_with_equal_nans(a0,a1),boost::simd::is_not_equal_with_equal_nans(a0,a1));
     }
     
   }
} // end of test for signed_int_

BOOST_SIMD_TEST_CASE_TPL ( is_not_equal_with_equal_nans_unsigned_int__2_0,  BOOST_SIMD_UNSIGNED_TYPES)
{
  
  using boost::simd::is_not_equal_with_equal_nans;
  using boost::simd::tag::is_not_equal_with_equal_nans_;
  typedef typename boost::simd::meta::as_integer<T>::type iT;
  typedef typename boost::simd::meta::call<is_not_equal_with_equal_nans_(T,T)>::type r_t;
  typedef typename boost::simd::meta::upgrade<T>::type u_t;
  typedef typename boost::simd::meta::logical<T>::type wished_r_t;


  // return type conformity test 
  BOOST_SIMD_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl; 
  double ulpd;
  ulpd=0.0;

  // random verifications
  static const boost::simd::uint32_t NR = BOOST_SIMD_NB_RANDOM_TEST;
  {
    BOOST_SIMD_CREATE_BUF(tab_a0,T, NR, T(-10000), T(10000));
    BOOST_SIMD_CREATE_BUF(tab_a1,T, NR, T(-10000), T(10000));
    double ulp0, ulpd ; ulpd=ulp0=0.0;
    T a0;
    T a1;
    for(boost::simd::uint32_t j =0; j < NR; ++j )
      {
        std::cout << "for params "
                  << "  a0 = "<< u_t(a0 = tab_a0[j])
                  << ", a1 = "<< u_t(a1 = tab_a1[j])
                  << std::endl;
        BOOST_SIMD_TEST_EQUAL( boost::simd::is_not_equal_with_equal_nans(a0,a1),boost::simd::is_not_equal_with_equal_nans(a0,a1));
     }
     
   }
} // end of test for unsigned_int_
