//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 linalg toolbox - logm"

#include <nt2/table.hpp>
#include <nt2/include/functions/logm.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/ten.hpp>
#include <nt2/include/constants/exp_1.hpp>
#include <nt2/include/functions/expm.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/horzcat.hpp>
#include <nt2/include/functions/from_diag.hpp>
#include <nt2/include/functions/blkdiag.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>

NT2_TEST_CASE_TPL(logm1, NT2_REAL_TYPES)//distinct eigenvalues
{
  typedef T r_t;
  typedef std::complex<T> cT;
  using nt2::logm;
  using nt2::tag::logm_;
  nt2::table<T> n =  nt2::from_diag(T(2)*nt2::_((1),T(3)));
  nt2::table<T> logmn = nt2::logm(n);
  nt2::table<T> el = expm(logmn);
  NT2_DISPLAY(n);
  NT2_DISPLAY(logmn);
  NT2_DISPLAY(el);
  NT2_TEST_ULP_EQUAL(el, n, 8);
  n(1, 2) = T(0.5);
  n(1, 3) = T(2.0);
  n(2, 3) = T(-1.0);
  nt2::table<T> logmn1 = nt2::logm(n);
  nt2::table<T> el1 = nt2::expm(logmn1);
  NT2_DISPLAY(n);
  NT2_DISPLAY(logmn1);
  NT2_DISPLAY(el1);
  NT2_TEST_ULP_EQUAL(el1, n, 5);
 }

NT2_TEST_CASE_TPL(logm2, NT2_REAL_TYPES)//double eigenvalue
{
  typedef T r_t;
  typedef std::complex<T> cT;
  using nt2::logm;
  using nt2::tag::logm_;
  nt2::table<T> r = nt2::trans(nt2::cons<T>(nt2::of_size(3, 3),
                                         0.6931,    0.2500,   -0.0625,
                                         0,    0.6931,    0.5000,
                                         0,         0,    0.6931));
  nt2::table<T> n =  nt2::from_diag(T(2)*nt2::ones(1,2, nt2::meta::as_<T>()));
  n(1, 2) = 0.5;
  nt2::table<T> logmn = nt2::logm(n);
  nt2::table<T> el = expm(logmn);
  NT2_TEST_ULP_EQUAL(el, n, 8);
  nt2::table<T> nn =  blkdiag(n, T(2)*n);
  nn(2, 3) = 1;
  nt2::table<T> logmnn = nt2::logm(nn);
  nt2::table<T> el1 = expm(logmnn);
  NT2_TEST_ULP_EQUAL(el1, nn, 8);

 }


NT2_TEST_CASE_TPL(logm3, NT2_REAL_TYPES)
{
  typedef T r_t;
  typedef std::complex<T> cT;
  using nt2::logm;
  using nt2::tag::logm_;
  nt2::table<T> r = nt2::trans(nt2::cons<T>(nt2::of_size(3, 3),
                                         0.6931,    0.2500,   -0.0625,
                                         0,    0.6931,    0.5000,
                                         0,         0,    0.6931));
  nt2::table<T> n =  nt2::from_diag(T(2)*nt2::ones(1,3, nt2::meta::as_<T>()));
  n(1, 2) = 0.5;
  n(2, 3) = T(1);
  nt2::table<T> logmn = nt2::logm(n);
  nt2::table<T> el = expm(logmn);
  NT2_TEST_ULP_EQUAL(el, n, 8);
}


NT2_TEST_CASE_TPL(logm4, NT2_REAL_TYPES)
{
  typedef T r_t;
  using nt2::logm;
  using nt2::tag::logm_;

  nt2::table<T> n =  nt2::from_diag(nt2::cath(T(2)*nt2::ones(1,3, nt2::meta::as_<T>()),
                                              T(3)*nt2::ones(1, 4, nt2::meta::as_<T>())));
  n(1, 1) = 0.5;
  n(2, 3) = n(4, 5) = n(1, 2) = T(1);
  nt2::table<T> logmn = nt2::logm(n);
  nt2::table<T> el = expm(logmn);
  NT2_TEST_ULP_EQUAL(el, n, 8);
 }
