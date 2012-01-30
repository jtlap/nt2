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
      NT2_TEST_EQUAL( float(x(i,j)), data[(i-1) + (j-1)*3]) ;
}

NT2_TEST_CASE( shared_ctor )
{
  using nt2::table;
  using nt2::of_size;
  using nt2::shared_;
  using nt2::settings;
  using nt2::no_padding_;
  using nt2::global_padding_;
  using nt2::lead_padding_;
  using nt2::share;

  float data[] =  {
                    1,2,3,0
                  , 4,5,6,0
                  , 0,0,0,0
                  , 0,0,0,0
                  };
  {
    table<float, settings(shared_,no_padding_)>
    x(of_size(4,2), share(&data[0], &data[0] + 8));

    NT2_TEST( nt2::extent(x) == of_size(4,2) );

    for(int j=1;j<=2;++j)
     for(int i=1;i<=4;++i)
        NT2_TEST_EQUAL( float(x(i,j)), data[(i-1) + (j-1)*4]) ;
  }

  {
    table<float, settings(shared_,lead_padding_<4>)>
    x(of_size(3,2), share(&data[0], &data[0] + 8));

    NT2_TEST( nt2::extent(x) == of_size(3,2) );

    for(int j=1;j<=2;++j)
     for(int i=1;i<=3;++i)
        NT2_TEST_EQUAL( float(x(i,j)), data[(i-1) + (j-1)*4]) ;
  }

  {
    table < float, settings ( shared_ , global_padding_<16>
                                      , lead_padding_<4>
                            )
          > x(of_size(3,2), share(&data[0], &data[0] + 16));

    NT2_TEST( nt2::extent(x) == of_size(3,2) );

    for(int j=1;j<=2;++j)
     for(int i=1;i<=3;++i)
        NT2_TEST_EQUAL( float(x(i,j)), data[(i-1) + (j-1)*4]) ;
  }

  {
    float f = 1.f;
    
    table < float, settings ( shared_ , no_padding_ )
          > x(nt2::extent(f), share(&f, &f + 1));

    NT2_TEST( nt2::extent(x) == of_size(1) );

    NT2_TEST_EQUAL( float(x(1,1)), 1.f );
    x = 2.f;
    NT2_TEST_EQUAL( float(x(1,1)), 2.f );
  }
}
