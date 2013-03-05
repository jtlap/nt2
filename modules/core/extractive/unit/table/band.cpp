//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2::band function"

#include <nt2/table.hpp>
#include <nt2/include/functions/band.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

NT2_TEST_CASE_TPL( band, NT2_TYPES )
{
  nt2::table<T> x,y( nt2::of_size(4,5) );

  for(int j=1;j<=5;j++)
    for(int i=1;i<=4;i++)
      y(i,j) = i + 10*j;

  x = nt2::diagonal(y);

  for(int j=1;j<=5;j++)
    for(int i=1;i<=4;i++)
      NT2_TEST_EQUAL( x(i,j), (i==j) ? y(i,j) : T(0));
}

NT2_TEST_CASE_TPL( offset_band1, NT2_TYPES )
{
  nt2::table<T> x,y( nt2::of_size(4,5) );

  for(int j=1;j<=5;j++)
    for(int i=1;i<=4;i++)
      y(i,j) = i + 10*j;

  x = nt2::band(y,1);

  for(int j=1;j<=5;j++)
    for(int i=1;i<=4;i++)
      NT2_TEST_EQUAL( x(i,j), ((i>=(j-1))&&(i<=j+1)) ? y(i,j) : T(0));

  x = nt2::band(y,1,2);

  for(int j=1;j<=5;j++)
    for(int i=1;i<=4;i++)
      NT2_TEST_EQUAL( x(i,j), ((i>=(j-1))&&(i<=j+2))? y(i,j) : T(0));
}
