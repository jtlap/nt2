//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/combinatorial/include/functions/combs.hpp>
#include <nt2/include/functions/colon.hpp>
#include <nt2/table.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/module.hpp>


NT2_TEST_CASE_TPL ( combs_integer__1_0, NT2_REAL_TYPES)
{

  using nt2::combs;
  using nt2::tag::combs_;

   nt2::table<T, nt2::_2D> a =  combs(nt2::_(T(1), T(5)), 3);
   nt2::table<T, nt2::_2D> b =  combs(nt2::_(T(1), T(5)), 5);
   NT2_TEST_EQUAL(b,nt2::_(T(1), T(5)));
   nt2::table<T, nt2::_2D> c =  combs(nt2::_(T(1), T(5)), 1);
   NT2_TEST_EQUAL(c,nt2::colvect(nt2::_(T(1), T(5))));

}
