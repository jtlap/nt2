//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/blas_sbmv.hpp>
#include <nt2/include/functions/blas_band_h.hpp>
#include <nt2/include/functions/band.hpp>
#include <nt2/include/functions/mtimes.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/functions/colon.hpp>
#include <nt2/include/functions/vertcat.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/functions/linspace.hpp>
#include <nt2/include/functions/plus.hpp>
#include <nt2/include/functions/size.hpp>
#include <nt2/include/functions/resize.hpp>
#include <nt2/include/functions/mtimes.hpp>
#include <nt2/include/functions/multiplies.hpp>
#include <nt2/include/functions/plus.hpp>
#include <nt2/include/functions/linspace.hpp>
#include <nt2/include/functions/transpose.hpp>
#include <nt2/include/functions/transpose.hpp>
#include <nt2/include/functions/average.hpp>



#include <nt2/table.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>


NT2_TEST_CASE_TPL(blas_sbmvu, NT2_REAL_TYPES )
{
  using nt2::blas_sbmv;
  using nt2::mtimes;
  using nt2::reshape;
  using nt2::_;
  using nt2::linspace;
  {
    nt2::table<T> b = reshape(_(T(1), T(25)), 5, 5);
    nt2::table<T> a = nt2::band(nt2::average(b, trans(b)), -2, 2);
    nt2::table<T> pa = nt2::blas_band_h('U', a, 2);
    nt2::table<T> v = reshape(_(T(1), T(5)), 5, 1);
    nt2::table<T> y = reshape(_(T(0), T(4)), 5, 1);
    T alpha =  T(5);
    T beta =  T(3);
    nt2::table<T> z = y*beta+alpha*mtimes(a, v);
    blas_sbmv('U', alpha, boost::proto::value(pa), boost::proto::value(v), 1, beta, boost::proto::value(y), 1);
    NT2_TEST_ULP_EQUAL(y, z, 1);
  }
}
NT2_TEST_CASE_TPL(blas_sbmvl, NT2_REAL_TYPES )
{
  using nt2::blas_sbmv;
  using nt2::mtimes;
  using nt2::reshape;
  using nt2::_;
  using nt2::linspace;
  {
    nt2::table<T> b = reshape(_(T(1), T(25)), 5, 5);
    nt2::table<T> a =  nt2::band(nt2::average(b, trans(b)), -2, 2);;
    nt2::table<T> pa = nt2::blas_band_h('L', a, 2);
    NT2_DISPLAY(a);
    nt2::table<T> v = reshape(_(T(1), T(5)), 5, 1);
    nt2::table<T> y = reshape(_(T(0), T(4)), 5, 1);
    T alpha =  T(5);
    T beta =  T(3);
    nt2::table<T> zl = y*beta+alpha*mtimes(a, v);
    blas_sbmv('L', alpha, boost::proto::value(pa), boost::proto::value(v), 1, beta, boost::proto::value(y), 1);
    NT2_TEST_ULP_EQUAL(y, zl, 1);
  }
}
NT2_TEST_CASE_TPL(blas_sbmvu2, NT2_REAL_TYPES )
{
  using nt2::blas_sbmv;
  using nt2::mtimes;
  using nt2::reshape;
  using nt2::_;
  using nt2::linspace;
  using nt2::end_;
  {
    nt2::table<T> b = reshape(_(T(1), T(25)), 5, 5);
    nt2::table<T> a =  nt2::band(nt2::average(b, trans(b)), -2, 2);;
    nt2::table<T> pa = nt2::blas_band_h('U', a, 2);
    nt2::table<T> v = reshape(_(T(1), T(10)), 10, 1);
    nt2::table<T> y = reshape(_(T(0), T(9)), 10, 1);

    T alpha =  T(5);
    T beta =  T(3);
    nt2::table<T> z = y(_(1, 2, end_), _)*beta+alpha*mtimes(a, v(_(1, 2, end_), _));
    blas_sbmv('U', alpha, boost::proto::value(pa), boost::proto::value(v), 2, beta, boost::proto::value(y), 2);
    NT2_TEST_ULP_EQUAL(y(_(1, 2, end_), _), z, 1);
  }
}

NT2_TEST_CASE_TPL(blas_sbmvl2, NT2_REAL_TYPES )
{
  using nt2::blas_sbmv;
  using nt2::mtimes;
  using nt2::reshape;
  using nt2::_;
  using nt2::linspace;
  using nt2::end_;
  {
    nt2::table<T> b = reshape(_(T(1), T(25)), 5, 5);
    nt2::table<T> a = nt2::band(nt2::average(b, trans(b)), -2, 2);
    nt2::table<T> pa = nt2::blas_band_h('L', a, 2);
    nt2::table<T> v = reshape(_(T(1), T(10)), 10, 1);
    nt2::table<T> y = reshape(_(T(0), T(9)), 10, 1);

    T alpha =  T(5);
    T beta =  T(3);
    nt2::table<T> tz= y(_(1, 2, end_), _)*beta+alpha*mtimes(trans(a), v(_(1, 2, end_), _));
    blas_sbmv('L', alpha, boost::proto::value(pa), boost::proto::value(v), 2, beta, boost::proto::value(y), 2);
    NT2_TEST_ULP_EQUAL(y(_(1, 2, end_), _), tz, 1);
  }
}


