//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/bitwise/include/functions/popcnt.hpp>
#include <boost/simd/sdk/simd/native.hpp>

#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/include/functions/splat.hpp>
#include <boost/simd/include/constants/one.hpp>
#include <boost/simd/include/constants/two.hpp>
#include <boost/simd/include/constants/three.hpp>
#include <boost/simd/include/constants/mone.hpp>
#include <boost/simd/include/constants/zero.hpp>
#include <boost/simd/include/constants/nan.hpp>
#include <boost/simd/sdk/config.hpp>
#include <boost/simd/sdk/simd/io.hpp>

NT2_TEST_CASE_TPL ( popcnt_real,  BOOST_SIMD_SIMD_REAL_TYPES)
{
  using boost::simd::popcnt;
  using boost::simd::tag::popcnt_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;
  typedef typename boost::dispatch::meta::call<popcnt_(vT)>::type r_t;

  // specific values tests
  NT2_TEST_EQUAL(popcnt(boost::simd::Nan<vT>()), boost::simd::splat<r_t>(sizeof(T)*8));
  NT2_TEST_EQUAL(popcnt(boost::simd::Zero<vT>()), boost::simd::Zero<r_t>());
} // end of test for floating_

NT2_TEST_CASE_TPL ( popcnt_integer,  BOOST_SIMD_SIMD_INTEGRAL_TYPES)
{
  using boost::simd::popcnt;
  using boost::simd::tag::popcnt_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;
  typedef typename boost::dispatch::meta::call<popcnt_(vT)>::type r_t;

  // specific values tests
  NT2_TEST_EQUAL(popcnt(boost::simd::Two<vT>()), boost::simd::One<r_t>());
  NT2_TEST_EQUAL(popcnt(boost::simd::Three<vT>()), boost::simd::Two<r_t>());
  NT2_TEST_EQUAL(popcnt(boost::simd::Mone<vT>()), boost::simd::splat<r_t>(sizeof(T)*8));
  NT2_TEST_EQUAL(popcnt(boost::simd::One<vT>()), boost::simd::One<r_t>());
  NT2_TEST_EQUAL(popcnt(boost::simd::Zero<vT>()), boost::simd::Zero<r_t>());
} // end of test for integer_
