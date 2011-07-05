/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define BOOST_SIMD_UNIT_MODULE "boost::simd::meta::is_scalar"

#include <boost/simd/sdk/config/types.hpp>
#include <boost/simd/sdk/meta/is_scalar.hpp>
#include <boost/simd/sdk/unit/module.hpp>
#include <boost/simd/sdk/unit/tests/basic.hpp>

////////////////////////////////////////////////////////////////////////////////
// Test that scalar are scalar (dur)
////////////////////////////////////////////////////////////////////////////////
BOOST_SIMD_TEST_CASE(is_scalar_scalar)
{
  using boost::simd::meta::is_scalar;

  BOOST_SIMD_TEST( is_scalar<double>::value        );
  BOOST_SIMD_TEST( is_scalar<float>::value         );
  BOOST_SIMD_TEST( is_scalar<boost::simd::uint64_t>::value );
  BOOST_SIMD_TEST( is_scalar<boost::simd::uint32_t>::value );
  BOOST_SIMD_TEST( is_scalar<boost::simd::uint16_t>::value );
  BOOST_SIMD_TEST( is_scalar<boost::simd::uint8_t>::value  );
  BOOST_SIMD_TEST( is_scalar<boost::simd::int64_t>::value  );
  BOOST_SIMD_TEST( is_scalar<boost::simd::int32_t>::value  );
  BOOST_SIMD_TEST( is_scalar<boost::simd::int16_t>::value  );
  BOOST_SIMD_TEST( is_scalar<boost::simd::int8_t>::value   );
  BOOST_SIMD_TEST( is_scalar<bool>::value          );
}

////////////////////////////////////////////////////////////////////////////////
// Test that non-scalar types are not scalar
////////////////////////////////////////////////////////////////////////////////
struct foo {};  // type of unknown hierarchy

BOOST_SIMD_TEST_CASE(is_nonscalar)
{
  using boost::simd::meta::is_scalar;
  BOOST_SIMD_TEST( !is_scalar<foo>::value );
}
