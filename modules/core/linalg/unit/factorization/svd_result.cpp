//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 linalg toolbox - svd_result factorization"

#include <nt2/table.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/functions/svd.hpp>
#include <nt2/include/functions/ldexp.hpp>
#include <nt2/include/functions/repnum.hpp>
#include <nt2/include/functions/mtimes.hpp>
#include <nt2/include/functions/isulpequal.hpp>
#include <nt2/include/functions/globalmax.hpp>
#include <nt2/include/functions/ulpdist.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>

NT2_TEST_CASE_TPL(svd_result, NT2_REAL_TYPES)
{
  using nt2::_;
  using nt2::tag::factorization::svd_;
  typedef typename nt2::meta::as_integer<T, signed>::type itype_t;
  typedef nt2::table<T> t_t;
  typedef nt2::table<itype_t> it_t;
  t_t b =       nt2::ones (4, 4, nt2::meta::as_<T>())
        + T(10)*nt2::eye  (4, 4, nt2::meta::as_<T>());
  b(_, 1) = b(_, 3);
  NT2_DISPLAY(b);
  nt2::display("b bis     ", b);
  for(size_t i=1; i <= 4; i++) b(i, 1) = b(i, 3);
  nt2::display("b ter     ", b);
  t_t bb = b;

  nt2::details::svd_result<t_t> f(b,'A','A');

  nt2::display("b bis     ", b);
  nt2::display("values", f.values());
  t_t u  = f.u();
  nt2::display("u    ", u);
  t_t vt = f.vt();
  nt2::display("vt    ", vt);
  t_t w  = f.w();
  nt2::display("w    ", w);
  NT2_TEST(nt2::isulpequal(nt2::mtimes(u, nt2::mtimes(w, vt)), bb, T(16.0)));
  std::cout << nt2::globalmax(nt2::ulpdist(nt2::mtimes(u, nt2::mtimes(w, vt)), b)) << std::endl;
  t_t sg = f.singular();
  nt2::display("sg   ", sg);
  t_t nul = f.null();
  nt2::display("null   ", nul);
  t_t zer = f.zerosolve();
  nt2::display("zer    ", zer);
  T condition =  f.cond();
  std::cout << "cond " << condition << std::endl;
  T norm =  f.norm();
  std::cout << "norm " << norm << std::endl;
  T norminv =  f.norminv();
  std::cout << "norminv " << norminv << std::endl;
  std::cout << "rank         " << f.rank()  << std::endl;
  t_t ort = f.orth();
  nt2::display("orth ", ort);
  std::cout << nt2::details::svd_result<t_t>(b,'N','N').norm() << std::endl;
}
