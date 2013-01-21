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
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/include/constants/properties.hpp>
#include <limits>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

////////////////////////////////////////////////////////////////////////////////
// Test value of infinites for every base real types
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL( real_inf, BOOST_SIMD_REAL )
{
  NT2_TEST_EQUAL( boost::simd::Inf<T>() , std::numeric_limits<T>::infinity()  );
  NT2_TEST_EQUAL( boost::simd::Minf<T>(), -std::numeric_limits<T>::infinity() );
}

////////////////////////////////////////////////////////////////////////////////
// Test value of infinites for every base integral types
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL( int_inf, BOOST_SIMD_INTEGRAL_TYPES )
{
  NT2_TEST_EQUAL( boost::simd::Inf<T>() , boost::simd::Valmax<T>()  );
  NT2_TEST_EQUAL( boost::simd::Minf<T>(), boost::simd::Valmin<T>()  );
}

////////////////////////////////////////////////////////////////////////////////
// Test value of infinites for raw char type
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( char_inf)
{
  NT2_TEST_EQUAL( boost::simd::Inf<char>() , boost::simd::Valmax<char>()  );
  NT2_TEST_EQUAL( boost::simd::Minf<char>(), boost::simd::Valmin<char>()  );
}
