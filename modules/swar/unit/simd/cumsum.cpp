//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 swar toolbox - cumsum/simd Mode"

//////////////////////////////////////////////////////////////////////////////
// Test behavior of swar components in simd mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 24/02/2011
/// modified by jt the 20/03/2011
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
#include <nt2/toolbox/swar/include/cumsum.hpp>
// specific includes for arity 1 tests
#include <nt2/include/functions/all.hpp>

NT2_TEST_CASE_TPL ( cumsum_real__1_0,  NT2_REAL_TYPES)
{
  using nt2::cumsum;
  using nt2::tag::cumsum_;
  using nt2::load; 
  using nt2::simd::native;
  using nt2::meta::cardinal_of;
  typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef typename nt2::meta::upgrade<T>::type   u_t;
  typedef native<T,ext_t>                        n_t;
  typedef n_t                                     vT;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef native<iT,ext_t>                       ivT;
  typedef typename nt2::meta::call<cumsum_(vT)>::type r_t;
  typedef typename nt2::meta::call<cumsum_(T)>::type sr_t;
  typedef typename nt2::meta::scalar_of<r_t>::type ssr_t;

  // random verifications
  static const uint32_t NR = NT2_NB_RANDOM_TEST;
  {
    NT2_CREATE_BUF(tab_a0,T, NR, T(-100), T(100));
    double ulp0, ulpd ; ulpd=ulp0=0.0;
    for(uint32_t j = 0; j < NR/cardinal_of<n_t>::value; j++)
      {
        vT a0 = load<vT>(&tab_a0[0],j);
        r_t v = cumsum(a0);
        NT2_CREATE_BUF(z,T, cardinal_of<n_t>::value, T(0), T(0));
        for( uint32_t i = 0; i<cardinal_of<n_t>::value; i++) z[i]=0;
        for( uint32_t i = 0; i<cardinal_of<n_t>::value; i++) {
          for( uint32_t k = i; k<cardinal_of<n_t>::value; k++) {
            z[k]+=a0[i];
          }
        }
        vT zz = load<vT>(&z[0],0);
        for( uint32_t i = 0; i<cardinal_of<n_t>::value; i++)
         {
            NT2_TEST_ULP_EQUAL(v[i],zz[i], 16);
         }
      }
    
  }
} // end of test for real_

NT2_TEST_CASE_TPL ( cumsum_signed_int__1_0,  NT2_INTEGRAL_SIGNED_TYPES)
{
  using nt2::cumsum;
  using nt2::tag::cumsum_;
  using nt2::load; 
  using nt2::simd::native;
  using nt2::meta::cardinal_of;
  typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef typename nt2::meta::upgrade<T>::type   u_t;
  typedef native<T,ext_t>                        n_t;
  typedef n_t                                     vT;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef native<iT,ext_t>                       ivT;
  typedef typename nt2::meta::call<cumsum_(vT)>::type r_t;
  typedef typename nt2::meta::call<cumsum_(T)>::type sr_t;
  typedef typename nt2::meta::scalar_of<r_t>::type ssr_t;

  // random verifications
  static const uint32_t NR = NT2_NB_RANDOM_TEST;
  {
    NT2_CREATE_BUF(tab_a0,T, NR, nt2::Valmin<T>(), nt2::Valmax<T>());
    double ulp0, ulpd ; ulpd=ulp0=0.0;
    for(uint32_t j = 0; j < NR/cardinal_of<n_t>::value; j++)
      {
        vT a0 = load<vT>(&tab_a0[0],j);
        r_t v = cumsum(a0);
        NT2_CREATE_BUF(z,T, cardinal_of<n_t>::value, T(0), T(0));
        for( uint32_t i = 0; i<cardinal_of<n_t>::value; i++) z[i]=0;
        for( uint32_t i = 0; i<cardinal_of<n_t>::value; i++) {
          for( uint32_t k = i; k<cardinal_of<n_t>::value; k++) {
            z[k]+=a0[i];
          }
        }
        vT zz = load<vT>(&z[0],0);
        for( uint32_t i = 0; i<cardinal_of<n_t>::value; i++)
         {
            NT2_TEST_ULP_EQUAL(v[i],zz[i], 16);
         }
      }
    
  }
} // end of test for signed_int_

NT2_TEST_CASE_TPL ( cumsum_unsigned_int__1_0,  NT2_UNSIGNED_TYPES)
{
  using nt2::cumsum;
  using nt2::tag::cumsum_;
  using nt2::load; 
  using nt2::simd::native;
  using nt2::meta::cardinal_of;
  typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef typename nt2::meta::upgrade<T>::type   u_t;
  typedef native<T,ext_t>                        n_t;
  typedef n_t                                     vT;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef native<iT,ext_t>                       ivT;
  typedef typename nt2::meta::call<cumsum_(vT)>::type r_t;
  typedef typename nt2::meta::call<cumsum_(T)>::type sr_t;
  typedef typename nt2::meta::scalar_of<r_t>::type ssr_t;

  // random verifications
  static const uint32_t NR = NT2_NB_RANDOM_TEST;
  {
    NT2_CREATE_BUF(tab_a0,T, NR, nt2::Valmin<T>(), nt2::Valmax<T>());
    double ulp0, ulpd ; ulpd=ulp0=0.0;
    for(uint32_t j = 0; j < NR/cardinal_of<n_t>::value; j++)
      {
        vT a0 = load<vT>(&tab_a0[0],j);
        r_t v = cumsum(a0);
        NT2_CREATE_BUF(z,T, cardinal_of<n_t>::value, T(0), T(0));
        for( uint32_t i = 0; i<cardinal_of<n_t>::value; i++) z[i]=0;
        for( uint32_t i = 0; i<cardinal_of<n_t>::value; i++) {
          for( uint32_t k = i; k<cardinal_of<n_t>::value; k++) {
            z[k]+=a0[i];
          }
        }
        vT zz = load<vT>(&z[0],0);
        for( uint32_t i = 0; i<cardinal_of<n_t>::value; i++)
         {
            NT2_TEST_ULP_EQUAL(v[i],zz[i], 16);
         }
      }
    
  }
} // end of test for unsigned_int_
