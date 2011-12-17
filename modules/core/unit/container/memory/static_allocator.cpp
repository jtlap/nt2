//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2::memory static_allocator"

#include <nt2/core/container/memory/buffer.hpp>
#include <nt2/core/container/memory/static_allocator.hpp>

#include <boost/array.hpp>
#include <boost/mpl/int.hpp>
#include <boost/fusion/adapted/array.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>

NT2_TEST_CASE_TPL(static_allocator, NT2_TYPES )
{
  using boost::mpl::int_;
  using nt2::memory::buffer;
  using nt2::memory::static_allocator;

  boost::array<std::size_t,1> ss = { 5  };
  boost::array<std::size_t,1> bs = { -2 };

  static_allocator<T, int_<5> > a;
  buffer<T, static_allocator<T, int_<5> > > v( ss, bs, a );

  for( std::ptrdiff_t i=v.lower(); i<=v.upper(); ++i )
    v[i] = 10*(i - v.lower());

  for( std::ptrdiff_t i=v.lower(); i<=v.upper(); ++i )
    NT2_TEST_EQUAL( v[i], 10*(i - v.lower()) );
}

NT2_TEST_CASE_TPL(static_allocator_copy, NT2_TYPES )
{
  using boost::mpl::int_;
  using nt2::memory::buffer;
  using nt2::memory::static_allocator;

  boost::array<std::size_t,1> ss = { 5  };
  boost::array<std::size_t,1> bs = { -2 };

  static_allocator<T, int_<5> > a;
  buffer<T, static_allocator<T, int_<5> > > v( ss, bs, a );

  for( std::ptrdiff_t i=v.lower(); i<=v.upper(); ++i )
    v[i] = 10*(i - v.lower());

  buffer<T, static_allocator<T, int_<5> > > w(v);

  for( std::ptrdiff_t i=w.lower(); i<=w.upper(); ++i )
    NT2_TEST_EQUAL( w[i], v[i] );

  for( std::ptrdiff_t i=w.lower(); i<=w.upper(); ++i )
    w[i] = i - w.lower();

  for( std::ptrdiff_t i=w.lower(); i<=w.upper(); ++i )
    NT2_TEST_EQUAL( w[i], i - w.lower() );

  for( std::ptrdiff_t i=v.lower(); i<=v.upper(); ++i )
    NT2_TEST_EQUAL( v[i], 10*(i - v.lower()) );
}

NT2_TEST_CASE_TPL(static_allocator_resize, NT2_TYPES )
{
  using boost::mpl::int_;
  using nt2::memory::buffer;
  using nt2::memory::static_allocator;

  boost::array<std::size_t,1> ss = { 5  };
  boost::array<std::size_t,1> bs = { -2 };

  static_allocator<T, int_<5> > a;
  buffer<T, static_allocator<T, int_<5> > > v( ss, bs, a );
  
  boost::array<std::size_t,1> less_s = { 3 };
  v.resize( less_s );
  NT2_TEST_EQUAL( v.size(), 3u );

  v.resize( ss );
  NT2_TEST_EQUAL( v.size(), 5u );

  boost::array<std::size_t,1> more_s = { 7 };
  NT2_TEST_THROW( v.resize(more_s), nt2::assert_exception );
  NT2_TEST_EQUAL( v.size(), 5u );
}
