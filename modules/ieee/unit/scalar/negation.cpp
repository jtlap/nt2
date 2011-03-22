//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 ieee toolbox - negation/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// Test behavior of ieee components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created by jt the 04/12/2010
/// modified by jt the 18/03/2011
#include <boost/type_traits/is_same.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/memory/buffer.hpp>
#include <nt2/sdk/constant/real.hpp>
#include <nt2/sdk/constant/infinites.hpp>
#include <nt2/include/functions/ulpdist.hpp>
#include <nt2/toolbox/ieee/include/negation.hpp>
// specific includes for arity 2 tests
#include <nt2/include/functions/sign.hpp>

NT2_TEST_CASE_TPL ( negation_real__2_0,  NT2_REAL_TYPES)
{
  
  using nt2::negation;
  using nt2::tag::negation_;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef typename nt2::meta::call<negation_(T,T)>::type r_t;
  typedef typename nt2::meta::upgrade<T>::type u_t;
  typedef typename boost::result_of<nt2::meta::arithmetic(T,T)>::type wished_r_t;


  // return type conformity test 
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl; 
  double ulpd;
  ulpd=0.0;


  // specific values tests
  NT2_TEST_EQUAL(negation(nt2::Inf<T>(), nt2::Inf<T>()), nt2::Inf<r_t>());
  NT2_TEST_EQUAL(negation(nt2::Minf<T>(), nt2::Minf<T>()), nt2::Inf<r_t>());
  NT2_TEST_EQUAL(negation(nt2::Mone<T>(), nt2::Mone<T>()), nt2::One<r_t>());
  NT2_TEST_EQUAL(negation(nt2::Nan<T>(), nt2::Nan<T>()), nt2::Nan<r_t>());
  NT2_TEST_EQUAL(negation(nt2::One<T>(), nt2::One<T>()), nt2::One<r_t>());
  NT2_TEST_EQUAL(negation(nt2::Zero<T>(), nt2::Zero<T>()), nt2::Zero<r_t>());
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
        NT2_TEST_EQUAL( nt2::negation(a0,a1),nt2::sign(a1)*a0);
     }
     
   }
} // end of test for real_

NT2_TEST_CASE_TPL ( negation_unsigned_int__2_0,  NT2_UNSIGNED_TYPES)
{
  
  using nt2::negation;
  using nt2::tag::negation_;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef typename nt2::meta::call<negation_(T,T)>::type r_t;
  typedef typename nt2::meta::upgrade<T>::type u_t;
  typedef typename boost::result_of<nt2::meta::arithmetic(T,T)>::type wished_r_t;


  // return type conformity test 
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl; 
  double ulpd;
  ulpd=0.0;


  // specific values tests
  NT2_TEST_EQUAL(negation(nt2::One<T>(), nt2::One<T>()), nt2::One<r_t>());
  NT2_TEST_EQUAL(negation(nt2::Zero<T>(), nt2::Zero<T>()), nt2::Zero<r_t>());
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
        NT2_TEST_EQUAL( nt2::negation(a0,a1),nt2::sign(a1)*a0);
     }
     
   }
} // end of test for unsigned_int_

NT2_TEST_CASE_TPL ( negation_signed_int__2_0,  NT2_INTEGRAL_SIGNED_TYPES)
{
  
  using nt2::negation;
  using nt2::tag::negation_;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef typename nt2::meta::call<negation_(T,T)>::type r_t;
  typedef typename nt2::meta::upgrade<T>::type u_t;
  typedef typename boost::result_of<nt2::meta::arithmetic(T,T)>::type wished_r_t;


  // return type conformity test 
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl; 
  double ulpd;
  ulpd=0.0;


  // specific values tests
  NT2_TEST_EQUAL(negation(nt2::Mone<T>(), nt2::Mone<T>()), nt2::One<r_t>());
  NT2_TEST_EQUAL(negation(nt2::One<T>(), nt2::One<T>()), nt2::One<r_t>());
  NT2_TEST_EQUAL(negation(nt2::Zero<T>(), nt2::Zero<T>()), nt2::Zero<r_t>());
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
        NT2_TEST_EQUAL( nt2::negation(a0,a1),nt2::sign(a1)*a0);
     }
     
   }
} // end of test for signed_int_
