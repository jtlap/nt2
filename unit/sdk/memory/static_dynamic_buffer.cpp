/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 0x01.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::memory::buffer - static/dynamic mode"

#include <boost/mpl/int.hpp>
#include <nt2/sdk/memory/buffer.hpp>

#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>

////////////////////////////////////////////////////////////////////////////////
// Test for dynamic buffer static properties
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(buffer_static_properties)
{
  using nt2::memory::buffer;
  using nt2::memory::allocator;

  typedef boost::mpl::int_<1> base_;
  typedef buffer<float,base_,int,allocator<float> > buffer_type;

  NT2_TEST( !buffer_type::is_static::value );
  NT2_TEST( buffer_type::has_static_base::value );
  NT2_TEST( !buffer_type::has_static_size::value );
}

////////////////////////////////////////////////////////////////////////////////
// Test for static/dynamic buffer default ctor
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(buffer_default_ctor)
{
  using nt2::memory::buffer;
  using nt2::memory::allocator;

  typedef boost::mpl::int_<1> base_;
  typedef buffer<float,base_,int,allocator<float> > buffer_type;

  buffer_type b;

  NT2_TEST_EQUAL( b.size()    , 0U          );
  NT2_TEST_EQUAL( b.lower()   ,  0          );
  NT2_TEST_EQUAL( b.upper()   , -1          );
  NT2_TEST_EQUAL( b.origin()  , (float*)(0) );
  NT2_TEST_EQUAL( b.begin()   , (float*)(0) );
}


////////////////////////////////////////////////////////////////////////////////
// Test for dynamic buffer ctor from allocator
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(buffer_allocator_ctor)
{
  using nt2::memory::buffer;
  using nt2::memory::allocator;

  typedef boost::mpl::int_<1> base_;
  typedef buffer<float,base_,int,allocator<float> > buffer_type;

  allocator<float> a;
  buffer_type b(a);

  NT2_TEST_EQUAL( b.size()    , 0U          );
  NT2_TEST_EQUAL( b.lower()   ,  0          );
  NT2_TEST_EQUAL( b.upper()   , -1          );
  NT2_TEST_EQUAL( b.origin()  , (float*)(0) );
  NT2_TEST_EQUAL( b.begin()   , (float*)(0) );
}


////////////////////////////////////////////////////////////////////////////////
// Test for dynamic buffer ctor from base/size
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(buffer_ctor)
{
  using nt2::memory::buffer;
  using nt2::memory::align_on;
  using nt2::memory::allocator;

  typedef boost::mpl::int_<1> base_;
  typedef buffer<float,base_,int,allocator<float> > buffer_type;
  buffer_type b(base_(),5);

  NT2_TEST_EQUAL( b.size()      , 5U                  );
  NT2_TEST_EQUAL( b.lower()     , base_::value        );
  NT2_TEST_EQUAL( b.upper()     ,  5                  );
  NT2_TEST_NOT_EQUAL( b.origin(), (float*)(0)         );
  NT2_TEST_NOT_EQUAL( b.begin() , (float*)(0)         );
  NT2_TEST_EQUAL( b.origin()    , b.begin()+b.lower() );
  NT2_TEST( align_on(b.origin()) );

  for ( buffer_type::index_type i = b.lower(); i <= b.upper(); ++i )
    b[i] = 1+i;

  for ( buffer_type::index_type i = b.lower(); i <= b.upper(); ++i )
    NT2_TEST_EQUAL( b[i], 1+i );
}

////////////////////////////////////////////////////////////////////////////////
// Test for dynamic buffer assignment
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(buffer_assignment)
{
  using nt2::memory::buffer;
  using nt2::memory::align_on;
  using nt2::memory::allocator;

  typedef boost::mpl::int_<1> base_;
  typedef buffer<float,base_,int,allocator<float> > buffer_type;
  buffer_type b,x(base_(),5);

  for ( buffer_type::index_type i = x.lower(); i <= x.upper(); ++i )
    x[i] = 1+i;

  b = x;

  NT2_TEST_EQUAL( b.size()      , 5U                  );
  NT2_TEST_EQUAL( b.lower()     ,  base_::value       );
  NT2_TEST_EQUAL( b.upper()     ,  5                  );
  NT2_TEST_NOT_EQUAL( b.origin(), (float*)(0)         );
  NT2_TEST_NOT_EQUAL( b.begin() , (float*)(0)         );
  NT2_TEST_EQUAL( b.origin()    , b.begin()+b.lower() );
  NT2_TEST( align_on(b.origin()) );

  for ( buffer_type::index_type i = b.lower(); i <= b.upper(); ++i )
    NT2_TEST_EQUAL( b[i], 1+i );
}

////////////////////////////////////////////////////////////////////////////////
// Test for dynamic buffer swap
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(buffer_swap)
{
  using nt2::memory::buffer;
  using nt2::memory::align_on;
  using nt2::memory::allocator;

  typedef boost::mpl::int_<1> base_;
  typedef buffer<float,base_,int,allocator<float> > buffer_type;
  buffer_type b(base_(),3),x(base_(),5);

  for ( buffer_type::index_type i = x.lower(); i <= x.upper(); ++i )
    x[i] = 1+i;
  for ( buffer_type::index_type i = b.lower(); i <= b.upper(); ++i )
    b[i] = i;

  swap(b,x);

  NT2_TEST_EQUAL( b.size()      , 5U                  );
  NT2_TEST_EQUAL( b.lower()     , base_::value        );
  NT2_TEST_EQUAL( b.upper()     , 5                   );
  NT2_TEST_NOT_EQUAL( b.origin(), (float*)(0)         );
  NT2_TEST_NOT_EQUAL( b.begin() , (float*)(0)         );
  NT2_TEST_EQUAL( b.origin()    , b.begin()+b.lower() );
  NT2_TEST( align_on(b.origin()) );

  NT2_TEST_EQUAL( x.size()      , 3U                  );
  NT2_TEST_EQUAL( x.lower()     , base_::value        );
  NT2_TEST_EQUAL( x.upper()     ,   3                 );
  NT2_TEST_NOT_EQUAL( x.origin(), (float*)(0)         );
  NT2_TEST_NOT_EQUAL( x.begin() , (float*)(0)         );
  NT2_TEST_EQUAL( x.origin()    , x.begin()+x.lower() );
  NT2_TEST( align_on(x.origin()) );

  for ( buffer_type::index_type i = x.lower(); i <= x.upper(); ++i )
    NT2_TEST_EQUAL( x[i], i );

  for ( buffer_type::index_type i = b.lower(); i <= b.upper(); ++i )
    NT2_TEST_EQUAL( b[i], 1+i );
}
