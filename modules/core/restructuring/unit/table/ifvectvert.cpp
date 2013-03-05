//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2::ifvectvert function"

#include <nt2/table.hpp>
#include <nt2/include/functions/ifvectvert.hpp>
#include <nt2/include/functions/isequal.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>

NT2_TEST_CASE_TPL( ifvectvert_scalar, (float) )
{
  NT2_TEST_EQUAL(nt2::ifvectvert(T(1)), T(1));
}


NT2_TEST_CASE_TPL( ifvectvert, (float) )
{
  nt2::table<T> r, r2;
  nt2::table<T, nt2::_2D> y( nt2::ones(4,4, nt2::meta::as_<T>()) );
  nt2::table<T, nt2::of_size_<4, 4> > y2 = nt2::ones(4, 4, nt2::meta::as_<T>());
  nt2::table<T, nt2::of_size_<1, 16> > y3= nt2::ones(1, 16, nt2::meta::as_<T>());;

  for(int j=1;j<=4;j++)
    for(int i=1;i<=4;i++)
      y(i,j) = T(i + 10*j);

  r = nt2::ifvectvert(y);
  r2 = nt2::ifvectvert(y2);
  NT2_TEST(nt2::isequal(y, r));
  NT2_TEST(nt2::isequal(y2, r2));

  y = nt2::reshape(y, 1, 16);
  y3 = nt2::reshape(y2, 1, 16);
  r = nt2::ifvectvert(y);
  r2 = nt2::ifvectvert(y3);
  NT2_TEST(nt2::isequal(y(nt2::_), r));
  NT2_TEST(nt2::isequal(y2(nt2::_), r2));

  y = y(nt2::_);
  r = nt2::ifvectvert(y);
  NT2_TEST(nt2::isequal(y, r));
}
