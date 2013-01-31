//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 linalg toolbox - lu_result factorization"

#include <nt2/table.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/functions/lu.hpp>
#include <nt2/include/functions/ldexp.hpp>
#include <nt2/include/functions/mtimes.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>

NT2_TEST_CASE_TPL(lu_result, NT2_REAL_TYPES)
{
  using nt2::_;
  using nt2::tag::factorization::lu_;
  typedef typename nt2::meta::as_integer<T, signed>::type itype_t;
  typedef nt2::table<T> t_t;
  typedef nt2::table<itype_t> it_t;
  t_t b =       nt2::ones (4, 4, nt2::meta::as_<T>())
        + T(10)*nt2::eye  (4, 4, nt2::meta::as_<T>());

  t_t z = b(3, _);
  b(3, _) =  b(2, _);
  b(2, _) = z;
  nt2::details::lu_result<t_t> f(b);

  nt2::display("b     ", b);
  nt2::display("values", f.values());
  t_t p = f.p();
  t_t l = f.l();
  t_t u = f.u();
  t_t pl= f.pl();
  it_t ip= f.ip();
  nt2::display("p    ", p);
  nt2::display("l    ", l);
  nt2::display("u    ", u);
  nt2::display("pl   ", pl);
  nt2::display("ip   ", ip);
  itype_t e;
  T m =  f.absdet(e);
  std::cout << "asbdet order " << e << std::endl;
  std::cout << "asbdet mant  " << m << std::endl;
  std::cout << "asbdet       " << nt2::ldexp(m, e) << std::endl;
  std::cout << "asbdet       " << f.absdet()<< std::endl;
  std::cout << "rank         " << f.rank()  << std::endl;
  std::cout << "signdet      " << f.signdet()<< std::endl;
  std::cout << "det          " << f.det()<< std::endl;
  NT2_TEST_ULP_EQUAL(nt2::mtimes(p, nt2::mtimes(l, u)), b, T(2));
 }
