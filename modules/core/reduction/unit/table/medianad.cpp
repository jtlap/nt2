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
#include <nt2/include/functions/medianad.hpp>
#include <nt2/include/functions/sum.hpp>
#include <nt2/include/functions/size.hpp>
#include <nt2/include/functions/firstnonsingleton.hpp>
#include <nt2/include/functions/isequal.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>

NT2_TEST_CASE_TPL( medianad_scalar, NT2_TYPES )
{
  T x = nt2::medianad(T(42));
  NT2_TEST_EQUAL( x, T(0) );

  x = nt2::medianad(T(42),1);
  NT2_TEST_EQUAL( x, T(0) );

  x = nt2::medianad(T(42),0);
  NT2_TEST_EQUAL( x, T(0) );

}

NT2_TEST_CASE_TPL( medianad, NT2_TYPES )
{
  nt2::table<T> y( nt2::of_size(4,3,3) );
  nt2::table<T> sy;
  nt2::table<T> sy2;

  int k = 0; 
  for(int l=1;l<=3;l++)
    for(int j=1;j<=3;j++)
      for(int i=1;i<=4;i++)
        y(i,j,l) = ++k;
  display("y", y);
  sy2 = nt2::medianad(y);
  display("sy2", sy2);

  sy2 = nt2::medianad(y, 1);
  display("sy2", sy2);

  sy2 = nt2::medianad(y, 2);
  display("sy2", sy2);

  sy2 = nt2::medianad(y, 3);
  display("sy2", sy2);
  
  sy2 = nt2::medianad(y, 4);
  display("sy2", sy2);

}

NT2_TEST_CASE_TPL( medianad_2, NT2_TYPES )
{
  nt2::table<T> y( nt2::of_size(4,3,3) );
  nt2::table<T> sy2;

  int k = 0; 
  for(int l=1;l<=3;l++)
    for(int j=1;j<=3;j++)
      for(int i=1;i<=4;i++)
        y(i,j,l) = ++k;
  sy2 = nt2::medianad(y);
  NT2_TEST(nt2::isequal(sy2,medianad(y)));
  sy2 = nt2::medianad(y, 1);
  NT2_TEST(nt2::isequal(sy2,medianad(y, 1)));
  sy2 = nt2::medianad(y, 2);
  NT2_TEST(nt2::isequal(sy2,medianad(y, 2)));
  sy2 = nt2::medianad(y, 3);
  NT2_TEST(nt2::isequal(sy2,medianad(y, 3)));
  sy2 = nt2::medianad(y, 4);
  NT2_TEST(nt2::isequal(sy2,medianad(y, 4)));


}
