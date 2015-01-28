//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/sph2cart.hpp>
#include <nt2/include/functions/sin.hpp>
#include <nt2/include/functions/cos.hpp>
#include <nt2/include/functions/linspace.hpp>
#include <nt2/include/functions/multiplies.hpp>
#include <nt2/include/functions/of_size.hpp>
#include <nt2/include/functions/tie.hpp>
#include <nt2/table.hpp>
#include <boost/fusion/include/at_c.hpp>


#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>

NT2_TEST_CASE_TPL(sph2cart_table, NT2_REAL_TYPES)
{
  using nt2::sph2cart;
  using nt2::table;
  typedef table<T> tab_t;
  static const int nb = 60;
  tab_t a = nt2::linspace(T(0), T(10), nb);
  tab_t b = nt2::linspace(T(0), T(1 ), nb);
  tab_t c = nt2::linspace(T(2), T(3 ), nb);
  tab_t  e(nt2::of_size(1, nb)), f(nt2::of_size(1, nb)), g(nt2::of_size(1, nb));
  {
    sph2cart(a, b, c, e, f, g);
    NT2_TEST_ULP_EQUAL(e, c*nt2::cos(b)*nt2::cos(a),0.5);
    NT2_TEST_ULP_EQUAL(f, c*nt2::cos(b)*nt2::sin(a),0.5);
    NT2_TEST_ULP_EQUAL(g, c*nt2::sin(b),0.5);
  }

  {
    e = sph2cart(a, b, c, f, g);
    NT2_TEST_ULP_EQUAL(e, c*nt2::cos(b)*nt2::cos(a),0.5);
    NT2_TEST_ULP_EQUAL(f, c*nt2::cos(b)*nt2::sin(a),0.5);
    NT2_TEST_ULP_EQUAL(g, c*nt2::sin(b),0.5);
  }

  {
    auto z = sph2cart(a, b, c, g);
    NT2_TEST_ULP_EQUAL(boost::fusion::at_c<0>(z), c*nt2::cos(b)*nt2::cos(a),0.5);
    NT2_TEST_ULP_EQUAL(boost::fusion::at_c<1>(z), c*nt2::cos(b)*nt2::sin(a),0.5);
    NT2_TEST_ULP_EQUAL(g, c*nt2::sin(b),0.5);
  }
  {
    nt2::tie(e, f, g) = sph2cart(a, b, c);
    NT2_TEST_ULP_EQUAL(e, c*nt2::cos(b)*nt2::cos(a),0.5);
    NT2_TEST_ULP_EQUAL(f, c*nt2::cos(b)*nt2::sin(a),0.5);
    NT2_TEST_ULP_EQUAL(g, c*nt2::sin(b),0.5);
  }
}
