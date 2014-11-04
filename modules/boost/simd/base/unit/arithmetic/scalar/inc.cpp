//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/arithmetic/include/functions/inc.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/include/constants/zero.hpp>
#include <boost/simd/include/constants/one.hpp>
#include <boost/simd/include/constants/mone.hpp>
#include <boost/simd/include/constants/two.hpp>
#include <boost/simd/include/constants/three.hpp>
#include <boost/simd/include/constants/mtwo.hpp>
#include <boost/simd/include/constants/inf.hpp>
#include <boost/simd/include/constants/minf.hpp>
#include <boost/simd/include/constants/nan.hpp>
#include <boost/simd/sdk/config.hpp>

NT2_TEST_CASE_TPL ( inc_signed_int,  BOOST_SIMD_INTEGRAL_SIGNED_TYPES)
{
  using boost::simd::inc;
  using boost::simd::tag::inc_;
  typedef typename boost::dispatch::meta::call<inc_(T)>::type r_t;
  typedef T wished_r_t;


  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
  NT2_TEST_EQUAL(inc(boost::simd::Mone<T>()), boost::simd::Zero<T>());
  NT2_TEST_EQUAL(inc(boost::simd::One<T>()), boost::simd::Two<T>());
  NT2_TEST_EQUAL(inc(boost::simd::Zero<T>()), boost::simd::One<T>());
}

NT2_TEST_CASE_TPL ( inc_unsigned_uint,  BOOST_SIMD_UNSIGNED_TYPES)
{
  using boost::simd::inc;
  using boost::simd::tag::inc_;
  typedef typename boost::dispatch::meta::call<inc_(T)>::type r_t;
  typedef T wished_r_t;


  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
  NT2_TEST_EQUAL(inc(boost::simd::One<T>()), boost::simd::Two<T>());
  NT2_TEST_EQUAL(inc(boost::simd::Two<T>()), boost::simd::Three<T>());
  NT2_TEST_EQUAL(inc(boost::simd::Zero<T>()), boost::simd::One<T>());
  NT2_TEST_EQUAL(inc(boost::simd::Valmax<T>()), boost::simd::Zero<T>());
}

NT2_TEST_CASE_TPL( inc_floating, BOOST_SIMD_REAL_TYPES)
{
  using boost::simd::inc;
  using boost::simd::tag::inc_;
  typedef typename boost::dispatch::meta::call<inc_(T)>::type r_t;
  typedef T wished_r_t;

  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
#ifndef BOOST_SIMD_NO_INVALIDS
  NT2_TEST_EQUAL(inc(boost::simd::Inf<T>()), boost::simd::Inf<T>());
  NT2_TEST_EQUAL(inc(boost::simd::Nan<T>()), boost::simd::Nan<T>());
  NT2_TEST_EQUAL(inc(boost::simd::Minf<T>()), boost::simd::Minf<T>());
#endif
  NT2_TEST_EQUAL(inc(boost::simd::One<T>()), boost::simd::Two<T>());
  NT2_TEST_EQUAL(inc(boost::simd::Two<T>()), boost::simd::Three<T>());
  NT2_TEST_EQUAL(inc(boost::simd::Zero<T>()), boost::simd::One<T>());
}
