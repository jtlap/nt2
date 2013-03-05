//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "boost::dispatch::meta::downgrade"

#include <boost/simd/sdk/config/types.hpp>
#include <boost/dispatch/meta/downgrade.hpp>
#include <boost/type_traits/is_same.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>

////////////////////////////////////////////////////////////////////////////////
// Test that downgrade is correct for middle-sized types
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(downgrad_ints)
{
  using boost::dispatch::meta::downgrade;
  using boost::is_same;

  NT2_TEST( (is_same<downgrade<double  			>::type,float 				>::value ));
  NT2_TEST( (is_same<downgrade<float   			>::type,float					>::value ));
  NT2_TEST( (is_same<downgrade<boost::simd::int64_t >::type,boost::simd::int32_t 	>::value ));
  NT2_TEST( (is_same<downgrade<boost::simd::int32_t >::type,boost::simd::int16_t 	>::value ));
  NT2_TEST( (is_same<downgrade<boost::simd::int16_t >::type,boost::simd::int8_t 	>::value ));
  NT2_TEST( (is_same<downgrade<boost::simd::uint64_t>::type,boost::simd::uint32_t >::value ));
  NT2_TEST( (is_same<downgrade<boost::simd::uint32_t>::type,boost::simd::uint16_t >::value ));
  NT2_TEST( (is_same<downgrade<boost::simd::uint16_t>::type,boost::simd::uint8_t  >::value ));
}

////////////////////////////////////////////////////////////////////////////////
// Test that downgrade is correct w/r to forced sign
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(downgrade_ints_forced_signed)
{
  using boost::dispatch::meta::downgrade;
  using boost::is_same;

	NT2_TEST( (is_same<downgrade<double  			,	unsigned>::type,float 				>::value ));
  NT2_TEST( (is_same<downgrade<float   			,	unsigned>::type,float 				>::value ));
  NT2_TEST( (is_same<downgrade<boost::simd::int64_t ,	unsigned>::type,boost::simd::uint32_t >::value ));
  NT2_TEST( (is_same<downgrade<boost::simd::int32_t ,	unsigned>::type,boost::simd::uint16_t >::value ));
  NT2_TEST( (is_same<downgrade<boost::simd::int16_t ,	unsigned>::type,boost::simd::uint8_t 	>::value ));
  NT2_TEST( (is_same<downgrade<boost::simd::uint64_t,	unsigned>::type,boost::simd::uint32_t >::value ));
  NT2_TEST( (is_same<downgrade<boost::simd::uint32_t,	unsigned>::type,boost::simd::uint16_t >::value ));
  NT2_TEST( (is_same<downgrade<boost::simd::uint16_t,	unsigned>::type,boost::simd::uint8_t  >::value ));

	NT2_TEST( (is_same<downgrade<double  			,	signed>::type,float 				>::value ));
  NT2_TEST( (is_same<downgrade<float   			,	signed>::type,float					>::value ));
  NT2_TEST( (is_same<downgrade<boost::simd::int64_t ,	signed>::type,boost::simd::int32_t 	>::value ));
  NT2_TEST( (is_same<downgrade<boost::simd::int32_t ,	signed>::type,boost::simd::int16_t 	>::value ));
  NT2_TEST( (is_same<downgrade<boost::simd::int16_t ,	signed>::type,boost::simd::int8_t 	>::value ));
  NT2_TEST( (is_same<downgrade<boost::simd::uint64_t,	signed>::type,boost::simd::int32_t 	>::value ));
  NT2_TEST( (is_same<downgrade<boost::simd::uint32_t,	signed>::type,boost::simd::int16_t 	>::value ));
  NT2_TEST( (is_same<downgrade<boost::simd::uint16_t,	signed>::type,boost::simd::int8_t  	>::value ));
}

////////////////////////////////////////////////////////////////////////////////
// Test that downgrade is correct w/r to tpye of sizeof == 1
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(downgrade_sizeof_1)
{
  using boost::dispatch::meta::downgrade;
  using boost::is_same;

  NT2_TEST( (is_same<downgrade<boost::simd::int8_t	>::type,boost::simd::int8_t >::value ));
  NT2_TEST( (is_same<downgrade<boost::simd::uint8_t >::type,boost::simd::uint8_t>::value ));
  NT2_TEST( (is_same<downgrade<boost::simd::int8_t	,unsigned	>::type,boost::simd::uint8_t >::value ));
  NT2_TEST( (is_same<downgrade<boost::simd::uint8_t ,unsigned	>::type,boost::simd::uint8_t>::value 	));
  NT2_TEST( (is_same<downgrade<boost::simd::int8_t	,signed		>::type,boost::simd::int8_t >::value 	));
  NT2_TEST( (is_same<downgrade<boost::simd::uint8_t ,signed		>::type,boost::simd::int8_t>::value 	));
}

