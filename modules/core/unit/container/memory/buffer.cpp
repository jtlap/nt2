//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2::memory buffer adaptation as a Buffer"

#include <nt2/core/container/memory/buffer.hpp>

#include <algorithm>
#include <boost/array.hpp>
#include <boost/fusion/adapted/array.hpp>
#include <boost/fusion/include/single_view.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

//==============================================================================
// buffer dimensions traits
//==============================================================================
NT2_TEST_CASE_TPL( buffer_dimensions, NT2_TYPES )
{
  using nt2::meta::dimensions_of;
  using nt2::memory::buffer;
  using boost::mpl::size_t;
  using boost::mpl::_;
  
  NT2_TEST_EXPR_TYPE(buffer<T >(), dimensions_of<_>, size_t<1> );
}

//==============================================================================
// buffer value_of traits
//==============================================================================
NT2_TEST_CASE_TPL( buffer_value_of, NT2_TYPES )
{
  using boost::dispatch::meta::value_of;
  using nt2::memory::buffer;
  using boost::mpl::_;

  NT2_TEST_EXPR_TYPE(buffer<T >(), value_of<_>, T );
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
  
  NT2_TEST_EXPR_TYPE((buffer<int>()),(apply_model<_,T>),(buffer<T>));
}

//==============================================================================
// Test for dynamic default buffer default ctor
//==============================================================================
NT2_TEST_CASE_TPL( buffer_default_ctor, NT2_TYPES)
{
  using nt2::memory::buffer;

  typedef buffer<T> type ;

  type b;

  NT2_TEST_EQUAL(b.size() , 0U );
  NT2_TEST_EQUAL(b.lower(), 0  );
  NT2_TEST_EQUAL(b.upper(), -1 );
}

//==============================================================================
// Test for buffer assignment
//==============================================================================
NT2_TEST_CASE_TPL(buffer_assignment, NT2_TYPES )
{
  using nt2::memory::buffer;

  typedef buffer<T> buffer_type ;

  buffer_type x, b(5,-2);

  for ( typename buffer_type::index_type i = b.lower(); i <= b.upper(); ++i )
    b[i] = 3+i ;

  x = b;
  
  NT2_TEST_EQUAL(x.size() , 5U );
  NT2_TEST_EQUAL(x.lower(), -2 );
  NT2_TEST_EQUAL(x.upper(), 2  );

  for ( typename buffer_type::index_type i = x.lower(); i <= x.upper(); ++i )
    NT2_TEST_EQUAL( x[i], 3+i );
    
}

//==============================================================================
// Test for dynamic buffer swap
//==============================================================================
NT2_TEST_CASE_TPL(buffer_swap, NT2_TYPES )
{
  using nt2::memory::buffer;

  typedef buffer<T> buffer_type ;

  T datax[5] = {1,2,3,4,5};

  buffer_type b(boost::fusion::single_view<int>(3),1);
  for ( typename buffer_type::index_type i = b.lower(); i <= b.upper(); ++i )
    b[i] = 10*i ;

  buffer_type x( 5, boost::fusion::single_view<int>(-2) );
  for ( typename buffer_type::index_type i = x.lower(); i <= x.upper(); ++i )
    x[i] = 3+i ;

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
// buffer Range interface
//==============================================================================
struct f_
{
  template<class T> T operator()(T const& e) const { return 10*e; }
};
  
NT2_TEST_CASE_TPL(buffer_iterator, NT2_TYPES )
{
  using nt2::memory::buffer;

  typedef buffer<T> buffer_type ;

  buffer_type x(5,-2);
  for ( typename buffer_type::index_type i = x.lower(); i <= x.upper(); ++i )
    x[i] = 3+i ;

  f_ f;
  
  typename buffer_type::iterator b = x.begin();
  typename buffer_type::iterator e = x.end();

  std::transform(b,e,b,f);

  for ( typename buffer_type::index_type i = x.lower(); i <= x.upper(); ++i )
    NT2_TEST_EQUAL( x[i], f(3+i) );
}
