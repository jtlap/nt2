//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 arithmetic toolbox - divfix/simd Mode"

//////////////////////////////////////////////////////////////////////////////
// Test behavior of arithmetic components in simd mode
//////////////////////////////////////////////////////////////////////////////
/// created by jt the 01/12/2010
/// modified by jt the 14/02/2011
#include <nt2/sdk/memory/is_aligned.hpp>
#include <nt2/sdk/memory/aligned_type.hpp>
#include <nt2/sdk/memory/load.hpp>
#include <nt2/sdk/memory/buffer.hpp>
#include <boost/type_traits/is_same.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/constant/real.hpp>
#include <nt2/sdk/constant/infinites.hpp>
#include <nt2/toolbox/arithmetic/include/divfix.hpp>

NT2_TEST_CASE_TPL ( divfix_real__2,  NT2_REAL_TYPES)
{
  using nt2::divfix;
  using nt2::tag::divfix_;
  using nt2::load; 
  using nt2::simd::native;
  using nt2::meta::cardinal_of;
  typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef typename nt2::meta::upgrade<T>::type   u_t;
  typedef native<T,ext_t>                        n_t;
  typedef n_t                                     vT;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef native<iT,ext_t>                       ivT;
  typedef typename nt2::meta::call<divfix_(vT,vT)>::type r_t;
  typedef typename nt2::meta::call<divfix_(T,T)>::type sr_t;


  // specific values tests
  NT2_TEST_ULP_EQUAL(  divfix(4,3), 1, 0);
  NT2_TEST_ULP_EQUAL(  divfix(nt2::Inf<T>(), nt2::Inf<T>()), nt2::Nan<T>(), 0);
  NT2_TEST_ULP_EQUAL(  divfix(nt2::Minf<T>(), nt2::Minf<T>()), nt2::Nan<T>(), 0);
  NT2_TEST_ULP_EQUAL(  divfix(nt2::Mone<T>(), nt2::Mone<T>()), nt2::One<T>(), 0);
  NT2_TEST_ULP_EQUAL(  divfix(nt2::Nan<T>(), nt2::Nan<T>()), nt2::Nan<T>(), 0);
  NT2_TEST_ULP_EQUAL(  divfix(nt2::One<T>(), nt2::One<T>()), nt2::One<T>(), 0);
  NT2_TEST_ULP_EQUAL(  divfix(nt2::Zero<T>(), nt2::Zero<T>()), nt2::Nan<T>(), 0);
  // random verifications
  static const uint32_t NR = NT2_NB_RANDOM_TEST;
  {
    NT2_CREATE_SCALAR_BUFFER(a0,T, NR, T(-10), T(10));
    NT2_CREATE_SCALAR_BUFFER(a1,T, NR, T(-10), T(10));
    double ulp0 = 0.0, ulpd = 0.0;
    for (int j =0; j < NR; ++j )
      {
        std::cout << "for params "
                  << "  a0 = "<< u_t(a0 = tab_a0[j])
                  << ", a1 = "<< u_t(a1 = tab_a1[j])
                  << std::endl;
        NT2_TEST_ULP_EQUAL( nt2::divfix(a0,a1),r_t(nt2::trunc((1.0*a0)/a1)),0);
        ulp0=nt2::max(ulpd,ulp0);
     }
     std::cout << "max ulp found is: " << ulp0 << std::endl;
   }
} // end of test for real_

NT2_TEST_CASE_TPL ( divfix_unsigned_int__2,  NT2_UNSIGNED_TYPES)
{
  using nt2::divfix;
  using nt2::tag::divfix_;
  using nt2::load; 
  using nt2::simd::native;
  using nt2::meta::cardinal_of;
  typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef typename nt2::meta::upgrade<T>::type   u_t;
  typedef native<T,ext_t>                        n_t;
  typedef n_t                                     vT;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef native<iT,ext_t>                       ivT;
  typedef typename nt2::meta::call<divfix_(vT,vT)>::type r_t;
  typedef typename nt2::meta::call<divfix_(T,T)>::type sr_t;


  // specific values tests
  NT2_TEST_ULP_EQUAL(  divfix(4,3), 1, 0);
  NT2_TEST_ULP_EQUAL(  divfix(nt2::One<T>(), nt2::One<T>()), nt2::One<T>(), 0);
  NT2_TEST_ULP_EQUAL(  divfix(nt2::Zero<T>(), nt2::Zero<T>()), nt2::Zero<T>(), 0);
  // random verifications
  static const uint32_t NR = NT2_NB_RANDOM_TEST;
  {
    NT2_CREATE_SCALAR_BUFFER(a0,T, NR, 0, 100);
    NT2_CREATE_SCALAR_BUFFER(a1,T, NR, 0, 100);
    double ulp0 = 0.0, ulpd = 0.0;
    for (int j =0; j < NR; ++j )
      {
        std::cout << "for params "
                  << "  a0 = "<< u_t(a0 = tab_a0[j])
                  << ", a1 = "<< u_t(a1 = tab_a1[j])
                  << std::endl;
        NT2_TEST_ULP_EQUAL( nt2::divfix(a0,a1),r_t(nt2::trunc((1.0*a0)/a1)),0);
        ulp0=nt2::max(ulpd,ulp0);
     }
     std::cout << "max ulp found is: " << ulp0 << std::endl;
   }
} // end of test for unsigned_int_

NT2_TEST_CASE_TPL ( divfix_signed_int__2,  NT2_INTEGRAL_SIGNED_TYPES)
{
  using nt2::divfix;
  using nt2::tag::divfix_;
  using nt2::load; 
  using nt2::simd::native;
  using nt2::meta::cardinal_of;
  typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef typename nt2::meta::upgrade<T>::type   u_t;
  typedef native<T,ext_t>                        n_t;
  typedef n_t                                     vT;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef native<iT,ext_t>                       ivT;
  typedef typename nt2::meta::call<divfix_(vT,vT)>::type r_t;
  typedef typename nt2::meta::call<divfix_(T,T)>::type sr_t;


  // specific values tests
  NT2_TEST_ULP_EQUAL(  divfix(4,3), 1, 0);
  NT2_TEST_ULP_EQUAL(  divfix(nt2::Mone<T>(), nt2::Mone<T>()), nt2::One<T>(), 0);
  NT2_TEST_ULP_EQUAL(  divfix(nt2::One<T>(), nt2::One<T>()), nt2::One<T>(), 0);
  NT2_TEST_ULP_EQUAL(  divfix(nt2::Zero<T>(), nt2::Zero<T>()), nt2::Zero<T>(), 0);
  // random verifications
  static const uint32_t NR = NT2_NB_RANDOM_TEST;
  {
    NT2_CREATE_SCALAR_BUFFER(a0,T, NR, -100, 100);
    NT2_CREATE_SCALAR_BUFFER(a1,T, NR, -100, 100);
    double ulp0 = 0.0, ulpd = 0.0;
    for (int j =0; j < NR; ++j )
      {
        std::cout << "for params "
                  << "  a0 = "<< u_t(a0 = tab_a0[j])
                  << ", a1 = "<< u_t(a1 = tab_a1[j])
                  << std::endl;
        NT2_TEST_ULP_EQUAL( nt2::divfix(a0,a1),r_t(nt2::trunc((1.0*a0)/a1)),0);
        ulp0=nt2::max(ulpd,ulp0);
     }
     std::cout << "max ulp found is: " << ulp0 << std::endl;
   }
} // end of test for signed_int_