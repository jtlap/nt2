//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/table.hpp>
#include <nt2/include/functions/null.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/eps.hpp>
#include <nt2/include/functions/ctranspose.hpp>
#include <nt2/include/functions/mtimes.hpp>
#include <nt2/include/functions/mnorm.hpp>
#include <nt2/include/constants/eps.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

NT2_TEST_CASE_TPL(null, NT2_REAL_TYPES)
{
  using nt2::_ ;

  nt2::table<T> n = nt2::eye(10, 10, nt2::meta::as_<T>());
  n(3, 5) = T(2);
  n(4, 4) = T(0);
  n(1, 1) = 5*nt2::Eps<T>();
  nt2::table<T> nulln = nt2::null(n);
  nt2::table<T> nulln1 = nt2::null(n,  T(0.1)*nt2::Eps<T>());

  nt2::table<T> rn1 = nt2::zeros(10, 1, nt2::meta::as_<T>());
  rn1(4) = T(-1);
  nt2::table<T> rn = nt2::zeros(10, 2, nt2::meta::as_<T>());
  rn(4, 1) = T(-1);
  rn(1, 2) = T(1);
  NT2_TEST_ULP_EQUAL(rn, nulln,0);
  NT2_TEST_ULP_EQUAL(rn1, nulln1,0);
 }

NT2_TEST_CASE_TPL(null_2, NT2_REAL_TYPES)
{
  using nt2::_ ;

  T t[] = {
    1,0,-1,0,0,
    -2,1,1,0,0,
    0,1,0,0,-1,
    1,-1,0,0,0,
    0,0,0,-1,1,
    0,0,-1,1,0,
    0,0,1,-1,0,
    0,0,0,1,-1,
    0,-1,0,0,1,
    0,0,0,1,-1 };

  nt2::table<T> tt(nt2::of_size(5,10), &t[0], &t[50]) ,u(nt2::ctrans(tt));
  nt2::table<T> n = nt2::null(u);

  NT2_TEST_EQUAL(nt2::width(n), 1u);
  NT2_TEST_LESSER(mnorm(nt2::mtimes(u, n)), numel(u)*nt2::Eps<T>());

  T t1[] = {0,0,-1,0,1,0,0,0,0,0,0,0,
            0,0,0,-1,0,0,-1,0,1,0,1,-1,
            1,0,0,-1,0,0,0,0,0,-1,1,0,
            0,0,0,0,0,0,0,0,0,0,0,1,
            1,0,-1,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,1,-1,-1,
            0,1,0,0,0,-1,1,-1,-1,0,0,1,
            -1,-1,1,0,0,0,0,1,0,0,0,0,
            0,0,0,1,-1,0,1,0,-1,0,0,1,
            0,0,0,0,0,1,0,0,0,0,0,1
           };

  nt2::table<T> tt1(nt2::of_size(12, 10), &t1[0], &t1[10*12]), u1(nt2::ctrans(tt1));
  nt2::table<T> n1 = nt2::null(u1);

  NT2_TEST_EQUAL(nt2::width(n1), 3);
  NT2_TEST_LESSER(mnorm(nt2::mtimes(u1, n1)), numel(u1)*nt2::Eps<T>());
}


