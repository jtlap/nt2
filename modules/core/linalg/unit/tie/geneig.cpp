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
#include <nt2/include/functions/ctranspose.hpp>
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
  typedef std::complex<T> cT;
  typedef nt2::table<cT> ct_t;
  ct_t w =   geneig(T(2), T(2));
  NT2_TEST_ULP_EQUAL(w, cT(1), 0);
  w =   geneig(T(2),T(2), nt2::matrix_);
  NT2_TEST_ULP_EQUAL(w, cT(1), 0);
  w =   geneig(T(2),T(2), nt2::vector_);
  NT2_TEST_ULP_EQUAL(w, cT(1), 0);
}



NT2_TEST_CASE_TPL(geneig_1o_ni, NT2_REAL_TYPES)
{
  using nt2::tag::geneig_;
  using nt2::mtimes;
  using nt2::_;
  typedef std::complex<T> cT;
  typedef nt2::table<T> t_t;
  typedef nt2::table<cT> ct_t;
  t_t a =  nt2::cons(nt2::of_size(2, 2), nt2::Sqrt_2o_2<T>(), T(0), T(0), T(1));
  t_t b =  nt2::cons(nt2::of_size(2, 2), T(0), -nt2::Sqrt_2o_2<T>(), T(1), T(0));
  ct_t w, w1, wd;
  std::cout <<  "11 w = nt2::geneig(a, b);" << std::endl;
  w = nt2::geneig(a, b);

  std::cout <<  "12 w = nt2::geneig(a, b, nt2::vector_);" << std::endl;
  w1 = nt2::geneig(a, b, nt2::vector_);
  NT2_TEST_EQUAL(w, w1);

  std::cout <<  "13 wd = nt2::geneig(a, b, nt2::matrix_);"<< std::endl;
  wd = nt2::geneig(a, b, nt2::matrix_);
  NT2_TEST_EQUAL(w, nt2::diag_of(wd));
}


NT2_TEST_CASE_TPL(geneig_2o_ni, NT2_REAL_TYPES)
{
  using nt2::tag::geneig_;
  using nt2::mtimes;
  using nt2::_;
  typedef std::complex<T> cT;
  typedef nt2::table<T> t_t;
  typedef nt2::table<cT> ct_t;
  t_t a =  nt2::cons(nt2::of_size(2, 2), nt2::Sqrt_2o_2<T>(), T(0), T(0), T(1));
  t_t b =  nt2::cons(nt2::of_size(2, 2), T(0), -nt2::Sqrt_2o_2<T>(), T(1), T(0));
  ct_t w, dw, alpha, dalpha;
  t_t beta, dbeta, beta1;
  ct_t vr;

  std::cout <<  "21 nt2::tie(vr, dw) = nt2::geneig(a, b);"<< std::endl;
  nt2::tie(vr, dw) = nt2::geneig(a, b);
  NT2_TEST_LESSER(nt2::globalmax(nt2::abs(mtimes(a, vr)-mtimes(mtimes(b, vr), dw))), 0.001);

  std::cout <<  "22 nt2::tie(vr, dw) = nt2::geneig(a, b, matrix_);"<< std::endl;
  nt2::tie(vr, dw) = nt2::geneig(a, b, nt2::matrix_);
  NT2_TEST_LESSER(nt2::globalmax(nt2::abs(mtimes(a, vr)-mtimes(mtimes(b, vr), dw))), 0.001);

  std::cout <<  "23 nt2::tie(vr, w) = nt2::geneig(a, b, vector_);"<< std::endl;
  nt2::tie(vr, w) = nt2::geneig(a, b, nt2::vector_);
  NT2_TEST_EQUAL(nt2::diag_of(dw), w);
  NT2_TEST_LESSER(nt2::globalmax(nt2::abs(mtimes(a, vr)-mtimes(mtimes(b, vr), from_diag(w)))), 0.001);

  std::cout <<  "24 nt2::tie(alpha, beta) = nt2::geneig(a, b, nt2::alphabeta_);" << std::endl;
  nt2::tie(alpha, beta) = nt2::geneig(a, b, nt2::alphabeta_);
  NT2_TEST_EQUAL(alpha/beta, w);

  std::cout <<  "24 nt2::tie(alpha, beta) = nt2::geneig(a, b, nt2::alphabeta_, nt2::vector_);" << std::endl;
  nt2::tie(alpha, beta) = nt2::geneig(a, b, nt2::alphabeta_, nt2::vector_);
  NT2_TEST_EQUAL(alpha/beta, w);

  std::cout <<  "24 nt2::tie(alpha, beta) = nt2::geneig(a, b, nt2::alphabeta_, nt2::matrix_);" << std::endl;
  nt2::tie(alpha, beta) = nt2::geneig(a, b, nt2::alphabeta_, nt2::matrix_);
  NT2_TEST_EQUAL(nt2::diag_of(alpha)/nt2::diag_of(beta), w);

}

NT2_TEST_CASE_TPL(geneig_3o_ni, NT2_REAL_TYPES)
{
  using nt2::tag::geneig_;
  using nt2::mtimes;
  using nt2::_;
  typedef std::complex<T> cT;
  typedef nt2::table<T> t_t;
  typedef nt2::table<cT> ct_t;
  t_t a =  nt2::cons(nt2::of_size(2, 2), nt2::Sqrt_2o_2<T>(), T(0), T(0), T(1));
  t_t b =  nt2::cons(nt2::of_size(2, 2), T(0), -nt2::Sqrt_2o_2<T>(), T(1), T(0));
  ct_t w, dw, alpha, dalpha;
  t_t beta, dbeta, beta1;
  ct_t vr, vl, cvl;

  std::cout <<  "31 nt2::tie(vr, dw, vl) = nt2::geneig(a, b);"<< std::endl;
  nt2::tie(vr, dw, vl) = nt2::geneig(a, b);
  NT2_TEST_LESSER(nt2::globalmax(nt2::abs(mtimes(a, vr)-mtimes(mtimes(b, vr), dw))), 0.001);
  cvl =  ctrans(vl);
  NT2_TEST_LESSER(nt2::globalmax(nt2::abs(mtimes(cvl, a)-mtimes(dw, mtimes(cvl, b)))), 0.001);

  std::cout <<  "32 nt2::tie(vr, dw, vl) = nt2::geneig(a, b, matrix_);"<< std::endl;
  nt2::tie(vr, dw, vl) = nt2::geneig(a, b, nt2::matrix_);
  NT2_TEST_LESSER(nt2::globalmax(nt2::abs(mtimes(a, vr)-mtimes(mtimes(b, vr), dw))), 0.001);
  cvl =  ctrans(vl);
  NT2_TEST_LESSER(nt2::globalmax(nt2::abs(mtimes(cvl, a)-mtimes(dw, mtimes(cvl, b)))), 0.001);

  std::cout <<  "33 nt2::tie(vr, w, vl) = nt2::geneig(a, b, vector_);"<< std::endl;
  nt2::tie(vr, w, vl) = nt2::geneig(a, b, nt2::vector_);
  NT2_TEST_EQUAL(nt2::diag_of(dw), w);
  NT2_TEST_LESSER(nt2::globalmax(nt2::abs(mtimes(a, vr)-mtimes(mtimes(b, vr), from_diag(w)))), 0.001);
  cvl =  ctrans(vl);
  NT2_TEST_LESSER(nt2::globalmax(nt2::abs(mtimes(cvl, a)-mtimes(nt2::from_diag(w), mtimes(cvl, b)))), 0.001);

  std::cout <<  "34 nt2::tie(vr, dalpha, dbeta) = nt2::geneig(a, b, nt2::alphabeta_);" << std::endl;
  nt2::tie(vr, dalpha, dbeta) = nt2::geneig(a, b, nt2::alphabeta_);
  NT2_TEST_EQUAL(nt2::diag_of(dalpha)/nt2::diag_of(dbeta), w);
  NT2_TEST_LESSER(nt2::globalmax(nt2::abs(mtimes(mtimes(a, vr), dbeta)-mtimes(mtimes(b, vr), dalpha))), 0.001);

  std::cout <<  "35 nt2::tie(vr, dalpha, dbeta) = nt2::geneig(a, b, nt2::alphabeta_, nt2::matrix_);" << std::endl;
  nt2::tie(vr, dalpha, dbeta) = nt2::geneig(a, b, nt2::alphabeta_, nt2::matrix_);
  NT2_TEST_EQUAL(nt2::diag_of(dalpha)/nt2::diag_of(dbeta), w);
  NT2_TEST_LESSER(nt2::globalmax(nt2::abs(mtimes(mtimes(a, vr), dbeta)-mtimes(mtimes(b, vr), dalpha))), 0.001);

  std::cout <<  "36 nt2::tie(vr, alpha, beta) = nt2::geneig(a, b, nt2::alphabeta_, nt2::vector_);" << std::endl;
  nt2::tie(vr, alpha, beta) = nt2::geneig(a, b, nt2::alphabeta_, nt2::vector_);
  NT2_TEST_EQUAL(alpha/beta, w);
  NT2_TEST_LESSER(nt2::globalmax(nt2::abs(mtimes(mtimes(a, vr), nt2::from_diag(beta))-mtimes(mtimes(b, vr), nt2::from_diag(alpha)))), 0.001);
}

NT2_TEST_CASE_TPL(geneig_4o_ni, NT2_REAL_TYPES)
{
  using nt2::tag::geneig_;
  using nt2::mtimes;
  using nt2::_;
  typedef std::complex<T> cT;
  typedef nt2::table<T> t_t;
  typedef nt2::table<cT> ct_t;
  t_t a =  nt2::cons(nt2::of_size(2, 2), nt2::Sqrt_2o_2<T>(), T(0), T(0), T(1));
  t_t b =  nt2::cons(nt2::of_size(2, 2), T(0), -nt2::Sqrt_2o_2<T>(), T(1), T(0));
  ct_t w, dw, alpha, dalpha;
  t_t beta, dbeta, beta1;
  ct_t vr, vl, cvl;

  std::cout <<  "41 nt2::tie(vr, dalpha, dbeta, vl) = nt2::geneig(a, b);"<< std::endl;
  nt2::tie(vr, dalpha, dbeta, vl) = nt2::geneig(a, b);
  NT2_TEST_LESSER(nt2::globalmax(nt2::abs(mtimes(mtimes(a, vr), dbeta)-mtimes(mtimes(b, vr), dalpha))), 0.001);
  cvl =  ctrans(vl);
  NT2_TEST_LESSER(nt2::globalmax(nt2::abs(mtimes(dbeta,mtimes(cvl, a))-mtimes(dalpha, mtimes(cvl, b)))), 0.001);

  std::cout <<  "42 nt2::tie(vr, dalpha, dbeta, vl) = nt2::geneig(a, b, nt2::matrix_);"<< std::endl;
  nt2::tie(vr, dalpha, dbeta, vl) = nt2::geneig(a, b);
  NT2_TEST_LESSER(nt2::globalmax(nt2::abs(mtimes(mtimes(a, vr), dbeta)-mtimes(mtimes(b, vr), dalpha))), 0.001);
  cvl =  ctrans(vl);
  NT2_TEST_LESSER(nt2::globalmax(nt2::abs(mtimes(dbeta,mtimes(cvl, a))-mtimes(dalpha, mtimes(cvl, b)))), 0.001);

  std::cout <<  "43 nt2::tie(vr, alpha, beta, vl) = nt2::geneig(a, b, nt2::vector_);"<< std::endl;
  nt2::tie(vr, alpha, beta, vl) = nt2::geneig(a, b, nt2::vector_);
  NT2_TEST_LESSER(nt2::globalmax(nt2::abs(mtimes(mtimes(a, vr), nt2::from_diag(beta))-mtimes(mtimes(b, vr), nt2::from_diag(alpha)))), 0.001);
  cvl =  ctrans(vl);
  NT2_TEST_LESSER(nt2::globalmax(nt2::abs(mtimes(nt2::from_diag(beta),mtimes(cvl, a))-mtimes(nt2::from_diag(alpha), mtimes(cvl, b)))), 0.001);
}


NT2_TEST_CASE_TPL(geneig_1o_ni_sub, NT2_REAL_TYPES)
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
  ct_t w, w1, wd;
  w = w1 = nt2::ones(4, 1, as_<T>());
  wd = nt2::ones(4, 2, as_<T>());

  std::cout <<  "sub 11 w = nt2::geneig(a, b);" << std::endl;
  w(_(1, 2, 4))= nt2::geneig(a, b);

  std::cout <<  "sub 12 w = nt2::geneig(a, b, nt2::vector_);" << std::endl;
  w1(_(1, 2, 4)) = nt2::geneig(a, b, nt2::vector_);
  NT2_TEST_EQUAL(w(_(1, 2, 4)), w1(_(1, 2, 4)));

  std::cout <<  "sub 13 wd = nt2::geneig(a, b, nt2::matrix_);"<< std::endl;
  wd(_(1, 2, 4), _) = nt2::geneig(a, b, nt2::matrix_);
  NT2_TEST_EQUAL(w(_(1, 2, 4)), nt2::diag_of(wd(_(1, 2, 4), _)));
}


NT2_TEST_CASE_TPL(geneig_2o_ni_sub, NT2_REAL_TYPES)
{
  using nt2::tag::geneig_;
  using nt2::mtimes;
  using nt2::meta::as_;
  using nt2::_;
  typedef std::complex<T> cT;
  typedef nt2::table<T> t_t;
  typedef nt2::table<cT> ct_t;
  t_t a =  nt2::cons(nt2::of_size(2, 2), nt2::Sqrt_2o_2<T>(), T(0), T(0), T(1));
  t_t b =  nt2::cons(nt2::of_size(2, 2), T(0), -nt2::Sqrt_2o_2<T>(), T(1), T(0));
  ct_t w, dw, alpha, dalpha;
  t_t beta, dbeta, beta1;
  ct_t vr;
  beta =  nt2::ones(4, 1, as_<T>());
  alpha = w = nt2::ones(4, 1, as_<T>());
  dw = nt2::ones(4, 2, as_<T>());
  dalpha = vr = nt2::ones(4, 2, as_<T>());
  dbeta = nt2::ones(4, 2, as_<T>());

  std::cout <<  "sub 21 nt2::tie(vr(_(1, 2, 4), _)), dw(_(1, 2, 4), _))) = nt2::geneig(a, b);"<< std::endl;
  nt2::tie(vr(_(1, 2, 4), _), dw(_(1, 2, 4), _)) = nt2::geneig(a, b);
  NT2_TEST_LESSER(nt2::globalmax(nt2::abs(mtimes(a, vr(_(1, 2, 4), _))-mtimes(mtimes(b, vr(_(1, 2, 4), _)), dw(_(1, 2, 4), _)))), 0.001);

  std::cout <<  "sub 22 nt2::tie(vr(_(1, 2, 4), _)), dw(_(1, 2, 4), _))) = nt2::geneig(a, b, matrix_);"<< std::endl;
  nt2::tie(vr(_(1, 2, 4), _), dw(_(1, 2, 4), _)) = nt2::geneig(a, b, nt2::matrix_);
  NT2_TEST_LESSER(nt2::globalmax(nt2::abs(mtimes(a, vr(_(1, 2, 4), _))-mtimes(mtimes(b, vr(_(1, 2, 4), _)), dw(_(1, 2, 4), _)))), 0.001);

  std::cout <<  "sub 23 nt2::tie(vr(_(1, 2, 4), _)), w(_(1, 2, 4)))) = nt2::geneig(a, b, vector_);"<< std::endl;
  nt2::tie(vr(_(1, 2, 4), _), w(_(1, 2, 4))) = nt2::geneig(a, b, nt2::vector_);
  NT2_TEST_EQUAL(nt2::diag_of(dw(_(1, 2, 4), _)), w(_(1, 2, 4)));
  NT2_TEST_LESSER(nt2::globalmax(nt2::abs(mtimes(a, vr(_(1, 2, 4), _))-mtimes(mtimes(b, vr(_(1, 2, 4), _)), from_diag(w(_(1, 2, 4)))))), 0.001);

  std::cout <<  "sub 24 nt2::tie(alpha, beta) = nt2::geneig(a, b, nt2::alphabeta_);" << std::endl;
  nt2::tie(alpha(_(1, 2, 4)), beta(_(1, 2, 4))) = nt2::geneig(a, b, nt2::alphabeta_);
  NT2_TEST_EQUAL(alpha(_(1, 2, 4))/beta(_(1, 2, 4)), w(_(1, 2, 4)));

  std::cout <<  "sub 25 nt2::tie(alpha, beta) = nt2::geneig(a, b, nt2::alphabeta_, nt2::vector_);" << std::endl;
  nt2::tie(alpha(_(1, 2, 4)), beta(_(1, 2, 4))) = nt2::geneig(a, b, nt2::alphabeta_, nt2::vector_);
  NT2_TEST_EQUAL(alpha(_(1, 2, 4))/beta(_(1, 2, 4)), w(_(1, 2, 4)));

  std::cout <<  "sub 26 nt2::tie(dalpha, dbeta) = nt2::geneig(a, b, nt2::alphabeta_, nt2::matrix_);" << std::endl;
  nt2::tie(dalpha(_(1, 2, 4), _), dbeta(_(1, 2, 4), _)) = nt2::geneig(a, b, nt2::alphabeta_, nt2::matrix_);
  NT2_TEST_EQUAL(nt2::diag_of(dalpha(_(1, 2, 4), _))/nt2::diag_of(dbeta(_(1, 2, 4), _)), w(_(1, 2, 4)));
}

NT2_TEST_CASE_TPL(geneig_3o_ni_sub, NT2_REAL_TYPES)
{
  using nt2::tag::geneig_;
  using nt2::mtimes;
  using nt2::meta::as_;
  using nt2::_;
  typedef std::complex<T> cT;
  typedef nt2::table<T> t_t;
  typedef nt2::table<cT> ct_t;
  t_t a =  nt2::cons(nt2::of_size(2, 2), nt2::Sqrt_2o_2<T>(), T(0), T(0), T(1));
  t_t b =  nt2::cons(nt2::of_size(2, 2), T(0), -nt2::Sqrt_2o_2<T>(), T(1), T(0));
  ct_t w, dw, alpha, dalpha;
  t_t beta, dbeta, beta1;
  ct_t vr, vl, cvl;
  beta =  nt2::ones(4, 1, as_<T>());
  alpha = w = nt2::ones(4, 1, as_<T>());
  dw = nt2::ones(4, 2, as_<T>());
  dalpha = vr = vl = nt2::ones(4, 2, as_<T>());
  dbeta = nt2::ones(4, 2, as_<T>());

  std::cout <<  "31 nt2::tie(vr(_(1, 2, 4), _), dw(_(1, 2, 4), _), vl(_(1, 2, 4), _)) = nt2::geneig(a, b);"<< std::endl;
  nt2::tie(vr(_(1, 2, 4), _), dw(_(1, 2, 4), _), vl(_(1, 2, 4), _)) = nt2::geneig(a, b);
  NT2_TEST_LESSER(nt2::globalmax(nt2::abs(mtimes(a, vr(_(1, 2, 4), _))-mtimes(mtimes(b, vr(_(1, 2, 4), _)), dw(_(1, 2, 4), _)))), 0.001);
  cvl =  ctrans(vl(_(1, 2, 4), _));
  NT2_TEST_LESSER(nt2::globalmax(nt2::abs(mtimes(cvl, a)-mtimes(dw(_(1, 2, 4), _), mtimes(cvl, b)))), 0.001);

  std::cout <<  "32 nt2::tie(vr(_(1, 2, 4), _), dw(_(1, 2, 4), _), vl(_(1, 2, 4), _)) = nt2::geneig(a, b, matrix_);"<< std::endl;
  nt2::tie(vr(_(1, 2, 4), _), dw(_(1, 2, 4), _), vl(_(1, 2, 4), _)) = nt2::geneig(a, b, nt2::matrix_);
  NT2_TEST_LESSER(nt2::globalmax(nt2::abs(mtimes(a, vr(_(1, 2, 4), _))-mtimes(mtimes(b, vr(_(1, 2, 4), _)), dw(_(1, 2, 4), _)))), 0.001);
  cvl =  ctrans(vl(_(1, 2, 4), _));
  NT2_TEST_LESSER(nt2::globalmax(nt2::abs(mtimes(cvl, a)-mtimes(dw(_(1, 2, 4), _), mtimes(cvl, b)))), 0.001);

  std::cout <<  "33 nt2::tie(vr(_(1, 2, 4), _), w, vl(_(1, 2, 4), _)) = nt2::geneig(a, b, vector_);"<< std::endl;
  nt2::tie(vr(_(1, 2, 4), _), w, vl(_(1, 2, 4), _)) = nt2::geneig(a, b, nt2::vector_);
  NT2_TEST_EQUAL(nt2::diag_of(dw(_(1, 2, 4), _)), w);
  NT2_TEST_LESSER(nt2::globalmax(nt2::abs(mtimes(a, vr(_(1, 2, 4), _))-mtimes(mtimes(b, vr(_(1, 2, 4), _)), from_diag(w)))), 0.001);
  cvl =  ctrans(vl(_(1, 2, 4), _));
  NT2_TEST_LESSER(nt2::globalmax(nt2::abs(mtimes(cvl, a)-mtimes(nt2::from_diag(w), mtimes(cvl, b)))), 0.001);

  std::cout <<  "34 nt2::tie(vr(_(1, 2, 4), _), dalpha(_(1, 2, 4), _), dbeta(_(1, 2, 4), _)) = nt2::geneig(a, b, nt2::alphabeta_);" << std::endl;
  nt2::tie(vr(_(1, 2, 4), _), dalpha(_(1, 2, 4), _), dbeta(_(1, 2, 4), _)) = nt2::geneig(a, b, nt2::alphabeta_);
  NT2_TEST_EQUAL(nt2::diag_of(dalpha(_(1, 2, 4), _))/nt2::diag_of(dbeta(_(1, 2, 4), _)), w);
  NT2_TEST_LESSER(nt2::globalmax(nt2::abs(mtimes(mtimes(a, vr(_(1, 2, 4), _)), dbeta(_(1, 2, 4), _))-mtimes(mtimes(b, vr(_(1, 2, 4), _)), dalpha(_(1, 2, 4), _)))), 0.001);

  std::cout <<  "35 nt2::tie(vr(_(1, 2, 4), _), dalpha(_(1, 2, 4), _), dbeta(_(1, 2, 4), _)) = nt2::geneig(a, b, nt2::alphabeta_, nt2::matrix_);" << std::endl;
  nt2::tie(vr(_(1, 2, 4), _), dalpha(_(1, 2, 4), _), dbeta(_(1, 2, 4), _)) = nt2::geneig(a, b, nt2::alphabeta_, nt2::matrix_);
  NT2_TEST_EQUAL(nt2::diag_of(dalpha(_(1, 2, 4), _))/nt2::diag_of(dbeta(_(1, 2, 4), _)), nt2::diag_of(dw(_(1, 2, 4), _)));
  NT2_TEST_LESSER(nt2::globalmax(nt2::abs(mtimes(mtimes(a, vr(_(1, 2, 4), _)), dbeta(_(1, 2, 4), _))-mtimes(mtimes(b, vr(_(1, 2, 4), _)), dalpha(_(1, 2, 4), _)))), 0.001);

  std::cout <<  "36 nt2::tie(vr(_(1, 2, 4), _), alpha(_(1, 2, 4)), beta(_(1, 2, 4))) = nt2::geneig(a, b, nt2::alphabeta_, nt2::vector_);" << std::endl;
  nt2::tie(vr(_(1, 2, 4), _), alpha(_(1, 2, 4)), beta(_(1, 2, 4))) = nt2::geneig(a, b, nt2::alphabeta_, nt2::vector_);
  NT2_TEST_EQUAL(alpha(_(1, 2, 4))/beta(_(1, 2, 4)), nt2::diag_of(dw(_(1, 2, 4), _)));
  NT2_TEST_LESSER(nt2::globalmax(nt2::abs(mtimes(mtimes(a, vr(_(1, 2, 4), _)), nt2::from_diag(beta(_(1, 2, 4))))-mtimes(mtimes(b, vr(_(1, 2, 4), _)), nt2::from_diag(alpha(_(1, 2, 4)))))), 0.001);
}

NT2_TEST_CASE_TPL(geneig_4o_ni_sub, NT2_REAL_TYPES)
{
  using nt2::tag::geneig_;
  using nt2::mtimes;
  using nt2::meta::as_;
  using nt2::_;
  typedef std::complex<T> cT;
  typedef nt2::table<T> t_t;
  typedef nt2::table<cT> ct_t;
  t_t a =  nt2::cons(nt2::of_size(2, 2), nt2::Sqrt_2o_2<T>(), T(0), T(0), T(1));
  t_t b =  nt2::cons(nt2::of_size(2, 2), T(0), -nt2::Sqrt_2o_2<T>(), T(1), T(0));
  ct_t w, dw, alpha, dalpha;
  t_t beta, dbeta, beta1;
  ct_t vr, vl, cvl;
  beta =  nt2::ones(4, 1, as_<T>());
  alpha = w = nt2::ones(4, 1, as_<T>());
  dw = nt2::ones(4, 2, as_<T>());
  dalpha = vr = vl = nt2::ones(4, 2, as_<T>());
  dbeta = nt2::ones(4, 2, as_<T>());

  std::cout <<  "41 nt2::tie(vr(_(1, 2, 4), _), dalpha(_(1, 2, 4), _), dbeta(_(1, 2, 4), _), vl(_(1, 2, 4), _)) = nt2::geneig(a, b);"<< std::endl;
  nt2::tie(vr(_(1, 2, 4), _), dalpha(_(1, 2, 4), _), dbeta(_(1, 2, 4), _), vl(_(1, 2, 4), _)) = nt2::geneig(a, b);
  NT2_TEST_LESSER(nt2::globalmax(nt2::abs(mtimes(mtimes(a, vr(_(1, 2, 4), _)), dbeta(_(1, 2, 4), _))-mtimes(mtimes(b, vr(_(1, 2, 4), _)), dalpha(_(1, 2, 4), _)))), 0.001);
  cvl =  ctrans(vl(_(1, 2, 4), _));
  NT2_TEST_LESSER(nt2::globalmax(nt2::abs(mtimes(dbeta(_(1, 2, 4), _),mtimes(cvl, a))-mtimes(dalpha(_(1, 2, 4), _), mtimes(cvl, b)))), 0.001);

  std::cout <<  "42 nt2::tie(vr(_(1, 2, 4), _), dalpha(_(1, 2, 4), _), dbeta(_(1, 2, 4), _), vl(_(1, 2, 4), _)) = nt2::geneig(a, b, nt2::matrix_);"<< std::endl;
  nt2::tie(vr(_(1, 2, 4), _), dalpha(_(1, 2, 4), _), dbeta(_(1, 2, 4), _), vl(_(1, 2, 4), _)) = nt2::geneig(a, b);
  NT2_TEST_LESSER(nt2::globalmax(nt2::abs(mtimes(mtimes(a, vr(_(1, 2, 4), _)), dbeta(_(1, 2, 4), _))-mtimes(mtimes(b, vr(_(1, 2, 4), _)), dalpha(_(1, 2, 4), _)))), 0.001);
  cvl =  ctrans(vl(_(1, 2, 4), _));
  NT2_TEST_LESSER(nt2::globalmax(nt2::abs(mtimes(dbeta(_(1, 2, 4), _),mtimes(cvl, a))-mtimes(dalpha(_(1, 2, 4), _), mtimes(cvl, b)))), 0.001);

  std::cout <<  "43 nt2::tie(vr(_(1, 2, 4), _), alpha, beta, vl(_(1, 2, 4), _)) = nt2::geneig(a, b, nt2::vector_);"<< std::endl;
  nt2::tie(vr(_(1, 2, 4), _), alpha, beta, vl(_(1, 2, 4), _)) = nt2::geneig(a, b, nt2::vector_);
  NT2_TEST_LESSER(nt2::globalmax(nt2::abs(mtimes(mtimes(a, vr(_(1, 2, 4), _)), nt2::from_diag(beta))-mtimes(mtimes(b, vr(_(1, 2, 4), _)), nt2::from_diag(alpha)))), 0.001);
  cvl =  ctrans(vl(_(1, 2, 4), _));
  NT2_TEST_LESSER(nt2::globalmax(nt2::abs(mtimes(nt2::from_diag(beta),mtimes(cvl, a))-mtimes(nt2::from_diag(alpha), mtimes(cvl, b)))), 0.001);
}
