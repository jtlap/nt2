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
#include <boost/simd/memory/reallocate.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

//==============================================================================
// Test allocating and deallocating
//==============================================================================
NT2_TEST_CASE(allocate)
{
  using boost::simd::memory::byte;
  using boost::simd::memory::allocate;
  using boost::simd::memory::deallocate;
  using boost::simd::is_aligned;

  byte* ptr = 0;
  NT2_TEST( is_aligned(ptr = allocate(5)) );

  for(int i=0;i<5;++i) ptr[i] = 10*i;
  for(int i=0;i<5;++i) NT2_TEST_EQUAL(ptr[i],10*i);

  deallocate( ptr );
}

//==============================================================================
// Test allocating and deallocating and arbitrary alignment
//==============================================================================
NT2_TEST_CASE(allocate_align)
{
  using boost::simd::memory::byte;
  using boost::simd::memory::allocate;
  using boost::simd::memory::deallocate;
  using boost::simd::is_aligned;

  byte* ptr = 0;
  NT2_TEST( is_aligned(ptr = allocate(5, 128), 128) );

  for(int i=0;i<5;++i) ptr[i] = 10*i;
  for(int i=0;i<5;++i) NT2_TEST_EQUAL(ptr[i],10*i);

  deallocate( ptr );
}

//==============================================================================
// Test static allocating and deallocating and arbitrary alignment
//==============================================================================
NT2_TEST_CASE(allocate_static_align)
{
  using boost::simd::memory::byte;
  using boost::simd::memory::allocate;
  using boost::simd::memory::deallocate;
  using boost::simd::is_aligned;

  byte* ptr = 0;
  NT2_TEST( is_aligned(ptr = allocate<16>(5), 16) );

  for(int i=0;i<5;++i) ptr[i] = 10*i;
  for(int i=0;i<5;++i) NT2_TEST_EQUAL(ptr[i],10*i);

  deallocate( ptr );
}

//==============================================================================
// Test reallocating and deallocating
//==============================================================================
NT2_TEST_CASE(reallocate)
{
  using boost::simd::memory::byte;
  using boost::simd::memory::reallocate;
  using boost::simd::memory::deallocate;
  using boost::simd::is_aligned;

  byte *ptr(0), *ptr2(0);
  NT2_TEST( is_aligned(ptr = reallocate(ptr,5)) );
  for(int i=0;i<5;++i) ptr[i] = 10*i;
  for(int i=0;i<5;++i) NT2_TEST_EQUAL(ptr[i],10*i);

  NT2_TEST( is_aligned(ptr2 = reallocate(ptr,2)) );
  for(int i=0;i<2;++i) ptr2[i] = 10*i;
  for(int i=0;i<2;++i) NT2_TEST_EQUAL(ptr2[i],10*i);

  NT2_TEST( is_aligned(ptr = reallocate(ptr2,7)) );
  for(int i=0;i<7;++i) ptr[i] = 10*i;
  for(int i=0;i<7;++i) NT2_TEST_EQUAL(ptr[i],10*i);

  ptr = reallocate(ptr,0);
  NT2_TEST( !ptr );
}

//==============================================================================
// Test reallocating and deallocating on arbitrary alignment
//==============================================================================
NT2_TEST_CASE(reallocate_align)
{
  using boost::simd::memory::byte;
  using boost::simd::memory::reallocate;
  using boost::simd::memory::deallocate;
  using boost::simd::is_aligned;

  byte *ptr(0), *ptr2(0);
  NT2_TEST( is_aligned(ptr = reallocate(ptr,5,64), 64) );
  for(int i=0;i<5;++i) ptr[i] = 10*i;
  for(int i=0;i<5;++i) NT2_TEST_EQUAL(ptr[i],10*i);

  NT2_TEST( is_aligned(ptr = reallocate(ptr,3,64), 64) );
  for(int i=0;i<3;++i) ptr[i] = 10*i;
  for(int i=0;i<3;++i) NT2_TEST_EQUAL(ptr[i],10*i);

  NT2_TEST( is_aligned(ptr2 = reallocate(ptr,2,32), 32) );
  for(int i=0;i<2;++i) ptr2[i] = 10*i;
  for(int i=0;i<2;++i) NT2_TEST_EQUAL(ptr2[i],10*i);

  NT2_TEST( is_aligned(ptr = reallocate(ptr2,7,64), 64) );
  for(int i=0;i<7;++i) ptr[i] = 10*i;
  for(int i=0;i<7;++i) NT2_TEST_EQUAL(ptr[i],10*i);

  ptr = reallocate(ptr,0,64);
  NT2_TEST( !ptr );
}
