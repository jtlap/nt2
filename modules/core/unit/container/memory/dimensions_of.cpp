/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::memory dimensions_of"

#include <nt2/core/container/meta/dimensions_of.hpp>
#include <nt2/core/container/memory/adapted/array.hpp>
#include <nt2/core/container/memory/adapted/vector.hpp>
#include <nt2/core/container/memory/iliffe_buffer.hpp>
#include <nt2/core/container/memory/buffer.hpp>
#include <nt2/sdk/memory/allocator.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

////////////////////////////////////////////////////////////////////////////////
// Random type has 0 dimensions
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( not_a_buffer )
{
  using nt2::meta::dimensions_of;

  NT2_TEST_EQUAL( dimensions_of<int>::value, 0UL );
  NT2_TEST_EQUAL( dimensions_of<long&>::value, 0UL );
  NT2_TEST_EQUAL( dimensions_of<float const&>::value, 0UL );
}

////////////////////////////////////////////////////////////////////////////////
// array type has some dimensions
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( std_array_buffer )
{
  using nt2::meta::dimensions_of;
  using boost::array;

  NT2_TEST_EQUAL((dimensions_of< array<int,4> >::value), 1UL );
  NT2_TEST_EQUAL((dimensions_of< array<array<int,4>,4> >::value), 2UL );
  NT2_TEST_EQUAL((dimensions_of< array<array<array<int,4>,4>,4> >::value), 3UL);
}

////////////////////////////////////////////////////////////////////////////////
// vector type has some dimensions
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( std_vector_buffer )
{
  using nt2::meta::dimensions_of;
  using std::vector;

  NT2_TEST_EQUAL((dimensions_of< vector<int> >::value), 1UL );
  NT2_TEST_EQUAL((dimensions_of< vector<vector<int> > >::value), 2UL );
  NT2_TEST_EQUAL((dimensions_of< vector<vector<vector<int> > > >::value), 3UL);
}

////////////////////////////////////////////////////////////////////////////////
// iliffe_buffer type has some dimensions
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( iliffe_buffer )
{
  using nt2::meta::dimensions_of;
  using nt2::memory::iliffe_buffer;
  using nt2::memory::no_padding;
  using nt2::memory::allocator;
  using nt2::memory::buffer;
  using nt2::memory::byte;

  NT2_TEST_EQUAL((dimensions_of< iliffe_buffer<1,int,buffer<int>,buffer<byte>,no_padding,allocator<int> > >::value), 1UL );
  NT2_TEST_EQUAL((dimensions_of< iliffe_buffer<2,int,buffer<int>,buffer<byte>,no_padding,allocator<int> > >::value), 2UL );
  NT2_TEST_EQUAL((dimensions_of< iliffe_buffer<3,int,buffer<int>,buffer<byte>,no_padding,allocator<int> > >::value), 3UL );
}
