//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/arithmetic/include/functions/sqrt1pm1.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/include/constants/real.hpp>
#include <boost/simd/include/constants/infinites.hpp>
#include <boost/dispatch/functor/meta/call.hpp>

#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>

NT2_TEST_CASE_TPL ( sqrt1pm1_real__1_0,  BOOST_SIMD_REAL_TYPES)
{
  using boost::simd::sqrt1pm1;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                        vT;
  typedef typename boost::dispatch::meta::call<sqrt1pm1_(vT)>::type r_t;
  typedef typename boost::dispatch::meta::call<sqrt1pm1_(T)>::type sr_t;

  // specific values tests
  NT2_TEST_ULP_EQUAL(sqrt1pm1(boost::simd::Inf<vT>())[0], boost::simd::Inf<sr_t>(), 0);
  NT2_TEST_ULP_EQUAL(sqrt1pm1(boost::simd::Minf<vT>())[0], boost::simd::Nan<sr_t>(), 0);
  NT2_TEST_ULP_EQUAL(sqrt1pm1(boost::simd::Mone<vT>())[0], boost::simd::Mone<sr_t>(), 0);
  NT2_TEST_ULP_EQUAL(sqrt1pm1(boost::simd::Nan<vT>())[0], boost::simd::Nan<sr_t>(), 0);
  NT2_TEST_ULP_EQUAL(sqrt1pm1(boost::simd::One<vT>())[0], boost::simd::Sqrt_2<sr_t>()-boost::simd::One<sr_t>(), 2);
  NT2_TEST_ULP_EQUAL(sqrt1pm1(boost::simd::Zero<vT>())[0], boost::simd::Zero<sr_t>(), 0);
} // end of test for floating_
