//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 linalg toolbox - invol function"

#include <nt2/table.hpp>
#include <nt2/include/functions/invol.hpp>
#include <nt2/include/functions/transpose.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/functions/cast.hpp>
#include <nt2/include/functions/colon.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/module.hpp>


NT2_TEST_CASE_TPL ( invol_templated, NT2_REAL_TYPES)
{
  nt2::table<T> ih4 =
    nt2::trans(nt2::reshape(nt2::cons(

      T( -1200),      T(   150),      T(   100),       T(   75),
      T(-36000),      T(  6000),      T(  4500),       T( 3600),
      T( 72000),      T(-13500),      T(-10800),       T(-9000),
      T(-42000),      T(  8400),      T(  7000),       T( 6000)
                            )/T(300), nt2::of_size(4, 4)));
  NT2_TEST_ULP_EQUAL(nt2::invol(4, nt2::meta::as_<T>()), ih4, 1.5);
  NT2_TEST_ULP_EQUAL(nt2::cast<T>(nt2::invol(4)), ih4, 1.5);
}
