/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define BOOST_SIMD_UNIT_MODULE "boost::simd::meta::all"

#include <boost/simd/sdk/meta/all.hpp>
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
  using boost::simd::meta::all;
  using boost::is_same;
  using boost::mpl::_1;
  using boost::mpl::vector;

  BOOST_SIMD_TEST(  (all< is_same<_1,bool  >, vector<bool,bool,bool> >::value) 	);
  BOOST_SIMD_TEST( !(all< is_same<_1,double>, vector<int,double,bool> >::value)	);
  BOOST_SIMD_TEST( !(all< is_same<_1,double>, vector<bool,double,double> >::value)	);
  BOOST_SIMD_TEST( !(all< is_same<_1,double>, vector<double,double,bool> >::value)	);
  BOOST_SIMD_TEST( !(all< is_same<_1,double>, vector<double,int,double> >::value)	);
}

////////////////////////////////////////////////////////////////////////////////
// Test any with 1 non-sequence argument
////////////////////////////////////////////////////////////////////////////////
BOOST_SIMD_TEST_CASE(unary_non_sequence)
{
  using boost::simd::meta::all;
  using boost::is_same;
  using boost::mpl::_1;

  BOOST_SIMD_TEST(  (all< is_same<_1,bool  >, bool >::value) );
  BOOST_SIMD_TEST( !(all< is_same<_1,double>, bool >::value) );
}

////////////////////////////////////////////////////////////////////////////////
// Test any with non-sequence arguments
////////////////////////////////////////////////////////////////////////////////
BOOST_SIMD_TEST_CASE(non_sequences)
{
  using boost::simd::meta::all;
  using boost::is_same;
  using boost::mpl::_1;

  // Work
  BOOST_SIMD_TEST((all< is_same<_1,bool>, bool, bool             >::value) );
  BOOST_SIMD_TEST((all< is_same<_1,bool>, bool, bool, bool       >::value) );
  BOOST_SIMD_TEST((all< is_same<_1,bool>, bool, bool, bool, bool	>::value) );

  // Don't work
  BOOST_SIMD_TEST( !(all< is_same<_1,bool>, float, bool              	>::value) );
  BOOST_SIMD_TEST( !(all< is_same<_1,bool>, float, double, bool       	>::value) );
  BOOST_SIMD_TEST( !(all< is_same<_1,bool>, float, double, float, bool	>::value) );
}

