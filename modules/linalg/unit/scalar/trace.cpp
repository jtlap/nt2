//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 linalg toolbox - trace factorization"

#include <nt2/table.hpp>
#include <nt2/include/functions/trace.hpp>
#include <nt2/include/functions/rif.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/ten.hpp>

#include <nt2/include/functions/ulpdist.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>

NT2_TEST_CASE_TPL(trace, NT2_REAL_TYPES)
{
  typedef T r_t;
  using nt2::trace;
  using nt2::tag::trace_;
  nt2::table<T> n = nt2::rif(10, 10, nt2::meta::as_<T>());
  display("n", n);
  NT2_TEST_ULP_EQUAL(trace(n), T(55), 0);
  NT2_TEST_ULP_EQUAL(trace(n+n), T(110), 0);
  n = nt2::rif(2, 10, nt2::meta::as_<T>());
  display("n", n);
  NT2_TEST_ULP_EQUAL(trace(n), T(3), 0);
  NT2_TEST_ULP_EQUAL(trace(n+n), T(6), 0);
 }
