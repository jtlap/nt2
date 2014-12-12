//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/blas_dotu.hpp>
#include <nt2/include/functions/mtimes.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/functions/colon.hpp>
#include <nt2/include/functions/vertcat.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/functions/linspace.hpp>
#include <nt2/include/functions/plus.hpp>
#include <nt2/include/functions/size.hpp>
#include <nt2/include/functions/resize.hpp>
#include <nt2/include/functions/dot.hpp>

#include <nt2/table.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>


NT2_TEST_CASE_TPL(blas_dotu, NT2_REAL_TYPES )
{
  using nt2::blas_dotu;
  {
    nt2::table<T> x = nt2::_(T(0), T(10));
    nt2::table<T> y = nt2::_(T(10), T(-1), T(0));
    T p = blas_dotu(numel(x), boost::proto::value(x), 1,  boost::proto::value(y), 1);

    NT2_TEST_ULP_EQUAL(p, nt2::dot(x, y), 1);
  }
  {
    typedef std::complex<T> cT;
    nt2::table<cT> x = nt2::linspace(cT(0, 1), cT(1, 0), 10);
    nt2::table<cT> y = nt2::linspace(cT(1, 0), cT(0, 1), 10);

    NT2_DISPLAY(x);
    NT2_DISPLAY(y);
    cT p =blas_dotu(numel(x), boost::proto::value(x), 1,  boost::proto::value(y), 1);
    NT2_TEST_ULP_EQUAL(p, nt2::sum(x*y), 2);
  }
}

NT2_TEST_CASE_TPL(blas_dotu2, NT2_REAL_TYPES )
{
  using nt2::blas_dotu;
  using nt2::_;
  using nt2::end_;
  {
    nt2::table<T> x = nt2::_(T(0), T(11));
    nt2::table<T> y = nt2::_(T(11), T(-1), T(0));
    T p = blas_dotu(numel(x)/2, boost::proto::value(x), 2,  boost::proto::value(y), 2);

    NT2_TEST_ULP_EQUAL(p, nt2::dot(x(_(1, 2, end_)), y(_(1, 2, end_))), 1);
  }
  {
    typedef std::complex<T> cT;
    nt2::table<cT> x = nt2::linspace(cT(0, 1), cT(0, 10), 10);
    nt2::table<cT> y = nt2::linspace(cT(1, 0), cT(10, 0), 10);
    NT2_DISPLAY(x);
    NT2_DISPLAY(y);
    NT2_DISPLAY(x(_(1, 2, end_)));
    NT2_DISPLAY(y(_(1, 2, end_)));
    NT2_DISPLAY(numel(x)/2);
    cT p = blas_dotu(numel(x)/2, boost::proto::value(x), 2,  boost::proto::value(y), 2);
    NT2_DISPLAY(p);
    NT2_TEST_ULP_EQUAL(p, nt2::sum(x(_(1, 2, end_))*y(_(1, 2, end_))), 2);
  }
}

