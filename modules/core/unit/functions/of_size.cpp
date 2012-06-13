//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2::settings of_size helper"

#include <nt2/core/settings/settings.hpp>
#include <nt2/core/settings/size.hpp>
#include <nt2/core/functions/of_size.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

////////////////////////////////////////////////////////////////////////////////
// Test of_size initializations
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( init_of_size )
{
  using nt2::of_size_;

  of_size_<-1>     spec1;
  NT2_TEST_EQUAL( spec1.size(), 1u );
  NT2_TEST_EQUAL( spec1[0], 0u );

  of_size_<-1,-1>     spec2;
  NT2_TEST_EQUAL( spec2.size(), 2u );
  NT2_TEST_EQUAL( spec2[0], 0u );
  NT2_TEST_EQUAL( spec2[1], 1u );

  of_size_<-1,-1,-1>     spec3;
  NT2_TEST_EQUAL( spec3.size(), 3u );
  NT2_TEST_EQUAL( spec3[0], 0u );
  NT2_TEST_EQUAL( spec3[1], 1u );
  NT2_TEST_EQUAL( spec3[2], 1u );

  of_size_<-1,-1,-1,-1>     spec4;
  NT2_TEST_EQUAL( spec4.size(), 4u );
  NT2_TEST_EQUAL( spec4[0], 0u );
  NT2_TEST_EQUAL( spec4[1], 1u );
  NT2_TEST_EQUAL( spec4[2], 1u );
  NT2_TEST_EQUAL( spec4[2], 1u );
}

////////////////////////////////////////////////////////////////////////////////
// Test of_size pre-initializations in case of static sizes
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( pre_init_of_size )
{
  using nt2::of_size_;

  of_size_<42>     spec1;
  NT2_TEST_EQUAL( spec1.size(), 1u );
  NT2_TEST_EQUAL( spec1[0], 42u );

  of_size_<6,9>     spec2;
  NT2_TEST_EQUAL( spec2.size(), 2u );
  NT2_TEST_EQUAL( spec2[0], 6u );
  NT2_TEST_EQUAL( spec2[1], 9u );

  of_size_<4,2,6>     spec3;
  NT2_TEST_EQUAL( spec3.size(), 3u );
  NT2_TEST_EQUAL( spec3[0], 4u );
  NT2_TEST_EQUAL( spec3[1], 2u );
  NT2_TEST_EQUAL( spec3[2], 6u );

  of_size_<1,3,5,7>     spec4;
  NT2_TEST_EQUAL( spec4.size(), 4u );
  NT2_TEST_EQUAL( spec4[0], 1u );
  NT2_TEST_EQUAL( spec4[1], 3u );
  NT2_TEST_EQUAL( spec4[2], 5u );
  NT2_TEST_EQUAL( spec4[3], 7u );
}

////////////////////////////////////////////////////////////////////////////////
// Test of_size function calls
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( of_size_call )
{
  using nt2::of_size;
  using nt2::_4D;
  using nt2::_3D;
  using nt2::_2D;
  using nt2::_1D;

  _4D s4 = of_size(2,3,4,5);
  NT2_TEST_EQUAL( s4.size(), 4u );
  NT2_TEST_EQUAL( s4[0], 2u );
  NT2_TEST_EQUAL( s4[1], 3u );
  NT2_TEST_EQUAL( s4[2], 4u );
  NT2_TEST_EQUAL( s4[3], 5u );

  _3D s3 = of_size(2,3,4);
  NT2_TEST_EQUAL( s3.size(), 3u );
  NT2_TEST_EQUAL( s3[0], 2u );
  NT2_TEST_EQUAL( s3[1], 3u );
  NT2_TEST_EQUAL( s3[2], 4u );

  _2D s2 = of_size(2,3);
  NT2_TEST_EQUAL( s2.size(), 2u );
  NT2_TEST_EQUAL( s2[0], 2u );
  NT2_TEST_EQUAL( s2[1], 3u );

  _1D s1 = of_size(2);
  NT2_TEST_EQUAL( s1.size(), 1u );
  NT2_TEST_EQUAL( s1[0], 2u );
}

////////////////////////////////////////////////////////////////////////////////
// Test of_size function calls - Range constructor
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( of_size_call_range )
{
  using nt2::of_size;
  using nt2::_4D;
  using nt2::_3D;
  using nt2::_2D;
  using nt2::_1D;

  std::size_t range[4] = {2,3,4,5};

  _4D s4 = of_size(&range[0],&range[0]+4);
  NT2_TEST_EQUAL( s4.size(), 4u );
  NT2_TEST_EQUAL( s4[0], 2u );
  NT2_TEST_EQUAL( s4[1], 3u );
  NT2_TEST_EQUAL( s4[2], 4u );
  NT2_TEST_EQUAL( s4[3], 5u );

  _3D s3 = of_size(&range[0],&range[0]+3);
  NT2_TEST_EQUAL( s3.size(), 3u );
  NT2_TEST_EQUAL( s3[0], 2u );
  NT2_TEST_EQUAL( s3[1], 3u );
  NT2_TEST_EQUAL( s3[2], 4u );

  _2D s2 = of_size(&range[0],&range[0]+2);
  NT2_TEST_EQUAL( s2.size(), 2u );
  NT2_TEST_EQUAL( s2[0], 2u );
  NT2_TEST_EQUAL( s2[1], 3u );

  _1D s1 = of_size(&range[0],&range[0]+1);
  NT2_TEST_EQUAL( s1.size(), 1u );
  NT2_TEST_EQUAL( s1[0], 2u );
}

////////////////////////////////////////////////////////////////////////////////
// Test of_size equality operator
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( of_size_equality )
{
  using nt2::_4D;
  using nt2::_3D;
  using nt2::_2D;
  using nt2::_1D;
  using nt2::of_size;
  using nt2::of_size_;

  of_size_<>        s0;
  of_size_<2>       s1;
  of_size_<2,3>     s2;
  of_size_<2,3,4>   s3;
  of_size_<2,3,4,5> s4;

  _1D d1(2);
  _2D d2(2,3);
  _3D d3(2,3,4);
  _4D d4(2,3,4,5);

  _2D d12(2,1);
  _3D d13(2,1,1);
  _4D d14(2,1,1,1);

  // Test that _0D compares to [1 ... ]
  NT2_TEST_EQUAL( s0, of_size(1 )      );
  NT2_TEST_EQUAL( s0, of_size(1,1 )    );
  NT2_TEST_EQUAL( s0, of_size(1,1,1 )  );
  NT2_TEST_EQUAL( s0, of_size(1,1,1,1 ));

  // Test that static and dynamic of_size compares
  NT2_TEST_EQUAL( s1, d1 );
  NT2_TEST_EQUAL( s2, d2 );
  NT2_TEST_EQUAL( s3, d3 );
  NT2_TEST_EQUAL( s4, d4 );

  // Test out of dims comparison
  NT2_TEST_EQUAL( s1, d12 );
  NT2_TEST_EQUAL( s1, d13 );
  NT2_TEST_EQUAL( s1, d14 );

  // Test that stuff don't compare wrongly
  NT2_TEST( s4 != s1 );
  NT2_TEST( s4 != s2 );
  NT2_TEST( s4 != s3 );

  NT2_TEST( s4 != d1 );
  NT2_TEST( s4 != d2 );
  NT2_TEST( s4 != d3 );

  NT2_TEST( d4 != d1 );
  NT2_TEST( d4 != d2 );
  NT2_TEST( d4 != d3 );

  NT2_TEST( d4 != s1 );
  NT2_TEST( d4 != s2 );
  NT2_TEST( d4 != s3 );

  NT2_TEST( of_size(1,3,9,7) != of_size(4,4) );
}
