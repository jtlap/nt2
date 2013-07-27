//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/conv.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/colon.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/meta/as.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/core/container/table/table.hpp>

NT2_TEST_CASE_TPL ( conv_real__1_0,  NT2_REAL_TYPES)
{
  using nt2::conv;
  using nt2::tag::conv_;
  nt2::container::table<T> a =  nt2::_(T(1), T(4));
  nt2::container::table<T> b =  nt2::_(T(1), T(3));
  nt2::container::table<T> c(nt2::of_size(1, 0));
  nt2::container::table<T> ab = nt2::cons<T>(nt2::of_size(1, 6), 1, 4, 10, 16, 17, 12);
  NT2_TEST_EQUAL(ab,conv(a, b));
  NT2_TEST_EQUAL(conv(a, c), nt2::zeros(1, 3, nt2::meta::as_<T>()));
  NT2_TEST_EQUAL(conv(c, b), nt2::zeros(1, 2, nt2::meta::as_<T>()));
  NT2_TEST_EQUAL(conv(b, b), nt2::cons<T>(nt2::of_size(1, 5), 1, 4, 10, 12, 9));
}

NT2_TEST_CASE_TPL ( conv_real__2_0,  NT2_REAL_TYPES)
{
  using nt2::conv;
  using nt2::tag::conv_;
  T a = T(1.0);
  T b = T(0.0);
  T c = T(2.0);
  nt2::container::table<T> aa =  nt2::_(T(1), T(1));
  nt2::container::table<T> bb =  nt2::_(T(0), T(0));
  nt2::container::table<T> ab = T(0);
  NT2_TEST_EQUAL(ab,conv(aa, bb));
  NT2_TEST_EQUAL(ab,conv(a, b));
  NT2_TEST_EQUAL(c,conv(a, c));
  NT2_TEST_EQUAL(ab,conv(aa, b));
  NT2_TEST_EQUAL(ab,conv(a, bb));
}

