/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 0x01.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define BOOST_SIMD_UNIT_MODULE "boost::simd::memory based aligned new/delete overload"

#include <boost/simd/sdk/memory/overload.hpp>
#include <boost/simd/sdk/memory/is_aligned.hpp>

#include <boost/simd/sdk/unit/module.hpp>
#include <boost/simd/sdk/unit/tests/basic.hpp>
#include <boost/simd/sdk/unit/tests/relation.hpp>

class foo
{
  public:
  BOOST_SIMD_MEMORY_OVERLOAD_NEW_DELETE(foo)

  int  member;
};

////////////////////////////////////////////////////////////////////////////////
// Test foo allocation using the aligned new/delete
////////////////////////////////////////////////////////////////////////////////
BOOST_SIMD_TEST_CASE(overload_new_delete)
{
  using boost::simd::memory::is_aligned;

  foo* ptr = new foo;

  BOOST_SIMD_TEST( is_aligned(ptr) );
  ptr->member = 42;
  BOOST_SIMD_TEST_EQUAL( ptr->member, 42 );
  delete ptr;
}

////////////////////////////////////////////////////////////////////////////////
// Test foo allocation using the aligned new/delete
////////////////////////////////////////////////////////////////////////////////
BOOST_SIMD_TEST_CASE(overload_new_delete_array)
{
  using boost::simd::memory::is_aligned;

  foo* ptr = new foo[5];

  BOOST_SIMD_TEST( is_aligned(ptr) );

  for(int i=0;i<5;++i) ptr[i].member = 10*i;
  for(int i=0;i<5;++i) BOOST_SIMD_TEST_EQUAL( ptr[i].member, 10*i );

  delete[] ptr;
}

