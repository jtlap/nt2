//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 predicates toolbox - is_negative/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// Test behavior of predicates components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 21/02/2011
/// modified by jt the 18/03/2011
#include <boost/type_traits/is_same.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/memory/buffer.hpp>
#include <nt2/sdk/constant/real.hpp>
#include <nt2/sdk/constant/infinites.hpp>
#include <nt2/include/functions/ulpdist.hpp>
#include <nt2/toolbox/predicates/include/is_negative.hpp>
// specific includes for arity 1 tests
#include <nt2/sdk/meta/logical.hpp>
#include <nt2/include/functions/bitofsign.hpp>

NT2_TEST_CASE_TPL ( is_negative_real__1_0,  NT2_REAL_TYPES)
{
  
  using nt2::is_negative;
  using nt2::tag::is_negative_;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef typename nt2::meta::call<is_negative_(T)>::type r_t;
  typedef typename nt2::meta::upgrade<T>::type u_t;
  typedef typename nt2::meta::logical<T>::type wished_r_t;


  // return type conformity test 
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl; 
  double ulpd;
  ulpd=0.0;


  // specific values tests
  NT2_TEST_EQUAL(is_negative(-nt2::Zero<T>()), nt2::True<r_t>());
  NT2_TEST_EQUAL(is_negative(nt2::Half<T>()), nt2::False<r_t>());
  NT2_TEST_EQUAL(is_negative(nt2::Inf<T>()), nt2::False<r_t>());
  NT2_TEST_EQUAL(is_negative(nt2::Minf<T>()), nt2::True<r_t>());
  NT2_TEST_EQUAL(is_negative(nt2::Mone<T>()), nt2::True<r_t>());
  NT2_TEST_EQUAL(is_negative(nt2::Nan<T>()), nt2::True<r_t>());
  NT2_TEST_EQUAL(is_negative(nt2::One<T>()), nt2::False<r_t>());
  NT2_TEST_EQUAL(is_negative(nt2::Quarter<T>()), nt2::False<r_t>());
  NT2_TEST_EQUAL(is_negative(nt2::Two<T>()), nt2::False<r_t>());
  NT2_TEST_EQUAL(is_negative(nt2::Zero<T>()), nt2::False<r_t>());
  // random verifications
  static const uint32_t NR = NT2_NB_RANDOM_TEST;
  {
    NT2_CREATE_BUF(tab_a0,T, NR, T(-10000), T(10000));
    double ulp0, ulpd ; ulpd=ulp0=0.0;
    T a0;
    for (uint32_t j =0; j < NR; ++j )
      {
        std::cout << "for param "
                  << "  a0 = "<< u_t(a0 = tab_a0[j])
                  << std::endl;
        NT2_TEST_EQUAL( nt2::is_negative(a0),a0<0);
     }
     
   }
} // end of test for real_

NT2_TEST_CASE_TPL ( is_negative_signed_int__1_0,  NT2_INTEGRAL_SIGNED_TYPES)
{
  
  using nt2::is_negative;
  using nt2::tag::is_negative_;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef typename nt2::meta::call<is_negative_(T)>::type r_t;
  typedef typename nt2::meta::upgrade<T>::type u_t;
  typedef typename nt2::meta::logical<T>::type wished_r_t;


  // return type conformity test 
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl; 
  double ulpd;
  ulpd=0.0;


  // specific values tests
  NT2_TEST_EQUAL(is_negative(nt2::Mone<T>()), nt2::True<r_t>());
  NT2_TEST_EQUAL(is_negative(nt2::One<T>()), nt2::False<r_t>());
  NT2_TEST_EQUAL(is_negative(nt2::Two<T>()), nt2::False<r_t>());
  NT2_TEST_EQUAL(is_negative(nt2::Zero<T>()), nt2::False<r_t>());
  // random verifications
  static const uint32_t NR = NT2_NB_RANDOM_TEST;
  {
    NT2_CREATE_BUF(tab_a0,T, NR, T(-10000), T(10000));
    double ulp0, ulpd ; ulpd=ulp0=0.0;
    T a0;
    for (uint32_t j =0; j < NR; ++j )
      {
        std::cout << "for param "
                  << "  a0 = "<< u_t(a0 = tab_a0[j])
                  << std::endl;
        NT2_TEST_EQUAL( nt2::is_negative(a0),a0<0);
     }
     
   }
} // end of test for signed_int_

NT2_TEST_CASE_TPL ( is_negative_unsigned_int__1_0,  NT2_UNSIGNED_TYPES)
{
  
  using nt2::is_negative;
  using nt2::tag::is_negative_;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef typename nt2::meta::call<is_negative_(T)>::type r_t;
  typedef typename nt2::meta::upgrade<T>::type u_t;
  typedef typename nt2::meta::logical<T>::type wished_r_t;


  // return type conformity test 
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl; 
  double ulpd;
  ulpd=0.0;


  // specific values tests
  NT2_TEST_EQUAL(is_negative(nt2::One<T>()), nt2::False<r_t>());
  NT2_TEST_EQUAL(is_negative(nt2::Two<T>()), nt2::False<r_t>());
  NT2_TEST_EQUAL(is_negative(nt2::Zero<T>()), nt2::False<r_t>());
  // random verifications
  static const uint32_t NR = NT2_NB_RANDOM_TEST;
  {
    NT2_CREATE_BUF(tab_a0,T, NR, T(-10000), T(10000));
    double ulp0, ulpd ; ulpd=ulp0=0.0;
    T a0;
    for (uint32_t j =0; j < NR; ++j )
      {
        std::cout << "for param "
                  << "  a0 = "<< u_t(a0 = tab_a0[j])
                  << std::endl;
        NT2_TEST_EQUAL( nt2::is_negative(a0),a0<0);
     }
     
   }
} // end of test for unsigned_int_
