//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 linalg toolbox - pascal function"

#include <nt2/table.hpp>
#include <nt2/include/functions/pascal.hpp>
#include <nt2/include/functions/trans.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>

NT2_TEST_CASE_TPL ( pascal, NT2_REAL_TYPES)
{
   nt2::table<T> p40 =
    nt2::trans(nt2::reshape(nt2::cons(
                              T(1),     T(1),     T(1),     T(1),
                              T(1),     T(2),     T(3),     T(4),
                              T(1),     T(3),     T(6),    T(10),
                              T(1),     T(4),    T(10),    T(20)
                              ), nt2::of_size(4, 4)));
   nt2::table<T> p42 =
     nt2::trans(nt2::reshape(nt2::cons(
                               T(-1),    T(-1),    T(-1),    T(-1),
                               T( 3),    T( 2),    T( 1),    T( 0),
                               T(-3),    T(-1),    T( 0),    T( 0),
                               T( 1),    T( 0),    T( 0),    T( 0)
                              ), nt2::of_size(4, 4)));
   nt2::table<T> p41 =
    nt2::trans(nt2::reshape(nt2::cons(
                              T(1),    T( 0),     T(0),    T( 0),
                              T(1),    T(-1),     T(0),    T( 0),
                              T(1),    T(-2),     T(1),    T( 0),
                              T(1),    T(-3),     T(3),    T(-1)
                              ), nt2::of_size(4, 4)));

   NT2_TEST_EQUAL(nt2::pascal(4, 0, nt2::meta::as_<T>()), p40);
   NT2_TEST_EQUAL(nt2::pascal(4, nt2::meta::as_<T>()), p40);
   NT2_TEST_EQUAL(nt2::pascal<T>(4), p40);
   NT2_TEST_EQUAL(nt2::pascal(4, 1, nt2::meta::as_<T>()), p41);
   NT2_TEST_EQUAL(nt2::pascal(4, 2, nt2::meta::as_<T>()), p42);
   NT2_TEST_EQUAL(nt2::pascal<T>(4, 1), p41);
   NT2_TEST_EQUAL(nt2::pascal<T>(4, 2), p42);
}


