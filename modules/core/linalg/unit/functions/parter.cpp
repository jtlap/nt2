//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 linalg toolbox - parter function"

#include <nt2/table.hpp>
#include <nt2/include/functions/parter.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/functions/transpose.hpp>
#include <nt2/include/functions/cast.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/module.hpp>

// The execution gives
// With T = [float]
// nt2::parter(3,ta_t()) =  // in parter.cpp
//      2 -2 -0.666667
//      0.666667 2 -2
//      0.4 0.666667 2
// colvect(a0) =  // in cauchy.hpp, but commented out on master
//      1.5
//      2.5
//      3.5
// rowvect(a1) =  // in cauchy.hpp but commented out on master
//      -1 -2 -3
// zz =           // in cauchy.hpp but commented out on master

//      2 -2 -0.666667
//      0.666667 2 -2
//      0.4 0.666667 2
// z =                // in parter.cpp

//      inf -1 -0.5
//      1 inf -1
//      0.5 1 2
////////////////////////// z is false but not garbage it is the result as if one
////////////////////////// had stripped the fractional part of colvect(a0)
////////////////////////// This seems to happen during the affectation process to a table

NT2_TEST_CASE_TPL ( parter, (float))//NT2_REAL_TYPES)
{
  typedef typename nt2::meta::as_<T> ta_t;
  nt2::table<T> m3 =nt2::trans(nt2::cons(nt2::of_size(3, 3),
                                         T(90), T(-90), T(-30),
                                         T(30), T( 90), T(-90),
                                         T(18), T( 30), T( 90))/T(45));

//   NT2_DISPLAY(m3);
  NT2_DISPLAY(nt2::parter(3,ta_t()));
  nt2::table<T> z = nt2::parter(3,ta_t());
  NT2_DISPLAY(z);
  NT2_TEST_ULP_EQUAL(z, m3, 0.5);
//   NT2_TEST_ULP_EQUAL(nt2::parter(3,ta_t()), m3, 0.5);
//   NT2_TEST_ULP_EQUAL(nt2::parter<T>(3), m3, 0.5);
//   NT2_TEST_ULP_EQUAL(nt2::cast<T>(nt2::parter(3)), m3, 0.5);
}




