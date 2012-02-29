/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::meta::view_at"

#include <nt2/sdk/meta/view_at.hpp>
#include <boost/fusion/include/at.hpp>
#include <boost/fusion/include/size.hpp>
#include <boost/fusion/include/vector.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

NT2_TEST_CASE(view_at)
{
  using nt2::meta::view_at;  
  using boost::fusion::size; 
  using boost::fusion::at_c;
  using boost::fusion::vector;

  vector<int,float,char> v(3,3.1415f,'A');

  NT2_TEST_EQUAL( size( view_at<0>(v) ) , 1u );
  NT2_TEST_EQUAL( size( view_at<1>(v) ) , 1u );
  NT2_TEST_EQUAL( size( view_at<2>(v) ) , 1u );
  
  NT2_TEST_EQUAL( at_c<0>( view_at<0>(v) ) , 3      );
  NT2_TEST_EQUAL( at_c<0>( view_at<1>(v) ) , 3.1415f);
  NT2_TEST_EQUAL( at_c<0>( view_at<2>(v) ) , 'A'    );

  at_c<0>( view_at<0>(v) ) = 9;
  at_c<0>( view_at<1>(v) ) = 0.001f;
  at_c<0>( view_at<2>(v) ) = 'Z';

  NT2_TEST_EQUAL( at_c<0>( view_at<0>(v) ) , 9      );
  NT2_TEST_EQUAL( at_c<0>( view_at<1>(v) ) , 0.001f);
  NT2_TEST_EQUAL( at_c<0>( view_at<2>(v) ) , 'Z'    );
}
