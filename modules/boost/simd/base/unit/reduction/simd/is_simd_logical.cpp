//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/reduction/include/functions/is_simd_logical.hpp>
#include <boost/simd/include/functions/negate.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/sdk/simd/logical.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/constant/constant.hpp>

NT2_TEST_CASE_TPL ( is_simd_logical_real__1_0,  BOOST_SIMD_SIMD_REAL_TYPES)
{
  using boost::simd::is_simd_logical;
  using boost::simd::tag::is_simd_logical_;
  using boost::simd::native;
  using boost::simd::meta::cardinal_of;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                        n_t;
  typedef n_t                                     vT;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef native<iT,ext_t>                       ivT;
  typedef typename boost::dispatch::meta::call<is_simd_logical_(vT)>::type r_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type ssr_t;
  typedef boost::simd::logical<T> vsr_t;

  // specific values tests
  NT2_TEST_EQUAL(is_simd_logical(-boost::simd::Nan<vT>()), vsr_t(false));
  NT2_TEST_EQUAL(is_simd_logical(boost::simd::Inf<vT>()), vsr_t(false));
  NT2_TEST_EQUAL(is_simd_logical(boost::simd::Minf<vT>()), vsr_t(false));
  NT2_TEST_EQUAL(is_simd_logical(boost::simd::Mone<vT>()), vsr_t(false));
  NT2_TEST_EQUAL(is_simd_logical(boost::simd::Nan<vT>()), vsr_t(true));
  NT2_TEST_EQUAL(is_simd_logical(boost::simd::One<vT>()), vsr_t(false));
  NT2_TEST_EQUAL(is_simd_logical(boost::simd::Zero<vT>()), vsr_t(true));
} // end of test for floating_
