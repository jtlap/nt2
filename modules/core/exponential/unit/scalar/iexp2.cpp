//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 exponential toolbox - iexp2/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of exponential components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created by jt the 08/12/2010
///
#include <nt2/exponential/include/functions/iexp2.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/include/constants/mone.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/two.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/constant/constant.hpp>


NT2_TEST_CASE_TPL ( iexp2_unsigned_int__1_0,  NT2_INTEGRAL_SIGNED_TYPES)
{

  using nt2::iexp2;
  using nt2::tag::iexp2_;
  typedef typename nt2::meta::call<iexp2_(T)>::type r_t;
  typedef T wished_r_t;


  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
  NT2_TEST_EQUAL(iexp2(nt2::One<T>()), nt2::Two<r_t>());
  NT2_TEST_EQUAL(iexp2(nt2::Zero<T>()), nt2::One<r_t>());
  NT2_TEST_EQUAL(iexp2(nt2::Mone<T>()), nt2::Zero<r_t>());
  NT2_TEST_EQUAL(iexp2(T(sizeof(T)*8-2)),  1ll << (sizeof(T)*8-2));
} // end of test for unsigned_int_

NT2_TEST_CASE_TPL ( iexp2_signed_int__1_0,  NT2_UNSIGNED_TYPES)
{

  using nt2::iexp2;
  using nt2::tag::iexp2_;
  typedef typename nt2::meta::call<iexp2_(T)>::type r_t;
  typedef T wished_r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
  NT2_TEST_EQUAL(iexp2(nt2::One<T>()), nt2::Two<r_t>());
  NT2_TEST_EQUAL(iexp2(nt2::Zero<T>()), nt2::One<r_t>());
  NT2_TEST_EQUAL(iexp2(T(sizeof(T)*8-1)),  1ull << (sizeof(T)*8-1));
} // end of test for signed_int_
