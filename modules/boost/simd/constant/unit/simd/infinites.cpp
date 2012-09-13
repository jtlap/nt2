/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "boost::simd::constants infinites"

#include <boost/simd/include/constants/infinites.hpp>
#include <boost/simd/include/constants/properties.hpp>
#include <limits>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

////////////////////////////////////////////////////////////////////////////////
// Test value of infinites for every base real types
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL( real_inf, BOOST_SIMD_SIMD_REAL_TYPES )
{
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef boost::simd::native<T,ext_t>                vT;

  for(std::size_t i=0; i< boost::simd::meta::cardinal_of<vT>::value;++i){
    NT2_TEST_EQUAL( (boost::simd::Inf<vT>())[i], std::numeric_limits<T>::infinity() );
  }

  for(std::size_t i=0; i< boost::simd::meta::cardinal_of<vT>::value;++i){
    NT2_TEST_EQUAL( (boost::simd::Minf<vT>())[i], -std::numeric_limits<T>::infinity() );
  }
}

////////////////////////////////////////////////////////////////////////////////
// Test value of infinites for every base integral types
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL( int_inf, BOOST_SIMD_SIMD_INTEGRAL_TYPES )
{
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef boost::simd::native<T,ext_t>                vT;

  for(std::size_t i=0; i< boost::simd::meta::cardinal_of<vT>::value;++i){
    NT2_TEST_EQUAL( (boost::simd::Inf<vT>())[i], boost::simd::Valmax<T>() );
  }

  for(std::size_t i=0; i< boost::simd::meta::cardinal_of<vT>::value;++i){
    NT2_TEST_EQUAL( (boost::simd::Minf<vT>())[i], boost::simd::Valmin<T>() );
  }
}

////////////////////////////////////////////////////////////////////////////////
// Test value of infinites for raw char type
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( char_inf )
{
  typedef typename boost::simd::meta::vector_of<char, BOOST_SIMD_BYTES>::type vT;

  for(std::size_t i=0; i< boost::simd::meta::cardinal_of<vT>::value;++i){
    NT2_TEST_EQUAL( (boost::simd::Inf<vT>())[i], boost::simd::Valmax<char>() );
  }

  for(std::size_t i=0; i< boost::simd::meta::cardinal_of<vT>::value;++i){
    NT2_TEST_EQUAL( (boost::simd::Minf<vT>())[i], boost::simd::Valmin<char>() );
  }
}
