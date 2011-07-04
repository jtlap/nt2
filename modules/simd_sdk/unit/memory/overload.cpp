/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 0x01.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::memory based aligned new/delete overload"

#include <nt2/sdk/memory/overload.hpp>
#include <nt2/sdk/memory/is_aligned.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

class foo
{
  public:
  NT2_MEMORY_OVERLOAD_NEW_DELETE(foo)

  int  member;
};

////////////////////////////////////////////////////////////////////////////////
// Test foo allocation using the aligned new/delete
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(overload_new_delete)
{
  using nt2::memory::is_aligned;

  foo* ptr = new foo;

  NT2_TEST( is_aligned(ptr) );
  ptr->member = 42;
  NT2_TEST_EQUAL( ptr->member, 42 );
  delete ptr;
}

////////////////////////////////////////////////////////////////////////////////
// Test foo allocation using the aligned new/delete
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(overload_new_delete_array)
{
  using nt2::memory::is_aligned;

  foo* ptr = new foo[5];

  NT2_TEST( is_aligned(ptr) );

  for(int i=0;i<5;++i) ptr[i].member = 10*i;
  for(int i=0;i<5;++i) NT2_TEST_EQUAL( ptr[i].member, 10*i );

  delete[] ptr;
}

