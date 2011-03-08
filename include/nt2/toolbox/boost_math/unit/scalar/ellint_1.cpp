//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 boost_math toolbox - ellint_1/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// Test behavior of boost_math components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 07/03/2011
/// modified by jt the 07/03/2011
#include <boost/type_traits/is_same.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/no_ulp_tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/memory/buffer.hpp>
#include <nt2/sdk/constant/real.hpp>
#include <nt2/sdk/constant/infinites.hpp>
#include <nt2/include/functions/ulpdist.hpp>
#include <nt2/toolbox/boost_math/include/ellint_1.hpp>
// specific includes for arity 1 tests
#include <nt2/include/functions/ellint_1.hpp>

NT2_TEST_CASE_TPL ( ellint_1_real__1,  NT2_REAL_TYPES)
{
  
  using nt2::boost_math::ellint_1;
  using nt2::boost_math::tag::ellint_1_;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef typename nt2::meta::call<ellint_1_(T)>::type r_t;
  typedef typename nt2::meta::upgrade<T>::type u_t;
  typedef T wished_r_t;


  // return type conformity test 
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl; 
  double ulpd;

  // random verifications
  static const uint32_t NR = NT2_NB_RANDOM_TEST;
  {
    NT2_CREATE_BUF(tab_a0,T, NR, T(-10), T(10));
    double ulp0 = 0.0, ulpd = 0.0;
    T a0;
    for (int j =0; j < NR; ++j )
      {
        std::cout << "for param "
                  << "  a0 = "<< u_t(a0 = tab_a0[j])
                  << std::endl;
        NT2_TEST_EQUAL( nt2::boost_math::ellint_1(a0),nt2::ellint_1(a0));
     }
     
   }
} // end of test for real_

NT2_TEST_CASE_TPL ( ellint_1_real__2,  NT2_REAL_TYPES)
{
  
  using nt2::boost_math::ellint_1;
  using nt2::boost_math::tag::ellint_1_;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef typename nt2::meta::call<ellint_1_(T,T)>::type r_t;
  typedef typename nt2::meta::upgrade<T>::type u_t;
  typedef T wished_r_t;


  // return type conformity test 
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl; 
  double ulpd;

  // random verifications
  static const uint32_t NR = NT2_NB_RANDOM_TEST;
  {
    NT2_CREATE_BUF(tab_a0,T, NR, T(-10), T(10));
    NT2_CREATE_BUF(tab_a1,T, NR, T(-10), T(10));
    double ulp0 = 0.0, ulpd = 0.0;
    T a0;
    T a1;
    for (int j =0; j < NR; ++j )
      {
        std::cout << "for params "
                  << "  a0 = "<< u_t(a0 = tab_a0[j])
                  << ", a1 = "<< u_t(a1 = tab_a1[j])
                  << std::endl;
        NT2_TEST_EQUAL( nt2::boost_math::ellint_1(a0,a1),nt2::boost_math::ellint_1(a0,a1));
     }
     
   }
} // end of test for real_
