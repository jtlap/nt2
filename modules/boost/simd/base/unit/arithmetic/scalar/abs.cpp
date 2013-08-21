//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/arithmetic/include/functions/abs.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/include/constants/one.hpp>
#include <boost/simd/include/constants/mone.hpp>
#include <boost/simd/include/constants/inf.hpp>
#include <boost/simd/include/constants/minf.hpp>
#include <boost/simd/include/constants/nan.hpp>
#include <boost/simd/include/constants/valmax.hpp>
#include <boost/simd/include/constants/valmin.hpp>
#include <boost/simd/sdk/config.hpp>

NT2_TEST_CASE_TPL ( abs_real,  BOOST_SIMD_REAL_TYPES)
{

  using boost::simd::abs;
  using boost::simd::tag::abs_;
  typedef typename boost::dispatch::meta::call<abs_(T)>::type r_t;
  typedef T wished_r_t;


  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
#ifndef BOOST_SIMD_NO_INVALIDS
  NT2_TEST_EQUAL(abs(boost::simd::Inf<T>()), boost::simd::Inf<T>());
  NT2_TEST_EQUAL(abs(boost::simd::Minf<T>()), boost::simd::Inf<T>());
  NT2_TEST_EQUAL(abs(boost::simd::Nan<T>()), boost::simd::Nan<T>());
#endif
  NT2_TEST_EQUAL(abs(boost::simd::Mone<T>()), boost::simd::One<T>());
  NT2_TEST_EQUAL(abs(boost::simd::One<T>()), boost::simd::One<T>());
  NT2_TEST_EQUAL(abs(boost::simd::Valmax<T>()), boost::simd::Valmax<T>());
  NT2_TEST_EQUAL(abs(boost::simd::Valmin<T>()), boost::simd::Valmax<T>());
  NT2_TEST_EQUAL(abs(boost::simd::Zero<T>()), boost::simd::Zero<T>());
} // end of test for floating_

NT2_TEST_CASE_TPL ( abs_unsigned_int,  BOOST_SIMD_UNSIGNED_TYPES)
{

  using boost::simd::abs;
  using boost::simd::tag::abs_;
  typedef typename boost::dispatch::meta::call<abs_(T)>::type r_t;
  typedef T wished_r_t;

  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
  NT2_TEST_EQUAL(abs(boost::simd::One<T>()), boost::simd::One<T>());
  NT2_TEST_EQUAL(abs(boost::simd::Valmax<T>()), boost::simd::Valmax<T>());
  NT2_TEST_EQUAL(abs(boost::simd::Valmin<T>()), boost::simd::Valmin<T>());
  NT2_TEST_EQUAL(abs(boost::simd::Zero<T>()), boost::simd::Zero<T>());
} // end of test for unsigned_int_

NT2_TEST_CASE_TPL ( abs_signed_int,  BOOST_SIMD_INTEGRAL_SIGNED_TYPES)
{

  using boost::simd::abs;
  using boost::simd::tag::abs_;
  typedef typename boost::dispatch::meta::call<abs_(T)>::type r_t;
  typedef T wished_r_t;

  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
  NT2_TEST_EQUAL(abs(boost::simd::Mone<T>()), boost::simd::One<T>());
  NT2_TEST_EQUAL(abs(boost::simd::One<T>()), boost::simd::One<T>());
  NT2_TEST_EQUAL(abs(boost::simd::Valmax<T>()), boost::simd::Valmax<T>());
  NT2_TEST_EQUAL(abs(boost::simd::Valmin<T>()), boost::simd::Valmin<T>());
  NT2_TEST_EQUAL(abs(boost::simd::Zero<T>()), boost::simd::Zero<T>());
} // end of test for signed_int_
