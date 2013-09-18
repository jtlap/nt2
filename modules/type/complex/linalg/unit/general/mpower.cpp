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
#include <nt2/include/functions/pinv.hpp>
#include <nt2/include/functions/expm.hpp>
#include <nt2/include/constants/pi.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/complex/meta/as_complex.hpp>

NT2_TEST_CASE_TPL(mpower, NT2_REAL_TYPES)
{
  typedef typename nt2::meta::as_complex<T>::type  cT;
  using nt2::mpower;
  using nt2::tag::mpower_;

  nt2::table<cT> n(nt2::of_size(2, 2)), npi;
  n(1, 1) = n(1, 2) = n(2, 2) = cT(1);
  n(2, 1) = cT(0);
  npi = n;
  npi(1, 2) = nt2::Pi<cT>();
  nt2::table<cT> mpowernpi = nt2::mpower(n, nt2::Pi<cT>());
  NT2_TEST_ULP_EQUAL(mpowernpi, npi, 0.5);
 }

