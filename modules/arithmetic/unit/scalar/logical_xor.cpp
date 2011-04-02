//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 arithmetic toolbox - logical_xor/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// Test behavior of arithmetic components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created by jt the 01/12/2010
/// modified by jt the 23/03/2011
#include <boost/type_traits/is_same.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/memory/buffer.hpp>
#include <nt2/sdk/constant/real.hpp>
#include <nt2/sdk/constant/infinites.hpp>
#include <nt2/include/functions/max.hpp>
#include <nt2/toolbox/arithmetic/include/logical_xor.hpp>

NT2_TEST_CASE_TPL ( logical_xor_real__2_0,  NT2_REAL_TYPES)
{
  
  using nt2::logical_xor;
  using nt2::tag::logical_xor_;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef typename nt2::meta::call<logical_xor_(T,T)>::type r_t;
  typedef typename nt2::meta::upgrade<T>::type u_t;
  typedef bool wished_r_t;


  // return type conformity test 
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl; 
  double ulpd;
  ulpd=0.0;


  // specific values tests
  NT2_TEST_ULP_EQUAL(logical_xor(T(0),T(1)), true, 0);
  NT2_TEST_ULP_EQUAL(logical_xor(T(3),T(0)), true, 0);
  NT2_TEST_ULP_EQUAL(logical_xor(nt2::Inf<T>(), nt2::Inf<T>()), false, 0);
  NT2_TEST_ULP_EQUAL(logical_xor(nt2::Minf<T>(), nt2::Minf<T>()), false, 0);
  NT2_TEST_ULP_EQUAL(logical_xor(nt2::Mone<T>(), nt2::Mone<T>()), false, 0);
  NT2_TEST_ULP_EQUAL(logical_xor(nt2::Nan<T>(), nt2::Nan<T>()), false, 0);
  NT2_TEST_ULP_EQUAL(logical_xor(nt2::One<T>(), nt2::One<T>()), false, 0);
  NT2_TEST_ULP_EQUAL(logical_xor(nt2::Zero<T>(), nt2::Zero<T>()), false, 0);
  // random verifications
  static const uint32_t NR = NT2_NB_RANDOM_TEST;
  {
    NT2_CREATE_BUF(tab_a0,T, NR, T(-10), T(10));
    NT2_CREATE_BUF(tab_a1,T, NR, T(-10), T(10));
    double ulp0, ulpd ; ulpd=ulp0=0.0;
    T a0;
    T a1;
    for (uint32_t j =0; j < NR; ++j )
      {
        std::cout << "for params "
                  << "  a0 = "<< u_t(a0 = tab_a0[j])
                  << ", a1 = "<< u_t(a1 = tab_a1[j])
                  << std::endl;
        NT2_TEST_ULP_EQUAL( nt2::logical_xor(a0,a1),(a0!=0)^(a1!=0),0);
        ulp0=nt2::max(ulpd,ulp0);
     }
     std::cout << "max ulp found is: " << ulp0 << std::endl;
   }
} // end of test for real_

NT2_TEST_CASE_TPL ( logical_xor_unsigned_int__2_0,  NT2_UNSIGNED_TYPES)
{
  
  using nt2::logical_xor;
  using nt2::tag::logical_xor_;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef typename nt2::meta::call<logical_xor_(T,T)>::type r_t;
  typedef typename nt2::meta::upgrade<T>::type u_t;
  typedef bool wished_r_t;


  // return type conformity test 
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl; 
  double ulpd;
  ulpd=0.0;


  // specific values tests
  NT2_TEST_ULP_EQUAL(logical_xor(nt2::One<T>(), nt2::One<T>()), false, 0);
  NT2_TEST_ULP_EQUAL(logical_xor(nt2::Zero<T>(), nt2::Zero<T>()), false, 0);
  // random verifications
  static const uint32_t NR = NT2_NB_RANDOM_TEST;
  {
    NT2_CREATE_BUF(tab_a0,T, NR, 0, 100);
    NT2_CREATE_BUF(tab_a1,T, NR, 0, 100);
    double ulp0, ulpd ; ulpd=ulp0=0.0;
    T a0;
    T a1;
    for (uint32_t j =0; j < NR; ++j )
      {
        std::cout << "for params "
                  << "  a0 = "<< u_t(a0 = tab_a0[j])
                  << ", a1 = "<< u_t(a1 = tab_a1[j])
                  << std::endl;
        NT2_TEST_ULP_EQUAL( nt2::logical_xor(a0,a1),(a0!=0)^(a1!=0),0);
        ulp0=nt2::max(ulpd,ulp0);
     }
     std::cout << "max ulp found is: " << ulp0 << std::endl;
   }
} // end of test for unsigned_int_

NT2_TEST_CASE_TPL ( logical_xor_signed_int__2_0,  NT2_INTEGRAL_SIGNED_TYPES)
{
  
  using nt2::logical_xor;
  using nt2::tag::logical_xor_;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef typename nt2::meta::call<logical_xor_(T,T)>::type r_t;
  typedef typename nt2::meta::upgrade<T>::type u_t;
  typedef bool wished_r_t;


  // return type conformity test 
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl; 
  double ulpd;
  ulpd=0.0;


  // specific values tests
  NT2_TEST_ULP_EQUAL(logical_xor(nt2::Mone<T>(), nt2::Mone<T>()), false, 0);
  NT2_TEST_ULP_EQUAL(logical_xor(nt2::One<T>(), nt2::One<T>()), false, 0);
  NT2_TEST_ULP_EQUAL(logical_xor(nt2::Zero<T>(), nt2::Zero<T>()), false, 0);
  // random verifications
  static const uint32_t NR = NT2_NB_RANDOM_TEST;
  {
    NT2_CREATE_BUF(tab_a0,T, NR, -100, 100);
    NT2_CREATE_BUF(tab_a1,T, NR, -100, 100);
    double ulp0, ulpd ; ulpd=ulp0=0.0;
    T a0;
    T a1;
    for (uint32_t j =0; j < NR; ++j )
      {
        std::cout << "for params "
                  << "  a0 = "<< u_t(a0 = tab_a0[j])
                  << ", a1 = "<< u_t(a1 = tab_a1[j])
                  << std::endl;
        NT2_TEST_ULP_EQUAL( nt2::logical_xor(a0,a1),(a0!=0)^(a1!=0),0);
        ulp0=nt2::max(ulpd,ulp0);
     }
     std::cout << "max ulp found is: " << ulp0 << std::endl;
   }
} // end of test for signed_int_
