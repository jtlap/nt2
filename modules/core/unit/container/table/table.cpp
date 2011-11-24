/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::table "

#include <nt2/table.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

////////////////////////////////////////////////////////////////////////////////
// table type has some dimensions
////////////////////////////////////////////////////////////////////////////////

NT2_TEST_CASE_TPL( table_dimensions ,NT2_TYPES)
{
  using nt2::table;
  using nt2::_1D;
  using nt2::_2D;
  using nt2::_3D;
  using nt2::_4D;
  using nt2::meta::dimensions_of;

  NT2_TEST_EQUAL( (dimensions_of<table<T,_1D> >::value), 1UL) ;
  NT2_TEST_EQUAL( (dimensions_of<table<T,_2D> >::value), 2UL) ;
  NT2_TEST_EQUAL( (dimensions_of<table<T,_3D> >::value), 3UL) ;
  NT2_TEST_EQUAL( (dimensions_of<table<T,_4D> >::value), 4UL) ;
}


////////////////////////////////////////////////////////////////////////////////
// table type has some value
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL( table_values, NT2_TYPES )
{
  using boost::is_same;
  using boost::dispatch::meta::value_of;
  using nt2::table;
  using nt2::_1D;
  using nt2::_2D;
  using nt2::_3D;
  using nt2::_4D;

  NT2_TEST((is_same< typename value_of< table<T,_1D> >::type, T>::value ));
  NT2_TEST((is_same< typename value_of< table<T,_2D> >::type, T>::value ));
  NT2_TEST((is_same< typename value_of< table<T,_3D> >::type, T>::value ));
  NT2_TEST((is_same< typename value_of< table<T,_4D> >::type, T>::value ));

}

////////////////////////////////////////////////////////////////////////////////
// table type has a model
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL( table_models, NT2_TYPES )
{
  using boost::is_same;
  using boost::dispatch::meta::model_of;
  using boost::mpl::apply;
  using nt2::table;
  using nt2::_1D;
  using nt2::_2D;
  using nt2::_3D;
  using nt2::_4D;

  typedef typename model_of< table<T,_1D> >::type model1d;
  typedef typename model_of< table<T,_2D> >::type model2d;
  typedef typename model_of< table<T,_3D> >::type model3d;
  typedef typename model_of< table<T,_4D> >::type model4d;

  NT2_TEST((is_same<typename apply<model1d,float>::type, table<float,_1D> >::value ));
  NT2_TEST((is_same<typename apply<model2d,float>::type, table<float,_2D> >::value ));
  NT2_TEST((is_same<typename apply<model3d,float>::type, table<float,_3D> >::value ));
  NT2_TEST((is_same<typename apply<model4d,float>::type, table<float,_4D> >::value ));


}
