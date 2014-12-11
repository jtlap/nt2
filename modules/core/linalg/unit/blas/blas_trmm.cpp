//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/blas_trmm.hpp>
#include <nt2/include/functions/mtimes.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/functions/colon.hpp>
#include <nt2/include/functions/vertcat.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/functions/linspace.hpp>
#include <nt2/include/functions/plus.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/include/functions/resize.hpp>
#include <nt2/include/functions/mtimes.hpp>
#include <nt2/include/functions/multiplies.hpp>
#include <nt2/include/functions/plus.hpp>
#include <nt2/include/functions/linspace.hpp>
#include <nt2/include/functions/transpose.hpp>
#include <nt2/include/functions/ctranspose.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/triu.hpp>
#include <nt2/include/functions/tril.hpp>
#include <nt2/include/functions/tri1u.hpp>
#include <nt2/include/functions/tri1l.hpp>



#include <nt2/table.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>


NT2_TEST_CASE_TPL(blas_trmm, NT2_REAL_TYPES )
{
  using nt2::blas_trmm;
  using nt2::mtimes;
  using nt2::reshape;
  using nt2::_;
  using nt2::linspace;
  using nt2::height;
  using nt2::zeros;
  using nt2::of_size;
 {
   {//1
      nt2::table<T> a = reshape(_(T(1), T(9)), 3, 3);
      nt2::table<T> b = reshape(_(T(1), T(6)), 3, 2);
      T alpha = T(2);
      nt2::table<T> z = alpha*mtimes(triu(a), b);
      blas_trmm('L', 'U', 'N', 'N', alpha, boost::proto::value(a), boost::proto::value(b));
      NT2_TEST_ULP_EQUAL(b, z, 1);
    }
    {//2
      nt2::table<T> a = reshape(_(T(1), T(9)), 3, 3);
      nt2::table<T> b = reshape(_(T(1), T(6)), 3, 2);
      T alpha = T(2);
      nt2::table<T> z = alpha*mtimes(tri1u(a), b);
      blas_trmm('L', 'U', 'N', 'U', alpha, boost::proto::value(a), boost::proto::value(b));
      NT2_TEST_ULP_EQUAL(b, z, 1);
    }
    {//3
      nt2::table<T> a = reshape(_(T(1), T(9)), 3, 3);
      nt2::table<T> b = reshape(_(T(1), T(6)), 3, 2);
      T alpha = T(2);
      nt2::table<T> z = alpha*mtimes(tril(a), b);
      blas_trmm('L', 'L', 'N', 'N', alpha, boost::proto::value(a), boost::proto::value(b));
      NT2_TEST_ULP_EQUAL(b, z, 1);
    }
    {//4
      nt2::table<T> a = reshape(_(T(1), T(9)), 3, 3);
      nt2::table<T> b = reshape(_(T(1), T(6)), 3, 2);
      T alpha = T(2);
      nt2::table<T> z = alpha*mtimes(tri1l(a), b);
      blas_trmm('L', 'L', 'N', 'U', alpha, boost::proto::value(a), boost::proto::value(b));
      NT2_TEST_ULP_EQUAL(b, z, 1);
    }

    {//5
      nt2::table<T> a = reshape(_(T(1), T(9)), 3, 3);
      nt2::table<T> b = reshape(_(T(1), T(6)), 2, 3);
      T alpha = T(2);
      nt2::table<T> z = alpha*mtimes(b, triu(a));
      blas_trmm('R', 'U', 'N', 'N', alpha, boost::proto::value(a), boost::proto::value(b));
      NT2_TEST_ULP_EQUAL(b, z, 1);
    }
    {//6
      nt2::table<T> a = reshape(_(T(1), T(9)), 3, 3);
      nt2::table<T> b = reshape(_(T(1), T(6)), 2, 3);
      T alpha = T(2);
      nt2::table<T> z = alpha*mtimes(b, tri1u(a));
      blas_trmm('R', 'U', 'N', 'U', alpha, boost::proto::value(a), boost::proto::value(b));
      NT2_TEST_ULP_EQUAL(b, z, 1);
    }
    {//7
      nt2::table<T> a = reshape(_(T(1), T(9)), 3, 3);
      nt2::table<T> b = reshape(_(T(1), T(6)), 2, 3);
      T alpha = T(2);
      nt2::table<T> z = alpha*mtimes(b, tril(a));
      blas_trmm('R', 'L', 'N', 'N', alpha, boost::proto::value(a), boost::proto::value(b));
      NT2_TEST_ULP_EQUAL(b, z, 1);
    }
    {//8
      nt2::table<T> a = reshape(_(T(1), T(9)), 3, 3);
      nt2::table<T> b = reshape(_(T(1), T(6)), 2, 3);
      T alpha = T(2);
      nt2::table<T> z = alpha*mtimes(b, tri1l(a));
      blas_trmm('R', 'L', 'N', 'U', alpha, boost::proto::value(a), boost::proto::value(b));
      NT2_TEST_ULP_EQUAL(b, z, 1);
    }

    {
      nt2::table<T> a = reshape(_(T(1), T(9)), 3, 3);
      nt2::table<T> b = reshape(_(T(1), T(6)), 3, 2);
      T alpha = T(2);
      nt2::table<T> z = alpha*mtimes(trans(triu(a)), b);
      blas_trmm('L', 'U', 'T', 'N', alpha, boost::proto::value(a), boost::proto::value(b));
      NT2_TEST_ULP_EQUAL(b, z, 1);
    }
    {
      nt2::table<T> a = reshape(_(T(1), T(9)), 3, 3);
      nt2::table<T> b = reshape(_(T(1), T(6)), 3, 2);
      T alpha = T(2);
      nt2::table<T> z = alpha*mtimes(trans(tri1u(a)), b);
      blas_trmm('L', 'U', 'T', 'U', alpha, boost::proto::value(a), boost::proto::value(b));
      NT2_TEST_ULP_EQUAL(b, z, 1);
    }
    {
      nt2::table<T> a = reshape(_(T(1), T(9)), 3, 3);
      nt2::table<T> b = reshape(_(T(1), T(6)), 3, 2);
      T alpha = T(2);
      nt2::table<T> z = alpha*mtimes(trans(tril(a)), b);
      blas_trmm('L', 'L', 'T', 'N', alpha, boost::proto::value(a), boost::proto::value(b));
      NT2_TEST_ULP_EQUAL(b, z, 1);
    }
    {
      nt2::table<T> a = reshape(_(T(1), T(9)), 3, 3);
      nt2::table<T> b = reshape(_(T(1), T(6)), 3, 2);
      T alpha = T(2);
      nt2::table<T> z = alpha*mtimes(trans(tri1l(a)), b);
      blas_trmm('L', 'L', 'T', 'U', alpha, boost::proto::value(a), boost::proto::value(b));
      NT2_TEST_ULP_EQUAL(b, z, 1);
    }

    {
      nt2::table<T> a = reshape(_(T(1), T(9)), 3, 3);
      nt2::table<T> b = reshape(_(T(1), T(6)), 2, 3);
      T alpha = T(2);
      nt2::table<T> z = alpha*mtimes(b, trans(triu(a)));
      blas_trmm('R', 'U', 'T', 'N', alpha, boost::proto::value(a), boost::proto::value(b));
      NT2_TEST_ULP_EQUAL(b, z, 1);
    }
    {
      nt2::table<T> a = reshape(_(T(1), T(9)), 3, 3);
      nt2::table<T> b = reshape(_(T(1), T(6)), 2, 3);
      T alpha = T(2);
      nt2::table<T> z = alpha*mtimes(b, trans(tri1u(a)));
      blas_trmm('R', 'U', 'T', 'U', alpha, boost::proto::value(a), boost::proto::value(b));
      NT2_TEST_ULP_EQUAL(b, z, 1);
    }
    {
      nt2::table<T> a = reshape(_(T(1), T(9)), 3, 3);
      nt2::table<T> b = reshape(_(T(1), T(6)), 2, 3);
      T alpha = T(2);
      nt2::table<T> z = alpha*mtimes(b, trans(tril(a)));
      blas_trmm('R', 'L', 'T', 'N', alpha, boost::proto::value(a), boost::proto::value(b));
      NT2_TEST_ULP_EQUAL(b, z, 1);
    }
    {
      nt2::table<T> a = reshape(_(T(1), T(9)), 3, 3);
      nt2::table<T> b = reshape(_(T(1), T(6)), 2, 3);
      T alpha = T(2);
      nt2::table<T> z = alpha*mtimes(b, trans(tri1l(a)));
      blas_trmm('R', 'L', 'T', 'U', alpha, boost::proto::value(a), boost::proto::value(b));
      NT2_TEST_ULP_EQUAL(b, z, 1);
    }
   }
}


NT2_TEST_CASE_TPL(blas_trmmc, NT2_REAL_TYPES )
{
  using nt2::blas_trmm;
  using nt2::mtimes;
  using nt2::reshape;
  using nt2::_;
  using nt2::linspace;
  using nt2::height;
  using nt2::zeros;
  using nt2::of_size;
 {
   typedef std::complex<T> cT;
   {//1
     nt2::table<cT> a = reshape(linspace(cT(1, 1), cT(4, 0), 9), 3, 3);
      nt2::table<cT> b = reshape(_(T(1), T(6)), 3, 2);
      cT alpha = cT(2,1);
      nt2::table<cT> z = alpha*mtimes(triu(a), b);
      blas_trmm('L', 'U', 'N', 'N', alpha, boost::proto::value(a), boost::proto::value(b));
      NT2_TEST_ULP_EQUAL(b, z, 1);
    }
    {//2
     nt2::table<cT> a = reshape(linspace(cT(1, 1), cT(4, 0), 9), 3, 3);
      nt2::table<cT> b = reshape(_(T(1), T(6)), 3, 2);
      cT alpha = cT(2,1);
      nt2::table<cT> z = alpha*mtimes(tri1u(a), b);
      blas_trmm('L', 'U', 'N', 'U', alpha, boost::proto::value(a), boost::proto::value(b));
      NT2_TEST_ULP_EQUAL(b, z, 1);
    }
    {//3
     nt2::table<cT> a = reshape(linspace(cT(1, 1), cT(4, 0), 9), 3, 3);
      nt2::table<cT> b = reshape(_(T(1), T(6)), 3, 2);
      cT alpha = cT(2,1);
      nt2::table<cT> z = alpha*mtimes(tril(a), b);
      blas_trmm('L', 'L', 'N', 'N', alpha, boost::proto::value(a), boost::proto::value(b));
      NT2_TEST_ULP_EQUAL(b, z, 1);
    }
    {//4
     nt2::table<cT> a = reshape(linspace(cT(1, 1), cT(4, 0), 9), 3, 3);
      nt2::table<cT> b = reshape(_(T(1), T(6)), 3, 2);
      cT alpha = cT(2,1);
      nt2::table<cT> z = alpha*mtimes(tri1l(a), b);
      blas_trmm('L', 'L', 'N', 'U', alpha, boost::proto::value(a), boost::proto::value(b));
      NT2_TEST_ULP_EQUAL(b, z, 1);
    }

    {//5
     nt2::table<cT> a = reshape(linspace(cT(1, 1), cT(4, 0), 9), 3, 3);
      nt2::table<cT> b = reshape(_(T(1), T(6)), 2, 3);
      cT alpha = cT(2,1);
      nt2::table<cT> z = alpha*mtimes(b, triu(a));
      blas_trmm('R', 'U', 'N', 'N', alpha, boost::proto::value(a), boost::proto::value(b));
      NT2_TEST_ULP_EQUAL(b, z, 1);
    }
    {//6
     nt2::table<cT> a = reshape(linspace(cT(1, 1), cT(4, 0), 9), 3, 3);
      nt2::table<cT> b = reshape(_(T(1), T(6)), 2, 3);
      cT alpha = cT(2,1);
      nt2::table<cT> z = alpha*mtimes(b, tri1u(a));
      blas_trmm('R', 'U', 'N', 'U', alpha, boost::proto::value(a), boost::proto::value(b));
      NT2_TEST_ULP_EQUAL(b, z, 1);
    }
    {//7
     nt2::table<cT> a = reshape(linspace(cT(1, 1), cT(4, 0), 9), 3, 3);
      nt2::table<cT> b = reshape(_(T(1), T(6)), 2, 3);
      cT alpha = cT(2,1);
      nt2::table<cT> z = alpha*mtimes(b, tril(a));
      blas_trmm('R', 'L', 'N', 'N', alpha, boost::proto::value(a), boost::proto::value(b));
      NT2_TEST_ULP_EQUAL(b, z, 1);
    }
    {//8
     nt2::table<cT> a = reshape(linspace(cT(1, 1), cT(4, 0), 9), 3, 3);
      nt2::table<cT> b = reshape(_(T(1), T(6)), 2, 3);
      cT alpha = cT(2,1);
      nt2::table<cT> z = alpha*mtimes(b, tri1l(a));
      blas_trmm('R', 'L', 'N', 'U', alpha, boost::proto::value(a), boost::proto::value(b));
      NT2_TEST_ULP_EQUAL(b, z, 1);
    }

    {
     nt2::table<cT> a = reshape(linspace(cT(1, 1), cT(4, 0), 9), 3, 3);
      nt2::table<cT> b = reshape(_(T(1), T(6)), 3, 2);
      cT alpha = cT(2,1);
      nt2::table<cT> z = alpha*mtimes(ctrans(triu(a)), b);
      blas_trmm('L', 'U', 'C', 'N', alpha, boost::proto::value(a), boost::proto::value(b));
      NT2_TEST_ULP_EQUAL(b, z, 1);
    }
    {
     nt2::table<cT> a = reshape(linspace(cT(1, 1), cT(4, 0), 9), 3, 3);
      nt2::table<cT> b = reshape(_(T(1), T(6)), 3, 2);
      cT alpha = cT(2,1);
      nt2::table<cT> z = alpha*mtimes(ctrans(tri1u(a)), b);
      blas_trmm('L', 'U', 'C', 'U', alpha, boost::proto::value(a), boost::proto::value(b));
      NT2_TEST_ULP_EQUAL(b, z, 1);
    }
    {
     nt2::table<cT> a = reshape(linspace(cT(1, 1), cT(4, 0), 9), 3, 3);
      nt2::table<cT> b = reshape(_(T(1), T(6)), 3, 2);
      cT alpha = cT(2,1);
      nt2::table<cT> z = alpha*mtimes(ctrans(tril(a)), b);
      blas_trmm('L', 'L', 'C', 'N', alpha, boost::proto::value(a), boost::proto::value(b));
      NT2_TEST_ULP_EQUAL(b, z, 1);
    }
    {
     nt2::table<cT> a = reshape(linspace(cT(1, 1), cT(4, 0), 9), 3, 3);
      nt2::table<cT> b = reshape(_(T(1), T(6)), 3, 2);
      cT alpha = cT(2,1);
      nt2::table<cT> z = alpha*mtimes(ctrans(tri1l(a)), b);
      blas_trmm('L', 'L', 'C', 'U', alpha, boost::proto::value(a), boost::proto::value(b));
      NT2_TEST_ULP_EQUAL(b, z, 1);
    }

    {
     nt2::table<cT> a = reshape(linspace(cT(1, 1), cT(4, 0), 9), 3, 3);
      nt2::table<cT> b = reshape(_(T(1), T(6)), 2, 3);
      cT alpha = cT(2,1);
      nt2::table<cT> z = alpha*mtimes(b, ctrans(triu(a)));
      blas_trmm('R', 'U', 'C', 'N', alpha, boost::proto::value(a), boost::proto::value(b));
      NT2_TEST_ULP_EQUAL(b, z, 1);
    }
    {
      nt2::table<cT> a = reshape(linspace(cT(1, 1), cT(4, 0), 9), 3, 3);
      nt2::table<cT> b = reshape(_(T(1), T(6)), 2, 3);
      cT alpha = cT(2,1);
      nt2::table<cT> z = alpha*mtimes(b, ctrans(tri1u(a)));
      blas_trmm('R', 'U', 'C', 'U', alpha, boost::proto::value(a), boost::proto::value(b));
      NT2_TEST_ULP_EQUAL(b, z, 1);
    }
    {
     nt2::table<cT> a = reshape(linspace(cT(1, 1), cT(4, 0), 9), 3, 3);
      nt2::table<cT> b = reshape(_(T(1), T(6)), 2, 3);
      cT alpha = cT(2,1);
      nt2::table<cT> z = alpha*mtimes(b, ctrans(tril(a)));
      blas_trmm('R', 'L', 'C', 'N', alpha, boost::proto::value(a), boost::proto::value(b));
      NT2_TEST_ULP_EQUAL(b, z, 1);
    }
    {
     nt2::table<cT> a = reshape(linspace(cT(1, 1), cT(4, 0), 9), 3, 3);
      nt2::table<cT> b = reshape(_(T(1), T(6)), 2, 3);
      cT alpha = cT(2,1);
      nt2::table<cT> z = alpha*mtimes(b, ctrans(tri1l(a)));
      blas_trmm('R', 'L', 'C', 'U', alpha, boost::proto::value(a), boost::proto::value(b));
      NT2_TEST_ULP_EQUAL(b, z, 1);
    }
   }
}
