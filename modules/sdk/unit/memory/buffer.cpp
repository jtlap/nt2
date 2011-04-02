/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 0x01.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::memory::buffer"

#include <nt2/sdk/memory/buffer.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

////////////////////////////////////////////////////////////////////////////////
// Test for dynamic default buffer ctor
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL(buffer_default_ctor, NT2_TYPES )
{
  using nt2::memory::buffer;

  typedef          buffer<T>             buffer_type;
  typedef typename buffer<T>::size_type  size_type;
  const size_type s = 10;
  buffer_type b;

  NT2_TEST_EQUAL( b.size()  , 0U      );
  NT2_TEST_EQUAL( b.lower() ,  0      );
  NT2_TEST_EQUAL( b.upper() , -1      );
  NT2_TEST_EQUAL( b.begin() , (T*)(0) );

  b.resize(s);
  NT2_TEST_EQUAL( b.size()  , s       );
  NT2_TEST_EQUAL( b.lower() , 0       );
  NT2_TEST_EQUAL( b.upper() , (s-1)   );
  NT2_TEST_NOT_EQUAL( b.begin() , (T*)(0) );
  
}

////////////////////////////////////////////////////////////////////////////////
// Test for dynamic buffer ctor
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL(buffer_ctor, NT2_TYPES )
{
  using nt2::memory::buffer;

  typedef buffer<float> buffer_type;
  buffer_type b(0,5);

  NT2_TEST_EQUAL( b.size()      , 5U          );
  NT2_TEST_EQUAL( b.lower()     ,  0          );
  NT2_TEST_EQUAL( b.upper()     ,  4          );
  NT2_TEST_NOT_EQUAL( b.begin() , (float*)(0) );
  NT2_TEST_EQUAL( &b[b.lower()] , b.begin()   );

  for ( buffer_type::index_type i = b.lower(); i <= b.upper(); ++i )
    b[i] = buffer_type::value_type(1+i);

  for ( buffer_type::index_type i = b.lower(); i <= b.upper(); ++i )
    NT2_TEST_EQUAL( b[i], 1+i );
}

////////////////////////////////////////////////////////////////////////////////
// Test for dynamic buffer assignment
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL(buffer_assignment, NT2_TYPES )
{
  using nt2::memory::buffer;

  typedef buffer<float> buffer_type;
  buffer_type b,x(0,5);
  for ( buffer_type::index_type i = x.lower(); i <= x.upper(); ++i )
    x[i] = buffer_type::value_type(1+i);

  b = x;

  NT2_TEST_EQUAL( b.size()      , 5U          );
  NT2_TEST_EQUAL( b.lower()     ,  0          );
  NT2_TEST_EQUAL( b.upper()     ,  4          );
  NT2_TEST_NOT_EQUAL( b.begin() , (float*)(0) );
  NT2_TEST_EQUAL( &b[b.lower()] , b.begin()   );

  for ( buffer_type::index_type i = b.lower(); i <= b.upper(); ++i )
    NT2_TEST_EQUAL( b[i], 1+i );
}

////////////////////////////////////////////////////////////////////////////////
// Test for dynamic buffer swap
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL(buffer_swap, NT2_TYPES )
{
  using nt2::memory::buffer;

  typedef buffer<float> buffer_type;
  buffer_type b(-1,3),x(0,5);
  for ( buffer_type::index_type i = x.lower(); i <= x.upper(); ++i )
    x[i] = buffer_type::value_type(1+i);
  for ( buffer_type::index_type i = b.lower(); i <= b.upper(); ++i )
    b[i] = buffer_type::value_type(i);

  swap(b,x);

  NT2_TEST_EQUAL( b.size()      , 5U          );
  NT2_TEST_EQUAL( b.lower()     ,  0          );
  NT2_TEST_EQUAL( b.upper()     ,  4          );
  NT2_TEST_NOT_EQUAL( b.begin() , (float*)(0) );
  NT2_TEST_EQUAL( &b[b.lower()] , b.begin()   );

  NT2_TEST_EQUAL( x.size()      , 3U          );
  NT2_TEST_EQUAL( x.lower()     ,  -1         );
  NT2_TEST_EQUAL( x.upper()     ,   1         );
  NT2_TEST_NOT_EQUAL( x.begin() , (float*)(0) );
  NT2_TEST_EQUAL( &x[x.lower()] , x.begin()   );

  for ( buffer_type::index_type i = x.lower(); i <= x.upper(); ++i )
    NT2_TEST_EQUAL( x[i], i );

  for ( buffer_type::index_type i = b.lower(); i <= b.upper(); ++i )
    NT2_TEST_EQUAL( b[i], 1+i );
}
