//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 boolean toolbox - if_one_else_zero/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// cover test behavior of boolean components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 21/02/2011
///
#include <nt2/boolean/include/functions/if_one_else_zero.hpp>
#include <nt2/include/functions/max.hpp>
#include <nt2/sdk/simd/logical.hpp>
#include <nt2/sdk/meta/upgrade.hpp>
#include <boost/simd/sdk/simd/io.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>



NT2_TEST_CASE_TPL ( if_one_else_zero_real__1_0,  NT2_REAL_TYPES)
{

  using nt2::if_one_else_zero;
  using nt2::tag::if_one_else_zero_;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef typename nt2::meta::call<if_one_else_zero_(T)>::type r_t;
  typedef typename nt2::meta::scalar_of<r_t>::type ssr_t;
  typedef typename nt2::meta::upgrade<T>::type u_t;
  typedef T wished_r_t;


  // return type conformity test
  NT2_TEST_TYPE_IS( r_t, wished_r_t );

  // random verifications
  static const nt2::uint32_t NR = NT2_NB_RANDOM_TEST;
  {
    NT2_CREATE_BUF(tab_a0,T, NR, T(-10000), T(10000));
    double ulp0, ulpd ; ulpd=ulp0=0.0;
    T a0;
    for(nt2::uint32_t j =0; j < NR; ++j )
      {
        std::cout << "for param "
                  << "  a0 = "<< u_t(a0 = tab_a0[j])
                  << std::endl;
        NT2_TEST_EQUAL( nt2::if_one_else_zero(a0),r_t(a0!=0));
     }

   }
} // end of test for floating_

NT2_TEST_CASE_TPL ( if_one_else_zero_signed_int__1_0,  NT2_INTEGRAL_SIGNED_TYPES)
{

  using nt2::if_one_else_zero;
  using nt2::tag::if_one_else_zero_;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef typename nt2::meta::call<if_one_else_zero_(T)>::type r_t;
  typedef typename nt2::meta::scalar_of<r_t>::type ssr_t;
  typedef typename nt2::meta::upgrade<T>::type u_t;
  typedef T wished_r_t;


  // return type conformity test
  NT2_TEST_TYPE_IS( r_t, wished_r_t );
  // random verifications
  static const nt2::uint32_t NR = NT2_NB_RANDOM_TEST;
  {
    NT2_CREATE_BUF(tab_a0,T, NR, T(-10000), T(10000));
    double ulp0, ulpd ; ulpd=ulp0=0.0;
    T a0;
    for(nt2::uint32_t j =0; j < NR; ++j )
      {
        std::cout << "for param "
                  << "  a0 = "<< u_t(a0 = tab_a0[j])
                  << std::endl;
        NT2_TEST_EQUAL( nt2::if_one_else_zero(a0),r_t(a0!=0));
     }

   }
} // end of test for signed_int_

NT2_TEST_CASE_TPL ( if_one_else_zero_unsigned_int__1_0,  NT2_UNSIGNED_TYPES)
{

  using nt2::if_one_else_zero;
  using nt2::tag::if_one_else_zero_;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef typename nt2::meta::call<if_one_else_zero_(T)>::type r_t;
  typedef typename nt2::meta::scalar_of<r_t>::type ssr_t;
  typedef typename nt2::meta::upgrade<T>::type u_t;
  typedef T wished_r_t;


  // return type conformity test
  NT2_TEST_TYPE_IS( r_t, wished_r_t );

  // random verifications
  static const nt2::uint32_t NR = NT2_NB_RANDOM_TEST;
  {
    NT2_CREATE_BUF(tab_a0,T, NR, T(0), T(10000));
    double ulp0, ulpd ; ulpd=ulp0=0.0;
    T a0;
    for(nt2::uint32_t j =0; j < NR; ++j )
      {
        std::cout << "for param "
                  << "  a0 = "<< u_t(a0 = tab_a0[j])
                  << std::endl;
        NT2_TEST_EQUAL( nt2::if_one_else_zero(a0),r_t(a0!=0));
     }

   }
} // end of test for unsigned_int_
