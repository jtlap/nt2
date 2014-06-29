//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/sdk/memory/container.hpp>
#include <nt2/core/functions/of_size.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>

#include <boost/fusion/include/vector_tie.hpp>
#include <boost/fusion/include/make_vector.hpp>

#define DIMS (nt2::_1D)(nt2::_2D)(nt2::_3D)(nt2::_4D)

#include <vector>

#include "object.hpp"
#include "local_io.hpp"
#include "local_semantic.hpp"

NT2_TEST_CASE_TPL( container_dynamic_default_ctor, DIMS)
{
  using nt2::settings;
  using nt2::of_size_;
  using nt2::memory::container;

  container<some_kind_, nt2::object,settings(T)> b;

  NT2_TEST(b.empty());
  NT2_TEST_EQUAL(b.size()             , 0u );
  NT2_TEST_EQUAL(b.leading_size()     , 0u );
  NT2_TEST_EQUAL(b.extent(), of_size_<0>());
}

NT2_TEST_CASE( container_static_default_ctor)
{
  using nt2::of_size;
  using nt2::of_size_;
  using nt2::settings;
  using nt2::memory::container;

  typedef container<some_kind_, nt2::object,settings(of_size_<3,7>)> type;
  type b;

  std::vector<nt2::object> ref(3*7);

  NT2_TEST(!b.empty());
  NT2_TEST_EQUAL(b.leading_size(), b.extent()[0] );
  NT2_TEST_EQUAL( b.extent(), (of_size_<3,7>())  );
  NT2_TEST_EQUAL(b.data(), &b[0]);

  for(type::difference_type j=0;j<7;++j)
    for(type::difference_type i=0;i<3;++i)
      NT2_TEST_EQUAL( b[i+3*j].s , std::string("default") );
}

NT2_TEST_CASE( container_automatic_static_default_ctor)
{
  using nt2::of_size_;
  using nt2::settings;
  using nt2::automatic_;
  using nt2::memory::container;

  typedef container < some_kind_
                    , nt2::object
                    , settings(of_size_<3,7>, automatic_)
                    > type;
  type b;

  NT2_TEST(!b.empty());
  NT2_TEST_EQUAL(b.leading_size(), b.extent()[0] );
  NT2_TEST_EQUAL(b.extent(), (of_size_<3,7>()) );
  NT2_TEST_EQUAL(b.data(), &b[0]);

  for(type::difference_type j=0;j<7;++j)
    for(type::difference_type i=0;i<3;++i)
      NT2_TEST_EQUAL( b[i+3*j].s , std::string("default") );
}

NT2_TEST_CASE( container_size_ctor)
{
  using nt2::of_size;
  using nt2::of_size_;
  using nt2::settings;
  using nt2::memory::container;

  typedef container<some_kind_, nt2::object,settings()> type;
  type b( of_size(3,7) );

  NT2_TEST(!b.empty());
  NT2_TEST_EQUAL(b.leading_size(), b.extent()[0] );
  NT2_TEST_EQUAL( b.extent(), (of_size_<3,7>()) );
  NT2_TEST_EQUAL(b.data(), &b[0]);

  for(type::difference_type j=0;j<7;++j)
    for(type::difference_type i=0;i<3;++i)
      NT2_TEST_EQUAL( b[i+3*j].s , std::string("default") );
}

NT2_TEST_CASE( container_copy_ctor)
{
  using nt2::of_size;
  using nt2::settings;
  using nt2::memory::container;

  typedef container<some_kind_, nt2::object,settings()> type;
  type b( of_size(5,3) );
  type x( b );

  NT2_TEST(!x.empty());
  NT2_TEST_EQUAL(x.leading_size(), b.extent()[0] );
  NT2_TEST_EQUAL( x.extent(), (of_size(5,3)) );
  NT2_TEST_EQUAL(x.data(), &x[0]);
  NT2_TEST_NOT_EQUAL(x.data(), b.data());

  for(type::difference_type j=0;j<3;++j)
    for(type::difference_type i=0;i<5;++i)
      NT2_TEST_EQUAL( x[i+5*j].s , std::string("copied") );
}

NT2_TEST_CASE( automatic_container_copy_ctor)
{
  using nt2::of_size;
  using nt2::of_size_;
  using nt2::automatic_;
  using nt2::settings;
  using nt2::memory::container;

  typedef container < some_kind_
                    , nt2::object
                    , settings(of_size_<3,7>, automatic_)
                    > type;
  type b;
  type x( b );

  NT2_TEST(!x.empty());
  NT2_TEST_EQUAL(x.leading_size(), b.extent()[0] );
  NT2_TEST_EQUAL( x.extent(), (of_size(3,7)) );
  NT2_TEST_EQUAL(x.data(), &x[0]);
  NT2_TEST_NOT_EQUAL(x.data(), b.data());

  for(type::difference_type j=0;j<7;++j)
    for(type::difference_type i=0;i<3;++i)
      NT2_TEST_EQUAL( x[i+3*j].s , std::string("copied") );
}

NT2_TEST_CASE( container_assignment)
{
  using nt2::of_size;
  using nt2::settings;
  using nt2::memory::container;

  typedef container<some_kind_, nt2::object,settings()> type;
  type b( of_size(5,3) );
  type x;

  x = b;

  NT2_TEST(!x.empty());
  NT2_TEST_EQUAL(x.leading_size(), x.extent()[0] );
  NT2_TEST_EQUAL( x.extent(), (of_size(5,3)) );
  NT2_TEST_EQUAL(x.data(), &x[0]);
  NT2_TEST_NOT_EQUAL(x.data(), b.data());

  for(type::difference_type j=0;j<3;++j)
    for(type::difference_type i=0;i<5;++i)
      NT2_TEST_EQUAL(x[i+5*j].s , std::string("assigned") );
}

NT2_TEST_CASE( automatic_container_assignment)
{
  using nt2::of_size;
  using nt2::of_size_;
  using nt2::settings;
  using nt2::memory::container;

  typedef container<some_kind_, nt2::object,settings(of_size_<5,3>)> type;
  type b;
  type x;

  x = b;

  NT2_TEST(!x.empty());
  NT2_TEST_EQUAL(x.leading_size(), x.extent()[0] );
  NT2_TEST_EQUAL( x.extent(), (of_size(5,3)) );
  NT2_TEST_EQUAL(x.data(), &x[0]);
  NT2_TEST_NOT_EQUAL(x.data(), b.data());

  for(type::difference_type j=0;j<3;++j)
    for(type::difference_type i=0;i<5;++i)
      NT2_TEST_EQUAL(x[i+5*j].s , std::string("assigned") );
}

NT2_TEST_CASE( container_swap)
{
  using nt2::of_size;
  using nt2::of_size_;
  using nt2::settings;
  using nt2::memory::container;

  typedef container<some_kind_, nt2::object,settings()> type;
  type b( of_size(5,3) );
  type x( of_size(7,2) );

  swap(x,b);

  NT2_TEST(!b.empty());
  NT2_TEST_EQUAL(b.leading_size(), b.extent()[0] );
  NT2_TEST_EQUAL( b.extent(), (of_size(7,2)) );
  NT2_TEST_EQUAL(b.data(), &b[0]);

  NT2_TEST(!x.empty());
  NT2_TEST_EQUAL(x.leading_size(), x.extent()[0] );
  NT2_TEST_EQUAL( x.extent(), (of_size(5,3)) );
  NT2_TEST_EQUAL(x.data(), &x[0]);

  NT2_TEST_NOT_EQUAL(x.data(), b.data());

  for(type::difference_type j=0;j<3;++j)
    for(type::difference_type i=0;i<5;++i)
      NT2_TEST_EQUAL(x[i+5*j].s , std::string("default") );

  for(type::difference_type j=0;j<2;++j)
    for(type::difference_type i=0;i<7;++i)
      NT2_TEST_EQUAL(b[i+7*j].s , std::string("default") );
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

  typedef container<some_kind_, nt2::object,settings()> type;
  type b;

  NT2_TEST(b.empty());
  NT2_TEST_EQUAL(b.size(),  0u );
  NT2_TEST_EQUAL(b.leading_size(), b.extent()[0] );
  NT2_TEST_EQUAL(b.extent(), of_size_<0>());

  b.resize( of_size(3,2) );

  NT2_TEST(!b.empty());
  NT2_TEST_EQUAL(b.leading_size(), b.extent()[0] );
  NT2_TEST_EQUAL(b.extent(), (of_size(3,2)) );
  NT2_TEST_EQUAL(b.data(), &b[0]);

  for(type::difference_type j=0;j<2;++j)
    for(type::difference_type i=0;i<3;++i)
      NT2_TEST_EQUAL(b[i+3*j].s, std::string("default") );

  b.resize( of_size(1,11) );

  NT2_TEST(!b.empty());
  NT2_TEST_EQUAL(b.leading_size(), b.extent()[0] );
  NT2_TEST_EQUAL(b.extent(), (of_size(1,11)) );
  NT2_TEST_EQUAL(b.data(), &b[0]);

  for(type::difference_type j=0;j<11;++j)
    NT2_TEST_EQUAL(b[j].s, std::string("default") );

  b.resize( of_size(2,7) );

  NT2_TEST(!b.empty());
  NT2_TEST_EQUAL(b.leading_size(), b.extent()[0] );
  NT2_TEST_EQUAL(b.extent(), (of_size(2,7)) );
  NT2_TEST_EQUAL(b.data(), &b[0]);

  for(type::difference_type j=0;j<7;++j)
    for(type::difference_type i=0;i<2;++i)
      NT2_TEST_EQUAL(b[i+2*j].s, std::string("default") );
}

//==============================================================================
// Test for container push_back
//==============================================================================
NT2_TEST_CASE( container_push_back )
{
  nt2::memory::container<some_kind_, nt2::object, nt2::settings()>
  a(nt2::of_size(2, 3));

  for(std::ptrdiff_t i=0; i<7; ++i)
    a.push_back(nt2::object("foo"));

  NT2_TEST_EQUAL( a.extent(), nt2::of_size(2*3+7) );
  for(std::ptrdiff_t i=0; i<2*3; ++i)
    NT2_TEST_EQUAL( a[i].s, std::string("copied") );
  for(std::ptrdiff_t i=0; i<7; ++i)
    NT2_TEST_EQUAL( a[2*3+i].s, std::string("copied") );
}
