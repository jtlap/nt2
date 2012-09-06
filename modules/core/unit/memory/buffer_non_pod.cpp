//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2::memory buffer of non-pod types"

#ifdef _MSC_VER
#pragma warning(disable: 4996) // unsafe std::transform
#endif

#include <nt2/sdk/memory/buffer.hpp>

#include <algorithm>
#include <boost/array.hpp>
#include <boost/fusion/adapted/array.hpp>
#include <boost/fusion/include/vector_tie.hpp>
#include <boost/fusion/include/make_vector.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>

#include "object.hpp"

//==============================================================================
// Test for default buffer ctor
//==============================================================================
NT2_TEST_CASE( buffer_default_ctor )
{
  using nt2::memory::buffer;

  buffer<nt2::object> b;

  NT2_TEST(b.empty());
  NT2_TEST_EQUAL(b.size()     , 0u      );
  NT2_TEST_EQUAL(b.capacity() , 0u      );
  NT2_TEST_EQUAL(b.begin()    , b.end() );
  NT2_TEST_EQUAL(b.raw()      , (nt2::object*)(0) );
}

//==============================================================================
// Test for size buffer ctor
//==============================================================================
NT2_TEST_CASE( buffer_size_ctor )
{
  using nt2::memory::buffer;

  buffer<nt2::object> b(5);

  NT2_TEST(!b.empty());
  NT2_TEST_EQUAL(b.size()     , 5u    );
  NT2_TEST_EQUAL(b.capacity() , 5u    );
  NT2_TEST_EQUAL(b.raw()      , &b[0] );

  for ( std::size_t i = 0; i < 5; ++i )
    NT2_TEST_EQUAL( b[i].s, std::string("default") );
}

//==============================================================================
// Test for dynamic buffer copy ctor
//==============================================================================
NT2_TEST_CASE( buffer_copy_ctor )
{
  using nt2::memory::buffer;

  buffer<nt2::object>  b(5);
  buffer<nt2::object>       x(b);

  NT2_TEST(!x.empty());
  NT2_TEST_EQUAL(x.size()     , 5u    );
  NT2_TEST_EQUAL(x.capacity() , 5u    );
  NT2_TEST_EQUAL(x.raw()      , &x[0] );

  for( std::size_t i = 0; i < 5; ++i )
    NT2_TEST_EQUAL( x[i].s, std::string("copied") );
}

//==============================================================================
// Test for buffer resize
//==============================================================================
NT2_TEST_CASE( buffer_resize )
{
  using nt2::memory::buffer;

  buffer<nt2::object> b(5);

  b.resize(9);
  NT2_TEST(!b.empty());
  NT2_TEST_EQUAL(b.size()     , 9u    );
  NT2_TEST_EQUAL(b.capacity() , 9u    );
  NT2_TEST_EQUAL(b.raw()      , &b[0] );

  for( std::size_t i = 0; i < 9; ++i )
    NT2_TEST_EQUAL( b[i].s, std::string("default") );

  b.resize(3);
  NT2_TEST(!b.empty());
  NT2_TEST_EQUAL(b.size()     , 3u    );
  NT2_TEST_EQUAL(b.capacity() , 9u    );
  NT2_TEST_EQUAL(b.raw()      , &b[0] );

  for( std::size_t i = 0; i < 3; ++i )
    NT2_TEST_EQUAL( b[i].s, std::string("default") );

  b.resize(5);
  NT2_TEST(!b.empty());
  NT2_TEST_EQUAL(b.size()     , 5u    );
  NT2_TEST_EQUAL(b.capacity() , 9u    );
  NT2_TEST_EQUAL(b.raw()      , &b[0] );

  for( std::size_t i = 0; i < 5; ++i )
    NT2_TEST_EQUAL( b[i].s, std::string("default") );

  b.resize(1);
  NT2_TEST(!b.empty());
  NT2_TEST_EQUAL(b.size()     , 1u    );
  NT2_TEST_EQUAL(b.capacity() , 9u    );
  NT2_TEST_EQUAL(b.raw()      , &b[0] );

  for( std::size_t i = 0; i < 1; ++i )
    NT2_TEST_EQUAL( b[i].s, std::string("default") );
}

//==============================================================================
// Test for buffer assignment
//==============================================================================
NT2_TEST_CASE( buffer_assignment )
{
  using nt2::memory::buffer;

  buffer<nt2::object> b(5);
  buffer<nt2::object> x;

  x = b;

  NT2_TEST(!x.empty());
  NT2_TEST_EQUAL(x.size()     , 5u    );
  NT2_TEST_EQUAL(x.capacity() , 5u    );
  NT2_TEST_EQUAL(x.raw()      , &x[0] );

  for( std::size_t i = 0; i < 5; ++i )
    NT2_TEST_EQUAL( x[i].s, std::string("assigned") );
}

//==============================================================================
// Test for buffer swap
//==============================================================================
NT2_TEST_CASE( buffer_swap )
{
  using nt2::memory::buffer;

  buffer<nt2::object> b(5);
  buffer<nt2::object> x(7);

  swap(x,b);

  NT2_TEST(!x.empty());
  NT2_TEST_EQUAL(x.size()     , 5u    );
  NT2_TEST_EQUAL(x.capacity() , 5u    );
  NT2_TEST_EQUAL(x.raw()      , &x[0] );

  NT2_TEST(!b.empty());
  NT2_TEST_EQUAL(b.size()     , 7u    );
  NT2_TEST_EQUAL(b.capacity() , 7u    );
  NT2_TEST_EQUAL(b.raw()      , &b[0] );

  for( std::size_t i = 0; i < 5; ++i )
    NT2_TEST_EQUAL( x[i].s, std::string("default") );

  for( std::size_t i = 0; i < 7; ++i )
    NT2_TEST_EQUAL( b[i].s, std::string("default") );

  swap(b,x);

  NT2_TEST(!x.empty());
  NT2_TEST_EQUAL(x.size()     , 7u    );
  NT2_TEST_EQUAL(x.capacity() , 7u    );
  NT2_TEST_EQUAL(x.raw()      , &x[0] );

  NT2_TEST(!b.empty());
  NT2_TEST_EQUAL(b.size()     , 5u    );
  NT2_TEST_EQUAL(b.capacity() , 5u    );
  NT2_TEST_EQUAL(b.raw()      , &b[0] );

  for( std::size_t i = 0; i < 7; ++i )
    NT2_TEST_EQUAL( x[i].s, std::string("default") );

  for( std::size_t i = 0; i < 5; ++i )
    NT2_TEST_EQUAL( b[i].s, std::string("default") );
}

//==============================================================================
// buffer Range interface
//==============================================================================
struct f_
{
  template<class T> std::string operator()(T const&) const
  {
    return "transformed";
  }
};

NT2_TEST_CASE( buffer_iterator )
{
  using nt2::memory::buffer;

  buffer<nt2::object> x(5);

  f_ f;

  buffer<nt2::object>::iterator b = x.begin();
  buffer<nt2::object>::iterator e = x.end();

  std::transform(b,e,b,f);

  for ( std::size_t i = 0; i < 5; ++i )
    NT2_TEST_EQUAL( x[i].s, std::string("transformed") );
}

NT2_TEST_CASE(buffer_push_back )
{
  using nt2::memory::buffer;

  buffer<nt2::object> x(5);
  for ( std::ptrdiff_t i = 0; i < 5; ++i ) x[i] = nt2::object("foo");
  for ( std::ptrdiff_t i = 0; i < 7; ++i ) x.push_back("bar");

  NT2_TEST_EQUAL( x.size(), (std::size_t)5+7 );
  std::ptrdiff_t i = 0;
  for ( ; i < 5; ++i ) NT2_TEST_EQUAL( x[i].s, std::string("copied") );
  for ( ; i < 5+7; ++i ) NT2_TEST_EQUAL( x[i].s, std::string("copied") );

  std::cout << "capacity = " << x.capacity() << std::endl;
}

NT2_TEST_CASE(buffer_push_back_def )
{
  using nt2::memory::buffer;

  buffer<nt2::object> x;
  for ( std::ptrdiff_t i = 0; i < 7; ++i ) x.push_back("bar");

  NT2_TEST_EQUAL( x.size(), (std::size_t)7 );
  std::ptrdiff_t i = 0;
  for ( ; i < 7; ++i ) NT2_TEST_EQUAL( x[i].s, std::string("copied") );

  std::cout << "capacity = " << x.capacity() << std::endl;
}
