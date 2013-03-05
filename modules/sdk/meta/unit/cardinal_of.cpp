//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2::meta::cardinal_of"

#include <nt2/sdk/config/types.hpp>
#include <nt2/sdk/meta/cardinal_of.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

////////////////////////////////////////////////////////////////////////////////
// Test that cardinal_of scalars is 1
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(cardinal_of_scalar)
{
  using nt2::meta::cardinal_of;

  NT2_TEST_EQUAL( cardinal_of<double>::value        , 1u );
  NT2_TEST_EQUAL( cardinal_of<float>::value         , 1u );
  NT2_TEST_EQUAL( cardinal_of<nt2::uint64_t>::value , 1u );
  NT2_TEST_EQUAL( cardinal_of<nt2::uint32_t>::value , 1u );
  NT2_TEST_EQUAL( cardinal_of<nt2::uint16_t>::value , 1u );
  NT2_TEST_EQUAL( cardinal_of<nt2::uint8_t>::value  , 1u );
  NT2_TEST_EQUAL( cardinal_of<nt2::int64_t>::value  , 1u );
  NT2_TEST_EQUAL( cardinal_of<nt2::int32_t>::value  , 1u );
  NT2_TEST_EQUAL( cardinal_of<nt2::int16_t>::value  , 1u );
  NT2_TEST_EQUAL( cardinal_of<nt2::int8_t>::value   , 1u );
  NT2_TEST_EQUAL( cardinal_of<bool>::value          , 1u );
}
