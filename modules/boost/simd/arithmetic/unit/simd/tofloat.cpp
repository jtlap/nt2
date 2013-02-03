//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 boost.simd.arithmetic toolbox - tofloat/simd Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of boost.simd.arithmetic components in simd mode
//////////////////////////////////////////////////////////////////////////////
/// created by jt the 04/12/2010
///
#include <boost/simd/toolbox/arithmetic/include/functions/tofloat.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/toolbox/constant/constant.hpp>
#include <boost/simd/sdk/memory/is_aligned.hpp>
#include <boost/simd/sdk/memory/aligned_type.hpp>
#include <boost/simd/include/functions/load.hpp>


NT2_TEST_CASE_TPL ( tofloat_real__1_0,  BOOST_SIMD_SIMD_REAL_TYPES)
{
  using boost::simd::tofloat;
  using boost::simd::tag::tofloat_;
  using boost::simd::load;
  using boost::simd::native;
  using boost::simd::meta::cardinal_of;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef typename boost::dispatch::meta::upgrade<T>::type   u_t;
  typedef native<T,ext_t>                        n_t;
  typedef n_t                                     vT;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef native<iT,ext_t>                       ivT;
  typedef typename boost::dispatch::meta::strip<typename boost::dispatch::meta::call<tofloat_(vT)>::type>::type r_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type sr_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type ssr_t;

  // specific values tests
  NT2_TEST_EQUAL(tofloat(boost::simd::Inf<vT>())[0], boost::simd::Inf<sr_t>());
  NT2_TEST_EQUAL(tofloat(boost::simd::Minf<vT>())[0], boost::simd::Minf<sr_t>());
  NT2_TEST_EQUAL(tofloat(boost::simd::Mone<vT>())[0], boost::simd::Mone<sr_t>());
  NT2_TEST_EQUAL(tofloat(boost::simd::Nan<vT>())[0], boost::simd::Nan<sr_t>());
  NT2_TEST_EQUAL(tofloat(boost::simd::One<vT>())[0], boost::simd::One<sr_t>());
  NT2_TEST_EQUAL(tofloat(boost::simd::Zero<vT>())[0], boost::simd::Zero<sr_t>());
  NT2_TEST_EQUAL(tofloat(boost::simd::Two<vT>())[0], boost::simd::Two<sr_t>());
} // end of test for floating_

NT2_TEST_CASE_TPL ( tofloat_int_convert__1_0,  BOOST_SIMD_SIMD_INT_CONVERT_TYPES)
{
  using boost::simd::tofloat;
  using boost::simd::tag::tofloat_;
  using boost::simd::load;
  using boost::simd::native;
  using boost::simd::meta::cardinal_of;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef typename boost::dispatch::meta::upgrade<T>::type   u_t;
  typedef native<T,ext_t>                        n_t;
  typedef n_t                                     vT;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef native<iT,ext_t>                       ivT;
  typedef typename boost::dispatch::meta::strip<typename boost::dispatch::meta::call<tofloat_(vT)>::type>::type r_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type sr_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type ssr_t;

  NT2_TEST_EQUAL(tofloat(boost::simd::Mone<vT>())[0], boost::simd::Mone<sr_t>());
  NT2_TEST_EQUAL(tofloat(boost::simd::One<vT>())[0], boost::simd::One<sr_t>());
  NT2_TEST_EQUAL(tofloat(boost::simd::Zero<vT>())[0], boost::simd::Zero<sr_t>());
  NT2_TEST_EQUAL(tofloat(boost::simd::Two<vT>())[0], boost::simd::Two<sr_t>());
  NT2_TEST_EQUAL(tofloat(boost::simd::Valmax<vT>())[0], sr_t(boost::simd::Valmax<T>()));
  NT2_TEST_EQUAL(tofloat(boost::simd::Valmin<vT>())[0], sr_t(boost::simd::Valmin<T>()));

  // specific values tests
} // end of test for int_convert_

NT2_TEST_CASE_TPL ( tofloat_uint_convert__1_0,  BOOST_SIMD_SIMD_UINT_CONVERT_TYPES)
{
  using boost::simd::tofloat;
  using boost::simd::tag::tofloat_;
  using boost::simd::load;
  using boost::simd::native;
  using boost::simd::meta::cardinal_of;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef typename boost::dispatch::meta::upgrade<T>::type   u_t;
  typedef native<T,ext_t>                        n_t;
  typedef n_t                                     vT;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef native<iT,ext_t>                       ivT;
  typedef typename boost::dispatch::meta::strip<typename boost::dispatch::meta::call<tofloat_(vT)>::type>::type r_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type sr_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type ssr_t;
  NT2_TEST_EQUAL(tofloat(boost::simd::One<vT>())[0], boost::simd::One<sr_t>());
  NT2_TEST_EQUAL(tofloat(boost::simd::Zero<vT>())[0], boost::simd::Zero<sr_t>());
  NT2_TEST_EQUAL(tofloat(boost::simd::Two<vT>())[0], boost::simd::Two<sr_t>());
  NT2_TEST_EQUAL(tofloat(boost::simd::Valmax<vT>())[0], sr_t(boost::simd::Valmax<T>()));

  // specific values tests
} // end of test for uint_convert_

#ifdef BOOST_SIMD_HAS_SSE2_SUPPORT
NT2_TEST_CASE( tofloat_long_long )
{
  using boost::simd::tofloat;
  using boost::simd::splat;
  typedef boost::simd::native<long long, boost::simd::tag::sse_> vT;

  long long i = boost::simd::Valmin<long long>();
  NT2_TEST_EQUAL(tofloat(i), tofloat(splat<vT>(i))[0]);
}
#endif
