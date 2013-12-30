//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================

#include <nt2/table.hpp>
#include <nt2/sdk/complex/complex.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/functions/svd.hpp>
#include <nt2/include/functions/mtimes.hpp>
#include <nt2/include/functions/complexify.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>

NT2_TEST_CASE_TPL(svd_resultc, NT2_REAL_TYPES)
{
  using nt2::_;
  using nt2::tag::factorization::svd_;
  typedef typename nt2::meta::as_integer<T, signed>::type itype_t;
  typedef std::complex<T> cT;
  typedef nt2::table<T> t_t;
  typedef nt2::table<cT> ct_t;
  ct_t b =       nt2::ones (4, 4, nt2::meta::as_<cT>())
        + T(10)*nt2::eye  (4, 4, nt2::meta::as_<cT>());
  b(_, 1) = b(_, 3);
  nt2::display("b bis     ", b);
  for(size_t i=1; i <= 4; i++) b(i, 1) = b(i, 3);
  nt2::display("b ter     ", b);
  ct_t bb = b;
  nt2::details::svd_result<ct_t> f(b,'A','A');

   nt2::display("b     ", b);
   nt2::display("values", f.values());
   ct_t u  = f.u();
   nt2::display("u    ", u);
   ct_t vt = f.vt();
   nt2::display("vt    ", vt);
   t_t w  = f.w();
   nt2::display("w    ", w);
   ct_t cw = nt2::complexify(w);
   NT2_DISPLAY(cw);

   NT2_TEST_ULP_EQUAL(nt2::mtimes(u, nt2::mtimes(cw, vt)), bb, 16.5);
   t_t sg = f.singular();
   nt2::display("sg   ", sg);
   ct_t nul = f.null();
   nt2::display("null   ", nul);
   ct_t zer = f.zerosolve();
   nt2::display("zer    ", zer);
   T condition =  f.cond();
   std::cout << "cond " << condition << std::endl;
   T norm =  f.norm();
   std::cout << "norm " << norm << std::endl;
   T norminv =  f.norminv();
   std::cout << "norminv " << norminv << std::endl;
   std::cout << "rank         " << f.rank()  << std::endl;
   ct_t ort = f.orth();
   nt2::display("orth ", ort);
   std::cout << nt2::details::svd_result<ct_t>(b,'N','N').norm() << std::endl;
}
