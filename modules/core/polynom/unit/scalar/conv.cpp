//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 polynom toolbox - conv"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of polynom components
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 06/03/2011
///
#include <nt2/include/functions/conv.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/table.hpp>

NT2_TEST_CASE_TPL ( conv_real__1_0,  NT2_REAL_TYPES)
{
  using nt2::conv;
  using nt2::tag::conv_;
  nt2::table<T> a =  nt2::_(T(1), T(4));
  nt2::table<T> b =  nt2::_(T(1), T(3));
  NT2_DISPLAY(a);
  NT2_DISPLAY(b);
  nt2::table<T> c(nt2::of_size(1, 0));
  nt2::table<T> ab = cons(nt2::of_size(1, 6), 1, 4, 10, 16, 17, 12);
  NT2_DISPLAY(ab);
  NT2_DISPLAY(conv(a, b));
  NT2_TEST_EQUAL(ab,conv(a, b));
  NT2_TEST_EQUAL(conv(a, c), nt2::zeros(1, 3, nt2::meta::as_<T>()));
  NT2_TEST_EQUAL(conv(c, b), nt2::zeros(1, 2, nt2::meta::as_<T>()));
  NT2_TEST_EQUAL(conv(b, b), nt2::cons<T>(nt2::of_size(1, 5), 1, 4, 10, 12, 9));
}


