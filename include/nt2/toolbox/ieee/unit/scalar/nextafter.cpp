//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 ieee toolbox - nextafter/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// Test behavior of ieee components in scalar 
//////////////////////////////////////////////////////////////////////////////
#include <nt2/sdk/functor/meta/call.hpp>
#include <boost/type_traits/is_same.hpp>
#include <nt2/toolbox/ieee/include/nextafter.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/memory/buffer.hpp>
#include <nt2/sdk/constant/real.hpp>
#include <nt2/sdk/constant/infinites.hpp>

NT2_TEST_CASE_TPL ( nextafter_float,  (float))
{
  using nt2::nextafter;
  using nt2::functors::nextafter_;
  typedef typename nt2::meta::call<nextafter_(T, T)>::type r_t;
  typedef typename nt2::meta::upgrade<T>::type u_t;
  typedef T wished_r_t;

  // return type conformity test 
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl; 

  // random comparison with other impl or formula 
  static const uint32_t NR = 100;
  {
    NT2_CREATE_BUFFER(a0,T, 100, T(-10), T(10));
    NT2_CREATE_BUFFER(a1,T, 100, T(-10), T(10));
    for (int j =0; j < NR; ++j )
      {
        std::cout << "for params "
                  << "  a0 = "<< u_t(a0 = tab_a0[j])
                  << ", a1 = "<< u_t(a1 = tab_a1[j])
                  << std::endl;
        NT2_TEST_ULP_EQUAL( nt2::nextafter(a0,a1), ::nextafterf(a0,a1),0);
     }
   }
} // end of test for float

NT2_TEST_CASE_TPL ( nextafter_double,  (double))
{
  using nt2::nextafter;
  using nt2::functors::nextafter_;
  typedef typename nt2::meta::call<nextafter_(T, T)>::type r_t;
  typedef typename nt2::meta::upgrade<T>::type u_t;
  typedef T wished_r_t;

  // return type conformity test 
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl; 

  // random comparison with other impl or formula 
  static const uint32_t NR = 100;
  {
    NT2_CREATE_BUFFER(a0,T, 100, T(-10), T(10));
    NT2_CREATE_BUFFER(a1,T, 100, T(-10), T(10));
    for (int j =0; j < NR; ++j )
      {
        std::cout << "for params "
                  << "  a0 = "<< u_t(a0 = tab_a0[j])
                  << ", a1 = "<< u_t(a1 = tab_a1[j])
                  << std::endl;
        NT2_TEST_ULP_EQUAL( nt2::nextafter(a0,a1), ::nextafter(a0,a1),0);
     }
   }
} // end of test for double

NT2_TEST_CASE_TPL ( nextafter_unsigned_int_,  NT2_UNSIGNED_TYPES)
{
  using nt2::nextafter;
  using nt2::functors::nextafter_;
  typedef typename nt2::meta::call<nextafter_(T, T)>::type r_t;
  typedef typename nt2::meta::upgrade<T>::type u_t;
  typedef T wished_r_t;

  // return type conformity test 
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl; 

  // random comparison with other impl or formula 
  static const uint32_t NR = 100;
  {
    NT2_CREATE_BUFFER(a0,T, 100, 0, 100);
    NT2_CREATE_BUFFER(a1,T, 100, 0, 100);
    for (int j =0; j < NR; ++j )
      {
        std::cout << "for params "
                  << "  a0 = "<< u_t(a0 = tab_a0[j])
                  << ", a1 = "<< u_t(a1 = tab_a1[j])
                  << std::endl;
        NT2_TEST_ULP_EQUAL( nt2::nextafter(a0,a1), (a1 == a0) ? a0 : (a1 > a0) ? a0+nt2::One<T>() : a0-nt2::One<T>(),0);
     }
   }
} // end of test for unsigned_int_

NT2_TEST_CASE_TPL ( nextafter_signed_int_,  NT2_INTEGRAL_SIGNED_TYPES)
{
  using nt2::nextafter;
  using nt2::functors::nextafter_;
  typedef typename nt2::meta::call<nextafter_(T, T)>::type r_t;
  typedef typename nt2::meta::upgrade<T>::type u_t;
  typedef T wished_r_t;

  // return type conformity test 
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl; 

  // random comparison with other impl or formula 
  static const uint32_t NR = 100;
  {
    NT2_CREATE_BUFFER(a0,T, 100, -100, 100);
    NT2_CREATE_BUFFER(a1,T, 100, -100, 100);
    for (int j =0; j < NR; ++j )
      {
        std::cout << "for params "
                  << "  a0 = "<< u_t(a0 = tab_a0[j])
                  << ", a1 = "<< u_t(a1 = tab_a1[j])
                  << std::endl;
        NT2_TEST_ULP_EQUAL( nt2::nextafter(a0,a1), (a1 == a0) ? a0 : (a1 > a0) ? a0+nt2::One<T>() : a0-nt2::One<T>(),0);
     }
   }
} // end of test for signed_int_