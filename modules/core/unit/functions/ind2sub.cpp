/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::ind2sub function"

#include <nt2/include/functions/ind2sub.hpp>

#include <boost/array.hpp>
#include <boost/fusion/include/make_vector.hpp>
#include <boost/mpl/int.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

NT2_TEST_CASE( ind2sub_2D )
{
  using boost::fusion::make_vector;
  using boost::mpl::int_;

  boost::array<int, 2> a = nt2::ind2sub( make_vector(3,3), int_<3>() );
  boost::array<int, 2> b = {{3,1}};
  for(int i=0;i<2;++i) NT2_TEST_EQUAL( a[i], b[i] );
}

NT2_TEST_CASE( ind2sub_2D_base )
{
  using boost::fusion::make_vector;
  using boost::mpl::int_;

  boost::array<int, 2> a = nt2::ind2sub( make_vector(3,3), int_<3>(), make_vector(1,1) );
  boost::array<int, 2> b = {{3,1}};
  for(int i=0;i<2;++i) NT2_TEST_EQUAL( a[i], b[i] );
}

NT2_TEST_CASE( ind2sub_4D )
{
  using boost::fusion::make_vector;
  using boost::mpl::int_;

  boost::array<int, 4> a = nt2::ind2sub( make_vector(7,5,3,2), int_<93>() );
  boost::array<int, 4> b = {{2,4,3,1}};
  for(int i=0;i<4;++i) NT2_TEST_EQUAL( a[i], b[i] );
}

NT2_TEST_CASE( ind2sub_4D_base )
{
  using boost::fusion::make_vector;
  using boost::mpl::int_;

  boost::array<int, 4> a = nt2::ind2sub( make_vector(7,5,3,2), int_<93>(), make_vector(1,1,1,1) );
  boost::array<int, 4> b = {{2,4,3,1}};
  for(int i=0;i<4;++i) NT2_TEST_EQUAL( a[i], b[i] );
}
