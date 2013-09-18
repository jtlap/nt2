//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 linalg toolbox - eyeplus factorization"

#include <nt2/table.hpp>
#include <nt2/include/functions/eyeplus.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/constants/two.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/module.hpp>


NT2_TEST_CASE_TPL(eyeplus, NT2_REAL_TYPES)
{
  using nt2::eyeplus;
  using nt2::tag::eyeplus_;
  nt2::table<T> n = nt2::eye(10, 10, nt2::meta::as_<T>());
  nt2::table<T> eyeplusn = nt2::eyeplus(n);
  NT2_TEST_EQUAL(eyeplusn, nt2::Two<T>()*nt2::eye(10, nt2::meta::as_<T>()));
}

NT2_TEST_CASE_TPL(eyeplus2, NT2_REAL_TYPES)
{
  using nt2::eyeplus;
  using nt2::tag::eyeplus_;
  nt2::table<T> n = nt2::eye(10, 4, nt2::meta::as_<T>());
  nt2::table<T> eyeplusn = nt2::eyeplus(n, T(0.5));
  NT2_TEST_EQUAL(eyeplusn, n*T(1.5));
}
NT2_TEST_CASE_TPL(eyepluss, NT2_REAL_TYPES)
{
  using nt2::eyeplus;
  using nt2::tag::eyeplus_;
  T eyeplusn = nt2::eyeplus(T(3));
  NT2_TEST_EQUAL(eyeplusn, T(4));
  eyeplusn = nt2::eyeplus(T(3), T(0.5));
  NT2_TEST_EQUAL(eyeplusn, T(2.5));

}
