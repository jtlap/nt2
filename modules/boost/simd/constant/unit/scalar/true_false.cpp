//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "boost::simd::constants true/false scalar case"

#include <boost/simd/sdk/simd/logical.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/include/constants/true_false.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

////////////////////////////////////////////////////////////////////////////////
// Test value of true/false constants for every base real types
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL( true_false_value, BOOST_SIMD_TYPES )
{
  using boost::simd::logical;

  NT2_TEST_EQUAL( boost::simd::False< boost::simd::logical<T> >(), logical<T>(false) );
  NT2_TEST_EQUAL( boost::simd::True< boost::simd::logical<T> >() , logical<T>(true) );
  NT2_TEST_EQUAL( boost::simd::False< logical<T> >(), logical<T>(false) );
  NT2_TEST_EQUAL( boost::simd::True< logical<T> >() , logical<T>(true) );

  NT2_TEST_EQUAL( boost::simd::False< boost::simd::logical<T> >(), false );
  NT2_TEST_EQUAL( boost::simd::True< boost::simd::logical<T> >() , true );
  NT2_TEST_EQUAL( boost::simd::False< logical<T> >(), false );
  NT2_TEST_EQUAL( boost::simd::True< logical<T> >() , true );
}
