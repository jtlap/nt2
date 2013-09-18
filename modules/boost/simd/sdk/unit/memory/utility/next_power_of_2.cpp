//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/meta/next_power_of_2.hpp>
#include <boost/simd/sdk/next_power_of_2.hpp>

#include <boost/mpl/int.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

////////////////////////////////////////////////////////////////////////////////
// Test the meta::next_power_of_2 version on int_
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(static_next_power_of_2)
{
  using boost::simd::meta::next_power_of_2;
  using boost::mpl::int_;

  NT2_TEST_EQUAL( (next_power_of_2< int_<0x00> >::value), 0x00 );
  NT2_TEST_EQUAL( (next_power_of_2< int_<0x01> >::value), 0x01 );
  NT2_TEST_EQUAL( (next_power_of_2< int_<0x02> >::value), 0x02 );
  NT2_TEST_EQUAL( (next_power_of_2< int_<0x03> >::value), 0x04 );
  NT2_TEST_EQUAL( (next_power_of_2< int_<0x04> >::value), 0x04 );
  NT2_TEST_EQUAL( (next_power_of_2< int_<0x05> >::value), 0x08 );
  NT2_TEST_EQUAL( (next_power_of_2< int_<0x06> >::value), 0x08 );
  NT2_TEST_EQUAL( (next_power_of_2< int_<0x07> >::value), 0x08 );
  NT2_TEST_EQUAL( (next_power_of_2< int_<0x08> >::value), 0x08 );
  NT2_TEST_EQUAL( (next_power_of_2< int_<0x0D> >::value), 0x10 );
  NT2_TEST_EQUAL( (next_power_of_2< int_<0x14> >::value), 0x20 );
  NT2_TEST_EQUAL( (next_power_of_2< int_<0x33> >::value), 0x40 );
  NT2_TEST_EQUAL( (next_power_of_2< int_<0x6A> >::value), 0x80 );
  NT2_TEST_EQUAL( (next_power_of_2< int_<0x201> >::value), 0x400 );
}

////////////////////////////////////////////////////////////////////////////////
// Test the next_power_of_2 version on int
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(dynamic_next_power_of_2)
{
  using boost::simd::next_power_of_2;

  NT2_TEST_EQUAL( next_power_of_2(0x00), 0x00 );
  NT2_TEST_EQUAL( next_power_of_2(0x01), 0x01 );
  NT2_TEST_EQUAL( next_power_of_2(0x02), 0x02 );
  NT2_TEST_EQUAL( next_power_of_2(0x03), 0x04 );
  NT2_TEST_EQUAL( next_power_of_2(0x04), 0x04 );
  NT2_TEST_EQUAL( next_power_of_2(0x05), 0x08 );
  NT2_TEST_EQUAL( next_power_of_2(0x06), 0x08 );
  NT2_TEST_EQUAL( next_power_of_2(0x07), 0x08 );
  NT2_TEST_EQUAL( next_power_of_2(0x08), 0x08 );
  NT2_TEST_EQUAL( next_power_of_2(0x0D), 0x10 );
  NT2_TEST_EQUAL( next_power_of_2(0x14), 0x20 );
  NT2_TEST_EQUAL( next_power_of_2(0x33), 0x40 );
  NT2_TEST_EQUAL( next_power_of_2(0x6A), 0x80 );
  NT2_TEST_EQUAL( next_power_of_2(0x201), 0x400 );
}

////////////////////////////////////////////////////////////////////////////////
// Test the meta::next_power_of_2 version on integral constant
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(next_power_of_2_c)
{
  using boost::simd::meta::next_power_of_2_c;

  NT2_TEST_EQUAL( (next_power_of_2_c< 0x00 >::value), 0x00U );
  NT2_TEST_EQUAL( (next_power_of_2_c< 0x01 >::value), 0x01U );
  NT2_TEST_EQUAL( (next_power_of_2_c< 0x02 >::value), 0x02U );
  NT2_TEST_EQUAL( (next_power_of_2_c< 0x03 >::value), 0x04U );
  NT2_TEST_EQUAL( (next_power_of_2_c< 0x04 >::value), 0x04U );
  NT2_TEST_EQUAL( (next_power_of_2_c< 0x05 >::value), 0x08U );
  NT2_TEST_EQUAL( (next_power_of_2_c< 0x06 >::value), 0x08U );
  NT2_TEST_EQUAL( (next_power_of_2_c< 0x07 >::value), 0x08U );
  NT2_TEST_EQUAL( (next_power_of_2_c< 0x08 >::value), 0x08U );
  NT2_TEST_EQUAL( (next_power_of_2_c< 0x0D >::value), 0x10U );
  NT2_TEST_EQUAL( (next_power_of_2_c< 0x14 >::value), 0x20U );
  NT2_TEST_EQUAL( (next_power_of_2_c< 0x33 >::value), 0x40U );
  NT2_TEST_EQUAL( (next_power_of_2_c< 0x6A >::value), 0x80U );
  NT2_TEST_EQUAL( (next_power_of_2_c< 0x201 >::value), 0x400U );
}
