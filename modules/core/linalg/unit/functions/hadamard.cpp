//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 linalg toolbox - hadamard function"

#include <nt2/table.hpp>
#include <nt2/include/functions/hadamard.hpp>
#include <nt2/include/functions/trans.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/functions/mtimes.hpp>
#include <nt2/include/functions/cast.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>

NT2_TEST_CASE_TPL ( hadamard, NT2_REAL_TYPES)
{
  nt2::table<T> b4 =
    nt2::trans(nt2::reshape(nt2::cons(
                              T(1),     T(1),    T( 1),    T( 1),
                              T(1),    T(-1),    T( 1),    T(-1),
                              T(1),     T(1),    T(-1),    T(-1),
                              T(1),    T(-1),    T(-1),     T(1)
                              ), nt2::of_size(4, 4)));
  nt2::table<T> v = nt2::hadamard(4, nt2::meta::as_<T>());
  nt2::table<T> v1 = nt2::hadamard<T>(4);
  nt2::table<T> v2 = nt2::cast<T>(nt2::hadamard(4));
  NT2_TEST_EQUAL(v, b4);
  NT2_TEST_EQUAL(v1, b4);
  NT2_TEST_EQUAL(v2, b4);
  NT2_TEST_EQUAL(nt2::mtimes(trans(v2), v2), T(4)*nt2::eye(4, nt2::meta::as_<T>()));
}


NT2_TEST_CASE_TPL ( hadamard12, NT2_REAL_TYPES)
{
  nt2::table<T> b12 =
    nt2::trans(nt2::reshape(nt2::cons(
                              T(1),    T( 1),    T( 1),    T( 1),    T( 1),    T( 1),    T( 1),    T( 1),    T( 1),    T( 1),    T( 1),    T( 1),
                              T(1),    T(-1),    T( 1),    T(-1),    T( 1),    T( 1),    T( 1),    T(-1),    T(-1),    T(-1),    T( 1),    T(-1),
                              T(1),    T(-1),    T(-1),    T( 1),    T(-1),    T( 1),    T( 1),    T( 1),    T(-1),    T(-1),    T(-1),    T( 1),
                              T(1),    T( 1),    T(-1),    T(-1),    T( 1),    T(-1),    T( 1),    T( 1),    T( 1),    T(-1),    T(-1),    T(-1),
                              T(1),    T(-1),    T( 1),    T(-1),    T(-1),    T( 1),    T(-1),    T( 1),    T( 1),    T( 1),    T(-1),    T(-1),
                              T(1),    T(-1),    T(-1),    T( 1),    T(-1),    T(-1),    T( 1),    T(-1),    T( 1),    T( 1),    T( 1),    T(-1),
                              T(1),    T(-1),    T(-1),    T(-1),    T( 1),    T(-1),    T(-1),    T( 1),    T(-1),    T( 1),    T( 1),    T( 1),
                              T(1),    T( 1),    T(-1),    T(-1),    T(-1),    T( 1),    T(-1),    T(-1),    T( 1),    T(-1),    T( 1),    T( 1),
                              T(1),    T( 1),    T( 1),    T(-1),    T(-1),    T(-1),    T( 1),    T(-1),    T(-1),    T( 1),    T(-1),    T( 1),
                              T(1),    T( 1),    T( 1),    T( 1),    T(-1),    T(-1),    T(-1),    T( 1),    T(-1),    T(-1),    T( 1),    T(-1),
                              T(1),    T(-1),    T( 1),    T( 1),    T( 1),    T(-1),    T(-1),    T(-1),    T( 1),    T(-1),    T(-1),    T( 1),
                              T(1),    T( 1),    T(-1),    T( 1),    T( 1),    T( 1),    T(-1),    T(-1),    T(-1),    T( 1),    T(-1),    T(-1)
                              ), nt2::of_size(12, 12)));
  nt2::table<T> v = nt2::hadamard(12, nt2::meta::as_<T>());
  nt2::table<T> v1 = nt2::hadamard<T>(12);
  nt2::table<T> v2 = nt2::cast<T>(nt2::hadamard(12));
  NT2_TEST_EQUAL(v, b12);
  NT2_TEST_EQUAL(v1, b12);
  NT2_TEST_EQUAL(v2, b12);
  NT2_TEST_EQUAL(nt2::mtimes(trans(v2), v2), T(12)*nt2::eye(12, nt2::meta::as_<T>()));
}
NT2_TEST_CASE_TPL ( hadamard20, NT2_REAL_TYPES)
{
  nt2::table<T> v = nt2::hadamard(20, nt2::meta::as_<T>());
  nt2::table<T> v1 = nt2::hadamard<T>(20);
  nt2::table<T> v2 = nt2::cast<T>(nt2::hadamard(20));
  NT2_TEST_EQUAL(nt2::mtimes(trans(v2), v2), T(20)*nt2::eye(20, nt2::meta::as_<T>()));
}


