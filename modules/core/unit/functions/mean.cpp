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
#include <nt2/include/functions/mean.hpp>
#include <nt2/include/functions/sum.hpp>
#include <nt2/include/functions/size.hpp>
#include <nt2/include/functions/firstnonsingleton.hpp>
#include <nt2/include/functions/isequal.hpp>


#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>

NT2_TEST_CASE_TPL( mean_scalar, NT2_REAL_TYPES )
{
  T x = nt2::mean(T(42));
  NT2_TEST_EQUAL( x, T(42) );

  x = nt2::mean(T(42),1);
  NT2_TEST_EQUAL( x, T(42) );

  x = nt2::mean(T(42),0);
  NT2_TEST_EQUAL( x, T(42) );

}

NT2_TEST_CASE_TPL( mean, NT2_REAL_TYPES )
{
  nt2::table<T> y( nt2::of_size(5,3) );
  nt2::table<T> sy;
  nt2::table<T> sy2;


  for(int j=1;j<=3;j++)
    for(int i=1;i<=5;i++)
      y(i,j) = i + 10*j;
  display("y", y);
  sy = nt2::sum(y)/T(nt2::size(y, nt2::firstnonsingleton(y)));
  sy2 = nt2::mean(y);
  display("sy", sy);
  display("sy2", sy2);
  for(size_t j=1;j<=size(sy, 2);j++)
    for(size_t i=1;i<=size(sy, 1);i++)
      NT2_TEST_EQUAL(sy(i,j), sy2(i, j));

  sy = nt2::sum(y, 1)/T(nt2::size(y, 1));
  sy2 = nt2::mean(y, 1);
  display("sy", sy);
  display("sy2", sy2);
  for(size_t j=1;j<=size(sy, 2);j++)
    for(size_t i=1;i<=size(sy, 1);i++)
      NT2_TEST_EQUAL(sy(i,j), sy2(i, j));

  sy = nt2::sum(y, 2)/T(nt2::size(y, 2));
  sy2 = nt2::mean(y, 2);
  display("sy", sy);
  display("sy2", sy2);
  for(size_t j=1;j<=size(sy, 2);j++)
    for(size_t i=1;i<=size(sy, 1);i++)
      NT2_TEST_EQUAL(sy(i,j), sy2(i, j));

  sy = nt2::sum(y, 3)/T(nt2::size(y, 3));
  sy2 = nt2::mean(y, 3);
  display("sy", sy);
  display("sy2", sy2);
  for(size_t j=1;j<=size(sy, 2);j++)
    for(size_t i=1;i<=size(sy, 1);i++)
      NT2_TEST_EQUAL(sy(i,j), sy2(i, j));


}

NT2_TEST_CASE_TPL( mean_2, NT2_REAL_TYPES )
{
  nt2::table<T> y( nt2::of_size(5,3) );
  nt2::table<T> sy;
  nt2::table<T> sy2, syb;


  for(int j=1;j<=3;j++)
    for(int i=1;i<=5;i++)
      y(i,j) = i + 10*j;
  sy = nt2::sum(y)/T(nt2::size(y, nt2::firstnonsingleton(y)));
  syb= nt2::sum(y)*nt2::rec(T(nt2::size(y, nt2::firstnonsingleton(y)))); 
  sy2 = nt2::mean(y);
  NT2_TEST(nt2::isequal(sy2,  nt2::mean(y)));
  NT2_TEST(nt2::isequal(syb,  nt2::mean(y)));

  sy = nt2::sum(y, 1)/T(nt2::size(y, 1));
  sy2 = nt2::mean(y, 1);
  syb= nt2::sum(y, 1)*nt2::rec(T(nt2::size(y, 1))); 
  NT2_TEST(nt2::isequal(sy2,  nt2::mean(y, 1)));
  NT2_TEST(nt2::isequal(syb,  nt2::mean(y, 1)));


  sy = nt2::sum(y, 2)/T(nt2::size(y, 2));
  sy2 = nt2::mean(y, 2);
  syb= nt2::sum(y, 2)*nt2::rec(T(nt2::size(y, 2))); 
  NT2_TEST(nt2::isequal(sy2,  nt2::mean(y, 2)));
  NT2_TEST(nt2::isequal(syb,  nt2::mean(y, 2)));


  sy = nt2::sum(y, 3)/T(nt2::size(y, 3));
  sy2 = nt2::mean(y, 3);
  syb= nt2::sum(y, 3)*nt2::rec(T(nt2::size(y, 3))); 
  NT2_TEST(nt2::isequal(sy2,  nt2::mean(y, 3)));
  NT2_TEST(nt2::isequal(syb,  nt2::mean(y, 3)));
}
