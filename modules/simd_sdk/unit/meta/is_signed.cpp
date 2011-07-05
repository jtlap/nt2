/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define BOOST_SIMD_UNIT_MODULE "boost::simd::meta::is_signed"

#include <boost/simd/sdk/config/types.hpp>
#include <boost/simd/sdk/meta/is_signed.hpp>
#include <boost/simd/sdk/unit/module.hpp>
#include <boost/simd/sdk/unit/tests/basic.hpp>

////////////////////////////////////////////////////////////////////////////////
// Test that is_signed is correct
////////////////////////////////////////////////////////////////////////////////
BOOST_SIMD_TEST_CASE(is_signed)
{
  using boost::simd::meta::is_signed;
  using namespace boost;

  BOOST_SIMD_TEST( is_signed<double>::value        );
  BOOST_SIMD_TEST( is_signed<float>::value         );
  BOOST_SIMD_TEST( !is_signed<boost::simd::uint64_t>::value);
  BOOST_SIMD_TEST( !is_signed<boost::simd::uint32_t>::value);
  BOOST_SIMD_TEST( !is_signed<boost::simd::uint16_t>::value);
  BOOST_SIMD_TEST( !is_signed<boost::simd::uint8_t>::value );
  BOOST_SIMD_TEST( is_signed<boost::simd::int64_t>::value  );
  BOOST_SIMD_TEST( is_signed<boost::simd::int32_t>::value  );
  BOOST_SIMD_TEST( is_signed<boost::simd::int16_t>::value  );
  BOOST_SIMD_TEST( is_signed<boost::simd::int8_t>::value   );
  BOOST_SIMD_TEST( !is_signed<bool>::value         );
}

BOOST_SIMD_TEST_CASE(is_unsigned)
{
  using boost::simd::meta::is_unsigned;
  using namespace boost;

  BOOST_SIMD_TEST( !is_unsigned<double>::value        );
  BOOST_SIMD_TEST( !is_unsigned<float>::value         );
  BOOST_SIMD_TEST(  is_unsigned<boost::simd::uint64_t>::value );
  BOOST_SIMD_TEST(  is_unsigned<boost::simd::uint32_t>::value );
  BOOST_SIMD_TEST(  is_unsigned<boost::simd::uint16_t>::value );
  BOOST_SIMD_TEST(  is_unsigned<boost::simd::uint8_t>::value  );
  BOOST_SIMD_TEST( !is_unsigned<boost::simd::int64_t>::value  );
  BOOST_SIMD_TEST( !is_unsigned<boost::simd::int32_t>::value  );
  BOOST_SIMD_TEST( !is_unsigned<boost::simd::int16_t>::value  );
  BOOST_SIMD_TEST( !is_unsigned<boost::simd::int8_t>::value   );
  BOOST_SIMD_TEST(  is_unsigned<bool>::value          );
}
