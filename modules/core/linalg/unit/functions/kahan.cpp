//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 linalg toolbox - kahan function"

#include <nt2/table.hpp>
#include <nt2/include/functions/kahan.hpp>
#include <nt2/include/functions/transpose.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/functions/cast.hpp>
#include <nt2/include/constants/i.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>

NT2_TEST_CASE_TPL ( kahand, (double))
{

  nt2::table<T> k4 = nt2::trans(nt2::cons(nt2::of_size(4, 4),
   T(1.000000000000888),  T(-0.362357754476674),  T(-0.362357754476674),  T(-0.362357754476674),
   T(                0),  T( 0.932039085967892),  T(-0.337731590275575),  T(-0.337731590275575),
   T(                0),  T(                 0),  T( 0.868696857771067),  T(-0.314779042702705),
   T(                0),  T(                 0),  T(                 0),  T( 0.809659425299355)
                             ));

  nt2::table<T> a1 = nt2::kahan(nt2::of_size(4, 4), T(1.2), T(1.0e3));
  nt2::table<T> a2 = nt2::kahan(4, T(1.2), T(1.0e3), nt2::meta::as_<T>());
  nt2::table<T> a = nt2::kahan(nt2::of_size(4, 4), T(1.2), T(1.0e3), nt2::meta::as_<T>());
  NT2_DISPLAY(a);
  NT2_TEST_ULP_EQUAL(a, k4, 5);
  NT2_TEST_ULP_EQUAL(a2, k4, 5);
  NT2_TEST_ULP_EQUAL(a1, k4, 5);
}

NT2_TEST_CASE_TPL ( kahanr, NT2_REAL_TYPES)
{

  nt2::table<T> k4 = nt2::trans(nt2::cons(nt2::of_size(4, 4),
   T(1.000000000000000),  T(-0.362357754476674),  T(-0.362357754476674),  T(-0.362357754476674),
   T(                0),  T( 0.932039085967226),  T(-0.337731590275575),  T(-0.337731590275575),
   T(                0),  T(                 0),  T( 0.868696857770623),  T(-0.314779042702705),
   T(                0),  T(                 0),  T(                 0),  T( 0.809659425299133)
                                         ));

  nt2::table<T> a1 = nt2::kahan(nt2::of_size(4, 4), T(1.2), T(0));
  nt2::table<T> a2 = nt2::kahan(4, T(1.2), T(0), nt2::meta::as_<T>());
  nt2::table<T> a = nt2::kahan(nt2::of_size(4, 4), T(1.2), T(0), nt2::meta::as_<T>());
  NT2_DISPLAY(a);
  NT2_TEST_ULP_EQUAL(a, k4, 5);
  NT2_TEST_ULP_EQUAL(a2, k4, 5);
  NT2_TEST_ULP_EQUAL(a1, k4, 5);
}


