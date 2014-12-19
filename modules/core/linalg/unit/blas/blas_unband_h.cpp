//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/blas_unband_h.hpp>
#include <nt2/include/functions/blas_band_h.hpp>
#include <nt2/include/functions/band.hpp>
#include <nt2/include/functions/mtimes.hpp>
#include <nt2/include/functions/reshape.hpp>
#include <nt2/include/functions/triu.hpp>
#include <nt2/include/functions/tril.hpp>
#include <nt2/include/functions/transpose.hpp>
#include <nt2/include/functions/ctranspose.hpp>
#include <nt2/include/functions/average.hpp>



#include <nt2/table.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>


NT2_TEST_CASE_TPL(blas_unband_su, NT2_REAL_TYPES )
{
  using nt2::blas_unband_h;
  using nt2::blas_band_h;
  using nt2::reshape;
  using nt2::_;
  nt2::table<T> a = band(reshape(_(T(1), T(25)), 5, 5), -2, 1);
  nt2::table<T> sa = average(a, trans(a));
  nt2::table<T> b(nt2::of_size(4, 5));
  nt2::table<T> ua(nt2::of_size(5, 5));;
  b = blas_band_h('U', sa, 2);
  ua = blas_unband_h('S', 'U', b,2);
  NT2_TEST_EQUAL(ua, sa);
}

NT2_TEST_CASE_TPL(blas_unband_hlc, NT2_REAL_TYPES )
{
  using nt2::blas_unband_h;
  using nt2::blas_band_h;
  using nt2::reshape;
  using nt2::_;
  typedef std::complex<T> cT;
  nt2::table<cT> a = band(reshape(_(T(1), T(25)), 5, 5), -2, 1)*cT(1, 2);
  nt2::table<cT> sa = average(a, ctrans(a));
  nt2::table<cT> b(nt2::of_size(4, 5));
  nt2::table<cT> ua(nt2::of_size(5, 5));;
  b = blas_band_h('L', sa, 2);
  ua = blas_unband_h('H', 'L', b,2);
  NT2_TEST_EQUAL(ua, sa);
}

NT2_TEST_CASE_TPL(blas_unband_slc, NT2_REAL_TYPES )
{
  using nt2::blas_unband_h;
  using nt2::blas_band_h;
  using nt2::reshape;
  using nt2::_;
  typedef std::complex<T> cT;
  nt2::table<cT> a = band(reshape(_(T(1), T(25)), 5, 5), -2, 1)*cT(1, 2);
  nt2::table<cT> sa = average(a, trans(a));
  nt2::table<cT> b(nt2::of_size(4, 5));
  nt2::table<cT> ua(nt2::of_size(5, 5));;
  b = blas_band_h('L', sa, 2);
  ua = blas_unband_h('S', 'L', b,2);
  NT2_TEST_EQUAL(ua, sa);
}

