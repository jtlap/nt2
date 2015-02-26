//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/lscov.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/functions/globalmax.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/functions/size.hpp>
#include <nt2/include/constants/eps.hpp>
#include <nt2/include/functions/tie.hpp>
#include <nt2/include/functions/horzcat.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/include/functions/colon.hpp>
#include <nt2/table.hpp>


NT2_TEST_CASE_TPL ( lscov, NT2_REAL_TYPES)
{
  using nt2::lscov;
  typedef nt2::table<T> table_t;
  table_t x1 = nt2::cons<T>(nt2::of_size(6, 1), .2, .5, .6, .8, 1.0, 1.1);
  table_t x2 = nt2::cons<T>(nt2::of_size(6, 1), .1, .3, .4, .9, 1.1, 1.4);
  table_t x  = nt2::horzcat(nt2::horzcat(nt2::ones(nt2::size(x1), nt2::meta::as_<T>()), x1), x2);
  table_t y  = nt2::cons<T>(nt2::of_size(6, 1),.17, .26, .28, .23, .27, .34);
  table_t rb = nt2::cons<T>(nt2::of_size(3, 1), 1.203026427962488e-01, 3.283887468030698e-01, -1.312020460358062e-01);
  NT2_DISPLAY(x);
  NT2_DISPLAY(y);

  table_t b = nt2::lscov(x, y, nt2::ones(size(y), nt2::meta::as_<T>()));
  NT2_DISPLAY(b);
  NT2_DISPLAY(rb);
  NT2_TEST_ULP_EQUAL(b, rb, 10);
  b = nt2::lscov(x, y);
  NT2_DISPLAY(b);
  NT2_DISPLAY(rb);
  NT2_TEST_ULP_EQUAL(b, rb, 10);
  b = nt2::lscov(x, y);
  NT2_DISPLAY(b);
  NT2_DISPLAY(rb);
  NT2_TEST_ULP_EQUAL(b, rb, 10);
  b = nt2::lscov(x, y, nt2::eye(length(y), nt2::meta::as_<T>()));
  NT2_DISPLAY("0");
  table_t stdx, mse, s;
  tie(b, stdx) = nt2::lscov(x, y);
  NT2_DISPLAY(b);
  NT2_DISPLAY(stdx);
  NT2_DISPLAY("1");
  tie(b, stdx, mse) = nt2::lscov(x, y);
  NT2_DISPLAY(b);
  NT2_DISPLAY(stdx);
  NT2_DISPLAY(mse);
  NT2_DISPLAY("2");
  tie(b, stdx, mse, s) = nt2::lscov(x, y);
  NT2_DISPLAY(b);
  NT2_DISPLAY(stdx);
  NT2_DISPLAY(mse);
  NT2_DISPLAY(s);

//   T resnorm;
//   table_t residual, lambda;
//   std::size_t exitflag, nbiter;

//   nt2::tie(x, resnorm, residual, exitflag, nbiter, lambda) =  nt2::lscov(c, d);
//   NT2_TEST_ULP_EQUAL(x, rx, 1.5);
//   NT2_TEST_ULP_EQUAL(exitflag, rexitflag, 1);
//   NT2_TEST_ULP_EQUAL(nbiter, rnbiter, 1);
//   NT2_TEST_LESSER_EQUAL(nt2::globalmax(nt2::abs(lambda-rlambda)), 10*nt2::Eps<T>());
}


