/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define BOOST_SIMD_UNIT_MODULE "boost::simd::meta::set"

#include <boost/simd/sdk/meta/set.hpp>
#include <boost/simd/sdk/meta/join.hpp>
#include <boost/simd/sdk/meta/is_set.hpp>
#include <boost/simd/sdk/meta/has_key.hpp>

#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/sizeof.hpp>
#include <boost/mpl/int.hpp>
#include <boost/simd/sdk/unit/module.hpp>
#include <boost/simd/sdk/unit/tests/basic.hpp>

////////////////////////////////////////////////////////////////////////////////
// Test empty set 'emptyness'
////////////////////////////////////////////////////////////////////////////////
BOOST_SIMD_TEST_CASE(empty_set)
{
  using boost::simd::meta::set;
  using boost::simd::meta::is_set;
  using boost::simd::meta::has_key;

  BOOST_SIMD_TEST( is_set< set<> >::value            );
  BOOST_SIMD_TEST( !(has_key< set<> ,void>::value )  );
  BOOST_SIMD_TEST( !(has_key< set<> ,int>::value  )  );
  BOOST_SIMD_TEST( !(has_key< set<> ,float>::value)  );
}

////////////////////////////////////////////////////////////////////////////////
// Test set access
////////////////////////////////////////////////////////////////////////////////
BOOST_SIMD_TEST_CASE(normal_set)
{
  using boost::simd::meta::set;
  using boost::simd::meta::is_set;
  using boost::simd::meta::has_key;

  // Is it detected as a set
  BOOST_SIMD_TEST( (is_set < set<int,float,void> >::value) );

  // Check for element inside the set
  BOOST_SIMD_TEST(  (has_key< set<int,float,void>, void  >::value) );
  BOOST_SIMD_TEST(  (has_key< set<int,float,void>, int   >::value) );
  BOOST_SIMD_TEST(  (has_key< set<int,float,void>, float >::value) );
  BOOST_SIMD_TEST( !(has_key< set<int,float,void>, double>::value) );
  BOOST_SIMD_TEST( !(has_key< set<int,float,void>, int** >::value) );
}

////////////////////////////////////////////////////////////////////////////////
// Test set join
////////////////////////////////////////////////////////////////////////////////
BOOST_SIMD_TEST_CASE(join_set)
{
  using boost::simd::meta::set;
  using boost::simd::meta::is_set;
  using boost::simd::meta::has_key;
  using boost::simd::meta::join;

  BOOST_SIMD_TEST( (is_set< join< set<float>,set<int> > >::value)        );
  BOOST_SIMD_TEST( (has_key< join< set<float>,set<int> >, float >::value));
  BOOST_SIMD_TEST( (has_key< join< set<float>,set<int> >, int >::value)  );

  BOOST_SIMD_TEST(  (is_set< join< set<int>,set<> > >::value)        );
  BOOST_SIMD_TEST( !(has_key< join< set<int>,set<> >, float >::value));
  BOOST_SIMD_TEST(  (has_key< join< set<int>,set<> >, int >::value)  );

  BOOST_SIMD_TEST(  (is_set< join< set<>,set<int> > >::value)        );
  BOOST_SIMD_TEST( !(has_key< join< set<>,set<int> >, float >::value));
  BOOST_SIMD_TEST(  (has_key< join< set<>,set<int> >, int >::value)  );

  BOOST_SIMD_TEST( (is_set< join< set<>,set<> > >::value)          );
  BOOST_SIMD_TEST( !(has_key< join< set<>,set<> >, float >::value) );
  BOOST_SIMD_TEST( !(has_key< join< set<>,set<> >, int >::value)   );
}
