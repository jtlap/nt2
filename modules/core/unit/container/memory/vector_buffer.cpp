//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2::memory std::vector adaptation as a Buffer"

#include <nt2/core/container/memory/vector_buffer.hpp>

#include <algorithm>
#include <boost/array.hpp>
#include <boost/fusion/adapted/array.hpp>
#include <boost/fusion/include/single_view.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

//==============================================================================
// vector_buffer dimensions traits
//==============================================================================
NT2_TEST_CASE_TPL( vector_buffer_dimensions, NT2_TYPES )
{
  using nt2::meta::dimensions_of;
  using nt2::memory::vector_buffer;
  using boost::mpl::size_t;
  using boost::mpl::_;
  
  NT2_TEST_EXPR_TYPE(vector_buffer<T >(), dimensions_of<_>, size_t<1> );
}

//==============================================================================
// vector_buffer value_of traits
//==============================================================================
NT2_TEST_CASE_TPL( vector_buffer_value_of, NT2_TYPES )
{
  using boost::dispatch::meta::value_of;
  using nt2::memory::vector_buffer;
  using boost::mpl::_;

  NT2_TEST_EXPR_TYPE(vector_buffer<T >(), value_of<_>, T );
}

//==============================================================================
// vector_buffer model_of traits
//==============================================================================
template<class T, class U>
struct  apply_model
      : boost::mpl::apply < typename boost::dispatch::meta::model_of<T>::type
                          , U
                          >
{};

NT2_TEST_CASE_TPL( vector_buffer_model_of, NT2_TYPES )
{
  using boost::dispatch::meta::model_of;
  using nt2::memory::vector_buffer;
  using boost::mpl::_;
  
  NT2_TEST_EXPR_TYPE((vector_buffer<int>()),(apply_model<_,T>),(vector_buffer<T>));
}

//==============================================================================
// Test for dynamic default vector_buffer default ctor
//==============================================================================
NT2_TEST_CASE_TPL( vector_buffer_default_ctor, NT2_TYPES)
{
  using nt2::memory::vector_buffer;

  typedef vector_buffer<T> type ;

  type b;

  NT2_TEST_EQUAL(b.size() , 0U );
  NT2_TEST_EQUAL(b.lower(), 0  );
  NT2_TEST_EQUAL(b.upper(), -1 );
}

//==============================================================================
// Test for dynamic default vector_buffer ctor
//==============================================================================
NT2_TEST_CASE_TPL( vector_buffer_data_ctor, NT2_TYPES)
{
  using nt2::memory::vector_buffer;

  typedef vector_buffer<T> buffer_type ;

  boost::array<std::size_t,1> ss = {{ 5 }};
  boost::array<std::size_t,1> bs = {{ -2 }};

  std::vector<T> data(5);
  for (int n=0; n<data.size(); n++) data[n]=n+1;

  buffer_type b(data,ss,bs);

  NT2_TEST_EQUAL(b.size() , 5U );
  NT2_TEST_EQUAL(b.lower(), -2 );
  NT2_TEST_EQUAL(b.upper(), 2  );

  for ( typename buffer_type::index_type i = b.lower(); i <= b.upper(); ++i )
    NT2_TEST_EQUAL( dereference(b,boost::fusion::single_view<int>(i)), 3+i );
    
}

//==============================================================================
// Test for vector_buffer assignment
//==============================================================================
NT2_TEST_CASE_TPL(vector_buffer_assignment, NT2_TYPES )
{
  using nt2::memory::vector_buffer;

  typedef vector_buffer<T> buffer_type ;

  boost::array<std::size_t,1> ss = {{ 5 }};
  boost::array<std::size_t,1> bs = {{ -2 }};

  std::vector<T> data(5);
  for (int n=0; n<data.size(); n++) data[n]=n+1;

  buffer_type x, b(data,ss,bs);

  x = b;
  
  NT2_TEST_EQUAL(x.size() , 5U );
  NT2_TEST_EQUAL(x.lower(), -2 );
  NT2_TEST_EQUAL(x.upper(), 2  );

  for ( typename buffer_type::index_type i = x.lower(); i <= x.upper(); ++i )
    NT2_TEST_EQUAL( dereference(x,boost::fusion::single_view<int>(i)), 3+i );
    
}

//==============================================================================
// Test for dynamic vector_buffer swap
//==============================================================================
NT2_TEST_CASE_TPL(vector_buffer_swap, NT2_TYPES )
{
  using nt2::memory::vector_buffer;

  typedef vector_buffer<T> buffer_type ;

  boost::array<std::size_t,1> sx = { 5  };
  boost::array<std::size_t,1> bx = { -2 };
  std::vector<T> datax(5);
  for (int n=0; n<datax.size(); n++) datax[n]=n+1;

  boost::array<std::size_t,1> sb = { 3 };
  boost::array<std::size_t,1> bb = { 1 };
  std::vector<T> datab(3);
  for (int n=0; n<datab.size(); n++) datab[n]=10*(n+1);

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
    NT2_TEST_EQUAL( dereference(b,boost::fusion::single_view<int>(i)), 3+i );
    
  for ( typename buffer_type::index_type i = x.lower(); i <= x.upper(); ++i )
    NT2_TEST_EQUAL( dereference(x,boost::fusion::single_view<int>(i)), 10*i );

}

//==============================================================================
// vector_buffer Range interface
//==============================================================================
struct f_
{
  template<class T> T operator()(T const& e) const { return 10*e; }
};
  
NT2_TEST_CASE_TPL(vector_buffer_iterator, NT2_TYPES )
{
  using nt2::memory::vector_buffer;

  typedef vector_buffer<T> buffer_type ;

  boost::array<std::size_t,1> sx = { 5  };
  boost::array<std::size_t,1> bx = { -2 };
  std::vector<T> data(5);
  for (int n=0; n<data.size(); n++) data[n]=(n+1);

  buffer_type x(data,sx,bx);
  f_ f;
  
  typename buffer_type::iterator b = x.begin();
  typename buffer_type::iterator e = x.end();

  std::transform(b,e,b,f);

  for ( typename buffer_type::index_type i = x.lower(); i <= x.upper(); ++i )
    NT2_TEST_EQUAL( dereference(x,boost::fusion::single_view<int>(i)), f(3+i) );
  
}
