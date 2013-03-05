//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "boost::dispatch::meta::scalar_of.cpp"

#include <boost/type_traits/is_same.hpp>
#include <boost/dispatch/meta/scalar_of.hpp>
#include <boost/simd/sdk/config/types.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>

////////////////////////////////////////////////////////////////////////////////
// Test that scalar_of on scalar is idempotent
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(scalar_of_scalar)
{
  using boost::dispatch::meta::scalar_of;
  using boost::is_same;

  NT2_TEST( (is_same<scalar_of<double>::type        , double        >::value) );
  NT2_TEST( (is_same<scalar_of<float>::type         , float         >::value) );
  NT2_TEST( (is_same<scalar_of<boost::simd::uint64_t>::type , boost::simd::uint64_t >::value) );
  NT2_TEST( (is_same<scalar_of<boost::simd::uint32_t>::type , boost::simd::uint32_t >::value) );
  NT2_TEST( (is_same<scalar_of<boost::simd::uint16_t>::type , boost::simd::uint16_t >::value) );
  NT2_TEST( (is_same<scalar_of<boost::simd::uint8_t>::type  , boost::simd::uint8_t  >::value) );
  NT2_TEST( (is_same<scalar_of<boost::simd::int64_t>::type  , boost::simd::int64_t  >::value) );
  NT2_TEST( (is_same<scalar_of<boost::simd::int32_t>::type  , boost::simd::int32_t  >::value) );
  NT2_TEST( (is_same<scalar_of<boost::simd::int16_t>::type  , boost::simd::int16_t  >::value) );
  NT2_TEST( (is_same<scalar_of<boost::simd::int8_t>::type   , boost::simd::int8_t   >::value) );
}
