//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2::memory boost::array adaptation as a Buffer"

#include <nt2/sdk/memory/array_buffer.hpp>

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
// Test for default array_buffer ctor
//==============================================================================
NT2_TEST_CASE_TPL( array_buffer_default_ctor, NT2_TYPES)
{
  using nt2::memory::array_buffer;

  array_buffer<T, boost::mpl::size_t<2> > b;

  NT2_TEST_EQUAL(b.size()       , 2 );
  NT2_TEST_EQUAL(b.raw(),&b[0]);
}

//==============================================================================
// Test for dynamic array_buffer copy ctor
//==============================================================================
NT2_TEST_CASE_TPL( array_buffer_data_ctor, NT2_TYPES)
{
  using nt2::memory::array_buffer;

  array_buffer<T, boost::mpl::size_t<5> > b;

  for ( std::ptrdiff_t i = 0; i < 5; ++i ) b[i] = T(3+i);

  array_buffer<T, boost::mpl::size_t<5> > x(b);

  NT2_TEST_EQUAL(x.size() , 5     );
  NT2_TEST_EQUAL(x.raw()  , &x[0] );

  for ( std::ptrdiff_t i = 0; i < 5; ++i ) NT2_TEST_EQUAL( x[i], T(3+i) );
}

//==============================================================================
// Test for array_buffer assignment
//==============================================================================
NT2_TEST_CASE_TPL(array_buffer_assignment, NT2_TYPES )
{
  using nt2::memory::array_buffer;

  array_buffer<T, boost::mpl::size_t<5> > b;

  for ( std::ptrdiff_t i = 0; i < 5; ++i ) b[i] = T(3+i);

  array_buffer<T, boost::mpl::size_t<5> > x;
  x = b;

  NT2_TEST_EQUAL(x.size() , 5     );
  NT2_TEST_EQUAL(x.raw()  , &x[0] );

  for ( std::ptrdiff_t i = 0; i < 5; ++i ) NT2_TEST_EQUAL( x[i], T(3+i) );
}

//==============================================================================
// Test for array_buffer swap
//==============================================================================
NT2_TEST_CASE_TPL(array_buffer_swap, NT2_TYPES )
{
  using nt2::memory::array_buffer;

  array_buffer<T, boost::mpl::size_t<5> > b,x;

  for ( std::ptrdiff_t i = 0; i < 5; ++i ) b[i] = T(3+i);
  for ( std::ptrdiff_t i = 0; i < 5; ++i ) x[i] = T(3*(i+1));

  swap(x,b);

  NT2_TEST_EQUAL(x.size() , 5     );
  NT2_TEST_EQUAL(b.size() , 5     );
  NT2_TEST_EQUAL(x.raw()  , &x[0] );
  NT2_TEST_EQUAL(b.raw()  , &b[0] );

  for ( std::ptrdiff_t i = 0; i < 5; ++i ) NT2_TEST_EQUAL( b[i], T(3*(i+1)) );
  for ( std::ptrdiff_t i = 0; i < 5; ++i ) NT2_TEST_EQUAL( x[i], T(3+i) );
}

//==============================================================================
// array_buffer Range interface
//==============================================================================
#ifdef BOOST_MSVC
#pragma warning(disable: 4996) // unsafe std::transform
#endif

struct f_
{
  template<class T> T operator()(T const& e) const { return T(10*e); }
};

NT2_TEST_CASE_TPL(array_buffer_iterator, NT2_TYPES )
{
  using nt2::memory::array_buffer;

  array_buffer<T, boost::mpl::size_t<5> > x;
  for ( std::ptrdiff_t i = 0; i < 5; ++i ) x[i] = T(3+i);

  f_ f;

  typename array_buffer<T, boost::mpl::size_t<5> >::iterator b = x.begin();
  typename array_buffer<T, boost::mpl::size_t<5> >::iterator e = x.end();

  std::transform(b,e,b,f);

  for ( std::ptrdiff_t i = 0; i < 5; ++i )  NT2_TEST_EQUAL( x[i], f(T(3+i)) );
}
