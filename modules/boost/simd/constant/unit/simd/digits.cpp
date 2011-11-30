/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "boost::simd::constants digits"

#include <boost/simd/include/constants/digits.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <boost/simd/sdk/simd/native.hpp>

#ifdef BOOST_MSVC
  #pragma warning(disable: 4309) // truncation of constant value
#endif

////////////////////////////////////////////////////////////////////////////////
// Test value of digit constant for every base types
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL( digit_value, BOOST_SIMD_SIMD_TYPES )
{
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef boost::simd::native<T,ext_t>             dst_t;

  for(std::size_t i=0; i< boost::simd::meta::cardinal_of<dst_t>::value;++i)
  {
    NT2_TEST_EQUAL( (boost::simd::Mten<dst_t>())[i], static_cast<T>(  -10 ) );
    NT2_TEST_EQUAL( (boost::simd::Mnine<dst_t>())[i], static_cast<T>( -9 ) );
    NT2_TEST_EQUAL( (boost::simd::Meight<dst_t>())[i], static_cast<T>( -8 ) );
    NT2_TEST_EQUAL( (boost::simd::Mseven<dst_t>())[i], static_cast<T>( -7 ) );
    NT2_TEST_EQUAL( (boost::simd::Msix<dst_t>())[i], static_cast<T>( -6 ) );
    NT2_TEST_EQUAL( (boost::simd::Mfive<dst_t>())[i], static_cast<T>( -5 ) );
    NT2_TEST_EQUAL( (boost::simd::Mfour<dst_t>())[i], static_cast<T>( -4 ) );
    NT2_TEST_EQUAL( (boost::simd::Mthree<dst_t>())[i], static_cast<T>( -3 ) );
    NT2_TEST_EQUAL( (boost::simd::Mtwo<dst_t>())[i], static_cast<T>( -2 ) );
    NT2_TEST_EQUAL( (boost::simd::Mone<dst_t>())[i], static_cast<T>( -1 ) );
    NT2_TEST_EQUAL( (boost::simd::Zero<dst_t>())[i], static_cast<T>(  0 ) );
    NT2_TEST_EQUAL( (boost::simd::Ten<dst_t>())[i], static_cast<T>(  10 ) );
    NT2_TEST_EQUAL( (boost::simd::Nine<dst_t>())[i], static_cast<T>( 9 ) );
    NT2_TEST_EQUAL( (boost::simd::Eight<dst_t>())[i], static_cast<T>( 8 ) );
    NT2_TEST_EQUAL( (boost::simd::Seven<dst_t>())[i], static_cast<T>( 7 ) );
    NT2_TEST_EQUAL( (boost::simd::Six<dst_t>())[i], static_cast<T>( 6 ) );
    NT2_TEST_EQUAL( (boost::simd::Five<dst_t>())[i], static_cast<T>( 5 ) );
    NT2_TEST_EQUAL( (boost::simd::Four<dst_t>())[i], static_cast<T>( 4 ) );
    NT2_TEST_EQUAL( (boost::simd::Three<dst_t>())[i], static_cast<T>( 3 ) );
    NT2_TEST_EQUAL( (boost::simd::Two<dst_t>())[i], static_cast<T>( 2 ) );
    NT2_TEST_EQUAL( (boost::simd::One<dst_t>())[i], static_cast<T>( 1 ) );
  }
}

////////////////////////////////////////////////////////////////////////////////
// Test integral_constant for every base types
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL( integral_constant, BOOST_SIMD_SIMD_INTEGRAL_TYPES )
{
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef boost::simd::native<T,ext_t>             dst_t;

  for(std::size_t i=0; i< boost::simd::meta::cardinal_of<dst_t>::value;++i)
    NT2_TEST_EQUAL( (boost::simd::integral_constant<dst_t,42>())[i], static_cast<T>(42) );
}
