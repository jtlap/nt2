/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define BOOST_SIMD_UNIT_MODULE "boost::simd::meta::as_bits"

#include <boost/simd/sdk/config/types.hpp>
#include <boost/simd/sdk/meta/as_bits.hpp>

#include <boost/simd/sdk/unit/module.hpp>
#include <boost/simd/sdk/unit/tests/relation.hpp>

////////////////////////////////////////////////////////////////////////////////
// Test that as_bits return the proper bits
////////////////////////////////////////////////////////////////////////////////
BOOST_SIMD_TEST_CASE(as_bits_real)
{
  using boost::simd::meta::as_bits;

  as_bits<double>::type zd = { 0. };
  as_bits<double>::type od = { 1. };
  as_bits<float>::type  zf = { 0.f };
  as_bits<float>::type  of = { 1.f };

  BOOST_SIMD_TEST_EQUAL( zd.bits, 0x0000000000000000LL);
  BOOST_SIMD_TEST_EQUAL( od.bits, 0x3FF0000000000000LL);
  BOOST_SIMD_TEST_EQUAL( zf.bits, 0x00000000 );
  BOOST_SIMD_TEST_EQUAL( of.bits, 0x3F800000 );
}

////////////////////////////////////////////////////////////////////////////////
// Test that as_bits return the proper bits for integer types
////////////////////////////////////////////////////////////////////////////////
BOOST_SIMD_TEST_CASE_TPL ( as_bits_integer, BOOST_SIMD_INTEGRAL_TYPES )
{
  using boost::simd::meta::as_bits;

  typename as_bits<T>::type z = { 0 };
  typename as_bits<T>::type o = { 1 };
  typename as_bits<T,signed>::type c = { T(~0) };

  BOOST_SIMD_TEST_EQUAL( z.bits,  0);
  BOOST_SIMD_TEST_EQUAL( o.bits,  1);
  BOOST_SIMD_TEST_EQUAL( c.bits, ~0);
}
