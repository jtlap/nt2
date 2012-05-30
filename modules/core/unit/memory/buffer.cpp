//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2::memory buffer"

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

//==============================================================================
// Test for default buffer ctor
//==============================================================================
NT2_TEST_CASE_TPL( buffer_default_ctor, NT2_TYPES)
{
  using nt2::memory::buffer;

  buffer<T> b;

  NT2_TEST(b.empty());
  NT2_TEST_EQUAL(b.size()     , 0u      );
  NT2_TEST_EQUAL(b.capacity() , 0u      );
  NT2_TEST_EQUAL(b.begin()    , b.end() );
  NT2_TEST_EQUAL(b.raw()      , (T*)(0) );
}

//==============================================================================
// Test for size buffer ctor
//==============================================================================
NT2_TEST_CASE_TPL( buffer_size_ctor, NT2_TYPES)
{
  using nt2::memory::buffer;

  buffer<T> b(5);

  NT2_TEST(!b.empty());
  NT2_TEST_EQUAL(b.size()     , 5u    );
  NT2_TEST_EQUAL(b.capacity() , 5u    );
  NT2_TEST_EQUAL(b.raw()      , &b[0] );

  for ( std::ptrdiff_t i = 0; i < 5; ++i ) b[i] = T(3+i);
  for ( std::ptrdiff_t i = 0; i < 5; ++i ) NT2_TEST_EQUAL( b[i], T(3+i) );
}

//==============================================================================
// Test for dynamic buffer copy ctor
//==============================================================================
NT2_TEST_CASE_TPL( buffer_data_ctor, NT2_TYPES)
{
  using nt2::memory::buffer;

  buffer<T> b(5);

  for ( std::ptrdiff_t i = 0; i < 5; ++i ) b[i] = T(3+i);

  buffer<T>  x(b);

  NT2_TEST(!x.empty());
  NT2_TEST_EQUAL(x.size()     , 5u    );
  NT2_TEST_EQUAL(x.capacity() , 5u    );
  NT2_TEST_EQUAL(x.raw()      , &x[0] );

  for ( std::ptrdiff_t i = 0; i < 5; ++i ) NT2_TEST_EQUAL( x[i], T(3+i) );
}

//==============================================================================
// Test for buffer resize
//==============================================================================
NT2_TEST_CASE_TPL(buffer_resize, NT2_TYPES )
{
  using nt2::memory::buffer;

  buffer<T> b(5);

  for ( std::ptrdiff_t i = 0; i < 5; ++i ) b[i] = T(3+i);

  b.resize(3);
  NT2_TEST(!b.empty());
  NT2_TEST_EQUAL(b.size()     , 3u    );
  NT2_TEST_EQUAL(b.capacity() , 5u    );
  NT2_TEST_EQUAL(b.raw()      , &b[0] );

  for ( std::ptrdiff_t i = 0; i < 3; ++i ) NT2_TEST_EQUAL( b[i], T(3+i) );

  b.resize(5);
  NT2_TEST(!b.empty());
  NT2_TEST_EQUAL(b.size()     , 5u    );
  NT2_TEST_EQUAL(b.capacity() , 5u    );
  NT2_TEST_EQUAL(b.raw()      , &b[0] );

  for ( std::ptrdiff_t i = 0; i < 5; ++i ) NT2_TEST_EQUAL( b[i], T(3+i) );

  b.resize(9);
  NT2_TEST(!b.empty());
  NT2_TEST_EQUAL(b.size()     , 9u    );
  NT2_TEST_EQUAL(b.capacity() , 9u    );
  NT2_TEST_EQUAL(b.raw()      , &b[0] );

  for ( std::ptrdiff_t i = 0; i < 9; ++i ) b[i] = T(4*(i+1));
  for ( std::ptrdiff_t i = 0; i < 9; ++i ) NT2_TEST_EQUAL( b[i], T(4*(i+1)) );

  b.resize(1);
  NT2_TEST(!b.empty());
  NT2_TEST_EQUAL(b.size()     , 1u    );
  NT2_TEST_EQUAL(b.capacity() , 9u    );
  NT2_TEST_EQUAL(b.raw()      , &b[0] );

  for ( std::ptrdiff_t i = 0; i < 1; ++i ) NT2_TEST_EQUAL( b[i], T(4*(i+1)) );
}

//==============================================================================
// Test for buffer assignment
//==============================================================================
NT2_TEST_CASE_TPL(buffer_assignment, NT2_TYPES )
{
  using nt2::memory::buffer;

  buffer<T> b(5);;

  for ( std::ptrdiff_t i = 0; i < 5; ++i ) b[i] = T(3+i);

  buffer<T> x;
  x = b;

  NT2_TEST(!x.empty());
  NT2_TEST_EQUAL(x.size()     , 5u    );
  NT2_TEST_EQUAL(x.capacity() , 5u    );
  NT2_TEST_EQUAL(x.raw()      , &x[0] );

  for ( std::ptrdiff_t i = 0; i < 5; ++i ) NT2_TEST_EQUAL( x[i], T(3+i) );
}

//==============================================================================
// Test for buffer swap
//==============================================================================
NT2_TEST_CASE_TPL(buffer_swap, NT2_TYPES )
{
  using nt2::memory::buffer;

  buffer<T> b(5);
  buffer<T> x(7);

  for ( std::ptrdiff_t i = 0; i < 5; ++i ) b[i] = T(3+i);
  for ( std::ptrdiff_t i = 0; i < 7; ++i ) x[i] = T(3*(i+1));

  swap(x,b);

  NT2_TEST(!x.empty());
  NT2_TEST_EQUAL(x.size()     , 5u    );
  NT2_TEST_EQUAL(x.capacity() , 5u    );
  NT2_TEST_EQUAL(x.raw()      , &x[0] );

  NT2_TEST(!b.empty());
  NT2_TEST_EQUAL(b.size()     , 7u    );
  NT2_TEST_EQUAL(b.capacity() , 7u    );
  NT2_TEST_EQUAL(b.raw()      , &b[0] );

  for ( std::ptrdiff_t i = 0; i < 7; ++i ) NT2_TEST_EQUAL( b[i], T(3*(i+1)) );
  for ( std::ptrdiff_t i = 0; i < 5; ++i ) NT2_TEST_EQUAL( x[i], T(3+i) );
}

//==============================================================================
// buffer Range interface
//==============================================================================
#ifdef BOOST_MSVC
#pragma warning(disable: 4996) // unsafe std::transform
#endif

struct f_
{
  template<class T> T operator()(T const& e) const { return T(10*e); }
};

NT2_TEST_CASE_TPL(buffer_iterator, NT2_TYPES )
{
  using nt2::memory::buffer;

  buffer<T> x(5);
  for ( std::ptrdiff_t i = 0; i < 5; ++i ) x[i] = T(3+i);

  f_ f;

  typename buffer<T>::iterator b = x.begin();
  typename buffer<T>::iterator e = x.end();

  std::transform(b,e,b,f);

  for ( std::ptrdiff_t i = 0; i < 5; ++i )  NT2_TEST_EQUAL( x[i], f(T(3+i)) );
}
