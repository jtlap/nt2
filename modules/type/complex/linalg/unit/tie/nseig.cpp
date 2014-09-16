//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/nseig.hpp>

#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/functions/colon.hpp>
#include <nt2/include/functions/from_diag.hpp>
#include <nt2/include/functions/nseig.hpp>
#include <nt2/include/constants/one.hpp>

#include <nt2/include/functions/transpose.hpp>
#include <nt2/include/functions/ctranspose.hpp>
#include <nt2/include/functions/mtimes.hpp>
#include <nt2/include/functions/globalmax.hpp>
#include <nt2/include/functions/real.hpp>
#include <nt2/include/functions/triu.hpp>

#include <nt2/table.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>
#include <nt2/linalg/options.hpp>


NT2_TEST_CASE_TPL(nseig_sca, NT2_REAL_TYPES)
{
  using nt2::nseig;
  typedef std::complex<T> cT;
   typedef nt2::table<cT> ct_t;
  ct_t w =   nseig(cT(2));
  NT2_TEST_ULP_EQUAL(w, cT(2), 0);
  w =   nseig(T(2), nt2::matrix_);
  NT2_TEST_ULP_EQUAL(w, cT(2), 0);
  w =   nseig(T(2), nt2::vector_);
  NT2_TEST_ULP_EQUAL(w, cT(2), 0);
 }


NT2_TEST_CASE_TPL(nseigc, NT2_REAL_TYPES)
{
  using nt2::nseig;
  using nt2::mtimes;
  using nt2::_;
  typedef std::complex<T> cT;
  typedef nt2::table<cT> ct_t;
  ct_t b =      nt2::triu(nt2::from_diag(nt2::_(T(1), T(4)))
                     + nt2::ones  (4, 4, nt2::meta::as_<T>()));
  //  b(_, 1) = b(_, 3);
  ct_t w, w1;

  w = nseig(b);
  ct_t cb = b;

  w1 = nseig(cb);
  NT2_TEST_ULP_EQUAL(w, w1, 2);
  w = nseig(b, nt2::matrix_);
  w1 = nseig(cb, nt2::matrix_);
  std::cout << "- 1 -" << std::endl;
  NT2_TEST_ULP_EQUAL(w, w1, 2);

  w = nseig(b, nt2::matrix_, nt2::balance_);
  w1 = nseig(cb, nt2::matrix_, nt2::balance_);
  std::cout << "- -1 -" << std::endl;
  NT2_TEST_ULP_EQUAL(w, w1, 2);

  ct_t v;
  nt2::tie(v, w) = nseig(b);
  std::cout << "- 0 -" << std::endl;
  NT2_TEST_ULP_EQUAL(mtimes( v, w), mtimes(cb, v), 8);

  nt2::tie(v, w) = nseig(cb);
  std::cout << "- 1 -" << std::endl;
  NT2_TEST_ULP_EQUAL(mtimes(v, w), mtimes(cb, v), 8);

  nt2::tie(v, w) = nseig(b, nt2::matrix_);
  std::cout << "- 2 -" << std::endl;
  NT2_TEST_ULP_EQUAL(mtimes( v, w), mtimes(cb, v), 8);

  nt2::tie(v, w) = nseig(cb, nt2::matrix_);
  std::cout << "- 3 -" << std::endl;
  NT2_TEST_ULP_EQUAL(mtimes(v, w), mtimes(cb, v), 8);

  nt2::tie(v, w) = nseig(b, nt2::vector_);
  std::cout << "- 4 -" << std::endl;
  NT2_TEST_ULP_EQUAL(mtimes( v, nt2::from_diag(w)), mtimes(cb, v), 8);

  nt2::tie(v, w) = nseig(cb, nt2::vector_);
  std::cout << "- 5 -" << std::endl;
  NT2_TEST_ULP_EQUAL(mtimes(v, nt2::from_diag(w)), mtimes(cb, v), 8);

  ct_t vl;

  nt2::tie(v, w, vl) = nseig(b);
  std::cout << "- 6 -" << std::endl;
  NT2_TEST_ULP_EQUAL(mtimes( v, w), mtimes(cb, v), 8);

  nt2::tie(v, w, vl) = nseig(cb);
  std::cout << "- 7 -" << std::endl;
  NT2_TEST_ULP_EQUAL(mtimes(v, w), mtimes(cb, v), 8);
  std::cout << "- 1 -" << std::endl;
  NT2_TEST_ULP_EQUAL(mtimes(vl, ctrans(w)), mtimes(ctrans(cb), vl), 8);

  nt2::tie(v, w, vl) = nseig(b, nt2::matrix_);
  std::cout << "- 8 -" << std::endl;
  NT2_TEST_ULP_EQUAL(mtimes( v, w), mtimes(cb, v), 8);
  std::cout << "- 9 -" << std::endl;
  NT2_TEST_ULP_EQUAL(mtimes(vl, ctrans(w)), mtimes(ctrans(cb), vl), 8);

  nt2::tie(v, w, vl) = nseig(cb, nt2::matrix_);
  std::cout << "- 10 -" << std::endl;
  NT2_TEST_ULP_EQUAL(mtimes(v, w), mtimes(cb, v), 8);
  std::cout << "- 11 -" << std::endl;
  NT2_TEST_ULP_EQUAL(mtimes(vl, ctrans(w)), mtimes(ctrans(cb), vl), 8);

  nt2::tie(v, w, vl) = nseig(b, nt2::vector_);
  std::cout << "- 12 -" << std::endl;
  NT2_TEST_ULP_EQUAL(mtimes( v, nt2::from_diag(w)), mtimes(cb, v), 8);
  std::cout << "- 13 -" << std::endl;
  NT2_TEST_ULP_EQUAL(mtimes(vl, ctrans(nt2::from_diag(w))), mtimes(ctrans(cb), vl), 8);

  nt2::tie(v, w, vl) = nseig(cb, nt2::vector_);
  std::cout << "- 14 -" << std::endl;
  NT2_TEST_ULP_EQUAL(mtimes(v, nt2::from_diag(w)), mtimes(cb, v), 8);
  std::cout << "- 15 -" << std::endl;
  NT2_TEST_ULP_EQUAL(mtimes(vl, ctrans(nt2::from_diag(w))), mtimes(ctrans(cb), vl), 8);

  nt2::tie(v, w) = nseig(cb, nt2::vector_, nt2::balance_);
  std::cout << "- 16 -" << std::endl;
  NT2_TEST_ULP_EQUAL(mtimes(v, nt2::from_diag(w)), mtimes(cb, v), 8);

  nt2::tie(v, w) = nseig(cb, nt2::matrix_, nt2::balance_);
  std::cout << "- 17 -" << std::endl;
  NT2_TEST_ULP_EQUAL(mtimes(v, w), mtimes(cb, v), 8);

  nt2::tie(v, w, vl) = nseig(cb, nt2::vector_, nt2::balance_);
  std::cout << "- 18 -" << std::endl;
  NT2_TEST_ULP_EQUAL(mtimes(v, nt2::from_diag(w)), mtimes(cb, v), 8);
  std::cout << "- 19 -" << std::endl;
  NT2_TEST_ULP_EQUAL(mtimes(vl, ctrans(nt2::from_diag(w))), mtimes(ctrans(cb), vl), 8);

  nt2::tie(v, w, vl) = nseig(cb, nt2::matrix_, nt2::balance_);
  std::cout << "- 20 -" << std::endl;
  NT2_TEST_ULP_EQUAL(mtimes(v, w), mtimes(cb, v), 8);
  std::cout << "- 21 -" << std::endl;
  NT2_TEST_ULP_EQUAL(mtimes(vl, ctrans(w)), mtimes(ctrans(cb), vl), 8);

  nt2::tie(v, w, vl) = nseig(cb);
  std::cout << "- 22-" << std::endl;
  NT2_TEST_ULP_EQUAL(mtimes(v, w), mtimes(cb, v), 8);
  std::cout << "- 23 -" << std::endl;
  NT2_TEST_ULP_EQUAL(mtimes(vl, ctrans(w)), mtimes(ctrans(cb), vl), 8);
}

