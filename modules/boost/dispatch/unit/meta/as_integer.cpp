//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "boost::dispatch::meta::as_integer"

#include <boost/simd/sdk/config/types.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/type_traits/is_same.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>

////////////////////////////////////////////////////////////////////////////////
// Test that as_integer is correct w/r to original sign
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(as_integer_native_sign)
{
  using boost::dispatch::meta::as_integer;
  using boost::is_same;

  NT2_TEST( (is_same<as_integer<double  >::type,boost::simd::int64_t >::value ));
  NT2_TEST( (is_same<as_integer<float   >::type,boost::simd::int32_t >::value ));
  NT2_TEST( (is_same<as_integer<boost::simd::int64_t >::type,boost::simd::int64_t >::value ));
  NT2_TEST( (is_same<as_integer<boost::simd::int32_t >::type,boost::simd::int32_t >::value ));
  NT2_TEST( (is_same<as_integer<boost::simd::int16_t >::type,boost::simd::int16_t >::value ));
  NT2_TEST( (is_same<as_integer<boost::simd::int8_t  >::type,boost::simd::int8_t  >::value ));
  NT2_TEST( (is_same<as_integer<boost::simd::uint64_t>::type,boost::simd::uint64_t>::value ));
  NT2_TEST( (is_same<as_integer<boost::simd::uint32_t>::type,boost::simd::uint32_t>::value ));
  NT2_TEST( (is_same<as_integer<boost::simd::uint16_t>::type,boost::simd::uint16_t>::value ));
  NT2_TEST( (is_same<as_integer<boost::simd::uint8_t >::type,boost::simd::uint8_t >::value ));
  NT2_TEST( (is_same<as_integer<bool    >::type,boost::simd::uint8_t >::value ));
}

////////////////////////////////////////////////////////////////////////////////
// Test that as_integer is correct w/r to forced sign
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(as_integer_native_forced_signed)
{
  using boost::dispatch::meta::as_integer;
  using boost::is_same;
  using namespace boost::simd;

  NT2_TEST( (is_same<as_integer<double  ,unsigned>::type,boost::simd::uint64_t >::value ));
  NT2_TEST( (is_same<as_integer<float   ,unsigned>::type,boost::simd::uint32_t >::value ));
  NT2_TEST( (is_same<as_integer<boost::simd::int64_t ,unsigned>::type,boost::simd::uint64_t >::value ));
  NT2_TEST( (is_same<as_integer<boost::simd::int32_t ,unsigned>::type,boost::simd::uint32_t >::value ));
  NT2_TEST( (is_same<as_integer<boost::simd::int16_t ,unsigned>::type,boost::simd::uint16_t >::value ));
  NT2_TEST( (is_same<as_integer<boost::simd::int8_t  ,unsigned>::type,boost::simd::uint8_t  >::value ));
  NT2_TEST( (is_same<as_integer<boost::simd::uint64_t,unsigned>::type,boost::simd::uint64_t >::value ));
  NT2_TEST( (is_same<as_integer<boost::simd::uint32_t,unsigned>::type,boost::simd::uint32_t >::value ));
  NT2_TEST( (is_same<as_integer<boost::simd::uint16_t,unsigned>::type,boost::simd::uint16_t >::value ));
  NT2_TEST( (is_same<as_integer<boost::simd::uint8_t ,unsigned>::type,boost::simd::uint8_t  >::value ));
  NT2_TEST( (is_same<as_integer<bool    ,unsigned>::type,boost::simd::uint8_t >::value ));
}

////////////////////////////////////////////////////////////////////////////////
// Test that as_integer is correct w/r to forced sign
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(as_integer_native_forced_unsigned)
{
  using boost::dispatch::meta::as_integer;
  using boost::is_same;
  using namespace boost::simd;

  NT2_TEST( (is_same<as_integer<double  ,signed>::type,boost::simd::int64_t>::value ));
  NT2_TEST( (is_same<as_integer<float   ,signed>::type,boost::simd::int32_t>::value ));
  NT2_TEST( (is_same<as_integer<boost::simd::int64_t ,signed>::type,boost::simd::int64_t>::value ));
  NT2_TEST( (is_same<as_integer<boost::simd::int32_t ,signed>::type,boost::simd::int32_t>::value ));
  NT2_TEST( (is_same<as_integer<boost::simd::int16_t ,signed>::type,boost::simd::int16_t>::value ));
  NT2_TEST( (is_same<as_integer<boost::simd::int8_t  ,signed>::type,boost::simd::int8_t >::value ));
  NT2_TEST( (is_same<as_integer<boost::simd::uint64_t,signed>::type,boost::simd::int64_t>::value ));
  NT2_TEST( (is_same<as_integer<boost::simd::uint32_t,signed>::type,boost::simd::int32_t>::value ));
  NT2_TEST( (is_same<as_integer<boost::simd::uint16_t,signed>::type,boost::simd::int16_t>::value ));
  NT2_TEST( (is_same<as_integer<boost::simd::uint8_t ,signed>::type,boost::simd::int8_t >::value ));
  NT2_TEST( (is_same<as_integer<bool    ,signed>::type,boost::simd::int8_t >::value ));
}
