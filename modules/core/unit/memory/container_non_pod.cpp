//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2::memory container"

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

#define DIMS (nt2::_1D)(nt2::_2D)(nt2::_3D)(nt2::_4D)

struct object
{
  object()              : s("default")  {}
  object(object const&) : s("copied")   {}

  object& operator=(object const&)
  {
    s = "assigned";
    return *this;
  }

  object& operator=(std::string const& src)
  {
    s = src;
    return *this;
  }

  ~object() {}

  std::string s;
};

void swap(object& l, object& r)
{
  l.s = "left swapped";
  r.s = "right swapped";
}

//==============================================================================
// Test for container default ctor
//==============================================================================
NT2_TEST_CASE_TPL( container_dynamic_default_ctor, DIMS)
{
  using nt2::settings;
  using nt2::of_size_;
  using nt2::memory::container;

  container<object,settings(T)> b;

  NT2_TEST(b.empty());
  NT2_TEST_EQUAL(b.size()             , 0u );
  NT2_TEST_EQUAL(b.leading_size()     , 0u );
  NT2_TEST(b.extent() == of_size_<0>());
  NT2_TEST_EQUAL(b.raw(), (object*)(0));
}

//==============================================================================
// Test for container default ctor
//==============================================================================
NT2_TEST_CASE( container_static_default_ctor)
{
  using nt2::of_size;
  using nt2::of_size_;
  using nt2::settings;
  using nt2::memory::container;

  {
    typedef container<object,settings(of_size_<3,7>)> type;
    type b;

    NT2_TEST(!b.empty());
    NT2_TEST_EQUAL(b.leading_size(), b.extent()[0] );
    NT2_TEST( (b.extent() == of_size_<3,7>()) );
    NT2_TEST_EQUAL(b.raw(), &b[0]);

    for(  type::difference_type j=0;j<7;++j)
      for(  type::difference_type i=0;i<3;++i)
        NT2_TEST_EQUAL( b[i+3*j].s , std::string("default") );
  }

  {
    typedef container<object,settings(of_size_<1,5>)> type;
    type b;

    NT2_TEST(!b.empty());
    NT2_TEST_EQUAL(b.leading_size(), b.extent()[0] );
    NT2_TEST((b.extent() == of_size_<1,5>()));
    NT2_TEST_EQUAL(b.raw(), &b[0]);

    for(  type::difference_type j=0;j<5;++j)
      for(  type::difference_type i=0;i<1;++i)
        NT2_TEST_EQUAL( b[i+1*j].s , std::string("default") );
  }
}

//==============================================================================
// Test for container default ctor of automatic containers
//==============================================================================
NT2_TEST_CASE( container_automatic_static_default_ctor)
{
  using nt2::of_size_;
  using nt2::settings;
  using nt2::automatic_;
  using nt2::memory::container;

  {
    typedef container<object,settings(of_size_<3,7>, automatic_)> type;
    type b;

    NT2_TEST(!b.empty());
    NT2_TEST_EQUAL(b.leading_size(), b.extent()[0] );
    NT2_TEST( (b.extent() == of_size_<3,7>()) );
    NT2_TEST_EQUAL(b.raw(), &b[0]);

    for(  type::difference_type j=0;j<7;++j)
      for(  type::difference_type i=0;i<3;++i)
        NT2_TEST_EQUAL( b[i+3*j].s , std::string("default") );
  }

  {
    typedef container<object,settings(of_size_<1,7>, automatic_)> type;
    type b;

    NT2_TEST(!b.empty());
    NT2_TEST_EQUAL(b.leading_size()             , b.extent()[0] );
    NT2_TEST( (b.extent() == of_size_<1,7>()) );
    NT2_TEST_EQUAL(b.raw(), &b[0]);

    for(  type::difference_type j=0;j<7;++j)
      for(  type::difference_type i=0;i<1;++i)
        NT2_TEST_EQUAL( b[i+1*j].s , std::string("default") );
  }
}

//==============================================================================
// Test for container size ctor
//==============================================================================
NT2_TEST_CASE( container_size_ctor)
{
  using nt2::of_size;
  using nt2::of_size_;
  using nt2::settings;
  using nt2::memory::container;

  {
    typedef container<object,settings()> type;
    type b( of_size(3,7) );

    NT2_TEST(!b.empty());
    NT2_TEST_EQUAL(b.leading_size(), b.extent()[0] );
    NT2_TEST( (b.extent() == of_size_<3,7>()) );
    NT2_TEST_EQUAL(b.raw(), &b[0]);

    for(  type::difference_type j=0;j<7;++j)
      for(  type::difference_type i=0;i<3;++i)
        NT2_TEST_EQUAL( b[i+3*j].s , std::string("default") );
  }


  {
    typedef container<object,settings()> type;
    type b( of_size(1,7) );

    NT2_TEST(!b.empty());
    NT2_TEST_EQUAL(b.leading_size()             , b.extent()[0] );
    NT2_TEST( (b.extent() == of_size_<1,7>()) );
    NT2_TEST_EQUAL(b.raw(), &b[0]);

    for(  type::difference_type j=0;j<7;++j)
      for(  type::difference_type i=0;i<1;++i)
        NT2_TEST_EQUAL( b[i+1*j].s , std::string("default") );
  }
}

//==============================================================================
// Test for container copy ctor
//==============================================================================
NT2_TEST_CASE( container_copy_ctor)
{
  using nt2::of_size;
  using nt2::settings;
  using nt2::memory::container;

  {
    typedef container<object,settings()> type;
    type b( of_size(5,3) );
    type x( b );

    NT2_TEST(!x.empty());
    NT2_TEST_EQUAL(x.leading_size(), b.extent()[0] );
    NT2_TEST( (x.extent() == of_size(5,3)) );
    NT2_TEST_EQUAL(x.raw(), &x[0]);
    NT2_TEST_NOT_EQUAL(x.raw(), b.raw());

    for(  type::difference_type j=0;j<3;++j)
      for(  type::difference_type i=0;i<5;++i)
        NT2_TEST_EQUAL( x[i+5*j].s , std::string("copied") );
  }

  {
    typedef container<object,settings()> type;
    type b( of_size(1,3) );
    type x( b );

    NT2_TEST(!x.empty());
    NT2_TEST_EQUAL(x.leading_size(), x.extent()[0] );
    NT2_TEST( (x.extent() == of_size(1,3)) );
    NT2_TEST_EQUAL(x.raw(), &x[0]);
    NT2_TEST_NOT_EQUAL(x.raw(), b.raw());

    for(  type::difference_type j=0;j<3;++j)
      for(  type::difference_type i=0;i<1;++i)
        NT2_TEST_EQUAL( x[i+1*j].s , std::string("copied") );
  }
}

//==============================================================================
// Test for automatic container copy ctor
//==============================================================================
NT2_TEST_CASE( automatic_container_copy_ctor)
{
  using nt2::of_size;
  using nt2::of_size_;
  using nt2::automatic_;
  using nt2::settings;
  using nt2::memory::container;

  {
    typedef container<object,settings(of_size_<3,7>, automatic_)> type;
    type b;
    type x( b );

    NT2_TEST(!x.empty());
    NT2_TEST_EQUAL(x.leading_size(), b.extent()[0] );
    NT2_TEST( (x.extent() == of_size(3,7)) );
    NT2_TEST_EQUAL(x.raw(), &x[0]);
    NT2_TEST_NOT_EQUAL(x.raw(), b.raw());

    for(  type::difference_type j=0;j<7;++j)
      for(  type::difference_type i=0;i<3;++i)
        NT2_TEST_EQUAL( x[i+3*j].s , std::string("copied") );
  }

  {
    typedef container<object,settings(of_size_<1,7>, automatic_)> type;
    type b;
    type x( b );

    NT2_TEST(!x.empty());
    NT2_TEST_EQUAL(x.leading_size(), x.extent()[0] );
    NT2_TEST( (x.extent() == of_size(1,7)) );
    NT2_TEST_EQUAL(x.raw(), &x[0]);
    NT2_TEST_NOT_EQUAL(x.raw(), b.raw());

    for(  type::difference_type j=0;j<7;++j)
      for(  type::difference_type i=0;i<1;++i)
        NT2_TEST_EQUAL( x[i+1*j].s , std::string("copied") );
  }
}

//==============================================================================
// Test for container assignment
//==============================================================================
NT2_TEST_CASE( container_assignment)
{
  using nt2::of_size;
  using nt2::settings;
  using nt2::memory::container;

  {
    typedef container<object,settings()> type;
    type b( of_size(5,3) );
    type x;

    x = b;

    NT2_TEST(!x.empty());
    NT2_TEST_EQUAL(x.leading_size(), x.extent()[0] );
    NT2_TEST( (x.extent() == of_size(5,3)) );
    NT2_TEST_EQUAL(x.raw(), &x[0]);
    NT2_TEST_NOT_EQUAL(x.raw(), b.raw());

    for(  type::difference_type j=0;j<3;++j)
      for(  type::difference_type i=0;i<5;++i)
        NT2_TEST_EQUAL(x[i+5*j].s , std::string("assigned") );
  }

  {
    typedef container<object,settings()> type;
    type b( of_size(1,3) );
    type x;

    x = b;

    NT2_TEST(!x.empty());
    NT2_TEST_EQUAL(x.leading_size(), x.extent()[0] );
    NT2_TEST( (x.extent() == of_size(1,3)) );
    NT2_TEST_EQUAL(x.raw(), &x[0]);
    NT2_TEST_NOT_EQUAL(x.raw(), b.raw());

    for(  type::difference_type j=0;j<3;++j)
      for(  type::difference_type i=0;i<1;++i)
        NT2_TEST_EQUAL(x[i+1*j].s , std::string("assigned") );
  }
}

//==============================================================================
// Test for automatic container assignment
//==============================================================================
NT2_TEST_CASE( automatic_container_assignment)
{
  using nt2::of_size;
  using nt2::of_size_;
  using nt2::settings;
  using nt2::memory::container;

  {
    typedef container<object,settings(of_size_<5,3>)> type;
    type b;
    type x;

    x = b;

    NT2_TEST(!x.empty());
    NT2_TEST_EQUAL(x.leading_size(), x.extent()[0] );
    NT2_TEST( (x.extent() == of_size(5,3)) );
    NT2_TEST_EQUAL(x.raw(), &x[0]);
    NT2_TEST_NOT_EQUAL(x.raw(), b.raw());

    for(  type::difference_type j=0;j<3;++j)
      for(  type::difference_type i=0;i<5;++i)
        NT2_TEST_EQUAL(x[i+5*j].s , std::string("assigned") );
  }

  {
    typedef container<object,settings(of_size_<1,3>)> type;
    type b;
    type x;

    x = b;

    NT2_TEST(!x.empty());
    NT2_TEST_EQUAL(x.leading_size(), x.extent()[0] );
    NT2_TEST( (x.extent() == of_size(1,3)) );
    NT2_TEST_EQUAL(x.raw(), &x[0]);
    NT2_TEST_NOT_EQUAL(x.raw(), b.raw());

    for(  type::difference_type j=0;j<3;++j)
      for(  type::difference_type i=0;i<1;++i)
        NT2_TEST_EQUAL(x[i+1*j].s , std::string("assigned") );
  }
}

//==============================================================================
// Test for container swap
//==============================================================================
NT2_TEST_CASE( container_swap)
{
  using nt2::of_size;
  using nt2::of_size_;
  using nt2::settings;
  using nt2::memory::container;

  {
    typedef container<object,settings()> type;
    type b( of_size(5,3) );
    type x( of_size(7,2) );

    swap(x,b);

    NT2_TEST(!b.empty());
    NT2_TEST_EQUAL(b.leading_size(), b.extent()[0] );
    NT2_TEST( (b.extent() == of_size(7,2)) );
    NT2_TEST_EQUAL(b.raw(), &b[0]);

    NT2_TEST(!x.empty());
    NT2_TEST_EQUAL(x.leading_size(), x.extent()[0] );
    NT2_TEST( (x.extent() == of_size(5,3)) );
    NT2_TEST_EQUAL(x.raw(), &x[0]);

    NT2_TEST_NOT_EQUAL(x.raw(), b.raw());

    for(  type::difference_type j=0;j<3;++j)
      for(  type::difference_type i=0;i<5;++i)
        NT2_TEST_EQUAL(x[i+5*j].s , std::string("default") );

    for(  type::difference_type j=0;j<2;++j)
      for(  type::difference_type i=0;i<7;++i)
        NT2_TEST_EQUAL(b[i+7*j].s , std::string("default") );
  }

  {
    typedef container<object,settings()> type;
    type b( of_size(1,3) );
    type x( of_size(1,2) );

    swap(x,b);

    NT2_TEST(!b.empty());
    NT2_TEST_EQUAL(b.leading_size(), b.extent()[0] );
    NT2_TEST( (b.extent() == of_size(1,2)) );
    NT2_TEST_EQUAL(b.raw(), &b[0]);

    NT2_TEST(!x.empty());
    NT2_TEST_EQUAL(x.leading_size(), x.extent()[0] );
    NT2_TEST( (x.extent() == of_size(1,3)) );
    NT2_TEST_EQUAL(x.raw(), &x[0]);

    NT2_TEST_NOT_EQUAL(x.raw(), b.raw());

    for(  type::difference_type j=0;j<3;++j)
      for(  type::difference_type i=0;i<1;++i)
        NT2_TEST_EQUAL(x[i+1*j].s , std::string("default") );

    for(  type::difference_type j=0;j<2;++j)
      for(  type::difference_type i=0;i<1;++i)
        NT2_TEST_EQUAL(b[i+1*j].s , std::string("default") );
  }
}

//==============================================================================
// Test for container resize
//==============================================================================
NT2_TEST_CASE( container_resize)
{
  using nt2::of_size;
  using nt2::settings;
  using nt2::of_size_;
  using nt2::memory::container;

  {
    typedef container<object,settings()> type;
    type b;

    NT2_TEST(b.empty());
    NT2_TEST_EQUAL(b.size(),  0 );
    NT2_TEST_EQUAL(b.leading_size(), b.extent()[0] );
    NT2_TEST(b.extent() == of_size_<0>());
    NT2_TEST_EQUAL(b.raw(), (object*)(0));

    b.resize( of_size(3,2) );

    NT2_TEST(!b.empty());
    NT2_TEST_EQUAL(b.leading_size(), b.extent()[0] );
    NT2_TEST(b.extent() == of_size(3,2));
    NT2_TEST_EQUAL(b.raw(), &b[0]);

    for(  type::difference_type j=0;j<2;++j)
      for(  type::difference_type i=0;i<3;++i)
        NT2_TEST_EQUAL(b[i+3*j].s, std::string("default") );

    b.resize( of_size(1,11) );

    NT2_TEST(!b.empty());
    NT2_TEST_EQUAL(b.leading_size(), b.extent()[0] );
    NT2_TEST(b.extent() == of_size(1,11));
    NT2_TEST_EQUAL(b.raw(), &b[0]);

    for(  type::difference_type j=0;j<11;++j)
        NT2_TEST_EQUAL(b[j].s, std::string("default") );

    b.resize( of_size(2,7) );

    NT2_TEST(!b.empty());
    NT2_TEST_EQUAL(b.leading_size(), b.extent()[0] );
    NT2_TEST(b.extent() == of_size(2,7));
    NT2_TEST_EQUAL(b.raw(), &b[0]);

    for(  type::difference_type j=0;j<7;++j)
      for(  type::difference_type i=0;i<2;++i)
        NT2_TEST_EQUAL(b[i+2*j].s, std::string("default") );
  }
}
