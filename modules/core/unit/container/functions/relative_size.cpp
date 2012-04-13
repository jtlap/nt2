/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2 container relative_size"

#include <nt2/table.hpp>
#include <nt2/include/functions/extent.hpp>
#include <nt2/include/functions/of_size.hpp>
#include <nt2/include/functions/relative_size.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

NT2_TEST_CASE( integral_subscript )
{
  using nt2::table;
  using nt2::of_size;
  typedef double T;

  table<T> a( of_size(5,4,3,2) );

  NT2_TEST_EQUAL( nt2::relative_size(boost::proto::child_c<1>(a(4,3,2,nt2::_)), of_size(5,4,3,2), boost::mpl::int_<0>(), boost::mpl::int_<4>()), 1 );
  NT2_TEST_EQUAL( nt2::relative_size(boost::proto::child_c<2>(a(4,3,nt2::_,1)), of_size(5,4,3,2), boost::mpl::int_<1>(), boost::mpl::int_<4>()), 1 );
  NT2_TEST_EQUAL( nt2::relative_size(boost::proto::child_c<3>(a(4,nt2::_,2,1)), of_size(5,4,3,2), boost::mpl::int_<2>(), boost::mpl::int_<4>()), 1 );
  NT2_TEST_EQUAL( nt2::relative_size(boost::proto::child_c<4>(a(nt2::_,3,2,1)), of_size(5,4,3,2), boost::mpl::int_<3>(), boost::mpl::int_<4>()), 1 );
}

NT2_TEST_CASE( colon_subscript )
{
  using nt2::table;
  using nt2::of_size;
  typedef double T;

  table<T> a( of_size(5,4,3,2) );

  NT2_TEST_EQUAL( nt2::relative_size(boost::proto::child_c<1>(a(nt2::_)), of_size(5,4,3,2), boost::mpl::int_<0>(), boost::mpl::int_<4>()), 5 );
  NT2_TEST_EQUAL( nt2::relative_size(boost::proto::child_c<1>(a(nt2::_)), of_size(5,4,3,2), boost::mpl::int_<1>(), boost::mpl::int_<4>()), 4 );
  NT2_TEST_EQUAL( nt2::relative_size(boost::proto::child_c<1>(a(nt2::_)), of_size(5,4,3,2), boost::mpl::int_<2>(), boost::mpl::int_<4>()), 3 );
  NT2_TEST_EQUAL( nt2::relative_size(boost::proto::child_c<1>(a(nt2::_)), of_size(5,4,3,2), boost::mpl::int_<3>(), boost::mpl::int_<4>()), 2 );
}

NT2_TEST_CASE( mixed_subscript )
{
  using nt2::table;
  using nt2::of_size;
  typedef double T;

  table<T> a( of_size(5,4,3,2) );

  NT2_TEST_EQUAL( nt2::relative_size(boost::proto::child_c<1>(a(nt2::_,1)), of_size(5,4,3,2), boost::mpl::int_<0>(), boost::mpl::int_<4>()), 5 );
  NT2_TEST_EQUAL( nt2::relative_size(boost::proto::child_c<1>(a(nt2::_,1)), of_size(5,4,3,2), boost::mpl::int_<1>(), boost::mpl::int_<4>()), 4 );
  NT2_TEST_EQUAL( nt2::relative_size(boost::proto::child_c<1>(a(nt2::_,1)), of_size(5,4,3,2), boost::mpl::int_<2>(), boost::mpl::int_<4>()), 3 );
  NT2_TEST_EQUAL( nt2::relative_size(boost::proto::child_c<1>(a(nt2::_,1)), of_size(5,4,3,2), boost::mpl::int_<3>(), boost::mpl::int_<4>()), 2 );

  NT2_TEST_EQUAL( nt2::relative_size(boost::proto::child_c<2>(a(nt2::_,1)), of_size(5,4,3,2), boost::mpl::int_<0>(), boost::mpl::int_<4>()), 1 );
  NT2_TEST_EQUAL( nt2::relative_size(boost::proto::child_c<2>(a(nt2::_,1)), of_size(5,4,3,2), boost::mpl::int_<1>(), boost::mpl::int_<4>()), 1 );
  NT2_TEST_EQUAL( nt2::relative_size(boost::proto::child_c<2>(a(nt2::_,1)), of_size(5,4,3,2), boost::mpl::int_<2>(), boost::mpl::int_<4>()), 1 );
  NT2_TEST_EQUAL( nt2::relative_size(boost::proto::child_c<2>(a(nt2::_,1)), of_size(5,4,3,2), boost::mpl::int_<3>(), boost::mpl::int_<4>()), 1 );
}
