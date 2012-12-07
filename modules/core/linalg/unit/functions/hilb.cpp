//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 linalg toolbox - hilb function"

#include <nt2/table.hpp>
#include <nt2/include/functions/hilb.hpp>
#include <nt2/include/functions/trans.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/constants/i.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>

NT2_TEST_CASE_TPL ( hilb, NT2_REAL_TYPES)
{
  nt2::table<T> h3 =
    nt2::trans(nt2::reshape(nt2::cons(
                              T(1.0),     T(0.5),     T(1.0/3.0),
                              T(0.5),     T(1.0/3.0), T(0.25),
                              T(1.0/3.0), T(0.25),    T(0.2)
                              ), nt2::of_size(3, 3)));
  nt2::table<T> v = nt2::hilb(3, nt2::meta::as_<T>());
  NT2_DISPLAY(v);
  NT2_DISPLAY(h3);
  NT2_TEST_EQUAL(v, h3);
}



