//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/blas_hpr.hpp>
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
#include <nt2/include/functions/multiplies.hpp>
#include <nt2/include/functions/plus.hpp>
#include <nt2/include/functions/linspace.hpp>
#include <nt2/include/functions/transpose.hpp>
#include <nt2/include/functions/ctranspose.hpp>
#include <nt2/include/functions/average.hpp>
#include <nt2/include/functions/triu.hpp>
#include <nt2/include/functions/tril.hpp>



#include <nt2/table.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>


NT2_TEST_CASE_TPL(blas_hpr, NT2_REAL_TYPES )
{
  using nt2::blas_hpr;
  using nt2::reshape;
  using nt2::_;
  using nt2::linspace;
  using nt2::average;
  {
    nt2::table<T> b = reshape(_(T(1), T(4)), 2, 2);
    nt2::table<T> a = average(b, trans(b));
    nt2::table<T> pa = nt2::blas_pack('U', a);
    nt2::table<T> x = reshape(_(T(1), T(2)), 2, 1);
    T alpha = T(2);
    nt2::table<T> z = alpha*mtimes(x, trans(x))+a;
    blas_hpr('U', alpha, boost::proto::value(x), 1, boost::proto::value(pa));
    nt2::table<T> zz = nt2::blas_pack('U',z);
    NT2_TEST_ULP_EQUAL(pa, zz, 0.5);
  }
  {
    nt2::table<T> b = reshape(_(T(1), T(4)), 2, 2);
    nt2::table<T> a = average(b, trans(b));
    nt2::table<T> pa = nt2::blas_pack('L', a);
    nt2::table<T> x = reshape(_(T(1), T(2)), 2, 1);
    T alpha = T(2);
    nt2::table<T> z = alpha*mtimes(x, trans(x))+a;
    blas_hpr('L', alpha, boost::proto::value(x), 1, boost::proto::value(pa));
    nt2::table<T> zz = nt2::blas_pack('L',z);
    NT2_TEST_ULP_EQUAL(pa, zz, 1);
  }

  {
    typedef std::complex<T> cT;
    nt2::table<cT> b = reshape(linspace(cT(1, 1), cT(4, 0), 25), 5, 5);
    nt2::table<cT> a = average(b, ctrans(b));
    nt2::table<cT> pa = nt2::blas_pack('U', a);
    nt2::table<cT> x = reshape(linspace(cT(0, 1), cT(2, 2), 5), 5, 1);
    T alpha = T(2);
    nt2::table<cT> z = alpha*mtimes(x, ctrans(x))+a;
    blas_hpr('U', alpha, boost::proto::value(x), 1, boost::proto::value(pa));
    nt2::table<cT> zz = nt2::blas_pack('U',z);
    NT2_TEST_ULP_EQUAL(pa, zz, 2);


  }
  {
    typedef std::complex<T> cT;
    nt2::table<cT> b = reshape(linspace(cT(1, 1), cT(4, 0), 25), 5, 5);
    nt2::table<cT> a = average(b, ctrans(b));
    nt2::table<cT> pa = nt2::blas_pack('L', a);
    nt2::table<cT> x = reshape(linspace(cT(0, 1), cT(2, 2), 5), 5, 1);
    T alpha = T(2);
    nt2::table<cT> z = alpha*mtimes(x, ctrans(x))+a;
    blas_hpr('L', alpha, boost::proto::value(x), 1, boost::proto::value(pa));
    nt2::table<cT> zz = nt2::blas_pack('L',z);
    NT2_TEST_ULP_EQUAL(pa, zz, 2);

  }
}


