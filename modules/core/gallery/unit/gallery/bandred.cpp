//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 gallery toolbox - bandred function"

#include <nt2/table.hpp>
#include <nt2/include/functions/bandred.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/blkdiag.hpp>
#include <nt2/include/functions/transpose.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/module.hpp>


NT2_TEST_CASE_TPL ( bandred, NT2_REAL_TYPES)
{
  typedef typename nt2::meta::as_<T> ta_t;
  nt2::table<T> rc, p;
  nt2::table<T> br622 = nt2::blkdiag(
    nt2::transpose(
      nt2::cons(nt2::of_size(3, 3),
                T( 1),     T(1),    T(-2),
                T( 1),     T(1),    T(-2),
                T(-2),    T(-2),   T( 4))),
      nt2::zeros(3, 3, ta_t())
  );
  p = nt2::ones(6, 6, nt2::meta::as_<T>());
  rc = nt2::bandred(p, 2, 2);
  NT2_TEST_ULP_EQUAL(br622, rc, 1);
  NT2_DISPLAY(br622);
  NT2_DISPLAY(rc);
}






