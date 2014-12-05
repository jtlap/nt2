//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/blas_swap.hpp>
#include <nt2/include/functions/mtimes.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/functions/colon.hpp>
#include <nt2/include/functions/vertcat.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/functions/linspace.hpp>
#include <nt2/include/functions/plus.hpp>

#include <nt2/table.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>


NT2_TEST_CASE_TPL(blas_swap, NT2_REAL_TYPES )
{
  using nt2::blas_swap;
  {
    nt2::table<T> x = nt2::_(T(0), T(10));
    nt2::table<T> y = nt2::_(T(0), T(10))+T(10);
    nt2::table<T> v = nt2::catv(x, y);

    blas_swap(numel(x), boost::proto::value(x), 1,  boost::proto::value(y), 1);

    NT2_TEST_ULP_EQUAL(v, catv(y, x), 0.5);
  }
  {
    typedef std::complex<T> cT;
    nt2::table<cT> x = nt2::linspace(cT(0, 1), cT(1, 0), 10);
    nt2::table<cT> y = nt2::linspace(cT(1, 1), cT(2, 0), 10);
    nt2::table<cT> v = nt2::catv(x, y);

    blas_swap(numel(x), boost::proto::value(x), 1,  boost::proto::value(y), 1);

    NT2_TEST_ULP_EQUAL(v, catv(y, x), 0.5);
  }
}

NT2_TEST_CASE_TPL(blas_swap2, NT2_REAL_TYPES )
{
  using nt2::blas_swap;
  using nt2::_;
  using nt2::end_;
  {
    nt2::table<T> x = _(T(0), T(11));
    nt2::table<T> y = _(T(0), T(11))+T(10);
    nt2::table<T> xx =x;
    nt2::table<T> yy =y;
    blas_swap(numel(x)/2,  boost::proto::value(x), 2,  boost::proto::value(y), 2);

    NT2_TEST_ULP_EQUAL(x(_(1, 2, end_)), yy(_(1, 2, end_)), 0.5);
    NT2_TEST_ULP_EQUAL(x(_(2, 2, end_)), xx(_(2, 2, end_)), 0.5);
    NT2_TEST_ULP_EQUAL(y(_(1, 2, end_)), xx(_(1, 2, end_)), 0.5);
    NT2_TEST_ULP_EQUAL(y(_(2, 2, end_)), yy(_(2, 2, end_)), 0.5);
  }
  {
    typedef std::complex<T> cT;
    nt2::table<cT> x = nt2::linspace(cT(0, 1), cT(1, 0), 10);
    nt2::table<cT> y = nt2::linspace(cT(1, 1), cT(2, 0), 10);
    nt2::table<cT> xx =x;
    nt2::table<cT> yy =y;
    blas_swap(numel(x)/2,  boost::proto::value(x), 2,  boost::proto::value(y), 2);

    NT2_TEST_ULP_EQUAL(x(_(1, 2, end_)), yy(_(1, 2, end_)), 0.5);
    NT2_TEST_ULP_EQUAL(x(_(2, 2, end_)), xx(_(2, 2, end_)), 0.5);
    NT2_TEST_ULP_EQUAL(y(_(1, 2, end_)), xx(_(1, 2, end_)), 0.5);
    NT2_TEST_ULP_EQUAL(y(_(2, 2, end_)), yy(_(2, 2, end_)), 0.5);
  }

}
