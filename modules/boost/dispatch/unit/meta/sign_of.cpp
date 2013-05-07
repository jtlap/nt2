//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "boost::dispatch::meta::sign_of"

#include <boost/dispatch/meta/sign_of.hpp>
#include <boost/simd/sdk/config/types.hpp>
#include <boost/type_traits/is_same.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>

////////////////////////////////////////////////////////////////////////////////
// Test that sign_of is correct
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(sign_of)
{
  using boost::dispatch::meta::sign_of;
  using boost::is_same;

  NT2_TEST( (is_same<sign_of<double       >::type,signed  >::value ));
  NT2_TEST( (is_same<sign_of<float        >::type,signed  >::value ));
  NT2_TEST( (is_same<sign_of<boost::simd::int64_t >::type,signed  >::value ));
  NT2_TEST( (is_same<sign_of<boost::simd::int32_t >::type,signed  >::value ));
  NT2_TEST( (is_same<sign_of<boost::simd::int16_t >::type,signed  >::value ));
  NT2_TEST( (is_same<sign_of<boost::simd::int8_t  >::type,signed  >::value ));
  NT2_TEST( (is_same<sign_of<boost::simd::uint64_t>::type,unsigned>::value ));
  NT2_TEST( (is_same<sign_of<boost::simd::uint32_t>::type,unsigned>::value ));
  NT2_TEST( (is_same<sign_of<boost::simd::uint16_t>::type,unsigned>::value ));
  NT2_TEST( (is_same<sign_of<boost::simd::uint8_t >::type,unsigned>::value ));
  NT2_TEST( (is_same<sign_of<bool         >::type,unsigned>::value ));
}
