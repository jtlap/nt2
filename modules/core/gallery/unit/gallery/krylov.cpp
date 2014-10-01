//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 gallery toolbox - krylov function"

#include <nt2/table.hpp>
#include <nt2/include/functions/krylov.hpp>
#include <nt2/include/functions/transpose.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/functions/extent.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

NT2_TEST_CASE_TPL ( krylov, NT2_REAL_TYPES)
{
  nt2::table<T> a = nt2::_(T(1), T(3));
  nt2::table<T> t30 =nt2::trans(nt2::reshape(nt2::cons(
                                               T(0), T(1), T(0),
                                               T(2), T(0), T(2),
                                               T(0), T(1), T(0)),
                                             nt2::of_size(3, 3)));

  nt2::table<T> kt30 =nt2::trans(nt2::reshape(nt2::cons(
                                               T(1), T(1), T(4),
                                               T(1), T(4), T(4),
                                               T(1), T(1), T(4)),
                                             nt2::of_size(3, 3)));
  NT2_TEST_ULP_EQUAL(krylov(t30, nt2::ones(3, 1, nt2::meta::as_<T>()), 3), kt30, 0.5);
  nt2::table<T> z = krylov(t30, nt2::ones(3, 1, nt2::meta::as_<T>()));
  NT2_TEST_ULP_EQUAL(z, kt30, 0.5);
  nt2::table<T> z1 = krylov(t30);
  NT2_TEST_ULP_EQUAL(z1, kt30, 0.5);

  NT2_TEST_ULP_EQUAL(krylov(t30, nt2::ones(3, 1, nt2::meta::as_<T>()))   , kt30, 0.5);
  NT2_TEST_ULP_EQUAL(krylov(t30), kt30, 0.5);
}

NT2_TEST_CASE( krylov_scalar )
{
  nt2::table<double> z2  = nt2::krylov(3);

  NT2_TEST_EQUAL( nt2::extent(z2), nt2::of_size(3,3) );
  NT2_TEST_EQUAL( z2(nt2::_,1), nt2::ones(3,1) );
}


