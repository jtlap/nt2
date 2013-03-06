//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2::meta::downgrade"

#include <nt2/sdk/config/types.hpp>
#include <nt2/sdk/meta/downgrade.hpp>
#include <boost/type_traits/is_same.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>

////////////////////////////////////////////////////////////////////////////////
// Test that downgrade is correct for middle-sized types
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(downgrad_ints)
{
  using nt2::meta::downgrade;
  using boost::is_same;

  NT2_TEST( (is_same<downgrade<double  			>::type,float 				>::value ));
  NT2_TEST( (is_same<downgrade<float   			>::type,float					>::value ));
  NT2_TEST( (is_same<downgrade<nt2::int64_t >::type,nt2::int32_t 	>::value ));
  NT2_TEST( (is_same<downgrade<nt2::int32_t >::type,nt2::int16_t 	>::value ));
  NT2_TEST( (is_same<downgrade<nt2::int16_t >::type,nt2::int8_t 	>::value ));
  NT2_TEST( (is_same<downgrade<nt2::uint64_t>::type,nt2::uint32_t >::value ));
  NT2_TEST( (is_same<downgrade<nt2::uint32_t>::type,nt2::uint16_t >::value ));
  NT2_TEST( (is_same<downgrade<nt2::uint16_t>::type,nt2::uint8_t  >::value ));
}

////////////////////////////////////////////////////////////////////////////////
// Test that downgrade is correct w/r to forced sign
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(downgrade_ints_forced_signed)
{
  using nt2::meta::downgrade;
  using boost::is_same;

	NT2_TEST( (is_same<downgrade<double  			,	unsigned>::type,float 				>::value ));
  NT2_TEST( (is_same<downgrade<float   			,	unsigned>::type,float 				>::value ));
  NT2_TEST( (is_same<downgrade<nt2::int64_t ,	unsigned>::type,nt2::uint32_t >::value ));
  NT2_TEST( (is_same<downgrade<nt2::int32_t ,	unsigned>::type,nt2::uint16_t >::value ));
  NT2_TEST( (is_same<downgrade<nt2::int16_t ,	unsigned>::type,nt2::uint8_t 	>::value ));
  NT2_TEST( (is_same<downgrade<nt2::uint64_t,	unsigned>::type,nt2::uint32_t >::value ));
  NT2_TEST( (is_same<downgrade<nt2::uint32_t,	unsigned>::type,nt2::uint16_t >::value ));
  NT2_TEST( (is_same<downgrade<nt2::uint16_t,	unsigned>::type,nt2::uint8_t  >::value ));

	NT2_TEST( (is_same<downgrade<double  			,	signed>::type,float 				>::value ));
  NT2_TEST( (is_same<downgrade<float   			,	signed>::type,float					>::value ));
  NT2_TEST( (is_same<downgrade<nt2::int64_t ,	signed>::type,nt2::int32_t 	>::value ));
  NT2_TEST( (is_same<downgrade<nt2::int32_t ,	signed>::type,nt2::int16_t 	>::value ));
  NT2_TEST( (is_same<downgrade<nt2::int16_t ,	signed>::type,nt2::int8_t 	>::value ));
  NT2_TEST( (is_same<downgrade<nt2::uint64_t,	signed>::type,nt2::int32_t 	>::value ));
  NT2_TEST( (is_same<downgrade<nt2::uint32_t,	signed>::type,nt2::int16_t 	>::value ));
  NT2_TEST( (is_same<downgrade<nt2::uint16_t,	signed>::type,nt2::int8_t  	>::value ));
}

////////////////////////////////////////////////////////////////////////////////
// Test that downgrade is correct w/r to tpye of sizeof == 1
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(downgrade_sizeof_1)
{
  using nt2::meta::downgrade;
  using boost::is_same;

  NT2_TEST( (is_same<downgrade<nt2::int8_t	>::type,nt2::int8_t >::value ));
  NT2_TEST( (is_same<downgrade<nt2::uint8_t >::type,nt2::uint8_t>::value ));
  NT2_TEST( (is_same<downgrade<nt2::int8_t	,unsigned	>::type,nt2::uint8_t >::value ));
  NT2_TEST( (is_same<downgrade<nt2::uint8_t ,unsigned	>::type,nt2::uint8_t>::value 	));
  NT2_TEST( (is_same<downgrade<nt2::int8_t	,signed		>::type,nt2::int8_t >::value 	));
  NT2_TEST( (is_same<downgrade<nt2::uint8_t ,signed		>::type,nt2::int8_t>::value 	));
}

