//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2::memory padded_allocator"

#include <nt2/sdk/memory/buffer.hpp>
#include <nt2/sdk/memory/padded_allocator.hpp>

#include <boost/mpl/int.hpp>
#include <boost/fusion/include/make_vector.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>

NT2_TEST_CASE_TPL(padded_allocator, NT2_TYPES )
{
  using std::allocator;
  using nt2::memory::buffer;
  using nt2::memory::padded_allocator;

  typedef padded_allocator< 16, std::allocator<T> > alloc_t;
  buffer<T, 1, alloc_t > v( 5 );

  for( std::ptrdiff_t i=v.lower(); i<=v.upper(); ++i )
    v(i) = T(1+10*i);

  for( std::ptrdiff_t i=v.lower(); i<=v.upper(); ++i )
    NT2_TEST_EQUAL( v(i), T(1+10*i) );
}

NT2_TEST_CASE_TPL(padded_allocator_copy, NT2_TYPES )
{
  using std::allocator;
  using boost::mpl::int_;
  using nt2::memory::buffer;
  using nt2::memory::padded_allocator;

  typedef padded_allocator< 32, std::allocator<T> > alloc_t;
  buffer<T, 1, alloc_t > v( 5 );

  for( std::ptrdiff_t i=v.lower(); i<=v.upper(); ++i )
    v(i) = T(1+10*i);

  buffer<T, 1, alloc_t > w(v);

  for( std::ptrdiff_t i=w.lower(); i<=w.upper(); ++i )
    NT2_TEST_EQUAL( w(i), T(1+10*i) );
}
