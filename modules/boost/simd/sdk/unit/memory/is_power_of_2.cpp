/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 0x01.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "boost::simd::is_power_of_2"

#include <boost/simd/sdk/memory/is_power_of_2.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/sdk/memory/meta/is_power_of_2.hpp>

#include <boost/mpl/int.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>

////////////////////////////////////////////////////////////////////////////////
// Test the meta::is_power_of_2 version on int_
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(is_power_of_2)
{
  using boost::simd::is_power_of_2;

  NT2_TEST(!is_power_of_2(0x00) );
  NT2_TEST( is_power_of_2(0x01) );
  NT2_TEST( is_power_of_2(0x02) );
  NT2_TEST(!is_power_of_2(0x03) );
  NT2_TEST( is_power_of_2(0x04) );
  NT2_TEST(!is_power_of_2(0x05) );
  NT2_TEST(!is_power_of_2(0x06) );
  NT2_TEST(!is_power_of_2(0x07) );
  NT2_TEST( is_power_of_2(0x08) );
  NT2_TEST( is_power_of_2(0x10) );
  NT2_TEST( is_power_of_2(0x20) );
  NT2_TEST( is_power_of_2(0x40) );
  NT2_TEST( is_power_of_2(0x80) );
  NT2_TEST(!is_power_of_2(1337) );
}
////////////////////////////////////////////////////////////////////////////////
// Test the meta::is_power_of_2 version on int_
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(meta_is_power_of_2)
{
  using boost::simd::meta::is_power_of_2;
  using boost::mpl::int_;

  NT2_TEST(!(is_power_of_2< int_<0x00> >::value));
  NT2_TEST( (is_power_of_2< int_<0x01> >::value));
  NT2_TEST( (is_power_of_2< int_<0x02> >::value));
  NT2_TEST(!(is_power_of_2< int_<0x03> >::value));
  NT2_TEST( (is_power_of_2< int_<0x04> >::value));
  NT2_TEST(!(is_power_of_2< int_<0x05> >::value));
  NT2_TEST(!(is_power_of_2< int_<0x06> >::value));
  NT2_TEST(!(is_power_of_2< int_<0x07> >::value));
  NT2_TEST( (is_power_of_2< int_<0x08> >::value));
  NT2_TEST( (is_power_of_2< int_<0x10> >::value));
  NT2_TEST( (is_power_of_2< int_<0x20> >::value));
  NT2_TEST( (is_power_of_2< int_<0x40> >::value));
  NT2_TEST( (is_power_of_2< int_<0x80> >::value));
  NT2_TEST(!(is_power_of_2< int_<1337> >::value));
}

////////////////////////////////////////////////////////////////////////////////
// Test the meta::is_power_of_2 version on integer
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(meta_is_power_of_2_c)
{
  using boost::simd::meta::is_power_of_2_c;

  NT2_TEST(!(is_power_of_2_c< 0x00 >::value));
  NT2_TEST( (is_power_of_2_c< 0x01 >::value));
  NT2_TEST( (is_power_of_2_c< 0x02 >::value));
  NT2_TEST(!(is_power_of_2_c< 0x03 >::value));
  NT2_TEST( (is_power_of_2_c< 0x04 >::value));
  NT2_TEST(!(is_power_of_2_c< 0x05 >::value));
  NT2_TEST(!(is_power_of_2_c< 0x06 >::value));
  NT2_TEST(!(is_power_of_2_c< 0x07 >::value));
  NT2_TEST( (is_power_of_2_c< 0x08 >::value));
  NT2_TEST( (is_power_of_2_c< 0x10 >::value));
  NT2_TEST( (is_power_of_2_c< 0x20 >::value));
  NT2_TEST( (is_power_of_2_c< 0x40 >::value));
  NT2_TEST( (is_power_of_2_c< 0x80 >::value));
  NT2_TEST(!(is_power_of_2_c< 1337 >::value));
}
