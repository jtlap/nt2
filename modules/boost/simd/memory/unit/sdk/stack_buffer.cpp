//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/memory/stack_buffer.hpp>
#include <boost/simd/memory/is_aligned.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

NT2_TEST_CASE_TPL(stack_buffer, BOOST_SIMD_TYPES)
{
  using boost::simd::is_aligned;

  BOOST_SIMD_STACK_BUFFER( array, T, 13 );

  NT2_TEST( is_aligned(&array[ 0 ], BOOST_SIMD_ALLOCA_ALIGNMENT) );
  for(std::size_t i=0; i < 13; ++i) array[i] = T(i+1);
  for(std::size_t i=0; i < 13; ++i) NT2_TEST_EQUAL(array[i], T(i+1));
}

NT2_TEST_CASE_TPL(aligned_stack_buffer, BOOST_SIMD_TYPES)
{
  using boost::simd::is_aligned;

  BOOST_SIMD_ALIGNED_STACK_BUFFER( array, T, 13 );

  NT2_TEST( is_aligned(&array[ 0 ]) );
  for(std::size_t i=0; i < 13; ++i) array[i] = T(i+1);
  for(std::size_t i=0; i < 13; ++i) NT2_TEST_EQUAL(array[i], T(i+1));
}

NT2_TEST_CASE_TPL(scoped_buffer, BOOST_SIMD_TYPES)
{
  using boost::simd::is_aligned;

  BOOST_SIMD_SCOPED_STACK_BUFFER( array, T, 13 );

  NT2_TEST( is_aligned(&array[ 0 ], BOOST_SIMD_ALLOCA_ALIGNMENT) );
  for(std::size_t i=0; i < 13; ++i) array[i] = T(i+1);
  for(std::size_t i=0; i < 13; ++i) NT2_TEST_EQUAL(array[i], T(i+1));
}

NT2_TEST_CASE_TPL(aligned_scoped_buffer, BOOST_SIMD_TYPES)
{
  using boost::simd::is_aligned;

  BOOST_SIMD_ALIGNED_SCOPED_STACK_BUFFER( array, T, 13 );

  NT2_TEST( is_aligned(&array[ 0 ]) );
  for(std::size_t i=0; i < 13; ++i) array[i] = T(i+1);
  for(std::size_t i=0; i < 13; ++i) NT2_TEST_EQUAL(array[i], T(i+1));
}
