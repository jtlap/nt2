/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::inbtrue function"

#include <nt2/table.hpp>
#include <nt2/include/functions/toint.hpp>
#include <nt2/include/functions/of_size.hpp>
#include <nt2/include/functions/numel.hpp>
#include <nt2/include/functions/size.hpp>
#include <nt2/include/functions/inbtrue.hpp>
#include <nt2/include/functions/sb2b.hpp>
#include <nt2/include/functions/is_greater.hpp>
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
#include <nt2/sdk/unit/type_id.hpp>

NT2_TEST_CASE_TPL( inbtrue_scalar, (float)(double))//NT2_TYPES )
{
  nt2::int32_t x = nt2::inbtrue(1);
  NT2_TEST_EQUAL( x, 1 );

  x = nt2::inbtrue(1,1);
  NT2_TEST_EQUAL( x, 1 );

  x = nt2::inbtrue(1,2);
  NT2_TEST_EQUAL( x, 1) ;

  x = nt2::inbtrue(0,2);
  NT2_TEST_EQUAL( x, 0) ;

}

NT2_TEST_CASE_TPL( inbtrue_expr, NT2_TYPES )
{
  using nt2::_;
  typedef typename nt2::meta::as_integer<T>::type itype_t;
  nt2::table<T> y( nt2::of_size(5,3) );
  nt2::table<T> y1;
  nt2::table<itype_t> sy1, sy, sy2, sy3;
  for(int j=1;j<=3;j++)
    for(int i=1;i<=5;i++)
      y(i,j) = (i > j) || (j == 2)|| (i == 1);
  disp("y", y);

//   nt2::table<nt2::logical<T> > l;
//   l = gt(y, T(13));
//   disp("l ",  l);
//   nt2::table<itype_t > nb;
//   nb = nt2::inbtrue(l);
//   //  std::cout << nt2::type_id(inbtrue(l)) << std::endl;
//   disp("nb ",  inbtrue(l));
//   disp("nb ",  nb);

  sy  = nt2::inbtrue(y, 1);
  sy2 = nt2::cast<itype_t>(nt2::sum(y, 1));
  for(int j=1;j<=3;j++)
    NT2_TEST_EQUAL(sy2(j) , sy(j));
  NT2_DISP(sy);
  NT2_DISP(sy2); 

  sy = nt2::inbtrue(y, 2);
  sy2 =  nt2::cast<itype_t>(nt2::sum(y, 2));
  for(int j=1;j<=5;j++)
    NT2_TEST_EQUAL(sy2(j) , sy(j));
  NT2_DISP(sy);
  NT2_DISP(sy2); 

  sy = nt2::inbtrue(y, 3);
  sy2 =  nt2::cast<itype_t>(nt2::sum(y, 3));
  for(int j=1;j<=3;j++)
    for(int i=1;i<=5;i++)
      NT2_TEST_EQUAL(sy2(i, j), sy(i, j));
  NT2_DISP(sy);
  NT2_DISP(sy2); 

  sy = nt2::inbtrue(y(_));
  sy2 =  nt2::cast<itype_t>(nt2::sum(y(_)));
  NT2_DISP(sy);
  NT2_DISP(sy2); 

 }

