//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 arithmetic toolbox - sadd/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// Test behavior of arithmetic components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created by jt the 28/11/2010
/// modified by jt the 25/03/2011
#include <boost/type_traits/is_same.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/memory/buffer.hpp>
#include <nt2/sdk/constant/real.hpp>
#include <nt2/sdk/constant/infinites.hpp>
#include <nt2/include/functions/ulpdist.hpp>
#include <nt2/toolbox/arithmetic/include/sadd.hpp>

NT2_TEST_CASE_TPL ( sadd_signed_int__2_0,  NT2_INTEGRAL_SIGNED_TYPES)
{
  
  using nt2::sadd;
  using nt2::tag::sadd_;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef typename nt2::meta::call<sadd_(T,T)>::type r_t;
  typedef typename nt2::meta::upgrade<T>::type u_t;
  typedef T wished_r_t;


  // return type conformity test 
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl; 
  double ulpd;
  ulpd=0.0;


  // specific values tests
  NT2_TEST_ULP_EQUAL(sadd(nt2::Mone<T>(), nt2::Mone<T>()), -nt2::Two<T>(), 0);
  NT2_TEST_ULP_EQUAL(sadd(nt2::One<T>(), nt2::One<T>()), nt2::Two<T>(), 0);
  NT2_TEST_ULP_EQUAL(sadd(nt2::Valmax<T>(),nt2::One<T>()), nt2::Valmax<T>(), 0);
  NT2_TEST_ULP_EQUAL(sadd(nt2::Valmin<T>(),nt2::Mone<T>()), nt2::Valmin<T>(), 0);
  NT2_TEST_ULP_EQUAL(sadd(nt2::Zero<T>(), nt2::Zero<T>()), nt2::Zero<T>(), 0);
  // random verifications
  static const uint32_t NR = NT2_NB_RANDOM_TEST;
  {
    NT2_CREATE_BUF(tab_a0,T, NR, 3*(nt2::Valmin<T>()/4), 3*(nt2::Valmax<T>()/4));
    NT2_CREATE_BUF(tab_a1,T, NR, 3*(nt2::Valmin<T>()/4), 3*(nt2::Valmax<T>()/4));
    double ulp0, ulpd ; ulpd=ulp0=0.0;
    T a0;
    T a1;
    for (uint32_t j =0; j < NR; ++j )
      {
        std::cout << "for params "
                  << "  a0 = "<< u_t(a0 = tab_a0[j])
                  << ", a1 = "<< u_t(a1 = tab_a1[j])
	          << ", sadd = "<< u_t(nt2::sadd(a0,a1))
	          << ", add  = "<< (a0+a1) 
                   << std::endl;
        NT2_TEST_ULP_EQUAL( nt2::sadd(a0,a1),nt2::sadd(a0,a1),0);
        ulp0=nt2::max(ulpd,ulp0);
     }
     std::cout << "max ulp found is: " << ulp0 << std::endl;
   }
} // end of test for signed_int_

NT2_TEST_CASE_TPL ( sadd_unsigned_int__2_0,  NT2_UNSIGNED_TYPES)
{
  
  using nt2::sadd;
  using nt2::tag::sadd_;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef typename nt2::meta::call<sadd_(T,T)>::type r_t;
  typedef typename nt2::meta::upgrade<T>::type u_t;
  typedef T wished_r_t;


  // return type conformity test 
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl; 
  double ulpd;
  ulpd=0.0;


  // specific values tests
  NT2_TEST_ULP_EQUAL(sadd(nt2::One<T>(), nt2::One<T>()), nt2::Two<T>(), 0);
  NT2_TEST_ULP_EQUAL(sadd(nt2::Valmax<T>(),nt2::One<T>()), nt2::Valmax<T>(), 0);
  NT2_TEST_ULP_EQUAL(sadd(nt2::Zero<T>(), nt2::Zero<T>()), nt2::Zero<T>(), 0);
  // random verifications
  static const uint32_t NR = NT2_NB_RANDOM_TEST;
  {
    NT2_CREATE_BUF(tab_a0,T, NR, 3*(nt2::Valmin<T>()/4), 3*(nt2::Valmax<T>()/4));
    NT2_CREATE_BUF(tab_a1,T, NR, 3*(nt2::Valmin<T>()/4), 3*(nt2::Valmax<T>()/4));
    double ulp0, ulpd ; ulpd=ulp0=0.0;
    T a0;
    T a1;
    for (uint32_t j =0; j < NR; ++j )
      {
        std::cout << "for params "
                  << "  a0 = "<< u_t(a0 = tab_a0[j])
                  << ", a1 = "<< u_t(a1 = tab_a1[j])
	          << ", sadd = "<< nt2::sadd(tab_a0[j],tab_a1[j])
	          << ", add  = "<< (tab_a0[j]+tab_a1[j]) 
                   << std::endl;
        NT2_TEST_ULP_EQUAL( nt2::sadd(a0,a1),nt2::sadd(a0,a1),0);
        ulp0=nt2::max(ulpd,ulp0);
     }
     std::cout << "max ulp found is: " << ulp0 << std::endl;
   }
  // uint64_t z1 = 9044803437091041280, z2= 18446744073709551615;
 uint64_t z1 = 9223372036854775808ull,z2 = 18446744073709551615ull; 
  std::cout << z1+z2 << std::endl;
  std::cout << nt2::sadd(z1, z2) << std::endl;
  {
    std::cout << "-----------" << std::endl;
    uint64_t  a0 , a1;
    a0 = 8686754297894607872ull, a1 = 2143419214071720192ull; 
      
      std::cout << a0 << std::endl;
    std::cout << a1 << std::endl;
    std::cout << (a0+a1) << std::endl;
    std::cout << nt2::sadd(a0, a1) << std::endl;
    std::cout << "-----------" << std::endl;
  }
  {
    int64_t  a0 , a1;
    a0 = 8686754297894607872ull, a1 = 2143419214071720192ull; 
      
      std::cout << a0 << std::endl;
    std::cout << a1 << std::endl;
    std::cout << (a0+a1) << std::endl;
    std::cout << nt2::sadd(a0, a1) << std::endl;
  }
} // end of test for unsigned_int_
