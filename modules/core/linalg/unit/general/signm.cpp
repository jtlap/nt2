//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 linalg toolbox - signm"

#include <nt2/table.hpp>
#include <nt2/include/functions/signm.hpp>
#include <nt2/include/functions/sign.hpp>
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

NT2_TEST_CASE_TPL(signm0, NT2_REAL_TYPES)//distinct eigenvalues
{
  NT2_TEST_EQUAL(nt2::sign(T(3)), nt2::signm(T(3)));
 }

NT2_TEST_CASE_TPL(signm1, NT2_REAL_TYPES)//distinct eigenvalues
{
  using nt2::signm;
  using nt2::tag::signm_;
  typedef std::complex<T> cT;
  nt2::table<T> n =  nt2::from_diag(T(2)*nt2::_((1),T(3)));
  nt2::table<cT> signmn = nt2::signm(n);
  nt2::table<cT> el =  nt2::from_diag(nt2::sign(nt2::diag_of(n)));
  NT2_TEST_ULP_EQUAL(el, signmn, 0.5);
 }

NT2_TEST_CASE_TPL(signm2, NT2_REAL_TYPES)//distinct eigenvalues
{
  using nt2::signm;
  using nt2::tag::signm_;
  typedef std::complex<T> cT;
  nt2::table<T> n =  nt2::cons<T>(nt2::of_size(4, 4),
                                  4.624474393e-01,    5.240723374e-01,    1.245024882e+00,    9.846853861e-01,
                                  5.240723374e-01,    1.865923243e+00,    5.068274499e-01,    9.061514670e-01,
                                  1.245024882e+00,    5.068274499e-01,    1.132849763e+00,    9.841813571e-01,
                                  9.846853861e-01,    9.061514670e-01,    9.841813571e-01,    8.737175167e-01);
   nt2::table<cT> x =  nt2::cons<T>(nt2::of_size(4, 4),
                                   -5.266543801e-02,  -5.846251163e-01,   7.606625611e-01,  -2.771863871e-01,
                                   -5.846251163e-01,   5.316040474e-01,   4.981798085e-01,   3.569698707e-01,
                                    7.606625611e-01,   4.981798085e-01,   4.104374467e-01,  -6.892350009e-02,
                                   -2.771863871e-01,   3.569698707e-01,  -6.892350009e-02,  -8.893760562e-01);

  nt2::table<cT> signmn = nt2::signm(n);
  NT2_TEST_ULP_EQUAL(x, signmn, 0.5);
 }

