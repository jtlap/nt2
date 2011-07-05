/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define BOOST_SIMD_UNIT_MODULE "boost::simd::constants infinites"

#include <limits>
#include <boost/simd/include/constants/infinites.hpp>
#include <boost/simd/include/constants/properties.hpp>

#include <boost/simd/sdk/unit/module.hpp>
#include <boost/simd/sdk/unit/tests/relation.hpp>

////////////////////////////////////////////////////////////////////////////////
// Test value of infinites for every base real types
////////////////////////////////////////////////////////////////////////////////
BOOST_SIMD_TEST_CASE_TPL( real_inf, BOOST_SIMD_REAL )
{
  BOOST_SIMD_TEST_EQUAL( boost::simd::Inf<T>() , std::numeric_limits<T>::infinity()  );
  BOOST_SIMD_TEST_EQUAL( boost::simd::Minf<T>(), -std::numeric_limits<T>::infinity() );
}

////////////////////////////////////////////////////////////////////////////////
// Test value of infinites for every base integral types
////////////////////////////////////////////////////////////////////////////////
BOOST_SIMD_TEST_CASE_TPL( int_inf, BOOST_SIMD_INTEGRAL_TYPES )
{
  BOOST_SIMD_TEST_EQUAL( boost::simd::Inf<T>() , boost::simd::Valmax<T>()  );
  BOOST_SIMD_TEST_EQUAL( boost::simd::Minf<T>(), boost::simd::Valmin<T>()  );
}
