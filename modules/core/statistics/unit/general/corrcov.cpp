//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/corrcov.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/functions/colon.hpp>
#include <nt2/include/functions/globalmax.hpp>
#include <nt2/include/functions/average.hpp>
#include <nt2/include/functions/rand.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/functions/from_diag.hpp>
#include <nt2/include/functions/size.hpp>
#include <nt2/include/constants/eps.hpp>
#include <nt2/include/functions/tie.hpp>
#include <nt2/include/functions/inv.hpp>
#include <nt2/include/functions/horzcat.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/include/functions/colon.hpp>
#include <nt2/include/functions/rand.hpp>
#include <nt2/include/functions/reshape.hpp>
#include <nt2/table.hpp>



NT2_TEST_CASE_TPL ( corrcov1, NT2_REAL_TYPES)
{
  typedef std::complex<T> cT;
  using nt2::corrcov;
  typedef nt2::table<T> table_t;
  typedef nt2::table<cT> ctable_t;
  table_t a = nt2::cons<T>(nt2::of_size(4, 4),
                      276,   304,   332,   360,
                      304,   336,   368,   400,
                      332,   368,   404,   440,
                      360,   400,   440,   480);


table_t rc = nt2::cons<T>(nt2::of_size(4, 4),
                     1.000000000000000,   0.998273181236194,   0.994243728262620,   0.989070710093680,
                     0.998273181236194,   1.000000000000000,   0.998820615228279,   0.996023841111995,
                     0.994243728262620,   0.998820615228279,   1.000000000000000,   0.999174576830044,
                     0.989070710093680,   0.996023841111995,   0.999174576830044 ,  1.000000000000000);


table_t rs = nt2::cons<T>(nt2::of_size(4, 1),
                     16.613247725836150,
                     18.330302779823359,
                     20.099751242241780,
                     21.908902300206645);
  NT2_DISPLAY(a);
  table_t c, s;
  tie(c, s)=  corrcov(a);
  NT2_TEST_ULP_EQUAL(s, rs, 10);
  NT2_TEST_ULP_EQUAL(c, rc, 10);
}
NT2_TEST_CASE_TPL ( corrcov2, NT2_REAL_TYPES)
{
  typedef std::complex<T> cT;
  using nt2::corrcov;
  typedef nt2::table<T> table_t;
  typedef nt2::table<cT> ctable_t;
  table_t a = nt2::cons<T>(nt2::of_size(4, 4),
                           1335.26, 28.6667, 117.655, -413.241,
                           28.6667, 1350.34, -58.7517, -71.1862,
                           117.655, -58.7517, 923.748, -132.755,
                           -413.241, -71.1862, -132.755, 1223.6);


table_t rc = nt2::cons<T>(nt2::of_size(4, 4),
     1.000000000000000e+00,     2.134878756114708e-02,     1.059377422598603e-01,    -3.232963117431662e-01,
     2.134878756114708e-02,     1.000000000000000e+00,    -5.260440536297345e-02,    -5.538019874373137e-02,
     1.059377422598603e-01,    -5.260440536297345e-02,     1.000000000000000e+00,    -1.248689320322681e-01,
    -3.232963117431661e-01,    -5.538019874373137e-02,    -1.248689320322681e-01,     1.000000000000000e+00);


table_t rs = nt2::cons<T>(nt2::of_size(4, 1),
                          3.654120961325719e+01,
                          3.674697266442502e+01,
                          3.039322292880438e+01,
                          3.497999428244665e+01 );
  NT2_DISPLAY(a);
  table_t c, s;
  tie(c, s)=  corrcov(a);
  NT2_TEST_ULP_EQUAL(s, rs, 10);
  NT2_TEST_ULP_EQUAL(c, rc, 10);
}



