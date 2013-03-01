//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 linalg toolbox - invhess function"

#include <nt2/table.hpp>
#include <nt2/include/functions/invhess.hpp>
#include <nt2/include/functions/trans.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/functions/cast.hpp>
#include <nt2/include/functions/colon.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/module.hpp>


NT2_TEST_CASE_TPL ( invhess_templated, NT2_REAL_TYPES)
{
  nt2::table<T> ih4 =
    nt2::trans(nt2::reshape(nt2::cons(
                              T(1),    T(-1),    T(-1),    T(-1),
                              T(1),    T( 2),    T(-2),    T(-2),
                              T(1),    T( 2),    T( 3),    T(-3),
                              T(1),    T( 2),    T( 3),    T( 4)
                            ), nt2::of_size(4, 4)));
  NT2_TEST_EQUAL(nt2::invhess( nt2::_(T(1), T(4)), -nt2::_(T(1), T(3))), ih4);
  NT2_TEST_EQUAL(nt2::invhess( nt2::_(T(1), T(4))), ih4);
  NT2_TEST_EQUAL(nt2::invhess(4, nt2::meta::as_<T>()), ih4);
  NT2_TEST_EQUAL(nt2::cast<T>(nt2::invhess(4)), ih4);
}
