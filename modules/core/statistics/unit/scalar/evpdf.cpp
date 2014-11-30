//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/evpdf.hpp>
#include <nt2/include/constants/invexp_1.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/half.hpp>
#include <nt2/include/constants/minf.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/include/functions/transpose.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/module.hpp>

#include <nt2/table.hpp>

NT2_TEST_CASE_TPL ( evpdf_1, NT2_REAL_TYPES)
{

  using nt2::evpdf;
  using nt2::tag::evpdf_;
  using nt2::_;


  // specific values tests
  NT2_TEST_ULP_EQUAL(evpdf(nt2::Nan<T>(), nt2::Half<T>(), nt2::Half<T>()), nt2::Nan<T>(), 0);
  NT2_TEST_ULP_EQUAL(evpdf(nt2::One<T>(), nt2::Half<T>(), nt2::Half<T>()),  nt2::splat<T>(3.587481574680342e-01), 1.5);
  NT2_TEST_ULP_EQUAL(evpdf(nt2::Zero<T>(), nt2::Half<T>(), nt2::Half<T>()), nt2::splat<T>(5.092927600871650e-01), 1);
  NT2_TEST_ULP_EQUAL(evpdf(nt2::Inf<T>(), nt2::Half<T>(), nt2::Half<T>()), nt2::Zero<T>(), 1);
  NT2_TEST_ULP_EQUAL(evpdf(nt2::Minf<T>(), nt2::Half<T>(), nt2::Half<T>()), nt2::Zero<T>(), 1);
  NT2_TEST_ULP_EQUAL(evpdf(nt2::Half<T>(), nt2::Half<T>(), nt2::Half<T>()), nt2::splat<T>(7.357588823428847e-01), 1);

  nt2::table<T> a = nt2::cons<T>(nt2::of_size(2, 2), 0.5, 1, 2, 4);
  nt2::table<T> r = nt2::cons<T>(nt2::of_size(2, 2),
     7.357588823428847e-01,     3.307042988904181e-01,
     1.472661576201773e-01,     6.868967509417984e-02);
  NT2_TEST_ULP_EQUAL(evpdf(nt2::Half<T>(), a, a), r, 0.5);
} // end of test for floating_

