//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/exponential/include/functions/nthroot.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/module.hpp>

#include <nt2/constant/constant.hpp>
#include <nt2/include/functions/splat.hpp>
#include <nt2/sdk/meta/as_integer.hpp>

NT2_TEST_CASE_TPL ( nthroot_real__2_0,  NT2_SIMD_REAL_TYPES)
{
  using nt2::nthroot;
  using nt2::tag::nthroot_;
  using boost::simd::native;
  typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                vT;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef native<iT,ext_t>                       ivT;
  typedef typename nt2::meta::call<nthroot_(vT,ivT)>::type r_t;

  // specific values tests
#ifndef BOOST_SIMD_NO_INVALIDS
  NT2_TEST_ULP_EQUAL(nthroot(nt2::Inf<vT>(),nt2::splat<ivT>(3)), nt2::Inf<r_t>(), 0.5);
  NT2_TEST_ULP_EQUAL(nthroot(nt2::Inf<vT>(),nt2::splat<ivT>(4)), nt2::Inf<r_t>(), 0.5);
  NT2_TEST_ULP_EQUAL(nthroot(nt2::Minf<vT>(),nt2::splat<ivT>(3)), nt2::Minf<r_t>(), 0.5);
  NT2_TEST_ULP_EQUAL(nthroot(nt2::Minf<vT>(),nt2::splat<ivT>(4)), nt2::Nan<r_t>(), 0.5);
  NT2_TEST_ULP_EQUAL(nthroot(nt2::Nan<vT>(),nt2::splat<ivT>(3)), nt2::Nan<r_t>(), 0.5);
  NT2_TEST_ULP_EQUAL(nthroot(nt2::Nan<vT>(),nt2::splat<ivT>(4)), nt2::Nan<r_t>(), 0.5);
#endif
  NT2_TEST_ULP_EQUAL(nthroot(nt2::Mone<vT>(),nt2::splat<ivT>(3)), nt2::Mone<r_t>(), 0.5);
  NT2_TEST_ULP_EQUAL(nthroot(nt2::Mone<vT>(),nt2::splat<ivT>(4)), nt2::Nan<r_t>(), 0.5);
  NT2_TEST_ULP_EQUAL(nthroot(nt2::One<vT>(),nt2::splat<ivT>(3)), nt2::One<r_t>(), 0.5);
  NT2_TEST_ULP_EQUAL(nthroot(nt2::One<vT>(),nt2::splat<ivT>(4)), nt2::One<r_t>(), 0.5);
  NT2_TEST_ULP_EQUAL(nthroot(nt2::Zero<vT>(),nt2::splat<ivT>(3)), nt2::Zero<r_t>(), 0.5);
  NT2_TEST_ULP_EQUAL(nthroot(nt2::Zero<vT>(),nt2::splat<ivT>(4)), nt2::Zero<r_t>(), 0.5);
  NT2_TEST_ULP_EQUAL(nthroot(nt2::splat<vT>(-8),nt2::splat<ivT>(3)), nt2::splat<r_t>(-2), 0.5);
  NT2_TEST_ULP_EQUAL(nthroot(nt2::splat<vT>(256),nt2::splat<ivT>(4)), nt2::splat<r_t>(4), 0.5);
  NT2_TEST_ULP_EQUAL(nthroot(nt2::splat<vT>(8),nt2::splat<ivT>(3)), nt2::splat<r_t>(2), 0.5);
} // end of test for floating_

NT2_TEST_CASE_TPL ( nthroot_sintgt_16__2_0,  NT2_SIMD_INT_CONVERT_TYPES)
{
  using nt2::nthroot;
  using nt2::tag::nthroot_;
  using boost::simd::native;
  typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                vT;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef native<iT,ext_t>                       ivT;
  typedef typename nt2::meta::call<nthroot_(vT,ivT)>::type r_t;

  // specific values tests
  NT2_TEST_ULP_EQUAL(nthroot(nt2::splat<vT>(-8),nt2::splat<ivT>(3)), nt2::splat<r_t>(-2), 0.5);
  NT2_TEST_ULP_EQUAL(nthroot(nt2::splat<vT>(256),nt2::splat<ivT>(4)), nt2::splat<r_t>(4), 0.5);
  NT2_TEST_ULP_EQUAL(nthroot(nt2::splat<vT>(8),nt2::splat<ivT>(3)), nt2::splat<r_t>(2), 0.5);
} // end of test for sintgt_16_

NT2_TEST_CASE_TPL ( nthroot_uintgt_16__2_0,  NT2_SIMD_UINT_CONVERT_TYPES)
{
  using nt2::nthroot;
  using nt2::tag::nthroot_;
  using boost::simd::native;
  typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                vT;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef native<iT,ext_t>                       ivT;
  typedef typename nt2::meta::call<nthroot_(vT,ivT)>::type r_t;

  // specific values tests
  NT2_TEST_ULP_EQUAL(nthroot(nt2::splat<vT>(256),nt2::splat<ivT>(4)), nt2::splat<r_t>(4), 0.5);
  NT2_TEST_ULP_EQUAL(nthroot(nt2::splat<vT>(8),nt2::splat<ivT>(3)), nt2::splat<r_t>(2), 0.5);
} // end of test for uintgt_16_
