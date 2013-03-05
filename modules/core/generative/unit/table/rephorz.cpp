//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2::rephorz function"

#include <nt2/table.hpp>
#include <nt2/include/functions/rephorz.hpp>
#include <nt2/include/functions/horzcat.hpp>
#include <nt2/include/functions/rif.hpp>
#include <nt2/include/functions/cif.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

NT2_TEST_CASE_TPL( rephorz_, NT2_REAL_TYPES )
{
  using nt2::_;
  using nt2::end_;

  nt2::table<T> a = nt2::rif(nt2::of_size(7, 1), nt2::meta::as_<T>());
  nt2::table<T> b = rephorz(a,  2);

  NT2_TEST_EQUAL(b,  rephorz(a,  2));
  NT2_TEST_EQUAL(b(_, _(1u, size(a, 2))), a);
  NT2_TEST_EQUAL(b(_, _(size(a, 2)+1, end_)), a);

  a = nt2::cif(nt2::of_size(7, 7), nt2::meta::as_<T>());
  b = rephorz(a,  2);
  NT2_TEST_EQUAL(b,  rephorz(a,  2));
  NT2_TEST_EQUAL(b(_, _(1u, size(a, 2))), a);
  NT2_TEST_EQUAL(b(_, _(size(a, 2)+1, end_)), a);
}
