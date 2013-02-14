//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 linalg toolbox - cycol function"

#include <nt2/table.hpp>
#include <nt2/include/functions/cycol.hpp>
#include <nt2/include/functions/colon.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/module.hpp>

using nt2::_;
NT2_TEST_CASE_TPL ( cycol, (double))
{
  nt2::table<T> v2 = nt2::cycol(size_t(4), size_t(6), size_t(2));
  NT2_DISPLAY(v2);
  NT2_TEST_EQUAL(v2(_, nt2::_(1, 2)), v2(_, nt2::_(3, 4)));
  NT2_TEST_EQUAL(v2(_, 1), v2(_, 5));
}



