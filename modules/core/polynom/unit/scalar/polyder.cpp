//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/polyder.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/table.hpp>

NT2_TEST_CASE_TPL ( polyder_real__1_0,  NT2_REAL_TYPES)
{

  using nt2::polyder;
  using nt2::tag::polyder_;
  nt2::table<T> a =  nt2::_(T(1), T(4));
  nt2::table<T> b =  nt2::_(T(1), T(3));
  nt2::table<T> c(nt2::of_size(1, 0));
  nt2::table<T> n, d;
  T daab[] = { 5, 16, 30, 32, 17 };
  T daa [] = { 3, 4, 3};
  nt2::table<T> dab(nt2::of_size(1, 5), &daab[0], &daab[5]);
  nt2::table<T> da (nt2::of_size(1, 3), &daa[0], &daa[3]);
  NT2_TEST_EQUAL(dab,polyder(a, b));
  NT2_TEST_EQUAL(da,polyder(a));
}


