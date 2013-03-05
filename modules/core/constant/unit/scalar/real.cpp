//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2::constants real"

#include <nt2/include/constants/real.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

////////////////////////////////////////////////////////////////////////////////
// Test value of real constants for every base real types
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL  (  real_value, (double)(float) )
{
  NT2_TEST_EQUAL( nt2::Mhalf<T>()       , static_cast<T>(-1./2. ) );
  NT2_TEST_EQUAL( nt2::Mzero<T>()       , static_cast<T>(-0.    ) );
  NT2_TEST_EQUAL( nt2::Half<T>()        , static_cast<T>(1./2.  ) );
  NT2_TEST_EQUAL( nt2::Third<T>()       , static_cast<T>(1./3.  ) );
  NT2_TEST_EQUAL( nt2::Quarter<T>()     , static_cast<T>(1./4.  ) );
  NT2_TEST_EQUAL( nt2::Twotom10<T>()    , static_cast<T>(9.765625e-4) );
  NT2_TEST_EQUAL( nt2::Pi<T>()          , static_cast<T>(3.1415926535897930) );
  NT2_TEST_EQUAL( nt2::Sqrt_2o_2<T>()   , static_cast<T>(7.071067811865476e-1) );
  NT2_TEST_EQUAL( nt2::Gold<T>()        , static_cast<T>(1.6180339887498950) );
  NT2_TEST_EQUAL( nt2::Cgold<T>()       , static_cast<T>(3.8196601125010515e-1) );
}

////////////////////////////////////////////////////////////////////////////////
// Test type dependant values
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(type_dependant_real)
{
  NT2_TEST_EQUAL( nt2::Twotonmb<double>()    , 4503599627370496. );
  NT2_TEST_EQUAL( nt2::Splitfactor<double>() , 134217728.        );
  NT2_TEST_EQUAL( nt2::Twotonmb<float>()     , 8388608.f         );
  NT2_TEST_EQUAL( nt2::Splitfactor<float>()  , 8192.f            );
}

////////////////////////////////////////////////////////////////////////////////
// Test real_constant for every base types
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL  (  real_constant, (double)(float) )
{
  NT2_TEST_EQUAL( (nt2::real_constant < T , 0x3FF3BE76C8B43958LL
                                          , 0x3F9DF3B6
                                      >()
                  )
                , static_cast<T>(1.234)
                );
}

NT2_TEST_CASE(double_constant)
{
  NT2_TEST_EQUAL((nt2::double_constant<double,0x3FF3BE76C8B43958LL>()), 1.234);
}

NT2_TEST_CASE(single_constant)
{
  NT2_TEST_EQUAL((nt2::single_constant<float,0x3F9DF3B6>()),1.234f);
}
