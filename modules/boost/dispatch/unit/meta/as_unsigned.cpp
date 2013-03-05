//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "boost::dispatch::meta::as_unsigned"

#include <boost/simd/sdk/config/types.hpp>
#include <boost/dispatch/meta/as_unsigned.hpp>
#include <boost/type_traits/is_same.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>

////////////////////////////////////////////////////////////////////////////////
// Test that as_integer is correct w/r to original sign
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(as_unsigned)
{
  using boost::dispatch::meta::as_unsigned;
  using boost::is_same;

  NT2_TEST( (is_same<as_unsigned<double       >::type,double      >::value ));
  NT2_TEST( (is_same<as_unsigned<float        >::type,float       >::value ));
  NT2_TEST( (is_same<as_unsigned<boost::simd::int64_t >::type,boost::simd::uint64_t>::value ));
  NT2_TEST( (is_same<as_unsigned<boost::simd::int32_t >::type,boost::simd::uint32_t>::value ));
  NT2_TEST( (is_same<as_unsigned<boost::simd::int16_t >::type,boost::simd::uint16_t>::value ));
  NT2_TEST( (is_same<as_unsigned<boost::simd::int8_t  >::type,boost::simd::uint8_t >::value ));
  NT2_TEST( (is_same<as_unsigned<boost::simd::uint64_t>::type,boost::simd::uint64_t>::value ));
  NT2_TEST( (is_same<as_unsigned<boost::simd::uint32_t>::type,boost::simd::uint32_t>::value ));
  NT2_TEST( (is_same<as_unsigned<boost::simd::uint16_t>::type,boost::simd::uint16_t>::value ));
  NT2_TEST( (is_same<as_unsigned<boost::simd::uint8_t >::type,boost::simd::uint8_t >::value ));
  NT2_TEST( (is_same<as_unsigned<bool         >::type,bool         >::value ));
}
