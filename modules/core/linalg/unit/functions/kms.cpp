//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 linalg toolbox - kms function"

#include <nt2/table.hpp>
#include <nt2/include/functions/kms.hpp>
#include <nt2/include/functions/transpose.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/constants/i.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/module.hpp>


NT2_TEST_CASE_TPL ( kmsr, NT2_REAL_TYPES)
{

  nt2::table<T> k4 = nt2::trans(nt2::cons(nt2::of_size(4, 4),
                                          T(1.0000),    T(0.5000),    T(0.2500),    T(0.1250),
                                          T(0.5000),    T(1.0000),    T(0.5000),    T(0.2500),
                                          T(0.2500),    T(0.5000),    T(1.0000),    T(0.5000),
                                          T(0.1250),    T(0.2500),    T(0.5000),    T(1.0000)
                                         ));

  nt2::table<T> a = nt2::kms(4, T(0.5));
  nt2::table<T> a1 = nt2::kms(4, 0.5, nt2::meta::as_<T>());
  nt2::table<T> a2 = nt2::kms<T>(4);
  NT2_DISPLAY(a);
  NT2_TEST_ULP_EQUAL(a, k4, 5);
  NT2_TEST_ULP_EQUAL(a1, k4, 5);
  NT2_TEST_ULP_EQUAL(a2, k4, 5);
}


