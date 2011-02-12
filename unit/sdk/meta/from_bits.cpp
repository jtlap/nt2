/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::meta::from_bits"

#include <nt2/sdk/config/types.hpp>
#include <nt2/sdk/meta/from_bits.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

////////////////////////////////////////////////////////////////////////////////
// Test that from_bits return the proper value
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(from_bits_real)
{
  using nt2::meta::from_bits;

	from_bits<double>::type zd = { 0x0000000000000000LL };
	from_bits<double>::type od = { 0x3FF0000000000000LL };
  from_bits<float>::type  zf = { 0x00000000 };
  from_bits<float>::type  of = { 0x3F800000 };

  NT2_TEST_EQUAL( zd.value, 0.  );
  NT2_TEST_EQUAL( od.value, 1.  );
  NT2_TEST_EQUAL( zf.value, 0.f );
  NT2_TEST_EQUAL( of.value, 1.f );
}

////////////////////////////////////////////////////////////////////////////////
// Test that from_bits return the proper value for integer types
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL	(	from_bits_integer
									, (nt2::uint64_t)(nt2::uint32_t)(nt2::uint16_t)(nt2::uint8_t)
										(nt2::int64_t)(nt2::int32_t)(nt2::int16_t)(nt2::int8_t)
									)
{
  using nt2::meta::from_bits;

	typename from_bits<T>::type z = { 0 };
	typename from_bits<T>::type o = { 1 };
	typename from_bits<T>::type c = { T(~0) };
  
  NT2_TEST_EQUAL( z.value, T( 0));
  NT2_TEST_EQUAL( o.value, T( 1));
  NT2_TEST_EQUAL( c.value, T(~0));
}
