//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 arithmetic toolbox - round/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// Test behavior of arithmetic components in scalar mode
//////////////////////////////////////////////////////////////////////////////
#include <boost/type_traits/is_same.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/memory/buffer.hpp>
#include <nt2/sdk/constant/real.hpp>
#include <nt2/sdk/constant/infinites.hpp>
#include <nt2/toolbox/arithmetic/include/round.hpp>

NT2_TEST_CASE_TPL ( round_real__1,  NT2_REAL_TYPES)
{
  using nt2::round;
  using nt2::tag::round_;
  typedef typename nt2::meta::call<round_(T)>::type r_t;
  typedef typename nt2::meta::upgrade<T>::type u_t;
  typedef T wished_r_t;

  // return type conformity test 
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl; 


  // specific values tests
  NT2_TEST_ULP_EQUAL(  round(T(1.4)), 1, 0);
  NT2_TEST_ULP_EQUAL(  round(T(1.5)), 2, 0);
  NT2_TEST_ULP_EQUAL(  round(T(1.6)), 2, 0);
  NT2_TEST_ULP_EQUAL(  round(T(2.5)), 2, 0);
  NT2_TEST_ULP_EQUAL(  round(nt2::Half<T>()), nt2::Zero<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(  round(nt2::Inf<T>()), nt2::Inf<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(  round(nt2::Mhalf<T>()), nt2::Zero<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(  round(nt2::Minf<T>()), nt2::Minf<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(  round(nt2::Mone<T>()), nt2::Mone<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(  round(nt2::Nan<T>()), nt2::Nan<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(  round(nt2::One<T>()), nt2::One<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(  round(nt2::Zero<T>()), nt2::Zero<r_t>(), 0);
  // random verifications
  static const uint32_t NR = 100;
  {
    NT2_CREATE_BUFFER(a0,T, 100, T(-10), T(10));
    for (int j =0; j < NR; ++j )
      {
        std::cout << "for param "
                  << "  a0 = "<< u_t(a0 = tab_a0[j])
                  << std::endl;
        NT2_TEST_ULP_EQUAL( nt2::round(a0),::round(a0),0);
     }
   }
} // end of test for real_

NT2_TEST_CASE_TPL ( round_unsigned_int__1,  NT2_UNSIGNED_TYPES)
{
  using nt2::round;
  using nt2::tag::round_;
  typedef typename nt2::meta::call<round_(T)>::type r_t;
  typedef typename nt2::meta::upgrade<T>::type u_t;
  typedef T wished_r_t;

  // return type conformity test 
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl; 


  // specific values tests
  NT2_TEST_ULP_EQUAL(  round(nt2::One<T>()), nt2::One<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(  round(nt2::Zero<T>()), nt2::Zero<r_t>(), 0);
  // random verifications
  static const uint32_t NR = 100;
  {
    NT2_CREATE_BUFFER(a0,T, 100, 0, 100);
    for (int j =0; j < NR; ++j )
      {
        std::cout << "for param "
                  << "  a0 = "<< u_t(a0 = tab_a0[j])
                  << std::endl;
        NT2_TEST_ULP_EQUAL( nt2::round(a0),a0,0);
     }
   }
} // end of test for unsigned_int_

NT2_TEST_CASE_TPL ( round_signed_int__1,  NT2_INTEGRAL_SIGNED_TYPES)
{
  using nt2::round;
  using nt2::tag::round_;
  typedef typename nt2::meta::call<round_(T)>::type r_t;
  typedef typename nt2::meta::upgrade<T>::type u_t;
  typedef T wished_r_t;

  // return type conformity test 
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl; 


  // specific values tests
  NT2_TEST_ULP_EQUAL(  round(nt2::Mone<T>()), nt2::Mone<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(  round(nt2::One<T>()), nt2::One<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(  round(nt2::Zero<T>()), nt2::Zero<T>(), 0);
  // random verifications
  static const uint32_t NR = 100;
  {
    NT2_CREATE_BUFFER(a0,T, 100, -100, 100);
    for (int j =0; j < NR; ++j )
      {
        std::cout << "for param "
                  << "  a0 = "<< u_t(a0 = tab_a0[j])
                  << std::endl;
        NT2_TEST_ULP_EQUAL( nt2::round(a0),a0,0);
     }
   }
} // end of test for signed_int_