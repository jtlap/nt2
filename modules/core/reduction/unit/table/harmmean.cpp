//==============================================================================
//          Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================

#include <nt2/table.hpp>
#include <nt2/include/functions/harmmean.hpp>
#include <nt2/include/functions/sum.hpp>
#include <nt2/include/functions/rec.hpp>
#include <nt2/include/functions/size.hpp>
#include <nt2/include/functions/firstnonsingleton.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>

NT2_TEST_CASE_TPL( harmmean_scalar, NT2_REAL_TYPES )
{
  T x = nt2::harmmean(T(42));
  NT2_TEST_EQUAL( x, T(42) );

  x = nt2::harmmean(T(42),1);
  NT2_TEST_EQUAL( x, T(42) );

  x = nt2::harmmean(T(42),0);
  NT2_TEST_EQUAL( x, T(42) );

}

NT2_TEST_CASE_TPL( harmmean, NT2_REAL_TYPES )
{
  using nt2::sum;
  using nt2::rec;
  nt2::table<T> y( nt2::of_size(5,3) );
  nt2::table<T> sy;
  nt2::table<T> sy2;

  for(int j=1;j<=3;j++)
    for(int i=1;i<=5;i++)
      y(i,j) = i + 10*j;

  display("y", y);
  sy = rec(sum(rec(y)))*T(nt2::size(y, nt2::firstnonsingleton(y)));
  sy2 = nt2::harmmean(y);
  NT2_TEST_EQUAL(sy, sy2);

  sy = rec(nt2::sum(rec(y), 1))*T(nt2::size(y, 1));
  sy2 = nt2::harmmean(y, 1);
  NT2_TEST_EQUAL(sy, sy2);

  sy = rec(nt2::sum(rec(y), 2))*T(nt2::size(y, 2));
  sy2 = nt2::harmmean(y, 2);
  NT2_TEST_EQUAL(sy, sy2);

  sy = rec(nt2::sum(rec(y), 3))*T(nt2::size(y, 3));
  sy2 = nt2::harmmean(y, 3);
  NT2_TEST_EQUAL(sy, sy2);
}

