//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2::memory iliffe_buffer"

#include <nt2/sdk/memory/buffer.hpp>
#include <nt2/sdk/memory/array_buffer.hpp>
#include <nt2/sdk/memory/iliffe_buffer.hpp>
#include <nt2/sdk/memory/fixed_allocator.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>

#include <boost/fusion/include/vector_tie.hpp>
#include <boost/fusion/include/make_vector.hpp>

#define DIMS                                    \
(boost::mpl::size_t<1>)(boost::mpl::size_t<2>)  \
(boost::mpl::size_t<3>)(boost::mpl::size_t<4>)  \
/**/

//==============================================================================
// iliffe_buffer type has some dimensions
//==============================================================================
NT2_TEST_CASE_TPL( iliffe_buffer_dimensions, DIMS )
{
  using nt2::memory::iliffe_buffer;
  using nt2::meta::dimensions_of;
  using nt2::memory::buffer;

  typedef iliffe_buffer<T, buffer<int,1>, buffer<int*,1> > type;

  NT2_TEST_EQUAL((dimensions_of<type>::value), T::value );
}

//==============================================================================
// iliffe_buffer type has some value
//==============================================================================
NT2_TEST_CASE_TPL( iliffe_buffer_values, NT2_TYPES )
{
  using boost::dispatch::meta::value_of;
  using nt2::memory::iliffe_buffer;
  using nt2::memory::buffer;
  using boost::mpl::_;

  NT2_TEST_EXPR_TYPE
  ( (iliffe_buffer<boost::mpl::size_t<1>, buffer<T,1>, void >())
  , value_of<_>
  , T
  );
}

//==============================================================================
// iliffe_buffer type has a model
//==============================================================================
template<class T, class U>
struct  apply_model
      : boost::mpl::apply < typename boost::dispatch::meta::model_of<T>::type
                          , U
                          >
{};

NT2_TEST_CASE_TPL( iliffe_buffer_models, NT2_TYPES )
{
  using boost::dispatch::meta::model_of;
  using nt2::memory::iliffe_buffer;
  using nt2::memory::buffer;
  using boost::mpl::_;

  NT2_TEST_EXPR_TYPE
  ( (iliffe_buffer<boost::mpl::size_t<1>, buffer<int,1>, void >())
  , (apply_model<_,T>)
  , (iliffe_buffer<boost::mpl::size_t<1>, buffer<T,1>, T >)
  );
}

//==============================================================================
// Test for 1D dynamic iliffe_ buffer default ctor
//==============================================================================
NT2_TEST_CASE_TPL( iliffe_buffer_dynamic_1D_default_ctor, NT2_TYPES)
{
  using boost::fusion::at_c;
  using nt2::memory::buffer;
  using nt2::memory::iliffe_buffer;

  typedef iliffe_buffer<boost::mpl::size_t<1>,buffer<T,-2>,void> buffer_t;

  buffer_t b;

  NT2_TEST_EQUAL(b.size()       ,  0 );
  NT2_TEST_EQUAL(b.inner_size() ,  0 );
  NT2_TEST_EQUAL(b.outer_size() ,  1 );
  NT2_TEST_EQUAL(b.lower()      , -2 );
  NT2_TEST_EQUAL(b.inner_lower(), -2 );
  NT2_TEST_EQUAL(b.outer_lower(),  1 );
  NT2_TEST_EQUAL(b.upper()      , -3 );
  NT2_TEST_EQUAL(b.inner_upper(), -3 );
  NT2_TEST_EQUAL(b.outer_upper(),  1 );
}

//==============================================================================
// Test for 1D automatic iliffe_ buffer default ctor
//==============================================================================
NT2_TEST_CASE_TPL( iliffe_buffer_automatic_1D_default_ctor, NT2_TYPES)
{
  using boost::fusion::at_c;
  using nt2::memory::array_buffer;
  using nt2::memory::iliffe_buffer;

  typedef iliffe_buffer<boost::mpl::size_t<1>,array_buffer<T,5,-2>,void> buffer_t;

  buffer_t b;

  NT2_TEST_EQUAL(b.size()       ,  5 );
  NT2_TEST_EQUAL(b.inner_size() ,  5 );
  NT2_TEST_EQUAL(b.outer_size() ,  1 );
  NT2_TEST_EQUAL(b.lower()      , -2 );
  NT2_TEST_EQUAL(b.inner_lower(), -2 );
  NT2_TEST_EQUAL(b.outer_lower(),  1 );
  NT2_TEST_EQUAL(b.upper()      ,  2 );
  NT2_TEST_EQUAL(b.inner_upper(),  2 );
  NT2_TEST_EQUAL(b.outer_upper(),  1 );
}

//==============================================================================
// Test for nD dynamic iliffe_ buffer default ctor
//==============================================================================
NT2_TEST_CASE_TPL( iliffe_buffer_dynamic_nD_default_ctor, NT2_TYPES)
{
  using boost::fusion::at_c;
  using nt2::memory::buffer;
  using nt2::memory::iliffe_buffer;

  typedef iliffe_buffer < boost::mpl::size_t<2>
                        , buffer<T,-2>
                        , buffer<T*,1>
                        > buffer_t;

  buffer_t b;

  NT2_TEST_EQUAL(b.size()       ,  0 );
  NT2_TEST_EQUAL(b.inner_size() ,  0 );
  NT2_TEST_EQUAL(b.outer_size() ,  0 );
  NT2_TEST_EQUAL(b.lower()      , -2 );
  NT2_TEST_EQUAL(b.inner_lower(), -2 );
  NT2_TEST_EQUAL(b.outer_lower(),  1 );
  NT2_TEST_EQUAL(b.upper()      , -3 );
  NT2_TEST_EQUAL(b.inner_upper(), -3 );
  NT2_TEST_EQUAL(b.outer_upper(),  0 );
}

//==============================================================================
// Test for nD static iliffe_ buffer default ctor
//==============================================================================
NT2_TEST_CASE_TPL( iliffe_buffer_automatic_nD_default_ctor, NT2_TYPES)
{
  using boost::fusion::at_c;
  using nt2::memory::array_buffer;
  using nt2::memory::iliffe_buffer;

  typedef iliffe_buffer < boost::mpl::size_t<2>
                        , array_buffer<T ,7*8,-2>
                        , array_buffer<T*,  8, 1>
                        > buffer_t;

  buffer_t b;

  NT2_TEST_EQUAL(b.size()       ,  56 );
  NT2_TEST_EQUAL(b.inner_size() ,   7 );
  NT2_TEST_EQUAL(b.outer_size() ,   8 );
  NT2_TEST_EQUAL(b.lower()      ,  -2 );
  NT2_TEST_EQUAL(b.inner_lower(),  -2 );
  NT2_TEST_EQUAL(b.outer_lower(),   1 );
  NT2_TEST_EQUAL(b.upper()      ,  53 );
  NT2_TEST_EQUAL(b.inner_upper(),   4 );
  NT2_TEST_EQUAL(b.outer_upper(),   8 );
}

//==============================================================================
// Test for 2D static [1 N] ]iliffe_ buffer default ctor
//==============================================================================
NT2_TEST_CASE_TPL( iliffe_buffer_automatic__nD_default_ctor, NT2_TYPES)
{
  using boost::fusion::at_c;
  using nt2::memory::array_buffer;
  using nt2::memory::iliffe_buffer;

  typedef iliffe_buffer < boost::mpl::size_t<2>
                        , array_buffer<T ,7, 1>
                        , array_buffer<T*,7,-2>
                        > buffer_t;

  buffer_t b;

  NT2_TEST_EQUAL(b.size()       ,   7 );
  NT2_TEST_EQUAL(b.inner_size() ,   1 );
  NT2_TEST_EQUAL(b.outer_size() ,   7 );
  NT2_TEST_EQUAL(b.lower()      ,   1 );
  NT2_TEST_EQUAL(b.inner_lower(),   1 );
  NT2_TEST_EQUAL(b.outer_lower(),  -2 );
  NT2_TEST_EQUAL(b.upper()      ,   7 );
  NT2_TEST_EQUAL(b.inner_upper(),   1 );
  NT2_TEST_EQUAL(b.outer_upper(),   4 );
}

//==============================================================================
// Test for dynamic 1D iliffe_buffer copy ctor
//==============================================================================
NT2_TEST_CASE_TPL( buffer_1D_copy_ctor, NT2_TYPES)
{
  using boost::fusion::at_c;
  using nt2::memory::buffer;
  using nt2::memory::iliffe_buffer;

  typedef iliffe_buffer<boost::mpl::size_t<1>, buffer<T,-3>, void> buffer_t;

  buffer_t b( 7 );

  for ( typename buffer_t::difference_type i = -3; i <= 3; ++i )
    b[boost::fusion::vector_tie(i)] = 4+i;

  buffer_t x(b);

  NT2_TEST_EQUAL(x.size()       ,    7 );
  NT2_TEST_EQUAL(x.inner_size() ,    7 );
  NT2_TEST_EQUAL(x.outer_size() ,    1 );
  NT2_TEST_EQUAL(x.lower()      ,   -3 );
  NT2_TEST_EQUAL(x.inner_lower(),   -3 );
  NT2_TEST_EQUAL(x.outer_lower(),    1 );
  NT2_TEST_EQUAL(x.upper()      ,    3 );
  NT2_TEST_EQUAL(x.inner_upper(),    3 );
  NT2_TEST_EQUAL(x.outer_upper(),    1 );

  for ( typename buffer_t::difference_type i = -3; i <= 3; ++i )
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

  for ( typename buffer_t::difference_type i = -3; i <= 3; ++i )
    b[boost::fusion::vector_tie(i)] = 4+i;

  buffer_t x(b);

  NT2_TEST_EQUAL(x.size()       ,    7 );
  NT2_TEST_EQUAL(x.inner_size() ,    7 );
  NT2_TEST_EQUAL(x.outer_size() ,    1 );
  NT2_TEST_EQUAL(x.lower()      ,   -3 );
  NT2_TEST_EQUAL(x.inner_lower(),   -3 );
  NT2_TEST_EQUAL(x.outer_lower(),    1 );
  NT2_TEST_EQUAL(x.upper()      ,    3 );
  NT2_TEST_EQUAL(x.inner_upper(),    3 );
  NT2_TEST_EQUAL(x.outer_upper(),    1 );

  for ( typename buffer_t::difference_type i = -3; i <= 3; ++i )
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

  for ( typename buffer_t::difference_type j = 1; j <= 3; ++j )
    for ( typename buffer_t::difference_type i = -2; i <= 2; ++i )
      b[boost::fusion::vector_tie(i,j)] = 3+i + 10*j ;

  buffer_t x(b);

  NT2_TEST_EQUAL(x.size()       ,  15 );
  NT2_TEST_EQUAL(x.inner_size() ,   5 );
  NT2_TEST_EQUAL(x.outer_size() ,   3 );
  NT2_TEST_EQUAL(x.lower()      ,  -2 );
  NT2_TEST_EQUAL(x.inner_lower(),  -2 );
  NT2_TEST_EQUAL(x.outer_lower(),   1 );
  NT2_TEST_EQUAL(x.upper()      ,  12 );
  NT2_TEST_EQUAL(x.inner_upper(),   2 );
  NT2_TEST_EQUAL(x.outer_upper(),   3 );

  for ( typename buffer_t::difference_type j = 1; j <= 3; ++j )
    for ( typename buffer_t::difference_type i = -2; i <= 2; ++i )
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

  for ( typename buffer_t::difference_type j = 1; j <= 3; ++j )
    for ( typename buffer_t::difference_type i = -2; i <= 2; ++i )
      b[boost::fusion::vector_tie(i,j)] = 3+i + 10*j ;

  buffer_t x(b);

  NT2_TEST_EQUAL(x.size()       ,  15 );
  NT2_TEST_EQUAL(x.inner_size() ,   5 );
  NT2_TEST_EQUAL(x.outer_size() ,   3 );
  NT2_TEST_EQUAL(x.lower()      ,  -2 );
  NT2_TEST_EQUAL(x.inner_lower(),  -2 );
  NT2_TEST_EQUAL(x.outer_lower(),   1 );
  NT2_TEST_EQUAL(x.upper()      ,  12 );
  NT2_TEST_EQUAL(x.inner_upper(),   2 );
  NT2_TEST_EQUAL(x.outer_upper(),   3 );

  for ( typename buffer_t::difference_type j = 1; j <= 3; ++j )
    for ( typename buffer_t::difference_type i = -2; i <= 2; ++i )
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

  for ( typename buffer_t::difference_type i = -3; i <= 3; ++i )
    b[boost::fusion::vector_tie(i)] = 4+i;

  x = b;

  NT2_TEST_EQUAL(x.size()       ,    7 );
  NT2_TEST_EQUAL(x.inner_size() ,    7 );
  NT2_TEST_EQUAL(x.outer_size() ,    1 );
  NT2_TEST_EQUAL(x.lower()      ,   -3 );
  NT2_TEST_EQUAL(x.inner_lower(),   -3 );
  NT2_TEST_EQUAL(x.outer_lower(),    1 );
  NT2_TEST_EQUAL(x.upper()      ,    3 );
  NT2_TEST_EQUAL(x.inner_upper(),    3 );
  NT2_TEST_EQUAL(x.outer_upper(),    1 );

  for ( typename buffer_t::difference_type i = -3; i <= 3; ++i )
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

  for ( typename buffer_t::difference_type i = -3; i <= 3; ++i )
    b[boost::fusion::vector_tie(i)] = 4+i;

  x = b;

  NT2_TEST_EQUAL(x.size()       ,    7 );
  NT2_TEST_EQUAL(x.inner_size() ,    7 );
  NT2_TEST_EQUAL(x.outer_size() ,    1 );
  NT2_TEST_EQUAL(x.lower()      ,   -3 );
  NT2_TEST_EQUAL(x.inner_lower(),   -3 );
  NT2_TEST_EQUAL(x.outer_lower(),    1 );
  NT2_TEST_EQUAL(x.upper()      ,    3 );
  NT2_TEST_EQUAL(x.inner_upper(),    3 );
  NT2_TEST_EQUAL(x.outer_upper(),    1 );

  for ( typename buffer_t::difference_type i = -3; i <= 3; ++i )
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

  for ( typename buffer_t::difference_type j = 1; j <= 3; ++j )
    for ( typename buffer_t::difference_type i = -2; i <= 2; ++i )
      b[boost::fusion::vector_tie(i,j)] = 3+i + 10*j ;

  x = b;

  NT2_TEST_EQUAL(x.size()       ,  15 );
  NT2_TEST_EQUAL(x.inner_size() ,   5 );
  NT2_TEST_EQUAL(x.outer_size() ,   3 );
  NT2_TEST_EQUAL(x.lower()      ,  -2 );
  NT2_TEST_EQUAL(x.inner_lower(),  -2 );
  NT2_TEST_EQUAL(x.outer_lower(),   1 );
  NT2_TEST_EQUAL(x.upper()      ,  12 );
  NT2_TEST_EQUAL(x.inner_upper(),   2 );
  NT2_TEST_EQUAL(x.outer_upper(),   3 );

  for ( typename buffer_t::difference_type j = 1; j <= 3; ++j )
    for ( typename buffer_t::difference_type i = -2; i <= 2; ++i )
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

  for ( typename buffer_t::difference_type j = 1; j <= 3; ++j )
    for ( typename buffer_t::difference_type i = -2; i <= 2; ++i )
      b[boost::fusion::vector_tie(i,j)] = 3+i + 10*j ;

  x = b;

  NT2_TEST_EQUAL(x.size()       ,  15 );
  NT2_TEST_EQUAL(x.inner_size() ,   5 );
  NT2_TEST_EQUAL(x.outer_size() ,   3 );
  NT2_TEST_EQUAL(x.lower()      ,  -2 );
  NT2_TEST_EQUAL(x.inner_lower(),  -2 );
  NT2_TEST_EQUAL(x.outer_lower(),   1 );
  NT2_TEST_EQUAL(x.upper()      ,  12 );
  NT2_TEST_EQUAL(x.inner_upper(),   2 );
  NT2_TEST_EQUAL(x.outer_upper(),   3 );

  for ( typename buffer_t::difference_type j = 1; j <= 3; ++j )
    for ( typename buffer_t::difference_type i = -2; i <= 2; ++i )
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

  for ( typename buffer_t::difference_type i = -3; i <= 3; ++i )
    b[boost::fusion::vector_tie(i)] = 4+i;

  for ( typename buffer_t::difference_type i = -3; i <= 0; ++i )
    x[boost::fusion::vector_tie(i)] = -i;

  swap(b,x);

  NT2_TEST_EQUAL( b.size()  , 4 );
  NT2_TEST_EQUAL( b.lower() , -3);
  NT2_TEST_EQUAL( b.upper() , 0 );

  NT2_TEST_EQUAL(b.size()       ,    4 );
  NT2_TEST_EQUAL(b.inner_size() ,    4 );
  NT2_TEST_EQUAL(b.outer_size() ,    1 );
  NT2_TEST_EQUAL(b.lower()      ,   -3 );
  NT2_TEST_EQUAL(b.inner_lower(),   -3 );
  NT2_TEST_EQUAL(b.outer_lower(),    1 );
  NT2_TEST_EQUAL(b.upper()      ,    0 );
  NT2_TEST_EQUAL(b.inner_upper(),    0 );
  NT2_TEST_EQUAL(b.outer_upper(),    1 );

  NT2_TEST_EQUAL(x.size()       ,    7 );
  NT2_TEST_EQUAL(x.inner_size() ,    7 );
  NT2_TEST_EQUAL(x.outer_size() ,    1 );
  NT2_TEST_EQUAL(x.lower()      ,   -3 );
  NT2_TEST_EQUAL(x.inner_lower(),   -3 );
  NT2_TEST_EQUAL(x.outer_lower(),    1 );
  NT2_TEST_EQUAL(x.upper()      ,    3 );
  NT2_TEST_EQUAL(x.inner_upper(),    3 );
  NT2_TEST_EQUAL(x.outer_upper(),    1 );

  for ( typename buffer_t::difference_type i = -3; i <= 3; ++i )
    NT2_TEST_EQUAL( x[boost::fusion::vector_tie(i)], 4+i);

  for ( typename buffer_t::difference_type i = -3; i <= 0; ++i )
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

  for ( typename buffer_t::difference_type i = -3; i <= 3; ++i )
    b[boost::fusion::vector_tie(i)] = 4;

  for ( typename buffer_t::difference_type i = -3; i <= 3; ++i )
    x[boost::fusion::vector_tie(i)] = 10;

  swap(b,x);

  NT2_TEST_EQUAL(b.size()       ,    7 );
  NT2_TEST_EQUAL(b.inner_size() ,    7 );
  NT2_TEST_EQUAL(b.outer_size() ,    1 );
  NT2_TEST_EQUAL(b.lower()      ,   -3 );
  NT2_TEST_EQUAL(b.inner_lower(),   -3 );
  NT2_TEST_EQUAL(b.outer_lower(),    1 );
  NT2_TEST_EQUAL(b.upper()      ,    3 );
  NT2_TEST_EQUAL(b.inner_upper(),    3 );
  NT2_TEST_EQUAL(b.outer_upper(),    1 );

  NT2_TEST_EQUAL(x.size()       ,    7 );
  NT2_TEST_EQUAL(x.inner_size() ,    7 );
  NT2_TEST_EQUAL(x.outer_size() ,    1 );
  NT2_TEST_EQUAL(x.lower()      ,   -3 );
  NT2_TEST_EQUAL(x.inner_lower(),   -3 );
  NT2_TEST_EQUAL(x.outer_lower(),    1 );
  NT2_TEST_EQUAL(x.upper()      ,    3 );
  NT2_TEST_EQUAL(x.inner_upper(),    3 );
  NT2_TEST_EQUAL(x.outer_upper(),    1 );

  for ( typename buffer_t::difference_type i = -3; i <= 3; ++i )
    NT2_TEST_EQUAL( x[boost::fusion::vector_tie(i)], 4);

  for ( typename buffer_t::difference_type i = -3; i <= 3; ++i )
    NT2_TEST_EQUAL( b[boost::fusion::vector_tie(i)], 10);
}

//==============================================================================
// Test for static 2D iliffe_buffer swap
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

  for ( typename buffer_t::difference_type j = 1; j <= 3; ++j )
    for ( typename buffer_t::difference_type i = 1; i <= 5; ++i )
      b[boost::fusion::vector_tie(i,j)] = 7;

  for ( typename buffer_t::difference_type j = 1; j <= 3; ++j )
    for ( typename buffer_t::difference_type i = 1; i <= 5; ++i )
      x[boost::fusion::vector_tie(i,j)] = 9;

  swap(b,x);

  NT2_TEST_EQUAL(b.size()       ,   15 );
  NT2_TEST_EQUAL(b.inner_size() ,    5 );
  NT2_TEST_EQUAL(b.outer_size() ,    3 );
  NT2_TEST_EQUAL(b.lower()      ,    1 );
  NT2_TEST_EQUAL(b.inner_lower(),    1 );
  NT2_TEST_EQUAL(b.outer_lower(),    1 );
  NT2_TEST_EQUAL(b.upper()      ,   15 );
  NT2_TEST_EQUAL(b.inner_upper(),    5 );
  NT2_TEST_EQUAL(b.outer_upper(),    3 );

  NT2_TEST_EQUAL(x.size()       ,   15 );
  NT2_TEST_EQUAL(x.inner_size() ,    5 );
  NT2_TEST_EQUAL(x.outer_size() ,    3 );
  NT2_TEST_EQUAL(x.lower()      ,    1 );
  NT2_TEST_EQUAL(x.inner_lower(),    1 );
  NT2_TEST_EQUAL(x.outer_lower(),    1 );
  NT2_TEST_EQUAL(x.upper()      ,   15 );
  NT2_TEST_EQUAL(x.inner_upper(),    5 );
  NT2_TEST_EQUAL(x.outer_upper(),    3 );

  for ( typename buffer_t::difference_type j = 1; j <= 3; ++j )
    for ( typename buffer_t::difference_type i = 1; i <= 5; ++i )
    NT2_TEST_EQUAL( x[boost::fusion::vector_tie(i,j)], 7);

  for ( typename buffer_t::difference_type j = 1; j <= 3; ++j )
    for ( typename buffer_t::difference_type i = 1; i <= 5; ++i )
    NT2_TEST_EQUAL( b[boost::fusion::vector_tie(i,j)], 9);
}
