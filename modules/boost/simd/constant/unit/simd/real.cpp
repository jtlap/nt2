/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "boost::simd::constants SIMD real"

#include <boost/simd/include/constants/real.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

////////////////////////////////////////////////////////////////////////////////
// Test value of real constants for every base real types
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL(real_values, BOOST_SIMD_SIMD_TYPES)
{
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef boost::simd::native<T,ext_t> vd_t;
  for(std::size_t i=0; i< boost::simd::meta::cardinal_of<vd_t>::value;++i)
  {
    NT2_TEST_EQUAL( (boost::simd::Mhalf<vd_t>())[i], boost::simd::Mhalf<T>() );
    NT2_TEST_EQUAL( (boost::simd::Mzero<vd_t>())[i], boost::simd::Mzero<T>() );
    NT2_TEST_EQUAL( (boost::simd::Half<vd_t>())[i], boost::simd::Half<T>() );
    NT2_TEST_EQUAL( (boost::simd::Third<vd_t>())[i], boost::simd::Third<T>() );
    NT2_TEST_EQUAL( (boost::simd::Quarter<vd_t>())[i], boost::simd::Quarter<T>() );
    NT2_TEST_EQUAL( (boost::simd::Twotom10<vd_t>())[i], boost::simd::Twotom10<T>() );
    NT2_TEST_EQUAL( (boost::simd::Pi<vd_t>())[i], boost::simd::Pi<T>() );
    NT2_TEST_EQUAL( (boost::simd::Sqrt_2<vd_t>())[i], boost::simd::Sqrt_2<T>() );
    NT2_TEST_EQUAL( (boost::simd::Sqrt_2o_2<vd_t>())[i], boost::simd::Sqrt_2o_2<T>() );
    NT2_TEST_EQUAL( (boost::simd::Gold<vd_t>())[i], boost::simd::Gold<T>() );
    NT2_TEST_EQUAL( (boost::simd::Cgold<vd_t>())[i], boost::simd::Cgold<T>() );
    NT2_TEST_EQUAL( (boost::simd::Twotonmb<vd_t>())[i] , boost::simd::Twotonmb<T>() );
    NT2_TEST_EQUAL( (boost::simd::Splitfactor<vd_t>())[i], boost::simd::Splitfactor<T>());
  }
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
  typedef boost::simd::native<T,ext_t>      v_t;

  for(std::size_t i=0; i< boost::simd::meta::cardinal_of<v_t>::value;++i)
  {
    NT2_TEST_EQUAL( (boost::simd::Const<v_t, type_dependant_const_value<T>::value>())[i], T(1.234)   );
  }
}

////////////////////////////////////////////////////////////////////////////////
// Test real_constant for every base types
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL(real_pattern, BOOST_SIMD_SIMD_REAL_TYPES)
{
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef boost::simd::native<T,ext_t> vd_t;
  for(std::size_t i=0; i< boost::simd::meta::cardinal_of<vd_t>::value;++i)
  {
    NT2_TEST_EQUAL( (boost::simd::real_constant < vd_t , 0x3FF3BE76C8B43958LL
                                            , 0x3F9DF3B6
                                        >()
                    )[i],
                    (boost::simd::real_constant < T , 0x3FF3BE76C8B43958LL
                                                            , 0x3F9DF3B6
                                                        >()
                                    ));
  }
}
