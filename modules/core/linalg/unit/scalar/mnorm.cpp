//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/table.hpp>
#include <nt2/include/functions/mnorm.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/three.hpp>
#include <nt2/include/constants/nine.hpp>
#include <nt2/linalg/options.hpp>

#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/module.hpp>


NT2_TEST_CASE_TPL(norm, NT2_REAL_TYPES)
{
  using nt2::mnorm;
  using nt2::tag::mnorm_;
  nt2::table<T> n = nt2::ones(1, 9, nt2::meta::as_<T>());
  NT2_TEST_ULP_EQUAL(mnorm(n),  nt2::Three<T>(), 0);
  nt2::table<T> n1 = nt2::ones(9, 1, nt2::meta::as_<T>());
  NT2_TEST_ULP_EQUAL(mnorm(n1),  nt2::Three<T>(), 0);
  nt2::table<T> a = nt2::ones(9, 9, nt2::meta::as_<T>());
  NT2_TEST_ULP_EQUAL(mnorm(a), nt2::Nine<T>(), 0.5);
  nt2::table<T, nt2::of_size_<1,9> > ns=  n;
  NT2_TEST_ULP_EQUAL(mnorm(ns),  nt2::Three<T>(), 0);
  nt2::table<T, nt2::of_size_<9,1> > ns1 = n1;
  NT2_TEST_ULP_EQUAL(mnorm(ns1),  nt2::Three<T>(), 0);
}

