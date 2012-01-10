//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2::memory buffer"

#include <nt2/sdk/memory/buffer.hpp>

#include <algorithm>
#include <boost/array.hpp>
#include <boost/fusion/adapted/array.hpp>
#include <boost/fusion/include/make_vector.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>

//==============================================================================
// buffer value_of traits
//==============================================================================
NT2_TEST_CASE_TPL( buffer_value_of, NT2_TYPES )
{
  using boost::dispatch::meta::value_of;
  using nt2::memory::buffer;
  using boost::mpl::_;

  NT2_TEST_EXPR_TYPE((buffer<T,1>()), value_of<_>, T );
}

//==============================================================================
// buffer model_of traits
//==============================================================================
template<class T, class U>
struct  apply_model
      : boost::mpl::apply < typename boost::dispatch::meta::model_of<T>::type
                          , U
                          >
{};

NT2_TEST_CASE_TPL( buffer_model_of, NT2_TYPES )
{
  using boost::dispatch::meta::model_of;
  using nt2::memory::buffer;
  using boost::mpl::_;

  NT2_TEST_EXPR_TYPE((buffer<int,1>()),(apply_model<_,T>),(buffer<T,1>));
}

//==============================================================================
// Test for dynamic default buffer default ctor
//==============================================================================
NT2_TEST_CASE_TPL( buffer_default_ctor, NT2_TYPES)
{
  using nt2::memory::buffer;

  typedef buffer<T,1> type ;

  type b;

  NT2_TEST_EQUAL(b.size()       , 0 );
  NT2_TEST_EQUAL(b.inner_size() , 0 );
  NT2_TEST_EQUAL(b.outer_size() , 1 );
  NT2_TEST_EQUAL(b.lower()      , 1 );
  NT2_TEST_EQUAL(b.inner_lower(), 1 );
  NT2_TEST_EQUAL(b.outer_lower(), 1 );
  NT2_TEST_EQUAL(b.upper()      , 0 );
  NT2_TEST_EQUAL(b.inner_upper(), 0 );
  NT2_TEST_EQUAL(b.outer_upper(), 1 );
}

//==============================================================================
// Test for dynamic default buffer copy ctor
//==============================================================================
NT2_TEST_CASE_TPL( buffer_copy_ctor, NT2_TYPES)
{
  using nt2::memory::buffer;

  typedef buffer<T,1> type ;

  type b(boost::fusion::make_vector(5));

  for ( typename type::difference_type i = b.lower(); i <= b.upper(); ++i )
  b[boost::fusion::make_vector(i)] = T(3+i);

  type x(b);

  NT2_TEST_EQUAL(x.size()       , 5 );
  NT2_TEST_EQUAL(x.inner_size() , 5 );
  NT2_TEST_EQUAL(x.outer_size() , 1 );
  NT2_TEST_EQUAL(x.lower()      , 1 );
  NT2_TEST_EQUAL(x.inner_lower(), 1 );
  NT2_TEST_EQUAL(x.outer_lower(), 1 );
  NT2_TEST_EQUAL(x.upper()      , 5 );
  NT2_TEST_EQUAL(x.inner_upper(), 5 );
  NT2_TEST_EQUAL(x.outer_upper(), 1 );

  for ( typename type::difference_type i = x.lower(); i <= x.upper(); ++i )
    NT2_TEST_EQUAL( x[boost::fusion::make_vector(i)], T(3+i) );
}

//==============================================================================
// Test for buffer assignment
//==============================================================================
NT2_TEST_CASE_TPL(buffer_assignment, NT2_TYPES )
{
  using nt2::memory::buffer;

  typedef buffer<T,-2> buffer_type ;

  buffer_type x, b(boost::fusion::make_vector(5));

  for ( typename buffer_type::difference_type i = b.lower(); i <= b.upper(); ++i )
    b[boost::fusion::make_vector(i)] = T(3+i);

  x = b;

  NT2_TEST_EQUAL(x.size()       ,  5 );
  NT2_TEST_EQUAL(x.inner_size() ,  5 );
  NT2_TEST_EQUAL(x.outer_size() ,  1 );
  NT2_TEST_EQUAL(x.lower()      , -2 );
  NT2_TEST_EQUAL(x.inner_lower(), -2 );
  NT2_TEST_EQUAL(x.outer_lower(),  1 );
  NT2_TEST_EQUAL(x.upper()      ,  2 );
  NT2_TEST_EQUAL(x.inner_upper(),  2 );
  NT2_TEST_EQUAL(x.outer_upper(),  1 );

  for ( typename buffer_type::difference_type i = x.lower(); i <= x.upper(); ++i )
    NT2_TEST_EQUAL( x[boost::fusion::make_vector(i)], T(3+i) );
}

//==============================================================================
// Test for dynamic buffer swap
//==============================================================================
NT2_TEST_CASE_TPL(buffer_swap, NT2_TYPES )
{
  using nt2::memory::buffer;

  typedef buffer<T,1> buffer_type ;

  buffer_type b(boost::fusion::make_vector<int>(3));
  for ( typename buffer_type::difference_type i = b.lower(); i <= b.upper(); ++i )
    b[boost::fusion::make_vector(i)] = T(10*i) ;

  buffer_type x( boost::fusion::make_vector(5) );
  for ( typename buffer_type::difference_type i = x.lower(); i <= x.upper(); ++i )
    x[boost::fusion::make_vector(i)] = T(3+i) ;

  swap(b,x);

  NT2_TEST_EQUAL(x.size()       ,  3 );
  NT2_TEST_EQUAL(x.inner_size() ,  3 );
  NT2_TEST_EQUAL(x.outer_size() ,  1 );
  NT2_TEST_EQUAL(x.lower()      ,  1 );
  NT2_TEST_EQUAL(x.inner_lower(),  1 );
  NT2_TEST_EQUAL(x.outer_lower(),  1 );
  NT2_TEST_EQUAL(x.upper()      ,  3 );
  NT2_TEST_EQUAL(x.inner_upper(),  3 );
  NT2_TEST_EQUAL(x.outer_upper(),  1 );

  NT2_TEST_EQUAL(b.size()       ,  5 );
  NT2_TEST_EQUAL(b.inner_size() ,  5 );
  NT2_TEST_EQUAL(b.outer_size() ,  1 );
  NT2_TEST_EQUAL(b.lower()      ,  1 );
  NT2_TEST_EQUAL(b.inner_lower(),  1 );
  NT2_TEST_EQUAL(b.outer_lower(),  1 );
  NT2_TEST_EQUAL(b.upper()      ,  5 );
  NT2_TEST_EQUAL(b.inner_upper(),  5 );
  NT2_TEST_EQUAL(b.outer_upper(),  1 );

  for ( typename buffer_type::difference_type i = b.lower(); i <= b.upper(); ++i )
    NT2_TEST_EQUAL( b[boost::fusion::make_vector(i)], T(3+i) );

  for ( typename buffer_type::difference_type i = x.lower(); i <= x.upper(); ++i )
    NT2_TEST_EQUAL( x[boost::fusion::make_vector(i)], T(10*i) );
}

//==============================================================================
// buffer Range interface
//==============================================================================
struct f_
{
  template<class T> T operator()(T const& e) const { return 10*e; }
};

NT2_TEST_CASE_TPL(buffer_iterator, NT2_TYPES )
{
  using nt2::memory::buffer;

  typedef buffer<T,-2> buffer_type ;

  buffer_type x(boost::fusion::make_vector(5));
  for ( typename buffer_type::difference_type i = x.lower(); i <= x.upper(); ++i )
    x[boost::fusion::make_vector(i)] = T(3+i) ;

  f_ f;

  typename buffer_type::iterator b = x.begin();
  typename buffer_type::iterator e = x.end();

  std::transform(b,e,b,f);

  for ( typename buffer_type::difference_type i = x.lower(); i <= x.upper(); ++i )
    NT2_TEST_EQUAL( x[boost::fusion::make_vector(i)], f(3+i) );
}

//==============================================================================
// Test for array_buffer asserting access
//==============================================================================
NT2_TEST_CASE_TPL( buffer_wrong_access, NT2_TYPES)
{
  using nt2::memory::buffer;
  typedef buffer<T,-2> buffer_type ;
  buffer_type b;
  T value;

  NT2_TEST_ASSERT( value  = b[boost::fusion::make_vector(-3)] );
  NT2_TEST_ASSERT( value  = b[boost::fusion::make_vector(9)]  );
  NT2_TEST_ASSERT( b[boost::fusion::make_vector(-5)]  = value );
  NT2_TEST_ASSERT( b[boost::fusion::make_vector(7)]   = value );
}
