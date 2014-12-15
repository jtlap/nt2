//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/blas_unpack.hpp>
#include <nt2/include/functions/blas_pack.hpp>
#include <nt2/include/functions/mtimes.hpp>
#include <nt2/include/functions/reshape.hpp>
#include <nt2/include/functions/triu.hpp>
#include <nt2/include/functions/tril.hpp>
#include <nt2/include/functions/transpose.hpp>
#include <nt2/include/functions/ctranspose.hpp>



#include <nt2/table.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>


NT2_TEST_CASE_TPL(blas_unpackut, NT2_REAL_TYPES )
{
  using nt2::blas_unpack;
  using nt2::blas_pack;
  using nt2::reshape;
  using nt2::_;
  nt2::table<T> a = triu(reshape(_(T(1), T(9)), 3, 3));
  nt2::table<T> b(nt2::of_size(1, 3));
  nt2::table<T> ua(nt2::of_size(3, 3));;
  NT2_DISPLAY(a);
  b = blas_pack('U', a);
  ua = blas_unpack('U', 'T', b);
  NT2_DISPLAY(a);
  NT2_DISPLAY(ua);
  NT2_TEST_EQUAL(ua, a);
}


NT2_TEST_CASE_TPL(blas_unpackus, NT2_REAL_TYPES )
{
  using nt2::blas_unpack;
  using nt2::blas_pack;
  using nt2::reshape;
  using nt2::_;
  nt2::table<T> aa = triu(reshape(_(T(1), T(9)), 3, 3));
  nt2::table<T> a = (aa+trans(aa));
  nt2::table<T> b(nt2::of_size(1, 3));
  nt2::table<T> ua(nt2::of_size(3, 3));;
  NT2_DISPLAY(a);
  b = blas_pack('U', a);
  ua = blas_unpack('U', 'S', b);
  NT2_DISPLAY(a);
  NT2_DISPLAY(ua);
  NT2_TEST_EQUAL(ua, a);
}

NT2_TEST_CASE_TPL(blas_unpackuh, NT2_REAL_TYPES )
{
  using nt2::blas_unpack;
  using nt2::blas_pack;
  using nt2::reshape;
  using nt2::_;
  typedef std::complex<T> cT;
  nt2::table<cT> aa = triu(reshape(_(T(1), T(9)), 3, 3));
  nt2::table<cT> a = (aa+ctrans(aa));
  nt2::table<cT> b(nt2::of_size(1, 3));
  nt2::table<cT> ua(nt2::of_size(3, 3));;
  NT2_DISPLAY(a);
  b = blas_pack('U', a);
  ua = blas_unpack('U', 'H', b);
  NT2_DISPLAY(a);
  NT2_DISPLAY(ua);
  NT2_TEST_EQUAL(ua, a);
}

NT2_TEST_CASE_TPL(blas_unpacklt, NT2_REAL_TYPES )
{
  using nt2::blas_unpack;
  using nt2::blas_pack;
  using nt2::reshape;
  using nt2::_;
  nt2::table<T> a = tril(reshape(_(T(1), T(9)), 3, 3));
  nt2::table<T> b(nt2::of_size(1, 3));
  nt2::table<T> ua(nt2::of_size(3, 3));;
  NT2_DISPLAY(a);
  b = blas_pack('L', a);
  ua = blas_unpack('L', 'T', b);
  NT2_DISPLAY(a);
  NT2_DISPLAY(ua);
  NT2_TEST_EQUAL(ua, a);
}


NT2_TEST_CASE_TPL(blas_unpackls, NT2_REAL_TYPES )
{
  using nt2::blas_unpack;
  using nt2::blas_pack;
  using nt2::reshape;
  using nt2::_;
  nt2::table<T> aa = tril(reshape(_(T(1), T(9)), 3, 3));
  nt2::table<T> a = (aa+trans(aa));
  nt2::table<T> b(nt2::of_size(1, 3));
  nt2::table<T> ua(nt2::of_size(3, 3));;
  NT2_DISPLAY(a);
  b = blas_pack('L', a);
  ua = blas_unpack('L', 'S', b);
  NT2_DISPLAY(a);
  NT2_DISPLAY(ua);
  NT2_TEST_EQUAL(ua, a);
}

NT2_TEST_CASE_TPL(blas_unpacklh, NT2_REAL_TYPES )
{
  using nt2::blas_unpack;
  using nt2::blas_pack;
  using nt2::reshape;
  using nt2::_;
  typedef std::complex<T> cT;
  nt2::table<cT> aa = tril(reshape(_(T(1), T(9)), 3, 3));
  nt2::table<cT> a = (aa+ctrans(aa));
  nt2::table<cT> b(nt2::of_size(1, 3));
  nt2::table<cT> ua(nt2::of_size(3, 3));;
  NT2_DISPLAY(a);
  b = blas_pack('L', a);
  ua = blas_unpack('L', 'H', b);
  NT2_DISPLAY(a);
  NT2_DISPLAY(ua);
  NT2_TEST_EQUAL(ua, a);
}

