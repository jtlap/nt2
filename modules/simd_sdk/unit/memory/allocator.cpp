/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 0x01.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define BOOST_SIMD_UNIT_MODULE "boost::simd::memory::allocator"

#include <boost/simd/sdk/memory/allocator.hpp>
#include <boost/simd/sdk/memory/is_aligned.hpp>

#include <vector>
#include <boost/simd/sdk/unit/module.hpp>
#include <boost/simd/sdk/unit/tests/relation.hpp>
#include <boost/simd/sdk/unit/tests/basic.hpp>

////////////////////////////////////////////////////////////////////////////////
// Test allocator with std::vector
////////////////////////////////////////////////////////////////////////////////
BOOST_SIMD_TEST_CASE_TPL(vector, BOOST_SIMD_TYPES)
{
  using boost::simd::memory::is_aligned;
  std::vector<T, boost::simd::memory::allocator<T> > p(5);

  BOOST_SIMD_TEST( is_aligned( &p[0] ) );
  for(int i=0;i<5;++i) p[i] = T(10)*i;
  for(int i=0;i<5;++i) BOOST_SIMD_TEST_EQUAL(p[i],T(10)*i);
}
