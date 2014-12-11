//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/blas_syr2k.hpp>
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
#include <nt2/include/functions/average.hpp>

#include <nt2/include/functions/tril.hpp>
#include <nt2/include/functions/triu.hpp>



#include <nt2/table.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>


NT2_TEST_CASE_TPL(blas_syr2k, NT2_REAL_TYPES )
{
  using nt2::blas_syr2k;
  using nt2::mtimes;
  using nt2::reshape;
  using nt2::_;
  using nt2::linspace;
  using nt2::height;
  using nt2::zeros;
  using nt2::of_size;
  {
    nt2::table<T> c1 = reshape(_(T(1), T(9)), 3, 3);
    nt2::table<T> c =  average(c1, trans(c1));
    nt2::table<T> a = reshape(_(T(1), T(6)), 3, 2);
    nt2::table<T> b = reshape(_(T(0), T(5)), 3, 2);
    T alpha = T(2);
    T beta =  T(3);
    nt2::table<T> z = c*beta+alpha*mtimes(a, trans(b))+alpha*mtimes(b, trans(a));
    blas_syr2k('L', 'N', alpha, boost::proto::value(a), boost::proto::value(b), beta, boost::proto::value(c));
    NT2_TEST_ULP_EQUAL(tril(c), tril(z), 1);
  }
  {
    nt2::table<T> c1 = reshape(_(T(1), T(9)), 3, 3);
    nt2::table<T> c =  average(c1, trans(c1));
    nt2::table<T> a = reshape(_(T(1), T(6)), 3, 2);
    nt2::table<T> b = reshape(_(T(0), T(5)), 3, 2);
    T alpha = T(2);
    T beta =  T(3);
    nt2::table<T> z = c*beta+alpha*mtimes(a, trans(b))+alpha*mtimes(b, trans(a));
    blas_syr2k('U', 'N', alpha, boost::proto::value(a), boost::proto::value(b), beta, boost::proto::value(c));
    NT2_TEST_ULP_EQUAL(triu(c), triu(z), 1);
  }
  {
    nt2::table<T> c1 = reshape(_(T(1), T(4)), 2, 2);
    nt2::table<T> c =  average(c1, trans(c1));
    nt2::table<T> a = reshape(_(T(1), T(6)), 3, 2);
    nt2::table<T> b = reshape(_(T(0), T(5)), 3, 2);
    T alpha = T(2);
    T beta =  T(3);
    nt2::table<T> z = c*beta+alpha*mtimes(trans(a), b)+alpha*mtimes(trans(b), a);
    blas_syr2k('L', 'T', alpha, boost::proto::value(a), boost::proto::value(b), beta, boost::proto::value(c));
    NT2_TEST_ULP_EQUAL(tril(c), tril(z), 1);
  }
  {
    nt2::table<T> c1 = reshape(_(T(1), T(4)), 2, 2);
    nt2::table<T> c =  average(c1, trans(c1));
    nt2::table<T> a = reshape(_(T(1), T(6)), 3, 2);
    nt2::table<T> b = reshape(_(T(0), T(5)), 3, 2);
    T alpha = T(2);
    T beta =  T(3);
    nt2::table<T> z = c*beta+alpha*mtimes(trans(a), b)+alpha*mtimes(trans(b), a);
    blas_syr2k('U', 'T', alpha, boost::proto::value(a), boost::proto::value(b), beta, boost::proto::value(c));
    NT2_TEST_ULP_EQUAL(triu(c), triu(z), 1);
  }


}
NT2_TEST_CASE_TPL(blas_syr2kc, NT2_REAL_TYPES )
{
  using nt2::blas_syr2k;
  using nt2::mtimes;
  using nt2::reshape;
  using nt2::_;
  using nt2::linspace;
  using nt2::height;
  using nt2::zeros;
  using nt2::of_size;
  typedef std::complex<T> cT;
  {
    nt2::table<cT> c1 = reshape(linspace(cT(1, 1), cT(4, 0),9), 3, 3);
    nt2::table<cT> c =  average(c1, trans(c1));
    nt2::table<cT> a = reshape(linspace(cT(0, 1), cT(0, 2), 6), 3, 2);
    nt2::table<cT> b = reshape(linspace(cT(0, 1), cT(1, 0), 6), 3, 2);
    cT alpha = cT(2, 2);
    cT beta =  cT(3, 1);
    nt2::table<cT> z = c*beta+alpha*mtimes(a, trans(b))+alpha*mtimes(b, trans(a));
    blas_syr2k('L', 'N', alpha, boost::proto::value(a), boost::proto::value(b), beta, boost::proto::value(c));
    NT2_TEST_ULP_EQUAL(tril(c), tril(z), 1);
  }
  {
    nt2::table<cT> c1 = reshape(linspace(cT(1, 1), cT(4, 0),9), 3, 3);
    nt2::table<cT> c =  average(c1, trans(c1));
    nt2::table<cT> a = reshape(linspace(cT(0, 1), cT(0, 2), 6), 3, 2);
    nt2::table<cT> b = reshape(linspace(cT(0, 1), cT(1, 0), 6), 3, 2);
    cT alpha = cT(2, 2);
    cT beta =  cT(3, 1);
    nt2::table<cT> z = c*beta+alpha*mtimes(a, trans(b))+alpha*mtimes(b, trans(a));
    blas_syr2k('U', 'N', alpha, boost::proto::value(a), boost::proto::value(b), beta, boost::proto::value(c));
    NT2_TEST_ULP_EQUAL(triu(c), triu(z), 1);
  }
  {
    nt2::table<cT> c1 = reshape(linspace(cT(1, 1), cT(4, 0), 4), 2, 2);
    nt2::table<cT> c =  average(c1, trans(c1));
    nt2::table<cT> a = reshape(linspace(cT(0, 1), cT(0, 2), 6), 3, 2);
    nt2::table<cT> b = reshape(linspace(cT(0, 1), cT(1, 0), 6), 3, 2);
    cT alpha = cT(2, 2);
    cT beta =  cT(3, 1);
    nt2::table<cT> z = c*beta+alpha*mtimes(trans(a), b)+alpha*mtimes(trans(b), a);
    blas_syr2k('L', 'T', alpha, boost::proto::value(a), boost::proto::value(b), beta, boost::proto::value(c));
    NT2_TEST_ULP_EQUAL(tril(c), tril(z), 1);
  }
  {
    nt2::table<cT> c1 = reshape(linspace(cT(1, 1), cT(4, 0), 4), 2, 2);
    nt2::table<cT> c =  average(c1, trans(c1));
    nt2::table<cT> a = reshape(linspace(cT(0, 1), cT(0, 2), 6), 3, 2);
    nt2::table<cT> b = reshape(linspace(cT(0, 1), cT(1, 0), 6), 3, 2);
    cT alpha = cT(2, 2);
    cT beta =  cT(3, 1);
    nt2::table<cT> z = c*beta+alpha*mtimes(trans(a), b)+alpha*mtimes(trans(b), a);
    blas_syr2k('U', 'T', alpha, boost::proto::value(a), boost::proto::value(b), beta, boost::proto::value(c));
    NT2_TEST_ULP_EQUAL(triu(c), triu(z), 1);
  }


}


// NT2_TEST_CASE_TPL(blas_syr2kc, NT2_REAL_TYPES )
// {
//   using nt2::blas_syr2k;
//   using nt2::mtimes;
//   using nt2::reshape;
//   using nt2::_;
//   using nt2::linspace;
//   using nt2::height;
//   using nt2::zeros;
//   using nt2::of_size;
//   typedef std::complex<T> cT;

//   {
//     nt2::table<cT> c1 = reshape(linspace(cT(1, 1), cT(4, 0),9), 3, 3);
//     nt2::table<cT> c =  average(a1, trans(a1));
//     nt2::table<cT> a = reshape(linspace(cT(0, 1), cT(0, 2), 6), 3, 2);
//     nt2::table<cT> b = reshape(linspace(cT(0, 1), cT(1, 0), 6), 3, 2);

//     cT alpha = cT(2, 2);
//     cT beta =  cT(3, 1);
//     nt2::table<cT> z = c*beta+alpha*mtimes(a, b);
//     blas_syr2k('L', 'N', alpha, boost::proto::value(a), boost::proto::value(b), beta, boost::proto::value(c));
//     NT2_TEST_ULP_EQUAL(c, z, 1);
//   }
//   {
//     nt2::table<cT> a1 = reshape(linspace(cT(1, 1), cT(4, 0), 9), 3, 3);
//     nt2::table<cT> b = reshape(linspace(cT(0, 1), cT(2), 6), 3, 2);
//     nt2::table<cT> c = reshape(linspace(cT(0, 1), cT(1, 0), 6), 3, 2);
//     nt2::table<cT> a =  average(a1, trans(a1));

//     cT alpha = cT(2, 2);
//     cT beta =  cT(3, 1);
//     nt2::table<cT> z = c*beta+alpha*mtimes(a, b);
//     blas_syr2k('L', 'T', alpha, boost::proto::value(a), boost::proto::value(b), beta, boost::proto::value(c));
//     NT2_TEST_ULP_EQUAL(c, z, 1);
//   }

//   {
//     nt2::table<cT> a1 = reshape(linspace(cT(1, 1), cT(4, 0), 9), 3, 3);
//     nt2::table<cT> b = reshape(linspace(cT(0, 1), cT(2), 6), 2, 3);
//     nt2::table<cT> c = reshape(linspace(cT(0, 1), cT(1, 0), 6), 2, 3);
//     nt2::table<cT> a =  average(a1, trans(a1));

//     cT alpha = cT(2, 2);
//     cT beta =  cT(3, 1);
//     nt2::table<cT> z = c*beta+alpha*mtimes(b, a);
//     blas_syr2k('U', 'N', alpha, boost::proto::value(a), boost::proto::value(b), beta, boost::proto::value(c));
//     NT2_TEST_ULP_EQUAL(c, z, 1);
//   }
//   {
//     nt2::table<cT> a1 = reshape(linspace(cT(1, 1), cT(4, 0), 9), 3, 3);
//     nt2::table<cT> b = reshape(linspace(cT(0, 1), cT(2), 6), 2, 3);
//     nt2::table<cT> c = reshape(linspace(cT(0, 1), cT(1, 0), 6), 2, 3);
//     nt2::table<cT> a =  average(a1, trans(a1));

//     cT alpha = cT(2, 2);
//     cT beta =  cT(3, 1);
//     nt2::table<cT> z = c*beta+alpha*mtimes(b, a);
//     blas_syr2k('U', 'T', alpha, boost::proto::value(a), boost::proto::value(b), beta, boost::proto::value(c));
//     NT2_TEST_ULP_EQUAL(c, z, 1);
//   }
// }
