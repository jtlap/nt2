/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "boost::simd::constants real"

#include <boost/simd/include/constants/real.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

////////////////////////////////////////////////////////////////////////////////
// Test value of real constants for every base real types
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL  (  real_value, BOOST_SIMD_REAL_TYPES )
{
  NT2_TEST_EQUAL( boost::simd::Mhalf<T>()       , static_cast<T>(-1./2. ) );
  NT2_TEST_EQUAL( boost::simd::Mzero<T>()       , static_cast<T>(-0.    ) );
  NT2_TEST_EQUAL( boost::simd::Half<T>()        , static_cast<T>(1./2.  ) );
  NT2_TEST_EQUAL( boost::simd::Third<T>()       , static_cast<T>(1./3.  ) );
  NT2_TEST_EQUAL( boost::simd::Quarter<T>()     , static_cast<T>(1./4.  ) );
  NT2_TEST_EQUAL( boost::simd::Twotom10<T>()    , static_cast<T>(9.765625e-4) );
  NT2_TEST_EQUAL( boost::simd::Pi<T>()          , static_cast<T>(3.1415926535897930) );
  NT2_TEST_EQUAL( boost::simd::Sqrt_2o_2<T>()     , static_cast<T>(7.071067811865476e-1) );
  NT2_TEST_EQUAL( boost::simd::Gold<T>()        , static_cast<T>(1.6180339887498950) );
  NT2_TEST_EQUAL( boost::simd::Cgold<T>()       , static_cast<T>(3.8196601125010515e-1) );
}

NT2_TEST_CASE_TPL( real_value_int, BOOST_SIMD_INTEGRAL_TYPES )
{
  NT2_TEST_EQUAL( boost::simd::Mhalf<T>()       , static_cast<T>(0) );
  NT2_TEST_EQUAL( boost::simd::Mzero<T>()       , static_cast<T>(0) );
  NT2_TEST_EQUAL( boost::simd::Half<T>()        , static_cast<T>(0) );
  NT2_TEST_EQUAL( boost::simd::Third<T>()       , static_cast<T>(0) );
  NT2_TEST_EQUAL( boost::simd::Quarter<T>()     , static_cast<T>(0) );
  NT2_TEST_EQUAL( boost::simd::Twotom10<T>()    , static_cast<T>(0) );
  NT2_TEST_EQUAL( boost::simd::Pi<T>()          , static_cast<T>(3) );
  NT2_TEST_EQUAL( boost::simd::Sqrt_2<T>()      , static_cast<T>(1) );
  NT2_TEST_EQUAL( boost::simd::Sqrt_2o_2<T>()     , static_cast<T>(0) );
  NT2_TEST_EQUAL( boost::simd::Gold<T>()        , static_cast<T>(1) );
  NT2_TEST_EQUAL( boost::simd::Cgold<T>()       , static_cast<T>(0) );
}

////////////////////////////////////////////////////////////////////////////////
// Test type dependant values
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(type_dependant_real)
{
  NT2_TEST_EQUAL( boost::simd::Twotonmb<double>()    , 4503599627370496. );
  NT2_TEST_EQUAL( boost::simd::Splitfactor<double>(), 134217728.        );
  NT2_TEST_EQUAL( boost::simd::Twotonmb<float>()     , 8388608.f         );
  NT2_TEST_EQUAL( boost::simd::Splitfactor<float>() , 8192.f            );
}

NT2_TEST_CASE(type_dependant_const)
{
  NT2_TEST_EQUAL( (boost::simd::Const<double,0x3FF3BE76C8B43958LL>()), 1.234   );
  NT2_TEST_EQUAL( (boost::simd::Const<float,0x3F9DF3B6>())           , 1.234f );
}

////////////////////////////////////////////////////////////////////////////////
// Test real_constant for every base types
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL  (  real_constant, (double)(float) )
{
  NT2_TEST_EQUAL( (boost::simd::real_constant < T , 0x3FF3BE76C8B43958LL
                                          , 0x3F9DF3B6
                                      >()
                  )
                , static_cast<T>(1.234)
                );
}

NT2_TEST_CASE(double_constant)
{
  NT2_TEST_EQUAL((boost::simd::double_constant<double,0x3FF3BE76C8B43958LL>()), 1.234);
}

NT2_TEST_CASE(single_constant)
{
  NT2_TEST_EQUAL((boost::simd::single_constant<float,0x3F9DF3B6>()),1.234f);
}
