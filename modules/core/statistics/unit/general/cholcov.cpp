//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/cholcov.hpp>
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
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/include/functions/colon.hpp>
#include <nt2/include/functions/rand.hpp>
#include <nt2/include/functions/reshape.hpp>
#include <nt2/table.hpp>

NT2_TEST_CASE_TPL ( cholcov1, NT2_REAL_TYPES)
{
  typedef std::complex<T> cT;
  using nt2::cholcov;
  typedef nt2::table<T> table_t;
  typedef nt2::table<cT> ctable_t;
  table_t a = nt2::cons<T>(nt2::of_size(4, 4),
                      276,   304,   332,   360,
                      304,   336,   368,   400,
                      332,   368,   404,   440,
                      360,   400,   440,   480);



  table_t rt = nt2::cons<T>(nt2::of_size(2, 4),
                            1.488563522579013e+00,     1.654642495040083e+01,
                            5.671444314291980e-01,     1.832152687943607e+01,
                            -3.542746597205766e-01,     2.009662880847131e+01,
                            -1.275693750870463e+00,     2.187173073750658e+01);
  table_t t;
  int p;
  t =  cholcov(a, nt2::definite_);
  tie(t, p)=  cholcov(a, nt2::definite_);
  NT2_TEST(p!=0);
  NT2_TEST(isempty(t));
  t =  cholcov(a, nt2::semidefinite_);
  tie(t, p)=  cholcov(a, nt2::semidefinite_);
  NT2_TEST(p == 0);
  NT2_TEST_ULP_EQUAL(t, rt, 500);


 }




