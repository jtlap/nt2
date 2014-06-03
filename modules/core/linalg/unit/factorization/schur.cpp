//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 linalg toolbox - schur factorization"

#include <nt2/table.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/functions/schur.hpp>
#include <nt2/include/constants/sqrt_2o_2.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/functions/ldexp.hpp>
#include <nt2/include/functions/from_diag.hpp>
#include <nt2/include/functions/repnum.hpp>
#include <nt2/include/functions/rif.hpp>
#include <nt2/include/functions/transpose.hpp>
#include <nt2/include/functions/horzcat.hpp>
#include <nt2/include/functions/globalmax.hpp>
#include <nt2/include/functions/tocomplex.hpp>
#include <nt2/include/functions/triu.hpp>
#include <nt2/include/functions/mtimes.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <complex>
#include <nt2/linalg/options.hpp>


NT2_TEST_CASE_TPL(schur_sca, NT2_REAL_TYPES)
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
}


NT2_TEST_CASE_TPL(schur, NT2_REAL_TYPES)
{
  using nt2::schur;
  using nt2::_;
  typedef std::complex<T> cT;
  typedef nt2::table<T> t_t;
  typedef nt2::table<cT> ct_t;
  T sq = nt2::Sqrt_2o_2<T>();
// t_t b = nt2::cons(nt2::of_size(2, 2), sq, sq, -sq, sq);
  t_t b =       nt2::ones (4, 4, nt2::meta::as_<T>())
        + T(10)*nt2::eye  (4, 4, nt2::meta::as_<T>());
//   b(1, 1) = T(1);
//   b(_, 1) = b(_, 3);
//   b(3, 3) = T(20);

  nt2::display("b", b);
  {
    t_t t = schur(b);
    nt2::display("t", t);
  }
  ct_t cb = b;
  nt2::display("cb", cb);
  {
    ct_t ct =  schur(cb);
    nt2::display("ct", ct);
  }
  {
    ct_t ct =  schur(cb, nt2::real_);
    nt2::display("t", ct);
  }
  {
    ct_t ct =  schur(b, nt2::cmplx_);
    nt2::display("t", ct);
  }
  std::cout << "icitte" << std::endl;
  {
    ct_t w =  schur(cb, nt2::eigs_);
    nt2::display("w", w);
  }
  std::cout << "latte" << std::endl;
  std::cout << "icitte" << std::endl;
  {
    ct_t w =  schur(b, nt2::eigs_);
    nt2::display("w", w);
  }
  std::cout << "latte" << std::endl;
  {
    ct_t ct =  schur(cb);
    nt2::display("t", ct);
  }
  {
    std::cout << "--1--" << std::endl;
    t_t t, u;
    tie(t, u) = schur(b);
    nt2::display("t", t);
    nt2::display("u", u);
    t_t z =  mtimes(mtimes(u, t), nt2::trans(u));
    NT2_TEST_ULP_EQUAL(b, z, 32);
  }
  {
    std::cout << "--2--" << std::endl;
    ct_t ct, cu;
    tie(ct, cu) = schur(cb);
    nt2::display("ct", ct);
    nt2::display("cu", cu);
    ct_t cz =  mtimes(mtimes(cu, ct), nt2::trans(conj(cu)));
    NT2_TEST_ULP_EQUAL(cb, cz, 32);
  }
  {
    std::cout << "--3--" << std::endl;
    ct_t ct, cu;
    tie(ct, cu) = schur(cb, nt2::real_);
    nt2::display("ct", ct);
    nt2::display("cu", cu);
    ct_t cz =  mtimes(mtimes(cu, ct), nt2::trans(conj(cu)));
    NT2_TEST_ULP_EQUAL(cb, cz, 32);
  }
  {
    std::cout << "--4--" << std::endl;
    ct_t ct, cu;
    tie(ct, cu) = schur(b, nt2::cmplx_);
    nt2::display("ct", ct);
    nt2::display("cu", cu);
    ct_t cz =  mtimes(mtimes(cu, ct), nt2::trans(conj(cu)));
    NT2_TEST_ULP_EQUAL(cb, cz, 32);
  }
  {
    std::cout << "--5--" << std::endl;
    t_t t, u;
    ct_t w;
    tie(t, u, w) = schur(b);
    nt2::display("t", t);
    nt2::display("u", u);
    nt2::display("w", w);
    t_t z =  mtimes(mtimes(u, t), nt2::trans(u));
    NT2_TEST_ULP_EQUAL(b, z, 32);
  }

  {
    std::cout << "--6--" << std::endl;
    ct_t ct, cu;
    ct_t w;
    tie(ct, cu, w) = schur(cb);
    nt2::display("t", ct);
    nt2::display("u", cu);
    nt2::display("w", w);
    ct_t cz =  mtimes(mtimes(cu, ct), nt2::trans(conj(cu)));
    NT2_TEST_ULP_EQUAL(cb, cz, 32);
  }

}
NT2_TEST_CASE_TPL(schur_b, NT2_REAL_TYPES)
{
  using nt2::schur;
  typedef nt2::table<T> t_t;
  typedef std::complex<T> cT;
  typedef nt2::table<cT > ct_t;
  t_t n =  nt2::from_diag(nt2::cath(T(2)*nt2::ones(1,3, nt2::meta::as_<T>()),
                                    T(3)*nt2::ones(1, 4, nt2::meta::as_<T>())));
  n(1, 1) = T(0.5);
  n(2, 3) = n(4, 5) = n(1, 2) = T(1);
    nt2::display("n", n);
  ct_t u, t;
  tie(t, u) = schur(n, nt2::cmplx_);
  ct_t cz =  mtimes(mtimes(u, t), nt2::trans(conj(u)));
    nt2::display("t", t);
    nt2::display("u", u);
  NT2_TEST_ULP_EQUAL(tocomplex(n), cz, 32);
}
