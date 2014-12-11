//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/blas_trsm.hpp>
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
#include <nt2/include/functions/linsolve.hpp>



#include <nt2/table.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>


NT2_TEST_CASE_TPL(blas_trsm, NT2_REAL_TYPES )
{
  using nt2::blas_trsm;
  using nt2::linsolve;
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
      nt2::table<T> z = linsolve(triu(a), alpha*b);
      blas_trsm('L', 'U', 'N', 'N', alpha, boost::proto::value(a), boost::proto::value(b));
      NT2_TEST_ULP_EQUAL(b, z, 3.5);
    }
    {//2
      nt2::table<T> a = reshape(_(T(1), T(9)), 3, 3);
      nt2::table<T> b = reshape(_(T(1), T(6)), 3, 2);
      T alpha = T(2);
      nt2::table<T> z = linsolve(tri1u(a), alpha*b);
      blas_trsm('L', 'U', 'N', 'U', alpha, boost::proto::value(a), boost::proto::value(b));
      NT2_TEST_ULP_EQUAL(b, z, 3.5);
    }
    {//3
      nt2::table<T> a = reshape(_(T(1), T(9)), 3, 3);
      nt2::table<T> b = reshape(_(T(1), T(6)), 3, 2);
      T alpha = T(2);
      nt2::table<T> z = linsolve(tril(a), alpha*b);
      blas_trsm('L', 'L', 'N', 'N', alpha, boost::proto::value(a), boost::proto::value(b));
      NT2_TEST_ULP_EQUAL(b, z, 3.5);
    }
    {//4
      nt2::table<T> a = reshape(_(T(1), T(9)), 3, 3);
      nt2::table<T> b = reshape(_(T(1), T(6)), 3, 2);
      T alpha = T(2);
      nt2::table<T> z = linsolve(tri1l(a), alpha*b);
      blas_trsm('L', 'L', 'N', 'U', alpha, boost::proto::value(a), boost::proto::value(b));
      NT2_TEST_ULP_EQUAL(b, z, 3.5);
    }

    {//5
      nt2::table<T> a = reshape(_(T(1), T(9)), 3, 3);
      nt2::table<T> b = reshape(_(T(1), T(6)), 2, 3);
      T alpha = T(2);
      nt2::table<T> z = linsolve(trans(triu(a)), trans(alpha*b));
      blas_trsm('R', 'U', 'N', 'N', alpha, boost::proto::value(a), boost::proto::value(b));
      NT2_TEST_ULP_EQUAL(b, trans(z), 10);
    }
    {//6
      nt2::table<T> a = reshape(_(T(1), T(9)), 3, 3);
      nt2::table<T> b = reshape(_(T(1), T(6)), 2, 3);
      T alpha = T(2);
      nt2::table<T> z = trans(linsolve(trans(tri1u(a)), trans(alpha*b)));
      blas_trsm('R', 'U', 'N', 'U', alpha, boost::proto::value(a), boost::proto::value(b));
      NT2_TEST_ULP_EQUAL(b, z, 3.5);
    }
    {//7
      nt2::table<T> a = reshape(_(T(1), T(9)), 3, 3);
      nt2::table<T> b = reshape(_(T(1), T(6)), 2, 3);
      T alpha = T(2);
      nt2::table<T> z = trans(linsolve(trans(tril(a)), trans(alpha*b)));
      blas_trsm('R', 'L', 'N', 'N', alpha, boost::proto::value(a), boost::proto::value(b));
      NT2_TEST_ULP_EQUAL(b, z, 3.5);
    }
    {//8
      nt2::table<T> a = reshape(_(T(1), T(9)), 3, 3);
      nt2::table<T> b = reshape(_(T(1), T(6)), 2, 3);
      T alpha = T(2);
      nt2::table<T> z = trans(linsolve(trans(tri1l(a)), trans(alpha*b)));
      blas_trsm('R', 'L', 'N', 'U', alpha, boost::proto::value(a), boost::proto::value(b));
      NT2_TEST_ULP_EQUAL(b, z, 3.5);
    }

    {//9
      nt2::table<T> a = reshape(_(T(1), T(9)), 3, 3);
      nt2::table<T> b = reshape(_(T(1), T(6)), 3, 2);
      T alpha = T(2);
      nt2::table<T> z = linsolve(trans(triu(a)), alpha*b);
      blas_trsm('L', 'U', 'T', 'N', alpha, boost::proto::value(a), boost::proto::value(b));
      NT2_TEST_ULP_EQUAL(b, z, 3.5);
    }
    {//10
      nt2::table<T> a = reshape(_(T(1), T(9)), 3, 3);
      nt2::table<T> b = reshape(_(T(1), T(6)), 3, 2);
      T alpha = T(2);
      nt2::table<T> z = linsolve(trans(tri1u(a)),  alpha*b);
      blas_trsm('L', 'U', 'T', 'U', alpha, boost::proto::value(a), boost::proto::value(b));
      NT2_TEST_ULP_EQUAL(b, z, 3.5);
    }
    {//11
      nt2::table<T> a = reshape(_(T(1), T(9)), 3, 3);
      nt2::table<T> b = reshape(_(T(1), T(6)), 3, 2);
      T alpha = T(2);
      nt2::table<T> z = linsolve(trans(tril(a)), alpha*b);
      blas_trsm('L', 'L', 'T', 'N', alpha, boost::proto::value(a), boost::proto::value(b));
      NT2_TEST_ULP_EQUAL(b, z, 3.5);
    }
    {//12
      nt2::table<T> a = reshape(_(T(1), T(9)), 3, 3);
      nt2::table<T> b = reshape(_(T(1), T(6)), 3, 2);
      T alpha = T(2);
      nt2::table<T> z = linsolve(trans(tri1l(a)), alpha*b);
      blas_trsm('L', 'L', 'T', 'U', alpha, boost::proto::value(a), boost::proto::value(b));
      NT2_TEST_ULP_EQUAL(b, z, 3.5);
    }

    {//13
      nt2::table<T> a = reshape(_(T(1), T(9)), 3, 3);
      nt2::table<T> b = reshape(_(T(1), T(6)), 2, 3);
      T alpha = T(2);
      nt2::table<T> z = trans(linsolve(triu(a), trans(alpha*b)));
      blas_trsm('R', 'U', 'T', 'N', alpha, boost::proto::value(a), boost::proto::value(b));
      NT2_TEST_ULP_EQUAL(b, z, 3.5);
    }
    {//14
      nt2::table<T> a = reshape(_(T(1), T(9)), 3, 3);
      nt2::table<T> b = reshape(_(T(1), T(6)), 2, 3);
      T alpha = T(2);
      nt2::table<T> z = trans(linsolve(tri1u(a), trans(alpha*b)));
      blas_trsm('R', 'U', 'T', 'U', alpha, boost::proto::value(a), boost::proto::value(b));
      NT2_TEST_ULP_EQUAL(b, z, 3.5);
    }
    {//15
      nt2::table<T> a = reshape(_(T(1), T(9)), 3, 3);
      nt2::table<T> b = reshape(_(T(1), T(6)), 2, 3);
      T alpha = T(2);
      nt2::table<T> z = trans(linsolve(tril(a), trans(alpha*b)));
      blas_trsm('R', 'L', 'T', 'N', alpha, boost::proto::value(a), boost::proto::value(b));
      NT2_TEST_ULP_EQUAL(b, z, 3.5);
    }
    {//16
      nt2::table<T> a = reshape(_(T(1), T(9)), 3, 3);
      nt2::table<T> b = reshape(_(T(1), T(6)), 2, 3);
      T alpha = T(2);
      nt2::table<T> z = trans(linsolve(tri1l(a), trans(alpha*b)));
      blas_trsm('R', 'L', 'T', 'U', alpha, boost::proto::value(a), boost::proto::value(b));
      NT2_TEST_ULP_EQUAL(b, z, 3.5);
    }
   }
}

NT2_TEST_CASE_TPL(blas_trsmc, NT2_REAL_TYPES )
{
  using nt2::blas_trsm;
  using nt2::linsolve;
  using nt2::reshape;
  using nt2::_;
  using nt2::linspace;
  using nt2::height;
  using nt2::zeros;
  using nt2::of_size;
  {
    typedef std::complex<T> cT;
    {//1
      nt2::table<cT> a = reshape(_(T(1), T(9)), 3, 3);
      nt2::table<cT> b = reshape(_(T(1), T(6)), 3, 2);
      cT alpha = cT(2, 3);
      nt2::table<cT> z = linsolve(triu(a), alpha*b);
      blas_trsm('L', 'U', 'N', 'N', alpha, boost::proto::value(a), boost::proto::value(b));
      NT2_TEST_ULP_EQUAL(b, z, 3.5);
    }
    {//2
      nt2::table<cT> a = reshape(_(T(1), T(9)), 3, 3);
      nt2::table<cT> b = reshape(_(T(1), T(6)), 3, 2);
      cT alpha = cT(2, 3);
      nt2::table<cT> z = linsolve(tri1u(a), alpha*b);
      blas_trsm('L', 'U', 'N', 'U', alpha, boost::proto::value(a), boost::proto::value(b));
      NT2_TEST_ULP_EQUAL(b, z, 3.5);
    }
    {//3
      nt2::table<cT> a = reshape(_(T(1), T(9)), 3, 3);
      nt2::table<cT> b = reshape(_(T(1), T(6)), 3, 2);
      cT alpha = cT(2, 3);
      nt2::table<cT> z = linsolve(tril(a), alpha*b);
      blas_trsm('L', 'L', 'N', 'N', alpha, boost::proto::value(a), boost::proto::value(b));
      NT2_TEST_ULP_EQUAL(b, z, 3.5);
    }
    {//4
      nt2::table<cT> a = reshape(_(T(1), T(9)), 3, 3);
      nt2::table<cT> b = reshape(_(T(1), T(6)), 3, 2);
      cT alpha = cT(2, 3);
      nt2::table<cT> z = linsolve(tri1l(a), alpha*b);
      blas_trsm('L', 'L', 'N', 'U', alpha, boost::proto::value(a), boost::proto::value(b));
      NT2_TEST_ULP_EQUAL(b, z, 3.5);
    }

    {//5
      nt2::table<cT> a = reshape(_(T(1), T(9)), 3, 3);
      nt2::table<cT> b = reshape(_(T(1), T(6)), 2, 3);
      cT alpha = cT(2, 3);
      nt2::table<cT> z = linsolve(ctrans(triu(a)), ctrans(alpha*b));
      blas_trsm('R', 'U', 'N', 'N', alpha, boost::proto::value(a), boost::proto::value(b));
      NT2_TEST_ULP_EQUAL(b, ctrans(z), 10);
    }
    {//6
      nt2::table<cT> a = reshape(_(T(1), T(9)), 3, 3);
      nt2::table<cT> b = reshape(_(T(1), T(6)), 2, 3);
      cT alpha = cT(2, 3);
      nt2::table<cT> z = ctrans(linsolve(ctrans(tri1u(a)), ctrans(alpha*b)));
      blas_trsm('R', 'U', 'N', 'U', alpha, boost::proto::value(a), boost::proto::value(b));
      NT2_TEST_ULP_EQUAL(b, z, 3.5);
    }
    {//7
      nt2::table<cT> a = reshape(_(T(1), T(9)), 3, 3);
      nt2::table<cT> b = reshape(_(T(1), T(6)), 2, 3);
      cT alpha = cT(2, 3);
      nt2::table<cT> z = ctrans(linsolve(ctrans(tril(a)), ctrans(alpha*b)));
      blas_trsm('R', 'L', 'N', 'N', alpha, boost::proto::value(a), boost::proto::value(b));
      NT2_TEST_ULP_EQUAL(b, z, 3.5);
    }
    {//8
      nt2::table<cT> a = reshape(_(T(1), T(9)), 3, 3);
      nt2::table<cT> b = reshape(_(T(1), T(6)), 2, 3);
      cT alpha = cT(2, 3);
      nt2::table<cT> z = ctrans(linsolve(ctrans(tri1l(a)), ctrans(alpha*b)));
      blas_trsm('R', 'L', 'N', 'U', alpha, boost::proto::value(a), boost::proto::value(b));
      NT2_TEST_ULP_EQUAL(b, z, 3.5);
    }

    {//9
      nt2::table<cT> a = reshape(_(T(1), T(9)), 3, 3);
      nt2::table<cT> b = reshape(_(T(1), T(6)), 3, 2);
      cT alpha = cT(2, 3);
      nt2::table<cT> z = linsolve(ctrans(triu(a)), alpha*b);
      blas_trsm('L', 'U', 'C', 'N', alpha, boost::proto::value(a), boost::proto::value(b));
      NT2_TEST_ULP_EQUAL(b, z, 3.5);
    }
    {//10
      nt2::table<cT> a = reshape(_(T(1), T(9)), 3, 3);
      nt2::table<cT> b = reshape(_(T(1), T(6)), 3, 2);
      cT alpha = cT(2, 3);
      nt2::table<cT> z = linsolve(ctrans(tri1u(a)),  alpha*b);
      blas_trsm('L', 'U', 'C', 'U', alpha, boost::proto::value(a), boost::proto::value(b));
      NT2_TEST_ULP_EQUAL(b, z, 3.5);
    }
    {//11
      nt2::table<cT> a = reshape(_(T(1), T(9)), 3, 3);
      nt2::table<cT> b = reshape(_(T(1), T(6)), 3, 2);
      cT alpha = cT(2, 3);
      nt2::table<cT> z = linsolve(ctrans(tril(a)), alpha*b);
      blas_trsm('L', 'L', 'C', 'N', alpha, boost::proto::value(a), boost::proto::value(b));
      NT2_TEST_ULP_EQUAL(b, z, 3.5);
    }
    {//12
      nt2::table<cT> a = reshape(_(T(1), T(9)), 3, 3);
      nt2::table<cT> b = reshape(_(T(1), T(6)), 3, 2);
      cT alpha = cT(2, 3);
      nt2::table<cT> z = linsolve(ctrans(tri1l(a)), alpha*b);
      blas_trsm('L', 'L', 'C', 'U', alpha, boost::proto::value(a), boost::proto::value(b));
      NT2_TEST_ULP_EQUAL(b, z, 3.5);
    }

    {//13
      nt2::table<cT> a = reshape(_(T(1), T(9)), 3, 3);
      nt2::table<cT> b = reshape(_(T(1), T(6)), 2, 3);
      cT alpha = cT(2, 3);
      nt2::table<cT> z = ctrans(linsolve(triu(a), ctrans(alpha*b)));
      blas_trsm('R', 'U', 'C', 'N', alpha, boost::proto::value(a), boost::proto::value(b));
      NT2_TEST_ULP_EQUAL(b, z, 3.5);
    }
    {//14
      nt2::table<cT> a = reshape(_(T(1), T(9)), 3, 3);
      nt2::table<cT> b = reshape(_(T(1), T(6)), 2, 3);
      cT alpha = cT(2, 3);
      nt2::table<cT> z = ctrans(linsolve(tri1u(a), ctrans(alpha*b)));
      blas_trsm('R', 'U', 'C', 'U', alpha, boost::proto::value(a), boost::proto::value(b));
      NT2_TEST_ULP_EQUAL(b, z, 3.5);
    }
    {//15
      nt2::table<cT> a = reshape(_(T(1), T(9)), 3, 3);
      nt2::table<cT> b = reshape(_(T(1), T(6)), 2, 3);
      cT alpha = cT(2, 3);
      nt2::table<cT> z = ctrans(linsolve(tril(a), ctrans(alpha*b)));
      blas_trsm('R', 'L', 'C', 'N', alpha, boost::proto::value(a), boost::proto::value(b));
      NT2_TEST_ULP_EQUAL(b, z, 3.5);
    }
    {//16
      nt2::table<cT> a = reshape(_(T(1), T(9)), 3, 3);
      nt2::table<cT> b = reshape(_(T(1), T(6)), 2, 3);
      cT alpha = cT(2, 3);
      nt2::table<cT> z = ctrans(linsolve(tri1l(a), ctrans(alpha*b)));
      blas_trsm('R', 'L', 'C', 'U', alpha, boost::proto::value(a), boost::proto::value(b));
      NT2_TEST_ULP_EQUAL(b, z, 3.5);
    }
   }
}
