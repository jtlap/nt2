/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define BOOST_DISPATCH_UNIT_MODULE "boost::dispatch::meta::any"

#include <boost/dispatch/meta/any.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/type_traits/is_same.hpp>

#include <boost/simd/sdk/unit/module.hpp>
#include <boost/simd/sdk/unit/tests/basic.hpp>

////////////////////////////////////////////////////////////////////////////////
// Test any with 1 sequence argument
////////////////////////////////////////////////////////////////////////////////
BOOST_SIMD_TEST_CASE(unary_sequence)
{
  using boost::dispatch::meta::any;
  using boost::is_same;
  using boost::mpl::_1;
  using boost::mpl::vector;

  BOOST_SIMD_TEST(  (any< is_same<_1,bool  >, vector<int,float,bool> >::value) );
  BOOST_SIMD_TEST( !(any< is_same<_1,double>, vector<int,float,bool> >::value) );
}

////////////////////////////////////////////////////////////////////////////////
// Test any with 1 non-sequence argument
////////////////////////////////////////////////////////////////////////////////
BOOST_SIMD_TEST_CASE(unary_non_sequence)
{
  using boost::dispatch::meta::any;
  using boost::is_same;
  using boost::mpl::_1;

  BOOST_SIMD_TEST(  (any< is_same<_1,bool  >, bool >::value) );
  BOOST_SIMD_TEST( !(any< is_same<_1,double>, bool >::value) );
}

////////////////////////////////////////////////////////////////////////////////
// Test any with non-sequence arguments
////////////////////////////////////////////////////////////////////////////////
BOOST_SIMD_TEST_CASE(non_sequences)
{
  using boost::dispatch::meta::any;
  using boost::is_same;
  using boost::mpl::_1;

  // Work
  BOOST_SIMD_TEST((any< is_same<_1,bool>, float, bool              >::value) );
  BOOST_SIMD_TEST((any< is_same<_1,bool>, float, bool, float       >::value) );
  BOOST_SIMD_TEST((any< is_same<_1,bool>, float, bool, float, float>::value) );

  // Don't work
  BOOST_SIMD_TEST( !(any< is_same<_1,bool>, float, double              >::value) );
  BOOST_SIMD_TEST( !(any< is_same<_1,bool>, float, double, float       >::value) );
  BOOST_SIMD_TEST( !(any< is_same<_1,bool>, float, double, float, float>::value) );
}
