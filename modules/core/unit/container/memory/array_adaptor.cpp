/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::memory boost::array adaptation as a Buffer"

#include <nt2/core/container/memory/adapted/buffer_adaptor.hpp>
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
NT2_TEST_CASE_TPL( std_array_dimensions, NT2_TYPES )
{
  using boost::array;
  using nt2::meta::dimensions_of;
  using nt2::memory::no_padding;
  using nt2::owned_;

  typedef buffer_adaptor<array<T,4>,boost::array<int,1>,boost::array<int,1>, no_padding, owned_ > type ;

  NT2_TEST_EQUAL((dimensions_of<type>::value), 1UL );

}

////////////////////////////////////////////////////////////////////////////////
// array type has some value
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL( std_array_values, NT2_TYPES)
{
  using boost::array;
  using boost::dispatch::meta::value_of;
  using nt2::memory::buffer_adaptor;
  using nt2::memory::no_padding;
  using nt2::owned_;
  using boost::mpl::_;


  typedef buffer_adaptor<boost::array<T,4>,boost::array<int,1>,boost::array<int,1>, no_padding, owned_ > type ;

  type t1;
  
  NT2_TEST_EXPR_TYPE(t1, value_of<_>, T );

}



////////////////////////////////////////////////////////////////////////////////
// array type has a model
////////////////////////////////////////////////////////////////////////////////
// NT2_TEST_CASE( std_array_model )
// {
//   using boost::array;
//   using boost::mpl::apply;
//   using boost::is_same;
//   using boost::dispatch::meta::model_of;

//   typedef model_of< array<int,4> >::type model1d;
//   typedef model_of< array<array<int,4>,3> >::type model2d;
//   typedef model_of< array<array<array<int,4>,3>,2> >::type model3d;


//   NT2_TEST((is_same<apply<model1d,float>::type, array<float,4> >::value ));
//   NT2_TEST((is_same<apply<model2d,float>::type, array<array<float,4>,3> >::value ));
//   NT2_TEST((is_same<apply<model3d,float>::type, array<array<array<float,4>,3>,2> >::value ));
// }

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

