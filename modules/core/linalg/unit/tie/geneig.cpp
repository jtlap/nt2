//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/table.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/functions/geneig.hpp>
#include <nt2/include/functions/transpose.hpp>
#include <nt2/include/functions/diag_of.hpp>
#include <nt2/include/functions/globalmax.hpp>
#include <nt2/include/functions/mtimes.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/constants/sqrt_2o_2.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <complex>
#include <nt2/table.hpp>
#include <nt2/linalg/options.hpp>

NT2_TEST_CASE_TPL(geneig_sca, NT2_REAL_TYPES)
{
  using nt2::geneig;
  typedef nt2::table<T> t_t;
  t_t w =   geneig(T(2), T(2));
  NT2_TEST_ULP_EQUAL(w, T(1), 0);
  w =   geneig(T(2),T(2), nt2::matrix_);
  NT2_TEST_ULP_EQUAL(w, T(1), 0);
  w =   geneig(T(2),T(2), nt2::vector_);
  NT2_TEST_ULP_EQUAL(w, T(1), 0);
 }

NT2_TEST_CASE_TPL(geneig, NT2_REAL_TYPES)
{
  using nt2::tag::geneig_;
  using nt2::mtimes;
  using nt2::_;
  typedef std::complex<T> cT;
  typedef nt2::table<T> t_t;
  typedef nt2::table<cT> ct_t;
  t_t a =  nt2::cons(nt2::of_size(2, 2), nt2::Sqrt_2o_2<T>(), T(0), T(0), T(1));
  t_t b =  nt2::cons(nt2::of_size(2, 2), T(0), -nt2::Sqrt_2o_2<T>(), T(1), T(0));
  ct_t w, wd, alpha;
  t_t beta;
  display("a", a);
  display("b", b);
  std::cout <<  "w = nt2::geneig(a, b);" << std::endl;
  w = nt2::geneig(a, b);
  display("w", w);
  std::cout <<  "wd = nt2::geneig(a, b, nt2::matrix_);"<< std::endl;
  wd = nt2::geneig(a, b, nt2::matrix_);
  display("wd", wd);
  std::cout <<  "tie(alpha, beta) = nt2::geneig(a, b, nt2::alphabeta_);"<< std::endl;
  tie(alpha, beta) = nt2::geneig(a, b, nt2::alphabeta_);
  display("alpha", alpha);
  display("beta", beta);
  NT2_TEST_ULP_EQUAL(w, alpha/beta, 2);

  std::cout <<  "tie(alpha, beta) = nt2::geneig(a, b, nt2::alphabeta_, nt2::vector_);"<< std::endl;
  tie(alpha, beta) = nt2::geneig(a, b, nt2::alphabeta_, nt2::vector_);
  display("alpha", alpha);
  display("beta", beta);
  NT2_TEST_ULP_EQUAL(w, alpha/beta, 2);

  std::cout <<  "tie(alpha, beta) = nt2::geneig(a, b, nt2::alphabeta_, nt2::matrix_);"<< std::endl;
  tie(alpha, beta) = nt2::geneig(a, b, nt2::alphabeta_, nt2::matrix_);
  display("alpha", alpha);
  display("beta", beta);
  NT2_TEST_ULP_EQUAL(w, nt2::diag_of(alpha)/nt2::diag_of(beta), 2);

  std::cout <<  "tie(vr, w1) = nt2::geneig(a, b, nt2::matrix_);"<< std::endl;
  ct_t w1, vr;
  tie(vr, w1) = nt2::geneig(a, b, nt2::matrix_);
  display("w1", w1);
  display("vr", vr);
  NT2_TEST_ULP_EQUAL(w1, wd, 2);
  NT2_TEST_LESSER(nt2::globalmax(nt2::abs(mtimes(a, vr)-mtimes(mtimes(b, vr), w1))), 0.001);

  ct_t vl;
  std::cout <<  "tie(vr, w1, vl) = nt2::geneig(a, b, nt2::matrix_);"<< std::endl;
  tie(vr, w1, vl) = nt2::geneig(a, b, nt2::matrix_);
  display("w1", w1);
  display("vr", vr);
  display("vl", vl);
  ct_t cvl =  ctrans(vl);
  NT2_TEST_ULP_EQUAL(w1, wd, 2);
  NT2_TEST_LESSER(nt2::globalmax(nt2::abs(mtimes(cvl, a)-mtimes(w1, mtimes(cvl, b)))), 0.001);


  std::cout <<  "tie(vr, alpha, beta, vl) = nt2::geneig(a, b, nt2::matrix_);"<< std::endl;
  tie(vr, alpha, beta, vl) = nt2::geneig(a, b, nt2::matrix_);
  display("alpha", alpha);
  display("beta", beta);
  display("vr", vr);
  display("vl", vl);
  NT2_TEST_LESSER(nt2::globalmax(nt2::abs(mtimes(mtimes(a, vr), beta)-mtimes(mtimes(b, vr), alpha))), 0.001);

}


NT2_TEST_CASE_TPL(geneig_sub, NT2_REAL_TYPES)
{
  using nt2::tag::geneig_;
  using nt2::mtimes;
  using nt2::_;
  using nt2::meta::as_;
  typedef std::complex<T> cT;
  typedef nt2::table<T> t_t;
  typedef nt2::table<cT> ct_t;
  t_t a =  nt2::cons(nt2::of_size(2, 2), nt2::Sqrt_2o_2<T>(), T(0), T(0), T(1));
  t_t b =  nt2::cons(nt2::of_size(2, 2), T(0), -nt2::Sqrt_2o_2<T>(), T(1), T(0));
  ct_t w = nt2::ones(nt2::of_size(4, 1), as_<T>())
    , wd = nt2::ones(nt2::of_size(4, 2), as_<T>())
    , alpha = nt2::ones(nt2::of_size(4, 1), as_<T>());
  t_t beta = nt2::ones(nt2::of_size(4, 1), as_<T>());
  display("a", a);
  display("b", b);
  std::cout <<  "w = nt2::geneig(a, b);" << std::endl;
  w(_(1, 2, 4))= nt2::geneig(a, b);
  display("w", w);
  std::cout <<  "wd = nt2::geneig(a, b, nt2::matrix_);"<< std::endl;
  wd(_(1, 2, 4), _) = nt2::geneig(a, b, nt2::matrix_);
  display("wd", wd);
  std::cout <<  "tie(alpha, beta) = nt2::geneig(a, b, nt2::alphabeta_);"<< std::endl;
  tie(alpha(_(1, 2, 4)), beta(_(1, 2, 4))) = nt2::geneig(a, b, nt2::alphabeta_);
  display("alpha", alpha);
  display("beta", beta);
  NT2_TEST_ULP_EQUAL(w(_(1, 2, 4)), alpha(_(1, 2, 4))/beta(_(1, 2, 4)), 2);

  std::cout <<  "tie(alpha, beta) = nt2::geneig(a, b, nt2::alphabeta_, nt2::vector_);"<< std::endl;
  tie(alpha(_(1, 2, 4)), beta(_(1, 2, 4))) = nt2::geneig(a, b, nt2::alphabeta_, nt2::vector_);
  display("alpha", alpha);
  display("beta", beta);
  NT2_TEST_ULP_EQUAL(w(_(1, 2, 4)), alpha(_(1, 2, 4))/beta(_(1, 2, 4)), 2);

  ct_t alphad = nt2::ones(nt2::of_size(4, 2), as_<T>());
  t_t betad = nt2::ones(nt2::of_size(4, 2), as_<T>());
  std::cout <<  "tie(alpha, beta) = nt2::geneig(a, b, nt2::alphabeta_, nt2::matrix_);"<< std::endl;
  tie(alphad(_(1, 2, 4), _), betad(_(1, 2, 4), _)) = nt2::geneig(a, b, nt2::alphabeta_, nt2::matrix_);
  display("alpha", alphad);
  display("beta", betad);
  NT2_TEST_ULP_EQUAL(nt2::diag_of(wd(_(1, 2, 4), _)), nt2::diag_of(alphad(_(1, 2, 4), _))/nt2::diag_of(betad(_(1, 2, 4), _)), 2);

  std::cout <<  "tie(vr, w1) = nt2::geneig(a, b, nt2::matrix_);"<< std::endl;
  ct_t w1 = nt2::ones(nt2::of_size(4, 2), as_<T>()), vr = nt2::ones(nt2::of_size(4, 2), as_<T>());
  tie(vr(_(1, 2, 4), _), w1(_(1, 2, 4), _)) = nt2::geneig(a, b, nt2::matrix_);
  display("w1", w1);
  display("vr", vr);
  NT2_TEST_ULP_EQUAL(w1, wd, 2);
  NT2_TEST_LESSER(nt2::globalmax(nt2::abs(mtimes(a, vr(_(1, 2, 4), _))-mtimes(mtimes(b, vr(_(1, 2, 4), _)), w1(_(1, 2, 4), _)))), 0.001);

  ct_t vl = nt2::ones(nt2::of_size(4, 2), as_<T>());
  std::cout <<  "tie(vr, w1, vl) = nt2::geneig(a, b, nt2::matrix_);"<< std::endl;
  tie(vr(_(1, 2, 4), _), w1(_(1, 2, 4), _), vl(_(1, 2, 4), _)) = nt2::geneig(a, b, nt2::matrix_);
  display("w1", w1);
  display("vr", vr);
  display("vl", vl);
  ct_t cvl =  ctrans(vl(_(1, 2, 4), _));
  NT2_TEST_ULP_EQUAL(w1, wd, 2);
  NT2_TEST_LESSER(nt2::globalmax(nt2::abs(mtimes(cvl, a)-mtimes(w1(_(1, 2, 4), _), mtimes(cvl, b)))), 0.001);


  std::cout <<  "tie(vr, alpha, beta, vl) = nt2::geneig(a, b, nt2::matrix_);"<< std::endl;
  tie(vr(_(1, 2, 4), _), alphad(_(1, 2, 4), _), betad(_(1, 2, 4), _), vl(_(1, 2, 4), _)) = nt2::geneig(a, b, nt2::matrix_);
  display("alphad", alphad);
  display("betad", betad);
  display("vr", vr);
  display("vl", vl);
  NT2_TEST_LESSER(nt2::globalmax(nt2::abs(mtimes(mtimes(a, vr(_(1, 2, 4), _)), betad(_(1, 2, 4), _))-mtimes(mtimes(b, vr(_(1, 2, 4), _)), alphad(_(1, 2, 4), _)))), 0.001);

}



