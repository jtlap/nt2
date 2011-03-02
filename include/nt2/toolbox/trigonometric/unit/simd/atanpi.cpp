//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 trigonometric toolbox - atanpi/simd Mode"

//////////////////////////////////////////////////////////////////////////////
// Test behavior of trigonometric components in simd mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 11/02/2011
/// modified by jt the 02/03/2011
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
#include <nt2/include/functions/max.hpp>
#include <nt2/toolbox/trigonometric/include/atanpi.hpp>

NT2_TEST_CASE_TPL ( atanpi_real__1,  NT2_REAL_TYPES)
{
  using nt2::atanpi;
  using nt2::tag::atanpi_;
  using nt2::load; 
  using nt2::simd::native;
  using nt2::meta::cardinal_of;
  typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef typename nt2::meta::upgrade<T>::type   u_t;
  typedef native<T,ext_t>                        n_t;
  typedef n_t                                     vT;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef native<iT,ext_t>                       ivT;
  typedef typename nt2::meta::call<atanpi_(vT)>::type r_t;
  typedef typename nt2::meta::call<atanpi_(T)>::type sr_t;
  typedef typename nt2::meta::scalar_of<r_t>::type ssr_t;


  // specific values tests
  NT2_TEST_ULP_EQUAL(atanpi(nt2::Half<T>()), 2.656505117707799e+01, 0.5);
  NT2_TEST_ULP_EQUAL(atanpi(nt2::Inf<T>()), 90, 0.5);
  NT2_TEST_ULP_EQUAL(atanpi(nt2::Mhalf<T>()), -2.656505117707799e+01, 0.5);
  NT2_TEST_ULP_EQUAL(atanpi(nt2::Minf<T>()), -90, 0.5);
  NT2_TEST_ULP_EQUAL(atanpi(nt2::Mone<T>()), -45, 0.5);
  NT2_TEST_ULP_EQUAL(atanpi(nt2::Nan<T>()), nt2::Nan<r_t>(), 0.5);
  NT2_TEST_ULP_EQUAL(atanpi(nt2::One<T>()), 45, 0.5);
  NT2_TEST_ULP_EQUAL(atanpi(nt2::Zero<T>()), nt2::Zero<r_t>(), 0.5);
  // random verifications
  static const uint32_t NR = NT2_NB_RANDOM_TEST;
  {
    NT2_CREATE_BUF(tab_a0,T, NR, nt2::Mone<T>(), nt2::One<T>());
    double ulp0 = 0.0, ulpd = 0.0;
    T a0;
    for (int j =0; j < NR; ++j )
      {
        std::cout << "for param "
                  << "  a0 = "<< u_t(a0 = tab_a0[j])
                  << std::endl;
        NT2_TEST_ULP_EQUAL( nt2::atanpi(a0),::cephes_atanl(a0)*nt2::long_pi,1);
        ulp0=nt2::max(ulpd,ulp0);
     }
     std::cout << "max ulp found is: " << ulp0 << std::endl;
   }
} // end of test for real_

NT2_TEST_CASE_TPL ( atanpi_unsigned_int__1,  NT2_UNSIGNED_TYPES)
{
  using nt2::atanpi;
  using nt2::tag::atanpi_;
  using nt2::load; 
  using nt2::simd::native;
  using nt2::meta::cardinal_of;
  typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef typename nt2::meta::upgrade<T>::type   u_t;
  typedef native<T,ext_t>                        n_t;
  typedef n_t                                     vT;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef native<iT,ext_t>                       ivT;
  typedef typename nt2::meta::call<atanpi_(vT)>::type r_t;
  typedef typename nt2::meta::call<atanpi_(T)>::type sr_t;
  typedef typename nt2::meta::scalar_of<r_t>::type ssr_t;


  // specific values tests
  NT2_TEST_ULP_EQUAL(atanpi(nt2::One<T>()), 45, 0.5);
  NT2_TEST_ULP_EQUAL(atanpi(nt2::Zero<T>()), nt2::Zero<r_t>(), 0.5);
} // end of test for unsigned_int_

NT2_TEST_CASE_TPL ( atanpi_signed_int__1,  NT2_INTEGRAL_SIGNED_TYPES)
{
  using nt2::atanpi;
  using nt2::tag::atanpi_;
  using nt2::load; 
  using nt2::simd::native;
  using nt2::meta::cardinal_of;
  typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef typename nt2::meta::upgrade<T>::type   u_t;
  typedef native<T,ext_t>                        n_t;
  typedef n_t                                     vT;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef native<iT,ext_t>                       ivT;
  typedef typename nt2::meta::call<atanpi_(vT)>::type r_t;
  typedef typename nt2::meta::call<atanpi_(T)>::type sr_t;
  typedef typename nt2::meta::scalar_of<r_t>::type ssr_t;


  // specific values tests
  NT2_TEST_ULP_EQUAL(atanpi(nt2::Mone<T>()), -45, 0.5);
  NT2_TEST_ULP_EQUAL(atanpi(nt2::One<T>()), 45, 0.5);
  NT2_TEST_ULP_EQUAL(atanpi(nt2::Zero<T>()), nt2::Zero<r_t>(), 0.5);
} // end of test for signed_int_
