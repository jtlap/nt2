//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/table.hpp>
#include <nt2/include/functions/modf.hpp>
#include <nt2/include/functions/linspace.hpp>
#include <nt2/include/functions/of_size.hpp>
#include <nt2/include/functions/tie.hpp>

#include <nt2/sdk/meta/as_integer.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

NT2_TEST_CASE_TPL(modf_table, NT2_REAL_TYPES)
{
  // Reference values
  static const int nb = 10;
  nt2::table<T> v = nt2::linspace(T(1), T(5), nb) + T(0.5);
  nt2::table<T> im(nt2::of_size(1, nb));
  nt2::table<T> ie(nt2::of_size(1, nb));

  for(int i=1; i <= nb; ++i)
  {
    im(i) = nt2::modf(v(i), ie(i));
  }

  nt2::table<T> m2 = nt2::modf(v);
  NT2_TEST_EQUAL(m2, im);

  {
    // -1 to test resizing works properly
    nt2::table<T> m(nt2::of_size(1, nb-1));
    nt2::table<T> e(nt2::of_size(1, nb));

    nt2::modf(v,m,e);
    NT2_TEST_EQUAL(m, im);
    NT2_TEST_EQUAL(e, ie);
  }

  {
    // -1 to test resizing works properly
    nt2::table<T> m(nt2::of_size(1, nb-1));
    nt2::table<T> e(nt2::of_size(1, nb));

    m = modf(v, e);
    NT2_TEST_EQUAL(m, im);
    NT2_TEST_EQUAL(e, ie);
  }

  {
    // -1 to test resizing works properly
    nt2::table<T> m(nt2::of_size(1, nb-1));
    nt2::table<T> e(nt2::of_size(1, nb));

    nt2::tie(m, e) = nt2::modf(v);

    NT2_TEST_EQUAL(m, im);
    NT2_TEST_EQUAL(e, ie);
  }

  {
    // -1 to test resizing works properly
    nt2::table<T> m(nt2::of_size(1, nb-1));

    m = nt2::modf(v);

    NT2_TEST_EQUAL(m, im);
  }
}
