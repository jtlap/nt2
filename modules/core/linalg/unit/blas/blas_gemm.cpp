//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/blas_gemm.hpp>
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



#include <nt2/table.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>


NT2_TEST_CASE_TPL(blas_gemm, NT2_REAL_TYPES )
{
  using nt2::blas_gemm;
  using nt2::mtimes;
  using nt2::reshape;
  using nt2::_;
  using nt2::linspace;
  using nt2::height;
  using nt2::zeros;
  using nt2::of_size;
 {
    {
      nt2::table<T> a = reshape(_(T(1), T(6)), 2, 3);
      nt2::table<T> b = reshape(_(T(1), T(6)), 3, 2);
      nt2::table<T> c = zeros(of_size(2, 2), nt2::meta::as_<T>()); //reshape(_(T(0), T(3)), 2, 2);
      T alpha = T(2);
      T beta =  T(3);
      nt2::table<T> z = c*beta+alpha*mtimes(a, b);
      blas_gemm('N', 'N', alpha, boost::proto::value(a), boost::proto::value(b), beta, boost::proto::value(c));
      NT2_TEST_ULP_EQUAL(c, z, 1);
    }
    {
      nt2::table<T> a = reshape(_(T(1), T(6)), 2, 3);
      nt2::table<T> b = reshape(_(T(1), T(6)), 2, 3);
      nt2::table<T> c = zeros(of_size(2, 2), nt2::meta::as_<T>());//reshape(_(T(0), T(3)), 2, 2);
      T alpha = T(2);
      T beta =  T(3);
      nt2::table<T> z = c*beta+alpha*mtimes(a, trans(b));
      blas_gemm('N', 'T', alpha, boost::proto::value(a), boost::proto::value(b), beta, boost::proto::value(c));
      NT2_TEST_ULP_EQUAL(c, z, 1);
    }
    {
      nt2::table<T> a = reshape(_(T(1), T(6)), 2, 3);
      nt2::table<T> b = reshape(_(T(1), T(6)), 2, 3);
      nt2::table<T> c = reshape(_(T(0), T(8)), 3, 3);
      T alpha = T(2);
      T beta =  T(3);
      nt2::table<T> z = c*beta+alpha*mtimes(trans(a), b);
      blas_gemm('T', 'N', alpha, boost::proto::value(a), boost::proto::value(b), beta, boost::proto::value(c));
      NT2_TEST_ULP_EQUAL(c, z, 1);
    }

    {
      nt2::table<T> a = reshape(_(T(1), T(6)), 2, 3);
      nt2::table<T> b = reshape(_(T(1), T(6)), 3, 2);
      nt2::table<T> c = reshape(_(T(0), T(8)), 3, 3);
      T alpha = T(2);
      T beta =  T(3);
      nt2::table<T> z = c*beta+alpha*mtimes(trans(a), trans(b));
      blas_gemm('T', 'T', alpha, boost::proto::value(a), boost::proto::value(b), beta, boost::proto::value(c));
      NT2_TEST_ULP_EQUAL(c, z, 1);
    }


//   {
//     typedef std::complex<T> cT;
//     nt2::table<cT> a = reshape(linspace(cT(1, 1), cT(4, 0), 4), 2, 2);
//     nt2::table<cT> v = reshape(linspace(cT(0, 1), cT(2), 2), 2, 1);
//     nt2::table<cT> y = reshape(linspace(cT(0, 1), cT(1, 0), 2), 2, 1);
//     cT alpha =  cT(2, 1);
//     cT beta =  cT(1, 3);
//     nt2::table<cT> z = y*beta+alpha*mtimes(a, v);
//     blas_gemm('N', alpha, boost::proto::value(a), boost::proto::value(v), 1, beta, boost::proto::value(y), 1);
//     NT2_TEST_ULP_EQUAL(y, z, 1);
//   }
  }
}

NT2_TEST_CASE_TPL(blas_gemmc, NT2_REAL_TYPES )
{
  using nt2::blas_gemm;
  using nt2::mtimes;
  using nt2::reshape;
  using nt2::_;
  using nt2::linspace;
  using nt2::height;
  using nt2::zeros;
  using nt2::of_size;
 {
   typedef std::complex<T> cT;
   {
     nt2::table<cT> a = reshape(linspace(cT(1, 1), cT(4, 0), 6), 2, 3);
     nt2::table<cT> b = reshape(linspace(cT(0, 1), cT(2),6), 3, 2);
     nt2::table<cT> c = reshape(linspace(cT(0, 1), cT(1, 0), 4), 2, 2);

     cT alpha = cT(2, 1);
     cT beta =  cT(3, 1);
     nt2::table<cT> z = c*beta+alpha*mtimes(a, b);
     blas_gemm('N', 'N', alpha, boost::proto::value(a), boost::proto::value(b), beta, boost::proto::value(c));
     NT2_TEST_ULP_EQUAL(c, z, 2.5);
   }
   {
     nt2::table<cT> a = reshape(linspace(cT(1, 1), cT(4, 0), 6), 2, 3);
     nt2::table<cT> b = reshape(linspace(cT(0, 1), cT(2),6), 2, 3);
     nt2::table<cT> c = reshape(linspace(cT(0, 1), cT(1, 0), 4), 2, 2);
     cT alpha = cT(2, 1);
     cT beta =  cT(3, 1);
     nt2::table<cT> z = c*beta+alpha*mtimes(a, trans(b));
     blas_gemm('N', 'T', alpha, boost::proto::value(a), boost::proto::value(b), beta, boost::proto::value(c));
     NT2_TEST_ULP_EQUAL(c, z, 2.5);
   }
   {
     nt2::table<cT> a = reshape(linspace(cT(1, 1), cT(4, 0), 6), 2, 3);
     nt2::table<cT> b = reshape(linspace(cT(0, 1), cT(2),6), 2, 3);
     nt2::table<cT> c = reshape(linspace(cT(0, 1), cT(1, 0), 9), 3, 3);
     cT alpha = cT(2, 1);
     cT beta =  cT(3, 1);
     nt2::table<cT> z = c*beta+alpha*mtimes(trans(a), b);
     blas_gemm('T', 'N', alpha, boost::proto::value(a), boost::proto::value(b), beta, boost::proto::value(c));
     NT2_TEST_ULP_EQUAL(c, z, 2.5);
   }

   {
     nt2::table<cT> a = reshape(linspace(cT(1, 1), cT(4, 0), 6), 2, 3);
     nt2::table<cT> b = reshape(linspace(cT(0, 1), cT(2),6), 3, 2);
     nt2::table<cT> c = reshape(linspace(cT(0, 1), cT(1, 0), 9), 3, 3);
     cT alpha = cT(2, 1);
     cT beta =  cT(3, 1);
     nt2::table<cT> z = c*beta+alpha*mtimes(trans(a), trans(b));
     blas_gemm('T', 'T', alpha, boost::proto::value(a), boost::proto::value(b), beta, boost::proto::value(c));
     NT2_TEST_ULP_EQUAL(c, z, 2.5);
   }

 }
}
