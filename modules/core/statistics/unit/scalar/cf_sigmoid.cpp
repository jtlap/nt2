//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/cf_sigmoid.hpp>
#include <nt2/include/functions/sigmoid.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/half.hpp>
#include <nt2/include/constants/minf.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/include/functions/linspace.hpp>
#include <nt2/include/functions/splat.hpp>
#include <nt2/include/functions/max.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/module.hpp>

#include <nt2/table.hpp>

NT2_TEST_CASE_TPL ( cf_sigmoid, (float))
{
  using nt2::cf_sigmoid;
  using nt2::tag::cf_sigmoid_;

  // specific values tests
  NT2_TEST_ULP_EQUAL(cf_sigmoid(nt2::Nan<T>() ), nt2::Nan<T>(), 0);
  NT2_TEST_ULP_EQUAL(cf_sigmoid(nt2::One<T>() ), nt2::splat<T>(0.731058578630005), 17);
  NT2_TEST_ULP_EQUAL(cf_sigmoid(nt2::Zero<T>()), nt2::Half<T>(), 1);
  NT2_TEST_ULP_EQUAL(cf_sigmoid(nt2::Inf<T>() ), nt2::One<T>(), 1);
  NT2_TEST_ULP_EQUAL(cf_sigmoid(nt2::Minf<T>()), nt2::Zero<T>(), 1);
  NT2_TEST_ULP_EQUAL(cf_sigmoid(nt2::Half<T>()), nt2::splat<T>(0.622459331201855), 1);

  nt2::table<T> x =  nt2::linspace(T(-17), T(17));
  nt2::table<T> y =  cf_sigmoid(x);
  nt2::table<T> y1 =  nt2::sigmoid(x);
  NT2_DISPLAY(nt2::max(nt2::abs(y-y1)));
} // end of test for floating_

