/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define BOOST_SIMD_UNIT_MODULE "boost::simd::constants real"

#include <boost/simd/sdk/unit/module.hpp>
#include <boost/simd/include/constants/real.hpp>
#include <boost/simd/sdk/unit/tests/relation.hpp>

////////////////////////////////////////////////////////////////////////////////
// Test value of real constants for every base real types
////////////////////////////////////////////////////////////////////////////////
BOOST_SIMD_TEST_CASE_TPL  (  real_value, (double)(float) )
{
  BOOST_SIMD_TEST_EQUAL( boost::simd::Mhalf<T>()       , static_cast<T>(-1./2. ) );
  BOOST_SIMD_TEST_EQUAL( boost::simd::Mzero<T>()       , static_cast<T>(-0.    ) );
  BOOST_SIMD_TEST_EQUAL( boost::simd::Half<T>()        , static_cast<T>(1./2.  ) );
  BOOST_SIMD_TEST_EQUAL( boost::simd::Third<T>()       , static_cast<T>(1./3.  ) );
  BOOST_SIMD_TEST_EQUAL( boost::simd::Quarter<T>()     , static_cast<T>(1./4.  ) );
  BOOST_SIMD_TEST_EQUAL( boost::simd::Twotom10<T>()    , static_cast<T>(9.765625e-4) );
  BOOST_SIMD_TEST_EQUAL( boost::simd::Pi<T>()          , static_cast<T>(3.1415926535897930) );
  BOOST_SIMD_TEST_EQUAL( boost::simd::Sqrt_2o_2<T>()   , static_cast<T>(7.071067811865476e-1) );
  BOOST_SIMD_TEST_EQUAL( boost::simd::Gold<T>()        , static_cast<T>(1.6180339887498950) );
  BOOST_SIMD_TEST_EQUAL( boost::simd::Cgold<T>()       , static_cast<T>(3.8196601125010515e-1) );
}

////////////////////////////////////////////////////////////////////////////////
// Test type dependant values
////////////////////////////////////////////////////////////////////////////////
BOOST_SIMD_TEST_CASE(type_dependant_real)
{
  BOOST_SIMD_TEST_EQUAL( boost::simd::Two2nmb<double>()    , 4503599627370496. );
  BOOST_SIMD_TEST_EQUAL( boost::simd::Splitfactor<double>(), 134217728.        );
  BOOST_SIMD_TEST_EQUAL( boost::simd::Two2nmb<float>()     , 8388608.f         );
  BOOST_SIMD_TEST_EQUAL( boost::simd::Splitfactor<float>() , 8192.f            );
}

////////////////////////////////////////////////////////////////////////////////
// Test real_constant for every base types
////////////////////////////////////////////////////////////////////////////////
BOOST_SIMD_TEST_CASE_TPL  (  real_constant, (double)(float) )
{
  BOOST_SIMD_TEST_EQUAL( (boost::simd::real_constant < T , 0x3FF3BE76C8B43958LL
                                          , 0x3F9DF3B6
                                      >()
                  )
                , static_cast<T>(1.234)
                );
}

BOOST_SIMD_TEST_CASE(double_constant)
{
  BOOST_SIMD_TEST_EQUAL((boost::simd::double_constant<double,0x3FF3BE76C8B43958LL>()), 1.234);
}

BOOST_SIMD_TEST_CASE(single_constant)
{
  BOOST_SIMD_TEST_EQUAL((boost::simd::single_constant<float,0x3F9DF3B6>()),1.234f);
}
