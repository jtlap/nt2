//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/include/constants/real.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

#include "../constant.hpp"

NT2_TEST_CASE_TPL(  real_value, BOOST_SIMD_REAL_TYPES )
{
  NT2_CHECK_CONSTANT(Moneo_6    , T(-1./6.)                   , T );
  NT2_CHECK_CONSTANT(Mhalf      , T(-1./2.)                   , T );
  NT2_CHECK_CONSTANT(Mzero      , T(-0.)                      , T );
  NT2_CHECK_CONSTANT(Half       , T(1/2.)                     , T );
  NT2_CHECK_CONSTANT(Third      , T(1/3.)                     , T );
  NT2_CHECK_CONSTANT(Quarter    , T(1/4.)                     , T );
  NT2_CHECK_CONSTANT(Oneo_5     , T(1./5.)                    , T );
  NT2_CHECK_CONSTANT(Oneo_6     , T(1./6.)                    , T );
  NT2_CHECK_CONSTANT(Oneo_7     , T(1./7.)                    , T );
  NT2_CHECK_CONSTANT(Oneo_8     , T(1./8.)                    , T );
  NT2_CHECK_CONSTANT(Oneo_9     , T(1./9.)                    , T );
  NT2_CHECK_CONSTANT(Oneo_10    , T(1./10.)                   , T );
  NT2_CHECK_CONSTANT(Oneo_12    , T(1./12.)                   , T );
  NT2_CHECK_CONSTANT(Oneo_15    , T(1./15.)                   , T );
  NT2_CHECK_CONSTANT(Oneo_120   , T(1./120.)                  , T );
  NT2_CHECK_CONSTANT(Oneo_180   , T(1./180.)                  , T );
  NT2_CHECK_CONSTANT(Twoto31    , T(2147483648ll)             , T );
  NT2_CHECK_CONSTANT(Twotom10   , T(9.765625e-4)              , T );
  NT2_CHECK_CONSTANT(Pi         , T(3.1415926535897930)       , T );
  NT2_CHECK_CONSTANT(Pio_2      , T(1.570796326794896558)     , T );
  NT2_CHECK_CONSTANT(Sqrt_2     , T(1.4142135623730949234)    , T );
  NT2_CHECK_CONSTANT(Sqrt_1o_5  , T(0.4472135954999579277)    , T );
  NT2_CHECK_CONSTANT(Sqrt_2o_2  , T(7.071067811865476e-1)     , T );
  NT2_CHECK_CONSTANT(Sqrt_2o_3  , T(0.81649658092772603446)   , T );
  NT2_CHECK_CONSTANT(Log10_pi   , T(0.49714987269413385418)   , T );
  NT2_CHECK_CONSTANT(Gold       , T(1.6180339887498950)       , T );
  NT2_CHECK_CONSTANT(Cgold      , T(3.8196601125010515e-1)    , T );
}

NT2_TEST_CASE_TPL( nan_value, BOOST_SIMD_REAL_TYPES )
{
  NT2_TEST_EXPR_TYPE( (boost::simd::Nan<T>())
                    , boost::mpl::_
                    , T
                    );

  NT2_TEST( check_is_nan(boost::simd::Nan<T>()) );
}

NT2_TEST_CASE(type_dependant_real)
{
  NT2_CHECK_CONSTANT(Twotonmb     , 4503599627370496  , double );
  NT2_CHECK_CONSTANT(Splitfactor  , 134217728.        , double );
  NT2_CHECK_CONSTANT(Twotonmb     , 8388608.f         , float );
  NT2_CHECK_CONSTANT(Splitfactor  , 8192.f            , float );
}

NT2_TEST_CASE(type_dependant_const)
{
  NT2_TEST_EXPR_TYPE( (boost::simd::Const<double,0x3FF3BE76C8B43958LL>())
                    , boost::mpl::_
                    , double
                    );

  NT2_TEST_EXPR_TYPE( (boost::simd::Const<float,0x3F9DF3B6>())
                    , boost::mpl::_
                    , float
                    );

  NT2_TEST_EQUAL( (boost::simd::Const<double,0x3FF3BE76C8B43958LL>()), 1.234   );
  NT2_TEST_EQUAL( (boost::simd::Const<float,0x3F9DF3B6>()), 1.234f );
}

NT2_TEST_CASE_TPL(  real_constant, (double)(float) )
{
  NT2_TEST_EXPR_TYPE( (boost::simd::real_constant < T
                                              , 0x3FF3BE76C8B43958LL
                                              , 0x3F9DF3B6
                                              >()
                      )
                    , boost::mpl::_
                    , T
                    );

  NT2_TEST_EQUAL( (boost::simd::real_constant < T
                                              , 0x3FF3BE76C8B43958LL
                                              , 0x3F9DF3B6
                                              >()
                  )
                , static_cast<T>(1.234)
                );
}

NT2_TEST_CASE(double_constant)
{
  NT2_TEST_EXPR_TYPE( (boost::simd::double_constant<double,0x3FF3BE76C8B43958LL>())
                    , boost::mpl::_
                    , double
                    );

  NT2_TEST_EQUAL( (boost::simd::double_constant<double,0x3FF3BE76C8B43958LL>())
                , 1.234
                );
}

NT2_TEST_CASE(single_constant)
{
  NT2_TEST_EXPR_TYPE( (boost::simd::single_constant<float,0x3F9DF3B6>())
                    , boost::mpl::_
                    , float
                    );

  NT2_TEST_EQUAL( (boost::simd::single_constant<float,0x3F9DF3B6>())
                , 1.234f
                );
}
