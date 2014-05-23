//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/table.hpp>
#include <nt2/include/functions/two_split.hpp>
#include <nt2/include/constants/eps.hpp>
#include <nt2/include/functions/numel.hpp>
#include <nt2/include/functions/colon.hpp>
#include <nt2/include/functions/size.hpp>
#include <nt2/include/functions/tie.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>

NT2_TEST_CASE_TPL(remquo_table, NT2_REAL_TYPES)
{
  // Reference values
  nt2::table<T> v = nt2::_(T(1), T(10)) - nt2::Eps<T>();
  nt2::table<T> im(nt2::extent(v));
  nt2::table<T> ie(nt2::extent(v));

  std::size_t nb = nt2::numel(v);

  for(std::size_t i=1; i <= nb; ++i)
  {
    im(i) = nt2::two_split(v(i), ie(i));
  }

  {
    // -1 to test resizing works properly
    nt2::table<T> m(nt2::of_size(nb-1));
    nt2::table<T> e(nt2::of_size(nb));

    nt2::two_split(v,m,e);
    NT2_TEST_ULP_EQUAL(m, im, 0.5);
    NT2_TEST_ULP_EQUAL(e, ie, 0.5);
  }

  {
    // -1 to test resizing works properly
    nt2::table<T> m(nt2::of_size(nb-1));
    nt2::table<T> e(nt2::of_size(nb));

    m = two_split(v, e);
    NT2_TEST_ULP_EQUAL(m, im, 0.5);
    NT2_TEST_ULP_EQUAL(e, ie, 0.5);
  }

  {
    // -1 to test resizing works properly
    nt2::table<T> m(nt2::of_size(nb-1));
    nt2::table<T> e(nt2::of_size(nb));

    nt2::tie(m, e) = nt2::two_split(v);

    NT2_TEST_ULP_EQUAL(m, im, 0.5);
    NT2_TEST_ULP_EQUAL(e, ie, 0.5);
  }

  {
    // -1 to test resizing works properly
    nt2::table<T> m(nt2::of_size(nb-1));

    m = nt2::two_split(v);
    NT2_TEST_ULP_EQUAL(m, im, 0.5);
  }
}
