//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 linalg toolbox - inv factorization"

#include <nt2/table.hpp>
#include <nt2/include/functions/inv.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/ten.hpp>
#include <nt2/include/constants/eps.hpp>
#include <nt2/include/constants/two.hpp>
#include <nt2/include/functions/rec.hpp>
#include <nt2/include/functions/ulpdist.hpp>
#include <nt2/include/functions/isulpequal.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>


NT2_TEST_CASE_TPL(inv, NT2_REAL_TYPES)
{
  typedef T r_t;
  using nt2::inv;
  using nt2::tag::inv_;
  nt2::table<T> n = nt2::eye(10, 10, nt2::meta::as_<T>());
  nt2::table<T> invn = nt2::inv(n);
  NT2_DISPLAY(n);
  NT2_DISPLAY(invn);
  NT2_TEST(nt2::isulpequal(invn, n, 0.5));
}

NT2_TEST_CASE_TPL(inv_1, NT2_REAL_TYPES)
{
  typedef T r_t;
  using nt2::inv;
  using nt2::tag::inv_;
  nt2::table<T> n = nt2::eye(10, 10, nt2::meta::as_<T>()), nn;
  nn = n;
  n(1, 1) = nt2::Eps<T>()*nt2::Half<T>();
  nn(1, 1) = nt2::rec(n(1, 1));
  nt2::table<T> invn = nt2::inv(n);
  NT2_DISPLAY(n);
  NT2_DISPLAY(invn);
  NT2_TEST(nt2::isulpequal(invn, nn, 0.5));
 }
NT2_TEST_CASE_TPL(inv_2, NT2_REAL_TYPES)
{
  typedef T r_t;
  using nt2::inv;
  using nt2::tag::inv_;
  nt2::table<T> n = nt2::eye(10, 8, nt2::meta::as_<T>()), nn;
  NT2_TEST_ASSERT(nt2::inv(n));
 }
NT2_TEST_CASE_TPL(inv_nowarn, NT2_REAL_TYPES)
{
  typedef T r_t;
  using nt2::inv;
  using nt2::tag::inv_;
  nt2::table<T> n = nt2::eye(10, 10, nt2::meta::as_<T>()), nn;
  nn = n;
  n(1, 1) = nt2::Eps<T>()*nt2::Half<T>();
  nn(1, 1) = nt2::rec(n(1, 1));
  nt2::table<T> invn = nt2::inv(n, false);
  NT2_DISPLAY(n);
  NT2_DISPLAY(invn);
  NT2_TEST(nt2::isulpequal(invn, nn, 0.5));
 }
