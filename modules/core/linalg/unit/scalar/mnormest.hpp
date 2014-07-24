//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/table.hpp>
#include <nt2/include/functions/mnormest.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/sqrt.hpp>
#include <nt2/include/functions/pow.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/ten.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/minf.hpp>

#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>

NT2_TEST_CASE_TPL(mnormest, NT2_REAL_TYPES)
{
  using nt2::mnormest;
  using nt2::tag::mnormest_;

  nt2::table<T> n = nt2::ones(10, 10, nt2::meta::as_<T>());
  int cnt;
  NT2_TEST_ULP_EQUAL(mnormest(n, T(1.0e-6)), nt2::Ten<T>(), 0.5);
  NT2_TEST_ULP_EQUAL(mnormest(n, T(1.0e-6), cnt), nt2::Ten<T>(), 0.5);
  NT2_TEST_EQUAL(cnt, 4);
  NT2_TEST_ULP_EQUAL(mnormest(n)           , nt2::Ten<T>(), 0.5);
  NT2_TEST_ULP_EQUAL(mnormest(n, cnt)      , nt2::Ten<T>(), 0.5);
  NT2_TEST_EQUAL(cnt, 4);
}
