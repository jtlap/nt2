//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================

#include <nt2/table.hpp>
#include <nt2/include/functions/band.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

NT2_TEST_CASE_TPL( band_types, NT2_TYPES )
{
  using boost::mpl::_;
  using nt2::meta::value_type_;

  nt2::table<T> x( nt2::of_size(4,4) );
  NT2_TEST_EXPR_TYPE( nt2::band(x)      , (value_type_<_>), (T));
  NT2_TEST_EXPR_TYPE( nt2::band(x,1)    , (value_type_<_>), (T));
  NT2_TEST_EXPR_TYPE( nt2::band(x,-1,1) , (value_type_<_>), (T));
}

NT2_TEST_CASE_TPL( band_scalar, NT2_TYPES )
{
  // Diretc diagonal
  T x = nt2::band(T(42));
  NT2_TEST_EQUAL( x, T(42) );

  x = nt2::diagonal(T(69));
  NT2_TEST_EQUAL( x, T(69) );

  // Include some amount of subdiagonal
  x = nt2::band(T(42),-1);
  NT2_TEST_EQUAL( x, T(0) );

  x = nt2::band(T(42),0);
  NT2_TEST_EQUAL( x, T(42) );

  x = nt2::band(T(42),1);
  NT2_TEST_EQUAL( x, T(42) );

  // Include some amount of sub/superdiagonal

  x = nt2::band(T(42),2,2);
  NT2_TEST_EQUAL( x, T(0) );


  x = nt2::band(T(42),-2,2);
  NT2_TEST_EQUAL( x, T(42) );

  x = nt2::band(T(42),-2,-2);
  NT2_TEST_EQUAL( x, T(0) );
}

NT2_TEST_CASE( band_assert )
{
  NT2_TEST_ASSERT(nt2::band(13,2,-2));

  nt2::table<double> x( nt2::of_size(2,5,3) );
  NT2_TEST_ASSERT(nt2::band(x));
  NT2_TEST_ASSERT(nt2::band(x,1));
  NT2_TEST_ASSERT(nt2::band(x,1,2));

  nt2::table<double> y( nt2::of_size(4,4) );
  NT2_TEST_ASSERT(nt2::band(y,-1));
  NT2_TEST_ASSERT(nt2::band(y,1,-2));
}

NT2_TEST_CASE_TPL( band, NT2_TYPES )
{
  nt2::table<T>   x
                , y( nt2::of_size(4,5) )
                , ref( nt2::of_size(4,5) );

  for(int j=1;j<=5;j++)
    for(int i=1;i<=4;i++)
      y(i,j) = i + 10*j;

  for(int j=1;j<=5;j++)
    for(int i=1;i<=4;i++)
      ref(i,j) = (i==j) ? y(i,j) : T(0);

  x = nt2::diagonal(y);

  NT2_TEST_EQUAL( x, ref );

  x = nt2::band(y,0);
  NT2_TEST_EQUAL( x, ref );

  for(int j=1;j<=5;j++)
    for(int i=1;i<=4;i++)
      ref(i,j) = ((i>=(j-1))&&(i<=j+1)) ? y(i,j) : T(0);

  x = nt2::band(y,1);
  NT2_TEST_EQUAL( x, ref );

  for(int j=1;j<=5;j++)
    for(int i=1;i<=4;i++)
      ref(i,j) = ((i>=(j-3))&&(i<=j-1)) ? y(i,j) : T(0);

  x = nt2::band(y,1,3);
  NT2_TEST_EQUAL( x, ref );

  for(int j=1;j<=5;j++)
    for(int i=1;i<=4;i++)
      ref(i,j) = ((i>=(j-1))&&(i<=j+1)) ? y(i,j) : T(0);

  x = nt2::band(y,-1,1);
  NT2_TEST_EQUAL( x, ref );

  for(int j=1;j<=5;j++)
    for(int i=1;i<=4;i++)
      ref(i,j) = ((i>=(j+1))&&(i<=j+3)) ? y(i,j) : T(0);

  x = nt2::band(y,-3,-1);
  NT2_TEST_EQUAL( x, ref );
}
