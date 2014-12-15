//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/blas_unband.hpp>
#include <nt2/include/functions/blas_band.hpp>
#include <nt2/include/functions/band.hpp>
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


NT2_TEST_CASE_TPL(blas_unbandut, NT2_REAL_TYPES )
{
  using nt2::blas_unband;
  using nt2::blas_band;
  using nt2::reshape;
  using nt2::_;
  nt2::table<T> a = band(reshape(_(T(1), T(25)), 5, 5), -2, 1);
  nt2::table<T> b(nt2::of_size(4, 5));
  nt2::table<T> ua(nt2::of_size(5, 5));;
  b = blas_band(a, 2, 1);
  ua = blas_unband(b, 5, 2, 1);
  NT2_TEST_EQUAL(ua, a);
}

