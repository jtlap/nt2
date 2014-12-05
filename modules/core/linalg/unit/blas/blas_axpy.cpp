//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/blas_axpy.hpp>
#include <nt2/include/functions/colon.hpp>
#include <nt2/include/functions/plus.hpp>
#include <nt2/include/functions/numel.hpp>
#include <nt2/include/functions/linspace.hpp>
#include <nt2/include/functions/multiplies.hpp>
#include <nt2/include/functions/plus.hpp>

#include <nt2/table.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <complex>

NT2_TEST_CASE_TPL(blas_axpy, NT2_REAL_TYPES )
{
  using nt2::blas_axpy;
  {
    nt2::table<T> x = nt2::_(T(0), T(10));
    nt2::table<T> y = nt2::_(T(0), T(10))+T(10);
    nt2::table<T> yy = y;
    T alpha = T(2);
    blas_axpy(numel(x), alpha, boost::proto::value(x), 1, boost::proto::value(y), 1);

    NT2_TEST_ULP_EQUAL(y, alpha*x+yy, 0.5);
  }
  {
    typedef std::complex<T> cT;
    nt2::table<cT> x = nt2::linspace(cT(0, 1), cT(1, 0), 10);
    nt2::table<cT> y = nt2::linspace(cT(1, 1), cT(1, 0), 10);
    nt2::table<cT> yy = y;
    cT alpha = cT(2, 1);
    blas_axpy(numel(x), alpha, boost::proto::value(x), 1, boost::proto::value(y), 1);
    NT2_TEST_ULP_EQUAL(y, alpha*x+yy, 0.5);
  }
}

NT2_TEST_CASE_TPL(blas_axpy2, NT2_REAL_TYPES )
{
  using nt2::blas_axpy;
  using nt2::end_;
  using nt2::_;

  {
    nt2::table<T> x = nt2::_(T(0), T(11));
    nt2::table<T> y = nt2::_(T(0), T(10))+T(10);
    nt2::table<T> yy = y;
    T alpha = T(2);
    blas_axpy(numel(x)/2, alpha, boost::proto::value(x), 2, boost::proto::value(y), 2);
    NT2_TEST_ULP_EQUAL(y(_(1, 2, end_)), alpha*x(_(1, 2, end_))+yy(_(1, 2, end_)), 0.5);
    NT2_TEST_ULP_EQUAL(y(_(2, 2, end_)), yy(_(2, 2, end_)), 0.5);
  }

  {
    typedef std::complex<T> cT;
    nt2::table<cT> x = nt2::linspace(cT(0, 1), cT(1, 0), 10);
    nt2::table<cT> y = nt2::linspace(cT(1, 1), cT(1, 0), 10);
    nt2::table<cT> yy = y;
    cT alpha = cT(2, 1);

    blas_axpy(numel(x)/2, alpha, boost::proto::value(x), 2, boost::proto::value(y), 2);
    NT2_TEST_ULP_EQUAL(y(_(1, 2, end_)), alpha*x(_(1, 2, end_))+yy(_(1, 2, end_)), 0.5);
    NT2_TEST_ULP_EQUAL(y(_(2, 2, end_)), yy(_(2, 2, end_)), 0.5);

  }
}

