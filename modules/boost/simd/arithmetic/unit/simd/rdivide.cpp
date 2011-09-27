//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 boost.simd.arithmetic toolbox - rdivide/simd Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of boost.simd.arithmetic components in simd mode
//////////////////////////////////////////////////////////////////////////////
/// created by jt the 01/12/2010
/// 
#include <boost/simd/toolbox/arithmetic/include/functions/rdivide.hpp>
#include <boost/simd/include/functions/ulpdist.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/memory/buffer.hpp>
#include <boost/simd/toolbox/constant/constant.hpp>
#include <boost/simd/sdk/memory/is_aligned.hpp>
#include <boost/simd/sdk/memory/aligned_type.hpp>
#include <boost/simd/include/functions/load.hpp>
#include <boost/simd/toolbox/constant/constant.hpp>


NT2_TEST_CASE_TPL ( rdivide_real__2_0,  BOOST_SIMD_SIMD_REAL_TYPES)
{
  using boost::simd::rdivide;
  using boost::simd::tag::rdivide_;
  using boost::simd::load; 
  using boost::simd::native;
  using boost::simd::meta::cardinal_of;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef typename boost::dispatch::meta::upgrade<T>::type   u_t;
  typedef native<T,ext_t>                        n_t;
  typedef n_t                                     vT;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef native<iT,ext_t>                       ivT;
  typedef typename boost::dispatch::meta::call<rdivide_(vT,vT)>::type r_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type sr_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type ssr_t;
  double ulpd;
  ulpd=0.0;


  // specific values tests
  NT2_TEST_ULP_EQUAL(rdivide(boost::simd::splat<vT>(1),boost::simd::splat<vT>(2))[0], T(0.5), 0);
  NT2_TEST_ULP_EQUAL(rdivide(boost::simd::Inf<vT>(), boost::simd::Inf<vT>())[0], boost::simd::Nan<T>(), 0);
  NT2_TEST_ULP_EQUAL(rdivide(boost::simd::Minf<vT>(), boost::simd::Minf<vT>())[0], boost::simd::Nan<T>(), 0);
  NT2_TEST_ULP_EQUAL(rdivide(boost::simd::Mone<vT>(), boost::simd::Mone<vT>())[0], boost::simd::One<T>(), 0);
  NT2_TEST_ULP_EQUAL(rdivide(boost::simd::Nan<vT>(), boost::simd::Nan<vT>())[0], boost::simd::Nan<T>(), 0);
  NT2_TEST_ULP_EQUAL(rdivide(boost::simd::One<vT>(), boost::simd::One<vT>())[0], boost::simd::One<T>(), 0);
  NT2_TEST_ULP_EQUAL(rdivide(boost::simd::Zero<vT>(), boost::simd::Zero<vT>())[0], boost::simd::Nan<T>(), 0);
} // end of test for floating_

NT2_TEST_CASE_TPL ( rdivide_unsigned_int__2_0,  BOOST_SIMD_SIMD_UNSIGNED_TYPES)
{
  using boost::simd::rdivide;
  using boost::simd::tag::rdivide_;
  using boost::simd::load; 
  using boost::simd::native;
  using boost::simd::meta::cardinal_of;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef typename boost::dispatch::meta::upgrade<T>::type   u_t;
  typedef native<T,ext_t>                        n_t;
  typedef n_t                                     vT;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef native<iT,ext_t>                       ivT;
  typedef typename boost::dispatch::meta::call<rdivide_(vT,vT)>::type r_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type sr_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type ssr_t;
  double ulpd;
  ulpd=0.0;


  // specific values tests
  NT2_TEST_ULP_EQUAL(rdivide(boost::simd::splat<vT>(2),boost::simd::splat<vT>(3))[0], T(0), 0);
  NT2_TEST_ULP_EQUAL(rdivide(boost::simd::splat<vT>(3),boost::simd::splat<vT>(2))[0], T(1), 0);
  NT2_TEST_ULP_EQUAL(rdivide(boost::simd::One<vT>(), boost::simd::One<vT>())[0], boost::simd::One<T>(), 0);
  NT2_TEST_ULP_EQUAL(rdivide(boost::simd::One<vT>(),boost::simd::Zero<vT>())[0], boost::simd::Valmax<T>(), 0);
  NT2_TEST_ULP_EQUAL(rdivide(boost::simd::Zero<vT>(), boost::simd::Zero<vT>())[0], boost::simd::Zero<T>(), 0);
} // end of test for unsigned_int_

NT2_TEST_CASE_TPL ( rdivide_signed_int__2_0,  BOOST_SIMD_SIMD_INTEGRAL_SIGNED_TYPES)
{
  using boost::simd::rdivide;
  using boost::simd::tag::rdivide_;
  using boost::simd::load; 
  using boost::simd::native;
  using boost::simd::meta::cardinal_of;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef typename boost::dispatch::meta::upgrade<T>::type   u_t;
  typedef native<T,ext_t>                        n_t;
  typedef n_t                                     vT;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef native<iT,ext_t>                       ivT;
  typedef typename boost::dispatch::meta::call<rdivide_(vT,vT)>::type r_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type sr_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type ssr_t;
  double ulpd;
  ulpd=0.0;


  // specific values tests
  NT2_TEST_ULP_EQUAL(rdivide(boost::simd::splat<vT>(2),boost::simd::splat<vT>(3))[0], T(0), 0);
  NT2_TEST_ULP_EQUAL(rdivide(boost::simd::splat<vT>(3),boost::simd::splat<vT>(2))[0], T(1), 0);
  NT2_TEST_ULP_EQUAL(rdivide(boost::simd::Mone<vT>(), boost::simd::Mone<vT>())[0], boost::simd::One<T>(), 0);
  NT2_TEST_ULP_EQUAL(rdivide(boost::simd::Mone<vT>(),boost::simd::Zero<vT>())[0], boost::simd::Valmin<T>(), 0);
  NT2_TEST_ULP_EQUAL(rdivide(boost::simd::One<vT>(), boost::simd::One<vT>())[0], boost::simd::One<T>(), 0);
  NT2_TEST_ULP_EQUAL(rdivide(boost::simd::One<vT>(),boost::simd::Zero<vT>())[0], boost::simd::Valmax<T>(), 0);
  NT2_TEST_ULP_EQUAL(rdivide(boost::simd::Valmax<vT>(),boost::simd::Mone<vT>())[0], boost::simd::Valmin<T>()+boost::simd::One<T>(), 0);
  NT2_TEST_ULP_EQUAL(rdivide(boost::simd::Valmin<vT>(),boost::simd::Mone<vT>())[0], boost::simd::Valmax<T>(), 0);
  NT2_TEST_ULP_EQUAL(rdivide(boost::simd::Zero<vT>(), boost::simd::Zero<vT>())[0], boost::simd::Zero<T>(), 0);
} // end of test for signed_int_
