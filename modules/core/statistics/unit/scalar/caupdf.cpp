//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 statistics toolbox - caupdf/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of statistics  components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 22/02/2011
///
#include <nt2/include/functions/caupdf.hpp>
#include <nt2/include/constants/invpi.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/memory/buffer.hpp>
#include <nt2/toolbox/constant/constant.hpp>
#include <nt2/table.hpp>


NT2_TEST_CASE_TPL ( caupdf_real__2_0,  NT2_REAL_TYPES)
{

  using nt2::caupdf;
  using nt2::tag::caupdf_;
  // specific values tests
  NT2_TEST_ULP_EQUAL(caupdf(nt2::Nan<T>()), nt2::Nan<T>(), 0);
  NT2_TEST_ULP_EQUAL(caupdf(nt2::One<T>()), nt2::Invpi<T>()/2, 0);
  NT2_TEST_ULP_EQUAL(caupdf(nt2::Zero<T>()), nt2::Invpi<T>(), 0);
  NT2_TEST_ULP_EQUAL(caupdf(nt2::Inf<T>()), nt2::Zero<T>(), 0);
  NT2_TEST_ULP_EQUAL(caupdf(nt2::Minf<T>()), nt2::Zero<T>(), 0);
} // end of test for floating_

NT2_TEST_CASE_TPL ( caupdf_2,  NT2_REAL_TYPES)
{

  using nt2::caupdf;
  using nt2::tag::caupdf_;
  using nt2::_;


  // specific values tests
  NT2_TEST_ULP_EQUAL(caupdf(nt2::Nan<T>(), nt2::One<T>()), nt2::Nan<T>(), 0);
  NT2_TEST_ULP_EQUAL(caupdf(nt2::Zero<T>(), nt2::One<T>() ), nt2::Invpi<T>()/2, 0);
  NT2_TEST_ULP_EQUAL(caupdf(nt2::One<T>(), nt2::One<T>()), nt2::Invpi<T>(), 0);
  NT2_TEST_ULP_EQUAL(caupdf(nt2::Inf<T>(), nt2::One<T>()), nt2::Zero<T>(), 0);
  NT2_TEST_ULP_EQUAL(caupdf(nt2::Minf<T>(), nt2::One<T>()), nt2::Zero<T>(), 0);

  nt2::table<T> a = _(T(-5), T(1), T(5));
  NT2_DISPLAY(a);
  NT2_DISPLAY(caupdf(a, nt2::One<T>()));
  a = nt2::reshape(_(T(1), T(16)), 4, 4);
  NT2_DISPLAY(a);
  NT2_DISPLAY(caupdf(a, a));
  NT2_DISPLAY(caupdf(a, nt2::One<T>(), nt2::Two<T>()));
  NT2_DISPLAY(caupdf(a, a, nt2::Two<T>()));
  NT2_DISPLAY(caupdf(a, a, a));
} // end of test for floating_

