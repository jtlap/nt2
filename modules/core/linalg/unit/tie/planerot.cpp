//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 linalg toolbox - tied planerot function"

#include <nt2/table.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/functions/planerot.hpp>
#include <nt2/include/functions/rif.hpp>
#include <nt2/include/functions/tie.hpp>
#include <nt2/include/functions/isulpequal.hpp>
#include <nt2/include/functions/mtimes.hpp>
#include <nt2/include/constants/sqrt_2.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>

NT2_TEST_CASE_TPL ( planerot, NT2_REAL_TYPES)
{
  typedef typename nt2::meta::as_integer<T, signed>::type  itype_t;
  typedef nt2::table<itype_t> it_t;
  typedef nt2::table<T> table_t;
  table_t x = nt2::ones(2, 1, nt2::meta::as_<T>());
  NT2_DISPLAY(x);
  table_t g, y;
  nt2::tie(g, y) = nt2::planerot(x);
  NT2_DISPLAY(g);
  NT2_DISPLAY(y);
  table_t r = nt2::zeros(2, 1, nt2::meta::as_<T>());
  r(1) = nt2::Sqrt_2<T>();
  NT2_TEST_ULP_EQUAL(r, y, 0.5);
}

NT2_TEST_CASE_TPL ( planerot2, NT2_REAL_TYPES)
{
  typedef typename nt2::meta::as_integer<T, signed>::type  itype_t;
  typedef nt2::table<itype_t> it_t;
  typedef nt2::table<T> table_t;
  table_t x = nt2::rif(2, 1, nt2::meta::as_<T>());
  NT2_DISPLAY(x);
  table_t g, y;
  nt2::tie(g, y) = nt2::planerot(x);
  NT2_DISPLAY(g);
  NT2_DISPLAY(y);
  NT2_TEST(nt2::isulpequal(nt2::mtimes(g, x), y));
}


