/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 0x01.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define BOOST_SIMD_UNIT_MODULE "boost::simd::memory::stride"

#include <boost/array.hpp>
#include <boost/mpl/vector_c.hpp>
#include <boost/simd/sdk/memory/stride.hpp>
#include <boost/simd/sdk/memory/align_on.hpp>
#include <boost/fusion/adapted/mpl.hpp>
#include <boost/fusion/adapted/array.hpp>
#include <boost/simd/sdk/memory/no_padding.hpp>
#include <boost/simd/sdk/memory/lead_padding.hpp>
#include <boost/simd/sdk/memory/global_padding.hpp>

#include <boost/simd/sdk/unit/module.hpp>
#include <boost/simd/sdk/unit/tests/relation.hpp>

////////////////////////////////////////////////////////////////////////////////
// Test for stride with no_padding
////////////////////////////////////////////////////////////////////////////////
BOOST_SIMD_TEST_CASE(stride_no_padding)
{
  using boost::simd::stride;
  using boost::array;
  using boost::mpl::vector_c;
  using boost::simd::memory::no_padding;

  no_padding p;

  vector_c<int,9,7,5,3> ss4;
  vector_c<int,7,5,3>   ss3;
  vector_c<int,5,3>     ss2;
  vector_c<int,3>       ss1;

  array<int,4> ds4 = {{9,7,5,3}};
  array<int,3> ds3 = {{7,5,3}};
  array<int,2> ds2 = {{5,3}};
  array<int,1> ds1 = {{3}};

  BOOST_SIMD_TEST_EQUAL( (stride<1>(ds4,p)), 9 );
  BOOST_SIMD_TEST_EQUAL( (stride<2>(ds4,p)), 7 );
  BOOST_SIMD_TEST_EQUAL( (stride<1>(ds3,p)), 7 );
  BOOST_SIMD_TEST_EQUAL( (stride<3>(ds4,p)), 5 );
  BOOST_SIMD_TEST_EQUAL( (stride<2>(ds3,p)), 5 );
  BOOST_SIMD_TEST_EQUAL( (stride<1>(ds2,p)), 5 );
  BOOST_SIMD_TEST_EQUAL( (stride<4>(ds4,p)), 3 );
  BOOST_SIMD_TEST_EQUAL( (stride<3>(ds3,p)), 3 );
  BOOST_SIMD_TEST_EQUAL( (stride<2>(ds2,p)), 3 );
  BOOST_SIMD_TEST_EQUAL( (stride<1>(ds1,p)), 3 );

  BOOST_SIMD_TEST_EQUAL( int(stride<1>(ss4,p)), 9 );
  BOOST_SIMD_TEST_EQUAL( int(stride<2>(ss4,p)), 7 );
  BOOST_SIMD_TEST_EQUAL( int(stride<1>(ss3,p)), 7 );
  BOOST_SIMD_TEST_EQUAL( int(stride<3>(ss4,p)), 5 );
  BOOST_SIMD_TEST_EQUAL( int(stride<2>(ss3,p)), 5 );
  BOOST_SIMD_TEST_EQUAL( int(stride<1>(ss2,p)), 5 );
  BOOST_SIMD_TEST_EQUAL( int(stride<4>(ss4,p)), 3 );
  BOOST_SIMD_TEST_EQUAL( int(stride<3>(ss3,p)), 3 );
  BOOST_SIMD_TEST_EQUAL( int(stride<2>(ss2,p)), 3 );
  BOOST_SIMD_TEST_EQUAL( int(stride<1>(ss1,p)), 3 );
}

////////////////////////////////////////////////////////////////////////////////
// Test for stride with global_padding
////////////////////////////////////////////////////////////////////////////////
BOOST_SIMD_TEST_CASE(stride_global_padding)
{
  using boost::simd::stride;
  using boost::array;
  using boost::mpl::vector_c;
  using boost::simd::memory::global_padding;

  global_padding p;

  vector_c<int,9,7,5,3> ss4;
  vector_c<int,7,5,3>   ss3;
  vector_c<int,5,3>     ss2;
  vector_c<int,3>       ss1;

  array<int,4> ds4 = {{9,7,5,3}};
  array<int,3> ds3 = {{7,5,3}};
  array<int,2> ds2 = {{5,3}};
  array<int,1> ds1 = {{3}};

  BOOST_SIMD_TEST_EQUAL( (stride<1>(ds4,p)), 9 );
  BOOST_SIMD_TEST_EQUAL( (stride<2>(ds4,p)), 7 );
  BOOST_SIMD_TEST_EQUAL( (stride<1>(ds3,p)), 7 );
  BOOST_SIMD_TEST_EQUAL( (stride<3>(ds4,p)), 5 );
  BOOST_SIMD_TEST_EQUAL( (stride<2>(ds3,p)), 5 );
  BOOST_SIMD_TEST_EQUAL( (stride<1>(ds2,p)), 5 );
  BOOST_SIMD_TEST_EQUAL( (stride<4>(ds4,p)), 3 );
  BOOST_SIMD_TEST_EQUAL( (stride<3>(ds3,p)), 3 );
  BOOST_SIMD_TEST_EQUAL( (stride<2>(ds2,p)), 3 );
  BOOST_SIMD_TEST_EQUAL( (stride<1>(ds1,p)), 3 );

  BOOST_SIMD_TEST_EQUAL( int(stride<1>(ss4,p)), 9 );
  BOOST_SIMD_TEST_EQUAL( int(stride<2>(ss4,p)), 7 );
  BOOST_SIMD_TEST_EQUAL( int(stride<1>(ss3,p)), 7 );
  BOOST_SIMD_TEST_EQUAL( int(stride<3>(ss4,p)), 5 );
  BOOST_SIMD_TEST_EQUAL( int(stride<2>(ss3,p)), 5 );
  BOOST_SIMD_TEST_EQUAL( int(stride<1>(ss2,p)), 5 );
  BOOST_SIMD_TEST_EQUAL( int(stride<4>(ss4,p)), 3 );
  BOOST_SIMD_TEST_EQUAL( int(stride<3>(ss3,p)), 3 );
  BOOST_SIMD_TEST_EQUAL( int(stride<2>(ss2,p)), 3 );
  BOOST_SIMD_TEST_EQUAL( int(stride<1>(ss1,p)), 3 );
}

////////////////////////////////////////////////////////////////////////////////
// Test for stride with lead_padding
////////////////////////////////////////////////////////////////////////////////
BOOST_SIMD_TEST_CASE(stride_lead_padding)
{
  using boost::simd::stride;
  using boost::array;
  using boost::mpl::vector_c;
  using boost::simd::memory::lead_padding;
  using boost::simd::memory::align_on;

  lead_padding p;

  vector_c<int,9,7,5,3> ss4;
  vector_c<int,7,5,3>   ss3;
  vector_c<int,5,3>     ss2;
  vector_c<int,3>       ss1;

  array<int,4> ds4 = {{9,7,5,3}};
  array<int,3> ds3 = {{7,5,3}};
  array<int,2> ds2 = {{5,3}};
  array<int,1> ds1 = {{3}};

  BOOST_SIMD_TEST_EQUAL( (stride<1>(ds4,p)), align_on(9) );
  BOOST_SIMD_TEST_EQUAL( (stride<2>(ds4,p)), 7 );
  BOOST_SIMD_TEST_EQUAL( (stride<1>(ds3,p)), align_on(7) );
  BOOST_SIMD_TEST_EQUAL( (stride<3>(ds4,p)), 5 );
  BOOST_SIMD_TEST_EQUAL( (stride<2>(ds3,p)), 5 );
  BOOST_SIMD_TEST_EQUAL( (stride<1>(ds2,p)), align_on( 5) );
  BOOST_SIMD_TEST_EQUAL( (stride<4>(ds4,p)), 3 );
  BOOST_SIMD_TEST_EQUAL( (stride<3>(ds3,p)), 3 );
  BOOST_SIMD_TEST_EQUAL( (stride<2>(ds2,p)), 3 );
  BOOST_SIMD_TEST_EQUAL( (stride<1>(ds1,p)), align_on(3) );

  BOOST_SIMD_TEST_EQUAL( int(stride<1>(ss4,p)), align_on(9) );
  BOOST_SIMD_TEST_EQUAL( int(stride<2>(ss4,p)), 7 );
  BOOST_SIMD_TEST_EQUAL( int(stride<1>(ss3,p)), align_on(7) );
  BOOST_SIMD_TEST_EQUAL( int(stride<3>(ss4,p)), 5 );
  BOOST_SIMD_TEST_EQUAL( int(stride<2>(ss3,p)), 5 );
  BOOST_SIMD_TEST_EQUAL( int(stride<1>(ss2,p)), align_on(5) );
  BOOST_SIMD_TEST_EQUAL( int(stride<4>(ss4,p)), 3 );
  BOOST_SIMD_TEST_EQUAL( int(stride<3>(ss3,p)), 3 );
  BOOST_SIMD_TEST_EQUAL( int(stride<2>(ss2,p)), 3 );
  BOOST_SIMD_TEST_EQUAL( int(stride<1>(ss1,p)), align_on(3) );
}
