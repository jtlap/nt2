//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/arithmetic/include/functions/logical_xor.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/include/constants/one.hpp>
#include <boost/simd/include/constants/mone.hpp>
#include <boost/simd/include/constants/two.hpp>
#include <boost/simd/include/constants/mtwo.hpp>
#include <boost/simd/include/constants/inf.hpp>
#include <boost/simd/include/constants/minf.hpp>
#include <boost/simd/include/constants/nan.hpp>
#include <boost/simd/include/constants/false.hpp>
#include <boost/simd/include/constants/true.hpp>
#include <boost/simd/sdk/config.hpp>
#include <boost/simd/sdk/simd/io.hpp>

NT2_TEST_CASE_TPL ( logical_xor_real__2_0,  BOOST_SIMD_SIMD_REAL_TYPES)
{
  using boost::simd::logical_xor;
  using boost::simd::tag::logical_xor_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;
  typedef typename boost::dispatch::meta::call<logical_xor_(vT,vT)>::type r_t;

 //  // specific values tests
#ifndef BOOST_SIMD_NO_INVALIDS
  NT2_TEST_EQUAL(logical_xor(boost::simd::Inf<vT>(), boost::simd::Inf<vT>()), boost::simd::False<r_t>());
  NT2_TEST_EQUAL(logical_xor(boost::simd::Minf<vT>(), boost::simd::Minf<vT>()), boost::simd::False<r_t>());
  NT2_TEST_EQUAL(logical_xor(boost::simd::Nan<vT>(), boost::simd::Nan<vT>()), boost::simd::False<r_t>());
#endif
  NT2_TEST_EQUAL(logical_xor(boost::simd::Mone<vT>(), boost::simd::Mone<vT>()), boost::simd::False<r_t>());
  NT2_TEST_EQUAL(logical_xor(boost::simd::One<vT>(), boost::simd::One<vT>()), boost::simd::False<r_t>());
  NT2_TEST_EQUAL(logical_xor(boost::simd::Zero<vT>(), boost::simd::Zero<vT>()), boost::simd::False<r_t>());
  NT2_TEST_EQUAL(logical_xor(boost::simd::splat<vT>(0),boost::simd::splat<vT>(1)), boost::simd::True<r_t>());
  NT2_TEST_EQUAL(logical_xor(boost::simd::splat<vT>(3),boost::simd::splat<vT>(0)), boost::simd::True<r_t>());
 } // end of test for floating_
