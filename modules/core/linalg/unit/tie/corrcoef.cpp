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



NT2_TEST_CASE_TPL ( corrcoef1, NT2_REAL_TYPES)
{
  typedef std::complex<T> cT;
  using nt2::corrcoef;
  using nt2::_;
  typedef nt2::table<T> table_t;
  typedef nt2::table<cT> ctable_t;
  table_t a = nt2::cons<T>(nt2::of_size(30, 4),
                           3, 54, 55, 32, 50, 26, 70, 7, 45, 1, 108, 40, 116, 28, 46, 16, 20, 15, 56, 98, 13, 66, 29, 104, 64, 96, 91, 115, 97, 99,
                           94, 51, 27, 30, 43, 109,  9, 112, 14, 62, 117, 92, 76, 101, 118, 37, 85, 23, 52, 67, 39, 82, 42, 8, 25, 44, 110, 31, 119, 103,
                           11, 100, 74, 107, 75, 60, 93, 73, 36, 35, 120, 77, 78, 24, 84, 61, 19, 88, 49, 18, 90, 111, 113, 22, 89, 68, 81, 59, 57, 65,
                           114, 58, 63, 4, 72, 69, 41, 80, 10, 83, 5, 79, 53, 95, 21, 6, 17, 87, 38, 33, 105, 12, 102, 71, 86, 47, 34, 48, 2, 106
                          );


  table_t rcf = nt2::cons<T>(nt2::of_size(4, 4),
                             1.000000000000000e+00,     2.134873961025726e-02,     1.059377538184698e-01,    -3.232965163767901e-01,
                             2.134873961025726e-02,     1.000000000000000e+00,    -5.260440206929290e-02,    -5.538026347477288e-02,
                             1.059377538184698e-01,    -5.260440206929290e-02,     1.000000000000000e+00,    -1.248692586044558e-01
                            );


  NT2_DISPLAY(a);
  table_t cf;
  cf =  corrcoef(a);
  NT2_TEST_ULP_EQUAL(cf, rcf, 10);
  table_t rcf2 =   nt2::cons<T>(nt2::of_size(2, 2),
                                1.000000000000000e+00,     2.134872600251597e-02,
                                2.134872600251597e-02,     1.000000000000000e+00);
  cf =  corrcoef(a(_, 1), a(_, 2));
}





