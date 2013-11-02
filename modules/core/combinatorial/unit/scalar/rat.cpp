//==============================================================================
//         Copyright 2003 - 2013   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/combinatorial/include/functions/rat.hpp>

#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>

NT2_TEST_CASE_TPL ( rat_real__1_0,  NT2_REAL_TYPES)
{
  using nt2::rat;
  using nt2::tag::rat_;

  // specific values tests
  T n, d;
  rat(T(1.5), n, d);
  NT2_TEST_ULP_EQUAL(n, T(3), 0);
  NT2_TEST_ULP_EQUAL(d, T(2), 0);
  rat(T(3.14159), n, d);
  NT2_TEST_ULP_EQUAL(n, T(355), 0);
  NT2_TEST_ULP_EQUAL(d, T(113), 0);
}
