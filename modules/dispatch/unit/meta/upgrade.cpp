/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define BOOST_SIMD_UNIT_MODULE "boost::simd::meta::upgrade"

#include <boost/simd/sdk/config/types.hpp>
#include <boost/simd/sdk/meta/upgrade.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/simd/sdk/unit/module.hpp>
#include <boost/simd/sdk/unit/tests/basic.hpp>

////////////////////////////////////////////////////////////////////////////////
// Test that upgrade is correct for middle-sized types
////////////////////////////////////////////////////////////////////////////////
BOOST_SIMD_TEST_CASE(upgrade_ints)
{
  using boost::simd::meta::upgrade;
  using boost::is_same;

  BOOST_SIMD_TEST( (is_same<upgrade<double  			>::type,double 				>::value ));
  BOOST_SIMD_TEST( (is_same<upgrade<float   			>::type,double 				>::value ));
  BOOST_SIMD_TEST( (is_same<upgrade<boost::simd::int32_t >::type,boost::simd::int64_t 	>::value ));
  BOOST_SIMD_TEST( (is_same<upgrade<boost::simd::int16_t >::type,boost::simd::int32_t 	>::value ));
  BOOST_SIMD_TEST( (is_same<upgrade<boost::simd::int8_t 	>::type,boost::simd::int16_t 	>::value ));
  BOOST_SIMD_TEST( (is_same<upgrade<boost::simd::uint32_t>::type,boost::simd::uint64_t >::value ));
  BOOST_SIMD_TEST( (is_same<upgrade<boost::simd::uint16_t>::type,boost::simd::uint32_t >::value ));
  BOOST_SIMD_TEST( (is_same<upgrade<boost::simd::uint8_t	>::type,boost::simd::uint16_t	>::value ));
}

////////////////////////////////////////////////////////////////////////////////
// Test that upgrade is correct w/r to forced sign
////////////////////////////////////////////////////////////////////////////////
BOOST_SIMD_TEST_CASE(upgrade_ints_forced_signed)
{
  using boost::simd::meta::upgrade;
  using boost::is_same;

  BOOST_SIMD_TEST( (is_same<upgrade<double  			,signed>::type,double				>::value ));
  BOOST_SIMD_TEST( (is_same<upgrade<float   			,signed>::type,double				>::value ));
  BOOST_SIMD_TEST( (is_same<upgrade<boost::simd::int32_t ,signed>::type,boost::simd::int64_t >::value ));
  BOOST_SIMD_TEST( (is_same<upgrade<boost::simd::int16_t ,signed>::type,boost::simd::int32_t >::value ));
  BOOST_SIMD_TEST( (is_same<upgrade<boost::simd::int8_t 	,signed>::type,boost::simd::int16_t	>::value ));
  BOOST_SIMD_TEST( (is_same<upgrade<boost::simd::uint32_t,signed>::type,boost::simd::int64_t >::value ));
  BOOST_SIMD_TEST( (is_same<upgrade<boost::simd::uint16_t,signed>::type,boost::simd::int32_t >::value ));
  BOOST_SIMD_TEST( (is_same<upgrade<boost::simd::uint8_t	,signed>::type,boost::simd::int16_t	>::value ));

  BOOST_SIMD_TEST( (is_same<upgrade<double  			,unsigned>::type,double				>::value ));
  BOOST_SIMD_TEST( (is_same<upgrade<float   			,unsigned>::type,double				>::value ));
  BOOST_SIMD_TEST( (is_same<upgrade<boost::simd::int32_t ,unsigned>::type,boost::simd::uint64_t>::value ));
  BOOST_SIMD_TEST( (is_same<upgrade<boost::simd::int16_t ,unsigned>::type,boost::simd::uint32_t>::value ));
  BOOST_SIMD_TEST( (is_same<upgrade<boost::simd::int8_t 	,unsigned>::type,boost::simd::uint16_t>::value ));
  BOOST_SIMD_TEST( (is_same<upgrade<boost::simd::uint32_t,unsigned>::type,boost::simd::uint64_t>::value ));
  BOOST_SIMD_TEST( (is_same<upgrade<boost::simd::uint16_t,unsigned>::type,boost::simd::uint32_t>::value ));
  BOOST_SIMD_TEST( (is_same<upgrade<boost::simd::uint8_t	,unsigned>::type,boost::simd::uint16_t>::value ));
}

////////////////////////////////////////////////////////////////////////////////
// Test that upgrade is correct w/r to tpye of sizeof == 8
////////////////////////////////////////////////////////////////////////////////
BOOST_SIMD_TEST_CASE(upgrade_sizeof_8)
{
  using boost::simd::meta::upgrade;
  using boost::is_same;

  BOOST_SIMD_TEST( (is_same<upgrade<boost::simd::uint64_t					>::type,boost::simd::uint64_t>::value ));
  BOOST_SIMD_TEST( (is_same<upgrade<boost::simd::uint64_t					>::type,boost::simd::uint64_t>::value ));
  BOOST_SIMD_TEST( (is_same<upgrade<boost::simd::uint64_t,signed		>::type,boost::simd::int64_t>::value 	));
  BOOST_SIMD_TEST( (is_same<upgrade<boost::simd::uint64_t,signed		>::type,boost::simd::int64_t>::value 	));
  BOOST_SIMD_TEST( (is_same<upgrade<boost::simd::uint64_t,unsigned	>::type,boost::simd::uint64_t>::value ));
  BOOST_SIMD_TEST( (is_same<upgrade<boost::simd::uint64_t,unsigned	>::type,boost::simd::uint64_t>::value ));
}

