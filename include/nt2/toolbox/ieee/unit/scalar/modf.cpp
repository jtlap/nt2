//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 ieee toolbox - modf/scalar Mode"

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
#include <nt2/toolbox/ieee/include/modf.hpp>
#include <boost/fusion/tuple.hpp>
// specific includes for arity 1 tests
#include <nt2/include/functions/trunc.hpp>
#include <nt2/include/functions/frac.hpp>

NT2_TEST_CASE_TPL ( modf_real__1_0,  NT2_REAL_TYPES)
{
  
  using nt2::modf;
  using nt2::tag::modf_;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef typename nt2::meta::call<modf_(T)>::type r_t;
  typedef typename nt2::meta::upgrade<T>::type u_t;
  typedef boost::fusion::vector<T,T> wished_r_t;


  // return type conformity test 
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl; 
  double ulpd;
  ulpd=0.0;

  // random verifications
  static const uint32_t NR = NT2_NB_RANDOM_TEST;
  {
    NT2_CREATE_BUF(tab_a0,T, NR, T(-10), T(10));
    double ulp0, ulpd ; ulpd=ulp0=0.0;
    T a0;
    for (uint32_t j =0; j < NR; ++j )
      {
        std::cout << "for param "
                  << "  a0 = "<< u_t(a0 = tab_a0[j])
                  << std::endl;
        r_t r = nt2::modf(a0);
        typedef typename nt2::meta::strip<typename boost::fusion::result_of::at_c<r_t,0>::type>::type r_t0;
        typedef typename nt2::meta::strip<typename boost::fusion::result_of::at_c<r_t,1>::type>::type r_t1;
        r_t0 r0 = boost::fusion::get<0>(r);
        r_t1 r1 = boost::fusion::get<1>(r);
        NT2_TEST_EQUAL( boost::fusion::get<0>(r), nt2::frac(a0));
        NT2_TEST_EQUAL( boost::fusion::get<1>(r), nt2::trunc(a0));
     }
     
   }
} // end of test for real_

NT2_TEST_CASE_TPL ( modf_unsigned_int__1_0,  NT2_UNSIGNED_TYPES)
{
  
  using nt2::modf;
  using nt2::tag::modf_;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef typename nt2::meta::call<modf_(T)>::type r_t;
  typedef typename nt2::meta::upgrade<T>::type u_t;
  typedef boost::fusion::vector<T,T> wished_r_t;


  // return type conformity test 
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl; 
  double ulpd;
  ulpd=0.0;

  // random verifications
  static const uint32_t NR = NT2_NB_RANDOM_TEST;
  {
    NT2_CREATE_BUF(tab_a0,T, NR, 0, 100);
    double ulp0, ulpd ; ulpd=ulp0=0.0;
    T a0;
    for (uint32_t j =0; j < NR; ++j )
      {
        std::cout << "for param "
                  << "  a0 = "<< u_t(a0 = tab_a0[j])
                  << std::endl;
        r_t r = nt2::modf(a0);
        typedef typename nt2::meta::strip<typename boost::fusion::result_of::at_c<r_t,0>::type>::type r_t0;
        typedef typename nt2::meta::strip<typename boost::fusion::result_of::at_c<r_t,1>::type>::type r_t1;
        r_t0 r0 = boost::fusion::get<0>(r);
        r_t1 r1 = boost::fusion::get<1>(r);
        NT2_TEST_EQUAL( boost::fusion::get<0>(r), nt2::frac(a0));
        NT2_TEST_EQUAL( boost::fusion::get<1>(r), nt2::trunc(a0));
     }
     
   }
} // end of test for unsigned_int_

NT2_TEST_CASE_TPL ( modf_signed_int__1_0,  NT2_INTEGRAL_SIGNED_TYPES)
{
  
  using nt2::modf;
  using nt2::tag::modf_;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef typename nt2::meta::call<modf_(T)>::type r_t;
  typedef typename nt2::meta::upgrade<T>::type u_t;
  typedef boost::fusion::vector<T,T> wished_r_t;


  // return type conformity test 
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl; 
  double ulpd;
  ulpd=0.0;

  // random verifications
  static const uint32_t NR = NT2_NB_RANDOM_TEST;
  {
    NT2_CREATE_BUF(tab_a0,T, NR, -100, 100);
    double ulp0, ulpd ; ulpd=ulp0=0.0;
    T a0;
    for (uint32_t j =0; j < NR; ++j )
      {
        std::cout << "for param "
                  << "  a0 = "<< u_t(a0 = tab_a0[j])
                  << std::endl;
        r_t r = nt2::modf(a0);
        typedef typename nt2::meta::strip<typename boost::fusion::result_of::at_c<r_t,0>::type>::type r_t0;
        typedef typename nt2::meta::strip<typename boost::fusion::result_of::at_c<r_t,1>::type>::type r_t1;
        r_t0 r0 = boost::fusion::get<0>(r);
        r_t1 r1 = boost::fusion::get<1>(r);
        NT2_TEST_EQUAL( boost::fusion::get<0>(r), nt2::frac(a0));
        NT2_TEST_EQUAL( boost::fusion::get<1>(r), nt2::trunc(a0));
     }
     
   }
} // end of test for signed_int_
