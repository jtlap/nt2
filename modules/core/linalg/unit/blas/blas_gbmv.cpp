//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/blas_gbmv.hpp>
#include <nt2/include/functions/mtimes.hpp>
#include <nt2/include/functions/band.hpp>
#include <nt2/include/functions/blas_band.hpp>
#include <nt2/include/functions/blas_unband.hpp>
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
#include <nt2/include/functions/ctranspose.hpp>



#include <nt2/table.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>


// NT2_TEST_CASE_TPL(blas_gbmv, NT2_REAL_TYPES )
// {
//   using nt2::blas_gbmv;
//   using nt2::mtimes;
//   using nt2::reshape;
//   using nt2::_;
//   using nt2::linspace;
//   {
//     nt2::table<T> a = band(reshape(_(T(1), T(25)), 5, 5), -1, 2);
//     nt2::table<T> ua = blas_band(a, 1, 2);
//     nt2::table<T> v = reshape(_(T(1), T(5)), 5, 1);
//     nt2::table<T> y = reshape(_(T(0), T(4)), 5, 1);
//     T alpha =  T(2);
//     T beta =  T(3);
//     nt2::table<T> z = y*beta+alpha*mtimes(a, v);
//     blas_gbmv('N', 5, 1, alpha, boost::proto::value(ua), boost::proto::value(v), 1, beta, boost::proto::value(y), 1);
//     NT2_TEST_ULP_EQUAL(y, z, 1);
//   }
//   {
//     typedef std::complex<T> cT;
//     nt2::table<cT> a = band(reshape(linspace(cT(1, 1), cT(4, 0), 25), 5, 5), -1, 2);
//     nt2::table<cT> ua = blas_band(a, 1, 2);
//     nt2::table<cT> v = reshape(linspace(cT(0, 1), cT(2), 5), 5, 1);
//     nt2::table<cT> y = reshape(linspace(cT(0, 1), cT(1, 0), 5), 5, 1);
//     cT alpha =  cT(2, 1);
//     cT beta =  cT(1, 3);
//     nt2::table<cT> z = y*beta+alpha*mtimes(a, v);
//     blas_gbmv('N', 5, 1, alpha, boost::proto::value(ua), boost::proto::value(v), 1, beta, boost::proto::value(y), 1);
//     NT2_TEST_ULP_EQUAL(y, z, 1);
//   }
// }

NT2_TEST_CASE_TPL(blas_gbmv2, NT2_REAL_TYPES )
{
  using nt2::blas_gbmv;
  using nt2::mtimes;
  using nt2::reshape;
  using nt2::_;
  using nt2::linspace;
  using nt2::end_;
  {
    nt2::table<T> a = band(reshape(_(T(1), T(25)), 5, 5), -1, 2);
    nt2::table<T> ua = blas_band(a, 1, 2);
    nt2::table<T> v = reshape(_(T(1), T(10)), 10, 1);
    nt2::table<T> y = reshape(_(T(0), T(9)), 10, 1);

    T alpha =  T(2);
    T beta =  T(3);
    nt2::table<T> z = y(_(1, 2, end_), _)*beta+alpha*mtimes(a, v(_(1, 2, end_), _));
    blas_gbmv('N', 5, 1, alpha, boost::proto::value(ua), boost::proto::value(v), 2, beta, boost::proto::value(y), 2);
    NT2_TEST_ULP_EQUAL(y(_(1, 2, end_), _), z, 1);

    nt2::table<T> tz= y(_(1, 2, end_), _)*beta+alpha*mtimes(trans(a), v(_(1, 2, end_), _));
    blas_gbmv('T', 5, 1, alpha, boost::proto::value(ua), boost::proto::value(v), 2, beta, boost::proto::value(y), 2);
    NT2_TEST_ULP_EQUAL(y(_(1, 2, end_), _), tz, 1);

    nt2::table<T> ctz= y(_(1, 2, end_), _)*beta+alpha*mtimes(ctrans(a), v(_(1, 2, end_), _));
    blas_gbmv('C', 5, 1, alpha, boost::proto::value(ua), boost::proto::value(v), 2, beta, boost::proto::value(y), 2);
    NT2_TEST_ULP_EQUAL(y(_(1, 2, end_), _), ctz, 1);
  }
  {
    typedef std::complex<T> cT;
    nt2::table<cT> a = band(reshape(linspace(cT(1, 1), cT(4, 0), 25), 5, 5), -1, 2);
    nt2::table<cT> ua = blas_band(a, 1, 2);
    nt2::table<cT> v = reshape(linspace(cT(0, 1), cT(2), 10), 10, 1);
    nt2::table<cT> y = reshape(linspace(cT(0, 1), cT(1, 0), 10), 10, 1);
    cT alpha =  cT(2, 1);
    cT beta =  cT(1, 3);
    nt2::table<cT> z = y(_(1, 2, end_), _)*beta+alpha*mtimes(a, v(_(1, 2, end_), _));
    blas_gbmv('N', 5, 1, alpha, boost::proto::value(ua), boost::proto::value(v), 2, beta, boost::proto::value(y), 2);
    NT2_TEST_ULP_EQUAL(y(_(1, 2, end_), _), z, 3);

    nt2::table<cT> tz = y(_(1, 2, end_), _)*beta+alpha*mtimes(trans(a), v(_(1, 2, end_), _));
    blas_gbmv('T', 5, 1, alpha, boost::proto::value(ua), boost::proto::value(v), 2, beta, boost::proto::value(y), 2);
    NT2_TEST_ULP_EQUAL(y(_(1, 2, end_), _), tz, 3);

    nt2::table<cT> ctz = y(_(1, 2, end_), _)*beta+alpha*mtimes(ctrans(a), v(_(1, 2, end_), _));
    blas_gbmv('C', 5, 1, alpha, boost::proto::value(ua), boost::proto::value(v), 2, beta, boost::proto::value(y), 2);
    NT2_TEST_ULP_EQUAL(y(_(1, 2, end_), _), ctz, 3);
  }
}


