//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/blas_rotg.hpp>
#include <nt2/include/functions/mtimes.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/constants/zero.hpp>


#include <nt2/table.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>


NT2_TEST_CASE_TPL(blas_rotg, NT2_REAL_TYPES )
{
  using nt2::blas_rotg;

  T a = T(1);
  T b = T(1);
  nt2::table<T> x = nt2::cons<T>(nt2::of_size(2, 1), a, b);
  T c, s;
  blas_rotg(a, b, c, s);
  nt2::table<T> r = nt2::cons<T>(nt2::of_size(2, 2), c, -s, s, c);
  NT2_TEST_ULP_EQUAL(nt2::mtimes(r, x)(2), nt2::Zero<T>(), 0.5);

}

