//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/logninv.hpp>
#include <nt2/include/constants/exp_1.hpp>
#include <nt2/constant/constant.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>

NT2_TEST_CASE_TPL ( logninv_1,  NT2_REAL_TYPES)
{
  using nt2::logninv;
  // specific values tests
  NT2_TEST_ULP_EQUAL(logninv(nt2::Nan<T>()), nt2::Nan<T>(), 0.5);
  NT2_TEST_ULP_EQUAL(logninv(nt2::Half<T>()), nt2::One<T>(), 0.5);
  NT2_TEST_ULP_EQUAL(logninv(nt2::Zero<T>()), nt2::Zero<T>(), 0.5);
  NT2_TEST_ULP_EQUAL(logninv(nt2::One<T>()), nt2::Inf<T>(), 0.5);
} // end of test for floating_

NT2_TEST_CASE_TPL ( logninv_2,  NT2_REAL_TYPES)
{
  using nt2::logninv;
  // specific values tests
  NT2_TEST_ULP_EQUAL(logninv(nt2::Nan<T>(), nt2::One<T>()), nt2::Nan<T>(), 0.5);
  NT2_TEST_ULP_EQUAL(logninv(nt2::Half<T>(), nt2::One<T>()), nt2::Exp_1<T>(), 0.5);
  NT2_TEST_ULP_EQUAL(logninv(nt2::Zero<T>(), nt2::One<T>()), nt2::Zero<T>(), 0.5);
  NT2_TEST_ULP_EQUAL(logninv(nt2::One<T>(), nt2::One<T>()), nt2::Inf<T>(), 0.5);
} // end of test for floating_

