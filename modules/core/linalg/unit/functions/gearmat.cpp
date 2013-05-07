//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 linalg toolbox - gearmat function"

#include <nt2/table.hpp>
#include <nt2/include/functions/gearmat.hpp>
#include <nt2/include/functions/transpose.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/functions/mtimes.hpp>
#include <nt2/include/functions/triw.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>
#include <nt2/table.hpp>

NT2_TEST_CASE_TPL ( gearmat, NT2_REAL_TYPES)
{
  nt2::table<T> gear4 =nt2::trans(nt2::reshape(nt2::cons(
                                                 T( 0),    T(1),     T(0),     T(1),
                                                 T( 1),    T(0),     T(1),     T(0),
                                                 T( 0),    T(1),     T(0),     T(1),
                                                 T(-1),    T(0),     T(1),     T(0)
                                               ),  nt2::of_size(4, 4)));
  NT2_DISPLAY(gear4);
  nt2::table<T> v = nt2::gearmat(4, 4, -4, nt2::meta::as_<T>());
  NT2_DISPLAY(v);
  NT2_TEST_EQUAL(v, gear4);
  NT2_TEST_EQUAL(nt2::gearmat(4,nt2::meta::as_<T>()), gear4);
  NT2_TEST_EQUAL(nt2::gearmat(4,T(4)), gear4);
  NT2_TEST_EQUAL(nt2::gearmat(4,T(4), T(-4)), gear4);
}


