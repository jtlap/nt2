//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 linalg toolbox - toeppen function"

#include <nt2/table.hpp>
#include <nt2/include/functions/toeppen.hpp>
#include <nt2/include/functions/transpose.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/functions/repnum.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>

NT2_TEST_CASE_TPL ( toeppen_default, NT2_REAL_TYPES)
{
  nt2::table<T> t6 =
    nt2::trans(nt2::reshape(nt2::cons(
                              T(3), T(4), T(5), T(0), T(0), T(0),
                              T(2), T(3), T(4), T(5), T(0), T(0),
                              T(1), T(2), T(3), T(4), T(5), T(0),
                              T(0), T(1), T(2), T(3), T(4), T(5),
                              T(0), T(0), T(1), T(2), T(3), T(4),
                              T(0), T(0), T(0), T(1), T(2), T(3)),
                            nt2::of_size(6, 6)));
  nt2::table<T> ruthis =
    nt2::trans(nt2::reshape(nt2::cons(
                              T(  0),   T( 10),   T(  1),   T(  0),   T(  0),    T( 0),
                              T(-10),   T(  0),   T( 10),   T(  1),   T(  0),    T( 0),
                              T(  1),   T(-10),   T(  0),   T( 10),   T(  1),    T( 0),
                              T(  0),   T(  1),   T(-10),   T(  0),   T( 10),    T( 1),
                              T(  0),   T(  0),   T(  1),   T(-10),   T(  0),    T(10),
                              T(  0),   T(  0),   T(  0),   T(  1),   T(-10),    T( 0)),
                            nt2::of_size(6, 6)));
  NT2_TEST_EQUAL(nt2::toeppen(6, T(1), T(2), T(3), T(4), T(5)), t6);
  NT2_TEST_EQUAL(nt2::toeppen(6, nt2::meta::as_<T>()), ruthis);
}

