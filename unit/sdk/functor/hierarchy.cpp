/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::functors::hierarchy"

#include <nt2/sdk/config/types.hpp>
#include <nt2/sdk/meta/has_key.hpp>
#include <nt2/sdk/functor/hierarchy.hpp>

#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>

////////////////////////////////////////////////////////////////////////////////
// Test elements of empty_
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(empty_hierarchy)
{
  using nt2::functors::empty_;
  using nt2::meta::has_key;

  NT2_TEST( !(has_key<empty_, nt2::uint8_t >::value) );
  NT2_TEST( !(has_key<empty_, nt2::uint16_t>::value) );
  NT2_TEST( !(has_key<empty_, nt2::uint32_t>::value) );
  NT2_TEST( !(has_key<empty_, nt2::uint64_t>::value) );
  NT2_TEST( !(has_key<empty_, nt2::int8_t  >::value) );
  NT2_TEST( !(has_key<empty_, nt2::int16_t >::value) );
  NT2_TEST( !(has_key<empty_, nt2::int32_t >::value) );
  NT2_TEST( !(has_key<empty_, nt2::int64_t >::value) );
  NT2_TEST( !(has_key<empty_, float   >::value) );
  NT2_TEST( !(has_key<empty_, double  >::value) );
  NT2_TEST( !(has_key<empty_, bool    >::value) );
}

////////////////////////////////////////////////////////////////////////////////
// Test elements of bool_
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(bool_hierarchy)
{
  using nt2::functors::bool_;
  using nt2::meta::has_key;

  NT2_TEST( !(has_key<bool_, nt2::uint8_t >::value) );
  NT2_TEST( !(has_key<bool_, nt2::uint16_t>::value) );
  NT2_TEST( !(has_key<bool_, nt2::uint32_t>::value) );
  NT2_TEST( !(has_key<bool_, nt2::uint64_t>::value) );
  NT2_TEST( !(has_key<bool_, nt2::int8_t  >::value) );
  NT2_TEST( !(has_key<bool_, nt2::int16_t >::value) );
  NT2_TEST( !(has_key<bool_, nt2::int32_t >::value) );
  NT2_TEST( !(has_key<bool_, nt2::int64_t >::value) );
  NT2_TEST( !(has_key<bool_, float   >::value) );
  NT2_TEST( !(has_key<bool_, double  >::value) );
  NT2_TEST(  (has_key<bool_, bool    >::value) );
}

////////////////////////////////////////////////////////////////////////////////
// Test elements of int8_
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(int8_hierarchy)
{
  using nt2::functors::int8_;
  using nt2::meta::has_key;

  NT2_TEST(  (has_key<int8_, nt2::uint8_t >::value) );
  NT2_TEST( !(has_key<int8_, nt2::uint16_t>::value) );
  NT2_TEST( !(has_key<int8_, nt2::uint32_t>::value) );
  NT2_TEST( !(has_key<int8_, nt2::uint64_t>::value) );
  NT2_TEST(  (has_key<int8_, nt2::int8_t  >::value) );
  NT2_TEST( !(has_key<int8_, nt2::int16_t >::value) );
  NT2_TEST( !(has_key<int8_, nt2::int32_t >::value) );
  NT2_TEST( !(has_key<int8_, nt2::int64_t >::value) );
  NT2_TEST( !(has_key<int8_, float   >::value) );
  NT2_TEST( !(has_key<int8_, double  >::value) );
  NT2_TEST( !(has_key<int8_, bool    >::value) );
}

////////////////////////////////////////////////////////////////////////////////
// Test elements of int16_
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(int16_hierarchy)
{
  using nt2::functors::int16_;
  using nt2::meta::has_key;

  NT2_TEST( !(has_key<int16_, nt2::uint8_t >::value) );
  NT2_TEST(  (has_key<int16_, nt2::uint16_t>::value) );
  NT2_TEST( !(has_key<int16_, nt2::uint32_t>::value) );
  NT2_TEST( !(has_key<int16_, nt2::uint64_t>::value) );
  NT2_TEST( !(has_key<int16_, nt2::int8_t  >::value) );
  NT2_TEST(  (has_key<int16_, nt2::int16_t >::value) );
  NT2_TEST( !(has_key<int16_, nt2::int32_t >::value) );
  NT2_TEST( !(has_key<int16_, nt2::int64_t >::value) );
  NT2_TEST( !(has_key<int16_, float   >::value) );
  NT2_TEST( !(has_key<int16_, double  >::value) );
  NT2_TEST( !(has_key<int16_, bool    >::value) );
}

////////////////////////////////////////////////////////////////////////////////
// Test elements of int32_
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(int32_hierarchy)
{
  using nt2::functors::int32_;
  using nt2::meta::has_key;

  NT2_TEST( !(has_key<int32_, nt2::uint8_t >::value) );
  NT2_TEST( !(has_key<int32_, nt2::uint16_t>::value) );
  NT2_TEST(  (has_key<int32_, nt2::uint32_t>::value) );
  NT2_TEST( !(has_key<int32_, nt2::uint64_t>::value) );
  NT2_TEST( !(has_key<int32_, nt2::int8_t  >::value) );
  NT2_TEST( !(has_key<int32_, nt2::int16_t >::value) );
  NT2_TEST(  (has_key<int32_, nt2::int32_t >::value) );
  NT2_TEST( !(has_key<int32_, nt2::int64_t >::value) );
  NT2_TEST( !(has_key<int32_, float   >::value) );
  NT2_TEST( !(has_key<int32_, double  >::value) );
  NT2_TEST( !(has_key<int32_, bool    >::value) );
}

////////////////////////////////////////////////////////////////////////////////
// Test elements of int64_
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(int64_hierarchy)
{
  using nt2::functors::int64_;
  using nt2::meta::has_key;

  NT2_TEST( !(has_key<int64_, nt2::uint8_t >::value) );
  NT2_TEST( !(has_key<int64_, nt2::uint16_t>::value) );
  NT2_TEST( !(has_key<int64_, nt2::uint32_t>::value) );
  NT2_TEST(  (has_key<int64_, nt2::uint64_t>::value) );
  NT2_TEST( !(has_key<int64_, nt2::int8_t  >::value) );
  NT2_TEST( !(has_key<int64_, nt2::int16_t >::value) );
  NT2_TEST( !(has_key<int64_, nt2::int32_t >::value) );
  NT2_TEST(  (has_key<int64_, nt2::int64_t >::value) );
  NT2_TEST( !(has_key<int64_, float   >::value) );
  NT2_TEST( !(has_key<int64_, double  >::value) );
  NT2_TEST( !(has_key<int64_, bool    >::value) );
}

////////////////////////////////////////////////////////////////////////////////
// Test elements of types8_
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(types8_hierarchy)
{
  using nt2::functors::types8_;
  using nt2::meta::has_key;

  NT2_TEST(  (has_key<types8_, nt2::uint8_t >::value) );
  NT2_TEST( !(has_key<types8_, nt2::uint16_t>::value) );
  NT2_TEST( !(has_key<types8_, nt2::uint32_t>::value) );
  NT2_TEST( !(has_key<types8_, nt2::uint64_t>::value) );
  NT2_TEST(  (has_key<types8_, nt2::int8_t  >::value) );
  NT2_TEST( !(has_key<types8_, nt2::int16_t >::value) );
  NT2_TEST( !(has_key<types8_, nt2::int32_t >::value) );
  NT2_TEST( !(has_key<types8_, nt2::int64_t >::value) );
  NT2_TEST( !(has_key<types8_, float   >::value) );
  NT2_TEST( !(has_key<types8_, double  >::value) );
  NT2_TEST( !(has_key<types8_, bool    >::value) );
}

////////////////////////////////////////////////////////////////////////////////
// Test elements of types16_
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(types16_hierarchy)
{
  using nt2::functors::types16_;
  using nt2::meta::has_key;

  NT2_TEST( !(has_key<types16_, nt2::uint8_t >::value) );
  NT2_TEST(  (has_key<types16_, nt2::uint16_t>::value) );
  NT2_TEST( !(has_key<types16_, nt2::uint32_t>::value) );
  NT2_TEST( !(has_key<types16_, nt2::uint64_t>::value) );
  NT2_TEST( !(has_key<types16_, nt2::int8_t  >::value) );
  NT2_TEST(  (has_key<types16_, nt2::int16_t >::value) );
  NT2_TEST( !(has_key<types16_, nt2::int32_t >::value) );
  NT2_TEST( !(has_key<types16_, nt2::int64_t >::value) );
  NT2_TEST( !(has_key<types16_, float   >::value) );
  NT2_TEST( !(has_key<types16_, double  >::value) );
  NT2_TEST( !(has_key<types16_, bool    >::value) );
}

////////////////////////////////////////////////////////////////////////////////
// Test elements of types32_
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(types32_hierarchy)
{
  using nt2::functors::types32_;
  using nt2::meta::has_key;

  NT2_TEST( !(has_key<types32_, nt2::uint8_t >::value) );
  NT2_TEST( !(has_key<types32_, nt2::uint16_t>::value) );
  NT2_TEST(  (has_key<types32_, nt2::uint32_t>::value) );
  NT2_TEST( !(has_key<types32_, nt2::uint64_t>::value) );
  NT2_TEST( !(has_key<types32_, nt2::int8_t  >::value) );
  NT2_TEST( !(has_key<types32_, nt2::int16_t >::value) );
  NT2_TEST(  (has_key<types32_, nt2::int32_t >::value) );
  NT2_TEST( !(has_key<types32_, nt2::int64_t >::value) );
  NT2_TEST(  (has_key<types32_, float   >::value) );
  NT2_TEST( !(has_key<types32_, double  >::value) );
  NT2_TEST( !(has_key<types32_, bool    >::value) );
}

////////////////////////////////////////////////////////////////////////////////
// Test elements of types64_
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(types64_hierarchy)
{
  using nt2::functors::types64_;
  using nt2::meta::has_key;

  NT2_TEST( !(has_key<types64_, nt2::uint8_t >::value) );
  NT2_TEST( !(has_key<types64_, nt2::uint16_t>::value) );
  NT2_TEST( !(has_key<types64_, nt2::uint32_t>::value) );
  NT2_TEST(  (has_key<types64_, nt2::uint64_t>::value) );
  NT2_TEST( !(has_key<types64_, nt2::int8_t  >::value) );
  NT2_TEST( !(has_key<types64_, nt2::int16_t >::value) );
  NT2_TEST( !(has_key<types64_, nt2::int32_t >::value) );
  NT2_TEST(  (has_key<types64_, nt2::int64_t >::value) );
  NT2_TEST( !(has_key<types64_, float   >::value) );
  NT2_TEST(  (has_key<types64_, double  >::value) );
  NT2_TEST( !(has_key<types64_, bool    >::value) );
}

////////////////////////////////////////////////////////////////////////////////
// Test elements of uint_
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(uint_hierarchy)
{
  using nt2::functors::uint_;
  using nt2::meta::has_key;

  NT2_TEST(  (has_key<uint_, nt2::uint8_t >::value) );
  NT2_TEST(  (has_key<uint_, nt2::uint16_t>::value) );
  NT2_TEST(  (has_key<uint_, nt2::uint32_t>::value) );
  NT2_TEST(  (has_key<uint_, nt2::uint64_t>::value) );
  NT2_TEST( !(has_key<uint_, nt2::int8_t  >::value) );
  NT2_TEST( !(has_key<uint_, nt2::int16_t >::value) );
  NT2_TEST( !(has_key<uint_, nt2::int32_t >::value) );
  NT2_TEST( !(has_key<uint_, nt2::int64_t >::value) );
  NT2_TEST( !(has_key<uint_, float   >::value) );
  NT2_TEST( !(has_key<uint_, double  >::value) );
  NT2_TEST( !(has_key<uint_, bool    >::value) );
}

////////////////////////////////////////////////////////////////////////////////
// Test elements of int_
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(int_hierarchy)
{
  using nt2::functors::int_;
  using nt2::meta::has_key;

  NT2_TEST( !(has_key<int_, nt2::uint8_t >::value) );
  NT2_TEST( !(has_key<int_, nt2::uint16_t>::value) );
  NT2_TEST( !(has_key<int_, nt2::uint32_t>::value) );
  NT2_TEST( !(has_key<int_, nt2::uint64_t>::value) );
  NT2_TEST(  (has_key<int_, nt2::int8_t  >::value) );
  NT2_TEST(  (has_key<int_, nt2::int16_t >::value) );
  NT2_TEST(  (has_key<int_, nt2::int32_t >::value) );
  NT2_TEST(  (has_key<int_, nt2::int64_t >::value) );
  NT2_TEST( !(has_key<int_, float   >::value) );
  NT2_TEST( !(has_key<int_, double  >::value) );
  NT2_TEST( !(has_key<int_, bool    >::value) );
}

////////////////////////////////////////////////////////////////////////////////
// Test elements of real_
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(real_hierarchy)
{
  using nt2::functors::real_;
  using nt2::meta::has_key;

  NT2_TEST( !(has_key<real_, nt2::uint8_t >::value) );
  NT2_TEST( !(has_key<real_, nt2::uint16_t>::value) );
  NT2_TEST( !(has_key<real_, nt2::uint32_t>::value) );
  NT2_TEST( !(has_key<real_, nt2::uint64_t>::value) );
  NT2_TEST( !(has_key<real_, nt2::int8_t  >::value) );
  NT2_TEST( !(has_key<real_, nt2::int16_t >::value) );
  NT2_TEST( !(has_key<real_, nt2::int32_t >::value) );
  NT2_TEST( !(has_key<real_, nt2::int64_t >::value) );
  NT2_TEST(  (has_key<real_, float   >::value) );
  NT2_TEST(  (has_key<real_, double  >::value) );
  NT2_TEST( !(has_key<real_, bool    >::value) );
}

////////////////////////////////////////////////////////////////////////////////
// Test elements of signed_
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(signed_hierarchy)
{
  using nt2::functors::signed_;
  using nt2::meta::has_key;

  NT2_TEST( !(has_key<signed_, nt2::uint8_t >::value) );
  NT2_TEST( !(has_key<signed_, nt2::uint16_t>::value) );
  NT2_TEST( !(has_key<signed_, nt2::uint32_t>::value) );
  NT2_TEST( !(has_key<signed_, nt2::uint64_t>::value) );
  NT2_TEST(  (has_key<signed_, nt2::int8_t  >::value) );
  NT2_TEST(  (has_key<signed_, nt2::int16_t >::value) );
  NT2_TEST(  (has_key<signed_, nt2::int32_t >::value) );
  NT2_TEST(  (has_key<signed_, nt2::int64_t >::value) );
  NT2_TEST(  (has_key<signed_, float   >::value) );
  NT2_TEST(  (has_key<signed_, double  >::value) );
  NT2_TEST( !(has_key<signed_, bool    >::value) );
}

////////////////////////////////////////////////////////////////////////////////
// Test elements of unsigned_
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(unsigned_hierarchy)
{
  using nt2::functors::unsigned_;
  using nt2::meta::has_key;

  NT2_TEST(  (has_key<unsigned_, nt2::uint8_t >::value) );
  NT2_TEST(  (has_key<unsigned_, nt2::uint16_t>::value) );
  NT2_TEST(  (has_key<unsigned_, nt2::uint32_t>::value) );
  NT2_TEST(  (has_key<unsigned_, nt2::uint64_t>::value) );
  NT2_TEST( !(has_key<unsigned_, nt2::int8_t  >::value) );
  NT2_TEST( !(has_key<unsigned_, nt2::int16_t >::value) );
  NT2_TEST( !(has_key<unsigned_, nt2::int32_t >::value) );
  NT2_TEST( !(has_key<unsigned_, nt2::int64_t >::value) );
  NT2_TEST( !(has_key<unsigned_, float   >::value) );
  NT2_TEST( !(has_key<unsigned_, double  >::value) );
  NT2_TEST( !(has_key<unsigned_, bool    >::value) );
}

////////////////////////////////////////////////////////////////////////////////
// Test elements of integer_
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(integer_hierarchy)
{
  using nt2::functors::integer_;
  using nt2::meta::has_key;

  NT2_TEST(  (has_key<integer_, nt2::uint8_t >::value) );
  NT2_TEST(  (has_key<integer_, nt2::uint16_t>::value) );
  NT2_TEST(  (has_key<integer_, nt2::uint32_t>::value) );
  NT2_TEST(  (has_key<integer_, nt2::uint64_t>::value) );
  NT2_TEST(  (has_key<integer_, nt2::int8_t  >::value) );
  NT2_TEST(  (has_key<integer_, nt2::int16_t >::value) );
  NT2_TEST(  (has_key<integer_, nt2::int32_t >::value) );
  NT2_TEST(  (has_key<integer_, nt2::int64_t >::value) );
  NT2_TEST( !(has_key<integer_, float   >::value) );
  NT2_TEST( !(has_key<integer_, double  >::value) );
  NT2_TEST( !(has_key<integer_, bool    >::value) );
}

////////////////////////////////////////////////////////////////////////////////
// Test elements of arithmetic_
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(arithmetic_hierarchy)
{
  using nt2::functors::arithmetic_;
  using nt2::meta::has_key;

  NT2_TEST(  (has_key<arithmetic_, nt2::uint8_t >::value) );
  NT2_TEST(  (has_key<arithmetic_, nt2::uint16_t>::value) );
  NT2_TEST(  (has_key<arithmetic_, nt2::uint32_t>::value) );
  NT2_TEST(  (has_key<arithmetic_, nt2::uint64_t>::value) );
  NT2_TEST(  (has_key<arithmetic_, nt2::int8_t  >::value) );
  NT2_TEST(  (has_key<arithmetic_, nt2::int16_t >::value) );
  NT2_TEST(  (has_key<arithmetic_, nt2::int32_t >::value) );
  NT2_TEST(  (has_key<arithmetic_, nt2::int64_t >::value) );
  NT2_TEST(  (has_key<arithmetic_, float   >::value) );
  NT2_TEST(  (has_key<arithmetic_, double  >::value) );
  NT2_TEST( !(has_key<arithmetic_, bool    >::value) );
}

////////////////////////////////////////////////////////////////////////////////
// Test elements of fundamental_
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(fundamental_hierarchy)
{
  using nt2::functors::fundamental_;
  using nt2::meta::has_key;

  NT2_TEST( (has_key<fundamental_, nt2::uint8_t >::value) );
  NT2_TEST( (has_key<fundamental_, nt2::uint16_t>::value) );
  NT2_TEST( (has_key<fundamental_, nt2::uint32_t>::value) );
  NT2_TEST( (has_key<fundamental_, nt2::uint64_t>::value) );
  NT2_TEST( (has_key<fundamental_, nt2::int8_t  >::value) );
  NT2_TEST( (has_key<fundamental_, nt2::int16_t >::value) );
  NT2_TEST( (has_key<fundamental_, nt2::int32_t >::value) );
  NT2_TEST( (has_key<fundamental_, nt2::int64_t >::value) );
  NT2_TEST( (has_key<fundamental_, float   >::value) );
  NT2_TEST( (has_key<fundamental_, double  >::value) );
  NT2_TEST( (has_key<fundamental_, bool    >::value) );
}
