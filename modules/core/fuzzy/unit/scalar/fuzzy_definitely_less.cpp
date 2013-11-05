//==============================================================================
//         Copyright 2003 - 2013   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/fuzzy/include/functions/fuzzy_definitely_less.hpp>

#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>
#include <nt2/sdk/simd/logical.hpp>

#include <nt2/include/constants/false.hpp>

NT2_TEST_CASE_TPL ( fuzzy_definitely_less_real,  NT2_REAL_TYPES)
{
  using nt2::fuzzy_definitely_less;
  using nt2::tag::fuzzy_definitely_less_;

  typedef typename nt2::meta::call<fuzzy_definitely_less_(T,T,T)>::type r_t;
  typedef typename nt2::meta::as_logical<T>::type wished_r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
  NT2_TEST_EQUAL(fuzzy_definitely_less(T(0),T(0),T(1)), nt2::False<r_t>());
  NT2_TEST_EQUAL(fuzzy_definitely_less(T(0),T(1),T(1)), nt2::False<r_t>());
}

NT2_TEST_CASE_TPL ( fuzzy_definitely_less_signed_int,  NT2_INTEGRAL_SIGNED_TYPES)
{
  using nt2::fuzzy_definitely_less;
  using nt2::tag::fuzzy_definitely_less_;

  typedef typename nt2::meta::call<fuzzy_definitely_less_(T,T,T)>::type r_t;
  typedef typename nt2::meta::as_logical<T>::type wished_r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
  NT2_TEST_EQUAL(fuzzy_definitely_less(T(0),T(0),T(1)), nt2::False<r_t>());
  NT2_TEST_EQUAL(fuzzy_definitely_less(T(0),T(1),T(1)), nt2::False<r_t>());
}

NT2_TEST_CASE_TPL ( fuzzy_definitely_less_unsigned_int,  NT2_UNSIGNED_TYPES)
{
  using nt2::fuzzy_definitely_less;
  using nt2::tag::fuzzy_definitely_less_;

  typedef typename nt2::meta::call<fuzzy_definitely_less_(T,T,T)>::type r_t;
  typedef typename nt2::meta::as_logical<T>::type wished_r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
  NT2_TEST_EQUAL(fuzzy_definitely_less(T(0),T(0),T(1)), nt2::False<r_t>());
  NT2_TEST_EQUAL(fuzzy_definitely_less(T(0),T(1),T(1)), nt2::False<r_t>());
}
