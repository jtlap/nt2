//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 linalg toolbox - minij function"

#include <nt2/table.hpp>
#include <nt2/include/functions/minij.hpp>
#include <nt2/include/functions/trans.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/functions/mtimes.hpp>
#include <nt2/include/functions/triw.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>
#include <nt2/table.hpp>

NT2_TEST_CASE_TPL ( minij, NT2_REAL_TYPES)
{
  nt2::table<T> t3 =nt2::trans(nt2::reshape(nt2::cons(
                                              T(1), T(1), T(1),
                                              T(1), T(2), T(2),
                                              T(1), T(2), T(3)),
                                            nt2::of_size(3, 3)));
  NT2_DISPLAY(t3);
  nt2::table<T> v = nt2::minij(3, nt2::meta::as_<T>());
  NT2_DISPLAY(v);
  nt2::table<T> v2=  nt2::minij(3, 3, nt2::meta::as_<T>());
  NT2_DISPLAY(v2);

  NT2_TEST_EQUAL(v, t3);
  NT2_TEST_EQUAL(v2, t3);
  nt2::table<T> sqrtv = nt2::triw(3, 3, T(1));
  NT2_DISPLAY(sqrtv);
  NT2_TEST_EQUAL(v2, nt2::mtimes(nt2::trans(sqrtv), sqrtv));
}



