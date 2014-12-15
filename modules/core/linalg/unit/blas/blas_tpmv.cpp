//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/blas_tpmv.hpp>
#include <nt2/include/functions/blas_pack.hpp>
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
#include <nt2/include/functions/ctranspose.hpp>
#include <nt2/include/functions/average.hpp>
#include <nt2/include/functions/triu.hpp>
#include <nt2/include/functions/tri1u.hpp>
#include <nt2/include/functions/tril.hpp>
#include <nt2/include/functions/tri1l.hpp>



#include <nt2/table.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>


NT2_TEST_CASE_TPL(blas_tpmv, NT2_REAL_TYPES )
{
  using nt2::blas_tpmv;
  using nt2::mtimes;
  using nt2::reshape;
  using nt2::_;
  using nt2::linspace;
  {
    nt2::table<T> a = reshape(_(T(1), T(4)), 2, 2);
    nt2::table<T> pa = blas_pack('U', a);
    nt2::table<T> x = reshape(_(T(1), T(2)), 2, 1);
    nt2::table<T> x1 = x;
    nt2::table<T> z = mtimes(triu(a), x1);
    blas_tpmv('U', 'N', 'N', boost::proto::value(pa), boost::proto::value(x), 1);
    NT2_TEST_ULP_EQUAL(x, z, 1);

    x = x1;
    z = mtimes(tri1u(a), x1);
    blas_tpmv('U', 'N', 'U', boost::proto::value(pa), boost::proto::value(x), 1);
    NT2_TEST_ULP_EQUAL(x, z, 1);

    x = x1;
    z = mtimes(trans(triu(a)), x1);
    blas_tpmv('U', 'T', 'N', boost::proto::value(pa), boost::proto::value(x), 1);
    NT2_TEST_ULP_EQUAL(x, z, 1);

    x = x1;
    z = mtimes(trans(tri1u(a)), x1);
    blas_tpmv('U', 'T', 'U', boost::proto::value(pa), boost::proto::value(x), 1);
    NT2_TEST_ULP_EQUAL(x, z, 1);

    pa = blas_pack('L', a);
    x1 = x;
    z = mtimes(tril(a), x1);
    blas_tpmv('L', 'N', 'N', boost::proto::value(pa), boost::proto::value(x), 1);
    NT2_TEST_ULP_EQUAL(x, z, 1);

    x = x1;
    z = mtimes(tri1l(a), x1);
    blas_tpmv('L', 'N', 'U', boost::proto::value(pa), boost::proto::value(x), 1);
    NT2_TEST_ULP_EQUAL(x, z, 1);

    x = x1;
    z = mtimes(trans(tril(a)), x1);
    blas_tpmv('L', 'T', 'N', boost::proto::value(pa), boost::proto::value(x), 1);
    NT2_TEST_ULP_EQUAL(x, z, 1);

    x = x1;
    z = mtimes(trans(tri1l(a)), x1);
    blas_tpmv('L', 'T', 'U', boost::proto::value(pa), boost::proto::value(x), 1);
    NT2_TEST_ULP_EQUAL(x, z, 1);


  }

  {
    typedef std::complex<T> cT;
    nt2::table<cT> a = reshape(linspace(cT(1, 1), cT(4, 0), 4), 2, 2);
    nt2::table<cT> pa = blas_pack('U', a);
    nt2::table<cT> x = reshape(linspace(cT(0, 1), cT(2, 2), 2), 2, 1);
    nt2::table<cT> x1 = x;
    nt2::table<cT> z = mtimes(triu(a), x1);
    blas_tpmv('U', 'N', 'N', boost::proto::value(pa), boost::proto::value(x), 1);
    NT2_TEST_ULP_EQUAL(x, z, 1);

    x = x1;
    z = mtimes(tri1u(a), x1);
    blas_tpmv('U', 'N', 'U', boost::proto::value(pa), boost::proto::value(x), 1);
    NT2_TEST_ULP_EQUAL(x, z, 1);

    x = x1;
    z = mtimes(trans(triu(a)), x1);
    blas_tpmv('U', 'T', 'N', boost::proto::value(pa), boost::proto::value(x), 1);
    NT2_TEST_ULP_EQUAL(x, z, 1);

    x = x1;
    z = mtimes(trans(tri1u(a)), x1);
    blas_tpmv('U', 'T', 'U', boost::proto::value(pa), boost::proto::value(x), 1);
    NT2_TEST_ULP_EQUAL(x, z, 1);

    pa = blas_pack('L', a);
    x1 = x;
    z = mtimes(tril(a), x1);
    blas_tpmv('L', 'N', 'N', boost::proto::value(pa), boost::proto::value(x), 1);
    NT2_TEST_ULP_EQUAL(x, z, 1);

    x = x1;
    z = mtimes(tri1l(a), x1);
    blas_tpmv('L', 'N', 'U', boost::proto::value(pa), boost::proto::value(x), 1);
    NT2_TEST_ULP_EQUAL(x, z, 1);

    x = x1;
    z = mtimes(trans(tril(a)), x1);
    blas_tpmv('L', 'T', 'N', boost::proto::value(pa), boost::proto::value(x), 1);
    NT2_TEST_ULP_EQUAL(x, z, 1);

    x = x1;
    z = mtimes(trans(tri1l(a)), x1);
    blas_tpmv('L', 'T', 'U', boost::proto::value(pa), boost::proto::value(x), 1);
    NT2_TEST_ULP_EQUAL(x, z, 1);


  }
}


