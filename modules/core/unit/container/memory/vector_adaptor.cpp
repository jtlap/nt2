/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::memory std::vector adaptor"

#include <nt2/core/container/memory/adapted/buffer_adaptor.hpp>
#include <nt2/core/container/memory/adapted/vector.hpp>
#include <nt2/core/container/memory/dereference.hpp>
#include <nt2/sdk/memory/no_padding.hpp>
#include <boost/type_traits/is_same.hpp>
#include <vector>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>
#include <nt2/core/settings/sharing.hpp>


////////////////////////////////////////////////////////////////////////////////
// vector type has some dimensions
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL( std_vector_adaptor_dimensions, NT2_TYPES)
{
  using std::vector;
  using nt2::meta::dimensions_of;
  using nt2::memory::buffer_adaptor;
  using nt2::memory::no_padding;
  using nt2::owned_;

  typedef buffer_adaptor<std::vector<T>,boost::array<int,1>,boost::array<int,1>, no_padding, owned_ > type ;

  NT2_TEST_EQUAL((dimensions_of<type>::value), 1UL );
}



////////////////////////////////////////////////////////////////////////////////
// vector type has some value
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL( std_vector_values, NT2_TYPES)
{
  using std::vector;
  using boost::dispatch::meta::value_of;
  using nt2::memory::buffer_adaptor;
  using nt2::memory::no_padding;
  using nt2::owned_;
  using boost::mpl::_;


  typedef buffer_adaptor<std::vector<T>,boost::array<int,1>,boost::array<int,1>, no_padding, owned_ > type ;

  type t1;
  
  NT2_TEST_EXPR_TYPE(t1, value_of<_>, T );

}

////////////////////////////////////////////////////////////////////////////////
// vector type has a model
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL( std_vector_model, NT2_TYPES)
{
  using boost::mpl::apply;
  using boost::is_same;
  using boost::dispatch::meta::model_of;

  using std::vector;
  using nt2::memory::buffer_adaptor;
  using nt2::memory::no_padding;
  using nt2::owned_;
  using boost::mpl::_;


  // typedef buffer_adaptor<std::vector<T>,boost::array<int,1>,boost::array<int,1>, no_padding, owned_ > type ;

  // typedef model_of<type>::type model;

  // typedef buffer_adaptor<std::vector<float>,boost::array<int,1>,boost::array<int,1>, no_padding, owned_ > type_f ;


  // NT2_TEST((is_same<apply<model,float>::type, type_f >::value ));


}

////////////////////////////////////////////////////////////////////////////////
// vector type has some reference
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL( std_vector_bracket, NT2_TYPES)
{
  using std::vector;
  using boost::is_same;
  using nt2::memory::buffer_adaptor;
  using nt2::memory::no_padding;
  using nt2::owned_;

  boost::array<std::size_t,1> sizes = {{5}};
  boost::array<std::size_t,1> bases = {{-2}};
  boost::array<std::ptrdiff_t,1> pos;

  typedef buffer_adaptor<std::vector<T>, boost::array<std::size_t,1>, boost::array<std::size_t,1>, no_padding, owned_ > type ;

  type t1(bases,sizes);


  for(pos[0]=-2;pos[0]<=2;++pos[0]){
    t1[pos[0]]= T(10*(2+pos[0]));
  }

  for(pos[0]=-2;pos[0]<=2;++pos[0]){
    NT2_TEST_EQUAL(t1[pos[0]], 10*(2+pos[0]) );
  }

}


////////////////////////////////////////////////////////////////////////////////
// vector type is restructurable
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL( std_vector_restructure, NT2_TYPES)
{
  using std::vector;
  using boost::is_same;
  using nt2::memory::buffer_adaptor;
  using nt2::memory::no_padding;
  using nt2::owned_;

  boost::array<std::size_t,1> sizes = {{5}};
  boost::array<std::size_t,1> bases = {{-2}};
  boost::array<std::ptrdiff_t,1> pos;

  typedef buffer_adaptor<std::vector<T>, boost::array<std::size_t,1>, boost::array<std::size_t,1>, no_padding, owned_ > type ;

  type t1(bases,sizes);


  for(pos[0]=-2;pos[0]<=2;++pos[0]){
    t1[pos[0]]= T(10*(2+pos[0]));
  }

  for(pos[0]=-2;pos[0]<=2;++pos[0]){
    NT2_TEST_EQUAL(t1[pos[0]], 10*(2+pos[0]) );
  }



  boost::array<std::size_t,1> sizes_ = {{10}};
  boost::array<std::size_t,1> bases_ = {{-5}};


  restructure(t1,sizes_, bases_);


  for(pos[0]=-5;pos[0]<=4;++pos[0]){
    t1[pos[0]]= T(10*(5+pos[0]));
  }

  for(pos[0]=-5;pos[0]<=4;++pos[0]){
    NT2_TEST_EQUAL(t1[pos[0]], 10*(5+pos[0]) );
  }


}
