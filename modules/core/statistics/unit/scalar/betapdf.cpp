//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/betapdf.hpp>
#include <nt2/include/constants/invexp_1.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/half.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/include/functions/transpose.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/module.hpp>

#include <nt2/table.hpp>

NT2_TEST_CASE_TPL ( betapdf_1, NT2_REAL_TYPES)
{

  using nt2::betapdf;
  using nt2::tag::betapdf_;
  using nt2::_;


  // specific values tests
  NT2_TEST_ULP_EQUAL(betapdf(nt2::Nan<T>(), nt2::Half<T>(), nt2::Half<T>()), nt2::Nan<T>(), 0);
  NT2_TEST_ULP_EQUAL(betapdf(nt2::One<T>(), nt2::Half<T>(), nt2::Half<T>()), nt2::Zero<T>(), 0);
  NT2_TEST_ULP_EQUAL(betapdf(nt2::Zero<T>(), nt2::Half<T>(), nt2::Half<T>()), nt2::Zero<T>(), 0);
  NT2_TEST_ULP_EQUAL(betapdf(nt2::Inf<T>(), nt2::Half<T>(), nt2::Half<T>()), nt2::Zero<T>(), 0);
  NT2_TEST_ULP_EQUAL(betapdf(nt2::Minf<T>(), nt2::Half<T>(), nt2::Half<T>()), nt2::Zero<T>(), 0);
  NT2_TEST_ULP_EQUAL(betapdf(nt2::Half<T>(), nt2::Half<T>(), nt2::Half<T>()), nt2::splat<T>(6.366197723675815e-01), 0);

  nt2::table<T> a = nt2::cons<T>(nt2::of_size(2, 2), 0.5, 1, 2, 4);
  nt2::table<T> r = nt2::cons<T>(nt2::of_size(2, 2),
     6.366197723675815e-01,     1.000000000000000e+00,
     1.500000000000000e+00,     2.187500000000002e+00);
  NT2_TEST_ULP_EQUAL(betapdf(nt2::Half<T>(), a, a), r, 1.5);
} // end of test for floating_

