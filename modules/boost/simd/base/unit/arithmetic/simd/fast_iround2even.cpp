//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/arithmetic/include/functions/fast_iround2even.hpp>
#include <boost/simd/sdk/simd/io.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/constant/constant.hpp>
#include <boost/simd/include/constants/zero.hpp>
#include <boost/simd/include/constants/one.hpp>
#include <boost/simd/include/constants/inf.hpp>
#include <boost/simd/include/constants/zero.hpp>
#include <boost/simd/include/constants/minf.hpp>
#include <boost/simd/include/constants/mone.hpp>
#include <boost/simd/include/constants/nan.hpp>
#include <boost/simd/include/constants/three.hpp>
#include <boost/simd/include/constants/two.hpp>
#include <boost/simd/operator/include/functions/make.hpp>
NT2_TEST_CASE_TPL ( fast_iround2even_real, BOOST_SIMD_SIMD_REAL_TYPES)
{
  using boost::simd::fast_iround2even;
  using boost::simd::tag::fast_iround2even_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;
  typedef typename boost::dispatch::meta::call<fast_iround2even_(vT)>::type r_t;

  // specific values tests
  NT2_TEST_EQUAL(fast_iround2even(boost::simd::splat<vT>(1.4)), boost::simd::One<r_t>());
  NT2_TEST_EQUAL(fast_iround2even(boost::simd::splat<vT>(1.5)), boost::simd::Two<r_t>());
  NT2_TEST_EQUAL(fast_iround2even(boost::simd::splat<vT>(1.6)), boost::simd::Two<r_t>());
  NT2_TEST_EQUAL(fast_iround2even(boost::simd::splat<vT>(-2.5)),-boost::simd::Two<r_t>());
  NT2_TEST_EQUAL(fast_iround2even(boost::simd::splat<vT>(-1.4)), -boost::simd::One<r_t>());
  NT2_TEST_EQUAL(fast_iround2even(boost::simd::splat<vT>(-1.5)), -boost::simd::Two<r_t>());
  NT2_TEST_EQUAL(fast_iround2even(boost::simd::splat<vT>(-1.6)), -boost::simd::Two<r_t>());
  NT2_TEST_EQUAL(fast_iround2even(boost::simd::splat<vT>(-2.5)), -boost::simd::Two<r_t>());
  NT2_TEST_EQUAL(fast_iround2even(boost::simd::Half<vT>()), boost::simd::Zero<r_t>());
  NT2_TEST_EQUAL(fast_iround2even(boost::simd::Mhalf<vT>()), boost::simd::Zero<r_t>());
  NT2_TEST_EQUAL(fast_iround2even(boost::simd::Mone<vT>()), boost::simd::Mone<r_t>());
  NT2_TEST_EQUAL(fast_iround2even(boost::simd::One<vT>()), boost::simd::One<r_t>());
  NT2_TEST_EQUAL(fast_iround2even(boost::simd::Zero<vT>()), boost::simd::Zero<r_t>());
} // end of test for floating_
