//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/bitwise/include/functions/clz.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/include/constants/two.hpp>
#include <boost/simd/include/constants/one.hpp>
#include <boost/simd/include/constants/mone.hpp>
#include <boost/simd/include/constants/signmask.hpp>
#include <boost/simd/include/constants/nan.hpp>
#include <boost/simd/sdk/config.hpp>

NT2_TEST_CASE_TPL ( clz_real,  BOOST_SIMD_REAL_TYPES)
{

  using boost::simd::clz;
  using boost::simd::tag::clz_;
  typedef typename boost::dispatch::meta::call<clz_(T)>::type r_t;
  typedef typename boost::dispatch::meta::as_integer<T, unsigned>::type wished_r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
#ifndef BOOST_SIMD_NO_INVALIDS
  NT2_TEST_EQUAL(clz(boost::simd::Nan<T>()), 0u);
#endif
  NT2_TEST_EQUAL(clz(boost::simd::Mone<T>()), 0u);
  NT2_TEST_EQUAL(clz(boost::simd::Signmask<T>()),0u);
} // end of test for real_

NT2_TEST_CASE_TPL ( clz_signed_int,  BOOST_SIMD_INTEGRAL_SIGNED_TYPES)
{

  using boost::simd::clz;
  using boost::simd::tag::clz_;
  typedef typename boost::dispatch::meta::call<clz_(T)>::type r_t;
  typedef typename boost::dispatch::meta::as_integer<T, unsigned>::type wished_r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
  NT2_TEST_EQUAL(clz(boost::simd::One<T>()), sizeof(T)*8-boost::simd::One<r_t>());
  NT2_TEST_EQUAL(clz(boost::simd::Signmask<T>()), boost::simd::Zero<r_t>());
} // end of test for signed_int_

 NT2_TEST_CASE_TPL ( clz_unsigned_int,  BOOST_SIMD_UNSIGNED_TYPES)
 {

  using boost::simd::clz;
  using boost::simd::tag::clz_;
  typedef typename boost::dispatch::meta::call<clz_(T)>::type r_t;
  typedef typename boost::dispatch::meta::as_integer<T, unsigned>::type wished_r_t;


  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
  NT2_TEST_EQUAL(clz(boost::simd::One<T>()),  r_t(sizeof(T)*8-boost::simd::One<r_t>()));

  T j = 1;
  for(int i=1; i < boost::simd::Valmax<char>(); i*= 2)
    {
      NT2_TEST_EQUAL(clz(T(i)),T(sizeof(T)*8- T(j)));
      ++j;
    }
 } // end of test for unsigned_int_
