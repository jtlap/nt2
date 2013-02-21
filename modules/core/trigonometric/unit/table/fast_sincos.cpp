//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/table.hpp>
#include <nt2/include/functions/fast_sincos.hpp>
#include <nt2/include/functions/sin.hpp>
#include <nt2/include/functions/cos.hpp>
#include <nt2/include/functions/linspace.hpp>
#include <nt2/include/functions/of_size.hpp>
#include <nt2/include/functions/tie.hpp>
#include <nt2/include/constants/pio_4.hpp>


#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>

NT2_TEST_CASE_TPL(fast_sincos_table, NT2_REAL_TYPES)
{
  using nt2::fast_sincos;
  using nt2::table;
  typedef table<T> tab_t;
  static const int nb = 60;
  tab_t a = nt2::linspace(T(0), nt2::Pio_4<T>(), nb);
  tab_t  s(nt2::of_size(1, nb)), c(nt2::of_size(1, nb));
  {
    fast_sincos(a, s, c);
    NT2_TEST_ULP_EQUAL(s, nt2::sin(a),0.5);
    NT2_TEST_ULP_EQUAL(c, nt2::cos(a),0.5);
  }

  {
    s = fast_sincos(a, c);
    NT2_TEST_ULP_EQUAL(s, nt2::sin(a),0.5);
    NT2_TEST_ULP_EQUAL(c, nt2::cos(a),0.5);
  }

  {
    nt2::tie(s, c) = fast_sincos(a);
    NT2_TEST_ULP_EQUAL(s, nt2::sin(a),0.5);
    NT2_TEST_ULP_EQUAL(c, nt2::cos(a),0.5);
  }
}
