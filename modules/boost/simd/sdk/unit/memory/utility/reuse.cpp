//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/memory/reuse.hpp>
#include <boost/simd/memory/is_aligned.hpp>
#include <vector>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

//==============================================================================
// Test reusing and deallocating
//==============================================================================
NT2_TEST_CASE(reuse)
{
  using boost::simd::reuse;
  using boost::simd::is_aligned;

  char *ptr(0), *ptr2(0);
  NT2_TEST( is_aligned(ptr = static_cast<char*>(reuse(ptr,5))) );
  for(int i=0;i<5;++i) ptr[i] = 10*i;
  for(int i=0;i<5;++i) NT2_TEST_EQUAL(ptr[i],10*i);

  NT2_TEST( is_aligned(ptr2 = static_cast<char*>(reuse(ptr,2))) );
  for(int i=0;i<2;++i) ptr2[i] = 10*i;
  for(int i=0;i<2;++i) NT2_TEST_EQUAL(ptr2[i],10*i);

  NT2_TEST( is_aligned(ptr = static_cast<char*>(reuse(ptr2,7))) );
  for(int i=0;i<7;++i) ptr[i] = 10*i;
  for(int i=0;i<7;++i) NT2_TEST_EQUAL(ptr[i],10*i);

  ptr = static_cast<char*>(reuse(ptr,0));
  NT2_TEST( !ptr || (::free(ptr), true) );
}

//==============================================================================
// Test reusing and deallocating with allocator
//==============================================================================
NT2_TEST_CASE(reuse_allocator)
{
  using std::allocator;
  using boost::simd::reuse;
  using boost::simd::is_aligned;

  allocator<char> alloc;

  char *ptr(0), *ptr2(0);
  NT2_TEST( is_aligned(ptr = static_cast<char*>(reuse(alloc,ptr,5))) );
  for(int i=0;i<5;++i) ptr[i] = 10*i;
  for(int i=0;i<5;++i) NT2_TEST_EQUAL(ptr[i],10*i);

  NT2_TEST( is_aligned(ptr2 = static_cast<char*>(reuse(alloc,ptr,2))) );
  for(int i=0;i<2;++i) ptr2[i] = 10*i;
  for(int i=0;i<2;++i) NT2_TEST_EQUAL(ptr2[i],10*i);

  NT2_TEST( is_aligned(ptr = static_cast<char*>(reuse(alloc,ptr2,7))) );
  for(int i=0;i<7;++i) ptr[i] = 10*i;
  for(int i=0;i<7;++i) NT2_TEST_EQUAL(ptr[i],10*i);

  ptr = static_cast<char*>(reuse(alloc,ptr,0));
  NT2_TEST( !ptr );
}

//==============================================================================
// Test reusing and deallocating on arbitrary alignment
//==============================================================================
NT2_TEST_CASE(reuse_align)
{
  using boost::simd::reuse;
  using boost::simd::is_aligned;

  char *ptr(0), *ptr2(0);
  NT2_TEST( is_aligned(ptr = static_cast<char*>(reuse(ptr,5,8)), 8) );
  for(int i=0;i<5;++i) ptr[i] = 10*i;
  for(int i=0;i<5;++i) NT2_TEST_EQUAL(ptr[i],10*i);

  NT2_TEST( is_aligned(ptr = static_cast<char*>(reuse(ptr,3,8)), 8) );
  for(int i=0;i<3;++i) ptr[i] = 10*i;
  for(int i=0;i<3;++i) NT2_TEST_EQUAL(ptr[i],10*i);

  NT2_TEST( is_aligned(ptr2 = static_cast<char*>(reuse(ptr,2,16)), 16) );
  for(int i=0;i<2;++i) ptr2[i] = 10*i;
  for(int i=0;i<2;++i) NT2_TEST_EQUAL(ptr2[i],10*i);

  NT2_TEST( is_aligned(ptr = static_cast<char*>(reuse(ptr2,7,8)), 8) );
  for(int i=0;i<7;++i) ptr[i] = 10*i;
  for(int i=0;i<7;++i) NT2_TEST_EQUAL(ptr[i],10*i);

  ptr = static_cast<char*>(reuse(ptr,0,8));
  NT2_TEST( !ptr || (::free(ptr), true) );
}

//==============================================================================
// Test reusing and deallocating on arbitrary alignment
//==============================================================================
NT2_TEST_CASE(reuse_align_allocator)
{
  using std::allocator;
  using boost::simd::reuse;
  using boost::simd::is_aligned;

  allocator<char> alloc;

  char *ptr(0), *ptr2(0);
  NT2_TEST( is_aligned(ptr = static_cast<char*>(reuse(alloc,ptr,5,8)), 8) );
  for(int i=0;i<5;++i) ptr[i] = 10*i;
  for(int i=0;i<5;++i) NT2_TEST_EQUAL(ptr[i],10*i);

  NT2_TEST( is_aligned(ptr = static_cast<char*>(reuse(alloc,ptr,3,8)), 8) );
  for(int i=0;i<3;++i) ptr[i] = 10*i;
  for(int i=0;i<3;++i) NT2_TEST_EQUAL(ptr[i],10*i);

  NT2_TEST( is_aligned(ptr2 = static_cast<char*>(reuse(alloc,ptr,2,16)), 16) );
  for(int i=0;i<2;++i) ptr2[i] = 10*i;
  for(int i=0;i<2;++i) NT2_TEST_EQUAL(ptr2[i],10*i);

  NT2_TEST( is_aligned(ptr = static_cast<char*>(reuse(alloc,ptr2,7,8)), 8) );
  for(int i=0;i<7;++i) ptr[i] = 10*i;
  for(int i=0;i<7;++i) NT2_TEST_EQUAL(ptr[i],10*i);

  ptr = static_cast<char*>(reuse(alloc,ptr,0,8));
  NT2_TEST( !ptr );
}
