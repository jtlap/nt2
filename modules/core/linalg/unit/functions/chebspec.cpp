//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 linalg toolbox - chebspec function"

#include <nt2/table.hpp>
#include <nt2/include/functions/chebspec.hpp>
#include <nt2/include/functions/trans.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>

NT2_TEST_CASE_TPL ( chebspec, NT2_REAL_TYPES)
{

  nt2::table<T> c30 =
    nt2::trans(nt2::reshape(nt2::cons(
                              T(1.5),   T(-2.0), T(0.5),
                              T(0.5),   T(-0.0), T(-0.5),
                              T(-0.5),  T(2.0),  T(-1.5)
                              ), nt2::of_size(3, 3)));
  nt2::table<T> v =  nt2::chebspec( 3, 0);
  nt2::display("v", v);
  NT2_DISPLAY(v);
  NT2_DISPLAY(c30);
  NT2_TEST_EQUAL(v, c30);
  nt2::table<T> c31 =
    nt2::trans(nt2::reshape(nt2::cons(
                              T(-1.0),   T(-3.0),  T(1.0),
                              T(3.0),    T(1.0),   T(-3.0),
                              T(-4.0),   T(12.0),  T(-9.5)
                              ), nt2::of_size(3, 3)))/T(3);
  nt2::table<T> v1 =  nt2::chebspec( 3, 1);
  nt2::display("v1", v1);
  NT2_DISPLAY(c31);
  NT2_TEST_ULP_EQUAL(v1, c31, 2.0);
}

NT2_TEST_CASE_TPL ( chebspec_targetted, NT2_REAL_TYPES)
{

  nt2::table<T> c30 =
    nt2::trans(nt2::reshape(nt2::cons(
                              T(1.5),   T(-2.0), T(0.5),
                              T(0.5),   T(-0.0), T(-0.5),
                              T(-0.5),  T(2.0),  T(-1.5)
                              ), nt2::of_size(3, 3)));
  nt2::table<T> c31 =
    nt2::trans(nt2::reshape(nt2::cons(
                              T(-1.0),   T(-3.0),  T(1.0),
                              T(3.0),    T(1.0),   T(-3.0),
                              T(-4.0),   T(12.0),  T(-9.5)
                              ), nt2::of_size(3, 3)))/T(3);

  NT2_TEST_EQUAL(nt2::chebspec( 3, 0, nt2::meta::as_<T>()), c30);
  NT2_TEST_ULP_EQUAL(nt2::chebspec( 3, 1, nt2::meta::as_<T>()), c31, 2.0);
}


NT2_TEST_CASE_TPL ( chebspec_small, NT2_REAL_TYPES)
{
  nt2::table<T> c00 = nt2::zeros(0, 1,  nt2::meta::as_<T>());
  nt2::table<T> c01 = nt2::zeros(0, 1,  nt2::meta::as_<T>());
  nt2::table<T> c10 = T(1)/T(6);
  nt2::table<T> c11 = T(-0.5);

  NT2_TEST_EQUAL(nt2::chebspec( 1, 0, nt2::meta::as_<T>()), c10);
  NT2_TEST_EQUAL(nt2::chebspec( 1, 1, nt2::meta::as_<T>()), c11);
  NT2_TEST_EQUAL(nt2::chebspec( 0, 0, nt2::meta::as_<T>()), c00);
  NT2_TEST_EQUAL(nt2::chebspec( 0, 1, nt2::meta::as_<T>()), c01);
}
NT2_TEST_CASE_TPL ( chebspec_templated, NT2_REAL_TYPES)
{
   nt2::table<T> c30 =
    nt2::trans(nt2::reshape(nt2::cons(
                              T(1.5),   T(-2.0), T(0.5),
                              T(0.5),   T(-0.0), T(-0.5),
                              T(-0.5),  T(2.0),  T(-1.5)
                              ), nt2::of_size(3, 3)));
  nt2::table<T> c31 =
    nt2::trans(nt2::reshape(nt2::cons(
                              T(-1.0),   T(-3.0),  T(1.0),
                              T(3.0),    T(1.0),   T(-3.0),
                              T(-4.0),   T(12.0),  T(-9.5)
                              ), nt2::of_size(3, 3)))/T(3);

  NT2_TEST_EQUAL(nt2::chebspec<T>( 3, 0), c30);
  NT2_TEST_ULP_EQUAL(nt2::chebspec<T>( 3, 1), c31, 2.0);
}
