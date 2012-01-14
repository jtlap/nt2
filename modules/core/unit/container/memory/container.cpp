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
#include <nt2/core/container/table/normalize_settings.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>

#include <boost/fusion/include/vector_tie.hpp>
#include <boost/fusion/include/make_vector.hpp>

#define DIMS (nt2::_1D)(nt2::_2D)(nt2::_3D)(nt2::_4D)

//==============================================================================
// container type has some dimensions
//==============================================================================
NT2_TEST_CASE_TPL( container_buffer_dimensions, DIMS )
{
  using nt2::id_;
  using nt2::settings;
  using nt2::tag::table_;
  using nt2::meta::dimensions_of;
  using nt2::memory::container;

  NT2_TEST_EQUAL
  ((dimensions_of< container<table_, id_<0>, double, settings(T)> >::value)
  , std::size_t(T::static_size)
  );
}

//==============================================================================
// container type has some value
//==============================================================================
NT2_TEST_CASE_TPL( container_values, NT2_TYPES )
{
  using nt2::id_;
  using boost::mpl::_;
  using nt2::settings;
  using nt2::tag::table_;
  using nt2::memory::container;
  using boost::dispatch::meta::value_of;

  NT2_TEST_EXPR_TYPE( (container <table_, id_<0>, T, settings()>())
                    , value_of<_>
                    , T
                    );
}

//==============================================================================
// container type has a model
//==============================================================================
template<class T, class U>
struct  apply_model
      : boost::mpl::apply < typename boost::dispatch::meta::model_of<T>::type
                          , U
                          >
{};

NT2_TEST_CASE_TPL( container_models, NT2_TYPES )
{
  using nt2::id_;
  using boost::mpl::_;
  using nt2::settings;
  using nt2::tag::table_;
  using nt2::memory::container;

  NT2_TEST_EXPR_TYPE
  ( (container<table_, id_<0>, int, settings()>())
  , (apply_model<_,T>)
  , (container<table_, id_<0>, T, settings()>)
  );
}

//==============================================================================
// Test for container default ctor
//==============================================================================
NT2_TEST_CASE_TPL( container_dynamic_default_ctor, DIMS)
{
  using nt2::id_;
  using nt2::settings;
  using nt2::of_size_;
  using nt2::tag::table_;
  using nt2::memory::container;

  container<table_,id_<0>,double,settings(T)> b;
  int dims = T::static_size;

  NT2_TEST(b.empty());
  NT2_TEST_EQUAL(b.size()       ,  0 );
  NT2_TEST(b.extent() == of_size_<0>());
}

//==============================================================================
// Test for container default ctor
//==============================================================================
NT2_TEST_CASE_TPL( container_static_default_ctor, NT2_TYPES)
{
  using nt2::id_;
  using nt2::of_size_;
  using nt2::settings;
  using nt2::tag::table_;
  using nt2::memory::container;

  typedef container<table_,id_<0>,T,settings(of_size_<32,7>)> type;
  type b;

  NT2_TEST(!b.empty());
  NT2_TEST_EQUAL(b.size()       ,  32*7 );
  NT2_TEST( (b.extent() == of_size_<32,7>()) );

  for(typename type::difference_type j=1;j<=7;++j)
    for(typename type::difference_type i=1;i<=32;++i)
      b[boost::fusion::vector_tie(i,j)] = T(i + j);

  for(typename type::difference_type j=1;j<=7;++j)
    for(typename type::difference_type i=1;i<=32;++i)
      NT2_TEST_EQUAL(b[boost::fusion::vector_tie(i,j)], T(i + j));
}

//==============================================================================
// Test for container default ctor
//==============================================================================
NT2_TEST_CASE_TPL( container_automatic_static_default_ctor, NT2_TYPES)
{
  using nt2::id_;
  using nt2::of_size_;
  using nt2::settings;
  using nt2::automatic_;
  using nt2::tag::table_;
  using nt2::memory::container;

  typedef container<table_,id_<0>,T,settings(of_size_<32,7>, automatic_)> type;
  type b;

  NT2_TEST(!b.empty());
  NT2_TEST_EQUAL(b.size()       ,  32*7 );
  NT2_TEST( (b.extent() == of_size_<32,7>()) );

  for(typename type::difference_type j=1;j<=7;++j)
    for(typename type::difference_type i=1;i<=32;++i)
      b[boost::fusion::vector_tie(i,j)] = T(i + j);

  for(typename type::difference_type j=1;j<=7;++j)
    for(typename type::difference_type i=1;i<=32;++i)
      NT2_TEST_EQUAL(b[boost::fusion::vector_tie(i,j)], T(i + j));
}

//==============================================================================
// Test for container size ctor
//==============================================================================
NT2_TEST_CASE_TPL( container_size_ctor, NT2_TYPES)
{
  using nt2::id_;
  using nt2::of_size;
  using nt2::settings;
  using nt2::tag::table_;
  using nt2::memory::container;

  typedef container<table_,id_<0>,T,settings()> type;
  type b( of_size(32,3) );

  NT2_TEST(!b.empty());
  NT2_TEST_EQUAL(b.size()       ,  32*3 );
  NT2_TEST( (b.extent() == of_size(32,3)) );

  for(typename type::difference_type j=1;j<=3;++j)
    for(typename type::difference_type i=1;i<=32;++i)
      b[boost::fusion::vector_tie(i,j)] = T(i + j);

  for(typename type::difference_type j=1;j<=3;++j)
    for(typename type::difference_type i=1;i<=32;++i)
      NT2_TEST_EQUAL(b[boost::fusion::vector_tie(i,j)], T(i + j));
}

//==============================================================================
// Test for container copy ctor
//==============================================================================
NT2_TEST_CASE_TPL( container_copy_ctor, NT2_TYPES)
{
  using nt2::id_;
  using nt2::of_size;
  using nt2::settings;
  using nt2::tag::table_;
  using nt2::memory::container;

  typedef container<table_,id_<0>,T,settings()> type;
  type b( of_size(32,3) );

  for(typename type::difference_type j=1;j<=3;++j)
    for(typename type::difference_type i=1;i<=32;++i)
      b[boost::fusion::vector_tie(i,j)] = T(i + j);

  type x( b );

  NT2_TEST(!x.empty());
  NT2_TEST_EQUAL(x.size()       ,  32*3 );
  NT2_TEST( (x.extent() == of_size(32,3)) );

  for(typename type::difference_type j=1;j<=3;++j)
    for(typename type::difference_type i=1;i<=32;++i)
      NT2_TEST_EQUAL(x[boost::fusion::vector_tie(i,j)], T(i + j));
}

//==============================================================================
// Test for container assignment
//==============================================================================
NT2_TEST_CASE_TPL( container_assignment, NT2_TYPES)
{
  using nt2::id_;
  using nt2::of_size;
  using nt2::settings;
  using nt2::tag::table_;
  using nt2::memory::container;

  typedef container<table_,id_<0>,T,settings()> type;
  type b( of_size(32,3) );

  for(typename type::difference_type j=1;j<=3;++j)
    for(typename type::difference_type i=1;i<=32;++i)
      b[boost::fusion::vector_tie(i,j)] = T(i + j);

  type x;

  x = b;

  NT2_TEST(!x.empty());
  NT2_TEST_EQUAL(x.size()       ,  32*3 );
  NT2_TEST( (x.extent() == of_size(32,3)) );

  for(typename type::difference_type j=1;j<=3;++j)
    for(typename type::difference_type i=1;i<=32;++i)
      NT2_TEST_EQUAL(x[boost::fusion::vector_tie(i,j)], T(i + j));
}

//==============================================================================
// Test for container swap
//==============================================================================
NT2_TEST_CASE_TPL( container_swap, NT2_TYPES)
{
  using nt2::id_;
  using nt2::of_size;
  using nt2::settings;
  using nt2::tag::table_;
  using nt2::memory::container;

  typedef container<table_,id_<0>,T,settings()> type;
  type b( of_size(32,3) );
  type x( of_size(32,2) );

  for(typename type::difference_type j=1;j<=3;++j)
    for(typename type::difference_type i=1;i<=32;++i)
      b[boost::fusion::vector_tie(i,j)] = T(j);

  for(typename type::difference_type j=1;j<=2;++j)
    for(typename type::difference_type i=1;i<=32;++i)
      x[boost::fusion::vector_tie(i,j)] = T(i);

  swap(x,b);

  NT2_TEST(!x.empty());
  NT2_TEST_EQUAL(x.size()       ,  32*3 );
  NT2_TEST( (x.extent() == of_size(32,3)) );

  NT2_TEST(!b.empty());
  NT2_TEST_EQUAL(b.size()       ,  32*2 );
  NT2_TEST( (b.extent() == of_size(32,2)) );

  for(typename type::difference_type j=1;j<=2;++j)
    for(typename type::difference_type i=1;i<=32;++i)
      NT2_TEST_EQUAL(b[boost::fusion::vector_tie(i,j)], T(i));

  for(typename type::difference_type j=1;j<=3;++j)
    for(typename type::difference_type i=1;i<=32;++i)
      NT2_TEST_EQUAL(x[boost::fusion::vector_tie(i,j)], T(j));
}
