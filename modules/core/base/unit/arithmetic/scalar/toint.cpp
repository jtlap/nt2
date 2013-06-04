//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 arithmetic toolbox - toint/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of arithmetic components in scalar mode
//////////////////////////////////////////////////////////////////////////////

#include <nt2/arithmetic/include/functions/toint.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/include/constants/zero.hpp>
#include <boost/simd/include/constants/one.hpp>
#include <boost/simd/include/constants/mone.hpp>

NT2_TEST_CASE_TPL ( toint_real,  NT2_REAL_TYPES)
{

  using nt2::toint;
  using nt2::tag::toint_;
  typedef typename nt2::meta::call<toint_(T)>::type r_t;
  typedef typename nt2::meta::as_integer<T>::type wished_r_t;


  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
  NT2_TEST_EQUAL(toint(boost::simd::Mone<T>()), boost::simd::Mone<r_t>());
  NT2_TEST_EQUAL(toint(boost::simd::One<T>()),  boost::simd::One<r_t>());
  NT2_TEST_EQUAL(toint(boost::simd::Zero<T>()), boost::simd::Zero<r_t>());
} // end of test for floating_

NT2_TEST_CASE_TPL ( toint_unsigned_int,  NT2_UNSIGNED_TYPES)
{

  using nt2::toint;
  using nt2::tag::toint_;
  typedef typename nt2::meta::call<toint_(T)>::type r_t;
  typedef typename nt2::meta::as_integer<T>::type wished_r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
  NT2_TEST_EQUAL(toint(boost::simd::One<T>()),  boost::simd::One<r_t>());
  NT2_TEST_EQUAL(toint(boost::simd::Zero<T>()), boost::simd::Zero<r_t>());
} // end of test for unsigned_int_

NT2_TEST_CASE_TPL ( toint_signed_int,  NT2_INTEGRAL_SIGNED_TYPES)
{

  using nt2::toint;
  using nt2::tag::toint_;
  typedef typename nt2::meta::call<toint_(T)>::type r_t;
  typedef typename nt2::meta::as_integer<T>::type wished_r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
  NT2_TEST_EQUAL(toint(boost::simd::Mone<T>()), boost::simd::Mone<r_t>());
  NT2_TEST_EQUAL(toint(boost::simd::One<T>()),  boost::simd::One<r_t>());
} // end of test for signed_int_
