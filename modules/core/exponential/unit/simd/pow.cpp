//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 exponential toolbox - pow/simd Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of exponential components in simd mode
//////////////////////////////////////////////////////////////////////////////
/// created by jt the 08/12/2010
///
#include <nt2/exponential/include/functions/pow.hpp>
#include <boost/simd/sdk/simd/native.hpp>
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
#include <nt2/constant/constant.hpp>
#include <nt2/sdk/meta/cardinal_of.hpp>
#include <nt2/include/functions/splat.hpp>

NT2_TEST_CASE_TPL ( pow_real__2_0,  NT2_SIMD_REAL_TYPES)
{
  using nt2::pow;
  using nt2::tag::pow_;
  using nt2::load;
  using boost::simd::native;
  using nt2::meta::cardinal_of;
  typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                        n_t;
  typedef n_t                                     vT;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef native<iT,ext_t>                       ivT;
  typedef typename nt2::meta::call<pow_(vT,vT)>::type r_t;


  // specific values tests
  NT2_TEST_ULP_EQUAL(pow(nt2::splat<vT>(-1),nt2::splat<vT>(5)), nt2::Mone<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(pow(nt2::splat<vT>(-1),nt2::splat<vT>(6)), nt2::One<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(pow(nt2::Inf<vT>(), nt2::Inf<vT>()), nt2::Inf<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(pow(nt2::Minf<vT>(), nt2::Minf<vT>()), nt2::Nan<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(pow(nt2::Mone<vT>(), nt2::Mone<vT>()), nt2::Mone<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(pow(nt2::Nan<vT>(), nt2::Nan<vT>()), nt2::Nan<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(pow(nt2::One<vT>(), nt2::One<vT>()), nt2::One<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(pow(nt2::Zero<vT>(), nt2::Zero<vT>()), nt2::One<r_t>(), 0);
} // end of test for floating_

NT2_TEST_CASE_TPL ( pow_real__2_1,  NT2_SIMD_REAL_TYPES)
{
  using nt2::pow;
  using nt2::tag::pow_;
  using nt2::load;
  using boost::simd::native;
  using nt2::meta::cardinal_of;
  typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                        n_t;
  typedef n_t                                     vT;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef native<iT,ext_t>                       ivT;
  typedef typename nt2::meta::call<pow_(vT,ivT)>::type r_t;

  // specific values tests
  NT2_TEST_ULP_EQUAL(pow(nt2::Inf<vT>(),3), nt2::Inf<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(pow(nt2::Minf<vT>(),3), nt2::Minf<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(pow(nt2::Mone<vT>(),3),nt2::Mone<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(pow(nt2::Nan<vT>(),3), nt2::Nan<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(pow(nt2::One<vT>(),3), nt2::One<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(pow(nt2::Two <vT>(),3),nt2::Eight<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(pow(nt2::Zero<vT>(),0), nt2::One<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(pow(nt2::Zero<vT>(),3), nt2::Zero<r_t>(), 0);
} // end of test for floating_

NT2_TEST_CASE_TPL ( powi_real__2_0,  NT2_SIMD_REAL_TYPES)
{
  using nt2::pow;
  using nt2::tag::pow_;
  using nt2::load;
  using boost::simd::native;
  using nt2::meta::cardinal_of;
  typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                        n_t;
  typedef n_t                                     vT;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef native<iT,ext_t>                       ivT;
  typedef typename nt2::meta::call<pow_(vT,iT)>::type r_t;

  // specific values tests
  NT2_TEST_ULP_EQUAL(pow(nt2::Inf<vT>(),3), nt2::Inf<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(pow(nt2::Inf<vT>(),4), nt2::Inf<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(pow(nt2::Minf<vT>(),3), nt2::Minf<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(pow(nt2::Minf<vT>(),4), nt2::Inf<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(pow(nt2::Mone<vT>(),3), nt2::Mone<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(pow(nt2::Mone<vT>(),4), nt2::One<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(pow(nt2::Nan<vT>(),3), nt2::Nan<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(pow(nt2::Nan<vT>(),4), nt2::Nan<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(pow(nt2::One<vT>(),3), nt2::One<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(pow(nt2::One<vT>(),4), nt2::One<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(pow(nt2::Zero<vT>(),3), nt2::Zero<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(pow(nt2::Zero<vT>(),4), nt2::Zero<r_t>(), 0);
} // end of test for floating_
