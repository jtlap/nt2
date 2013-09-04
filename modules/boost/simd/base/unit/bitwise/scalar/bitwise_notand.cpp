//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/bitwise/include/functions/bitwise_notand.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/constant/constant.hpp>


NT2_TEST_CASE_TPL ( bitwise_notand_real,  BOOST_SIMD_REAL_TYPES)
{

  using boost::simd::bitwise_notand;
  using boost::simd::tag::bitwise_notand_;
  typedef typename boost::dispatch::meta::call<bitwise_notand_(T,T)>::type r_t;
  typedef T wished_r_t;


  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
#ifndef BOOST_SIMD_NO_INVALIDS
  NT2_TEST_EQUAL(bitwise_notand(boost::simd::Inf<T>(), boost::simd::Inf<T>()), boost::simd::Zero<r_t>());
  NT2_TEST_EQUAL(bitwise_notand(boost::simd::Minf<T>(), boost::simd::Minf<T>()), boost::simd::Zero<r_t>());
  NT2_TEST_EQUAL(bitwise_notand(boost::simd::Nan<T>(), boost::simd::Nan<T>()), boost::simd::Zero<r_t>());
#endif
  NT2_TEST_EQUAL(bitwise_notand(boost::simd::Zero<T>(), boost::simd::Zero<T>()), boost::simd::Zero<r_t>());
  NT2_TEST_EQUAL(bitwise_notand(boost::simd::Zero<T>(),boost::simd::One<T>()), boost::simd::One<r_t>());
} // end of test for floating_

NT2_TEST_CASE_TPL ( bitwise_notand_integer,  BOOST_SIMD_INTEGRAL_TYPES)
{

  using boost::simd::bitwise_notand;
  using boost::simd::tag::bitwise_notand_;
  typedef typename boost::dispatch::meta::call<bitwise_notand_(T,T)>::type r_t;
  typedef T wished_r_t;


  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
  NT2_TEST_EQUAL(bitwise_notand(boost::simd::One<T>(), boost::simd::One<T>()), boost::simd::Zero<r_t>());
  NT2_TEST_EQUAL(bitwise_notand(boost::simd::Zero<T>(), boost::simd::Zero<T>()), boost::simd::Zero<r_t>());
  NT2_TEST_EQUAL(bitwise_notand(boost::simd::Zero<T>(),boost::simd::One<T>()), boost::simd::One<r_t>());
} // end of test for integer_
