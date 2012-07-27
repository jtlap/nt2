//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2::memory boost::array adaptation as a Buffer"

#ifdef _MSC_VER
#pragma warning(disable: 4996) // unsafe std::transform
#endif

#include <nt2/sdk/memory/array_buffer.hpp>

#include <string>
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
// Test for default array_buffer ctor
//==============================================================================
NT2_TEST_CASE( array_buffer_default_ctor )
{
  using nt2::memory::array_buffer;

  array_buffer<nt2::object, boost::mpl::size_t<2> > b;

  NT2_TEST_EQUAL(b.size(), 2u );
  NT2_TEST_EQUAL(b.raw(),&b[0]);

  for(std::size_t i=0;i<b.size();++i)
  {
    NT2_TEST_EQUAL(b[i].s, std::string("default") );
  }
}

//==============================================================================
// Test for dynamic array_buffer copy ctor
//==============================================================================
NT2_TEST_CASE( array_buffer_data_ctor )
{
  using nt2::memory::array_buffer;

  array_buffer<nt2::object, boost::mpl::size_t<5> > b;

  for(std::size_t i=0;i<b.size();++i)
    NT2_TEST_EQUAL(b[i].s, std::string("default") );

  array_buffer<nt2::object, boost::mpl::size_t<5> > x(b);
  NT2_TEST_EQUAL(x.size() , 5u     );
  NT2_TEST_EQUAL(x.raw()  , &x[0] );

  for( std::size_t i = 0; i < 5; ++i )
    NT2_TEST_EQUAL(x[i].s, std::string("copied") );
}

//==============================================================================
// Test for array_buffer assignment
//==============================================================================
NT2_TEST_CASE(array_buffer_assignment )
{
  using nt2::memory::array_buffer;

  array_buffer<nt2::object, boost::mpl::size_t<5> > b;
  for(std::size_t i=0;i<b.size();++i)
    NT2_TEST_EQUAL(b[i].s, std::string("default") );

  array_buffer<nt2::object, boost::mpl::size_t<5> > x;
  x = b;

  NT2_TEST_EQUAL(x.size() , 5u     );
  NT2_TEST_EQUAL(x.raw()  , &x[0] );

  for(std::size_t i=0;i<b.size();++i)
    NT2_TEST_EQUAL(x[i].s, std::string("assigned") );
}

//==============================================================================
// Test for array_buffer swap
//==============================================================================
NT2_TEST_CASE(array_buffer_swap)
{
  using nt2::memory::array_buffer;

  array_buffer<nt2::object, boost::mpl::size_t<5> > b,x;
  for(std::size_t i=0;i<b.size();++i)
  {
    NT2_TEST_EQUAL(b[i].s, std::string("default") );
    NT2_TEST_EQUAL(x[i].s, std::string("default") );
  }

  swap(x,b);

  NT2_TEST_EQUAL(x.size() , 5u    );
  NT2_TEST_EQUAL(b.size() , 5u    );
  NT2_TEST_EQUAL(x.raw()  , &x[0] );
  NT2_TEST_EQUAL(b.raw()  , &b[0] );

  for( std::size_t i = 0; i < 5; ++i )
  {
    NT2_TEST_EQUAL(b[i].s, std::string("right swapped") );
    NT2_TEST_EQUAL(x[i].s, std::string("left swapped") );
  }

  swap(b,x);

  for( std::size_t i = 0; i < 5; ++i )
  {
    NT2_TEST_EQUAL(x[i].s, std::string("right swapped") );
    NT2_TEST_EQUAL(b[i].s, std::string("left swapped") );
  }
}

//==============================================================================
// array_buffer Range interface
//==============================================================================
struct f_
{
  template<class T> std::string operator()(T const&) const
  {
    return "transformed";
  }
};

NT2_TEST_CASE(array_buffer_iterator)
{
  using nt2::memory::array_buffer;

  array_buffer<nt2::object, boost::mpl::size_t<5> > x;
  for(std::size_t i=0;i<x.size();++i)
    NT2_TEST_EQUAL(x[i].s, std::string("default") );

  f_ f;

  array_buffer<nt2::object, boost::mpl::size_t<5> >::iterator b = x.begin();
  array_buffer<nt2::object, boost::mpl::size_t<5> >::iterator e = x.end();

  std::transform(b,e,b,f);

  for(std::size_t i=0;i<x.size();++i)
    NT2_TEST_EQUAL(x[i].s, std::string("transformed") );
}
