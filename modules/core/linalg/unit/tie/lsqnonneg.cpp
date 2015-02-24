//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 linalg toolbox - tied lsqnonneg function"

#include <nt2/include/functions/lsqnonneg.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/functions/globalmax.hpp>
#include <nt2/include/constants/eps.hpp>
#include <nt2/include/functions/tie.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/include/functions/colon.hpp>
#include <nt2/table.hpp>


NT2_TEST_CASE_TPL ( lsqnonneg_no_1i, NT2_REAL_TYPES)
{
  using nt2::lsqnonneg;
  typedef nt2::table<T> table_t;
  table_t c = nt2::cons<T>(nt2::of_size(4, 2),
                      0.0372,    0.6861,    0.6233,    0.6344,
                      0.2869,    0.7071,    0.6245,    0.6170);
  table_t d =  nt2::cons<T>(nt2::of_size(4, 1),  0.8587,    0.1781,    0.0747,    0.8405);

  table_t x = nt2::lsqnonneg(c, d);
  table_t rx =  nt2::cons<T>(nt2::of_size(2, 1),0.0, 6.929343971302935e-01);
  std::size_t rexitflag = 1;
  std::size_t rnbiter = 1;
  table_t rlambda = nt2::cons<T>(nt2::of_size(2, 1), -1.506118191364654e-01, -1.387778780781446e-16);
  NT2_TEST_ULP_EQUAL(x, rx, 1.5);
  T resnorm;
  table_t residual, lambda;
  std::size_t exitflag, nbiter;

  nt2::tie(x, resnorm, residual, exitflag, nbiter, lambda) =  nt2::lsqnonneg(c, d);
  NT2_TEST_ULP_EQUAL(x, rx, 1.5);
  NT2_TEST_ULP_EQUAL(exitflag, rexitflag, 1);
  NT2_TEST_ULP_EQUAL(nbiter, rnbiter, 1);
  NT2_TEST_LESSER_EQUAL(nt2::globalmax(nt2::abs(lambda-rlambda)), 10*nt2::Eps<T>());
}


