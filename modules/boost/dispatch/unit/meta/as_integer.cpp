/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define BOOST_SIMD_UNIT_MODULE "boost::dispatch::meta::as_integer"

#include <boost/simd/sdk/config/types.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/type_traits/is_same.hpp>

#include <boost/simd/sdk/unit/module.hpp>
#include <boost/simd/sdk/unit/tests/basic.hpp>

////////////////////////////////////////////////////////////////////////////////
// Test that as_integer is correct w/r to original sign
////////////////////////////////////////////////////////////////////////////////
BOOST_SIMD_TEST_CASE(as_integer_native_sign)
{
  using boost::dispatch::meta::as_integer;
  using boost::is_same;

  BOOST_SIMD_TEST( (is_same<as_integer<double  >::type,boost::simd::int64_t >::value ));
  BOOST_SIMD_TEST( (is_same<as_integer<float   >::type,boost::simd::int32_t >::value ));
  BOOST_SIMD_TEST( (is_same<as_integer<boost::simd::int64_t >::type,boost::simd::int64_t >::value ));
  BOOST_SIMD_TEST( (is_same<as_integer<boost::simd::int32_t >::type,boost::simd::int32_t >::value ));
  BOOST_SIMD_TEST( (is_same<as_integer<boost::simd::int16_t >::type,boost::simd::int16_t >::value ));
  BOOST_SIMD_TEST( (is_same<as_integer<boost::simd::int8_t  >::type,boost::simd::int8_t  >::value ));
  BOOST_SIMD_TEST( (is_same<as_integer<boost::simd::uint64_t>::type,boost::simd::uint64_t>::value ));
  BOOST_SIMD_TEST( (is_same<as_integer<boost::simd::uint32_t>::type,boost::simd::uint32_t>::value ));
  BOOST_SIMD_TEST( (is_same<as_integer<boost::simd::uint16_t>::type,boost::simd::uint16_t>::value ));
  BOOST_SIMD_TEST( (is_same<as_integer<boost::simd::uint8_t >::type,boost::simd::uint8_t >::value ));
  BOOST_SIMD_TEST( (is_same<as_integer<bool    >::type,boost::simd::uint8_t >::value ));
}

////////////////////////////////////////////////////////////////////////////////
// Test that as_integer is correct w/r to forced sign
////////////////////////////////////////////////////////////////////////////////
BOOST_SIMD_TEST_CASE(as_integer_native_forced_signed)
{
  using boost::dispatch::meta::as_integer;
  using boost::is_same;
  using namespace boost::simd;

  BOOST_SIMD_TEST( (is_same<as_integer<double  ,unsigned>::type,boost::simd::uint64_t >::value ));
  BOOST_SIMD_TEST( (is_same<as_integer<float   ,unsigned>::type,boost::simd::uint32_t >::value ));
  BOOST_SIMD_TEST( (is_same<as_integer<boost::simd::int64_t ,unsigned>::type,boost::simd::uint64_t >::value ));
  BOOST_SIMD_TEST( (is_same<as_integer<boost::simd::int32_t ,unsigned>::type,boost::simd::uint32_t >::value ));
  BOOST_SIMD_TEST( (is_same<as_integer<boost::simd::int16_t ,unsigned>::type,boost::simd::uint16_t >::value ));
  BOOST_SIMD_TEST( (is_same<as_integer<boost::simd::int8_t  ,unsigned>::type,boost::simd::uint8_t  >::value ));
  BOOST_SIMD_TEST( (is_same<as_integer<boost::simd::uint64_t,unsigned>::type,boost::simd::uint64_t >::value ));
  BOOST_SIMD_TEST( (is_same<as_integer<boost::simd::uint32_t,unsigned>::type,boost::simd::uint32_t >::value ));
  BOOST_SIMD_TEST( (is_same<as_integer<boost::simd::uint16_t,unsigned>::type,boost::simd::uint16_t >::value ));
  BOOST_SIMD_TEST( (is_same<as_integer<boost::simd::uint8_t ,unsigned>::type,boost::simd::uint8_t  >::value ));
  BOOST_SIMD_TEST( (is_same<as_integer<bool    ,unsigned>::type,boost::simd::uint8_t >::value ));
}

////////////////////////////////////////////////////////////////////////////////
// Test that as_integer is correct w/r to forced sign
////////////////////////////////////////////////////////////////////////////////
BOOST_SIMD_TEST_CASE(as_integer_native_forced_unsigned)
{
  using boost::dispatch::meta::as_integer;
  using boost::is_same;
  using namespace boost::simd;

  BOOST_SIMD_TEST( (is_same<as_integer<double  ,signed>::type,boost::simd::int64_t>::value ));
  BOOST_SIMD_TEST( (is_same<as_integer<float   ,signed>::type,boost::simd::int32_t>::value ));
  BOOST_SIMD_TEST( (is_same<as_integer<boost::simd::int64_t ,signed>::type,boost::simd::int64_t>::value ));
  BOOST_SIMD_TEST( (is_same<as_integer<boost::simd::int32_t ,signed>::type,boost::simd::int32_t>::value ));
  BOOST_SIMD_TEST( (is_same<as_integer<boost::simd::int16_t ,signed>::type,boost::simd::int16_t>::value ));
  BOOST_SIMD_TEST( (is_same<as_integer<boost::simd::int8_t  ,signed>::type,boost::simd::int8_t >::value ));
  BOOST_SIMD_TEST( (is_same<as_integer<boost::simd::uint64_t,signed>::type,boost::simd::int64_t>::value ));
  BOOST_SIMD_TEST( (is_same<as_integer<boost::simd::uint32_t,signed>::type,boost::simd::int32_t>::value ));
  BOOST_SIMD_TEST( (is_same<as_integer<boost::simd::uint16_t,signed>::type,boost::simd::int16_t>::value ));
  BOOST_SIMD_TEST( (is_same<as_integer<boost::simd::uint8_t ,signed>::type,boost::simd::int8_t >::value ));
  BOOST_SIMD_TEST( (is_same<as_integer<bool    ,signed>::type,boost::simd::int8_t >::value ));
}
