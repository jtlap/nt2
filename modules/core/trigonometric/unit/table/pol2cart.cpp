//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/pol2cart.hpp>
#include <nt2/include/functions/sin.hpp>
#include <nt2/include/functions/cos.hpp>
#include <nt2/include/functions/linspace.hpp>
#include <nt2/include/functions/multiplies.hpp>
#include <nt2/include/functions/of_size.hpp>
#include <nt2/include/functions/tie.hpp>
#include <nt2/include/constants/pi.hpp>
#include <nt2/table.hpp>


#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>

NT2_TEST_CASE_TPL(pol2cart_table, NT2_REAL_TYPES)
{
  using nt2::pol2cart;
  using nt2::table;
  typedef table<T> tab_t;
  static const int nb = 60;
  tab_t a = nt2::linspace(T(0), T(10)*nt2::Pi<T>(), nb);
  tab_t r = nt2::linspace(T(1), T(5), nb);
  tab_t  s(nt2::of_size(1, nb)), c(nt2::of_size(1, nb));
  {
    pol2cart(r, a, c, s);
    NT2_TEST_ULP_EQUAL(s, r*nt2::sin(a),0.5);
    NT2_TEST_ULP_EQUAL(c, r*nt2::cos(a),0.5);
  }

  {
    c = pol2cart(r, a, s);
    NT2_TEST_ULP_EQUAL(s, r*nt2::sin(a),0.5);
    NT2_TEST_ULP_EQUAL(c, r*nt2::cos(a),0.5);
  }

  {
    nt2::tie(c, s) = pol2cart(r, a);
    NT2_TEST_ULP_EQUAL(s, r*nt2::sin(a),0.5);
    NT2_TEST_ULP_EQUAL(c, r*nt2::cos(a),0.5);
  }
}
