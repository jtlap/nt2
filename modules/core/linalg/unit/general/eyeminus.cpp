//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 linalg toolbox - eyeminus factorization"

#include <nt2/table.hpp>
#include <nt2/include/functions/eyeminus.hpp>
#include <nt2/include/functions/zeros.hpp>

#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/module.hpp>


NT2_TEST_CASE_TPL(eyeminus, NT2_REAL_TYPES)
{
  using nt2::eyeminus;
  using nt2::tag::eyeminus_;
  nt2::table<T> n = nt2::eye(10, 10, nt2::meta::as_<T>());
  nt2::table<T> eyeminusn = nt2::eyeminus(n);
  NT2_TEST_EQUAL(eyeminusn, nt2::zeros(10, nt2::meta::as_<T>()));
}

NT2_TEST_CASE_TPL(eyeminus2, NT2_REAL_TYPES)
{
  using nt2::eyeminus;
  using nt2::tag::eyeminus_;
  nt2::table<T> n = nt2::eye(10, 4, nt2::meta::as_<T>());
  nt2::table<T> eyeminusn = nt2::eyeminus(n, T(0.5));
  NT2_TEST_EQUAL(eyeminusn, n*T(0.5));
}
NT2_TEST_CASE_TPL(eyeminuss, NT2_REAL_TYPES)
{
  using nt2::eyeminus;
  using nt2::tag::eyeminus_;
  T eyeminusn = nt2::eyeminus(T(3));
  NT2_TEST_EQUAL(eyeminusn, T(-2));
  eyeminusn = nt2::eyeminus(T(3), T(0.5));
  NT2_TEST_EQUAL(eyeminusn, T(-0.5));

}
