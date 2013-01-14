/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "boost::simd::meta::cardinal_of"

#include <boost/simd/sdk/config/types.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/sdk/meta/cardinal_of.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

////////////////////////////////////////////////////////////////////////////////
// Test that cardinal_of scalars is 1
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(cardinal_of_scalar)
{
  using boost::simd::meta::cardinal_of;

  NT2_TEST_EQUAL( cardinal_of<double>::value        , 1u );
  NT2_TEST_EQUAL( cardinal_of<float>::value         , 1u );
  NT2_TEST_EQUAL( cardinal_of<boost::simd::uint64_t>::value , 1u );
  NT2_TEST_EQUAL( cardinal_of<boost::simd::uint32_t>::value , 1u );
  NT2_TEST_EQUAL( cardinal_of<boost::simd::uint16_t>::value , 1u );
  NT2_TEST_EQUAL( cardinal_of<boost::simd::uint8_t>::value  , 1u );
  NT2_TEST_EQUAL( cardinal_of<boost::simd::int64_t>::value  , 1u );
  NT2_TEST_EQUAL( cardinal_of<boost::simd::int32_t>::value  , 1u );
  NT2_TEST_EQUAL( cardinal_of<boost::simd::int16_t>::value  , 1u );
  NT2_TEST_EQUAL( cardinal_of<boost::simd::int8_t>::value   , 1u );
  NT2_TEST_EQUAL( cardinal_of<bool>::value          , 1u );
}

NT2_TEST_CASE_TPL(cardinal_of_cref, BOOST_SIMD_TYPES)
{
  using boost::simd::meta::cardinal_of;

  NT2_TEST_EQUAL( cardinal_of<T&>::value      , cardinal_of<T>::value );
  NT2_TEST_EQUAL( cardinal_of<T const>::value , cardinal_of<T>::value );
  NT2_TEST_EQUAL( cardinal_of<T const&>::value, cardinal_of<T>::value );
}
