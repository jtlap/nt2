//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2::memory T* adaptation as a Buffer"

#include <nt2/core/container/memory/pointer_buffer.hpp>

#include <algorithm>
#include <boost/array.hpp>
#include <boost/fusion/adapted/array.hpp>
#include <boost/fusion/include/single_view.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

//==============================================================================
// pointer_buffer dimensions traits
//==============================================================================
NT2_TEST_CASE_TPL( pointer_buffer_dimensions, NT2_TYPES )
{
  using nt2::meta::dimensions_of;
  using nt2::memory::pointer_buffer;
  using boost::mpl::size_t;
  using boost::mpl::_;
  
  NT2_TEST_EXPR_TYPE(pointer_buffer<T >(), dimensions_of<_>, size_t<1> );
}

//==============================================================================
// pointer_buffer value_of traits
//==============================================================================
NT2_TEST_CASE_TPL( pointer_buffer_value_of, NT2_TYPES )
{
  using boost::dispatch::meta::value_of;
  using nt2::memory::pointer_buffer;
  using boost::mpl::_;

  NT2_TEST_EXPR_TYPE(pointer_buffer<T >(), value_of<_>, T );
}

//==============================================================================
// pointer_buffer model_of traits
//==============================================================================
template<class T, class U>
struct  apply_model
      : boost::mpl::apply < typename boost::dispatch::meta::model_of<T>::type
                          , U
                          >
{};

NT2_TEST_CASE_TPL( pointer_buffer_model_of, NT2_TYPES )
{
  using boost::dispatch::meta::model_of;
  using nt2::memory::pointer_buffer;
  using boost::mpl::_;
  
  NT2_TEST_EXPR_TYPE((pointer_buffer<int>()),(apply_model<_,T>),(pointer_buffer<T>));
}

//==============================================================================
// Test for dynamic default pointer_buffer default ctor
//==============================================================================
NT2_TEST_CASE_TPL( pointer_buffer_default_ctor, NT2_TYPES)
{
  using nt2::memory::pointer_buffer;

  typedef pointer_buffer<T> type ;

  type b;

  NT2_TEST_EQUAL(b.size() , 0U );
  NT2_TEST_EQUAL(b.lower(), 0  );
  NT2_TEST_EQUAL(b.upper(), -1 );
  NT2_TEST_EQUAL(b.begin(), b.end() );
}

//==============================================================================
// Test for dynamic default pointer_buffer ctor
//==============================================================================
NT2_TEST_CASE_TPL( pointer_buffer_data_ctor, NT2_TYPES)
{
  using nt2::memory::pointer_buffer;

  typedef pointer_buffer<T> buffer_type ;

  boost::array<std::size_t,1> ss = {{ 5 }};
  boost::array<std::size_t,1> bs = {{ -2 }};

  T data[5] = {1,2,3,4,5};
  buffer_type b(&data[0],ss,bs);

  NT2_TEST_EQUAL(b.size() , 5U );
  NT2_TEST_EQUAL(b.lower(), -2 );
  NT2_TEST_EQUAL(b.upper(), 2  );

  for ( typename buffer_type::index_type i = b.lower(); i <= b.upper(); ++i )
    NT2_TEST_EQUAL( dereference(b,boost::fusion::single_view<int>(i)), 3+i );
    
  for ( typename buffer_type::index_type i = b.lower(); i <= b.upper(); ++i )
    dereference(b,boost::fusion::single_view<int>(i)) *= 10;

  for( int i=0; i < 5; ++i ) NT2_TEST_EQUAL( data[i], 10*(1+i) );
}

//==============================================================================
// Test for pointer_buffer assignment
//==============================================================================
NT2_TEST_CASE_TPL(pointer_buffer_assignment, NT2_TYPES )
{
  using nt2::memory::pointer_buffer;

  typedef pointer_buffer<T> buffer_type ;

  boost::array<std::size_t,1> ss = {{ 5 }};
  boost::array<std::size_t,1> bs = {{ -2 }};

  T data[5] = {1,2,3,4,5};
  buffer_type x, b(&data[0],ss,bs);

  x = b;
  
  NT2_TEST_EQUAL(x.size() , 5U );
  NT2_TEST_EQUAL(x.lower(), -2 );
  NT2_TEST_EQUAL(x.upper(), 2  );

  for ( typename buffer_type::index_type i = x.lower(); i <= x.upper(); ++i )
    NT2_TEST_EQUAL( dereference(x,boost::fusion::single_view<int>(i)), 3+i );
    
  for ( typename buffer_type::index_type i = x.lower(); i <= x.upper(); ++i )
    dereference(x,boost::fusion::single_view<int>(i)) *= 10;

  for( int i=0; i < 5; ++i ) NT2_TEST_EQUAL( data[i], 10*(1+i) );
}

//==============================================================================
// Test for dynamic pointer_buffer swap
//==============================================================================
NT2_TEST_CASE_TPL(pointer_buffer_swap, NT2_TYPES )
{
  using nt2::memory::pointer_buffer;

  typedef pointer_buffer<T> buffer_type ;

  boost::array<std::size_t,1> sx = { 5  };
  boost::array<std::size_t,1> bx = { -2 };
  T datax[5] = {1,2,3,4,5};

  boost::array<std::size_t,1> sb = { 3 };
  boost::array<std::size_t,1> bb = { 1 };
  T datab[3] = {10,20,30};

  buffer_type b(&datab[0],sb,bb);
  buffer_type x(&datax[0],sx,bx);

  swap(b,x);

  NT2_TEST_EQUAL(b.size() , 5U );
  NT2_TEST_EQUAL(b.lower(), -2 );
  NT2_TEST_EQUAL(b.upper(), 2  );

  NT2_TEST_EQUAL(x.size() , 3U );
  NT2_TEST_EQUAL(x.lower(), 1  );
  NT2_TEST_EQUAL(x.upper(), 3  );

  for ( typename buffer_type::index_type i = b.lower(); i <= b.upper(); ++i )
    NT2_TEST_EQUAL( dereference(b,boost::fusion::single_view<int>(i)), 3+i );
    
  for ( typename buffer_type::index_type i = x.lower(); i <= x.upper(); ++i )
    NT2_TEST_EQUAL( dereference(x,boost::fusion::single_view<int>(i)), 10*i );

  for ( typename buffer_type::index_type i = x.lower(); i <= x.upper(); ++i )
    dereference(x,boost::fusion::single_view<int>(i)) = 9*i;

  for( int i=0; i < 3; ++i ) NT2_TEST_EQUAL( datab[i], 9*(1+i) );
    
  for ( typename buffer_type::index_type i = b.lower(); i <= b.upper(); ++i )
    dereference(b,boost::fusion::single_view<int>(i)) = T(i);

  for( int i=0; i < 5; ++i ) NT2_TEST_EQUAL( datax[i], T(i-2) );
}

//==============================================================================
// pointer_buffer Range interface
//==============================================================================
struct f_
{
  template<class T> T operator()(T const& e) const { return 10*e; }
};
  
NT2_TEST_CASE_TPL(pointer_buffer_iterator, NT2_TYPES )
{
  using nt2::memory::pointer_buffer;

  typedef pointer_buffer<T> buffer_type ;

  boost::array<std::size_t,1> sx = { 5  };
  boost::array<std::size_t,1> bx = { -2 };
  T data[5] = {1,2,3,4,5};

  buffer_type x(&data[0],sx,bx);
  f_ f;
  
  typename buffer_type::iterator b = x.begin();
  typename buffer_type::iterator e = x.end();

  std::transform(b,e,b,f);

  for ( typename buffer_type::index_type i = x.lower(); i <= x.upper(); ++i )
    NT2_TEST_EQUAL( dereference(x,boost::fusion::single_view<int>(i)), f(3+i) );
  
  for( int i=0; i < 5; ++i ) NT2_TEST_EQUAL( data[i], f(i+1) );
}

//==============================================================================
// pointer_buffer as_buffer
//==============================================================================
NT2_TEST_CASE_TPL(pointer_buffer_as_buffer, NT2_TYPES )
{
  using nt2::memory::pointer_buffer;
  using nt2::meta::as_buffer;

  typedef pointer_buffer<T> buffer_type ;

  boost::array<std::size_t,1> sx = { 5  };
  boost::array<std::size_t,1> bx = { -2 };
  T data[5] = {1,2,3,4,5};
  buffer_type x;

  x = as_buffer<T*>()(&data[0],sx,bx);


  for ( typename buffer_type::index_type i = x.lower(); i <= x.upper(); ++i )
    NT2_TEST_EQUAL( dereference(x,boost::fusion::single_view<int>(i)), 3+i );
  
}
