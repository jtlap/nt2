//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/condeig.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/functions/colon.hpp>
#include <nt2/include/functions/tie.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/include/functions/reshape.hpp>
#include <nt2/table.hpp>



NT2_TEST_CASE_TPL ( condeig1, NT2_REAL_TYPES)
{
  typedef std::complex<T> cT;
  using nt2::condeig;
  typedef nt2::table<T> table_t;
  typedef nt2::table<cT> ctable_t;
  table_t a;
  table_t rs = nt2::cons<T>(nt2::of_size(3, 1),
                         1.039619199903542,
                         1.039619199903542,
                         1.000000000000000);
  a = nt2::reshape(nt2::_(T(1), T(9)), 3, 3);
  NT2_DISPLAY(a);
  table_t s =  condeig(a);
  NT2_TEST_ULP_EQUAL(s, rs, 10);
  ctable_t x, d;
  tie(x, d, s) =  condeig(a);
  NT2_TEST_ULP_EQUAL(s, rs, 10);
}



