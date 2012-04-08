/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::reshape function"

#include <nt2/table.hpp>
#include <nt2/include/functions/reshape.hpp>
#include <nt2/include/functions/size.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/ndims.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>

NT2_TEST_CASE_TPL( reshape_ofsize, (float) )
{
  nt2::table<T> r;
  nt2::table<T, nt2::_2D> y( nt2::of_size(4,4) );

  for(int j=1;j<=4;j++)
    for(int i=1;i<=4;i++)
      y(i,j) = T(i + 10*j);

  r = nt2::reshape(y, nt2::of_size(2,2,2,2) );

  NT2_TEST_EQUAL( nt2::ndims(r)  , 4 );
  NT2_TEST_EQUAL( nt2::size(r,1) , 2 );
  NT2_TEST_EQUAL( nt2::size(r,2) , 2 );
  NT2_TEST_EQUAL( nt2::size(r,3) , 2 );
  NT2_TEST_EQUAL( nt2::size(r,4) , 2 );

  for(int l=1;l<=2;l++)
   for(int k=1;k<=2;k++)
    for(int j=1;j<=2;j++)
     for(int i=1;i<=2;i++)
      NT2_TEST_EQUAL( T(r(i,j,k,l)) , T(y(i+2*(j-1),k+2*(l-1))) );

  r = nt2::reshape(y, nt2::of_size(2,2,4) );

  NT2_TEST_EQUAL( nt2::ndims(r)  , 3 );
  NT2_TEST_EQUAL( nt2::size(r,1) , 2 );
  NT2_TEST_EQUAL( nt2::size(r,2) , 2 );
  NT2_TEST_EQUAL( nt2::size(r,3) , 4 );

   for(int k=1;k<=4;k++)
    for(int j=1;j<=2;j++)
     for(int i=1;i<=2;i++)
      NT2_TEST_EQUAL( T(r(i,j,k)) , T(y(i+2*(j-1),k)) );

  r = nt2::reshape(y, nt2::of_size(2,8) );

  NT2_TEST_EQUAL( nt2::ndims(r)  , 2 );
  NT2_TEST_EQUAL( nt2::size(r,1) , 2 );
  NT2_TEST_EQUAL( nt2::size(r,2) , 8 );

    for(int j=1;j<=8;j++)
     for(int i=1;i<=2;i++)
      NT2_TEST_EQUAL( T(r(i,j)) , T(y(i+2*((j-1)%2),(j-1)/2+1)) );
}

NT2_TEST_CASE_TPL( reshape_size, (float) )
{
  nt2::table<T> r;
  nt2::table<T, nt2::_2D> y( nt2::of_size(4,4) );

  for(int j=1;j<=4;j++)
    for(int i=1;i<=4;i++)
      y(i,j) = T(i + 10*j);

  r = nt2::reshape(y,2,2,2,2);

  NT2_TEST_EQUAL( nt2::ndims(r)  , 4 );
  NT2_TEST_EQUAL( nt2::size(r,1) , 2 );
  NT2_TEST_EQUAL( nt2::size(r,2) , 2 );
  NT2_TEST_EQUAL( nt2::size(r,3) , 2 );
  NT2_TEST_EQUAL( nt2::size(r,4) , 2 );

  for(int l=1;l<=2;l++)
   for(int k=1;k<=2;k++)
    for(int j=1;j<=2;j++)
     for(int i=1;i<=2;i++)
      NT2_TEST_EQUAL( T(r(i,j,k,l)) , T(y(i+2*(j-1),k+2*(l-1))) );

  r = nt2::reshape(y,2,2,4);

  NT2_TEST_EQUAL( nt2::ndims(r)  , 3 );
  NT2_TEST_EQUAL( nt2::size(r,1) , 2 );
  NT2_TEST_EQUAL( nt2::size(r,2) , 2 );
  NT2_TEST_EQUAL( nt2::size(r,3) , 4 );

   for(int k=1;k<=4;k++)
    for(int j=1;j<=2;j++)
     for(int i=1;i<=2;i++)
      NT2_TEST_EQUAL( T(r(i,j,k)) , T(y(i+2*(j-1),k)) );

  r = nt2::reshape(y, 2,8 );

  NT2_TEST_EQUAL( nt2::ndims(r)  , 2 );
  NT2_TEST_EQUAL( nt2::size(r,1) , 2 );
  NT2_TEST_EQUAL( nt2::size(r,2) , 8 );

    for(int j=1;j<=8;j++)
     for(int i=1;i<=2;i++)
      NT2_TEST_EQUAL( T(r(i,j)) , T(y(i+2*((j-1)%2),(j-1)/2+1)) );
}

NT2_TEST_CASE_TPL( reshape_expr, (float) )
{
  nt2::table<T, nt2::_4D> r4;
  nt2::table<T, nt2::_3D> r3;
  nt2::table<T, nt2::_2D> r2;
  nt2::table<T, nt2::_2D> y( nt2::of_size(4,4) );

  for(int j=1;j<=4;j++)
    for(int i=1;i<=4;i++)
      y(i,j) = T(i + 10*j);

  r4 = nt2::reshape(y, nt2::size( nt2::ones(2,2,2,2) ) );

  NT2_TEST_EQUAL( nt2::ndims(r4)  , 4 );
  NT2_TEST_EQUAL( nt2::size(r4,1) , 2 );
  NT2_TEST_EQUAL( nt2::size(r4,2) , 2 );
  NT2_TEST_EQUAL( nt2::size(r4,3) , 2 );
  NT2_TEST_EQUAL( nt2::size(r4,4) , 2 );

  for(int l=1;l<=2;l++)
   for(int k=1;k<=2;k++)
    for(int j=1;j<=2;j++)
     for(int i=1;i<=2;i++)
      NT2_TEST_EQUAL( T(r4(i,j,k,l)) , T(y(i+2*(j-1),k+2*(l-1))) );

  r3 = nt2::reshape(y, nt2::size( nt2::ones(2,2,4) ) );

  NT2_TEST_EQUAL( nt2::ndims(r3)  , 3 );
  NT2_TEST_EQUAL( nt2::size(r3,1) , 2 );
  NT2_TEST_EQUAL( nt2::size(r3,2) , 2 );
  NT2_TEST_EQUAL( nt2::size(r3,3) , 4 );

   for(int k=1;k<=4;k++)
    for(int j=1;j<=2;j++)
     for(int i=1;i<=2;i++)
      NT2_TEST_EQUAL( T(r3(i,j,k)) , T(y(i+2*(j-1),k)) );

  r2 = nt2::reshape(y, nt2::size( nt2::ones(2,8) ) );

  NT2_TEST_EQUAL( nt2::ndims(r2)  , 2 );
  NT2_TEST_EQUAL( nt2::size(r2,1) , 2 );
  NT2_TEST_EQUAL( nt2::size(r2,2) , 8 );

    for(int j=1;j<=8;j++)
     for(int i=1;i<=2;i++)
      NT2_TEST_EQUAL( T(r2(i,j)) , T(y(i+2*((j-1)%2),(j-1)/2+1)) );
}

NT2_TEST_CASE_TPL( incorrect_reshape, (float) )
{
  nt2::table<T> r;
  nt2::table<T, nt2::_2D> y( nt2::of_size(4,4) );

  NT2_TEST_ASSERT(r = nt2::reshape(y, nt2::of_size(3,8) ));
  NT2_TEST_ASSERT(r = nt2::reshape(y, nt2::of_size(2,8,2) ));
  NT2_TEST_ASSERT(r = nt2::reshape(y, nt2::of_size(1,1,1,32) ));

  NT2_TEST_ASSERT(r = nt2::reshape(y, nt2::size( nt2::ones(3,8) )       ));
  NT2_TEST_ASSERT(r = nt2::reshape(y, nt2::size( nt2::ones(2,8,2) )     ));
  NT2_TEST_ASSERT(r = nt2::reshape(y, nt2::size( nt2::ones(1,1,1,32) )  ));

  NT2_TEST_ASSERT(r = nt2::reshape(y, 3,8)      );
  NT2_TEST_ASSERT(r = nt2::reshape(y, 2,8,2)    );
  NT2_TEST_ASSERT(r = nt2::reshape(y, 1,1,1,32) );
}
