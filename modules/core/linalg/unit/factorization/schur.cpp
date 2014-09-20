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

NT2_TEST_CASE_TPL(schur1o_ni, NT2_REAL_TYPES)
{
  using nt2::schur;
  using nt2::_;
  using nt2::meta::as_;
  typedef std::complex<T> cT;
  typedef nt2::table<T> t_t;
  typedef nt2::table<cT> ct_t;
  t_t b =  nt2::cons(nt2::of_size(4, 4),
                     T(9.648885351992765e-01),     T(4.853756487228412e-01),     T(9.157355251890671e-01),     T(3.571167857418955e-02),
                     T(1.576130816775483e-01),     T(8.002804688888001e-01),     T(7.922073295595544e-01),     T(8.491293058687771e-01),
                     T(9.705927817606157e-01),     T(1.418863386272153e-01),     T(9.594924263929030e-01),     T(9.339932477575505e-01),
                     T(9.571669482429456e-01),     T(4.217612826262750e-01),     T(6.557406991565868e-01),     T(6.787351548577735e-01));

  t_t t, t1;
  ct_t ct, ct1, w, cb = b;

  t = schur(b);
  t1 = schur(b, nt2::real_);
  NT2_TEST_EQUAL(t, t1);

  ct = schur(b, nt2::cmplx_);
  ct1= schur(cb);
  NT2_TEST_EQUAL(ct, ct1);
  NT2_DISPLAY(ct);
  NT2_DISPLAY(t);
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
  t_t b =  nt2::cons(nt2::of_size(4, 4),
                     T(9.648885351992765e-01),     T(4.853756487228412e-01),     T(9.157355251890671e-01),     T(3.571167857418955e-02),
                     T(1.576130816775483e-01),     T(8.002804688888001e-01),     T(7.922073295595544e-01),     T(8.491293058687771e-01),
                     T(9.705927817606157e-01),     T(1.418863386272153e-01),     T(9.594924263929030e-01),     T(9.339932477575505e-01),
                     T(9.571669482429456e-01),     T(4.217612826262750e-01),     T(6.557406991565868e-01),     T(6.787351548577735e-01));

  t_t t, t1;
  ct_t ct, ct1, w, cb = b;
  t_t u, u1;
  ct_t cu, cu1;
  nt2::tie(u, t) = schur(b);
  NT2_TEST_ULP_EQUAL(b, mtimes(mtimes(u, t), nt2::trans(u)), 100);
  nt2::tie(u1, t1) = schur(b, nt2::real_);
  NT2_TEST_EQUAL(t, t1);
  NT2_TEST_EQUAL(u, u1);
  nt2::tie(cu, ct)= schur(cb);
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
  t_t b =  nt2::cons(nt2::of_size(4, 4),
                     T(9.648885351992765e-01),     T(4.853756487228412e-01),     T(9.157355251890671e-01),     T(3.571167857418955e-02),
                     T(1.576130816775483e-01),     T(8.002804688888001e-01),     T(7.922073295595544e-01),     T(8.491293058687771e-01),
                     T(9.705927817606157e-01),     T(1.418863386272153e-01),     T(9.594924263929030e-01),     T(9.339932477575505e-01),
                     T(9.571669482429456e-01),     T(4.217612826262750e-01),     T(6.557406991565868e-01),     T(6.787351548577735e-01));

  t_t t, t1;
  ct_t ct, ct1, w, cb = b;
  t_t u, u1;
  ct_t cu, cu1;
  nt2::tie(u, t, w) = schur(b);
  NT2_TEST_ULP_EQUAL(b, mtimes(mtimes(u, t), nt2::trans(u)), 100);
  nt2::tie(u1, t1, w) = schur(b, nt2::real_);
  NT2_TEST_EQUAL(t, t1);
  NT2_TEST_EQUAL(u, u1);
  nt2::tie(cu, ct, w)= schur(cb);
  nt2::tie(cu1, ct1, w)= schur(b, nt2::cmplx_);
  NT2_TEST_EQUAL(ct, ct1);
  NT2_TEST_EQUAL(cu, cu1);
  NT2_TEST_ULP_EQUAL(cb, mtimes(mtimes(cu, ct), nt2::ctrans(cu)), 100);
}

// NT2_TEST_CASE_TPL(schur, NT2_REAL_TYPES)
// {
//   using nt2::schur;
//   using nt2::_;
//   typedef std::complex<T> cT;
//   typedef nt2::table<T> t_t;
//   typedef nt2::table<cT> ct_t;
//   t_t b =       nt2::ones (4, 4, nt2::meta::as_<T>())
//         + T(10)*nt2::eye  (4, 4, nt2::meta::as_<T>());

//   nt2::display("b", b);
//   {
//     t_t t = schur(b);
//     nt2::display("t", t);
//   }
//   ct_t cb = b;
//   nt2::display("cb", cb);
//   {
//     ct_t ct =  schur(cb);
//     nt2::display("ct", ct);
//   }
//   {
//     ct_t ct =  schur(cb, nt2::real_);
//     nt2::display("t", ct);
//   }
//   {
//     ct_t ct =  schur(b, nt2::cmplx_);
//     nt2::display("t", ct);
//   }


//   {
//     ct_t w =  schur(cb, nt2::eigs_);
//     nt2::display("w", w);
//   }
//   {
//     ct_t w =  schur(b, nt2::eigs_);
//     nt2::display("w", w);
//   }
//   {
//     ct_t ct =  schur(cb);
//     nt2::display("t", ct);
//   }


//   {
//     std::cout << "--1--" << std::endl;
//     t_t t, u;
//     tie(t, u) = schur(b);
//     nt2::display("t", t);
//     nt2::display("u", u);
//     t_t z =  mtimes(mtimes(u, t), nt2::trans(u));
//     NT2_TEST_ULP_EQUAL(b, z, 32);
//   }
//   {
//     std::cout << "--2--" << std::endl;
//     ct_t ct, cu;
//     tie(ct, cu) = schur(cb);
//     nt2::display("ct", ct);
//     nt2::display("cu", cu);
//     ct_t cz =  mtimes(mtimes(cu, ct), nt2::trans(conj(cu)));
//     NT2_TEST_ULP_EQUAL(cb, cz, 32);
//   }
//   {
//     std::cout << "--3--" << std::endl;
//     t_t t;
//     t_t u;
//     tie(t, u) = schur(cb, nt2::real_);
//     nt2::display("t", t);
//     nt2::display("u", u);
//     t_t z =  mtimes(mtimes(u, t), nt2::trans(conj(u)));
//     NT2_TEST_ULP_EQUAL(cb, tocomplex(z), 32);
//   }
//   {
//     std::cout << "--4--" << std::endl;
//     ct_t ct, cu;
//     tie(ct, cu) = schur(b, nt2::cmplx_);
//     nt2::display("ct", ct);
//     nt2::display("cu", cu);
//     ct_t cz =  mtimes(mtimes(cu, ct), nt2::trans(conj(cu)));
//     NT2_TEST_ULP_EQUAL(cb, cz, 32);
//   }
//   {
//     std::cout << "--5--" << std::endl;
//     ct_t t, u;
//     ct_t w;
//     tie(t, u, w) = schur(b);
//     nt2::display("t", t);
//     nt2::display("u", u);
//     nt2::display("w", w);
//     ct_t z =  mtimes(mtimes(u, t), nt2::trans(u));
//     NT2_TEST_ULP_EQUAL(nt2::tocomplex(b), z, 32);
//   }

//   {
//     std::cout << "--6--" << std::endl;
//     ct_t ct, cu;
//     ct_t w;
//     tie(ct, cu, w) = schur(cb);
//     nt2::display("t", ct);
//     nt2::display("u", cu);
//     nt2::display("w", w);
//     ct_t cz =  mtimes(mtimes(cu, ct), nt2::trans(conj(cu)));
//     NT2_TEST_ULP_EQUAL(cb, cz, 32);
//   }

// }

// NT2_TEST_CASE_TPL(schur_b, NT2_REAL_TYPES)
// {
//   using nt2::schur;
//   typedef nt2::table<T> t_t;
//   typedef std::complex<T> cT;
//   typedef nt2::table<cT > ct_t;
//   t_t n =  nt2::from_diag(nt2::cath(T(2)*nt2::ones(1,3, nt2::meta::as_<T>()),
//                                     T(3)*nt2::ones(1, 4, nt2::meta::as_<T>())));
//   n(1, 1) = T(0.5);
//   n(2, 3) = n(4, 5) = n(1, 2) = T(1);
//     nt2::display("n", n);
//   ct_t u, t;
//   tie(t, u) = schur(n, nt2::cmplx_);
//   ct_t cz =  mtimes(mtimes(u, t), nt2::trans(conj(u)));
//     nt2::display("t", t);
//     nt2::display("u", u);
//   NT2_TEST_ULP_EQUAL(tocomplex(n), cz, 50);
// }

// NT2_TEST_CASE_TPL(schur_sub, NT2_REAL_TYPES)
// {
//   using nt2::schur;
//   using nt2::_;
//   using nt2::meta::as_;
//   typedef std::complex<T> cT;
//   typedef nt2::table<T> t_t;
//   typedef nt2::table<cT> ct_t;
//   t_t b =       nt2::ones (4, 4, nt2::meta::as_<T>())
//         + T(10)*nt2::eye  (4, 4, nt2::meta::as_<T>());

//   nt2::display("b", b);
//   {
//     t_t t = nt2::ones(8, 4, as_<T>());
//     t(_(1, 2, 8), _) = schur(b);
//     nt2::display("t", t);
//   }
//   ct_t cb = b;
//   nt2::display("cb", cb);
//   {
//     ct_t ct = nt2::ones(8, 4, as_<T>());
//     ct(_(1, 2, 8), _) =  schur(cb);
//     nt2::display("ct", ct);
//   }
//   {
//     ct_t ct =  schur(cb, nt2::real_);
//     nt2::display("t", ct);
//   }
//   {
//     ct_t ct = nt2::ones(8, 4, as_<T>());
//     ct(_(1, 2, 8), _) =  schur(b, nt2::cmplx_);
//     nt2::display("t", ct);
//   }


//   {
//     ct_t w = nt2::ones(8, 1, as_<T>());
//     w(_(1, 2, 8)) =  schur(cb, nt2::eigs_);
//     nt2::display("w", w);
//   }
//   {
//     ct_t w = nt2::ones(8, 1, as_<T>());
//     w(_(1, 2, 8))  =  schur(b, nt2::eigs_);
//     nt2::display("w", w);
//   }

//   {
//     std::cout << "--1--" << std::endl;
//     t_t t, u;
//     t = u = nt2::ones(8, 4, as_<T>());
//     tie(t(_(1, 2, 8), _), u(_(1, 2, 8), _)) = schur(b);
//     nt2::display("t", t);
//     nt2::display("u", u);
//     t_t z =  mtimes(mtimes(u(_(1, 2, 8), _), t(_(1, 2, 8), _)), nt2::trans(u(_(1, 2, 8), _)));
//     NT2_TEST_ULP_EQUAL(b, z, 32);
//   }
//   {
//     std::cout << "--2--" << std::endl;
//     ct_t ct, cu;
//     ct = cu = nt2::ones(8, 4, as_<T>());
//     tie(ct(_(1, 2, 8), _), cu(_(1, 2, 8), _)) = schur(cb);
//     nt2::display("ct", ct);
//     nt2::display("cu", cu);
//     ct_t cz =  mtimes(mtimes(cu(_(1, 2, 8), _), ct(_(1, 2, 8), _)), nt2::trans(conj(cu(_(1, 2, 8), _))));
//     NT2_TEST_ULP_EQUAL(cb, cz, 32);
//   }
//   {
//     std::cout << "--3--" << std::endl;
//     t_t ct, cu;
//     tie(ct, cu) = schur(cb, nt2::real_);
//     nt2::display("ct", ct);
//     nt2::display("cu", cu);
//     ct_t cz =  mtimes(mtimes(cu, ct), nt2::trans(conj(cu)));
//     NT2_TEST_ULP_EQUAL(cb, cz, 32);
//   }
//   {
//     std::cout << "--4--" << std::endl;
//     ct_t ct, cu;
//     ct = cu = nt2::ones(8, 4, as_<T>());
//     tie(ct(_(1, 2, 8), _), cu(_(1, 2, 8), _)) = schur(b, nt2::cmplx_);
//     nt2::display("ct", ct);
//     nt2::display("cu", cu);
//     ct_t cz =  mtimes(mtimes(cu(_(1, 2, 8), _), ct(_(1, 2, 8), _)), nt2::trans(conj(cu(_(1, 2, 8), _))));
//     NT2_TEST_ULP_EQUAL(cb, cz, 32);
//   }
//   {
//     std::cout << "--5--" << std::endl;
//     ct_t t, u;
//     ct_t w;
//     tie(t, u, w) = schur(b);
//     nt2::display("t", t);
//     nt2::display("u", u);
//     nt2::display("w", w);
//     ct_t z =  mtimes(mtimes(u, t), nt2::trans(conj(u)));
//     NT2_TEST_ULP_EQUAL(nt2::tocomplex(b), z, 32);
//   }

//   {
//     std::cout << "--6--" << std::endl;
//     ct_t ct, cu;
//     ct_t w;
//     ct = cu = nt2::ones(8, 4, as_<T>());
//     w = nt2::ones(8, 1, as_<T>());
//     tie(ct(_(1, 2, 8), _), cu(_(1, 2, 8), _), w(_(1, 2, 8))) = schur(cb);
//     nt2::display("t", ct);
//     nt2::display("u", cu);
//     nt2::display("w", w);
//     ct_t cz =  mtimes(mtimes(cu(_(1, 2, 8), _), ct(_(1, 2, 8), _)), nt2::trans(conj(cu(_(1, 2, 8), _))));
//     NT2_TEST_ULP_EQUAL(cb, cz, 32);
//   }

// }
