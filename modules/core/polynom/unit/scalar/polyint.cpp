//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/polyder.hpp>
#include <nt2/include/functions/polyint.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/colon.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/table.hpp>

NT2_TEST_CASE_TPL ( polyint_1_0,  NT2_REAL_TYPES)
{

  using nt2::polyint;
  using nt2::tag::polyint_;
  nt2::table<T> a =  nt2::_(T(4), T(-1), T(1));
  nt2::table<T> c(nt2::of_size(1, 0));
  nt2::table<T> ia =  polyint(a, T(1));
  NT2_TEST_EQUAL(ia, nt2::ones(1,5, nt2::meta::as_<T>()));
}


