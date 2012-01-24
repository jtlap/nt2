//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 trigonometric toolbox - fast_cosd/simd Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of trigonometric components in simd mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 11/02/2011
/// 
#include <nt2/toolbox/trigonometric/include/functions/fast_cosd.hpp>
#include <nt2/include/functions/ulpdist.hpp>
#include <nt2/toolbox/trigonometric/constants.hpp>
extern "C" {extern long double cephes_cosl(long double);}

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
#include <nt2/include/functions/load.hpp>


NT2_TEST_CASE_TPL ( fast_cosd_real__1_0,  NT2_SIMD_REAL_TYPES)
{
  using nt2::fast_cosd;
  using nt2::tag::fast_cosd_;
  using nt2::load; 
  using boost::simd::native;
  using nt2::meta::cardinal_of;
  typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef typename nt2::meta::upgrade<T>::type   u_t;
  typedef native<T,ext_t>                        n_t;
  typedef n_t                                     vT;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef native<iT,ext_t>                       ivT;
  typedef typename nt2::meta::call<fast_cosd_(vT)>::type r_t;
  typedef typename nt2::meta::call<fast_cosd_(T)>::type sr_t;
  typedef typename nt2::meta::scalar_of<r_t>::type ssr_t;
  double ulpd;
  ulpd=0.0;


  // specific values tests
  NT2_TEST_ULP_EQUAL(fast_cosd(-nt2::_180<vT>())[0], nt2::Nan<sr_t>(), 0.5);
  NT2_TEST_ULP_EQUAL(fast_cosd(-nt2::_45<vT>())[0], nt2::Sqrt_2o_2<sr_t>(), 1);
  NT2_TEST_ULP_EQUAL(fast_cosd(-nt2::_90<vT>())[0], nt2::Nan<sr_t>(), 0.5);
  NT2_TEST_ULP_EQUAL(fast_cosd(nt2::Inf<vT>())[0], nt2::Nan<sr_t>(), 0.5);
  NT2_TEST_ULP_EQUAL(fast_cosd(nt2::Minf<vT>())[0], nt2::Nan<sr_t>(), 0.5);
  NT2_TEST_ULP_EQUAL(fast_cosd(nt2::Nan<vT>())[0], nt2::Nan<sr_t>(), 0.5);
  NT2_TEST_ULP_EQUAL(fast_cosd(nt2::Zero<vT>())[0], nt2::One<sr_t>(), 0.5);
  NT2_TEST_ULP_EQUAL(fast_cosd(nt2::_180<vT>())[0], nt2::Nan<sr_t>(), 0.5);
  NT2_TEST_ULP_EQUAL(fast_cosd(nt2::_45<vT>())[0], nt2::Sqrt_2o_2<sr_t>(), 1);
  NT2_TEST_ULP_EQUAL(fast_cosd(nt2::_90<vT>())[0], nt2::Nan<sr_t>(), 0.5);
} // end of test for floating_

NT2_TEST_CASE_TPL ( fast_cosd_int_convert__1_0,  NT2_SIMD_INT_CONVERT_TYPES)
{
  using nt2::fast_cosd;
  using nt2::tag::fast_cosd_;
  using nt2::load; 
  using boost::simd::native;
  using nt2::meta::cardinal_of;
  typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef typename nt2::meta::upgrade<T>::type   u_t;
  typedef native<T,ext_t>                        n_t;
  typedef n_t                                     vT;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef native<iT,ext_t>                       ivT;
  typedef typename nt2::meta::call<fast_cosd_(vT)>::type r_t;
  typedef typename nt2::meta::call<fast_cosd_(T)>::type sr_t;
  typedef typename nt2::meta::scalar_of<r_t>::type ssr_t;
  double ulpd;
  ulpd=0.0;


  // specific values tests
  NT2_TEST_ULP_EQUAL(fast_cosd(nt2::Zero<vT>())[0], nt2::One<sr_t>(), 0.5);
  NT2_TEST_ULP_EQUAL(fast_cosd(nt2::_45<vT>())[0], nt2::Sqrt_2o_2<sr_t>(), 1);
} // end of test for int_convert_

NT2_TEST_CASE_TPL ( fast_cosd_uint_convert__1_0,  NT2_SIMD_UINT_CONVERT_TYPES)
{
  using nt2::fast_cosd;
  using nt2::tag::fast_cosd_;
  using nt2::load; 
  using boost::simd::native;
  using nt2::meta::cardinal_of;
  typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef typename nt2::meta::upgrade<T>::type   u_t;
  typedef native<T,ext_t>                        n_t;
  typedef n_t                                     vT;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef native<iT,ext_t>                       ivT;
  typedef typename nt2::meta::call<fast_cosd_(vT)>::type r_t;
  typedef typename nt2::meta::call<fast_cosd_(T)>::type sr_t;
  typedef typename nt2::meta::scalar_of<r_t>::type ssr_t;
  double ulpd;
  ulpd=0.0;


  // specific values tests
  NT2_TEST_ULP_EQUAL(fast_cosd(nt2::Zero<vT>())[0], nt2::One<sr_t>(), 0.5);
  NT2_TEST_ULP_EQUAL(fast_cosd(nt2::_45<vT>())[0], nt2::Sqrt_2o_2<sr_t>(), 1);
} // end of test for uint_convert_
