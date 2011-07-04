/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::meta::upgrade"

#include <nt2/sdk/config/types.hpp>
#include <nt2/sdk/meta/upgrade.hpp>
#include <boost/type_traits/is_same.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>

////////////////////////////////////////////////////////////////////////////////
// Test that upgrade is correct for middle-sized types
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(upgrade_ints)
{
  using nt2::meta::upgrade;
  using boost::is_same;

  NT2_TEST( (is_same<upgrade<double  			>::type,double 				>::value ));
  NT2_TEST( (is_same<upgrade<float   			>::type,double 				>::value ));
  NT2_TEST( (is_same<upgrade<nt2::int32_t >::type,nt2::int64_t 	>::value ));
  NT2_TEST( (is_same<upgrade<nt2::int16_t >::type,nt2::int32_t 	>::value ));
  NT2_TEST( (is_same<upgrade<nt2::int8_t 	>::type,nt2::int16_t 	>::value ));
  NT2_TEST( (is_same<upgrade<nt2::uint32_t>::type,nt2::uint64_t >::value ));
  NT2_TEST( (is_same<upgrade<nt2::uint16_t>::type,nt2::uint32_t >::value ));
  NT2_TEST( (is_same<upgrade<nt2::uint8_t	>::type,nt2::uint16_t	>::value ));
}

////////////////////////////////////////////////////////////////////////////////
// Test that upgrade is correct w/r to forced sign
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(upgrade_ints_forced_signed)
{
  using nt2::meta::upgrade;
  using boost::is_same;

  NT2_TEST( (is_same<upgrade<double  			,signed>::type,double				>::value ));
  NT2_TEST( (is_same<upgrade<float   			,signed>::type,double				>::value ));
  NT2_TEST( (is_same<upgrade<nt2::int32_t ,signed>::type,nt2::int64_t >::value ));
  NT2_TEST( (is_same<upgrade<nt2::int16_t ,signed>::type,nt2::int32_t >::value ));
  NT2_TEST( (is_same<upgrade<nt2::int8_t 	,signed>::type,nt2::int16_t	>::value ));
  NT2_TEST( (is_same<upgrade<nt2::uint32_t,signed>::type,nt2::int64_t >::value ));
  NT2_TEST( (is_same<upgrade<nt2::uint16_t,signed>::type,nt2::int32_t >::value ));
  NT2_TEST( (is_same<upgrade<nt2::uint8_t	,signed>::type,nt2::int16_t	>::value ));

  NT2_TEST( (is_same<upgrade<double  			,unsigned>::type,double				>::value ));
  NT2_TEST( (is_same<upgrade<float   			,unsigned>::type,double				>::value ));
  NT2_TEST( (is_same<upgrade<nt2::int32_t ,unsigned>::type,nt2::uint64_t>::value ));
  NT2_TEST( (is_same<upgrade<nt2::int16_t ,unsigned>::type,nt2::uint32_t>::value ));
  NT2_TEST( (is_same<upgrade<nt2::int8_t 	,unsigned>::type,nt2::uint16_t>::value ));
  NT2_TEST( (is_same<upgrade<nt2::uint32_t,unsigned>::type,nt2::uint64_t>::value ));
  NT2_TEST( (is_same<upgrade<nt2::uint16_t,unsigned>::type,nt2::uint32_t>::value ));
  NT2_TEST( (is_same<upgrade<nt2::uint8_t	,unsigned>::type,nt2::uint16_t>::value ));
}

////////////////////////////////////////////////////////////////////////////////
// Test that upgrade is correct w/r to tpye of sizeof == 8
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(upgrade_sizeof_8)
{
  using nt2::meta::upgrade;
  using boost::is_same;

  NT2_TEST( (is_same<upgrade<nt2::uint64_t					>::type,nt2::uint64_t>::value ));
  NT2_TEST( (is_same<upgrade<nt2::uint64_t					>::type,nt2::uint64_t>::value ));
  NT2_TEST( (is_same<upgrade<nt2::uint64_t,signed		>::type,nt2::int64_t>::value 	));
  NT2_TEST( (is_same<upgrade<nt2::uint64_t,signed		>::type,nt2::int64_t>::value 	));
  NT2_TEST( (is_same<upgrade<nt2::uint64_t,unsigned	>::type,nt2::uint64_t>::value ));
  NT2_TEST( (is_same<upgrade<nt2::uint64_t,unsigned	>::type,nt2::uint64_t>::value ));
}

