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

  std::allocator<T> sa;
  typedef padded_allocator< std::allocator<T> > alloc_t;
  alloc_t a(16,sa);
  buffer<T, 1, alloc_t > v( boost::fusion::make_vector(5), a );

  for( std::ptrdiff_t i=v.lower(); i<=v.upper(); ++i )
    v[boost::fusion::make_vector(i)] = T(1+10*i);

  for( std::ptrdiff_t i=v.lower(); i<=v.upper(); ++i )
    NT2_TEST_EQUAL( v[boost::fusion::make_vector(i)], T(1+10*i) );
}

NT2_TEST_CASE_TPL(padded_allocator_copy, NT2_TYPES )
{
  using std::allocator;
  using boost::mpl::int_;
  using nt2::memory::buffer;
  using nt2::memory::padded_allocator;
  
  std::allocator<T> sa;
  typedef padded_allocator< std::allocator<T> > alloc_t;
  alloc_t a(32,sa);

  buffer<T, 1, alloc_t > v( boost::fusion::make_vector(5), a );

  for( std::ptrdiff_t i=v.lower(); i<=v.upper(); ++i )
    v[boost::fusion::make_vector(i)] = T(1+10*i);

  buffer<T, 1, alloc_t > w(v);

  for( std::ptrdiff_t i=w.lower(); i<=w.upper(); ++i )
    NT2_TEST_EQUAL( w[boost::fusion::make_vector(i)], T(1+10*i) );
}
