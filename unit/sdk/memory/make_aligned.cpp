/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 0x01.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::memory::make_aligned"

#include <nt2/sdk/config/types.hpp>
#include <nt2/sdk/memory/is_aligned.hpp>
#include <nt2/sdk/memory/meta/make_aligned.hpp>

#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>

////////////////////////////////////////////////////////////////////////////////
// Test make_aligned on simple type
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(make_aligned)
{
  using nt2::memory::is_aligned;
  using nt2::meta::make_aligned;
  using namespace nt2;

  make_aligned<double>::type    ad;
  make_aligned<float>::type     af;
  make_aligned<uint64_t>::type  aui64;
  make_aligned<uint32_t>::type  aui32;
  make_aligned<uint16_t>::type  aui16;
  make_aligned<uint8_t>::type   aui8;
  make_aligned<int64_t>::type   ai64;
  make_aligned<int32_t>::type   ai32;
  make_aligned<int16_t>::type   ai16;
  make_aligned<int8_t>::type    ai8;
  make_aligned<bool>::type      ab;

  NT2_TEST( is_aligned(&ad) );
  NT2_TEST( is_aligned(&af) );
  NT2_TEST( is_aligned(&aui64) );
  NT2_TEST( is_aligned(&aui32) );
  NT2_TEST( is_aligned(&aui16) );
  NT2_TEST( is_aligned(&aui8) );
  NT2_TEST( is_aligned(&ai64) );
  NT2_TEST( is_aligned(&ai32) );
  NT2_TEST( is_aligned(&ai16) );
  NT2_TEST( is_aligned(&ai8) );
  NT2_TEST( is_aligned(&ab) );
}

////////////////////////////////////////////////////////////////////////////////
// Test make_aligned on array type
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(make_aligned_array)
{
  using nt2::memory::is_aligned;
  using nt2::meta::make_aligned;
  using namespace nt2;

  make_aligned<double[3]>::type    ad;
  make_aligned<float[3]>::type     af;
  make_aligned<uint64_t[3]>::type  aui64;
  make_aligned<uint32_t[3]>::type  aui32;
  make_aligned<uint16_t[3]>::type  aui16;
  make_aligned<uint8_t[3]>::type   aui8;
  make_aligned<int64_t[3]>::type   ai64;
  make_aligned<int32_t[3]>::type   ai32;
  make_aligned<int16_t[3]>::type   ai16;
  make_aligned<int8_t[3]>::type    ai8;
  make_aligned<bool[3]>::type      ab;

  NT2_TEST( is_aligned(&ad) );
  NT2_TEST( is_aligned(&af) );
  NT2_TEST( is_aligned(&aui64) );
  NT2_TEST( is_aligned(&aui32) );
  NT2_TEST( is_aligned(&aui16) );
  NT2_TEST( is_aligned(&aui8) );
  NT2_TEST( is_aligned(&ai64) );
  NT2_TEST( is_aligned(&ai32) );
  NT2_TEST( is_aligned(&ai16) );
  NT2_TEST( is_aligned(&ai8) );
  NT2_TEST( is_aligned(&ab) );
}
