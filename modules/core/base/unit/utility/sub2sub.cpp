//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2::sub2sub function"

#include <nt2/include/functions/sub2sub.hpp>
#include <boost/array.hpp>
#include <boost/fusion/include/make_vector.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

NT2_TEST_CASE( sub2sub_1Dto1D )
{
    using boost::fusion::make_vector;

    boost::array<int, 1> a = nt2::sub2sub( make_vector(3), make_vector(2), make_vector(3) );
    boost::array<int, 1> b = {{2}};
    for(int i=0;i<1;++i) NT2_TEST_EQUAL( a[i], b[i] );
}

NT2_TEST_CASE( sub2sub_2Dto2Did )
{
    using boost::fusion::make_vector;

    boost::array<int, 2> a = nt2::sub2sub( make_vector(3,4), make_vector(2,3), make_vector(3,4) );
    boost::array<int, 2> b = {{2,3}};
    for(int i=0;i<2;++i) NT2_TEST_EQUAL( a[i], b[i] );
}

NT2_TEST_CASE( sub2sub_2Dto2D )
{
    using boost::fusion::make_vector;

    boost::array<int, 2> a = nt2::sub2sub( make_vector(3,4), make_vector(2,4), make_vector(4,3) );
    boost::array<int, 2> b = {{3,3}};
    for(int i=0;i<2;++i) NT2_TEST_EQUAL( a[i], b[i] );
}

NT2_TEST_CASE( sub2sub_1Dto2D )
{
    using boost::fusion::make_vector;

    boost::array<int, 2> a = nt2::sub2sub( make_vector(8), make_vector(3), make_vector(2,4) );
    boost::array<int, 2> b = {{1,2}};
    for(int i=0;i<2;++i) NT2_TEST_EQUAL( a[i], b[i] );
}

NT2_TEST_CASE( sub2sub_2Dto1D )
{
    using boost::fusion::make_vector;

    boost::array<int, 1> a = nt2::sub2sub( make_vector(4,2), make_vector(4,1), make_vector(8) );
    boost::array<int, 1> b = {{4}};
    for(int i=0;i<1;++i) NT2_TEST_EQUAL( a[i], b[i] );
}

NT2_TEST_CASE( sub2sub_3Dto3Did )
{
    using boost::fusion::make_vector;

    boost::array<int, 3> a = nt2::sub2sub( make_vector(3,4,5), make_vector(2,3,4), make_vector(3,4,5) );
    boost::array<int, 3> b = {{2,3,4}};
    for(int i=0;i<3;++i) NT2_TEST_EQUAL( a[i], b[i] );
}

NT2_TEST_CASE( sub2sub_3Dto3D )
{
    using boost::fusion::make_vector;

    boost::array<int, 3> a = nt2::sub2sub( make_vector(3,4,5), make_vector(2,3,4), make_vector(5,4,3) );
    boost::array<int, 3> b = {{4,1,3}};
    for(int i=0;i<3;++i) NT2_TEST_EQUAL( a[i], b[i] );
}

NT2_TEST_CASE( sub2sub_3Dto2D )
{
    using boost::fusion::make_vector;

    boost::array<int, 2> a = nt2::sub2sub(  make_vector(2,2,2), make_vector(1,1,2), make_vector(3,4) );
    boost::array<int, 2> b = {{2,2}};
    for(int i=0;i<2;++i) NT2_TEST_EQUAL( a[i], b[i] );
}

NT2_TEST_CASE( sub2sub_2Dto3D )
{
  using boost::fusion::make_vector;

  boost::array<int, 3> a = nt2::sub2sub( make_vector(3,4), make_vector(2,2), make_vector(2,2,2) );
  boost::array<int, 3> b = {{1,1,2}};
  for(int i=0;i<3;++i) NT2_TEST_EQUAL( a[i], b[i] );
}

NT2_TEST_CASE( sub2sub_1Dto3D )
{
    using boost::fusion::make_vector;

    boost::array<int, 3> a = nt2::sub2sub(  make_vector(24), make_vector(14), make_vector(2,3,4) );
    boost::array<int, 3> b = {{2,1,3}};
    for(int i=0;i<2;++i) NT2_TEST_EQUAL( a[i], b[i] );
}

NT2_TEST_CASE( sub2sub_3Dto1D )
{
    using boost::fusion::make_vector;

    boost::array<int, 1> a = nt2::sub2sub(  make_vector(2,3,4), make_vector(2,1,3), make_vector(24) );
    boost::array<int, 1> b = {{14}};
    for(int i=0;i<1;++i) NT2_TEST_EQUAL( a[i], b[i] );
}
