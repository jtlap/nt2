//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 linalg toolbox - dramadah function"

#include <nt2/table.hpp>
#include <nt2/include/functions/dramadah.hpp>
#include <nt2/include/functions/transpose.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>

NT2_TEST_CASE_TPL ( dramadah, (double))
{
  nt2::table<T> c41 =
    nt2::trans(nt2::cons(nt2::of_size(4, 4),
                         T(1), T(1), T(0), T(1),
                         T(0), T(1), T(1), T(0),
                         T(0), T(0), T(1), T(1),
                         T(1), T(0), T(0), T(1)
                 ));
  nt2::table<T> c42 =
    nt2::trans(nt2::cons(nt2::of_size(4, 4),
                         T(1), T(1), T(0), T(1),
                         T(0), T(1), T(1), T(0),
                         T(0), T(0), T(1), T(1),
                         T(0), T(0), T(0), T(1)
                 ));
  nt2::table<T> c43 =
    nt2::trans(nt2::cons(nt2::of_size(4, 4),
                         T(1), T(1), T(0), T(0),
                         T(0), T(1), T(1), T(0),
                         T(1), T(0), T(1), T(1),
                         T(0), T(1), T(0), T(1)
                 ));


  nt2::table<T> v =  nt2::dramadah( 4, 1);
  NT2_DISPLAY(v);
  NT2_DISPLAY(c41);
  NT2_TEST_EQUAL(v, c41);
  v =  nt2::dramadah( 4, 2);
  NT2_DISPLAY(v);
  NT2_DISPLAY(c42);
  NT2_TEST_EQUAL(v, c42);
  v =  nt2::dramadah( 4, 3);
  NT2_DISPLAY(v);
  NT2_DISPLAY(c43);
  NT2_TEST_EQUAL(v, c43);

}

NT2_TEST_CASE_TPL ( dramadah_targetted, NT2_REAL_TYPES)
{
  nt2::table<T> c41 =
    nt2::trans(nt2::cons(nt2::of_size(4, 4),
                         T(1), T(1), T(0), T(1),
                         T(0), T(1), T(1), T(0),
                         T(0), T(0), T(1), T(1),
                         T(1), T(0), T(0), T(1)
                 ));
  nt2::table<T> c42 =
    nt2::trans(nt2::cons(nt2::of_size(4, 4),
                         T(1), T(1), T(0), T(1),
                         T(0), T(1), T(1), T(0),
                         T(0), T(0), T(1), T(1),
                         T(0), T(0), T(0), T(1)
                 ));
  nt2::table<T> c43 =
    nt2::trans(nt2::cons(nt2::of_size(4, 4),
                         T(1), T(1), T(0), T(0),
                         T(0), T(1), T(1), T(0),
                         T(1), T(0), T(1), T(1),
                         T(0), T(1), T(0), T(1)
                 ));


  nt2::table<T> v =  nt2::dramadah( 4, 1, nt2::meta::as_<T>());
  v = nt2::dramadah<T>( 4, 1);
  NT2_DISPLAY(v);
  NT2_DISPLAY(c41);
  NT2_TEST_EQUAL(v, c41);
  v =  nt2::dramadah( 4, 2, nt2::meta::as_<T>());
  NT2_DISPLAY(v);
  NT2_DISPLAY(c42);
  NT2_TEST_EQUAL(v, c42);
  v =  nt2::dramadah( 4, 3, nt2::meta::as_<T>());
  NT2_DISPLAY(v);
  NT2_DISPLAY(c43);
  NT2_TEST_EQUAL(v, c43);

}

