//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/blas_rotmg.hpp>
#include <nt2/include/functions/mtimes.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/functions/sqrt.hpp>
#include <nt2/include/constants/zero.hpp>


#include <nt2/table.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>


NT2_TEST_CASE_TPL(blas_rotmg, NT2_REAL_TYPES )
{
  using nt2::blas_rotmg;

  T d1 = T(1);
  T d2 = T(1);
  T x1 = T(3);
  T y1 = T(4);
  nt2::table<T> dparam(nt2::of_size(1, 5));
  dparam(1) = T(-1.0);
  nt2::table<T> x = nt2::cons<T>(nt2::of_size(2, 1), nt2::sqrt(d1)*x1, nt2::sqrt(d2)*y1);

  blas_rotmg(d1, d2, x1, y1, boost::proto::value(dparam));
  NT2_DISPLAY(dparam);
  NT2_DISPLAY(x);
  nt2::table<T> r = nt2::cons<T>(nt2::of_size(2, 2), dparam(2),T(-1), T(1), dparam(5));
  NT2_TEST_ULP_EQUAL(nt2::mtimes(r, x)(2), nt2::Zero<T>(), 0.5);

}

