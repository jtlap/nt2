//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 linalg toolbox - tr_result solvers"

#include <nt2/table.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/functions/tril.hpp>
#include <nt2/include/functions/tr_solve.hpp>

#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>

NT2_TEST_CASE_TPL(tr_result, NT2_REAL_TYPES)
{
  typedef nt2::table<T> t_t;
  t_t a =     nt2::tril(  nt2::ones (4, 4, nt2::meta::as_<T>())
                          + T(10)*nt2::eye  (4, 4, nt2::meta::as_<T>()));
  t_t b = nt2::ones(4, 1, nt2::meta::as_<T>());
  nt2::display("a     ", a);
  nt2::display("b     ", b);
  nt2::details::tr_solve_result<t_t> f(a, b, 'L', 'N', 'N');

  nt2::display("x", f.x());
  NT2_DISPLAY(a);
}
