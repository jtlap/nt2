//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/cart2pol.hpp>
#include <nt2/include/functions/atan2.hpp>
#include <nt2/include/functions/hypot.hpp>
#include <nt2/include/functions/linspace.hpp>
#include <nt2/include/functions/of_size.hpp>
#include <nt2/include/functions/tie.hpp>
#include <nt2/include/constants/pi.hpp>
#include <nt2/table.hpp>


#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>

NT2_TEST_CASE_TPL(cart2pol_table, NT2_REAL_TYPES)
{
  using nt2::cart2pol;
  using nt2::table;
  typedef table<T> tab_t;
  static const int nb = 60;
  tab_t a = nt2::linspace(T(0), T(10), nb);
  tab_t b = nt2::linspace(T(0), T(1 ), nb);
  tab_t  s(nt2::of_size(1, nb)), c(nt2::of_size(1, nb));
  {
    cart2pol(a, b, s, c);
    NT2_TEST_ULP_EQUAL(s, nt2::hypot(a, b),0.5);
    NT2_TEST_ULP_EQUAL(c, nt2::atan2(b, a),0.5);
  }

  {
    s = cart2pol(a, b, c);
    NT2_TEST_ULP_EQUAL(s, nt2::hypot(a, b),0.5);
    NT2_TEST_ULP_EQUAL(c, nt2::atan2(b, a),0.5);

  }

  {
    nt2::tie(s, c) = cart2pol(a, b);
    NT2_TEST_ULP_EQUAL(s, nt2::hypot(a, b),0.5);
    NT2_TEST_ULP_EQUAL(c, nt2::atan2(b, a),0.5);
  }
}
