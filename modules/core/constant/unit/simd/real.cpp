//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/constants/real.hpp>

#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/sdk/simd/io.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

#include "../constant.hpp"

NT2_TEST_CASE_TPL(  real_value, BOOST_SIMD_SIMD_REAL_TYPES )
{
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef boost::simd::native<T,ext_t>  n_t;

  NT2_CHECK_CONSTANT(Moneo_6    , T(-1./6.)                   , n_t );
  NT2_CHECK_CONSTANT(Mhalf      , T(-1./2.)                   , n_t );
  NT2_CHECK_CONSTANT(Mzero      , T(-0.)                      , n_t );
  NT2_CHECK_CONSTANT(Half       , T(1/2.)                     , n_t );
  NT2_CHECK_CONSTANT(Third      , T(1/3.)                     , n_t );
  NT2_CHECK_CONSTANT(Quarter    , T(1/4.)                     , n_t );
  NT2_CHECK_CONSTANT(Oneo_5     , T(1./5.)                    , n_t );
  NT2_CHECK_CONSTANT(Oneo_6     , T(1./6.)                    , n_t );
  NT2_CHECK_CONSTANT(Oneo_7     , T(1./7.)                    , n_t );
  NT2_CHECK_CONSTANT(Oneo_8     , T(1./8.)                    , n_t );
  NT2_CHECK_CONSTANT(Oneo_9     , T(1./9.)                    , n_t );
  NT2_CHECK_CONSTANT(Oneo_10    , T(1./10.)                   , n_t );
  NT2_CHECK_CONSTANT(Oneo_12    , T(1./12.)                   , n_t );
  NT2_CHECK_CONSTANT(Oneo_15    , T(1./15.)                   , n_t );
  NT2_CHECK_CONSTANT(Oneo_120   , T(1./120.)                  , n_t );
  NT2_CHECK_CONSTANT(Oneo_180   , T(1./180.)                  , n_t );
  NT2_CHECK_CONSTANT(Twotom10   , T(9.765625e-4)              , n_t );
  NT2_CHECK_CONSTANT(Twoto31    , T(2147483648ll)             , n_t );
  NT2_CHECK_CONSTANT(Pi         , T(3.1415926535897930)       , n_t );
  NT2_CHECK_CONSTANT(Pio_2      , T(1.570796326794896558)     , n_t );
  NT2_CHECK_CONSTANT(Sqrt_2     , T(1.4142135623730949234)    , n_t );
  NT2_CHECK_CONSTANT(Sqrt_1o_5  , T(0.4472135954999579277)    , n_t );
  NT2_CHECK_CONSTANT(Sqrt_2o_2  , T(7.071067811865476e-1)     , n_t );
  NT2_CHECK_CONSTANT(Sqrt_2o_3  , T(0.81649658092772603446)   , n_t );
  NT2_CHECK_CONSTANT(Log10_pi   , T(0.49714987269413385418)   , n_t );
  NT2_CHECK_CONSTANT(Gold       , T(1.6180339887498950)       , n_t );
  NT2_CHECK_CONSTANT(Cgold      , T(3.8196601125010515e-1)    , n_t );
  NT2_CHECK_CONSTANT(Twotonmb   , nt2::Twotonmb<T>()    , n_t );
  NT2_CHECK_CONSTANT(Splitfactor, nt2::Splitfactor<T>() , n_t );
}

NT2_TEST_CASE_TPL( nan_value, BOOST_SIMD_SIMD_REAL_TYPES )
{
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef boost::simd::native<T,ext_t>  n_t;

  NT2_CHECK_CONSTANT(Nan, nt2::Nan<T>(), n_t );
}


template<class T>
struct type_dependant_const_value;

template<>
struct type_dependant_const_value<double>
{
  static const uint64_t value = 0x3FF3BE76C8B43958LL;
};

template<>
struct type_dependant_const_value<float>
{
  static const uint64_t value = 0x3F9DF3B6;
};

NT2_TEST_CASE_TPL(type_dependant_const, BOOST_SIMD_SIMD_REAL_TYPES)
{
  typedef BOOST_SIMD_DEFAULT_EXTENSION      ext_t;
  typedef boost::simd::native<T,ext_t>      n_t;

  NT2_TEST_EXPR_TYPE( (nt2::Const < n_t
                                          , type_dependant_const_value<T>::value
                                          >()
                      )
                    , boost::mpl::_
                    , n_t
                    );

  NT2_TEST_EQUAL( (nt2::Const < n_t
                                      , type_dependant_const_value<T>::value
                                      >()
                  )
                , nt2::splat<n_t>
                  ( nt2::Const< n_t
                                      , type_dependant_const_value<T>::value
                                      >()
                  )
                );
}

NT2_TEST_CASE_TPL(  real_constant, BOOST_SIMD_SIMD_REAL_TYPES )
{
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef boost::simd::native<T,ext_t>  n_t;

  NT2_TEST_EXPR_TYPE( (nt2::real_constant < n_t
                                                  , 0x3FF3BE76C8B43958LL
                                                  , 0x3F9DF3B6
                                                  >()
                      )
                    , boost::mpl::_
                    , n_t
                    );

  NT2_TEST_EQUAL( (nt2::real_constant < n_t
                                              , 0x3FF3BE76C8B43958LL
                                              , 0x3F9DF3B6
                                              >()
                  )
                , nt2::splat<n_t>(nt2::real_constant < T
                                              , 0x3FF3BE76C8B43958LL
                                              , 0x3F9DF3B6
                                              >()
                  )
                );
}
