//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 linalg toolbox - compar function"

#include <nt2/table.hpp>
#include <nt2/include/functions/compar.hpp>
#include <nt2/include/functions/transpose.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/functions/cast.hpp>
#include <nt2/include/functions/triu.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>

NT2_TEST_CASE_TPL ( compar, NT2_REAL_TYPES)
{
  nt2::table<T> x = nt2::reshape(nt2::_(T(1), T(12)), nt2::of_size(3, 4));
  nt2::table<T> c340 =
    nt2::trans(nt2::reshape(nt2::cons(
                              T( 1),    T(-4),    T(-7),   T(-10),
                              T(-2),    T( 5),    T(-8),   T(-11),
                              T(-3),    T(-6),    T( 9),   T(-12)
                              ), nt2::of_size(4, 3)));
  nt2::table<T> v = nt2::compar(x, 0);
  nt2::table<T> v1 = nt2::compar(x);
  NT2_TEST_EQUAL(v, c340);
  NT2_TEST_EQUAL(v1, c340);

  nt2::table<T> c341 =
    nt2::trans(nt2::reshape(nt2::cons(
                              T(  1),   T(-10),   T(-10),   T(-10),
                              T(-11),   T(  5),   T(-11),   T(-11),
                              T(-12),   T(-12),   T(  9),   T(-12)
                              ), nt2::of_size(4, 3)));
  nt2::table<T> v2 = nt2::compar(x, 1);
  NT2_TEST_EQUAL(v2, c341);
  nt2::table<T> v3 = nt2::compar(nt2::triu(x), 1);
  NT2_TEST_EQUAL(v3, nt2::triu(c341));
}




