//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/memory/allocate.hpp>
#include <boost/simd/memory/is_aligned.hpp>
#include <boost/simd/memory/deallocate.hpp>
#include <vector>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

//==============================================================================
// Test allocating and deallocating
//==============================================================================
NT2_TEST_CASE(allocate)
{
  using boost::simd::allocate;
  using boost::simd::deallocate;
  using boost::simd::is_aligned;

  char* ptr = 0;
  NT2_TEST( is_aligned(ptr = static_cast<char*>(allocate(5))) );

  for(int i=0;i<5;++i) ptr[i] = 10*i;
  for(int i=0;i<5;++i) NT2_TEST_EQUAL(ptr[i],10*i);

  deallocate( ptr );
}

//==============================================================================
// Test allocating and deallocating and arbitrary alignment
//==============================================================================
NT2_TEST_CASE(allocate_align)
{
  using boost::simd::allocate;
  using boost::simd::deallocate;
  using boost::simd::is_aligned;

  char* ptr = 0;
  NT2_TEST( is_aligned(ptr = static_cast<char*>(allocate(5, 16)), 16) );

  for(int i=0;i<5;++i) ptr[i] = 10*i;
  for(int i=0;i<5;++i) NT2_TEST_EQUAL(ptr[i],10*i);

  deallocate( ptr );
}

//==============================================================================
// Test static allocating and deallocating and arbitrary alignment
//==============================================================================
NT2_TEST_CASE(allocate_static_align)
{
  using boost::simd::allocate;
  using boost::simd::deallocate;
  using boost::simd::is_aligned;

  char* ptr = 0;
  NT2_TEST( is_aligned(ptr = static_cast<char*>(allocate<16>(5)), 16) );

  for(int i=0;i<5;++i) ptr[i] = 10*i;
  for(int i=0;i<5;++i) NT2_TEST_EQUAL(ptr[i],10*i);

  deallocate( ptr );
}

NT2_TEST_CASE_TPL(allocator_allocate, BOOST_SIMD_TYPES)
{
  using boost::simd::allocate;
  using boost::simd::deallocate;
  using boost::simd::is_aligned;

  std::allocator<T> alloc;

  char* ptr = 0;
  NT2_TEST( (is_aligned(ptr = static_cast<char*>(allocate(alloc, 5)))) );

  for(int i=0;i<5;++i) ptr[i] = 10*i;
  for(int i=0;i<5;++i) NT2_TEST_EQUAL(ptr[i],10*i);

  deallocate( alloc, ptr );
}

NT2_TEST_CASE_TPL(allocator_allocate_align, BOOST_SIMD_TYPES)
{
  using boost::simd::allocate;
  using boost::simd::deallocate;
  using boost::simd::is_aligned;

  std::allocator<T> alloc;

  char* ptr = 0;
  NT2_TEST( (is_aligned(ptr = static_cast<char*>(allocate(alloc, 5, 32)), 32)) );

  for(int i=0;i<5;++i) ptr[i] = 10*i;
  for(int i=0;i<5;++i) NT2_TEST_EQUAL(ptr[i],10*i);

  deallocate( alloc, ptr );
}

NT2_TEST_CASE_TPL(static_allocator_allocate_align, BOOST_SIMD_TYPES)
{
  using boost::simd::allocate;
  using boost::simd::deallocate;
  using boost::simd::is_aligned;

  std::allocator<T> alloc;

  char* ptr = 0;
  NT2_TEST( (is_aligned(ptr = static_cast<char*>(allocate<32>(alloc, 5)), 32)) );

  for(int i=0;i<5;++i) ptr[i] = 10*i;
  for(int i=0;i<5;++i) NT2_TEST_EQUAL(ptr[i],10*i);

  deallocate( alloc, ptr );
}
