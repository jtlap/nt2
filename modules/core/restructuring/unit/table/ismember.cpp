//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//=============================================================================
#include <nt2/table.hpp>
#include <nt2/include/functions/ismember.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/meta/as.hpp>

#include <nt2/include/functions/is_nez.hpp>
#include <nt2/include/functions/reshape.hpp>
#include <nt2/include/functions/find.hpp>
#include <nt2/include/functions/is_nez.hpp>
#include <nt2/include/constants/true.hpp>
#include <nt2/include/constants/false.hpp>
#include <nt2/include/constants/eps.hpp>

NT2_TEST_CASE_TPL(ismember_, NT2_REAL_TYPES)
{
  using nt2::ismember;
  using nt2::tag::ismember_;
  using nt2::table;

  nt2::table<T> b = nt2::cons<T>(3, 1, 2, 3, 5, 2, 3);
  nt2::table<T> a = nt2::reshape(nt2::cons<T>(0, 2, 3, 3, 4, 5, 6, 1), 2, 4);
  nt2::table<nt2::logical<T>> r = nt2::reshape(nt2::is_nez(nt2::cons<T>(0, 1, 1, 1, 0, 1, 0, 1)), 2, 4);
  nt2::table<nt2::logical<T>> c = ismember(a, b);
  NT2_TEST_EQUAL(c, r);
  nt2::table<T> a1= a+10*nt2::Eps<T>();
  nt2::table<nt2::logical<T>> c1 = ismember(a1, b, 20*nt2::Eps<T>());
  NT2_TEST_EQUAL(c1, r);
  nt2::table<T> a2= a-10*nt2::Eps<T>();
  nt2::table<nt2::logical<T>> c2 = ismember(a2, b, 20*nt2::Eps<T>());
  NT2_TEST_EQUAL(c2, r);
}






