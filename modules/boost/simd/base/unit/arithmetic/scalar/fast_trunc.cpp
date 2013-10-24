//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/arithmetic/include/functions/fast_trunc.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/include/constants/zero.hpp>
#include <boost/simd/include/constants/one.hpp>
#include <boost/simd/include/constants/mone.hpp>
#include <boost/simd/include/constants/inf.hpp>
#include <boost/simd/include/constants/minf.hpp>
#include <boost/simd/include/constants/nan.hpp>
#include <boost/simd/include/constants/pi.hpp>
#include <boost/simd/include/constants/three.hpp>
#include <boost/simd/sdk/config.hpp>

NT2_TEST_CASE_TPL ( fast_trunc_real,  BOOST_SIMD_REAL_TYPES)
{

  using boost::simd::fast_trunc;
  using boost::simd::tag::fast_trunc_;
  typedef typename boost::dispatch::meta::call<fast_trunc_(T)>::type r_t;
  typedef T wished_r_t;

  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
  NT2_TEST_EQUAL(fast_trunc(boost::simd::One<T>()), boost::simd::One<T>());
  NT2_TEST_EQUAL(fast_trunc(boost::simd::Mone<T>()), boost::simd::Mone<T>());
  NT2_TEST_EQUAL(fast_trunc(boost::simd::Zero<T>()), boost::simd::Zero<T>());
  NT2_TEST_EQUAL(fast_trunc(boost::simd::Pi<T>()), boost::simd::Three<T>());
  NT2_TEST_EQUAL(fast_trunc(T(1.4)), T(1));
  NT2_TEST_EQUAL(fast_trunc(T(1.5)), T(1));
  NT2_TEST_EQUAL(fast_trunc(T(1.6)), T(1));
  NT2_TEST_EQUAL(fast_trunc(T(2.5)), T(2));
  NT2_TEST_EQUAL(fast_trunc(T(-1.4)), T(-1));
  NT2_TEST_EQUAL(fast_trunc(T(-1.5)), T(-1));
  NT2_TEST_EQUAL(fast_trunc(T(-1.6)), T(-1));
  NT2_TEST_EQUAL(fast_trunc(T(-2.5)), T(-2));
} // end of test for floating_

NT2_TEST_CASE_TPL ( fast_trunc_unsigned_int,  BOOST_SIMD_UNSIGNED_TYPES)
{

  using boost::simd::fast_trunc;
  using boost::simd::tag::fast_trunc_;
  typedef typename boost::dispatch::meta::call<fast_trunc_(T)>::type r_t;
  typedef T wished_r_t;


  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
  NT2_TEST_EQUAL(fast_trunc(boost::simd::One<T>()), boost::simd::One<T>());
  NT2_TEST_EQUAL(fast_trunc(boost::simd::Zero<T>()), boost::simd::Zero<T>());
} // end of test for unsigned_int_

NT2_TEST_CASE_TPL ( fast_trunc_signed_int,  BOOST_SIMD_INTEGRAL_SIGNED_TYPES)
{

  using boost::simd::fast_trunc;
  using boost::simd::tag::fast_trunc_;
  typedef typename boost::dispatch::meta::call<fast_trunc_(T)>::type r_t;
  typedef T wished_r_t;


  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
  NT2_TEST_EQUAL(fast_trunc(boost::simd::Mone<T>()), boost::simd::Mone<T>());
  NT2_TEST_EQUAL(fast_trunc(boost::simd::One<T>()), boost::simd::One<T>());
  NT2_TEST_EQUAL(fast_trunc(boost::simd::Zero<T>()), boost::simd::Zero<T>());
} // end of test for signed_int_

