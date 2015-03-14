//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/corrcoef.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/functions/colon.hpp>
#include <nt2/include/functions/globalmax.hpp>
#include <nt2/include/functions/average.hpp>
#include <nt2/include/functions/rand.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/functions/from_diag.hpp>
#include <nt2/include/functions/all.hpp>
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
#include <nt2/include/functions/mean.hpp>
#include <nt2/include/functions/nanmean.hpp>


NT2_TEST_CASE_TPL ( corrcoef1, NT2_REAL_TYPES)
{
  typedef std::complex<T> cT;
  using nt2::corrcoef;
  using nt2::_;
  typedef nt2::table<T> table_t;
  typedef nt2::table<cT> ctable_t;
  table_t a = nt2::cons<T>(nt2::of_size(17, 4),
                           3  , 54 , 55, 32 , 50, 26 , 70, 7  , 45, 1 , 108, 40, 116, 28 , 46 , 16 , 20,
                           94 , 54 , 27, 30 , 43, 109,  9, 112, 14, 62, 117, 92, 76 , 101, 118, 37 , 85,
                           11 , 100, 74, 107, 75, 60 , 93, 73 , 36, 35, 120, 77, 78 , 24 , 84 , 61 , 19,
                           114, 58 , 63, 4  , 72, 69 , 41, 80 , 10, 83, 5  , 79, 53 , 95 , 21 , 6  , 17
                          );


  table_t rcf = nt2::cons<T>(nt2::of_size(4, 4),
                              1.000000000000000,  -0.068942029647742,   0.621675095640225,  -0.345859763083263,
                             -0.068942029647742,   1.000000000000000,  -0.098118015111609,   0.291206273219003,
                              0.621675095640225,  -0.098118015111609,   1.000000000000000,  -0.421351972589345,
                             -0.345859763083263,   0.291206273219003,  -0.421351972589345,   1.000000000000000
                            );


  NT2_DISPLAY(a);
  table_t cf;
  cf =  corrcoef(a);
  NT2_TEST_ULP_EQUAL(cf, rcf, 20);
  table_t rcf2 =   nt2::cons<T>(nt2::of_size(2, 2),
                                1.000000000000000,  -0.068942029647742,
                                -0.068942029647742,   1.000000000000000);


  cf =  corrcoef(a(_, 1), a(_, 2));
  NT2_TEST_ULP_EQUAL(cf, rcf2, 20);
  cf =  corrcoef(a, nt2::all_);
  NT2_TEST_ULP_EQUAL(cf, rcf, 20);
  cf =  corrcoef(a, nt2::complete_);
  NT2_TEST_ULP_EQUAL(cf, rcf, 20);

  cf =  corrcoef(a, nt2::pairwise_);
  NT2_TEST_ULP_EQUAL(cf, rcf, 20);
  a(1, 1) = nt2::Nan<T>();

  table_t rcf3 = nt2::cons<T>(nt2::of_size(4, 4),
                              1.000000000000000e+00,    -1.799895219745339e-02,     5.685763111100622e-01,    -2.412791002693299e-01,
                             -1.799895219745339e-02,     1.000000000000000e+00,    -9.811801511160850e-02,     2.912062732190031e-01,
                              5.685763111100622e-01,    -9.811801511160850e-02,     1.000000000000000e+00,    -4.213519725893449e-01,
                             -2.412791002693299e-01,     2.912062732190031e-01,    -4.213519725893449e-01,     1.000000000000000e+00);

  cf =  corrcoef(a, nt2::pairwise_);
  NT2_TEST_ULP_EQUAL(cf, rcf3, 20);
  NT2_DISPLAY(   corrcoef(a(_(2, nt2::end_), 1), a(_(2, nt2::end_), 4)));
  NT2_DISPLAY(   corrcoef(a(_(2, nt2::end_), 1), a(_(2, nt2::end_), 3)));
  NT2_DISPLAY(   corrcoef(a(_(2, nt2::end_), 1), a(_(2, nt2::end_), 2)));
}





