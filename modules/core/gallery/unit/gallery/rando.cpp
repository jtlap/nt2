//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 gallery toolbox - rando function"

#include <nt2/table.hpp>
#include <nt2/include/functions/rando.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/functions/globalmax.hpp>
#include <nt2/include/functions/find.hpp>
#include <nt2/include/functions/isempty.hpp>
#include <nt2/include/functions/linspace.hpp>
#include <nt2/include/functions/extent.hpp>
#include <nt2/include/functions/of_size.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/module.hpp>


template < class T, class U > bool are_all_in(const T & set, const U & values)
{

  for(size_t i=1; i <= numel(values); ++i)
  {
    if (nt2::isempty(nt2::find(values(i) == set))) return false;
  }
  return true;
}

NT2_TEST_CASE_TPL ( rando, NT2_REAL_TYPES)
{
  nt2::table<T> rc;
  rc = nt2::rando(4,  nt2::meta::as_<T>());
  NT2_TEST(are_all_in(nt2::_(T(0), T(1)), rc));
  NT2_TEST_EQUAL(nt2::extent(rc), nt2::of_size(4, 4));
  rc = nt2::rando(4, 5,  nt2::meta::as_<T>());
  NT2_TEST(are_all_in(nt2::_(T(0), T(1)), rc));
  NT2_TEST_EQUAL(nt2::extent(rc), nt2::of_size(4, 5));
  rc = nt2::rando(4, 5, 1, nt2::meta::as_<T>());
  NT2_TEST(are_all_in(nt2::_(T(0), T(1)), rc));
  rc = nt2::rando(4, 5, 2, nt2::meta::as_<T>());
  NT2_TEST(are_all_in(nt2::cons(T(-1), T(1)), rc));
  rc = nt2::rando(4, 5, 3, nt2::meta::as_<T>());
  NT2_TEST(are_all_in(nt2::cons(T(-1), T(0), T(1)), rc));
  rc = nt2::rando<T>(4, 5, 3);
  NT2_TEST(are_all_in(nt2::cons(T(-1), T(0), T(1)), rc));
  rc = nt2::rando<T>(4, 5);
  NT2_TEST(are_all_in(nt2::_(T(0), T(1)), rc));
  rc = nt2::rando<T>(4);
  NT2_TEST(are_all_in(nt2::_(T(0), T(1)), rc));

}

NT2_TEST_CASE ( rando_no_type)
{
  typedef double T;
  nt2::table<T> rc;
  rc = nt2::rando(4, 5);
  NT2_TEST(are_all_in(nt2::_(T(0), T(1)), rc));
  NT2_TEST_EQUAL(nt2::extent(rc), nt2::of_size(4, 5));
  rc = nt2::rando(4, 5, 1);
  NT2_TEST(are_all_in(nt2::_(T(0), T(1)), rc));
  rc = nt2::rando(4, 5, 2);
  NT2_TEST(are_all_in(nt2::cons(T(-1), T(1)), rc));
  rc = nt2::rando(4, 5, 3);
  NT2_TEST(are_all_in(nt2::cons(T(-1), T(0), T(1)), rc));
}






