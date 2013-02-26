//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 linalg toolbox - subspace factorization"

#include <nt2/table.hpp>
#include <nt2/include/functions/subspace.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/colon.hpp>
#include <nt2/include/functions/colvect.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/pio_2.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>

NT2_TEST_CASE_TPL(subspace, NT2_REAL_TYPES)
{
  typedef T r_t;
  using nt2::subspace;
  using nt2::tag::subspace_;
  nt2::table<T> n = nt2::eye(10, 10, nt2::meta::as_<T>());
  NT2_TEST_ULP_EQUAL(subspace(n(nt2::_, nt2::_(1, 5)),n(nt2::_, nt2::_(1, 5))) , nt2::Zero<T>(), 0);
  NT2_TEST_ULP_EQUAL(subspace(n(nt2::_, nt2::_(1, 5)),n(nt2::_, nt2::_(3, 5))) , nt2::Pio_2<T>(), 1);
}
NT2_TEST_CASE_TPL(subspace1, NT2_REAL_TYPES)
{
  typedef T r_t;
  using nt2::subspace;
  using nt2::tag::subspace_;
  nt2::table<T> a = nt2::ones(5, 1, nt2::meta::as_<T>());
  nt2::table<T> b = nt2::colvect(nt2::_(T(1), T(5)));
  NT2_TEST_ULP_EQUAL(subspace(a, b),T(0.4405106630046984), 1);
}
