//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/boolean/include/functions/seladd.hpp>
#include <boost/simd/sdk/simd/io.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

#include <boost/simd/include/constants/one.hpp>
#include <boost/simd/include/constants/inf.hpp>
#include <boost/simd/include/constants/zero.hpp>
#include <boost/simd/include/constants/minf.hpp>
#include <boost/simd/include/constants/mone.hpp>
#include <boost/simd/include/constants/nan.hpp>
#include <boost/simd/include/constants/allbits.hpp>

NT2_TEST_CASE_TPL ( seladd_real__3_0,  BOOST_SIMD_REAL_TYPES)
{

  using boost::simd::seladd;
  using boost::simd::tag::seladd_;
  using boost::simd::logical;
  typedef typename boost::dispatch::meta::call<seladd_(logical<T>,T,T)>::type r_t;
  typedef T wished_r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS( r_t, wished_r_t );

  // specific values tests
  NT2_TEST_EQUAL(seladd(logical<T>(T(0)),T(1),T(2)), T(1));
  NT2_TEST_EQUAL(seladd(logical<T>(boost::simd::Nan<T>()),T(1),T(2)), T(3));
  NT2_TEST_EQUAL(seladd(logical<T>(boost::simd::Nan<T>()),boost::simd::Inf<T>(),boost::simd::Inf<T>()), boost::simd::Inf<r_t>());
  NT2_TEST_EQUAL(seladd(logical<T>(boost::simd::Nan<T>()),boost::simd::Minf<T>(),boost::simd::Minf<T>()), boost::simd::Minf<r_t>());
  NT2_TEST_EQUAL(seladd(logical<T>(boost::simd::Nan<T>()),boost::simd::Nan<T>(),boost::simd::Nan<T>()), boost::simd::Nan<r_t>());
  NT2_TEST_EQUAL(seladd(logical<T>(boost::simd::Nan<T>()),boost::simd::Zero<T>(),boost::simd::Zero<T>()), boost::simd::Zero<r_t>());
} // end of test for floating_

NT2_TEST_CASE_TPL ( seladd_integer__3_0,  BOOST_SIMD_INTEGRAL_TYPES)
{

  using boost::simd::seladd;
  using boost::simd::tag::seladd_;
  using boost::simd::logical;
  typedef typename boost::dispatch::meta::call<seladd_(logical<T>,T,T)>::type r_t;
  typedef T wished_r_t;


  // return type conformity test
  NT2_TEST_TYPE_IS( r_t, wished_r_t );

  // specific values tests
  NT2_TEST_EQUAL(seladd(logical<T>(T(-1)),T(1),T(2)), T(3));
  NT2_TEST_EQUAL(seladd(logical<T>(T(0)),T(1),T(2)), T(1));
  NT2_TEST_EQUAL(seladd(logical<T>(boost::simd::Zero<T>()),boost::simd::Zero<T>(),boost::simd::Zero<T>()), boost::simd::Zero<r_t>());
} // end of test for integer_
