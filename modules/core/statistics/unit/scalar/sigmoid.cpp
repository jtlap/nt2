//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/sigmoid.hpp>
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

NT2_TEST_CASE_TPL ( sigmoid_1, NT2_REAL_TYPES)
{

  using nt2::sigmoid;
  using nt2::tag::sigmoid_;
  using nt2::_;


  // specific values tests
  NT2_TEST_ULP_EQUAL(sigmoid(nt2::Nan<T>() ), nt2::Nan<T>(), 0);
  NT2_TEST_ULP_EQUAL(sigmoid(nt2::One<T>() ),  nt2::splat<T>(7.310585786300049e-01), 1.5);
  NT2_TEST_ULP_EQUAL(sigmoid(nt2::Zero<T>()), nt2::Half<T>(), 1);
  NT2_TEST_ULP_EQUAL(sigmoid(nt2::Inf<T>() ), nt2::One<T>(), 1);
  NT2_TEST_ULP_EQUAL(sigmoid(nt2::Minf<T>()), nt2::Zero<T>(), 1);
  NT2_TEST_ULP_EQUAL(sigmoid(nt2::Half<T>()), nt2::splat<T>(6.224593312018546e-01), 1);
} // end of test for floating_

