/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define BOOST_SIMD_UNIT_MODULE "boost::simd::meta::as_real"

#include <boost/simd/sdk/config/types.hpp>
#include <boost/simd/sdk/meta/as_real.hpp>
#include <boost/type_traits/is_same.hpp>

#include <boost/simd/sdk/unit/module.hpp>
#include <boost/simd/sdk/unit/tests/basic.hpp>

////////////////////////////////////////////////////////////////////////////////
// Test that as_real is correct w/r to original sign
////////////////////////////////////////////////////////////////////////////////
BOOST_SIMD_TEST_CASE(as_real)
{
  using boost::simd::meta::as_real;
  using boost::is_same;

  BOOST_SIMD_TEST( (is_same<as_real<double       >::type,double  >::value ));
  BOOST_SIMD_TEST( (is_same<as_real<float        >::type,float   >::value ));
  BOOST_SIMD_TEST( (is_same<as_real<boost::simd::int64_t >::type,double  >::value ));
  BOOST_SIMD_TEST( (is_same<as_real<boost::simd::int32_t >::type,float   >::value ));
  BOOST_SIMD_TEST( (is_same<as_real<boost::simd::uint64_t>::type,double  >::value ));
  BOOST_SIMD_TEST( (is_same<as_real<boost::simd::uint32_t>::type,float   >::value ));
}
