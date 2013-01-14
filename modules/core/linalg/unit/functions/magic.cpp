//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 linalg toolbox - magic function"

#include <nt2/table.hpp>
#include <nt2/include/functions/magic.hpp>
#include <nt2/include/functions/trans.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/cast.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>

NT2_TEST_CASE_TPL ( magicodd, NT2_REAL_TYPES)
{
  nt2::table<T> m3 =
    nt2::trans(nt2::reshape(nt2::cons(
                              T(8), T(1), T(6),
                              T(3), T(5), T(7),
                              T(4), T(9), T(2)
                              ), nt2::of_size(3, 3)));
   nt2::table<T> v =  nt2::magic(3, nt2::meta::as_<T>());
   NT2_DISPLAY(v);
  nt2::table<T> v1 = nt2::cast<T>(nt2::magic(3));
  nt2::table<T> v2 = nt2::magic<T>(3);

  NT2_TEST_EQUAL(v, m3);
  NT2_TEST_EQUAL(v1, m3);
   NT2_TEST_EQUAL(v2, m3);
}

NT2_TEST_CASE_TPL ( magic2even, NT2_REAL_TYPES)
{
  nt2::table<T> m4 =
    nt2::trans(nt2::reshape(nt2::cons(
                              T(16),     T(2),     T(3),    T(13),
                              T(5),    T(11),    T(10),     T(8),
                              T(9),     T(7),    T( 6),    T(12),
                              T(4),    T(14),    T(15),     T(1)
                              ), nt2::of_size(4, 4)));
   nt2::table<T> v =  nt2::magic(4, nt2::meta::as_<T>());
   NT2_DISPLAY(v);
  nt2::table<T> v1 = nt2::cast<T>(nt2::magic(4));
  nt2::table<T> v2 = nt2::magic<T>(4);

  NT2_TEST_EQUAL(v, m4);
  NT2_TEST_EQUAL(v1, m4);
  NT2_TEST_EQUAL(v2, m4);

}

NT2_TEST_CASE_TPL ( magiceven, NT2_REAL_TYPES)
{
  nt2::table<T> m6 =
    nt2::trans(nt2::reshape(nt2::cons(
                              T(35),   T(1),     T(6),    T(26),    T(19),    T(24),
                              T(3),    T(32),    T(7),    T(21),    T(23),    T(25),
                              T(31),   T(9),     T(2),    T(22),    T(27),    T(20),
                              T(8),    T(28),    T(33),   T(17),    T(10),    T(15),
                              T(30),   T(5),     T(34),   T(12),    T(14),    T(16),
                              T(4),    T(36),    T(29),   T(13),    T(18),    T(11)
                              ), nt2::of_size(6, 6)));
  nt2::table<T> v =  nt2::magic(6, nt2::meta::as_<T>());
  nt2::table<T> v1 = nt2::cast<T>(nt2::magic(6));
  nt2::table<T> v2 = nt2::magic<T>(6);

  NT2_TEST_EQUAL(v, m6);
  NT2_TEST_EQUAL(v1, m6);
  NT2_TEST_EQUAL(v2, m6);

}

