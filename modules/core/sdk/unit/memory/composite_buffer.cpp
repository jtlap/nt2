//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2::memory composite_buffer as a Buffer"

#include <nt2/sdk/memory/buffer.hpp>
#include <nt2/sdk/memory/array_buffer.hpp>
#include <nt2/sdk/memory/composite_buffer.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

#include <boost/fusion/include/io.hpp>
#include <boost/fusion/include/make_vector.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

struct foo
{
  double d; float f; short c;
};

BOOST_FUSION_ADAPT_STRUCT(foo,(double,d)(float,f)(short,c))

struct data_type_
{
  template<class T> struct apply { typedef typename T::data_t type; };
};

//==============================================================================
// Checks proper composite internal typedefs based on buffer
//==============================================================================
NT2_TEST_CASE( composite_buffer_typing )
{
  using boost::mpl::_;
  using nt2::meta::value_type_;
  using nt2::meta::reference_;
  using nt2::meta::const_reference_;
  using nt2::meta::pointer_;
  using nt2::meta::const_pointer_;
  using nt2::memory::composite_buffer;
  using nt2::memory::composite_reference;
  using nt2::memory::buffer;

  NT2_TEST_EXPR_TYPE( (composite_buffer< buffer<foo> >())
                    , data_type_
                    , (boost::fusion::vector3<buffer<double>,buffer<float>,buffer<short> >)
                    );

  NT2_TEST_EXPR_TYPE( (composite_buffer< buffer<foo> >())
                    , value_type_<_>
                    , (foo)
                    );

  NT2_TEST_EXPR_TYPE( (composite_buffer< buffer<foo> >())
                    , reference_<_>
                    , (composite_reference<foo>)
                    );

  NT2_TEST_EXPR_TYPE( (composite_buffer< buffer<foo> >())
                    , const_reference_<_>
                    , (composite_reference<foo const>)
                    );

  NT2_TEST_EXPR_TYPE( (composite_buffer< buffer<foo> >())
                    , pointer_<_>
                    , (boost::fusion::vector3<double*,float*,short*>)
                    );

  NT2_TEST_EXPR_TYPE( (composite_buffer< buffer<foo> >())
                    , const_pointer_<_>
                    , (boost::fusion::vector3<double const*,float const*,short const*>)
                    );
}

//==============================================================================
// Checks proper composite internal typedefs based on array_buffer
//==============================================================================
NT2_TEST_CASE( composite_array_buffer_typing )
{
  using boost::mpl::_;
  using nt2::meta::value_type_;
  using nt2::meta::reference_;
  using nt2::meta::const_reference_;
  using nt2::meta::pointer_;
  using nt2::meta::const_pointer_;
  using nt2::memory::composite_buffer;
  using nt2::memory::composite_reference;
  using nt2::memory::array_buffer;

  NT2_TEST_EXPR_TYPE( (composite_buffer< array_buffer<foo,boost::mpl::int_<1> > >())
                    , data_type_
                    , ( boost::fusion::
                        vector3 < array_buffer<double,boost::mpl::int_<1> >
                                , array_buffer<float,boost::mpl::int_<1> >
                                , array_buffer<short,boost::mpl::int_<1> >
                                >
                      )
                    );

  NT2_TEST_EXPR_TYPE( (composite_buffer< array_buffer<foo,boost::mpl::int_<1> > >())
                    , value_type_<_>
                    , (foo)
                    );

  NT2_TEST_EXPR_TYPE( (composite_buffer< array_buffer<foo,boost::mpl::int_<1> > >())
                    , reference_<_>
                    , (composite_reference<foo>)
                    );

  NT2_TEST_EXPR_TYPE( (composite_buffer< array_buffer<foo,boost::mpl::int_<1> > >())
                    , const_reference_<_>
                    , (composite_reference<foo const>)
                    );

  NT2_TEST_EXPR_TYPE( (composite_buffer< array_buffer<foo,boost::mpl::int_<1> > >())
                    , pointer_<_>
                    , (boost::fusion::vector3<double*,float*,short*>)
                    );

  NT2_TEST_EXPR_TYPE( (composite_buffer< array_buffer<foo,boost::mpl::int_<1> > >())
                    , const_pointer_<_>
                    , (boost::fusion::vector3<double const*,float const*,short const*>)
                    );
}

//==============================================================================
// composite_buffer default constructor
//==============================================================================
NT2_TEST_CASE( composite_buffer_default_ctor )
{
  using nt2::memory::buffer;
  using nt2::memory::composite_buffer;

  composite_buffer< buffer<foo> > b;

  NT2_TEST(b.empty());
  NT2_TEST_EQUAL(b.size()     , 0u      );
  NT2_TEST_EQUAL(b.capacity() , 0u      );
  NT2_TEST_EQUAL(b.begin()    , b.end() );
  NT2_TEST_EQUAL( b.raw()
                , boost::fusion::make_vector((double*)0,(float*)0,(short*)0)
                );
}

//==============================================================================
// composite_buffer allocator constructor
//==============================================================================
NT2_TEST_CASE( composite_buffer_allocator_ctor )
{
  using nt2::memory::buffer;
  using nt2::memory::composite_buffer;

  composite_buffer< buffer<foo> >::allocator_type allocs;
  composite_buffer< buffer<foo> > b(allocs);

  NT2_TEST(b.empty());
  NT2_TEST_EQUAL(b.size()     , 0u      );
  NT2_TEST_EQUAL(b.capacity() , 0u      );
  NT2_TEST_EQUAL(b.begin()    , b.end() );
  NT2_TEST_EQUAL( b.raw()
                , boost::fusion::make_vector((double*)0,(float*)0,(short*)0)
                );
}

//==============================================================================
// Test for size composite_buffer ctor
//==============================================================================
NT2_TEST_CASE( composite_buffer_size_ctor )
{
  using nt2::memory::buffer;
  using nt2::memory::composite_buffer;

  composite_buffer< buffer<foo> > b(5);

  NT2_TEST(!b.empty());
  NT2_TEST_EQUAL(b.size()     , 5u    );
  NT2_TEST_EQUAL(b.capacity() , 5u    );

  for ( std::size_t i = 0; i < 5; ++i )
  {
    foo f = {2.*i,3.f*i,short(i)};
    b[i] = f;
  }

  for ( std::size_t i = 0; i < 5; ++i )
  {
    foo f = {2.*i,3.f*i,short(i)};
    NT2_TEST_EQUAL( b[i], boost::fusion::as_vector(f) );
  }
}

//==============================================================================
// Test for size+allocator composite_buffer ctor
//==============================================================================
NT2_TEST_CASE( composite_buffer_size_allocator_ctor )
{
  using nt2::memory::buffer;
  using nt2::memory::composite_buffer;

  composite_buffer< buffer<foo> >::allocator_type allocs;
  composite_buffer< buffer<foo> > b(5,allocs);

  NT2_TEST(!b.empty());
  NT2_TEST_EQUAL(b.size()     , 5u    );
  NT2_TEST_EQUAL(b.capacity() , 5u    );

  for ( std::size_t i = 0; i < 5; ++i )
  {
    foo f = {2.*i,3.f*i,short(i)};
    b[i] = f;
  }

  for ( std::size_t i = 0; i < 5; ++i )
  {
    foo f = {2.*i,3.f*i,short(i)};
    NT2_TEST_EQUAL( b[i], boost::fusion::as_vector(f) );
  }
}

//==============================================================================
// Test for dynamic composite_buffer copy ctor
//==============================================================================
NT2_TEST_CASE( buffer_data_ctor)
{
  using nt2::memory::buffer;
  using nt2::memory::composite_buffer;

  composite_buffer< buffer<foo> > b(5);

  for ( std::size_t i = 0; i < 5; ++i )
  {
    foo f = {2.*i,3.f*i,short(i)};
    b[i] = f;
  }

  composite_buffer< buffer<foo> > x(b);

  NT2_TEST(!x.empty());
  NT2_TEST_EQUAL(x.size()     , 5u    );
  NT2_TEST_EQUAL(x.capacity() , 5u    );

  for ( std::size_t i = 0; i < 5; ++i )
  {
    foo f = {2.*i,3.f*i,short(i)};
    NT2_TEST_EQUAL( x[i], boost::fusion::as_vector(f) );
  }
}

//==============================================================================
// Test for buffer resize
//==============================================================================
NT2_TEST_CASE(buffer_resize)
{
  using nt2::memory::buffer;
  using nt2::memory::composite_buffer;

  composite_buffer< buffer<foo> > b(5);

  for ( std::size_t i = 0; i < 5; ++i )
  {
    foo f = {2.*i,3.f*i,short(i)};
    b[i] = f;
  }

  b.resize(3);
  NT2_TEST(!b.empty());
  NT2_TEST_EQUAL(b.size()     , 3u    );
  NT2_TEST_EQUAL(b.capacity() , 5u    );

  for ( std::size_t i = 0; i < 3; ++i )
  {
    foo f = {2.*i,3.f*i,short(i)};
    NT2_TEST_EQUAL( b[i], boost::fusion::as_vector(f) );
  }

  b.resize(5);
  NT2_TEST(!b.empty());
  NT2_TEST_EQUAL(b.size()     , 5u    );
  NT2_TEST_EQUAL(b.capacity() , 5u    );

  for ( std::size_t i = 0; i < 5; ++i )
  {
    foo f = {2.*i,3.f*i,short(i)};
    NT2_TEST_EQUAL( b[i], boost::fusion::as_vector(f) );
  }

  b.resize(9);
  NT2_TEST(!b.empty());
  NT2_TEST_EQUAL(b.size()     , 9u    );
  NT2_TEST_EQUAL(b.capacity() , 9u    );

  for ( std::size_t i = 0; i < 9; ++i )
  {
    foo f = {-1.*i,i/2.f,short(i+1)};
    b[i] = f;
  }

  for ( std::size_t i = 0; i < 9; ++i )
  {
    foo f = {-1.*i,i/2.f,short(i+1)};
    NT2_TEST_EQUAL( b[i], boost::fusion::as_vector(f) );
  }

  b.resize(1);
  NT2_TEST(!b.empty());
  NT2_TEST_EQUAL(b.size()     , 1u    );
  NT2_TEST_EQUAL(b.capacity() , 9u    );

  for ( std::size_t i = 0; i < 1; ++i )
  {
    foo f = {-1.*i,i/2.f,short(i+1)};
    NT2_TEST_EQUAL( b[i], boost::fusion::as_vector(f) );
  }
}

//==============================================================================
// Test for buffer assignment
//==============================================================================
NT2_TEST_CASE(buffer_assignment)
{
  using nt2::memory::buffer;
  using nt2::memory::composite_buffer;

  composite_buffer< buffer<foo> > x, b(5);

  for ( std::size_t i = 0; i < 5; ++i )
  {
    foo f = {2.*i,3.f*i,short(i)};
    b[i] = f;
  }

  x = b;

  NT2_TEST(!x.empty());
  NT2_TEST_EQUAL(x.size()     , 5u    );
  NT2_TEST_EQUAL(x.capacity() , 5u    );

  for ( std::size_t i = 0; i < 5; ++i )
  {
    foo f = {2.*i,3.f*i,short(i)};
    NT2_TEST_EQUAL( x[i], boost::fusion::as_vector(f) );
  }
}

//==============================================================================
// Test for buffer swap
//==============================================================================
NT2_TEST_CASE(buffer_swap)
{
  using nt2::memory::buffer;
  using nt2::memory::composite_buffer;

  composite_buffer< buffer<foo> > x(7), b(5);

  for ( std::size_t i = 0; i < 5; ++i )
  {
    foo f = {2.*i,3.f*i,short(i)};
    b[i] = f;
  }

  for ( std::size_t i = 0; i < 7; ++i )
  {
    foo f = {2.+i,3.f-i,short(1+i)};
    x[i] = f;
  }

  swap(x,b);

  NT2_TEST(!x.empty());
  NT2_TEST_EQUAL(x.size()     , 5u    );
  NT2_TEST_EQUAL(x.capacity() , 5u    );

  NT2_TEST(!b.empty());
  NT2_TEST_EQUAL(b.size()     , 7u    );
  NT2_TEST_EQUAL(b.capacity() , 7u    );

  for ( std::size_t i = 0; i < 5; ++i )
  {
    foo f = {2.*i,3.f*i,short(i)};
    NT2_TEST_EQUAL( x[i], boost::fusion::as_vector(f) );
  }

  for ( std::size_t i = 0; i < 7; ++i )
  {
    foo f = {2.+i,3.f-i,short(1+i)};
    NT2_TEST_EQUAL( b[i], boost::fusion::as_vector(f) );
  }
}

//==============================================================================
// buffer Range interface
//==============================================================================
struct f_
{
  template<class T> T operator()(T const& e) const
  {
    T that(e);
    boost::fusion::at_c<0>(that) *= 2;
    boost::fusion::at_c<1>(that) *= 10;
    boost::fusion::at_c<2>(that) *= 3;
    return e;
  }
};

NT2_TEST_CASE(buffer_iterator)
{
  using nt2::memory::buffer;
  using nt2::memory::composite_buffer;

  composite_buffer< buffer<foo> > x(5);
  composite_buffer< buffer<foo> > const xc(5);

  for ( std::size_t i = 0; i < 5; ++i )
  {
    foo f = {2.*i,3.f*i,short(i)};
    x[i] = f;
  }

  f_ f;

  composite_buffer< buffer<foo> >::iterator b = x.begin();
  composite_buffer< buffer<foo> >::iterator e = x.end();

  std::transform( b, e, b, f );

  for ( std::size_t i = 0; i < 5; ++i )
  {
    foo fx = {4.*i,30.f*i,short(3*i)};
    NT2_TEST_EQUAL( x[i], boost::fusion::as_vector(fx) );
  }
}
