//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 linalg toolbox - binomial function"

#include <nt2/table.hpp>
#include <nt2/include/functions/binomial.hpp>
#include <nt2/include/functions/transpose.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/functions/cast.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>

NT2_TEST_CASE_TPL ( binomial, NT2_REAL_TYPES)
{
  nt2::table<T> b4 =
    nt2::trans(nt2::reshape(nt2::cons(
                              T(1),    T( 3),    T( 3),    T( 1),
                              T(1),    T( 1),    T(-1),    T(-1),
                              T(1),    T(-1),    T(-1),    T( 1),
                              T(1),    T(-3),    T( 3),    T(-1)
                              ), nt2::of_size(4, 4)));
   nt2::table<T> v = nt2::binomial(4, nt2::meta::as_<T>());
   nt2::table<T> v1 = nt2::binomial<T>(4);
   nt2::table<T> v2 = nt2::cast<T>(nt2::binomial(4));
   NT2_TEST_EQUAL(v, b4);
   NT2_TEST_EQUAL(v1, b4);
   NT2_TEST_EQUAL(v2, b4);
}



