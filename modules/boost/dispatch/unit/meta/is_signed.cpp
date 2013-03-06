//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "boost::dispatch::meta::is_signed"

#include <boost/simd/sdk/config/types.hpp>
#include <boost/dispatch/meta/is_signed.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>

////////////////////////////////////////////////////////////////////////////////
// Test that is_signed is correct
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(is_signed)
{
  using boost::dispatch::meta::is_signed;
  using namespace boost::simd;

  NT2_TEST( is_signed<double>::value        );
  NT2_TEST( is_signed<float>::value         );
  NT2_TEST( !is_signed<boost::simd::uint64_t>::value);
  NT2_TEST( !is_signed<boost::simd::uint32_t>::value);
  NT2_TEST( !is_signed<boost::simd::uint16_t>::value);
  NT2_TEST( !is_signed<boost::simd::uint8_t>::value );
  NT2_TEST( is_signed<boost::simd::int64_t>::value  );
  NT2_TEST( is_signed<boost::simd::int32_t>::value  );
  NT2_TEST( is_signed<boost::simd::int16_t>::value  );
  NT2_TEST( is_signed<boost::simd::int8_t>::value   );
  NT2_TEST( !is_signed<bool>::value         );
}

NT2_TEST_CASE(is_unsigned)
{
  using boost::dispatch::meta::is_unsigned;
  using namespace boost::simd;

  NT2_TEST( !is_unsigned<double>::value        );
  NT2_TEST( !is_unsigned<float>::value         );
  NT2_TEST(  is_unsigned<boost::simd::uint64_t>::value );
  NT2_TEST(  is_unsigned<boost::simd::uint32_t>::value );
  NT2_TEST(  is_unsigned<boost::simd::uint16_t>::value );
  NT2_TEST(  is_unsigned<boost::simd::uint8_t>::value  );
  NT2_TEST( !is_unsigned<boost::simd::int64_t>::value  );
  NT2_TEST( !is_unsigned<boost::simd::int32_t>::value  );
  NT2_TEST( !is_unsigned<boost::simd::int16_t>::value  );
  NT2_TEST( !is_unsigned<boost::simd::int8_t>::value   );
  NT2_TEST(  is_unsigned<bool>::value          );
}
