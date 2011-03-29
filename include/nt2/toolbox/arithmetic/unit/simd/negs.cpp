//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 arithmetic toolbox - negs/simd Mode"

//////////////////////////////////////////////////////////////////////////////
// Test behavior of arithmetic components in simd mode
//////////////////////////////////////////////////////////////////////////////
/// created by jt the 30/11/2010
/// modified by jt the 29/03/2011
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
#include <nt2/toolbox/arithmetic/include/negs.hpp>

NT2_TEST_CASE_TPL ( negs_real__1_0,  NT2_REAL_TYPES)
{
  using nt2::negs;
  using nt2::tag::negs_;
  using nt2::load; 
  using nt2::simd::native;
  using nt2::meta::cardinal_of;
  typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef typename nt2::meta::upgrade<T>::type   u_t;
  typedef native<T,ext_t>                        n_t;
  typedef n_t                                     vT;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef native<iT,ext_t>                       ivT;
  typedef typename nt2::meta::call<negs_(vT)>::type r_t;
  typedef typename nt2::meta::call<negs_(T)>::type sr_t;
  typedef typename nt2::meta::scalar_of<r_t>::type ssr_t;
  double ulpd;
  ulpd=0.0;


  // specific values tests
  NT2_TEST_EQUAL(negs(nt2::splat<vT>(100))[0], T(-100));
  NT2_TEST_EQUAL(negs(nt2::Inf<vT>())[0], nt2::Minf<T>());
  NT2_TEST_EQUAL(negs(nt2::Minf<vT>())[0], nt2::Inf<T>());
  NT2_TEST_EQUAL(negs(nt2::Mone<vT>())[0], nt2::One<T>());
  NT2_TEST_EQUAL(negs(nt2::Nan<vT>())[0], nt2::Nan<T>());
  NT2_TEST_EQUAL(negs(nt2::One<vT>())[0], nt2::Mone<T>());
  NT2_TEST_EQUAL(negs(nt2::Valmax<vT>())[0], nt2::Valmin<T>());
  NT2_TEST_EQUAL(negs(nt2::Valmin<vT>())[0], nt2::Valmax<T>());
  NT2_TEST_EQUAL(negs(nt2::Zero<vT>())[0], nt2::Zero<T>());
  // random verifications
  static const uint32_t NR = NT2_NB_RANDOM_TEST;
  {
    NT2_CREATE_BUF(tab_a0,T, NR, T(-100), T(100));
    double ulp0, ulpd ; ulpd=ulp0=0.0;
    for(uint32_t j = 0; j < NR/cardinal_of<n_t>::value; j++)
      {
        vT a0 = load<vT>(&tab_a0[0],j);
        r_t v = negs(a0);
        for(int i = 0; i< cardinal_of<n_t>::value; i++)
        {
          int k = i+j*cardinal_of<n_t>::value;
          NT2_TEST_EQUAL( v[i],ssr_t(nt2::negs(tab_a0[k])));
        }
      }
    
  }
} // end of test for real_

NT2_TEST_CASE_TPL ( negs_signed_int__1_0,  NT2_INTEGRAL_SIGNED_TYPES)
{
  using nt2::negs;
  using nt2::tag::negs_;
  using nt2::load; 
  using nt2::simd::native;
  using nt2::meta::cardinal_of;
  typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef typename nt2::meta::upgrade<T>::type   u_t;
  typedef native<T,ext_t>                        n_t;
  typedef n_t                                     vT;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef native<iT,ext_t>                       ivT;
  typedef typename nt2::meta::call<negs_(vT)>::type r_t;
  typedef typename nt2::meta::call<negs_(T)>::type sr_t;
  typedef typename nt2::meta::scalar_of<r_t>::type ssr_t;
  double ulpd;
  ulpd=0.0;


  // specific values tests
  NT2_TEST_EQUAL(negs(nt2::splat<vT>(100))[0], T(-100));
  NT2_TEST_EQUAL(negs(nt2::Mone<vT>())[0], nt2::One<T>());
  NT2_TEST_EQUAL(negs(nt2::One<vT>())[0], nt2::Mone<T>());
  NT2_TEST_EQUAL(negs(nt2::Valmax<vT>())[0], -nt2::Valmax<T>());
  NT2_TEST_EQUAL(negs(nt2::Valmin<vT>())[0], nt2::Valmax<T>());
  NT2_TEST_EQUAL(negs(nt2::Zero<vT>())[0], nt2::Zero<T>());
  // random verifications
  static const uint32_t NR = NT2_NB_RANDOM_TEST;
  {
    NT2_CREATE_BUF(tab_a0,T, NR, T(-100), T(100));
    double ulp0, ulpd ; ulpd=ulp0=0.0;
    for(uint32_t j = 0; j < NR/cardinal_of<n_t>::value; j++)
      {
        vT a0 = load<vT>(&tab_a0[0],j);
        r_t v = negs(a0);
        for(int i = 0; i< cardinal_of<n_t>::value; i++)
        {
          int k = i+j*cardinal_of<n_t>::value;
          NT2_TEST_EQUAL( v[i],ssr_t(nt2::negs(tab_a0[k])));
        }
      }
    
  }
} // end of test for signed_int_
