//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 linalg toolbox - lu factorization"

#include <nt2/table.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/functions/lu.hpp>

#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>

NT2_TEST_CASE_TPL(lu_factorization, NT2_REAL_TYPES)
{
  using nt2::tag::factorization::lu_;

  typedef typename nt2::meta::as_integer<T, signed>::type itype_t;
  typedef nt2::table<T> t_t;
  typedef nt2::table<itype_t> it_t;
  t_t b =       nt2::ones (4, 4, nt2::meta::as_<T>())
        + T(10)*nt2::eye  (4, 4, nt2::meta::as_<T>());

  typedef typename nt2::meta::call<lu_(t_t const&)>::type result_type;
  result_type res = nt2::factorization::lu(b);
  NT2_DISPLAY(b);
  NT2_DISPLAY(res.p());
  NT2_DISPLAY(res.l());
  NT2_DISPLAY(res.u());
  NT2_TEST_EQUAL(res.status(), 0);

  itype_t e;
  T m =  res.absdet(e);
  std::cout << "asbdet order " << e << std::endl;
  std::cout << "asbdet mant  " << m << std::endl;
  std::cout << "asbdet       " << nt2::ldexp(m, e) << std::endl;
  std::cout << "asbdet       " << res.absdet()<< std::endl;
  std::cout << "rank         " << res.rank()  << std::endl;
  std::cout << "signdet      " << res.signdet()<< std::endl;
  std::cout << "det          " << res.det()<< std::endl;
  t_t c =  nt2::ones (4, 1, nt2::meta::as_<T>());
  NT2_DISPLAY(c);
  t_t x = res.solve(c);
  NT2_DISPLAY(x);
}
