/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::settings of_size helper"

#include <boost/type_traits/is_same.hpp>
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
  NT2_TEST_EQUAL( spec1.size(), 1 );
  NT2_TEST_EQUAL( spec1[0], 0 );

  of_size_<-1,-1>     spec2;
  NT2_TEST_EQUAL( spec2.size(), 2 );
  NT2_TEST_EQUAL( spec2[0], 0 );
  NT2_TEST_EQUAL( spec2[1], 1 );

  of_size_<-1,-1,-1>     spec3;
  NT2_TEST_EQUAL( spec3.size(), 3 );
  NT2_TEST_EQUAL( spec3[0], 0 );
  NT2_TEST_EQUAL( spec3[1], 1 );
  NT2_TEST_EQUAL( spec3[2], 1 );

  of_size_<-1,-1,-1,-1>     spec4;
  NT2_TEST_EQUAL( spec4.size(), 4 );
  NT2_TEST_EQUAL( spec4[0], 0 );
  NT2_TEST_EQUAL( spec4[1], 1 );
  NT2_TEST_EQUAL( spec4[2], 1 );
  NT2_TEST_EQUAL( spec4[2], 1 );
}

////////////////////////////////////////////////////////////////////////////////
// Test of_size pre-initializations in case of static sizes
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( pre_init_of_size )
{
  using nt2::of_size_;

  of_size_<42>     spec1;
  NT2_TEST_EQUAL( spec1.size(), 1 );
  NT2_TEST_EQUAL( spec1[0], 42 );

  of_size_<6,9>     spec2;
  NT2_TEST_EQUAL( spec2.size(), 2 );
  NT2_TEST_EQUAL( spec2[0], 6 );
  NT2_TEST_EQUAL( spec2[1], 9 );

  of_size_<4,2,6>     spec3;
  NT2_TEST_EQUAL( spec3.size(), 3 );
  NT2_TEST_EQUAL( spec3[0], 4 );
  NT2_TEST_EQUAL( spec3[1], 2 );
  NT2_TEST_EQUAL( spec3[2], 6 );

  of_size_<1,3,5,7>     spec4;
  NT2_TEST_EQUAL( spec4.size(), 4 );
  NT2_TEST_EQUAL( spec4[0], 1 );
  NT2_TEST_EQUAL( spec4[1], 3 );
  NT2_TEST_EQUAL( spec4[2], 5 );
  NT2_TEST_EQUAL( spec4[3], 7 );
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
  NT2_TEST_EQUAL( s4.size(), 4 );
  NT2_TEST_EQUAL( s4[0], 2 );
  NT2_TEST_EQUAL( s4[1], 3 );
  NT2_TEST_EQUAL( s4[2], 4 );
  NT2_TEST_EQUAL( s4[3], 5 );

  _3D s3 = of_size(2,3,4);
  NT2_TEST_EQUAL( s3.size(), 3 );
  NT2_TEST_EQUAL( s3[0], 2 );
  NT2_TEST_EQUAL( s3[1], 3 );
  NT2_TEST_EQUAL( s3[2], 4 );

  _2D s2 = of_size(2,3);
  NT2_TEST_EQUAL( s2.size(), 2 );
  NT2_TEST_EQUAL( s2[0], 2 );
  NT2_TEST_EQUAL( s2[1], 3 );

  _1D s1 = of_size(2);
  NT2_TEST_EQUAL( s1.size(), 1 );
  NT2_TEST_EQUAL( s1[0], 2 );
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
  NT2_TEST_EQUAL( s4.size(), 4 );
  NT2_TEST_EQUAL( s4[0], 2 );
  NT2_TEST_EQUAL( s4[1], 3 );
  NT2_TEST_EQUAL( s4[2], 4 );
  NT2_TEST_EQUAL( s4[3], 5 );

  _3D s3 = of_size(&range[0],&range[0]+3);
  NT2_TEST_EQUAL( s3.size(), 3 );
  NT2_TEST_EQUAL( s3[0], 2 );
  NT2_TEST_EQUAL( s3[1], 3 );
  NT2_TEST_EQUAL( s3[2], 4 );

  _2D s2 = of_size(&range[0],&range[0]+2);
  NT2_TEST_EQUAL( s2.size(), 2 );
  NT2_TEST_EQUAL( s2[0], 2 );
  NT2_TEST_EQUAL( s2[1], 3 );

  _1D s1 = of_size(&range[0],&range[0]+1);
  NT2_TEST_EQUAL( s1.size(), 1 );
  NT2_TEST_EQUAL( s1[0], 2 );
}


