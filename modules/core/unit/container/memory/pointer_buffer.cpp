/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::memory T* adaptation as a Buffer"

#include <nt2/core/container/memory/pointer_buffer.hpp>
#include <nt2/core/container/memory/dereference.hpp>
#include <nt2/sdk/memory/no_padding.hpp>
#include <boost/type_traits/is_same.hpp>

#include <boost/array.hpp>
#include <boost/fusion/include/mpl.hpp>
#include <boost/fusion/adapted/array.hpp>
#include <boost/fusion/include/single_view.hpp>



#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>

////////////////////////////////////////////////////////////////////////////////
// pointer_buffer type has some dimensions
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL( pointer_buffer_dimensions, NT2_TYPES )
{
  using nt2::meta::dimensions_of;
  using nt2::memory::pointer_buffer;

  typedef pointer_buffer<T> type ;

  NT2_TEST_EQUAL((dimensions_of<type>::value), 1UL );

}


////////////////////////////////////////////////////////////////////////////////
// pointer_buffer type has some value
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL( pointer_buffer_values, NT2_TYPES )
{

  using boost::dispatch::meta::value_of;
  using nt2::memory::pointer_buffer;
  using boost::mpl::_;

  typedef pointer_buffer<T > type ;

  type t1;
  
  NT2_TEST_EXPR_TYPE(t1, value_of<_>, T );

}

////////////////////////////////////////////////////////////////////////////////
// pointer_buffer type has a model
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL( pointer_buffer_model, NT2_TYPES )
{
  using boost::is_same;
  using boost::dispatch::meta::model_of;
  using boost::mpl::apply;
  using nt2::memory::pointer_buffer;

  typedef typename model_of< pointer_buffer<T> >::type model1d;

  NT2_TEST((is_same < typename apply<model1d,float>::type
                    , pointer_buffer<float> >::value
          ));
  
}

////////////////////////////////////////////////////////////////////////////////
// Test for dynamic default pointer_buffer default ctor
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL( pointer_buffer_default_ctor, NT2_TYPES)
{
  using nt2::memory::pointer_buffer;

  typedef pointer_buffer<T> type ;

  type b;

  NT2_TEST_EQUAL(b.size(), 0U );
  NT2_TEST_EQUAL(b.begin(), b.end() );

  boost::array<std::size_t,1> s = {{ 10 }};
  b.resize(s);
 
  NT2_TEST_EQUAL(b.size(), 10 );
  NT2_TEST_NOT_EQUAL(b.begin(), b.end() );


}

////////////////////////////////////////////////////////////////////////////////
// Test for dynamic default pointer_buffer ctor
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL( pointer_buffer_ctor, NT2_TYPES)
{
  using nt2::memory::pointer_buffer;

  typedef pointer_buffer<T> buffer_type ;

  boost::array<std::size_t,1> ss = {{ 5 }};
  boost::array<std::size_t,1> bs = {{ 0 }};

  buffer_type b(ss,bs);

  NT2_TEST_EQUAL(b.size(), 5U );
  NT2_TEST_NOT_EQUAL(b.begin(), b.end() );


}

////////////////////////////////////////////////////////////////////////////////
// Test for dynamic pointer_buffer assignment
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL(pointer_buffer_assignment, NT2_TYPES )
{
  using nt2::memory::pointer_buffer;

  typedef pointer_buffer<T> buffer_type ;

  boost::array<std::size_t,1> ss = {{ 5 }};
  boost::array<std::size_t,1> bs = {{ 0 }};

  buffer_type b,x(ss,bs);

  NT2_TEST_EQUAL(b.size() , 0U );
  NT2_TEST_EQUAL(b.begin(), b.end() );

  b = x;

  NT2_TEST_EQUAL    (b.size() , 5U );
  NT2_TEST_NOT_EQUAL(b.begin(), b.end() );

}


////////////////////////////////////////////////////////////////////////////////
// Test for dynamic pointer_buffer swap
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL(pointer_buffer_swap, NT2_TYPES )
{

  using nt2::memory::pointer_buffer;

  typedef pointer_buffer<T> buffer_type ;

  boost::array<std::size_t,1> sx = { 5 };
  boost::array<std::size_t,1> bx = { 0 };

  boost::array<std::size_t,1> sb = { 3 };
  boost::array<std::size_t,1> bb = { -1 };

  buffer_type b(sb,bb),x(sx,bx);

  swap(b,x);

  NT2_TEST_EQUAL( b.size()      , 5U          );
  NT2_TEST_EQUAL( x.size()      , 3U          );


}


NT2_TEST_CASE_TPL( pointer_bracket, NT2_TYPES)
{
  using boost::is_same;
  using nt2::memory::pointer_buffer;

  boost::array<std::size_t,1> sizes = {{5}};
  boost::array<std::size_t,1> bases = {{-2}};

  T* tab = new T[5];

  for (int n = 0; n < 5; n++){
    tab[n] = n+1;
  }

  typedef pointer_buffer<T> buffer_type ;

  buffer_type b(tab,sizes,bases);

  NT2_TEST_EQUAL    (b.size() , 5U );
  NT2_TEST_NOT_EQUAL(b.begin(), b.end() );


  for ( typename buffer_type::index_type i = -2; i <= 2; ++i )
    NT2_TEST_EQUAL( dereference(b,boost::fusion::single_view<int>(i)), 3+i );

  boost::array<std::size_t,1> sz = {{4}};
  boost::array<std::size_t,1> bs = {{-1}};

  restructure(b,sz,bs);

  NT2_TEST_EQUAL    (b.size() , 4U );


  for ( typename buffer_type::index_type i = -1; i <= 3; ++i )
    NT2_TEST_EQUAL( dereference(b,boost::fusion::single_view<int>(i)), 2+i );

  delete[] tab;

}


