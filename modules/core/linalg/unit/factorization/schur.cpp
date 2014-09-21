//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 linalg toolbox - schur factorization"

#include <nt2/include/functions/schur.hpp>
#include <nt2/table.hpp>
#include <nt2/include/functions/diag_of.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/functions/transpose.hpp>
#include <nt2/include/functions/ctranspose.hpp>
#include <nt2/include/functions/mtimes.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <complex>
#include <nt2/linalg/options.hpp>

template < class T > nt2::table<T> bmat()
{
  return  nt2::cons(nt2::of_size(4, 4),
                     T(9.648885351992765e-01),     T(4.853756487228412e-01),     T(9.157355251890671e-01),     T(3.571167857418955e-02),
                     T(1.576130816775483e-01),     T(8.002804688888001e-01),     T(7.922073295595544e-01),     T(8.491293058687771e-01),
                     T(9.705927817606157e-01),     T(1.418863386272153e-01),     T(9.594924263929030e-01),     T(9.339932477575505e-01),
                     T(9.571669482429456e-01),     T(4.217612826262750e-01),     T(6.557406991565868e-01),     T(6.787351548577735e-01));
}


NT2_TEST_CASE_TPL(schur_scalar, NT2_REAL_TYPES)
{
  using nt2::schur;
  typedef nt2::table<T> t_t;
  t_t t=   schur(T(2));
  NT2_TEST_ULP_EQUAL(t, T(2), 0);
  t =   schur(T(2), nt2::real_);
  NT2_TEST_ULP_EQUAL(t, T(2), 0);
  typedef std::complex<T> cT;
  typedef nt2::table<cT> ct_t;
  ct_t ct =   schur(T(2), nt2::cmplx_);
  NT2_TEST_ULP_EQUAL(t, T(2), 0);
  t =   schur(cT(2), nt2::real_);
  NT2_TEST_ULP_EQUAL(t, T(2), 0);
  ct =   schur(cT(2, 2), nt2::cmplx_);
  NT2_TEST_ULP_EQUAL(ct, cT(2, 2), 0);

}

NT2_TEST_CASE_TPL(schur_assert, NT2_REAL_TYPES)
{
  using nt2::schur;
  typedef std::complex<T> cT;
  typedef nt2::table<T> t_t;
  typedef nt2::table<cT> ct_t;
  ct_t cb = bmat<T>()*cT(1, 1);
  t_t t;
  NT2_TEST_ASSERT(t = schur(cb, nt2::real_));
}


NT2_TEST_CASE_TPL(schur1o_ni, NT2_REAL_TYPES)
{
  using nt2::schur;
  using nt2::_;
  using nt2::meta::as_;
  typedef std::complex<T> cT;
  typedef nt2::table<T> t_t;
  typedef nt2::table<cT> ct_t;
  t_t b = bmat<T>();
  t_t t, t1;
  ct_t ct, ct1, w, cb = b;

  std::cout << "11 t = schur(b);" << std::endl;
  t = schur(b);
  std::cout << "12 t1 = schur(b, nt2::real_);" << std::endl;
  t1 = schur(b, nt2::real_);
  NT2_TEST_EQUAL(t, t1);

  std::cout << "13 ct = schur(b, nt2::cmplx_);" << std::endl;
  ct = schur(b, nt2::cmplx_);
  std::cout << "14 ct1 = schur(b);" << std::endl;
  ct1= schur(cb);
  NT2_TEST_EQUAL(ct, ct1);
  NT2_DISPLAY(ct);
  NT2_DISPLAY(t);
  std::cout << "15 w = schur(b, nt2::eigs_);" << std::endl;
  w = schur(cb, nt2::eigs_);
  NT2_TEST_EQUAL(w, nt2::diag_of(ct));

}

NT2_TEST_CASE_TPL(schur2o_ni, NT2_REAL_TYPES)
{
  using nt2::schur;
  using nt2::_;
  using nt2::meta::as_;
  typedef std::complex<T> cT;
  typedef nt2::table<T> t_t;
  typedef nt2::table<cT> ct_t;
  t_t b = bmat<T>();

  t_t t, t1;
  ct_t ct, ct1, w, cb = b;
  t_t u, u1;
  ct_t cu, cu1;
  std::cout << "21 nt2::tie(u, t) = schur(b);" << std::endl;
  nt2::tie(u, t) = schur(b);
  NT2_TEST_ULP_EQUAL(b, mtimes(mtimes(u, t), nt2::trans(u)), 100);
  std::cout << "22 nt2::tie(u1, t1) = schur(b, nt2::real_);" << std::endl;
  nt2::tie(u1, t1) = schur(b, nt2::real_);
  NT2_TEST_EQUAL(t, t1);
  NT2_TEST_EQUAL(u, u1);
  std::cout << "23  nt2::tie(cu, ct)= schur(cb);" << std::endl;
  nt2::tie(cu, ct)= schur(cb);
  std::cout << "24  nt2::tie(cu, ct)= schur(b, nt2::cmplx_);" << std::endl;
  nt2::tie(cu1, ct1)= schur(b, nt2::cmplx_);
  NT2_TEST_EQUAL(ct, ct1);
  NT2_TEST_EQUAL(cu, cu1);
  NT2_TEST_ULP_EQUAL(cb, mtimes(mtimes(cu, ct), nt2::ctrans(cu)), 100);
}

NT2_TEST_CASE_TPL(schur3o_ni, NT2_REAL_TYPES)
{
  using nt2::schur;
  using nt2::_;
  using nt2::meta::as_;
  typedef std::complex<T> cT;
  typedef nt2::table<T> t_t;
  typedef nt2::table<cT> ct_t;
  t_t b = bmat<T>();

  t_t t, t1;
  ct_t ct, ct1, w, cb = b;
  t_t u, u1;
  ct_t cu, cu1;
  std::cout << "31 nt2::tie(u, t, w) = schur(b);" << std::endl;
  nt2::tie(u, t, w) = schur(b);
  NT2_TEST_ULP_EQUAL(b, mtimes(mtimes(u, t), nt2::trans(u)), 100);
  std::cout << "32 nt2::tie(u1, t1, w) = schur(b, nt2::real_);" << std::endl;
  nt2::tie(u1, t1, w) = schur(b, nt2::real_);
  NT2_TEST_EQUAL(t, t1);
  NT2_TEST_EQUAL(u, u1);
  std::cout << "33  nt2::tie(cu, ct, w)= schur(cb);" << std::endl;
  nt2::tie(cu, ct, w)= schur(cb);
  NT2_TEST_EQUAL(w, nt2::diag_of(ct));
  NT2_TEST_ULP_EQUAL(cb, mtimes(mtimes(cu, ct), nt2::ctrans(cu)), 100);
  std::cout << "34 nt2::tie(cu1, ct1, w) = schur(b, nt2::cmplx_);" << std::endl;
  nt2::tie(cu1, ct1, w) = schur(b, nt2::cmplx_);
  NT2_TEST_EQUAL(ct, ct1);
  NT2_TEST_EQUAL(cu, cu1);
  NT2_TEST_EQUAL(w, nt2::diag_of(ct));
  NT2_TEST_ULP_EQUAL(cb, mtimes(mtimes(cu1, ct1), nt2::ctrans(cu1)), 100);
}


NT2_TEST_CASE_TPL(schur1o_ni_sub, NT2_REAL_TYPES)
{
  using nt2::schur;
  using nt2::_;
  using nt2::meta::as_;
  typedef std::complex<T> cT;
  typedef nt2::table<T> t_t;
  typedef nt2::table<cT> ct_t;
  t_t b = bmat<T>();
  t_t t, t1;
  ct_t ct, ct1, w, cb = b;
  t = t1 =  nt2::ones(8, 4, as_<T>());
  ct =  ct1  =  nt2::ones(8, 4, as_<T>());
  w =  nt2::ones(8, 1, as_<T>());

  std::cout << "11 t(_(1, 2, 8), _) = schur(b);" << std::endl;
  t(_(1, 2, 8), _) = schur(b);
  std::cout << "12 t1(_(1, 2, 8), _) = schur(b, nt2::real_);" << std::endl;
  t1(_(1, 2, 8), _) = schur(b, nt2::real_);
  NT2_TEST_EQUAL(t, t1);

  std::cout << "13 ct(_(1, 2, 8), _) = schur(b, nt2::cmplx_);" << std::endl;
  ct(_(1, 2, 8), _) = schur(b, nt2::cmplx_);
  std::cout << "14 ct1(_(1, 2, 8), _) = schur(b);" << std::endl;
  ct1(_(1, 2, 8), _) = schur(cb);
  NT2_TEST_EQUAL(ct, ct1);
  std::cout << "15 w(_(1, 2, 8)) = schur(b, nt2::eigs_);" << std::endl;
  w(_(1, 2, 8)) = schur(cb, nt2::eigs_);
  NT2_TEST_EQUAL(w(_(1, 2, 8)), nt2::diag_of(ct(_(1, 2, 8), _)));

}

NT2_TEST_CASE_TPL(schur2o_ni_sub, NT2_REAL_TYPES)
{
  using nt2::schur;
  using nt2::_;
  using nt2::meta::as_;
  typedef std::complex<T> cT;
  typedef nt2::table<T> t_t;
  typedef nt2::table<cT> ct_t;
  t_t b = bmat<T>();

  t_t t, t1;
  ct_t ct, ct1, cb = b;
  t_t u, u1;
  ct_t cu, cu1;
  t = t1 = nt2::ones(8, 4, as_<T>());
  ct = ct1 = nt2::ones(8, 4, as_<T>());
  u = u1 = nt2::ones(8, 4, as_<T>());
  cu = cu1 = nt2::ones(8, 4, as_<T>());


  std::cout << "21 nt2::tie(u(_(1, 2, 8), _), t(_(1, 2, 8), _)) = schur(b);" << std::endl;
  nt2::tie(u(_(1, 2, 8), _), t(_(1, 2, 8), _)) = schur(b);
  NT2_TEST_ULP_EQUAL(b, mtimes(mtimes(u(_(1, 2, 8), _), t(_(1, 2, 8), _)), nt2::trans(u(_(1, 2, 8), _))), 100);
  std::cout << "22 nt2::tie(u1(_(1, 2, 8), _), t1(_(1, 2, 8), _)) = schur(b, nt2::real_);" << std::endl;
  nt2::tie(u1(_(1, 2, 8), _), t1(_(1, 2, 8), _)) = schur(b, nt2::real_);
  NT2_TEST_EQUAL(t, t1);
  NT2_TEST_EQUAL(u, u1);
  std::cout << "23  nt2::tie(cu(_(1, 2, 8), _), ct(_(1, 2, 8), _))= schur(cb);" << std::endl;
  nt2::tie(cu(_(1, 2, 8), _), ct(_(1, 2, 8), _))= schur(cb);
  std::cout << "24  nt2::tie(cu,(_(1, 2, 8), _) ct(_(1, 2, 8), _))= schur(b, nt2::cmplx_);" << std::endl;
  nt2::tie(cu1(_(1, 2, 8), _), ct1(_(1, 2, 8), _))= schur(b, nt2::cmplx_);
  NT2_TEST_EQUAL(ct, ct1);
  NT2_TEST_EQUAL(cu, cu1);
  NT2_TEST_ULP_EQUAL(cb, mtimes(mtimes(cu(_(1, 2, 8), _), ct(_(1, 2, 8), _)), nt2::ctrans(cu(_(1, 2, 8), _))), 100);
}

NT2_TEST_CASE_TPL(schur3o_ni_sub, NT2_REAL_TYPES)
{
  using nt2::schur;
  using nt2::_;
  using nt2::meta::as_;
  typedef std::complex<T> cT;
  typedef nt2::table<T> t_t;
  typedef nt2::table<cT> ct_t;
  t_t b = bmat<T>();

  t_t t, t1;
  ct_t ct, ct1, w, cb = b;
  t_t u, u1;
  ct_t cu, cu1;
  t = t1 = nt2::ones(8, 4, as_<T>());
  u = u1 = nt2::ones(8, 4, as_<T>());
  ct = ct1 = nt2::ones(8, 4, as_<T>());
  cu = cu1 = nt2::ones(8, 4, as_<T>());
  w = nt2::ones(8, 1, as_<T>());

  std::cout << "31 nt2::tie(u(_(1, 2, 8), _), t(_(1, 2, 8), _), w(_(1, 2, 8))) = schur(b);" << std::endl;
  nt2::tie(u(_(1, 2, 8), _), t(_(1, 2, 8), _), w(_(1, 2, 8))) = schur(b);
  NT2_TEST_ULP_EQUAL(b, mtimes(mtimes(u(_(1, 2, 8), _), t(_(1, 2, 8), _)), nt2::trans(u(_(1, 2, 8), _))), 100);

  std::cout << "32 nt2::tie(u1(_(1, 2, 8), _), t1(_(1, 2, 8), _), w(_(1, 2, 8))) = schur(b, nt2::real_);" << std::endl;
  nt2::tie(u1(_(1, 2, 8), _), t1(_(1, 2, 8), _), w(_(1, 2, 8))) = schur(b, nt2::real_);
  NT2_TEST_EQUAL(t, t1);
  NT2_TEST_EQUAL(u, u1);

  std::cout << "33  nt2::tie(cu(_(1, 2, 8), _), ct(_(1, 2, 8), _), w_(1, 2, 8)))(_(1, 2, 8))= schur(cb);" << std::endl;
  nt2::tie(cu(_(1, 2, 8), _), ct(_(1, 2, 8), _), w(_(1, 2, 8)))= schur(cb);
  NT2_TEST_ULP_EQUAL(cb, mtimes(mtimes(cu(_(1, 2, 8), _), ct(_(1, 2, 8), _)), nt2::ctrans(cu(_(1, 2, 8), _))), 100);
  NT2_TEST_EQUAL(w(_(1, 2, 8)), nt2::diag_of(ct(_(1, 2, 8), _)));

  std::cout << "34 nt2::tie(cu1(_(1, 2, 8), _), ct1(_(1, 2, 8), _), w(_(1, 2, 8))) = schur(b, nt2::cmplx_);" << std::endl;
  nt2::tie(cu1(_(1, 2, 8), _), ct1(_(1, 2, 8), _), w(_(1, 2, 8))) = schur(b, nt2::cmplx_);
  NT2_TEST_EQUAL(ct, ct1);
  NT2_TEST_EQUAL(cu, cu1);
  NT2_TEST_EQUAL(w(_(1, 2, 8)), nt2::diag_of(ct1(_(1, 2, 8), _)));
}
