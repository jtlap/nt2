//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 linalg toolbox - cond factorization"

#include <nt2/table.hpp>
#include <nt2/include/functions/cond.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/ten.hpp>

#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>

NT2_TEST_CASE_TPL(cond, NT2_REAL_TYPES)
{
  typedef T r_t;
  using nt2::cond;
  using nt2::tag::cond_;
  nt2::table<T> n = nt2::eye(10, 10, nt2::meta::as_<T>());
  NT2_TEST_ULP_EQUAL(cond(n), nt2::One<T>(), 0);
  NT2_TEST_ULP_EQUAL(cond(n+n), nt2::One<T>(), 0);
  NT2_TEST_ULP_EQUAL(cond(n, 1), nt2::One<T>(), 0);
  NT2_TEST_ULP_EQUAL(cond(n+n, 1), nt2::One<T>(), 0);
  n(10, 10) = 10;
  NT2_TEST_ULP_EQUAL(cond(n), nt2::Ten<T>(), 0);
  NT2_TEST_ULP_EQUAL(cond(n+n), nt2::Ten<T>(), 0);
  NT2_TEST_ULP_EQUAL(cond(n, 1), nt2::Ten<T>(), 0);
  NT2_TEST_ULP_EQUAL(cond(n+n, 1), nt2::Ten<T>(), 0);
 }
