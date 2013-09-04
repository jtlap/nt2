//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/bitwise/include/functions/firstbitunset.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/include/constants/zero.hpp>
#include <boost/simd/include/constants/one.hpp>
#include <boost/simd/include/constants/two.hpp>
#include <boost/simd/include/constants/mone.hpp>
#include <boost/simd/include/constants/inf.hpp>
#include <boost/simd/include/constants/minf.hpp>
#include <boost/simd/include/constants/nan.hpp>
#include <boost/simd/include/constants/signmask.hpp>
#include <boost/simd/sdk/config.hpp>

NT2_TEST_CASE_TPL ( firstbitunset_real,  BOOST_SIMD_REAL_TYPES)
{

  using boost::simd::firstbitunset;
  using boost::simd::tag::firstbitunset_;
  typedef typename boost::dispatch::meta::call<firstbitunset_(T)>::type r_t;
  typedef typename boost::dispatch::meta::as_integer<T, unsigned>::type wished_r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
#ifndef BOOST_SIMD_NO_INVALIDS
  NT2_TEST_EQUAL(firstbitunset(boost::simd::Inf<T>()), boost::simd::One<r_t>());
  NT2_TEST_EQUAL(firstbitunset(boost::simd::Minf<T>()), boost::simd::One<r_t>());
  NT2_TEST_EQUAL(firstbitunset(boost::simd::Nan<T>()), boost::simd::Zero<r_t>());
#endif
  NT2_TEST_EQUAL(firstbitunset(boost::simd::Signmask<T>()), boost::simd::One<r_t>());
  NT2_TEST_EQUAL(firstbitunset(boost::simd::Zero<T>()), boost::simd::One<r_t>());
} // end of test for floating_

NT2_TEST_CASE_TPL ( firstbitunset_signed_int,  BOOST_SIMD_INTEGRAL_SIGNED_TYPES)
{

  using boost::simd::firstbitunset;
  using boost::simd::tag::firstbitunset_;
  typedef typename boost::dispatch::meta::call<firstbitunset_(T)>::type r_t;
  typedef typename boost::dispatch::meta::as_integer<T, unsigned>::type wished_r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
  NT2_TEST_EQUAL(firstbitunset(boost::simd::One<T>()), boost::simd::Two<r_t>());
  NT2_TEST_EQUAL(firstbitunset(boost::simd::Signmask<T>()), boost::simd::One<r_t>());
  NT2_TEST_EQUAL(firstbitunset(boost::simd::Zero<T>()), boost::simd::One<r_t>());
} // end of test for signed_int_

NT2_TEST_CASE_TPL ( firstbitunset_unsigned_int,  BOOST_SIMD_UNSIGNED_TYPES)
{

  using boost::simd::firstbitunset;
  using boost::simd::tag::firstbitunset_;
  typedef typename boost::dispatch::meta::call<firstbitunset_(T)>::type r_t;
  typedef typename boost::dispatch::meta::as_integer<T, unsigned>::type wished_r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
  NT2_TEST_EQUAL(firstbitunset(boost::simd::One<T>()), boost::simd::Two<r_t>());
  NT2_TEST_EQUAL(firstbitunset(boost::simd::Zero<T>()), boost::simd::One<r_t>());
} // end of test for unsigned_int_
