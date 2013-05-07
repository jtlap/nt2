//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 linalg toolbox - tridiag function"

#include <nt2/table.hpp>
#include <nt2/include/functions/tridiag.hpp>
#include <nt2/include/functions/transpose.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/functions/repnum.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>

NT2_TEST_CASE_TPL ( tridiag_default, NT2_REAL_TYPES)
{
    nt2::table<T> t3 =
    nt2::trans(nt2::reshape(nt2::cons(
                              T(2),    T(-1),     T(0),
                              T(-1),     T(2),    T(-1),
                              T(0),    T(-1),     T(2)
                              ), nt2::of_size(3, 3)));
//    NT2_TEST_EQUAL(nt2::tridiag<T>(3), t3);
    NT2_TEST_EQUAL(nt2::tridiag(3, nt2::meta::as_<T>()), t3);
}
NT2_TEST_CASE_TPL ( tridiag_scalars, NT2_REAL_TYPES)
{
   nt2::table<T> t3 =
    nt2::trans(nt2::reshape(nt2::cons(
                              T(2),    T(-1),     T(0),
                              T(-1),     T(2),    T(-1),
                              T(0),    T(-1),     T(2)
                              ), nt2::of_size(3, 3)));
    NT2_TEST_EQUAL(nt2::tridiag(3, T(-1), T(2), T(-1)), t3);

}
NT2_TEST_CASE_TPL ( tridiag_vectors, NT2_REAL_TYPES)
{
   nt2::table<T> t3 =
    nt2::trans(nt2::reshape(nt2::cons(
                              T(2),    T(-1),     T(0),
                              T(-1),     T(2),    T(-1),
                              T(0),    T(-1),     T(2)
                              ), nt2::of_size(3, 3)));
   NT2_TEST_EQUAL(nt2::tridiag( nt2::repnum(T(-1), 1, 2),
                                nt2::repnum(T(2), 1, 3),
                                nt2::repnum(T(-1), 1, 2)), t3);

}
NT2_TEST_CASE_TPL ( tridiag_onescalar, NT2_REAL_TYPES)
{
   nt2::table<T> t3 =
    nt2::trans(nt2::reshape(nt2::cons(
                              T(2),    T(-1),     T(0),
                              T(-1),     T(2),    T(-1),
                              T(0),    T(-1),     T(2)
                              ), nt2::of_size(3, 3)));
   NT2_TEST_EQUAL(nt2::tridiag( T(-1),
                                nt2::repnum(T(2), 1, 3),
                                nt2::repnum(T(-1), 1, 2)), t3);

   NT2_TEST_EQUAL(nt2::tridiag( nt2::repnum(T(-1), 1, 2),
                                T(2),
                                nt2::repnum(T(-1), 1, 2)), t3);

   NT2_TEST_EQUAL(nt2::tridiag( nt2::repnum(T(-1), 1, 2),
                                nt2::repnum(T(2), 1, 3),
                                T(-1)), t3);

}
NT2_TEST_CASE_TPL ( tridiag_2scalar, NT2_REAL_TYPES)
{
   nt2::table<T> t3 =
    nt2::trans(nt2::reshape(nt2::cons(
                              T(2),    T(-1),     T(0),
                              T(-1),     T(2),    T(-1),
                              T(0),    T(-1),     T(2)
                              ), nt2::of_size(3, 3)));
   NT2_TEST_EQUAL(nt2::tridiag( T(-1),
                                T(2),
                                nt2::repnum(T(-1), 1, 2)), t3);

   NT2_TEST_EQUAL(nt2::tridiag( nt2::repnum(T(-1), 1, 2),
                                T(2),
                                T(-1)), t3);

   NT2_TEST_EQUAL(nt2::tridiag( T(-1),
                                nt2::repnum(T(2), 1, 3),
                                T(-1)), t3);

}
