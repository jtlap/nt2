//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/arithmetic/include/functions/touints.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/include/constants/inf.hpp>
#include <boost/simd/include/constants/zero.hpp>
#include <boost/simd/include/constants/one.hpp>
#include <boost/simd/include/constants/mone.hpp>
#include <boost/simd/include/constants/minf.hpp>
#include <boost/simd/include/constants/nan.hpp>
#include <boost/simd/include/functions/ldexp.hpp>


NT2_TEST_CASE_TPL ( touints_real,  BOOST_SIMD_REAL_TYPES)
{

  using boost::simd::touints;
  using boost::simd::tag::touints_;
  typedef typename boost::dispatch::meta::call<touints_(T)>::type              r_t;
  typedef typename boost::dispatch::meta::as_integer<T, unsigned>::type wished_r_t;

  NT2_TEST_TYPE_IS( r_t, wished_r_t );
  // specific values tests
#ifndef BOOST_SIMD_NO_INVALIDS
  NT2_TEST_EQUAL(touints(boost::simd::Inf<T>()) , boost::simd::Inf<r_t>());
  NT2_TEST_EQUAL(touints(boost::simd::Minf<T>()), boost::simd::Zero<r_t>());
  NT2_TEST_EQUAL(touints(boost::simd::Nan<T>()) , boost::simd::Zero<r_t>());
#endif
  NT2_TEST_EQUAL(touints(boost::simd::One<T>()) , boost::simd::One<r_t>());
  NT2_TEST_EQUAL(touints(boost::simd::Zero<T>()), boost::simd::Zero<r_t>());
  NT2_TEST_EQUAL(touints(T(2)*boost::simd::Valmax<r_t>()),  boost::simd::Valmax<r_t>());
  NT2_TEST_EQUAL(touints(T(2)*boost::simd::Valmin<r_t>()),  boost::simd::Valmin<r_t>());
  NT2_TEST_EQUAL(touints(boost::simd::Mone<T>()), boost::simd::Zero<r_t>());

  T v = T(1);
  r_t iv = 1;
  int N = int(sizeof(T)*8);
  for(int i=0; i <= N ; i++, v*= 2, iv <<= 1)
  {
    NT2_TEST_EQUAL(touints(v), iv);
  }
  NT2_TEST_EQUAL(touints(boost::simd::ldexp(boost::simd::One<T>(), N+1)), boost::simd::Valmax<r_t>());
}

NT2_TEST_CASE_TPL ( touints_unsigned_int,  BOOST_SIMD_UNSIGNED_TYPES)
{

  using boost::simd::touints;
  using boost::simd::tag::touints_;
  typedef typename boost::dispatch::meta::call<touints_(T)>::type               r_t;
  typedef typename boost::dispatch::meta::as_integer<T, unsigned>::type wished_r_t;

  NT2_TEST_TYPE_IS( r_t, wished_r_t );

  // specific values tests
  NT2_TEST_EQUAL(touints(boost::simd::One<T>()), boost::simd::One<r_t>());
  NT2_TEST_EQUAL(touints(boost::simd::Zero<T>()), boost::simd::Zero<r_t>());
} // end of test for unsigned_int_

NT2_TEST_CASE_TPL ( touints_signed_int,  BOOST_SIMD_INTEGRAL_SIGNED_TYPES)
{

  using boost::simd::touints;
  using boost::simd::tag::touints_;
  typedef typename boost::dispatch::meta::call<touints_(T)>::type               r_t;
  typedef typename boost::dispatch::meta::as_integer<T, unsigned>::type wished_r_t;

  NT2_TEST_TYPE_IS( r_t, wished_r_t );

//  NT2_TEST_EQUAL(touints(boost::simd::Mone<T>()), boost::simd::Valmax<r_t>());
  NT2_TEST_EQUAL(touints(boost::simd::Mone<T>()), boost::simd::Zero<r_t>());
  NT2_TEST_EQUAL(touints(boost::simd::One<T>()), boost::simd::One<r_t>());
  NT2_TEST_EQUAL(touints(boost::simd::Zero<T>()), boost::simd::Zero<r_t>());
} // end of test for signed_int_
