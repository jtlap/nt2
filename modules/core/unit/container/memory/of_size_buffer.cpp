//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2::memory of_size adaptation as a Buffer"

#include <nt2/core/utility/of_size/of_size.hpp>

#include <algorithm>
#include <boost/array.hpp>
#include <boost/fusion/adapted/array.hpp>
#include <boost/fusion/include/single_view.hpp>
#include <boost/fusion/include/make_vector.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

//==============================================================================
// of_size dimensions traits
//==============================================================================
NT2_TEST_CASE( of_size_dimensions )
{
  using boost::mpl::_;
  using boost::mpl::size_t;
  using nt2::meta::dimensions_of;

  using nt2::_0D;
  using nt2::_1D;
  using nt2::_2D;
  using nt2::_3D;
  using nt2::_4D;
  using nt2::of_size_;
    
  NT2_TEST_EXPR_TYPE(_0D()                , dimensions_of<_>, size_t<2> );
  NT2_TEST_EXPR_TYPE(_1D()                , dimensions_of<_>, size_t<2> );
  NT2_TEST_EXPR_TYPE(_2D()                , dimensions_of<_>, size_t<2> );
  NT2_TEST_EXPR_TYPE(_3D()                , dimensions_of<_>, size_t<2> );
  NT2_TEST_EXPR_TYPE(_4D()                , dimensions_of<_>, size_t<2> );
  NT2_TEST_EXPR_TYPE(of_size_<1>()        , dimensions_of<_>, size_t<2> );
  NT2_TEST_EXPR_TYPE((of_size_<1,2>())    , dimensions_of<_>, size_t<2> );
  NT2_TEST_EXPR_TYPE((of_size_<1,2,3>())  , dimensions_of<_>, size_t<2> );
  NT2_TEST_EXPR_TYPE((of_size_<1,2,3,4>()), dimensions_of<_>, size_t<2> );
}

//==============================================================================
// of_size_ value_of traits
//==============================================================================
NT2_TEST_CASE( of_size_value_of )
{
  using boost::mpl::_;
  using boost::dispatch::meta::value_of;
  using nt2::of_size_;
  using nt2::_0D;
  using nt2::_1D;
  using nt2::_2D;
  using nt2::_3D;
  using nt2::_4D;
  
  NT2_TEST_EXPR_TYPE(_0D(), value_of<_>, std::size_t );
  NT2_TEST_EXPR_TYPE(_1D(), value_of<_>, std::size_t );
  NT2_TEST_EXPR_TYPE(_2D(), value_of<_>, std::size_t );
  NT2_TEST_EXPR_TYPE(_3D(), value_of<_>, std::size_t );
  NT2_TEST_EXPR_TYPE(_4D(), value_of<_>, std::size_t );
  NT2_TEST_EXPR_TYPE((of_size_<1,2,3,3>()), value_of<_>, std::size_t );
}

//==============================================================================
// of_size_ model_of traits
//==============================================================================
template<class T, class U>
struct  apply_model
      : boost::mpl::apply < typename boost::dispatch::meta::model_of<T>::type
                          , U
                          >
{};

NT2_TEST_CASE_TPL( of_size_model_of, NT2_TYPES )
{
  using boost::dispatch::meta::model_of;
  using boost::mpl::_;
  using nt2::of_size_;
  using nt2::_0D;
  using nt2::_1D;
  using nt2::_2D;
  using nt2::_3D;
  using nt2::_4D;
  
  NT2_TEST_EXPR_TYPE(_0D(),(apply_model<_,T>),_0D);
  NT2_TEST_EXPR_TYPE(_1D(),(apply_model<_,T>),_1D);
  NT2_TEST_EXPR_TYPE(_2D(),(apply_model<_,T>),_2D);
  NT2_TEST_EXPR_TYPE(_3D(),(apply_model<_,T>),_3D);
  NT2_TEST_EXPR_TYPE(_4D(),(apply_model<_,T>),_4D);
  NT2_TEST_EXPR_TYPE((of_size_<1,2,3,4>()),(apply_model<_,T>),(of_size_<1,2,3,4>));
}

//==============================================================================
// Test for 1D dereference on of_size_
//==============================================================================
NT2_TEST_CASE( of_size_dereference )
{
  using boost::fusion::single_view;
  using nt2::memory::dereference;
  using nt2::of_size_;
  using nt2::_0D;
  using nt2::_1D;
  using nt2::_2D;
  using nt2::_3D;
  using nt2::_4D;

  _0D s0;
  _1D s1(1);
  _2D s2(1,2);
  _3D s3(1,2,3);
  _4D s4(1,2,3,4);
  
  for( int i=0; i<4; ++i )
    NT2_TEST_EQUAL( dereference(s0,single_view<int>(i)), 1 );
    
  for( int i=0; i<4; ++i )
    NT2_TEST_EQUAL( dereference(s4,single_view<int>(i)), 1+i );

  for( int i=0; i<4; ++i )
    NT2_TEST_EQUAL( dereference(of_size_<2,4,6,8>(),single_view<int>(i)), 2*(1+i) );

  for( int i=0; i<3; ++i )
    NT2_TEST_EQUAL( dereference(s3,single_view<int>(i)), 1+i );

  for( int i=0; i<3; ++i )
    NT2_TEST_EQUAL( dereference(of_size_<2,4,6>(),single_view<int>(i)), 2*(1+i) );

  for( int i=0; i<2; ++i )
    NT2_TEST_EQUAL( dereference(s2,single_view<int>(i)), 1+i );

  for( int i=0; i<2; ++i )
    NT2_TEST_EQUAL( dereference(of_size_<2,4>(),single_view<int>(i)), 2*(1+i) );

  for( int i=0; i<1; ++i )
    NT2_TEST_EQUAL( dereference(s1,single_view<int>(i)), 1+i );

  for( int i=0; i<1; ++i )
    NT2_TEST_EQUAL( dereference(of_size_<2>(),single_view<int>(i)), 2*(1+i) );
}

//==============================================================================
// Test for 2D dereference on of_size_
//==============================================================================
NT2_TEST_CASE( of_size_dereference_2D )
{
  using boost::fusion::make_vector;
  using nt2::memory::dereference;
  using nt2::of_size_;
  using nt2::_0D;
  using nt2::_1D;
  using nt2::_2D;
  using nt2::_3D;
  using nt2::_4D;

  _0D s0;
  _1D s1(1);
  _2D s2(1,2);
  _3D s3(1,2,3);
  _4D s4(1,2,3,4);
  
  for( int i=0; i<4; ++i )
    NT2_TEST_EQUAL( dereference(s0,make_vector(1,i)), 1 );
  
  for( int i=0; i<4; ++i )
    NT2_TEST_EQUAL( dereference(s4,make_vector(1,i)), 1+i );

  for( int i=0; i<4; ++i )
    NT2_TEST_EQUAL( dereference(of_size_<2,4,6,8>(),make_vector(1,i)), 2*(1+i) );

  for( int i=0; i<3; ++i )
    NT2_TEST_EQUAL( dereference(s3,make_vector(1,i)), 1+i );

  for( int i=0; i<3; ++i )
    NT2_TEST_EQUAL( dereference(of_size_<2,4,6>(),make_vector(1,i)), 2*(1+i) );

  for( int i=0; i<2; ++i )
    NT2_TEST_EQUAL( dereference(s2,make_vector(1,i)), 1+i );

  for( int i=0; i<2; ++i )
    NT2_TEST_EQUAL( dereference(of_size_<2,4>(),make_vector(1,i)), 2*(1+i) );

  for( int i=0; i<1; ++i )
    NT2_TEST_EQUAL( dereference(s1,make_vector(1,i)), 1+i );

  for( int i=0; i<1; ++i )
    NT2_TEST_EQUAL( dereference(of_size_<2>(),make_vector(1,i)), 2*(1+i) );
}
