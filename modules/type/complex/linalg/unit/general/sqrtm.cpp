//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 linalg toolbox - sqrtm factorization"

#include <nt2/table.hpp>
#include <nt2/include/functions/sqrtm.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/ten.hpp>

#include <nt2/include/functions/cons.hpp>
#include <nt2/include/functions/transpose.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>
#include <nt2/sdk/complex/meta/as_complex.hpp>

NT2_TEST_CASE_TPL(sqrtm, NT2_REAL_TYPES)
{
  typedef typename nt2::meta::as_complex<T>::type  cT;
  using nt2::sqrtm;
  using nt2::tag::sqrtm_;

  nt2::table<cT> n(nt2::of_size(2, 2));
  n(1, 1) = n(1, 2) = n(2, 2) =  cT(1);
  n(2, 1) = cT(0);
  nt2::table<cT> sqrtmn = nt2::sqrtm(n);
  NT2_TEST_ULP_EQUAL(mtimes(sqrtmn, sqrtmn), n, 0.5);
 }



 NT2_TEST_CASE_TPL(sqrtm2, NT2_REAL_TYPES)
{
  typedef typename nt2::meta::as_complex<T>::type  cT;
  using nt2::sqrtm;
  using nt2::tag::sqrtm_;
  nt2::table<cT> n = nt2::trans(nt2::cons(nt2::of_size(2, 2),
                                          cT(1, 1), cT(0, 1),
                                          cT(1), cT(1, -1)
                                         ));
  nt2::table<cT> r = nt2::trans(nt2::cons(nt2::of_size(2, 2),
                                          cT(1.079508833429258,  0.370665396720664), cT(-0.031190606620217, 0.447995216412301),
                                          cT(0.447995216412301, 0.031190606620217), cT(1.141890046669693, -0.525325036103938)
                                         ));

  nt2::table<cT> sqrtmn = nt2::sqrtm(n);
  NT2_TEST_ULP_EQUAL(mtimes(sqrtmn, sqrtmn), n, 5);
  NT2_TEST_ULP_EQUAL(r, sqrtmn, 128);
 }
