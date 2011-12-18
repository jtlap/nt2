//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2::memory boost::array adaptation as a Buffer"

#include <nt2/core/container/memory/array_buffer.hpp>

#include <algorithm>
#include <boost/array.hpp>
#include <boost/fusion/adapted/array.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

//==============================================================================
// array_buffer dimensions traits
//==============================================================================
NT2_TEST_CASE_TPL( array_buffer_dimensions, NT2_TYPES )
{
  using nt2::meta::dimensions_of;
  using nt2::memory::array_buffer;
  using boost::mpl::size_t;
  using boost::mpl::_;

  typedef array_buffer<T,2> buffer_type;

  NT2_TEST_EXPR_TYPE(buffer_type(), dimensions_of<_>, size_t<1> );
}

//==============================================================================
// array_buffer value_of traits
//==============================================================================
NT2_TEST_CASE_TPL( array_buffer_value_of, NT2_TYPES )
{
  using boost::dispatch::meta::value_of;
  using nt2::memory::array_buffer;
  using boost::mpl::_;

  typedef array_buffer<T,2> buffer_type;

  NT2_TEST_EXPR_TYPE(buffer_type(), value_of<_>, T );
}

//==============================================================================
// array_buffer model_of traits
//==============================================================================
template<class T, class U>
struct  apply_model
      : boost::mpl::apply < typename boost::dispatch::meta::model_of<T>::type
                          , U
                          >
{};

NT2_TEST_CASE_TPL( array_buffer_model_of, NT2_TYPES )
{
  using boost::dispatch::meta::model_of;
  using nt2::memory::array_buffer;
  using boost::mpl::_;

  typedef array_buffer<char,2> buffer_type;  

  NT2_TEST_EXPR_TYPE((buffer_type()),(apply_model<_,T>),(array_buffer<T,2>));
}

//==============================================================================
// Test for dynamic default array_buffer default ctor
//==============================================================================
NT2_TEST_CASE_TPL( array_buffer_default_ctor, NT2_TYPES)
{
  using nt2::memory::array_buffer;

  typedef array_buffer<T,2> type ;

  type b;

  NT2_TEST_EQUAL(b.size() , 0U );
  NT2_TEST_EQUAL(b.lower(), 0  );
  NT2_TEST_EQUAL(b.upper(), -1 );
  NT2_TEST_EQUAL(b.begin(), b.end() );
}

//==============================================================================
// Test for dynamic default array_buffer ctor
//==============================================================================
NT2_TEST_CASE_TPL( array_buffer_data_ctor, NT2_TYPES)
{
  using nt2::memory::array_buffer;
  typedef array_buffer<T,5> buffer_type ;

  boost::array<std::size_t,1> ss = {{ 5 }};
  boost::array<std::size_t,1> bs = {{ -2 }};

  boost::array<T,5> data = {{1,2,3,4,5}};

  buffer_type b(data,ss,bs);

  NT2_TEST_EQUAL(b.size() , 5U );
  NT2_TEST_EQUAL(b.lower(), -2 );
  NT2_TEST_EQUAL(b.upper(), 2  );

  for ( typename buffer_type::index_type i = b.lower(); i <= b.upper(); ++i )
    NT2_TEST_EQUAL( b[i], 3+i );
}

//==============================================================================
// Test for array_buffer assignment
//==============================================================================
NT2_TEST_CASE_TPL(array_buffer_assignment, NT2_TYPES )
{
  using nt2::memory::array_buffer;

  typedef array_buffer<T,5> buffer_type ;

  boost::array<std::size_t,1> ss = {{ 5 }};
  boost::array<std::size_t,1> bs = {{ -2 }};

  boost::array<T,5> data = {{1,2,3,4,5}};
  buffer_type x, b(data,ss,bs);

  x = b;
  
  NT2_TEST_EQUAL(x.size() , 5U );
  NT2_TEST_EQUAL(x.lower(), -2 );
  NT2_TEST_EQUAL(x.upper(), 2  );

  for ( typename buffer_type::index_type i = x.lower(); i <= x.upper(); ++i )
    NT2_TEST_EQUAL( x[i], 3+i );    
}

//==============================================================================
// Test for dynamic array_buffer swap
//==============================================================================
NT2_TEST_CASE_TPL(array_buffer_swap, NT2_TYPES )
{
  using nt2::memory::array_buffer;

  typedef array_buffer<T,5> buffer_type ;

  boost::array<std::size_t,1> sx = { 5  };
  boost::array<std::size_t,1> bx = { -2 };
  boost::array<T,5> datax = {{1,2,3,4,5}};

  boost::array<std::size_t,1> sb = { 3 };
  boost::array<std::size_t,1> bb = { 1 };
  boost::array<T,5> datab = {{10,20,30,40,50}};

  buffer_type b(datab,sb,bb);
  buffer_type x(datax,sx,bx);

  swap(b,x);

  NT2_TEST_EQUAL(b.size() , 5U );
  NT2_TEST_EQUAL(b.lower(), -2 );
  NT2_TEST_EQUAL(b.upper(), 2  );

  NT2_TEST_EQUAL(x.size() , 3U );
  NT2_TEST_EQUAL(x.lower(), 1  );
  NT2_TEST_EQUAL(x.upper(), 3  );

  for ( typename buffer_type::index_type i = b.lower(); i <= b.upper(); ++i )
    NT2_TEST_EQUAL( b[i], 3+i );
    
  for ( typename buffer_type::index_type i = x.lower(); i <= x.upper(); ++i )
    NT2_TEST_EQUAL( x[i], 10*i );

}

//==============================================================================
// array_buffer Range interface
//==============================================================================
struct f_
{
  template<class T> T operator()(T const& e) const { return 10*e; }
};
  
NT2_TEST_CASE_TPL(array_buffer_iterator, NT2_TYPES )
{
  using nt2::memory::array_buffer;

  typedef array_buffer<T,5> buffer_type ;

  boost::array<std::size_t,1> sx = { 5  };
  boost::array<std::size_t,1> bx = { -2 };
  boost::array<T,5> data = {{1,2,3,4,5}};

  buffer_type x(data,sx,bx);
  f_ f;
  
  typename buffer_type::iterator b = x.begin();
  typename buffer_type::iterator e = x.end();

  std::transform(b,e,b,f);

  for ( typename buffer_type::index_type i = x.lower(); i <= x.upper(); ++i )
    NT2_TEST_EQUAL( x[i], f(3+i) );
}
