//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/memory/aligned_realloc.hpp>
#include <boost/simd/memory/is_aligned.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

static bool         had_realloc;
static std::size_t  realloc_size;

static void reset_status()
{
  had_realloc  = false;
  realloc_size = 0;
}

static void* stateful_realloc(void* ptr, std::size_t sz, std::size_t)
{
  had_realloc  = true;
  realloc_size = sz;
  return std::realloc(ptr,sz);
}

//==============================================================================
// Test reallocating and deallocating on arbitrary alignment
//==============================================================================
NT2_TEST_CASE(aligned_realloc)
{
  using boost::simd::aligned_free;
  using boost::simd::aligned_realloc;
  using boost::simd::is_aligned;

  char *ptr(0), *ptr2(0);

  reset_status();
  NT2_TEST( is_aligned(ptr = static_cast<char*>(aligned_realloc(ptr,5,8,stateful_realloc)), 8) );
  for(int i=0;i<5;++i) ptr[i] = 10*i;
  for(int i=0;i<5;++i) NT2_TEST_EQUAL(ptr[i],10*i);

  NT2_TEST( had_realloc );
  NT2_TEST_GREATER_EQUAL( realloc_size, 5u );

  reset_status();
  NT2_TEST( is_aligned(ptr = static_cast<char*>(aligned_realloc(ptr,3,8,stateful_realloc)), 8) );
  for(int i=0;i<3;++i) ptr[i] = 10*i;
  for(int i=0;i<3;++i) NT2_TEST_EQUAL(ptr[i],10*i);

  NT2_TEST( had_realloc );
  NT2_TEST_GREATER_EQUAL( realloc_size, 3u );

  reset_status();
  NT2_TEST( is_aligned(ptr2 = static_cast<char*>(aligned_realloc(ptr,2,16,stateful_realloc)), 16) );
  for(int i=0;i<2;++i) ptr2[i] = 10*i;
  for(int i=0;i<2;++i) NT2_TEST_EQUAL(ptr2[i],10*i);

  NT2_TEST( had_realloc );
  NT2_TEST_GREATER_EQUAL( realloc_size, 2u );

  reset_status();
  NT2_TEST( is_aligned(ptr = static_cast<char*>(aligned_realloc(ptr2,7,8,stateful_realloc)), 8) );
  for(int i=0;i<7;++i) ptr[i] = 10*i;
  for(int i=0;i<7;++i) NT2_TEST_EQUAL(ptr[i],10*i);

  NT2_TEST( had_realloc );
  NT2_TEST_GREATER_EQUAL( realloc_size, 7u );

  reset_status();
  ptr = static_cast<char*>(aligned_realloc(ptr,0,8,stateful_realloc));
  NT2_TEST( !ptr || (std::free(ptr), true) );

  NT2_TEST( had_realloc );
  NT2_TEST_EQUAL( realloc_size, 0u );
}
