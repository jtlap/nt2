//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 boost.simd.arithmetic toolbox - abss/simd Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of boost.simd.arithmetic components in simd mode
//////////////////////////////////////////////////////////////////////////////
/// created by jt the 30/11/2010
/// 
#include <boost/simd/toolbox/arithmetic/include/functions/abss.hpp>
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


NT2_TEST_CASE_TPL ( abss_real__1_0,  BOOST_SIMD_SIMD_REAL_TYPES)
{
  using boost::simd::abss;
  using boost::simd::tag::abss_;
  using boost::simd::load; 
  using boost::simd::native;
  using boost::simd::meta::cardinal_of;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef typename boost::dispatch::meta::upgrade<T>::type   u_t;
  typedef native<T,ext_t>                        n_t;
  typedef n_t                                     vT;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef native<iT,ext_t>                       ivT;
  typedef typename boost::dispatch::meta::call<abss_(vT)>::type r_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type sr_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type ssr_t;

  // specific values tests
  NT2_TEST_EQUAL(abss(boost::simd::splat<vT>(1))[0], T(1));
  NT2_TEST_EQUAL(abss(boost::simd::Inf<vT>())[0], boost::simd::Inf<T>());
  NT2_TEST_EQUAL(abss(boost::simd::Minf<vT>())[0], boost::simd::Inf<T>());
  NT2_TEST_EQUAL(abss(boost::simd::Mone<vT>())[0], boost::simd::One<T>());
  NT2_TEST_EQUAL(abss(boost::simd::Nan<vT>())[0], boost::simd::Nan<T>());
  NT2_TEST_EQUAL(abss(boost::simd::One<vT>())[0], boost::simd::One<T>());
  NT2_TEST_EQUAL(abss(boost::simd::Valmax<vT>())[0], boost::simd::Valmax<T>());
  NT2_TEST_EQUAL(abss(boost::simd::Valmin<vT>())[0], boost::simd::Valmax<T>());
  NT2_TEST_EQUAL(abss(boost::simd::Zero<vT>())[0], boost::simd::Zero<T>());
} // end of test for floating_

NT2_TEST_CASE_TPL ( abss_unsigned_int__1_0,  BOOST_SIMD_SIMD_UNSIGNED_TYPES)
{
  using boost::simd::abss;
  using boost::simd::tag::abss_;
  using boost::simd::load; 
  using boost::simd::native;
  using boost::simd::meta::cardinal_of;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef typename boost::dispatch::meta::upgrade<T>::type   u_t;
  typedef native<T,ext_t>                        n_t;
  typedef n_t                                     vT;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef native<iT,ext_t>                       ivT;
  typedef typename boost::dispatch::meta::call<abss_(vT)>::type r_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type sr_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type ssr_t;

  // specific values tests
  NT2_TEST_EQUAL(abss(boost::simd::One<vT>())[0], boost::simd::One<T>());
  NT2_TEST_EQUAL(abss(boost::simd::Valmax<vT>())[0], boost::simd::Valmax<T>());
  NT2_TEST_EQUAL(abss(boost::simd::Valmin<vT>())[0], boost::simd::Valmin<T>());
  NT2_TEST_EQUAL(abss(boost::simd::Zero<vT>())[0], boost::simd::Zero<T>());
} // end of test for unsigned_int_

NT2_TEST_CASE_TPL ( abss_signed_int__1_0,  BOOST_SIMD_SIMD_INTEGRAL_SIGNED_TYPES)
{
  using boost::simd::abss;
  using boost::simd::tag::abss_;
  using boost::simd::load; 
  using boost::simd::native;
  using boost::simd::meta::cardinal_of;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef typename boost::dispatch::meta::upgrade<T>::type   u_t;
  typedef native<T,ext_t>                        n_t;
  typedef n_t                                     vT;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef native<iT,ext_t>                       ivT;
  typedef typename boost::dispatch::meta::call<abss_(vT)>::type r_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type sr_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type ssr_t;

  // specific values tests
  NT2_TEST_EQUAL(abss(boost::simd::Mone<vT>())[0], boost::simd::One<T>());
  NT2_TEST_EQUAL(abss(boost::simd::One<vT>())[0], boost::simd::One<T>());
  NT2_TEST_EQUAL(abss(boost::simd::Valmax<vT>())[0], boost::simd::Valmax<T>());
  NT2_TEST_EQUAL(abss(boost::simd::Valmin<vT>())[0], boost::simd::Valmax<T>());
  NT2_TEST_EQUAL(abss(boost::simd::Zero<vT>())[0], boost::simd::Zero<T>());
} // end of test for signed_int_
