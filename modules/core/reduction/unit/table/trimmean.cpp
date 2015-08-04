//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================

#include <nt2/table.hpp>
#include <nt2/include/functions/trimmean.hpp>
#include <nt2/include/functions/sum.hpp>
#include <nt2/include/functions/rec.hpp>
#include <nt2/include/functions/median.hpp>
#include <nt2/include/functions/size.hpp>
#include <nt2/include/functions/firstnonsingleton.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>

NT2_TEST_CASE_TPL( trimmean_scalar, NT2_REAL_TYPES )
{
  T x = nt2::trimmean(T(42));
  NT2_TEST_EQUAL( x, T(42) );

  x = nt2::trimmean(T(42),1);
  NT2_TEST_EQUAL( x, T(42) );

  x = nt2::trimmean(T(42),0);
  NT2_TEST_EQUAL( x, T(42) );

}

NT2_TEST_CASE_TPL( trimmean, NT2_REAL_TYPES )
{
  nt2::table<T> y( nt2::of_size(5,3) );
  nt2::table<T> sy;
  nt2::table<T> sy2;

  for(int j=1;j<=3;j++)
    for(int i=1;i<=5;i++)
      y(i,j) = (6-i) + 10*(4-j);

  display("y", y);
  sy = nt2::sum(y)/T(nt2::size(y, nt2::firstnonsingleton(y)));
  sy2 = nt2::trimmean(y, T(1), nt2::both_, 1);
  NT2_TEST_EQUAL(sy, sy2);


  sy = nt2::median(y, 1);
  sy2 = nt2::trimmean(y, T(0), nt2::both_, 1);
  NT2_TEST_EQUAL(sy, sy2);

  sy = nt2::mean(y(nt2::_(2, 4), nt2::_), 1);
  sy2 = nt2::trimmean(y, T(0.5), nt2::both_, 1);
  NT2_TEST_EQUAL(sy, sy2);

  sy2 = nt2::trimmean(y);
  NT2_TEST_EQUAL(sy, sy2);

  sy2 = nt2::trimmean(y, 1);
  NT2_TEST_EQUAL(sy, sy2);

  sy2 = nt2::trimmean(y, nt2::both_);
  NT2_TEST_EQUAL(sy, sy2);

  sy = nt2::mean(y(nt2::_(3, 5), nt2::_), 1);
  sy2 = nt2::trimmean(y, T(0.5), nt2::lower_, 1);
  NT2_TEST_EQUAL(sy, sy2);

  sy = nt2::mean(y(nt2::_(1, 3), nt2::_), 1);
  sy2 = nt2::trimmean(y, T(0.5), nt2::upper_, 1);
  NT2_TEST_EQUAL(sy, sy2);


  sy = median(y, 2);
  sy2 = nt2::trimmean(y, T(1), nt2::both_, 2);
  NT2_TEST_EQUAL(sy, sy2);

  sy = mean(y, 2);
  sy2 = nt2::trimmean(y, T(0), nt2::both_, 2);
  NT2_TEST_EQUAL(sy, sy2);
}
