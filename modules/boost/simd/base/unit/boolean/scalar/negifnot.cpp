//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/boolean/include/functions/negifnot.hpp>
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

NT2_TEST_CASE_TPL ( negifnot_real__2_0,  BOOST_SIMD_REAL_TYPES)
{

  using boost::simd::negifnot;
  using boost::simd::tag::negifnot_;
  using boost::simd::logical;
  typedef typename boost::dispatch::meta::call<negifnot_(logical<T>,T)>::type r_t;
  typedef T wished_r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS( r_t, wished_r_t );

  // specific values tests
  NT2_TEST_EQUAL(negifnot(logical<T>(T(0)),T(1)), -1);
  NT2_TEST_EQUAL(negifnot(logical<T>(T(1)),T(1)), 1);
  NT2_TEST_EQUAL(negifnot(logical<T>(boost::simd::Inf<T>()),T(1)), 1);
  NT2_TEST_EQUAL(negifnot(logical<T>(boost::simd::Minf<T>()),T(1)), 1);
  NT2_TEST_EQUAL(negifnot(logical<T>(boost::simd::Nan<T>()),T(1)), 1);
  NT2_TEST_EQUAL(negifnot(logical<T>(boost::simd::Zero<T>()),T(1)), -1);
} // end of test for floating_

NT2_TEST_CASE_TPL ( negifnot_signed_int__2_0,  BOOST_SIMD_INTEGRAL_SIGNED_TYPES)
{

  using boost::simd::negifnot;
  using boost::simd::tag::negifnot_;
  using boost::simd::logical;
  typedef typename boost::dispatch::meta::call<negifnot_(logical<T>,T)>::type r_t;
  typedef T wished_r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS( r_t, wished_r_t );

  // specific values tests
  NT2_TEST_EQUAL(negifnot(logical<T>(T(0)),T(1)), -1);
  NT2_TEST_EQUAL(negifnot(logical<T>(T(1)),T(1)), 1);
} // end of test for signed_int_
