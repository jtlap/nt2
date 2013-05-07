//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 linalg toolbox - cauchy function"

#include <nt2/table.hpp>
#include <nt2/include/functions/cauchy.hpp>
#include <nt2/include/functions/rec.hpp>
#include <nt2/include/functions/cif.hpp>
#include <nt2/include/functions/rif.hpp>
#include <nt2/include/functions/transpose.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/functions/colon.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>

NT2_TEST_CASE_TPL ( cauchy_ints, NT2_REAL_TYPES)
{
  NT2_DISPLAY(nt2::cauchy(3, 3, nt2::meta::as_<T>()));
  nt2::table<T> a0 = nt2::_(T(1), 3);
  NT2_DISPLAY(nt2::cauchy(a0));

  nt2::table<T> v =  cauchy(a0);
  NT2_DISPLAY(v);
  nt2::table<T> z = nt2::rec(nt2::cif(3, nt2::meta::as_<T>())+nt2::rif(3, nt2::meta::as_<T>()));
  NT2_TEST_EQUAL(v, z);
}

NT2_TEST_CASE_TPL ( cauchy_ints_2, NT2_REAL_TYPES)
{
  nt2::table<T> m3 =nt2::trans(nt2::cons(nt2::of_size(3, 3),
                                         T(90), T(-90), T(-30),
                                         T(30), T( 90), T(-90),
                                         T(18), T( 30), T( 90))/T(45));
  nt2::table<T> v =  nt2::cauchy(nt2::_(T(1.5), T(3.5)), -nt2::_(T(1), T(3)));
  NT2_DISPLAY(v);
  NT2_TEST_EQUAL(v, m3);
}
