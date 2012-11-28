/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::nbtrue function"

#include <nt2/table.hpp>
#include <nt2/include/functions/toint.hpp>
#include <nt2/include/functions/is_not_nan.hpp>
#include <nt2/include/functions/of_size.hpp>
#include <nt2/include/functions/numel.hpp>
#include <nt2/include/functions/size.hpp>
#include <nt2/include/functions/nbtrue.hpp>
#include <nt2/include/functions/sb2b.hpp>
#include <nt2/include/functions/is_greater.hpp>
#include <nt2/include/functions/if_one_else_zero.hpp>
#include <nt2/include/functions/sb2b.hpp>
#include <nt2/include/functions/sum.hpp>
#include <nt2/include/functions/cast.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/ten.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>

NT2_TEST_CASE_TPL( nbtrue_scalar, (float)(double))//NT2_TYPES )
{
  T x = nt2::nbtrue(1);
  NT2_TEST_EQUAL( x, 1 );

  x = nt2::nbtrue(1,1);
  NT2_TEST_EQUAL( x, 1 );

  x = nt2::nbtrue(1,2);
  NT2_TEST_EQUAL( x, 1) ;

  x = nt2::nbtrue(0,2);
  NT2_TEST_EQUAL( x, 0) ;

}

NT2_TEST_CASE_TPL( nbtrue_expr, NT2_TYPES )
{
  using nt2::_;
  typedef typename nt2::meta::as_integer<T>::type itype_t;
  nt2::table<T> y( nt2::of_size(5,3) );
  nt2::table<T> y1;
  nt2::table<T> sy1, sy, sy2, sy3;
  for(int j=1;j<=3;j++)
    for(int i=1;i<=5;i++)
      y(i,j) = (i > j) || (j == 2)|| (i == 1);
  display("y", y);

  sy  = nt2::nbtrue(y, 1);
  sy2 = nt2::sum(y, 1);
  for(int j=1;j<=3;j++)
    NT2_TEST_EQUAL(sy2(j) , sy(j));
  NT2_DISPLAY(sy);
  NT2_DISPLAY(sy2);

  sy = nt2::nbtrue(y, 2);
  sy2 =  nt2::sum(y, 2);
  for(int j=1;j<=5;j++)
    NT2_TEST_EQUAL(sy2(j) , sy(j));
  NT2_DISPLAY(sy);
  NT2_DISPLAY(sy2);

  sy = nt2::nbtrue(y, 3);
  sy2 =  nt2::sum(y, 3);
  for(int j=1;j<=3;j++)
    for(int i=1;i<=5;i++)
      NT2_TEST_EQUAL(sy2(i, j), sy(i, j));
  NT2_DISPLAY(sy);
  NT2_DISPLAY(sy2);

  sy = nt2::nbtrue(y(_));
  sy2 =  nt2::sum(y(_));
  NT2_DISPLAY(sy);
  NT2_DISPLAY(sy2);

 }

NT2_TEST_CASE_TPL( nbtrue_expr1, NT2_REAL_TYPES )
{
  typedef typename nt2::meta::as_logical<T>::type lT;
  nt2::table<T> y( nt2::of_size(5,3) );
  for(int j=1;j<=3;j++)
    for(int i=1;i<=5;i++)
      y(i,j) = (i > j) || (j == 2)|| (i == 1) ? T(1) : nt2::Nan<T>() ;
  display("y", y);

  NT2_DISPLAY(nbtrue(y));
  NT2_DISPLAY(nbtrue(nt2::is_not_nan(y)));
  NT2_DISPLAY(nt2::is_not_nan(y));
  NT2_DISPLAY(nt2::if_one_else_zero(nt2::is_not_nan(y)));
  NT2_DISPLAY(nt2::sum(nt2::if_one_else_zero(nt2::is_not_nan(y))));
  nt2::table<T> s = nt2::if_one_else_zero(nt2::is_not_nan(y));
  NT2_DISPLAY(s);
  NT2_DISPLAY(nt2::sum(s));

}
