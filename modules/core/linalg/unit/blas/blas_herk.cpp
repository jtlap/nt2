//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/blas_herk.hpp>
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


NT2_TEST_CASE_TPL(blas_herk, NT2_REAL_TYPES )
{
  using nt2::blas_herk;
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
    T alpha = T(2);
    T beta =  T(3);
    nt2::table<T> z = c*beta+alpha*mtimes(a, trans(a));
    blas_herk('L', 'N', alpha, boost::proto::value(a), beta, boost::proto::value(c));
    NT2_TEST_ULP_EQUAL(tril(c), tril(z), 1);
  }
  {
    nt2::table<T> c1 = reshape(_(T(1), T(9)), 3, 3);
    nt2::table<T> c =  average(c1, trans(c1));
    nt2::table<T> a = reshape(_(T(1), T(6)), 3, 2);
    T alpha = T(2);
    T beta =  T(3);
    nt2::table<T> z = c*beta+alpha*mtimes(a, trans(a));
    blas_herk('U', 'N', alpha, boost::proto::value(a), beta, boost::proto::value(c));
    NT2_TEST_ULP_EQUAL(triu(c), triu(z), 1);
  }
  {
    nt2::table<T> c1 = reshape(_(T(1), T(4)), 2, 2);
    nt2::table<T> c =  average(c1, trans(c1));
    nt2::table<T> a = reshape(_(T(1), T(6)), 3, 2);
    T alpha = T(2);
    T beta =  T(3);
    nt2::table<T> z = c*beta+alpha*mtimes(trans(a), a);
    blas_herk('L', 'T', alpha, boost::proto::value(a), beta, boost::proto::value(c));
    NT2_TEST_ULP_EQUAL(tril(c), tril(z), 1);
  }
  {
    nt2::table<T> c1 = reshape(_(T(1), T(4)), 2, 2);
    nt2::table<T> c =  average(c1, trans(c1));
    nt2::table<T> a = reshape(_(T(1), T(6)), 3, 2);
    T alpha = T(2);
    T beta =  T(3);
    nt2::table<T> z = c*beta+alpha*mtimes(trans(a), a);
    blas_herk('U', 'T', alpha, boost::proto::value(a), beta, boost::proto::value(c));
    NT2_TEST_ULP_EQUAL(triu(c), triu(z), 1);
  }


}
NT2_TEST_CASE_TPL(blas_herkc, NT2_REAL_TYPES )
{
  using nt2::blas_herk;
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
    nt2::table<cT> c =  average(c1, ctrans(c1));
    nt2::table<cT> a = reshape(linspace(cT(0, 1), cT(0, 2), 6), 3, 2);
    T alpha = T(2);
    T beta =  T(3);
    nt2::table<cT> z = c*beta+alpha*mtimes(a, ctrans(a));
    blas_herk('L', 'N', alpha, boost::proto::value(a), beta, boost::proto::value(c));
    NT2_TEST_ULP_EQUAL(tril(c), tril(z), 1);
  }
  {
    nt2::table<cT> c1 = reshape(linspace(cT(1, 1), cT(4, 0),9), 3, 3);
    nt2::table<cT> c =  average(c1, ctrans(c1));
    nt2::table<cT> a = reshape(linspace(cT(0, 1), cT(0, 2), 6), 3, 2);
    T alpha = T(2);
    T beta =  T(3);
    nt2::table<cT> z = c*beta+alpha*mtimes(a, ctrans(a));
    blas_herk('U', 'N', alpha, boost::proto::value(a), beta, boost::proto::value(c));
    NT2_TEST_ULP_EQUAL(triu(c), triu(z), 1);
  }
  {
    nt2::table<cT> c1 = reshape(linspace(cT(1, 1), cT(4, 0), 4), 2, 2);
    nt2::table<cT> c =  average(c1, ctrans(c1));
    nt2::table<cT> a = reshape(linspace(cT(0, 1), cT(0, 2), 6), 3, 2);
    T alpha = T(2);
    T beta =  T(3);
    nt2::table<cT> z = c*beta+alpha*mtimes(ctrans(a), a);
    blas_herk('L', 'C', alpha, boost::proto::value(a), beta, boost::proto::value(c));
    NT2_TEST_ULP_EQUAL(tril(c), tril(z), 1);
  }
  {
    nt2::table<cT> c1 = reshape(linspace(cT(1, 1), cT(4, 0), 4), 2, 2);
    nt2::table<cT> c =  average(c1, ctrans(c1));
    nt2::table<cT> a = reshape(linspace(cT(0, 1), cT(0, 2), 6), 3, 2);
    T alpha = T(2);
    T beta =  T(3);
    nt2::table<cT> z = c*beta+alpha*mtimes(ctrans(a), a);
    blas_herk('U', 'C', alpha, boost::proto::value(a), beta, boost::proto::value(c));
    NT2_TEST_ULP_EQUAL(triu(c), triu(z), 1);
  }


}

