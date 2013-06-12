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
#include <nt2/include/functions/cons.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/complex/meta/as_complex.hpp>
#include <nt2/include/constants/i.hpp>

NT2_TEST_CASE_TPL(inv, NT2_REAL_TYPES)
{
  typedef typename nt2::meta::as_complex<T>::type  cT;
  typedef T r_t;
  using nt2::inv;
  using nt2::tag::inv_;
  nt2::table<cT> n = nt2::eye(10, 10, nt2::meta::as_<cT>());
  nt2::table<cT> invn = nt2::inv(n);
  NT2_TEST_ULP_EQUAL(invn, n, 0.5);
}

NT2_TEST_CASE_TPL(inv_1, NT2_REAL_TYPES)
{
  typedef typename nt2::meta::as_complex<T>::type  cT;
  typedef T r_t;
  using nt2::inv;
  using nt2::tag::inv_;
  nt2::table<cT> n = nt2::eye(10, 10, nt2::meta::as_<cT>()), nn;
  nn = n;
  n(1, 1) = nt2::Eps<T>()*nt2::Half<cT>();
  nn(1, 1) = nt2::rec(n(1, 1));
  nt2::table<cT> invn = nt2::inv(n);
  NT2_TEST_ULP_EQUAL(invn, nn, 0.5);
 }
NT2_TEST_CASE_TPL(inv_2, NT2_REAL_TYPES)
{
  typedef typename nt2::meta::as_complex<T>::type  cT;
  typedef T r_t;
  using nt2::inv;
  using nt2::tag::inv_;
  nt2::table<cT> n = nt2::eye(10, 8, nt2::meta::as_<cT>()), nn;
  NT2_TEST_ASSERT(nt2::inv(n));
 }
NT2_TEST_CASE_TPL(inv_nowarn, NT2_REAL_TYPES)
{
  typedef typename nt2::meta::as_complex<T>::type  cT;
  typedef T r_t;
  using nt2::inv;
  using nt2::tag::inv_;
  nt2::table<cT> n = nt2::eye(10, 10, nt2::meta::as_<cT>()), nn;
  nn = n;
  n(1, 1) = nt2::Eps<T>()*nt2::Half<cT>();
  nn(1, 1) = nt2::rec(n(1, 1));
  nt2::table<cT> invn = nt2::inv(n, false);
  NT2_TEST_ULP_EQUAL(invn, nn, 0.5);
 }
NT2_TEST_CASE_TPL(inv_3, NT2_REAL_TYPES)
{
  typedef typename nt2::meta::as_complex<T>::type  cT;
  typedef T r_t;
  using nt2::inv;
  using nt2::tag::inv_;
  nt2::table<cT> a = nt2::cons(nt2::of_size(2, 2),
                               cT(1, 1), cT(1, -1),
                               cT(0, 1), cT(2));
  nt2::table<cT> inva = nt2::cons(nt2::of_size(2, 2),
                                  cT(1, -1), cT(0, 1),
                                  cT(-0.5, -0.5), cT(1));
  NT2_TEST_ULP_EQUAL(inva, inv(a), 0.5);
 }
