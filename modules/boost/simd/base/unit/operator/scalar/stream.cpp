//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "boost::simd::memory::stream"

#include <boost/simd/include/functions/stream.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/sdk/config/types.hpp>
#include <boost/simd/sdk/config/type_lists.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

////////////////////////////////////////////////////////////////////////////////
// Test store behavior
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL(stream, BOOST_SIMD_TYPES)
{
  using boost::simd::stream;

  T data[5];
  for(boost::simd::int32_t i=0;i<5;++i) stream(static_cast<T>(i),&data[0],i);
  NT2_TEST_EQUAL( data[0], T(0) );
  NT2_TEST_EQUAL( data[1], T(1) );
  NT2_TEST_EQUAL( data[2], T(2) );
  NT2_TEST_EQUAL( data[3], T(3) );
  NT2_TEST_EQUAL( data[4], T(4) );
}
