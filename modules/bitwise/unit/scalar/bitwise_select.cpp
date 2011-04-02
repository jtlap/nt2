//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 bitwise toolbox - bitwise_select/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// Test behavior of bitwise components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 18/02/2011
/// modified by jt the 16/03/2011
#include <boost/type_traits/is_same.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/memory/buffer.hpp>
#include <nt2/sdk/constant/real.hpp>
#include <nt2/sdk/constant/infinites.hpp>
#include <nt2/include/functions/ulpdist.hpp>
#include <nt2/toolbox/bitwise/include/bitwise_select.hpp>

NT2_TEST_CASE_TPL ( bitwise_select_real__3,  NT2_REAL_TYPES)
{
  
  using nt2::bitwise_select;
  using nt2::tag::bitwise_select_;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef typename nt2::meta::call<bitwise_select_(T,T,T)>::type r_t;
  typedef typename nt2::meta::upgrade<T>::type u_t;
  typedef T wished_r_t;


  // return type conformity test 
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl; 
  double ulpd;
  ulpd=0.0;


  // specific values tests
  NT2_TEST_EQUAL(bitwise_select(nt2::Inf<T>(), nt2::Inf<T>(), nt2::Inf<T>()), nt2::Inf<r_t>());
  NT2_TEST_EQUAL(bitwise_select(nt2::Minf<T>(), nt2::Minf<T>(), nt2::Minf<T>()), nt2::Minf<r_t>());
  NT2_TEST_EQUAL(bitwise_select(nt2::Nan<T>(), nt2::Nan<T>(), nt2::Nan<T>()), nt2::Nan<r_t>());
  NT2_TEST_EQUAL(bitwise_select(nt2::Zero<T>(), nt2::Zero<T>(), nt2::Zero<T>()), nt2::Zero<r_t>());
} // end of test for real_

NT2_TEST_CASE_TPL ( bitwise_select_integer__3,  NT2_INTEGRAL_TYPES)
{
  
  using nt2::bitwise_select;
  using nt2::tag::bitwise_select_;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef typename nt2::meta::call<bitwise_select_(T,T,T)>::type r_t;
  typedef typename nt2::meta::upgrade<T>::type u_t;
  typedef T wished_r_t;


  // return type conformity test 
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl; 
  double ulpd;
  ulpd=0.0;


  // specific values tests
  NT2_TEST_EQUAL(bitwise_select(-1,1,2), 1);
  NT2_TEST_EQUAL(bitwise_select(0,1,2), 2);
  NT2_TEST_EQUAL(bitwise_select(nt2::Zero<T>(), nt2::Zero<T>(), nt2::Zero<T>()), nt2::Zero<r_t>());
  // random verifications
  static const uint32_t NR = NT2_NB_RANDOM_TEST;
  {
    NT2_CREATE_BUF(tab_a0,T, NR, T(-10000), T(10000));
    NT2_CREATE_BUF(tab_a1,T, NR, T(-10000), T(10000));
    NT2_CREATE_BUF(tab_a2,T, NR, T(-10000), T(10000));
    double ulp0, ulpd ; ulpd=ulp0=0.0;
    T a0;
    T a1;
    T a2;
    for (uint32_t j =0; j < NR; ++j )
      {
        std::cout << "for params "
                  << "  a0 = "<< u_t(a0 = tab_a0[j])
                  << ", a1 = "<< u_t(a1 = tab_a1[j])
                  << ", a2 = "<< u_t(a2 = tab_a2[j])
                  << std::endl;
        NT2_TEST_EQUAL( nt2::bitwise_select(a0,a1,a2),(a1&a0)|(a2&(~a0)));
     }
     
   }
} // end of test for integer_
