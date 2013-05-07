//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 linalg toolbox - chebvand function"

#include <nt2/table.hpp>
#include <nt2/include/functions/chebvand.hpp>
#include <nt2/include/functions/transpose.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>

NT2_TEST_CASE_TPL ( chebvand, NT2_REAL_TYPES)
{

  nt2::table<T> c30 =
    nt2::trans(nt2::reshape(nt2::cons(
                              T(1.0),  T(1.0),  T(1.0),
                              T(0),    T(0.5),  T(1.0),
                              T(-1.0), T(-0.5), T(1.0)
                              ), nt2::of_size(3, 3)));
  nt2::table<T> v =  nt2::chebvand( 3, 3);
  NT2_TEST_EQUAL(v, c30);
  nt2::table<T> v1 =  nt2::chebvand( 3, nt2::linspace(T(0), T(1), 3));
  NT2_TEST_EQUAL(v1, c30);
  nt2::table<T> v2 =  nt2::chebvand(3);
  NT2_TEST_EQUAL(v2, c30);
  nt2::table<T> v3 =  nt2::chebvand(nt2::linspace(T(0), T(1), 3));
  NT2_TEST_EQUAL(v3, c30);
  NT2_TEST_EQUAL(nt2::chebvand( 3, 3, nt2::meta::as_<T>()), c30);
  NT2_TEST_EQUAL(nt2::chebvand<T>( 3, 3), c30);
  NT2_TEST_EQUAL(nt2::chebvand( 3, nt2::meta::as_<T>()), c30);
  NT2_TEST_EQUAL(nt2::chebvand<T>(3), c30);

}

