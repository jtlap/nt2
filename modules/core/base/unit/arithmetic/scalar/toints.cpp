//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 arithmetic toolbox - toints/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of arithmetic components in scalar mode
//////////////////////////////////////////////////////////////////////////////

#include <nt2/arithmetic/include/functions/toints.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/mone.hpp>
#include <nt2/include/constants/minf.hpp>
#include <nt2/include/constants/nan.hpp>


NT2_TEST_CASE_TPL ( toints_real,  BOOST_SIMD_REAL_TYPES)
{

  using nt2::toints;
  using nt2::tag::toints_;
  typedef typename boost::dispatch::meta::call<toints_(T)>::type              r_t;
  typedef typename boost::dispatch::meta::as_integer<T>::type wished_r_t;

  NT2_TEST_TYPE_IS( r_t, wished_r_t );
  // specific values tests
  NT2_TEST_EQUAL(toints(nt2::Inf<T>()) , nt2::Inf<r_t>());
  NT2_TEST_EQUAL(toints(nt2::Minf<T>()), nt2::Minf<r_t>());
  NT2_TEST_EQUAL(toints(nt2::Mone<T>()), nt2::Mone<r_t>());
  NT2_TEST_EQUAL(toints(nt2::Nan<T>()) , nt2::Zero<r_t>());
  NT2_TEST_EQUAL(toints(nt2::One<T>()) , nt2::One<r_t>());
  NT2_TEST_EQUAL(toints(nt2::Zero<T>()), nt2::Zero<r_t>());
 } // end of test for floating_

NT2_TEST_CASE_TPL ( toints_unsigned_int,  BOOST_SIMD_UNSIGNED_TYPES)
{

  using nt2::toints;
  using nt2::tag::toints_;
  typedef typename boost::dispatch::meta::call<toints_(T)>::type               r_t;
  typedef typename boost::dispatch::meta::as_integer<T>::type wished_r_t;

  NT2_TEST_TYPE_IS( r_t, wished_r_t );
  // specific values tests
  NT2_TEST_EQUAL(toints(nt2::One<T>()), nt2::One<r_t>());
  NT2_TEST_EQUAL(toints(nt2::Zero<T>()), nt2::Zero<r_t>());
} // end of test for unsigned_int_

NT2_TEST_CASE_TPL ( toints_signed_int,  BOOST_SIMD_INTEGRAL_SIGNED_TYPES)
{

  using nt2::toints;
  using nt2::tag::toints_;
  typedef typename boost::dispatch::meta::call<toints_(T)>::type               r_t;
  typedef typename boost::dispatch::meta::as_integer<T>::type wished_r_t;

  NT2_TEST_TYPE_IS( r_t, wished_r_t );
//  NT2_TEST_EQUAL(toints(nt2::Mone<T>()), nt2::Valmax<r_t>());
  NT2_TEST_EQUAL(toints(nt2::Mone<T>()), nt2::Mone<r_t>());
  NT2_TEST_EQUAL(toints(nt2::One<T>()), nt2::One<r_t>());
  NT2_TEST_EQUAL(toints(nt2::Zero<T>()), nt2::Zero<r_t>());
} // end of test for signed_int_

