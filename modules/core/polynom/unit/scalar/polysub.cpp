//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/polysub.hpp>
#include <nt2/include/functions/conv.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/table.hpp>

NT2_TEST_CASE_TPL ( polysub_1_0,  NT2_REAL_TYPES)
{

  using nt2::polysub;
  using nt2::tag::polysub_;
  nt2::table<T, nt2::_2D> a =  nt2::_(T(1), T(4));
  nt2::table<T, nt2::_2D> b =  nt2::_(T(1), T(2));
  nt2::table<T, nt2::_2D> c;
  T aab[] = { 1, 2, 2, 2};
  nt2::table<T> d(nt2::of_size(1, 4), &aab[0], &aab[4]);
  c = polysub(a, b);
  NT2_DISPLAY(polysub(a, b));
  NT2_DISPLAY(polysub(b, a));
  NT2_TEST_EQUAL(d,polysub(a, b));
  NT2_TEST_EQUAL(-d,polysub(b, a));
}


