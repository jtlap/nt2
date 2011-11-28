/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::memory boost::array adaptation as a Buffer"

#include <nt2/core/container/memory/adapted/array.hpp>
#include <nt2/core/container/memory/dereference.hpp>
#include <nt2/sdk/memory/no_padding.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/array.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>

////////////////////////////////////////////////////////////////////////////////
// array type has some dimensions
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( std_array_dimensions )
{
  using boost::array;
  using nt2::meta::dimensions_of;

  NT2_TEST_EQUAL((dimensions_of< array<int,4> >::value), 1UL );
  NT2_TEST_EQUAL((dimensions_of< array<array<int,4>,4> >::value), 2UL );
  NT2_TEST_EQUAL((dimensions_of< array<array<array<int,4>,4>,4> >::value), 3UL);
}

////////////////////////////////////////////////////////////////////////////////
// array type has storage order
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( std_array_storage_order )
{
  using boost::array;
  using nt2::meta::storage_order_of;
  using nt2::C_order_;
  using boost::mpl::_;

  array<int,4> a0;
  array<array<int,4>,4> a1;
  array<array<array<int,4>,4>,4> a2;

  NT2_TEST_EXPR_TYPE(a0, storage_order_of<_>, C_order_ );
  NT2_TEST_EXPR_TYPE(a1, storage_order_of<_>, C_order_ );
  NT2_TEST_EXPR_TYPE(a2, storage_order_of<_>, C_order_ );

}


////////////////////////////////////////////////////////////////////////////////
// array type has some value
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( std_array_values )
{
  using boost::array;
  using boost::is_same;
  using boost::dispatch::meta::value_of;

  NT2_TEST((is_same< value_of< array<int,4> >::type, int>::value ));
  NT2_TEST((is_same< value_of< array<array<int,4>,4> >::type, int>::value ));
  NT2_TEST((is_same< value_of< array<array<array<int,4>,4>,4> >::type, int>::value ));
}
////////////////////////////////////////////////////////////////////////////////
// array type has a model
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( std_array_model )
{
  using boost::array;
  using boost::mpl::apply;
  using boost::is_same;
  using boost::dispatch::meta::model_of;

  typedef model_of< array<int,4> >::type model1d;
  typedef model_of< array<array<int,4>,3> >::type model2d;
  typedef model_of< array<array<array<int,4>,3>,2> >::type model3d;


  NT2_TEST((is_same<apply<model1d,float>::type, array<float,4> >::value ));
  NT2_TEST((is_same<apply<model2d,float>::type, array<array<float,4>,3> >::value ));
  NT2_TEST((is_same<apply<model3d,float>::type, array<array<array<float,4>,3>,2> >::value ));
}

////////////////////////////////////////////////////////////////////////////////
// array type has some dimensions
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( std_array_reference )
{
  using boost::array;
  using boost::is_same;
  using nt2::meta::dereference_;

  typedef array<array<array<int,2>,3>,4> base;

  NT2_TEST((is_same< dereference_<base&,1>::type, array<array<int,2>,3>& >::value) );
  NT2_TEST((is_same< dereference_<base&,2>::type, array<int,2>& >::value) );
  NT2_TEST((is_same< dereference_<base&,3>::type, int& >::value) );

  NT2_TEST((is_same< dereference_<base const&,1>::type, array<array<int,2>,3> const& >::value) );
  NT2_TEST((is_same< dereference_<base const&,2>::type, array<int,2> const& >::value) );
  NT2_TEST((is_same< dereference_<base const&,3>::type, int const& >::value) );
}

////////////////////////////////////////////////////////////////////////////////
// array type models Buffer Concept
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( std_array_1D_as_buffer )
{
  using boost::array;
  using nt2::memory::initialize;
  using nt2::memory::dereference;

  boost::array<double,5> tab;

  boost::array<std::size_t,1> sizes = {{5}};
  boost::array<std::size_t,1> bases = {{-2}};
  boost::array<std::size_t,1> pos;

  //////////////////////////////////////////////////////////////////////////////
  // array type supports being initialized externally
  //////////////////////////////////////////////////////////////////////////////
  initialize(tab, sizes, bases, nt2::memory::no_padding() );

  //////////////////////////////////////////////////////////////////////////////
  // array type supports R/W access through Position
  //////////////////////////////////////////////////////////////////////////////
  for(pos[0]=0;pos[0]<5;++pos[0])
    dereference<1UL>(tab,pos) = double(10*(1+pos[0]));

  for(pos[0]=0;pos[0]<5;++pos[0])
    NT2_TEST_EQUAL(dereference<1UL>(tab,pos), 10*(1+pos[0]) );
}

////////////////////////////////////////////////////////////////////////////////
// array type models Buffer Concept
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( std_array_2D_as_buffer )
{
  using boost::array;
  using nt2::memory::initialize;
  using nt2::memory::dereference;

  boost::array<boost::array<double,5>,2> tab;

  boost::array<std::size_t,2> sizes = {{5,2}};
  boost::array<std::size_t,2> bases = {{-2,0}};
  boost::array<std::size_t,2> pos;

  //////////////////////////////////////////////////////////////////////////////
  // array type supports being initialized externally
  //////////////////////////////////////////////////////////////////////////////
  initialize(tab, sizes, bases, nt2::memory::no_padding() );

  //////////////////////////////////////////////////////////////////////////////
  // array type supports R/W access through Position
  //////////////////////////////////////////////////////////////////////////////
  for(pos[1]=0;pos[1]<2;++pos[1])
    for(pos[0]=0;pos[0]<5;++pos[0])
      dereference<2UL>(tab,pos) = double(10*(1+pos[1]) + (1+pos[0]));

  for(pos[1]=0;pos[1]<2;++pos[1])
    for(pos[0]=0;pos[0]<5;++pos[0])
    NT2_TEST_EQUAL(dereference<2UL>(tab,pos), 10*(1+pos[1]) + (1+pos[0]) );
}


////////////////////////////////////////////////////////////////////////////////
// array type models Buffer Concept
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( std_array_3D_as_buffer )
{
  using boost::array;
  using nt2::memory::initialize;
  using nt2::memory::dereference;

  boost::array<boost::array<boost::array<double,2>,2>,3> tab;

  boost::array<std::size_t,3> sizes = {{2,2,2}};
  boost::array<std::size_t,3> bases = {{0,0,0}};
  boost::array<std::size_t,3> pos;

  //////////////////////////////////////////////////////////////////////////////
  // array type supports being initialized externally
  //////////////////////////////////////////////////////////////////////////////
  initialize(tab, sizes, bases, nt2::memory::no_padding() );

  //////////////////////////////////////////////////////////////////////////////
  // array type supports R/W access through Position
  //////////////////////////////////////////////////////////////////////////////
  for(pos[2]=0;pos[2]<3;++pos[2])
    for(pos[1]=0;pos[1]<2;++pos[1])
      for(pos[0]=0;pos[0]<2;++pos[0])
      dereference<3UL>(tab,pos) = double(100*(1+pos[2]) + 10*(1+pos[1]) + (1+pos[0]));

  for(pos[2]=0;pos[2]<3;++pos[2])
    for(pos[1]=0;pos[1]<2;++pos[1])
      for(pos[0]=0;pos[0]<2;++pos[0])
    NT2_TEST_EQUAL(dereference<3UL>(tab,pos), 100*(1+pos[2]) + 10*(1+pos[1]) + (1+pos[0]));
}
