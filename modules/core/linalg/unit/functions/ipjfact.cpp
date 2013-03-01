//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 linalg toolbox - ipjfact function"

#include <nt2/table.hpp>
#include <nt2/include/functions/ipjfact.hpp>
#include <nt2/include/functions/trans.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/functions/diag_of.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>
#include <nt2/include/functions/tie.hpp>


NT2_TEST_CASE_TPL ( ipjfact_double, (double))
{
  nt2::table<T> r4 = nt2::trans(nt2::cons(nt2::of_size(4, 4),
                                          T(  2),         T(  6),        T(  24),       T(  120),
                                          T(  6),         T( 24),        T( 120),       T(  720),
                                          T( 24),         T(120),        T( 720),       T( 5040),
                                          T(120),         T(720),        T(5040),       T(40320)
                                         ));
  nt2::table<T> r =  nt2::ipjfact(4, nt2::meta::as_<T>());
  T d;
  NT2_DISPLAY(r);
  NT2_TEST_ULP_EQUAL(r, r4, 0.5);
  nt2::tie(r, d)  =  nt2::ipjfact(4, nt2::meta::as_<T>());
  NT2_TEST_ULP_EQUAL(r, r4, 0.5);
  NT2_TEST_ULP_EQUAL(d, T(414720), 0.5);

}
