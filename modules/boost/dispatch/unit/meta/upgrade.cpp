//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "boost::dispatch::meta::upgrade"

#include <boost/simd/sdk/config/types.hpp>
#include <boost/dispatch/meta/upgrade.hpp>
#include <boost/type_traits/is_same.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>

////////////////////////////////////////////////////////////////////////////////
// Test that upgrade is correct for middle-sized types
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(upgrade_ints)
{
  using boost::dispatch::meta::upgrade;
  using boost::is_same;

  NT2_TEST( (is_same<upgrade<double  			>::type,double 				>::value ));
  NT2_TEST( (is_same<upgrade<float   			>::type,double 				>::value ));
  NT2_TEST( (is_same<upgrade<boost::simd::int32_t >::type,boost::simd::int64_t 	>::value ));
  NT2_TEST( (is_same<upgrade<boost::simd::int16_t >::type,boost::simd::int32_t 	>::value ));
  NT2_TEST( (is_same<upgrade<boost::simd::int8_t 	>::type,boost::simd::int16_t 	>::value ));
  NT2_TEST( (is_same<upgrade<boost::simd::uint32_t>::type,boost::simd::uint64_t >::value ));
  NT2_TEST( (is_same<upgrade<boost::simd::uint16_t>::type,boost::simd::uint32_t >::value ));
  NT2_TEST( (is_same<upgrade<boost::simd::uint8_t	>::type,boost::simd::uint16_t	>::value ));
}

////////////////////////////////////////////////////////////////////////////////
// Test that upgrade is correct w/r to forced sign
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(upgrade_ints_forced_signed)
{
  using boost::dispatch::meta::upgrade;
  using boost::is_same;

  NT2_TEST( (is_same<upgrade<double  			,signed>::type,double				>::value ));
  NT2_TEST( (is_same<upgrade<float   			,signed>::type,double				>::value ));
  NT2_TEST( (is_same<upgrade<boost::simd::int32_t ,signed>::type,boost::simd::int64_t >::value ));
  NT2_TEST( (is_same<upgrade<boost::simd::int16_t ,signed>::type,boost::simd::int32_t >::value ));
  NT2_TEST( (is_same<upgrade<boost::simd::int8_t 	,signed>::type,boost::simd::int16_t	>::value ));
  NT2_TEST( (is_same<upgrade<boost::simd::uint32_t,signed>::type,boost::simd::int64_t >::value ));
  NT2_TEST( (is_same<upgrade<boost::simd::uint16_t,signed>::type,boost::simd::int32_t >::value ));
  NT2_TEST( (is_same<upgrade<boost::simd::uint8_t	,signed>::type,boost::simd::int16_t	>::value ));

  NT2_TEST( (is_same<upgrade<double  			,unsigned>::type,double				>::value ));
  NT2_TEST( (is_same<upgrade<float   			,unsigned>::type,double				>::value ));
  NT2_TEST( (is_same<upgrade<boost::simd::int32_t ,unsigned>::type,boost::simd::uint64_t>::value ));
  NT2_TEST( (is_same<upgrade<boost::simd::int16_t ,unsigned>::type,boost::simd::uint32_t>::value ));
  NT2_TEST( (is_same<upgrade<boost::simd::int8_t 	,unsigned>::type,boost::simd::uint16_t>::value ));
  NT2_TEST( (is_same<upgrade<boost::simd::uint32_t,unsigned>::type,boost::simd::uint64_t>::value ));
  NT2_TEST( (is_same<upgrade<boost::simd::uint16_t,unsigned>::type,boost::simd::uint32_t>::value ));
  NT2_TEST( (is_same<upgrade<boost::simd::uint8_t	,unsigned>::type,boost::simd::uint16_t>::value ));
}

////////////////////////////////////////////////////////////////////////////////
// Test that upgrade is correct w/r to tpye of sizeof == 8
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(upgrade_sizeof_8)
{
  using boost::dispatch::meta::upgrade;
  using boost::is_same;

  NT2_TEST( (is_same<upgrade<boost::simd::uint64_t					>::type,boost::simd::uint64_t>::value ));
  NT2_TEST( (is_same<upgrade<boost::simd::uint64_t					>::type,boost::simd::uint64_t>::value ));
  NT2_TEST( (is_same<upgrade<boost::simd::uint64_t,signed		>::type,boost::simd::int64_t>::value 	));
  NT2_TEST( (is_same<upgrade<boost::simd::uint64_t,signed		>::type,boost::simd::int64_t>::value 	));
  NT2_TEST( (is_same<upgrade<boost::simd::uint64_t,unsigned	>::type,boost::simd::uint64_t>::value ));
  NT2_TEST( (is_same<upgrade<boost::simd::uint64_t,unsigned	>::type,boost::simd::uint64_t>::value ));
}

