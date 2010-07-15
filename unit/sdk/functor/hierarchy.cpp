/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::functors::hierarchy"

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

  NT2_TEST( !(has_key<empty_, uint8_t >::value) );
  NT2_TEST( !(has_key<empty_, uint16_t>::value) );
  NT2_TEST( !(has_key<empty_, uint32_t>::value) );
  NT2_TEST( !(has_key<empty_, uint64_t>::value) );
  NT2_TEST( !(has_key<empty_, int8_t  >::value) );
  NT2_TEST( !(has_key<empty_, int16_t >::value) );
  NT2_TEST( !(has_key<empty_, int32_t >::value) );
  NT2_TEST( !(has_key<empty_, int64_t >::value) );
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

  NT2_TEST( !(has_key<bool_, uint8_t >::value) );
  NT2_TEST( !(has_key<bool_, uint16_t>::value) );
  NT2_TEST( !(has_key<bool_, uint32_t>::value) );
  NT2_TEST( !(has_key<bool_, uint64_t>::value) );
  NT2_TEST( !(has_key<bool_, int8_t  >::value) );
  NT2_TEST( !(has_key<bool_, int16_t >::value) );
  NT2_TEST( !(has_key<bool_, int32_t >::value) );
  NT2_TEST( !(has_key<bool_, int64_t >::value) );
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

  NT2_TEST(  (has_key<int8_, uint8_t >::value) );
  NT2_TEST( !(has_key<int8_, uint16_t>::value) );
  NT2_TEST( !(has_key<int8_, uint32_t>::value) );
  NT2_TEST( !(has_key<int8_, uint64_t>::value) );
  NT2_TEST(  (has_key<int8_, int8_t  >::value) );
  NT2_TEST( !(has_key<int8_, int16_t >::value) );
  NT2_TEST( !(has_key<int8_, int32_t >::value) );
  NT2_TEST( !(has_key<int8_, int64_t >::value) );
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

  NT2_TEST( !(has_key<int16_, uint8_t >::value) );
  NT2_TEST(  (has_key<int16_, uint16_t>::value) );
  NT2_TEST( !(has_key<int16_, uint32_t>::value) );
  NT2_TEST( !(has_key<int16_, uint64_t>::value) );
  NT2_TEST( !(has_key<int16_, int8_t  >::value) );
  NT2_TEST(  (has_key<int16_, int16_t >::value) );
  NT2_TEST( !(has_key<int16_, int32_t >::value) );
  NT2_TEST( !(has_key<int16_, int64_t >::value) );
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

  NT2_TEST( !(has_key<int32_, uint8_t >::value) );
  NT2_TEST( !(has_key<int32_, uint16_t>::value) );
  NT2_TEST(  (has_key<int32_, uint32_t>::value) );
  NT2_TEST( !(has_key<int32_, uint64_t>::value) );
  NT2_TEST( !(has_key<int32_, int8_t  >::value) );
  NT2_TEST( !(has_key<int32_, int16_t >::value) );
  NT2_TEST(  (has_key<int32_, int32_t >::value) );
  NT2_TEST( !(has_key<int32_, int64_t >::value) );
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

  NT2_TEST( !(has_key<int64_, uint8_t >::value) );
  NT2_TEST( !(has_key<int64_, uint16_t>::value) );
  NT2_TEST( !(has_key<int64_, uint32_t>::value) );
  NT2_TEST(  (has_key<int64_, uint64_t>::value) );
  NT2_TEST( !(has_key<int64_, int8_t  >::value) );
  NT2_TEST( !(has_key<int64_, int16_t >::value) );
  NT2_TEST( !(has_key<int64_, int32_t >::value) );
  NT2_TEST(  (has_key<int64_, int64_t >::value) );
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

  NT2_TEST(  (has_key<types8_, uint8_t >::value) );
  NT2_TEST( !(has_key<types8_, uint16_t>::value) );
  NT2_TEST( !(has_key<types8_, uint32_t>::value) );
  NT2_TEST( !(has_key<types8_, uint64_t>::value) );
  NT2_TEST(  (has_key<types8_, int8_t  >::value) );
  NT2_TEST( !(has_key<types8_, int16_t >::value) );
  NT2_TEST( !(has_key<types8_, int32_t >::value) );
  NT2_TEST( !(has_key<types8_, int64_t >::value) );
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

  NT2_TEST( !(has_key<types16_, uint8_t >::value) );
  NT2_TEST(  (has_key<types16_, uint16_t>::value) );
  NT2_TEST( !(has_key<types16_, uint32_t>::value) );
  NT2_TEST( !(has_key<types16_, uint64_t>::value) );
  NT2_TEST( !(has_key<types16_, int8_t  >::value) );
  NT2_TEST(  (has_key<types16_, int16_t >::value) );
  NT2_TEST( !(has_key<types16_, int32_t >::value) );
  NT2_TEST( !(has_key<types16_, int64_t >::value) );
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

  NT2_TEST( !(has_key<types32_, uint8_t >::value) );
  NT2_TEST( !(has_key<types32_, uint16_t>::value) );
  NT2_TEST(  (has_key<types32_, uint32_t>::value) );
  NT2_TEST( !(has_key<types32_, uint64_t>::value) );
  NT2_TEST( !(has_key<types32_, int8_t  >::value) );
  NT2_TEST( !(has_key<types32_, int16_t >::value) );
  NT2_TEST(  (has_key<types32_, int32_t >::value) );
  NT2_TEST( !(has_key<types32_, int64_t >::value) );
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

  NT2_TEST( !(has_key<types64_, uint8_t >::value) );
  NT2_TEST( !(has_key<types64_, uint16_t>::value) );
  NT2_TEST( !(has_key<types64_, uint32_t>::value) );
  NT2_TEST(  (has_key<types64_, uint64_t>::value) );
  NT2_TEST( !(has_key<types64_, int8_t  >::value) );
  NT2_TEST( !(has_key<types64_, int16_t >::value) );
  NT2_TEST( !(has_key<types64_, int32_t >::value) );
  NT2_TEST(  (has_key<types64_, int64_t >::value) );
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

  NT2_TEST(  (has_key<uint_, uint8_t >::value) );
  NT2_TEST(  (has_key<uint_, uint16_t>::value) );
  NT2_TEST(  (has_key<uint_, uint32_t>::value) );
  NT2_TEST(  (has_key<uint_, uint64_t>::value) );
  NT2_TEST( !(has_key<uint_, int8_t  >::value) );
  NT2_TEST( !(has_key<uint_, int16_t >::value) );
  NT2_TEST( !(has_key<uint_, int32_t >::value) );
  NT2_TEST( !(has_key<uint_, int64_t >::value) );
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

  NT2_TEST( !(has_key<int_, uint8_t >::value) );
  NT2_TEST( !(has_key<int_, uint16_t>::value) );
  NT2_TEST( !(has_key<int_, uint32_t>::value) );
  NT2_TEST( !(has_key<int_, uint64_t>::value) );
  NT2_TEST(  (has_key<int_, int8_t  >::value) );
  NT2_TEST(  (has_key<int_, int16_t >::value) );
  NT2_TEST(  (has_key<int_, int32_t >::value) );
  NT2_TEST(  (has_key<int_, int64_t >::value) );
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

  NT2_TEST( !(has_key<real_, uint8_t >::value) );
  NT2_TEST( !(has_key<real_, uint16_t>::value) );
  NT2_TEST( !(has_key<real_, uint32_t>::value) );
  NT2_TEST( !(has_key<real_, uint64_t>::value) );
  NT2_TEST( !(has_key<real_, int8_t  >::value) );
  NT2_TEST( !(has_key<real_, int16_t >::value) );
  NT2_TEST( !(has_key<real_, int32_t >::value) );
  NT2_TEST( !(has_key<real_, int64_t >::value) );
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

  NT2_TEST( !(has_key<signed_, uint8_t >::value) );
  NT2_TEST( !(has_key<signed_, uint16_t>::value) );
  NT2_TEST( !(has_key<signed_, uint32_t>::value) );
  NT2_TEST( !(has_key<signed_, uint64_t>::value) );
  NT2_TEST(  (has_key<signed_, int8_t  >::value) );
  NT2_TEST(  (has_key<signed_, int16_t >::value) );
  NT2_TEST(  (has_key<signed_, int32_t >::value) );
  NT2_TEST(  (has_key<signed_, int64_t >::value) );
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

  NT2_TEST(  (has_key<unsigned_, uint8_t >::value) );
  NT2_TEST(  (has_key<unsigned_, uint16_t>::value) );
  NT2_TEST(  (has_key<unsigned_, uint32_t>::value) );
  NT2_TEST(  (has_key<unsigned_, uint64_t>::value) );
  NT2_TEST( !(has_key<unsigned_, int8_t  >::value) );
  NT2_TEST( !(has_key<unsigned_, int16_t >::value) );
  NT2_TEST( !(has_key<unsigned_, int32_t >::value) );
  NT2_TEST( !(has_key<unsigned_, int64_t >::value) );
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

  NT2_TEST(  (has_key<integer_, uint8_t >::value) );
  NT2_TEST(  (has_key<integer_, uint16_t>::value) );
  NT2_TEST(  (has_key<integer_, uint32_t>::value) );
  NT2_TEST(  (has_key<integer_, uint64_t>::value) );
  NT2_TEST(  (has_key<integer_, int8_t  >::value) );
  NT2_TEST(  (has_key<integer_, int16_t >::value) );
  NT2_TEST(  (has_key<integer_, int32_t >::value) );
  NT2_TEST(  (has_key<integer_, int64_t >::value) );
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

  NT2_TEST(  (has_key<arithmetic_, uint8_t >::value) );
  NT2_TEST(  (has_key<arithmetic_, uint16_t>::value) );
  NT2_TEST(  (has_key<arithmetic_, uint32_t>::value) );
  NT2_TEST(  (has_key<arithmetic_, uint64_t>::value) );
  NT2_TEST(  (has_key<arithmetic_, int8_t  >::value) );
  NT2_TEST(  (has_key<arithmetic_, int16_t >::value) );
  NT2_TEST(  (has_key<arithmetic_, int32_t >::value) );
  NT2_TEST(  (has_key<arithmetic_, int64_t >::value) );
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

  NT2_TEST( (has_key<fundamental_, uint8_t >::value) );
  NT2_TEST( (has_key<fundamental_, uint16_t>::value) );
  NT2_TEST( (has_key<fundamental_, uint32_t>::value) );
  NT2_TEST( (has_key<fundamental_, uint64_t>::value) );
  NT2_TEST( (has_key<fundamental_, int8_t  >::value) );
  NT2_TEST( (has_key<fundamental_, int16_t >::value) );
  NT2_TEST( (has_key<fundamental_, int32_t >::value) );
  NT2_TEST( (has_key<fundamental_, int64_t >::value) );
  NT2_TEST( (has_key<fundamental_, float   >::value) );
  NT2_TEST( (has_key<fundamental_, double  >::value) );
  NT2_TEST( (has_key<fundamental_, bool    >::value) );
}
