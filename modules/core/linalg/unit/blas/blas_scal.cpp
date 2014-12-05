//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/blas_scal.hpp>
#include <nt2/include/functions/colon.hpp>
#include <nt2/include/functions/plus.hpp>
#include <nt2/include/functions/numel.hpp>
#include <nt2/include/functions/linspace.hpp>
#include <nt2/include/functions/multiplies.hpp>

#include <nt2/table.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <complex>

NT2_TEST_CASE_TPL(blas_scal, NT2_REAL_TYPES )
{
  using nt2::blas_scal;
  {
    nt2::table<T> x = nt2::_(T(0), T(10));
    T alpha = T(2);
    nt2::table<T> x2 = x+x;
    blas_scal(numel(x), alpha, boost::proto::value(x), 1);
    NT2_TEST_ULP_EQUAL(x, x2, 0.5);
  }
  {
    typedef std::complex<T> cT;
    nt2::table<cT> x = nt2::linspace(cT(0, 1), cT(1, 0), 10);
    cT alpha = cT(2, 2);
    nt2::table<cT> xalpha = alpha*x;
    blas_scal(numel(x), alpha, boost::proto::value(x), 1);
    NT2_TEST_ULP_EQUAL(x, xalpha, 0.5);
  }
}

NT2_TEST_CASE_TPL(blas_scal2, NT2_REAL_TYPES )
{
  using nt2::blas_scal;
  using nt2::end_;

  {
    nt2::table<T> x = nt2::_(T(0), T(11));
    T alpha = T(2);
    nt2::table<T> x2 = x;
    x2(nt2::_(1, 2, end_)) =  x2(nt2::_(1, 2, end_))+ x2(nt2::_(1, 2, end_));
    blas_scal(numel(x)/2, alpha, boost::proto::value(x), 2);
    NT2_TEST_ULP_EQUAL(x, x2, 0.5);
  }
  {
    typedef std::complex<T> cT;
    nt2::table<cT> x = nt2::linspace(cT(0, 1), cT(1, 0), 10);
    cT alpha = cT(2, 2);
    nt2::table<cT> xalpha = x;
    xalpha(nt2::_(1, 2, end_)) =  alpha*xalpha(nt2::_(1, 2, end_));

    blas_scal(numel(x)/2, alpha, boost::proto::value(x), 2);
    NT2_TEST_ULP_EQUAL(x, xalpha, 0.5);
  }
}

