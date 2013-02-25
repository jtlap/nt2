//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 linalg toolbox - mpower factorization"

#include <nt2/table.hpp>
#include <nt2/include/functions/mpower.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/constants/pi.hpp>

#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>

NT2_TEST_CASE_TPL(mpower, NT2_REAL_TYPES)
{
  typedef T r_t;
  using nt2::mpower;
  using nt2::tag::mpower_;

  nt2::table<T> n(nt2::of_size(2, 2)), npi;
  n(1, 1) = n(1, 2) = n(2, 2) = 1;
  n(2, 1) = T(0);
  npi = n;
  npi(1, 2) = nt2::Pi<T>();
  NT2_DISPLAY(n);
  NT2_DISPLAY(npi);
  nt2::table<T> mpowernpi = nt2::mpower(n, nt2::Pi<T>());
  NT2_DISPLAY(mpowernpi);
  NT2_TEST_ULP_EQUAL(mpowernpi, npi, 0.5);
 }

NT2_TEST_CASE_TPL(mpower2, NT2_REAL_TYPES)
{
  typedef T r_t;
  using nt2::mpower;
  using nt2::tag::mpower_;

  nt2::table<T> n(nt2::of_size(2, 2)), npi;
  n(1, 1)  = n(2, 2) = 1;
  n(2, 1) = n(1, 2) = T(0);
  NT2_DISPLAY(n);
  nt2::table<T> mpowerpin = nt2::mpower(nt2::Pi<T>(), n);
  NT2_DISPLAY(mpowerpin);
  NT2_TEST_ULP_EQUAL(mpowerpin, nt2::Pi<T>()*n, 0.5);
 }

