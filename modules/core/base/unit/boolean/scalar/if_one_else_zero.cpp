//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 boolean toolbox - if_one_else_zero/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of boolean components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 21/02/2011
///
#include <nt2/boolean/include/functions/if_one_else_zero.hpp>
#include <nt2/sdk/simd/logical.hpp>
#include <boost/simd/sdk/simd/io.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

#include <boost/simd/constant/constant.hpp>
#include <boost/simd/include/constants/one.hpp>
#include <boost/simd/include/constants/inf.hpp>
#include <boost/simd/include/constants/zero.hpp>
#include <boost/simd/include/constants/minf.hpp>
#include <boost/simd/include/constants/mone.hpp>
#include <boost/simd/include/constants/nan.hpp>

NT2_TEST_CASE_TPL ( if_one_else_zero_real__1_0,  NT2_REAL_TYPES)
{

  using nt2::if_one_else_zero;
  using nt2::tag::if_one_else_zero_;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef typename nt2::meta::call<if_one_else_zero_(T)>::type r_t;
  typedef T wished_r_t;


  // return type conformity test
  NT2_TEST_TYPE_IS( r_t, wished_r_t );

  // specific values tests
  NT2_TEST_EQUAL(if_one_else_zero(-nt2::Zero<T>()), nt2::Zero<r_t>());
  NT2_TEST_EQUAL(if_one_else_zero(nt2::Half<T>()), nt2::One<r_t>());
  NT2_TEST_EQUAL(if_one_else_zero(nt2::Inf<T>()), nt2::One<r_t>());
  NT2_TEST_EQUAL(if_one_else_zero(nt2::Minf<T>()), nt2::One<r_t>());
  NT2_TEST_EQUAL(if_one_else_zero(nt2::Mone<T>()), nt2::One<r_t>());
  NT2_TEST_EQUAL(if_one_else_zero(nt2::Nan<T>()), nt2::One<r_t>());
  NT2_TEST_EQUAL(if_one_else_zero(nt2::One<T>()), nt2::One<r_t>());
  NT2_TEST_EQUAL(if_one_else_zero(nt2::Quarter<T>()), nt2::One<r_t>());
  NT2_TEST_EQUAL(if_one_else_zero(nt2::Two<T>()), nt2::One<r_t>());
  NT2_TEST_EQUAL(if_one_else_zero(nt2::Zero<T>()), nt2::Zero<r_t>());

} // end of test for floating_

NT2_TEST_CASE_TPL ( if_one_else_zero_signed_int__1_0,  NT2_INTEGRAL_SIGNED_TYPES)
{

  using nt2::if_one_else_zero;
  using nt2::tag::if_one_else_zero_;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef typename nt2::meta::call<if_one_else_zero_(T)>::type r_t;
  typedef T wished_r_t;


  // return type conformity test
  NT2_TEST_TYPE_IS( r_t, wished_r_t );
  // specific values tests
  NT2_TEST_EQUAL(if_one_else_zero(nt2::Mone<T>()), nt2::One<r_t>());
  NT2_TEST_EQUAL(if_one_else_zero(nt2::One<T>()), nt2::One<r_t>());
  NT2_TEST_EQUAL(if_one_else_zero(nt2::Two<T>()), nt2::One<r_t>());
  NT2_TEST_EQUAL(if_one_else_zero(nt2::Zero<T>()), nt2::Zero<r_t>());
} // end of test for signed_int_

NT2_TEST_CASE_TPL ( if_one_else_zero_unsigned_int__1_0,  NT2_UNSIGNED_TYPES)
{

  using nt2::if_one_else_zero;
  using nt2::tag::if_one_else_zero_;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef typename nt2::meta::call<if_one_else_zero_(T)>::type r_t;
  typedef T wished_r_t;


  // return type conformity test
  NT2_TEST_TYPE_IS( r_t, wished_r_t );

  // specific values tests
  NT2_TEST_EQUAL(if_one_else_zero(nt2::One<T>()), nt2::One<r_t>());
  NT2_TEST_EQUAL(if_one_else_zero(nt2::Two<T>()), nt2::One<r_t>());
  NT2_TEST_EQUAL(if_one_else_zero(nt2::Zero<T>()), nt2::Zero<r_t>());
} // end of test for unsigned_int_
