//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/blas_band_h.hpp>
#include <nt2/include/functions/mtimes.hpp>
#include <nt2/include/functions/reshape.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/functions/triu.hpp>
#include <nt2/include/functions/tril.hpp>
#include <nt2/include/functions/average.hpp>
#include <nt2/include/functions/transpose.hpp>
#include <nt2/include/functions/band.hpp>



#include <nt2/table.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>


NT2_TEST_CASE_TPL(blas_band_h, NT2_REAL_TYPES )
{
  using nt2::blas_band_h;
  using nt2::reshape;
  using nt2::band;
  using nt2::reshape;
  using nt2::_;
  {
    nt2::table<T> a = reshape(_(T(1), T(25)), 5, 5);
    nt2::table<T> sa = band(average(a, trans(a)), -2, 2);
    nt2::table<T> b(nt2::of_size(4, 5));
    nt2::table<T> r = nt2::cons<T>(nt2::of_size(3, 5),
                                   0, 0, 1,
                                   0, 4, 7,
                                   7, 10, 13,
                                   13, 16, 19,
                                   19, 22, 25);
    b = blas_band_h('U', sa, 2);
    NT2_DISPLAY(sa);
    NT2_DISPLAY(b);
    NT2_TEST_EQUAL(b, r);
  }
  {
    nt2::table<T> a = reshape(_(T(1), T(25)), 5, 5);
    nt2::table<T> sa = band(average(a, trans(a)), -2, 2);
    nt2::table<T> b(nt2::of_size(4, 5));
    nt2::table<T> r = nt2::cons<T>(nt2::of_size(3, 5),
                                   1, 4, 7,
                                   7, 10, 13,
                                   13, 16, 19,
                                   19, 22, 0,
                                   25, 0, 0);
    b = blas_band_h('L', sa, 2);
    NT2_DISPLAY(sa);
    NT2_DISPLAY(b);
    NT2_TEST_EQUAL(b, r);
  }}


