//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2::memory composite container"

#include <nt2/sdk/memory/container.hpp>
#include <nt2/core/functions/of_size.hpp>
#include <nt2/core/container/table/semantic.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>

#include <boost/fusion/include/vector_tie.hpp>
#include <boost/fusion/include/make_vector.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

struct foo
{
  double d; float f; short c;
};

BOOST_FUSION_ADAPT_STRUCT(foo,(double,d)(float,f)(short,c))

#define DIMS (nt2::_2D)(nt2::_3D)(nt2::_4D)

//==============================================================================
// Test for container default ctor
//==============================================================================
NT2_TEST_CASE_TPL( container_dynamic_default_ctor, DIMS)
{
  using nt2::settings;
  using nt2::of_size_;
  using nt2::memory::container;

  container<foo,settings(T)> b;

  NT2_TEST(b.empty());
  NT2_TEST_EQUAL(b.size()             , 0u );
  NT2_TEST_EQUAL(b.leading_size()     , 0u );
  NT2_TEST(b.extent() == of_size_<0>());
  NT2_TEST_EQUAL( b.raw()
                , boost::fusion::make_vector( (double*)(0)
                                            , (float*)(0)
                                            , (short*)(0)
                                            )
                );
}

//==============================================================================
// Test for container default ctor
//==============================================================================
NT2_TEST_CASE( container_static_default_ctor )
{
  using nt2::of_size;
  using nt2::of_size_;
  using nt2::settings;
  using nt2::memory::container;

  typedef container<foo,settings(of_size_<3,7>)> type;
  type b;

  NT2_TEST(!b.empty());
  NT2_TEST_EQUAL(b.leading_size(), b.extent()[0] );
  NT2_TEST( (b.extent() == of_size_<3,7>()) );

  for(type::difference_type j=0;j<7;++j)
    for(type::difference_type i=0;i<3;++i)
    {
      foo f = {2.*i,1.f+j*i,short(j)};
      b[i+3*j] = f;
    }


  for(type::difference_type j=0;j<7;++j)
    for(type::difference_type i=0;i<3;++i)
    {
      foo f = {2.*i,1.f+j*i,short(j)};
      NT2_TEST_EQUAL( b[i+3*j], boost::fusion::as_vector(f) );
    }
}

//==============================================================================
// Test for container default ctor of automatic containers
//==============================================================================
NT2_TEST_CASE( container_automatic_static_default_ctor )
{
  using nt2::of_size;
  using nt2::of_size_;
  using nt2::automatic_;
  using nt2::settings;
  using nt2::memory::container;

  typedef container<foo,settings(of_size_<3,7>, automatic_)> type;
  type b;

  NT2_TEST(!b.empty());
  NT2_TEST_EQUAL(b.leading_size(), b.extent()[0] );
  NT2_TEST( (b.extent() == of_size_<3,7>()) );

  for(type::difference_type j=0;j<7;++j)
    for(type::difference_type i=0;i<3;++i)
    {
      foo f = {2.*i,1.f+j*i,short(j)};
      b[i+3*j] = f;
    }

  for(type::difference_type j=0;j<7;++j)
    for(type::difference_type i=0;i<3;++i)
    {
      foo f = {2.*i,1.f+j*i,short(j)};
      NT2_TEST_EQUAL( b[i+3*j], boost::fusion::as_vector(f) );
    }
}

//==============================================================================
// Test for container size ctor
//==============================================================================
NT2_TEST_CASE( container_size_ctor )
{
  using nt2::of_size;
  using nt2::of_size_;
  using nt2::settings;
  using nt2::memory::container;

  typedef container<foo,settings()> type;
  type b( of_size(3,7) );

  NT2_TEST(!b.empty());
  NT2_TEST_EQUAL(b.leading_size(), b.extent()[0] );
  NT2_TEST( (b.extent() == of_size_<3,7>()) );

  for(type::difference_type j=0;j<7;++j)
    for(type::difference_type i=0;i<3;++i)
    {
      foo f = {2.*i,1.f+j*i,short(j)};
      b[i+3*j] = f;
    }

  for(type::difference_type j=0;j<7;++j)
    for(type::difference_type i=0;i<3;++i)
    {
      foo f = {2.*i,1.f+j*i,short(j)};
      NT2_TEST_EQUAL( b[i+3*j], boost::fusion::as_vector(f) );
    }
}

//==============================================================================
// Test for container copy ctor
//==============================================================================
NT2_TEST_CASE( container_copy_ctor )
{
  using nt2::of_size;
  using nt2::settings;
  using nt2::memory::container;

  typedef container<foo,settings()> type;
  type b( of_size(3,7) );

  for(type::difference_type j=0;j<7;++j)
    for(type::difference_type i=0;i<3;++i)
    {
      foo f = {2.*i,1.f+j*i,short(j)};
      b[i+3*j] = f;
    }

  type x(b);
  NT2_TEST(!x.empty());
  NT2_TEST_EQUAL(x.leading_size(), x.extent()[0] );
  NT2_TEST( (x.extent() == of_size(3,7)) );

  for(type::difference_type j=0;j<7;++j)
    for(type::difference_type i=0;i<3;++i)
    {
      foo f = {2.*i,1.f+j*i,short(j)};
      NT2_TEST_EQUAL( x[i+3*j], boost::fusion::as_vector(f) );
    }
}

//==============================================================================
// Test for automatic container copy ctor
//==============================================================================
NT2_TEST_CASE( automatic_container_copy_ctor )
{
  using nt2::of_size;
  using nt2::of_size_;
  using nt2::automatic_;
  using nt2::settings;
  using nt2::memory::container;

  typedef container<foo,settings(of_size_<3,7>, automatic_)> type;
  type b;

  for(type::difference_type j=0;j<7;++j)
    for(type::difference_type i=0;i<3;++i)
    {
      foo f = {2.*i,1.f+j*i,short(j)};
      b[i+3*j] = f;
    }

  type x( b );

  NT2_TEST(!x.empty());
  NT2_TEST_EQUAL(x.leading_size(), b.extent()[0] );
  NT2_TEST( (x.extent() == of_size(3,7)) );

  for(type::difference_type j=0;j<7;++j)
    for(type::difference_type i=0;i<3;++i)
    {
      foo f = {2.*i,1.f+j*i,short(j)};
      NT2_TEST_EQUAL( x[i+3*j], boost::fusion::as_vector(f) );
    }
}

//==============================================================================
// Test for container assignment
//==============================================================================
NT2_TEST_CASE_TPL( container_assignment, DIMS)
{
  using nt2::of_size;
  using nt2::settings;
  using nt2::memory::container;

  typedef container<foo,settings()> type;
  type b( of_size(3,5) );

  for(type::difference_type j=0;j<5;++j)
    for(type::difference_type i=0;i<3;++i)
    {
      foo f = {2.*i,1.f+j*i,short(j)};
      b[i+3*j] = f;
    }

  type x;

  x = b;

  NT2_TEST(!x.empty());
  NT2_TEST_EQUAL(x.leading_size(), x.extent()[0] );
  NT2_TEST( (x.extent() == of_size(3,5)) );

  for(type::difference_type j=0;j<5;++j)
    for(type::difference_type i=0;i<3;++i)
    {
      foo f = {2.*i,1.f+j*i,short(j)};
      NT2_TEST_EQUAL( x[i+3*j], boost::fusion::as_vector(f) );
    }
}

//==============================================================================
// Test for automatic container assignment
//==============================================================================
NT2_TEST_CASE_TPL( automatic_container_assignment, DIMS)
{
  using nt2::of_size;
  using nt2::of_size_;
  using nt2::settings;
  using nt2::memory::container;

  typedef container<foo,settings(of_size_<3,5>)> type;
  type b;

  for(type::difference_type j=0;j<5;++j)
    for(type::difference_type i=0;i<3;++i)
    {
      foo f = {2.*i,1.f+j*i,short(j)};
      b[i+3*j] = f;
    }

  type x;

  x = b;

  NT2_TEST(!x.empty());
  NT2_TEST_EQUAL(x.leading_size(), x.extent()[0] );
  NT2_TEST( (x.extent() == of_size(3,5)) );

  for(type::difference_type j=0;j<5;++j)
    for(type::difference_type i=0;i<3;++i)
    {
      foo f = {2.*i,1.f+j*i,short(j)};
      NT2_TEST_EQUAL( x[i+3*j], boost::fusion::as_vector(f) );
    }
}

//==============================================================================
// Test for container swap
//==============================================================================
NT2_TEST_CASE( container_swap )
{
  using nt2::of_size;
  using nt2::of_size_;
  using nt2::settings;
  using nt2::memory::container;

  typedef container<foo,settings()> type;
  type b( of_size(5,3) );

  for(typename type::difference_type j=0;j<3;++j)
    for(typename type::difference_type i=0;i<5;++i)
    {
      foo f = {2.*i,1.f+j*i,short(j)};
      b[i+5*j] = f;
    }

  type x( of_size(7,2) );

  for(typename type::difference_type j=0;j<2;++j)
    for(typename type::difference_type i=0;i<7;++i)
    {
      foo f = {2.*j,1.f+j-i,short(i)};
      x[i+7*j] = f;
    }

  swap(x,b);

  NT2_TEST(!b.empty());
  NT2_TEST_EQUAL(b.leading_size(), b.extent()[0] );
  NT2_TEST( (b.extent() == of_size(7,2)) );

  NT2_TEST(!x.empty());
  NT2_TEST_EQUAL(x.leading_size(), x.extent()[0] );
  NT2_TEST( (x.extent() == of_size(5,3)) );

  for(typename type::difference_type j=0;j<3;++j)
    for(typename type::difference_type i=0;i<5;++i)
    {
      foo f = {2.*i,1.f+j*i,short(j)};
      NT2_TEST_EQUAL( x[i+5*j], boost::fusion::as_vector(f) );
    }

  for(typename type::difference_type j=0;j<2;++j)
    for(typename type::difference_type i=0;i<7;++i)
    {
      foo f = {2.*j,1.f+j-i,short(i)};
      NT2_TEST_EQUAL( b[i+7*j], boost::fusion::as_vector(f) );
    }
}

//==============================================================================
// Test for container resize
//==============================================================================
NT2_TEST_CASE( container_resize )
{
  using nt2::of_size;
  using nt2::settings;
  using nt2::of_size_;
  using nt2::memory::container;

  typedef container<foo,settings()> type;
  type b;

  NT2_TEST(b.empty());
  NT2_TEST_EQUAL(b.size(),  0u );
  NT2_TEST_EQUAL(b.leading_size(), b.extent()[0] );
  NT2_TEST(b.extent() == of_size_<0>());

  b.resize( of_size(3,2) );

  NT2_TEST(!b.empty());
  NT2_TEST_EQUAL(b.leading_size(), b.extent()[0] );
  NT2_TEST(b.extent() == of_size(3,2));

  for(typename type::difference_type j=0;j<2;++j)
    for(typename type::difference_type i=0;i<3;++i)
    {
      foo f = {2.*i,1.f+j*i,short(j)};
      b[i+3*j] = f;
    }

  for(typename type::difference_type j=0;j<2;++j)
    for(typename type::difference_type i=0;i<3;++i)
    {
      foo f = {2.*i,1.f+j*i,short(j)};
      NT2_TEST_EQUAL( b[i+3*j], boost::fusion::as_vector(f) );
    }

  b.resize( of_size(1,11) );

  NT2_TEST(!b.empty());
  NT2_TEST_EQUAL(b.leading_size(), b.extent()[0] );
  NT2_TEST(b.extent() == of_size(1,11));

  for(typename type::difference_type i=0;i<11;++i)
  {
    foo f = {-1./i,1.f+i,short(i)};
    b[i] = f;
  }

  for(typename type::difference_type i=0;i<11;++i)
  {
    foo f = {-1./i,1.f+i,short(i)};
    NT2_TEST_EQUAL( b[i], boost::fusion::as_vector(f) );
  }

  b.resize( of_size(2,7) );

  NT2_TEST(!b.empty());
  NT2_TEST_EQUAL(b.leading_size(), b.extent()[0] );
  NT2_TEST(b.extent() == of_size(2,7));

  for(typename type::difference_type j=0;j<7;++j)
    for(typename type::difference_type i=0;i<2;++i)
    {
      foo f = {2./j,3.f*i,short(i+j)};
      b[i+2*j] = f;
    }

  for(typename type::difference_type j=0;j<7;++j)
    for(typename type::difference_type i=0;i<2;++i)
    {
      foo f = {2./j,3.f*i,short(i+j)};
      NT2_TEST_EQUAL( b[i+2*j], boost::fusion::as_vector(f) );
    }
}
