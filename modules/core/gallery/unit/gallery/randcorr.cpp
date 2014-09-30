//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 gallery toolbox - randcorr function"

#include <nt2/table.hpp>
#include <nt2/include/functions/randcorr.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/functions/transpose.hpp>
#include <nt2/include/functions/colon.hpp>
#include <nt2/include/functions/linspace.hpp>
#include <nt2/include/functions/svd.hpp>
#include <nt2/include/functions/sort.hpp>
#include <nt2/include/functions/globalsum.hpp>
#include <nt2/include/functions/asum2.hpp>
#include <nt2/include/functions/numel.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/module.hpp>


NT2_TEST_CASE_TPL ( randcorr, NT2_REAL_TYPES)
{
  nt2::table<T> x0 = nt2::colvect(nt2::_(T(2), T(6)));
  nt2::table<T> x =  (x0/nt2::globalsum(x0))*T(nt2::numel(x0));
  nt2::table<T> rc =  nt2::randcorr(x, 5, 0);
  NT2_TEST_ULP_EQUAL(nt2::svd(rc), nt2::flipud(x), 5); //check rc has the chosen singular values
  rc = nt2::randcorr(x);
  NT2_TEST_ULP_EQUAL(nt2::svd(rc), nt2::flipud(x), 5); //check rc has the chosen singular values
  rc = nt2::randcorr(x, 6, 1);
  NT2_TEST_ULP_EQUAL(nt2::svd(rc), nt2::flipud(x), 5); //check rc has the chosen singular values
}






