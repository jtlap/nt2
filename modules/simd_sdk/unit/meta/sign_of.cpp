/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define BOOST_SIMD_UNIT_MODULE "boost::simd::meta::sign_of"

#include <boost/simd/sdk/meta/sign_of.hpp>
#include <boost/simd/sdk/config/types.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/simd/sdk/unit/module.hpp>
#include <boost/simd/sdk/unit/tests/basic.hpp>

////////////////////////////////////////////////////////////////////////////////
// Test that sign_of is correct
////////////////////////////////////////////////////////////////////////////////
BOOST_SIMD_TEST_CASE(sign_of)
{
  using boost::simd::meta::sign_of;
  using boost::is_same;

  BOOST_SIMD_TEST( (is_same<sign_of<double       >::type,signed  >::value ));
  BOOST_SIMD_TEST( (is_same<sign_of<float        >::type,signed  >::value ));
  BOOST_SIMD_TEST( (is_same<sign_of<boost::simd::int64_t >::type,signed  >::value ));
  BOOST_SIMD_TEST( (is_same<sign_of<boost::simd::int32_t >::type,signed  >::value ));
  BOOST_SIMD_TEST( (is_same<sign_of<boost::simd::int16_t >::type,signed  >::value ));
  BOOST_SIMD_TEST( (is_same<sign_of<boost::simd::int8_t  >::type,signed  >::value ));
  BOOST_SIMD_TEST( (is_same<sign_of<boost::simd::uint64_t>::type,unsigned>::value ));
  BOOST_SIMD_TEST( (is_same<sign_of<boost::simd::uint32_t>::type,unsigned>::value ));
  BOOST_SIMD_TEST( (is_same<sign_of<boost::simd::uint16_t>::type,unsigned>::value ));
  BOOST_SIMD_TEST( (is_same<sign_of<boost::simd::uint8_t >::type,unsigned>::value ));
  BOOST_SIMD_TEST( (is_same<sign_of<bool         >::type,unsigned>::value ));
}
