/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define BOOST_SIMD_UNIT_MODULE "boost::simd::meta::from_bits"

#include <boost/simd/sdk/config/types.hpp>
#include <boost/simd/sdk/meta/from_bits.hpp>
#include <boost/simd/sdk/unit/module.hpp>
#include <boost/simd/sdk/unit/tests/relation.hpp>

////////////////////////////////////////////////////////////////////////////////
// Test that from_bits return the proper value
////////////////////////////////////////////////////////////////////////////////
BOOST_SIMD_TEST_CASE(from_bits_real)
{
  using boost::simd::meta::from_bits;

	from_bits<double>::type zd = { 0x0000000000000000LL };
	from_bits<double>::type od = { 0x3FF0000000000000LL };
  from_bits<float>::type  zf = { 0x00000000 };
  from_bits<float>::type  of = { 0x3F800000 };

  BOOST_SIMD_TEST_EQUAL( zd.value, 0.  );
  BOOST_SIMD_TEST_EQUAL( od.value, 1.  );
  BOOST_SIMD_TEST_EQUAL( zf.value, 0.f );
  BOOST_SIMD_TEST_EQUAL( of.value, 1.f );
}

////////////////////////////////////////////////////////////////////////////////
// Test that from_bits return the proper value for integer types
////////////////////////////////////////////////////////////////////////////////
BOOST_SIMD_TEST_CASE_TPL	(	from_bits_integer
									, (boost::simd::uint64_t)(boost::simd::uint32_t)(boost::simd::uint16_t)(boost::simd::uint8_t)
										(boost::simd::int64_t)(boost::simd::int32_t)(boost::simd::int16_t)(boost::simd::int8_t)
									)
{
  using boost::simd::meta::from_bits;

	typename from_bits<T>::type z = { 0 };
	typename from_bits<T>::type o = { 1 };
	typename from_bits<T>::type c = { T(~0) };
  
  BOOST_SIMD_TEST_EQUAL( z.value, T( 0));
  BOOST_SIMD_TEST_EQUAL( o.value, T( 1));
  BOOST_SIMD_TEST_EQUAL( c.value, T(~0));
}
