//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/valuation.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/table.hpp>

NT2_TEST_CASE_TPL ( valuation_real__1_0,  NT2_REAL_TYPES)
{

  using nt2::valuation;
  using nt2::tag::valuation_;
  nt2::table<T> a =  nt2::_(T(1), T(4));
  nt2::table<T> b =  nt2::_(T(0), T(0), T(3));
  nt2::table<T> c(nt2::of_size(1, 0));
  NT2_TEST_EQUAL(0, valuation(a));
  NT2_TEST_EQUAL(-1, valuation(b));
  b(2) = b(1) = T(1);
  NT2_TEST_EQUAL(1, valuation(b));

}

