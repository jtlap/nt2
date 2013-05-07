//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/table.hpp>
#include <nt2/include/functions/sincosd.hpp>
#include <nt2/include/functions/sind.hpp>
#include <nt2/include/functions/cosd.hpp>
#include <nt2/include/functions/linspace.hpp>
#include <nt2/include/functions/of_size.hpp>
#include <nt2/include/functions/tie.hpp>
#include <nt2/include/constants/pi.hpp>


#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>

NT2_TEST_CASE_TPL(sincosd_table, NT2_REAL_TYPES)
{
  using nt2::sincosd;
  using nt2::table;
  typedef table<T> tab_t;
  static const int nb = 60;
  tab_t a = nt2::linspace(T(0), T(1800), nb);
  tab_t  s(nt2::of_size(1, nb)), c(nt2::of_size(1, nb));
  {
    sincosd(a, s, c);
    NT2_TEST_ULP_EQUAL(s, nt2::sind(a),1.5);
    NT2_TEST_ULP_EQUAL(c, nt2::cosd(a),1.5);
  }

  {
    s = sincosd(a, c);
    NT2_TEST_ULP_EQUAL(s, nt2::sind(a),1.5);
    NT2_TEST_ULP_EQUAL(c, nt2::cosd(a),1.5);
  }

  {
    nt2::tie(s, c) = sincosd(a);
    NT2_TEST_ULP_EQUAL(s, nt2::sind(a),1.5);
    NT2_TEST_ULP_EQUAL(c, nt2::cosd(a),1.5);
  }
}
