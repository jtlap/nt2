//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 arithmetic toolbox - tofloat/simd Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of arithmetic components in simd mode
//////////////////////////////////////////////////////////////////////////////
///
#include <nt2/toolbox/arithmetic/include/functions/tofloat.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <nt2/toolbox/constant/constant.hpp>
#include <nt2/include/functions/splat.hpp>
#include <nt2/sdk/meta/scalar_of.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <boost/dispatch/meta/strip.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>


NT2_TEST_CASE_TPL ( tofloat_real__1_0,  NT2_SIMD_REAL_TYPES)
{
  using nt2::tofloat;
  using nt2::tag::tofloat_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                        n_t;
  typedef n_t                                     vT;
  typedef typename boost::dispatch::meta::as_floating<T>::type fT;
  typedef native<fT,ext_t>                       fvT;
  typedef typename boost::dispatch::meta::strip<typename boost::dispatch::meta::call<tofloat_(vT)>::type>::type r_t;
  typedef typename nt2::meta::scalar_of<r_t>::type sr_t;

  NT2_TEST_TYPE_IS(r_t, fvT);

  // specific values tests
  NT2_TEST_EQUAL(tofloat(nt2::Inf<vT>())[0], nt2::Inf<sr_t>());
  NT2_TEST_EQUAL(tofloat(nt2::Minf<vT>())[0], nt2::Minf<sr_t>());
  NT2_TEST_EQUAL(tofloat(nt2::Mone<vT>())[0], nt2::Mone<sr_t>());
  NT2_TEST_EQUAL(tofloat(nt2::Nan<vT>())[0], nt2::Nan<sr_t>());
  NT2_TEST_EQUAL(tofloat(nt2::One<vT>())[0], nt2::One<sr_t>());
  NT2_TEST_EQUAL(tofloat(nt2::Zero<vT>())[0], nt2::Zero<sr_t>());
  NT2_TEST_EQUAL(tofloat(nt2::Two<vT>())[0], nt2::Two<sr_t>());
} // end of test for floating_

NT2_TEST_CASE_TPL ( tofloat_int_convert__1_0,  NT2_SIMD_INT_CONVERT_TYPES)
{
  using nt2::tofloat;
  using nt2::tag::tofloat_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                        n_t;
  typedef n_t                                     vT;
  typedef typename boost::dispatch::meta::as_floating<T>::type fT;
  typedef native<fT,ext_t>                       fvT;
  typedef typename boost::dispatch::meta::strip<typename boost::dispatch::meta::call<tofloat_(vT)>::type>::type r_t;
  typedef typename nt2::meta::scalar_of<r_t>::type sr_t;
  typedef typename nt2::meta::scalar_of<r_t>::type ssr_t;

  NT2_TEST_TYPE_IS(r_t, fvT);

  // specific values tests
  NT2_TEST_EQUAL(tofloat(nt2::Mone<vT>())[0], nt2::Mone<sr_t>());
  NT2_TEST_EQUAL(tofloat(nt2::One<vT>())[0], nt2::One<sr_t>());
  NT2_TEST_EQUAL(tofloat(nt2::Zero<vT>())[0], nt2::Zero<sr_t>());
  NT2_TEST_EQUAL(tofloat(nt2::Two<vT>())[0], nt2::Two<sr_t>());
  NT2_TEST_EQUAL(tofloat(nt2::Valmax<vT>())[0], sr_t(nt2::Valmax<T>()));
  NT2_TEST_EQUAL(tofloat(nt2::Valmin<vT>())[0], sr_t(nt2::Valmin<T>()));

} // end of test for int_convert_

NT2_TEST_CASE_TPL ( tofloat_uint_convert__1_0,  NT2_SIMD_UINT_CONVERT_TYPES)
{
  using nt2::tofloat;
  using nt2::tag::tofloat_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                        n_t;
  typedef n_t                                     vT;
  typedef typename boost::dispatch::meta::as_floating<T>::type fT;
  typedef native<fT,ext_t>                       fvT;
  typedef typename boost::dispatch::meta::strip<typename boost::dispatch::meta::call<tofloat_(vT)>::type>::type r_t;
  typedef typename nt2::meta::scalar_of<r_t>::type sr_t;
  typedef typename nt2::meta::scalar_of<r_t>::type ssr_t;

  NT2_TEST_TYPE_IS(r_t, fvT);

  // specific values tests
  NT2_TEST_EQUAL(tofloat(nt2::One<vT>())[0], nt2::One<sr_t>());
  NT2_TEST_EQUAL(tofloat(nt2::Zero<vT>())[0], nt2::Zero<sr_t>());
  NT2_TEST_EQUAL(tofloat(nt2::Two<vT>())[0], nt2::Two<sr_t>());
  NT2_TEST_EQUAL(tofloat(nt2::Valmax<vT>())[0], sr_t(nt2::Valmax<T>()));

} // end of test for uint_convert_

#ifdef BOOST_SIMD_HAS_SSE2_SUPPORT
NT2_TEST_CASE( tofloat_long_long )
{
  using nt2::tofloat;
  using nt2::splat;
  typedef boost::simd::native<long long, boost::simd::tag::sse_> vT;

  long long i = boost::simd::Valmin<long long>();
  NT2_TEST_EQUAL(tofloat(i), tofloat(splat<vT>(i))[0]);
}
#endif
