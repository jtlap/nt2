/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::sum1 function"

#include <nt2/table.hpp>
#include <nt2/include/functions/median.hpp>
#include <nt2/include/functions/sum.hpp>
#include <nt2/include/functions/size.hpp>
#include <nt2/include/functions/firstnonsingleton.hpp>
#include <nt2/include/functions/isequal.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/horzcat.hpp>

NT2_TEST_CASE_TPL( median_scalar, NT2_REAL_TYPES )
{
  T x = nt2::median(T(42));
  NT2_TEST_EQUAL( x, T(42) );

  x = nt2::median(T(42),1);
  NT2_TEST_EQUAL( x, T(42) );

  x = nt2::median(T(42),0);
  NT2_TEST_EQUAL( x, T(42) );

}


NT2_TEST_CASE_TPL( median_2, NT2_REAL_TYPES )
{
  nt2::table<T> y( nt2::of_size(4,3) );
  nt2::table<T> sy2;
  nt2::table<T> r1 = nt2::_(T(2.5), T(4), T(10.5));
  nt2::table<T> r2 = nt2::colvect(nt2::_(T(5), T(8)));
  int k = 0;
  for(int j=1;j<=3;j++)
    for(int i=1;i<=4;i++)
      y(i,j) = ++k;
  sy2 = nt2::median(y);
  NT2_TEST_EQUAL(sy2, r1);
  NT2_DISPLAY(sy2);
  sy2 = nt2::median(y, 1);
  NT2_TEST_EQUAL(sy2, r1);
  NT2_DISPLAY(sy2);
  sy2 = nt2::median(y, 2);
  NT2_TEST_EQUAL(sy2, r2);
  NT2_DISPLAY(sy2);
  sy2 = nt2::median(y, 3);
  NT2_TEST_EQUAL(sy2, y);
  NT2_DISPLAY(sy2);
  sy2 = nt2::median(y, 4);
  NT2_TEST_EQUAL(sy2, y);
  NT2_DISPLAY(sy2);
}

NT2_TEST_CASE_TPL( medianmore, (float)(double))//NT2_TYPES )
{
  nt2::table<T> y;
  y =  nt2::horzcat(nt2::horzcat(nt2::ones(4, 1, nt2::meta::as_<T>()),
                                 nt2::zeros(4, 1, nt2::meta::as_<T>())),
                    nt2::ones(4, 1, nt2::meta::as_<T>()));

  nt2::table<T> sy;
  sy =  median(y, 2);
  NT2_DISPLAY(y);
  NT2_DISPLAY(sy);
  NT2_TEST_EQUAL(sy, nt2::ones(4, 1, nt2::meta::as_<T>()));
}
