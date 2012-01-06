//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2::memory container"

#include <iostream>

#include <nt2/sdk/memory/container.hpp>
#include <nt2/core/functions/of_size.hpp>
#include <nt2/core/container/table/normalize_settings.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>

#include <boost/fusion/include/vector_tie.hpp>

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
  , T::static_size
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
  NT2_TEST_EQUAL(b.inner_size() ,  0 );
  NT2_TEST_EQUAL(b.outer_size() ,  (dims==1) ? 1 : 0 );
  NT2_TEST_EQUAL(b.lower()      ,  1 );
  NT2_TEST_EQUAL(b.inner_lower(),  1 );
  NT2_TEST_EQUAL(b.outer_lower(),  1 );
  NT2_TEST_EQUAL(b.upper()      ,  0 );
  NT2_TEST_EQUAL(b.inner_upper(),  0 );
  NT2_TEST_EQUAL(b.outer_upper(),  (dims==1) ? 1 : 0 );
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

  container<table_,id_<0>,T,settings(of_size_<32,7>)> b;

  NT2_TEST(!b.empty());
  NT2_TEST_EQUAL(b.size()       ,  32*7 );
  NT2_TEST_EQUAL(b.inner_size() ,  32   );
  NT2_TEST_EQUAL(b.outer_size() ,  7    );
  NT2_TEST_EQUAL(b.lower()      ,  1    );
  NT2_TEST_EQUAL(b.inner_lower(),  1    );
  NT2_TEST_EQUAL(b.outer_lower(),  1    );
  NT2_TEST_EQUAL(b.upper()      ,  32*7 );
  NT2_TEST_EQUAL(b.inner_upper(),  32   );
  NT2_TEST_EQUAL(b.outer_upper(),  7    );
  NT2_TEST( (b.extent() == of_size_<32,7>()) );
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

  container<table_,id_<0>,T,settings(of_size_<32,7>, automatic_)> b;

  NT2_TEST(!b.empty());
  NT2_TEST_EQUAL(b.size()       ,  32*7 );
  NT2_TEST_EQUAL(b.inner_size() ,  32   );
  NT2_TEST_EQUAL(b.outer_size() ,  7    );
  NT2_TEST_EQUAL(b.lower()      ,  1    );
  NT2_TEST_EQUAL(b.inner_lower(),  1    );
  NT2_TEST_EQUAL(b.outer_lower(),  1    );
  NT2_TEST_EQUAL(b.upper()      ,  32*7 );
  NT2_TEST_EQUAL(b.inner_upper(),  32   );
  NT2_TEST_EQUAL(b.outer_upper(),  7    );
  NT2_TEST( (b.extent() == of_size_<32,7>()) );
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

  container<table_,id_<0>,T,settings()> b( of_size(32,3) );
  typedef typename container<table_,id_<0>,T,settings()>::difference_type diff_t;
  NT2_TEST(!b.empty());
  NT2_TEST_EQUAL(b.size()       ,  32*3 );
  NT2_TEST_EQUAL(b.inner_size() ,  32   );
  NT2_TEST_EQUAL(b.outer_size() ,  3    );
  NT2_TEST_EQUAL(b.lower()      ,  1    );
  NT2_TEST_EQUAL(b.inner_lower(),  1    );
  NT2_TEST_EQUAL(b.outer_lower(),  1    );
  NT2_TEST_EQUAL(b.upper()      ,  32*3 );
  NT2_TEST_EQUAL(b.inner_upper(),  32   );
  NT2_TEST_EQUAL(b.outer_upper(),  3    );
  NT2_TEST( (b.extent() == of_size(32,3)) );

  for(diff_t j=b.outer_lower();j<=b.outer_upper();++j)
    for(diff_t i=b.inner_lower();i<=b.inner_upper();++i)
      b[boost::fusion::vector_tie(i,j)] = T(i + j);

  for(diff_t j=b.outer_lower();j<=b.outer_upper();++j)
    for(diff_t i=b.inner_lower();i<=b.inner_upper();++i)
      NT2_TEST_EQUAL(b[boost::fusion::vector_tie(i,j)], T(i + j));
}

/*
//==============================================================================
// Test for container assignment
//==============================================================================
NT2_TEST_CASE_TPL(container_assignment, DIMS )
{
  using nt2::id_;
  using nt2::settings;
  using nt2::tag::table_;
  using nt2::memory::container;

  container<table_,id_<0>,T,settings(T)> b;

  NT2_TEST(!b.empty());
  NT2_TEST_EQUAL(b.size()       ,  32*7 );
  NT2_TEST_EQUAL(b.inner_size() ,  32   );
  NT2_TEST_EQUAL(b.outer_size() ,  7    );
  NT2_TEST_EQUAL(b.lower()      ,  1    );
  NT2_TEST_EQUAL(b.inner_lower(),  1    );
  NT2_TEST_EQUAL(b.outer_lower(),  1    );
  NT2_TEST_EQUAL(b.upper()      ,  32*7 );
  NT2_TEST_EQUAL(b.inner_upper(),  32   );
  NT2_TEST_EQUAL(b.outer_upper(),  7    );
  NT2_TEST( (b.extent() == of_size_<32,7>()) );
}

/*
//==============================================================================
// Test for 1D autotmatic iliffe_ buffer default ctor
//==============================================================================
NT2_TEST_CASE_TPL( iliffe_buffer_automatic_1D_default_ctor, NT2_TYPES)
{
  using nt2::memory::iliffe_buffer;
  using nt2::memory::array_buffer;

  typedef iliffe_buffer<boost::mpl::size_t<1>,array_buffer<T,5,-2>,void> buffer_t;

  buffer_t b;

  NT2_TEST_EQUAL(b.size() , 5U  );
  NT2_TEST_EQUAL(b.lower(), -2  );
  NT2_TEST_EQUAL(b.upper(), 2   );
}

//==============================================================================
// Test for nD dynamic iliffe_ buffer default ctor
//==============================================================================
NT2_TEST_CASE_TPL( iliffe_buffer_dynamic_nD_default_ctor, NT2_TYPES)
{
  using nt2::memory::iliffe_buffer;
  using nt2::memory::buffer;

  typedef iliffe_buffer < boost::mpl::size_t<2>
                        , buffer<T,-2>
                        , buffer<T*,1>
                        > buffer_t;

  buffer_t b;

  NT2_TEST_EQUAL(boost::fusion::at_c<0>(b.size()) , 0 );
  NT2_TEST_EQUAL(boost::fusion::at_c<1>(b.size()) , 0 );
  NT2_TEST_EQUAL(boost::fusion::at_c<0>(b.lower()), -2);
  NT2_TEST_EQUAL(boost::fusion::at_c<1>(b.lower()), 1 );
  NT2_TEST_EQUAL(boost::fusion::at_c<0>(b.upper()), -3);
  NT2_TEST_EQUAL(boost::fusion::at_c<1>(b.upper()), 0 );
}

//==============================================================================
// Test for nD static iliffe_ buffer default ctor
//==============================================================================
NT2_TEST_CASE_TPL( iliffe_buffer_automatic_nD_default_ctor, NT2_TYPES)
{
  using nt2::memory::iliffe_buffer;
  using nt2::memory::array_buffer;

  typedef iliffe_buffer < boost::mpl::size_t<2>
                        , array_buffer<T ,7*8,-2>
                        , array_buffer<T*,  8, 1>
                        > buffer_t;

  buffer_t b;

  NT2_TEST_EQUAL(boost::fusion::at_c<0>(b.size()) , 7 );
  NT2_TEST_EQUAL(boost::fusion::at_c<1>(b.size()) , 8 );
  NT2_TEST_EQUAL(boost::fusion::at_c<0>(b.lower()), -2);
  NT2_TEST_EQUAL(boost::fusion::at_c<1>(b.lower()), 1 );
  NT2_TEST_EQUAL(boost::fusion::at_c<0>(b.upper()), 4 );
  NT2_TEST_EQUAL(boost::fusion::at_c<1>(b.upper()), 8 );
}

//==============================================================================
// Test for 2D static [1 N] ]iliffe_ buffer default ctor
//==============================================================================
NT2_TEST_CASE_TPL( iliffe_buffer_automatic__nD_default_ctor, NT2_TYPES)
{
  using nt2::memory::iliffe_buffer;
  using nt2::memory::array_buffer;

  typedef iliffe_buffer < boost::mpl::size_t<2>
                        , array_buffer<T ,7, 1>
                        , array_buffer<T*,7,-2>
                        > buffer_t;

  buffer_t b;

  NT2_TEST_EQUAL(boost::fusion::at_c<0>(b.size()) , 1 );
  NT2_TEST_EQUAL(boost::fusion::at_c<1>(b.size()) , 7 );
  NT2_TEST_EQUAL(boost::fusion::at_c<0>(b.lower()), 1 );
  NT2_TEST_EQUAL(boost::fusion::at_c<1>(b.lower()), -2);
  NT2_TEST_EQUAL(boost::fusion::at_c<0>(b.upper()), 1 );
  NT2_TEST_EQUAL(boost::fusion::at_c<1>(b.upper()), 4 );
}

//==============================================================================
// Test for dynamic 1D iliffe_buffer copy ctor
//==============================================================================
NT2_TEST_CASE_TPL( buffer_1D_copy_ctor, NT2_TYPES)
{
  using nt2::memory::iliffe_buffer;
  using nt2::memory::buffer;

  typedef iliffe_buffer<boost::mpl::size_t<1>, buffer<T,-3>, void> buffer_t;

  buffer_t b( 7 );

  for ( typename buffer_t::index_type i = -3; i <= 3; ++i )
    b[boost::fusion::vector_tie(i)] = 4+i;

  buffer_t x(b);

  NT2_TEST_EQUAL( x.size()  , 7 );
  NT2_TEST_EQUAL( x.lower() , -3);
  NT2_TEST_EQUAL( x.upper() , 3 );

  for ( typename buffer_t::index_type i = -3; i <= 3; ++i )
    NT2_TEST_EQUAL( x[boost::fusion::vector_tie(i)], 4+i);
}

//==============================================================================
// Test for automatic 1D iliffe_buffer copy ctor
//==============================================================================
NT2_TEST_CASE_TPL( buffer_static_1D_copy_ctor, NT2_TYPES)
{
  using nt2::memory::iliffe_buffer;
  using nt2::memory::array_buffer;

  typedef iliffe_buffer<boost::mpl::size_t<1>, array_buffer<T,7,-3>, void> buffer_t;

  buffer_t b( 7 );

  for ( typename buffer_t::index_type i = -3; i <= 3; ++i )
    b[boost::fusion::vector_tie(i)] = 4+i;

  buffer_t x(b);

  NT2_TEST_EQUAL( x.size()  , 7 );
  NT2_TEST_EQUAL( x.lower() , -3);
  NT2_TEST_EQUAL( x.upper() , 3 );

  for ( typename buffer_t::index_type i = -3; i <= 3; ++i )
    NT2_TEST_EQUAL( x[boost::fusion::vector_tie(i)], 4+i);
}

//==============================================================================
// Test for dynamic 2D iliffe_buffer copy ctor
//==============================================================================
NT2_TEST_CASE_TPL( buffer_2D_copy_ctor, NT2_TYPES)
{
  using nt2::memory::iliffe_buffer;
  using nt2::memory::buffer;

  typedef iliffe_buffer < boost::mpl::size_t<2>
                        , buffer<T,-2>
                        , buffer<T*,1>
                        > buffer_t;

  boost::array<std::size_t,2> ss = {{5,3}};
  buffer_t b( ss );

  for ( typename buffer_t::index_type j = 1; j <= 3; ++j )
    for ( typename buffer_t::index_type i = -2; i <= 2; ++i )
      b[boost::fusion::vector_tie(i,j)] = 3+i + 10*j ;

  buffer_t x(b);

  NT2_TEST_EQUAL(boost::fusion::at_c<0>(x.size()) , 5 );
  NT2_TEST_EQUAL(boost::fusion::at_c<1>(x.size()) , 3 );
  NT2_TEST_EQUAL(boost::fusion::at_c<0>(x.lower()), -2);
  NT2_TEST_EQUAL(boost::fusion::at_c<1>(x.lower()), 1 );
  NT2_TEST_EQUAL(boost::fusion::at_c<0>(x.upper()), 2 );
  NT2_TEST_EQUAL(boost::fusion::at_c<1>(x.upper()), 3 );

  for ( typename buffer_t::index_type j = 1; j <= 3; ++j )
    for ( typename buffer_t::index_type i = -2; i <= 2; ++i )
    NT2_TEST_EQUAL( x[boost::fusion::vector_tie(i,j)], 3+i + 10*j);
}


//==============================================================================
// Test for automatic 2D iliffe_buffer copy ctor
//==============================================================================
NT2_TEST_CASE_TPL( buffer_static_2D_copy_ctor, NT2_TYPES)
{
  using nt2::memory::iliffe_buffer;
  using nt2::memory::array_buffer;

  typedef iliffe_buffer < boost::mpl::size_t<2>
                        , array_buffer<T, 15,-2>
                        , array_buffer<T*,3 , 1>
                        > buffer_t;

  boost::array<std::size_t,2> ss = {{5,3}};
  buffer_t b( ss );

  for ( typename buffer_t::index_type j = 1; j <= 3; ++j )
    for ( typename buffer_t::index_type i = -2; i <= 2; ++i )
      b[boost::fusion::vector_tie(i,j)] = 3+i + 10*j ;

  buffer_t x(b);

  NT2_TEST_EQUAL(boost::fusion::at_c<0>(x.size()) , 5 );
  NT2_TEST_EQUAL(boost::fusion::at_c<1>(x.size()) , 3 );
  NT2_TEST_EQUAL(boost::fusion::at_c<0>(x.lower()), -2);
  NT2_TEST_EQUAL(boost::fusion::at_c<1>(x.lower()), 1 );
  NT2_TEST_EQUAL(boost::fusion::at_c<0>(x.upper()), 2 );
  NT2_TEST_EQUAL(boost::fusion::at_c<1>(x.upper()), 3 );

  for ( typename buffer_t::index_type j = 1; j <= 3; ++j )
    for ( typename buffer_t::index_type i = -2; i <= 2; ++i )
    NT2_TEST_EQUAL( x[boost::fusion::vector_tie(i,j)], 3+i + 10*j);
}

//==============================================================================
// Test for dynamic 1D iliffe_buffer assignment
//==============================================================================
NT2_TEST_CASE_TPL( buffer_1D_assignment, NT2_TYPES)
{
  using nt2::memory::iliffe_buffer;
  using nt2::memory::buffer;

  typedef iliffe_buffer<boost::mpl::size_t<1>, buffer<T,-3>, void> buffer_t;

  buffer_t x,b( 7 );

  for ( typename buffer_t::index_type i = -3; i <= 3; ++i )
    b[boost::fusion::vector_tie(i)] = 4+i;

  x = b;

  NT2_TEST_EQUAL( x.size()  , 7 );
  NT2_TEST_EQUAL( x.lower() , -3);
  NT2_TEST_EQUAL( x.upper() , 3 );

  for ( typename buffer_t::index_type i = -3; i <= 3; ++i )
    NT2_TEST_EQUAL( x[boost::fusion::vector_tie(i)], 4+i);
}

//==============================================================================
// Test for automatic 1D iliffe_buffer assignment
//==============================================================================
NT2_TEST_CASE_TPL( buffer_static_1D_assignment, NT2_TYPES)
{
  using nt2::memory::iliffe_buffer;
  using nt2::memory::array_buffer;

  typedef iliffe_buffer < boost::mpl::size_t<1>
                        , array_buffer<T,7,-3>
                        , void
                        > buffer_t;

  buffer_t x,b( 7 );

  for ( typename buffer_t::index_type i = -3; i <= 3; ++i )
    b[boost::fusion::vector_tie(i)] = 4+i;

  x = b;

  NT2_TEST_EQUAL( x.size()  , 7 );
  NT2_TEST_EQUAL( x.lower() , -3);
  NT2_TEST_EQUAL( x.upper() , 3 );

  for ( typename buffer_t::index_type i = -3; i <= 3; ++i )
    NT2_TEST_EQUAL( x[boost::fusion::vector_tie(i)], 4+i);
}

//==============================================================================
// Test for dynamic 2D iliffe_buffer assignment
//==============================================================================
NT2_TEST_CASE_TPL( buffer_2D_assignment, NT2_TYPES)
{
  using nt2::memory::iliffe_buffer;
  using nt2::memory::buffer;

  typedef iliffe_buffer < boost::mpl::size_t<2>
                        , buffer<T,-2>
                        , buffer<T*,1>
                        > buffer_t;

  boost::array<std::size_t,2> ss = {{5,3}};
  buffer_t x, b( ss );

  for ( typename buffer_t::index_type j = 1; j <= 3; ++j )
    for ( typename buffer_t::index_type i = -2; i <= 2; ++i )
      b[boost::fusion::vector_tie(i,j)] = 3+i + 10*j ;

  x = b;

  NT2_TEST_EQUAL(boost::fusion::at_c<0>(x.size()) , 5 );
  NT2_TEST_EQUAL(boost::fusion::at_c<1>(x.size()) , 3 );
  NT2_TEST_EQUAL(boost::fusion::at_c<0>(x.lower()), -2);
  NT2_TEST_EQUAL(boost::fusion::at_c<1>(x.lower()), 1 );
  NT2_TEST_EQUAL(boost::fusion::at_c<0>(x.upper()), 2 );
  NT2_TEST_EQUAL(boost::fusion::at_c<1>(x.upper()), 3 );

  for ( typename buffer_t::index_type j = 1; j <= 3; ++j )
    for ( typename buffer_t::index_type i = -2; i <= 2; ++i )
    NT2_TEST_EQUAL( x[boost::fusion::vector_tie(i,j)], 3+i + 10*j);
}

//==============================================================================
// Test for static 2D iliffe_buffer assignment
//==============================================================================
NT2_TEST_CASE_TPL( buffer_static_2D_assignment, NT2_TYPES)
{
  using nt2::memory::iliffe_buffer;
  using nt2::memory::array_buffer;

  typedef iliffe_buffer < boost::mpl::size_t<2>
                        , array_buffer<T ,15,-2>
                        , array_buffer<T*, 3, 1>
                        > buffer_t;

  boost::array<std::size_t,2> ss = {{5,3}};
  buffer_t x, b( ss );

  for ( typename buffer_t::index_type j = 1; j <= 3; ++j )
    for ( typename buffer_t::index_type i = -2; i <= 2; ++i )
      b[boost::fusion::vector_tie(i,j)] = 3+i + 10*j ;

  x = b;

  NT2_TEST_EQUAL(boost::fusion::at_c<0>(x.size()) , 5 );
  NT2_TEST_EQUAL(boost::fusion::at_c<1>(x.size()) , 3 );
  NT2_TEST_EQUAL(boost::fusion::at_c<0>(x.lower()), -2);
  NT2_TEST_EQUAL(boost::fusion::at_c<1>(x.lower()), 1 );
  NT2_TEST_EQUAL(boost::fusion::at_c<0>(x.upper()), 2 );
  NT2_TEST_EQUAL(boost::fusion::at_c<1>(x.upper()), 3 );

  for ( typename buffer_t::index_type j = 1; j <= 3; ++j )
    for ( typename buffer_t::index_type i = -2; i <= 2; ++i )
    NT2_TEST_EQUAL( x[boost::fusion::vector_tie(i,j)], 3+i + 10*j);
}

//==============================================================================
// Test for dynamic 1D iliffe_buffer swap
//==============================================================================
NT2_TEST_CASE_TPL( buffer_1D_swap, NT2_TYPES)
{
  using nt2::memory::iliffe_buffer;
  using nt2::memory::buffer;

  typedef iliffe_buffer<boost::mpl::size_t<1>, buffer<T,-3>, void> buffer_t;

  buffer_t x(4),b( 7 );

  for ( typename buffer_t::index_type i = -3; i <= 3; ++i )
    b[boost::fusion::vector_tie(i)] = 4+i;

  for ( typename buffer_t::index_type i = -3; i <= 0; ++i )
    x[boost::fusion::vector_tie(i)] = -i;

  swap(b,x);

  NT2_TEST_EQUAL( b.size()  , 4 );
  NT2_TEST_EQUAL( b.lower() , -3);
  NT2_TEST_EQUAL( b.upper() , 0 );

  NT2_TEST_EQUAL( x.size()  , 7 );
  NT2_TEST_EQUAL( x.lower() , -3);
  NT2_TEST_EQUAL( x.upper() , 3 );

  for ( typename buffer_t::index_type i = -3; i <= 3; ++i )
    NT2_TEST_EQUAL( x[boost::fusion::vector_tie(i)], 4+i);

  for ( typename buffer_t::index_type i = -3; i <= 0; ++i )
    NT2_TEST_EQUAL( b[boost::fusion::vector_tie(i)], -i);
}

//==============================================================================
// Test for static 1D iliffe_buffer swap
//==============================================================================
NT2_TEST_CASE_TPL( buffer_static_1D_swap, NT2_TYPES)
{
  using nt2::memory::iliffe_buffer;
  using nt2::memory::array_buffer;

  typedef iliffe_buffer < boost::mpl::size_t<1>
                        , array_buffer<T,7,-3>
                        , void
                        > buffer_t;

  buffer_t x,b;

  for ( typename buffer_t::index_type i = -3; i <= 3; ++i )
    b[boost::fusion::vector_tie(i)] = 4;

  for ( typename buffer_t::index_type i = -3; i <= 3; ++i )
    x[boost::fusion::vector_tie(i)] = 10;

  swap(b,x);

  NT2_TEST_EQUAL( b.size()  , 7 );
  NT2_TEST_EQUAL( b.lower() , -3);
  NT2_TEST_EQUAL( b.upper() , 3 );

  NT2_TEST_EQUAL( x.size()  , 7 );
  NT2_TEST_EQUAL( x.lower() , -3);
  NT2_TEST_EQUAL( x.upper() , 3 );

  for ( typename buffer_t::index_type i = -3; i <= 3; ++i )
    NT2_TEST_EQUAL( x[boost::fusion::vector_tie(i)], 4);

  for ( typename buffer_t::index_type i = -3; i <= 3; ++i )
    NT2_TEST_EQUAL( b[boost::fusion::vector_tie(i)], 10);
}

//==============================================================================
// Test for static 2D iliffe_buffer assignment
//==============================================================================
NT2_TEST_CASE_TPL( buffer_static_2D_swap, NT2_TYPES)
{
  using nt2::memory::iliffe_buffer;
  using nt2::memory::array_buffer;

  typedef iliffe_buffer < boost::mpl::size_t<2>
                        , array_buffer<T ,15,1>
                        , array_buffer<T*, 3,1>
                        > buffer_t;

  buffer_t x, b;

  for ( typename buffer_t::index_type j = 1; j <= 3; ++j )
    for ( typename buffer_t::index_type i = 1; i <= 5; ++i )
      b[boost::fusion::vector_tie(i,j)] = 7;

  for ( typename buffer_t::index_type j = 1; j <= 3; ++j )
    for ( typename buffer_t::index_type i = 1; i <= 5; ++i )
      x[boost::fusion::vector_tie(i,j)] = 9;

  swap(b,x);

  NT2_TEST_EQUAL(boost::fusion::at_c<0>(b.size()) , 5 );
  NT2_TEST_EQUAL(boost::fusion::at_c<1>(b.size()) , 3 );
  NT2_TEST_EQUAL(boost::fusion::at_c<0>(b.lower()), 1);
  NT2_TEST_EQUAL(boost::fusion::at_c<1>(b.lower()), 1 );
  NT2_TEST_EQUAL(boost::fusion::at_c<0>(b.upper()), 5 );
  NT2_TEST_EQUAL(boost::fusion::at_c<1>(b.upper()), 3 );

  NT2_TEST_EQUAL(boost::fusion::at_c<0>(x.size()) , 5 );
  NT2_TEST_EQUAL(boost::fusion::at_c<1>(x.size()) , 3 );
  NT2_TEST_EQUAL(boost::fusion::at_c<0>(x.lower()), 1);
  NT2_TEST_EQUAL(boost::fusion::at_c<1>(x.lower()), 1 );
  NT2_TEST_EQUAL(boost::fusion::at_c<0>(x.upper()), 5 );
  NT2_TEST_EQUAL(boost::fusion::at_c<1>(x.upper()), 3 );

  for ( typename buffer_t::index_type j = 1; j <= 3; ++j )
    for ( typename buffer_t::index_type i = 1; i <= 5; ++i )
    NT2_TEST_EQUAL( x[boost::fusion::vector_tie(i,j)], 7);

  for ( typename buffer_t::index_type j = 1; j <= 3; ++j )
    for ( typename buffer_t::index_type i = 1; i <= 5; ++i )
    NT2_TEST_EQUAL( b[boost::fusion::vector_tie(i,j)], 9);
}
*/
