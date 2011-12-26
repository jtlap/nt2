//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2::memory fixed_allocator"

#include <nt2/sdk/memory/buffer.hpp>
#include <nt2/sdk/memory/fixed_allocator.hpp>

#include <boost/array.hpp>
#include <boost/fusion/adapted/array.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>

NT2_TEST_CASE_TPL(fixed_allocator, NT2_TYPES )
{
  using nt2::memory::buffer;
  using nt2::memory::fixed_allocator;

  T data[] = { 1, 2, 3, 4, 5 };

  fixed_allocator<T> a(&data[0], &data[0] + 5);
  buffer<T, -2 ,fixed_allocator<T> > v( 5, a );

  for( std::ptrdiff_t i=v.lower(); i<=v.upper(); ++i )
    NT2_TEST_EQUAL( v[i], data[i - v.lower()] );

  for( std::ptrdiff_t i=v.lower(); i<=v.upper(); ++i )
    v[i] = 1+10*(i-v.lower());

  for( std::size_t i=0; i<5; ++i )
    NT2_TEST_EQUAL( data[i], 1+10*i );
}

NT2_TEST_CASE_TPL(fixed_allocator_copy, NT2_TYPES )
{
  using nt2::memory::buffer;
  using nt2::memory::fixed_allocator;

  T data[] = { 1, 2, 3, 4, 5 };

  fixed_allocator<T> a(&data[0], &data[0] + 5);
  
  buffer<T, -2 ,fixed_allocator<T> > v( 5, a );
  buffer<T, -2, fixed_allocator<T> > w(v);

  for( std::ptrdiff_t i=w.lower(); i<=w.upper(); ++i )
    NT2_TEST_EQUAL( w[i], data[i - w.lower()] );

  for( std::ptrdiff_t i=v.lower(); i<=v.upper(); ++i )
    v[i] = 1+10*(i-v.lower());

  for( std::size_t i=0; i<5; ++i )
    NT2_TEST_EQUAL( data[i], 1+10*i );

  for( std::ptrdiff_t i=w.lower(); i<=w.upper(); ++i )
    NT2_TEST_EQUAL( w[i], v[i] );
}

NT2_TEST_CASE_TPL(fixed_allocator_resize, NT2_TYPES )
{
  using nt2::memory::buffer;
  using nt2::memory::fixed_allocator;

  T data[] = { 1, 2, 3, 4, 5 };

  fixed_allocator<T> a(&data[0], &data[0] + 5);
  buffer<T, -2 ,fixed_allocator<T> > v( 5, a );
  
  boost::array<std::size_t,1> less_s = { 3 };

  v.resize( 3 );

  for( std::ptrdiff_t i=v.lower(); i<=v.upper(); ++i )
    NT2_TEST_EQUAL( v[i], data[i - v.lower()] );  

  v.resize( 5 );

  for( std::ptrdiff_t i=v.lower(); i<=v.upper(); ++i )
    NT2_TEST_EQUAL( v[i], data[i - v.lower()] );  

  NT2_TEST_THROW( v.resize(7), nt2::assert_exception );
}
