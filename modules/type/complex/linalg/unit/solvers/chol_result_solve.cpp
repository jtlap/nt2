//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 linalg toolbox - chol_result solvers"

#include <nt2/table.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/functions/chol_solve.hpp>
#include <nt2/include/functions/isulpequal.hpp>
#include <nt2/include/functions/mtimes.hpp>
#include <nt2/include/functions/ulpdist.hpp>
#include <nt2/include/functions/globalmax.hpp>

#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>


NT2_TEST_CASE_TPL(chol_resultc, NT2_REAL_TYPES)
{
  std::cout << std::setprecision(20); 
  typedef std::complex<T> cT;
  typedef nt2::table<cT> ct_t;
  ct_t a =       nt2::ones (4, 4, nt2::meta::as_<cT>())
        + T(10)*nt2::eye  (4, 4, nt2::meta::as_<cT>());
  ct_t b = nt2::ones(4, 1, nt2::meta::as_<cT>());
  ct_t aa = a;
  ct_t bb = b; 
  nt2::display("a     ", a);
  nt2::display("b     ", b);
  nt2::details::chol_solve_result<ct_t> f(a, b, 'L');

  nt2::display("x", f.x());
  NT2_DISPLAY(a);
  NT2_DISPLAY(b);
  NT2_DISPLAY(mtimes(aa, f.x()));
  std::cout << nt2::globalmax(nt2::ulpdist(bb, mtimes(aa, f.x()))) << std::endl; ; 
  NT2_TEST(nt2::isulpequal(bb, mtimes(aa, f.x())));   
}
