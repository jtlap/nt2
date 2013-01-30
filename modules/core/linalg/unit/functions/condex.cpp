//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 linalg toolbox - condex function"

#include <nt2/table.hpp>
#include <nt2/include/functions/condex.hpp>
#include <nt2/include/functions/trans.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/functions/diag_of.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>
#include <nt2/include/functions/tie.hpp>

NT2_TEST_CASE_TPL ( condex, NT2_REAL_TYPES)
{
  nt2::table<T> r31 =
    nt2::trans(nt2::cons(nt2::of_size(4, 4),
                         T(1),    T(-1),  T(-200),  T(   0),
                         T(0),    T( 1),  T( 100),  T(-100),
                         T(0),    T( 1),  T( 101),  T(-101),
                         T(0),    T( 0),  T(   0),  T( 100)
                 ));
  NT2_DISPLAY(r31);
  nt2::table<T> r;
  r =  nt2::condex(3, 1, T(100));
  NT2_DISPLAY(r);
  NT2_TEST_ULP_EQUAL(r, r31, 2);
  //________________________________________________________________
  nt2::table<T> r32 =
    nt2::trans(nt2::cons(nt2::of_size(3, 3),
                         T(1.0000),     T(0.9998),    T(-2.0000),
                         T(     0),     T(0.0100),    T(-0.0100),
                         T(     0),     T(     0),    T( 1.0000)
                 ));
  NT2_DISPLAY(r32);
  nt2::table<T> r2;
  r2 =  nt2::condex(3, 2, nt2::meta::as_<T>());
  NT2_DISPLAY(r2);
  NT2_TEST_ULP_EQUAL(r2, r32, 2);
  //________________________________________________________________
  nt2::table<T> r33 =
    nt2::trans(nt2::cons(nt2::of_size(3, 3),
                         T(1),    T(0),    T(0),
                         T(-1),   T(1),    T(0),
                         T(-1),   T(-1),   T(-1)
                 ));
  nt2::table<T> r3;
  r3 =  nt2::condex(3, 3, nt2::meta::as_<T>());
  NT2_DISPLAY(r3);
  NT2_TEST_ULP_EQUAL(r3, r33, 3);
  //________________________________________________________________
  nt2::table<T> r34 =
    nt2::trans(nt2::cons(nt2::of_size(3, 3),
                         T(1),    T(0),    T(0),
                         T(0),    T(1),    T(0),
                         T(0),    T(0),    T(1)
                 ));
  nt2::table<T> r4;
  r4 =  nt2::condex(3, 4, nt2::meta::as_<T>());
  NT2_DISPLAY(r4);
  NT2_TEST_ULP_EQUAL(r4, r34, 300);
}

// NT2_TEST_CASE_TPL ( condex_double, (double))
// {
//   nt2::table<T> r31 =
//     nt2::trans(nt2::cons(nt2::of_size(4, 4),
//                          T(1),    T(-1),  T(-200),  T(   0),
//                          T(0),    T( 1),  T( 100),  T(-100),
//                          T(0),    T( 1),  T( 101),  T(-101),
//                          T(0),    T( 0),  T(   0),  T( 100)
//                  ));
//   nt2::table<T> r;
//   r =  nt2::condex(3, 1);
//   NT2_DISPLAY(r);
//   NT2_TEST_ULP_EQUAL(r, r31, 2);
// }



