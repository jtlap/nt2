//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/arithmetic/include/functions/ceil.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/include/constants/one.hpp>
#include <boost/simd/include/constants/mone.hpp>
#include <boost/simd/include/constants/inf.hpp>
#include <boost/simd/include/constants/minf.hpp>
#include <boost/simd/include/constants/nan.hpp>
#include <boost/simd/include/constants/pi.hpp>
#include <boost/simd/include/constants/four.hpp>
#include <boost/simd/sdk/config.hpp>
#include <boost/simd/sdk/simd/io.hpp>
#include <boost/simd/include/functions/splat.hpp>

NT2_TEST_CASE_TPL ( ceil_real__1_0,  BOOST_SIMD_SIMD_REAL_TYPES)
{
  using boost::simd::ceil;
  using boost::simd::tag::ceil_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;
  typedef typename boost::dispatch::meta::call<ceil_(vT)>::type r_t;

  // specific values tests
#ifndef BOOST_SIMD_NO_INVALIDS
  NT2_TEST_EQUAL(ceil(boost::simd::Inf<vT>()), boost::simd::Inf<r_t>());
  NT2_TEST_EQUAL(ceil(boost::simd::Minf<vT>()), boost::simd::Minf<r_t>());
  NT2_TEST_EQUAL(ceil(boost::simd::Nan<vT>()), boost::simd::Nan<r_t>());
#endif
  NT2_TEST_EQUAL(ceil(boost::simd::Mone<vT>()), boost::simd::Mone<r_t>());
  NT2_TEST_EQUAL(ceil(boost::simd::One<vT>()), boost::simd::One<r_t>());
  NT2_TEST_EQUAL(ceil(boost::simd::Zero<vT>()), boost::simd::Zero<r_t>());
  NT2_TEST_EQUAL(ceil(boost::simd::splat<vT>(-1.1)), boost::simd::splat<r_t>(-1));
  NT2_TEST_EQUAL(ceil(boost::simd::splat<vT>(1.1)), boost::simd::splat<r_t>(2));
} // end of test for floating_

NT2_TEST_CASE_TPL ( ceil_si,  BOOST_SIMD_SIMD_INTEGRAL_SIGNED_TYPES)
{
  using boost::simd::ceil;
  using boost::simd::tag::ceil_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;
  typedef typename boost::dispatch::meta::call<ceil_(vT)>::type r_t;

  // specific values tests
  NT2_TEST_EQUAL(ceil(boost::simd::Mone<vT>()), boost::simd::Mone<r_t>());
  NT2_TEST_EQUAL(ceil(boost::simd::One<vT>()), boost::simd::One<r_t>());
  NT2_TEST_EQUAL(ceil(boost::simd::Zero<vT>()), boost::simd::Zero<r_t>());
} // end of test for floating_

NT2_TEST_CASE_TPL ( ceil_ui,  BOOST_SIMD_SIMD_UNSIGNED_TYPES)
{
  using boost::simd::ceil;
  using boost::simd::tag::ceil_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;
  typedef typename boost::dispatch::meta::call<ceil_(vT)>::type r_t;

  // specific values tests
  NT2_TEST_EQUAL(ceil(boost::simd::One<vT>()), boost::simd::One<r_t>());
  NT2_TEST_EQUAL(ceil(boost::simd::Zero<vT>()), boost::simd::Zero<r_t>());
} // end of test for floating_
