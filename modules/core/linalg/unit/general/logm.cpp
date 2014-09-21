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
#include <nt2/include/functions/log.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/ten.hpp>
#include <nt2/include/constants/exp_1.hpp>
#include <nt2/include/constants/i.hpp>
#include <nt2/include/functions/expm.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/horzcat.hpp>
#include <nt2/include/functions/from_diag.hpp>
#include <nt2/include/functions/blkdiag.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>

NT2_TEST_CASE_TPL(logm0, NT2_REAL_TYPES)//distinct eigenvalues
{
  NT2_TEST_EQUAL(nt2::log(T(3)), nt2::logm(T(3)));
 }

NT2_TEST_CASE_TPL(logm1, NT2_REAL_TYPES)//distinct eigenvalues
{
  using nt2::logm;
  using nt2::tag::logm_;
  nt2::table<T> n =  nt2::from_diag(T(2)*nt2::_((1),T(3)));
  nt2::table<T> logmn = nt2::logm(n);
  nt2::table<T> el =  nt2::from_diag(nt2::log(nt2::diag_of(n)));
  NT2_TEST_ULP_EQUAL(el, logmn, 0.5);
  n(1, 2) = T(0.5);
  n(1, 3) = T(2.0);
  n(2, 3) = T(-1.0);
  nt2::table<T> logmn1 = nt2::logm(n);
  nt2::table<T> r = nt2::trans(nt2::cons<T>(nt2::of_size(3, 3),
                                            0.69314718055994528623, 0.17328679513998632156, 0.56728627386229113494,
                                            0, 1.3862943611198905725, -0.20273255405408219243,
                                            0, 0, 1.7917594692280549573 ));
  nt2::table<T> el1 = nt2::expm(logmn1);
  NT2_TEST_ULP_EQUAL(r, logmn1, 5);
 }

NT2_TEST_CASE_TPL(logm2, NT2_REAL_TYPES)//double eigenvalue
{
  using nt2::logm;
  using nt2::tag::logm_;
  nt2::table<T> r = nt2::trans(nt2::cons<T>(nt2::of_size(2, 2),
                                            0.69314718055994528623, 0.25,
                                            0, 0.69314718055994528623  ));
  nt2::table<T> n =  nt2::from_diag(T(2)*nt2::ones(1,2, nt2::meta::as_<T>()));
  n(1, 2) = 0.5;
  nt2::table<T> logmn = nt2::logm(n);
  NT2_TEST_ULP_EQUAL(r,  logmn, 0.5);
  nt2::table<T> nn =  blkdiag(n, T(2)*n);
  nn(2, 3) = 1;
  nt2::table<T> logmnn = nt2::logm(nn);
  nt2::table<T> r1 =     nt2::trans(nt2::cons<T>(nt2::of_size(4, 4), 0.69314718055994528623, 0.25, -0.038356602430006839222, 0.0071066024300068392217,
                                                 0, 0.69314718055994528623, 0.34657359027997264311, -0.048286795139986321557,
                                                 0, 0, 1.3862943611198905725 ,0.25,
                                                 0, 0, 0, 1.3862943611198905725 ));
  NT2_TEST_ULP_EQUAL(r1, logmnn, 8);

 }


NT2_TEST_CASE_TPL(logm3, NT2_REAL_TYPES)
{
  using nt2::logm;
  using nt2::tag::logm_;
  nt2::table<T> r = nt2::trans(nt2::cons<T>(nt2::of_size(3, 3),
                                            0.69314718055994573032, 0.2500000000000000, -0.0625,
                                            0, 0.69314718055994573032, 0.500000000000000,
                                            0, 0, 0.69314718055994573032
                                           ));
  nt2::table<T> n =  nt2::from_diag(T(2)*nt2::ones(1,3, nt2::meta::as_<T>()));
  n(1, 2) = 0.5;
  n(2, 3) = T(1);
  nt2::table<T> logmn = nt2::logm(n);
  NT2_TEST_ULP_EQUAL(r, logmn, 2);
}


NT2_TEST_CASE_TPL(logm4, NT2_REAL_TYPES)
{
  using nt2::logm;
  using nt2::tag::logm_;

  nt2::table<T> n =  nt2::from_diag(nt2::cath(T(2)*nt2::ones(1,3, nt2::meta::as_<T>()),
                                              T(3)*nt2::ones(1, 4, nt2::meta::as_<T>())));
  n(1, 1) = 0.5;
  n(2, 3) = n(4, 5) = n(1, 2) = T(1);
  nt2::table<T> r = nt2::trans(nt2::cons<T>(nt2::of_size(7, 7),
                                            -0.69314718055994528623, 0.92419624074659367796, -0.28279749383106245197, 0, 0, 0, 0,
                                            0, 0.69314718055994528623, 0.5, 0, 0, 0, 0,
                                            0, 0, 0.69314718055994528623, 0, 0, 0, 0,
                                            0, 0, 0, 1.0986122886681113364, 0.33333333333333342585, 0, 0,
                                            0, 0, 0, 0, 1.0986122886681113364, 0, 0,
                                            0, 0, 0, 0, 0, 1.0986122886681113364, 0,
                                            0, 0, 0, 0, 0, 0, 1.0986122886681113364 ));
  nt2::table<T> logmn = nt2::logm(n);
  NT2_TEST_ULP_EQUAL(r, logmn, 8);
}

NT2_TEST_CASE_TPL(logm5, NT2_REAL_TYPES)
{
  typedef std::complex<T> cT;
  using nt2::logm;
  using nt2::tag::logm_;

  nt2::table<cT> n = nt2::I<cT>()*nt2::eye(2, nt2::meta::as_<T>());
  nt2::table<cT> logmn = nt2::logm(n);
  nt2::table<cT> r = nt2::trans(nt2::cons<cT>(nt2::of_size(2, 2),
                                             cT(0,1.570796326794896558), cT(0,0),
                                             cT(0,0), cT(0,1.570796326794896558) ));
  NT2_TEST_ULP_EQUAL(r, logmn, 0.5);
  n(2, 2)+= cT(1);
  nt2::table<cT> logmn1 = nt2::logm(n);
  nt2::table<cT> r1 = nt2::trans(nt2::cons<cT>(nt2::of_size(2, 2),
                                               cT(0,1.570796326794896558), cT(0,0),
                                               cT(0,0), cT (0.34657359027997269862,0.785398163397448279)
                                              ));
  NT2_TEST_ULP_EQUAL(r1, logmn1, 0.5);
  n(2, 2) = cT(2, 1);
  nt2::table<cT> logmn2 = nt2::logm(n);
  nt2::table<cT> r2 = nt2::trans(nt2::cons<cT>(nt2::of_size(2, 2),
                                               cT(0,1.570796326794896558), cT(0,0),
                                               cT(0,0), cT(0.80471895621705025192,0.46364760900080614903)
                                              ));
  NT2_TEST_ULP_EQUAL(r2, logmn2, 0.5);

}
NT2_TEST_CASE_TPL(logm6, NT2_REAL_TYPES)
{
  typedef std::complex<T> cT;
  using nt2::logm;
  using nt2::tag::logm_;
  nt2::table<cT>  n =  nt2::I<cT>()*nt2::from_diag(T(2)*nt2::_((1),T(3)));
  n(2, 3)+= cT(1);
  nt2::table<cT> logmn = nt2::logm(n);
  nt2::table<cT> r =   nt2::trans(nt2::cons<cT>(nt2::of_size(3, 3),
                                                cT(0.69314718055994528623,1.570796326794896558), cT(0,0), cT(0,0),
                                                cT(0,0), cT(1.3862943611198905725,1.570796326794896558), cT(0,-0.20273255405408219243),
                                                cT(0,0), cT(0,0), cT(1.7917594692280549573,1.570796326794896558)
                                               ));
  NT2_TEST_ULP_EQUAL(r, logmn, 0.5);
 }
NT2_TEST_CASE_TPL(logm7, NT2_REAL_TYPES)
{
  typedef std::complex<T> cT;
  using nt2::logm;
  using nt2::tag::logm_;
  nt2::table<cT>  n =  nt2::trans(nt2::cons<cT>(nt2::of_size(2, 2),
                                                cT(0, 1), cT(1, 1),
                                                cT(0, 0), cT(0, -1)))*T(1.0e-16);
  nt2::table<cT> logmn = nt2::logm(n);
  nt2::table<cT> r =   nt2::trans(nt2::cons<cT>(nt2::of_size(2, 2),
                                                cT(-3.684136148790473e+01,  1.570796326794897e+00),        cT(4.712388980384690e+00,  4.712388980384690e+00),
                                                cT(0.000000000000000e+00,  0.000000000000000e+00),         cT(-3.684136148790473e+01, -1.570796326794897e+00)
                                               ));
  NT2_TEST_ULP_EQUAL(r, logmn, 1);
 }
