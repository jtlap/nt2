/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2 container subscript"

#include <nt2/table.hpp>
#include <nt2/include/functions/extent.hpp>
#include <nt2/include/functions/of_size.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

NT2_TEST_CASE( integral_subscript )
{
  using nt2::table;
  using nt2::of_size;
  typedef double T;

  table<T> a0( of_size(5,4,3,2) );

  //============================================================================
  // 1D subscript
  //============================================================================
  for(int j=1;j<=5*4*3*2;j++) a0(j) = T(j);

  int ii(1);
  for(int l=1;l<=2;l++)
    for(int k=1;k<=3;k++)
      for(int j=1;j<=4;j++)
        for(int i=1;i<=5;i++)
        {
          NT2_TEST_EQUAL( T(a0(i,j,k,l)) , T(ii));
          ii++;
        }

  //============================================================================
  // 2D subscript
  //============================================================================
  for(int j=1;j<=4*3*2;j++)
    for(int i=1;i<=5;i++)
      a0(i,j) = T(i + 10*j);

  int jj(1);

  for(int l=1;l<=2;l++)
    for(int k=1;k<=3;k++)
      for(int j=1;j<=4;j++)
      {
        ii = 1;
        for(int i=1;i<=5;i++)
        {
          NT2_TEST_EQUAL( T(a0(i,j,k,l)) , T(ii + 10*jj));
          ii++;
        }
        jj++;
      }
  
  //============================================================================
  // 3D subscript
  //============================================================================
  for(int k=1;k<=3*2;k++)
    for(int j=1;j<=4;j++)
      for(int i=1;i<=5;i++)
        a0(i,j,k) = T(i + 10*j + 100*k);

  int kk(1);

  for(int l=1;l<=2;l++)
    for(int k=1;k<=3;k++)
    {
      jj = 1;
      for(int j=1;j<=4;j++)
      {
        ii = 1;
        for(int i=1;i<=5;i++)
        {
          NT2_TEST_EQUAL( T(a0(i,j,k,l)) , T(ii + 10*jj + 100*kk));
          ii++;
        }
        jj++;
      }
      kk++;
    }

  //============================================================================
  // 4D subscript
  //============================================================================
  for(int l=1;l<=2;l++)
    for(int k=1;k<=3;k++)
      for(int j=1;j<=4;j++)
        for(int i=1;i<=5;i++)
          a0(i,j,k,l) = T(i + 10*j + 100*k + 1000*l);

  for(int l=1;l<=2;l++)
    for(int k=1;k<=3;k++)
      for(int j=1;j<=4;j++)
        for(int i=1;i<=5;i++)
          NT2_TEST_EQUAL( T(a0(i,j,k,l)) , T(i + 10*j + 100*k + 1000*l) );
}

NT2_TEST_CASE( integral_subscript_extent )
{
  using nt2::table;
  using nt2::of_size;
  typedef double T;

  table<T> a0( of_size(5,4,3,2) );

  NT2_TEST( nt2::extent( a0(1)       ) == of_size(1) );
  NT2_TEST( nt2::extent( a0(1,1)     ) == of_size(1) );
  NT2_TEST( nt2::extent( a0(1,1,1)   ) == of_size(1) );
  NT2_TEST( nt2::extent( a0(1,1,1,1) ) == of_size(1) );
}

NT2_TEST_CASE( colon_subscript )
{
  using nt2::table;
  using nt2::of_size;
  using nt2::_;
  typedef double T;

  table<T> a0( of_size(5,4,3,2) );

  for(int l=1;l<=2;l++)
   for(int k=1;k<=3;k++)
    for(int j=1;j<=4;j++)
     for(int i=1;i<=5;i++)
      a0(i,j,k,l) = T(i + 10*j + 100*k + 1000*l);

  //============================================================================
  // 1D subscript
  //============================================================================
  {
/*
    table<T> a1 = a0(_);
    std::cout << a1(1) << "\n";
    std::cout << a1(5) << "\n";
    std::cout << a1(10) << "\n";
    std::cout << a1(15) << "\n";
    std::cout << a1(20) << "\n";
*/
  }

  //============================================================================
  // 2D subscript
  //============================================================================
  {
    table<T> a1 = a0(_,_);

    NT2_TEST( nt2::extent( a1 ) == of_size(5,24) );
    for(int j=1;j<=24;j++)
     for(int i=1;i<=5;i++)
      NT2_TEST_EQUAL( T(a1(i,j)), T(a0(i,j)) );

    for(int r=1;r<=5;r++)
    {
      table<T> a2 = a0(r,_);
      NT2_TEST( nt2::extent( a2 ) == of_size(1,24) );

      for(int i=1;i<=24;i++)
        NT2_TEST_EQUAL( T(a2(1,i)), T(a0(r,i)) );
    }

    for(int r=1;r<=24;r++)
    {
      table<T> a3 = a0(_,r);
      NT2_TEST( nt2::extent( a3 ) == of_size(5,1) );

      for(int i=1;i<=5;i++)
        NT2_TEST_EQUAL( T(a3(i,1)), T(a0(i,r)) );
    }
  }

  //============================================================================
  // 3D subscript
  //============================================================================
/*
  {  
    table<T> a1 = a0(_,_,_);

    NT2_TEST( nt2::extent( a1 ) == of_size(5,4,6) );
    for(int k=1;k<=6;k++)
     for(int j=1;j<=4;j++)
      for(int i=1;i<=5;i++)
       NT2_TEST_EQUAL( T(a1(i,j,k)), T(a0(i,j,k)) );


    for(int r=1;r<=5;r++)
    {
      table<T> a2 = a0(r,_,_);
      NT2_TEST( nt2::extent( a2 ) == of_size(1,4,6) );

      for(int j=1;j<=6;j++)
       for(int i=1;i<=4;i++)
        NT2_TEST_EQUAL( T(a2(1,i,j)), T(a0(r,i,j)) );
    }

    for(int r=1;r<=4;r++)
    {
      table<T> a2 = a0(_,r,_);
      NT2_TEST( nt2::extent( a2 ) == of_size(5,1,6) );

      for(int j=1;j<=6;j++)
       for(int i=1;i<=5;i++)
        NT2_TEST_EQUAL( T(a2(i,1,j)), T(a0(i,r,j)) );
    }

    for(int r=1;r<=6;r++)
    {
      table<T> a2 = a0(_,_,r);
      NT2_TEST( nt2::extent( a2 ) == of_size(5,4,1) );

      for(int j=1;j<=4;j++)
       for(int i=1;i<=5;i++)
        NT2_TEST_EQUAL( T(a2(i,j,1)), T(a0(i,j,r)) );
    }

  }
*/
/*
  //============================================================================
  // 4D subscript
  //============================================================================
*/
}

NT2_TEST_CASE( colon_subscript_extent )
{
  using nt2::table;
  using nt2::of_size;
  using nt2::_;
  typedef double T;

  table<T> a0( of_size(5,4,3,2) );

  NT2_TEST( nt2::extent( a0(_)       ) == of_size(120)     );

  NT2_TEST( nt2::extent( a0(_,1,1)   ) == of_size(5)       );
  NT2_TEST( nt2::extent( a0(1,_,_)   ) == of_size(1,4,6)   );
  NT2_TEST( nt2::extent( a0(1,_,1)   ) == of_size(1,4)     );
  NT2_TEST( nt2::extent( a0(1,1,_)   ) == of_size(1,1,6)   );

  NT2_TEST( nt2::extent( a0(_,_,_,_) ) == of_size(5,4,3,2) );
  NT2_TEST( nt2::extent( a0(_,_,_,1) ) == of_size(5,4,3)   );
  NT2_TEST( nt2::extent( a0(_,_,1,_) ) == of_size(5,4,1,2) );
  NT2_TEST( nt2::extent( a0(_,_,1,1) ) == of_size(5,4)     );
  NT2_TEST( nt2::extent( a0(_,1,_,_) ) == of_size(5,1,3,2) );
  NT2_TEST( nt2::extent( a0(_,1,_,1) ) == of_size(5,1,3)   );
  NT2_TEST( nt2::extent( a0(_,1,1,_) ) == of_size(5,1,1,2) );
  NT2_TEST( nt2::extent( a0(_,1,1,1) ) == of_size(5)       );
  NT2_TEST( nt2::extent( a0(1,_,_,_) ) == of_size(1,4,3,2) );
  NT2_TEST( nt2::extent( a0(1,_,_,1) ) == of_size(1,4,3)   );
  NT2_TEST( nt2::extent( a0(1,_,1,_) ) == of_size(1,4,1,2) );
  NT2_TEST( nt2::extent( a0(1,_,1,1) ) == of_size(1,4)     );
  NT2_TEST( nt2::extent( a0(1,1,_,_) ) == of_size(1,1,3,2) );
  NT2_TEST( nt2::extent( a0(1,1,_,1) ) == of_size(1,1,3)   );
  NT2_TEST( nt2::extent( a0(1,1,1,_) ) == of_size(1,1,1,2) );
}
