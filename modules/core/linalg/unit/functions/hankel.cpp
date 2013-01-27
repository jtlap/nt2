//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 linalg toolbox - hankel function"

#include <nt2/table.hpp>
#include <nt2/include/functions/hankel.hpp>
#include <nt2/include/functions/trans.hpp>
#include <nt2/include/functions/linspace.hpp>
#include <nt2/include/functions/fliplr.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>


NT2_TEST_CASE_TPL ( hankelexpr, NT2_REAL_TYPES)
{
  nt2::table<T> b5 =
    nt2::trans(nt2::reshape(nt2::cons(
                              T(1),    T(2),     T(3),     T(4),     T(5),
                              T(2),    T(3),     T(4),     T(5),     T(0),
                              T(3),    T(4),     T(5),     T(0),     T(0),
                              T(4),    T(5),     T(0),     T(0),     T(0),
                              T(5),    T(0),     T(0),     T(0),     T(0)
                              ), nt2::of_size(5, 5)));
  nt2::table<T> v =  nt2::linspace(T(1), T(5), 5);
  NT2_DISPLAY( nt2::hankel(v));
  NT2_TEST_EQUAL(b5, nt2::hankel(v));
}

NT2_TEST_CASE_TPL ( hankel2, NT2_REAL_TYPES)
{
  nt2::table<T> b5 =
    nt2::trans(nt2::reshape(nt2::cons(
                              T(1),    T( 2),     T(3),     T(4),     T(5),
                              T(2),    T( 3),     T(4),     T(5),     T(4),
                              T(3),    T( 4),     T(5),     T(4),     T(3),
                              T(4),    T( 5),     T(4),     T(3),     T(2),
                              T(5),    T( 4),     T(3),     T(2),     T(1)
                              ), nt2::of_size(5, 5)));
  nt2::table<T> v =  nt2::linspace(T(1), T(5), 5);
  NT2_DISPLAY( nt2::hankel(v, nt2::fliplr(v)));
  NT2_TEST_EQUAL(b5, nt2::hankel(v, nt2::fliplr(v)));
}
