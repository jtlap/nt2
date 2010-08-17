/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 0x01.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::memory::buffer"

#include <boost/mpl/int.hpp>
#include <nt2/sdk/memory/buffer.hpp>

#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
/*
  buffer& operator=( buffer const& src )
  operator=( Buffer const& src )

  using parent::size;
  using parent::capacity;
  using parent::lower;
  using parent::upper;

  reference operator[](difference_type const& i)
  const_reference operator[](difference_type const& i) const
  pointer origin()  const { return impl.origin_;  }
  pointer begin()   const { return impl.begin_;   }

  template<class T,class Base, class Size, class Allocator>
  void swap ( buffer<T,Base,Size,Allocator>& a
            , buffer<T,Base,Size,Allocator>& b
            );
*/
////////////////////////////////////////////////////////////////////////////////
// Test for dynamic buffer static properties
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(dynamic_buffer_static_properties)
{
  using nt2::memory::buffer;
  using nt2::memory::allocator;

  typedef buffer<float,int,int,allocator<float> > buffer_type;

  NT2_TEST( !buffer_type::is_static::value );
  NT2_TEST( !buffer_type::has_static_base::value );
  NT2_TEST( !buffer_type::has_static_size::value );
}

////////////////////////////////////////////////////////////////////////////////
// Test for dynamic buffer default ctor
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(dynamic_buffer_ctor)
{
  using nt2::memory::buffer;
  using nt2::memory::allocator;

  typedef buffer<float,int,int,allocator<float> > buffer_type;

  buffer_type b;

  NT2_TEST_EQUAL( b.size()    , 0U          );
  NT2_TEST_EQUAL( b.capacity(), 0U          );
  NT2_TEST_EQUAL( b.lower()   ,  0          );
  NT2_TEST_EQUAL( b.upper()   , -1          );
  NT2_TEST_EQUAL( b.origin()  , (float*)(0) );
  NT2_TEST_EQUAL( b.begin()   , (float*)(0) );
/*
  buffer( Allocator const& a )  : parent(a) { parent::default_init(); }
  buffer( Base const& b, Size const& s) : parent()
  buffer( Buffer const& src )
*/
}
