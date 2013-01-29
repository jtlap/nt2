//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 linalg toolbox - dorr function"

#include <nt2/table.hpp>
#include <nt2/include/functions/dorr.hpp>
#include <nt2/include/functions/trans.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/functions/diag_of.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>
#include <nt2/include/functions/tie.hpp>

NT2_TEST_CASE_TPL ( dorr, NT2_REAL_TYPES)
{
  nt2::table<T> r4 = nt2::trans(nt2::cons(nt2::of_size(4, 4),
                                T(2.0000),    T(-1.7500),          T(0),          T(0),
                                T(-0.2500),    T(1.0000),    T(-0.7500),          T(0),
                                T(0),         T(-0.7500),    T( 1.0000),    T(-0.2500),
                                T(0),               T(0),    T(-1.7500),     T(2.0000)
                             ));
  nt2::table<T> c, d, e, r;
  nt2::tie(c, d, e) = nt2::dorr(4, T(0.01));
  NT2_TEST_ULP_EQUAL(c, nt2::diag_of(r4, -1), 2);
  NT2_TEST_ULP_EQUAL(d, nt2::diag_of(r4,  0), 2);
  NT2_TEST_ULP_EQUAL(e, nt2::diag_of(r4,  1), 2);
  r =  nt2::dorr(4, T(0.01));
  NT2_DISPLAY(r);
  NT2_TEST_ULP_EQUAL(r, r4, 2);
  r =  nt2::dorr(4, nt2::meta::as_<T>());
  NT2_DISPLAY(r);
  NT2_TEST_ULP_EQUAL(r, r4, 2);

}

NT2_TEST_CASE_TPL ( dorr_double, (double))
{
  nt2::table<T> r4 = nt2::trans(nt2::cons(nt2::of_size(4, 4),
                                T(2.0000),    T(-1.7500),          T(0),          T(0),
                                T(-0.2500),    T(1.0000),    T(-0.7500),          T(0),
                                T(0),         T(-0.7500),    T( 1.0000),    T(-0.2500),
                                T(0),               T(0),    T(-1.7500),     T(2.0000)
                             ));
  nt2::table<T> r =  nt2::dorr(4);
  NT2_DISPLAY(r);
  NT2_TEST_ULP_EQUAL(r, r4, 2);

}
