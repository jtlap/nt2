/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2 container relative_index"

#include <nt2/table.hpp>
#include <nt2/include/functions/extent.hpp>
#include <nt2/include/functions/of_size.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

NT2_TEST_CASE( integral_subscript )
{
  using nt2::table;
  using nt2::of_size;
  typedef double T;

  table<T> a( of_size(5,4,3,2) );

  //============================================================================
  // 1D subscript
  //============================================================================
  for(int i=1;i<=5*4*3*2;i++)
    NT2_TEST_EQUAL( nt2::relative_index(boost::proto::child_c<1>(a(i)), boost::fusion::make_vector(0), boost::mpl::int_<0>()), i );

  //============================================================================
  // 2D subscript
  //============================================================================
  for(int j=1;j<=4*3*2;j++)
    for(int i=1;i<=5;i++)
    {
      NT2_TEST_EQUAL( nt2::relative_index(boost::proto::child_c<1>(a(i,j)), boost::fusion::make_vector(0), boost::mpl::int_<0>()), i );
      NT2_TEST_EQUAL( nt2::relative_index(boost::proto::child_c<2>(a(i,j)), boost::fusion::make_vector(0), boost::mpl::int_<0>()), j );
    }

  //============================================================================
  // 3D subscript
  //============================================================================
  for(int k=1;k<=3*2;k++)
    for(int j=1;j<=4;j++)
      for(int i=1;i<=5;i++)
      {
        NT2_TEST_EQUAL( nt2::relative_index(boost::proto::child_c<1>(a(i,j,k)), boost::fusion::make_vector(0), boost::mpl::int_<0>()), i );
        NT2_TEST_EQUAL( nt2::relative_index(boost::proto::child_c<2>(a(i,j,k)), boost::fusion::make_vector(0), boost::mpl::int_<0>()), j );
        NT2_TEST_EQUAL( nt2::relative_index(boost::proto::child_c<3>(a(i,j,k)), boost::fusion::make_vector(0), boost::mpl::int_<0>()), k );
      }

  //============================================================================
  // 4D subscript
  //============================================================================
  for(int l=1;l<=2;l++)
    for(int k=1;k<=3;k++)
      for(int j=1;j<=4;j++)
        for(int i=1;i<=5;i++)
        {
          NT2_TEST_EQUAL( nt2::relative_index(boost::proto::child_c<1>(a(i,j,k,l)), boost::fusion::make_vector(0), boost::mpl::int_<0>()), i );
          NT2_TEST_EQUAL( nt2::relative_index(boost::proto::child_c<2>(a(i,j,k,l)), boost::fusion::make_vector(0), boost::mpl::int_<0>()), j );
          NT2_TEST_EQUAL( nt2::relative_index(boost::proto::child_c<3>(a(i,j,k,l)), boost::fusion::make_vector(0), boost::mpl::int_<0>()), k );
          NT2_TEST_EQUAL( nt2::relative_index(boost::proto::child_c<4>(a(i,j,k,l)), boost::fusion::make_vector(0), boost::mpl::int_<0>()), l );
        }
}

NT2_TEST_CASE( colon_subscript )
{
  using nt2::table;
  using nt2::of_size;
  typedef double T;

  table<T> a( of_size(5,4,3,2) );

  //============================================================================
  // 1D subscript
  //============================================================================
  for(int i=1;i<=5*4*3*2;i++)
    NT2_TEST_EQUAL( nt2::relative_index(boost::proto::child_c<1>(a(nt2::_)), boost::fusion::make_vector(i), boost::mpl::int_<0>()), i);

  //============================================================================
  // 2D subscript
  //============================================================================
  for(int j=1;j<=4*3*2;j++)
    for(int i=1;i<=5;i++)
    {
        NT2_TEST_EQUAL( nt2::relative_index(boost::proto::child_c<1>(a(nt2::_)), boost::fusion::make_vector(i,j), boost::mpl::int_<0>()), i);
        NT2_TEST_EQUAL( nt2::relative_index(boost::proto::child_c<1>(a(nt2::_)), boost::fusion::make_vector(i,j), boost::mpl::int_<1>()), j);
    }

  //============================================================================
  // 3D subscript
  //============================================================================
  for(int k=1;k<=3*2;k++)
    for(int j=1;j<=4;j++)
      for(int i=1;i<=5;i++)
      {
          NT2_TEST_EQUAL( nt2::relative_index(boost::proto::child_c<1>(a(nt2::_)), boost::fusion::make_vector(i,j,k), boost::mpl::int_<0>()), i);
          NT2_TEST_EQUAL( nt2::relative_index(boost::proto::child_c<1>(a(nt2::_)), boost::fusion::make_vector(i,j,k), boost::mpl::int_<1>()), j);
          NT2_TEST_EQUAL( nt2::relative_index(boost::proto::child_c<1>(a(nt2::_)), boost::fusion::make_vector(i,j,k), boost::mpl::int_<2>()), k);
      }

  //============================================================================
  // 4D subscript
  //============================================================================
  for(int l=1;l<=2;l++)
    for(int k=1;k<=3;k++)
      for(int j=1;j<=4;j++)
        for(int i=1;i<=5;i++)
        {
          NT2_TEST_EQUAL( nt2::relative_index(boost::proto::child_c<1>(a(nt2::_)), boost::fusion::make_vector(i,j,k,l), boost::mpl::int_<0>()), i);
          NT2_TEST_EQUAL( nt2::relative_index(boost::proto::child_c<1>(a(nt2::_)), boost::fusion::make_vector(i,j,k,l), boost::mpl::int_<1>()), j);
          NT2_TEST_EQUAL( nt2::relative_index(boost::proto::child_c<1>(a(nt2::_)), boost::fusion::make_vector(i,j,k,l), boost::mpl::int_<2>()), k);
          NT2_TEST_EQUAL( nt2::relative_index(boost::proto::child_c<1>(a(nt2::_)), boost::fusion::make_vector(i,j,k,l), boost::mpl::int_<3>()), l);
        }
}

NT2_TEST_CASE( mixed_subscript )
{
  using nt2::table;
  using nt2::of_size;
  typedef double T;

  table<T> a( of_size(5,4,3,2) );

  for(int j=1;j<=4*3*2;j++)
    for(int i=1;i<=5;i++)
    {
      NT2_TEST_EQUAL( nt2::relative_index(boost::proto::child_c<1>(a(i,nt2::_)), boost::fusion::make_vector(i,j), boost::mpl::int_<0>()), i );
      NT2_TEST_EQUAL( nt2::relative_index(boost::proto::child_c<1>(a(i,nt2::_)), boost::fusion::make_vector(i,j), boost::mpl::int_<1>()), i );
      NT2_TEST_EQUAL( nt2::relative_index(boost::proto::child_c<2>(a(i,nt2::_)), boost::fusion::make_vector(i,j), boost::mpl::int_<0>()), i );
      NT2_TEST_EQUAL( nt2::relative_index(boost::proto::child_c<2>(a(i,nt2::_)), boost::fusion::make_vector(i,j), boost::mpl::int_<1>()), j );
      
      NT2_TEST_EQUAL( nt2::relative_index(boost::proto::child_c<1>(a(nt2::_,j)), boost::fusion::make_vector(i,j), boost::mpl::int_<0>()), i );
      NT2_TEST_EQUAL( nt2::relative_index(boost::proto::child_c<1>(a(nt2::_,j)), boost::fusion::make_vector(i,j), boost::mpl::int_<1>()), j );
      NT2_TEST_EQUAL( nt2::relative_index(boost::proto::child_c<2>(a(nt2::_,j)), boost::fusion::make_vector(i,j), boost::mpl::int_<0>()), j );
      NT2_TEST_EQUAL( nt2::relative_index(boost::proto::child_c<2>(a(nt2::_,j)), boost::fusion::make_vector(i,j), boost::mpl::int_<1>()), j );
    }
}
