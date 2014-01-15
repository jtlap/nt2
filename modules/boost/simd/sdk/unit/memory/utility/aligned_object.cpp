//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/memory/aligned_object.hpp>
#include <boost/simd/memory/is_aligned.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

class foo : public boost::simd::aligned_object<16>
{
  public:
  int  member;
};

////////////////////////////////////////////////////////////////////////////////
// Test foo allocation using the aligned new/delete
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(overload_new_delete)
{
  using boost::simd::is_aligned;

  foo* ptr = new foo;

  NT2_TEST( is_aligned(ptr,16) );
  ptr->member = 42;
  NT2_TEST_EQUAL( ptr->member, 42 );
  delete ptr;
}

////////////////////////////////////////////////////////////////////////////////
// Test foo allocation using the aligned new/delete
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(overload_new_delete_array)
{
  using boost::simd::is_aligned;

  foo* ptr = new foo[5];

  NT2_TEST( is_aligned(ptr,16) );

  for(int i=0;i<5;++i) ptr[i].member = 10*i;
  for(int i=0;i<5;++i) NT2_TEST_EQUAL( ptr[i].member, 10*i );

  delete[] ptr;
}

// Clang bug, doesn't deal properly with alignment in empty base classes
// http://llvm.org/bugs/show_bug.cgi?id=14564
// fixed in clang 3.4
#if !defined(__clang__) || (__clang_major__ >= 3 && __clang_minor__ >= 4)
NT2_TEST_CASE(static_alignment)
{
  using boost::simd::is_aligned;

  foo f;

  NT2_TEST_GREATER_EQUAL(sizeof(foo), 16u);
  NT2_TEST( is_aligned(&f, 16) );
}
#endif
