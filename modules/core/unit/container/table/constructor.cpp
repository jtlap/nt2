/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::table constructor checks"

#include <nt2/table.hpp>
#include <nt2/include/functions/extent.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

NT2_TEST_CASE( default_ctor )
{
  using nt2::table;
  using nt2::of_size;

  table<float> x;

  NT2_TEST( nt2::extent(x) == of_size(0) );
}

NT2_TEST_CASE( of_size_ctor )
{
  using nt2::table;
  using nt2::of_size;
  using nt2::of_size_;

  {
    table<float> x( of_size(2,3) );
    NT2_TEST( nt2::extent(x) == of_size(2,3) );
  }

  {
    table<float> x( of_size(2,3,4) );
    NT2_TEST( nt2::extent(x) == of_size(2,3,4) );
  }

  {
    table<float> x( of_size(2,3,4,5) );
    NT2_TEST( nt2::extent(x) == of_size(2,3,4,5) );
  }

  {
    table<float, of_size_<2,3> > x;
    NT2_TEST( nt2::extent(x) == of_size(2,3) );
  }

  {
    table<float, of_size_<2,3,4> > x;
    NT2_TEST( nt2::extent(x) == of_size(2,3,4) );
  }

  {
    table<float, of_size_<2,3,4,5> > x;
    NT2_TEST( nt2::extent(x) == of_size(2,3,4,5) );
  }
}

NT2_TEST_CASE( range_ctor )
{
  using nt2::table;
  using nt2::of_size;

  float data[] =  {
                    1,2,3
                  , 4,5,6
                  };
                                    
  table<float> x( of_size(3,2), &data[0], &data[0] + 6 );
  NT2_TEST( nt2::extent(x) == of_size(3,2) );

  for(int j=1;j<=2;++j)
   for(int i=1;i<=3;++i)
      NT2_TEST_EQUAL( x(i,j), data[(i-1) + (j-1)*3]) ;
}
