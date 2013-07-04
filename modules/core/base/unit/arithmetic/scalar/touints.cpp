//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 arithmetic toolbox - touints/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of arithmetic components in scalar mode
//////////////////////////////////////////////////////////////////////////////

#include <nt2/arithmetic/include/functions/touints.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/mone.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/minf.hpp>
#include <nt2/include/constants/nan.hpp>

NT2_TEST_CASE_TPL ( touints_real,  NT2_REAL_TYPES)
{

  using nt2::touints;
  using nt2::tag::touints_;
  typedef typename nt2::meta::call<touints_(T)>::type r_t;
  typedef typename nt2::meta::as_integer<T, unsigned>::type wished_r_t;


  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
  NT2_TEST_EQUAL(touints(nt2::Inf<T>()), nt2::Inf<r_t>());
  NT2_TEST_EQUAL(touints(nt2::Minf<T>()), nt2::Minf<r_t>());
  NT2_TEST_EQUAL(touints(nt2::Nan<T>()), nt2::Zero<r_t>());
  NT2_TEST_EQUAL(touints(nt2::Mone<T>()), nt2::Zero<r_t>());
  NT2_TEST_EQUAL(touints(nt2::One<T>()),  nt2::One<r_t>());
  NT2_TEST_EQUAL(touints(nt2::Zero<T>()), nt2::Zero<r_t>());
} // end of test for floating_

NT2_TEST_CASE_TPL ( touints_unsigned_int,  NT2_UNSIGNED_TYPES)
{

  using nt2::touints;
  using nt2::tag::touints_;
  typedef typename nt2::meta::call<touints_(T)>::type r_t;
  typedef typename nt2::meta::as_integer<T, unsigned>::type wished_r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
  NT2_TEST_EQUAL(touints(nt2::One<T>()),  nt2::One<r_t>());
  NT2_TEST_EQUAL(touints(nt2::Zero<T>()), nt2::Zero<r_t>());
} // end of test for unsigned_int_

NT2_TEST_CASE_TPL ( touints_signed_int,  NT2_INTEGRAL_SIGNED_TYPES)
{

  using nt2::touints;
  using nt2::tag::touints_;
  typedef typename nt2::meta::call<touints_(T)>::type r_t;
  typedef typename nt2::meta::as_integer<T, unsigned>::type wished_r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
  NT2_TEST_EQUAL(touints(nt2::Mone<T>()), nt2::Zero<r_t>());
  NT2_TEST_EQUAL(touints(nt2::One<T>()),  nt2::One<r_t>());
  NT2_TEST_EQUAL(touints(nt2::Zero<T>()), nt2::Zero<r_t>());
} // end of test for signed_int_
