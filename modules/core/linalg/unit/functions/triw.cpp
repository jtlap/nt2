//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 linalg toolbox - triw function"

#include <nt2/table.hpp>
#include <nt2/include/functions/triw.hpp>
#include <nt2/include/functions/trans.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/functions/diag_of.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>

NT2_TEST_CASE_TPL ( triw, NT2_REAL_TYPES)
{
  nt2::table<T> r4 =
    nt2::trans(nt2::cons(nt2::of_size(4, 4),
                         T(1),    T(-1),  T(-1),  T(-1),
                         T(0),    T( 1),  T(-1),  T(-1),
                         T(0),    T( 0),  T( 1),  T(-1),
                         T(0),    T( 0),  T( 0),  T( 1)
                 ));
  NT2_DISPLAY(r4);
  nt2::table<T> r;
  r =  nt2::triw(4, 4, nt2::meta::as_<T>());
  NT2_DISPLAY(r);
  NT2_TEST_EQUAL(r, r4);
  nt2::table<T> r42 =
    nt2::trans(nt2::cons(nt2::of_size(4, 4),
                         T(1),    T(-1),  T(-1),   T(0),
                         T(0),    T( 1),  T(-1),  T(-1),
                         T(0),    T( 0),  T( 1),  T(-1),
                         T(0),    T( 0),  T( 0),  T( 1)
                 ));

  r =  nt2::triw(4, 4, T(-1), 2);
  NT2_DISPLAY(r);
  NT2_TEST_EQUAL(r, r42);
}



