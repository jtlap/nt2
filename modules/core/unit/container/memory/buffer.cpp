/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 0x01.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::memory::buffer"

#include <nt2/core/container/memory/buffer.hpp>
#include <nt2/core/container/memory/dereference.hpp>

#include <nt2/sdk/memory/slice.hpp>
#include <nt2/sdk/memory/allocator.hpp>
#include <nt2/sdk/memory/no_padding.hpp>
#include <nt2/sdk/memory/lead_padding.hpp>
#include <nt2/sdk/memory/global_padding.hpp>

#include <boost/array.hpp>
#include <boost/type_traits/is_same.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>

#define PADDING                                                                   \
(nt2::memory::no_padding)(nt2::memory::lead_padding)(nt2::memory::global_padding) \

////////////////////////////////////////////////////////////////////////////////
// Test for dynamic default buffer ctor
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL(buffer_default_ctor, NT2_TYPES )
{
  using nt2::memory::buffer;

  typedef          buffer<int>             buffer_type;
  typedef typename buffer<int>::size_type  size_type;
  const size_type s = 10;
  buffer_type b;

  NT2_TEST_EQUAL( b.size()  , 0U      );
  NT2_TEST_EQUAL( b.lower() ,  0      );
  NT2_TEST_EQUAL( b.upper() , -1      );
  NT2_TEST_EQUAL( b.begin() , (int*)(0) );

  b.resize(s);
  NT2_TEST_EQUAL( b.size()  , s       );
  NT2_TEST_EQUAL( b.lower() , 0       );
  NT2_TEST_EQUAL( b.upper() , (s-1)   );
  NT2_TEST_NOT_EQUAL( b.begin() , (int*)(0) );
  
}

////////////////////////////////////////////////////////////////////////////////
// Test for dynamic buffer ctor
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL(buffer_ctor, NT2_TYPES )
{
  using nt2::memory::buffer;

  typedef buffer<float> buffer_type;
  buffer_type b(0,5);

  NT2_TEST_EQUAL( b.size()      , 5U          );
  NT2_TEST_EQUAL( b.lower()     ,  0          );
  NT2_TEST_EQUAL( b.upper()     ,  4          );
  NT2_TEST_NOT_EQUAL( b.begin() , (float*)(0) );
  NT2_TEST_EQUAL( &b[b.lower()] , b.begin()   );

  for ( buffer_type::index_type i = b.lower(); i <= b.upper(); ++i )
    b[i] = buffer_type::value_type(1+i);

  for ( buffer_type::index_type i = b.lower(); i <= b.upper(); ++i )
    NT2_TEST_EQUAL( b[i], 1+i );
}

////////////////////////////////////////////////////////////////////////////////
// Test for dynamic buffer assignment
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL(buffer_assignment, NT2_TYPES )
{
  using nt2::memory::buffer;

  typedef buffer<float> buffer_type;
  buffer_type b,x(0,5);
  for ( buffer_type::index_type i = x.lower(); i <= x.upper(); ++i )
    x[i] = buffer_type::value_type(1+i);

  b = x;

  NT2_TEST_EQUAL( b.size()      , 5U          );
  NT2_TEST_EQUAL( b.lower()     ,  0          );
  NT2_TEST_EQUAL( b.upper()     ,  4          );
  NT2_TEST_NOT_EQUAL( b.begin() , (float*)(0) );
  NT2_TEST_EQUAL( &b[b.lower()] , b.begin()   );

  for ( buffer_type::index_type i = b.lower(); i <= b.upper(); ++i )
    NT2_TEST_EQUAL( b[i], 1+i );
}

// ////////////////////////////////////////////////////////////////////////////////
// // Test for dynamic buffer swap
// ////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL(buffer_swap, NT2_TYPES )
{
  using nt2::memory::buffer;

  typedef buffer<float> buffer_type;
  buffer_type b(-1,3),x(0,5);
  for ( buffer_type::index_type i = x.lower(); i <= x.upper(); ++i )
    x[i] = buffer_type::value_type(1+i);
  for ( buffer_type::index_type i = b.lower(); i <= b.upper(); ++i )
    b[i] = buffer_type::value_type(i);

  swap(b,x);

  NT2_TEST_EQUAL( b.size()      , 5U          );
  NT2_TEST_EQUAL( b.lower()     ,  0          );
  NT2_TEST_EQUAL( b.upper()     ,  4          );
  NT2_TEST_NOT_EQUAL( b.begin() , (float*)(0) );
  NT2_TEST_EQUAL( &b[b.lower()] , b.begin()   );

  NT2_TEST_EQUAL( x.size()      , 3U          );
  NT2_TEST_EQUAL( x.lower()     ,  -1         );
  NT2_TEST_EQUAL( x.upper()     ,   1         );
  NT2_TEST_NOT_EQUAL( x.begin() , (float*)(0) );
  NT2_TEST_EQUAL( &x[x.lower()] , x.begin()   );

  for ( buffer_type::index_type i = x.lower(); i <= x.upper(); ++i )
    NT2_TEST_EQUAL( x[i], i );

  for ( buffer_type::index_type i = b.lower(); i <= b.upper(); ++i )
    NT2_TEST_EQUAL( b[i], 1+i );
}


// ////////////////////////////////////////////////////////////////////////////////
// // buffer type has some dimensions
// ////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL( buffer_dimensions, NT2_TYPES)
{
  using nt2::meta::dimensions_of;
  using nt2::memory::buffer;

  NT2_TEST_EQUAL((dimensions_of< buffer<T> >::value), 1UL );

}


// ////////////////////////////////////////////////////////////////////////////////
// // buffer type has some dimensions
// ////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL( buffer_storage_order, NT2_TYPES)
{
  using nt2::meta::storage_order_of;
  using nt2::memory::buffer;
  using nt2::C_order_;
  using boost::mpl::_;

  buffer<T> a0;

  NT2_TEST_EXPR_TYPE(a0, storage_order_of<_>, C_order_ );

  //  NT2_TEST_EQUAL((dimensions_of< buffer<T> >::value), 1UL );

}

// ////////////////////////////////////////////////////////////////////////////////
// // array type has some value
// ////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL( buffer_values, NT2_TYPES)
{
  using boost::is_same;
  using boost::dispatch::meta::value_of;
  using nt2::memory::buffer;

  NT2_TEST((is_same< typename value_of< buffer<T> >::type, T>::value ));

}

////////////////////////////////////////////////////////////////////////////////
// array type has a model
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL( buffer_models, NT2_TYPES )
{
  using boost::is_same;
  using boost::dispatch::meta::model_of;
  using boost::mpl::apply;
  using nt2::memory::buffer;

  typedef typename model_of< buffer<T> >::type model1d;

  NT2_TEST((is_same<typename apply<model1d,float>::type, buffer<float> >::value ));

}


////////////////////////////////////////////////////////////////////////////////
// buffer has some reference
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL( buffer_reference, NT2_TYPES )
{
  using boost::is_same;
  using nt2::meta::dereference_;
  using nt2::memory::buffer;

  typedef buffer<T> base;

  NT2_TEST((is_same< typename dereference_<base&,1>::type, T& >::value) );

  NT2_TEST((is_same< typename dereference_<base const&,1>::type, T const&  >::value) );
}


////////////////////////////////////////////////////////////////////////////////
//buffer models Buffer Concept
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL( buffer_1D_as_buffer, PADDING)
{

  using nt2::memory::initialize;
  using nt2::memory::dereference;
  using nt2::memory::buffer;

  buffer<int> tab;

  boost::array<std::size_t,1> sizes = {{5}};
  boost::array<std::size_t,1> bases = {{-2}};
  boost::array<std::ptrdiff_t,1> pos;

  //////////////////////////////////////////////////////////////////////////////
  // array type supports being initialized externally
  //////////////////////////////////////////////////////////////////////////////
  initialize(tab, sizes, bases, T());

  //////////////////////////////////////////////////////////////////////////////
  // array type supports R/W access through Position
  //////////////////////////////////////////////////////////////////////////////
  for(pos[0]=-2;pos[0]<=2;++pos[0])
    dereference<1U>(tab,pos) = int(10*(1+pos[0]));

  for(pos[0]=-2;pos[0]<=2;++pos[0])
    NT2_TEST_EQUAL(dereference<1U>(tab,pos), 10*(1+pos[0]) );

  boost::array<std::size_t,1> sizes_1 = {{6}};
  boost::array<std::size_t,1> bases_1 = {{-1}};

 //////////////////////////////////////////////////////////////////////////////
  // array type supports being initialized externally
  //////////////////////////////////////////////////////////////////////////////
  resize(tab, sizes_1, bases_1, T());

  //////////////////////////////////////////////////////////////////////////////
  // array type supports R/W access through Position
  //////////////////////////////////////////////////////////////////////////////
  for(pos[0]=-1;pos[0]<=4;++pos[0])
    dereference<1U>(tab,pos) = int(10*(1+pos[0]));

  for(pos[0]=-1;pos[0]<=4;++pos[0])
    NT2_TEST_EQUAL(dereference<1U>(tab,pos), 10*(1+pos[0]) );


}
