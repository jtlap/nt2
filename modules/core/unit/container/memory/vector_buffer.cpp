//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2::memory::vector_buffer"

#include <nt2/core/container/memory/vector_buffer.hpp>

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
// Test for dynamic default vector_buffer ctor
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL(vector_buffer_default_ctor, NT2_TYPES )
{
  using nt2::memory::vector_buffer;

  typedef          vector_buffer<T>       buffer_type;
  typedef typename buffer_type::size_type size_type;

  buffer_type b;

  NT2_TEST_EQUAL( b.size()  , 0U      );

  boost::array<size_type,1> s = { 10 };
  b.resize(s);
  
  NT2_TEST_EQUAL    ( b.size()  , 10      );
}

////////////////////////////////////////////////////////////////////////////////
// Test for dynamic vector_buffer ctor
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL(vector_buffer_ctor, NT2_TYPES )
{
  using nt2::memory::vector_buffer;
  using nt2::memory::dereference;
  
  typedef          vector_buffer<T>              buffer_type;
  typedef typename buffer_type::size_type size_type;

  boost::array<size_type,1> ss = { 5 };
  boost::array<size_type,1> bs = { 0 };

  buffer_type b(ss,bs);

  NT2_TEST_EQUAL    ( b.size()  , 5U      );

  for (typename buffer_type::index_type i = 0; i < 5; ++i )
    dereference(b,boost::fusion::single_view<int>(i)) = typename buffer_type::value_type(1+i);

  for ( typename buffer_type::index_type i = 0; i < 5; ++i )
    NT2_TEST_EQUAL( dereference(b,boost::fusion::single_view<int>(i)), 1+i );
}

////////////////////////////////////////////////////////////////////////////////
// Test for dynamic vector_buffer copy ctor
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL(vector_buffer_copy2_ctor, NT2_TYPES )
{
  using nt2::memory::vector_buffer;
  using nt2::memory::dereference;
  
  typedef          vector_buffer<T>              buffer_type;
  typedef typename buffer_type::size_type size_type;

  boost::array<size_type,1> ss = { 5 };
  boost::array<size_type,1> bs = { 0 };

  buffer_type b(ss,bs);

  NT2_TEST_EQUAL    ( b.size()  , 5U      );

  for (typename buffer_type::index_type i = 0; i < 5; ++i )
    dereference(b,boost::fusion::single_view<int>(i)) = typename buffer_type::value_type(1+i);

  buffer_type x(b);

  NT2_TEST_EQUAL    ( x.size()  , 5U      );

  for ( typename buffer_type::index_type i = 0; i < 5; ++i )
    NT2_TEST_EQUAL( dereference(x,boost::fusion::single_view<int>(i)), 1+i );

}

////////////////////////////////////////////////////////////////////////////////
// Test for dynamic vector_buffer copy ctor
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL(vector_buffer_copy_ctor, NT2_TYPES )
{
  // using nt2::memory::vector_buffer;
  // using nt2::memory::dereference;
  
  // typedef          vector_buffer<T>              buffer_type;
  // typedef typename buffer_type::size_type size_type;

  // boost::array<size_type,1> ss = { 5 };
  // boost::array<size_type,1> bs = { 0 };

  // buffer_type b(ss,bs);

  // NT2_TEST_EQUAL    ( b.size()  , 5U      );

  // for (typename buffer_type::index_type i = 0; i < 5; ++i )
  //   dereference(b,boost::fusion::single_view<int>(i)) = typename buffer_type::value_type(1+i);

  // boost::array<size_type,1> ss_ = { 4 };
  // boost::array<size_type,1> bs_ = { -2 };
  // buffer_type x(b,ss_,bs_);

  // NT2_TEST_EQUAL    ( x.size()  , 4U      );

  // for ( typename buffer_type::index_type i = -2; i < 2; ++i ){
  //   NT2_TEST_EQUAL( dereference(x,boost::fusion::single_view<int>(i)), 3+i );
  // }

}


////////////////////////////////////////////////////////////////////////////////
// Test for dynamic buffer assignment
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL(vector_buffer_assignment, NT2_TYPES )
{
  using nt2::memory::vector_buffer;
  using nt2::memory::dereference;

  typedef          vector_buffer<T>       buffer_type;
  typedef typename buffer_type::size_type size_type;

  boost::array<size_type,1> ss = { 5 };
  boost::array<size_type,1> bs = { 0 };

  buffer_type b,x(ss,bs);

  for( typename buffer_type::index_type i = 0; i < 5; ++i )
    dereference(x,boost::fusion::single_view<int>(i)) = typename buffer_type::value_type(1+i);

  b = x;

  NT2_TEST_EQUAL    ( b.size()      , 5U  );

  for( typename buffer_type::index_type i = 0; i < 5; ++i )
    NT2_TEST_EQUAL( dereference(b,boost::fusion::single_view<int>(i)), 1+i );
}


////////////////////////////////////////////////////////////////////////////////
// Test for dynamic buffer assignment
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL(vector_buffer_std_vector_ctor, NT2_TYPES )
{
  using nt2::memory::vector_buffer;
  using nt2::memory::dereference;

  typedef          vector_buffer<T>       buffer_type;
  typedef typename buffer_type::size_type size_type;

  typedef std::vector<T> vector_type;

  vector_type v(3);
  typename vector_type::size_type v_sz = v.size();

  // assign some values:
  for (int n=0; n<v_sz; n++) v[n]=n+1;

  boost::array<size_type,1> ss = { 5 };
  boost::array<size_type,1> bs = { 0 };

  buffer_type b(v,ss,bs);



  NT2_TEST_EQUAL    ( b.size()      , 5U  );

  // for( typename buffer_type::index_type i = 0; i < 5; ++i )
  //   dereference(x,boost::fusion::single_view<int>(i)) = typename buffer_type::value_type(1+i);

  for( typename buffer_type::index_type i = 0; i < 3; ++i )
    NT2_TEST_EQUAL( dereference(b,boost::fusion::single_view<int>(i)), 1+i );
}


////////////////////////////////////////////////////////////////////////////////
// Test for dynamic vector_buffer swap
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL(vector_buffer_swap, NT2_TYPES )
{
  using nt2::memory::vector_buffer;
  using nt2::memory::dereference;
  
  typedef          vector_buffer<T>              buffer_type;
  typedef typename buffer_type::size_type size_type;

  boost::array<size_type,1> sx = { 5 };
  boost::array<size_type,1> bx = { 0 };

  boost::array<size_type,1> sb = { 3 };
  boost::array<size_type,1> bb = { -1 };

  buffer_type b(sb,bb),x(sx,bx);

  for( typename buffer_type::index_type i = 0; i < 5; ++i )
    dereference(x,boost::fusion::single_view<int>(i)) = typename buffer_type::value_type(1+i);
  for( typename buffer_type::index_type i = -1; i < 1; ++i )
    dereference(b,boost::fusion::single_view<int>(i)) = typename buffer_type::value_type(2+i);

  swap(b,x);

  NT2_TEST_EQUAL( b.size()      , 5U          );
  NT2_TEST_EQUAL( x.size()      , 3U          );

  for( typename buffer_type::index_type i = -1; i < 1; ++i )
    NT2_TEST_EQUAL( dereference(x,boost::fusion::single_view<int>(i)), 2+i );

  for( typename buffer_type::index_type i = 0; i < 5; ++i )
    NT2_TEST_EQUAL( dereference(b,boost::fusion::single_view<int>(i)), 1+i );
}

////////////////////////////////////////////////////////////////////////////////
// vector_buffer type has some dimensions
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL( vector_buffer_dimensions, NT2_TYPES)
{
  using nt2::meta::dimensions_of;
  using nt2::memory::vector_buffer;

  NT2_TEST_EQUAL((dimensions_of< vector_buffer<T> >::value), 1UL );
}

////////////////////////////////////////////////////////////////////////////////
// vector_buffer type has some value
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL( vector_buffer_values, NT2_TYPES)
{
  using boost::is_same;
  using boost::dispatch::meta::value_of;
  using nt2::memory::vector_buffer;
  using boost::mpl::_;

  vector_buffer<T> a0;
  NT2_TEST_EXPR_TYPE(a0, value_of<_>, T );
}

////////////////////////////////////////////////////////////////////////////////
// 1D buffer type has a model
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL( vector_buffer_models, NT2_TYPES )
{
  using boost::is_same;
  using boost::dispatch::meta::model_of;
  using boost::mpl::apply;
  using nt2::memory::vector_buffer;

  typedef typename model_of< vector_buffer<T> >::type model1d;

  NT2_TEST((is_same < typename apply<model1d,float>::type
                    , vector_buffer<float> >::value
          ));
}

