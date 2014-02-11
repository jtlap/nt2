//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/memory/aligned_malloc.hpp>
#include <boost/simd/memory/aligned_free.hpp>
#include <boost/simd/memory/is_aligned.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

static bool         had_malloc;
static bool         had_free;
static std::size_t  malloc_size;

static void* stateful_malloc(std::size_t sz)
{
  had_malloc  = true;
  malloc_size = sz;
  return std::malloc(sz);
}

static void stateful_free(void* ptr, std::size_t)
{
  had_free  = true;
  return std::free(ptr);
}

static void reset_status()
{
  had_free    = false;
  had_malloc  = false;
  malloc_size = 0;
}

//==============================================================================
// Test allocating and deallocating
//==============================================================================
NT2_TEST_CASE(aligned_malloc)
{
  using boost::simd::aligned_malloc;
  using boost::simd::aligned_free;
  using boost::simd::is_aligned;

  reset_status();

  char* ptr = 0;
  NT2_TEST
  ( is_aligned(ptr = static_cast<char*>(aligned_malloc(5,8, stateful_malloc)),8) );

  NT2_TEST( had_malloc );
  NT2_TEST_GREATER_EQUAL( malloc_size, 5u );

  for(int i=0;i<5;++i) ptr[i] = 10*i;
  for(int i=0;i<5;++i) NT2_TEST_EQUAL(ptr[i],10*i);

  aligned_free( ptr, stateful_free );

  NT2_TEST( had_free );
}
