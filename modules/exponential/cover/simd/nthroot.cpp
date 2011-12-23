//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 exponential toolbox - nthroot/simd Mode"

//////////////////////////////////////////////////////////////////////////////
// cover test behavior of exponential components in simd mode
//////////////////////////////////////////////////////////////////////////////
/// created by jt the 08/12/2010
/// 
#include <nt2/toolbox/exponential/include/functions/nthroot.hpp>
#include <nt2/include/functions/ulpdist.hpp>
#include <nt2/include/functions/max.hpp>
#include <nt2/include/functions/sqr.hpp>
#include <nt2/include/functions/abs.hpp>

#include <boost/type_traits/is_same.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/meta/as_floating.hpp>
#include <nt2/sdk/meta/as_signed.hpp>
#include <nt2/sdk/meta/upgrade.hpp>
#include <nt2/sdk/meta/downgrade.hpp>
#include <nt2/sdk/meta/scalar_of.hpp>
#include <boost/dispatch/meta/as_floating.hpp>
#include <boost/type_traits/common_type.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/memory/buffer.hpp>
#include <nt2/toolbox/constant/constant.hpp>
#include <nt2/sdk/meta/cardinal_of.hpp>
#include <nt2/include/functions/splat.hpp>
#include <nt2/sdk/memory/is_aligned.hpp>
#include <nt2/sdk/memory/aligned_type.hpp>
#include <nt2/include/functions/load.hpp>
#include <nt2/toolbox/constant/constant.hpp>


NT2_TEST_CASE_TPL ( nthroot_real__2_0,  NT2_SIMD_REAL_TYPES)
{
  using nt2::nthroot;
  using nt2::tag::nthroot_;
  using nt2::load; 
  using boost::simd::native;
  using nt2::meta::cardinal_of;
  typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef typename nt2::meta::upgrade<T>::type   u_t;
  typedef native<T,ext_t>                        n_t;
  typedef n_t                                     vT;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef native<iT,ext_t>                       ivT;
  typedef typename nt2::meta::call<nthroot_(vT,ivT)>::type r_t;
  typedef typename nt2::meta::call<nthroot_(T,iT)>::type sr_t;
  typedef typename nt2::meta::scalar_of<r_t>::type ssr_t;
  double ulpd;
  ulpd=0.0;

  // random verifications
  static const nt2::uint32_t NR = NT2_NB_RANDOM_TEST;
  {
    NT2_CREATE_BUF(tab_a0,T, NR, T(0), T(10));
    NT2_CREATE_BUF(tab_a1,iT, NR, iT(-10), iT(10));
    double ulp0, ulpd ; ulpd=ulp0=0.0;
    for(nt2::uint32_t j = 0; j < NR;j+=cardinal_of<n_t>::value)
      {
        vT a0 = load<vT>(&tab_a0[0],j);
        ivT a1 = load<ivT>(&tab_a1[0],j);
        r_t v = nthroot(a0,a1);
        for(nt2::uint32_t i = 0; i< cardinal_of<n_t>::value; i++)
        {
          
          NT2_TEST_ULP_EQUAL( v[i],ssr_t(nt2::nthroot (a0[i],a1[i])), 1);
          ulp0 = nt2::max(ulpd,ulp0);
        }
      }
    std::cout << "max ulp found is: " << ulp0 << std::endl;
  }
} // end of test for floating_

NT2_TEST_CASE_TPL ( nthroot_sintgt_16__2_0,  NT2_SIMD_SIGNED_INT_GT_16_TYPES)
{
  using nt2::nthroot;
  using nt2::tag::nthroot_;
  using nt2::load; 
  using boost::simd::native;
  using nt2::meta::cardinal_of;
  typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef typename nt2::meta::upgrade<T>::type   u_t;
  typedef native<T,ext_t>                        n_t;
  typedef n_t                                     vT;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef native<iT,ext_t>                       ivT;
  typedef typename nt2::meta::call<nthroot_(vT,ivT)>::type r_t;
  typedef typename nt2::meta::call<nthroot_(T,iT)>::type sr_t;
  typedef typename nt2::meta::scalar_of<r_t>::type ssr_t;
  double ulpd;
  ulpd=0.0;

  // random verifications
  static const nt2::uint32_t NR = NT2_NB_RANDOM_TEST;
  {
    NT2_CREATE_BUF(tab_a0,T, NR, -100, 100);
    NT2_CREATE_BUF(tab_a1,iT, NR, -100, 100);
    double ulp0, ulpd ; ulpd=ulp0=0.0;
    for(nt2::uint32_t j = 0; j < NR;j+=cardinal_of<n_t>::value)
      {
        vT a0 = load<vT>(&tab_a0[0],j);
        ivT a1 = load<ivT>(&tab_a1[0],j);
        r_t v = nthroot(a0,a1);
        for(nt2::uint32_t i = 0; i< cardinal_of<n_t>::value; i++)
        {
          
          NT2_TEST_ULP_EQUAL( v[i],ssr_t(nt2::nthroot (a0[i],a1[i])), 1);
          ulp0 = nt2::max(ulpd,ulp0);
        }
      }
    std::cout << "max ulp found is: " << ulp0 << std::endl;
  }
} // end of test for sintgt_16_

NT2_TEST_CASE_TPL ( nthroot_uintgt_16__2_0,  NT2_SIMD_UNSIGNED_INT_GT_16_TYPES)
{
  using nt2::nthroot;
  using nt2::tag::nthroot_;
  using nt2::load; 
  using boost::simd::native;
  using nt2::meta::cardinal_of;
  typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef typename nt2::meta::upgrade<T>::type   u_t;
  typedef native<T,ext_t>                        n_t;
  typedef n_t                                     vT;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef native<iT,ext_t>                       ivT;
  typedef typename nt2::meta::call<nthroot_(vT,ivT)>::type r_t;
  typedef typename nt2::meta::call<nthroot_(T,iT)>::type sr_t;
  typedef typename nt2::meta::scalar_of<r_t>::type ssr_t;
  double ulpd;
  ulpd=0.0;

  // random verifications
  static const nt2::uint32_t NR = NT2_NB_RANDOM_TEST;
  {
    NT2_CREATE_BUF(tab_a0,T, NR, 0, 100);
    NT2_CREATE_BUF(tab_a1,iT, NR, 0, 100);
    double ulp0, ulpd ; ulpd=ulp0=0.0;
    for(nt2::uint32_t j = 0; j < NR;j+=cardinal_of<n_t>::value)
      {
        vT a0 = load<vT>(&tab_a0[0],j);
        ivT a1 = load<ivT>(&tab_a1[0],j);
        r_t v = nthroot(a0,a1);
        for(nt2::uint32_t i = 0; i< cardinal_of<n_t>::value; i++)
        {
          
          NT2_TEST_ULP_EQUAL( v[i],ssr_t(nt2::nthroot (a0[i],a1[i])), 1);
          ulp0 = nt2::max(ulpd,ulp0);
        }
      }
    std::cout << "max ulp found is: " << ulp0 << std::endl;
  }
} // end of test for uintgt_16_
