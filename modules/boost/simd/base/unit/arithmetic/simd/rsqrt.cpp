//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/arithmetic/include/functions/rsqrt.hpp>
#include <boost/simd/sdk/simd/io.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <boost/simd/constant/constant.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>

NT2_TEST_CASE_TPL ( rsqrt_real, BOOST_SIMD_SIMD_REAL_TYPES)
{
  using boost::simd::rsqrt;
  using boost::simd::tag::rsqrt_;
  using boost::simd::native;
  using boost::simd::meta::cardinal_of;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                        vT;

  // specific values tests
  NT2_TEST_ULP_EQUAL(rsqrt(boost::simd::Inf<vT>()), boost::simd::Zero<vT>(), 0.5);
  NT2_TEST_ULP_EQUAL(rsqrt(boost::simd::Minf<vT>()), boost::simd::Nan<vT>(), 0.5);
  NT2_TEST_ULP_EQUAL(rsqrt(boost::simd::Mone<vT>()), boost::simd::Nan<vT>(), 0.5);
  NT2_TEST_ULP_EQUAL(rsqrt(boost::simd::Nan<vT>()), boost::simd::Nan<vT>(), 0.5);
  NT2_TEST_ULP_EQUAL(rsqrt(boost::simd::One<vT>()), boost::simd::One<vT>(), 0.5);
  NT2_TEST_ULP_EQUAL(rsqrt(boost::simd::Zero<vT>()), boost::simd::Inf<vT>(), 0.5);
  NT2_TEST_ULP_EQUAL(rsqrt(boost::simd::Four<vT>()), boost::simd::Half<vT>(), 0.5);
} // end of test for floating_
