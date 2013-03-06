//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 boost.simd.operator toolbox - compare_not_equal/simd Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of boost.simd.operator components in simd mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 18/02/2011
///
#include <boost/simd/toolbox/reduction/include/functions/compare_not_equal.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/include/functions/any.hpp>

#include <boost/type_traits/is_same.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/toolbox/constant/constant.hpp>
#include <boost/simd/sdk/memory/is_aligned.hpp>
#include <boost/simd/sdk/memory/aligned_type.hpp>
#include <boost/simd/include/functions/load.hpp>


NT2_TEST_CASE_TPL ( compare_not_equal_real__2_0,  BOOST_SIMD_SIMD_REAL_TYPES)
{
  using boost::simd::compare_not_equal;
  using boost::simd::tag::compare_not_equal_;
  using boost::simd::load;
  using boost::simd::native;
  using boost::simd::meta::cardinal_of;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef typename boost::dispatch::meta::upgrade<T>::type   u_t;
  typedef native<T,ext_t>                        n_t;
  typedef n_t                                     vT;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef native<iT,ext_t>                       ivT;
  typedef typename boost::dispatch::meta::call<compare_not_equal_(vT,vT)>::type r_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type sr_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type ssr_t;

  // specific values tests
  NT2_TEST_EQUAL(compare_not_equal(boost::simd::Inf<vT>(), boost::simd::Inf<vT>()), r_t(false));
  NT2_TEST_EQUAL(compare_not_equal(boost::simd::Minf<vT>(), boost::simd::Minf<vT>()), r_t(false));
  NT2_TEST_EQUAL(compare_not_equal(boost::simd::Nan<vT>(), boost::simd::Nan<vT>()), r_t(true));
  NT2_TEST_EQUAL(compare_not_equal(boost::simd::One<vT>(),boost::simd::Zero<vT>()), r_t(true));
  NT2_TEST_EQUAL(compare_not_equal(boost::simd::Zero<vT>(), boost::simd::Zero<vT>()), r_t(false));
} // end of test for floating_

NT2_TEST_CASE_TPL ( compare_not_equal_integer__2_0,  BOOST_SIMD_SIMD_INTEGRAL_TYPES)
{
  using boost::simd::compare_not_equal;
  using boost::simd::tag::compare_not_equal_;
  using boost::simd::load;
  using boost::simd::native;
  using boost::simd::meta::cardinal_of;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef typename boost::dispatch::meta::upgrade<T>::type   u_t;
  typedef native<T,ext_t>                        n_t;
  typedef n_t                                     vT;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef native<iT,ext_t>                       ivT;
  typedef typename boost::dispatch::meta::call<compare_not_equal_(vT,vT)>::type r_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type sr_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type ssr_t;

  // specific values tests
  NT2_TEST_EQUAL(compare_not_equal(boost::simd::One<vT>(), boost::simd::One<vT>()), r_t(false));
  NT2_TEST_EQUAL(compare_not_equal(boost::simd::One<vT>(),boost::simd::Zero<vT>()), r_t(true));
  NT2_TEST_EQUAL(compare_not_equal(boost::simd::Zero<vT>(), boost::simd::Zero<vT>()), r_t(false));
} // end of test for integer_
